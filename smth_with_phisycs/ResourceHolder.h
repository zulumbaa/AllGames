#pragma once
#include <unordered_map>
#include <SFML/Audio.hpp>

template <typename ResourceType, typename ResourceID>
class ResourceHolder {
private:
	std::unordered_map<ResourceID, std::unique_ptr<ResourceType>> resourceHolder;
public:
	template <typename ... Args>
	void Load(const ResourceID& id, Args&&... args) {
		auto ptr = std::make_unique<ResourceType>();
		if (!ptr->loadFromFile(std::forward<Args>(args)...))
			throw std::runtime_error("Error with loading from file");

		resourceHolder.emplace(id, std::move(ptr));
	}
	ResourceType& Get(const ResourceID id) const{
		return *resourceHolder.at(id);
		
	}
};

template <typename ResourceID>
class MusicHolder {
private:
	std::unordered_map<ResourceID, std::unique_ptr<sf::Music>> resourceHolder;
public:
	template <typename ... Args>
	void Load(const ResourceID& id, Args&&... args) {
		auto ptr = std::make_unique<sf::Music>();
		if (!ptr->openFromFile(std::forward<Args>(args)...))
			throw std::runtime_error("Error with loading from file");

		resourceHolder.emplace(id, std::move(ptr));
	}
	sf::Music& Get(const ResourceID id) const {
		return *resourceHolder.at(id);

	}
};