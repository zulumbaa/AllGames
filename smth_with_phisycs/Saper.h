#ifndef SAPER_H
#define SAPER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>

namespace saper {
    extern unsigned int CELL_WIDTH, CELL_LENGTH;
    extern const unsigned int FIELD_LENGTH, FIELD_WIDTH, COUNT_OF_MINES;
    extern bool WIN, LOSE;
    extern std::vector<sf::Texture> sub_textures;
    extern sf::Image icons;
    extern const sf::Color redColor;
    extern sf::Sound start_sound, lose_sound, click_sound, win_sound;

    struct El {
    private:
        unsigned int texture_real_index = 0, texture_show_index = 10;
        bool is_open = false;
        sf::Sprite show, real;
    public:
        El(){}
        void changeShowTexture(unsigned index);
        void changeRealTexture(unsigned index);
        void openField();
        void setPosition(float x, float y);
        void makeRed();
        sf::Sprite getShow();
        sf::Sprite getReal();
        unsigned int getTextureRealIndex();
        unsigned int getTextureShowIndex();
        bool getIsOpen();
    };
    extern std::vector<std::vector<El>> field;

    void makeCellsArray(std::vector<sf::Sprite>& cells);
    void makeEmptyField(std::vector<std::vector<El>>& field);
    std::pair<int, int> makePandomPair();
    std::vector<std::pair<int, int>> generateMinesCoordinates(int count_of_mines = COUNT_OF_MINES);
    void putMines(std::vector<std::vector<El>>& field);
    void incrementDigits(std::vector<std::vector<El>>& field, const int row_index, const int column_index);
    void putDigits(std::vector<std::vector<El>>& field);
    void openAroundBubble(std::vector<std::vector<El>>& field, const int row_index, const int column_index);
    void displayField(sf::RenderWindow& window, std::vector<std::vector<El>>& field, char real_or_show = 's');
    void openMines(std::vector<std::vector<El>>& field);
    void buildField(std::vector<std::vector<El>>& field);
    bool checkIfWin(std::vector<std::vector<El>>& field);
    bool checkFlagsAround(std::vector<std::vector<El>>& field, const int row_index, const int column_index);
    void printLoseField(sf::RenderWindow& window, std::vector<std::vector<El>>& field);
    void openAroundOnce(sf::RenderWindow& window, std::vector<std::vector<El>>& field, const int row_index, const int column_index);
    void loadSoundFromFile(sf::Sound& sound, sf::SoundBuffer& sb, std::string file_name);
    int run();
}

#endif // SAPER_H
