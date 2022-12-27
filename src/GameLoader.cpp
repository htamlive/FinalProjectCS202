#include "GameLoader.h"
#include "SceneNode.h"
#include <string>

void ignoreText(std::istream &in) {
    std::string line;
    while (true) {
        try {
            std::getline(in, line);
            std::stoi(line);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
            break;
        }
    }
}

std::unique_ptr<SceneNode> loadNode(std::istream &in) {
    std::string line;
    getline(in, line);
    std::cout << line << std::endl;
    std::unique_ptr<SceneNode> node;
    if (line == "SceneNode") {
        node = std::make_unique<SceneNode>();
        node->loadCurrentNode(in);
    } else if (line == "Entity") {
        node = std::make_unique<Entity>();
        node->loadCurrentNode(in);
    } else {
        std::cout << "Unknown node type: " << line << std::endl;
    }
    int n;
    in >> n;
    in.ignore();
    for (int j = 0; j < n; j++) {
        node->attachChild(loadNode(in));
    }
    return node;
}
