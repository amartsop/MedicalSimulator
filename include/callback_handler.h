#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <camera.h>

class CallbackHandler
{
    public:
        CallbackHandler(GLFWwindow* window);

        // Cursor position callback function 
        void mouseCursorCallback(double xpos, double ypos);
        
        // Mouse scroll callback function 
        void mouseWheelCallback(float wheelX, float wheelY);

        // Set cursor initial coordinates 
        void setCursorCoords(float cursorX, float cursorY);

        // Set camera inputs 
        void setCamera(Camera *camera) { m_camera = camera; }

    private:
        // Camera handle 
        Camera* m_camera;

        // Mouse movement variables
        float m_sensitivity = 0.1f;
        bool m_firstMouse = true;
        float m_lastX, m_lastY;
};

