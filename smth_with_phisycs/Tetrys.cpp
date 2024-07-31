#include "Tetrys.h"

void TetrysGame::initWindow()
{
	videoMode.height = 1000;
    videoMode.width = 500;
    window = new sf::RenderWindow(videoMode, "Tetris Game", sf::Style::Default);
    window->setFramerateLimit(144);

	
}

void TetrysGame::initEl()
{
	grey_el.loadFromFile("other//tetrys//element.png");
	chooseRandomFigure();
}

void TetrysGame::initVariables()
{
	rightBorder = videoMode.width;
	leftBorder = 0;
	downBorder = videoMode.height;
	move_clock.restart();
	prev_time = move_clock.getElapsedTime().asSeconds();
	srand(time(NULL));
	rotating_coordinats = {
	{"lightblue", {
		{{4,0}, {4,1}, {4,2}, {4,3}},  
		{{3,0}, {4,0}, {5,0}, {6,0}}  
	}},
	{"blue", {
		{{5,0}, {5,1}, {5,2}, {4,2}},  
		{{3,0}, {4,0}, {5,0}, {5,1}},  
		{{4,2}, {4,1}, {4,0}, {5,0}},  
		{{5,1}, {4,1}, {3,1}, {3,0}}   
	}},
	{"orange", {
		{{4,0}, {4,1}, {4,2}, {5,2}},  
		{{4,1}, {5,1}, {6,1}, {6,0}},  
		{{5,2}, {5,1}, {5,0}, {4,0}},  
		{{6,0}, {5,0}, {4,0}, {4,1}}   
	}},
	{"yellow", {
		{{4,0}, {4,1}, {5,0}, {5,1}}  
	}},
	{"green", {
		{{3,1}, {4,0}, {4,1}, {5,0}},  
		{{5,2}, {4,1}, {5,1}, {4,0}},  
	}},
	{"purple", {
		{{3,0}, {4,0}, {4,1}, {5,0}},  
		{{4,2}, {4,1}, {5,1}, {4,0}},  
		{{5,1}, {4,1}, {4,0}, {3,1}},  
		{{5,0}, {5,1}, {4,1}, {5,2}}   
	}},
	{"red", {
		{{3,0}, {4,0}, {4,1}, {5,1}},  
		{{5,0}, {5,1}, {4,1}, {4,2}},  
	}}
	};

	font.loadFromFile("other//tetrys//PixelGameFont.ttf");
	score.setFont(font);
	score.setCharacterSize(24);
	score.setPosition(sf::Vector2f(9*CUBE_SIZE+score.getGlobalBounds().width/2, 0));
	score.setString(std::to_string(score_int));

	final_message.setFont(font);
	final_message.setCharacterSize(32);
	final_message.setString("Press R to restart!");
	final_message.setPosition(sf::Vector2f(rightBorder/5, downBorder / 3 ));

	main_music.openFromFile("other//tetrys//tetrys_main_music.wav");
	main_music.setLoop(true);
	main_music.play();

	sb_new_record.loadFromFile("other//tetrys//new_record.wav");
	sb_line_completed.loadFromFile("other//tetrys//line.wav");
	sound.setVolume(100);


}


TetrysGame::TetrysGame() {
	initWindow();
	initVariables();
	initEl();
	
}

TetrysGame::~TetrysGame()
{
	delete window;
}

const bool TetrysGame::getWindowIsOpen() const
{
	return window->isOpen();
}

