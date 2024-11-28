#include "Project.h"
using namespace Techstorm;

WindowDecorations& Techstorm::IProject::getWindowDecorations() { return mWindowDecorations; }

void Techstorm::IProject::setWindowDecorations(WindowDecorations& windowDecorations) { mWindowDecorations = windowDecorations; }

void Techstorm::IProject::init(int argc, char* argv[]) {
	auto resources = AllocatedPhysicsResources();
	PhysicsEngine::Instance().init(resources);
}

void Techstorm::IProject::postInit() {}

void Techstorm::IProject::initRenderer() {
}

int Techstorm::IProject::run(int argc, char* argv[]) {
	return 0;
}
int Techstorm::IProject::update()
{
	return 0;
}
int Techstorm::IProject::prePhysicsUpdate() { return 0; }

int Techstorm::IProject::physicsUpdate() {
	PhysicsEngine::Instance().update(1.0f / 60.0f);
	return 0; 
}

int Techstorm::IProject::postPhysicsUpdate() { return 0; }

int Techstorm::IProject::preObjectUpdate() { return 0; }

int Techstorm::IProject::objectUpdate() { return 0; }

int Techstorm::IProject::postObjectUpdate() { return 0; }

int Techstorm::IProject::texture() { return 0; }

int Techstorm::IProject::render() { 
	
	return 0;
}

int Techstorm::IProject::cleanup(int exitCode) { return exitCode; }

IProject* Techstorm::IProject::GetProject() {
	return ProjectReference::Instance().project;
}

/// <summary>
/// Sets the project reference.
/// </summary>
/// <param name="project">The project.</param>
inline void Techstorm::IProject::ProjectReference::setProjectReference(IProject* project) {
	if (project != nullptr) {
		this->project = project;
	}
}
