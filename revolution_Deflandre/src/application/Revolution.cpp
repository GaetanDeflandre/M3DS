#include "Revolution.h"

#include "glsupport.h"


#include "GLRender.h"

#include "Vector3.h"

#include "GLTool.h"


using namespace std;
using namespace p3d;

Revolution::Revolution() {
    // default profile
    _profile.push_back(Vector3(-0.8,0.6,0.0));
    _profile.push_back(Vector3(-0.3,0.2,0.0));
    _profile.push_back(Vector3(-0.9,-0.8,0.0));

}


void Revolution::initSphere() {
    vector<float> p;
    vector<float> n;
    vector<float> t;

    vector<unsigned int> index;

    unsigned nbSlice=20; // include last slice that closes sphere
    unsigned nbStack=20;


    // *******
    //  ITDID

    // stacks
    for(unsigned i=0; i<=nbStack; i++) {

        // slices
        for(unsigned j=0; j<nbSlice; j++) {
            double theta = (double)(2*M_PI*j) / (double)nbSlice;
            double phi   = (double)(M_PI*i)   / (double)nbStack;

            float x = cos(theta)*sin(phi);
            float y = cos(phi);
            float z = sin(theta)*sin(phi);

            p.push_back(x);
            p.push_back(y);
            p.push_back(z);

            // le vecteur normal est sur la droite qui
            // passe par le centre de la sphère et le sommet de la normale
            n.push_back(x);
            n.push_back(y);
            n.push_back(z);

            t.push_back(((float)nbSlice-(float)j) / (float)nbSlice);
            t.push_back(((float)nbStack-(float)i) / (float)nbStack);

        }
    }

    unsigned nbPoints = nbStack * nbSlice;
    for(unsigned i=0; i<nbPoints; i++) {

        index.push_back(i+nbSlice);
        index.push_back(i);
        index.push_back(i+1);
        index.push_back(i+1);
        index.push_back(i+1+nbSlice);
        index.push_back(i+nbSlice);

    }


    // *******




    initVAO(index,p,n,t);

    _texture=&_earth;

}


