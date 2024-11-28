/**
* \file ScriptingAPI.h
* 
* \brief This is what will handle all of Techstorm's scripting. Currently only Lua is supported, but AngelScript is planned for a future date. Along with this, the scripting API is responsible for
* the console, loading/unloading lua libraries, etc.
* \includegraph
* 
*/
#pragma once
#define TS_SCRIPTING_LUA
#define TS_SCRIPTING_ANGELSCRIPT

/// \brief Protects against safety issues when using lua because it makes the API more stable.
#define SOL_ALL_SAFETIES_ON 1

#ifdef TS_SCRIPTING_ANGELSCRIPT
#endif


#include <vector>
#include <string>
#include <unordered_map>

#include <sol/state.hpp>
#include <sol/state_view.hpp>
#include <sol/types.hpp>
#include <sol/forward.hpp>

#include "../utils/Singleton.h"

namespace Techstorm {
	
	/// <summary>
	/// Represents a function that can be exported to lua. The reason for it's existence is because it makes it easier to export functions to lua.
	/// </summary>
	struct ExportedFunction {
		const std::string cName; // What the function is called (i.e "Print")
		const sol::function cFunction;
	};

	using LuaLibraryRegistry = std::vector<sol::lib>;
	using LuaFunctionRegistry = std::unordered_map<std::string, ExportedFunction>;
	
	/// <summary>
	/// Everything related to the scripting API, i.e loading/unloading libraries, registering functions, etc. As is mentioned at the file's documentation, only lua is supported at the moment.
	/// </summary>
	/// <seealso cref="Singleton&lt;ScriptingAPI&gt;" />
	class ScriptingAPI : public Singleton<ScriptingAPI> {
	public:
		ScriptingAPI() = default;

		/// <summary>
		/// Initializes the scripting API.
		/// </summary>
		/// <returns>an integer value that represents the result of the operation.</returns>
		int InitializeScripting(LuaLibraryRegistry const& libraries, LuaFunctionRegistry const& functions)
		{
			this->mLibraries = libraries;
			return 0;
		}

		/// <summary>
		/// Registers the scripting API for Lua.
		/// </summary>
		/// <returns>an integer value that represents the result of the operation.</returns>
		int RegisterLua()
		{
			for (auto it = std::begin(Techstorm::ScriptingAPI::mLibraries); it != std::end(Techstorm::ScriptingAPI::mLibraries); it++) {
				this->mLua.open_libraries(*it);
			}

			return 0;
		}

		/// <summary>
		/// Registers the scripting API for AngelScript. This is just for organization sake and it could be merged with the lua version, but it wont be.
		/// </summary>
		/// <returns>an integer value that represents the result of the operation.</returns>
		int RegisterAngelScript()
		{
			return 0;
		}

	private:
		sol::state mLua;

		LuaLibraryRegistry mLibraries;
		LuaFunctionRegistry mFunctions;
	};
}
