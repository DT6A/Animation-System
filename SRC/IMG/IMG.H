/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : IMG.H
 * PURPOSE     : WinAPI animation system.
 *               Images system support.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 16.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __IMG_H_
#define __IMG_H_

//#include "Z:\T05ANIM\stdafx.h"
#include "..\def.h"

namespace tagl
{
  class image
  {
  public:
    INT W, H;    // Image size in pixels
    DWORD *Bits; // Image pixels
    HBITMAP hBm; // WinAPI bitmap handle

    image( const CHAR *FileName );
    ~image( VOID );

    DWORD ImageGet( INT X, INT Y ) const;
    //VOID ToTexture( VOID ) const;
  }; /* End of 'image' class */
} /* end of 'tagl' namespace */

#endif // __IMG_H_

/* END OF 'IMAGES.H' FILE */