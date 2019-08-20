/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MANAGER.H
 * PURPOSE     : WinAPI animation system.
 *               Render system support.
 *               Resources manager.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 15.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __MANAGER_H_
#define __MANAGER_H_

//#include "Z:\T05ANIM\stdafx.h"
#include "..\..\..\def.h"

using namespace std;

namespace tagl
{
  template<class Type>
    class resource_manager
    {
    public:
      map<string, Type> Stock;

      /* resourse_manager destructor function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      ~resource_manager( VOID )
      {
        for (auto r : Stock)
          delete r.second;
      } /* End of 'resource_manager' destructor */

      /* Add to stock function.
       * ARGUMENTS:
       *   - data to add:
       *       Type Res;
       * RETURNS:
       *   (resource_manager) resource manager reference.
       */
      resource_manager & Add( const Type & Res, const CHAR *Name )
      {
        if (Stock.find(Name) != Stock.end())
          return *this;

        Stock[Name] = Res;

        return *this;
      } /* End of 'Add' function */

      /* Add to stock function.
       * ARGUMENTS:
       *   - element name:
       *       string Res;
       * RETURNS:
       *   (Type *) resource manager reference.
       */
      Type Find( const string & Name )
      {
        if (Stock.find(Name) == Stock.end())
          return nullptr;
        return Stock[Name];
      } /* End of 'Add' function */
    }; /* End of 'resource_manager' class */
} /* end of 'tagl' namespace */

#endif // __MANAGER_H_

/* END OF 'MANAGER.H' FILE */
