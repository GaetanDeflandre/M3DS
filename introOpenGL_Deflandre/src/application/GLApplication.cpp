#include "GLApplication.h"

#include <iostream>
#include <cmath>

using namespace std;

GLApplication::~GLApplication() {
}

GLApplication::GLApplication() {

    /*
    // Ancienne déclaration
    _trianglePosition = {
        -0.8,-0.5,0.0, // vertex 0
        -0.2,-0.5,0.0, // 1
        -0.5,0.5,0.0,  // 2

        0.2,0.5,0.0,  // 3
        0.8,0.5,0.0,  // 4
        0.5,-0.5,0.0  // 5
    };
    //*/

    /*
    // Déclaration Question 9
    _trianglePosition = {
        -0.8,-0.5,0.0,// vertex 0 anciennement vertex 0
        0.8,0.5,0.0,  // 1 anciennement 4
        -0.5,0.5,0.0, // 2 anciennement 2
        -0.2,-0.5,0.0,// 3 anciennement 1
        0.5,-0.5,0.0, // 4 anciennement 5
        0.2,0.5,0.0   // 5 anciennement 3
    };
    //*/

    /*
    // Déclaration Question 13
    _trianglePosition = {
        -0.8,-0.8,0.0,
        0.8,0.8,0.0,
        0.0,0.2,0.0,
        -0.8,0.8,0.0,
        0.8,-0.8,0.0
        //0.0,0.2,0.0
    };
    //*/

    /*
    // Déclaration Question 14
    _trianglePosition = {
        -0.8,-0.8,0.0,
        -0.6,0.8,0.0,
        -0.4,-0.6,0.0,
        -0.2,0.6,0.0,
        0.0,-0.8,0.0,
        0.2,0.8,0.0,
        0.4,-0.6,0.0,
        0.6,0.6,0.0,
        0.8,-0.8,0.0
    };
    //*/

    /*
    // Déclaration Question 17
    _trianglePosition = {
        -0.6,-0.6,0.0,
        -0.6,0.6,0.0,
        -0.2,-0.6,0.0,
        -0.2,0.6,0.0,
        0.2,-0.6,0.0,
        0.2,0.6,0.0,
        0.6,-0.6,0.0,
        0.6,0.6,0.0,
    };
    //*/

    /*
    // Déclaration coleur initiale
    _triangleColor = {
        0.3,0,0.6,1,
        0.3,0,0.6,1,
        0.0,0.9,0.0,1,

        0.0,0.5,0.6,1,
        0.0,0.5,0.6,1,
        0.9,0.0,0.0,1
    };
    //*/

    // Question 14 tous les sommets à rouge :
    /*
    _triangleColor.clear();

    for(unsigned int i=0;i<9;++i) {

        // rouge
        _triangleColor.push_back(1);
        _triangleColor.push_back(0);
        _triangleColor.push_back(0);
        _triangleColor.push_back(1);

        // vert
        _triangleColor.push_back(0);
        _triangleColor.push_back(1);
        _triangleColor.push_back(0);
        _triangleColor.push_back(1);

        // bleu
        _triangleColor.push_back(0);
        _triangleColor.push_back(0);
        _triangleColor.push_back(1);
        _triangleColor.push_back(1);

        // mangenta
        _triangleColor.push_back(1);
        _triangleColor.push_back(0);
        _triangleColor.push_back(1);
        _triangleColor.push_back(1);

        // cyan
        _triangleColor.push_back(0);
        _triangleColor.push_back(1);
        _triangleColor.push_back(1);
        _triangleColor.push_back(1);

    }
    //*/


    /* Question 11: ordre des sommets */
    //_elementData = {0,3,2,5,1,4};

    /* Question 13 */
    //_elementData = {0,3,2,2,1,4};

    // Question 21
    _coeff = 0;
    _coeff_step = 0.05;

    /*
    // Déclaration Question 22
    _trianglePosition = {
        -0.6,-0.8,0,
        -0.6,0.8,0,
        0.6,-0.8,0,
        0.6,0.8,0
    };
    //*/

    /*
    // Text décl Question 24
     _triangleTexCoord = {
         0,0,
         0,1,
         1,0,
         1,1
     };
     //*/

     /*
     // Text décl Question 25
      _triangleTexCoord = {
          0,0.5,
          0,1,
          0.5,0.5,
          0.5,1
      };
      //*/

}

