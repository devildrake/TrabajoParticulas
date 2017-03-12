#pragma once
#include <iostream>
#include <glm\vec3.hpp>
#include <glm\glm.hpp>

class ParticleClass {
private:
	bool doOnce;
	void VerletStartup(float);
	
public:
	class Plane {
	public:

		float d;
		float nx, ny, nz;
		Plane() {
			d = nx = ny = nz = 0;
		}
		Plane(float nx, float ny, float nz, float d) {
			this->nx = nx;
			this->ny = ny;
			this->nz = nz;
			this->d = d;
		}
		void SetPlaneStats(float nx, float ny, float nz, float d) {
			this->nx = nx;
			this->ny = ny;
			this->nz = nz;
			this->d = d;
		}
	};

	float orgX, orgY, orgZ;//Atributos iniciales de posicion
	float x, y, z; //Atributos de posición
	float antX, antY, antZ; //Posiciones anteriores que se necesitan para el Verlet.
	float prevX, prevY, prevZ;
	float vx, vy, vz; //Atributos de velocidad
	float ax, ay, az;
	float timeAlive, timeToLive;
	float mass;
	bool isAlive;
	enum solucionMov{EULER,VERLET};
	enum tipoMov { CASCADA,FUENTE };
	Plane planos[6];


	ParticleClass();


	void ColPlane(Plane, float);

	void ColSphere(float,float,float,float,float);

	void Accelerate(float);

	void Die();

	void Bounce(Plane,float);

	void MoveParticle(float, solucionMov);

	void CheckCol(float);

	void UpdateParticle(float, solucionMov);

};