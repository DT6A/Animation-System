/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/
 
/* FILE NAME   : U_TEST.CPP
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
#include "u_test.h"
//#include "..\..\..\anim.h"

using namespace tagl;

/* Unit constructor function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
u_test::u_test( VOID ) : unit()
{
  texture *Textures[8];
  shader *Shd = render::CreateShader("bin\\shaders\\plane");
  shader *ShdPl = render::CreateShader("bin\\shaders\\secret");;

  for (INT i = 0; i < 8; i++)
    Textures[i] = render::CreateTexture();

  Textures[0] = render::CreateTexture("bin\\images\\grass.bmp");
  Textures[1] = render::CreateTexture("bin\\images\\zorkaroad.bmp");
  Textures[2] = render::CreateTexture("bin\\images\\stone.bmp");
  Textures[3] = render::CreateTexture("bin\\images\\opa.bmp");

  //Cow = render::CreatePrim("z:\\t05anim\\models\\cow.object");
  
  topology_mesh Sph;

  Btr = new prims();

  Btr->Load("models\\xtrail.g3dm", matr::Identity());
 

  Sph.CreateHeightmap("bin/images/zorkaroad.bmp", 0.0);
  Cow = Sph.ToPrim();
  Plane = Sph.ToPrim();
  Cow->Mtl = render::CreateMaterial("Test", Shd, Textures, vec(1), vec(0), vec(0));
  Plane->Mtl = render::CreateMaterial("IlonMask", ShdPl, Textures, vec(1), vec(0), vec(0));

  Ani.Cam.At = Location + vec(-35, 60, -100);
} /* End of 'u_test' constructor */

/* Unit destructor function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
u_test::~u_test( VOID )
{
  delete Btr;
} /* End of 'u_test' destructor */

/* Unit render function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
VOID u_test::Render( VOID )
{

  Ani.Draw(Cow, matr::Scale(vec(2500 * 10)));
  Ani.Cam.ChangeMode(CamModeOrtho);
  Ani.Draw(Plane, matr::Translate(vec(100, 100, 2)));
  Ani.Cam.ChangeMode(CamModeFrustum);
  if (anim::input::keyboard::Keys['R'])
  {
    Ani.Draw(Plane, matr::Scale(vec(25)) * matr::Translate(vec(-12.5, 0, -12.5)) *
      matr::RotateY(acos(Ani.Cam.Dir & vec(0, 0, 1)) / mth::PI * 180) *
      //matr::RotateY(acos(Ani.Cam.Dir & vec(1, 0, 0)) / mth::PI * -180) *
      matr::Rotate(acos(Ani.Cam.Dir & vec(0, 1, 0)) / mth::PI * -180, Ani.Cam.Right) *
      matr::Translate(Ani.Cam.Loc + Ani.Cam.Dir * 50));
  }
  Ani.Draw(Btr, matr::RotateY(Rotation) * matr::Translate(Location));

} /* End of 'Render' function */

