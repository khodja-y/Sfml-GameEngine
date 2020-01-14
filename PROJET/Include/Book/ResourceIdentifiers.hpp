#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

namespace Textures
{
	enum ID
	{
		Hue,
		Fond,
		Sol,
		ColorFill,

		Entities,
		Map,
		Jungle,
		TitleScreen,
		Buttons,
		Explosion,
		Particle,
		FinishLine,
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
	};
}

namespace Shaders
{
	enum ID
	{
		BrightnessPass,
		DownSamplePass,
		GaussianBlurPass,
		AddPass,
	};
}

namespace Music
{
	enum ID
	{
		MenuTheme,
		LevelTheme,
	};
}

namespace SoundEffect
{
	enum ID
	{
		Pas,
		Dead,
		CollectPickup,
		Button,
	};
}


// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> 			TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> 				FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID>				ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;

#endif // RESOURCEIDENTIFIERS_HPP
