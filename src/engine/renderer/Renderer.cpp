#include "Renderer.h"

#include <iostream>
// unused, but here for a bit
Camera ConvertCamera(Techstorm::CameraData* data) {
	using namespace Techstorm;
	Camera cam = Camera();

	// convert vectors in data to raylib vectors
	Vector3 position = { data->position.x, data->position.y, data->position.z };
	Vector3 target = { data->target.x, data->target.y, data->target.z };
	Vector3 up = { data->up.x, data->up.y, data->up.z };

	cam.position = position;
	cam.target = target;
	cam.up = up;
	cam.fovy = data->fovy;
	cam.projection = data->projection;

	return cam;
}

void Techstorm::Renderer::initialize()
{
	// TODO: Implement Renderer::initialize
	Vector2 size = GetWindowScaleDPI();
	this->mScreenBuffer = LoadRenderTexture(size.x, size.y);
}

void Techstorm::Renderer::render(GameCamera& cam)
{
#ifdef TS_RENDERER_2D
	render2D(cam);
#else
	render3D(cam);
#endif
}

void Techstorm::Renderer::texture(GameCamera& cam)
{
	BeginTextureMode(this->mScreenBuffer);
	ClearBackground(WHITE);
#ifdef TS_RENDERER_2D
#else
	BeginMode3D(cam.Data);
#endif

	mGameObjects.render();

#ifdef TS_RENDERER_2D
#else
	EndMode3D();
#endif
	EndTextureMode();
}
void Techstorm::Renderer::drawFBO() {
	// TODO: Allow FBO shaders

	DrawTextureRec(this->mScreenBuffer.texture, Rectangle{ 0, 0, (float)(this->mScreenBuffer.texture.width), (float)(this->mScreenBuffer.texture.height) }, Vector2{ 0, 0 }, this->mFBOTint);
}
void Techstorm::Renderer::addGameObject(GameObject* gameObject)
{
	this->mGameObjects.addGameObject(gameObject);
}

void Techstorm::Renderer::removeGameObject(GameObject* gameObject)
{
	//this->mGameObjects.erase(std::remove(this->mGameObjects.begin(), this->mGameObjects.end(), gameObject), this->mGameObjects.end());
}

void Techstorm::Renderer::addGameObjectGate(IGameObjectGate* gameObjectGate) {}
void Techstorm::Renderer::removeGameObjectGate(IGameObjectGate* gameObjectGate) {}

void Techstorm::Renderer::cleanup()
{
}

#ifdef TS_RENDERER_2D
void Techstorm::Renderer::render2D(GameCamera& cam)
{
}
#else
void Techstorm::Renderer::render3D(GameCamera& cam)
{
	UpdateCamera(&cam.Data, CAMERA_FIRST_PERSON);

	texture(cam);

	BeginDrawing();
	drawFBO();
	EndDrawing();
}

#endif
