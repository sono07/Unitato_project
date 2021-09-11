#include "../include/Matrix.h"
#include "../include/Logger.h"

#include <cmath>

Logger MatrixLog;

template <typename T>
Matrix<T>::Matrix(const size_t& columns, const size_t& rows) : m_Columns(columns), m_Rows(rows)
{
	this->array.resize(this->m_Columns * this->m_Rows);
	for (uint32_t i = 0; i < this->m_Columns; i++)
	{
		for (uint32_t j = 0; j < this->m_Rows; j++)
		{
			this->array.at(i * this->m_Rows + j) = 0;
		}
	}
}

template <typename T>
Matrix<T>::Matrix(const Matrix& matrix) : m_Columns(matrix.m_Columns), m_Rows(matrix.m_Rows)
{
	this->array = matrix.array;
}

template <typename T>
void Matrix<T>::CreateIdentity()
{
	for (uint32_t i = 0; i < this->m_Columns; i++)
	{
		for (uint32_t j = 0; j < this->m_Rows; j++)
		{
			if (i == j)
			{
				this->array.at(i * this->m_Rows + j) = 1;
			}
			else
			{
				this->array.at(i * this->m_Rows + j) = 0;
			}
		}
	}
}

template <typename T>
void Matrix<T>::CreateTranslation(const float& x, const float& y, const float& z)
{
	this->array.at(12) = x;
	this->array.at(13) = y;
	this->array.at(14) = z;
}

template <typename T>
void Matrix<T>::CreateRotationOnX(const float& angle)
{
	this->array.at(5) = cos(angle);
	this->array.at(6) = -sin(angle);
	this->array.at(9) = sin(angle);
	this->array.at(10) = cos(angle);
}

template <typename T>
void Matrix<T>::CreateRotationOnY(const float& angle)
{
	this->array.at(0) = cos(angle);
	this->array.at(2) = -sin(angle);
	this->array.at(8) = sin(angle);
	this->array.at(10) = cos(angle);
}

template <typename T>
void Matrix<T>::CreateRotationOnZ(const float& angle)
{
	this->array.at(0) = cos(angle);
	this->array.at(1) = sin(angle);
	this->array.at(4) = -sin(angle);
	this->array.at(5) = cos(angle);
}

template <typename T>
void Matrix<T>::CreateScale(const float& x, const float& y, const float& z)
{
	this->array.at(0) = x;
	this->array.at(5) = y;
	this->array.at(10) = z;
}

template <typename T>
void Matrix<T>::CreateRotation(float& angleX, float& angleY, float& angleZ)
{
	angleX = Math::ToRadian(angleX);
	angleY = Math::ToRadian(angleY);
	angleZ = Math::ToRadian(angleZ);

	this->array.at(0) = cos(angleZ) * cos(angleY);
	this->array.at(1) = sin(angleZ) * cos(angleY);
	this->array.at(2) = -sin(angleY);
	this->array.at(3) = 0.0f;

	this->array.at(4) = cos(angleZ) * sin(angleY) * sin(angleX) - sin(angleZ) * cos(angleX);
	this->array.at(5) = sin(angleZ) * sin(angleY) * sin(angleX) + cos(angleZ) * cos(angleX);
	this->array.at(6) = cos(angleY) * sin(angleX);
	this->array.at(7) = 0.0f;

	this->array.at(8) = cos(angleZ) * sin(angleY) * cos(angleX) + sin(angleZ) * sin(angleX);	
	this->array.at(9) = sin(angleZ) * sin(angleY) * cos(angleX) - cos(angleZ) * sin(angleX);
	this->array.at(10) = cos(angleY) * cos(angleX);
	this->array.at(11) = 0.0f;

	this->array.at(12) = 0.0f;
	this->array.at(13) = 0.0f;
	this->array.at(14) = 0.0f;
	this->array.at(15) = 1.0f;
}

