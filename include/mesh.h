#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <GLFW/glfw3.h>

#include <obj_loader.h>


class Mesh
{        
    public:

        Mesh(const std::string& fileName, GLenum drawType=GL_STATIC_DRAW);

        // Getters 
        std::vector<glm::vec3> getObjVerticesPos(void) const;
        std::vector<glm::vec2> getObjTextureCoords(void) const;
        std::vector<glm::vec3> getObjNormals(void) const;
        unsigned int getObjVerticesNum(void) const;

        // Update mesh
        void setObjVerticesPos(const std::vector<glm::vec3>& vertPos);
        
        // Draw mesh
        void draw() const;

        virtual ~Mesh();

    private:

        void bindMesh(void);

        enum
        {
            POSITION_VB,
            TEXCOORD_VB,
            NORMAL_VB,
            INDEX_VB,
            NUM_BUFFERS
        };

        GLuint m_vertexArrayObject;
        GLuint m_vertexArrayBuffers[NUM_BUFFERS];

        unsigned int m_drawCount;
        GLenum m_drawType;
        
        // Vertices position
        std::vector<glm::vec3> m_verticesPos;
        
        // Object handle (Maybe gonna need a copy constructor)
        OBJModel *m_object; 

        // Indexed model 
        IndexedModel m_model;
};


