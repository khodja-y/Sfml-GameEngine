#include <Book/World.hpp>

#include <algorithm>
#include <cmath>
#include <limits>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System.hpp>



World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mWorldBounds(0.f,                           //x
               0.f,                           //y
               2000.f,                        //width
               mWorldView.getSize().y)       //height
, mSpawnPosition((mWorldView.getSize().x / 2.f) , mWorldBounds.height - mWorldView.getSize().y / 2.f)  
, mScrollSpeed(50.f)                        
, mPlayerHue(nullptr)
, mCommandQueue()
{
    loadTextures();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);
    mWorldView.setSize(320.f, 240.f);
}


World::~World()
{
	
}

void World::update(sf::Time dt)
{

    //camera qui suit le perso
    mWorldView.setCenter(mPlayerHue->getPosition().x + 60.f, mPlayerHue->getPosition().y - 50.f);
    mPlayerHue->setVelocity(0.f, 0.f);


    //forward commands to the scene graphe
    while(!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    mSceneGraph.update(dt);
    adaptPlayerPosition();
    adaptViewPosition();
        
}

void World::loadTextures()
{
    mTextures.load(Textures::Hue, "Media/Textures/girl.png");
    mTextures.load(Textures::Fond, "Media/Textures/Desert.png");
    mTextures.load(Textures::Sol, "Media/Textures/b_scrollgrass1.png");
}


void World::buildScene()
{
    
    for(std::size_t i = 0; i < LayerCount; i++){
        SceneNode::Ptr Layer(new SceneNode());
        mSceneLayers[i] = Layer.get();

        mSceneGraph.attachChild(std::move(Layer));
    }


    //texture de fond
    sf::Texture& texture = mTextures.get(Textures::Fond);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);



    //lier la texture du fond avec le noeud 
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));


    sf::Texture& terre = mTextures.get(Textures::Sol);
    sf::IntRect terreRect(mWorldBounds);
    terre.setRepeated(true);

    std::unique_ptr<SpriteNode> solSprite(new SpriteNode(terre, terreRect));
    solSprite->setPosition(0.f, mSpawnPosition.y + 200.f);
    mSceneLayers[Sol]->attachChild(std::move(solSprite));

    
    
    std::unique_ptr<PlayerHue> leader(new PlayerHue(PlayerHue::Hue, mTextures));
    mPlayerHue = leader.get();
    mPlayerHue->setPosition(mSpawnPosition.x, mSpawnPosition.y + 190.f);
    mPlayerHue->setVelocity(0.f, 0.f);
    mSceneLayers[Air]->attachChild(std::move(leader));

}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds(mWorldBounds);
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerHue->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerHue->setPosition(position);


}

void World::adaptViewPosition()
{

	sf::FloatRect viewBounds(mWorldBounds);
	const float borderDistance = 160.f;

	sf::Vector2f position = mWorldView.getCenter();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	// position.y = std::max(position.y, viewBounds.top + borderDistance);
	// position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mWorldView.setCenter(position);


}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = mPlayerHue->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerHue->setVelocity(velocity / std::sqrt(2.f));

	// Add scrolling velocity
	mPlayerHue->marcher(velocity.x, 0.f);
}

