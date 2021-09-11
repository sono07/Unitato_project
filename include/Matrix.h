#pragma once

#include <vector>

#include "../include/Math.h"

template <typename T>
class Matrix
{
private:
	size_t m_Columns;
	size_t m_Rows;
	std::vector<T> array;

public:
	/// <summary>
	/// Instantiates a Matrix object
	/// </summary>
	/// <param name="columns">| Number of columns of the matrix</param>
	/// <param name="rows">| Number of rows of the matrix</param>
	Matrix<T>(const size_t& columns, const size_t& rows);

	/// <summary>
	/// Instantiates a Matrix object based on another matrix object (copy constructor)
	/// </summary>
	/// <param name="matrix">| A Matrix object</param>
	Matrix<T>(const Matrix& matrix);

	/// <summary>
	/// Creates an identity matrix 
	/// </summary>
	void CreateIdentity();

	/// <summary>
	/// Creates a translation on all three axes
	/// </summary>
	/// <param name="x">| Extent of translation on X axis</param>
	/// <param name="y">| Extent of translation on Y axis</param>
	/// <param name="z">| Extent of translation on Z axis</param>
	void CreateTranslation(const float& x, const float& y, const float& z);

	/// <summary>
	/// Creates a rotation on X axis
	/// </summary>
	/// <param name="angle">| Extent of rotation on X axis in degrees</param>
	void CreateRotationOnX(const float& angle);

	/// <summary>
	/// Creates a rotation on Y axis
	/// </summary>
	/// <param name="angle">| Extent of rotation on Y axis in degrees</param>
	void CreateRotationOnY(const float& angle);

	/// <summary>
	/// Creates a rotation on Z axis
	/// </summary>
	/// <param name="angle">| Extent of rotation on Z axis in degrees</param>
	void CreateRotationOnZ(const float& angle);

	/// <summary>
	/// Creates a rotation on all axes
	/// </summary>
	/// <param name="x">| Extent of rotation on X axis in degrees</param>
	/// <param name="y">| Extent of rotation on Y axis in degrees</param>
	/// <param name="z">| Extent of rotation on Z axis in degrees</param>
	void CreateRotation(float& x, float& y, float& z);

	/// <summary>
	/// Creates a scaling on all axes
	/// </summary>
	/// <param name="x">| Extent of scale on X axis</param>
	/// <param name="y">| Extent of scale on Y axis</param>
	/// <param name="z">| Extent of scale on Z axis</param>
	void CreateScale(const float& x, const float& y, const float& z);
	
	/// <summary>
	/// Creates the View / LookAt matrix
	/// </summary>
	/// <param name="camPos">| Position of the camera</param>
	/// <param name="camDir">| Direction in which the camera is facing</param>
	/// <param name="camRight">| Right vector of the camera</param>
	/// <param name="camUp">| Up vector of the camera</param>
	void CreateLookAt(std::tuple<float, float, float> camPos, std::tuple<float, float, float> camDir, std::tuple<float, float, float> camRight, std::tuple<float, float, float> camUp);

	/// <summary>
	/// Creates the Perspective matrix
	/// </summary>
	/// <param name="aspectRatio">| Aspect ratio of the renderer window</param>
	/// <param name="fov">| Field of view of the camera</param>
	/// <param name="near">| Near clipping plane</param>
	/// <param name="far">| Far clipping plane</param>
	void CreatePerspective(float aspectRatio, float fov, float near, float far);

	virtual ~Matrix<T>();
	T operator()(const size_t& i, const size_t& j) const;
	T& operator()(const size_t& i, const size_t& j);
	Matrix<T> operator=(const Matrix& matrix);
	Matrix<T> operator+(const T& scalar);
	Matrix<T> operator+(const Matrix& matrix);
	Matrix<T> operator*(const T& scalar);
	Matrix<T> operator*(const Matrix& matrix);
	Matrix<T> operator/(const T& scalar);
	Matrix<T> operator^(const T& scalar);

	/// <returns>The number of columns in a matrix</returns>
	const size_t GetColumns();

	/// <returns>The number of rows in a matrix</returns>
	const size_t GetRows();

	/// <returns>Pointer to the underlying array</returns>
	T* GetData() const;
};
