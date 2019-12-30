#ifndef ENTITY_HPP
#define ENTITY_HPP


#include <Book/SceneNode.hpp>
#include <Book/CommandQueue.hpp>

class Entity : public SceneNode
{
    public:
       explicit         Entity();
                        ~Entity();
        explicit        Entity(int hitpoints);

        void            setVelocity(sf::Vector2f velocity);
        void            setVelocity(float vx, float vy);

        void            marcher(sf::Vector2f velocity);
        void            marcher(float vx, float vy);

        void            jump(sf::Vector2f velocity);
        void            jump(float vx, float vy);
        
        sf::Vector2f    getVelocity() const;


        int                 getHitPoints() const;
        void                setHitPoints(int hitPoints);
        void				repair(int points);
		void				damage(int points);
		void				destroy();
		virtual void		remove();
		virtual bool		isDestroyed() const;

    protected:
        virtual void        updateCurrent(sf::Time dt, CommandQueue& commands);
        virtual void        updateCurrent(sf::Time dt);

    private:
        sf::Vector2f    mVelocity;
        int             mHitPoints;

    
};





#endif
