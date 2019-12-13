#include <Book/DataTables.hpp>
#include <Book/PlayerHue.hpp>
#include <Book/Pickup.hpp>


// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<HueData> initializeHueData()
{
	std::vector<HueData> data(PlayerHue::TypeCount);

	data[PlayerHue::Hue].hitpoints = 100;
    data[PlayerHue::Hue].speed = 200.f;
    data[PlayerHue::Hue].texture = Textures::Hue;

	return data;
}


std::vector<PickupData> initializePickupData()
{
	std::vector<PickupData> data(Pickup::TypeCount);
	
	data[Pickup::ColorFill].texture = Textures::ColorFill;
	data[Pickup::ColorFill].action = [] (PlayerHue& a) { a.repair(25); };
	

	return data;
}
