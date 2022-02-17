#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Application
{
public:
    Application(unsigned int width, unsigned int height, const char *name);
    ~Application();

    void run();
    void processEvent();

private:
    GLFWwindow *m_window;
    unsigned int m_width, m_height;
    const char *m_title;
};

#endif 