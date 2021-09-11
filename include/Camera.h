#pragma once

#include <tuple>

#include "../include/Matrix.h"

class Camera
{
private:
	Matrix<float> m_ViewMatrix = Matrix<float>(4, 4);
	Matrix<float> m_ProjectionMatrix = Matrix<float>(4, 4);
	std::tuple<float, float, float> m_Position;
	std::tuple<float, float, float> m_Rotation;
	std::tuple<float, float, float> m_Target;
	std::tuple<float, float, float> m_Up;
	float m_FOV = 45.0f;
	float m_NearClipPlane = 0.1f;
	float m_FarClipPlane = 100.0f;
public:

	/// <summary>
	/// Instantiates a Camera object
	/// </summary>
	/// <param name="position">| Position of the camera in world coordinates</param>
	/// <param name="rotation">| Rotation of the camera on X, Y, Z axes</param>
	/// <param name="fov">| Horizontal field-of-view</param>
	Camera(const std::tuple<float, float, float>& position, const std::tuple<float, float, float>& rotation, const float& fov);
	~Camera();

	/// <summary>
	/// Changes the camera's position (W & D keys)
	/// </summary>
	void SetPosWD(const std::tuple<float, float, float>& changeBy);

	/// <summary>
	/// Changes the camera's position (A & S keys)
	/// </summary>
	void SetPosAS(const std::tuple<float, float, float>& changeBy);

	/// <summary>
	/// Modifies and refreshes the camera's position (W & D keys)
	/// </summary>
	void MoveCamWD(const std::tuple<float, float, float>& changeBy);

	/// <summary>
	/// Modifies and refreshes the camera's position (A & S keys)
	/// </summary>
	void MoveCamAS(const std::tuple<float, float, float>& changeBy);

	/// </summary>
	/// Sets camera target
	/// </summary>
	void SetCamTarget(const std::tuple<float, float, float> camTarget);

	/// <summary>
	/// Creates the so-called view matrix
	/// </summary>
	void CreateViewMatrix();

	/// <summary>
	/// Creates the so-called (perspective) projection matrix
	/// </summary>
	void CreateProjectionMatrix(const float& width, const float& height);

	/// <returns>The calculated view matrix</returns>
	Matrix<float> GetViewMatrix();

	/// <returns>The calculated projection matrix</returns>
	Matrix<float> GetProjectionMatrix();

	/// <returns>The target of the camera</returns>
	std::tuple<float, float, float> GetTarget();

	/// <returns>The cameraUp vector</returns>
	std::tuple<float, float, float> GetUp();

	/// <returns>The position of the camera</returns>
	std::tuple<float, float, float> GetPosition();
};