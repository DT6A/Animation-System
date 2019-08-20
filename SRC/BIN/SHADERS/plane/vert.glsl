#version 430
 
layout (location = 0) in vec3 InPos;
layout (location = 1) in vec2 InTexCoord;
layout (location = 2) in vec3 InNorm;
layout (location = 3) in vec4 InColor;

uniform mat4 MatrWVP;
uniform mat4 MatrNorm; 
uniform mat4 MatrW;
uniform mat4 MatrVP;                    

out vec3 DrawPos;
out vec2 DrawTexCoord;
out vec3 DrawNorm;
out vec4 DrawColor;

void main()
{
  DrawPos = InPos;     
  DrawTexCoord = InTexCoord;
  DrawNorm = normalize(InNorm * mat3(MatrNorm));//* transpose(inverse(MatrW)));    
  DrawColor = InColor;                        
  gl_Position = MatrWVP * vec4(InPos, 1);
}
