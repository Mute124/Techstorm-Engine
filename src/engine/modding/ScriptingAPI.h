#pragma once
#define TS_SCRIPTING_LUA
#define TS_SCRIPTING_ANGELSCRIPT

#define SOL_ALL_SAFETIES_ON 1

#ifdef TS_SCRIPTING_ANGELSCRIPT
#endif

#include "../utils/Singleton.h"
#include <vector>
#include <sol/state.hpp>
#include <sol/state_view.hpp>
#include <sol/types.hpp>
#include <string>
#include <unordered_map>
#include <sol/forward.hpp>

namespace Techstorm {
	struct ExportedFunction {
		const std::string cName; // What the function is called (i.e "Print")
		const sol::function cFunction;
	};

	using LuaLibraryRegistry = std::vector<sol::lib>;
	using LuaFunctionRegistry = std::unordered_map<std::string, ExportedFunction>;

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
		/// Registers the scripting API for AngelScript.
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