/* Question 18 */
/** Initialise le tableau _trianglePosition */
void GLApplication::initStrip(unsigned nbSlice,float xmin,float xmax,float ymin,float ymax){

    const float ALPHA = 1;

    _trianglePosition.clear();
    _triangleColor.clear();

    float stepx = (abs(xmax)+abs(xmin)) / nbSlice;
    float step_color = 1.0 / (float)nbSlice;

    if(stepx<=0 || step_color<=0){
        cerr << "ERROR: Le pas est négatif" << endl;
        return;
    }

    for(unsigned i=0; i<=nbSlice; i++){


        // SOMMETS DU BAS
        // position
        _trianglePosition.push_back(xmin + i*stepx);
        _trianglePosition.push_back(ymin);
        _trianglePosition.push_back(0.0);

        // coleur
        _triangleColor.push_back(0);
        _triangleColor.push_back(step_color*i);
        _triangleColor.push_back(0);
        _triangleColor.push_back(ALPHA);


        // SOMMETS DU HAUT
        // position
        _trianglePosition.push_back(xmin + i*stepx);
        _trianglePosition.push_back(ymax);
        _trianglePosition.push_back(0.0);

        // coleur
        _triangleColor.push_back(0);
        _triangleColor.push_back(0);
        _triangleColor.push_back(1 - (step_color*i));
        _triangleColor.push_back(ALPHA);
    }

    _vertices_number = (nbSlice+1)*2;
}

void GLApplication::initRing(unsigned nbSlice,float r0,float r1){

    const float ALPHA = 1;

    _trianglePosition.clear();
    _triangleColor.clear();
    _triangleTexCoord.clear();

    float step_theta = 2*M_PI / (float)nbSlice;
    float step_color = 1.0 / (float)nbSlice;

    if(step_theta<=0 || step_color<=0){
        cerr << "ERROR: Le pas est négatif" << endl;
        return;
    }

    for(unsigned i=0; i<=nbSlice; i++){

        float theta = i * step_theta;
        float posX, posY;

        // SOMMETS INTERIEUR
        // position
        posX = r0 * cos(theta);
        posY = r0 * sin(theta);
        _trianglePosition.push_back(posX);
        _trianglePosition.push_back(posY);
        _trianglePosition.push_back(0.0);

        // coleur
        _triangleColor.push_back(0);
        _triangleColor.push_back(1/*step_color*i*/);
        _triangleColor.push_back(0);
        _triangleColor.push_back(ALPHA);

        // texture
        // on ramène vers une coordonnée normalisée [0;1]
        _triangleTexCoord.push_back((posX+1)/2);
        _triangleTexCoord.push_back((posY+1)/2);

        // SOMMETS EXTERIEUR
        // position
        posX = r1 * cos(theta);
        posY = r1 * sin(theta);
        _trianglePosition.push_back(posX);
        _trianglePosition.push_back(posY);
        _trianglePosition.push_back(0.0);

        // coleur
        _triangleColor.push_back(0);
        _triangleColor.push_back(0);
        _triangleColor.push_back(1/* - (step_color*i)*/);
        _triangleColor.push_back(ALPHA);

        // texture
        // on ramène vers une coordonnée normalisée [0;1]
        _triangleTexCoord.push_back((posX+1)/2);
        _triangleTexCoord.push_back((posY+1)/2);
    }

    _vertices_number = (nbSlice+1)*2;

}


