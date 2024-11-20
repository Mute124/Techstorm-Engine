#pragma once

#include <iostream>
#include <cstdarg>
#include <cstdint>
#include <string>
#include <thread>
#include "utils/Singleton.h"

const std::string TS_ASSET_DIR = std::string(TS_TOP_LAYER) + "/game/assets/";
const std::string TS_DATA_DIR = std::string(TS_TOP_LAYER) + "/game/data/";
const std::string TS_GAME_DIR = std::string(TS_TOP_LAYER) + "/game/";

namespace Techstorm {
	//std::string MakeDataPath(std::string const& path);

	//std::string MakeAssetPath(std::string const& path);
}
