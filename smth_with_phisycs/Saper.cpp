#include "Saper.h"

namespace saper {
    unsigned int CELL_WIDTH = 32, CELL_LENGTH = 32;
    const unsigned int FIELD_LENGTH = 25, FIELD_WIDTH = 25, COUNT_OF_MINES = 99;
    bool WIN = false, LOSE = false;
    std::vector<sf::Texture> sub_textures;
    sf::Image icons;
    const sf::Color redColor(255, 0, 0, 250);
    sf::Sound start_sound, lose_sound, click_sound, win_sound;
    std::vector<std::vector<El>> field(FIELD_WIDTH, std::vector<El>(FIELD_LENGTH));


    void El::changeShowTexture(unsigned index) {
        show.setTexture(sub_textures[index]);
        texture_show_index = index;
    }

    void El::changeRealTexture(unsigned index) {
        real.setTexture(sub_textures[index]);
        texture_real_index = index;
    }

    void El::openField() {
        show = real;
        texture_show_index = texture_real_index;
        is_open = true;
    }

    void El::setPosition(float x, float y) {
        real.setPosition(x, y);
        show.setPosition(x, y);
    }

    void El::makeRed() {
        real.setColor(redColor);
    }

    sf::Sprite El::getShow() { return show; }
    sf::Sprite El::getReal() { return real; }
    unsigned int El::getTextureRealIndex() { return texture_real_index; }
    unsigned int El::getTextureShowIndex() { return texture_show_index; }
    bool El::getIsOpen() { return is_open; }


    void makeCellsArray(std::vector<sf::Sprite>& cells) {
        unsigned img_width = icons.getSize().x;
        for (int i = 0; i < img_width; i += CELL_WIDTH) {
            sf::Texture sub_texture;
            sub_texture.loadFromImage(icons, sf::IntRect(i, 0, CELL_WIDTH, CELL_LENGTH));
            sub_textures.push_back(sub_texture);
            sf::Sprite sub_sprite;
            sub_sprite.setTexture(sub_texture);
            cells.push_back(sub_sprite);
        }
    }

    void makeEmptyField(std::vector<std::vector<El>>& field) {
        for (int i = 0; i < FIELD_LENGTH; i++) {
            for (int j = 0; j < FIELD_WIDTH; j++) {
                field[i][j].changeRealTexture(0);
                field[i][j].changeShowTexture(10);
                field[i][j].setPosition(j * CELL_WIDTH, i * CELL_LENGTH);
            }
        }
    }

    std::pair<int, int> makePandomPair() {
        std::pair<int, int> el(rand() % FIELD_LENGTH, rand() % FIELD_WIDTH);
        return el;
    }

    std::vector<std::pair<int, int>> generateMinesCoordinates(int count_of_mines) {
        std::vector<std::pair<int, int>> vect;
        for (int i = 0; i < count_of_mines; ++i) {
            vect.push_back(makePandomPair());
        }
        vect.erase(std::unique(vect.begin(), vect.end()), vect.end());
        while (vect.size() < count_of_mines) {
            vect.push_back(makePandomPair());
            vect.erase(std::unique(vect.begin(), vect.end()), vect.end());
        }
        return vect;
    }

    void putMines(std::vector<std::vector<El>>& field) {
        std::vector<std::pair<int, int>> indexes = generateMinesCoordinates();
        for (auto el : indexes) {
            field[el.first][el.second].changeRealTexture(9);
        }
    }

    void incrementDigits(std::vector<std::vector<El>>& field, const int row_index, const int column_index) {
        for (int i = row_index - 1; i <= row_index + 1; ++i) {
            for (int j = column_index - 1; j <= column_index + 1; ++j) {
                if (i >= 0 && i < FIELD_WIDTH && j >= 0 && j < FIELD_LENGTH && (i != row_index || j != column_index) && !(field[i][j].getTextureRealIndex() == 9)) {
                    field[i][j].changeRealTexture(field[i][j].getTextureRealIndex() + 1);
                }
            }
        }
    }

    void putDigits(std::vector<std::vector<El>>& field) {
        for (int i = 0; i < FIELD_LENGTH; i++) {
            for (int j = 0; j < FIELD_LENGTH; j++) {
                if (field[i][j].getTextureRealIndex() == 9)
                    incrementDigits(field, i, j);
            }
        }
    }

    void openAroundBubble(std::vector<std::vector<El>>& field, const int row_index, const int column_index) {
        if (row_index < 0 || row_index >= FIELD_WIDTH || column_index < 0 || column_index >= FIELD_LENGTH) {
            return;
        }
        if (field[row_index][column_index].getTextureShowIndex() != 10) {
            return;
        }
        field[row_index][column_index].openField();
        if (field[row_index][column_index].getTextureRealIndex() == 0) {
            for (int i = row_index - 1; i <= row_index + 1; ++i) {
                for (int j = column_index - 1; j <= column_index + 1; ++j) {
                    openAroundBubble(field, i, j);
                }
            }
        }
    }

    void displayField(sf::RenderWindow& window, std::vector<std::vector<El>>& field, char real_or_show ) {
        if (real_or_show == 'r') {
            for (auto row : field) {
                for (auto el : row) {
                    window.draw(el.getReal());
                }
            }
        }
        if (real_or_show == 'm') {
            for (auto row : field) {
                for (auto el : row) {
                    if (el.getTextureRealIndex() == 9)
                        window.draw(el.getReal());
                    else window.draw(el.getShow());
                }
            }
        }
        else {
            for (auto row : field) {
                for (auto el : row) {
                    window.draw(el.getShow());
                }
            }
        }
        window.display();
    }

