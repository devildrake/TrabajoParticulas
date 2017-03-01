#pragma once
#include <iostream>
class ParticleClass {
private:
	class Plane {
	public:
		float d;
		float nx, ny, nz;
		Plane() {
			d = nx = ny = nz = 0;
		}
		Plane(float d,float nx, float ny, float nz) {
			this->nx = nx;
			this->ny = ny;
			this->nz = nz;
			this->d = d;
		}
	};
public:
	float orgX, orgY, orgZ;//Atributos iniciales de posicion
	float x, y, z; //Atributos de posición
	float vx, vy, vz; //Atributos de velocidad
	float timeAlive, timeToLive;
	bool isAlive;
	Plane planos[6];


	ParticleClass();

	void Spawn();

	void AccelerateParticle(float);

	void Die();

	void Bounce(Plane);

	void MoveParticle(float);

	void CheckCol();

	void UpdateParticle(float);

};