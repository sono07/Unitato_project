#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>

class Material
{
private:
	std::string m_Name;
	std::tuple<float, float, float> m_DiffuseColor = { 1.0f, 1.0f, 1.0f };
	std::tuple<float, float, float> m_AmbientColor = { 1.0f, 1.0f, 1.0f };
	std::tuple<float, float, float> m_SpecularColor = { 1.0f, 1.0f, 1.0f };
	std::tuple<float, float, float> m_EmissiveColor = { 1.0f, 1.0f, 1.0f };
	float m_Shininess = 0.0f;
	float m_Transparency = 0.0f;
	float m_OpticalDensity = 0.0f;
	unsigned int m_IlluminationType = 0;
public:
	/// <summary>
	/// Instantiates a Material object
	/// </summary>
	/// <param name="material">| Temporary name-data pairs holding material attributes</param>
	Material(std::pair<std::string, std::vector<std::pair<std::string, std::vector<float>>>> material);

	~Material();
};