/* Unit response function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
VOID u_test::Response( VOID )
{
  static FLT AngleTp = 0;
  static FLT Angle = 0;
  static vec LocalAt;
  
  Location += (V * Ani.DeltaTime);
  LocalAt += (V * Ani.DeltaTime);

  //Location += V * Ani.DeltaTime * Velocity / 20;
  if (Ani.Cam.IsAttached && !IsFP)
  {

    Ani.Cam.At = Location;

    if (anim::input::keyboard::Keys['W'] && !anim::input::keyboard::Keys[VK_SHIFT]) 
    {

      if (Velocity <= MaxSpeed)
      {
        Velocity += Acceleration * Ani.DeltaTime;
        if (Velocity > MaxSpeed)
          Velocity = MaxSpeed;
        //V = Dir * (Velocity * Ani.DeltaTime);
      }
    }
    if (anim::input::keyboard::Keys['S'])
    {
      if (Velocity >= -MaxSpeed)
      {
        Velocity -= Acceleration * Ani.DeltaTime;
        if (Velocity < -MaxSpeed)
          Velocity = -MaxSpeed;
      }
    }
    //V = Dir * (Velocity * Ani.DeltaTime);
    FLT VA = (Velocity != 0) / 40.0;//Velocity * Ani.DeltaTime;


    if (anim::input::keyboard::Keys['D'])
    {
      RotationSpeed -= 60 * Ani.DeltaTime;//(RotationSpeed - VA * 8) < -47 ? -47 : RotationSpeed - VA * 8;
      if (RotationSpeed < -70)
        RotationSpeed = -70; 
    }
    if (anim::input::keyboard::Keys['A'])
    {
      RotationSpeed += 60 * Ani.DeltaTime;//(RotationSpeed + VA * 8) > 47 ? 47 : RotationSpeed + VA * 8;
      if (RotationSpeed > 70)
        RotationSpeed = 70;
      /*if (Velocity > 0)
      {
        Rotation -= RotationSpeed * VA;
        V = matr::VectorMulMatr(V, matr::RotateY(-RotationSpeed * VA));
        Dir = matr::VectorMulMatr(Dir, matr::RotateY(-RotationSpeed * VA));
        FPPos = matr::VectorMulMatr(FPPos, matr::RotateY(-RotationSpeed * VA));
        CamOffset = matr::VectorMulMatr(CamOffset, matr::RotateY(-RotationSpeed * VA));
        LocalAt = matr::VectorMulMatr(LocalAt, matr::RotateY(-RotationSpeed * VA));
      }
      else
      {
        Rotation += RotationSpeed * VA;
        V = matr::VectorMulMatr(V, matr::RotateY(RotationSpeed * VA));
        Dir = matr::VectorMulMatr(Dir, matr::RotateY(RotationSpeed * VA));
        FPPos = matr::VectorMulMatr(FPPos, matr::RotateY(RotationSpeed * VA));
        CamOffset = matr::VectorMulMatr(CamOffset, matr::RotateY(RotationSpeed * VA));
        LocalAt = matr::VectorMulMatr(LocalAt, matr::RotateY(RotationSpeed * VA));
      }*/
    }

    if (anim::input::keyboard::Keys['P'])
    {
      CamOffset += Ani.Cam.Dir * 102 * Ani.DeltaTime;
    }
    if (anim::input::keyboard::Keys['O'])
    {
      CamOffset -= Ani.Cam.Dir * 102 * Ani.DeltaTime;
    }

    if (Velocity > 0)
    {
      Rotation += RotationSpeed * VA;
      V = matr::VectorMulMatr(V, matr::RotateY(RotationSpeed * VA));
      Dir = matr::VectorMulMatr(Dir, matr::RotateY(RotationSpeed * VA));
      FPPos = matr::VectorMulMatr(FPPos, matr::RotateY(RotationSpeed * VA));
      CamOffset = matr::VectorMulMatr(CamOffset, matr::RotateY(RotationSpeed * VA));
      LocalAt = matr::VectorMulMatr(LocalAt, matr::RotateY(RotationSpeed * VA));
    }
    else
    {
      Rotation -= RotationSpeed * VA;
      V = matr::VectorMulMatr(V, matr::RotateY(-RotationSpeed * VA));
      Dir = matr::VectorMulMatr(Dir, matr::RotateY(-RotationSpeed * VA));
      FPPos = matr::VectorMulMatr(FPPos, matr::RotateY(-RotationSpeed * VA));
      CamOffset = matr::VectorMulMatr(CamOffset, matr::RotateY(-RotationSpeed * VA));
      LocalAt = matr::VectorMulMatr(LocalAt, matr::RotateY(-RotationSpeed * VA));
    }

    if (anim::input::keyboard::Keys[VK_LEFT])
      CamOffset = matr::VectorMulMatr(CamOffset, matr::RotateY(-90 * Ani.DeltaTime));
    if (anim::input::keyboard::Keys[VK_RIGHT])
      CamOffset = matr::VectorMulMatr(CamOffset, matr::RotateY(90 * Ani.DeltaTime));
    if (anim::input::keyboard::Keys[VK_UP])
    {
      if (AngleTp < 80)
      {
        AngleTp = (AngleTp + 70.0 * Ani.DeltaTime) > 80 ? 80 : (AngleTp + 70.0 * Ani.DeltaTime);
        if (AngleTp < 80)
          CamOffset = matr::VectorMulMatr(CamOffset, matr::Rotate(70 * Ani.DeltaTime, CamOffset % vec(0, 1, 0)));
      }
    }
    if (anim::input::keyboard::Keys[VK_DOWN])
    {
      if (AngleTp > -80)
      {
        AngleTp = (AngleTp - 70.0 * Ani.DeltaTime) < -80 ? -80 : (AngleTp - 70.0 * Ani.DeltaTime);
        if (AngleTp > -80)
          CamOffset = matr::VectorMulMatr(CamOffset, matr::Rotate(-70 * Ani.DeltaTime, CamOffset % vec(0, 1, 0)));
      }
    }
    Ani.Cam.Loc = Ani.Cam.At + CamOffset;
    Ani.Cam.UpdateView();
  }
  else if (Ani.Cam.IsAttached)
  {
    if (anim::input::keyboard::Keys['W'] && !anim::input::keyboard::Keys[VK_SHIFT]) 
    {
      if (Velocity <= MaxSpeed)
      {
        Velocity += Acceleration * Ani.DeltaTime;
        if (Velocity > MaxSpeed)
          Velocity = MaxSpeed;
      }
    }
    if (anim::input::keyboard::Keys['S'])
    {
      if (Velocity >= -MaxSpeed)
      {
        Velocity -= Acceleration * Ani.DeltaTime;
        if (Velocity < -MaxSpeed)
          Velocity = -MaxSpeed;
        //V = Dir * (Velocity * Ani.DeltaTime);
      }
    }
    FLT VA = (Velocity != 0) / 40.0;
    if (anim::input::keyboard::Keys['D'])
    {

      RotationSpeed -= 60 * Ani.DeltaTime;
      if (RotationSpeed < -70)
        RotationSpeed = -70;
      //V += vec(-1 * Velocity * Ani.DeltaTime / 10, 0, 0);
    }
    if (anim::input::keyboard::Keys['A'])
    {
      RotationSpeed += 60 * Ani.DeltaTime;
      if (RotationSpeed > 70)
        RotationSpeed = 70;
      /*if (Velocity > 0)
      {
        Rotation -= RotationSpeed * VA;
        V = matr::VectorMulMatr(V, matr::RotateY(-RotationSpeed * VA));
        Dir = matr::VectorMulMatr(Dir, matr::RotateY(-RotationSpeed * VA));
        FPPos = matr::VectorMulMatr(FPPos, matr::RotateY(-RotationSpeed * VA));
        Ani.Cam.At = matr::VectorMulMatr(TmpAt, matr::RotateY(-RotationSpeed * VA)) + Ani.Cam.Loc + FPPos;
        CamOffset = matr::VectorMulMatr(CamOffset, matr::RotateY(-RotationSpeed * VA));
      }
      else
      {
        Rotation += RotationSpeed * VA;
        V = matr::VectorMulMatr(V, matr::RotateY(RotationSpeed * VA));
        Dir = matr::VectorMulMatr(Dir, matr::RotateY(RotationSpeed * VA));
        FPPos = matr::VectorMulMatr(FPPos, matr::RotateY(RotationSpeed * VA));
        Ani.Cam.At = matr::VectorMulMatr(TmpAt, matr::RotateY(RotationSpeed * VA)) + Ani.Cam.Loc + FPPos;
        CamOffset = matr::VectorMulMatr(CamOffset, matr::RotateY(RotationSpeed * VA));
      } */
      //V += vec(1 * Velocity * Ani.DeltaTime / 10, 0, 0);
    }

    vec TmpAt = (Ani.Cam.At - Ani.Cam.Loc - FPPos);
    if (Velocity > 0)
    {
      Rotation += RotationSpeed * VA;
      V = matr::VectorMulMatr(V, matr::RotateY(RotationSpeed * VA));
      Dir = matr::VectorMulMatr(Dir, matr::RotateY(RotationSpeed * VA));
      Ani.Cam.At = matr::VectorMulMatr(TmpAt, matr::RotateY(RotationSpeed * VA)) + Ani.Cam.Loc + FPPos;
      FPPos = matr::VectorMulMatr(FPPos, matr::RotateY(RotationSpeed * VA));
      CamOffset = matr::VectorMulMatr(CamOffset, matr::RotateY(RotationSpeed * VA));
    }
    else
    { 
      Rotation -= RotationSpeed * VA;
      V = matr::VectorMulMatr(V, matr::RotateY(-RotationSpeed * VA));
      Dir = matr::VectorMulMatr(Dir, matr::RotateY(-RotationSpeed * VA));
      Ani.Cam.At = matr::VectorMulMatr(TmpAt, matr::RotateY(-RotationSpeed * VA)) + Ani.Cam.Loc + FPPos;
      FPPos = matr::VectorMulMatr(FPPos, matr::RotateY(-RotationSpeed * VA));
      CamOffset = matr::VectorMulMatr(CamOffset, matr::RotateY(-RotationSpeed * VA));
    }
    if (anim::input::keyboard::Keys[VK_LEFT])
      Ani.Cam.TurnY(90.0 * Ani.GlobalDeltaTime);
    if (anim::input::keyboard::Keys[VK_RIGHT])
      Ani.Cam.TurnY(-90.0 * Ani.GlobalDeltaTime);
    if (anim::input::keyboard::Keys[VK_UP])
    {
      Angle = (Angle + 90.0 * Ani.GlobalDeltaTime) > 90 ? 90 : (Angle + 90.0 * Ani.GlobalDeltaTime);
      if (Angle < 90)
        Ani.Cam.TurnXZ(90.0 * Ani.GlobalDeltaTime);
    }
    if (anim::input::keyboard::Keys[VK_DOWN])
    {
      Angle = (Angle - 90.0 * Ani.GlobalDeltaTime) < -90 ? -90 : (Angle - 90.0 * Ani.GlobalDeltaTime);
    if (Angle > -90)
        Ani.Cam.TurnXZ(-90.0 * Ani.GlobalDeltaTime);
    }

    Ani.Cam.Loc = Location + FPPos;
    Ani.Cam.At += V;
    Ani.Cam.UpdateView();
  }

  V = Dir * (Velocity * Ani.DeltaTime);

  if (anim::input::keyboard::Keys['1'] && !IsFP)
  {
    IsFP = TRUE;
    Ani.Cam.At = LocalAt;
  }
  if (anim::input::keyboard::Keys['2'] && IsFP)
  {
    IsFP = FALSE;
    LocalAt = Ani.Cam.At;
  }

  if (Velocity > 0)
  {
    Velocity -= Acceleration * Ani.DeltaTime / 2.5;
    if (Velocity < 0)
      Velocity = 0;
  }
  else if (Velocity < 0)
  {
    Velocity += Acceleration * Ani.DeltaTime / 2.5;
    if (Velocity > 0)
      Velocity = 0;
  }

 // if (Velocity == 0)
   // V = vec(0);
  if (RotationSpeed > 0)
  {
    RotationSpeed -= 60 * Ani.DeltaTime / 3;
    if (RotationSpeed < 0)
      RotationSpeed = 0;
  }
  else if (RotationSpeed < 0)
  {
    RotationSpeed += 60 * Ani.DeltaTime / 2;
    if (RotationSpeed > 0)
      RotationSpeed = 0;
  }

  /*if ((V.Normalize() & Dir) > 0)
    V -= (Dir * Acceleration * Ani.DeltaTime * Ani.DeltaTime / 1.8);
  else if ((V.Normalize() & Dir) < 0)
    V += (Dir * Acceleration * Ani.DeltaTime * Ani.DeltaTime / 1.8);
  if (!V < 0.05)
    V = vec(0);
  /*if (!V < 0.09)
  {
     V = vec(0);
  } */

  Btr->Prims[9]->Transform = matr::Translate(vec(75, 52.1, 134.8)) * matr::RotateY(RotationSpeed) * matr::Translate(vec(-75, -52.1, -134.8));
  Btr->Prims[10]->Transform = matr::Translate(vec(75, 52.1, 134.8)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::RotateY(RotationSpeed) * matr::Translate(vec(-75, -52.1, -134.8));
  Btr->Prims[11]->Transform = matr::Translate(vec(75, 52.1, 134.8)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::RotateY(RotationSpeed) * matr::Translate(vec(-75, -52.1, -134.8));
  Btr->Prims[12]->Transform = matr::Translate(vec(75, 52.1, 134.8)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::RotateY(RotationSpeed) * matr::Translate(vec(-75, -52.1, -134.8));
  Btr->Prims[13]->Transform = matr::Translate(vec(75, 52.1, 134.8)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::RotateY(RotationSpeed) * matr::Translate(vec(-75, -52.1, -134.8));
  Btr->Prims[14]->Transform = matr::Translate(vec(75, 52.1, 134.8)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::RotateY(RotationSpeed) * matr::Translate(vec(-75, -52.1, -134.8));

  Btr->Prims[16]->Transform = matr::Translate(vec(85.7, 52.1, -124.4)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::Translate(vec(-85.7, -52.1, 124.4));
  Btr->Prims[15]->Transform = matr::Translate(vec(85.7, 52.1, -124.4)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::Translate(vec(-85.7, -52.1, 124.4));
  Btr->Prims[17]->Transform = matr::Translate(vec(85.7, 52.1, -124.4)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::Translate(vec(-85.7, -52.1, 124.4));
  Btr->Prims[18]->Transform = matr::Translate(vec(85.7, 52.1, -124.4)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::Translate(vec(-85.7, -52.1, 124.4));
  Btr->Prims[19]->Transform = matr::Translate(vec(85.7, 52.1, -124.4)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::Translate(vec(-85.7, -52.1, 124.4));  


  Btr->Prims[28]->Transform = matr::Translate(vec(-75, 52.1, 134.8)) * matr::RotateY(RotationSpeed) * matr::Translate(vec(75, -52.1, -134.8));
  Btr->Prims[27]->Transform = matr::Translate(vec(-75, 52.1, 134.8)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::RotateY(RotationSpeed) * matr::Translate(vec(75, -52.1, -134.8));
  Btr->Prims[29]->Transform = matr::Translate(vec(-75, 52.1, 134.8)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::RotateY(RotationSpeed) * matr::Translate(vec(75, -52.1, -134.8));
  Btr->Prims[30]->Transform = matr::Translate(vec(-75, 52.1, 134.8)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::RotateY(RotationSpeed) * matr::Translate(vec(75, -52.1, -134.8));
  Btr->Prims[31]->Transform = matr::Translate(vec(-75, 52.1, 134.8)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::RotateY(RotationSpeed) * matr::Translate(vec(75, -52.1, -134.8));
  Btr->Prims[32]->Transform = matr::Translate(vec(-75, 52.1, 134.8)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::RotateY(RotationSpeed) * matr::Translate(vec(75, -52.1, -134.8));

  Btr->Prims[21]->Transform = matr::Translate(vec(-85.7, 52.1, -124.4)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::Translate(vec(85.7, -52.1, 124.4));
  Btr->Prims[22]->Transform = matr::Translate(vec(-85.7, 52.1, -124.4)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::Translate(vec(85.7, -52.1, 124.4));
  Btr->Prims[23]->Transform = matr::Translate(vec(-85.7, 52.1, -124.4)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::Translate(vec(85.7, -52.1, 124.4));
  Btr->Prims[24]->Transform = matr::Translate(vec(-85.7, 52.1, -124.4)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::Translate(vec(85.7, -52.1, 124.4));
  Btr->Prims[25]->Transform = matr::Translate(vec(-85.7, 52.1, -124.4)) * matr::RotateX(-Ani.Time * Velocity / 10) * matr::Translate(vec(85.7, -52.1, 124.4));

  Btr->Prims[71]->Transform = matr::Translate(vec(35, -20, 33)) * matr::RotateX(18) * matr::Translate(vec(-0.9, -1.15, 0)) * matr::RotateZ(RotationSpeed * 7) * matr::Translate(vec(0.9, 1.15, 0)) * matr::RotateX(-18) * matr::Translate(vec(-35, 20, -33));
} /* End of 'Response' function */

/* END OF 'U_TEST.CPP' FILE */