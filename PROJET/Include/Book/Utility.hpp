#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/Window/Keyboard.hpp>

#include <SFML/System/Vector2.hpp>

#include <Book/Animation.hpp>

#include <sstream>

namespace sf
{
	class Sprite;
	class Text;
}

// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

// Convert enumerators to strings
std::string toString(sf::Keyboard::Key key);

// Call setOrigin() with the center of the object
void			centerOrigin(sf::Sprite& sprite);
void			centerOrigin(sf::Text& text);
void			centerOrigin(Animation& animation);

// Degree/radian conversion
float			toDegree(float radian);
float			toRadian(float degree);

// Random number generation
int				randomInt(int exclusiveMax);

// Vector operations
float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);



#include <Book/Utility.inl>
#endif // UTILITY_HPP
