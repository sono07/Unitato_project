#include "../include/Camera.h"
#include "../include/Logger.h"

Logger CameraLog;

Camera::Camera(const std::tuple<float, float, float>& position, const std::tuple<float, float, float>& rotation, const float& fov)
{
	this->m_Target = { 0.0f, 0.0f, -1.0f };
	this->m_Position = position;
	this->m_Rotation = rotation;
	this->m_FOV = fov;
}

Camera::~Camera()
{
}

void Camera::SetPosWD(const std::tuple<float, float, float>& changeBy)
{
	std::get<0>(this->m_Position) += std::get<0>(changeBy);
	std::get<1>(this->m_Position) += std::get<1>(changeBy);
	std::get<2>(this->m_Position) += std::get<2>(changeBy);
}

void Camera::SetPosAS(const std::tuple<float, float, float>& changeBy)
{
	std::get<0>(this->m_Position) -= std::get<0>(changeBy);
	std::get<1>(this->m_Position) -= std::get<1>(changeBy);
	std::get<2>(this->m_Position) -= std::get<2>(changeBy);
}

void Camera::MoveCamWD(const std::tuple<float, float, float>& changeBy)
{
	this->SetPosWD(changeBy);
	/// 
	//std::cout << std::get<0>(this->m_Position) << " " << std::get<1>(this->m_Position) << " " << std::get<2>(this->m_Position)<<std::endl;
	///
	this->CreateViewMatrix();
}

void Camera::MoveCamAS(const std::tuple<float, float, float>& changeBy)
{
	this->SetPosAS(changeBy);
	/// 
	//std::cout << std::get<0>(this->m_Position) << " " << std::get<1>(this->m_Position) << " " << std::get<2>(this->m_Position) << std::endl;
	///
	this->CreateViewMatrix();
}

void Camera::SetCamTarget(const std::tuple<float, float, float> camTarget)
{
	this->m_Target = camTarget;
	this->CreateViewMatrix();
}

void Camera::CreateViewMatrix()
{
	std::tuple<float, float, float> cameraTarget = { std::get<0>(this->m_Position) + std::get<0>(this->m_Target), std::get<1>(this->m_Position) + std::get<1>(this->m_Target), std::get<2>(this->m_Position) + std::get<2>(this->m_Target) };

	std::tuple<float, float, float> worldUp = { 0.0f, 1.0f, 0.0f };

	std::tuple<float, float, float> cameraDirection = Math::Normalize(Math::Subtract(this->m_Position, this->m_Target));
	//should be 0, 0, 1

	std::tuple<float, float, float> cameraRight = Math::Normalize(Math::Cross(worldUp, cameraDirection));
	//should be 1, 0, 0

	std::tuple<float, float, float> cameraUp = Math::Cross(cameraDirection, cameraRight);
	//should be 0, 1, 0
	this->m_Up = cameraUp;

	Matrix<float> uViewMatrix(4, 4);
	uViewMatrix.CreateIdentity();
	uViewMatrix.CreateLookAt(this->m_Position, cameraDirection, cameraRight, cameraUp);

	this->m_ViewMatrix = uViewMatrix;

	//CameraLog.Trace("uViewMatrix = ", uViewMatrix);
}

void Camera::CreateProjectionMatrix(const float& width, const float& height)
{
	Matrix<float> uProjectionMatrix(4, 4);
	uProjectionMatrix.CreateIdentity();
	uProjectionMatrix.CreatePerspective(static_cast<float>(width) / static_cast<float>(height), 45.0f, 0.1f, 100.0f);

	this->m_ProjectionMatrix = uProjectionMatrix;

	//CameraLog.Trace("uProjectionMatrix = ", uProjectionMatrix);
}

Matrix<float> Camera::GetViewMatrix()
{
	return this->m_ViewMatrix;
}

Matrix<float> Camera::GetProjectionMatrix()
{
	return this->m_ProjectionMatrix;
}

std::tuple<float, float, float> Camera::GetTarget()
{
	return this->m_Target;
}

std::tuple<float, float, float> Camera::GetUp()
{
	return this->m_Up;
}

std::tuple<float, float, float> Camera::GetPosition()
{
	return this->m_Position;
}