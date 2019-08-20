#version 430

in vec3 DrawPos;
in vec2 DrawTexCoord;
in vec3 DrawNorm;
in vec4 DrawColor;

out vec4 OutColor;

layout( binding = 0 ) uniform sampler2D Orig; 
layout( binding = 1 ) uniform sampler2D New;
layout( binding = 2 ) uniform sampler2D Stone;

uniform int Iter;

void main()
{               
  int B = 2 * Iter + 1;
  texelfetch();
  OutColor = min()
}
