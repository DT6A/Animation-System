/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/
 
/* FILE NAME   : U_MAP.CPP
 * PURPOSE     : WinAPI animation system.
 *               Animation system support.
 *               Units system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 23.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

//#include "Z:\T05ANIM\stdafx.h"
#include "u_map.h"
#include "..\..\..\..\img\img.h"
//#include "..\..\..\anim.h"

using namespace tagl;

/* Get houses positions from image function.
 * ARGUMENTS:
 *   - image:
 *       const image &img;
 *   - locations stock:
 *       stock<vec> &Locs;
 * RETURNS: None.
 */
static VOID GetLocs( const image &img, stock<vec> &Locs )
{
  for (INT i = 0, k = 0; i < img.H; i++)
    for (INT j = 0; j < img.W; j++)
      if (!(img.ImageGet(j, i) & 0x00FFFFFF))
        Locs << matr::VectorMulMatr(vec(j, 0, i), matr::Scale(vec(2500 * 10 / 603)));
}

/* Unit constructor function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
u_map::u_map( VOID ) : unit()
{
  Angles[0] = 1006;
 /* Angles[1] = {FLT(-1261.47131), FLT(71.7397232),  3004 };
  Angles[2] = {FLT(-3469.66479), FLT(-87.8073273), FLT(7598.63086) };
  Angles[3] = {FLT(-6135.13770), FLT(-64.4538345), FLT(10835.2432) };
  Angles[4] = {FLT(14772.3730), FLT(-60.5059), FLT(-109986.570) }; 
  Angles[5] = {FLT(-4712.91992), FLT(-83.2236176), FLT(2221.26880) };
  Angles[6] = {FLT(-6557.52490), FLT(-98.3939209), FLT(5637.38037) };
  Angles[7] = {FLT(-7542.35693), FLT(-75.9342041), FLT(2492.54712) };
  Angles[8] = {FLT(-11019.4629), FLT(-74.1646271), FLT(1945.73950) };
  Angles[9] = {FLT(-7117.77539), FLT(-85.7413101), FLT(-1163.92761) };
  Angles[10] ={FLT(-2732.64136), FLT(-81.3179092), FLT(-5244.99561) };
  Angles[11] ={FLT(-3535.34399), FLT(-45.2799950), FLT(-8395.09863) };
  Angles[12] ={FLT(-5883.90479), FLT(-78.7118912), FLT(-9917.33105) };
  Angles[13] ={FLT(-8611.03809), FLT(-32.7668114), FLT(-8303.90430) };
  Angles[14] ={FLT(-9943.49707), FLT(-81.2393036), FLT(9952.17480) };
  Angles[15] ={FLT(-11084.0068), FLT(-97.0534058), FLT(10558.1553) };
  Angles[16] ={FLT(-12030.9229), FLT(-75.2314835), FLT(10025.2539) };
  Angles[17] ={FLT(-14814.2207), FLT(-82.6757050), FLT(10053.6865) };
  Angles[18] ={FLT(-15809.2764), FLT(-88.1489868), FLT(10627.7295) };
  Angles[19] ={FLT(-16941.4629), FLT(-83.8676529), FLT(10164.0352) };
  Angles[20] ={FLT(-21096.1270), FLT(-89.5912628), FLT(9759.26758) };*/


  image img("bin\\images\\mask.bmp");
  GetLocs(img, Locs);
  //A01 = new prims();

 // A01->Load("z:\\t05anim\\models\\ukrainian_house.g3dm", matr::Scale(vec(20)));
  //A01->Prims[0]->Mtl = A01->Prims[1]->Mtl;

  for (INT i = 0; i < 22; i++)
  {
    Houses[i] = new prims();
    Angles[i] = 0;
  }
 //for (INT i = 3; i < 22; i++)
  //  Houses[i]->Load("z:\\t05anim\\models\\Building_A05.g3dm", matr::Scale(vec(20)));
  
  Houses[0]->Load("models\\Cyprys_House.g3dm", matr::Scale(vec(90)) * matr::RotateY(30));
  Houses[1]->Load("models\\Cyprys_House.g3dm", matr::Scale(vec(90)) * matr::RotateY(30));
  Houses[2]->Load("models\\house_01.g3dm", matr::Scale(vec(10)) * matr::RotateY(10));
  Houses[3]->Load("models\\hotel.g3dm", matr::Scale(vec(10)) * matr::RotateY(180));
  Houses[4]->Load("models\\houseF.g3dm", matr::Scale(vec(400)) * matr::RotateY(90));
  Houses[5]->Load("models\\houseF.g3dm", matr::Scale(vec(400)) * matr::RotateY(90));
  Houses[6]->Load("models\\English_thatched_house.g3dm", matr::Scale(vec(100)) * matr::RotateY(10));
  Houses[7]->Load("models\\hotel.g3dm", matr::Scale(vec(10)) * matr::RotateY(10));
  Houses[8]->Load("models\\houseF.g3dm", matr::Scale(vec(400)) * matr::RotateY(10)); //Smaller
  Houses[9]->Load("models\\houseF.g3dm", matr::Scale(vec(400)) * matr::RotateY(10));
  Houses[10]->Load("models\\English_thatched_house.g3dm", matr::Scale(vec(100)) * matr::RotateY(70)); // Rotate
  Houses[11]->Load("models\\hotel.g3dm", matr::Scale(vec(10)) * matr::RotateY(10));
  Houses[12]->Load("models\\Cyprys_House.g3dm", matr::Scale(vec(90)) * matr::RotateY(30));
  Houses[13]->Load("models\\Cyprys_House.g3dm", matr::Scale(vec(90)) * matr::RotateY(30));
  Houses[14]->Load("models\\house_01.g3dm", matr::Scale(vec(10)) * matr::RotateY(10));
  Houses[15]->Load("models\\hotel.g3dm", matr::Scale(vec(10)) * matr::RotateY(180));
  Houses[16]->Load("models\\houseF.g3dm", matr::Scale(vec(400)) * matr::RotateY(90));
  Houses[17]->Load("models\\English_thatched_house.g3dm", matr::Scale(vec(100)) * matr::RotateY(10));
  Houses[18]->Load("models\\Cyprys_House.g3dm", matr::Scale(vec(100)) * matr::RotateY(10));
  Houses[19]->Load("models\\houseF.g3dm", matr::Scale(vec(400)) * matr::RotateY(10)); //Smaller
  Houses[20]->Load("models\\house_01.g3dm", matr::Scale(vec(10)) * matr::RotateY(10)); 
  Houses[21]->Load("models\\houseF.g3dm", matr::Scale(vec(400)) * matr::RotateY(70)); // Rotate
 
  for (INT i = 0; i < Houses[4]->Prims.Size(); i++)
  {
    Houses[4]->Prims[i]->Mtl->Ka = vec(0.7);
    Houses[5]->Prims[i]->Mtl->Ka = vec(0.7);
    Houses[16]->Prims[i]->Mtl->Ka = vec(0.7);
    //Houses[4]->Prims[i]->Mtl->Ka *= 1.4;

  }

