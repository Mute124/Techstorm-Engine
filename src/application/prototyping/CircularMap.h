#pragma once
#include <unordered_map>

template<typename T>
class CircularMap {
public:

	CircularMap(int size, std::unordered_map<int, T> map) : mMap(map), size(size) {

	}

	T next() {
		currentIndex = (currentIndex + 1) % size;
		return mMap[currentIndex];
	}

private:
	int size;
	int currentIndex = 0;
	std::unordered_map<int, T> mMap;
};