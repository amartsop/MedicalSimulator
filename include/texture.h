#pragma once

#include <iostream>
#include <glad/glad.h>

#include <stb_image.h>
#include <cassert>

class Texture{

    public:
        Texture(const std::string& fileName);

        void bind(unsigned int unit);
    
        GLuint getID(void) const { return m_texture; }

        virtual ~Texture();

    private:
        GLuint m_texture;
};