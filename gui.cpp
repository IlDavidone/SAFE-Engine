#include "gui.h"

void infoBox();
void lightParametersGui();
void createCubeGui();
void sceneViewer();

bool lightGuiOpen = true;
glm::vec3 cubePosition;

void showGui() {
	ImGui::Begin("Parameters", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		ImGui::OpenPopup("Exit");
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (lightGuiOpen) {
		lightParametersGui();
	}

	int winWidth, winHeight;
	glfwGetWindowSize(window, &winWidth, &winHeight);
	ImGui::SetWindowSize(ImVec2(winWidth / 4, winHeight / 4), ImGuiCond_Always);
	ImGui::SetWindowPos(ImVec2(winWidth - ImGui::GetWindowSize().x - 10, 5), ImGuiCond_Always);

	ImGui::SliderFloat("Light Bulb Speed", &lightPosSpeed, -2.0f, 2.0f);
	ImGui::Checkbox("Moving Light Bulb (Z-Axis)", &movingLightBulb);
	ImGui::SliderFloat3("Light Bulb Position", (float*)&lightPos, -8.0f, 8.0f);

	ImGui::Separator();
	if (ImGui::CollapsingHeader("Light Properties")) {
		ImGui::Text("Light Properties");
		ImGui::Checkbox("Light Parameters Window", &lightGuiOpen);

	}
	ImGui::Separator();

	ImGui::Checkbox("Demo Window", &showDemoWindow);
	ImGui::Text("ImGui Window size: %.1f", ImGui::GetWindowSize().x);
	infoBox();
	createCubeGui();
	sceneViewer();

	if (ImGui::BeginPopupModal("Exit", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar))
	{
		ImVec2 textSize = ImGui::CalcTextSize("Are you sure you want to exit?");
		float windowWidth = ImGui::GetWindowSize().x;
		ImGui::SetCursorPosX((windowWidth - textSize.x) * 0.5f);
		ImGui::Text("Are you sure you want to exit?");

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

		if (ImGui::Button("OK", ImVec2(120, 0))) {
			ImGui::CloseCurrentPopup(); 
			glfwSetWindowShouldClose(window, true);
		}
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) {
			ImGui::CloseCurrentPopup(); 
		}

		ImGui::EndPopup();
	}
	ImGui::End();
}

void infoBox() {
	ImGui::Begin("Info", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	ImVec2 textSize = ImGui::CalcTextSize("Application average 000.00000 ms/frame (0000.0 FPS) ");
	ImGui::SetWindowSize(ImVec2(textSize.x, textSize.y), ImGuiCond_Always);
	int winWidth, winHeight;
	glfwGetWindowSize(window, &winWidth, &winHeight);
	ImGui::SetWindowPos(ImVec2(10, winHeight - ImGui::GetWindowHeight() - 10));
	ImGui::Text("Application average %.5f ms/frame (%.1f FPS)", 1000.0f / framePerSeconds, 1000.0f / deltaTime);
	ImGui::End();
}

ImGuiWindowFlags windowFlagsLightParams = 0;

void lightParametersGui() {
	ImGui::Begin("Light Properties", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar | windowFlagsLightParams);

	static bool docked = false;
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Options", true))
		{
			if (ImGui::MenuItem("Dock", nullptr, &docked)){
				windowFlagsLightParams |= ImGuiWindowFlags_NoMove;
				windowFlagsLightParams |= ImGuiWindowFlags_NoResize;
				if (!docked) {
					windowFlagsLightParams &= ~ImGuiWindowFlags_NoMove;
					windowFlagsLightParams &= ~ImGuiWindowFlags_NoResize;
				}
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	int winWidth, winHeight;
	glfwGetWindowSize(window, &winWidth, &winHeight);
	ImGui::SetWindowSize(ImVec2(winWidth / 3, winHeight / 3), ImGuiCond_Once);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	if (ImGui::CollapsingHeader("Light Position", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::SliderFloat("Light Bulb Speed", &lightPosSpeed, -2.0f, 2.0f);
		ImGui::Checkbox("Moving Light Bulb (Z-Axis)", &movingLightBulb);
		ImGui::SliderFloat3("Light Bulb Position", (float*)&lightPos, -8.0f, 8.0f);
	}

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);

	if (ImGui::CollapsingHeader("Light Color and Intensity", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::ColorEdit3(" Ambient Color", (float*)&lightProps.ambient);
		ImGui::ColorEdit3(" Diffuse Color", (float*)&lightProps.diffuse);
		ImGui::ColorEdit3(" Specular Color", (float*)&lightProps.specular);
		ImGui::SliderFloat(" Material Shininess", (float*)&lightProps.shininess, 0.0f, 256.0f);
	}

	ImGui::End();
}

void createCubeGui() {
	ImGui::Begin("Create Cube", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
	int winWidth, winHeight;
	glfwGetWindowSize(window, &winWidth, &winHeight);
	ImGui::SetWindowSize(ImVec2(winWidth / 4, winHeight / 4), ImGuiCond_Always);
	ImGui::SetWindowPos(ImVec2(10, 5), ImGuiCond_Always);
	ImGui::SliderFloat3("Cube Position", (float*)&cubePosition, -20.0f, 20.0f);
	if (ImGui::Button("Create Cube")) {
		Cube cube(cubePositions->size(), 0.0f, cubePosition);
		cubePositions->push_back(cube);
	}
	ImGui::Text("Total Cubes: %d", (int)cubePositions->size());
	for (int i{ 0 }; i < cubePositions->size(); i++) {
		ImGui::Text("Cube %i: %f, %f, %f", i, (*cubePositions)[i].position.x, (*cubePositions)[i].position.y, (*cubePositions)[i].position.z);
		ImGui::SameLine();
		char label[32];
		snprintf(label, sizeof(label), "Delete##%d", i);
		if (ImGui::Button(label)) {
			cubePositions->erase(cubePositions->begin() + i);
			i--;
		}
	}
	ImGui::End();
}

void sceneViewer() {
	ImGui::Begin("Scene Viewer", NULL, ImGuiWindowFlags_NoCollapse);
	int winWidth, winHeight;
	glfwGetWindowSize(window, &winWidth, &winHeight);
	ImGui::SetWindowSize(ImVec2(winWidth / 4, winHeight / 1.5), ImGuiCond_Once);
	ImGui::SetWindowPos(ImVec2((winWidth / 2) - (ImGui::GetWindowWidth() / 2), 5), ImGuiCond_Once);
	ImGui::Text("Scene Viewer");
	ImGui::End();
}

void exitProgramPopup() {
	ImGui::OpenPopup("Exit");

	if (ImGui::BeginPopupModal("Exit", NULL))
	{
		ImGui::Text("Are you sure you want to exit?\nThis operation cannot be undone!");
		ImGui::Separator();

		//static int unused_i = 0;
		//ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

		static bool dont_ask_me_next_time = false;
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
		ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
		ImGui::PopStyleVar();

		if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		ImGui::EndPopup();
	}
}