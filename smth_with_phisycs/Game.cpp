#include "Game.h"


void Game::initVariables()
{
	view = View::LEVELS_WINDOW;
	rs_main_screen_background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));

}


void Game::initButtons()
{
	//MENU
	rs_game_name.setSize(sf::Vector2f(470, 230));
	rs_game_name.setPosition(sf::Vector2f((window->getSize().x) / 2, window->getSize().y / 4));
	rs_game_name.setOrigin(rs_game_name.getLocalBounds().width / 2, rs_game_name.getLocalBounds().height / 2);


	rs_startgame_button.setSize(sf::Vector2f(255, 65));
	rs_startgame_button.setPosition(sf::Vector2f(window->getSize().x / 2 + rs_startgame_button.getLocalBounds().width / 2,
		window->getSize().y / 4 + 4 * rs_startgame_button.getLocalBounds().height));
	rs_startgame_button.setOrigin(rs_game_name.getLocalBounds().width / 2, rs_game_name.getLocalBounds().height / 2);

	rs_setting_button.setSize(sf::Vector2f(255, 65));
	rs_setting_button.setPosition(sf::Vector2f(window->getSize().x / 2 + rs_setting_button.getLocalBounds().width / 2,
		window->getSize().y / 4 + 6 * rs_startgame_button.getLocalBounds().height));
	rs_setting_button.setOrigin(rs_game_name.getLocalBounds().width / 2, rs_game_name.getLocalBounds().height / 2);


	rs_exit_button.setSize(sf::Vector2f(255, 65));
	rs_exit_button.setPosition(sf::Vector2f(window->getSize().x / 2 + rs_exit_button.getLocalBounds().width / 2,
		window->getSize().y / 4 + 8 * rs_setting_button.getLocalBounds().height));
	rs_exit_button.setOrigin(rs_game_name.getLocalBounds().width / 2, rs_game_name.getLocalBounds().height / 2);

	//SETTING WINDOW

	rs_setting_window_bg.setSize(sf::Vector2f(480, 600));
	rs_setting_window_bg.setPosition(sf::Vector2f(window->getSize().x / 2,
		window->getSize().y / 2.5));
	rs_setting_window_bg.setOrigin(rs_setting_window_bg.getLocalBounds().width / 2, rs_setting_window_bg.getLocalBounds().height / 2);

	rs_ok_button.setSize(sf::Vector2f(200, 40));
	rs_ok_button.setPosition(sf::Vector2f(rs_setting_window_bg.getPosition().x,
		rs_setting_window_bg.getPosition().y + rs_setting_window_bg.getLocalBounds().height / 2 - 1.5 * rs_ok_button.getSize().y));
	rs_ok_button.setOrigin(rs_ok_button.getSize().x / 2, rs_ok_button.getSize().y / 2);

	rs_music_volume_settings.setSize(sf::Vector2f(400, 50));
	rs_music_volume_settings.setPosition(sf::Vector2f(rs_setting_window_bg.getPosition().x,
		rs_setting_window_bg.getPosition().y - rs_setting_window_bg.getLocalBounds().height/2 + 2 * rs_music_volume_settings.getSize().y));
	rs_music_volume_settings.setOrigin(rs_music_volume_settings.getSize().x / 2, rs_music_volume_settings.getSize().y / 2);

	rs_sounds_volume_settings.setSize(sf::Vector2f(400, 50));
	rs_sounds_volume_settings.setPosition(sf::Vector2f(rs_setting_window_bg.getPosition().x,
		rs_setting_window_bg.getPosition().y - rs_setting_window_bg.getLocalBounds().height / 2 + 4 * rs_sounds_volume_settings.getSize().y));
	rs_sounds_volume_settings.setOrigin(rs_sounds_volume_settings.getSize().x / 2, rs_sounds_volume_settings.getSize().y / 2);

	rs_music_slider.setSize(sf::Vector2f(30, 30));
	rs_music_slider.setPosition(sf::Vector2f(rs_music_volume_settings.getPosition().x + rs_music_volume_settings.getLocalBounds().width / 2,
		rs_music_volume_settings.getPosition().y + rs_music_volume_settings.getLocalBounds().height / 2));
	rs_music_slider.setOrigin(rs_music_slider.getSize().x / 2, rs_music_slider.getSize().y / 2);


	rs_sounds_slider.setSize(sf::Vector2f(30, 30));
	rs_sounds_slider.setPosition(sf::Vector2f(rs_sounds_volume_settings.getPosition().x + rs_sounds_volume_settings.getLocalBounds().width / 2,
		rs_sounds_volume_settings.getPosition().y + rs_sounds_volume_settings.getLocalBounds().height / 2));
	rs_sounds_slider.setOrigin(rs_sounds_slider.getSize().x / 2, rs_sounds_slider.getSize().y / 2);


	//LEVELS_WINDOW

	rs_levels_window.setSize(sf::Vector2f(1250, 830));
	rs_levels_window.setPosition(sf::Vector2f(window->getSize().x / 2,
		window->getSize().y / 2));
	rs_levels_window.setOrigin(rs_levels_window.getLocalBounds().width / 2, rs_levels_window.getLocalBounds().height / 2);

	float header_space = rs_levels_window.getLocalBounds().height * 0.25;
	float footer_space = rs_levels_window.getLocalBounds().height * 0.25;

	float button_spacing_x = rs_levels_window.getLocalBounds().width * 0.05;
	float button_spacing_y = rs_levels_window.getLocalBounds().height * 0.05;

	float start_y = rs_levels_window.getPosition().y - rs_levels_window.getLocalBounds().height / 2 + header_space;
	for (int i = 0; i < LEVELS_COUNT; i++) {
		float start_x = rs_levels_window.getPosition().x - rs_levels_window.getLocalBounds().width / 2+ button_spacing_x/3;
		for (int j = 0; j < LEVELS_COUNT; j++) {
			rs_levels[i][j].setSize(sf::Vector2f(255, 65));
			rs_levels[i][j].setTexture(&t_button_back);
			rs_levels[i][j].setPosition(sf::Vector2f(start_x, start_y));
			rs_levels[i][j].setOrigin(0, 0);

			start_x += rs_levels[i][j].getLocalBounds().width + button_spacing_x;
		}
		start_y += rs_levels[i][0].getLocalBounds().height + button_spacing_y;
	}

	rs_exit_levels_button.setSize(sf::Vector2f(255, 65));
	rs_exit_levels_button.setPosition(sf::Vector2f(
		rs_levels_window.getPosition().x - rs_exit_levels_button.getSize().x / 2,
		rs_levels_window.getPosition().y + rs_levels_window.getLocalBounds().height / 2 - rs_exit_levels_button.getSize().y - button_spacing_y
	));


}
void Game::initWindow()
{
	sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0];
	window = new sf::RenderWindow(fullscreenMode, "Something with physic", sf::Style::Fullscreen);

	window->setKeyRepeatEnabled(false);

	window->setFramerateLimit(144);
}

