#pragma once
#include "../engine/Project.h"
#include <raylib.h>

#define PROJECT_TYPENAME Project

/// <summary>
/// Write your project code here or do what you want with it. However,
/// you MUST implement the IProject interface somehow and set the project reference!
/// See <see cref="Techstorm::IProject" /> for more information on this.
/// </summary>
/// <inheritdoc />
class Project : public Techstorm::IProject {
public:

	Project() : IProject() {}

	void preInit() override {
		IProject::preInit();

		this->mLuaLibraries.push_back(sol::lib::base);
	}

};
