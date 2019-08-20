/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TIMER.H
 * PURPOSE     : WinAPI animation system.
 *               Timer support.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 14.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __TIMER_H_
#define __TIMER_H_

#include "..\..\def.h"

namespace tagl
{
  class timer
  {
  protected:
    UINT64
      StartTime,                   // Start program time
      OldTime,                     // Time from program start to previous frame
      OldTimeFps,                  // Old time FPS measurement
      PauseTime,                   // Time during pause period
      TimePerSec,                  // Timer resolution
      FrameCounter;                // Frames counter
  public:
    DBL 
      GlobalTime, GlobalDeltaTime, // Global time and interframe interval
      Time, DeltaTime,             // Time with pause and interframe interval
      FPS;                         // Frames per second value
    BOOL IsPause;                  // Pause flag

   timer( VOID );

   VOID TimerRender( HWND & hWnd );
  }; /* End of 'timer' class */
} /* end of 'tagl' namespace */

#endif // __TIMER_H_

/* END OF 'TIMER.H' FILE */