#version 130

in vec3 position;
in vec3 normal;
uniform vec3 lightPosition;
uniform vec3 diffuseColor;

uniform mat4 projection;
uniform mat4 transform;

out vec3 fColor;

void main() {

    // Position
    vec4 eyePosition=vec4(position,1); // passage en coordonnées homogènes
    vec4 clipPosition=projection*transform*eyePosition; // transformation par la matrice de projection

    gl_Position=clipPosition;


    // Q24: Normale
    vec3 N = normal;
    vec3 L = lightPosition;

    N = normalize(N);
    L = normalize(L);

    float intensity = max(dot(N,L),0.0);

    fColor = intensity * diffuseColor;
}
