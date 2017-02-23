#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

namespace LilSpheres {
	extern const int maxParticles;
	extern void setupParticles(int numTotalParticles, float radius = 0.05f);
	extern void cleanupParticles();
	extern void updateParticles(int startIdx, int count, float* array_data);
	extern void drawParticles(int startIdx, int count);
}

bool show_test_window = true;
int firstPosAlive;
int lastPosAlive;
bool flag = false;
float contador;
int inc;

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
	inc = 1;
	for (int i = 0; i < LilSpheres::maxParticles; ++i) {
		partVerts[i * 3 + 0] = ((float)rand() / RAND_MAX) * 10.f - 5.f;
		partVerts[i * 3 + 1] = ((float)rand() / RAND_MAX) * 10.f;
		partVerts[i * 3 + 2] = ((float)rand() / RAND_MAX) * 10.f - 5.f;
	}
	firstPosAlive = lastPosAlive = 0;
	//TODO
}


void PhysicsUpdate(float dt) {
	contador += dt;

	//HAY QUE MANEJAR LA EXCEPCION DEL RESETEO
	
	if (contador > 5) {
		//Flag es false hasta que el contador llega a 5 
		flag = true;
	}

	if (contador > 20) {
		//El contador reinicia al llegar a 20
		contador = 0;

	}

	if (flag) {
		//Generar y petar particulas
		firstPosAlive += inc;
		lastPosAlive += inc;
		firstPosAlive = firstPosAlive%LilSpheres::maxParticles;
		lastPosAlive = lastPosAlive%LilSpheres::maxParticles;

			if (firstPosAlive > lastPosAlive) {
				LilSpheres::updateParticles(firstPosAlive, LilSpheres::maxParticles-firstPosAlive, partVerts+firstPosAlive);
				LilSpheres::updateParticles(0, lastPosAlive, partVerts);
			}
			else {
				LilSpheres::updateParticles(firstPosAlive, lastPosAlive, partVerts+firstPosAlive);

			}
	
	}
	else {
	//Solo Generar particulas
		
		lastPosAlive += inc;
		lastPosAlive = lastPosAlive%LilSpheres::maxParticles;
		LilSpheres::updateParticles(firstPosAlive, lastPosAlive, partVerts+firstPosAlive);

		

	}


	std::cout << contador << "\n";
	//TODO

	std::cout << "First Pos Alive = " << firstPosAlive << "\n";

	std::cout << "Last Pos Alive = " << lastPosAlive << "\n";

}
void PhysicsCleanup() {
	delete[] partVerts;
	//OnDestroy
	//TODO
}