void Revolution::initCube() {
    vector<float> p;
    vector<float> n;
    vector<float> t;

    vector<unsigned int> index;

    // *******
    //  TODO

    /*
    // Exercice 4 Q1: 8 sommets
    for(int x=1; x>=-1; x=x-2){
        for(int y=1; y>=-1; y=y-2){
            for(int z=1; z>=-1; z=z-2){
                p.push_back((float)x);
                p.push_back((float)y);
                p.push_back((float)z);
            }
        }
    }

    // Face front
    index.push_back(0);
    index.push_back(4);
    index.push_back(6);

    index.push_back(0);
    index.push_back(6);
    index.push_back(2);

    // Face rigth
    index.push_back(1);
    index.push_back(0);
    index.push_back(2);

    index.push_back(1);
    index.push_back(2);
    index.push_back(3);

    // Face left
    index.push_back(4);
    index.push_back(5);
    index.push_back(6);

    index.push_back(5);
    index.push_back(7);
    index.push_back(6);

    // Face back
    index.push_back(5);
    index.push_back(1);
    index.push_back(3);

    index.push_back(5);
    index.push_back(3);
    index.push_back(7);

    // Face up
    index.push_back(1);
    index.push_back(5);
    index.push_back(4);

    index.push_back(1);
    index.push_back(4);
    index.push_back(0);

    // Face down
    index.push_back(7);
    index.push_back(3);
    index.push_back(2);

    index.push_back(7);
    index.push_back(2);
    index.push_back(6);
    */

    // Exercice 4 Q2

    // Face front
    // Triangle 1
    // v0
    p.push_back(1);
    p.push_back(1);
    p.push_back(1);
    n.push_back(0);
    n.push_back(0);
    n.push_back(1);
    t.push_back(0);
    t.push_back(0.5);
    index.push_back(0);

    // v1
    p.push_back(-1);
    p.push_back(1);
    p.push_back(1);
    n.push_back(0);
    n.push_back(0);
    n.push_back(1);
    t.push_back(0.33);
    t.push_back(0.5);
    index.push_back(1);

    // v2
    p.push_back(1);
    p.push_back(-1);
    p.push_back(1);
    n.push_back(0);
    n.push_back(0);
    n.push_back(1);
    t.push_back(0);
    t.push_back(1);
    index.push_back(2);

    // Triangle 2
    // v2
    p.push_back(1);
    p.push_back(-1);
    p.push_back(1);
    n.push_back(0);
    n.push_back(0);
    n.push_back(1);
    t.push_back(0);
    t.push_back(1);
    index.push_back(3);

    // v1
    p.push_back(-1);
    p.push_back(1);
    p.push_back(1);
    n.push_back(0);
    n.push_back(0);
    n.push_back(1);
    t.push_back(0.33);
    t.push_back(0.5);
    index.push_back(4);


    // v3
    p.push_back(-1);
    p.push_back(-1);
    p.push_back(1);
    n.push_back(0);
    n.push_back(0);
    n.push_back(1);
    t.push_back(0);
    t.push_back(0.5);
    index.push_back(5);



    // Face rigth
    // Triangle 1
    // v0
    p.push_back(1);
    p.push_back(1);
    p.push_back(1);
    n.push_back(1);
    n.push_back(0);
    n.push_back(0);
    t.push_back(0.33);
    t.push_back(0.5);
    index.push_back(6);

    // v2
    p.push_back(1);
    p.push_back(-1);
    p.push_back(1);
    n.push_back(1);
    n.push_back(0);
    n.push_back(0);
    t.push_back(0.33);
    t.push_back(0);
    index.push_back(7);

    // v6
    p.push_back(1);
    p.push_back(-1);
    p.push_back(-1);
    n.push_back(1);
    n.push_back(0);
    n.push_back(0);
    t.push_back(0.66);
    t.push_back(0);
    index.push_back(8);

    // Triangle 2
    // v0
    p.push_back(1);
    p.push_back(1);
    p.push_back(1);
    n.push_back(1);
    n.push_back(0);
    n.push_back(0);
    t.push_back(0.33);
    t.push_back(0.5);
    index.push_back(9);

    // v6
    p.push_back(1);
    p.push_back(-1);
    p.push_back(-1);
    n.push_back(1);
    n.push_back(0);
    n.push_back(0);
    t.push_back(0.66);
    t.push_back(0);
    index.push_back(10);


    // v4
    p.push_back(1);
    p.push_back(1);
    p.push_back(-1);
    n.push_back(1);
    n.push_back(0);
    n.push_back(0);
    t.push_back(0.66);
    t.push_back(0.5);
    index.push_back(11);

    // Face left
    // Triangle 1
    // v1
    p.push_back(-1);
    p.push_back(1);
    p.push_back(1);
    n.push_back(-1);
    n.push_back(0);
    n.push_back(0);
    t.push_back(0.33);
    t.push_back(1);
    index.push_back(12);

    // v7
    p.push_back(-1);
    p.push_back(-1);
    p.push_back(-1);
    n.push_back(-1);
    n.push_back(0);
    n.push_back(0);
    t.push_back(0.66);
    t.push_back(0.5);
    index.push_back(13);

    // v3
    p.push_back(-1);
    p.push_back(-1);
    p.push_back(1);
    n.push_back(-1);
    n.push_back(0);
    n.push_back(0);
    t.push_back(0.33);
    t.push_back(0.5);
    index.push_back(14);


    // Triangle 2
    // v1
    p.push_back(-1);
    p.push_back(1);
    p.push_back(1);
    n.push_back(-1);
    n.push_back(0);
    n.push_back(0);
    t.push_back(0.33);
    t.push_back(1);
    index.push_back(15);

    // v5
    p.push_back(-1);
    p.push_back(1);
    p.push_back(-1);
    n.push_back(-1);
    n.push_back(0);
    n.push_back(0);
    t.push_back(0.66);
    t.push_back(1);
    index.push_back(16);

    // v7
    p.push_back(-1);
    p.push_back(-1);
    p.push_back(-1);
    n.push_back(-1);
    n.push_back(0);
    n.push_back(0);
    t.push_back(0.66);
    t.push_back(0.5);
    index.push_back(17);

    // Face back
    // Triangle 1
    // v6
    p.push_back(1);
    p.push_back(-1);
    p.push_back(-1);
    n.push_back(0);
    n.push_back(0);
    n.push_back(-1);
    t.push_back(1);
    t.push_back(0);
    index.push_back(18);

    // v5
    p.push_back(-1);
    p.push_back(1);
    p.push_back(-1);
    n.push_back(0);
    n.push_back(0);
    n.push_back(-1);
    t.push_back(0.66);
    t.push_back(0.5);
    index.push_back(19);

    // v4
    p.push_back(1);
    p.push_back(1);
    p.push_back(-1);
    n.push_back(0);
    n.push_back(0);
    n.push_back(-1);
    t.push_back(1);
    t.push_back(0.5);
    index.push_back(20);


    // Triangle 2
    // v5
    p.push_back(-1);
    p.push_back(1);
    p.push_back(-1);
    n.push_back(0);
    n.push_back(0);
    n.push_back(-1);
    t.push_back(0.66);
    t.push_back(0.5);
    index.push_back(21);

    // v6
    p.push_back(1);
    p.push_back(-1);
    p.push_back(-1);
    n.push_back(0);
    n.push_back(0);
    n.push_back(-1);
    t.push_back(1);
    t.push_back(0);
    index.push_back(22);

    // v7
    p.push_back(-1);
    p.push_back(-1);
    p.push_back(-1);
    n.push_back(0);
    n.push_back(0);
    n.push_back(-1);
    t.push_back(0.66);
    t.push_back(0);
    index.push_back(23);

    // Face up
    // Triangle 1
    // v5
    p.push_back(-1);
    p.push_back(1);
    p.push_back(-1);
    n.push_back(0);
    n.push_back(1);
    n.push_back(0);
    t.push_back(0);
    t.push_back(0.5);
    index.push_back(24);

    // v1
    p.push_back(-1);
    p.push_back(1);
    p.push_back(1);
    n.push_back(0);
    n.push_back(1);
    n.push_back(0);
    t.push_back(0);
    t.push_back(0);
    index.push_back(25);

    // v4
    p.push_back(1);
    p.push_back(1);
    p.push_back(-1);
    n.push_back(0);
    n.push_back(1);
    n.push_back(0);
    t.push_back(0.33);
    t.push_back(0.5);
    index.push_back(26);


    // Triangle 2
    // v0
    p.push_back(1);
    p.push_back(1);
    p.push_back(1);
    n.push_back(0);
    n.push_back(1);
    n.push_back(0);
    t.push_back(0.33);
    t.push_back(0);
    index.push_back(27);

    // v4
    p.push_back(1);
    p.push_back(1);
    p.push_back(-1);
    n.push_back(0);
    n.push_back(1);
    n.push_back(0);
    t.push_back(0.33);
    t.push_back(0.5);
    index.push_back(28);

    // v1
    p.push_back(-1);
    p.push_back(1);
    p.push_back(1);
    n.push_back(0);
    n.push_back(1);
    n.push_back(0);
    t.push_back(0);
    t.push_back(0);
    index.push_back(29);

    // Face down
    // Triangle 1
    // v2
    p.push_back(1);
    p.push_back(-1);
    p.push_back(1);
    n.push_back(0);
    n.push_back(-1);
    n.push_back(0);
    t.push_back(1);
    t.push_back(0.5);
    index.push_back(30);

    // v3
    p.push_back(-1);
    p.push_back(-1);
    p.push_back(1);
    n.push_back(0);
    n.push_back(-1);
    n.push_back(0);
    t.push_back(0.66);
    t.push_back(0.5);
    index.push_back(31);

    // v7
    p.push_back(-1);
    p.push_back(-1);
    p.push_back(-1);
    n.push_back(0);
    n.push_back(-1);
    n.push_back(0);
    t.push_back(0.66);
    t.push_back(1);
    index.push_back(32);

    // Triangle 2
    // v7
    p.push_back(-1);
    p.push_back(-1);
    p.push_back(-1);
    n.push_back(0);
    n.push_back(-1);
    n.push_back(0);
    t.push_back(0.66);
    t.push_back(1);
    index.push_back(33);

    // v6
    p.push_back(1);
    p.push_back(-1);
    p.push_back(-1);
    n.push_back(0);
    n.push_back(-1);
    n.push_back(0);
    t.push_back(1);
    t.push_back(1);
    index.push_back(34);

    // v2
    p.push_back(1);
    p.push_back(-1);
    p.push_back(1);
    n.push_back(0);
    n.push_back(-1);
    n.push_back(0);
    t.push_back(1);
    t.push_back(0.5);
    index.push_back(35);


    // *******


    initVAO(index,p,n,t);

    _texture=&_dice;
}


