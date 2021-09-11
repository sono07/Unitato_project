#include "../include/Light.h"


Light::Light(const std::tuple<float, float, float>& color, const std::tuple<float, float, float>& position, const std::tuple<float, float, float>& direction, const float& intensity)
{
	this->m_Color = color;
	this->m_Position = position;
	this->m_Direction = direction;
	this->m_Intensity = intensity;
}

Light::~Light()
{
}

std::tuple<float, float, float> Light::GetPosition()
{
	return this->m_Position;
}

std::tuple<float, float, float> Light::GetDirection()
{
	return this->m_Direction;
}

std::tuple<float, float, float> Light::GetColor()
{
	return this->m_Color;
}

float Light::GetIntensity()
{
	return this->m_Intensity;
}