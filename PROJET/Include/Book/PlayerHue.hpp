#ifndef PLAYERHUE_HPP
#define PLAYERHUE_HPP

#include <Book/ResourceIdentifiers.hpp>
#include <Book/Entity.hpp>
#include <Book/CommandQueue.hpp>

#include <SFML/Graphics.hpp>


class PlayerHue : public Entity
{
    public:
        enum Type
        {
            Hue,
            TypeCount
        };

    public:
                        PlayerHue(Type type, const TextureHolder& textures);
                        PlayerHue();
                        ~PlayerHue();
        void            jump();
        
        virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        void            handleEvent(const sf::Event& event, CommandQueue& commands);
        void            handleRealtimeInput(CommandQueue& commands);
        
        virtual unsigned int    getCategory() const;

    private:
        Type            mType;
        sf::Sprite      mSprite;

};

#endif
