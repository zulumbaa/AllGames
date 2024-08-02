#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include "ResourceHolder.h"

enum SoundsId {
	Eating,
	Vomiting,
	GameOver,
	LevelUp
};
enum TextureId {
	GameOverSprite,
	RedRevo,
	GreyRevo,
	Sad,
	Happy,
	Normal,
	HeartsTexture0,
	HeartsTexture1,
	HeartsTexture2,
	HeartsTexture3
};

class RevoGame
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	sf::Vector2i mouseWindowPosition;
	sf::Vector2f mouseWindowPositionView;

	sf::RectangleShape hero, eat1, eat2, ScoreIndicatorBorder, ScoreIndicator, hearts;
	sf::Sprite gameOverSprite;
	ResourceHolder<sf::Texture, TextureId> textureHolder;

	sf::Font textFont;
	sf::Text levelText, timerText, restartText;

	sf::Clock clock, timer;

	sf::Sound sound;
	ResourceHolder<sf::SoundBuffer, SoundsId> soundsHolder;
	sf::Music soundtrack;

	float speed;
	double currentScore = 0;
	double finalScore = 100;
	double scoreDecrease = 0.01;
	const unsigned NUMBER_OF_LIFES = 3;
	const int INDEX_OF_FIRST_HESRTS_TEXTURE = static_cast<int>(TextureId::HeartsTexture0);
	int lifes = 3;
	bool isGameOver = false;
	int level = 1;
	float time;


	void initVariables();
	void initWindow();
	void initSounds();
	void initTextures();
	void initHero();
	void initEat();
	void initSpeed();
	void initgameOverText();
	void initScoreIndicator();
	void initHearts();
	void initText();

	void playSound(const SoundsId id);
	void heartLoosing();
public:
	RevoGame();
	virtual ~RevoGame();

	const bool getWindowIsOpen() const;
	void pollEvents();
	void updateMousePosition();
	void updateHero();
	void updateEat();
	void updateScoreIndicator();
	void updateHearts();
	void updateTimer();

	void update();

	void renderingAccordingToLevel();

	void render();

	void gameOver();
	void levelUp();
	void restartGame();
};

