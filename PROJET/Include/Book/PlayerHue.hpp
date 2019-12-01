#ifndef PLAYERHUE_HPP
#define PLAYERHUE_HPP

#include <Book/ResourceIdentifiers.hpp>
#include <Book/Entity.hpp>
#include <Book/CommandQueue.hpp>

#include <SFML/Graphics.hpp>


class PlayerHue : public Entity
{
    public:
                        PlayerHue(const TextureHolder& textures);
                        PlayerHue();
                        ~PlayerHue();
        void            jump();
        
        virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        void            handleEvent(const sf::Event& event, CommandQueue& commands);
        void            handleRealtimeInput(CommandQueue& commands);
        
        virtual unsigned int    getCategory() const;

    private:
        sf::Sprite      mSprite;

};

#endif
