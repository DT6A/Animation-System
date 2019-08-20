/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : Prtim.CPP
 * PURPOSE     : WinAPI animation system.
 *               Render system support.
 *               Primitives support module.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 19.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

//#include "Z:\T05ANIM\stdafx.h"

#include "prim.h"
#include "..\rnd.h"
#include "..\topology\topology.h"

using namespace tagl;

/* prim constructor function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
prim::prim( VOID ) : Transform(), NumOfI(0)
{

} /* End of 'prim' constructor */

/* prim constructor function.
 * ARGUMENTS:
 *   - vertex data:
 *       stock V;
 *   - index data:
 *       stock I;
 *   - primitive type:
 *       prim_type PrType;
 * RETURNS: None.
 */
prim::prim( const stock<VERTEX> &V, const stock<INT> &I, const prim_type PrType ) : Transform()
{
  Type = PrType;
  NumOfI = I.Size();

  glGenBuffers(1, &VBuf);
  glGenBuffers(1, &IBuf);
  glGenVertexArrays(1, &VA);

  glBindVertexArray(VA);

  glBindBuffer(GL_ARRAY_BUFFER, VBuf);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX) * V.Size(), V.Array, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, VBuf);

  glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)sizeof(vec));
  glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)(sizeof(vec) + sizeof(vec2)));
  glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)(sizeof(vec) * 2 + sizeof(vec2)));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * I.Size(), I.Array, GL_STATIC_DRAW);

  glBindVertexArray(0);
} /* End of 'prim' constructor */

/* prim destructor function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
prim::~prim( VOID )
{
  glBindVertexArray(VA);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &VBuf);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &VA);
  glDeleteBuffers(1, &IBuf);
} /* End of 'prim' destructor */

/* Loading primitive from file function.
 * ARGUMENTS:
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (prim) loaded primitive.
 */