template <typename T>
void Matrix<T>::CreateLookAt(std::tuple<float, float, float> camPos, std::tuple<float, float, float> camDir, std::tuple<float, float, float> camRight, std::tuple<float, float, float> camUp)
{
	Matrix<float> lookAt(4, 4);
	lookAt.CreateIdentity();

	Matrix<float> viewTranslation(4, 4);
	viewTranslation.CreateIdentity();
	viewTranslation.CreateTranslation(-std::get<0>(camPos), -std::get<1>(camPos), -std::get<2>(camPos));

	//MatrixLog.Trace("viewTranslate =", viewTranslation);

	Matrix<float> viewRotation(4, 4);
	viewRotation.CreateIdentity();

	viewRotation.array.at(0) = std::get<0>(camRight);
	viewRotation.array.at(4) = std::get<1>(camRight);
	viewRotation.array.at(8) = std::get<2>(camRight);
	viewRotation.array.at(1) = std::get<0>(camUp);
	viewRotation.array.at(5) = std::get<1>(camUp);
	viewRotation.array.at(9) = std::get<2>(camUp);
	viewRotation.array.at(2) = std::get<0>(camDir);
	viewRotation.array.at(6) = std::get<1>(camDir);
	viewRotation.array.at(10) = std::get<2>(camDir);

	//MatrixLog.Trace("viewRotation =", viewRotation);

	//viewRotation.array.at(3) = std::get<0>(camPos);
	//viewRotation.array.at(6) = std::get<1>(camPos);
	//viewRotation.array.at(11) = std::get<2>(camPos);
	//MatrixLog.Trace("viewRotation =", viewRotation);

	lookAt = viewRotation * viewTranslation;

	//MatrixLog.Trace("lookAt =", lookAt);

	this->array = lookAt.array;
}

template <typename T>
void Matrix<T>::CreatePerspective(float aspectRatio, float fov, float near, float far)
{
	Matrix<float> perspective(4, 4);
	perspective.CreateIdentity();

	float top = near * tan(Math::ToRadian(fov / 2)); //ymax
	float right = top * aspectRatio; //xmax
	float left = -right; //xmin
	float bottom = -top; //ymin

	float temp, temp2, temp3, temp4;
	temp = 2.0f * near;
	temp2 = right - left;
	temp3 = top - bottom;
	temp4 = far - near;

	perspective.array.at(0) = temp / temp2;
	perspective.array.at(5) = temp / temp3;
	perspective.array.at(8) = (right + left) / temp2;
	perspective.array.at(9) = (top + bottom) / temp3;
	perspective.array.at(10) = (-far - near) / temp4;
	perspective.array.at(11) = -1.0f;
	perspective.array.at(14) = (-temp * far) / temp4;

	this->array = perspective.array;
}

template <typename T>
Matrix<T>::~Matrix()
{
}

template<typename T>
T Matrix<T>::operator()(const size_t& i, const size_t& j) const
{
	return this->array.at(i * this->m_Rows + j);
}

template<typename T>
T& Matrix<T>::operator()(const size_t& i, const size_t& j)
{
	return this->array.at(i * this->m_Rows + j);
}

