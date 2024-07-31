#include "BasementGame.h"

void BasementGame::initVariables()
{
	view = Views::NORTH_WALL;


}

void BasementGame::initWindow()
{
	videoMode = sf::VideoMode::getFullscreenModes()[0];
	window = new sf::RenderWindow(videoMode, "Escape from the basement", sf::Style::Default);
	window->setFramerateLimit(144);
}

void BasementGame::initWalls()
{
	initNorthWall();
	initSouthWall();
	initWestWall();
	initEastWall();
}

void BasementGame::initNorthWall()
{
	north_wall.setSize(sf::Vector2f(videoMode.width, videoMode.height));

	if (!north_wall_texture.loadFromFile("other//basement//photos//north.jpeg"))
	{
		throw "Error reading image 'wall texture'";
	}
	north_wall.setTexture(&north_wall_texture);

}

void BasementGame::initEastWall()
{
	east_wall.setSize(sf::Vector2f(videoMode.width, videoMode.height));
	if (!east_wall_texture.loadFromFile("other//basement//photos//east.jpeg"))
	{
		throw "Error reading image 'wall texture'";
	}
	east_wall.setTexture(&east_wall_texture);

}

void BasementGame::initSouthWall()
{
	south_wall.setSize(sf::Vector2f(videoMode.width, videoMode.height));
	if (!south_wall_texture.loadFromFile("other//basement//photos//south.jpeg"))
	{
		throw "Error reading image 'wall texture'";
	}
	south_wall.setTexture(&south_wall_texture);

}

void BasementGame::initWestWall()
{
	west_wall.setSize(sf::Vector2f(videoMode.width, videoMode.height));
	if (!west_wall_texture.loadFromFile("other//basement//photos//west.jpeg"))
	{
		throw "Error reading image 'wall texture'";
	}
	west_wall.setTexture(&west_wall_texture);

}

