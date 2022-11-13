#pragma once
#include <vector>

#include <stack>
#include <map>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"

using namespace sf;

class Entity
{
private:
	void initVariables();
protected:
	Texture* texture;
	Sprite* sprite;
	float movementSpeed;
public:
	Entity();
	virtual ~Entity();

	void createSprite(Texture* texture);

	virtual void move(const float& dt, const float dir_x, const float dir_y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

