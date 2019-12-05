#ifndef SCENENODE_HPP
#define SCENENODE_HPP

// #include <iostream>
// #include <map>
// #include <string>
// #include <memory>
// #include <stdexcept>
// #include <vector>
// #include <cassert>
// #include <algorithm>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>


#include<Book/Category.hpp>


#include <vector>
#include <set>
#include <memory>
#include <utility>

struct Command;
class CommandQueue;


class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> Ptr;
		typedef std::pair<SceneNode*, SceneNode*> Pair; //pointeur sui stock les collisions

    public:
                        SceneNode();
                        ~SceneNode();

        void            attachChild(Ptr child);
        Ptr             detachChild(const SceneNode& node);

        void            update(sf::Time dt);

        sf::Transform   getWorldTransform() const;
        sf::Vector2f    getWorldPosition() const;
        
        virtual unsigned int     getCategory() const;
        void                     onCommand(const Command& command, sf::Time dt);

        void					checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
		void					checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
		void					removeWrecks();
		virtual sf::FloatRect	getBoundingRect() const;
		virtual bool			isMarkedForRemoval() const;
		virtual bool			isDestroyed() const;

    private:
        virtual void        updateCurrent(sf::Time dt);
        void                updateChildren(sf::Time dt);

    private:
        virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void			drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
        void			drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        std::vector<Ptr>    mChildren;
        SceneNode*          mParent;
    
};

bool	collision(const SceneNode& lhs, const SceneNode& rhs);
float	distance(const SceneNode& lhs, const SceneNode& rhs);





#endif