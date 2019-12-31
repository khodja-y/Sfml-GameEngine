#include <Book/PlayerHue.hpp>
#include <Book/ResourceIdentifiers.hpp>
#include <Book/ResourceHolder.hpp>
#include <Book/DataTables.hpp>
#include <Book/Utility.hpp>
#include <Book/EmitterNode.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace
{
	const std::vector<HueData> Table = initializePlayerHueData();
}

PlayerHue::PlayerHue()
{

}

PlayerHue::~PlayerHue()
{
	
}

PlayerHue::PlayerHue(Type type, const TextureHolder& textures) 
: mType(type) 
, mSprite(textures.get(Table[type].texture), Table[type].textureRect)
, mMort(textures.get(Textures::Explosion))
, mShowMort(true)
, mOnGround(true)
{
    mMort.setFrameSize(sf::Vector2i(15,15));
    mMort.setNumFrames(8);
    mMort.setDuration(sf::seconds(2));
	mMort.setScale(5, 5);

    centerOrigin(mMort);

    centerOrigin(mSprite);
	

    sf::FloatRect bounds = mSprite.getGlobalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    mSprite.setScale(5, 5);

	// std::unique_ptr<EmitterNode> smoke(new EmitterNode(Particle::Smoke));
	// smoke->setPosition(0.f, getBoundingRect().height / 2.f);
	// attachChild(std::move(smoke));
}

void PlayerHue::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (isDestroyed() && mShowMort)
		target.draw(mMort, states);
	else
		target.draw(mSprite, states);
}

void PlayerHue::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	// Update texts and roll animation
	// updateTexts();
	updateMarcheAnimation();

	// Entity has been destroyed: Possibly drop pickup, mark for removal
	if (isDestroyed())
	{
		// checkPickupDrop(commands);
		mMort.update(dt);
		return;
	}

	// Check if bullets or missiles are fired
	// checkProjectileLaunch(dt, commands);

	// Update enemy movement pattern; apply velocity
	// updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);
}



void PlayerHue::jump(){

    int speedJump = 5.f;
    sf::Vector2f position = getPosition();

    for(int i=0; i<1000; i++)
        setPosition(getPosition().x, getPosition().y - speedJump);

    setPosition(position.x, position.y);
}

unsigned int PlayerHue::getCategory() const
{
    return Category::PlayerHue;
}

sf::FloatRect PlayerHue::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void PlayerHue::updateMarcheAnimation()
{
	if (Table[mType].hasMarcheAnimation)
	{
		sf::IntRect textureRect = Table[mType].textureRect;

		// Roll left: Texture rect offset once
		if (getVelocity().x < 0.f)
			textureRect.left += textureRect.width;

		// Roll right: Texture rect offset twice
		else if (getVelocity().x > 0.f)
			textureRect.left += 2 * textureRect.width;

		mSprite.setTextureRect(textureRect);
	}
}

bool PlayerHue::isMarkedForRemoval() const
{
	return isDestroyed() && (mMort.isFinished() || !mShowMort);
}

void PlayerHue::remove()
{
	Entity::remove();
	mShowMort = false;
}


// void PlayerHue::updateMovementPattern(sf::Time dt)
// {
// 	// Enemy airplane: Movement pattern
// 	const std::vector<Direction>& directions = Table[mType].directions;
// 	if (!directions.empty())
// 	{
// 		// Moved long enough in current direction: Change direction
// 		if (mTravelledDistance > directions[mDirectionIndex].distance)
// 		{
// 			mDirectionIndex = (mDirectionIndex + 1) % directions.size();
// 			mTravelledDistance = 0.f;
// 		}

// 		// Compute velocity from direction
// 		float radians = toRadian(directions[mDirectionIndex].angle + 90.f);
// 		float vx = getMaxSpeed() * std::cos(radians);
// 		float vy = getMaxSpeed() * std::sin(radians);

// 		setVelocity(vx, vy);

// 		mTravelledDistance += getMaxSpeed() * dt.asSeconds();
// 	}
// }
