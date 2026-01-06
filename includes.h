#ifndef INCLUDES_H
#define INCLUDES_H

#include <glad/glad.h>
#include <Windows.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <cstdint>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "shaderClass.h"
#include "buffers.h"
#include "texture.h"
#include "camera.h"
#include "stb_image.h"
#include "globals.h"
#include "gui.h"

#endif