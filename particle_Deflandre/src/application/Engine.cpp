#include "Engine.h"
#include <cstdlib>

#include "ParticleList.h"
#include "Particle.h"

/**
@file
@author F. Aubert
@brief Basic particle engine

*/

using namespace std;
using namespace p3d;



/** Intégration du mouvement
** - on parcourt l'ensemble des particules p : il faut mettre à jour la position et la vitesse de p durant l'intervalle de temps dt (passé en paramètre).
** - p->position() donne la position actuelle (de type Point3d), et p->position(unPoint3d) affecte la position de p
** - p->velocity() donne la vitesse actuelle (de type Vector3) et p->velocity(unVector3) affecte la vitesse de p
** - p->force() donne la somme des forces s'appliquant sur la particule p (de type Vector3 et calculée lors de la boucle principale).
** - p->mass() donne la masse de la particule

** Il s'agit ici d'affecter la nouvelle position et la nouvelle vitesse en appliquant l'intégration d'Euler (cf cours).

**/
void Engine::euler(double dt) {
    for(unsigned int i=0; i<_particleList->size(); i++) {
        Particle *p=(*_particleList)[i];
        if (p->alive()) {

            /* A COMPLETER : affecter la nouvelle vitesse et la nouvelle position de p avec p->velocity(??), et p->position(??). */

            Vector3 pos = p->position();
            Vector3 vel = p->velocity();
            Vector3 f = p->force();
            double m = p->mass();

            p->velocity(vel + (f/m)*dt);
            p->position(pos + vel*dt);

        }
    }
}


/** Calcule les forces appliquées à chaque particule
** Pour ajouter une force il suffit de faire p->addForce(unVector3) (permet de cumuler avec, éventuellement, d'autres forces provenant d'autres procédures).
** Ici, la force est initialement nulle, et on se contente d'ajouter la force de gravité dans le sens des y négatifs.
** p->mass() donne la masse de la particule.

**/

void Engine::computeForce() {
    for(unsigned int i=0; i<_particleList->size(); i++) {
        Particle *p=(*_particleList)[i];
        if (p->alive()) {

            /* A COMPLETER : appliquer les forces subies */

            const double G = 9.81;
            Vector3 gravity = Vector3(0,-G,0);

            p->addForce(gravity);


        }
    }
}


/** Détermine s'il y a une collision avec les plans de la scène et modifie en conséquence la position et la vitesse de la particule

** - chaque plan de la scène est parcouru (tableau _planeList) : il faut déterminer la collision de chaque particule p avec ce plan
** simplement en testant si p est du coté négatif du plan. Si oui, la particule a traversé le plan et on corrige alors sa vitesse et sa position.

**/
void Engine::collisionPlane() {
    for(unsigned int j=0; j<_planeList.size(); j++) {
        Plane *plane=_planeList[j];

        for(unsigned int i=0; i<_particleList->size(); i++) {
            Particle *p=(*_particleList)[i];
            if (p->alive()) {
                Vector3 posCorrection(0,0,0); // correction en position à calculer si collision
                Vector3 velCorrection(0,0,0); // correction en vitesse à calculer si collision
                /* A COMPLETER  : détecter collision et corriger vitesse/position */
                /* on peut utiliser p->position(), p->velocity() (et les setters), et plane->point() et plane->normal() */
                /* p->radius() donne le rayon de la particule (exercice avec les sphère). */


                Vector3 AP = plane->point() - p->position();
                Vector3 H = plane->project(p->position());
                Vector3 n = plane->normal();

                if (AP.dot(n) > 0){

                    // Ex1 Q3
                    /*
                    p->velocity(Vector3(0,0,0));
                    //*/

                    Vector3 vold = p->velocity();

                    // Ex1 Q4
                    //*
                    velCorrection = -vold;

                    Vector3 pRadius = Vector3(0,p->radius(),0);

                    posCorrection = (1+_epsi) * ( H - (p->position() - pRadius) );
                    //*/

                    // Ex1 Q5
                    //*
                    double reduc = 0.6;
                    velCorrection -= reduc * (1+_epsi) * ((vold).dot(n) * n);

                    //*/
                }

                // appliquer les corrections calculées :
                p->addPositionCorrec(posCorrection);
                p->addVelocityCorrec(velCorrection);
            }

        }

    }
}

/** Calcul de l'impulsion entre 2 sphères
** - n = normale lors de la collision {\bf normalisée !}
** - restititution : > 0.9 superball ;  <0.1 ecrasement
**/
double Engine::computeImpulse(Particle *p1, Particle *p2,const Vector3 &n, double restitution) {
    double res;
    double v12n=(p2->velocity()-p1->velocity()).dot(n);
    double inv_mass=1.0/p1->mass()+1.0/p2->mass();
    res=-(1.0+restitution)*v12n/(inv_mass);
    return res;

}

