/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : ANIM.H
 * PURPOSE     : WinAPI animation system.
 *               Animation system support.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 14.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __ANIM_H_
#define __ANIM_H_

//#include "Z:\T05ANIM\stdafx.h"

#include "..\def.h"
#include "..\win\win.h"
#include "rnd\rnd.h"
#include "rnd\topology\topology.h"
#include "..\stock\stock.h"
//#include "unit\unit.h"
#include "timer\timer.h"
#include "input\input.h"

namespace tagl
{
  class unit;
  class anim : public win, public render, public timer, public input
  {
  private:
    anim( VOID );
    ~anim( VOID );
    prim *Test;
  public:
    stock<unit *> Units;
    static anim & Get( VOID );
    VOID Init( VOID );
    VOID Close( VOID );
    VOID DoExit( VOID );
    VOID Render( VOID );

    VOID Paint( HDC hDC );
    VOID Timer( VOID );
    VOID Resize( VOID );
    VOID ReloadShaders( VOID );
    friend class u_ctrl;
  }; /* End of 'anim' class*/

  class unit
  {
  protected:
     anim &Ani = anim::Get();
  public:

    /* Unit constructor function.
     * ARGUMETNS: None.
     * RETURNS: None.
     */
    unit( VOID )
    {
    } /* End of 'unit' destructor */
    /* Unit destructor function.
     * ARGUMETNS: None.
     * RETURNS: None.
     */
    virtual ~unit( VOID )
    {

    } /* End of 'unit' destructor */
    /* Unit render function.
     * ARGUMETNS: None.
     * RETURNS: None.
     */
    virtual VOID Render( VOID )
    {

    } /* End of 'Render' function */
    /* Unit response function.
     * ARGUMETNS: None.
     * RETURNS: None.
     */
    virtual VOID Response( VOID )
    {
    
    }  /* End of 'Response' function */
  }; /* End of 'unit' class */

}

#endif // __ANIM_H_
/* END OF 'ANIM.H' FILE */
