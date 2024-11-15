#pragma once
#define TS_SCRIPTING_LUA
#define TS_SCRIPTING_ANGELSCRIPT
#ifdef TS_SCRIPTING_LUA
#include <sol/sol.hpp>
#endif

#ifdef TS_SCRIPTING_ANGELSCRIPT
#include <angelscript.h>
#endif

#include "../utils/Singleton.h"
namespace Techstorm {
	/// <summary>
	/// Initializes the scripting API.
	/// </summary>
	/// <returns>an integer value that represents the result of the operation.</returns>
	int InitializeScripting();

	/// <summary>
	/// Registers the scripting API for Lua.
	/// </summary>
	/// <param name="lua">The lua state to register the API to.</param>
	/// <returns>an integer value that represents the result of the operation.</returns>
	int RegisterLua(sol::state& lua);

	/// <summary>
	/// Registers the scripting API for AngelScript.
	/// </summary>
	/// <returns>an integer value that represents the result of the operation.</returns>
	int RegisterAngelScript();
}
