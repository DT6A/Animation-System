/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/
 
/* FILE NAME   : INPUT.CPP
 * PURPOSE     : WinAPI animation system.
 *               Input system support.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 14.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "input.h"
//#include "Z:\T05ANIM\stdafx.h"

using namespace tagl;

INT input::mouse::Mx = 0;
INT input::mouse::My = 0; 
INT input::mouse::Mz = 0;
INT input::mouse::Mdx = 0;
INT input::mouse::Mdy = 0;
INT input::mouse::Mdz = 0;
INT input::mouse::MouseWheel = 0;

BYTE* input::keyboard::Keys = new BYTE[256];
BYTE* input::keyboard::KeysClick = new BYTE[256];
BYTE* input::keyboard::OldKeys = new BYTE[256];


/* Keyboard state obtain function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID input::keyboard::ObtainState( VOID )
{
  GetKeyboardState(Keys);

  for (INT i = 0; i < 256; i++)
  {
    Keys[i] >>= 7;
    if (!OldKeys[i] && Keys[i])
      KeysClick[i] = TRUE;
    else
      KeysClick[i] = FALSE;
  }
  memcpy(OldKeys, Keys, 256);
} /* End of 'ObtainState' function */

/* Mouse state obtain function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID input::mouse::ObtainState( HWND & hWnd )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);
  Mdx = pt.x - Mx;
  Mdy = pt.y - My;
  Mx = pt.x;
  My = pt.y;
  Mz += Mdz = MouseWheel;
  MouseWheel = 0;
} /* End of 'ObtainState' function */


/* Input state obtain function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID input::ObtainState( HWND & hWnd )
{
  input::keyboard::ObtainState();
  input::mouse::ObtainState(hWnd);
} /* End of 'ObtainState' function */

/* END OF 'INPUT.CPP' FILE */
