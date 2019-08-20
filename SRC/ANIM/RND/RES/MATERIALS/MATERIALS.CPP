/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MATERIALS.CPP
 * PURPOSE     : WinAPI animation system.
 *               Render system support.
 *               Materials system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 16.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "materials.h"

using namespace tagl;

/* material constructor function.
 * ARGUMETNS:
 *   - material shader:
 *       shader *NewShd;
 *   - material textures:
 *       texture **NewTextures;
 *   - light coefitients:
 *       vec NewKa, NewKd, NewKs;
 *   - phong coefitient:
 *       FLT NewPh;
 *   - transparency:
 *       FLT NewTrans;
 * RETURNS: None.
 */
material::material( shader *NewShd, texture *NewTextures[8],
                    const vec & NewKa, const vec & NewKd, const vec & NewKs,
                    const FLT NewPh, const FLT NewTrans) : Ka(NewKa), Kd(NewKd), Ks(NewKs), Ph(NewPh), Trans(NewTrans)
{
  if (NewTextures != nullptr)
    for (INT i = 0; i < 8; i++)
      Textures[i] = NewTextures[i];
  Shd = NewShd;
} /* End of 'material' constructor */

/* Material apply function.
 * ARGUMETNS: None.
 * RETURNS:
 *   (INT) program id.
 */
INT material::MaterialApply( VOID )
{
  INT loc;
  BOOL IsTexture = FALSE;
  if (Shd != nullptr)
    Shd->Apply();
  else
  {
    glUseProgram(0);
    return 0;
  }

  if (Textures[0]->TextureId != -1)
    IsTexture = TRUE;

  if ((loc = glGetUniformLocation(Shd->ProgId, "Ka")) != -1)
    glUniform3fv(loc, 1, &(Ka.GetField(0)));
  if ((loc = glGetUniformLocation(Shd->ProgId, "Kd")) != -1)
    glUniform3fv(loc, 1, &(Kd.GetField(0)));
  if ((loc = glGetUniformLocation(Shd->ProgId, "Ks")) != -1)
    glUniform3fv(loc, 1, &(Kd.GetField(0)));
  if ((loc = glGetUniformLocation(Shd->ProgId, "Ph")) != -1)
    glUniform1f(loc, Ph);
  if ((loc = glGetUniformLocation(Shd->ProgId, "Trans")) != -1)
    glUniform1f(loc, Trans);
  if ((loc = glGetUniformLocation(Shd->ProgId, "IsTexture1")) != -1)
    glUniform1i(loc, IsTexture);

  if (Textures != nullptr)
    for (INT i = 0; i < 8; i++)
      Textures[i]->Apply(i);
  return Shd != nullptr ? Shd->ProgId : 0;
} /* End of 'MaterialApply' function */

/* END OF 'MATERIALS.H' FILE */
