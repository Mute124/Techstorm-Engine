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
	int InitializeScripting();

	int RegisterLua(sol::state& lua);

	int RegisterAngelScript();
}
