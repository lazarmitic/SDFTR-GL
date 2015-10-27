#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

const float smoothing = 0.1;

void main()
{
      float distance = texture2D(ourTexture, TexCoord).a;
      float alpha = smoothstep(0.5 - smoothing, 0.5 + smoothing, distance);
      color = vec4(1.0, 1.0, 1.0, alpha);
}
