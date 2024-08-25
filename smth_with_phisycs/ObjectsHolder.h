#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "RenderObject.h"

class ObjectHolder {
private:
    std::unordered_map<int, std::unique_ptr<RenderObject>> objectHolder;
    int obj_id_with_border = 0;

public:
    RenderObject& Get(int id) const {
        return *objectHolder.at(id);
    }

    int getHighlightObjId() const {
        return obj_id_with_border;
    }

    void changeHiglightObj(int indx) {

        if (indx == 0) {
            if (obj_id_with_border != 0)
                objectHolder[obj_id_with_border]->hideBorder();

            obj_id_with_border = 0;
        }
        else if (objectHolder.find(indx) != objectHolder.end()) {
            if (obj_id_with_border != 0)
                objectHolder[obj_id_with_border]->hideBorder();

            obj_id_with_border = indx;
            objectHolder[obj_id_with_border]->showBorder();
        }
        else {
            std::cerr << "Object with ID " << indx << " not found in objectHolder." << std::endl;
        }
    }
    void AddObject(std::unique_ptr<RenderObject> object) {
        int id = object->getId(); 
        objectHolder[id] = std::move(object);
    }
    void RemoveObject(const int id) {
        auto it = objectHolder.find(id);

        if (it != objectHolder.end()) {
            if (obj_id_with_border == id) {
                obj_id_with_border = 0; 
            }
            objectHolder.erase(it); 
        }
        else {
            std::cerr << "Object with ID " << id << " not found in objectHolder." << std::endl;
        }
    }


    const std::unordered_map<int, std::unique_ptr<RenderObject>>& getAllObjects() const {
        return objectHolder;
    }

    void setPositionsFromFile() {
        std::ifstream file_pos_stream("Positions.txt");
        std::string line_in_file;

        if (!file_pos_stream) {
            std::cerr << "Failed to open file" << std::endl;
            return;
        }

        while (std::getline(file_pos_stream, line_in_file)) {
            size_t pos1 = line_in_file.find(' ');
            size_t pos2 = line_in_file.find(' ', pos1 + 1);

            if (pos1 == std::string::npos || pos2 == std::string::npos) {
                std::cerr << "Invalid line format: " << line_in_file << std::endl;
                continue;
            }

            int id = std::stoi(line_in_file.substr(0, pos1));
            std::string x_str = line_in_file.substr(pos1 + 1, pos2 - pos1 - 1);
            std::string y_str = line_in_file.substr(pos2 + 1);

            float x, y;
            try {
                x = std::stof(x_str);
                y = std::stof(y_str);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid coordinate format: " << line_in_file << std::endl;
                continue;
            }

            if (objectHolder.find(id) != objectHolder.end()) {
                objectHolder[id]->getObject().setPosition(sf::Vector2f(x, y));
            }
            else {
                std::cerr << "No object found with ID: " << id << std::endl;
            }
        }
    }

    void savePositionsToFile() {
        std::ofstream file_pos_stream("Positions.txt");

        if (!file_pos_stream) {
            std::cerr << "Failed to open file" << std::endl;
            return;
        }

        for (const auto& [id, object] : objectHolder) {
            sf::Vector2f position = object->getObject().getPosition();
            file_pos_stream << id << " " << position.x << " " << position.y << std::endl;
        }
    }
};