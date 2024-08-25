//TODO
//Нараховування балів(чим більше за раз тим більше очків, швидкість надає очки)
//Пофіксити те, що ти не встигаєш при падінні засунути кубик вбік
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <fstream>
#include <vector>
#include <ctime>
#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>

const float CUBE_SIZE = 50;

class TetrysGame
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
    float rightBorder, leftBorder, downBorder;

	sf::Vector2i mouseWindowPosition;
	sf::Vector2f mouseWindowPositionView;
    sf::Texture grey_el;


	sf::Color red = sf::Color::Color(250, 0, 0, 250);
	sf::Color purple = sf::Color::Color(128, 0, 128, 250);
	sf::Color yellow = sf::Color::Color(255, 255, 0, 250);
	sf::Color orange = sf::Color::Color(255, 165, 0, 250);
	sf::Color green = sf::Color::Color(0, 255, 0, 250);
	sf::Color blue = sf::Color::Color(0, 0, 255, 250);
    sf::Color lightblue = sf::Color::Color(173, 216, 230, 125);

    sf::Clock move_clock;
    float prev_time;
    float speed = 0.3;
    bool wanted_to_move = false;

    class Cube
    {
    private:
        sf::RectangleShape shape;
        int rotate_index = 0;

    public:
        Cube(sf::Texture* txtr = nullptr, sf::Color fillColor = sf::Color::White, float x = 0, float y = 0)
        {

            shape.setTexture(txtr);
            shape.setFillColor(fillColor);
            shape.setSize(sf::Vector2f(50.f, 50.f));

            shape.setPosition(sf::Vector2f(x*CUBE_SIZE, y*CUBE_SIZE));
        }

        void move(float offsetX, float offsetY)
        {
            shape.move(offsetX, offsetY);
        }

        void render(sf::RenderWindow& window)
        {
            window.draw(shape);
        }

        void setPosition(float x = 0, float y = 0)
        {
            shape.setPosition(x*CUBE_SIZE, y*CUBE_SIZE);
        }
        sf::Vector2f getPosition() const{
            return shape.getPosition();
        }
        sf::Color getColor() {
            return shape.getFillColor();
        }
        int getRotateIndex() {
            return rotate_index;
        }
        void setRotateIndex(int index) {
            rotate_index = index;
        }
    };

    std::vector<Cube> moving_figures;
    std::vector<Cube> fallen_figures;
    std::map<float, int> elements_in_one_line;
    std::map<std::string, std::vector<std::vector<std::pair<int, int>>>> rotating_coordinats;
    bool game_over = false;

    sf::Font font;
    sf::Text score, final_message;
    int score_int = 0;

    sf::SoundBuffer sb_line_completed, sb_new_record;
    sf::Music main_music;
    sf::Sound sound;
    


    void initWindow();
    void initEl();
    void initVariables();

    void pullEvent();
    void clockWork();
    void chooseRandomFigure();
    void moveFigures(float x, float y);
    bool checkIfFiguresIsOutByRight();
    bool checkIfFiguresIsOutByLeft();
    bool checkIfFigureFell();
    void checkIfNeedToDeleteLine();
    void deleteLine(float topY);
    void figureFellAction();
    std::string ColorToString(sf::Color color);
    void rotateFigures();
    void checkIfGameOver();
    void ActionWithScoreFileAfterGameOver();
    void playSound(sf::SoundBuffer& sb);
    void restart();


    void renderElements();

	
public:
	TetrysGame();
	virtual ~TetrysGame();
	const bool getWindowIsOpen() const;
	void update();
	void render();
};



