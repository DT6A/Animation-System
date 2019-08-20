/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/
 
/* FILE NAME   : INPUT.H
 * PURPOSE     : WinAPI animation system.
 *               Input system support.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 20.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __INPUT_H_
#define __INPUT_H_

//#include <mmsystem.h>
#include "..\..\def.h"
//#include "Z:\T05ANIM\stdafx.h"
//#pragma comment(lib, "winmm")

/* Joystick axis value obtain macro function */
//#define GET_JOYSRIC_AXIS(A) \
//  (2.0 * (ji.dw####A##pos - jc.w##A##min) / (ji.w####A##max - jc.w##A##min - 1) - 1)

namespace tagl
{
  class input
  {
  protected:
    VOID ObtainState( HWND & hWnd );

    class keyboard
    {
    public:
      static BYTE
        *Keys,      // Current keys states
        *OldKeys,   // Previous frame key states
        *KeysClick; // Click key flag


    public:
      static VOID ObtainState( VOID );
    }; /* End of 'keyboard' class */

    class mouse
    {
    public:
      static INT 
        Mx, My,        // Mouse cursor position
        Mz,            // Mouse wheel absolute value
        Mdx, Mdy, Mdz, // Delta values of mouse axis
        MouseWheel;    // Global mouse wheel delta value

    public:
      static VOID ObtainState( HWND & hWnd );
    }; /* End of 'mouse' class */

    class joystick
    {

    }; /* End of 'joystick' class */
    friend class u_ctrl;
    friend class u_test;
    friend class u_map;
    ~input( VOID )
    {
      delete[] keyboard::Keys;
      delete[] keyboard::KeysClick;
      delete[] keyboard::OldKeys;
    }
  }; /* End of 'input' class */
}

#endif // __INPUT_H_

/* END OF 'INPUT.H' FILE */