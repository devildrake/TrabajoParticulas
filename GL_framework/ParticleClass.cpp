#include "ParticleClass.h"

ParticleClass::ParticleClass() {
	x = y = z = 0;
	timeToLive = 1.0f;
	timeAlive = 0.0f;
	vx = vy = vz = 0;
	isAlive = false;
}

//Función que aplica la gravedad sobre el vector velocidad Y de la partícula
void ParticleClass::AccelerateParticle(float dt) {
	vy -= 9.81*dt;
}

void ParticleClass::Bounce(Plane plano) {

}

//Función que mueve la particula en función de sus vectores velocidad
void ParticleClass::MoveParticle(float dt) {
	x += vx*dt;
	y += vy*dt;
	z += vz*dt;
}

void ParticleClass::CheckCol() {

}

void ParticleClass::Spawn() {
	if (!isAlive) {
		isAlive = true;
	}
}

void ParticleClass::Die() {
	isAlive = false;
	timeAlive = 0;
	vx = vy = vz = 0;
	x = orgX;
	y = orgY;
	z = orgZ;
	std::cout << "Diededed" << std::endl;
}

void ParticleClass::UpdateParticle(float dt) {
	if (isAlive) {
		timeAlive += dt;
		MoveParticle(dt);
		AccelerateParticle(dt);
		if(timeAlive>=timeToLive){
			Die();
		}
	}
}