void Game::initPhotos()
{
	//MAIN_SCREEN
	t_main_screen_background.loadFromFile("images//main_menu_bg.png");
	rs_main_screen_background.setTexture(&t_main_screen_background);
	t_strartgame_button.loadFromFile("images//new_game.png");
	rs_startgame_button.setTexture(&t_strartgame_button);
	t_setting_button.loadFromFile("images//settings.png");
	rs_setting_button.setTexture(&t_setting_button);
	t_exit_button.loadFromFile("images//exit.png");
	rs_exit_button.setTexture(&t_exit_button);
	t_game_name.loadFromFile("images//game_name.png");
	rs_game_name.setTexture(&t_game_name);

	t_strartgame_button_l.loadFromFile("images//new_game_light.png");
	t_setting_button_l.loadFromFile("images//settings_light.png");
	t_exit_button_l.loadFromFile("images//exit_light.png");

	//SETTING_WINDOW
	t_setting_window_bg.loadFromFile("images//setting_window_bg.png");
	rs_setting_window_bg.setTexture(&t_setting_window_bg);
	t_ok_button.loadFromFile("images//ok.png");
	rs_ok_button.setTexture(&t_ok_button);
	t_sounds_volume_settings.loadFromFile("images//sounds_volume.png");
	rs_sounds_volume_settings.setTexture(&t_sounds_volume_settings);
	t_music_volume_settings.loadFromFile("images//music_volume.png");
	rs_music_volume_settings.setTexture(&t_music_volume_settings);
	t_slider.loadFromFile("images//slider.png");
	rs_music_slider.setTexture(&t_slider);
	rs_sounds_slider.setTexture(&t_slider);


	t_ok_button_l.loadFromFile("images//ok_light.png");

	//LEVELS_WINDOW

	t_levels_window.loadFromFile("images//levels_window.png");
	rs_levels_window.setTexture(&t_levels_window);

	t_button_back.loadFromFile("images//button_back.png");
	t_button_back_l.loadFromFile("images//button_back_l.png");

	rs_exit_levels_button.setTexture(&t_exit_button);

}