void TetrysGame::chooseRandomFigure()
{
	int random_numb = rand() % 7;
	moving_figures.clear();
	switch (random_numb)
	{
	case 0: {
		moving_figures.push_back(Cube(&grey_el, lightblue, 4, 0));
		moving_figures.push_back(Cube(&grey_el, lightblue, 4, 1));
		moving_figures.push_back(Cube(&grey_el, lightblue, 4, 2));
		moving_figures.push_back(Cube(&grey_el, lightblue, 4, 3));
		break;
	}
	case 1: {
		moving_figures.push_back(Cube(&grey_el, blue, 5, 0));
		moving_figures.push_back(Cube(&grey_el, blue, 5, 1));
		moving_figures.push_back(Cube(&grey_el, blue, 5, 2));
		moving_figures.push_back(Cube(&grey_el, blue, 4, 2));
		break;

	}
	case 2: {
		moving_figures.push_back(Cube(&grey_el, orange, 4, 0));
		moving_figures.push_back(Cube(&grey_el, orange, 4, 1));
		moving_figures.push_back(Cube(&grey_el, orange, 4, 2));
		moving_figures.push_back(Cube(&grey_el, orange, 5, 2));
		break;

	}
	case 3: {

		moving_figures.push_back(Cube(&grey_el, yellow, 4, 0));
		moving_figures.push_back(Cube(&grey_el, yellow, 4, 1));
		moving_figures.push_back(Cube(&grey_el, yellow, 5, 0));
		moving_figures.push_back(Cube(&grey_el, yellow, 5, 1));
		break;

	}
	case 4: {
		moving_figures.push_back(Cube(&grey_el, green, 3, 1));
		moving_figures.push_back(Cube(&grey_el, green, 4, 0));
		moving_figures.push_back(Cube(&grey_el, green, 4, 1));
		moving_figures.push_back(Cube(&grey_el, green, 5, 0));
		break;

	}
	case 5: {
		moving_figures.push_back(Cube(&grey_el, purple, 3, 0));
		moving_figures.push_back(Cube(&grey_el, purple, 4, 0));
		moving_figures.push_back(Cube(&grey_el, purple, 4, 1));
		moving_figures.push_back(Cube(&grey_el, purple, 5, 0));
		break;

	}
	case 6: {
		moving_figures.push_back(Cube(&grey_el, red, 3, 0));
		moving_figures.push_back(Cube(&grey_el, red, 4, 0));
		moving_figures.push_back(Cube(&grey_el, red, 4, 1));
		moving_figures.push_back(Cube(&grey_el, red, 5, 1));
		break;

	}

	default:
		break;
	}
}

void TetrysGame::moveFigures(float x, float y)
{
	for (auto& el : moving_figures) {
		el.move(x,y);
	}
}

bool TetrysGame::checkIfFiguresIsOutByRight()
{
	for (auto& moving_el : moving_figures) {

		sf::Vector2f element_pos = moving_el.getPosition();
		if (element_pos.x + CUBE_SIZE >= rightBorder) {
			return true;
		}
		for (auto& fallen_el : fallen_figures) {
			if (element_pos.x + CUBE_SIZE == fallen_el.getPosition().x && (element_pos.y == fallen_el.getPosition().y
				|| element_pos.y + CUBE_SIZE == fallen_el.getPosition().y)) {
				return true;
			}
		}
		
	}
	return false;
}
bool TetrysGame::checkIfFiguresIsOutByLeft()
{
	for (auto& moving_el : moving_figures) {
		sf::Vector2f element_pos = moving_el.getPosition();
		if (element_pos.x <= leftBorder) {
			return true;
		}
		for (auto& fallen_el : fallen_figures) {
			if (element_pos.x == fallen_el.getPosition().x + CUBE_SIZE && (element_pos.y == fallen_el.getPosition().y
				|| element_pos.y + CUBE_SIZE == fallen_el.getPosition().y)) {
				return true;
			}
		}
		
	}
	return false;
}

bool TetrysGame::checkIfFigureFell()
{
	for (auto& moving_el : moving_figures) {
		float current_el_position_bottom = moving_el.getPosition().y + CUBE_SIZE;
		float current_el_position_left = moving_el.getPosition().x;

		if (current_el_position_bottom >= downBorder) {
			return true;
		}
		for (auto& fallen_el : fallen_figures) {
			if (current_el_position_bottom == fallen_el.getPosition().y && current_el_position_left == fallen_el.getPosition().x) {
				return true;
			}
		}
	}
	return false;
}

void TetrysGame::checkIfNeedToDeleteLine()
{
	bool was_deleting = false;
	for (auto& pair : elements_in_one_line) {
		if (pair.second == 10) {
			deleteLine(pair.first);
			was_deleting = true;
			break;
		}
	}
	if (was_deleting) {
		checkIfNeedToDeleteLine();
	}
}

void TetrysGame::deleteLine(float topY)
{
	score_int += 100;
	//map clearing
	elements_in_one_line.clear();
	//cubes deleting
	auto del_iter = std::remove_if(fallen_figures.begin(), fallen_figures.end(),
		[&topY](const Cube& c) {return c.getPosition().y == topY; });
	fallen_figures.erase(del_iter, fallen_figures.end());

	//cubes falling
	std::for_each(fallen_figures.begin(), fallen_figures.end(),
		[&topY](Cube& c) {if (c.getPosition().y < topY) { c.move(0, CUBE_SIZE); } });
	//map updating
	std::for_each(fallen_figures.begin(), fallen_figures.end(),
		[&](const Cube& c) {elements_in_one_line[c.getPosition().y]++; });

	playSound(sb_line_completed);

}

void TetrysGame::figureFellAction()
{
	
	fallen_figures.insert(fallen_figures.end(), moving_figures.begin(), moving_figures.end());
	for (auto& moving_el : moving_figures) {
		elements_in_one_line[moving_el.getPosition().y]++;
	}
	checkIfNeedToDeleteLine();
	moving_figures.clear();
	chooseRandomFigure();
	checkIfFigureFell();
	checkIfGameOver();
}

