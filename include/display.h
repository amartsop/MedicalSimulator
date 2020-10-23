#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


class Display
{
    public:

        Display(const char* title, int width=800, int height=600);

        void clear(float r=0.0f, float g=0.0f, float b=0.0f, float a=1.0f) const;

        bool isClosed() const;

        void update(void); 


        // Getters
        GLFWwindow* getWindowHandle(void) const { return m_window; }

        int getWindowWidth() const { return m_width; }
        int getWindowHeight() const { return m_height; }

        // Setters 
        void setDisplayStatus(const bool& close) { m_isClosed = close; }

        virtual ~Display();

    private:

        // Window handle
        GLFWwindow* m_window;

        // // Context handle
        // SDL_GLContext m_glContext;

        // Window state
        bool m_isClosed;

        // Window settings
        int m_width, m_height;

        /****************** Callback functions ********************************/
        // Change window size callback
        static void frameBufferSizeCallback(GLFWwindow* window, int width,
            int height);
};
