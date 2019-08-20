#version 430

in vec3 DrawPos;
in vec2 DrawTexCoord;
in vec3 DrawNorm;
in vec4 DrawColor;

out vec4 OutColor;

layout( binding = 3 ) uniform sampler2D IlonMask;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Ph;
uniform float Trans;

uniform int Index;

void main()
{ 
 
  OutColor = texture2D(IlonMask, vec2(-DrawTexCoord.x, -DrawTexCoord.y));    
  if (OutColor.x > 0.9 && OutColor.y > 0.9 && OutColor.z > 0.9)
    discard;
//  OutColor = texture2D(Mask, vec2(DrawTexCoord.x, DrawTexCoord.y)) * texture2D(Stone, vec2(DrawTexCoord.x * 40, DrawTexCoord.y * 40)) + 
 // (vec4(1)- texture2D(Mask, vec2(DrawTexCoord.x, DrawTexCoord.y))) * texture2D(Grass, vec2(DrawTexCoord.x * 40, DrawTexCoord.y * 40));
}
