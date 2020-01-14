#include <Book/PlayerHue.hpp>
#include <Book/ResourceIdentifiers.hpp>
#include <Book/ResourceHolder.hpp>
#include <Book/DataTables.hpp>
#include <Book/Utility.hpp>
#include <Book/EmitterNode.hpp>
#include <Book/SoundNode.hpp>

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
, mMarche(textures.get(Textures::Hue))
, mShowMort(true)
, mOnGround(true)
, mPlayedDeathSound(false)
{
    mMarche.setFrameSize(sf::Vector2i(50,60));
    mMarche.setNumFrames(7);
    mMarche.setDuration(sf::seconds(2));

	mMort.setFrameSize(sf::Vector2i(250,250));
    mMort.setNumFrames(16);
    mMort.setDuration(sf::seconds(2));
	mMort.setScale(0.5,0.5);

    centerOrigin(mMort);

	centerOrigin(mMarche);

    centerOrigin(mSprite);
	

    sf::FloatRect bounds = mSprite.getGlobalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	mSprite.setScale(5,5);

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
	sf::Vector2f position = getPosition();
	float force = 5 * gravity * dt.asSeconds();
	setPosition(position.x, position.y - force * dt.asSeconds());

	if(getPosition().y > 390)
	{
		setPosition(position);
		force = 0;
		mOnGround = true;
		jumpCount = 0;
	}	
	updateMarcheAnimation();

	// if(Table[mType].hasMarcheAnimation)
	// {
	// 	// Roll left: Texture rect offset once
	// 	if (getVelocity().x < 0.f){
	// 		SoundEffect::ID soundEffect = SoundEffect::Pas;
	// 		playLocalSound(commands, soundEffect);
	// 	}

	// 	// Roll right: Texture rect offset twice
	// 	else if (getVelocity().x > 0.f){
	// 		SoundEffect::ID soundEffect = SoundEffect::Pas;
	// 		playLocalSound(commands, soundEffect);
	// 	}
		
	
	// }
	

	mPlayedDeathSound = true;


	if (isDestroyed())
	{
		if (!mPlayedDeathSound)
		{
			SoundEffect::ID soundEffect = SoundEffect::Dead;
			playLocalSound(commands, soundEffect);
			

			mPlayedDeathSound = true;
		}
		mMort.update(dt);
		return;
	}

	Entity::updateCurrent(dt, commands);
}



void PlayerHue::jump(sf::Time dt){

	sf::Vector2f velocity = getVelocity();
	velocity.x = 0;
	velocity.y = -2000.f;


	if(jumpCount < 2)
	{
		jumpCount++;
		setVelocity(velocity);
		mOnGround = false;
	}
	
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
			textureRect.left +=  textureRect.width;

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

void PlayerHue::playLocalSound(CommandQueue& commands, SoundEffect::ID effect)
{
	sf::Vector2f worldPosition = getWorldPosition();
	
	Command command;
	command.category = Category::SoundEffect;
	command.action = derivedAction<SoundNode>(
		[effect, worldPosition] (SoundNode& node, sf::Time)
		{
			node.playSound(effect, worldPosition);
		});

	commands.push(command);
}


