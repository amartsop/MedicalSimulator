#include <callback_handler.h>

CallbackHandler::CallbackHandler(GLFWwindow* window)
{
    // Mouse callback function
    glfwSetWindowUserPointer(window, reinterpret_cast<void *>(this));
}


void CallbackHandler::setCursorCoords(float cursorX, float cursorY)
{
    m_lastX = cursorX; m_lastY = cursorY;
}


void CallbackHandler::mouseCursorCallback(double xpos, double ypos)
{
    if (m_firstMouse)
    {
        m_lastX = xpos; m_lastY = ypos;
        m_firstMouse = false;
    }

    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos; 
    m_lastX = xpos; m_lastY = ypos;

    xoffset *= m_sensitivity; yoffset *= m_sensitivity;

    m_camera->processMouseInput(xoffset, yoffset);

}


void CallbackHandler::mouseWheelCallback(float wheelX, float wheelY)
{
   m_camera->processMouseWheel(wheelY);
}