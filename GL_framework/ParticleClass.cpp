#include "ParticleClass.h"

ParticleClass::ParticleClass() {
	x = y = z = 0;
	vx = vy = vz = 0;
	mass = 1;
	//square* planos;
	//cylinder* cilindro;
	//
}

void ParticleClass::AccelerateParticle(float dt) {
	vy -= 9.81*dt;
}

//Funci�n que invierte la velocidad en algun eje en funci�n del parametro
//0: Eje X 1: Eje Y 2: Eje Z
void ParticleClass::Bounce(int which) {
	switch (which) {
	case 0:
		vx = -vx;
		break;
	case 1:
		vy = -vx;
		break;
	case 2:
		vz = -vx;
		break;
	default:
		std::cout << "Invalid Option" << std::endl;
		break;
	}

}

//Funci�n que mueve la particula en funci�n de sus vectores velocidad
void ParticleClass::MoveParticle(float dt) {
	x += vx*dt;
	y += vy*dt;
	z += vz*dt;
}

//Funci�n que inicializa la deteccion de colisiones de la part�cula
//void ParticleClass:: StartPart(int numSquares,square* squareArray,sphere* aSphere, cylinder* aCylinder) {
//	planos = new square[numSquares];
//	esfera = aSphere;
//	cilindro = aCylinder;
//}

//ParticleClass::~ParticleClass() {
//	delete planos;
//	delete esfera;
//	delete cilindro;
//}

void ParticleClass::CheckCol() {

}

void ParticleClass::UpdateParticle(float dt) {
	MoveParticle(dt);
	AccelerateParticle(dt);
}

