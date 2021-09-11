#pragma once

#include "../include/Mesh.h"
#include "../include/Logger.h"

Logger MeshLog;

Mesh::Mesh(const std::string& path)
{
	if (!LoadObj(path))
	{
		MeshLog.Error("Model file could not be loaded!");
		abort();
	}

	FillBuffer();
}

Mesh::~Mesh()
{
}

bool Mesh::LoadObj(const std::string& objPath)
{
	if (objPath.substr(objPath.size() - 4, 4) != ".obj")
	{
		MeshLog.Error(objPath + " is not an OBJ file!");
		return false;
	}

	this->m_Name = objPath.substr(objPath.rfind("/") + 1, objPath.size() - objPath.rfind("/") - 5);

	float floatX, floatY, floatZ;
	unsigned int uintX, uintY, uintZ;

	std::ifstream inputStream(objPath);
	if (inputStream.is_open())
	{
		std::string streamLine;
		while (std::getline(inputStream, streamLine))
		{
			std::istringstream streamLine(streamLine);
			std::string vertexType;

			streamLine >> vertexType;
			if (vertexType == "v")
			{
				streamLine >> floatX >> floatY >> floatZ;
				this->m_Vertices.push_back(std::make_tuple(floatX, floatY, floatZ));
			}
			else if (vertexType == "vt")
			{
				streamLine >> floatX >> floatY;
				this->m_UVs.push_back(std::make_tuple(floatX, floatY));
			}
			else if (vertexType == "vn")
			{
				streamLine >> floatX >> floatY >> floatZ;
				this->m_Normals.push_back(std::make_tuple(floatX, floatY, floatZ));
			}
			else if (vertexType == "f")
			{
				char delimiter;

				for (uint32_t i = 0; i < 3; i++)
				{
					streamLine >> uintX >> delimiter >> uintY >> delimiter >> uintZ;

					this->m_Faces.push_back(std::make_tuple(uintX - 1, uintY - 1 , uintZ - 1));
				}
			}
		}

		inputStream.close();

		std::string mtlPath = objPath.substr(0, objPath.rfind("/") + 1) + this->m_Name + ".mtl";
		unsigned int materialsNumber = 0;
		std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::vector<float>>>>> materials;
		LoadMtl(mtlPath, materialsNumber, materials);

		return true;
	}
	else
	{
		MeshLog.Error("[ERROR] Unable to open file: " + objPath + "!");
		return false;
	}
}

bool Mesh::LoadMtl(const std::string& mtlPath, unsigned int& materialsNumber, std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::vector<float>>>>>& materialsVector)
{
	if (mtlPath.substr(mtlPath.size() - 4, 4) != ".mtl")
	{
		MeshLog.Warn(mtlPath + " has no MTL file!");
		return false;
	}

	std::pair<std::string, std::vector<std::pair<std::string, std::vector<float>>>> materials;
	std::pair<std::string, std::vector<float>> mtlData;

	float floatX, floatY, floatZ;
	std::string name;

	std::ifstream inputStream(mtlPath);
	if (inputStream.is_open())
	{
		std::string streamLine;
		while (std::getline(inputStream, streamLine))
		{
			std::istringstream streamLine(streamLine);
			std::string dataType;

			streamLine >> dataType;

			if (dataType == "newmtl")
			{
				if (materialsNumber != 0)
				{
					materialsVector.push_back(materials);
					materials.second.clear();
				}

				streamLine >> name;
				materials.first.assign(name);
				materialsNumber++;
			}
			else if (dataType == "Ns" || dataType == "Ni" || dataType == "d" || dataType == "illum")
			{
				streamLine >> floatX;
				mtlData = std::make_pair(dataType, std::vector<float>({ floatX }));
				materials.second.push_back(mtlData);
			}
			else if (dataType == "Ka" || dataType == "Kd" || dataType == "Ks" || dataType == "Ke")
			{
				streamLine >> floatX >> floatY >> floatZ;
				mtlData = std::make_pair(dataType, std::vector<float>({ floatX, floatY, floatZ }));
				materials.second.push_back(mtlData);
			}
		}

		inputStream.close();

		materialsVector.push_back(materials);

		for (uint32_t i = 0; i < materialsVector.size(); i++)
		{
			Material newMaterial(materialsVector.at(i));
			this->m_Materials.push_back(std::make_shared<Material>(newMaterial));
		}

		for (uint32_t i = 0; i < materialsVector.size(); i++)
		{
			std::cout << materialsVector.at(i).first << std::endl;
			for (uint32_t j = 0; j < materialsVector.at(i).second.size(); j++)
			{
				std::cout << materialsVector.at(i).second.at(j).first << "\t";
				for (uint32_t k = 0; k < materialsVector.at(i).second.at(j).second.size(); k++)
				{
					std::cout << materialsVector.at(i).second.at(j).second.at(k) << "\t";
				}
				std::cout << std::endl;
			}
		}

		return true;
	}
	else
	{
		MeshLog.Error("[ERROR] Unable to open file: " + mtlPath + "!");
		return false;
	}
}

