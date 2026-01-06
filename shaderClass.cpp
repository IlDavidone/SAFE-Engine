#include "includes.h"

std::string getFileContents(const char* filePath) { //temporary function to read shader files
	std::string contents;
	std::ifstream file(filePath);

	if (!file.is_open()) {
		std::cerr << "Could not open the file: " << filePath << std::endl;
		return "";
	}

	std::string fileBuffer;

	while (std::getline(file, fileBuffer))
		contents += fileBuffer + "\n";

	file.close();
	return contents;
}

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath) {
	std::string vertexCode{ getFileContents(vertexFilePath) };
	std::string fragmentCode{ getFileContents(fragmentFilePath) };

	const char* vertexSource{ vertexCode.c_str() };
	const char* fragmentSource{ fragmentCode.c_str() };

	GLuint vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	ID = { glCreateProgram() };
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::setColorUniform() {
	glUniform3f(glGetUniformLocation(ID, "objectColor"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(ID, "lightColor"), 1.0f, 1.0f, 1.0f);
}

void Shader::setDirectionalLightUniforms() {
	glUniform3f(glGetUniformLocation(ID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(ID, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(glGetUniformLocation(ID, "dirLight.diffuse"), 0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(ID, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
}

void Shader::setPointLightUniforms() {
#define MAX_POINT_LIGHTS 1024

	int lightCount = std::min((int)pointLightPositions.size(), MAX_POINT_LIGHTS);
	glUniform1i(glGetUniformLocation(ID, "nrPointLights"), lightCount);

	for (int i{ 0 }; i < pointLightPositions.size(); i++) {
		std::string uniformPositionName =
			"pointLights[" + std::to_string(i) + "].position";
		std::string uniformAmbientName =
			"pointLights[" + std::to_string(i) + "].ambient";
		std::string uniformDiffuseName =
			"pointLights[" + std::to_string(i) + "].diffuse";
		std::string uniformSpecularName =
			"pointLights[" + std::to_string(i) + "].specular";
		std::string uniformConstantName =
			"pointLights[" + std::to_string(i) + "].constant";
		std::string uniformLinearName =
			"pointLights[" + std::to_string(i) + "].linear";
		std::string uniformQuadraticName =
			"pointLights[" + std::to_string(i) + "].quadratic";

		glUniform3f(glGetUniformLocation(ID, uniformPositionName.c_str()), pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
		glUniform3f(glGetUniformLocation(ID, uniformAmbientName.c_str()), lightProps.ambient.x, lightProps.ambient.y, lightProps.ambient.z);
		glUniform3f(glGetUniformLocation(ID, uniformDiffuseName.c_str()), lightProps.diffuse.x, lightProps.diffuse.y, lightProps.diffuse.z);
		glUniform3f(glGetUniformLocation(ID, uniformSpecularName.c_str()), lightProps.specular.x, lightProps.specular.y, lightProps.specular.z);
		glUniform1f(glGetUniformLocation(ID, uniformConstantName.c_str()), 1.0f);
		glUniform1f(glGetUniformLocation(ID, uniformLinearName.c_str()), 0.09f);
		glUniform1f(glGetUniformLocation(ID, uniformQuadraticName.c_str()), 0.032f);
	}
}

void Shader::setSpotlightUniforms(Camera& camera) {
	glUniform3f(glGetUniformLocation(ID, "spotLight.position"), camera.Position.x, camera.Position.y, camera.Position.z);
	glUniform3f(glGetUniformLocation(ID, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
	glUniform3f(glGetUniformLocation(ID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(ID, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(ID, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(ID, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(ID, "spotLight.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(ID, "spotLight.quadratic"), 0.032f);
	glUniform1f(glGetUniformLocation(ID, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
	glUniform1f(glGetUniformLocation(ID, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));
}

void Shader::setMaterialUniforms() {
	glUniform3f(glGetUniformLocation(ID, "material.ambient"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(ID, "material.diffuse"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(ID, "material.specular"), 0.5f, 0.5f, 0.5f);
	glUniform1f(glGetUniformLocation(ID, "material.shininess"), 32.0f);
}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}

