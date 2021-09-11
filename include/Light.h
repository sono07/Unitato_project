#pragma once

#include <tuple>

class Light 
{
private:
	std::tuple<float, float, float> m_Color = {1.0f, 1.0f, 1.0f};
	std::tuple<float, float, float> m_Position;
	std::tuple<float, float, float> m_Direction;
	float m_Intensity = 0.5f;

public:
	/// <summary>
	/// Instantiates a Light object
	/// </summary>
	/// <param name="color">| Color of the light</param>
	/// <param name="position">| Position of the light in world coordinates</param>
	/// <param name="direction">| Direction of the light</param>
	/// <param name="intensity">| Intensity of the light</param>
	Light(const std::tuple<float, float, float>& color, const std::tuple<float, float, float>& position, const std::tuple<float, float, float>& direction, const float& intensity);
	~Light();

	/// <returns>The position of the light</returns>
	std::tuple<float, float, float> GetPosition();

	/// <returns>The direction of the light</returns>
	std::tuple<float, float, float> GetDirection();

	/// <returns>The color of the light</returns>
	std::tuple<float, float, float> GetColor();

	/// <returns>The intensity of the light</returns>
	float GetIntensity();
};