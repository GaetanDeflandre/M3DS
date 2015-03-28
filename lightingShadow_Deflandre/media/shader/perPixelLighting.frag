#version 130

out vec4 fragColor;

uniform vec3 materialDiffuse,materialSpecular;
uniform vec4 materialAmbient;

varying vec3 fN,fL,fV;

void main() {

    float diffuseIntensity;
    float specularIntensity=0;
    vec3 N,L,V;
    vec3 R;
    vec3 color;
    float shine=50.0;

    V=normalize(fV);
    L=normalize(fL);
    N=normalize(fN);

    // calcul du veteur spéculaire
    R=2*(dot(L,N))*N-L;
    R=normalize(R);

    // notez le max pour ne pas éclairer lorsque le produit scalaire est négatif (il faudra faire la même chose lors du calcul du spéculaire)
    diffuseIntensity=max(dot(N,L),0.0);

    specularIntensity=pow(max(dot(V,R),0.0),shine);

    // calcul du fragColor
    color = diffuseIntensity*materialDiffuse + materialAmbient.xyz + specularIntensity*materialSpecular;
    fragColor = vec4(color, materialAmbient.a);
}
