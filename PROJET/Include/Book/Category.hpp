#ifndef CATEGORY_HPP
#define CATEGORY_HPP


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		SceneAirLayer		= 1 << 0,
		PlayerHue			= 1 << 1,
		Pickup				= 1 << 2,
		ParticleSystem		= 1 << 3,
		SoundEffect			= 1 << 4,

	};
}

#endif // CATEGORY_HPP
