#include "../include/Shader.h"
#include "../include/Logger.h"

Logger ShaderLog;

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	GLint success;
	GLchar infoLog[512];

	std::string vertexShaderSource;
	ReadShader(vertexShaderPath, vertexShaderSource);
	char* source = const_cast<char*>(vertexShaderSource.c_str());

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &source, NULL);
	glCompileShader(vertexShader);

	std::string fragmentShaderSource;
	ReadShader(fragmentShaderPath, fragmentShaderSource);
	source = const_cast<char*>(fragmentShaderSource.c_str());
	
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &source, NULL);
	glCompileShader(fragmentShader);

	this->m_ProgramID = glCreateProgram();
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(this->m_ProgramID, 512, NULL, infoLog);
	}

	glAttachShader(this->m_ProgramID, vertexShader);
	glAttachShader(this->m_ProgramID, fragmentShader);
	glLinkProgram(this->m_ProgramID);
	glGetProgramiv(this->m_ProgramID, GL_LINK_STATUS, &success);

	if (!success) 
	{
		glGetProgramInfoLog(this->m_ProgramID, 512, NULL, infoLog);
	}

	glUseProgram(this->m_ProgramID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(this->m_ProgramID);
}

GLuint Shader::GetProgramID()
{
	return this->m_ProgramID;
}

void Shader::SetUniformMat4x4f(const std::string& name, const Matrix<float>& matrix)
{
	GLuint location = glGetUniformLocation(this->m_ProgramID, name.c_str());

	if (location != -1)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, matrix.GetData());
	}
	else
	{
		ShaderLog.Error("Uniform location for uniform '" + name + "' was unaccessible");
	}
}

void Shader::SetUniformVec3f(const std::string& name, const std::tuple<float, float, float>& vector)
{
	GLuint location = glGetUniformLocation(this->m_ProgramID, name.c_str());

	if (location != -1)
	{
		std::vector<float> dataVector = { std::get<0>(vector), std::get<1>(vector), std::get<2>(vector) };
		
		glUniform3fv(location, 1, dataVector.data());
	}
	else
	{
		ShaderLog.Error("Uniform location for uniform '" + name + "' was unaccessible");
	}
}