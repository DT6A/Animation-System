/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : RND.H
 * PURPOSE     : WinAPI animation system.
 *               Render system support.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 14.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __RND_H_
#define __RND_H_

//#include "Z:\T05ANIM\stdafx.h"
#include "..\..\def.h"
#include "..\..\stock\stock.h"
#include "prim\prim.h"
#include "res\manager.h"

namespace tagl
{
  class render
  {
  private:
    HDC hDC;     // Descriptor
    HGLRC hGLRC; // Pixel format
    HWND hWnd;   // Window handle
    INT W, H;    // Render size

    friend class image;

  public:
    camera Cam;
    static resource_manager<shader *> Shaders;
    static resource_manager<texture *> Textures;
    static resource_manager<material *> Materials;
    static stock<prim *> Primitives;

    render( HWND hWorkWnd );
    ~render( VOID );

    VOID UpdateProj( INT W, INT H );
    VOID Resize( INT W, INT H );
    VOID FrameStart( VOID );
    VOID FrameEnd( VOID );
    VOID FrameCopy( VOID );
    VOID Draw( const prim *Pr, const matr & World );
    VOID Draw( const prims *Prs, const matr & World );

    //HDC & GetHDC( VOID )
    
    

    static prim * CreatePrim( const CHAR * FileName );
    static prim * CreatePrim( const stock<VERTEX> & V, const stock<INT> & I, const prim::prim_type Type = prim::MESH );
    static material * CreateMaterial( const CHAR *Name, shader *NewShd, texture *NewTextures[8],
                                      const vec & NewKa, const vec & NewKd, const vec & NewKs,
                                      const FLT NewPh = 10, const FLT NewTrans = 1);
    static texture * CreateTexture( VOID );
    static texture * CreateTexture( const CHAR * FileName );
    static texture * CreateTexture( const CHAR *Name, const INT W, const INT H, const DWORD *Bits );
    static texture * CreateTexture( const CHAR *Name, const INT W, const INT H, const INT C, const DWORD *Bits );
    static shader * CreateShader( const CHAR * FileName );
  }; /* End of 'render' class */
} /* end of 'tagl' namespace */

#endif // __RND_H_

/* END OF 'RND.H' FILE */
