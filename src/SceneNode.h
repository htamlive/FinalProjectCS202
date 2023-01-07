#pragma once
#include "Enums.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>
#include <set>
#include <iostream>

#include "Consts.h"

/**
 * @brief A node in the scene graph.
 */
class SceneNode : public sf::Drawable,
                  public sf::Transformable,
                  private sf::NonCopyable {
public:
    typedef std::unique_ptr<SceneNode> Ptr;
    typedef std::pair<SceneNode*, SceneNode*> Pair;
    friend std::unique_ptr<SceneNode> loadNode(std::istream &in);

    SceneNode();

    /**
     * Add new child to the node
     *
     * @param child: the child to be added
     */
    virtual void attachChild(Ptr child);

    /**
     * Remove a child from the node
     *
     * @param child: reference to the to-be-deleted child
     *
     * @return a Ptr to child
     */
    virtual Ptr detachChild(const SceneNode &child);

    /**
     * Update the node and all the children node
     *
     * @param dt: time elapsed since last frame
     */
    virtual void update(sf::Time dt);

    /**
     * @return the absolute transform (all transform of node hierarchy combined)
     */
    sf::Transform getAbsTransform() const;

    /**
     * @return the absolute position (coordinate in the windows)
     */
    sf::Vector2f getAbsPosition() const;

    /**
     * Check collision between 2 SceneNode. Derived class from SceneNode should
     * implement `getBoundingRect` to use this function
     */
    friend bool checkCollision(const SceneNode& lnode, const SceneNode& rnode);

    /**
     * Check collision of the `node` with `this` and all children of `this`
     *
     * @param node Node to check collision
     * @param collisions Variables to store collision pair
     */
    void checkNodeCollision(SceneNode& node, std::set<Pair>& collisions);

    /**
     */
    void checkSceneCollision(SceneNode& node, std::set<Pair>& collisions);

    /**
     * Set the debug mode of the node
     * @param on: on/off
     * @param recursive: apply to all children
     */
    void setDebug(bool on, bool recursive = false);

    virtual Category::Type getCategory() const;

    virtual void saveNode(std::ostream& out) const;

    bool operator <(SceneNode const &other) const;

    /**
     * Implement this to allow collision detection
     */
    virtual sf::FloatRect getBoundingRect() const;

    virtual sf::FloatRect getLocalBounds() const;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const;

private:
    void drawBoundingBox(sf::RenderTarget& target, sf::RenderStates states) const;


    /**
     * Derived class should implement this method to draw itself
     *
     * @param target: Target to draw to 
     * @param state: State stored all the applied state forwarded from the
     * node's parent 
     */
    virtual void drawCurrent(sf::RenderTarget &target,
                             sf::RenderStates state) const;

    /**
     * Derived class should implement this method to update itself
     */
    virtual void updateCurrent(sf::Time dt);

    /**
     * Call the update methods of children
     */
    void updateChildren(sf::Time dt);

protected:
    virtual std::string getClassName() const;

    virtual void saveCurrentNode(std::ostream& out = std::cout) const;

    virtual void loadCurrentNode(std::istream& in = std::cin);

    virtual void onLoadingFinished();

    virtual bool shouldSave() const;

private:
    int idx = -1;
    bool debug = false;
    bool applyDebugToChildren = false;
    std::vector<Ptr> mChildren;
    SceneNode *mParent;
};

