#include <Book/PlayerHue.hpp>
#include <Book/ResourceIdentifiers.hpp>
#include <Book/ResourceHolder.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>



PlayerHue::PlayerHue(const TextureHolder& textures) 
: mSprite(textures.get(Textures::Hue))
{
    sf::FloatRect bounds = mSprite.getGlobalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    mSprite.setScale(0.1, 0.1);
}

void PlayerHue::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void PlayerHue::jump(){

    // int speedJump = 5.f;
    // sf::Vector2f position = getPosition();

    // for(int i=0; i<1000; i++)
    //     setPosition(getPosition().x, getPosition().y - speedJump);

    // setPosition(position.x, position.y);
}

unsigned int PlayerHue::getCategory() const
{
    return Category::PlayerHue;
}

