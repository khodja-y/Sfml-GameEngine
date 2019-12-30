#ifndef WORLD_HPP
#define WORLD_HPP


#include <Book/ResourceHolder.hpp>
#include <Book/PlayerHue.hpp>
#include <Book/SpriteNode.hpp>
#include <Book/SceneNode.hpp>
#include <Book/ResourceIdentifiers.hpp>
#include <Book/CommandQueue.hpp>
#include <Book/Pickup.hpp>
#include <Book/State.hpp>
#include <Book/Map.hpp>
#include <Book/ParticleNode.hpp>
#include <Book/PostEffect.hpp>
#include <Book/BloomEffect.hpp>
#include <Book/SoundPlayer.hpp>

#include <array>
#include <queue>

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/NonCopyable.hpp>



namespace sf
{
    class RenderTarget;
}

class World : private sf::NonCopyable
{
    public:
            explicit            World(sf::RenderTarget& target, FontHolder& fonts, SoundPlayer& sounds);
                                ~World();
            void                update(sf::Time dt);
            void                updateSounds();
            void                draw();

            CommandQueue&       getCommandQueue();

            bool 				hasAlivePlayer() const;
	        bool 			    hasPlayerReachedEnd() const;

    private:
            void                loadTextures();

            void                buildScene();

            void                adaptPlayerPosition();
            void	            adaptPlayerVelocity();
            void                adaptViewPosition();

            void		handleCollisions();

            sf::FloatRect	getViewBounds() const;
      
    private:
            enum Layer
            {
                Background,
                LowerAir,
                UpperAir,
                LayerCount
            };

            struct SpawnPoint 
		{
			SpawnPoint(PlayerHue::Type type, float x, float y)
			: type(type)
			, x(x)
			, y(y)
			{
			}

			PlayerHue::Type type;
			float x;
			float y;
		};

    private:
            sf::RenderTarget&					mTarget;
            sf::RenderTexture					mSceneTexture;
            sf::View						mWorldView;
            TextureHolder					mTextures;
            FontHolder&						mFonts;
            SoundPlayer&                    mSounds;

            //scene
            SceneNode						mSceneGraph;
	    std::array<SceneNode*, LayerCount>	                mSceneLayers;
            CommandQueue                                        mCommandQueue;

            sf::FloatRect               mWorldBounds;
            sf::Vector2f                mSpawnPosition; // position du joueur au début
            float                       mScrollSpeed;
            PlayerHue*                  mPlayerHue;
            Map                         mMap;

            BloomEffect                 mBloomEffect;
            
            

};



#endif
