#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;
uniform float scale;

float smoothing = 0.0;

void main()
{
      smoothing = 0.25 / ( 1 * scale );
      if(smoothing > 0.49) smoothing = 0.49;
      float distance = texture2D(ourTexture, TexCoord).a;
      float alpha = smoothstep(0.5 - smoothing, 0.5 + smoothing, distance);
      color = vec4(1.0, 1.0, 1.0, alpha);
}
