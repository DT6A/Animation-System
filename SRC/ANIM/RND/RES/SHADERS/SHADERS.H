/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : SHADERS.H
 * PURPOSE     : WinAPI animation system.
 *               Render system support.
 *               Shaders system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 19.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __SHADERS_H_
#define __SHADERS_H_

#include <assert.h>
//#include "Z:\T05ANIM\stdafx.h"
#include "..\..\..\..\def.h"

namespace tagl
{
  class shader
  {
  public:
    INT ProgId; // Shader program id

    friend class render;
    template<class Type> friend class resource_manager;

    VOID Apply( VOID ) const;
    VOID Reload( const CHAR *FolderName );

  private:
    CHAR * LoadTextFormFile( const CHAR * FileName );
    VOID ShaderLog( const CHAR * Prefix, const CHAR * Type, const CHAR * Text );
  protected:
    shader( const CHAR *FolderName );
    ~shader( VOID );
    shader( const shader &Sh )
    {
      assert(0);
    }
    VOID operator=( const shader &Sh )
    {
      assert(0);
    }
  }; /* End of 'shader' class */
} /* end of 'tagl' namespace */

#endif // __SHADERS_H_

/* END OF 'SHADERS.H' FILE */
