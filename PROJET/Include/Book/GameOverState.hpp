#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include <Book/State.hpp>
#include <Book/Container.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameOverState : public State
{
	public:
							GameOverState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		sf::Text			mGameOverText;
		sf::Time			mElapsedTime;
};

#endif // GAMEOVERSTATE_HPP