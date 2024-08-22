#pragma once
#include <SFML/Graphics.hpp>

static int CURRENT_ID = 0;

class RenderObject : public sf::Drawable {
protected:
	sf::RectangleShape obj;
	int id;

public:
	RenderObject() {
		id = ++CURRENT_ID;
	}
	void Draw(sf::RenderWindow& rw) {
		rw.draw(obj);
	}
	sf::RectangleShape& getObject() {
		return obj;
	}
	int getId() {
		return id;
	}
	void setOutlineThickness(float thickness) {
		obj.setOutlineThickness(thickness);
	}

	void setOutlineColor(const sf::Color& color) {
		obj.setOutlineColor(color);
	}
	void move(const sf::Vector2f& offset) {
		obj.move(offset);
	}
	void showBorder() {
		setOutlineThickness(3);
		setOutlineColor(sf::Color::Red);
	}

	void hideBorder() {
		setOutlineThickness(0);
		setOutlineColor(sf::Color::Transparent);
	}

	std::tuple<sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f> getBoundingBox() const {
		sf::Vector2f topLeft = obj.getPosition();
		sf::Vector2f topRight = sf::Vector2f(topLeft.x + obj.getSize().x, topLeft.y);
		sf::Vector2f bottomLeft = sf::Vector2f(topLeft.x, topLeft.y + obj.getSize().y);
		sf::Vector2f bottomRight = sf::Vector2f(topLeft.x + obj.getSize().x, topLeft.y + obj.getSize().y);
		return std::make_tuple(topLeft, topRight, bottomLeft, bottomRight);
	}

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(obj, states);
	}
};

