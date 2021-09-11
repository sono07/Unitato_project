#pragma once

#include <vector>
#include <tuple>
#include <cmath>

#include "../include/Matrix.h"

class Math
{
public:
	/// <summary>
	/// Adds two three dimensional vectors together (std::tuple<float, float, float>)
	/// </summary>
	/// <param name="vector1">| First vector for addition</param>
	/// <param name="vector2">| Second vector for addition</param>
	/// <returns>Result vector of addition</returns>
	static std::tuple<float, float, float> Add(const std::tuple<float, float, float>& vector1, const std::tuple<float, float, float>& vector2);

	/// <summary>
	/// Adds two vectors together (std::vector<float>)
	/// </summary>
	/// <param name="vector1">| First vector for addition</param>
	/// <param name="vector2">| Second vector for addition</param>
	/// <returns>Result vector of addition</returns>
	static std::vector<float> Add(const std::vector<float>& vector1, const std::vector<float>& vector2);

	/// <summary>
	/// Subtracts right-hand vector from left-hand vector (std::tuple<float, float, float>)
	/// </summary>
	/// <param name="vector1">| Left-hand side vector for subtraction</param>
	/// <param name="vector2">| Right-hand side vector vector for addition</param>
	/// <returns>Result vector of subtraction</returns>
	static std::tuple<float, float, float> Subtract(const std::tuple<float, float, float>& vector1, const std::tuple<float, float, float>& vector2);

	/// <summary>
	/// Subtracts right-hand vector from left-hand vector (std::vector<float>)
	/// </summary>
	/// <param name="vector1">| Left-hand side vector for subtraction</param>
	/// <param name="vector2">| Right-hand side vector vector for addition</param>
	/// <returns>Result vector of subtraction</returns>
	static std::vector<float> Subtract(const std::vector<float>& vector1, const std::vector<float>& vector2);

	/// <summary>
	/// Normalizes a vector: maps members to a [-1, 1] interval  (std::tuple<float, float, float>)
	/// </summary>
	/// <param name="vector">| Vector for normalization</param>
	/// <returns>Result vector of normalization</returns>
	static std::tuple<float, float, float> Normalize(const std::tuple<float, float, float>& vector);

	/// <summary>
	/// Normalizes a vector: maps members to a [-1, 1] interval  (std::tuple<float, float, float, float>)
	/// </summary>
	/// <param name="vector">| Vector for normalization</param>
	/// <returns>Result vector of normalization</returns>
	static std::tuple<float, float, float, float> Normalize(const std::tuple<float, float, float, float>& vector);

	/// <summary>
	/// Normalizes a vector: maps members to a [-1, 1] interval  (std::vector<float>)
	/// </summary>
	/// <param name="vector">| Vector for normalization</param>
	/// <returns>Result vector of normalization</returns>
	static std::vector<float> Normalize(const std::vector<float>& vector);

	/// <summary>
	/// Calculates the length of a vector (std::tuple<float, float, float>)
	/// </summary>
	/// <param name="vector">| Vector for length calculation</param>
	/// <returns>Length of the vector</returns>
	static float Length(const std::tuple<float, float, float>& vector);

	/// <summary>
	/// Calculates the length of a vector (std::tuple<float, float, float, float>)
	/// </summary>
	/// <param name="vector">| Vector for length calculation</param>
	/// <returns>Length of the vector</returns>
	static float Length(const std::tuple<float, float, float, float>& vector);

	/// <summary>
	/// Calculates the length of a vector (std::vector<float>)
	/// </summary>
	/// <param name="vector">| Vector for length calculation</param>
	/// <returns>Length of the vector</returns>
	static float Length(const std::vector<float>& vector);

	/// <summary>
	/// Calculates the dot product of two vectors (std::tuple<float, float, float>)
	/// </summary>
	/// <param name="vector1">| First vector for multiplication</param>
	/// <param name="vector2">| Second vector for multiplication</param>
	/// <returns>Result of multiplication</returns>
	static float Dot(const std::tuple<float, float, float>& vector1, const std::tuple<float, float, float>& vector2);

	/// <summary>
	/// Calculates the dot product of two vectors (std::vector<float>)
	/// </summary>
	/// <param name="vector1">| First vector for multiplication</param>
	/// <param name="vector2">| Second vector for multiplication</param>
	/// <returns>Result of multiplication</returns>
	static float Dot(const std::vector<float>& vector1, const std::vector<float>& vector2);

	/// <summary>
	/// Calculates the cross product of two vectors (std::tuple<float, float, float>)
	/// </summary>
	/// <param name="vector1">| Left-hand side vector for multiplication</param>
	/// <param name="vector2">| Right-hand side vector for multiplication</param>
	/// <returns>Result vector of multiplication</returns>
	static std::tuple<float, float, float> Cross(const std::tuple<float, float, float>& vector1, const std::tuple<float, float, float>& vector2);

	/// <summary>
	/// Calculates the cross product of two vectors (std::vector<float>)
	/// </summary>
	/// <param name="vector1">| Left-hand side vector for multiplication</param>
	/// <param name="vector2">| Right-hand side vector for multiplication</param>
	/// <returns>Result vector of multiplication</returns>
	static std::vector<float> Cross(const std::vector<float>& vector1, const std::vector<float>& vector2);

	/*
	/// <summary>
	/// Transforms a vector around a matrix
	/// </summary>
	/// <param name="point">| The point to be transformed</param>
	/// <param name="matrix">| The matrix the point is transformed around</param>
	/// <returns>The transformed point</returns>
	static std::tuple<float, float, float, float> Transform(const std::tuple<float, float, float, float> point, const Matrix<float>& matrix);
	*/

	/// <returns>Given angle of degrees in radian</returns>
	static float ToRadian(const float& angle);

	/// <returns>Given angle of radians in degrees</returns>
	static float ToDegrees(const float& radian);
};