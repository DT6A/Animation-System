/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TOPOLOGY.CPP
 * PURPOSE     : WinAPI animation system.
 *               Render system support.
 *               Topology system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 16.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "topology.h"
#include "..\..\..\img\img.h"

using namespace tagl;

/* Grid creation function.
 * ARGUMENTS:
 *   - grid size:
 *       INT W, H;
 * RETURNS: None.
 */
VOID topology_mesh::CreateGrid( const INT W, const INT H )
{
  for (INT i = 0; i < H; i++)
    for (INT j = 0; j < W; j++)
    {
      vec P(i, 0, j);
      vec2 T(j / (W - 1.0), i / (H - 1.0));
      vec N(0, 1, 0);
      vec4 C(1);
      V << VERTEX(P, T, N, C);
    }

  this->W = W;
  this->H = H;
}

/* Sphere creation function.
 * ARGUMENTS:
 *   - location:
 *       vec Loc;
 *   - radius:
 *       FLT R;
 *   - grid size:
 *       INT W, H;
 * RETURNS: None.
 */
VOID topology_mesh::CreateSphere( const vec & Loc, const FLT R, const INT W, const INT H )
{
  CreateGrid(W, H);
  
  for (INT i = 0, v = 0; i < H; i++)
  {
    DBL theta = (H - i - 1) * mth::PI / (H - 1),
      sit = sin(theta), cot = cos(theta);

    for (INT j = 0; j < W; j++, v++)
    {
      DBL phi = j * 2 * mth::PI / (W - 1),
        sip = sin(phi), cop = cos(phi),
        x = sit * sip,
        y = cot,
        z = sit * cop;

      V[v].P = vec(Loc[0] + x * R, Loc[1] + y * R, Loc[2] + z * R);
      V[v].N = vec(x, y, z);
    }
  }
} /* End of 'CreateSphere' funcrtion */


/* Evaluate topology normals function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID topology_mesh::EvalNormals( VOID )
{
  for (INT i = 0, k = 0; i < H; i++)
    for (INT j = 0; j < W; j++, k++)
      V[k++].N = vec(0);

  for (INT i = 0, k = 0; i < H - 1; i++)
    for (INT j = 0; j < W - 1; j++, k++)
    {
      VERTEX
        p00 = V[k],
        p01 = V[k + 1],
        p10 = V[k + W],
        p11 = V[k + W + 1];
      vec N;

      N = ((p00.P - p10.P) % (p11.P - p10.P)).Normalize();

      p00.N += N;
      p10.N += N;
      p11.N += N;

      N = ((p11.P - p01.P) % (p00.P - p01.P)).Normalize();

      p00.N += N;
      p01.N += N;
      p11.N += N;
    }

  for (INT i = 0; i < H * W; i++)
    V[i].N = V[i].N.Normalize();
} /* End of 'EvalNormals' function */

/* Plane creation function.
 * ARGUMENTS:
 *   - location:
 *       vec Loc;
 *   - directions:
 *       vec U, V;
 *   - grid size:
 *       INT W, H;
 * RETURNS: None.
 */
VOID topology_mesh::CreatePlane( const vec & Loc, const vec U, const vec V, const INT W, const INT H )
{
  CreateGrid(W, H);

  vec N = (V % U).Normalize();

  for (INT i = 0, v = 0; i < H; i++)
  {
    DBL sy = i / (H - 1.0);
    for (INT j = 0; j < W; j++, v++)
    {
      DBL sx = j / (W - 1.0);
      
      topology_mesh::V[v].P = Loc + ((U * sx) + (V * sy));
      topology_mesh::V[v].N = N;
      topology_mesh::V[v].T = vec2(sx, sy);
    }
  }
} /* End of 'CreatePlane' function */

/* Heightmap creation from file function function.
 * ARGUMENTS:
 *   - file name:
 *       string FileName;
 * RETURNS: None.
 */
VOID topology_mesh::CreateHeightmap( const CHAR *FileName, const FLT Scale )
{
  vec P = vec(0), Du = vec(1, 0, 0), Dv = vec(0, 0, 1);
  image img(FileName);

  CreatePlane(P, Du, Dv, img.W, img.H);

  vec N = V[0].N;

  for (INT i = 0, v = 0; i < H; i++)
    for (INT j = 0; j < W; j++, v++)
    {
      DWORD col = img.ImageGet(j, i);

      V[v].P += N * (((col >> 8) & 0xFF) / 255.0 * Scale);
      V[v].T = vec2((FLT)j / W, (FLT)i / H);
    }

  //EvalNormals();
} /* End of 'CreateHeightmap' function */
