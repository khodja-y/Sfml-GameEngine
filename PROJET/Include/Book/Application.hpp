// #ifndef APPLICATION_HPP
// #define APPLICATION_HPP

// #include <Book/ResourceHolder.hpp>
// #include <Book/ResourceIdentifiers.hpp>
// #include <Book/Player.hpp>
// #include <Book/StateStack.hpp>

// #include <SFML/System.hpp>
// #include <SFML/Graphics.hpp>


// class Application
// {
// 	public:
// 								Application();
// 		void					run();
		

// 	private:
// 		void					processInput();
// 		void					update(sf::Time dt);
// 		void					render();

// 		void					updateStatistics(sf::Time dt);
// 		void					registerStates();


// 	private:
// 		static const sf::Time	TimePerFrame;

// 		sf::RenderWindow		mWindow;
// 		TextureHolder			mTextures;
// 	  	FontHolder				mFonts;
// 		Player					mPlayer;

// 		StateStack				mStateStack;

// 		sf::Text				mStatisticsText;
// 		sf::Time				mStatisticsUpdateTime;
// 		std::size_t				mStatisticsNumFrames;
// };

// #endif // APPLICATION_HPP
