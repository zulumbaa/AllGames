#include "RevoGame.h"

void RevoGame::initVariables()
{
	window = nullptr;
}

void RevoGame::initWindow()
{
	videoMode.height = 600;
	videoMode.width = 800;
	window = new sf::RenderWindow(videoMode, "RevoGame", sf::Style::Default);
	window->setFramerateLimit(144);
}

void RevoGame::initHero()
{
	hero.setTexture(&textureHolder.Get(TextureId::Normal));
	hero.setSize(sf::Vector2f(50.f, 50.f));
	hero.setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
}

void RevoGame::initEat()
{
	eat1.setTexture(&textureHolder.Get(TextureId::GreyRevo));
	eat1.setSize(sf::Vector2f(10.f, 26.f));
	eat1.setPosition(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y));

	eat2.setTexture(&textureHolder.Get(TextureId::RedRevo));
	eat2.setSize(sf::Vector2f(8.f, 19.f));
	eat2.setPosition(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y));
}

void RevoGame::initSpeed()
{
	speed = 3.f;
}

void RevoGame::initSounds()
{
	soundsHolder.Load(SoundsId::Eating, "other//revogame//eating.wav");
	soundsHolder.Load(SoundsId::Vomiting, "other//revogame//ueu.wav");
	soundsHolder.Load(SoundsId::GameOver, "other//revogame//game_over.wav");
	soundsHolder.Load(SoundsId::LevelUp, "other//revogame//level_up.wav");

	if (!soundtrack.openFromFile("other//revogame//revo.wav")) {
		throw "Error reading sound 'music'";
	}
	soundtrack.setVolume(30.f);
	soundtrack.setLoop(true);
}

void RevoGame::initTextures()
{
	textureHolder.Load(TextureId::GreyRevo, "other//revogame//grey_revo.png");
	textureHolder.Load(TextureId::GameOverSprite, "other//revogame//gameOver.png");
	textureHolder.Load(TextureId::Happy, "other//revogame//happy.jpg");
	textureHolder.Load(TextureId::HeartsTexture0, "other//revogame//0_life.png");
	textureHolder.Load(TextureId::HeartsTexture1, "other//revogame//1_life.png");
	textureHolder.Load(TextureId::HeartsTexture2, "other//revogame//2_life.png");
	textureHolder.Load(TextureId::HeartsTexture3, "other//revogame//3_life.png");
	textureHolder.Load(TextureId::Normal, "other//revogame//normal.jpg");
	textureHolder.Load(TextureId::RedRevo, "other//revogame//red_revo.png");
	textureHolder.Load(TextureId::Sad, "other//revogame//sad.jpg");
}

void RevoGame::initgameOverText()
{
	gameOverSprite.setTexture(textureHolder.Get(TextureId::GameOverSprite));

	gameOverSprite.setScale(
		static_cast<float>(videoMode.width) / textureHolder.Get(TextureId::GameOverSprite).getSize().x,
		static_cast<float>(videoMode.height) / textureHolder.Get(TextureId::GameOverSprite).getSize().y
	);

	gameOverSprite.setPosition(sf::Vector2f(
		(videoMode.width - gameOverSprite.getGlobalBounds().width) / 2,
		(videoMode.height - gameOverSprite.getGlobalBounds().height) / 2
	));
}

void RevoGame::initScoreIndicator()
{
	ScoreIndicatorBorder.setSize(sf::Vector2f(200.f, 20.f));
	ScoreIndicatorBorder.setOutlineColor(sf::Color::White);
	ScoreIndicatorBorder.setPosition(sf::Vector2f(
		(videoMode.width - ScoreIndicator.getSize().x) / 3,
		5.f
	));

	ScoreIndicatorBorder.setOutlineThickness(1.f);
	ScoreIndicatorBorder.setFillColor(sf::Color::Transparent);

	ScoreIndicator.setSize(sf::Vector2f(1.f, 20.f));
	ScoreIndicator.setOutlineColor(sf::Color::Red);
	ScoreIndicator.setPosition(sf::Vector2f(
		(videoMode.width - ScoreIndicator.getSize().x) / 3,
		5.f
	));
}

