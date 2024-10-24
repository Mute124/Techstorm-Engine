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

	class GameCamera {
	public:
		void update();

		Camera3D Data;
	private:
		friend class Renderer;
		
	};
}