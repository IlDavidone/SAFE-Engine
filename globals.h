#ifndef GLOBALS_H
#define GLOBALS_H

#include "includes.h"

namespace pixel {
	constexpr uint16_t width{ 1536 };
	constexpr uint16_t height{ 864 };
}

class Cube {
	public:
		GLuint ID;
		float rotationAngle;
		glm::vec3 position;
		
		Cube(GLuint ID, float rotationAngle, glm::vec3 position) : ID(ID), rotationAngle(rotationAngle), position(position) {}

		void draw(Shader& shader, VAO vao);
		void scaleCube(float scaleFactor);
		void positionCube(glm::vec3 newPosition);
		void rotateCube(float angle);
};

extern GLFWwindow* window;

extern float vertices[];
extern unsigned int verticesSize;

extern float planeVertices[];
extern unsigned int planeVerticesSize;

#define MAX_BONE_INFLUENCE 4

extern struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

extern struct Textures {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Textures> textures;
	unsigned int VAO, VBO, EBO;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Textures> textures);
	void Draw(Shader& shader);
private:
	//  render data

	void setupMesh();
};

class Model
{
public:
	Model(const char* path)
	{
		loadModel(path);
	}
	void Draw(Shader& shader);
	std::vector<Mesh> meshes;
	std::vector<Textures> textures_loaded;
private:
	// model data
	std::string directory;

	void loadModel(std::string const& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene, const char* texturePath);
	std::vector<Textures> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);
};

extern unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);

extern std::unique_ptr<std::vector<Cube>> cubePositions;

extern std::vector<glm::vec3> pointLightPositions;

extern int framePerSeconds;

extern glm::mat4 model;
extern glm::mat4 view;
extern glm::mat4 projection;

extern glm::vec3 lightPos;

extern bool showDemoWindow;
extern bool movingLightBulb;

extern float deltaTime;
extern float lastFrame;
extern float currentFrame;

extern float lightPosSpeed;

extern struct lightProperties {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

extern lightProperties lightProps;

#endif