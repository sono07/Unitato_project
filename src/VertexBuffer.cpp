#include "../include/VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &this->m_ID);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &this->m_ID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
}

void VertexBuffer::Fill(const std::vector<float>& vertices) const
{
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), (void*)vertices.data(), GL_STATIC_DRAW);
}