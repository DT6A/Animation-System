/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : SHADERS.CPP
 * PURPOSE     : WinAPI animation system.
 *               Render system support.
 *               Shaders system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 16.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "shaders.h"

using namespace tagl;

/* shader constructor function.
 * ARGUMETNS:
 *   - shader prefix:
 *       CHAR *FileName;
 * RETURNS: None.
 */
shader::shader( const CHAR *FolderName )
{
  struct 
  {
    const CHAR *Name;
    INT Type;
    INT Id;
  } shd[] =
  {
    {"vert", GL_VERTEX_SHADER},
    {"frag", GL_FRAGMENT_SHADER}
  };
  INT res, Ns = sizeof(shd) / sizeof(shd[0]);
  CHAR *txt;
  BOOL IsOK = TRUE;
  static CHAR Buf[4000];

  for (INT i = 0; IsOK && i < Ns; i++)
  {
    sprintf(Buf, "%s/%s.glsl", FolderName, shd[i].Name);
    if ((txt = LoadTextFormFile(Buf)) == nullptr)
    {
      ShaderLog(FolderName, shd[i].Name, "Error load file");
      IsOK = FALSE;
      break;
    }

    if ((shd[i].Id = glCreateShader(shd[i].Type)) == 0)
    {
      ShaderLog(FolderName, shd[i].Name, "Error create shader");
      delete txt;
      IsOK = FALSE;
      break;
    }

    glShaderSource(shd[i].Id, 1, &txt, nullptr);
    //delete txt;

    glCompileShader(shd[i].Id);
    glGetShaderiv(shd[i].Id, GL_COMPILE_STATUS, &res);

    if (res != 1)
    {
      glGetShaderInfoLog(shd[i].Id, sizeof(Buf), &res, Buf);
      ShaderLog(FolderName, shd[i].Name, Buf);
      IsOK = FALSE;
      break;
    }
  }

  if (IsOK)
  {
    if ((ProgId = glCreateProgram()) == 0)
    {
      IsOK = FALSE;
      ShaderLog(FolderName, "PROG", "Error create program");
    }
    else
    {
      for (INT i = 0; i < Ns; i++)
        if(shd[i].Id != 0)
          glAttachShader(ProgId, shd[i].Id);

      glLinkProgram(ProgId);
      glGetProgramiv(ProgId, GL_LINK_STATUS, &res);

      if (res != 1)
      {
        glGetProgramInfoLog(ProgId, sizeof(Buf), &res, Buf);
        ShaderLog(FolderName, "PROG", Buf);
        IsOK = FALSE;
      }
    }
  }

  if (!IsOK)
  {
    for (INT i = 0; i < Ns; i++)
      if (shd[i].Id != 0)
      {
        if (ProgId != 0)
          glDetachShader(ProgId, shd[i].Id);
        glDeleteShader(shd[i].Id);
      }

    if (ProgId != 0)
      glDeleteProgram(ProgId);
    ProgId = 0;
  }
}

/* shader destructor function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
shader::~shader( VOID )
{
  INT shdrs[5], n;

  //if (ProgId == 0)
   // return;
  glGetAttachedShaders(ProgId, 5, &n, (GLuint *)shdrs);

  for (INT i = 0; i < n; i++)
  {
    glDetachShader(ProgId, shdrs[i]);
    glDeleteShader(shdrs[i]);
  }
  glDeleteProgram(ProgId);
}

/* Load text from file function.
 * ARGUMETNS:
 *   - file name:
 *       CHAR * FileName;
 * RETURNS:
 *   (CHAR *) loaded text.
 */
CHAR * shader::LoadTextFormFile( const CHAR * FileName )
{
  static std::string Txt, str;

  Txt.clear();

  std::fstream F(FileName);

  if (!F)
    return nullptr;
  while (!F.eof())
  {
    std::getline(F, str);
    Txt += str;
    Txt += '\n';
  }

  F.close();
  return (CHAR *)Txt.c_str();
}

