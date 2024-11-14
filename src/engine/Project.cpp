#include "Project.h"
using namespace Techstorm;

WindowDecorations& Techstorm::IProject::getWindowDecorations() { return mWindowDecorations; }

void Techstorm::IProject::setWindowDecorations(WindowDecorations& windowDecorations) { mWindowDecorations = windowDecorations; }

void Techstorm::IProject::preInit() {
}

void Techstorm::IProject::init(int argc, char* argv[]) {
	std::cout << "Thread ID for IProject init" << std::this_thread::get_id() << std::endl;
}

void Techstorm::IProject::postInit() {}

void Techstorm::IProject::initRenderer() {
}

int Techstorm::IProject::run(int argc, char* argv[]) {
	std::cout << "Thread ID for IProject run: " << std::this_thread::get_id() << "" << std::endl;
	return 0;
}

int Techstorm::IProject::prePhysicsUpdate() { return 0; }

int Techstorm::IProject::physicsUpdate() { return 0; }

int Techstorm::IProject::postPhysicsUpdate() { return 0; }

int Techstorm::IProject::preObjectUpdate() { return 0; }

int Techstorm::IProject::objectUpdate() { return 0; }

int Techstorm::IProject::postObjectUpdate() { return 0; }

int Techstorm::IProject::texture() { return 0; }

int Techstorm::IProject::render() { return 0; }

int Techstorm::IProject::cleanup(int exitCode) { return exitCode; }

IProject* Techstorm::IProject::GetProject() {
	return ProjectReference::Instance().project;
}
