#pragma once

namespace Techstorm {

	/// <summary>
	/// Serves as the settings for the game. Please note that cMaxThreads must be at least 2. If you want Techstorm to decide,
	/// set cMaxThreads to -1.
	/// </summary>
	using GameSettings = struct GameSettings {
		const int cMaxThreads = -1; 
	};
}
