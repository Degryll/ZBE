#version 140

in vec2 outTexCoord;
//in vec3 outNor;
uniform sampler2D tex;
out vec4 fColor;

void main( ) {
  fColor = texture(tex, outTexCoord);
}
