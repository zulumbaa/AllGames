#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <fstream>

class RevoGame
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	sf::Vector2i mouseWindowPosition;
	sf::Vector2f mouseWindowPositionView;


	sf::RectangleShape hero;
	sf::RectangleShape eat1;
	sf::RectangleShape eat2;
	sf::Texture red_revo_txt, grey_revo_txt, sad, happy, normal;

	sf::Texture gameOverTexture;
	sf::Sprite gameOverSprite;

	sf::RectangleShape ScoreIndicatorBorder;
	sf::RectangleShape ScoreIndicator;

	sf::Texture heartsTextures[4];
	sf::RectangleShape hearts;


	double currentScore = 0;
	double finalScore = 100;
	double scoreDecrease = 0.01;

	int lifes = 3;
	bool isGameOver = false;

	int level = 1;
	sf::Font textFont;
	sf::Text levelText;

	sf::Clock clock, timer;
	float time;
	sf::Text timerText;


	sf::Text restartText;


	sf::Sound soundEating;
	sf::SoundBuffer sbEating;

	sf::Sound soundVomiting;
	sf::SoundBuffer sbVomiting;

	sf::Sound soundGameOver;
	sf::SoundBuffer sbGameOver;

	sf::Sound soundLevelUp;
	sf::SoundBuffer sbLevelUp;


	sf::Music soundtrack;
	float speed;

	void initVariables();
	void initWindow();
	void initHero();
	void initEat();
	void initSpeed();
	void initSounds();
	void initgameOverText();
	void initScoreIndicator();
	void initHearts();
	void initText();

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

