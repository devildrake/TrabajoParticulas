#pragma once
#include <iostream>
class ParticleClass {

	//struct cylinder {

	//};
	//struct sphere {
	//	float center;
	//	float radius;

	//};

	//struct square {
	//	float v1, v2, v3, v4;
	//};

	//square* planos;
	//cylinder* cilindro;
	//sphere* esfera;
public:
	float x, y, z;
	float vx, vy, vz;
	float mass;

	ParticleClass();

	void AccelerateParticle(float);

	//Funci�n que invierte la velocidad en algun eje en funci�n del parametro
	//0: Eje X 1: Eje Y 2: Eje Z
	void Bounce(int);

	//Funci�n que mueve la particula en funci�n de sus vectores velocidad
	void MoveParticle(float);

	//Funci�n que inicializa la deteccion de colisiones de la part�cula
	//void StartPart(int numSquares,square* squareArray,sphere* aSphere, cylinder* aCylinder) {
	//	planos = new square[numSquares];
	//	esfera = aSphere;
	//	cilindro = aCylinder;
	//}

	//~ParticleClass() {
	//	delete planos;
	//	delete esfera;
	//	delete cilindro;
	//}

	void CheckCol();

	void UpdateParticle(float);

};