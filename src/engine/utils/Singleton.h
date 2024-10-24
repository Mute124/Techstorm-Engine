#pragma once
#define TS_SINGLETON(T) public Singleton<T>

namespace Techstorm {
	template<typename T>
	class Singleton
	{
	public:
		static T& Instance()
		{
			static T instance;
			return instance;
		}
	};
}