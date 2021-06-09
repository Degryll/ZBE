#version 140

in vec3 pos;
in vec2 texCoord;
uniform mat4 modelMat;
uniform mat4 texCoordMat;
out vec2 outTexCoord;

void main ( ) {
  outTexCoord = (texCoordMat * vec4(texCoord, 0.0, 1.0)).xy;
  gl_Position = modelMat * vec4(pos, 1.0);
}
