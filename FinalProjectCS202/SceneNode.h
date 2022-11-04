#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <memory>
#include <vector>

class SceneNode : public sf::Drawable,
                  public sf::Transformable,
                  private sf::NonCopyable {
  public:
    typedef std::unique_ptr<SceneNode> SceneNodePtr;

    SceneNode();

    void attachChild(SceneNodePtr child);
    SceneNodePtr detachChild(const SceneNode &child);

  private:
    void draw(sf::RenderTarget &target, sf::RenderStates state) const final;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const = 0;

  private:
    std::vector<SceneNodePtr> mChildren;
    SceneNode *mParent;
};
