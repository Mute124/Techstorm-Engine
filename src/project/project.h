#pragma once
#include "../engine/Project.h"
#include "../engine/math/Vector.h"

class Project : public Techstorm::IProject {
public:

	Project() : IProject() {}

	// Inherited via IProject
	int run(int argc, char* argv[]) override;

	// Inherited via IProject
	void init(int argc, char* argv[]) override;
	void preInit() override;

};