prim * prim::Load( const CHAR *FileName )
{
  CHAR Buf[1000];
  FILE *F;
  stock<VERTEX> V;
  stock<INT> I;
  INT NCounter = 0;

  if ((F = fopen(FileName, "r")) == NULL)
  {
    return nullptr;
  }

  while (fgets(Buf, sizeof(Buf), F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      V << VERTEX(vec(x, y, z), vec2(1), vec(0), vec4(1 - 0.3, 1 - 0.5, 1 - 0.7, 1));
    }
    else if (Buf[0] == 'v' && Buf[1] == 'n' && Buf[2] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      V[NCounter++].N = vec(x, y, z);
    }
    else if (Buf[0] = 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;
      CHAR
        f1[] = "%d %d %d",
        f2[] = "%d/%*d %d/%*d %d/%*d",
        f3[] = "%d//%*d %d//%*d %d//%*d",
        f4[] = "%d/%*d/%*d%d/%*d/%*d%d/%*d/%*d";

      sscanf(Buf + 2, f4, &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, f3, &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, f2, &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, f1, &n1, &n2, &n3) == 3;

      I << n1 - 1 << n2 - 1 << n3 - 1;
    }

  fclose(F);

  return new prim(V, I);
} /* End of 'Load' function */

/* Load primitives from 'G3DM' file function.
 * ARGUMENTS:
 *   - file name:
 *       const std::string &FileName;
 *   - transformation matrix:
 *       const matr &Transform;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL prims::Load( const std::string &FileName, const matr &Transform )
{
  FILE *F;
  DWORD Sign;
  INT NoofP = 0, NoofM = 0, NoofT = 0, i;

  /* Open file */
  if ((F = fopen(FileName.c_str(), "rb")) == NULL)
    return FALSE;
  /* Check signature */
  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"G3DM")
  {
    fclose(F);
    return FALSE;
  }

  /* Read quantities */
  fread(&NoofP, 4, 1, F);
  fread(&NoofM, 4, 1, F);
  fread(&NoofT, 4, 1, F);

  //Prims.Resize(NoofP);

  /* Primitive material indices */
  std::vector<INT> prims_mtl;
  prims_mtl.resize(NoofP);

  /* Load primitives */
  for (i = 0; i < NoofP; i++)
  {
    INT nv = 0, ni = 0, j;
    stock<VERTEX> V;
    stock<INT> I;

    fread(&nv, 4, 1, F);
    fread(&ni, 4, 1, F);
    fread(&prims_mtl[i], 4, 1, F);
    V.Resize(nv);
    I.Resize(ni);

    fread(&V.Array[0], 1, sizeof(VERTEX) * nv, F);
    fread(&I.Array[0], 1, sizeof(INT) * ni, F);

    for (j = 0; j < nv; j++)
    {
      V[j].P = Transform.PointTransform(V[j].P, Transform);
      V[j].N = Transform.NormalTransform(V[j].N, Transform).Normalize();
    }
    Prims.Add(render::CreatePrim(V, I));//new prim(topology::trimesh(V, I));
    Prims[i]->Index = i;
    Prims[i]->Mtl = nullptr;
  }

  /* Load materials */
  struct STORE_MATERIAL
  {
    CHAR Name[300]; /* Material name */

    /* Illumination coefficients */ 
    vec Ka, Kd, Ks;        /* Ambient, diffuse, specular coefficients */
    FLT Ph;                /* Phong power coefficient */
    FLT Trans;             /* Transparency factor */
    INT Tex[8];            /* Texture references */

    /* Shader string */
    CHAR ShaderStr[300];
    INT Shader;
  }; /* End of 'STORE_MATERIAL' struct */

  std::vector<material *> mtls;
  std::vector<STORE_MATERIAL> store_mtls;
  mtls.resize(NoofM);
  store_mtls.resize(NoofM);
  if (NoofM > 0)
  {
    fread(&store_mtls[0], sizeof(STORE_MATERIAL), NoofM, F);
    for (INT i = 0; i < NoofM; i++)
      mtls[i] = render::CreateMaterial(store_mtls[i].Name, nullptr, nullptr,
        store_mtls[i].Ka, store_mtls[i].Kd, store_mtls[i].Ks,
        store_mtls[i].Ph, store_mtls[i].Trans);
  }
  /* Load textures */
  std::vector<texture *> texs;
  texs.resize((NoofT < 8 ? 8 : NoofT));

  for (INT i = 0; i < (NoofT < 8 ? 8 : NoofT); i++)
    texs[i] = render::CreateTexture();

  for (i = 0; i < NoofT; i++)
  {
    CHAR Name[300];
    INT W, H, C;
    BYTE *mem;

    fread(Name, 1, 300, F);
    fread(&W, 4, 1, F);
    fread(&H, 4, 1, F);
    fread(&C, 4, 1, F);
    mem = new BYTE[W * H * C];
    fread(mem, C, W * H, F);
    texs[i] = render::CreateTexture(Name, W, H, C, (DWORD *)mem);
    delete[] mem;
  }
  fclose(F);

  for (INT i = 0; i < NoofM; i++)
  {
    for (INT t = 0; t < 8; t++)
      mtls[i]->Textures[t] = render::CreateTexture();
    mtls[i]->Shd = render::CreateShader("z:\\t05anim\\bin\\shaders\\deffault");
  }
 // for (INT i = 0; i < 8; i++)
   // texs[i] = render::CreateTexture();// new texture();
  /* Correct material texture references */
  for (INT i = 0; i < NoofM; i++)
    for (INT t = 0; t < 8; t++)
      if (store_mtls[i].Tex[t] != -1)
        mtls[i]->Textures[t] = texs[store_mtls[i].Tex[t]];

  /* Correct primitives material references */
  for (INT i = 0; i < NoofP; i++)
    if (prims_mtl[i] != -1)
      Prims[i]->Mtl = mtls[prims_mtl[i]];
  return TRUE;
} /* End of 'Load' function */

/* Set shader for all primitievs in collection function.
 * ARGUMENTS:
 *   - shader:
 *       shader *Shader
 * RETURNS: None.
 */
VOID prims::SetShader( shader *Shader )
{
  for (INT i = 0; i < Prims.Size(); i++)
    Prims[i]->Mtl->Shd = Shader;
} /* End of 'SetShader' function */

/* END OF 'PRIM.CPP' FILE */