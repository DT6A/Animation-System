/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/
 
/* FILE NAME   : U_TEST.H
 * PURPOSE     : WinAPI animation system.
 *               Animation system support.
 *               Units system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 23.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __U_TEST_H_
#define __U_TEST_H_

//#include "Z:\T05ANIM\stdafx.h"
//#include "..\..\..\unit\unit.h"
#include "..\..\..\anim.h"

namespace tagl
{
  class u_test : public unit
  {
  protected:
    FLT Velocity = 0, RotationSpeed = 0, Rotation = 0, Acceleration = 35000, MaxSpeed = 50000;
    vec Location = vec(2500 * 5, 90, 2500 * 5), V = vec(0, 0, 0), A = vec(0, 0, -10), Dir = vec(0, 0, -1), CamOffset = vec(0, 0, 650), FPPos = vec(-35, 60, 0);
    BOOL IsFP = TRUE, IsMoving = FALSE;
  public:
    prim *Cow;
    prim *Plane;
    prims *Btr;


    u_test( VOID );
    ~u_test( VOID );
    VOID Render( VOID );
    VOID Response( VOID );
  }; /* End of 'unit' class */
} /* end of 'tagl' namespace */

#endif // __U_TEST_H_

/* END OF 'UNIT.H' FILE */
