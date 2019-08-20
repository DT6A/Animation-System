/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : VEC.H
 * PURPOSE     : WinAPI animation system.
 *               Vectors math support.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 15.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __VEC_H_
#define __VEC_H_

#include "mthdef.h"

namespace mth
{
  template<class Type = double>
    class vec
    {
    private :
      Type x, y, z;

    public :
      /* Vector constructor function.
       * ARGUMENTS:
       *   - vector fields:
       *       Type a, b, c;
       * RETURNS:
       *   (vec) new vector.
       */
      vec( const Type & a, const Type & b, const Type & c ) : x(a), y(b), z(c)
      {
  
      } /* End of 'vec' constructor */

      /* Vector constructor function.
       * ARGUMENTS:
       *   - vector fields:
       *       Type a, b;
       * RETURNS: None.
       */
      vec( const Type & a, const Type & b ) : x(a), y(b), z(b)
      {

      } /* End of 'vec' constructor */

      /* Vector constructor function.
       * ARGUMENTS:
       *   - vector fields:
       *       Type a;
       * RETURNS: None.
       */
      explicit vec( const Type & a = 0 ) : x(a), y(a), z(a)
      {

      } /* End of 'vec' constructor */

      /* Vector copying constructor function.
       * ARGUMENTS:
       *   - vector to copy:
       *       vec V;
       * RETURNS: None.
       */
      vec( const vec<Type> & V ) : x(V.x), y(V.y), z(V.z)
      {

      } /* End of 'vec' constructor */

      /* operator[] overload function.
       * ARGUMENTS:
       *   - filed number:
       *       int i;
       * RETURNS:
       *   (Type) vector field with given number.
       */
      Type operator[]( int i ) const
      {
        if (i < 0)
          i = 0;
        else if (i >= 3)
          i = 2;

        return *(&this->x + i);
      } /* End of 'operator[]' function */

      /* operator! overload function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) vector length.
       */
      Type operator!( void ) const
      {
        return sqrt(x * x + y * y + z * z);
      } /* End of 'operator!' function */

      /* operator& overload function.
       * ARGUMENTS:
       *   - vector to multiply with:
       *       vec V;
       * RETURNS:
       *   (Type) dot production of two vectors.
       */
      Type operator&( const vec<Type> & V ) const
      {
        return (x * V.x + y * V.y + z * V.z);
      } /* End of 'operator&' function */

      /* operator% overload function.
       * ARGUMENTS:
       *   - vector to multiply with:
       *       vec V;
       * RETURNS:
       *   (Type) cross production of two vectors.
       */
      vec<Type> operator%( const vec<Type> & V ) const
      {
        return vec<Type>(y * V.z - z * V.y, -(x * V.z - z * V.x), x * V.y - y * V.x);
      } /* End of 'operator%' function */

      /* operator* overload function.
       * ARGUMENTS:
       *   - vector to multiply with:
       *       vec V
       * RETURNS:
       *   (vec) component production of two vectors.
       */
      vec<Type> operator*( const vec<Type> & V ) const
      {
        return vec<Type>(x * V.x, y * V.y, z * V.z);
      } /* End of 'operator *' function */

      /* operator* overload function.
       * ARGUMENTS:
       *   - number to multiply with:
       *       Type V
       * RETURNS:
       *   (vec) production of vector and number.
       */
      vec<Type> operator*( const Type & C ) const
      {
        return vec<Type>(x * C, y * C, z * C);
      } /* End of 'operator*' function */

      /* operator+ overload function.
       * ARGUMENTS:
       *   - vector to add:
       *       vec V
       * RETURNS:
       *   (vec) new vector.
       */
      vec<Type> operator+( const vec<Type> & V ) const
      {
        return vec<Type>(x + V.x, y + V.y, z + V.z);
      } /* End of 'operator+' function */

      /* operator/ overload function.
       * ARGUMENTS:
       *   - number to devide:
       *       Type C
       * RETURNS:
       *   (vec) new vector.
       */
      vec<Type> operator/( const Type & C ) const
      {
        if (C == 0)
          return vec<Type>();
        return vec<Type>(x / C, y / C, z / C);
      } /* End of 'operator/' function */

      /* operator- overload function.
       * ARGUMENTS:
       *   - vector to substract:
       *       vec V
       * RETURNS:
       *   (Type) new vector.
       */
      vec<Type> operator-( const vec<Type> & V ) const
      {
        return vec<Type>(x - V.x, y - V.y, z - V.z);
      } /* End of 'operator-' function */

      /* operator- overload function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec) vector with negative fields.
       */
      vec<Type> operator-( void ) const
      {
        return vec<Type>(-V.x, -V.y, -V.z);
      } /* End of 'operator-' function */

