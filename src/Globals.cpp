#include "Globals.h"

float vertices[] = {
    // back face (normal 0,0,-1)
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

    // front face (normal 0,0,1)
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

    // left face (normal -1,0,0)
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,

    // right face (normal 1,0,0)
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,

     // bottom face (normal 0,-1,0)
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,

     // top face (normal 0,1,0)
     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
     -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f
};

unsigned int verticesSize = sizeof(vertices);

float TCR{ 4.0f }; //texCoords repeat

float planeVertices[] = {
    -0.5f, 0.0f, -0.5f,     0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
     0.5f, 0.0f, -0.5f,     1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
     0.5f, 0.0f,  0.5f,     1.0f, 1.0f,     0.0f, 1.0f, 0.0f,

     0.5f, 0.0f,  0.5f,     1.0f, 1.0f,     0.0f, 1.0f, 0.0f,
    -0.5f, 0.0f,  0.5f,     0.0f, 1.0f,     0.0f, 1.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     0.0f, 0.0f,     0.0f, 1.0f, 0.0f
};

unsigned int planeVerticesSize = sizeof(planeVertices);

void Cube::draw(Shader& shader, VAO vao) {
    vao.Bind();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    vao.Unbind();
}
void Cube::positionCube(glm::vec3 newPosition) {
    position = newPosition;
}
void Cube::rotateCube(float angle) {
    rotationAngle += angle;
}

GLFWwindow* window = nullptr;

std::unique_ptr<std::vector<Cube>> cubePositions (new std::vector<Cube>);

Textures textures;

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Textures> textures)
    : vertices(vertices), indices(indices), textures(textures)
{
    setupMesh();
}
void Mesh::setupMesh()
{
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    // ids
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

    // weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
    glBindVertexArray(0);
};
void Mesh::Draw(Shader& shader)
{
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Model::Draw(Shader& shader)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
}
void Model::loadModel(std::string const& path)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode* node, const aiScene* scene)
{
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene, nullptr));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene, const char* texturePath = nullptr)
{
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Textures> textures;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    std::vector<Textures> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Textures> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Textures> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Textures> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, textures);
}
std::vector<Textures> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<Textures> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   // if texture hasn't been loaded already, load it
            Textures texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory, false);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
        }
    }
    return textures;
};

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

std::vector<glm::vec3> pointLightPositions {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
};

int framePerSeconds{};

glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f));

glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

glm::vec3 lightPos(0.0f, 1.2f, -4.0f);

bool showDemoWindow = false;
bool movingLightBulb = false;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;

float lightPosSpeed = 0.8f;

lightProperties lightProps = {
    glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    32.0f
};