/** Collisions entre toutes les sphères :
** - on teste toutes les paires de particules (double boucle, sans redondances) : s'il y a collision entre 2 sphères p1 et p2 on répond par impulsion.
** - utilisez p1->addVelocityCorrec(...), p2->addVelocityCorrec(...), etc pour tenir compte des corrections issues de cette collision qui seront à appliquer à p1 et p2
** - l'appel à computeImpulse vous donne le coefficient d'impulsion (cette méthode se trouve juste au dessus pour déterminer les paramètres).

**/
void Engine::interCollision() {
    for(unsigned int i=0; i<_particleList->size(); i++) {
        Particle *p1=(*_particleList)[i];
        if (p1->alive()) {
            for(unsigned int j=i+1; j<_particleList->size(); j++) {
                Particle *p2=(*_particleList)[j];
                if (p2->alive()) {
                    Vector3 posCorrectionP1(0,0,0); // correction en position de P1
                    Vector3 velCorrectionP1(0,0,0); // correction en vitesse de P1
                    Vector3 posCorrectionP2(0,0,0); // correction en position de P2
                    Vector3 velCorrectionP2(0,0,0); // correction en vitesse de P2

                    /* A COMPLETER */
                    Vector3 v1old = p1->position();
                    Vector3 v2old = p2->position();

                    if(v1old.distance(v2old) < p1->radius()+p2->radius()){

                        Vector3 n =  v2old - v1old;
                        double k = computeImpulse(p1, p2, n, _epsi);
                        double d = (v1old-v2old).length() - p1->radius() - p2->radius();


                        double m1 = p1->mass();
                        double m2 = p2->mass();

                        posCorrectionP1 = (1+_epsi) * (m2/(m1+m2))*d*n;
                        velCorrectionP1 = -(j/m1)*n;

                        posCorrectionP2 = -(1+_epsi) * (m1/(m1+m2))*d*n;
                        velCorrectionP2 = (j/m2)*n;
                    }

                    // appliquer la correction éventuelle :
                    p1->addPositionCorrec(posCorrectionP1);
                    p1->addVelocityCorrec(velCorrectionP1);
                    p2->addPositionCorrec(posCorrectionP2);
                    p2->addVelocityCorrec(velCorrectionP2);


                }
            }
        }
    }


}

/** ************************************************************************************************************ */
/** ************************************************************************************************************ */
/** ************************************************************************************************************ */
/** ************************************************************************************************************ */


Engine::Engine() {
    //ctor
    _start=clock();
    _dt=0.01;

    _particleList=NULL;
    _windEnable=false;
    //  _boxList=NULL;

}

Engine::~Engine() {
    //dtor
}

void Engine::addPlane(Plane *p) {
    _planeList.push_back(p);
}

void Engine::particleList(ParticleList *l) {
    _particleList=l;
}

/*
void Engine::boxList(BoxList *b) {
  _boxList=b;
}
*/

void Engine::draw() {
    _particleList->draw();
    //  _boxList->draw();
}




void Engine::resetForce() {
    for(unsigned int i=0; i<_particleList->size(); i++) {
        Particle *p=(*_particleList)[i];
        if (p->alive()) {
            p->resetForce();
        }
    }
}





void Engine::updatePositionVelocity() {
    for(unsigned int i=0; i<_particleList->size(); i++) {
        Particle *p=(*_particleList)[i];
        if (p->alive()) {
            p->velocityCorrection();
            p->positionCorrection();
        }
    }
}


int Engine::nbParticle() {
    return _particleList->nbParticle();
}




/**
** Boucle principale (appelée à chaque tracé d'image) : résolution pour une durée dt
** - incrémentation du temps
** - résolution des collisions (détection/réponse par rapports aux plans, et aux autres sphères).
** - calcul des forces
** - intégration par euler
**/
void Engine::update() {
    // synchronisation très basique avec le "vrai temps"
    double elapsed;
    do {
        elapsed=double(clock()-_start)/CLOCKS_PER_SEC;
    } while (elapsed<_dt); // _dt est le pas de temps minimal : attente si pas atteint
    _start=clock();

    // réinitialise toutes les forces à 0
    resetForce();
    // résolution des collisions (affectation des corrections en vitesse et positions)
    // avec les plans de la scène :
    collisionPlane();
    // inter collisions entre toutes les particules :
    if (!_modeParticle) interCollision();
    // prise en compte des corrections :
    updatePositionVelocity();
    // calcul des forces appliquées à chaque particule
    computeForce();
    // calcul des positions/vitesses avec euler explicite
    euler(elapsed);
    // mise à jour des particules (naissances/morts)
    _particleList->updateLife();

}

void Engine::modeParticle(bool mode) {
    _modeParticle=mode;
    _particleList->modeParticle(mode);
}

void Engine::enableWind(const p3d::Line &ray) {
    _wind=ray;
    _windEnable=true;
}

void Engine::disableWind() {
    _windEnable=false;
}



