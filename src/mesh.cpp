#include <mesh.h>


Mesh::Mesh(const std::string& fileName, GLenum drawType)
{
    // Draw type 
    m_drawType = drawType;

    // Create object handle
    m_object = new OBJModel(fileName);

    // Create indexed model
    m_model = m_object->ToIndexedModel();

    // Bind mesh
    bindMesh();
}


std::vector<glm::vec3> Mesh::getObjVerticesPos(void) const
{
    return m_object->getVertices();
}

std::vector<glm::vec2> Mesh::getObjTextureCoords(void) const
{
    return m_object->getTextureCoords(); 
}

std::vector<glm::vec3> Mesh::getObjNormals(void) const
{
    return m_object->getNormals();
}

unsigned int Mesh::getObjVerticesNum(void) const
{
    return m_object->getVerticesNum();
}

void Mesh::setObjVerticesPos(const std::vector<glm::vec3>& vertPos)
{
    m_object->setVertices(vertPos);

    // Create indexed model
    m_model = m_object->ToIndexedModel();

    bindMesh();
}


void Mesh::draw() const
{
    glBindVertexArray(m_vertexArrayObject);
    glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void Mesh::bindMesh(void)
{
    m_drawCount = m_model.indices.size();
    
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);
    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

   // Position coordinates 
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER,
        m_model.positions.size() * sizeof(m_model.positions[0]), 
        &m_model.positions[0], m_drawType);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER,
        m_model.positions.size() * sizeof(m_model.texCoords[0]), 
        &m_model.texCoords[0], m_drawType);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Normal coordinates
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER,
        m_model.normals.size() * sizeof(m_model.normals[0]), 
        &m_model.normals[0], m_drawType);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        m_model.indices.size() * sizeof(m_model.indices[0]), 
        &m_model.indices[0], m_drawType);

    //Debind
    glBindVertexArray(0);
}


Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);

    for (uint i = 0; i < NUM_BUFFERS; i++)
    {
        glDeleteBuffers(1, &m_vertexArrayBuffers[i]);
    }

    delete m_object; 
}