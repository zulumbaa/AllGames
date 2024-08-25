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
    textures.Load(Texture::Green, "other//saveAfriend//images//green.png");
    textures.Load(Texture::SideEditBorder, "other//saveAfriend//images//side_edit_border.png");
    textures.Load(Texture::Path, "other//saveAfriend//images//path.png");
    textures.Load(Texture::Water, "other//saveAfriend//images//water.png");

}

void SafeAFriend::initObjects()
{
    initEditSideBorder();

    std::unique_ptr<RenderObject> mushroom1 = std::make_unique<RenderObject>();
    mushroom1->getObject().setTexture(&textures.Get(Texture::Mushrooms));
    mushroom1->getObject().setSize(sf::Vector2f(100, 100));
    location_objects.AddObject(std::move(mushroom1));

    std::unique_ptr<RenderObject> green = std::make_unique<RenderObject>();
    green->getObject().setTexture(&textures.Get(Texture::Green));
    green->getObject().setSize(sf::Vector2f(100, 100));
    location_objects.AddObject(std::move(green));

    location_objects.setPositionsFromFile();
}

void SafeAFriend::initEditSideBorder()
{
    std::unique_ptr<RenderObject> side_border = std::make_unique<RenderObject>();
    side_border->getObject().setTexture(&textures.Get(Texture::SideEditBorder));
    side_border->getObject().setSize(sf::Vector2f(100, window->getSize().y));
    objects_to_insert_in_edit_mode.AddObject(std::move(side_border));

    for (int i = static_cast<int>(Texture::Mushrooms); i < static_cast<int>(Texture::SideEditBorder); ++i) {
        Texture textureEnum = static_cast<Texture>(i);

        std::unique_ptr<RenderObject> texture_object = std::make_unique<RenderObject>();
        texture_object->getObject().setTexture(&textures.Get(textureEnum));
        texture_object->getObject().setSize(sf::Vector2f(textureWidth, textureHeight));

        float y = i * textureHeight;  

        texture_object->getObject().setPosition(sf::Vector2f(0, y));
        objects_to_insert_in_edit_mode.AddObject(std::move(texture_object));
    }
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
                if (!isEditMode) {
                    location_objects.changeHiglightObj(0);
                    location_objects.savePositionsToFile();
                }
            }
            else if (ev.key.code == sf::Keyboard::Subtract) {
                if (isEditMode) {
                    if (tryToDeleteObjectInEditMode()) {
                        location_objects.savePositionsToFile();
                    }
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

        case sf::Event::MouseWheelScrolled:
            if (isEditMode) {
                scrollTexturesInSideBoard(ev.mouseWheelScroll.delta);
            }
            break;
        }
    }
}

bool SafeAFriend::tryMoveObject(int objectId)
{
    RenderObject* object = &location_objects.Get(objectId);
    if (object != nullptr) {
        sf::RectangleShape& obj = object->getObject();
        auto [topLeft, topRight, bottomLeft, bottomRight] = object->getBoundingBox();

        if (coordsInRectangle(mouseWindowPositionView, topLeft, topRight, bottomLeft, bottomRight)) {
            location_objects.changeHiglightObj(objectId);
            obj.setPosition(mouseWindowPositionView - obj.getSize() / 2.0f);
            return true;
        }
        else
            location_objects.changeHiglightObj(0);
        return false;
    }
}

void SafeAFriend::editPositionOfObject()
{
    if (isEditMode && isLeftMouseButtonPressed) {
        int id = location_objects.getHighlightObjId();
        if (id != 0) {
            tryMoveObject(id);
            return; 
        }

        for (auto& pair : location_objects.getAllObjects()) {
            if (pair.first != id) { 
                if (tryMoveObject(pair.first))
                    return;
            }
        }
    }
}

void SafeAFriend::scrollTexturesInSideBoard(float delta)
{
    int new_scrolled_index = scrolled_index + delta;
    std::cout << new_scrolled_index << std::endl;
    if (new_scrolled_index >= 0 && new_scrolled_index <= static_cast<int>(Texture::SideEditBorder))
    {
        scrolled_index += delta;
        int index = 0;

        for (auto& pair : objects_to_insert_in_edit_mode.getAllObjects()) {
            if (index > 0) { 
                sf::RectangleShape& obj = pair.second->getObject();
                obj.move(0, delta * textureHeight);
            }
            ++index;
        }
    }
}

bool SafeAFriend::tryToDeleteObjectInEditMode()
{
    for (auto& pair : location_objects.getAllObjects()) {
        if (pair.first == location_objects.getHighlightObjId()) {
            location_objects.RemoveObject(pair.first);
            return true;
        }
    }
    return false;
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
    if (isEditMode) {
         for (const auto& pair : objects_to_insert_in_edit_mode.getAllObjects()) {
                window->draw(pair.second->getObject());
         }
         for (const auto& pair : location_objects.getAllObjects()) {
             window->draw(pair.second->getObject());
         }
    }
    else {
        for (const auto& pair : location_objects.getAllObjects()) {
            window->draw(pair.second->getObject());
        }
    }
   

    window->display();
}
