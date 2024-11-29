#pragma once
#include "../Common.h"
namespace Techstorm {

	class Mod {
	private:
		string mName;
		string mVersion;
		string mAuthor;
		string mDescription;
	
	public:
		Mod();
		~Mod();
	};
}