void Game::initLevels()
{
	rs_levels = new sf::RectangleShape * [LEVELS_COUNT];
	for (int i = 0; i < LEVELS_COUNT; ++i) {
		rs_levels[i] = new sf::RectangleShape[LEVELS_COUNT];
	}
	levels_number_t = new sf::Text * [LEVELS_COUNT];
	for (int i = 0; i < LEVELS_COUNT; ++i) {
		levels_number_t[i] = new sf::Text[LEVELS_COUNT];
	}
}

Game::Game()
{
	initWindow();
	initVariables();
	initLevels();

	initPhotos();
	initMusic();
	initButtons();
	initText();



}

void Game::initText() {

	main_font.loadFromFile("fonts//Bungee-Regular.ttf");
	coords_t.setFont(main_font);
	coords_t.setPosition( window->getSize().x / 2, 20);
	coords_t.setFillColor(sf::Color::Black);

	levels_t.setFillColor(dark_green_c);
	levels_t.setFont(main_font);
	levels_t.setString("GAMES");
	levels_t.setCharacterSize(48); 
	levels_t.setPosition(sf::Vector2f(
		rs_levels_window.getPosition().x - levels_t.getLocalBounds().width / 2,
		rs_levels_window.getPosition().y - rs_levels_window.getLocalBounds().height / 2 + levels_t.getLocalBounds().height / 2 + 20
	));
	
	int counter = 1;

	for (int i = 0; i < LEVELS_COUNT; i++) {
		for (int j = 0; j < LEVELS_COUNT; j++) {
			levels_number_t[i][j].setFillColor(dark_green_c);
			levels_number_t[i][j].setFont(main_font);
			levels_number_t[i][j].setString(std::to_string(counter));
			counter++;
			levels_number_t[i][j].setCharacterSize(32);
			sf::FloatRect textBounds = levels_number_t[i][j].getLocalBounds();
			sf::Vector2f buttonPos = rs_levels[i][j].getPosition();
			sf::Vector2f buttonSize = rs_levels[i][j].getSize();

			levels_number_t[i][j].setOrigin(textBounds.width / 2, textBounds.height / 2);
			levels_number_t[i][j].setPosition(
				buttonPos.x + buttonSize.x / 2,
				buttonPos.y + buttonSize.y / 2.5
			);
		}

	}
}
void Game::initMusic()
{
	main_menu_music.openFromFile("music//people.mp3");
	main_menu_music.setLoop(true);
	main_menu_music.play();

	button_click.loadFromFile("music//button_click.mp3");
	menu_sounds.setBuffer(button_click);
}

Game::~Game()
{
	delete window;
	for (int i = 0; i < LEVELS_COUNT; ++i) {
		delete[] rs_levels[i];
	}
	delete[] rs_levels;
}

const bool Game::getWindowIsOpen() const
{
	return window->isOpen();
}

void Game::pollEvents()
{

	while (window->pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed: {
			window->close();
			break;
		}
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape) {
				window->close();
			}
			break;

		case sf::Event::MouseButtonPressed:
			switch (view) {
			case View::MAIN_SCREEN:
				if (ev.mouseButton.button == sf::Mouse::Left) {
					clickOnButtonsInMainScreen();
				}
				break;

			case View::SETTING_WINDOW:
				if (ev.mouseButton.button == sf::Mouse::Left) {
					clickOnSettingWindow();
				}
				break;
			case View::LEVELS_WINDOW:
				if (ev.mouseButton.button == sf::Mouse::Left) {
					clickOnLevelsWindow();
				}
				break;
			}
		}
		


	}
}



void Game::update()
{
	updateButtonsHover();
	pollEvents();
}

void Game::updateMousePosition()
{
	mouseWindowPosition = sf::Mouse::getPosition(*window);
	mouseWindowPositionView = window->mapPixelToCoords(mouseWindowPosition);

	std::string crd = std::to_string(mouseWindowPositionView.x) + "      " + std::to_string(mouseWindowPositionView.y) + "\n";
	coords_t.setString(crd);
}



void Game::updateButtonsHover()
{
	updateMousePosition();
	sf::Vector2f mouse_coords = mouseWindowPositionView;
	switch (view)
	{
	case MAIN_SCREEN:
		updateButtonHoverState(rs_startgame_button, &t_strartgame_button, &t_strartgame_button_l, mouse_coords);
		updateButtonHoverState(rs_setting_button, &t_setting_button, &t_setting_button_l, mouse_coords);
		updateButtonHoverState(rs_exit_button, &t_exit_button, &t_exit_button_l, mouse_coords);
		break;
	case SETTING_WINDOW:
		updateButtonHoverState(rs_ok_button, &t_ok_button, &t_ok_button_l, mouse_coords);
		break;
	case LEVELS_WINDOW:
		updateButtonHoverState(rs_exit_levels_button, &t_exit_button, &t_exit_button_l, mouse_coords);
		for (int i = 0; i < LEVELS_COUNT; i++) {
			for (int j = 0; j < LEVELS_COUNT; j++) {
				if (updateButtonHoverState(rs_levels[i][j], &t_button_back, &t_button_back_l, mouse_coords)) {
					levels_number_t[i][j].setFillColor(light_green_c);
				}
				else {
					levels_number_t[i][j].setFillColor(dark_green_c);

				}
			}
		}
		break;
	default:
		break;
	}
	
}

