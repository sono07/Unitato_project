#pragma once

#include "../include/Mesh.h"
#include "../include/Texture.h"
#include "../include/Matrix.h"

class Model 
{
private: 
	std::shared_ptr<Texture> m_Texture;
	std::shared_ptr<Mesh> m_Mesh;
	Matrix<float> m_ModelMatrix = Matrix<float>(4, 4);
	std::tuple<float, float, float> m_Position;
	std::tuple<float, float, float> m_Size;
public:
	/// <summary>
	/// Instantiates a Model object
	/// </summary>
	/// <param name="mesh">| Pointer to a Mesh object</param>
	/// <param name="texture">| Pointer to a Texture object</param>
	Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture);

	~Model();

	/// <summary>
	/// Creates a translation on all three axes
	/// </summary>
	/// <param name="x">| Represents transformation on the X axis</param>
	/// <param name="y">| Represents transformation on the Y axis</param>
	/// <param name="z">| Represents transformation on the Z axis</param>
	void TranslateModelMatrix(float x, float y, float z);

	/// <summary>
	/// Creates a rotation on all three axes
	/// </summary>
	/// <param name="angle">| Represents the rotation angle in degrees (°C)</param>
	void RotateModelMatrixOnX(float angle);

	/// <summary>
	/// Creates a rotation on all three axes, but with different angles
	/// </summary>
	/// <param name="angleX">| Represents the rotation angle around X axis in degrees (°C)</param>
	/// <param name="angleY">| Represents the rotation angle around Y axis in degrees (°C)</param>
	/// <param name="angleZ">| Represents the rotation angle around Z axis in degrees (°C)</param>
	void RotateModelMatrix(float angleX, float angleY, float angleZ);

	/// <summary>
	/// Creates a scaling on all three axes
	/// </summary>
	/// <param name="x">| Represents transformation on the X axis</param>
	/// <param name="y">| Represents transformation on the Y axis</param>
	/// <param name="z">| Represents transformation on the Z axis</param>
	void ScaleModelMatrix(float x, float y, float z);

	/// <summary>
	/// Calls underlying texture binding method Texture::Bind() through member texture
	/// </summary>
	void BindTexture();

	/// <returns>Pointer to underlying model matrix member</returns>
	Matrix<float> GetModelMatrix();

	/// <returns>Pointer to underlying Mesh object</returns>
	std::shared_ptr<Mesh> GetMesh();
};