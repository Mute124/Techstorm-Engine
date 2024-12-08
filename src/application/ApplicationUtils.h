#pragma once
#include "project.h"
#include "EReturnCode.h"
#include "modding/ScriptingAPI.h"
#ifdef _DEBUG
#include <crtdbg.h>
#endif
#include <iostream>
#include <unordered_map>
#include <thread>
#include <string>
#include <memory>
#include <mutex>

#include <Common.h>
#include <modding/ScriptingAPI.h>
#include <renderer/Renderer.h>
#include <renderer/WindowDecorations.h>
#include <conf/Config.h>

#include <project.h>
#include <raylib.h>
#include <thread>

#include <utils/MiscUtils.h>
#include <dbg/Logging.h>
namespace Techstorm::Application {
	
/*	class GameThread : public Singleton<GameThread> {
	public:


		std::mutex mutex;
		std::jthread thread;
		int threadFPS = 0;
		int maxFPS = 30;
		bool isStressed = false;
		bool idling = false;

		static inline std::shared_ptr<bool> GetThread(std::string name) {
			return sThreads[name];
		}

		static inline void SetThread(std::string name, std::shared_ptr<bool> thread) {
			sThreads[name] = thread;
		}

		static inline std::unordered_map<std::string, std::shared_ptr<bool>>& GetThreads() {
			return sThreads;
		}

		static inline float GetFrameTime() {
			return sFrameTime;
		}

		static inline void SetFrameTime(float frameTime) {
			sFrameTime = frameTime;
		}

		static inline bool IsWaitingForOthers() {
			return sIsWaitingForOthers;
		}

		static inline void SetWaitingForOthers(bool waiting) {
			sIsWaitingForOthers = waiting;
		}

		static inline bool ShouldExit() {
			return sExit;
		}

		static inline void SetExit(bool exit) {
			sExit = exit;
		}
		
		// Ensures that all threads run at the same time and avoids thread spaghetti
		virtual void idleUntilOthersAreReady() {
			while (sIsWaitingForOthers && !sExit) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}

		//virtual void run(std::shared_ptr<Project> userProject) = 0;




	};*/
	
/*	class GameUpdateThread  : public GameThread {
	public:
		GameUpdateThread(std::shared_ptr<Project> project) {
		//	SetThread("Update", std::make_shared<GameUpdateThread>(this));
			thread = std::jthread(&GameUpdateThread::run, project);
		}

		void run(std::shared_ptr<Project> userProject) override;
	};

	class GameWorkThread  : public GameThread {
	public:
		GameWorkThread(std::shared_ptr<Project> project) {
	//		SetThread("Work", std::make_shared<GameWorkThread>(this));
			thread = std::jthread(&GameWorkThread::run, project);
		}

		void run(std::shared_ptr<Project> userProject) override;
	};

	class GameMainThread  : public GameThread {
	public:
		GameMainThread(std::shared_ptr<Project> project) {
		//	SetThread("Main", std::make_shared<GameMainThread>(this));
			thread = std::jthread(&GameMainThread::run, project);
		}

		void idleUntilOthersAreReady() override {
			while (IsWaitingForOthers() && !ShouldExit()) {
				std::vector<bool> threadStates;
				bool allThreadsReady = true;
				for (auto& thread : GetThreads()) {
					threadStates.emplace_back(thread.second);

				}

				for (int i = 0; i < threadStates.size(); i++) {
					if (!threadStates[i]) {
						threadStates.clear();
						allThreadsReady = false;
						break;
					}
				}

				if(allThreadsReady) {
					SetWaitingForOthers(false);
					std::cout << "All threads are ready\n";
				}
				else {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				}
			}
		}

		void run(std::shared_ptr<Project> userProject) override;
	};*/




	class FrameManager : public Singleton<FrameManager> {
	public:

		float sFrameTime = 0.0f; // This is provided by the main thread. This is read only and should only be set by the main thread
		volatile bool sIsWaitingForOthers = false; // This is read only and should only be set by the main thread
		volatile bool sExit = false;
		std::unordered_map<std::string, std::shared_ptr<bool>> sThreads; // use this for information about each thread

		volatile bool isWorkerWaiting = false;
		volatile bool isUpdateWaiting = false;

		std::shared_ptr<PROJECT_TYPENAME> userProject;
		std::jthread updateThread;
		std::jthread workThread;

		int RunUpdateThread(PROJECT_TYPENAME* userProject)
		{
			isUpdateWaiting = true;

			while (sIsWaitingForOthers && !sExit) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}

			Log("Update thread started");

			while (!sExit) {
				
				userProject->update();

				userProject->preObjectUpdate();
				userProject->objectUpdate();
				userProject->postObjectUpdate();

				userProject->prePhysicsUpdate();
				userProject->physicsUpdate();
				userProject->postPhysicsUpdate();

				// This is here because it reduces CPU consumption
				std::this_thread::yield();
				
				// make it so this runs at 60 FPS
				std::this_thread::sleep_for(std::chrono::milliseconds(16));
			}
			return 0;
		}

		int RunWorkerThread(PROJECT_TYPENAME* userProject)
		{
			isWorkerWaiting = true;
			while (sIsWaitingForOthers && !sExit) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
			Log("Worker thread started");

			while (!sExit) {
				// This is here because it reduces CPU consumption
				std::this_thread::yield();
				std::this_thread::sleep_for(std::chrono::milliseconds(16));
			}

			return 0;
		}

		void launchThreads(PROJECT_TYPENAME& gameSettings)
		{
			sIsWaitingForOthers = true;
			updateThread = std::jthread([&]() {
				RunUpdateThread(&gameSettings);
			});

			updateThread.detach();
			
			
			workThread = std::jthread([&]() {
				RunWorkerThread(&gameSettings);
			});
			
			//workThread.detach();
			while (sIsWaitingForOthers && !sExit) {
				
				if (isWorkerWaiting && isUpdateWaiting) {


					Log("All threads are ready");

					sIsWaitingForOthers = false;
					break;
				}
				else {
					Log("Waiting for threads...", ELogLevel::TRACE);
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					
				}


			}
		}

		void killThreads() {
			sExit = true;
		}
	private:



		//GameUpdateThread* mUpdateThreadStatus;
		//GameWorkThread* mWorkThreadStatus;
		//GameMainThread mMainThreadStatus;
		//ThreadStatus renderThreadStatus;
	};




	using GameThreadInfo = std::unordered_map<std::string, bool>;

	GameThreadInfo CalculateGameThreadInfo(GameSettings& gameSettings);



	void DecorateWindow(WindowDecorations& decorations);
}
