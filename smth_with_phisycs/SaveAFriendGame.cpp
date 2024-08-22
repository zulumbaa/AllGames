#include "SaveAFriendGame.h"

void SafeAFriend::initWindow()
{
    sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0];
    window = new sf::RenderWindow(fullscreenMode, "Save a Friend", sf::Style::Fullscreen);

    window->setKeyRepeatEnabled(false);
    window->setFramerateLimit(144);
}

void SafeAFriend::initTextures()
{
    textures.Load(Texture::Mushrooms, "other//saveAfriend//images//mushrooms.png");
}

void SafeAFriend::initObjects()
{
    std::unique_ptr<RenderObject> mushroom1 = std::make_unique<RenderObject>();
    mushroom1->getObject().setTexture(&textures.Get(Texture::Mushrooms));
    mushroom1->getObject().setSize(sf::Vector2f(100, 100));
    objects.AddObject(std::move(mushroom1));

    objects.setPositionsFromFile();
}

SafeAFriend::SafeAFriend()
{
    initWindow();
    initTextures();
    initObjects();
}

SafeAFriend::~SafeAFriend()
{
    delete window;
}

const bool SafeAFriend::getWindowIsOpen() const
{
    return window->isOpen();
}

void SafeAFriend::pollEvents()
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
            else if (ev.key.code == sf::Keyboard::Numpad0) {
                isEditMode = !isEditMode;
                if (isEditMode) {
                    for (const auto& pair : objects.getAllObjects()) {
                        pair.second->showBorder();
                    }
                }
                else {
                    for (const auto& pair : objects.getAllObjects()) {
                        pair.second->hideBorder();
                    }
                    objects.savePositionsToFile();
                }
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (ev.mouseButton.button == sf::Mouse::Left) {
                isLeftMouseButtonPressed = true;
            }
            break;

        case sf::Event::MouseButtonReleased:
            if (ev.mouseButton.button == sf::Mouse::Left) {
                isLeftMouseButtonPressed = false;
            }
            break;
        }
    }
}

void SafeAFriend::editPositionOfObject()
{
    if (isEditMode && isLeftMouseButtonPressed) {
        for (auto& pair : objects.getAllObjects()) {
            sf::RectangleShape& obj = pair.second->getObject();
            auto [topLeft, topRight, bottomLeft, bottomRight] = pair.second->getBoundingBox();

            if (coordsInRectangle(mouseWindowPositionView, topLeft, topRight, bottomLeft, bottomRight)) {
                obj.setPosition(mouseWindowPositionView - obj.getSize() / 2.0f);
                break;
            }
        }
    }
    
}


void SafeAFriend::update(sf::Time deltatime)
{
    updateMousePosition();
    pollEvents();
    editPositionOfObject();
   
}

void SafeAFriend::updateMousePosition()
{
    mouseWindowPosition = sf::Mouse::getPosition(*window);
    mouseWindowPositionView = window->mapPixelToCoords(mouseWindowPosition);
}

void SafeAFriend::updateButtonsHover()
{
}

bool SafeAFriend::coordsInRectangle(sf::Vector2f coords, sf::Vector2f topLeft, sf::Vector2f topRight, sf::Vector2f bottomLeft, sf::Vector2f bottomRight)
{
    return (coords.x >= topLeft.x && coords.x <= topRight.x &&
        coords.y >= topLeft.y && coords.y <= bottomLeft.y);
}

void SafeAFriend::render()
{
    window->clear();

    for (const auto& pair : objects.getAllObjects()) {
        window->draw(pair.second->getObject());
    }

    window->display();
}
