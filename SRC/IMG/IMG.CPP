/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : IMG.CPP
 * PURPOSE     : WinAPI animation system.
 *               Images system support.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 16.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "img.h"
#include "..\anim\anim.h"

using namespace tagl;

/* image constructor function.
 * ARGUMETNS:
 *   - file name:
 *       CHAR *FileName;
 *   - handle:
 *       HDC hDC;
 * RETURNS: None.
 */
image::image( const CHAR *FileName )
{
  HBITMAP hBmFile;
  BITMAP bm;
  BITMAPINFOHEADER bmih = {0};
  HDC hMemDC1, hMemDC2;
  anim &Ani = anim::Get();

  if ((hBmFile = (HBITMAP)LoadImage(nullptr, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)) != nullptr)
  {
    GetObject(hBmFile, sizeof(BITMAP), &bm);
    bmih.biSize = sizeof(BITMAPINFOHEADER);
    bmih.biPlanes = 1;
    bmih.biCompression = BI_RGB;
    bmih.biBitCount = 32;
    bmih.biWidth = W = bm.bmWidth;
    bmih.biHeight = H = bm.bmHeight;
    bmih.biSizeImage = W * H * 4;

    hBm = CreateDIBSection(nullptr, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, (VOID **)&Bits, nullptr, 0);

    hMemDC1 = CreateCompatibleDC(Ani.hDC);
    SelectObject(hMemDC1, hBmFile);
    hMemDC2 = CreateCompatibleDC(Ani.hDC);
    SelectObject(hMemDC2, hBm);
    BitBlt(hMemDC2, 0, 0, W, H, hMemDC1, 0, 0, SRCCOPY);

    DeleteDC(hMemDC1);
    DeleteDC(hMemDC2);
    DeleteObject(hBmFile);

    for (INT i = 0; i < W * H; i++)
      Bits[i] |= 0xFF000000;
  }
} /* End of 'image' constructor */

/* Get image pixel function.
 * ARGUMETNS:
 *   - pixel index:
 *       INT X, Y;
 * RETURNS: None.
 */
DWORD image::ImageGet( INT X, INT Y ) const
{
  X = (X + W) % W;
  Y = (Y + H) % H;
  return Bits[Y * W + X];
} /* End of 'ImageGet' function */

/* image destructor function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
image::~image( VOID )
{
  DeleteObject(hBm);
} /* End of 'image' destructor */

/* END OF 'IMAGES.H' FILE */