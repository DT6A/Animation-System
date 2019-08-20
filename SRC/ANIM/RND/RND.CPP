/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : RND.CPP
 * PURPOSE     : WinAPI animation system.
 *               Render system support.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 19.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

//#include "Z:\T05ANIM\stdafx.h"
#include "..\anim.h"
#include "rnd.h"

using namespace tagl;

resource_manager<shader *> render::Shaders;
resource_manager<texture *> render::Textures;
resource_manager<material *> render::Materials;
stock<prim *> render::Primitives;

/* Render constructor function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
render::render( HWND hWorkWnd ) : Cam(vec(1, 0, 0), vec(-100, 0, 0), vec(0, 1, 0))
{
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};
  HFONT hFnt, hOldFnt;

  hDC = GetDC(hWorkWnd);

  /*** OpenGL initialisation ***/
  /* Point format description */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(hDC, &pfd);
  DescribePixelFormat(hDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  SetPixelFormat(hDC, i, &pfd);

  /* Creating build context */
  hGLRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hGLRC);

  glewInit();

  hFnt = CreateFont(47, 0, 0, 0, FW_BOLD, FALSE, FALSE,
    FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
    VARIABLE_PITCH | FF_SCRIPT, "Courier New");
  hOldFnt = (HFONT)SelectObject(hDC, hFnt);
  wglUseFontBitmaps(hDC, 0, 256, 102);
  hOldFnt = (HFONT)SelectObject(hDC, hOldFnt);
  DeleteObject(hFnt);

  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.3, 0.5, 0.7, 1);

  render::Cam.Near = 0.1;
  render::Cam.Far = 20000;
  render::Cam.ProjSize = 0.1;
} /* End of 'render' constructor */

/* Render destrucot function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
render::~render( VOID )
{
  for (int i = 0; i < render::Primitives.Size(); i++)
    delete Primitives.Array[i];
} /* End of 'render' destructor */

/* Render projection update function.
 * ARGUMENTS:
 *  - new size:
 *      INT W, H;
 * RETURNS: None.
 */
VOID render::UpdateProj( INT W, INT H )
{
  DBL ratio_x, ratio_y;

  ratio_x = ratio_y = render::Cam.ProjSize / 2;

  if (W > H)
    ratio_x *= (DBL)W / H;
  else
    ratio_y *= (DBL)H / W;

  render::Cam.UpdateProj(-ratio_x, ratio_x, -ratio_y, ratio_y);
} /* End of 'UpdateProj' function */

/* Render resize function.
 * ARGUMENTS:
 *   - new size:
 *       INT W, H;
 * RETURNS: None.
 */
VOID render::Resize( INT W, INT H )
{
  UpdateProj(W, H);
  glViewport(0, 0, W, H);
} /* End of 'Resize' function */

/* Render start function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID render::FrameStart( VOID )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  /*glBegin(GL_TRIANGLES);
  glColor3d(0, 0, 1);
  glVertex3d(-0.6, 0.5, 0);
  glColor3d(0, 1, 0);
  glVertex3d(-0.6, -0.5, 0);
  glColor3d(0, 1, 1);
  glVertex3d(0.6, 0.5, 0); 

  glEnd();*/
} /* End of 'FrameStart' function */

/* Render end function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID render::FrameEnd( VOID )
{
  glFinish();
} /* End of 'FrameEnd' function */

/* Frame copy function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID render::FrameCopy( VOID )
{
  SwapBuffers(hDC);
} /* End of 'FrameCopy' function */

/* Draw primitive function.
 * ARGUMENTS:
 *   - primitive to draw:
 *       prim V;
 *   - world transform matrix:
 *       matr World;
 * RETURNS: None.
 */
