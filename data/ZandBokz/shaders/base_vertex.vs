#version 140

in vec3 pos;
in vec2 texCoord;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
out vec2 outTexCoord;

void main ( ) {
  outTexCoord = texCoord;
  gl_Position = projection * view * model * vec4(pos, 1.0);
  //gl_Position = vec4(pos, 1.0);
}