void Revolution::initRevolution() {
    if (_profile.size()<2) return; // more than 2 vertices in the profile

    vector<float> p;
    vector<float> n;
    vector<float> t;

    vector<unsigned int> index;

    unsigned nbSlice=40; // include last slice that closes the object
    unsigned nbStack=_profile.size();

    std::vector<Vector3> faceNormalProfile;
    std::vector<Vector3> normalProfile; // to compute normal profile

    // *******
    //  ITDID


    // calcul des normales de chaque arete
    for(unsigned i=0; i<nbStack-1; i++){
        Vector3 dir = _profile[i+1]-_profile[i];
        faceNormalProfile.push_back(Vector3(dir.y(),dir.x(),0));
    }

    // calcul des normales de chaque sommet
    normalProfile.push_back(faceNormalProfile[0]);
    for(unsigned i=0; i<nbStack-1; i++){
        normalProfile.push_back((faceNormalProfile[i]+faceNormalProfile[i+1])/2);
    }

    // stacks
    for(unsigned i=0; i<=nbStack; i++) {

        // slices
        for(unsigned j=0; j<nbSlice; j++) {

            double theta = (double)(2*M_PI*j) / (double)nbSlice;

            Vector3 tmp = _profile[i].rotationY(theta);
            Vector3 ntmp = normalProfile[i].rotationY(theta);

            float x = tmp.x();
            float y = tmp.y();
            float z = tmp.z();

            p.push_back(x);
            p.push_back(y);
            p.push_back(z);

            n.push_back(ntmp.x());
            n.push_back(ntmp.y());
            n.push_back(ntmp.z());

            t.push_back(((float)nbSlice-(float)j) / (float)nbSlice);
            t.push_back(((float)nbStack-(float)i) / (float)nbStack);

        }
    }

    unsigned nbPoints = nbStack * (nbSlice-1);
    for(unsigned i=0; i<nbPoints; i++) {

        index.push_back(i+nbSlice);
        index.push_back(i);
        index.push_back(i+1);
        index.push_back(i+1);
        index.push_back(i+1+nbSlice);
        index.push_back(i+nbSlice);

    }


    // *******





    initVAO(index,p,n,t);
    _texture=&_ul1;
}