template<typename T>
Matrix<T> Matrix<T>::operator=(const Matrix<T>& matrix)
{
	this->m_Columns = matrix.m_Columns;
	this->m_Rows = matrix.m_Rows;
	this->array = matrix.array;
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const T& scalar)
{
	Matrix<T> result(*this);

	for (uint32_t i = 0; i < this->m_Columns; i++)
	{
		for (uint32_t j = 0; j < this->m_Rows; j++)
		{
			result.array.at(i * this->m_Rows + j) += scalar;
		}
	}
	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& matrix)
{
	Matrix<T> result(*this);

	for (uint32_t i = 0; i < this->m_Columns; i++)
	{
		for (uint32_t j = 0; j < this->m_Rows; j++)
		{
			result.array.at(i * this->m_Rows + j) += matrix.array.at(i * this->m_Rows + j);
		}
	}
	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T& scalar)
{
	Matrix<T> result(*this);

	for (uint32_t i = 0; i < this->m_Columns; i++)
	{
		for (uint32_t j = 0; j < this->m_Rows; j++)
		{
			result.array.at(i * this->m_Rows + j) *= scalar;
		}
	}
	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& matrix)
{
	Matrix<T> result(this->m_Columns, matrix.m_Rows);

	for (uint32_t i = 0; i < this->m_Columns; i++)
	{
		for (uint32_t j = 0; j < matrix.m_Rows; j++)
		{
			for (uint32_t k = 0; k < matrix.m_Columns; k++)
			{
				result.array.at(i * this->m_Columns + j) += this->array.at(i * this->m_Rows + k) * matrix.array.at(k * matrix.m_Rows + j);
			}
		}
	}	
	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const T& scalar)
{
	Matrix<T> result(*this);

	for (uint32_t i = 0; i < this->m_Columns; i++)
	{
		for (uint32_t j = 0; j < this->m_Rows; j++)
		{
			result.array.at(i * this->m_Rows + j) /= scalar;
		}
	}
	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator^(const T& scalar)
{
	Matrix<T> result(*this);

	for (uint32_t i = 0; i < this->m_Columns; i++)
	{
		for (uint32_t j = 0; j < this->m_Rows; j++)
		{
			result.array.at(i * this->m_Rows + j) = pow(this->array.at(i * this->m_Rows + j), scalar);
		}
	}
	return result;
}

template <typename T>
const size_t Matrix<T>::GetColumns()
{
	return this->m_Columns;
}

template <typename T>
const size_t Matrix<T>::GetRows()
{
	return this->m_Rows;
}

template <typename T>
T* Matrix<T>::GetData() const
{
	return (T*)this->array.data();
}

template Matrix<int>::Matrix(const size_t& m_Columns, const size_t& m_Rows);
template Matrix<float>::Matrix(const size_t& m_Columns, const size_t& m_Rows);
template Matrix<int>::Matrix(const Matrix& matrix);
template Matrix<float>::Matrix(const Matrix& matrix);
template Matrix<int>::~Matrix();
template Matrix<float>::~Matrix();
template int Matrix<int>::operator()(const size_t& i, const size_t& j) const;
template float Matrix<float>::operator()(const size_t& i, const size_t& j) const;
template int& Matrix<int>::operator()(const size_t& i, const size_t& j);
template float& Matrix<float>::operator()(const size_t& i, const size_t& j);
template Matrix<int> Matrix<int>::operator=(const Matrix<int>& matrix);
template Matrix<float> Matrix<float>::operator=(const Matrix<float>& matrix);
template Matrix<int> Matrix<int>::operator+(const int& scalar);
template Matrix<float> Matrix<float>::operator+(const float& scalar);
template Matrix<int> Matrix<int>::operator+(const Matrix<int>& matrix);
template Matrix<float> Matrix<float>::operator+(const Matrix<float>& matrix);
template Matrix<int> Matrix<int>::operator*(const int& scalar);
template Matrix<float> Matrix<float>::operator*(const float& scalar);
template Matrix<int> Matrix<int>::operator*(const Matrix<int>& matrix);
template Matrix<float> Matrix<float>::operator*(const Matrix<float>& matrix);
template Matrix<int> Matrix<int>::operator/(const int& scalar);
template Matrix<float> Matrix<float>::operator/(const float& scalar);
template Matrix<int> Matrix<int>::operator^(const int& scalar);
template Matrix<float> Matrix<float>::operator^(const float& scalar);
template const size_t Matrix<int>::GetColumns();
template const size_t Matrix<float>::GetColumns();
template const size_t Matrix<int>::GetRows();
template const size_t Matrix<float>::GetRows();
template int* Matrix<int>::GetData() const;
template float* Matrix<float>::GetData() const;
template void Matrix<int>::CreateIdentity();
template void Matrix<float>::CreateIdentity();
template void Matrix<int>::CreateTranslation(const float& x, const float& y, const float& z);
template void Matrix<float>::CreateTranslation(const float& x, const float& y, const float& z);
template void Matrix<int>::CreateRotationOnX(const float& angle);
template void Matrix<float>::CreateRotationOnX(const float& angle);
template void Matrix<int>::CreateRotationOnY(const float& angle);
template void Matrix<float>::CreateRotationOnY(const float& angle);
template void Matrix<int>::CreateRotationOnZ(const float& angle);
template void Matrix<float>::CreateRotationOnZ(const float& angle);
template void Matrix<int>::CreateScale(const float& x, const float& y, const float& z);
template void Matrix<float>::CreateScale(const float& x, const float& y, const float& z);
template void Matrix<int>::CreateRotation(float& x, float& y, float& z);
template void Matrix<float>::CreateRotation(float& x, float& y, float& z);
template void Matrix<float>::CreateLookAt(std::tuple<float, float, float> camPos, std::tuple<float, float, float> camDir, std::tuple<float, float, float> camRight, std::tuple<float, float, float> cameraUp);
template void Matrix<float>::CreatePerspective(float aspectRatio, float fov, float near, float far);