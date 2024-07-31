#include "RevoGame.h"

void RevoGame::initVariables()
{
	window = nullptr;
}

void RevoGame::initWindow()
{
	videoMode.height = 600;
	videoMode.width = 800;
	//sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

	//videoMode.width = desktopMode.width;
	//videoMode.height = desktopMode.height;
	window = new sf::RenderWindow(videoMode, "HZ", sf::Style::Default);
	window->setFramerateLimit(144);
}

void RevoGame::initHero()
{
	//hero.setFillColor(sf::Color::Magenta);
	happy.loadFromFile("other//revogame//happy.jpg");
	normal.loadFromFile("other//revogame//normal.jpg");
	sad.loadFromFile("other//revogame//sad.jpg");

	hero.setTexture(&normal);
	hero.setSize(sf::Vector2f(50.f, 50.f));
	hero.setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
}

void RevoGame::initEat()
{
	//eat1.setFillColor(sf::Color::Green);
	grey_revo_txt.loadFromFile("other//revogame//grey_revo.png");
	eat1.setTexture(&grey_revo_txt);
	eat1.setSize(sf::Vector2f(10.f, 26.f));
	eat1.setPosition(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y));

	//eat2.setFillColor(sf::Color::Red);
	red_revo_txt.loadFromFile("other//revogame//red_revo.png");
	eat2.setTexture(&red_revo_txt);
	eat2.setSize(sf::Vector2f(8.f, 19.f));
	eat2.setPosition(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y));
}

void RevoGame::initSpeed()
{
	speed = 3.f;
}

void RevoGame::initSounds()
{
	if (!sbEating.loadFromFile("other//revogame//eating.wav")) {
		throw "Error reading sound 'eating'";
	}
	soundEating.setBuffer(sbEating);

	if (!sbVomiting.loadFromFile("other//revogame//ueu.wav")) {
		throw "Error reading sound 'Vomiting'";
	}
	soundVomiting.setBuffer(sbVomiting);

	if (!sbGameOver.loadFromFile("other//revogame//game_over.wav")) {
		throw "Error reading sound 'GameOver'";
	}
	soundGameOver.setBuffer(sbGameOver);

	if (!sbLevelUp.loadFromFile("other//revogame//level_up.wav")) {
		throw "Error reading sound 'LevelUp'";
	}
	soundLevelUp.setBuffer(sbLevelUp);

	if (!soundtrack.openFromFile("other//revogame//revo.wav")) {
		throw "Error reading sound 'music'";
	}

	soundtrack.setVolume(30.f);
	soundtrack.setLoop(true);
}

void RevoGame::initgameOverText()
{
	if (!gameOverTexture.loadFromFile("other//revogame//gameOver.png"))
	{
		throw "Error reading image 'game over'";
	}
	gameOverSprite.setTexture(gameOverTexture);

	gameOverSprite.setScale(
		static_cast<float>(videoMode.width) / gameOverTexture.getSize().x,
		static_cast<float>(videoMode.height) / gameOverTexture.getSize().y
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
	for (int i = 0; i < 4; i++)
	{
		std::string filename = "other//revogame//"+std::to_string(i) + "_life.png";
		if (!heartsTextures[i].loadFromFile(filename))
		{
			throw "Error reading image heart";
		}
	}
	hearts.setTexture(&heartsTextures[3]);
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
	initHero();
	initEat();
	initSpeed();
	initSounds();
	initgameOverText();
	initScoreIndicator();
	initHearts();
	initText();


	soundtrack.play();
}

void RevoGame::heartLoosing()
{
	soundVomiting.play();
	lifes--;
	if (lifes == 2) {
		hero.setTexture(&normal);
	}
	else if (lifes == 3) {
		hero.setTexture(&sad);
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
		soundEating.play();
		eat1.setPosition(sf::Vector2f(rand() % window->getSize().x, 50.f + rand() / (RAND_MAX / (window->getSize().y - 50.f))));
		float newSize = hero.getSize().x + 10.f;
		hero.setSize(sf::Vector2f(newSize, newSize));
		currentScore += 10;
		do {
			eat2.setPosition(sf::Vector2f(rand() % window->getSize().x, 50.f + rand() / (RAND_MAX / (window->getSize().y - 50.f))));

		} while (hero.getGlobalBounds().contains((eat2.getPosition())));
	}

	if (hero.getGlobalBounds().contains((eat2.getPosition()))) {
		hero.setTexture(&sad);
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
		hero.setTexture(&happy);
	}

}

void RevoGame::updateHearts()
{
	hearts.setTexture(&heartsTextures[lifes]);
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
	soundGameOver.play();
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
	soundLevelUp.play();
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