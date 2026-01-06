#pragma once

#include "includes.h"

class Shader
{
public:
	GLuint ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void setColorUniform();
	void setDirectionalLightUniforms();
	void setPointLightUniforms();
	void setSpotlightUniforms(Camera& camera);
	void setMaterialUniforms();
	void Activate();
	void Delete();
};

std::string getFileContents(const char* filePath);

