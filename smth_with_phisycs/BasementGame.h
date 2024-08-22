#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <fstream>
#include <iostream>
#include <cstdlib> 
#include <ctime> 


enum class Views {
	NORTH_WALL,
	SOUTH_WALL,
	WEST_WALL,
	EAST_WALL,
	WINDOW,
	CARROT,
	BEET,
	BUCKETS,
	NOTE_FOUND,
	JARS,
	DOOR,
	LEAVING,
	LOSE

};

class BasementGame
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;



	sf::Vector2i mouseWindowPosition;
	sf::Vector2f mouseWindowPositionView;



	Views view;
	Views currentWallView;

	sf::Clock clock;

	sf::Texture north_wall_texture, south_wall_texture, west_wall_texture, east_wall_texture;
	sf::RectangleShape north_wall, south_wall, west_wall, east_wall;

	sf::Texture beet_texture, buckets_texture, carrots_1_texture, carrots_2_texture, carrots_3_texture,
		carrots_4_texture, door_texture, door_opening_texture, jar_found_texture, jar_opening_1_texture,
		jar_opening_2_texture, jars_texture, key_found_texture, note_found_texture, note_texture, opener_found_texture, window_texture;

	sf::Texture stairs_texture, dog_texture, lose_run_0_texture, lose_run_1_texture, lose_run_2_texture, lose_run_3_texture,
		win_run_0_texture, win_run_1_texture, win_run_2_texture, win_run_3_texture, win_run_4_texture, win_run_5_texture, win_run_6_texture, lose_texture;

	sf::RectangleShape beet, buckets, carrots, door, jars, opener_found, window_, note_found, leaving, lose;

	sf::Music soundtrack;

	sf::Font textFont;
	sf::Text Text;

	sf::Sound voise, sound, breathing;

	sf::SoundBuffer sbOpener, sbBuckets, sbNoteFound, sbNoteReading,
		sbDoorOpening, sbJarFound, sbNoOpener, sbLidLooking, sbJarLooking,
		sbLeft, sbStraight, sbLeftOrStraight, sbFance, sbBreathing;

	sf::SoundBuffer sbFirstWord[3];
	sf::SoundBuffer sbPotatoBox[3];
	sf::SoundBuffer sbWindow[3];
	sf::SoundBuffer sbBeetBox[3];
	sf::SoundBuffer sbCarrotBox[3];
	sf::SoundBuffer sbNote[3];
	sf::SoundBuffer sbDoorClosed[3];
	sf::SoundBuffer sbJars[3];
	sf::SoundBuffer sbBoxes[3];
	sf::SoundBuffer sbRedJars[3];
	sf::SoundBuffer sbEmptyJars[3];
	sf::SoundBuffer sbOtherJars[3];
	sf::SoundBuffer sbCarrotSearching[3];
	sf::SoundBuffer sbJarsKnock[3];
	sf::SoundBuffer sbLeftRun[3];


	sf::SoundBuffer sbNoteOpening, sbWindowKnock, sbBasementDoorOpening,
		sbLoseDoorOpening, sbLoseFanceOpening, sbWinFanceOpening, sbLoseRun,
		sbStairsRun, sbWinRun, sbJarBreaking, sbGav, sbJarOpening;




	int carrots_click_counter = 0;
	bool is_opener_found = false;
	bool is_note_found_first = false;
	bool is_note_found = false;
	bool is_jar_found = false;
	bool is_key_found = false;
	bool is_lose = false;
	bool is_leaving = false;


	void initVariables();
	void initWindow();
	void initWalls();
	void initNorthWall();
	void initSouthWall();
	void initWestWall();
	void initEastWall();
	void initMusic();
	void initOtherPhotosInBasement();
	void initText();
	void initVoises();
	void initSounds();

	bool isViewNotInWall();
	void changeWallView(sf::Keyboard::Key key);
	void returnToWallView();

	bool coordsInRectangle(sf::Vector2i, sf::Vector2i, sf::Vector2i, sf::Vector2i, sf::Vector2i);
	void playRandomSound(sf::SoundBuffer[], int);
	void downloadArrayOfSounds(sf::SoundBuffer*, std::string, int);
	void clockWaiting(int sec);
	int clockAndCklickWaiting(sf::Keyboard::Key key1, sf::Keyboard::Key key2, int sec);

	void searchingInNorthWall(sf::Vector2i);
	void searchingInSouthWall(sf::Vector2i);
	void searchingInWestWall(sf::Vector2i);
	void searchingInEastWall(sf::Vector2i);

	void searchingInWindow(sf::Vector2i);
	void searchingInCarrots(sf::Vector2i);
	void searchingInBuckets(sf::Vector2i);
	void openNote();
	void searchingInDoor(sf::Vector2i);
	void searchingInJars(sf::Vector2i);

	void loseText(std::string text);
	void loseDuringRunning(std::string text);

	void leavingProcess();

public:
	BasementGame();
	virtual ~BasementGame();

	const bool getWindowIsOpen() const;
	void pollEvents();
	void updateMousePosition();
	void updateView();
	void update();

	void renderNorthWall();
	void renderSouthWall();
	void renderWestWall();
	void renderEastWall();

	void render();

};

