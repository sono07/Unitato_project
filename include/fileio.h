#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/// <summary>
/// Utility function to read a shader file
/// </summary>
/// <param name="path">| Relative or absolute path to the shader file</param>
/// <param name="content">| Content of the shader file in a standard string</param>
void ReadShader(const std::string& path, std::string& content);

/// <summary>
/// Utility function to read a configuration file
/// </summary>
/// <param name="path">| Relative or absolute path to the configuration file</param>
/// <param name="content">| Configurations in a standard vector of name-value pairs</param>
void ReadConfig(const std::string& path, std::vector<std::pair<std::string, double>>& content);