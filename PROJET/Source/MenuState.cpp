#include <Book/MenuState.hpp>
#include <Book/ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mOptions()
, mOptionIndex(0)
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	sf::Font& font = context.fonts->get(Fonts::Main);

	mBackgroundSprite.setTexture(texture);
	
	// A simple menu demonstration
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	sf::FloatRect bounds = playOption.getLocalBounds();
	playOption.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	mOptions.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	bounds = exitOption.getLocalBounds();
	exitOption.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
	mOptions.push_back(exitOption);

	updateOptionText();
}

MenuState::~MenuState()
{
    
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	for(const sf::Text& text : mOptions)
		window.draw(text);
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
		return false;

    if(event.key.code == sf::Keyboard::Up)
    {
        if(mOptionIndex > 0)
            mOptionIndex--;
        else
            mOptionIndex = mOptions.size() - 1;

        updateOptionText();
    }
    else if(event.key.code == sf::Keyboard::Down)
    {
        if(mOptionIndex < mOptions.size() - 1)
            mOptionIndex++;
        else
            mOptionIndex = 0;

        updateOptionText();        
    }
    else if(event.key.code == sf::Keyboard::Return)
    {
        if(mOptionIndex == Play)
        {
            requestStackPop();
            requestStackPush(States::Game);
        }
        else if(mOptionIndex == Exit)
        {
            requestStackPop();
        }
    }
    
    return true;
    
}

void MenuState::updateOptionText()
{
    if(mOptions.empty())
        return;
    
    for(sf::Text& text : mOptions)
        text.setColor(sf::Color::White);

    mOptions[mOptionIndex].setColor(sf::Color::Red);
}