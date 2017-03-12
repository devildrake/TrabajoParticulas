#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "ParticleClass.h"

namespace LilSpheres {
	extern const int maxParticles;
	extern void setupParticles(int numTotalParticles, float radius = 0.05f);
	extern void cleanupParticles();
	extern void updateParticles(int startIdx, int count, float* array_data);
	extern void drawParticles(int startIdx, int count);
}

bool show_test_window = true;
int firstPosAlive;
int firstDead;
int inc;
int contadorParticulas;

ParticleClass::tipoMov tipoMov;
ParticleClass::tipoMov prevTipoMov;
ParticleClass::solucionMov sol;
ParticleClass* arrayParts = new ParticleClass[LilSpheres::maxParticles];
int maxParticles = LilSpheres::maxParticles;
float *partVerts = new float[LilSpheres::maxParticles * 3];

void GUI() {
	{	//FrameRate
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		//TODO
	}

	// ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if(show_test_window) {
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}
}

void PhysicsInit() {
	//Start
	contadorParticulas = 0;
	tipoMov = ParticleClass::tipoMov::CASCADA;
	prevTipoMov = ParticleClass::tipoMov::CASCADA;

	sol = ParticleClass::solucionMov::EULER;
	inc = 50;
	for (int i = 0; i < LilSpheres::maxParticles; ++i) {
		for (int i = 0; i < LilSpheres::maxParticles; ++i) {
			arrayParts[i].orgX = arrayParts[i].x = partVerts[i * 3 + 0] = ((float)rand() / RAND_MAX) + 4;
			arrayParts[i].orgY = arrayParts[i].y = partVerts[i * 3 + 1] = ((float)rand() / RAND_MAX) + 9.0f;
			arrayParts[i].orgZ = arrayParts[i].z = partVerts[i * 3 + 2] = ((float)rand() / RAND_MAX);

		}

		//arrayParts[i].orgX = arrayParts[i].x = 0;
		//arrayParts[i].orgY = arrayParts[i].y = 5;
		//arrayParts[i].orgZ = arrayParts[i].z = 0;

	}
	firstPosAlive = firstDead = 0;
	//TODO
}

float spawnCounter=0;

void SpawnParticles(float dt) {
	spawnCounter += dt;
	if (spawnCounter > 0.1f)
	{
		
		contadorParticulas += inc;
		int a = 0;
		while (a < inc) {
			arrayParts[firstDead].x = arrayParts[firstDead].orgX;
			arrayParts[firstDead].y = arrayParts[firstDead].orgY;
			arrayParts[firstDead].z = arrayParts[firstDead].orgZ;

			arrayParts[firstDead].isAlive = true;
			if (tipoMov == ParticleClass::tipoMov::CASCADA) {
				arrayParts[firstDead].vx = ((float)rand() / RAND_MAX) -4.0f;
				arrayParts[firstDead].vy = ((float)rand() / RAND_MAX) - 1.0f;
				arrayParts[firstDead].vz = ((float)rand() / RAND_MAX)*4-2;
			}
			else {
				arrayParts[firstDead].vx = ((float)rand() / RAND_MAX)* 8.0f  -4.0f;
				arrayParts[firstDead].vy = ((float)rand() / RAND_MAX)+5;
				arrayParts[firstDead].vz = ((float)rand() / RAND_MAX)*8.0f -4.0f ;
				std::cout << arrayParts[firstDead].vx << std::endl;
			}
			firstDead ++;
			firstDead = firstDead%LilSpheres::maxParticles;

			a++;
		}
	//	std::cout << "Particula "<<firstDead-1<<"\n Viva--->" << arrayParts[firstDead-1].isAlive << "\nPosicion---> (" << arrayParts[firstDead - 1].x << "," << arrayParts[firstDead - 1].y << "," << arrayParts[firstDead - 1].z << ")\n";
	//	std::cout << "FirstPosAlive" << firstPosAlive << "\n";
	//	std::cout << "FirstDead" << firstDead << "\n";
		spawnCounter = 0;
	}
}

void UpdateAliveParticles(float dt) {
	//std::cout << firstDead-firstPosAlive << "\n";
	if (firstPosAlive > firstDead) {
		for (int i = 0; i < firstDead; i++) {
			if (arrayParts[i].isAlive) {
				arrayParts[i].UpdateParticle(dt, sol);
				partVerts[i*3] = arrayParts[i].x;
				partVerts[i*3+1] = arrayParts[i].y;
				partVerts[i*3+2] = arrayParts[i].z;
			}
		}
		for (int i = firstPosAlive; i < LilSpheres::maxParticles; i++) {
			if (arrayParts[i].isAlive) {
				arrayParts[i].UpdateParticle(dt, sol);
				partVerts[i * 3] = arrayParts[i].x;
				partVerts[i * 3 + 1] = arrayParts[i].y;
				partVerts[i * 3 + 2] = arrayParts[i].z;
			}
		}
	}
	else {
		for (int i = firstPosAlive; i < firstDead; i++) {
			if (arrayParts[i].isAlive) {
				arrayParts[i].UpdateParticle(dt, sol);
				partVerts[i * 3] = arrayParts[i].x;
				partVerts[i * 3 + 1] = arrayParts[i].y;
				partVerts[i * 3 + 2] = arrayParts[i].z;
			}
		}
	}

	if (firstPosAlive > firstDead) {
	//	std::cout << "Excepcion\n";
			LilSpheres::updateParticles(0,firstDead*3,&partVerts[0]);
			LilSpheres::updateParticles(firstPosAlive, (LilSpheres::maxParticles-firstPosAlive)*3, &partVerts[firstPosAlive]);
	}
	else {

		LilSpheres::updateParticles(firstPosAlive, contadorParticulas*3, &partVerts[firstPosAlive]);
	}

}

void ChangeOrg(ParticleClass::tipoMov a) {
	if (a == ParticleClass::CASCADA) {
		for (int i = 0; i < LilSpheres::maxParticles; ++i) {
			arrayParts[i].orgX = arrayParts[i].x = partVerts[i * 3 + 0] = ((float)rand() / RAND_MAX) + 4;
			arrayParts[i].orgY = arrayParts[i].y = partVerts[i * 3 + 1] = ((float)rand() / RAND_MAX) + 9.0f;
			arrayParts[i].orgZ = arrayParts[i].z = partVerts[i * 3 + 2] = ((float)rand() / RAND_MAX) ;

		}
	}
	else {
		for (int i = 0; i < LilSpheres::maxParticles; ++i) {
			arrayParts[i].orgX = arrayParts[i].x = partVerts[i * 3 + 0] = ((float)rand() / RAND_MAX) * 3.0f - 1.5f;
			arrayParts[i].orgY = arrayParts[i].y = partVerts[i * 3 + 1] = ((float)rand() / RAND_MAX) * 2.0f + 4.0f;
			arrayParts[i].orgZ = arrayParts[i].z = partVerts[i * 3 + 2] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;

		}
	}
}

void PhysicsUpdate(float dt) {
	if (prevTipoMov != tipoMov) {
		ChangeOrg(tipoMov);
		prevTipoMov = tipoMov;
	}
	SpawnParticles(dt);
	UpdateAliveParticles(dt);
//	LilSpheres::updateParticles()
}


void PhysicsCleanup() {
	delete[] partVerts;
	//OnDestroy
	//TODO
}