#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include <Book/ResourceIdentifiers.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <functional>


class PlayerHue;



struct HueData
{
	int								hitpoints;
	float							speed;
	Textures::ID					texture;
	sf::IntRect						textureRect;
	bool							hasMarcheAnimation;
};


struct PickupData
{
	std::function<void(PlayerHue&)>	action;
	Textures::ID					texture;
	sf::IntRect						textureRect;
};

struct ParticleData
{
	sf::Color						color;
	sf::Time						lifetime;
};


std::vector<HueData>		initializePlayerHueData();
std::vector<PickupData>		initializePickupData();
std::vector<ParticleData>	initializeParticleData();

#endif // DATATABLES_HPP