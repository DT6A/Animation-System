#version 430

in vec3 DrawPos;
in vec2 DrawTexCoord;
in vec3 DrawNorm;
in vec4 DrawColor;

out vec4 OutColor;

layout(binding = 0) uniform sampler2D Texture; 

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Ph;
uniform float Trans;

uniform int Index;

uniform bool IsTexture1;

uniform vec3 CamPos;

vec3 Light( void )
{
  vec3 Color = vec3(0);
  //for (int i = 0; i < 3; i++)
  //{
    vec3 LightPos = vec3(1250 * 10, 1000, 1250 * 10);
    vec3 V = normalize(DrawPos - CamPos);
    vec3 L = normalize(DrawPos - LightPos);
    vec3 R = reflect(-L, DrawNorm);

    vec3 ambient = Ka;
 
    vec3 diffuse = Kd * max(dot(DrawNorm, L), 0.0);  
    diffuse = clamp(diffuse, 0.0, 1.0);
 //float DotN = max(dot(L, DrawNorm), 0);
    vec3 spec = Ks * pow(max(dot(R, V), 0.0), 0.3 * Ph);

    if (Index == 33 || Index == 42 || Index == 80 || Index == 83 || Index == 82 || Index == 84 || Index == 85)    
   {    
     ambient = vec3(0);
     diffuse /= 10;
     spec /= 2;
   } 
   spec = clamp(spec, 0.0, 1.0);

  Color += ambient + diffuse + spec;

  //Color = L * Ka + L * Kd * (L * DrawNorm) + Ks * pow(dot(R, L), Ph);
  //}
  return vec3(Color);
}

void main()
{     
  if (Index != 71 && Index > 32 && Index > -1 && Index != 76 || Index < 9)
    ;//discard;
  if (IsTexture1 == false)
    OutColor = vec4(Light(), Trans);// * texture2D(Texture, vec2(DrawTexCoord.x, -DrawTexCoord.y));
  else 
    OutColor = vec4(Light(), Trans) * texture2D(Texture, vec2(DrawTexCoord.x, -DrawTexCoord.y));
}
