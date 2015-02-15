#version 130

in vec3 position;
in vec3 normal;
uniform vec3 lightPosition;
uniform vec3 diffuseColor;

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 transformNormal;

out vec3 fColor;

void main() {

    // Position
    vec4 eyePosition=vec4(position,1); // passage en coordonnées homogènes
    vec4 clipPosition=projection*transform*eyePosition; // transformation par la matrice de projection

    gl_Position=clipPosition;


    // Q24 & 27: Normale

    // On passe les vecteurs des normales et de la source en vecteur 4.
    // Les vecteurs des normales et de la source ne sont pas des points,
    // mais des vecteurs, alors on met le w à 0
    float w = 0.0;
    vec4 N = vec4(normal,w);
    vec4 L = vec4(lightPosition,w);

    N = transform*N;

    N = normalize(N);
    L = normalize(L);

    float intensity = max(dot(N,L),0.0);

    fColor = intensity * diffuseColor;
}
