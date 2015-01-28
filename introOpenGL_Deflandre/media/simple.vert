#version 130
        
in vec3 position;
in vec4 color;
uniform float coeff;

out vec4 fColor;// Question 8
        
void main() {
    vec3 newPosition=position;
    newPosition = position * coeff;
    fColor = color;// Question 8
    gl_Position=vec4(newPosition,1.0);
}
