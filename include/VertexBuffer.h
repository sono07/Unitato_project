#pragma once

#include <GL/glew.h>

#include <vector>

class VertexBuffer
{
private:
	GLuint m_ID = 0;
public:

	/// <summary>
	/// Instantiates a VertexBuffer object by generating an ID
	/// </summary>
	VertexBuffer();

	/// <summary>
	/// Destroys a VertexBuffer object by freeing its container and deleting its ID
	/// </summary>
	~VertexBuffer();

	/// <summary>
	/// Calls OpenGL specifing functions to bind vertex buffer to the drawing API, all draw calls following Bind will use the vertex array in its calls
	/// </summary>
	void Bind() const;

	/// <summary>
	/// Copies sorted mesh data to the allocated array buffer on the GPU
	/// </summary>
	/// <param name="vertices">| The vector containing sorted mesh data (vertices, uvs, normals)</param>
	void Fill(const std::vector<float>& vertices) const;
};