/** ********************************************************************** **/
void GLApplication::initialize() {
    // appelée 1 seule fois à l'initialisation du contexte
    // => initialisations OpenGL
    glClearColor(1,1,1,1);

    glLineWidth(2.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


    _shader0=initProgram("simple");


    //initStrip(30,  -0.8, 0.8,  -0.8, 0.8);
    initRing(30, 0.2, 0.6);
    initTriangleBuffer();
    initTriangleVAO();
    initTexture();


}

void GLApplication::resize(int width,int height) {
    // appelée à chaque dimensionnement du widget OpenGL
    // (inclus l'ouverture de la fenêtre)
    // => réglages liés à la taille de la fenêtre
    glViewport(0,0,width,height);
    // ...
}

void GLApplication::update() {
    // appelée toutes les 20ms (60Hz)
    // => mettre à jour les données de l'application
    // avant l'affichage de la prochaine image (animation)
    // ...

    /* Question 21 */
    //*
    if(_coeff>1){
        _coeff_step = _coeff_step*-1;
    }

    if(_coeff<0){
        _coeff_step = abs(_coeff_step);
    }

    _coeff += _coeff_step;
    //*/

    /* /!\ pas d'animation fixe coeff a 1 */
    //_coeff = 1;

}

void GLApplication::draw() {
    // appelée après chaque update
    // => tracer toute l'image
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(_shader0);
    glBindVertexArray(_triangleVAO);

    /*
    // code initiale
    glDrawArrays(GL_TRIANGLES,0,6);
    //*/

    /* Question 11 */
    //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

    /* Question 14 */
    //glDrawArrays(GL_TRIANGLE_STRIP,0,9);

    /* Question 21 */
    // Méthode a mettre juste avant le glDrawArrays
    glUniform1f(glGetUniformLocation(_shader0,"coeff"),_coeff);

    /* Question 17 */
    //glDrawArrays(GL_TRIANGLE_STRIP,0,_vertices_number);

    /* Question 22 */
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    int locationTexUnit = glGetUniformLocation(_shader0, "texture");
    glUniform1i(locationTexUnit, 0);
    glDrawArrays(GL_TRIANGLE_STRIP,0,_trianglePosition.size()/3);

    glBindVertexArray(0);
    glUseProgram(0);


    snapshot(); // capture opengl window if requested
}

/** ********************************************************************** **/
/** i = button number, s = button text
 */
void GLApplication::leftPanel(int i,const std::string &s) {
    cout << "GLApplication : button clicked " << i << " " << s << endl;
    /*
    switch (i) {
    case 0:menu0();break;
    case 1:menu1();break;
    }
    //*/
}




/** *********************************************************** **/
GLuint GLApplication::initProgram(const std::string &filename) {
    GLuint program;
    int infoLength; // for message error

    string vertexSource=p3d::readTextFile(filename+".vert");
    string fragmentSource=p3d::readTextFile(filename+".frag");

    program=glCreateProgram();
    GLuint vertexShader=glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    glAttachShader(program,vertexShader);
    glAttachShader(program,fragmentShader);

    const char *source;
    source=vertexSource.c_str();
    glShaderSource(vertexShader,1,&source,NULL);
    source=fragmentSource.c_str();
    glShaderSource(fragmentShader,1,&source,NULL);

    GLint ok;
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&ok);
    if (!ok) {
        glGetShaderiv(vertexShader,GL_INFO_LOG_LENGTH,&infoLength);
        cout << "=============================" << endl;
        cout << "GLSL Error : " << endl;
        char *info=new char[infoLength];
        glGetShaderInfoLog(vertexShader,infoLength,NULL,info);
        cout << info;
        cout << endl;
        delete info;
        throw ErrorD("Vertex Shader compilation error");
    }

    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&ok);
    if (!ok) {
        glGetShaderiv(fragmentShader,GL_INFO_LOG_LENGTH,&infoLength);
        cout << "=============================" << endl;
        cout << "GLSL Error : " << endl;
        char *info=new char[infoLength];
        glGetShaderInfoLog(fragmentShader,infoLength,NULL,info);
        cout << info;
        cout << endl;
        delete info;
        throw ErrorD("Vertex Shader compilation error");
    }

    glBindAttribLocation(program,0,"position");

    /* Question 8 */
    glBindAttribLocation(program,1,"color");
    //glGetAttribLocation(program,"color");

    /* Question 22 */
    glBindAttribLocation(program,2,"texture");

    glLinkProgram(program);
    glGetProgramiv(program,GL_LINK_STATUS,&ok);
    if (!ok) {
        char *info=new char[infoLength];
        glGetProgramInfoLog(program,infoLength,NULL,info);
        cout << "Info Log :" << endl;
        cout << info;
        cout << endl;
        delete info;
        throw ErrorD("Program Shader : link error (varyings ok ?)");
    }

    return program;
}


void GLApplication::initTexture() {
    QImage img;
    img.load("../media/lagoon.jpg");
    img=img.convertToFormat(QImage::Format_ARGB32).mirrored();

    glGenTextures(1,&_textureId);
    glBindTexture(GL_TEXTURE_2D,_textureId);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.width(),img.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,img.bits());



    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
}


void GLApplication::initTriangleBuffer() {

    glGenBuffers(1,&_trianglePositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,_trianglePositionBuffer);
    glBufferData(GL_ARRAY_BUFFER,_trianglePosition.size()*sizeof(float),_trianglePosition.data(),GL_STATIC_DRAW);

    /* Question 8 */
    glGenBuffers(1,&_triangleColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,_triangleColorBuffer);
    glBufferData(GL_ARRAY_BUFFER,_triangleColor.size()*sizeof(float),_triangleColor.data(),GL_STATIC_DRAW);

    /* Question 11 */
    glGenBuffers(1,&_elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,_elementData.size()*sizeof(unsigned int),_elementData.data(),GL_STATIC_DRAW);

    /* Question 22 */
    glGenBuffers(1,&_triangleTexCoordBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,_triangleTexCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER,_triangleTexCoord.size()*sizeof(float),_triangleTexCoord.data(),GL_STATIC_DRAW);
}


void GLApplication::initTriangleVAO() {
    glGenVertexArrays(1,&_triangleVAO);
    glBindVertexArray(_triangleVAO);

    // position avec attribut 0
    glBindBuffer(GL_ARRAY_BUFFER,_trianglePositionBuffer);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

    /* Question 8 */
    // couleur avec attribut 1
    glBindBuffer(GL_ARRAY_BUFFER,_triangleColorBuffer);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,0);

    /* Question 11 */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);

    // position avec attribut 0
    glBindBuffer(GL_ARRAY_BUFFER,_triangleTexCoordBuffer);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,0);

    // /!\ a ne pas oublie
    // on active l'attribut 0 (pos)
    glEnableVertexAttribArray(0);
    // on active l'attribut 1 (color)
    glEnableVertexAttribArray(1);
    // on active l'attribut 1 (tex)
    glEnableVertexAttribArray(2);


    glBindVertexArray(0);
}



