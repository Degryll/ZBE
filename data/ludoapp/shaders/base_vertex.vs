#version 140

in vec3 pos;
in vec2 texCoord;
in vec3 nor;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
out vec2 outTexCoord;
//out vec3 outNor;

void main ( ) {
  outTexCoord = texCoord;
  //outNor = nor;
  gl_Position = projection * view * model * vec4(pos, 1.0);
}
