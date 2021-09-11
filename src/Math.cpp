#include "../include/Math.h"

static const float PI = 3.141592653f;

std::tuple<float, float, float> Math::Add(const std::tuple<float, float, float>& vector1, const std::tuple<float, float, float>& vector2)
{
	std::tuple<float, float, float> result;

	result = { std::get<0>(vector1) + std::get<0>(vector2), std::get<1>(vector1) + std::get<1>(vector2), std::get<2>(vector1) + std::get<2>(vector2) };

	return result;
}

std::vector<float> Math::Add(const std::vector<float>& vector1, const std::vector<float>& vector2)
{
	std::vector<float> result;

	for (uint32_t i = 0; i < vector1.size(); i++)
	{
		result.push_back(vector1.at(i) + vector2.at(i));
	}

	return result;
}

std::tuple<float, float, float> Math::Subtract(const std::tuple<float, float, float>& vector1, const std::tuple<float, float, float>& vector2)
{
	std::tuple<float, float, float> result;

	result = { std::get<0>(vector1) - std::get<0>(vector2), std::get<1>(vector1) - std::get<1>(vector2), std::get<2>(vector1) - std::get<2>(vector2) };

	return result;
}

std::vector<float> Math::Subtract(const std::vector<float>& vector1, const std::vector<float>& vector2)
{
	std::vector<float> result;

	for (uint32_t i = 0; i < vector1.size(); i++)
	{
		result.push_back(vector1.at(i) - vector2.at(i));
	}

	return result;
}

std::tuple<float, float, float> Math::Normalize(const std::tuple<float, float, float>& vector)
{
	float length = Length(vector);

	std::tuple<float, float, float> result = { std::get<0>(vector) / length, std::get<1>(vector) / length, std::get<2>(vector) / length };

	return result;
}

std::tuple<float, float, float, float> Math::Normalize(const std::tuple<float, float, float, float>& vector)
{
	float length = Length(vector);

	std::tuple<float, float, float, float> result = { std::get<0>(vector) / length, std::get<1>(vector) / length, std::get<2>(vector) / length, std::get<3>(vector) / length };

	return result;
}

std::vector<float> Math::Normalize(const std::vector<float>& vector)
{
	std::vector<float> result;

	float length = Length(vector);

	for (uint32_t i = 0; i < vector.size(); i++)
	{
		result.push_back(vector.at(i) / length);
	}

	return result;
}

float Math::Length(const std::tuple<float, float, float>& vector)
{
	float length = 0.0f;
		
	length = sqrt(pow(std::get<0>(vector), 2) + pow(std::get<1>(vector), 2) + pow(std::get<2>(vector), 2));

	return length;
}

float Math::Length(const std::tuple<float, float, float, float>& vector)
{
	float length = 0.0f;

	length = sqrt(pow(std::get<0>(vector), 2) + pow(std::get<1>(vector), 2) + pow(std::get<2>(vector), 2) + pow(std::get<3>(vector), 2));

	return length;
}

float Math::Length(const std::vector<float>& vector)
{
	float length = 0.0f;

	for (uint32_t i = 0; i < vector.size(); i++)
	{
		length += pow(vector.at(i), 2);
	}

	length = sqrt(length);

	return length;
}

float Math::Dot(const std::tuple<float, float, float>& vector1, const std::tuple<float, float, float>& vector2)
{
	float result;

	result = std::get<0>(vector1) * std::get<0>(vector2) + std::get<1>(vector1) * std::get<1>(vector2) + std::get<2>(vector1) * std::get<2>(vector2);

	return result;
}

float Math::Dot(const std::vector<float>& vector1, const std::vector<float>& vector2)
{
	if (vector1.size() == 3 && vector2.size() == 3)
	{
		float result = 0.0f;

		for (uint32_t i = 0; i < vector1.size(); i++)
		{
			result += vector1.at(i) * vector2.at(i);
		}

		return result;
	}
}

std::tuple<float, float, float> Math::Cross(const std::tuple<float, float, float>& vector1, const std::tuple<float, float, float>& vector2)
{
	std::tuple<float, float, float> result;

	result = { std::get<1>(vector1) * std::get<2>(vector2) - std::get<2>(vector1) * std::get<1>(vector2), std::get<2>(vector1) * std::get<0>(vector2) - std::get<0>(vector1) * std::get<2>(vector2), std::get<0>(vector1) * std::get<1>(vector2) - std::get<1>(vector1) * std::get<0>(vector2), };

	return result;
}

std::vector<float> Math::Cross(const std::vector<float>& vector1, const std::vector<float>& vector2)
{
	if (vector1.size() == 3 && vector2.size() == 3)
	{
		std::vector<float> result;

		result = { vector1.at(1) * vector2.at(2) - vector1.at(2) * vector2.at(1), vector1.at(2) * vector2.at(0) - vector1.at(0) * vector2.at(2), vector1.at(0) * vector2.at(1) - vector1.at(1) * vector2.at(0) };
	
		return result;
	}
}

/*
std::tuple<float, float, float, float> Math::Transform(const std::tuple<float, float, float, float> point, const Matrix<float>& matrix)
{
	std::tuple<float, float, float, float> result;
	std::vector<float> tempVector = { std::get<0>(point), std::get<1>(point), std::get<2>(point), std::get<3>(point) };
	std::vector<float> resultVector;

	for (int i = 0; i < 4; i++)
	{
		float resultValue = 0.0f;
		for (int j = 0; j < 4; j++)
		{
			resultValue += matrix(i, j) * tempVector.at(j);
		}
		resultVector.at(i) = resultValue;
	}

	result = { resultVector.at(0), resultVector.at(1), resultVector.at(2), resultVector.at(3) };

	return result;
}
*/


float Math::ToRadian(const float& angle)
{
	return angle * (PI / 180.0f);
}

float Math::ToDegrees(const float& radian)
{
	return radian * (180.0f / PI);
}