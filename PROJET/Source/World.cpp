#include <Book/World.hpp>
#include <Book/SoundNode.hpp>

#include <algorithm>
#include <cmath>
#include <limits>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System.hpp>



World::World(sf::RenderTarget& outputTarget, FontHolder& fonts, SoundPlayer& sounds)
: mTarget(outputTarget)
, mSceneTexture()
, mWorldView(mTarget.getDefaultView())
, mTextures()
, mFonts(fonts)
, mSounds(sounds)
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, 5000, mWorldView.getSize().y) // (x, y, width, height)
, mSpawnPosition((mWorldView.getSize().x / 2.f) , mWorldBounds.height - mWorldView.getSize().y / 2.f)  
, mScrollSpeed(-50.f)                        
, mPlayerHue(nullptr)
, mCommandQueue()
{
	mSceneTexture.create(mTarget.getSize().x, mTarget.getSize().y);

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
	adaptPlayerVelocity();

    // Collision detection and response (may destroy entities)
	handleCollisions();

    // Remove all destroyed entities (ennemies si on en met)
	mSceneGraph.removeWrecks();

    mSceneGraph.update(dt, mCommandQueue);
    adaptPlayerPosition();
    adaptViewPosition();
        
}

void World::loadTextures()
{
    // mTextures.load(Textures::Hue, "Media/Textures/player.png");
    mTextures.load(Textures::Fond, "Media/Textures/Jungle.png");
    mTextures.load(Textures::Sol, "Media/Textures/b_scrollgrass1.png");
	mTextures.load(Textures::Entities, "Media/Textures/player.png");
	mTextures.load(Textures::ColorFill, "Media/Textures/color_circle.png");

	mTextures.load(Textures::Explosion, "Media/Textures/player.png");
	mTextures.load(Textures::Particle, "Media/Textures/Particle.png");
}


void World::buildScene()
{
    
    for(std::size_t i = 0; i < LayerCount; i++){
		Category::Type category = (i == LowerAir) ? Category::SceneAirLayer : Category::None;

        SceneNode::Ptr Layer(new SceneNode(category));
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
    mSceneLayers[UpperAir]->attachChild(std::move(solSprite));


	

    std::unique_ptr<Pickup> color(new Pickup(Pickup::ColorFill, mTextures));
    color->setPosition(mSpawnPosition.x + 200.f, mSpawnPosition.y + 140.f);
	color->setScale(0.25, 0.25);
    mSceneLayers[UpperAir]->attachChild(std::move(color));
    
    
    std::unique_ptr<PlayerHue> leader(new PlayerHue(PlayerHue::Hue, mTextures));
    mPlayerHue = leader.get();
    mPlayerHue->setPosition(mSpawnPosition.x, mSpawnPosition.y + 140.f);
    mPlayerHue->setVelocity(0.f, 0.f);
    mSceneLayers[UpperAir]->attachChild(std::move(leader));


	const int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2,

    };

    if (!mMap.load("Media/Textures/tilesheet.png", sf::Vector2u(32, 32), level, 24, 10))
        return;

	std::unique_ptr<Map> map(new Map(mMap.getVertices(), mMap.getTileSet()));
	// mSceneLayers[UpperAir]->attachChild(std::move(map));

	// Add particle node to the scene
	std::unique_ptr<ParticleNode> smokeNode(new ParticleNode(Particle::Smoke, mTextures));
	mSceneLayers[LowerAir]->attachChild(std::move(smokeNode));

	// Add propellant particle node to the scene
	std::unique_ptr<ParticleNode> propellantNode(new ParticleNode(Particle::Propellant, mTextures));
	mSceneLayers[LowerAir]->attachChild(std::move(propellantNode));

	// Add sound effect node
	std::unique_ptr<SoundNode> soundNode(new SoundNode(mSounds));
	mSceneGraph.attachChild(std::move(soundNode));


}

void World::updateSounds()
{
	// Set listener's position to player position
	mSounds.setListenerPosition(mPlayerHue->getWorldPosition());

	// Remove unused sounds
	mSounds.removeStoppedSounds();
}

void World::draw()
{
    if (PostEffect::isSupported())
	{
		mSceneTexture.clear();
		mSceneTexture.setView(mWorldView);
		mSceneTexture.draw(mSceneGraph);
		mSceneTexture.display();
		
		mBloomEffect.apply(mSceneTexture, mTarget);
	}
	else
	{
		mTarget.setView(mWorldView);
		mTarget.draw(mSceneGraph);
	}
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

bool World::hasAlivePlayer() const
{
	return !mPlayerHue->isMarkedForRemoval();
}

bool World::hasPlayerReachedEnd() const
{
	return !mWorldBounds.contains(mPlayerHue->getPosition());
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

        // SI LE PLAYER TOUCHE UN PROJECTILE ENNEMIE OU QU'UN ENNEMIE TOUCHE UN PROJECTILE ALLIÉ
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

sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

