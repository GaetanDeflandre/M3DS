#version 130

in vec3 position;
in vec4 color;
in vec2 texCoord; // Question 22

uniform float coeff;

out vec4 fColor;// Question 8
out vec2 fTexCoord;// Question 22

void main() {
    vec3 newPosition=position;
    newPosition = position * coeff;
    fColor = color;// Question 8
    fColor.g *= (1.0 - coeff);
    fTexCoord = texCoord;
    gl_Position=vec4(newPosition,1.0);
}
