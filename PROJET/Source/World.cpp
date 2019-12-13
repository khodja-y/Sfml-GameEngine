#include <Book/World.hpp>

#include <algorithm>
#include <cmath>
#include <limits>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System.hpp>



World::World(sf::RenderWindow& window, FontHolder& fonts)
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
, mFonts(fonts)
{
    loadTextures();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);
    // mWorldView.setSize(320.f, 240.f);
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

    // Collision detection and response (may destroy entities)
	handleCollisions();

    // Remove all destroyed entities (ennemies si on en met)
	mSceneGraph.removeWrecks();

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
    mPlayerHue->setPosition(mSpawnPosition.x, mSpawnPosition.y + 140.f);
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
	const float borderDistance = 60.f;

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
	const float borderDistance = 320.f;

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

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}

void World::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

	for(SceneNode::Pair pair : collisionPairs)
	{
        // SI LE PLAYER TOUCHE UN ENNEMIE DIRECT
		// if (matchesCategories(pair, Category::PlayerAircraft, Category::EnemyAircraft))
		// {
		// 	auto& player = static_cast<Aircraft&>(*pair.first);
		// 	auto& enemy = static_cast<Aircraft&>(*pair.second);

		// 	// Collision: Player damage = enemy's remaining HP
		// 	player.damage(enemy.getHitpoints());
		// 	enemy.destroy();
		// }

		// else 
        if (matchesCategories(pair, Category::PlayerHue, Category::Pickup))
		{
			auto& player = static_cast<PlayerHue&>(*pair.first);
			auto& pickup = static_cast<Pickup&>(*pair.second);

			// Apply pickup effect to player, destroy projectile AJOUT DE LA COULEUR DANS SA PALETTE
			pickup.apply(player);
			pickup.destroy();
		}

        // PAREIL POUR LES ENNEMIES
		// else if (matchesCategories(pair, Category::EnemyAircraft, Category::AlliedProjectile)
		// 	  || matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile))
		// {
		// 	auto& aircraft = static_cast<Aircraft&>(*pair.first);
		// 	auto& projectile = static_cast<Projectile&>(*pair.second);

		// 	// Apply projectile damage to aircraft, destroy projectile
		// 	aircraft.damage(projectile.getDamage());
		// 	projectile.destroy();
		// }
	}
}

