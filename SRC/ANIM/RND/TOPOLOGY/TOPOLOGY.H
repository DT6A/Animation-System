/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TOPOLOGY.H
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

#ifndef __TOPOLOGY_H_
#define __TOPOLOGY_H_

//#include "Z:\T05ANIM\stdafx.h"
#include "..\prim\prim.h"
#include "..\rnd.h"

namespace tagl
{
  class topology
  {
  public:
    virtual ~topology( VOID )
    {
    
    }
    virtual prim * ToPrim( VOID ) const
    {
      return new prim();
    }
  }; /* End of 'topology' class */

  class topology_mesh : public topology
  {
  private:
    stock<VERTEX> V;
    stock<INT> I;
    INT W, H;
  public:
    topology_mesh( const stock<VERTEX> NewV = stock<VERTEX>(), const stock<INT> NewI = stock<INT>()) : V(NewV), I(NewI)
    {
    
    }

    prim * ToPrim( VOID )
    {
      for (INT i = 0, k = 0, v = 0; i < H - 1; i++)
      {
        for (INT j = 0; j < W; j++)
        {
          I << (v + W);
          I << v++;
        }
        if (i < H - 2)
          I << -1;
      }

      return render::CreatePrim(V, I, prim::LINE);//new prim(V, I, prim::LINE);
    }

    VOID CreateGrid( const INT W, const INT H );
    VOID CreateSphere( const vec & Loc, const FLT R, const INT W, const INT H );
    VOID EvalNormals( VOID );
    VOID CreatePlane( const vec & Loc, const vec U, const vec V, const INT W, const INT H );
    VOID CreateHeightmap( const CHAR *FileName, const FLT Scale );

  }; /* End of 'topology' class */
} /* end of 'tagl' namespace */

#endif // __TOPOLOGY_H_

/* END OF 'TOPOLOGY.H' FILE */
