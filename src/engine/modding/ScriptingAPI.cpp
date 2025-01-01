#include "ScriptingAPI.h"
#include "../conf/Config.h"

#ifdef TS_ENABLE_MODDING



/// <summary>
/// Initializes the scripting API.
/// </summary>
/// <returns>an integer value that represents the result of the operation.</returns>
int Techstorm::ScriptingAPI::initializeScripting(ScriptingLibraryRegistry const& libraries, ScriptingFunctionRegistry const& functions)
{
	Log("Opening scripting API libraries...");
	this->mLibraries = libraries;
	return 0;
}

void Techstorm::ScriptingAPI::registerConfigFunctions() {
	this->mLua.set_function("LookupConfigOption", &GetConfigString);
}

void Techstorm::ScriptingAPI::registerFileSystemFunctions()
{
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

	this->registerConfigFunctions();


	return 0;
}
#ifdef TS_ENABLE_ANGELSCRIPT
/// <summary>
/// Registers the scripting API for AngelScript. This is just for organization sake and it could be merged with the lua version, but it wont be.
/// </summary>
/// <returns>an integer value that represents the result of the operation.</returns>
int Techstorm::ScriptingAPI::registerAngelScript()
{
	return 0;
}

#endif

#endif