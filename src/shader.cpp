#include "shader.h"


Shader::Shader(const std::string& fileName)
{
    // Create program
    m_program = glCreateProgram();

    // Load shaders
    m_shaders_source[VERTEX_SHADER] = loadShader(fileName + ".vs");
    m_shaders_source[FRAGMENT_SHADER] = loadShader(fileName + ".fs");

    // Compile and attach shaders
    for(unsigned int i = 0; i < NUM_SHADERS; i++){
        // Compile shader 
        m_shaders[i] = compilerShader(m_shaders_source[i], m_shaders_type[i]);

        // Attach shader
        glAttachShader(m_program, m_shaders[i]);
    }

    // Link shader to program and check for errors
    glLinkProgram(m_program);
    checkShaderError(m_program, GL_LINK_STATUS, true,
        "Error: Program linking failed");

    glValidateProgram(m_program);
    checkShaderError(m_program, GL_VALIDATE_STATUS, true,
        "Error: Program is invalid ");
}

void Shader::bind(void)
{
    glUseProgram(m_program); 
}


// Compile shader
GLuint Shader::compilerShader(const std::string& shaderSource, GLuint shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    if (shader == 0){
        std::cerr << "Error: Shader creation failed!" << std::endl;
    }

    // Source code 
    const GLchar* shaderSourceStrings[1];
    shaderSourceStrings[0] = shaderSource.c_str();

    // Source code length
    GLint shaderSourceStringLengths[1];
    shaderSourceStringLengths[0] = shaderSource.length();

    // Compile shader
    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    checkShaderError(shader, GL_COMPILE_STATUS, false,
        "Error: Shader compilation failed: ");

    return shader;
}

// Load shader source code
std::string Shader::loadShader(const std::string& fileName)
{
    // Filename 
    std::ifstream file;

    // Open shader file
    file.open((fileName).c_str());

    // Output string
    std::string output, line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}


// Check shader compile errors
void Shader::checkShaderError(GLuint shader, GLuint flag,
    bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
} 

//------------------------Uniform functions -------------------------//

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(m_program, name.c_str()), value); 
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]); 
}

void Shader::setVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(m_program, name.c_str()), x, y); 
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]); 
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(m_program, name.c_str()), x, y, z); 
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]); 
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{ 
    glUniform4f(glGetUniformLocation(m_program, name.c_str()), x, y, z, w); 
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// Destructor
Shader::~Shader()
{
    for(unsigned int i = 0; i < NUM_SHADERS; i++){
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }
    glDeleteProgram(m_program);
}