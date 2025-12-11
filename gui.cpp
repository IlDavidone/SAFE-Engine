#include "gui.h"

void showGui() {
	ImGui::Begin("Parameters");

	// Fix: Get window size using glfwGetWindowSize (which returns via pointers)
	int winWidth, winHeight;
	glfwGetWindowSize(window, &winWidth, &winHeight);
	ImGui::SetWindowSize(ImVec2(winWidth / 3, winHeight / 4), ImGuiCond_Always);
	ImGui::SetWindowPos(ImVec2(winWidth - ImGui::GetWindowSize().x - 10, 5), ImGuiCond_Always);

	ImGui::SliderFloat("Light Bulb Speed", &lightPosSpeed, -2.0f, 2.0f);
	ImGui::Checkbox("Moving Light Bulb (Z-Axis)", &movingLightBulb);
	ImGui::SliderFloat3("Light Bulb Position", (float*)&lightPos, -8.0f, 8.0f);
	ImGui::Checkbox("Demo Window", &showDemoWindow);
	ImGui::Text("ImGui Window size: %.1f", ImGui::GetWindowSize().x);
	ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 25);
	ImGui::Separator();
	ImGui::Text("Application average %.5f ms/frame (%.1f FPS)", 1000.0f / framePerSeconds, 1000.0f / deltaTime);
	ImGui::End();
}