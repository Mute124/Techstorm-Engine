#include "GameCamera.h"

void Techstorm::GameCamera::init()
{
	if(sCameraCount == 0) {
		this->setAsMainCamera();
	}

	this->mCameraID = sCameraCount++;

	sCameras[this->mCameraID] = this;
}

void Techstorm::GameCamera::update()
{
//	UpdateCameraPro(
//		&this->mCameraData,
	//)

}

/// <summary>
/// Gets the camera data.
/// </summary>
/// <returns>A reference to the underlying mCameraData variable</returns>

Camera3D Techstorm::GameCamera::getCameraData() { return mCameraData; }

/// <summary>
/// Gets the position.
/// </summary>
/// <returns></returns>

inline Vector3 Techstorm::GameCamera::getPosition() const { return mCameraData.position; }

/// <summary>
/// Gets the target.
/// </summary>
/// <returns></returns>

inline Vector3 Techstorm::GameCamera::getTarget() const { return mCameraData.target; }

/// <summary>
/// Gets up.
/// </summary>
/// <returns></returns>
inline Vector3 Techstorm::GameCamera::getUp() const { return mCameraData.up; }

/// <summary>
/// Gets the camera's fovy (Field of View Y). For more information, please see the section on it in the documentation.
/// </summary>
/// <returns>The camera's fovy</returns>
/// \ref how-cameras-work
inline float Techstorm::GameCamera::getFovy() const { return mCameraData.fovy; }

/// <summary>
/// Gets the camera's projection.
/// </summary>
/// <returns></returns>
inline int Techstorm::GameCamera::getProjection() const { return mCameraData.projection; }

/// <summary>
/// Sets the camera data.
/// </summary>
/// <param name="data">The data.</param>
inline void Techstorm::GameCamera::setCameraData(Camera3D const& data) { mCameraData = data; }

/// <summary>
/// Sets the position.
/// </summary>
/// <param name="position">The position.</param>
inline void Techstorm::GameCamera::setPosition(Vector3 position) { mCameraData.position = position; }

/// <summary>
/// Sets the target.
/// </summary>
/// <param name="target">The target.</param>
inline void Techstorm::GameCamera::setTarget(Vector3 target) { mCameraData.target = target; }

/// <summary>
/// Sets up.
/// </summary>
/// <param name="up">Up.</param>
inline void Techstorm::GameCamera::setUp(Vector3 up) { mCameraData.up = up; }

/// <summary>
/// Sets the fovy.
/// </summary>
/// <param name="fovy">The fovy.</param>
inline void Techstorm::GameCamera::setFovy(float fovy) { mCameraData.fovy = fovy; }

/// <summary>
/// Sets the projection.
/// </summary>
/// <param name="projection">The projection.</param>
inline void Techstorm::GameCamera::setProjection(int projection) { mCameraData.projection = projection; }
