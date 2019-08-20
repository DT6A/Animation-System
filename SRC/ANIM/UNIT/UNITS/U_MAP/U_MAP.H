/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/
 
/* FILE NAME   : U_MAP.H
 * PURPOSE     : WinAPI animation system.
 *               Animation system support.
 *               Units system.
 *               Map unit.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 23.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __U_MAP_H_
#define __U_MAP_H_

#include "..\..\..\anim.h"

namespace tagl
{
  class u_map : public unit
  {
  protected:
    vec L1 = {-17948.1836, -70.3664322, -1733.02466 };
    stock<vec> Locs;
    prims * Houses[22];
    FLT Angles[22];
    INT Ind = 0;
    prims *A01;
  public:
    u_map( VOID );
    ~u_map( VOID );
    VOID Render( VOID );
    VOID Response( VOID );
  }; /* End of 'u_ctrl' class */
} /* end of 'tagl' namespace */

#endif // __U_MAP_H_

/* END OF 'U_MAP.H' FILE */
