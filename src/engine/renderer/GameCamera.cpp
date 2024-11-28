#include "GameCamera.h"
#include <raylib.h>

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
	UpdateCamera(&mCameraData, CAMERA_FIRST_PERSON);

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

  Vector3 Techstorm::GameCamera::getPosition() const { return mCameraData.position; }

/// <summary>
/// Gets the target.
/// </summary>
/// <returns></returns>

  Vector3 Techstorm::GameCamera::getTarget() const { return mCameraData.target; }

/// <summary>
/// Gets up.
/// </summary>
/// <returns></returns>
  Vector3 Techstorm::GameCamera::getUp() const { return mCameraData.up; }

/// <summary>
/// Gets the camera's fovy (Field of View Y). For more information, please see the section on it in the documentation.
/// </summary>
/// <returns>The camera's fovy</returns>
/// \ref how-cameras-work
  float Techstorm::GameCamera::getFovy() const { return mCameraData.fovy; }

/// <summary>
/// Gets the camera's projection.
/// </summary>
/// <returns></returns>
  int Techstorm::GameCamera::getProjection() const { return mCameraData.projection; }

/// <summary>
/// Sets the camera data.
/// </summary>
/// <param name="data">The data.</param>
  void Techstorm::GameCamera::setCameraData(Camera3D const& data) { mCameraData = data; }

/// <summary>
/// Sets the position.
/// </summary>
/// <param name="position">The position.</param>
void Techstorm::GameCamera::setPosition(Vector3 position) { mCameraData.position = position; }

/// <summary>
/// Sets the target.
/// </summary>
/// <param name="target">The target.</param>
void Techstorm::GameCamera::setTarget(Vector3 target) { mCameraData.target = target; }

/// <summary>
/// Sets up.
/// </summary>
/// <param name="up">Up.</param>
void Techstorm::GameCamera::setUp(Vector3 up) { mCameraData.up = up; }

/// <summary>
/// Sets the fovy.
/// </summary>
/// <param name="fovy">The fovy.</param>
void Techstorm::GameCamera::setFovy(float fovy) { mCameraData.fovy = fovy; }

/// <summary>
/// Sets the projection.
/// </summary>
/// <param name="projection">The projection.</param>
void Techstorm::GameCamera::setProjection(int projection) { mCameraData.projection = projection; }
