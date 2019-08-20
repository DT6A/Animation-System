/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TEXTURES.H
 * PURPOSE     : WinAPI animation system.
 *               Render system support.
 *               Textures system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 19.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __TEXTURES_H_
#define __TEXTURES_H_

#include <assert.h>

#include "..\..\..\..\def.h"

namespace tagl
{
  class texture
  {
  public:
    INT TextureId; // Texture GPU id

    friend class render;
    friend class prim;
    template<class Type> friend class resource_manager;

    VOID Apply( const INT Index ) const;

  protected:
    texture( const INT W, const INT H, const DWORD *Bits );
    texture( const INT W, const INT H, const INT C, const DWORD *Bits );
    texture( VOID ) : TextureId(-1)
    {
    
    }
    texture( const CHAR *FileName );
    ~texture( VOID );
    texture( const texture &Sh )
    {
      assert(0);
    }
    VOID operator=( const texture &Sh )
    {
      assert(0);
    }


  }; /* End of 'texture' class */
} /* end of 'tagl' namespace */

#endif // __TEXTURES_H_

/* END OF 'TEXTURES.H' FILE */
