#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>

#include "../include/Material.h"

class Mesh
{
private:
	std::string m_Name;
	std::vector<std::shared_ptr<Material>> m_Materials;
	std::vector<std::tuple<float, float, float>> m_Vertices;
	std::vector<std::tuple<float, float>> m_UVs;
	std::vector<std::tuple<float, float, float>> m_Normals;
	std::vector<std::tuple<unsigned int, unsigned int, unsigned int>> m_Faces;
	std::vector<float> m_DataBuffer;
public:
	/// <summary>
	/// Instantiates a Model object
	/// </summary>
	/// <param name="mesh">| Pointer to a Mesh object</param>
	/// <param name="texture">| Pointer to a Texture object</param>
	Mesh(const std::string& path);

	~Mesh();

	/// <summary>
	/// Loads mesh data from an .OBJ file
	/// </summary>
	/// <param name="path">| Relative or absolute path to the .OBJ file</param>
	/// <returns>True or false whether it was successful or not</returns>
	bool LoadObj(const std::string& path);

	/// <summary>
	/// Loads mesh data from an .OBJ file
	/// </summary>
	/// <param name="path">| Relative or absolute path to the .MTL file</param>
	/// <returns>True or false whether it was successful or not</returns>
	bool LoadMtl(const std::string& mtlPath, unsigned int& materialsNumber, std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::vector<float>>>>>& materials);

	/// <summary>
	/// Sorts mesh data (vertices, uvs, normals) and stores it in a vector for supplying it to the vertex shader
	/// </summary>
	void FillBuffer();

	/// <summary>
	/// Calculates mesh size using vertex data
	/// </summary>
	/// <returns>Sizes in the x, y and z dimensions</returns> 
	std::tuple<float, float, float> CalculateSize();

	/// <returns>Vector containing sorted mesh data</returns>
	std::vector<float>& GetDataBuffer();

	/// <returns>Number of triangles the mesh consists of</returns>
	unsigned int GetNumOfTriangles() const;
};