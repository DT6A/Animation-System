/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : ANIM.CPP
 * PURPOSE     : WinAPI animation system.
 *               Animation system support.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 19.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

//#include "Z:\T05ANIM\stdafx.h"

#include "anim.h"

using namespace tagl;


//anim unit::Ani = anim::Get();
/* Animation system construcot function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
anim::anim( VOID ) : win(), render(win::hWnd), timer()
{
} /* End of 'anim' constructor */

/* Animation system destrucot function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
anim::~anim( VOID )
{

} /* End of 'anim' destructor */

/* Get animation instance function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (anim&) animation instance.
 */
anim & anim::Get( VOID )
{
  static anim Instance;

  return Instance;
} /* End of 'Get' function */

/* Animation initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID anim::Init( VOID )
{
  
  //shader Sh("bin/shaders/test");
}

/* Animation close function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID anim::Close( VOID )
{
  for (int i = 0; i < Units.Size(); i++)
    delete Units.Array[i];
 /* for (int i = 0; i < render::Shaders.Size(); i++)
    delete Shaders.Array[i];
  for (int i = 0; i < render::Textures.Size(); i++)
    delete Textures.Array[i];
  for (int i = 0; i < render::Materials.Size(); i++)
    delete Materials.Array[i]; */

} /* End of 'Close' function */

VOID anim::DoExit( VOID )
{
  PostMessage(anim::win::hWnd, WM_CLOSE, 0, 0);
}

/* Animation system render frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID anim::Render( VOID )
{
  anim::TimerRender(anim::win::hWnd);
  anim::ObtainState(anim::win::hWnd);

  //anim::render::Cam.UpdateView();

  //Cam.Loc = vec(Cam.Loc[0], Cam.Loc[1] + GlobalTime, Cam.Loc[2]);

  // Units response
  for (int i = 0; i < Units.Size(); i++)
    Units[i]->Response();

  anim::FrameStart();
  // Draw units
  for (int i = 0; i < Units.Size(); i++)
    Units[i]->Render();

  anim::FrameEnd();
  anim::FrameCopy();

  InvalidateRect(anim::win::hWnd, NULL, FALSE);
} /* End of 'Render' function */

VOID anim::Paint( HDC hDC )
{
}

/* Timer handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID anim::Timer( VOID )
{
  static DBL LastReload = 0;
  Render();
  LastReload += DeltaTime;
  if (LastReload > 3)
  {
    ReloadShaders();
    LastReload = 0;
  }
} /* End of 'Paint' function */

/* Change window size handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID anim::Resize( VOID )
{
  render::Resize(win::W, win::H);
} /* End of 'Resize' function */

/* Reload all shaders function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID anim::ReloadShaders( VOID )
{
  for (auto &r : render::Shaders.Stock)
  {
    //delete r.second;
    //r.second = new shader(r.first.c_str());
    //const CHAR *Name = r.first.c_str();
    r.second->Reload(r.first.c_str());
  }
} /* End of 'ReloadShaders' function */

/* END OF 'ANIM.CPP' FILE */