bool Game::coordsInRectangle(sf::Vector2f coords, sf::Vector2f topLeft, sf::Vector2f topRight, sf::Vector2f bottomLeft, sf::Vector2f bottomRight)
{
	return (coords.x >= topLeft.x && coords.x <= topRight.x &&
		coords.y >= topLeft.y && coords.y <= bottomLeft.y);
}

bool Game::updateButtonHoverState(sf::RectangleShape& button, sf::Texture* normalTexture, sf::Texture* hoverTexture, const sf::Vector2f& mouseCoords) {
	sf::FloatRect bounds = button.getGlobalBounds();

	if (coordsInRectangle(mouseCoords,
		{ bounds.left, bounds.top },
		{ bounds.left + bounds.width, bounds.top },
		{ bounds.left, bounds.top + bounds.height },
		{ bounds.left + bounds.width, bounds.top + bounds.height })) {
		button.setTexture(hoverTexture);
		return true;
	}
	else {
		button.setTexture(normalTexture);
	}
	return false;
}
bool Game::coordsInButton(const sf::Vector2f& coords, const sf::FloatRect& bounds) {
	return (coords.x >= bounds.left && coords.x <= bounds.left + bounds.width &&
		coords.y >= bounds.top && coords.y <= bounds.top + bounds.height);
}

void Game::clickOnButtonsInMainScreen() {
	updateMousePosition();
	sf::FloatRect start_bounds = rs_startgame_button.getGlobalBounds();
	sf::FloatRect setting_bounds = rs_setting_button.getGlobalBounds();
	sf::FloatRect exit_bounds = rs_exit_button.getGlobalBounds();

	if (coordsInButton(mouseWindowPositionView, start_bounds)) {
		view = View::LEVELS_WINDOW;
		menu_sounds.play();
	}
	else if (coordsInButton(mouseWindowPositionView, setting_bounds)) {
		view = View::SETTING_WINDOW;
		menu_sounds.play();

	}
	else if (coordsInButton(mouseWindowPositionView, exit_bounds)) {
		window->close();
		menu_sounds.play();

	}
}