      /* operator*= overload function.
       * ARGUMENTS:
       *   - number to multiply with:
       *       Type C;
       * RETURNS:
       *   (vec&) new vector.
       */
      vec<Type> & operator*=( const Type & C )
      {
        x *= C;
        y *= C;
        z *= C;

        return *this;
      } /* End of 'operator*=' function */

      /* operator+ overload function.
       * ARGUMENTS:
       *   - vector to add:
       *       vec V
       * RETURNS:
       *   (vec&) new vector.
       */
      vec<Type> & operator+=( const vec<Type> & V )
      {
        x += V.x;
        y += V.y;
        z += V.z;

        return *this;
      } /* End of 'operator+=' function */

      /* operator- overload function.
       * ARGUMENTS:
       *   - vector to substract:
       *       vec V
       * RETURNS:
       *   (Type&) new vector.
       */
      vec<Type> & operator-=( const vec<Type> & V )
      {
        x -= V.x;
        y -= V.y;
        z -= V.z;

        return *this;
      } /* End of 'operator-=' function */

      /* operator/= overload function.
       * ARGUMENTS:
       *   - number to devide on:
       *       Type C
       * RETURNS:
       *   (Type&) new vector.
       */
      vec<Type> & operator/=( const Type & C )
      {
        if (C == 0)
          return vec<Type>();

        x /= C;
        y /= C;
        z /= C;

        return *this;
      } /* End of '' function */

      /* Get vector field function.
       * ARGUMENTS:
       *   - filed number:
       *       int i;
       * RETURNS:
       *   (Type) vector field with given number.
       */
      Type & GetField( const int i )
      {
        if (i <= 0)
          return x;
        else if (i == 1)
          return y;

        return z;
      } /* End of 'operator[]' function */

      /* Normalize vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec) normalized vector;
       */
      vec<Type> Normalize( void ) const
      {
        return *this / !(*this);
      } /* End of 'Normalize' function */

      /* Vector squared length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) vector squared length.
       */
      Type LengthSquared( void ) const
      {
        return this->x * this->x + this->y * this->y + this->z * this->z;
      } /* End of 'LengthSquared' function */

      /* Distance evaluation function.
       * ARGUMENTS:
       *   - vector to find distance with:
       *       (vec) V;
       * RETURNS:
       *   (Type) distance between points.
       */
      Type Distance( const vec<Type> & V ) const
      {
        return !(*this - V);
      } /* End of 'Distance' function */

      /* Random vector generation function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec) random normalized vector.
       */
      static vec<Type> RandomVector( void )
      {
        return vec<Type>(2.0 * rand() / RAND_MAX - 1, 2.0 * rand() / RAND_MAX - 1, 2.0 * rand() / RAND_MAX - 1);
      } /* End of 'RandomVector' function */

      /* Vector with zero fields creation function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec) vector with zero fields.
       */
      static vec<Type> Zero( void )
      {
        return vec<Type>();
      } /* End of 'Zero' function */

      friend class material;

    }; /* End of 'vec' class */

  template<class Type = double>
    class vec2
    {
    private :
      Type x, y;

    public:
      /* Vector constructor function.
       * ARGUMENTS:
       *   - vector fields:
       *       Type a, b;
       * RETURNS: None.
       */
      vec2( const Type & a, const Type & b ) : x(a), y(b)
      {

      } /* End of 'vec' constructor */

      /* Vector constructor function.
       * ARGUMENTS:
       *   - vector fields:
       *       Type a;
       * RETURNS: None.
       */
      explicit vec2( const Type & a = 0 ) : x(a), y(a)
      {

      } /* End of 'vec' constructor */

    }; /* End of 'vec2' class */

  template<class Type = double>
    class vec4
    {
    private :
      Type x, y, z, w;

    public:
      /* Vector constructor function.
       * ARGUMENTS:
       *   - vector fields:
       *       Type a, b, c, d;
       * RETURNS: None.
       */
      vec4( const Type & a, const Type & b, const Type & c, const Type & d ) : x(a), y(b), z(c), w(d)
      {

      } /* End of 'vec' constructor */

      /* Vector constructor function.
       * ARGUMENTS:
       *   - vector fields:
       *       Type a;
       * RETURNS: None.
       */
      explicit vec4( const Type & a = 0 ) : x(a), y(a), z(a), w(a)
      {

      } /* End of 'vec' constructor */

    }; /* End of 'vec4' class */
} /* end of 'mth' namespace */

template<class Type>
  std::ostream & operator<<( std::ostream &C, const mth::vec<Type> &V )
  {
    C << "<" << V[0] << ", " << V[1] << ", " << V[2] << ">";
    return C;
  }

#endif // __VEC_H_

/* END OF 'VEC.H' FILE */
