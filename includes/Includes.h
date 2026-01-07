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
#include <thread>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Camera.h"
#include "Shader.h"
#include "Buffers.h"
#include "Texture.h"
#include "stb/stb_image.h"
#include "Globals.h"
#include "gui.h"

#endif