void Game::clickOnSettingWindow() {
	updateMousePosition();
	sf::FloatRect ok_bounds = rs_ok_button.getGlobalBounds();
	sf::FloatRect m_slider_bounds = rs_music_slider.getGlobalBounds();
	sf::FloatRect m_setting_bounds = rs_music_volume_settings.getGlobalBounds();
	m_setting_bounds.height += m_setting_bounds.height * 0.3;
	sf::FloatRect s_slider_bounds = rs_sounds_slider.getGlobalBounds();
	sf::FloatRect s_setting_bounds = rs_sounds_volume_settings.getGlobalBounds();
	s_setting_bounds.height += s_setting_bounds.height * 0.3;


	int range_min = rs_music_volume_settings.getPosition().x - rs_music_volume_settings.getLocalBounds().width / 2;
	int range_max = rs_music_volume_settings.getPosition().x + rs_music_volume_settings.getLocalBounds().width / 2;

	double one_percentage_of_loud = (range_max - range_min )/ 100;

	if (coordsInButton(mouseWindowPositionView, ok_bounds)) {
		view = View::MAIN_SCREEN;
		menu_sounds.play();

	}
	else if (coordsInButton(mouseWindowPositionView, m_slider_bounds)) {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && coordsInButton(mouseWindowPositionView, m_setting_bounds)) {
			updateMousePosition();
			rs_music_slider.setPosition(sf::Vector2f(mouseWindowPositionView.x, rs_music_slider.getPosition().y));
			double curr_loud = (rs_music_slider.getPosition().x - range_min) / one_percentage_of_loud;
			main_menu_music.setVolume(curr_loud);
			render();
		}
	}
	else if (coordsInButton(mouseWindowPositionView, s_slider_bounds)) {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && coordsInButton(mouseWindowPositionView, s_setting_bounds)) {
			updateMousePosition();
			rs_sounds_slider.setPosition(sf::Vector2f(mouseWindowPositionView.x, rs_sounds_slider.getPosition().y));
			double curr_loud = (rs_sounds_slider.getPosition().x - range_min) / one_percentage_of_loud;
			menu_sounds.setVolume(curr_loud);
			render();
		}
		menu_sounds.play();
	}
}
void Game::clickOnLevelsWindow()
{
	updateMousePosition();
	sf::FloatRect exit_bounds = rs_exit_levels_button.getGlobalBounds();

	if (coordsInButton(mouseWindowPositionView, exit_bounds)) {
		view = View::MAIN_SCREEN;
		menu_sounds.play();
		return;
	}

	for (int i = 0; i < LEVELS_COUNT; i++) {
		for (int j = 0; j < LEVELS_COUNT; j++) {
			sf::FloatRect level_bounds = rs_levels[i][j].getGlobalBounds();
			if (coordsInButton(mouseWindowPositionView, level_bounds)) {
				int level_number = i * LEVELS_COUNT + j + 1; 
				switch (level_number) {
				case 1: {
					main_menu_music.pause();
					saper::run();
					main_menu_music.play();
					break;
				}
				case 2: {
					startRevoGame();
					break; }
				case 3:
					startBasementGame();
					break;
				case 4:
					startTetrysGame();
					break;
				case 5:
					startSaveAFriendGame();
					break;
				case 6:
					// Action for level 6
					// e.g., startLevel(6);
					break;
				case 7:
					// Action for level 7
					// e.g., startLevel(7);
					break;
				case 8:
					// Action for level 8
					// e.g., startLevel(8);
					break;
				case 9:
					// Action for level 9
					// e.g., startLevel(9);
					break;
				case 10:
					// Action for level 10
					// e.g., startLevel(10);
					break;
				case 11:
					// Action for level 11
					// e.g., startLevel(11);
					break;
				case 12:
					// Action for level 12
					// e.g., startLevel(12);
					break;
				case 13:
					// Action for level 13
					// e.g., startLevel(13);
					break;
				case 14:
					// Action for level 14
					// e.g., startLevel(14);
					break;
				case 15:
					// Action for level 15
					// e.g., startLevel(15);
					break;
				case 16:
					// Action for level 16
					// e.g., startLevel(16);
					break;
				}
				menu_sounds.play();
				return;
			}
		}
	}
}

void Game::startBasementGame()
{
	main_menu_music.pause();
	BasementGame game;
	while (game.getWindowIsOpen()) {
		game.update();
		game.render();
	}
	main_menu_music.play();

}

void Game::startTetrysGame()
{
	main_menu_music.pause();
	TetrysGame game;
	while (game.getWindowIsOpen()) {
		game.update();
		game.render();
	}
	main_menu_music.play();
}

void Game::startSaveAFriendGame()
{
	main_menu_music.pause();

	SafeAFriend game;
	while (game.getWindowIsOpen()) {
		sf::Clock deltaTime;
		game.update(deltaTime.restart());
		game.render();
	}
	main_menu_music.play();
}

void Game::startRevoGame()
{
	main_menu_music.pause();

	RevoGame game;
	while (game.getWindowIsOpen()) {
		game.update();
		game.render();
	}
	main_menu_music.play();

}



void Game::renderMainScreen() {
	window->draw(rs_main_screen_background);
	window->draw(rs_game_name);
	window->draw(rs_exit_button);
	window->draw(rs_setting_button);
	window->draw(rs_startgame_button);
}

void Game::renderSettingWindow()
{
	window->clear();
	window->draw(rs_main_screen_background);
	window->draw(rs_setting_window_bg);
	window->draw(rs_ok_button);
	window->draw(rs_music_volume_settings);
	window->draw(rs_sounds_volume_settings);
	window->draw(rs_music_slider);
	window->draw(rs_sounds_slider);
}

void Game::renderLevelsWindow()
{
	window->clear();
	window->draw(rs_main_screen_background);
	window->draw(rs_levels_window);

	for (int i = 0; i < LEVELS_COUNT; i++) {
		for (int j = 0; j < LEVELS_COUNT; j++) {
			window->draw(rs_levels[i][j]);
			window->draw(levels_number_t[i][j]);
		}

	}
	window->draw(coords_t);
	window->draw(levels_t);
	window->draw(rs_exit_levels_button);
}



void Game::render()
{
	window->clear();
	switch (view) {
	case MAIN_SCREEN:
	{
		renderMainScreen();
		break;
	}
	case SETTING_WINDOW:
	{
		renderSettingWindow();
		break;
	}
	case LEVELS_WINDOW:
		renderLevelsWindow();
		break;
	}
	window->display();
}
