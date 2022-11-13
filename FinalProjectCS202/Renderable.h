#pragma once

class Renderable {
public:
    // TODO: any parameter?
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};