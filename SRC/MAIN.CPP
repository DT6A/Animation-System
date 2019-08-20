/***************************************************************
* Copyright (C) 2018
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME   : MAIN.CPP
 * PURPOSE     : WinAPI animation system.
 *               Main module.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 12.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

//#include "Z:\T05ANIM\stdafx.h"
#include "anim\ANIM.H"
#include "anim\unit\units\u_test\u_test.h"
#include "anim\unit\units\u_map\u_map.h"
#include "anim\unit\units\u_control\u_control.h"

using namespace std;

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  tagl::anim &Animation = tagl::anim::Get();

  //mciSendString("open \"BIN\\262_19ce9c896a7fcf4aa5741e2a3d9a732d.mp3\" type mpegvideo alias mp3", nullptr, 0, nullptr);
  //mciSendString("play mp3 from 0", nullptr, 0, nullptr);

  Animation.Units << new tagl::u_map() << new tagl::u_ctrl() << new tagl::u_test();

  Animation.Run();
} /* End of 'WinMain' function *

/* END OF 'MAIN.CPP' FILE */