VOID render::Draw( const prim *Pr, const matr & World )
{
  INT PrType, prg, loc;
  matr
    W  = Pr->Transform * World,
    WVP = W * Cam.VP,
    MatrNorm = W.Inverse();//.Transpose();

  glLoadMatrixf(&(WVP[0]));

  if (Pr->Mtl != nullptr)
  {
    prg = Pr->Mtl->MaterialApply();

    if ((loc = glGetUniformLocation(prg, "MatrWVP")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, &WVP[0]);
    if ((loc = glGetUniformLocation(prg, "MatrNorm")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, &MatrNorm[0]);
    if ((loc = glGetUniformLocation(prg, "MatrW")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, &W[0]);
    if ((loc = glGetUniformLocation(prg, "MatrVP")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, &(Cam.VP[0]));
    if ((loc = glGetUniformLocation(prg, "CamPos")) != -1)
      glUniform3fv(loc, 1, &(Cam.Loc.GetField(0)));

    if (Pr->IBuf != -1)
      if ((loc = glGetUniformLocation(prg, "Index")) != -1)
        glUniform1i(loc, Pr->Index);
  }
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);

  PrType = Pr->Type == Pr->MESH ? GL_TRIANGLES : GL_TRIANGLE_STRIP;

  glBindVertexArray(Pr->VA);
  if (Pr->IBuf == 0)
    glDrawArrays(PrType, 0, Pr->NumOfI);
  else
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glDrawElements(PrType, Pr->NumOfI, GL_UNSIGNED_INT, NULL);
  }
  glBindVertexArray(0);

  glUseProgram(0);
} /* End of 'Draw' function */

/* Draw primitivies collection function.
 * ARGUMENTS:
 *   - primitivies to draw:
 *   - world transform matrix:
 *       matr World;
 * RETURNS: None.
 */
VOID render::Draw( const prims *Prs, const matr & World )
{
  /*for (INT i = 0; i < Prs->Prims.Size(); i++)
    Draw(Prs->Prims[i], World); //Prs->Prims[i]->Transform); */
  INT i;

  for (i = 0; i < Prs->Prims.Size(); i++)
    if (Prs->Prims[i]->Mtl != nullptr && Prs->Prims[i]->Mtl->Trans >= 1)
      Draw(Prs->Prims[i], World);


  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  for (i = 0; i < Prs->Prims.Size(); i++)
    if (Prs->Prims[i]->Mtl != nullptr && Prs->Prims[i]->Mtl->Trans < 1)
      Draw(Prs->Prims[i], World);

  glCullFace(GL_BACK);
  for (i = 0; i < Prs->Prims.Size(); i++)
    if (Prs->Prims[i]->Mtl != nullptr && Prs->Prims[i]->Mtl->Trans < 1)
      Draw(Prs->Prims[i], World);

  glDisable(GL_CULL_FACE);
} /* End of 'Draw' function */

/* Create primitive from file function.
 * ARGUMENTS:
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (prim*) loaded primitive.
 */
prim * render::CreatePrim( const CHAR * FileName )
{
  prim *Pr = prim::Load(FileName);

  Primitives.Add(Pr);
  return Pr;
} /* End of 'CreatePrim' function */

/* Create primitive from data function.
 * ARGUMENTS:
 *   - verticies:
 *       stock<VERTEX> V;
 *   - indexes:
 *       stock<INT> I;
 *   - primitive type:
 *       prim_type Type
 * RETURNS:
 *   (prim*) primitive.
 */
prim * render::CreatePrim( const stock<VERTEX> & V, const stock<INT> & I, const prim::prim_type Type )
{
  prim *Pr = new prim(V, I, Type);

  Primitives.Add(Pr);
  return Pr;
} /* End of 'CreatePrim' function */

/* Create shader from files function.
 * ARGUMENTS:
 *   - shader prefix:
 *        CHAR * FileName;
 * RETURNS:
 *   (shader *) shader.
 */
shader * render::CreateShader( const CHAR * FileName )
{
  shader *Sh;
  if ((Sh = Shaders.Find(FileName)) != nullptr)
    return Sh;
  Sh = new shader(FileName);
  Shaders.Add(Sh, FileName);

  return Sh;
} /* End of 'CreateShader' function */

/* Create empty texture function.
 * ARGUMENTS: None
 * RETURNS:
 *   (texture *) texture.
 */
texture * render::CreateTexture( VOID )
{
  texture *Tex;
  if ((Tex = Textures.Find("Empty")) != nullptr)
    return Tex;
  Tex = new texture();
  Textures.Add(Tex, "Empty");

  return Tex;
} /* End of 'CreateTexture' function */


/* Create texture from file function.
 * ARGUMENTS:
 *   - file name:
 *        CHAR * FileName;
 * RETURNS:
 *   (texture *) texture.
 */
texture * render::CreateTexture( const CHAR * FileName )
{
  texture *Tex;
  if ((Tex = Textures.Find(FileName)) != nullptr)
    return Tex;
  Tex = new texture(FileName);
  Textures.Add(Tex, FileName);

  return Tex;
} /* End of 'CreateTexture' function */


/* Create texture from data function.
 * ARGUMENTS:
 *   - texture name:
 *        CHAR *Name;
 *   - size:
 *        INT W, H;
 *   - pixels data:
 *       DWORD *Bits;
 * RETURNS:
 *   (texture *) texture.
 */
texture * render::CreateTexture( const CHAR *Name, const INT W, const INT H, const DWORD *Bits )
{
  texture *Tex;
  if ((Tex = Textures.Find(Name)) != nullptr)
    return Tex;
  Tex = new texture(W, H, Bits);
  Textures.Add(Tex, Name);

  return Tex;
} /* End of 'CreateTexture' function */

  /* Create texture from data function.
  * ARGUMENTS:
  *   - texture name:
  *        CHAR *Name;
  *   - size:
  *        INT W, H;
  *   - pixels data:
  *       DWORD *Bits;
  * RETURNS:
  *   (texture *) texture.
  */
texture * render::CreateTexture( const CHAR *Name, const INT W, const INT H, const INT C, const DWORD *Bits )
{
  texture *Tex;
  if ((Tex = Textures.Find(Name)) != nullptr)
    return Tex;
  Tex = new texture(W, H, C, Bits);

  Textures.Stock[Name] = Tex;//(Tex, Name);

  return Tex;
} /* End of 'CreateTexture' function */


/* Create material function.
 * ARGUMENTS:
 * ARGUMETNS:
 *   - material shader:
 *       shader *NewShd;
 *   - material textures:
 *       texture **NewTextures;
 *   - light coefitients:
 *       vec NewKa, NewKd, NewKs;
 *   - phong coefitient:
 *       FLT NewPh;
 *   - transparency:
 *       FLT NewTrans;
 * RETURNS:
 *   (material *) material.
 */
material * render::CreateMaterial( const CHAR *Name, shader *NewShd, texture *NewTextures[8],
                                   const vec & NewKa, const vec & NewKd, const vec & NewKs,
                                   const FLT NewPh, const FLT NewTrans )
{

  material *Mat;
  if ((Mat = Materials.Find(Name)) != nullptr)
    return Mat;
  Mat = new material(NewShd, NewTextures, NewKa, NewKd, NewKs, NewPh, NewTrans);
  Materials.Add(Mat, Name);

  return Mat;
} /* End of 'CreateMaterial' function */

/* END OF 'RND.CPP' FILE */