/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : CAMERA.H
 * PURPOSE     : WinAPI animation system.
 *               Camera math support.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 24.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "matr.h"

/* Camera modes enum */
enum CamMode
{
  CamModeFrustum, CamModeOrtho
};

namespace mth
{
  template<class Type = double>
    class camera
    {
    public:
      Type Near, Far, ProjSize;                                  // Camera render parameters
      vec<Type> Loc, Dir, Up, Right, At, Up1;                    // Camera parameters
      matr<Type> MatrView, MatrFrustum, MatrOrtho, MatrProj, VP; // Camera matricies
      CamMode Mode;                                              // Camera render mode
      BOOL IsAttached = TRUE;                                    // Camera state
      Type FW, FH, WP, HP;                                       // Ray tracing parameters

      /* camera construcor function.
       * ARGUMENTS:
       *   - camera params:
       *       vec L, A, U;
       *       Type l, r, b, t, n, f;
       *   - camera render mode:
       *       CamMode m;
       * RETURNS: None.
       */
      camera( const vec<Type> & L, const vec<Type> & A, const vec<Type> & U,
         const Type & l, const Type & r, const Type & b, const Type & t, const Type & n, const Type & f,
         const CamMode & m = CamModeFrustum ) : Loc(L), At(A), Up(U), Near(n), Far(f)
      {
        UpdateView();
        UpdateProj(l, r, b, t);
        UpdateVP();
      } /* End of 'camera' constructor */

      /* camera construcor function.
       * ARGUMENTS:
       *   - camera params:
       *       vec L, A, U;
       *   - camera render mode:
       *       CamMode m;
       * RETURNS: None.
       */
      camera( const vec<Type> & L, const vec<Type> & A, const vec<Type> & U,
              const CamMode & m = CamModeFrustum ) : Loc(L), At(A), Up(U)
      {
        UpdateView();
        UpdateVP();
      } /* End of 'camera' constructor */
      
      /* camera construcor function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      camera( void ) : Loc(0), At(0), Up(0, 1, 0)
      {
        UpdateView();
        Far = 1;
        Near = 0;
        Mode = CamModeFrustum;
        UpdateProj(0, 1, 1, 0);
        UpdateVP();
      } /* End of 'camera' constructor */

      /* View matrix update function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      void UpdateView( void )
      {
        Dir = (At - Loc).Normalize();
        Right = (Dir % Up).Normalize();
        Up1 = (Right % Dir).Normalize();

        MatrView = MatrView.View(Loc, At, Up1, Dir, Right);
        UpdateVP();
      } /* End of 'UpdateView' function */

      /* Projection matrix update function.
       * ARGUMENTS: 
       *   - render params:
       *       Type l, r, b, t;
       * RETURNS: None.
       */
      void UpdateProj( const Type & l, const Type & r, const Type & b, const Type & t )
      {
        MatrFrustum = MatrProj.Frustum(l, r, b, t, Near, Far);
        MatrOrtho = MatrProj.Ortho(l, r, b, t, Near, Far);

        if (Mode == CamModeFrustum)
          MatrProj = MatrFrustum;
        else
          MatrProj = MatrOrtho;

        UpdateVP();
      } /* End of '' function */

      /* Projection matrix update function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      void UpdateProj( void )
      {
        if (Mode == CamModeFrustum)
          MatrProj = MatrFrustum;
        else
          MatrProj = MatrOrtho;

        UpdateVP();
      } /* End of 'UpdateProj' function */

      /* Projection * view matrix update function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      void UpdateVP( VOID )
      {
        VP = MatrView * MatrProj;
      } /* End of 'UpdateVP' function */

      /* Set camera render mode function.
       * ARGUMENTS: 
       *   - render mode:
       *       CamMode m;
       * RETURNS: None.
       */
      void ChangeMode( const CamMode m )
      {
        Mode = m;
        UpdateProj();
      } /* End of 'ChangeMode' function */

      /* Camera move forward function.
       * ARGUMENTS:
       *   - direction:
       *       FLT Direction;
       * RETURNS:
       */
      VOID MoveForward( const FLT Direction )
      {
        Loc += (Dir * Direction);
        At += (Dir * Direction);
        UpdateView();
      } /* End of 'MoveForward' function */

      /* Camera move right function.
       * ARGUMENTS:
       *   - direction:
       *       FLT Direction;
       * RETURNS:
       */
      VOID MoveRight( const FLT Direction )
      {
        Loc += (Right * Direction);
        At += (Right * Direction);
        UpdateView();
      } /* End of 'MoveRight' function */

      /* Camera turn around Y axis function.
       * ARGUMENTS:
       *   - Angle:
       *       FLT Angle;
       * RETURNS:
       */
      VOID TurnY( const FLT Angle )
      {
        vec<Type> TmpAt = (At - Loc);

        Dir = MatrView.VectorMulMatr(Dir, MatrView.Rotate(Angle, Up));
        At = MatrView.VectorMulMatr(TmpAt, MatrView.Rotate(Angle, Up)) + Loc;
        UpdateView();
      } /* End of 'TurnY' function */

      /* Camera turn around XZ axis function.
       * ARGUMENTS:
       *   - Angle:
       *       FLT Angle;
       * RETURNS:
       */
      VOID TurnXZ( const FLT Angle )
      {
        vec<Type> TmpAt = (At - Loc);

        Dir = MatrView.VectorMulMatr(Dir, MatrView.Rotate(Angle, Right));
        At = MatrView.VectorMulMatr(TmpAt, MatrView.Rotate(Angle, Right)) + Loc;
        UpdateView();
      } /* End of 'TurnY' function */

      /* Set camera ray tracing parameters function.
       * ARGUMENTS:
       *   - Frame size in pixels:
       *       Type FrameW, FrameH;
       * RETURNS:
       */
      VOID SetRayTracing( const Type FrameW, const Type FrameH )
      {
        FW = FrameW;
        FH = FrameH;

        Type ratio_x, ratio_y, Size = ProjSize;

        ratio_x = ratio_y = 1;

        if (FrameW > FrameH)
        {
          ratio_x = (Type)FrameW / FrameH;
          Size = FrameH;
        }
        else
        {
          ratio_y = (Type)FrameH / FrameW;
          Size = FrameW;
        }

        WP = ratio_x * Size;
        HP = ratio_y * Size;
      }
    }; /* End of 'Camera' class */
} /* end of 'mth' namespace */

/*  function.
 *  ARGUMENTS:
 *  RETURNS:
 */
template<class Type>
  std::ostream & operator<<( std::ostream &C, const mth::camera<Type> &Cam )
  {
    C << "Far: "<< Cam.Far << endl << "Near: "<< Cam.Near << endl << "Mode: "<< (Cam.Mode == CamModeFrustum ? "Frustum" : "Ortho") << endl << endl;
    C << "Loc: " << Cam.Loc << endl << "Dir: " << Cam.Dir << endl << "Up: " << Cam.Up << endl << "Right: " << Cam.Right << endl << "At: " << Cam.At << endl;
    C << endl << "View matrix" << endl << Cam.MatrView << endl << "Frustum matrix" << endl << Cam.MatrFrustum << endl << "Ortho matrix" << endl << Cam.MatrOrtho;

    return C;
  } /* End of 'operator' function */

#endif // __CAMERA_H_

/* END OF 'CAMERA.H' FILE */
