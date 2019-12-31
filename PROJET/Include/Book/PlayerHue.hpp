#ifndef PLAYERHUE_HPP
#define PLAYERHUE_HPP

#include <Book/ResourceIdentifiers.hpp>
#include <Book/Entity.hpp>
#include <Book/CommandQueue.hpp>
#include <Book/Animation.hpp>

#include <SFML/Graphics/Sprite.hpp>


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
        
        

        // void            handleEvent(const sf::Event& event, CommandQueue& commands);
        // void            handleRealtimeInput(CommandQueue& commands);
        
        virtual unsigned int    getCategory() const;
        sf::FloatRect           getBoundingRect() const;

        virtual void            remove();
        virtual bool 			isMarkedForRemoval() const;

    private:

        virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void 			updateCurrent(sf::Time dt, CommandQueue& commands);
		// void					updateMovementPattern(sf::Time dt);

        void                    updateMarcheAnimation();


    private:
        Type            mType;
        sf::Sprite      mSprite;

        bool            mShowMort;

        bool            mOnGround;

        Animation       mMarche;
        Animation       mMort;

};

#endif
