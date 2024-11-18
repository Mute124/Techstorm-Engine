#include "ApplicationUtils.h"

static inline std::unordered_map<int, std::string> CreateThreadPriorityMap() {
	std::unordered_map<int, std::string> map = {
		{0, "Update"},
		{1, "Physics"},
		{2, ""}
	};

	return map;
}

Techstorm::Application::GameThreadInfo Techstorm::Application::CalculateGameThreadInfo(GameSettings& gameSettings)
{
	GameThreadInfo threadInfo;

	if(gameSettings.cMaxThreads == -1) {
		int maxThreads = std::thread::hardware_concurrency();
	} else {
		//threadInfo.cMaxThreads = gameSettings.threadCount;
	}

	return GameThreadInfo();
}

int Techstorm::Application::RunUpdateThread()
{
	int exitCode = 0;

	while(exitCode == 0) {
	}

	return 0;
}

int Techstorm::Application::RunPhysicsThread()
{
	return 0;
}

int Techstorm::Application::RunWorkerThread()
{
	return 0;
}

void Techstorm::Application::DecorateWindow(WindowDecorations& decorations)
{
}
