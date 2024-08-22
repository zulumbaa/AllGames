#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_map>
#include "ResourceHolder.h"
#include "ObjectsHolder.h"
#include "RenderObject.h"

enum Texture{
	Mushrooms
};



class SafeAFriend
{

private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	sf::Vector2i mouseWindowPosition;
	sf::Vector2f mouseWindowPositionView;

	ResourceHolder<sf::Texture, Texture> textures;

	ObjectHolder objects;


	bool isEditMode = false;
	bool isLeftMouseButtonPressed = false;

	void initWindow();
	void initTextures();
	void initObjects();
	


public:
	SafeAFriend();
	virtual ~SafeAFriend();

	const bool getWindowIsOpen() const;
	void pollEvents();

	void editPositionOfObject();


	void update(sf::Time deltatime);
	void updateMousePosition();
	void updateButtonsHover();
	bool coordsInRectangle(sf::Vector2f coords, sf::Vector2f topLeft, sf::Vector2f topRight, sf::Vector2f bottomLeft, sf::Vector2f bottomRight);
	

	void render();
	

};