    void openMines(std::vector<std::vector<El>>& field) {
        for (int i = 0; i < FIELD_LENGTH; i++) {
            for (int j = 0; j < FIELD_WIDTH; j++) {
                if (field[i][j].getTextureRealIndex() == 9) {
                    field[i][j].openField();
                }
            }
        }
    }

    void buildField(std::vector<std::vector<El>>& field) {
        makeEmptyField(field);
        putMines(field);
        putDigits(field);
    }

    bool checkIfWin(std::vector<std::vector<El>>& field) {
        for (auto row : field) {
            for (auto el : row) {
                if (el.getTextureRealIndex() != 9 && !el.getIsOpen())
                    return false;
            }
        }
        return true;
    }

    bool checkFlagsAround(std::vector<std::vector<El>>& field, const int row_index, const int column_index) {
        int needed_count_of_flags = field[row_index][column_index].getTextureRealIndex(), count_of_flags = 0;
        for (int i = row_index - 1; i <= row_index + 1; ++i) {
            for (int j = column_index - 1; j <= column_index + 1; ++j) {
                if (i >= 0 && i < FIELD_WIDTH && j >= 0 && j < FIELD_LENGTH && (i != row_index || j != column_index) && field[i][j].getTextureShowIndex() == 11) {
                    count_of_flags++;
                }
            }
        }
        return needed_count_of_flags == count_of_flags;
    }

    void printLoseField(sf::RenderWindow& window, std::vector<std::vector<El>>& field) {
        displayField(window, field, 'm');
        sf::Event event;
        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
        }
        buildField(field);
    }

    void openAroundOnce(sf::RenderWindow& window, std::vector<std::vector<El>>& field, const int row_index, const int column_index) {
        for (int i = row_index - 1; i <= row_index + 1; ++i) {
            for (int j = column_index - 1; j <= column_index + 1; ++j) {
                if (i >= 0 && i < FIELD_WIDTH && j >= 0 && j < FIELD_LENGTH && (i != row_index || j != column_index) && field[i][j].getTextureShowIndex() != 11) {
                    if (field[i][j].getTextureRealIndex() == 0) {
                        click_sound.play();
                        openAroundBubble(field, i, j);
                    }
                    field[i][j].openField();
                    if (field[i][j].getTextureRealIndex() == 9) {
                        field[i][j].makeRed();
                        LOSE = true;
                        lose_sound.play();
                    }

                }
            }
        }
        if (LOSE) {
            printLoseField(window, field);
        }
    }


    void loadSoundFromFile(sf::Sound& sound, sf::SoundBuffer& sb, std::string file_name) {
        std::string path = "other//saper//" + file_name;
        if (!sb.loadFromFile(path)) {
            throw "cant load sound from file";
        }
        sound.setBuffer(sb);
    }

    int run() {
        sf::RenderWindow window(sf::VideoMode(FIELD_WIDTH * CELL_WIDTH, FIELD_LENGTH * CELL_LENGTH), "Saper");
        sf::SoundBuffer start_sb, lose_sb, click_sb, win_sb;
        loadSoundFromFile(start_sound, start_sb, "start.wav");
        loadSoundFromFile(lose_sound, lose_sb, "lose_minesweeper.wav");
        loadSoundFromFile(click_sound, click_sb, "click.wav");
        loadSoundFromFile(win_sound, win_sb, "win.wav");
        if (!icons.loadFromFile("other//saper//icons.png")) {
            throw "cant load icons from file";
        }
        std::vector<sf::Sprite> cells;
        makeCellsArray(cells);
        buildField(field);
        start_sound.play();

        

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                else if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        int x = mousePos.x / CELL_LENGTH, y = mousePos.y / CELL_WIDTH;
                        if (field[y][x].getTextureShowIndex() != 11) {
                            if (field[y][x].getTextureRealIndex() == 9) {
                                field[y][x].makeRed();
                                lose_sound.play();
                                printLoseField(window, field);

                            }
                            else if (field[y][x].getTextureRealIndex() == 0) {
                                click_sound.play();
                                openAroundBubble(field, y, x);
                            }
                            else if (field[y][x].getTextureShowIndex() == 10) {
                                field[y][x].openField();
                            }
                            else if (checkFlagsAround(field, y, x)) {
                                openAroundOnce(window, field, y, x);
                            }

                        }
                        if (checkIfWin(field)) {
                            WIN = true;
                            displayField(window, field, 'm');
                            win_sound.play();
                            while (window.isOpen()) {
                                while (window.pollEvent(event)) {
                                    if (event.type == sf::Event::Closed) {
                                        window.close();
                                    }
                                }
                            }
                        }

                    }
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        int x = mousePos.x / CELL_LENGTH, y = mousePos.y / CELL_WIDTH;
                        if (field[y][x].getTextureShowIndex() == 10) {
                            field[y][x].changeShowTexture(11);
                        }
                        else if (field[y][x].getTextureShowIndex() == 11) {
                            field[y][x].changeShowTexture(10);
                        }
                    }
                }
            }

            displayField(window, field);


        }
        return 0;
    }
}
