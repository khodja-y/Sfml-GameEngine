// #include <SFML/Window.hpp>
// #include <SFML/OpenGL.hpp>
// #include <SFML/Graphics.hpp>

// #include <SFML/Graphics/Rect.hpp>

// #include <SFML/Graphics/RenderTarget.hpp>
// #include <SFML/Graphics/RenderStates.hpp>

#include <iostream>
#include <cmath>
#include <functional>

#include <Book/Game.hpp>
#include <Book/StringHelpers.hpp>

// #include "ResourceHolder.hpp"





// namespace Textures
// {
// 	enum ID
// 	{
// 		PlayerHue,
// 	};
// }

const float Game::PlayerSpeed = 200.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
: mWindow(sf::VideoMode(640, 480), "SFML Application", sf::Style::Default)
, mWorld(mWindow)
, mTexture()
, mPlayer()
, mFont()
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
, mIsPaused(false)
{

	
	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(5);

	//This can avoid graphical artifacts such as screen tearing, where a part of your
	//window shows the old frame, and another the new one.
	mWindow.setVerticalSyncEnabled(true);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	//game loop
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			if(!mIsPaused)update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

// void Game::processEvents()
// {
// 	sf::Event event;
// 	while (mWindow.pollEvent(event))
// 	{
// 		switch (event.type)
// 		{
// 			case sf::Event::GainedFocus:
// 				mIsPaused = false;
// 				break;
// 			case sf::Event::LostFocus:
// 				mIsPaused = true;
// 				break;
// 			case sf::Event::KeyPressed:
// 				handlePlayerInput(event.key.code, true);
// 				break;

// 			case sf::Event::KeyReleased:
// 				handlePlayerInput(event.key.code, false);
// 				break;

// 			case sf::Event::Closed:
// 				mWindow.close();
// 				break;
// 		}
// 	}
// }

void Game::update(sf::Time elapsedTime)
{

	mWorld.update(elapsedTime);
	
}

void Game::render()
{

	mWindow.clear();	
	mWorld.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");
							 
		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}



void Game::processInput()
{
	CommandQueue& commands = mWorld.getCommandQueue();

	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		mPlayer.handleEvent(event, commands);

		if(event.type == sf::Event::Closed)
			mWindow.close();
	}

	mPlayer.handleRealtimeInput(commands);
	
}
