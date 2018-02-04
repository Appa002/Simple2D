#version 410

layout (location=0) in vec3 vp;
layout (location=1) in vec2 vt;

uniform vec3 pos;
uniform vec3 camPos;
uniform vec3 scale;

out vec2 texture_coordinates;

void main(){
    vec3 finalPos;
    finalPos.x = vp.x * scale.x + (pos.x - camPos.x);
    finalPos.y = vp.y * scale.y + (pos.y - camPos.y);
    finalPos.z = vp.z * scale.z + (pos.z - camPos.z);

    gl_Position = vec4(finalPos.x, finalPos.y, finalPos.z, 1.0f);
    texture_coordinates = vt;
}
