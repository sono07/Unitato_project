#pragma once

#include <GL/glew.h>

#include <vector>

class VertexArray
{
private:
	GLuint m_ID = 0;
public:

	/// <summary>
	/// Instantiates a VertexArray object by generating an ID
	/// </summary>
	VertexArray();

	/// <summary>
	/// Destroys a VertexArray object by freeing its container and deleting its ID
	/// </summary>
	~VertexArray();

	/// <summary>
	/// Calls OpenGL specifing functions to bind vertex array to the drawing API, all draw calls following Bind will use the vertex array in its calls
	/// </summary>
	void Bind() const;

	/// <summary>
	/// Copies sorted mesh data to the allocated array buffer on the GPU
	/// </summary>
	/// <param name="vertices">| The vector containing sorted mesh data (vertices, uvs, normals)</param>
	void Fill(const std::vector<float>& vertices) const;
};