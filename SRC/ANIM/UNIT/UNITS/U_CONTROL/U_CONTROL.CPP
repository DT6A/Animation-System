/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/
 
/* FILE NAME   : U_CONTROL.CPP
 * PURPOSE     : WinAPI animation system.
 *               Animation system support.
 *               Units system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 19.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

//#include "Z:\T05ANIM\stdafx.h"
#include "u_control.h"
//#include "..\..\..\anim.h"

using namespace tagl;

/* Unit constructor function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
u_ctrl::u_ctrl( VOID ) : unit(), Angle(0)
{
} /* End of 'u_ctrl' constructor */

/* Unit destructor function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
u_ctrl::~u_ctrl( VOID )
{

} /* End of 'u_ctrl' destructor */

/* Unit render function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
VOID u_ctrl::Render( VOID )
{
  glLineWidth(2);
  glLoadMatrixf(&Ani.Cam.VP[0]);
  glBegin(GL_LINES);
    glColor3d(1, 0, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(400000, 0, 0);
    glColor3d(0, 1, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 400000, 0);
    glColor3d(0, 0, 1);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, 400000);
  glEnd();
  glLineWidth(1);

  INT len;
  CHAR Buf[100];
  
  glLoadIdentity();
  glColor3d(0.6, 1, 0.6);
  glRasterPos2d(-1, 0.9);
  glListBase(102);
  len = sprintf(Buf, "FPS: %.3f", Ani.FPS);

  glCallLists(len, GL_UNSIGNED_BYTE, Buf);

} /* End of 'Render' function */

/* Unit response function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
VOID u_ctrl::Response( VOID )
{
 
  // Switch fullscreen
  if (anim::input::keyboard::KeysClick['F'])
  {
    Ani.IsFullScreen = 1 - Ani.IsFullScreen;
    Ani.FlipFullScreen(Ani.IsFullScreen);
  }
  // Camera movement
  if (!Ani.Cam.IsAttached)
  {
    if (anim::input::keyboard::Keys['O'])
      Speed -= 100 * Ani.GlobalDeltaTime;
    if (anim::input::keyboard::Keys['P'])
      Speed += 100 * Ani.GlobalDeltaTime;
    if (anim::input::keyboard::KeysClick['P'] && anim::input::keyboard::Keys[VK_SHIFT])
      Ani.IsPause = 1 - Ani.IsPause;
    if (!anim::input::keyboard::Keys[VK_CONTROL])
    {
      if (anim::input::keyboard::Keys['W'] && !anim::input::keyboard::Keys[VK_SHIFT])
        Ani.Cam.MoveForward(Speed * Ani.GlobalDeltaTime);
      if (anim::input::keyboard::Keys['S'])
        Ani.Cam.MoveForward(-Speed * Ani.GlobalDeltaTime);
      if (anim::input::keyboard::Keys['A'])
        Ani.Cam.MoveRight(-Speed * Ani.GlobalDeltaTime);
      if (anim::input::keyboard::Keys['D'])
        Ani.Cam.MoveRight(Speed * Ani.GlobalDeltaTime);
    }
    if (anim::input::keyboard::Keys[VK_LEFT])
      Ani.Cam.TurnY(90.0 * Ani.GlobalDeltaTime);
    if (anim::input::keyboard::Keys[VK_RIGHT])
      Ani.Cam.TurnY(-90.0 * Ani.GlobalDeltaTime);
    if (anim::input::keyboard::Keys[VK_UP])
    {
      Angle = (Angle + 90.0 * Ani.GlobalDeltaTime) > 90 ? 90 : (Angle + 90.0 * Ani.GlobalDeltaTime);
      if (Angle < 90)
        Ani.Cam.TurnXZ(90.0 * Ani.GlobalDeltaTime);
    }
    if (anim::input::keyboard::Keys[VK_DOWN])
    {
      Angle = (Angle - 90.0 * Ani.GlobalDeltaTime) < -90 ? -90 : (Angle - 90.0 * Ani.GlobalDeltaTime);
      if (Angle > -90)
        Ani.Cam.TurnXZ(-90.0 * Ani.GlobalDeltaTime);
    }
  }

  if (anim::input::keyboard::KeysClick['V'])
    Ani.Cam.IsAttached = 1 - Ani.Cam.IsAttached;
  // Wireframe
  if (anim::input::keyboard::KeysClick['W'] && anim::input::keyboard::Keys[VK_SHIFT])
  {
    static BOOL IsWF = FALSE;

    if (!IsWF)
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      IsWF = 1 - IsWF;
    }
    else
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      IsWF = 1 - IsWF;
    }
  }

  // Exit
  if (anim::input::keyboard::KeysClick[VK_ESCAPE])
    Ani.DoExit();
} /* End of 'Response' function */

/* END OF 'u_ctrl.CPP' FILE */