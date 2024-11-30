#include "GameCamera.h"
<<<<<<< HEAD
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

=======

void Techstorm::GameCamera::update()
{
>>>>>>> 54653e5aab996b3ca5dfae6c481ea281d8cba5dc
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

<<<<<<< HEAD
  Vector3 Techstorm::GameCamera::getPosition() const { return mCameraData.position; }
=======
inline Vector3 Techstorm::GameCamera::getPosition() const { return mCameraData.position; }
>>>>>>> 54653e5aab996b3ca5dfae6c481ea281d8cba5dc

/// <summary>
/// Gets the target.
/// </summary>
/// <returns></returns>

<<<<<<< HEAD
  Vector3 Techstorm::GameCamera::getTarget() const { return mCameraData.target; }
=======
inline Vector3 Techstorm::GameCamera::getTarget() const { return mCameraData.target; }
>>>>>>> 54653e5aab996b3ca5dfae6c481ea281d8cba5dc

/// <summary>
/// Gets up.
/// </summary>
/// <returns></returns>
<<<<<<< HEAD
  Vector3 Techstorm::GameCamera::getUp() const { return mCameraData.up; }
=======
inline Vector3 Techstorm::GameCamera::getUp() const { return mCameraData.up; }
>>>>>>> 54653e5aab996b3ca5dfae6c481ea281d8cba5dc

/// <summary>
/// Gets the camera's fovy (Field of View Y). For more information, please see the section on it in the documentation.
/// </summary>
/// <returns>The camera's fovy</returns>
/// \ref how-cameras-work
<<<<<<< HEAD
  float Techstorm::GameCamera::getFovy() const { return mCameraData.fovy; }
=======
inline float Techstorm::GameCamera::getFovy() const { return mCameraData.fovy; }
>>>>>>> 54653e5aab996b3ca5dfae6c481ea281d8cba5dc

/// <summary>
/// Gets the camera's projection.
/// </summary>
/// <returns></returns>
<<<<<<< HEAD
  int Techstorm::GameCamera::getProjection() const { return mCameraData.projection; }
=======
inline int Techstorm::GameCamera::getProjection() const { return mCameraData.projection; }
>>>>>>> 54653e5aab996b3ca5dfae6c481ea281d8cba5dc

/// <summary>
/// Sets the camera data.
/// </summary>
/// <param name="data">The data.</param>
<<<<<<< HEAD
  void Techstorm::GameCamera::setCameraData(Camera3D const& data) { mCameraData = data; }
=======
inline void Techstorm::GameCamera::setCameraData(Camera3D const& data) { mCameraData = data; }
>>>>>>> 54653e5aab996b3ca5dfae6c481ea281d8cba5dc

/// <summary>
/// Sets the position.
/// </summary>
/// <param name="position">The position.</param>
<<<<<<< HEAD
void Techstorm::GameCamera::setPosition(Vector3 position) { mCameraData.position = position; }
=======
inline void Techstorm::GameCamera::setPosition(Vector3 position) { mCameraData.position = position; }
>>>>>>> 54653e5aab996b3ca5dfae6c481ea281d8cba5dc

/// <summary>
/// Sets the target.
/// </summary>
/// <param name="target">The target.</param>
<<<<<<< HEAD
void Techstorm::GameCamera::setTarget(Vector3 target) { mCameraData.target = target; }
=======
inline void Techstorm::GameCamera::setTarget(Vector3 target) { mCameraData.target = target; }
>>>>>>> 54653e5aab996b3ca5dfae6c481ea281d8cba5dc

/// <summary>
/// Sets up.
/// </summary>
/// <param name="up">Up.</param>
<<<<<<< HEAD
void Techstorm::GameCamera::setUp(Vector3 up) { mCameraData.up = up; }
=======
inline void Techstorm::GameCamera::setUp(Vector3 up) { mCameraData.up = up; }
>>>>>>> 54653e5aab996b3ca5dfae6c481ea281d8cba5dc

/// <summary>
/// Sets the fovy.
/// </summary>
/// <param name="fovy">The fovy.</param>
<<<<<<< HEAD
void Techstorm::GameCamera::setFovy(float fovy) { mCameraData.fovy = fovy; }
=======
inline void Techstorm::GameCamera::setFovy(float fovy) { mCameraData.fovy = fovy; }
>>>>>>> 54653e5aab996b3ca5dfae6c481ea281d8cba5dc

/// <summary>
/// Sets the projection.
/// </summary>
/// <param name="projection">The projection.</param>
<<<<<<< HEAD
void Techstorm::GameCamera::setProjection(int projection) { mCameraData.projection = projection; }
=======
inline void Techstorm::GameCamera::setProjection(int projection) { mCameraData.projection = projection; }
>>>>>>> 54653e5aab996b3ca5dfae6c481ea281d8cba5dc