void BasementGame::changeWallView(sf::Keyboard::Key key) {
	switch (key) {
	case sf::Keyboard::D:
		switch (view) {
		case Views::NORTH_WALL:
			view = Views::EAST_WALL;
			break;
		case Views::EAST_WALL:
			view = Views::SOUTH_WALL;
			break;
		case Views::SOUTH_WALL:
			view = Views::WEST_WALL;
			break;
		case Views::WEST_WALL:
			view = Views::NORTH_WALL;
			break;
		default:
			break;
		}
		break;
	case sf::Keyboard::A:
		switch (view) {
		case Views::NORTH_WALL:
			view = Views::WEST_WALL;
			break;
		case Views::WEST_WALL:
			view = Views::SOUTH_WALL;
			break;
		case Views::SOUTH_WALL:
			view = Views::EAST_WALL;
			break;
		case Views::EAST_WALL:
			view = Views::NORTH_WALL;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

bool BasementGame::isViewNotInWall() {
	return view != Views::NORTH_WALL || view != Views::EAST_WALL || view != Views::SOUTH_WALL || view != Views::WEST_WALL;
}

void BasementGame::returnToWallView() {

	view = currentWallView;
}


BasementGame::BasementGame()
{
	initWindow();
	initVariables();
	initWalls();
	initMusic();
	initOtherPhotosInBasement();
	initVoises();
	initSounds();
	soundtrack.play();
	playRandomSound(sbFirstWord, 3);
	initText();


}

BasementGame::~BasementGame()
{
	delete window;
}

const bool BasementGame::getWindowIsOpen() const
{
	return window->isOpen();
}

void BasementGame::pollEvents()
{
	sf::Keyboard::Key keyPressed;

	while (window->pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (!is_leaving) {
				keyPressed = ev.key.code;
				switch (keyPressed) {
				case sf::Keyboard::D:
				case sf::Keyboard::A:
					changeWallView(keyPressed);
					break;
				case sf::Keyboard::S:
					if (isViewNotInWall()) {
						returnToWallView();
					}
					break;
				default:
					break;
				}
				break;
			}

			else {
				break;
			}

		case sf::Event::MouseButtonPressed: {
			if (!is_leaving && ev.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i coords = mouseWindowPosition;
				switch (view) {
				case Views::NORTH_WALL:
					searchingInNorthWall(coords);
					break;
				case Views::WEST_WALL:
					searchingInWestWall(coords);
					break;
				case Views::SOUTH_WALL:
					searchingInSouthWall(coords);
					break;
				case Views::EAST_WALL:
					searchingInEastWall(coords);
					break;
				case Views::WINDOW:
					searchingInWindow(coords);
					break;
				case Views::CARROT:
					searchingInCarrots(coords);
					break;
				case Views::BUCKETS:
					searchingInBuckets(coords);
					break;
				case Views::JARS:
					searchingInJars(coords);
					break;
				case Views::NOTE_FOUND:
					openNote();
					break;
				case Views::DOOR:
					searchingInDoor(coords);
					break;
				default:
					break;
				}
			}
			break;
		}
		}
	}
}


void BasementGame::updateMousePosition()
{
	mouseWindowPosition = sf::Mouse::getPosition(*window);
	mouseWindowPositionView = window->mapPixelToCoords(mouseWindowPosition);

	std::string crd = std::to_string(mouseWindowPositionView.x) + "      " + std::to_string(mouseWindowPositionView.y) + "\n";
	std::cout << crd;
}


void BasementGame::updateView() {
	switch (view) {
	case Views::NORTH_WALL:
		renderNorthWall();
		break;
	case Views::SOUTH_WALL:
		renderSouthWall();
		break;
	case Views::WEST_WALL:
		renderWestWall();
		break;
	case Views::EAST_WALL:
		renderEastWall();
		break;
	case Views::WINDOW:
		window->draw(window_);
		break;
	case Views::BEET:
		window->draw(beet);
		break;
	case Views::CARROT:
		window->draw(carrots);
		break;
	case Views::BUCKETS:
		window->draw(buckets);
		break;
	case Views::NOTE_FOUND:
		window->draw(note_found);
		break;
	case Views::JARS:
		window->draw(jars);
		break;
	case Views::DOOR:
		window->draw(door);
		break;
	case Views::LEAVING:
		window->draw(leaving);
		break;
	case Views::LOSE:
		window->draw(lose);
		loseText(Text.getString());
		break;
	default:
		break;
	}
}



void BasementGame::update()
{
	pollEvents();
	updateMousePosition();
	updateView();
}

void BasementGame::renderNorthWall()
{
	window->draw(north_wall);
}

void BasementGame::initMusic()
{
	if (!soundtrack.openFromFile("other//basement//background_music.wav")) {
		throw "Error reading sound 'music'";
	}

	soundtrack.setVolume(50.f);
	soundtrack.setLoop(true);
}

void BasementGame::renderSouthWall()
{
	window->draw(south_wall);

}

void BasementGame::renderWestWall()
{
	window->draw(west_wall);
}

void BasementGame::renderEastWall()
{
	window->draw(east_wall);

}

void BasementGame::initOtherPhotosInBasement()
{
	// Beet
	beet.setSize(sf::Vector2f(videoMode.width, videoMode.height));
	beet_texture.loadFromFile("other//basement//photos//beet.jpeg");
	beet.setTexture(&beet_texture);

	// Buckets
	buckets.setSize(sf::Vector2f(videoMode.width, videoMode.height));
	buckets_texture.loadFromFile("other//basement//photos//buckets.jpeg");
	buckets.setTexture(&buckets_texture);

	//Note
	note_found.setSize(sf::Vector2f(videoMode.width, videoMode.height));
	note_found_texture.loadFromFile("other//basement//photos//note_found.jpeg");
	note_found.setTexture(&note_found_texture);
	note_texture.loadFromFile("other//basement//photos//note1.jpeg");

	// Carrots
	carrots.setSize(sf::Vector2f(videoMode.width, videoMode.height));
	carrots_1_texture.loadFromFile("other//basement//photos//carrots_1.jpeg");
	carrots_2_texture.loadFromFile("other//basement//photos//carrots_2.jpeg");
	carrots_3_texture.loadFromFile("other//basement//photos//carrots_3.jpeg");
	carrots_4_texture.loadFromFile("other//basement//photos//carrots_4.jpeg");

	carrots.setTexture(&carrots_1_texture);

	// Door
	door.setSize(sf::Vector2f(videoMode.width, videoMode.height));
	door_texture.loadFromFile("other//basement//photos//door.jpeg");
	door.setTexture(&door_texture);

	// Door Opening
	leaving.setSize(sf::Vector2f(videoMode.width, videoMode.height));
	door_opening_texture.loadFromFile("other//basement//photos//door_opening.jpeg");
	leaving.setTexture(&door_opening_texture);


	// Jars
	jars.setSize(sf::Vector2f(videoMode.width, videoMode.height));
	jars_texture.loadFromFile("other//basement//photos//jars.jpeg");
	jar_found_texture.loadFromFile("other//basement//photos//jar_found.jpeg");
	jar_opening_1_texture.loadFromFile("other//basement//photos//jar_opening_1.jpeg");
	jar_opening_2_texture.loadFromFile("other//basement//photos//jar_opening_2.jpeg");
	key_found_texture.loadFromFile("other//basement//photos//key_found.jpeg");
	jars.setTexture(&jars_texture);



	// Opener Found
	opener_found.setSize(sf::Vector2f(videoMode.width, videoMode.height));
	opener_found_texture.loadFromFile("other//basement//photos//opener_found.jpeg");
	opener_found.setTexture(&opener_found_texture);

	//window
	window_.setSize(sf::Vector2f(videoMode.width, videoMode.height));
	window_texture.loadFromFile("other//basement//photos//window.jpeg");
	window_.setTexture(&window_texture);

	//leaving
	stairs_texture.loadFromFile("other//basement//photos//stairs.jpeg");
	dog_texture.loadFromFile("other//basement//photos//dog.jpeg");
	lose_run_0_texture.loadFromFile("other//basement//photos//lose_run_0.jpeg");
	lose_run_1_texture.loadFromFile("other//basement//photos//lose_run_1.jpeg");
	lose_run_2_texture.loadFromFile("other//basement//photos//lose_run_2.jpeg");
	lose_run_3_texture.loadFromFile("other//basement//photos//lose_run_3.jpeg");
	win_run_0_texture.loadFromFile("other//basement//photos//win_run_0.jpeg");
	win_run_1_texture.loadFromFile("other//basement//photos//win_run_1.jpeg");
	win_run_2_texture.loadFromFile("other//basement//photos//win_run_2.jpeg");
	win_run_3_texture.loadFromFile("other//basement//photos//win_run_3.jpeg");
	win_run_4_texture.loadFromFile("other//basement//photos//win_run_4.jpeg");
	win_run_5_texture.loadFromFile("other//basement//photos//win_run_5.jpeg");
	win_run_6_texture.loadFromFile("other//basement//photos//win_run_6.jpeg");

	//lose
	lose.setSize(sf::Vector2f(videoMode.width, videoMode.height));
	lose_texture.loadFromFile("other//basement//photos//lose.jpg");
	lose.setTexture(&lose_texture);

}




void BasementGame::render()
{
	window->clear();
	updateView();
	window->draw(Text);
	window->display();
}



void BasementGame::searchingInEastWall(sf::Vector2i coords)
{
	sf::Vector2i windowTopLeft(1000, 100);
	sf::Vector2i windowTopRight(1850, 70);
	sf::Vector2i windowBottomLeft(1000, 390);
	sf::Vector2i windowBottomRight(1850, 334);

	sf::Vector2i carrotTopLeft(1270, 800);
	sf::Vector2i carrotTopRight(1700, 800);
	sf::Vector2i carrotBottomLeft(1270, 980);
	sf::Vector2i carrotBottomRight(1700, 980);

	sf::Vector2i beetTopLeft(870, 740);
	sf::Vector2i beetTopRight(1250, 740);
	sf::Vector2i beetBottomLeft(870, 970);
	sf::Vector2i beetBottomRight(1250, 970);

	sf::Vector2i potatoTopLeft(250, 730);
	sf::Vector2i potatoTopRight(670, 730);
	sf::Vector2i potatoBottomLeft(250, 920);
	sf::Vector2i potatoBottomRight(670, 920);

	if (coordsInRectangle(coords, windowTopLeft, windowTopRight, windowBottomLeft, windowBottomRight)) {
		view = Views::WINDOW;
		currentWallView = Views::EAST_WALL;
	}
	if (coordsInRectangle(coords, carrotTopLeft, carrotTopRight, carrotBottomLeft, carrotBottomRight)) {
		view = Views::CARROT;
		currentWallView = Views::EAST_WALL;
		if (!is_opener_found) {
			playRandomSound(sbCarrotBox, 3);
		}
	}
	if (coordsInRectangle(coords, beetTopLeft, beetTopRight, beetBottomLeft, beetBottomRight)) {
		view = Views::BEET;
		currentWallView = Views::EAST_WALL;
		playRandomSound(sbBeetBox, 3);
	}
	if (coordsInRectangle(coords, potatoTopLeft, potatoTopRight, potatoBottomLeft, potatoBottomRight)) {
		playRandomSound(sbPotatoBox, 3);
	}
}

void BasementGame::searchingInWindow(sf::Vector2i coords)
{

	sf::Vector2i windowTopLeft(260, 350);
	sf::Vector2i windowTopRight(1900, 350);
	sf::Vector2i windowBottomLeft(260, 860);
	sf::Vector2i windowBottomRight(1900, 860);

	if (coordsInRectangle(coords, windowTopLeft, windowTopRight, windowBottomLeft, windowBottomRight)) {
		playRandomSound(sbWindow, 3);
		sound.setBuffer(sbWindowKnock);
		sound.play();
	}

}

void BasementGame::searchingInCarrots(sf::Vector2i coords)
{

	sf::Vector2i Carrot1TopLeft(1193, 885);
	sf::Vector2i Carrot1TopRight(1523, 885);
	sf::Vector2i Carrot1BottomLeft(1193, 950);
	sf::Vector2i Carrot1BottomRight(1523, 950);

	sf::Vector2i Carrot2TopLeft(1450, 790);
	sf::Vector2i Carrot2TopRight(1640, 790);
	sf::Vector2i Carrot2BottomLeft(1450, 920);
	sf::Vector2i Carrot2BottomRight(1640, 920);

	sf::Vector2i Carrot3TopLeft(1250, 544);
	sf::Vector2i Carrot3TopRight(1330, 544);
	sf::Vector2i Carrot3BottomLeft(1250, 660);
	sf::Vector2i Carrot3BottomRight(1330, 660);

	sf::Vector2i OpenerTopLeft(1283, 614);
	sf::Vector2i OpenerTopRight(1365, 614);
	sf::Vector2i OpenerBottomLeft(1283, 660);
	sf::Vector2i OpenerBottomRight(1365, 660);


	if (carrots_click_counter == 0 && coordsInRectangle(coords, Carrot1TopLeft, Carrot1TopRight, Carrot1BottomLeft, Carrot1BottomRight)) {
		carrots.setTexture(&carrots_2_texture);
		carrots_click_counter = 1;
		sound.setBuffer(sbCarrotSearching[0]);
		sound.play();
	}
	if (carrots_click_counter == 1 && coordsInRectangle(coords, Carrot2TopLeft, Carrot2TopRight, Carrot2BottomLeft, Carrot2BottomRight)) {
		carrots.setTexture(&carrots_3_texture);
		carrots_click_counter = 2;
		sound.setBuffer(sbCarrotSearching[1]);
		sound.play();
	}
	if (carrots_click_counter == 2 && coordsInRectangle(coords, Carrot3TopLeft, Carrot3TopRight, Carrot3BottomLeft, Carrot3BottomRight)) {
		carrots.setTexture(&carrots_4_texture);
		carrots_click_counter = 3;
		sound.setBuffer(sbCarrotSearching[2]);
		sound.play();
	}
	if (carrots_click_counter == 3 && coordsInRectangle(coords, OpenerTopLeft, OpenerTopRight, OpenerBottomLeft, OpenerBottomRight)) {
		carrots.setTexture(&opener_found_texture);
		carrots_click_counter = 4;
		voise.setBuffer(sbOpener);
		voise.play();
		is_opener_found = true;
	}
}



void BasementGame::searchingInNorthWall(sf::Vector2i coords)
{
	sf::Vector2i BucketsTopLeft(1200, 820);
	sf::Vector2i BucketsTopRight(1300, 820);
	sf::Vector2i BucketsBottomLeft(1200, 970);
	sf::Vector2i BucketsBottomRight(1300, 970);


	if (coordsInRectangle(coords, BucketsTopLeft, BucketsTopRight, BucketsBottomRight, BucketsBottomRight)) {
		view = Views::BUCKETS;
		currentWallView = Views::NORTH_WALL;
		if (!is_note_found) {
			voise.setBuffer(sbBuckets);
			voise.play();
		}
		else {
			view = Views::NOTE_FOUND;
			currentWallView = Views::NORTH_WALL;
			note_found.setTexture(&note_found_texture);
		}
	}
}


void BasementGame::searchingInBuckets(sf::Vector2i coords)
{
	sf::Vector2i NoteTopLeft(880, 400);
	sf::Vector2i NoteTopRight(1030, 400);
	sf::Vector2i NoteBottomLeft(880, 500);
	sf::Vector2i NoteBottomRight(1030, 500);


	if (!is_note_found && coordsInRectangle(coords, NoteTopLeft, NoteTopRight, NoteBottomRight, NoteBottomRight)) {
		view = Views::NOTE_FOUND;
		currentWallView = Views::NORTH_WALL;
		note_found.setTexture(&note_found_texture);

		voise.setBuffer(sbNoteFound);
		voise.play();
		is_note_found = true;
		is_note_found_first = true;

	}
	else if (is_note_found) {
		view = Views::NOTE_FOUND;
		currentWallView = Views::NORTH_WALL;
		note_found.setTexture(&note_found_texture);
	}
}

void BasementGame::openNote()
{
	if (is_note_found_first) {
		note_found.setTexture(&note_texture);
		is_note_found_first = false;
		voise.setBuffer(sbNoteReading);
		voise.play();
		sound.setBuffer(sbNoteOpening);
		sound.play();


	}
	else if (is_note_found && !is_note_found_first) {
		note_found.setTexture(&note_texture);
		sound.setBuffer(sbNoteOpening);
		sound.play();
		playRandomSound(sbNote, 3);

	}
}

void BasementGame::searchingInWestWall(sf::Vector2i coords)
{
	sf::Vector2i jarsTopLeft(660, 200);
	sf::Vector2i jarsTopRight(1880, 200);
	sf::Vector2i jarsBottomLeft(660, 980);
	sf::Vector2i jarsBottomRight(1880, 980);

	sf::Vector2i boxesTopLeft(7, 400);
	sf::Vector2i boxesTopRight(600, 400);
	sf::Vector2i boxesBottomLeft(7, 990);
	sf::Vector2i boxesBottomRight(600, 990);

	if (coordsInRectangle(coords, jarsTopLeft, jarsTopRight, jarsBottomLeft, jarsBottomRight)) {

		view = Views::JARS;
		currentWallView = Views::WEST_WALL;
		if (!is_jar_found) {
			playRandomSound(sbJars, 3);
		}
		else {
			if (!is_opener_found) {
				voise.setBuffer(sbJarLooking);
				voise.play();
			}
		}
	}
	if (coordsInRectangle(coords, boxesTopLeft, boxesTopRight, boxesBottomLeft, boxesBottomRight)) {
		playRandomSound(sbBoxes, 3);
	}
}

void BasementGame::searchingInJars(sf::Vector2i coords)
{
	sf::Vector2i redTopLeft(40, 200);
	sf::Vector2i redTopRight(1900, 200);
	sf::Vector2i redBottomLeft(40, 420);
	sf::Vector2i redBottomRight(1900, 420);

	sf::Vector2i emptyTopLeft(205, 600);
	sf::Vector2i emptyTopRight(1300, 600);
	sf::Vector2i emptyBottomLeft(205, 880);
	sf::Vector2i emptyBottomRight(1300, 880);

	sf::Vector2i keyTopLeft(1330, 670);
	sf::Vector2i keyTopRight(1480, 670);
	sf::Vector2i keyBottomLeft(1330, 860);
	sf::Vector2i keyBottomRight(1480, 860);

	sf::Vector2i allEmptyTopLeft(1520, 520);
	sf::Vector2i allEmptyTopRight(1900, 520);
	sf::Vector2i allEmptyBottomLeft(1520, 850);
	sf::Vector2i allEmptyBottomRight(1900, 850);

	sf::Vector2i lidTopLeft(860, 200);
	sf::Vector2i lidTopRight(1390, 200);
	sf::Vector2i lidBottomLeft(860, 370);
	sf::Vector2i lidBottomRight(1390, 370);

	sf::Vector2i bankTopLeft(820, 430);
	sf::Vector2i bankTopRight(1480, 430);
	sf::Vector2i bankBottomLeft(820, 980);
	sf::Vector2i bankBottomRight(1480, 980);

	if (is_jar_found) {
		if (!is_key_found && (coordsInRectangle(coords, lidTopLeft, lidTopRight, lidBottomLeft, lidBottomRight) || (is_opener_found && coordsInRectangle(coords, bankTopLeft, bankTopRight, bankBottomLeft, bankBottomRight)))) {
			if (is_opener_found) {
				voise.stop();
				sound.setBuffer(sbJarOpening);
				sound.play();
				jars.setTexture(&jar_opening_1_texture);
				clockWaiting(1);
				jars.setTexture(&jar_opening_2_texture);
				clockWaiting(1);
				jars.setTexture(&key_found_texture);
				is_key_found = true;
				sound.stop();
			}
			else {
				voise.setBuffer(sbLidLooking);
				voise.play();
			}
		}
		if (!is_key_found && !is_opener_found && coordsInRectangle(coords, bankTopLeft, bankTopRight, bankBottomLeft, bankBottomRight)) {
			is_lose = true;
			view = Views::LOSE;
			currentWallView = Views::LOSE;
			loseText("You were heard..");
			sound.setBuffer(sbJarBreaking);
			sound.play();
		}
	}
	else {
		if (coordsInRectangle(coords, keyTopLeft, keyTopRight, keyBottomLeft, keyBottomRight)) {
			voise.setBuffer(sbJarFound);
			voise.play();
			jars.setTexture(&jar_found_texture);
			is_jar_found = true;

			clockWaiting(1);
			voise.setBuffer(sbJarLooking);
			voise.play();
		}
		if (coordsInRectangle(coords, redTopLeft, redTopRight, redBottomLeft, redBottomRight)) {
			playRandomSound(sbRedJars, 3);
			sound.setBuffer(sbJarsKnock[0]);
			sound.play();
		}
		if (coordsInRectangle(coords, emptyTopLeft, emptyTopRight, emptyBottomLeft, emptyBottomRight)) {
			playRandomSound(sbEmptyJars, 3);
			sound.setBuffer(sbJarsKnock[1]);
			sound.play();

		}
		if (coordsInRectangle(coords, allEmptyTopLeft, allEmptyTopRight, allEmptyBottomLeft, allEmptyBottomRight)) {
			playRandomSound(sbOtherJars, 3);
			sound.setBuffer(sbJarsKnock[2]);
			sound.play();

		}
	}


}

void BasementGame::loseText(std::string text = "You loose...")
{
	Text.setString(text);
	Text.setPosition(sf::Vector2f(1200, 850));
	Text.setCharacterSize(50);
	Text.setFillColor(sf::Color::White);

}

void BasementGame::loseDuringRunning(std::string text)
{
	is_leaving = false;
	is_lose = true;
	view = Views::LOSE;
	currentWallView = Views::LOSE;
	breathing.stop();
	soundtrack.stop();
	loseText(text);

}

void BasementGame::leavingProcess()
{
	soundtrack.openFromFile("other//basement//sounds//leaving.wav");
	soundtrack.play();
	soundtrack.setVolume(70);
	breathing.play();


	clockWaiting(1);
	leaving.setTexture(&stairs_texture);

	voise.setBuffer(sbLeftOrStraight);
	voise.play();

	Text.setCharacterSize(24);
	Text.setPosition(sf::Vector2f(700, 700));
	Text.setString("   RUN!!!!\nA - left\tW - straight");


	int choose = clockAndCklickWaiting(sf::Keyboard::A, sf::Keyboard::W, 5);
	if (choose == 1) {//win way
		Text.setString("");
		sound.setBuffer(sbStairsRun);
		sound.play();

		voise.setBuffer(sbStraight);
		voise.play();
		leaving.setTexture(&win_run_0_texture);
		choose = clockAndCklickWaiting(sf::Keyboard::W, sf::Keyboard::A, 2);
		if (choose == 1) {//no dog
			sound.setBuffer(sbLeftRun[0]);
			sound.play();

			leaving.setTexture(&win_run_1_texture);
			voise.setBuffer(sbLeft);
			voise.play();
			choose = clockAndCklickWaiting(sf::Keyboard::A, sf::Keyboard::A, 2);
			if (choose == 1 || choose == 2) {//left
				sound.setBuffer(sbLeftRun[1]);
				sound.play();

				leaving.setTexture(&win_run_2_texture);
				voise.setBuffer(sbStraight);
				voise.play();
				choose = clockAndCklickWaiting(sf::Keyboard::W, sf::Keyboard::W, 2);
				if (choose == 1 || choose == 2) {//straigth
					sound.setBuffer(sbLeftRun[2]);
					sound.play();

					leaving.setTexture(&win_run_3_texture);
					voise.setBuffer(sbFance);
					voise.play();
					choose = clockAndCklickWaiting(sf::Keyboard::W, sf::Keyboard::W, 3);
					if (choose == 1 || choose == 2) {//fance
						clockWaiting(1);
						leaving.setTexture(&win_run_4_texture);
						clockWaiting(1);

						sound.setBuffer(sbWinFanceOpening);
						sound.play();

						leaving.setTexture(&win_run_5_texture);
						sound.setBuffer(sbWinRun);
						sound.play();

						clockWaiting(1);
						leaving.setTexture(&win_run_6_texture);
						soundtrack.stop();
						breathing.stop();


					}
					else {
						loseDuringRunning("Too late...");
						return;
					}
				}
				else {
					loseDuringRunning("Too late...");
					return;
				}
			}
			else {
				loseDuringRunning("Too late...");
				return;
			}
		}
		else if (choose == 2) {//dog way
			leaving.setTexture(&dog_texture);
			render();
			voise.setBuffer(sbGav);
			voise.play();
			clockWaiting(1);
			loseDuringRunning("You have become food\nfor Jessica");
			return;
		}
		else {
			loseDuringRunning("Too late...");
			return;
		}
	}
	else if (choose == 2) {//lose way
		Text.setString("");
		sound.setBuffer(sbStairsRun);
		sound.play();

		voise.setBuffer(sbStraight);
		voise.play();
		leaving.setTexture(&lose_run_0_texture);
		choose = clockAndCklickWaiting(sf::Keyboard::W, sf::Keyboard::W, 2);
		if (choose == 1 || choose == 2) {
			sound.setBuffer(sbLoseRun);
			sound.play();

			voise.setBuffer(sbStraight);
			voise.play();
			leaving.setTexture(&lose_run_1_texture);
			choose = clockAndCklickWaiting(sf::Keyboard::W, sf::Keyboard::W, 2);
			if (choose == 1 || choose == 2) {
				sound.setBuffer(sbLoseFanceOpening);
				sound.play();
				leaving.setTexture(&lose_run_2_texture);

				clockWaiting(2);

				voise.setBuffer(sbLoseDoorOpening);
				voise.play();
				clockWaiting(1);

			}
			else {
				loseDuringRunning("Too late...");
				return;
			}
		}
		else {
			loseDuringRunning("Too late...");
			return;
		}
		loseDuringRunning("Unfortunately, closed");
		return;
	}
	else {
		loseDuringRunning("Too late...");
		return;
	}



}


void BasementGame::searchingInSouthWall(sf::Vector2i coords)
{

	sf::Vector2i doorTopLeft(900, 260);
	sf::Vector2i doorTopRight(1240, 260);
	sf::Vector2i doorBottomLeft(900, 920);
	sf::Vector2i doorBottomRight(1240, 920);

	if (coordsInRectangle(coords, doorTopLeft, doorTopRight, doorBottomLeft, doorBottomRight)) {
		view = Views::DOOR;
		currentWallView = Views::SOUTH_WALL;

	}
}



void BasementGame::searchingInDoor(sf::Vector2i coords)
{
	sf::Vector2i doorTopLeft(1445, 530);
	sf::Vector2i doorTopRight(1500, 530);
	sf::Vector2i doorBottomLeft(1455, 730);
	sf::Vector2i doorBottomRight(1500, 730);

	if (coordsInRectangle(coords, doorTopLeft, doorTopRight, doorBottomLeft, doorBottomRight)) {
		if (is_key_found) {
			view = Views::LEAVING;
			currentWallView = Views::LEAVING;
			voise.setBuffer(sbDoorOpening);
			voise.play();
			sound.setBuffer(sbBasementDoorOpening);
			sound.play();
			is_leaving = true;

			leavingProcess();

		}
		else {
			playRandomSound(sbDoorClosed, 3);
		}

	}
}


void BasementGame::playRandomSound(sf::SoundBuffer soundBufferArray[], int arraySize) {

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	int randomIndex = std::rand() % arraySize;

	voise.setBuffer(soundBufferArray[randomIndex]);
	voise.play();
}

void BasementGame::downloadArrayOfSounds(sf::SoundBuffer* sb, std::string filename_part, int numb_of_sounds)
{
	for (int i = 0; i < numb_of_sounds; i++) {
		std::string filename = "other//basement//sounds//" + filename_part + std::to_string(i) + ".wav";
		sb[i].loadFromFile(filename);
	}
}

void BasementGame::clockWaiting(int sec)
{
	render();
	clock.restart();
	while (clock.getElapsedTime().asSeconds() < sec) {
		continue;
	}
}

int BasementGame::clockAndCklickWaiting(sf::Keyboard::Key key1, sf::Keyboard::Key key2, int sec)
{
	render();
	clock.restart();

	while (clock.getElapsedTime().asSeconds() < sec)
	{
		if (sf::Keyboard::isKeyPressed(key1))
		{
			while (sf::Keyboard::isKeyPressed(key1)) {}
			return 1;
		}
		else if (sf::Keyboard::isKeyPressed(key2))
		{
			while (sf::Keyboard::isKeyPressed(key2)) {}
			return 2;
		}
	}

	return -1;
}



bool BasementGame::coordsInRectangle(sf::Vector2i coords, sf::Vector2i topLeft, sf::Vector2i topRight, sf::Vector2i bottomLeft, sf::Vector2i bottomRight)
{
	return (coords.x >= topLeft.x && coords.x <= topRight.x &&
		coords.y >= topLeft.y && coords.y <= bottomLeft.y);
}



void BasementGame::initText()
{
	if (!textFont.loadFromFile("other//basement//HelpMe.ttf"))
	{
		throw "Error reading font";
	}

	Text.setFont(textFont);

	Text.setString("Use ASD to move\nand\nRMB to interact\nwith objects");

	Text.setPosition(sf::Vector2f(1500, 500));
	Text.setCharacterSize(24);
	clockWaiting(5);
	Text.setString("");


}

void BasementGame::initVoises() {
	int numb_of_sounds = 3;
	downloadArrayOfSounds(sbFirstWord, "first_words_", 3);
	downloadArrayOfSounds(sbPotatoBox, "potato_box_", numb_of_sounds);
	downloadArrayOfSounds(sbWindow, "window_", numb_of_sounds);
	downloadArrayOfSounds(sbBeetBox, "beet_box_", numb_of_sounds);
	downloadArrayOfSounds(sbCarrotBox, "carrot_box_", numb_of_sounds);

	sbOpener.loadFromFile("other//basement//sounds//opener_found.wav");
	sbBuckets.loadFromFile("other//basement//sounds//buckets.wav");
	sbNoteFound.loadFromFile("other//basement//sounds//note_found.wav");
	sbNoteReading.loadFromFile("other//basement//sounds//note_reading.wav");

	downloadArrayOfSounds(sbNote, "note_", numb_of_sounds);
	downloadArrayOfSounds(sbDoorClosed, "door_closed_", numb_of_sounds);
	sbDoorOpening.loadFromFile("other//basement//sounds//door_opening.wav");

	downloadArrayOfSounds(sbJars, "jars_", numb_of_sounds);
	downloadArrayOfSounds(sbBoxes, "boxes_", numb_of_sounds);

	downloadArrayOfSounds(sbRedJars, "red_jars_", numb_of_sounds);
	downloadArrayOfSounds(sbEmptyJars, "empty_jars_", numb_of_sounds);
	downloadArrayOfSounds(sbOtherJars, "other_jars_", numb_of_sounds);

	sbJarFound.loadFromFile("other//basement//sounds//jar_found.wav");
	sbNoOpener.loadFromFile("other//basement//sounds//no_opener.wav");

	sbJarLooking.loadFromFile("other//basement//sounds//jar_looking_without_opener.wav");
	sbLidLooking.loadFromFile("other//basement//sounds//lid_looking_without_opener.wav");


	sbLeft.loadFromFile("other//basement//sounds//left.wav");
	sbLeftOrStraight.loadFromFile("other//basement//sounds//left_or_straight.wav");
	sbStraight.loadFromFile("other//basement//sounds//straight.wav");
	sbFance.loadFromFile("other//basement//sounds//fance.wav");



}

void BasementGame::initSounds()
{
	sound.setVolume(50);
	sbNoteOpening.loadFromFile("other//basement//sounds//note_opening_sound.wav");
	downloadArrayOfSounds(sbCarrotSearching, "carrot_searching_", 3);
	sbWindowKnock.loadFromFile("other//basement//sounds//window_knock.wav");
	sbBasementDoorOpening.loadFromFile("other//basement//sounds//basement_door_opening.wav");
	downloadArrayOfSounds(sbJarsKnock, "jars_knock_", 3);

	downloadArrayOfSounds(sbLeftRun, "left_run", 3);
	sbLoseDoorOpening.loadFromFile("other//basement//sounds//lose_door_opening.wav");
	sbLoseFanceOpening.loadFromFile("other//basement//sounds//lose_fance_opening.wav");
	sbWinFanceOpening.loadFromFile("other//basement//sounds//win_fance_opening.wav");
	sbLoseRun.loadFromFile("other//basement//sounds//lose_run.wav");
	sbWinRun.loadFromFile("other//basement//sounds//win_run.wav");
	sbStairsRun.loadFromFile("other//basement//sounds//stairs_run.wav");
	sbGav.loadFromFile("other//basement//sounds//gav.wav");
	sbJarOpening.loadFromFile("other//basement//sounds//jar_opening.wav");




	sbBreathing.loadFromFile("other//basement//sounds//breathing.wav");
	breathing.setBuffer(sbBreathing);
	breathing.setLoop(true);


	//not mine
	sbJarBreaking.loadFromFile("other//basement//sounds//jar_breaking.wav");

}
