#ifndef WORLD_HPP
#define WORLD_HPP


#include <Book/ResourceHolder.hpp>
#include <Book/PlayerHue.hpp>
#include <Book/SpriteNode.hpp>
#include <Book/SceneNode.hpp>
#include <Book/ResourceIdentifiers.hpp>
#include <Book/CommandQueue.hpp>

#include <array>
#include <queue>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


namespace sf
{
    class RenderWindow;
}

class World : private sf::NonCopyable
{
    public:
            explicit            World(sf::RenderWindow& window);
                                ~World();
            void                update(sf::Time dt);
            void                draw();

            CommandQueue&       getCommandQueue();

    private:
            void            loadTextures();
            void            buildScene();

            void        adaptPlayerPosition();
            void	adaptPlayerVelocity();
            void        adaptViewPosition();
      
    private:
            enum Layer
            {
                Background,
                Air,
                Sol,
                LayerCount,
            };

    private:
            sf::RenderWindow&   mWindow;
            sf::View            mWorldView;
            TextureHolder       mTextures;

            //scene
            SceneNode						mSceneGraph;
	    std::array<SceneNode*, LayerCount>	                mSceneLayers;
            CommandQueue                                        mCommandQueue;

            sf::FloatRect               mWorldBounds;
            sf::Vector2f                mSpawnPosition; //position du joueur au début
            float                       mScrollSpeed;
            PlayerHue*                  mPlayerHue;
            

};



#endif
