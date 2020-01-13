#include <Book/DataTables.hpp>
#include <Book/PlayerHue.hpp>
#include <Book/Pickup.hpp>
#include <Book/Particle.hpp>


using namespace std::placeholders;

std::vector<HueData> initializePlayerHueData()
{
	std::vector<HueData> data(PlayerHue::TypeCount);

	data[PlayerHue::Hue].hitpoints = 100;
    data[PlayerHue::Hue].speed = 200.f;
    data[PlayerHue::Hue].texture = Textures::Entities;
	data[PlayerHue::Hue].textureRect = sf::IntRect(0,0,15,15);
	data[PlayerHue::Hue].hasMarcheAnimation = true;

	return data;
}


std::vector<PickupData> initializePickupData()
{
	std::vector<PickupData> data(Pickup::TypeCount);
	
	data[Pickup::ColorFill].texture = Textures::ColorFill;
	data[Pickup::ColorFill].action = [] (PlayerHue& a) { a.destroy(); };
	data[Pickup::ColorFill].textureRect = sf::IntRect(0,0,256,256);
	

	return data;
}

std::vector<ParticleData> initializeParticleData()
{
	std::vector<ParticleData> data(Particle::ParticleCount);

	data[Particle::Propellant].color = sf::Color(255, 255, 50);
	data[Particle::Propellant].lifetime = sf::seconds(0.6f);

	data[Particle::Smoke].color = sf::Color(50, 50, 50);
	data[Particle::Smoke].lifetime = sf::seconds(4.f);

	return data;
}