/* 
  for (INT i = 0; i < Houses[5]->Prims.Size(); i++)
  {
    Houses[5]->Prims[i]->Mtl->Ka += vec(0.4);
    Houses[5]->Prims[i]->Mtl->Ka = Houses[5]->Prims[i]->Mtl->Ka.Normalize();
  }*/
  
} /* End of 'u_map' constructor */

/* Unit destructor function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
u_map::~u_map( VOID )
{
  for (INT i = 0; i < 22; i++)
    delete Houses[i];
} /* End of 'u_map' destructor */

/* Unit render function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
VOID u_map::Render( VOID )
{
  //Ani.Draw(A01->Prims[1], matr::Translate(L1));
  for (INT i = 0; i < 22; i++)
      Ani.Draw(Houses[i], matr::RotateY(Angles[i]) * matr::Translate(Locs[i]));
  
} /* End of 'Render' function */

/* Unit response function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
VOID u_map::Response( VOID )
{
  Ind = 1;
  //L1 = Ani.Cam.At;
  if (anim::input::keyboard::KeysClick[VK_TAB])
  {
    if (Ind < 22)
      Ind++;
    else
      Ind = 0;
  }
  if (anim::input::keyboard::Keys[VK_CONTROL])
  {
    if (anim::input::keyboard::Keys['A'])
      Angles[Ind] -= 90 * Ani.DeltaTime;
    if (anim::input::keyboard::Keys['D'])
      Angles[Ind] += 90 * Ani.DeltaTime;
  }
} /* End of 'Response' function */

/* END OF 'U_MAP.CPP' FILE */