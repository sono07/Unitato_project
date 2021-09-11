#pragma once

#include <GL/glew.h>

#include <string>

#include "../include/fileio.h"
#include "../include/Matrix.h"

class Shader
{
private:
	GLuint m_ProgramID = 0;
public:
	/// <summary>
	/// Instantiates a Shader object, generates and links it to OpenGL
	/// </summary>
	/// <param name="vertexShaderPath">| Path to a GLSL vertex shader  file</param>
	/// <param name="fragmentShaderPath">| Path to a GLSL fragment shader file</param>
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	/// <returns>The ID of the generated shader program</returns>
	GLuint GetProgramID();

	/// <summary>
	/// Sets a mat4 type uniform for the shader
	/// </summary>
	/// <param name="name">| The name of the uniform variable which is to be set</param>
	/// <param name="matrix">| A 4x4 matrix which is to be set as a uniform</param>
	void SetUniformMat4x4f(const std::string& name, const Matrix<float>& matrix);

	/// <summary>
	/// Sets a vec3 type uniform for the shader
	/// </summary>
	/// <param name="name">| The name of the uniform variable which is to be set</param>
	/// <param name="vector">| A vector which is to be set as a uniform</param>
	void SetUniformVec3f(const std::string& name, const std::tuple<float, float, float>& vector);

	/// <summary>
	/// Destroys a Shader object by and deleting its ID
	/// </summary>
	~Shader();
};