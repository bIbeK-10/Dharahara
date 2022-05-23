#include "Application.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "INIT.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Model.hpp"

//Camera construct
Camera camera(0.0f, 2.0f, 50.0f);
float lastX = 1366/2;
float lastY = 768/2;
bool firstMouse = true;

//frame
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

struct objects
{
    unsigned int vao, vbo, ebo;
};

//Application constructor
Application::Application(unsigned int width, unsigned int height, const char *title) : m_width(width), m_height(height), m_title(title)
{
    INIT::glfw();
    //create window
    m_window = glfwCreateWindow(m_width, m_height, m_title, NULL , NULL);
    INIT::AssertglfwInit(m_window);
    glfwMakeContextCurrent(m_window);

    INIT::glad();    
    
    //set callbacks
    glfwSetCursorPosCallback(m_window, mouse_callback );
    glfwSetScrollCallback(m_window, scroll_callback);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    INIT::Enable();
}

//Application destructor: Only needs to terminate glfw;
Application::~Application()
{
    INIT::terminateglfw();
}

void Application::run()
{
    // ****************************** Square Start ******************************
    float square_vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f
    };
    unsigned int square_indices[] = {
        0, 1, 2, 0, 3, 2
    };

    objects square;
    {
        glGenVertexArrays(1, &square.vao);
        glGenBuffers(1, &square.vbo);
        glGenBuffers(1, &square.ebo);
        glBindVertexArray(square.vao);
        glBindBuffer(GL_ARRAY_BUFFER, square.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, square.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    
    Shader squareShader("basicTexture.shader");
    // ****************************** Square End ******************************

    // ****************************** Splash Screen Start ******************************

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Shader splashScreen("splashScreen.shader");
    Texture splashScreenTexture("splashScreen.png");
    splashScreen.use();
    splashScreen.setInt("splashtexture", 0);
    splashScreenTexture.Bind(0);
    glBindVertexArray(square.vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(m_window);

    // ****************************** Splash Screen End ******************************

    // ****************************** Plain Start ******************************

    //co-ordinate same as square
    Texture plainTexture("grass.jpeg");
    squareShader.use();
    squareShader.setInt("texture1", 0);
    plainTexture.Bind(0);

    // ****************************** Plain End ******************************

    // ****************************** SkyBlock Start******************************

    Shader skyShader("basicTexture.shader");
    Texture skytop("skyblock/top.jpg");
    Texture skybottom("skyblock/bottom.jpg");
    Texture skyfront("skyblock/front.jpg");
    Texture skyback("skyblock/back.jpg");
    Texture skyleft("skyblock/left.jpg");
    Texture skyright("skyblock/right.jpg");

    // ****************************** SkyBlock End ******************************

    // ****************************** CUBE ******************************
    float cube_vertices[] = {
        //position           //normal             //texture

        //front face
        -0.5f, -0.5f, +0.5f, +0.0f, +0.0f, +1.0f, 0.0f, 0.0f,
        +0.5f, -0.5f, +0.5f, +0.0f, +0.0f, +1.0f, 1.0f, 0.0f,
        +0.5f, +0.5f, +0.5f, +0.0f, +0.0f, +1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, +0.5f, +0.0f, +0.0f, +1.0f, 0.0f, 0.0f,
        -0.5f, +0.5f, +0.5f, +0.0f, +0.0f, +1.0f, 0.0f, 1.0f,
        +0.5f, +0.5f, +0.5f, +0.0f, +0.0f, +1.0f, 1.0f, 1.0f,
        //right face
        +0.5f, -0.5f, +0.5f, +1.0f, +0.0f, +0.0f, 0.0f, 0.0f,
        +0.5f, -0.5f, -0.5f, +1.0f, +0.0f, +0.0f, 1.0f, 0.0f,
        +0.5f, +0.5f, -0.5f, +1.0f, +0.0f, +0.0f, 1.0f, 1.0f,
        +0.5f, -0.5f, +0.5f, +1.0f, +0.0f, +0.0f, 0.0f, 0.0f,
        +0.5f, +0.5f, +0.5f, +1.0f, +0.0f, +0.0f, 0.0f, 1.0f,
        +0.5f, +0.5f, -0.5f, +1.0f, +0.0f, +0.0f, 1.0f, 1.0f,
        //rear face
        +0.5f, -0.5f, -0.5f, +0.0f, +0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, +0.0f, +0.0f, -1.0f, 1.0f, 0.0f,
        -0.5f, +0.5f, -0.5f, +0.0f, +0.0f, -1.0f, 1.0f, 1.0f,
        +0.5f, -0.5f, -0.5f, +0.0f, +0.0f, -1.0f, 0.0f, 0.0f,
        +0.5f, +0.5f, -0.5f, +0.0f, +0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, +0.5f, -0.5f, +0.0f, +0.0f, -1.0f, 1.0f, 1.0f,
        //left face
        -0.5f, -0.5f, -0.5f, -1.0f, +0.0f, +0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, +0.5f, -1.0f, +0.0f, +0.0f, 1.0f, 0.0f,
        -0.5f, +0.5f, +0.5f, -1.0f, +0.0f, +0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, +0.0f, +0.0f, 0.0f, 0.0f,
        -0.5f, +0.5f, -0.5f, -1.0f, +0.0f, +0.0f, 0.0f, 1.0f,
        -0.5f, +0.5f, +0.5f, -1.0f, +0.0f, +0.0f, 1.0f, 1.0f,
        //bottom
        -0.5f, -0.5f, -0.5f, +0.0f, -1.0f, +0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, +0.5f, +0.0f, -1.0f, +0.0f, 1.0f, 0.0f,
        +0.5f, -0.5f, +0.5f, +0.0f, -1.0f, +0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, +0.0f, -1.0f, +0.0f, 0.0f, 0.0f,
        +0.5f, -0.5f, -0.5f, +0.0f, -1.0f, +0.0f, 0.0f, 1.0f,
        +0.5f, -0.5f, +0.5f, +0.0f, -1.0f, +0.0f, 1.0f, 1.0f,
        //top
        -0.5f, +0.5f, -0.5f, +0.0f, +1.0f, +0.0f, 0.0f, 0.0f,
        -0.5f, +0.5f, +0.5f, +0.0f, +1.0f, +0.0f, 1.0f, 0.0f,
        +0.5f, +0.5f, +0.5f, +0.0f, +1.0f, +0.0f, 1.0f, 1.0f,
        -0.5f, +0.5f, -0.5f, +0.0f, +1.0f, +0.0f, 0.0f, 0.0f,
        +0.5f, +0.5f, -0.5f, +0.0f, +1.0f, +0.0f, 0.0f, 1.0f,
        +0.5f, +0.5f, +0.5f, +0.0f, +1.0f, +0.0f, 1.0f, 1.0f};

    objects cube;
    {
        glGenVertexArrays(1, &cube.vao);
        glGenBuffers(1, &cube.vbo);
        glGenBuffers(1, &cube.ebo);
        glBindVertexArray(cube.vao);
        glBindBuffer(GL_ARRAY_BUFFER, cube.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void* )0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void* )(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void* )(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    // ****************************** CUBE END ******************************

    //cubeShader
    Shader cubeShader("plainCube.shader");
    glm::vec3 lightPos(-250.0f, 250.0f, 250.0f);

    //model
    Shader modelShader("Model.shader");

    Model dharahara("../res/objects/scene/dharahara.obj");

    //projection view matrices init
    glm::mat4 projection, view, model, transform;

    float currentFrame;
    // ****************************** LOOP ******************************
    while (!glfwWindowShouldClose(m_window))
    {
        // frame time logic
        currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processEvent();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //setup camera
        projection = glm::perspective(glm::radians(camera.Zoom), (float)m_width / (float)m_height, 0.1f, 280.0f);
        view = camera.GetViewMatrix();
        
        // ****************************** Plain ******************************
        {
            squareShader.use();
            float scaleFactor = 8;
            int width = 20;
            for (int i = -1 * width; i <= width; i++)
            {
                for (int j = -1 * width; j <= width; j++)
                {
                    model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                    model = glm::scale(model, glm::vec3(scaleFactor));
                    model = glm::translate(model, glm::vec3(i * 2, j * 2, 0.0f));
                    transform = projection * view * model;
                    squareShader.setMat4("transform", transform);
                    squareShader.setInt("texture1", 0);
                    plainTexture.Bind(0);
                    glBindVertexArray(square.vao);
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                }
            }
        }

        // ****************************** SkyBlock ******************************
        {
            skyShader.use();
            float Scale = 160.0f;
            float offset = 159.8f;
            float y_offset = 4.0f;
            //left
            {
                model = glm::translate(glm::mat4(1.0f), glm::vec3( -1 * offset + camera.Position[0] , y_offset + camera.Position[1], camera.Position[2]) );
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::scale(model, glm::vec3(Scale));
                transform = projection * view * model;
                skyShader.setInt("texture1", 0);
                skyShader.setMat4("transform", transform);
                skyleft.Bind(0);
                glBindVertexArray(square.vao);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            //front
            {
                model = glm::translate(glm::mat4(1.0f), glm::vec3( camera.Position[0] , y_offset + camera.Position[1], -1 * offset + camera.Position[2]));
                model = glm::scale(model, glm::vec3(Scale));
                transform = projection * view * model;
                skyShader.setInt("texture1", 1);
                skyShader.setMat4("transform", transform);
                skyfront.Bind(1);
                glBindVertexArray(square.vao);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            //right
            {
                model = glm::translate(glm::mat4(1.0f), glm::vec3(offset + camera.Position[0], y_offset + camera.Position[1], camera.Position[2]));
                model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::scale(model, glm::vec3(Scale));
                transform = projection * view * model;
                skyShader.setInt("texture1", 2);
                skyShader.setMat4("transform", transform);
                skyright.Bind(2);
                glBindVertexArray(square.vao);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            //back
            {
                model = glm::translate(glm::mat4(1.0f), glm::vec3( camera.Position[0], y_offset + camera.Position[1], offset + camera.Position[2]));
                model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::scale(model, glm::vec3(Scale));
                transform = projection * view * model;
                skyShader.setInt("texture1", 3);
                skyShader.setMat4("transform", transform);
                skyback.Bind(3);
                glBindVertexArray(square.vao);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            //top
            {
                model = glm::translate(glm::mat4(1.0f), glm::vec3(camera.Position[0], offset + y_offset + camera.Position[1], camera.Position[2]));
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::scale(model, glm::vec3(Scale));
                transform = projection * view * model;
                skyShader.setInt("texture1", 4);
                skyShader.setMat4("transform", transform);
                skytop.Bind(4);
                glBindVertexArray(square.vao);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            //bottom
            {
                model = glm::translate(glm::mat4(1.0f), glm::vec3(camera.Position[0], -offset + y_offset + camera.Position[1], camera.Position[2]));
                model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::scale(model, glm::vec3(Scale));
                transform = projection * view * model;
                skyShader.setInt("texture1", 5);
                skyShader.setMat4("transform", transform);
                skybottom.Bind(5);
                glBindVertexArray(square.vao);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }

        //light
        // {
        //     model = glm::mat4(1.0f);
        //     model = glm::scale(model, glm::vec3(0.2f));
        //     model = glm::translate(model, lightPos / 0.2f);
        //     transform = projection * view * model;
        //     cubeShader.use();
        //     cubeShader.setMat4("transform", transform);
        //     glBindVertexArray(cube.vao);
        //     glDrawArrays(GL_TRIANGLES, 0, 36);
        // }

        //constant model transform
        model = glm::mat4(1.0f);
        transform = projection * view * model;

        //model
        {
            modelShader.use();
            modelShader.setMat4("transform", transform);
            modelShader.setMat4("model", model);
            modelShader.setVec3("lightPos", lightPos);
            modelShader.setVec3("viewPos", camera.Position);
            modelShader.setVec3("materialP", glm::vec3(0.5, 1.0, 64.0));
            dharahara.Draw(modelShader);
        }

        glfwSwapBuffers(m_window);
        glfwPollEvents();
        // exit(0);
    }
}

void Application::processEvent()
{
    if ( glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS )
        glfwSetWindowShouldClose(m_window, GL_TRUE);
    if ( glfwGetKey(m_window, GLFW_KEY_Z) == GLFW_PRESS )
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if ( glfwGetKey(m_window, GLFW_KEY_X) == GLFW_PRESS )
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if ( glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS )
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if ( glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS )
        camera.ProcessKeyboard(LEFT, deltaTime);
    if ( glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS )
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if ( glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS )
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if ( glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS )
        camera.ProcessKeyboard(UP, deltaTime);
    if ( glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS )
        camera.ProcessKeyboard(DOWN, deltaTime);
    if ( glfwGetKey(m_window, GLFW_KEY_G) == GLFW_PRESS )
        camera.OnGround();
    if ( glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS )
        camera.Reset();
}