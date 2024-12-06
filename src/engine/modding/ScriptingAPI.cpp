#include "ScriptingAPI.h"
#include "../conf/Config.h"

#ifdef TS_ENABLE_MODDING

/// <summary>
/// Initializes the scripting API.
/// </summary>
/// <returns>an integer value that represents the result of the operation.</returns>
int Techstorm::ScriptingAPI::initializeScripting(ScriptingLibraryRegistry const& libraries, ScriptingFunctionRegistry const& functions)
{
	this->mLibraries = libraries;
	return 0;
}
// Define a simple function with parameters
void greet(const std::string& name, int age) {
	std::cout << "Hello, " << name << "! You are " << age << " years old." << std::endl;
}
/// <summary>
/// Registers the scripting API for Lua.
/// </summary>
/// <returns>an integer value that represents the result of the operation.</returns>
int Techstorm::ScriptingAPI::registerLua()
{
	for (auto it = std::begin(Techstorm::ScriptingAPI::mLibraries); it != std::end(Techstorm::ScriptingAPI::mLibraries); it++) {
		this->mLua.open_libraries(*it);
	}

	mLua.set_function("LookupConfigOption", &GetConfigString);


	return 0;
}

/// <summary>
/// Registers the scripting API for AngelScript. This is just for organization sake and it could be merged with the lua version, but it wont be.
/// </summary>
/// <returns>an integer value that represents the result of the operation.</returns>
int Techstorm::ScriptingAPI::registerAngelScript()
{
	return 0;
}

#endif