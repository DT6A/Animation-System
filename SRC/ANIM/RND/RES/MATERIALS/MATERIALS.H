/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MATERIALS.H
 * PURPOSE     : WinAPI animation system.
 *               Render system support.
 *               Materials system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 19.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __MATERIALS_H_
#define __MATERIALS_H_

//#include "Z:\T05ANIM\stdafx.h"

#include "..\..\..\..\def.h"
#include "..\shaders\shaders.h"
#include "..\textures\textures.h"

namespace tagl
{
  class material
  {
  public:
    vec Ka, Kd, Ks;        // Lighting coefitients
    FLT 
      Ph,                  // Phong coefitient
      Trans;               // Transparency
    shader *Shd;           // Shader
    texture * Textures[8]; // Textures

    friend class render;
    friend class prim;
    template<class Type> friend class resource_manager;

    INT MaterialApply( VOID );
  protected:
    material( shader *NewShd = nullptr, texture *NewTextures[8] = nullptr,
              const vec & NewKa = vec(1), const vec & NewKd = vec(1), const vec & NewKs = vec(1),
              const FLT NewPh = 10, const FLT NewTrans = 1);


  }; /* End of 'material' class */
} /* end of 'tagl' namespace */

#endif // __MATERIALS_H_

/* END OF 'MATERIALS.H' FILE */
