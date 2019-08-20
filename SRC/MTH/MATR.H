/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MATR.H
 * PURPOSE     : WinAPI animation system.
 *               Matrix math support.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 12.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __MATR_H_
#define __MATR_H_

#include "vec.h"

namespace mth
{
  template<class Type = double>
    class matr
    {
    private : 
      Type A[4][4];

      /* Degree to radian function.
       * ARGUMENTS:
       *   - angle in degrees:
       *       Type a;
       * RETURNS:
       *   (Type) angle in radians.
       */
      static Type Degree2Rad( const Type & a )
      {
        return Type(a / 180 * 3.1415926535);
      } /* End of 'Degree2Rad' function */

    public:
      /* matr constructor function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) identity matrix.
       */
      matr( void )
      {
        for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++)
            A[i][j] = (i == j);
      } /* End of matr constructor */

      /* matr constructor function.
       * ARGUMENTS:
       *   - number to fill matrix with:
       *       Type C;
       * RETURNS:
       *   (matr) matrix filled with given number.
       */
      explicit matr( const Type & C )
      {
        for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++)
            A[i][j] = C;
      } /* End of matr constructor */

      /* matr constructor function.
       * ARGUMENTS:
       *   - numbers to fill matrix with:
       *       Type a00 - a33;
       * RETURNS:
       *   (matr) matrix filled with given numbers.
       */
      matr( const Type &a00, const Type &a01, const Type &a02, const Type &a03,
            const Type &a10, const Type &a11, const Type &a12, const Type &a13,
            const Type &a20, const Type &a21, const Type &a22, const Type &a23,
            const Type &a30, const Type &a31, const Type &a32, const Type &a33)
      {
        A[0][0] = a00, A[0][1] = a01, A[0][2] = a02, A[0][3] = a03,
        A[1][0] = a10, A[1][1] = a11, A[1][2] = a12, A[1][3] = a13,
        A[2][0] = a20, A[2][1] = a21, A[2][2] = a22, A[2][3] = a23,
        A[3][0] = a30, A[3][1] = a31, A[3][2] = a32, A[3][3] = a33;
      } /* End of matr constructor */

      /* operator* overload function.
       * ARGUMENTS:
       *   - matrix to multiply:
       *       matr M;
       * RETURNS:
       *   (matr) matricies multiplication result.
       */
      matr<Type> operator*( const matr<Type> & M ) const
      {
        matr<Type> A(0);
        int k;

        for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++)
            for (A.A[i][j] = 0, k = 0; k < 4; k++)
              A.A[i][j] += this->A[i][k] * M.A[k][j];
         return A;
       } /* End of 'operator*' function */

      /* operator= overload function.
       * ARGUMENTS:
       *   - matrix to copy:
       *       matr M;
       * RETURNS:
       *   (matr) matricies multiplication result.
       */
      matr<Type> & operator=( const matr<Type> & M )
      {
        for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++)
              A[i][j] = M.A[i][j];
        return *this;
       } /* End of 'operator*' function */

      /* operator! overload function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) matrix determinator.
       */
      Type operator!( void ) const
      {
        return this->Determ();
      } /* End of 'operator!' function */

      /* operator[] overload function.
       * ARGUMENTS:
       *   - matrix element index:
       *       int i;
       * RETURNS:
       *   (Type) matrix element.
       */
      Type & operator[]( int i )
      {
        if (i < 0)
          i = 0;
        else if (i >= 16)
          i = 15;

        return A[i / 4][i % 4];
      } /* End of 'operator[]' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static matr<Type> Identity( void )
      {
        return matr<Type>();
      } /* End of '' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static matr<Type> Translate( const vec<Type> & T )
      {
        matr A = Identity();

        A.A[3][0] = T[0];
        A.A[3][1] = T[1];
        A.A[3][2] = T[2];

        return A;
      } /* End of '' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static matr<Type> RotateX( Type a )
      {
        matr<Type> A = Identity();

        a = Degree2Rad(a);

        Type si = sin(a), co = cos(a);

        A.A[1][1] = co;
        A.A[1][2] = si;
        A.A[2][1] = -si;
        A.A[2][2] = co;

        return A;
      } /* End of '' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static matr<Type> RotateY( Type a )
      {
        matr<Type> A = Identity();

        a = Degree2Rad(a);

        Type si = sin(a), co = cos(a);

        A.A[0][0] = co;
        A.A[0][2] = -si;
        A.A[2][0] = si;
        A.A[2][2] = co;

        return A;
      } /* End of '' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static matr<Type> RotateZ( Type a )
      {
        matr<Type> A = Identity();

        a = Degree2Rad(a);

        Type si = sin(a), co = cos(a);

        A.A[0][0] = co;
        A.A[0][1] = si;
        A.A[1][0] = -si;
        A.A[1][1] = co;

        return A;
      } /* End of '' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static matr<Type> Rotate( Type a, const vec<Type> & R )
      {
        Type A = Degree2Rad(a), si = sin(A), co = cos(A);
        vec<Type> V = R.Normalize();

        return matr<Type>(co + V[0] * V[0] * (1 - co),       V[0] * V[1] * (1 - co) + V[2] * si, V[0] * V[2] * (1 - co) - V[1] * si, 0,
                          V[1] * V[0] * (1 - co) - V[2] * si, co + V[1] * V[1] * (1 - co),       V[1] * V[2] * (1 - co) + V[0] * si, 0,
                          V[2] * V[0] * (1 - co) + V[1] * si, V[2] * V[1] * (1 - co) - V[0] * si, co + V[2] * V[2] * (1 - co),       0,
                          0, 0, 0, 1);
      } /* End of '' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static matr<Type> Scale( const vec<Type> S )
      {
        matr<Type> A = Identity();

        A.A[0][0] = S[0];
        A.A[1][1] = S[1];
        A.A[2][2] = S[2];

        return A;
      } /* End of '' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      matr<Type> Transpose( void ) const
      {
        matr<Type> M;

        for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++)
            M.A[i][j] = this->A[j][i];

        return M;
      } /* End of '' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static Type Determ3x3( const Type a11, const Type a12, const Type a13,
                             const Type a21, const Type a22, const Type a23,
                             const Type a31, const Type a32, const Type a33)
      {
        return Type(a11 * a22 * a33 - a11 * a23 * a32 - a12 * a21 * a33 + a12 * a23 * a31 + a13 * a21 * a32 - a13 * a22 * a31);
      } /* End of '' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      Type Determ( void ) const
      {
        return
          A[0][0] * Determ3x3(A[1][1], A[1][2], A[1][3],
                              A[2][1], A[2][2], A[2][3],
                              A[3][1], A[3][2], A[3][3]) -
          A[0][1] * Determ3x3(A[1][0], A[1][2], A[1][3],
                              A[2][0], A[2][2], A[2][3],
                              A[3][0], A[3][2], A[3][3]) +
          A[0][2] * Determ3x3(A[1][0], A[1][1], A[1][3],
                              A[2][0], A[2][1], A[2][3],
                              A[3][0], A[3][1], A[3][3]) -
          A[0][3] * Determ3x3(A[1][0], A[1][1], A[1][2],
                              A[2][0], A[2][1], A[2][2],
                              A[3][0], A[3][1], A[3][2]);
      } /* End of '' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      matr<Type> Inverse( void ) const
      {
        matr<Type> r;
        Type det = Determ();

        if (det == 0)
          return Identity();

        r.A[0][0] =
          Determ3x3(A[1][1], A[1][2], A[1][3],
            A[2][1], A[2][2], A[2][3],
            A[3][1], A[3][2], A[3][3]) / det;
        r.A[1][0] =
          -Determ3x3(A[1][0], A[1][2], A[1][3],
            A[2][0], A[2][2], A[2][3],
            A[3][0], A[3][2], A[3][3]) / det;
        r.A[2][0] =
          Determ3x3(A[1][0], A[1][1], A[1][3],
            A[2][0], A[2][1], A[2][3],
            A[3][0], A[3][1], A[3][3]) / det;
        r.A[3][0] =
          -Determ3x3(A[1][0], A[1][1], A[1][2],
            A[2][0], A[2][1], A[2][2],
            A[3][0], A[3][1], A[3][2]) / det;

        r.A[0][1] =
          -Determ3x3(A[0][1], A[0][2], A[0][3],
            A[2][1], A[2][2], A[2][3],
            A[3][1], A[3][2], A[3][3]) / det;
        r.A[1][1] =
          Determ3x3(A[0][0], A[0][2], A[0][3],
            A[2][0], A[2][2], A[2][3],
            A[3][0], A[3][2], A[3][3]) / det;
        r.A[2][1] =
          -Determ3x3(A[0][0], A[0][1], A[0][3],
            A[2][0], A[2][1], A[2][3],
            A[3][0], A[3][1], A[3][3]) / det;
        r.A[3][1] =
          Determ3x3(A[0][0], A[0][1], A[0][2],
            A[2][0], A[2][1], A[2][2],
            A[3][0], A[3][1], A[3][2]) / det;

        r.A[0][2] =
          Determ3x3(A[0][1], A[0][2], A[0][3],
            A[1][1], A[1][2], A[1][3],
            A[3][1], A[3][2], A[3][3]) / det;
        r.A[1][2] =
          -Determ3x3(A[0][0], A[0][2], A[0][3],
            A[1][0], A[1][2], A[1][3],
            A[3][0], A[3][2], A[3][3]) / det;
        r.A[2][2] =
          Determ3x3(A[0][0], A[0][1], A[0][3],
            A[1][0], A[1][1], A[1][3],
            A[3][0], A[3][1], A[3][3]) / det;
        r.A[3][2] =
          -Determ3x3(A[0][0], A[0][1], A[0][2],
            A[1][0], A[1][1], A[1][2],
            A[3][0], A[3][1], A[3][2]) / det;

        r.A[0][3] =
          -Determ3x3(A[0][1], A[0][2], A[0][3],
            A[1][1], A[1][2], A[1][3],
            A[2][1], A[2][2], A[2][3]) / det;

        r.A[1][3] =
          Determ3x3(A[0][0], A[0][2], A[0][3],
            A[1][0], A[1][2], A[1][3],
            A[2][0], A[2][2], A[2][3]) / det;
        r.A[2][3] =
          -Determ3x3(A[0][0], A[0][1], A[0][3],
            A[1][0], A[1][1], A[1][3],
            A[2][0], A[2][1], A[2][3]) / det;
        r.A[3][3] =
          Determ3x3(A[0][0], A[0][1], A[0][2],
            A[1][0], A[1][1], A[1][2],
            A[2][0], A[2][1], A[2][2]) / det;

        return r;
      } /* End of '' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static vec<Type> VectorMulMatr( const vec<Type> & V, const matr<Type> & M )
      {
        Type w = V[0] * M.A[0][3] + V[1] * M.A[1][3] + V[2] * M.A[2][3] + M.A[3][3];

        return vec<Type>((V[0] * M.A[0][0] + V[1] * M.A[1][0] + V[2] * M.A[2][0] + M.A[3][0]) / w,
          (V[0] * M.A[0][1] + V[1] * M.A[1][1] + V[2] * M.A[2][1] + M.A[3][1]) / w,
          (V[0] * M.A[0][2] + V[1] * M.A[1][2] + V[2] * M.A[2][2] + M.A[3][2]) / w);
      } /* End of 'VectorMulMatr' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static vec<Type> VectorTransform( const vec<Type> & V, const matr<Type> & M )
      {
        return vec<Type>(V[0] * M.A[0][0] + V[1] * M.A[1][0] + V[2] * M.A[2][0],
          V[0] * M.A[0][1] + V[1] * M.A[1][1] + V[2] * M.A[2][1],
          V[0] * M.A[0][2] + V[1] * M.A[1][2] + V[2] * M.A[2][2]);
      } /* End of 'VectorTransform' function */
    
      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static vec<Type> PointTransform( const vec<Type> & V, const matr<Type> & M )
      {
        return vec<Type>(V[0] * M.A[0][0] + V[1] * M.A[1][0] + V[2] * M.A[2][0] + M.A[3][0],
          V[0] * M.A[0][1] + V[1] * M.A[1][1] + V[2] * M.A[2][1] + M.A[3][1],
          V[0] * M.A[0][2] + V[1] * M.A[1][2] + V[2] * M.A[2][2] + M.A[3][2]);
      } /* End of 'PointTransform' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static vec<Type> NormalTransform( const vec<Type> & V, const matr<Type> & M )
      {
        matr A = M.Inverse();
        return VectorMulMatr(V, A.Transpose());
      } /* End of 'NormalTransform' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static matr<Type> Frustum( const Type & l, const Type & r, const Type & b, const Type & t, const Type & n, const Type & f )
      {
        return matr<Type>(2 * n / (r - l),   0,                 0,                      0,
                          0,                 2 * n / (t - b),   0,                      0,
                          (r + l) / (r - l), (t + b) / (t - b),    -(f + n) / (f - n), -1,
                          0,                 0,                 -(2 * n * f) / (f - n), 0);
      } /* End of '' function */ 

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static matr<Type> View( const vec<Type> & Loc, const vec<Type> & At, const vec<Type> & Up, const vec<Type> & Dir, const vec<Type> & Right )
      {
        matr M(Right[0], Up[0], -Dir[0], 0,
          Right[1], Up[1], -Dir[1], 0,
          Right[2], Up[2], -Dir[2], 0,
          -(Loc & Right), -(Loc & Up), (Loc & Dir), 1);
        return M;
      } /* End of '' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static matr<Type> View( const vec<Type> & Loc, const vec<Type> & At, const vec<Type> & Up1 )
      {
        vec<Type>
        Dir = (At - Loc).Normalize(),
        Right = (Dir % Up1).Normalize(),
        Up = (Right % Dir).Normalize();

        return matr<Type>(Right[0], Up[0], -Dir[0], 0,
          Right[1], Up[1], -Dir[1], 0,
          Right[2], Up[2], -Dir[2], 0,
          -(Loc & Right), -(Loc & Up), (Loc & Dir), 1);
      } /* End of '' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static matr<Type> Ortho( const Type & L, const Type & R, const Type & B, const Type & T, const Type & N, const Type & F )
      {
        matr<Type> M = Identity();

        M.A[0][0] = 2.0 / (R - L);
        M.A[1][1] = 2.0 / (T - B);
        M.A[2][2] = -2.0 / (F - N);
        M.A[3][0] = -((R + L) / (R - L));
        M.A[3][1] = -((T + B) / (T - B));
        M.A[3][2] = -((F + N) / (F - N));

        return M;
      } /* End of '' function */

      /*  function.
       *  ARGUMENTS:
       *  RETURNS:
       */
      static matr<Type> RandomMatrix( void )
      {
        matr<Type> M;

        for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++)
            M.A[i][j] = 2.0 * rand() / RAND_MAX - 1;

        return M;
      } /* End of '' function */

      //friend vec<Type>;
      //friend std::ostream & operator<<( std::ostream &C, const matr<Type> &M );
    };
} /* end of 'mth' namespace */

/*  function.
 *  ARGUMENTS:
 *  RETURNS:
 */
template<class Type>
  std::ostream & operator<<( std::ostream &C, const mth::matr<Type> &M )
  {
    for (int i = 0; i < 4; i++)
    { 
      for (int j = 0; j < 4; j++)
      {
        C.precision(3);
        C.width(7);
        C.flags(C.left);
        C << M[i * 4 + j];

        if (j != 3)
          C << " ";
      }
      C << endl;
    }

    C << endl;

    return C;
  } /* End of 'operator<<' function */

#endif // __MATR_H_

/* END OF 'CAMERA.H' FILE */
