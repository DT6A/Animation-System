/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : RND.H
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

#ifndef __PRIM_H_
#define __PRIM_H_

//#include "Z:\T05ANIM\stdafx.h"
#include "..\..\..\def.h"
#include "..\..\..\stock\stock.h"
#include "..\res\textures\textures.h"
#include "..\res\shaders\shaders.h"
#include "..\res\materials\materials.h"

namespace tagl
{
  class VERTEX
  {
  public:
    mth::vec<FLT> P;  // Position component
    mth::vec2<FLT> T; // Texture coordinate component
    mth::vec<FLT> N;  // Normal component
    mth::vec4<FLT> C; // Color conponent

    VERTEX( const mth::vec<FLT> & NewP, const mth::vec2<FLT> & NewT, const mth::vec<FLT> & NewN, const mth::vec4<FLT> & NewC ) : P(NewP), T(NewT), N(NewN), C(NewC)
    {
  
    }

    VERTEX( VOID ) : P(0), T(0), N(0), C(0)
    {
    
    }
  }; /* End of 'VERTEX' class*/

  class prim
  {
  public:
    matr Transform; // Transform matrix
    INT Index = -1; // Primitive index in primitives collection
    /* Primitive types enum */
    enum prim_type
    {
      POINT, MESH, LINE, LINESTRIP, STRIP
    } Type;

    UINT VA, VBuf, IBuf, // Primitive data
         NumOfI;         // Number of indexes

    material *Mtl;       // Primitive material

    prim( VOID );
    prim( const stock<VERTEX> &V, const stock<INT> &I, const prim_type PrType = MESH );
    ~prim( VOID );

    static prim * Load( const CHAR *FileName );
  protected:
    prim( const prim & Pr )
    {
    
    }
    VOID operator=( const prim & Pr )
    {
    
    }

  }; /* End of 'prim' class */

  class prims
  {
  public:
    stock<prim *> Prims; // Primitives colletcion

    prims( VOID ) : Prims()
    {
    
    }

    BOOL Load( const std::string &FileName, const matr &Transform );
    VOID SetShader( shader *Shader );
  };
} /* end of 'tagl' namespace */

#endif // __PRIM_H_
/* END OF 'PRIM.H' FILE */