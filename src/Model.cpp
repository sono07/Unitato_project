#pragma once

#include "../include/Model.h"
#include "../include/Logger.h"

Logger ModelLog;

Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture)
{
	this->m_Mesh = mesh;

	for (int i = 0; i < this->m_ModelMatrix.GetColumns(); i++)
	{
		for (int j = 0; j < this->m_ModelMatrix.GetRows(); j++)
		{
			if (i == j)
			{
				this->m_ModelMatrix(i, j) = 1;
			}
		}
	}
	ModelLog.Trace("m_ModelMatrix matrix: ", m_ModelMatrix);

	this->m_Texture = texture;
	this->m_Position = { 0.0f, 0.0f, 0.0f };
	this->m_Size = this->m_Mesh->CalculateSize();

	ModelLog.Trace("m_Size: ", this->m_Size);
}

Model::~Model()
{
}

void Model::TranslateModelMatrix(float x, float y, float z)
{
	Matrix<float> translationMatrix(4,4);
	translationMatrix.CreateIdentity();
	translationMatrix.CreateTranslation(x, y, z);

	this->m_ModelMatrix = this->m_ModelMatrix * translationMatrix;

	this->m_Position = { x, y, z };

	ModelLog.Trace("Translation matrix: ", translationMatrix);
}

void Model::RotateModelMatrixOnX(float angle)
{
	Matrix<float> rotationMatrix(4, 4);
	rotationMatrix.CreateIdentity();
	rotationMatrix.CreateRotationOnX(angle);

	this->m_ModelMatrix = this->m_ModelMatrix * rotationMatrix;

	ModelLog.Trace("Rotation matrix: ", rotationMatrix);
}

void Model::ScaleModelMatrix(float x, float y, float z)
{
	Matrix<float> scaleMatrix(4, 4);
	scaleMatrix.CreateIdentity();
	scaleMatrix.CreateScale(x, y, z);

	this->m_ModelMatrix = this->m_ModelMatrix * scaleMatrix;

	this->m_Size = { std::get<0>(this->m_Size) * x , std::get<1>(this->m_Size) * y, std::get<2>(this->m_Size) * z };
	ModelLog.Trace("Model scaled, new sizes: ", this->m_Size);

	ModelLog.Trace("Scale matrix: ", scaleMatrix);
}

void Model::RotateModelMatrix(float angleX, float angleY, float angleZ)
{
	Matrix<float> rotationMatrix(4, 4);
	rotationMatrix.CreateIdentity();
	rotationMatrix.CreateRotation(angleX, angleY, angleZ);
	
	this->m_ModelMatrix = this->m_ModelMatrix * rotationMatrix;

	ModelLog.Trace("Rotation matrix: ", rotationMatrix);
}

void Model::BindTexture()
{
	this->m_Texture->Bind();
}

std::shared_ptr<Mesh> Model::GetMesh()
{
	return this->m_Mesh;
}

Matrix<float> Model::GetModelMatrix()
{
	return this->m_ModelMatrix;
}