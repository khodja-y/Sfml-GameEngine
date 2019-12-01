#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <vector>
#include <cassert>
#include <algorithm>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

#include<Book/Category.hpp>
#include<Book/Command.hpp>


class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> Ptr;

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

    private:
        virtual void        updateCurrent(sf::Time dt);
        void                updateChildren(sf::Time dt);

    private:
        virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        std::vector<Ptr>    mChildren;
        SceneNode*          mParent;
    
};







#endif