void RevoGame::initHearts()
{
	hearts.setTexture(&textureHolder.Get(TextureId::HeartsTexture3));
	hearts.setSize(sf::Vector2f(84.f, 24.f));
	hearts.setPosition(sf::Vector2f(0.f, 0.f));
}
void RevoGame::initText()
{
	if (!textFont.loadFromFile("other//revogame//PixelGameFont.ttf"))
	{
		throw "Error reading font";
	}

	levelText.setFont(textFont);
	levelText.setString("LV. " + std::to_string(level));
	levelText.setPosition(sf::Vector2f(
		(videoMode.width - levelText.getLocalBounds().width),
		5.f
	));
	levelText.setCharacterSize(16);

	timerText.setFont(textFont);
	timerText.setString(std::to_string(time));
	timerText.setPosition(sf::Vector2f(
		(videoMode.width - 75.f),
		30.f
	));
	timerText.setCharacterSize(16);

	restartText.setFont(textFont);
	restartText.setString("press 'R' to restart");
	restartText.setPosition(sf::Vector2f(
		(videoMode.width - videoMode.width / 2 - restartText.getLocalBounds().width / 2),
		400.f
	));
	restartText.setCharacterSize(24);
}

RevoGame::RevoGame()
{
	initVariables();
	initWindow();
	initSounds();
	initTextures();
	initHero();
	initEat();
	initSpeed();
	initgameOverText();
	initScoreIndicator();
	initHearts();
	initText();


	soundtrack.play();
}

void RevoGame::playSound(const SoundsId id)
{
	sound.setBuffer(soundsHolder.Get(id));
	sound.play();
}

void RevoGame::heartLoosing()
{
	playSound(SoundsId::Vomiting);
	lifes--;
	if (lifes == 2) {
		hero.setTexture(&textureHolder.Get(TextureId::Normal));
	}
	else if (lifes == 3) {
		hero.setTexture(&textureHolder.Get(TextureId::Sad));
	}
	updateHearts();
}

RevoGame::~RevoGame()
{
	delete window;
}



const bool RevoGame::getWindowIsOpen() const
{
	return window->isOpen();
}

void RevoGame::pollEvents()
{
	while (window->pollEvent(ev)) {
		switch (ev.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::R && isGameOver) {
				restartGame();
			}
			break;
		default:
			break;
		}
	}
}

void RevoGame::updateMousePosition()
{
	mouseWindowPosition = sf::Mouse::getPosition(*window);
	mouseWindowPositionView = window->mapPixelToCoords(mouseWindowPosition);
}

void RevoGame::updateHero()
{
	bool moveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool moveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	bool moveUp = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool moveDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	if (moveLeft && !moveRight && !moveUp && !moveDown) {
		hero.move(-speed, 0.f);
		//hero.setFillColor(sf::Color::Red);
	}
	else if (!moveLeft && moveRight && !moveUp && !moveDown) {
		hero.move(speed, 0.f);
		//hero.setFillColor(sf::Color::Red);
	}
	else if (!moveLeft && !moveRight && moveUp && !moveDown) {
		hero.move(0.f, -speed);
		//hero.setFillColor(sf::Color::Red);
	}
	else if (!moveLeft && !moveRight && !moveUp && moveDown) {
		hero.move(0.f, speed);
		//hero.setFillColor(sf::Color::Red);
	}
	else if (moveLeft && !moveRight && moveUp && !moveDown) {
		hero.move(-speed, -speed);
		//hero.setFillColor(sf::Color::Red);
	}
	else if (moveLeft && !moveRight && !moveUp && moveDown) {
		hero.move(-speed, speed);
		//hero.setFillColor(sf::Color::Red);
	}
	else if (!moveLeft && moveRight && moveUp && !moveDown) {
		hero.move(speed, -speed);
		//hero.setFillColor(sf::Color::Red);
	}
	else if (!moveLeft && moveRight && !moveUp && moveDown) {
		hero.move(speed, speed);
		//hero.setFillColor(sf::Color::Red);
	}
	else {
		//hero.setFillColor(sf::Color::Magenta);
	}
}


