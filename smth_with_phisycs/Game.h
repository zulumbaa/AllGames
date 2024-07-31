#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>

#include <fstream>
#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <string>

#include "Saper.h"
#include "RevoGame.h"
#include "BasementGame.h"
#include "Tetrys.h"





enum View {
	MAIN_SCREEN,
	SETTING_WINDOW,
	LEVELS_WINDOW
};


class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	sf::Vector2i mouseWindowPosition;
	sf::Vector2f mouseWindowPositionView;

	

	View view;
	sf::Font main_font;
	sf::Text coords_t, levels_t;
	sf::Text** levels_number_t;
	sf::Color dark_green_c = sf::Color::Color(52, 74, 44);
	sf::Color light_green_c = sf::Color::Color(140, 188, 36);
	static const int LEVELS_COUNT = 4;


	sf::RectangleShape rs_main_screen_background, rs_game_name, rs_startgame_button, rs_setting_button, rs_exit_button,
		rs_setting_window_bg, rs_ok_button, rs_music_volume_settings, rs_sounds_volume_settings, rs_music_slider, rs_sounds_slider,rs_levels_window, rs_exit_levels_button;
	
	sf::RectangleShape** rs_levels;

	sf::Texture t_main_screen_background, t_game_name_button, t_strartgame_button, t_setting_button,
		t_exit_button, t_game_name, t_strartgame_button_l, t_setting_button_l, t_exit_button_l, t_setting_window_bg,
		t_ok_button, t_ok_button_l, t_music_volume_settings, t_sounds_volume_settings, t_slider, t_levels_window, t_button_back, t_button_back_l;


	sf::Music main_menu_music;

	sf::Sound menu_sounds;
	sf::SoundBuffer button_click;

	void initVariables();
	void initWindow();
	void initPhotos();
	void initButtons();
	void initMusic();
	void initLevels();
	void initText();


public:
	Game();
	virtual ~Game();

	const bool getWindowIsOpen() const;
	void pollEvents();

	void update();
	void updateMousePosition();
	void updateButtonsHover();
	bool coordsInRectangle(sf::Vector2f coords, sf::Vector2f topLeft, sf::Vector2f topRight, sf::Vector2f bottomLeft, sf::Vector2f bottomRight);
	bool coordsInButton(const sf::Vector2f& coords, const sf::FloatRect& bounds);
	bool updateButtonHoverState(sf::RectangleShape& button, sf::Texture* normalTexture, sf::Texture* hoverTexture, const sf::Vector2f& mouseCoords);
	void clickOnButtonsInMainScreen();
	void clickOnSettingWindow();
	void clickOnLevelsWindow();
	void startRevoGame();
	void startBasementGame();
	void startTetrysGame();
	
	
	void render();
	void renderMainScreen();
	void renderSettingWindow();
	void renderLevelsWindow();

};

