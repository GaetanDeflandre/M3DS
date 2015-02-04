#version 130

uniform sampler2D texture; // Question 22

in vec4 fColor;// Question 8
in vec2 fTexCoord;// Question 22

out vec4 fragColor;
        
void main() {
    //fragColor=texture2D(texture, fTexCoord); // que la couleur de la texture
    //fragColor=texture2D(texture,fTexCoord) * fColor; // multiplication de la couleur de la texture et de color

    fragColor=texture2D(texture,fTexCoord)*fColor.b;
    fragColor.g = fColor.g;

}
