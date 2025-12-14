#include "includes.h"

unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};

float texCoords[] = {
    0.0f, 0.0f,  
    1.0f, 0.0f,  
    0.5f, 1.0f  
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = pixel::width / 2.0f;
float lastY = pixel::height / 2.0f;
bool firstMouse = true;

int main() {
    stbi_set_flip_vertically_on_load(1);
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(pixel::width, pixel::height, "GL Engine (0_0_01)", NULL, NULL);
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

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glViewport(0, 0, pixel::width, pixel::height);

    Shader shaderProgram("glsl/vertices.txt", "glsl/fragments.txt");
	Shader lightShader("glsl/vertices.txt", "glsl/lightFragment.txt");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, verticesSize);

	EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttributes(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);                  // position
    VAO1.LinkAttributes(VBO1, 1, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // texcoord
    VAO1.LinkAttributes(VBO1, 2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat))); // normal


    VAO1.Unbind();
    VBO1.Unbind();

    VAO lightVAO;
	lightVAO.Bind();

	lightVAO.LinkAttributes(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);

	lightVAO.Unbind();

    shaderProgram.Activate();

	Texture texture("textures/cuber.jpg", LINEAR);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (showDemoWindow)
            ImGui::ShowDemoWindow(&showDemoWindow);

        showGui();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        shaderProgram.Activate();
        glUniform1i(glGetUniformLocation(shaderProgram.ID, "texture1"), 0);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "objectColor"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightColor"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "material.ambient"), lightProps.ambient.x, lightProps.ambient.y, lightProps.ambient.z);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "material.diffuse"), lightProps.diffuse.x, lightProps.diffuse.y, lightProps.diffuse.z);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "material.specular"), lightProps.specular.x, lightProps.specular.y, lightProps.specular.z);
        glUniform1f(glGetUniformLocation(shaderProgram.ID, "material.shininess"), lightProps.shininess);
        texture.Bind();

        //directional light
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "dirLight.specular"), 0.5f, 0.5f, 0.5f);

        //point lights
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

            glUniform3f(glGetUniformLocation(shaderProgram.ID, uniformPositionName.c_str()), pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
            glUniform3f(glGetUniformLocation(shaderProgram.ID, uniformAmbientName.c_str()), lightProps.ambient.x, lightProps.ambient.y, lightProps.ambient.z);
            glUniform3f(glGetUniformLocation(shaderProgram.ID, uniformDiffuseName.c_str()), lightProps.diffuse.x, lightProps.diffuse.y, lightProps.diffuse.z);
            glUniform3f(glGetUniformLocation(shaderProgram.ID, uniformSpecularName.c_str()), lightProps.specular.x, lightProps.specular.y, lightProps.specular.z);
            glUniform1f(glGetUniformLocation(shaderProgram.ID, uniformConstantName.c_str()), 1.0f);
            glUniform1f(glGetUniformLocation(shaderProgram.ID, uniformLinearName.c_str()), 0.09f);
            glUniform1f(glGetUniformLocation(shaderProgram.ID, uniformQuadraticName.c_str()), 0.032f);
        }

        //spot light
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "spotLight.position"), camera.Position.x, camera.Position.y, camera.Position.z);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(shaderProgram.ID, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(shaderProgram.ID, "spotLight.linear"), 0.09f);
        glUniform1f(glGetUniformLocation(shaderProgram.ID, "spotLight.quadratic"), 0.032f);
        glUniform1f(glGetUniformLocation(shaderProgram.ID, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
        glUniform1f(glGetUniformLocation(shaderProgram.ID, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

        glUniform3f(glGetUniformLocation(shaderProgram.ID, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);


        int projectionLoc = glGetUniformLocation(shaderProgram.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glm::mat4 view = camera.GetViewMatrix();
        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");

        for (int i{ 0 }; i < cubePositions->size(); i++) {
            (*cubePositions)[i].draw(shaderProgram);
        }

		lightShader.Activate();

        glUniform3f(glGetUniformLocation(lightShader.ID, "material.ambient"), 1.0f, 0.5f, 0.31f);
        glUniform3f(glGetUniformLocation(lightShader.ID, "material.diffuse"), 1.0f, 0.5f, 0.31f);
        glUniform3f(glGetUniformLocation(lightShader.ID, "material.specular"), 0.5f, 0.5f, 0.5f);
        glUniform1f(glGetUniformLocation(lightShader.ID, "material.shininess"), 32.0f);

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

        if (movingLightBulb) {
            lightPos.z -= lightPosSpeed * deltaTime;
        }
        framePerSeconds = 1000 / deltaTime;

        VAO1.Bind();

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

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    ImGui_ImplGlfw_CursorPosCallback(window, xposIn, yposIn);

    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse)
        return;

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

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}