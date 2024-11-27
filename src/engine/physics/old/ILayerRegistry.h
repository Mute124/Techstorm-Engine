#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <cstdint>

#include "../utils/Singleton.h"

namespace Techstorm {
	/*
	* K is the key to use
	* D is the derrived type
	* T is what the layer type is
	*/
	template<typename K, typename D, typename T>
	class ILayerRegistry abstract : public Singleton<D> {
	public:

		virtual void addDefaultLayers() = 0;
		virtual void newLayer(T layer, K key) = 0;
		virtual void newLayer(K key) = 0;

		virtual T& getlayer(K key) = 0;
		virtual K getLayerName(T layer) = 0;

		virtual bool layerExists(K key) = 0;
		virtual bool isLayer(K key, T layer) = 0;

		virtual void removeLayer(K key) = 0;
		virtual void clear() = 0;

		virtual uint16_t getLayerCount() = 0;

		virtual ~ILayerRegistry() = default;

	protected:
		std::unordered_map<K, T> mLayerMap;
		std::unordered_map<T, K> mLayerMapReverse;
		std::uint8_t mLayerCount; // Using 8 bit uint because who the hell needs more than 255 layers.
	};

	template<typename T>
	class LayerRegistry : public ILayerRegistry<std::string, LayerRegistry<T>, T> {
	public:
		LayerRegistry() = default;
		~LayerRegistry() = default;

		virtual void addDefaultLayers() {
		}

		virtual void newLayer(T layer, std::string key) {}

		virtual void newLayer(std::string key) {}

		virtual T& getlayer(std::string key) {}
		virtual std::string getLayerName(T layer) {}

		virtual bool layerExists(std::string key) {}
		virtual bool isLayer(std::string key, T layer) {}

		virtual void removeLayer(std::string key) {}
		virtual void clear() {}

		virtual uint16_t getLayerCount() {}
	};
}