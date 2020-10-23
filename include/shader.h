#pragma once 

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <sstream>


class Shader
{
    public:
        // Constructor
        Shader(const std::string& fileName);

        // Bind shader 
        void bind(void);

        // Destructor
        virtual ~Shader();

        // Uniform setters
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setVec2(const std::string& name, const glm::vec2 &value) const;
        void setVec2(const std::string& name, float x, float y) const;
        void setVec3(const std::string& name, const glm::vec3 &value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;
        void setVec4(const std::string& name, const glm::vec4 &value) const;
        void setVec4(const std::string& name, float x, float y, float z,
            float w) const;
        void setMat2(const std::string& name, const glm::mat2 &mat) const;
        void setMat3(const std::string& name, const glm::mat3 &mat) const;
        void setMat4(const std::string& name, const glm::mat4 &mat) const;

    private:
        static std::string loadShader(const std::string& fileName);

        static GLuint compilerShader(const std::string& shaderSource,
            GLuint shaderType);

        static void checkShaderError(GLuint shader, GLuint flag,
            bool isProgram, const std::string& errorMessage);

    //Emumeations of shaders
    enum{
        VERTEX_SHADER,
        FRAGMENT_SHADER,
        NUM_SHADERS
    };

    // Shaders type
    const GLuint m_shaders_type[NUM_SHADERS] = {GL_VERTEX_SHADER,
        GL_FRAGMENT_SHADER};


    // Shaders variables 
    GLuint m_program;
    std::string m_shaders_source[NUM_SHADERS];
    GLuint m_shaders[NUM_SHADERS];

};
