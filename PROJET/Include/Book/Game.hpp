// #ifndef GAME_HPP
// #define GAME_HPP

// #include <SFML/Graphics.hpp>
// #include <SFML/Window.hpp>
// #include <SFML/System.hpp>

// #include <Book/World.hpp>
// #include <Book/Player.hpp>


// class Game : private sf::NonCopyable
// {
// 	public:
// 								Game();
// 								~Game();
// 		void					run();
		

// 	private:
// 		void					processEvents();
// 		void					update(sf::Time elapsedTime);
// 		void					render();

// 		void					updateStatistics(sf::Time elapsedTime);	
// 		void					processInput();
		

// 	private:
// 		static const float		PlayerSpeed;
// 		static const sf::Time	TimePerFrame;

// 		sf::RenderWindow		mWindow;
// 		World					mWorld;
// 		sf::Texture				mTexture;
// 		Player					mPlayer;
// 		sf::Font				mFont;
// 		sf::Text				mStatisticsText;
// 		sf::Time				mStatisticsUpdateTime;

// 		std::size_t				mStatisticsNumFrames;
// 		bool					mIsPaused;

		
// };

// #endif 
