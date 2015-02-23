#include <math.h>
#include "Car.h"
#include "GLTool.h"
#include "GLRender.h"

using namespace p3d;
using namespace std;


// ************************************************************
Car::~Car() {
}

Car::Car() {
    _orientation.setIdentity();
    _position.set(0,0,0);
    _steering=0;
    _rotateWheel=0;
    _acceleration=0;
    _velocity=0;
}

// ******************************************************************
// méthodes à compléter lors du TP
void Car::drawRim() {
    p3d::modelviewMatrix.push();

    // Couleur jante
    p3d::diffuseColor=Vector3(1,0.8,0.2);

    // Nombre de rayon
    unsigned nb_rayon = 16;
    unsigned theta = 360/nb_rayon;

    // Centre de la jante
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(-0.25,0,0);
    p3d::modelviewMatrix.rotate(90,0,1,0);
    p3d::modelviewMatrix.scale(0.5,0.5,0.5);
    drawCylinder();
    p3d::modelviewMatrix.pop();

    // Les rayon
    p3d::modelviewMatrix.push();
    for (unsigned i=0; i<nb_rayon; i++){
        p3d::modelviewMatrix.push();
        p3d::modelviewMatrix.rotate(theta*i,1,0,0);
        p3d::modelviewMatrix.scale(0.1,0.1,2);
        drawCylinder();
        p3d::modelviewMatrix.pop();
    }
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.pop();
}

void Car::drawWheel() {
    p3d::modelviewMatrix.push();

    // Pneu
    p3d::diffuseColor=Vector3(0.05,0.05,0.05);
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.rotate(90,0,1,0);
    drawTorus();
    p3d::modelviewMatrix.pop();

    // Jante
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.scale(0.4,0.4,0.4);
    drawRim();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.pop();
}

void Car::drawAxle() {
    p3d::modelviewMatrix.push();

    // Essieu
    p3d::diffuseColor=Vector3(0.5,0.2,0.2);
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(-3,0,0);
    p3d::modelviewMatrix.rotate(90,0,1,0);
    p3d::modelviewMatrix.scale(0.1,0.1,6);
    drawCylinder();
    p3d::modelviewMatrix.pop();

    // Roue 1
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(-3,0,0);
    p3d::modelviewMatrix.rotate(-_rotateWheel/8,1,0,0);
    drawWheel();
    p3d::modelviewMatrix.pop();

    // Roue 2
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(3,0,0);
    p3d::modelviewMatrix.rotate(-_rotateWheel/8,1,0,0);
    drawWheel();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.pop();
}

void Car::drawBody() {
    p3d::modelviewMatrix.push();

    // Couleur de la carrosserie
    p3d::diffuseColor=Vector3(0.3,0.4,0.7);

    // partie basse
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.scale(1,1,2);
    drawCube();
    p3d::modelviewMatrix.pop();

    // partie haute
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(0,2,1);
    drawCube();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.pop();
}

void Car::draw() {
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.scale(0.5,0.5,0.5);
    p3d::modelviewMatrix.translate(0,-3,0);

    // Carrosserie
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(0,-0.8,0);
    p3d::modelviewMatrix.scale(2,1,2);
    drawBody();
    p3d::modelviewMatrix.pop();

    // Essieu arrière
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(0,-2,2);
    drawAxle();
    p3d::modelviewMatrix.pop();

    // Essieu avant
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(0,-2,-2);
    p3d::modelviewMatrix.rotate(_steering,0,1,0);
    drawAxle();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.pop();
}


void Car::drawWorld() {

    p3d::modelviewMatrix.push();

    p3d::modelviewMatrix.translate(_position);
    p3d::modelviewMatrix.rotate(_orientation);

    draw(); // tracé de la voiture dans son repère local
    p3d::modelviewMatrix.pop();
}

void Car::move() {

    // coefficients réducteurs
    const double reduc_roues = 0.02;
    const double reduc_vitesse = 0.3;

    _acceleration+=-_velocity * reduc_roues;
    _velocity+=_acceleration;
    _rotateWheel+=_velocity*20;
    _steering-=_steering/10*fabs(_velocity);

    _orientation.rotate(_steering*_velocity/(1.0+fabs(_velocity)),Vector3(0,1,0)); // le /100 est déterminé par essai/erreur

    // La direction dans le repère local de la voiture
    Vector3 direction = Vector3(0,0,-_velocity) * reduc_vitesse;

    // Chagement de repère
    _position += _orientation*direction;

}


void Car::accelerate() {
    _acceleration=0.05;

}

void Car::decelerate() {
    _acceleration=0;
}

void Car::brake() {
    _acceleration=-0.02;

}

void Car::turnLeft() {
    _steering+=0.5;
    if (_steering>35) _steering=35;
}

void Car::turnRight() {
    _steering-=0.5;
    if (_steering<-35) _steering=-35;
}





