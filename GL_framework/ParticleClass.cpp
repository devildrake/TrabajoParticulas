#include "ParticleClass.h"

ParticleClass::ParticleClass() {
	x = y = z = 0;
	vx = vy = vz = 0;
	ax = az = 0;
	ay = -9.81f;
	timeToLive = 2.5f;
	timeAlive = 0.0f;
	isAlive = false;
	doOnce = false;
	mass = 1;
	planos[0].SetPlaneStats(0.0f,100.0f,0.0f,0.0f); // Parte abajo del cubo
	planos[1].SetPlaneStats(0.0f, 0.0f, -100.0f, -500.0f);
	planos[2].SetPlaneStats(-100.0f, 0.0f, 0.0f, 500.0f);
	planos[3].SetPlaneStats(0.0f, 0.0f, 100.0f, -500.0f);
	planos[4].SetPlaneStats(100.0f, 0.0f, 0.0f, 500.0f);
	planos[5].SetPlaneStats(0.0f, -100.0f, 0.0f, 1000.0f);
}

//Función que aplica la gravedad sobre el vector velocidad Y de la partícula

void ParticleClass::Bounce(Plane plano,float dt) {
	//Aqui entra
	
	//REFLEJAR NUEVA POSICION
	//x = x - 2 * (plano.nx*x + plano.d)*plano.nx;
	//y = y - 2 * (plano.ny*y + plano.d)*plano.ny;
	//z = z - 2 * (plano.nz*z + plano.d)*plano.nz;
	//
	//antX = antX - 2 * (plano.nx*antX + plano.d)*plano.nx;
	//antY = antY - 2 * (plano.ny*antY + plano.d)*plano.ny;
	//antZ = antZ - 2 * (plano.nz*antZ + plano.d)*plano.nz;

	//vx = (x - antX) / dt;
	//vy = (y - antY) / dt;
	//vz = (z - antZ) / dt;
	//vx = vx - 2 * (plano.nx * vx)*plano.nx;
	//vy = vy - 2 * (plano.ny * vy)*plano.ny;
	//vz = vz - 2 * (plano.nz * vz)*plano.nz;
	//ESTO DE AQUI ARRIBA DEBERIA FUNCIONAR PERO SE LE VA CUANDO COLISIONA

	
	//std::cout << x << ", " << y << ", " << z << std::endl;

	//COLISION CON LA ESFERA
	x = x - 2 * (plano.nx*x + plano.d)*plano.nx;
	y = y - 2 * (plano.ny*y + plano.d)*plano.ny;
	z = z - 2 * (plano.nz*z + plano.d)*plano.nz;

	vx = vx - 2 * (plano.nx * vx)*plano.nx;
	vy = vy - 2 * (plano.ny * vy)*plano.ny;
	vz = vz - 2 * (plano.nz * vz)*plano.nz;
}

void ParticleClass::Accelerate(float dt) {
	vx = vx + ax*dt;
	vy = vy + ay*dt;
	vz = vz + az*dt;
}

//Función que mueve la particula en función de sus vectores velocidad
void ParticleClass::MoveParticle(float dt, solucionMov type) {
	float tempX, tempY, tempZ;
	
	if(type == EULER){
		doOnce = false;
		tempX = x;
		tempY = y;
		tempZ = z;

		x = x + vx*dt;
		y = y + vy*dt;
		z = z + vz*dt;

		antX = tempX;
		antY = tempY;
		antZ = tempZ;

		Accelerate(dt);
		CheckCol(dt);
	}
	else {
		if (!doOnce) {
			VerletStartup(dt);
			doOnce = true;
		}
		tempX = x;
		tempY = y;
		tempZ = z;

		x = x + (x - antX) + ax *(dt*dt);
		y = y + (y - antY) + ay *(dt*dt);
		z = z + (z - antZ) + az *(dt*dt);

		antX = tempX;
		antY = tempY;
		antZ = tempZ;

		Accelerate(dt);
		CheckCol(dt);
	}
}

void ParticleClass::VerletStartup(float dt) {
	antX = x - vx*dt;
	antY = y - vy*dt;
	antZ = z - vz*dt;
}

void ParticleClass::ColPlane(){
	//FORMA MAL DE HACERLO PERO QUE DEBERIA FUNCIONAR (esto es solo para el cubo)
	//colision suelo
	if (y <= 1) {
		vy = -vy;
		y = 1;
	}
	//colision con la cara izquierda
	if (x <= -4) {
		vx = -vx;
		x = -4;
	}
	//colision cara derecha
	if (x >= 5) {
		vx = -vx;
		x = 5;
	}
	//colision cara frontal
	if (z >= 5) {
		vz = -vz;
		z = 5;
	}
	//colision cara trasera
	if (z <= -5) {
		vz = -vz;
		z = -5;
	}
	//colision arriba
	if (y >= 10) {
		vy = -vy;
		y = 10;
	}
}

void ParticleClass::ColSphere(float centerX,float centerY,float centerZ, float radius, float dt) {
	float tNX, tNY, tNZ, tD; //componentes del plano tangente, vector normal y D
	if ((abs(centerX - x)<radius)&& (abs(centerY - y) < radius) && (abs(centerZ - z) < radius)) {
		//YA DETECTA BIEN LA COLISION CON LA ESFERA
		tNX = x - centerX;
		tNY = y - centerY;
		tNZ = z - centerZ;
		tD = -((tNX * x) + (tNY * y) + (tNZ * z));
		Bounce(Plane(tNX,tNY,tNZ,tD), dt);
	}
}

void ParticleClass::CheckCol(float dt) {
	ColPlane();
	ColSphere(.0f, 1.f, 0.f, 1.f, dt);
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

	doOnce = false;
}

void ParticleClass::UpdateParticle(float dt, ParticleClass::solucionMov type) {
	if (timeAlive >= timeToLive)
		Die();
	else {
		timeAlive += dt;
		MoveParticle(dt,type);
	}
}

