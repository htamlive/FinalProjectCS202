#include "Animal.h"
#include "TextureHolder.h"
#include "Consts.h"

Animal::Animal(sf::Vector2f velocity, float x, float y, float w, float h, Texture::ID texture) : Entity(velocity, x, y,
                                                                                                        w, h,
                                                                                                        texture) {}