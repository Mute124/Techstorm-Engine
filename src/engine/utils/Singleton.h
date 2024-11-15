#pragma once
#define TS_SINGLETON(T) public Singleton<T>

namespace Techstorm {
	/// <summary>
	/// A singleton class, it does what singletons do. The template (T) must be the type that is inheriting from this class, otherwise there will be issues.
	/// </summary>
	template<typename T>
	class Singleton
	{
	public:

		/// <summary>
		/// Retrieves the current singleton instance as a reference.
		/// </summary>
		/// <returns></returns>
		static T& Instance()
		{
			static T instance;
			return instance;
		}
	};
}
