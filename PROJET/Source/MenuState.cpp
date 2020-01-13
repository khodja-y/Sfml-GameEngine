#include <Book/MenuState.hpp>
#include <Book/ResourceHolder.hpp>
#include <Book/Button.hpp>
#include <Book/MusicPlayer.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	// sf::Font& font = context.fonts->get(Fonts::Main);

	mBackgroundSprite.setTexture(texture);

    

    //playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    auto playButton = std::make_shared<GUI::Button>(context);
    playButton->setPosition(100, 250);
    playButton->setText("Play");
    playButton->setCallback([this] ()
    {
        requestStackPop();
        requestStackPush(States::Game);
    });


    //settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    auto settingsButton = std::make_shared<GUI::Button>(context);
	settingsButton->setPosition(100, 300);
	settingsButton->setText("Settings");
	settingsButton->setCallback([this] ()
	{
		requestStackPush(States::Settings);
	});

    //exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    auto exitButton = std::make_shared<GUI::Button>(context);
    exitButton->setPosition(100, 350);
    exitButton->setText("Exit");
    exitButton->setCallback([this] ()
    {
        requestStackPop();
    });

    mGUIContainer.pack(playButton);
    mGUIContainer.pack(settingsButton);
    mGUIContainer.pack(exitButton);
    
    
    //play menu music 
    context.music->setVolume(10.f);
    context.music->play(Music::MenuTheme);
    
    
	
}

MenuState::~MenuState()
{
    
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

    window.draw(mGUIContainer);

}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    mGUIContainer.handleEvent(event);
    return false;
   
    
}
