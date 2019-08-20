/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/
 
/* FILE NAME   : U_CONTROL.H
 * PURPOSE     : WinAPI animation system.
 *               Animation system support.
 *               Units system.
 *               Control unit.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 19.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __U_CONTROL_H_
#define __U_CONTROL_H_

//#include "Z:\T05ANIM\stdafx.h"
//#include "..\..\..\unit\unit.h"
#include "..\..\..\anim.h"

namespace tagl
{
  class u_ctrl : public unit
  {
  protected:
    FLT 
      Angle,           // Camera angle
      Speed = 30 * 10; // Camera speed
  public:
    u_ctrl( VOID );
    ~u_ctrl( VOID );
    VOID Render( VOID );
    VOID Response( VOID );
  }; /* End of 'u_ctrl' class */
} /* end of 'tagl' namespace */

#endif // __U_CONTROL_H_

/* END OF 'UNIT.H' FILE */
