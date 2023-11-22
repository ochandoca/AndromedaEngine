#version 430 core

layout(location = 0) in vec2 position;
out vec2 blend_color;

void main(){
  gl_Position = vec4(position.x, position.y, 0.0, 1.0);
  blend_color = position;
}