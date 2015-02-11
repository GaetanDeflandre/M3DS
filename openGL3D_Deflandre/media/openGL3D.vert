#version 130

in vec3 position;
in vec3 color;

out vec3 fColor;

uniform mat4 projection;
uniform mat4 transform;

void main() {
    vec4 eyePosition=vec4(position,1); // passage en coordonnées homogènes

    // Q6
    //vec4 clipPosition=eyePosition;

    // Q10
    //vec4 clipPosition=projection*eyePosition;

    // Q15
    vec4 clipPosition=projection*transform*eyePosition; // transformation par la matrice de projection

    fColor=color;

    gl_Position=clipPosition;
}
