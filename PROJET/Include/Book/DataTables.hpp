#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include <Book/ResourceIdentifiers.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

#include <vector>
#include <functional>


class PlayerHue;

struct Direction
{
	Direction(float angle, float distance)
	: angle(angle)
	, distance(distance)
	{
	}

	float angle;
	float distance;
};

struct HueData
{
	int								hitpoints;
	float							speed;
	Textures::ID					texture;
	std::vector<Direction>			directions;
};


struct PickupData
{
	std::function<void(PlayerHue&)>	action;
	Textures::ID					texture;
};


std::vector<PlayerHue>	initializeAircraftData();
std::vector<PickupData>		initializePickupData();

#endif // DATATABLES_HPP