void Revolution::init() {
    glGenBuffers(1,&_vbo);
    glGenBuffers(1,&_elementBuffer);
    glGenVertexArrays(1,&_vao);

    _earth.readMipmap("EarthDay512.jpg");
    _dice.readMipmap("dice.png");
    _ul1.readMipmap("UL1-IEEA.jpg");

}


void Revolution::draw(EShader mode) {
    //  return;
    glBindVertexArray(_vao);


    p3d::material(Vector4(0,0,0,1),Vector3(0,0.8,0.2),Vector3(0,0.2,0.8),100);
    p3d::diffuseBackColor=Vector3(0.8,0,0);
    if (mode==Shader_Ambient) {
        p3d::ambientColor=Vector4(0.0,0.8,0,1);
        p3d::ambientBackColor=Vector4(0.8,0.0,0,1);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }

    _texture->bind(0);

    switch(mode) {
    case Shader_Ambient:p3d::shaderVertexAmbient();break;
    case Shader_Light:p3d::shaderLightPhong();break;
    case Shader_Texture:p3d::shaderTextureLight();break;
    }


    glDrawElements(GL_TRIANGLES,_nbElement,GL_UNSIGNED_INT,0);



    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBindVertexArray(0);

}


// Caution : position should be a (x,y,z) array, normal (x,y,z) array, texCoord (x,y) array. lengths should be coherent
void Revolution::initVAO(const std::vector<unsigned int> &index,const std::vector<float> &position,const std::vector<float> &normal,const std::vector<float> &texCoord) {

    vector<float> attrib;
    attrib.resize(position.size()*8);
    for(unsigned int i=0;i<position.size()/3;++i) {
        attrib[i*8+0]=position[i*3+0];
        attrib[i*8+1]=position[i*3+1];
        attrib[i*8+2]=position[i*3+2];

        if (!normal.empty()) {
            attrib[i*8+3]=normal[i*3+0];
            attrib[i*8+4]=normal[i*3+1];
            attrib[i*8+5]=normal[i*3+2];
        }

        if (!texCoord.empty()) {
            attrib[i*8+6]=texCoord[i*2+0];
            attrib[i*8+7]=texCoord[i*2+1];
        }
    }



    glBindBuffer(GL_ARRAY_BUFFER,_vbo);
    glBufferData(GL_ARRAY_BUFFER,attrib.size()*sizeof(float),attrib.data(),GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,index.size()*sizeof(unsigned int),index.data(),GL_STATIC_DRAW);
    _nbElement=index.size();

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER,_vbo);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),0);                                   // position
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(const GLvoid *)(3*sizeof(float)));   // normal
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(const GLvoid *)(6*sizeof(float)));   // texCoord

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_elementBuffer);

    glBindVertexArray(0);

}

void Revolution::drawProfile() {
    p3d::ambientColor=Vector4(1,0,0,1);
    p3d::shaderVertexAmbient();
    p3d::drawLineStrip(_profile);
    p3d::drawPoints(_profile);

    vector<Vector3> mirror;
    for(auto &p:_profile) {
        mirror.push_back(Vector3(-p.x(),p.y(),p.z()));
    }

    p3d::uniformAmbient(Vector4(0,0,0,1));
    p3d::drawLineStrip(mirror);
    p3d::drawPoints(mirror);

    p3d::uniformAmbient(Vector4(0,1,0,1));

    std::vector<p3d::Vector3> line = {Vector3(0,-1,0),Vector3(0,1,0)};

    p3d::drawLines(line);



}