void RevoGame::updateEat()
{

	if (hero.getGlobalBounds().contains((eat1.getPosition()))) {
		playSound(SoundsId::Eating);
		eat1.setPosition(sf::Vector2f(rand() % window->getSize().x, 50.f + rand() / (RAND_MAX / (window->getSize().y - 50.f))));
		float newSize = hero.getSize().x + 10.f;
		hero.setSize(sf::Vector2f(newSize, newSize));
		currentScore += 10;
		do {
			eat2.setPosition(sf::Vector2f(rand() % window->getSize().x, 50.f + rand() / (RAND_MAX / (window->getSize().y - 50.f))));

		} while (hero.getGlobalBounds().contains((eat2.getPosition())));
	}

	if (hero.getGlobalBounds().contains((eat2.getPosition()))) {
		hero.setTexture(&textureHolder.Get(TextureId::Sad));
		eat2.setPosition(sf::Vector2f(rand() % window->getSize().x, 50.f + rand() / (RAND_MAX / (window->getSize().y - 50.f))));
		float newSize = hero.getSize().x - hero.getSize().x / 3.f;
		hero.setSize(sf::Vector2f(newSize, newSize));
		currentScore = 0;

		eat1.setPosition(sf::Vector2f(rand() % window->getSize().x, 50.f + rand() / (RAND_MAX / (window->getSize().y - 50.f))));

		heartLoosing();
		if (lifes < 1) {
			gameOver();
		}
	}
}

void RevoGame::updateScoreIndicator()
{

	if (currentScore > 5) {
		currentScore -= scoreDecrease;
	}
	ScoreIndicator.setSize(sf::Vector2f(currentScore * 2, 20.f));

	if (currentScore <= 30) {
		ScoreIndicator.setFillColor(sf::Color::Red);
	}
	else if (currentScore > 30 && currentScore <= 60) {
		ScoreIndicator.setFillColor(sf::Color::Yellow);
	}
	else if (currentScore > 60 && currentScore < 100) {
		ScoreIndicator.setFillColor(sf::Color::Green);
	}
	else if (currentScore >= 100) {
		levelUp();
		hero.setTexture(&textureHolder.Get(TextureId::Happy));
	}

}

void RevoGame::updateHearts()
{
	hearts.setTexture(&textureHolder.Get(static_cast<TextureId>(INDEX_OF_FIRST_HESRTS_TEXTURE+lifes)));
}

void RevoGame::updateTimer()
{
	if (!isGameOver) {
		time = clock.getElapsedTime().asSeconds();
		timerText.setString(std::to_string(int(time)));
	}
}


void RevoGame::update()
{
	pollEvents();
	updateMousePosition();
	updateHero();
	updateEat();
	updateScoreIndicator();
	updateTimer();
}



void RevoGame::render()
{
	window->clear();

	if (isGameOver) {
		window->draw(gameOverSprite);
		window->draw(restartText);
	}
	else {
		window->draw(eat1);
		window->draw(eat2);
		window->draw(hero);

		renderingAccordingToLevel();
	}
	window->draw(ScoreIndicator);
	window->draw(ScoreIndicatorBorder);
	window->draw(hearts);
	window->draw(levelText);
	window->draw(timerText);

	window->display();
}



void RevoGame::gameOver()
{
	isGameOver = true;
	soundtrack.stop();
	playSound(SoundsId::GameOver);

}

void RevoGame::renderingAccordingToLevel()
{
	switch (level)
	{
	case 1:
	{
		break;
	}
	case 2:
	{

		break;
	}
	default:
		break;
	}
}

void RevoGame::levelUp()
{
	playSound(SoundsId::LevelUp);
	level++;
	scoreDecrease += 0.01;
	currentScore = 0;
	lifes = 3;
	speed += 0.3;
	updateHearts();
	levelText.setString("LV. " + std::to_string(level));
	hero.setSize(sf::Vector2f(50.f, 50.f));



}

void RevoGame::restartGame()
{
	lifes = 3;
	levelText.setString("LV. " + std::to_string(level));
	level = 1;
	isGameOver = false;
	soundtrack.play();
	currentScore = 0;
	speed = 3.f;
	scoreDecrease = 0.01;
	clock.restart();
	updateHearts();

}