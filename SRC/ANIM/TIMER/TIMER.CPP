/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TIMER.CPP
 * PURPOSE     : WinAPI animation system.
 *               Timer support.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 14.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

//#include "..\..\stdafx.h"
#include "timer.h"

using namespace tagl;

/* timer constructor function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
timer::timer( VOID )
{
  LARGE_INTEGER t;

  /* Timer init */
  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFps = t.QuadPart;
  PauseTime = 0;
} /* End of 'timer' constructor */

/* Timer response function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID timer::TimerRender( HWND & hWnd )
{
  LARGE_INTEGER t;

  FrameCounter++;
  QueryPerformanceCounter(&t);
  
  /* Global time */
  GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;

  /* Time wigh pause */
  if (IsPause)
  {
    DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    DeltaTime = GlobalDeltaTime;
    Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }

  /* FPS */
  if (t.QuadPart - OldTimeFps > TimePerSec)
  {
    CHAR str[100];

    FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFps);
    OldTimeFps = t.QuadPart;
   // sprintf(str, "FPS: %.5f", FPS);
    //SetWindowText(hWnd, str);
    FrameCounter = 0; 
  }
  OldTime = t.QuadPart;
} /* End of 'TimerRender' function */

/* END OF 'TIMER.CPP' FILE */