void Mesh::FillBuffer()
{
	MeshLog.Trace("m_Faces.size =", this->m_Faces.size());
	MeshLog.Trace("m_Vertices.size =", this->m_Vertices.size());
	MeshLog.Trace("m_UVs.size =", this->m_UVs.size());
	MeshLog.Trace("m_Normals.size =", this->m_Normals.size());

	for (uint32_t i = 0; i < m_Faces.size(); i++)
	{
			//Vertices
			this->m_DataBuffer.push_back(std::get<0>(this->m_Vertices.at(std::get<0>(this->m_Faces.at(i)))));
			this->m_DataBuffer.push_back(std::get<1>(this->m_Vertices.at(std::get<0>(this->m_Faces.at(i)))));
			this->m_DataBuffer.push_back(std::get<2>(this->m_Vertices.at(std::get<0>(this->m_Faces.at(i)))));

			//UVs
			this->m_DataBuffer.push_back(std::get<0>(this->m_UVs.at(std::get<1>(this->m_Faces.at(i)))));
			this->m_DataBuffer.push_back(std::get<1>(this->m_UVs.at(std::get<1>(this->m_Faces.at(i)))));

			//Normals
			this->m_DataBuffer.push_back(std::get<0>(this->m_Normals.at(std::get<2>(this->m_Faces.at(i)))));
			this->m_DataBuffer.push_back(std::get<1>(this->m_Normals.at(std::get<2>(this->m_Faces.at(i)))));
			this->m_DataBuffer.push_back(std::get<2>(this->m_Normals.at(std::get<2>(this->m_Faces.at(i)))));
	}
}

std::tuple<float, float, float> Mesh::CalculateSize()
{
	float minLength = std::get<0>(this->m_Vertices.at(0));
	float maxLength = std::get<0>(this->m_Vertices.at(0));
	float minHeight = std::get<1>(this->m_Vertices.at(0));
	float maxHeight = std::get<1>(this->m_Vertices.at(0));
	float minWidth = std::get<2>(this->m_Vertices.at(0));
	float maxWidth = std::get<2>(this->m_Vertices.at(0));

	for (uint32_t i = 0; i < this->m_Vertices.size(); i++)
	{
		if (minLength > std::get<0>(this->m_Vertices.at(i))) { minLength = std::get<0>(this->m_Vertices.at(i)); };
		if (maxLength < std::get<0>(this->m_Vertices.at(i))) { maxLength = std::get<0>(this->m_Vertices.at(i)); };

		if (minHeight > std::get<1>(this->m_Vertices.at(i))) { minHeight = std::get<1>(this->m_Vertices.at(i)); };
		if (maxHeight < std::get<1>(this->m_Vertices.at(i))) { maxHeight = std::get<1>(this->m_Vertices.at(i)); };

		if (minWidth > std::get<2>(this->m_Vertices.at(i))) { minWidth = std::get<2>(this->m_Vertices.at(i)); };
		if (maxWidth < std::get<2>(this->m_Vertices.at(i))) { maxWidth = std::get<2>(this->m_Vertices.at(i)); };
	}

	return std::make_tuple(abs(maxLength - minLength), abs(maxHeight - minHeight), abs(maxWidth - minWidth));
}

std::vector<float>& Mesh::GetDataBuffer()
{
	return this->m_DataBuffer;
}

unsigned int Mesh::GetNumOfTriangles() const
{
	return 9 * this->m_Faces.size();
}