/* Stock log to file function.
 * ARGUMETNS:
 *   - file name:
 *       CHAR * FileName;
 * RETURNS:
 *   (CHAR *) loaded text.
 */
VOID shader::ShaderLog( const CHAR * Prefix, const CHAR * Type, const CHAR * Text )
{
  FILE *F;

  if ((F = fopen("Z:/T05ANIM/BIN/SHADERS/SHD.LOG", "a")) == nullptr)
    return;
  fprintf(F, "%s/%s.GLSL:\n%s\n", Prefix, Type, Text);
  fclose(F);
}

/* Apply shader function.
 * ARGUMETNS: None.
 * RETURNS: None.
 */
VOID shader::Apply( VOID ) const
{
  glUseProgram(ProgId);
}


/* Reload shader function.
 * ARGUMETNS:
 *   - shader file name:
 *       CHAR *FolderName;
 * RETURNS: None.
 */
VOID shader::Reload( const CHAR *FolderName )
{
  INT shdrs[5], n;

  //if (ProgId == 0)
   // return;
  glGetAttachedShaders(ProgId, 5, &n, (GLuint *)shdrs);

  for (INT i = 0; i < n; i++)
  {
    glDetachShader(ProgId, shdrs[i]);
    glDeleteShader(shdrs[i]);
  }
  glDeleteProgram(ProgId);

  struct 
  {
    const CHAR *Name;
    INT Type;
    INT Id;
  } shd[] =
  {
    {"vert", GL_VERTEX_SHADER},
  {"frag", GL_FRAGMENT_SHADER}
  };
  INT res, Ns = sizeof(shd) / sizeof(shd[0]);
  CHAR *txt;
  BOOL IsOK = TRUE;
  static CHAR Buf[4000];

  for (INT i = 0; IsOK && i < Ns; i++)
  {
    sprintf(Buf, "%s/%s.glsl", FolderName, shd[i].Name);
    if ((txt = LoadTextFormFile(Buf)) == nullptr)
    {
      ShaderLog(FolderName, shd[i].Name, "Error load file");
      IsOK = FALSE;
      break;
    }

    if ((shd[i].Id = glCreateShader(shd[i].Type)) == 0)
    {
      ShaderLog(FolderName, shd[i].Name, "Error create shader");
      delete txt;
      IsOK = FALSE;
      break;
    }

    glShaderSource(shd[i].Id, 1, &txt, nullptr);
    //delete txt;

    glCompileShader(shd[i].Id);
    glGetShaderiv(shd[i].Id, GL_COMPILE_STATUS, &res);

    if (res != 1)
    {
      glGetShaderInfoLog(shd[i].Id, sizeof(Buf), &res, Buf);
      ShaderLog(FolderName, shd[i].Name, Buf);
      IsOK = FALSE;
      break;
    }
  }

  if (IsOK)
  {
    if ((ProgId = glCreateProgram()) == 0)
    {
      IsOK = FALSE;
      ShaderLog(FolderName, "PROG", "Error create program");
    }
    else
    {
      for (INT i = 0; i < Ns; i++)
        if(shd[i].Id != 0)
          glAttachShader(ProgId, shd[i].Id);

      glLinkProgram(ProgId);
      glGetProgramiv(ProgId, GL_LINK_STATUS, &res);

      if (res != 1)
      {
        glGetProgramInfoLog(ProgId, sizeof(Buf), &res, Buf);
        ShaderLog(FolderName, "PROG", Buf);
        IsOK = FALSE;
      }
    }
  }

  if (!IsOK)
  {
    for (INT i = 0; i < Ns; i++)
      if (shd[i].Id != 0)
      {
        if (ProgId != 0)
          glDetachShader(ProgId, shd[i].Id);
        glDeleteShader(shd[i].Id);
      }

    if (ProgId != 0)
      glDeleteProgram(ProgId);
    ProgId = 0;
  }
}

/* END OF 'SHADERS.CPP' FILE */
