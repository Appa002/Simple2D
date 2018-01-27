#version 410

in vec3 vp;
layout (location=1) in vec2 vt;
out vec2 texture_coordinates;

void main(){
    gl_Position = vec4(vp.x, vp.y, vp.z, 1.0f);
    texture_coordinates = vt;
}
