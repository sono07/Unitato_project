#include "../include/VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &this->m_ID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &this->m_ID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(this->m_ID);
}

void VertexArray::Fill(const std::vector<float>& vertices) const
{
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), (void*)vertices.data(), GL_STATIC_DRAW);
}
