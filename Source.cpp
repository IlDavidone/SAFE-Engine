#include "Includes.h"

struct Selectable {
    glm::vec3 position;
    float radius;
    int id;
};

std::vector<Selectable> selectables;
int selectedID = -1;

unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};

unsigned int planeIndices[] = {
    0, 1, 2,
    0, 2, 3
};

float texCoords[] = {
    0.0f, 0.0f,  
    1.0f, 0.0f,  
    0.5f, 1.0f  
};

float framebufferVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};

std::vector<glm::vec3> windows {
    glm::vec3(0.0f,  0.0f, 4.0f),
    glm::vec3(1.5f,  0.0f,  0.51f)
};

std::vector<const char*> faces
{
    "textures/skybox/right.jpg",
    "textures/skybox/left.jpg",
    "textures/skybox/top.jpg",
    "textures/skybox/bottom.jpg",
    "textures/skybox/front.jpg",
    "textures/skybox/back.jpg"
};

float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Renderer renderer;
float lastX = pixel::width / 2.0f;
float lastY = pixel::height / 2.0f;
bool firstMouse = true;

int main() {
    stbi_set_flip_vertically_on_load(true);

	Player player(camera, camera.Position);
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(pixel::width, pixel::height, "Left Engine A_0.0.02", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    Assimp::Importer importer;

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glViewport(0, 0, pixel::width, pixel::height);

    Shader shaderProgram("glsl/vertices.txt", "glsl/fragments.txt");
    Shader armsProgram("glsl/vertices.txt", "glsl/armsFragment.txt");
	Shader blendShader("glsl/vertices.txt", "glsl/blendingFragment.txt");
	Shader lightShader("glsl/vertices.txt", "glsl/lightFragment.txt");
	Shader screenShader("glsl/postprocessVertex.txt", "glsl/postprocessFragment.txt");
    Shader skyboxShader("glsl/skyboxVertex.txt", "glsl/skyboxFragment.txt");
    Shader asteroidShader("glsl/instancedVertex.txt", "glsl/instancedFragment.txt");

	screenShader.Activate();
    glUniform1i(glGetUniformLocation(screenShader.ID, "screenTexture"), 0);

    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    unsigned int textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 400, 200, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, pixel::width, pixel::height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    VAO framebufferVAO;
    framebufferVAO.Bind();
    VBO framebufferVBO(framebufferVertices, sizeof(framebufferVertices));
    framebufferVAO.LinkAttributes(framebufferVBO, 0, 2, GL_FLOAT, 4 * sizeof(GLfloat), (void*)0);                  // position
    framebufferVAO.LinkAttributes(framebufferVBO, 1, 2, GL_FLOAT, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat))); // texcoord
    framebufferVAO.Unbind();
    framebufferVBO.Unbind();

    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(vertices, verticesSize);
	EBO EBO1(indices, sizeof(indices));
    VAO1.LinkAttributes(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);                  // position
    VAO1.LinkAttributes(VBO1, 1, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // texcoord
    VAO1.LinkAttributes(VBO1, 2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat))); // normal
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    VAO planeVAO;
    planeVAO.Bind();
    VBO planeVBO(planeVertices, planeVerticesSize);
    EBO planeEBO(planeIndices, sizeof(planeIndices));
    planeVAO.LinkAttributes(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);                  // position
    planeVAO.LinkAttributes(VBO1, 1, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // texcoord
    planeVAO.LinkAttributes(VBO1, 2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat))); // normal
    planeVAO.Unbind();
    planeVBO.Unbind();
    planeEBO.Unbind();

    VAO vegetationVAO;
    vegetationVAO.Bind();
    VBO vegetationVBO(planeVertices, planeVerticesSize);
    EBO vegetationEBO(planeIndices, sizeof(planeIndices));
    vegetationVAO.LinkAttributes(vegetationVBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);                  // position
    vegetationVAO.LinkAttributes(vegetationVBO, 1, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // texcoord
    vegetationVAO.LinkAttributes(vegetationVBO, 2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat))); // normal
    vegetationVAO.Unbind();
    vegetationVBO.Unbind();
    vegetationEBO.Unbind();

    VAO lightVAO;
    lightVAO.Bind();
    lightVAO.LinkAttributes(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
	lightVAO.Unbind();

    shaderProgram.Activate();

    stbi_set_flip_vertically_on_load(false);
    Model myModel("models/backpack/backpack.obj");
    stbi_set_flip_vertically_on_load(true);
    Model rei("models/sketchfab.fbx");
    Model rock("models/objects/rock/rock.obj");
    Model planet("models/objects/planet/planet.obj");
    Model arms("models/armsfinal.fbx");

    unsigned int amount = 100000;
    glm::mat4* modelMatrices = new glm::mat4[amount];
    srand(glfwGetTime());
    float radius = 200.0;
    float offset = 100.0f;
    for (unsigned int i = 0; i < amount; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float)i / (float)amount * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = static_cast<float>((rand() % 360));
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        modelMatrices[i] = model;
    }

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
    for (unsigned int i = 0; i < rock.meshes.size(); i++)
    {
        unsigned int VAO = rock.meshes[i].VAO;
        glBindVertexArray(VAO);
        // set attribute pointers for matrix (4 times vec4)
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }


	Texture texture("textures/rei2.jpg", LINEAR);
    Texture diffuseTexture("textures/wall.jpg", LINEAR);
	Texture grassTexture("textures/redwindow.png", LINEAR);
    Texture specularTexture("textures/container_specular.jpg", LINEAR);
    stbi_set_flip_vertically_on_load(false);
    Texture cubemapTexture(faces);
    stbi_set_flip_vertically_on_load(true);

    VAO skyboxVAO;
    skyboxVAO.Bind();
    VBO skyboxVBO(skyboxVertices, sizeof(skyboxVertices));
    skyboxVAO.LinkAttributes(skyboxVBO, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);                  // position
    skyboxVAO.Unbind();
    skyboxVBO.Unbind();

    unsigned int diffuseMap = diffuseTexture.ID;
    unsigned int specularMap = specularTexture.ID;  

    selectables.push_back({ glm::vec3(0.0f, 0.0f, 0.0f), 2.0f, 0 }); // myModel
    selectables.push_back({ glm::vec3(3.0f, 0.0f, 0.0f), 2.0f, 1 }); // rei
    selectables.push_back({ glm::vec3(6.0f, 0.0f, 0.0f), 2.0f, 2 }); // rock

    glEnable(GL_MULTISAMPLE);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        std::map<float, glm::vec3> sorted;
        for (unsigned int i = 0; i < windows.size(); i++)
        {
            float distance = glm::length(camera.Position - windows[i]);
            sorted[distance] = windows[i];
        }

        glm::mat4 projection = glm::perspective(
            glm::radians(camera.Zoom),
            (float)pixel::width / (float)pixel::height,
            0.1f,
            500.0f
        );

        processInput(window);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (showDemoWindow)
            ImGui::ShowDemoWindow(&showDemoWindow);

        showGui(texture.ID);

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glViewport(0, 0, 400, 200);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS); 
        glDepthMask(GL_TRUE);

        shaderProgram.Activate();
        shaderProgram.setColorUniform();

        glActiveTexture(GL_TEXTURE0);
        texture.Bind();
        glUniform1i(glGetUniformLocation(shaderProgram.ID, "material.diffuse"), 0);

        glUniform1i(
            glGetUniformLocation(shaderProgram.ID, "material.useSpecular"),
            0
        );

        /*
        glActiveTexture(GL_TEXTURE0);
        diffuseTexture.Bind();
        glUniform1i(glGetUniformLocation(shaderProgram.ID, "material.diffuse"), 0);
        glActiveTexture(GL_TEXTURE1);
        specularTexture.Bind();
        glUniform1i(glGetUniformLocation(shaderProgram.ID, "material.specular"), 1);
        */

        glUniform1f(glGetUniformLocation(shaderProgram.ID, "material.shininess"), lightProps.shininess);

        //directional light
        shaderProgram.setDirectionalLightUniforms();

        shaderProgram.setPointLightUniforms();

        //spot light
        shaderProgram.setSpotlightUniforms(camera);

        glUniform3f(glGetUniformLocation(shaderProgram.ID, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);


        int projectionLoc = glGetUniformLocation(shaderProgram.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glm::mat4 view = camera.GetViewMatrix();
        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        if (selectedID == 0)
            glUniform3f(glGetUniformLocation(shaderProgram.ID, "objectColor"), 1.0f, 0.3f, 0.3f);
        else
            glUniform3f(glGetUniformLocation(shaderProgram.ID, "objectColor"), 1.0f, 1.0f, 1.0f);
        myModel.Draw(shaderProgram);

        model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        if (selectedID == 1)
            glUniform3f(glGetUniformLocation(shaderProgram.ID, "objectColor"), 1.0f, 0.3f, 0.3f);
        else
            glUniform3f(glGetUniformLocation(shaderProgram.ID, "objectColor"), 1.0f, 1.0f, 1.0f);
        rei.Draw(shaderProgram);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(6.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        if (selectedID == 2)
            glUniform3f(glGetUniformLocation(shaderProgram.ID, "objectColor"), 1.0f, 0.3f, 0.3f);
        else
            glUniform3f(glGetUniformLocation(shaderProgram.ID, "objectColor"), 1.0f, 1.0f, 1.0f);
        rock.Draw(shaderProgram);

        renderer.DrawPlayer(player, arms, armsProgram, projection, view);

        asteroidShader.Activate();
        projectionLoc = glGetUniformLocation(asteroidShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        view = camera.GetViewMatrix();
        viewLoc = glGetUniformLocation(asteroidShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        
        glUniform1i(
            glGetUniformLocation(asteroidShader.ID, "material.diffuse"),
            0
        );
        glUniform1i(
            glGetUniformLocation(asteroidShader.ID, "material.useSpecular"),
            0
        );
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id);
        for (unsigned int i = 0; i < rock.meshes.size(); i++)
        {
            glBindVertexArray(rock.meshes[i].VAO);
            glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(rock.meshes[i].indices.size()), GL_UNSIGNED_INT, 0, amount);
            glBindVertexArray(0);
        }

        shaderProgram.Activate();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseTexture.ID);
        for (int i{ 0 }; i < cubePositions->size(); i++) {
            (*cubePositions)[i].draw(shaderProgram, VAO1);
        }

		shaderProgram.Activate();
        planeVAO.Bind();
        glActiveTexture(GL_TEXTURE0);
        diffuseTexture.Bind();   // or plane texture
        glUniform1i(
            glGetUniformLocation(shaderProgram.ID, "material.diffuse"),
            0
        );
        model = glm::mat4(1.0f);              
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(4.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform1f(glGetUniformLocation(shaderProgram.ID, "uvScale"), 4.0f);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        planeVAO.Unbind();

        //myModel.Draw(shaderProgram);

		lightShader.Activate();

        lightShader.setMaterialUniforms();

        projectionLoc = glGetUniformLocation(lightShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        view = camera.GetViewMatrix();
        viewLoc = glGetUniformLocation(lightShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        modelLoc = glGetUniformLocation(lightShader.ID, "model");

        lightVAO.Bind();

        for (unsigned int i = 0; i < pointLightPositions.size(); i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

		lightVAO.Unbind();

        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
        glm::mat4 skyboxView = glm::mat4(glm::mat3(view));

        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);
        skyboxShader.Activate();
        glUniformMatrix4fv(
            glGetUniformLocation(skyboxShader.ID, "view"),
            1, GL_FALSE, glm::value_ptr(view)
        );
        glUniformMatrix4fv(
            glGetUniformLocation(skyboxShader.ID, "projection"),
            1, GL_FALSE, glm::value_ptr(projection)
        );
        skyboxVAO.Bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture.ID);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);
        skyboxVAO.Unbind();

        blendShader.Activate();
        vegetationVAO.Bind();
        glActiveTexture(GL_TEXTURE0);
        grassTexture.Bind();
        glUniform1i(glGetUniformLocation(blendShader.ID, "texture1"), 0);
        glUniform1i(
            glGetUniformLocation(blendShader.ID, "material.useSpecular"),
            0
        );

        projectionLoc = glGetUniformLocation(blendShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


        view = camera.GetViewMatrix();
        viewLoc = glGetUniformLocation(blendShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
        {
            glm::mat4 grassmodel = glm::mat4(1.0f);
            grassmodel = glm::translate(grassmodel, it->second);
            grassmodel = glm::rotate(grassmodel, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            grassmodel = glm::scale(grassmodel, glm::vec3(1.2f));
            glUniformMatrix4fv(glGetUniformLocation(blendShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(grassmodel));
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        vegetationVAO.Unbind();

        if (movingLightBulb) {
            lightPos.z -= lightPosSpeed * deltaTime;
        }
        framePerSeconds = 1000 / deltaTime;

        uint16_t height, width;
		glfwGetWindowSize(window, (int*)&width, (int*)&height);

        glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
        glViewport(0, 0, width, height);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		screenShader.Activate();
        framebufferVAO.Bind();
        glDisable(GL_DEPTH_TEST);
		glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
	lightVAO.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

	glfwTerminate(); // Clear all previously allocated GLFW resources.

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

glm::vec3 GetMouseRay(double mouseX, double mouseY,
    const glm::mat4& projection,
    const glm::mat4& view)
{
    float x = (2.0f * mouseX) / pixel::width - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / pixel::height;

    glm::vec4 rayClip(x, y, -1.0f, 1.0f);
    glm::vec4 rayEye = glm::inverse(projection) * rayClip;
    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);

    return glm::normalize(glm::vec3(glm::inverse(view) * rayEye));
}

bool RaySphere(const glm::vec3& ro,
    const glm::vec3& rd,
    const glm::vec3& center,
    float radius,
    float& t)
{
    glm::vec3 oc = ro - center;
    float b = glm::dot(oc, rd);
    float c = glm::dot(oc, oc) - radius * radius;
    float h = b * b - c;

    if (h < 0.0f) return false;

    h = sqrt(h);
    t = -b - h;
    return t > 0.0f;
}

uint8_t wireframeCounter {0};
uint8_t mouseCounter{0};

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        if (wireframeCounter == 0) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
		!wireframeCounter ? wireframeCounter++ : wireframeCounter = 0;

		Sleep(300); // Simple debouncing
    }

    static bool cursorDisabled = true;
    static bool tabWasDown = false;

    bool tabDown = glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS;

    if (tabDown && !tabWasDown)
    {
        cursorDisabled = !cursorDisabled;

        ImGuiIO& io = ImGui::GetIO();

        if (cursorDisabled)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
            firstMouse = true;
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
        }
    }

    tabWasDown = tabDown;
}

static bool mousePressedLastFrame = false;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    ImGui_ImplGlfw_CursorPosCallback(window, xposIn, yposIn);

    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse)
        return;

    bool mousePressedThisFrame = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

    // Only trigger on the edge: newly pressed this frame
    if (mousePressedThisFrame && !mousePressedLastFrame)
    {
        double mx, my;
        glfwGetCursorPos(window, &mx, &my);

        glm::mat4 projection = glm::perspective(
            glm::radians(camera.Zoom),
            (float)pixel::width / pixel::height,
            0.1f,
            500.0f
        );

        glm::vec3 rayDir = GetMouseRay(mx, my, projection, camera.GetViewMatrix());
        glm::vec3 rayOrigin = camera.Position;

        float closest = FLT_MAX;
        selectedID = -1;

        for (auto& obj : selectables)
        {
            float t;
            if (RaySphere(rayOrigin, rayDir, obj.position, obj.radius, t))
            {
                if (t < closest)
                {
                    closest = t;
                    selectedID = obj.id;
                }
            }
        }
    }

    // Update last-frame state
    mousePressedLastFrame = mousePressedThisFrame;

    // Only process camera movement when the cursor is disabled (camera mode).
    if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
        return;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    std::cout << lastX << " " << lastY << std::endl;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}