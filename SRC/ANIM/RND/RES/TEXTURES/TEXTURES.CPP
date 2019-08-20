/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TEXTURES.CPP
 * PURPOSE     : WinAPI animation system.
 *               Render system support.
 *               Textures system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 15.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "textures.h"
#include "..\..\..\..\img\img.h"

using namespace tagl;


/* texture constructor function.
 * ARGUMETNS:
 *   - texture size:
 *       INT W, H;
 *   - texture data:
 *       DWORD *Bits;
 * RETURNS: None.
 */
texture::texture( const INT W, const INT H, const DWORD *Bits )
{
  glGenTextures(1, (GLuint *)(&TextureId));
  glBindTexture(GL_TEXTURE_2D, TextureId);

  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Bits);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, 0);
} /* End of 'texture' constructor */

/* texture constructor function.
 * ARGUMETNS:
 *   - texture size:
 *       INT W, H;
 *   - textures count:
 *       INT C;
 *   - texture data:
 *       DWORD *Bits;
 * RETURNS: None.
 */
texture::texture( const INT W, const INT H, const INT C, const DWORD *Bits )
{
  glGenTextures(1, (GLuint *)(&TextureId));
  glBindTexture(GL_TEXTURE_2D, TextureId);

  gluBuild2DMipmaps(GL_TEXTURE_2D, C, W, H, C == 4 ? GL_BGRA_EXT : C == 3 ? GL_BGR_EXT : GL_LUMINANCE, GL_UNSIGNED_BYTE, Bits);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, 0);
} /* End of 'texture' constructor */

/* texture constructor function.
 * ARGUMETNS:
 *   - file name:
 *       CHAR *FileName;
 * RETURNS: None.
 */
texture::texture( const CHAR *FileName )
{
  image img(FileName);

  glGenTextures(1, (GLuint *)(&TextureId));
  glBindTexture(GL_TEXTURE_2D, TextureId);

  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, img.W, img.H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.Bits);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, 0);
}

/* texture destructor function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
texture::~texture( VOID )
{
  glDeleteTextures(1, (GLuint *)(&TextureId));
} /* End of 'texture' destructor */

/* Apply texture function.
 * ARGUMETNS:
 *   - slot to bind in:
 *       INT Index;
 * RETURNS: None.
 */
VOID texture::Apply( const INT Index ) const
{
  glActiveTexture(GL_TEXTURE0 + Index);
  glBindTexture(GL_TEXTURE_2D, TextureId);
}

/* END OF 'TEXTURES.CPP' FILE */
