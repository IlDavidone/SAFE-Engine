#include "Gui.h"

void infoBox();
void lightParametersGui();
void createCubeGui();
void sceneViewer();
void cubePropertyGui(int selectedID);

bool lightGuiOpen = true;
glm::vec3 cubePosition;

void showGui(unsigned int textureID) {
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

	ImGui::Text("%i", (const char*)&textureID);

	ImGui::SliderFloat("Light Bulb Speed", &lightPosSpeed, -2.0f, 2.0f);
	ImGui::Checkbox("Moving Light Bulb (Z-Axis)", &movingLightBulb);
	ImGui::SliderFloat3("Light Bulb Position", (float*)&lightPos, -8.0f, 8.0f);

	ImGui::Separator();
	if (ImGui::CollapsingHeader("Light Properties")) {
		ImGui::Text("Light Properties");
		ImGui::Checkbox("Light Parameters Window", &lightGuiOpen);

	}
	ImGui::Separator();

	//ImGui::Checkbox("Demo Window", &showDemoWindow);
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

	ImVec2 textSize = ImGui::CalcTextSize("Application average 000.00000 ms/frame (0000000.0 FPS) ");
	ImGui::SetWindowSize(ImVec2(textSize.x, textSize.y), ImGuiCond_Always);
	int winWidth, winHeight;
	glfwGetWindowSize(window, &winWidth, &winHeight);
	ImGui::SetWindowPos(ImVec2(10, winHeight - ImGui::GetWindowHeight() - 10));
	ImGui::Text("Application average %.5f ms/frame (%.1f FPS)", 1000.0f * deltaTime, 1.0f / deltaTime);
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
		ImGui::SliderFloat3("Light Bulb Position", (float*)&lightPos, -16.0f, 16.0f);
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
	ImGui::SameLine();
	if (ImGui::Button("Delete All")) {
		for (int i{ 0 }; i < cubePositions->size(); i++) {
			cubePositions->clear();
		}
	}
	ImGui::Text("Total Cubes: %d", (int)cubePositions->size());
	ImGui::Text("Position's Heap Memory Address: 0x%x", &cubePositions);

	ImGui::Separator();

	for (int i{ 0 }; i < cubePositions->size(); i++) {
		ImGui::Text("Cube %i: %f, %f, %f", i, (*cubePositions)[i].position.x, (*cubePositions)[i].position.y, (*cubePositions)[i].position.z);
		ImGui::SameLine();
		char label[32];
		snprintf(label, sizeof(label), "Delete##%d", i);
		if (ImGui::SmallButton(label)) {
			cubePositions->erase(cubePositions->begin() + i);
			i--;
		}
	}
	ImGui::End();
}

static bool showPropertiesWindow = true;

void sceneViewer() {
	ImGui::Begin("Scene Viewer", NULL, ImGuiWindowFlags_NoCollapse);
	int winWidth, winHeight;
	glfwGetWindowSize(window, &winWidth, &winHeight);
	ImGui::SetWindowSize(ImVec2(winWidth / 4, winHeight / 1.5), ImGuiCond_Once);

	if (ImGui::TreeNode("Scene"))
	{
		if (ImGui::TreeNode("Cameras")) {
			ImGui::TextUnformatted("Main Camera");

			ImGui::SameLine();

			if (ImGui::SmallButton("Properties")) {
				
			};

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Lights")) {
			ImGui::TextUnformatted("Main Light");

			ImGui::SameLine();

			if (ImGui::SmallButton("Properties")) {
				lightGuiOpen = !lightGuiOpen;
			};

			ImGui::TreePop();
		}

		static int selectedCube = -1;

		if (ImGui::TreeNode("Cubes"))
		{
			for (int i = 0; i < cubePositions->size(); i++)
			{
				ImGui::PushID(i);
				ImGui::Text("Cube %d", i);
				ImGui::SameLine();
				if (ImGui::SmallButton("Properties")) {
					selectedCube = i;
					showPropertiesWindow = true;
				}
				ImGui::SameLine();
				if (ImGui::SmallButton("Delete")) {
					cubePositions->erase(cubePositions->begin() + i);
					i--;
				}
				ImGui::PopID();
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();

		if (selectedCube >= 0 && selectedCube < cubePositions->size()) {
			cubePropertyGui(selectedCube);
		}
	}
	ImGui::End();
}

void cubePropertyGui(int selectedID) {
	if (showPropertiesWindow)
	{
		char labelCube[32];
		snprintf(labelCube, sizeof(labelCube), "Cube %d", (*cubePositions)[selectedID].ID);
		ImGui::Begin(labelCube, &showPropertiesWindow);
		int winWidth, winHeight;
		glfwGetWindowSize(window, &winWidth, &winHeight);
		ImGui::SetWindowSize(ImVec2(winWidth / 4, winHeight / 4), ImGuiCond_Once);
		ImGui::SetWindowPos(ImVec2((winWidth / 2) - (ImGui::GetWindowWidth() / 2), 5), ImGuiCond_Once);

		ImGui::SliderFloat3(" Cube Position", (float*)&(*cubePositions)[selectedID].position, -1000.0f, 1000.0f);

		ImGui::End();
	}
}