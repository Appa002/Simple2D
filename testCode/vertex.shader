#version 410

layout (location=0) in vec3 vp;
layout (location=1) in vec2 vt;

uniform vec3 pos;
uniform vec3 camPos;

out vec2 texture_coordinates;

void main(){
    vec3 finalPos;
    finalPos.x = vp.x + (pos.x - camPos.x);
    finalPos.y = vp.y + (pos.y - camPos.y);
    finalPos.z = vp.z + (pos.z - camPos.z);

    gl_Position = vec4(finalPos.x, finalPos.y, finalPos.z, 1.0f);
    texture_coordinates = vt;
}
