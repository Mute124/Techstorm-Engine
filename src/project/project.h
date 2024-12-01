#pragma once
#include "../engine/Project.h"


/// <summary>
/// Write your project code here or do what you want with it. However,
/// you MUST implement the IProject interface somehow and set the project reference!
/// See <see cref="Techstorm::IProject" /> for more information on this.
/// </summary>
/// <inheritdoc />
class Project final : public Techstorm::IProject {
private:

public:

	Project() : IProject() {
		//mRenderer = Renderer();
		
	}
	void preInit() override {
<<<<<<< HEAD
		// WARNING: This MUST be called before any operations that use the file registry. The only exceptions is if you are adding load functions and adding extensions
		// that need to be loaded on registration.
		IProject::preInit();
	}
=======
		IProject::preInit();

		this->mLuaLibraries.push_back(sol::lib::base);
	}

>>>>>>> 54653e5aab996b3ca5dfae6c481ea281d8cba5dc
};