std::string TetrysGame::ColorToString(sf::Color color)
{
	if (color == lightblue) return "lightblue";
	if (color == blue) return "blue";
	if (color == orange) return "orange";
	if (color == yellow) return "yellow";
	if (color == green) return "green";
	if (color == purple) return "purple";
	if (color == red) return "red";
	return "unknown";
}

void TetrysGame::rotateFigures()
{
	std::string color = ColorToString(moving_figures[0].getColor());
	int index = moving_figures[0].getRotateIndex();
	index++;
	int how_much_it_moved = moving_figures[0].getPosition().x - rotating_coordinats[color][0][0].first * CUBE_SIZE;
	int how_much_it_fall = moving_figures[0].getPosition().y - rotating_coordinats[color][0][0].second * CUBE_SIZE;
	if (index == rotating_coordinats[color].size()) {
		index = 0;
	}
	for (int i = 0; i < 4; i++) {
		moving_figures[i].setRotateIndex(index);
		moving_figures[i].setPosition(rotating_coordinats[color][index][i].first, rotating_coordinats[color][index][i].second);
		moving_figures[i].move(how_much_it_moved, how_much_it_fall);
	}
	while (checkIfFiguresIsOutByLeft()) {
		for (auto & el : moving_figures) {
			el.move(CUBE_SIZE, 0);
		}
	}
	while (checkIfFiguresIsOutByRight()) {
		for (auto& el : moving_figures) {
			el.move(-CUBE_SIZE, 0);
		}
	}
}

void TetrysGame::checkIfGameOver()
{
	for (auto& el : fallen_figures) {
		if (el.getPosition().y <= CUBE_SIZE) {
			game_over = true;
			main_music.pause();
			ActionWithScoreFileAfterGameOver();
			return;
		}
	}
}

void TetrysGame::ActionWithScoreFileAfterGameOver()
{
	std::ifstream fin("other//tetrys//scores.txt");
	int score_old;
	fin >> score_old;
	if (score_int > score_old) {
		final_message.setString("New Record!\nPrevious score: " + std::to_string(score_old) + "\nNew score: " + std::to_string(score_int) + "\nPress R to restart!");
		std::ofstream fout("other//tetrys//scores.txt");
		fout.clear();
		fout << score_int;
		playSound(sb_new_record);
	}
}

void TetrysGame::playSound(sf::SoundBuffer& sb)
{
	sound.setBuffer(sb);
	sound.play();
}

void TetrysGame::restart()
{
	moving_figures.clear();
	fallen_figures.clear();
	elements_in_one_line.clear();
	move_clock.restart();
	prev_time = move_clock.getElapsedTime().asSeconds();
	chooseRandomFigure();
	game_over = false;
	score_int = 0;
	final_message.setString("Press R to restart!");
	main_music.play();
}

void TetrysGame::renderElements()
{
	for (auto& el : moving_figures) {
		el.render(*window);
	}
	for (auto& el : fallen_figures) {
		el.render(*window);
	}
}

void TetrysGame::pullEvent()
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
			else if (ev.key.code == sf::Keyboard::R) {
				restart();
			}
			else if (ev.key.code == sf::Keyboard::W) {
				rotateFigures();
			}
			else if (ev.key.code == sf::Keyboard::S) {
				speed = 0.1;
			}
			else if (ev.key.code == sf::Keyboard::D) {
				if (!checkIfFiguresIsOutByRight()) {
					moveFigures(50, 0);
				}
			}
			else if (ev.key.code == sf::Keyboard::A) {
				if (!checkIfFiguresIsOutByLeft()) {
					moveFigures(-50, 0);
				}
			}
			break;

		case sf::Event::KeyReleased:
			if (ev.key.code == sf::Keyboard::S) {
				speed = 0.3;
			}
			break;
		case sf::Event::MouseButtonPressed:
			break;
		}
	}
}

void TetrysGame::clockWork()
{
	float cur_time = move_clock.getElapsedTime().asSeconds();
	
	if (cur_time - prev_time > speed) {
		for (auto& el : moving_figures) {
			el.move(0, CUBE_SIZE);
		}
		prev_time = cur_time;
		if (checkIfFigureFell()) {
			render();
			figureFellAction();
		}

	}
}

void TetrysGame::update()
{
	pullEvent();
	if (!game_over) {
		score.setString(std::to_string(score_int));
		clockWork();
	}
	
}

void TetrysGame::render()
{
    window->clear();
	renderElements();
	window->draw(score);
	if (game_over) {
		window->draw(final_message);
	}
    window->display();
}
