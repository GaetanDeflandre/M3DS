#version 130

in vec3 fN,fL,fV;

out vec4 fragColor;

uniform vec3 materialDiffuse,materialSpecular;
uniform vec4 materialAmbient;

void main() {

    float diffuseIntensity;
    float specularIntensity=0;
    vec3 N,L,V;
    vec3 R;
    vec4 color=vec4(0,0,0,0);
    float shine=50.0;

    V=fN;
    L=fL;
    N=fN;

    L=normalize(L);
    V=normalize(V);
    N=normalize(N);

    // calcul du veteur spéculaire
    R=2*(dot(L,N))*N-L;
    R=normalize(R);

    // notez le max pour ne pas éclairer lorsque le produit scalaire est négatif (il faudra faire la même chose lors du calcul du spéculaire)
    diffuseIntensity=max(dot(N,L),0.0);

    specularIntensity=max(pow(dot(V,R),shine),0.0);

    // rouge, vert, bleu de l'éclairement :
    color.rgb = diffuseIntensity*materialDiffuse + specularIntensity*materialSpecular + materialAmbient.xyz;
    // le alpha est porté uniquement par materialAmbient.a.:
    color.a=materialAmbient.a;

    fragColor=color;
}
