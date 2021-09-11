#include <fstream>

#include "../include/Material.h"
#include "../include/Logger.h"

Logger MaterialLog;

Material::Material(std::pair<std::string, std::vector<std::pair<std::string, std::vector<float>>>> material)
{
	this->m_Name = material.first;

	for (uint32_t i = 0; i < material.second.size(); i++)
	{
		if (material.second.at(i).first == "Ka") { this->m_AmbientColor = std::make_tuple(material.second.at(i).second.at(0), material.second.at(i).second.at(1), material.second.at(i).second.at(2)); }
		else if (material.second.at(i).first == "Kd") { this->m_DiffuseColor = std::make_tuple(material.second.at(i).second.at(0), material.second.at(i).second.at(1), material.second.at(i).second.at(2)); }
		else if (material.second.at(i).first == "Ks") { this->m_SpecularColor = std::make_tuple(material.second.at(i).second.at(0), material.second.at(i).second.at(1), material.second.at(i).second.at(2)); }
		else if (material.second.at(i).first == "Ke") { this->m_EmissiveColor = std::make_tuple(material.second.at(i).second.at(0), material.second.at(i).second.at(1), material.second.at(i).second.at(2)); }
		else if (material.second.at(i).first == "Ns") { this->m_Shininess = material.second.at(i).second.at(0); }
		else if (material.second.at(i).first == "Ni") { this->m_OpticalDensity = material.second.at(i).second.at(0); }
		else if (material.second.at(i).first == "Tr" || material.second.at(i).first == "d") { this->m_Transparency = material.second.at(i).second.at(0); }
		else if (material.second.at(i).first == "illum") { this->m_IlluminationType = material.second.at(i).second.at(0); }
		else { MaterialLog.Warn("Not specified Material attribute '" + material.second.at(i).first + "' found!"); };
	}
}

Material::~Material()
{
}