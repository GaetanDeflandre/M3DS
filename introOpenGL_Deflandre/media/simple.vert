#version 130
        
in vec3 position;
in vec4 color;

out vec4 fColor;// Question 8
        
void main() {
    fColor = color;// Question 8
    gl_Position=vec4(position,1.0);
}
