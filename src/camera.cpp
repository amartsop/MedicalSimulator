#include "camera.h"


Camera::Camera(GLFWwindow* window, const glm::vec3& pos, float fov,
    float aspect, float zNear, float zFar)
{
    // Window handler 
    m_window = window;

    // Initialize projection
    m_projection = glm::perspective(glm::radians(fov), aspect, zNear, zFar);

    // Initialize camera position
    m_position = pos;

    // Initialise camera front axis
    m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    // Initialize aspect and camera distances
    m_aspect = aspect; m_zNear = zNear; m_zFar = zFar; 
}


void Camera::update(double deltaTime)
{
    // Process input
    processKeyboardInput(deltaTime, m_cameraFront);

    // Camera projection 
    m_projection = glm::perspective(glm::radians(m_fov), m_aspect, m_zNear, m_zFar);

    // Camera view
    m_view = glm::lookAt(m_position, m_position + m_cameraFront, m_cameraUp);
}


void Camera::processMouseInput(float xCursorOffset, float yCursorOffset)
{
    m_yaw += xCursorOffset; m_pitch += yCursorOffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (m_pitch > 89.0f) m_pitch = 89.0f;
    if (m_pitch < -89.0f) m_pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_cameraFront = glm::normalize(front);
}


void Camera::processKeyboardInput(double deltaTime, const glm::vec3& cameraFront)
{
        
    float cameraSpeed = m_cameraSpeedScale * (float)deltaTime;

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_position += cameraSpeed * cameraFront;
    }

    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    {
        m_position -= cameraSpeed * cameraFront;
    }

    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_position -= glm::normalize(glm::cross(cameraFront, m_cameraUp)) *
            cameraSpeed;
    }

    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_position += glm::normalize(glm::cross(cameraFront, m_cameraUp)) *
            cameraSpeed;
    }
}

void Camera::processMouseWheel(float yWheel)
{
    m_fov -= yWheel;

    if (m_fov < 1.0f) m_fov = 1.0f;
    if (m_fov > 45.0f) m_fov = 45.0f;
}