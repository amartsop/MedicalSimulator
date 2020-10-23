#include <iostream>

#include "display.h"

Display::Display(const char* title, int width, int height)
{
    // Member initialization 
    m_width = width; m_height = height;

    // Window state initialization
    m_isClosed = false;

    // GLFW initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Create window
    m_window = glfwCreateWindow(m_width, m_height, title, NULL, NULL);

    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        m_isClosed = true;
        glfwTerminate();
    }

    // Create context 
    glfwMakeContextCurrent(m_window);

    // Initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        m_isClosed = true;
    }

    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);

    /********************** Callback functions ***************************/

    // Display resize
    glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallback);
}


Display::~Display()
{
    glfwTerminate();
}

void Display::clear(float r, float g, float b, float a) const
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Display::isClosed() const
{
    return m_isClosed;
}

void Display::update(void)
{
    // Swap buffers
    glfwSwapBuffers(m_window);
    m_isClosed = (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS); 
}

/********************** Callback functions ***************************/

// Change window size callback
void Display::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
