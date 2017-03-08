#include "ParticleClass.h"

ParticleClass::ParticleClass() {
	x = y = z = 0;
	vx = vy = vz = 0;
	ax = az = 0;
	ay = -9.81f;
	timeToLive = 1.5f;
	timeAlive = 0.0f;
	isAlive = false;
	mass = 1;
}

//Función que aplica la gravedad sobre el vector velocidad Y de la partícula

void ParticleClass::Bounce(Plane plano) {

}

void ParticleClass::Accelerate(float dt) {
	vx = vx + ax*dt;
	vy = vy + ay*dt;
	vz = vz + az*dt;
}

//Función que mueve la particula en función de sus vectores velocidad
void ParticleClass::MoveParticle(float dt, solucionMov type) {
	if(type == EULER){
		x = x + vx*dt;
		y = y + vy*dt;
		z = z + vz*dt;
		Accelerate(dt);
	}
	else {

	}
}

void ParticleClass::CheckCol() {

}
extern int contadorParticulas;
extern int firstPosAlive;
extern int maxParticles;

void ParticleClass::Die() {
	contadorParticulas--;
	firstPosAlive++;
	firstPosAlive = firstPosAlive%maxParticles;
	isAlive = false;
	timeAlive = 0;
	//vx = vy = vz = 0;
	x = orgX;
	y = orgY;
	z = orgZ;
//	std::cout << "Diededed" << std::endl;
}

void ParticleClass::UpdateParticle(float dt, ParticleClass::solucionMov type) {
	if (timeAlive >= timeToLive)
		Die();
	else {
		timeAlive += dt;
		MoveParticle(dt,type);
	}
}

