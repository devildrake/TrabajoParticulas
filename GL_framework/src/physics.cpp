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
ParticleClass::solucionMov sol;
ParticleClass* arrayParts = new ParticleClass[LilSpheres::maxParticles];
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
	sol = ParticleClass::solucionMov::EULER;
	inc = 1;
	for (int i = 0; i < LilSpheres::maxParticles; ++i) {
		arrayParts[i].orgX = arrayParts[i].x =  partVerts[i * 3 + 0] = ((float)rand() / RAND_MAX) * 10.f - 5.f;
		arrayParts[i].orgY = arrayParts[i].y = partVerts[i * 3 + 1] = ((float)rand() / RAND_MAX) * 10.f;
		arrayParts[i].orgZ = arrayParts[i].z = partVerts[i * 3 + 2] = ((float)rand() / RAND_MAX) * 10.f - 5.f;

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
	if (spawnCounter > 0.2f)
	{
		contadorParticulas += inc;
		int a = 0;
		while (a < inc) {
			arrayParts[firstDead].isAlive = true;
			arrayParts[firstDead].vx = (float)((rand()*4.5f) + 0.5f);
			arrayParts[firstDead].vy = (float)((rand()*0.5) - 0.3f);
			arrayParts[firstDead].vz = (float)((rand()*2.0f) - 1.0f);
			firstDead += inc;
			firstDead = firstDead%LilSpheres::maxParticles;
			spawnCounter = 0;
			a++;
		}
	}
}

void UpdateAliveParticles(float dt) {
	if (firstPosAlive > firstDead) {
		for (int i = 0; i < firstDead; i++) {
			if (!arrayParts[i].isAlive) {
				firstPosAlive++;
				firstPosAlive = firstPosAlive%LilSpheres::maxParticles;
			}
			else {
				arrayParts[i].UpdateParticle(dt, sol);
			}
		}
		for (int i = firstPosAlive; i < LilSpheres::maxParticles; i++) {
			if (!arrayParts[i].isAlive) {
				firstPosAlive++;
				firstPosAlive = firstPosAlive%LilSpheres::maxParticles;
			}
			else {
				arrayParts[i].UpdateParticle(dt, sol);
			}
		}
	}
	else {
		for (int i = 0; i < firstDead; i++) {
			if (!arrayParts[i].isAlive) {
				firstPosAlive++;
				firstPosAlive = firstPosAlive%LilSpheres::maxParticles;
			}
			else {
				arrayParts[i].UpdateParticle(dt, sol);
			}
		}
	}

	if (firstPosAlive > firstDead) {

			LilSpheres::updateParticles(0,contadorParticulas-firstDead,&partVerts[firstPosAlive]);
			LilSpheres::updateParticles(0, contadorParticulas - firstPosAlive, &partVerts[firstDead]);
		

		
	}
	else {

	}




}

void PhysicsUpdate(float dt) {

	SpawnParticles(dt);
	UpdateAliveParticles(dt);
//	LilSpheres::updateParticles()
}


void PhysicsCleanup() {
	delete[] partVerts;
	//OnDestroy
	//TODO
}