#include <Book/SceneNode.hpp>
#include <Book/Utility.hpp>
#include <Book/Command.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>


SceneNode::SceneNode() 
: mChildren() 
, mParent(nullptr)
{

}

SceneNode::~SceneNode()
{
    
}

void SceneNode::attachChild(Ptr child)
{

    child->mParent = this;
    mChildren.push_back(std::move(child));

}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{

    auto found = std::find_if(mChildren.begin(), mChildren.end(), 
    [&] (Ptr& p) -> bool {return p.get() && &node;});

    assert(found != mChildren.end());

    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;

}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    //draw the derived object
    drawCurrent(target, states);
	drawChildren(target, states);

    // for(const Ptr& child : mChildren){
    //     child->draw(target, states);
    // }

    drawBoundingRect(target, states);
}

void SceneNode::update(sf::Time dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt)
{

}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Ptr& child : mChildren)
		child->draw(target, states);
}

void SceneNode::updateChildren(sf::Time dt)
{
    for(Ptr& child : mChildren)
    {
        child->update(dt);
    }
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for(const SceneNode* node = this; node != nullptr; node = node->mParent)
    {
        transform = node->getTransform() * transform;
    } 

    return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}


unsigned int SceneNode::getCategory() const
{
    return Category::Scene;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
    if(command.category & getCategory())
        command.action(*this, dt);

    for(Ptr& child : mChildren)
        child->onCommand(command, dt);
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}

bool collision(const SceneNode& lhs, const SceneNode& rhs)
{
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

float distance(const SceneNode& lhs, const SceneNode& rhs)
{
	return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs)
{
	checkNodeCollision(sceneGraph, collisionPairs);

	for(Ptr& child : sceneGraph.mChildren)
		checkSceneCollision(*child, collisionPairs);
}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs)
{
	if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
		collisionPairs.insert(std::minmax(this, &node));

	for (Ptr& child : mChildren)
		child->checkNodeCollision(node, collisionPairs);
}

bool SceneNode::isMarkedForRemoval() const
{
	// By default, remove node if entity is destroyed
	return isDestroyed();
}

bool SceneNode::isDestroyed() const
{
	// By default, scene node needn't be removed
	return false;
}

void SceneNode::removeWrecks()
{
	// Remove all children which request so
	auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
	mChildren.erase(wreckfieldBegin, mChildren.end());

	// Call function recursively for all remaining children
	std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeWrecks));
}