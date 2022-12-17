//#include "Effect.h"
//#include "Player.h"
//
//Effect::Effect(Entity *entity, Texture::ID textureID, sf::Vector2f position,
//               sf::Vector2f size, sf::Time duration)
//    : duration(duration), entity(entity),
//      animation(textureID, sf::seconds(5), false) {
//    if (!entity) {
//        throw std::invalid_argument("Entity cannot be null");
//    }
//}
//
//void Effect::updateCurrent(sf::Time dt) {
//    animation.update(dt);
//    if (duration <= sf::Time::Zero) {
//        destroy();
//    }
//    duration -= dt;
//}
//
//void Effect::drawCurrent(sf::RenderTarget &target,
//                         sf::RenderStates states) const {
//    target.draw(animation.toSprite(), states);
//}
//
//void Effect::destroy() {
//    entity->detachChild(*this);
//    delete this;
//}
