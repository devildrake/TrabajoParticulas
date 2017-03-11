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
	planos[0].SetPlaneStats(0.0f,100.0f,0.0f,0.0f); // Parte abajo del cubo
	planos[1].SetPlaneStats(0.0f, 0.0f, -100.0f, -500.0f);
	planos[2].SetPlaneStats(-100.0f, 0.0f, 0.0f, 500.0f);
	planos[3].SetPlaneStats(0.0f, 0.0f, 100.0f, -500.0f);
	planos[4].SetPlaneStats(100.0f, 0.0f, 0.0f, 500.0f);
	planos[5].SetPlaneStats(0.0f, -100.0f, 0.0f, 1000.0f);
}

//Función que aplica la gravedad sobre el vector velocidad Y de la partícula

void ParticleClass::Bounce(Plane plano,float dt) {

	printf("Deberia rebotar\n");

	//EN TEORIA (CREO QUE) ESTO ES EL REBOTE CON EL PLANO SEGUN LOS POWER POINTS ALOMEJOR ESTA MAL APLICADA PORQUE NO ME ACLARABA SI ERA UN PRODUCTO VECTORIAL O QUE
	//vx = vx+ax*dt - 2 * (plano.nx*vx+ax*dt)*plano.nx;
	//vy = vy+ay*dt - 2 * (plano.ny*vy + ay*dt)*plano.ny;
	//vz = vz+ax*dt - 2 * (plano.nz*vz + az*dt)*plano.nz;

	//x = x + vx*dt - 2 * (plano.nx*x + vx*dt + plano.d)*plano.nx;
	//y = y + vy*dt - 2 * (plano.ny*x + vy*dt + plano.d)*plano.ny;
	//z = z + vz*dt - 2 * (plano.nz*z + vz*dt + plano.d)*plano.nz;
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
		CheckCol(dt);
	}
	else {

	}
}

//Método que recibe un plano y el delta time y determina si ha habido colision con ese plano
void ParticleClass::ColPlane(Plane plano,float dt) 
{
	if ((((plano.nx*x + plano.ny*y + plano.nz + z) + plano.d)*((plano.nx*(x + vx*dt) + plano.ny*(y + vy*dt) + plano.nz*(z + vz*dt)) + plano.d)) <= 0)
	{
		Bounce(plano, dt);
	}
}
void ParticleClass::ColSphere(float centerX,float centerY,float centerZ, float radius, float dt) {
	if ((centerX - x + radius)*(centerX - x*vx*dt + radius) <= 0 && (centerY - y + radius)*(centerY - y*vy*dt + radius) <= 0&& (centerZ - z + radius)*(centerZ - z*vz*dt + radius) <= 0) {
		printf("ColisionConEsfera");
		//AQUI HABRIA QUE CALCULAR EL PUNTO EXACTO EN EL QUE LA PARTÍCULA HA COLISIONADO CON LA ESFERA
		//PARA PODER CALCULAR EL PLANO TANGENTE, QUE TENDRA COMO VECTOR NORMAL EL VECTOR DESDE EL CENTRO DE LA ESFERA HASTA EL PUNTO DE COLISION

	}
}

void ParticleClass::CheckCol(float dt) {
	for (int i = 0; i < 6; i++) {
		ColPlane(planos[i],dt);
	}
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

