#include "SceneNode.h"
#include "Entity.h"
#include <iostream>
#include <memory>
#include <ostream>

std::unique_ptr<SceneNode> loadNode(std::istream &in = std::cin);
