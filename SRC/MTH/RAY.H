/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : RAY.H
 * PURPOSE     : WinAPI animation system.
 *               Rays math support.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 24.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __RAY_H_
#define __RAY_H_

#include "mthdef.h"
#include "vec.h"

namespace mth
{
  template<class Type = double>
    class ray
    {
    public:
      vec Org, Dir; // Ray components

      /* Ray constructor function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      ray( VOID ) : Org(0), Dir(0)
      {
      
      } /* End of 'ray' constructor */

      /* Ray constructor function.
       * ARGUMENTS:
       *   - ray origin:
       *       vec O;
       *   - ray direction:
       *       vec D;
       * RETURNS: None.
       */
      ray( const vec &O, const vec &D ) : Org(O), Dir(D)
      {
        Dir = Dir.Normalize();
      } /* End of 'ray' construcor */

      /* Get point in ray function.
       * ARGUMENTS:
       *   - distance from origin:
       *       Type t;
       * RETURNS:
       *   (vec) point on ray.
       */
      vec operator()( const Type t )
      {
        return Org + Dir * t;
      } /* End of 'operator()' function */

    };

}

#endif // __RAY_H_
/* END OF 'RAY.H' FILE */
