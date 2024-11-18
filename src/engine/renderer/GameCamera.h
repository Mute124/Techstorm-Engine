/**
* \file GameCamera.h
* \brief Declares the GameCamera class
*/
#pragma once
#include "../math/Vector.h"
#include <raylib.h>
namespace Techstorm {
#ifdef TS_RENDERER_2D
	struct CameraData {
		// TODO: Implement 2D camera
	};
#else // TS_RENDERER_3D
	struct CameraData {
		Vec3 position;
		Vec3 target;
		Vec3 up;
		float fovy;
		int projection;
	};
#endif

	class Renderer;

	/// <summary>
	/// Represents a camera wherein the world is rendered and viewed from.
	/// </summary>
	class GameCamera {
	public:
		GameCamera() = default;
		~GameCamera() = default;

		/// <summary>
		/// Updates this instance in one of two ways, depending on the camera's settings.
		/// </summary>
		/// <remarks>
		///		For a more in-depth explanation of camera settings, see \ref how-cameras-work and \ref GameCamera in the documentation.
		/// </remarks>
		virtual void update();

		/// <summary>
		/// Gets the camera data.
		/// </summary>
		/// <returns>A reference to the underlying mCameraData variable</returns>
		Camera3D getCameraData();

		/// <summary>
		/// Gets the position.
		/// </summary>
		/// <returns></returns>
		Vector3 getPosition() const;

		/// <summary>
		/// Gets the target.
		/// </summary>
		/// <returns></returns>
		Vector3 getTarget() const;

		/// <summary>
		/// Gets up.
		/// </summary>
		/// <returns></returns>
		Vector3 getUp() const;

		/// <summary>
		/// Gets the camera's fovy (Field of View Y). For more information, please see the section on it in the documentation.
		/// </summary>
		/// <returns>The camera's fovy</returns>
		/// \ref how-cameras-work
		float getFovy() const;

		/// <summary>
		/// Gets the camera's projection.
		/// </summary>
		/// <returns></returns>
		int getProjection() const;

		/// <summary>
		/// Sets the camera data.
		/// </summary>
		/// <param name="data">The data.</param>
		void setCameraData(Camera3D const& data);

		/// <summary>
		/// Sets the position.
		/// </summary>
		/// <param name="position">The position.</param>
		void setPosition(Vector3 position);

		/// <summary>
		/// Sets the target.
		/// </summary>
		/// <param name="target">The target.</param>
		void setTarget(Vector3 target);

		/// <summary>
		/// Sets up.
		/// </summary>
		/// <param name="up">Up.</param>
		void setUp(Vector3 up);

		/// <summary>
		/// Sets the fovy.
		/// </summary>
		/// <param name="fovy">The fovy.</param>
		void setFovy(float fovy);

		/// <summary>
		/// Sets the projection.
		/// </summary>
		/// <param name="projection">The projection.</param>
		void setProjection(int projection);

	private:
		Camera3D mCameraData;

		static inline void SimpleCameraUpdate(GameCamera& cam) {}
		static inline void ComplexCameraUpdate(GameCamera& cam) {}

		friend class Renderer; /// \ref Renderer
	};
}
