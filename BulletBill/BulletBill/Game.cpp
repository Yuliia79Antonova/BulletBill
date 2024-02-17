/// <summary>
/// @author Yuliia Antonova
/// @date Feb 2024
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Q == t_event.key.code)
	{
		m_graphics = !m_graphics;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	moveTarget();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	if (m_graphics)
	{
		m_window.draw(m_backgroundSprite);
		m_window.draw(m_wallSprite);
	}
	else
	{
		m_window.draw(m_wall);
		m_window.draw(m_target);
	}
		m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\background.jpg"))
	{
		std::cout << "problem loading background image" << std::endl;
	}

	m_wall.setFillColor(sf::Color::Black);
	m_wall.setSize(sf::Vector2f{ 32.0f, 100.0f });
	m_wall.setPosition(400.0f, 500.0f);

	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setPosition(0.0f, 0.0f);

	if (!m_wallTexture.loadFromFile("ASSETS\\IMAGES\\wall.jpg"))
	{
		std::cout << "problem loading wall image" << std::endl;
	}
	m_wallTexture.setRepeated(true);
	m_wallSprite.setTexture(m_wallTexture);
	m_wallSprite.setTextureRect(sf::IntRect(0, 0, 32, 100));
	m_wallSprite.setPosition(m_wall.getPosition());

	

	m_target.setFillColor(sf::Color::Green);
	m_target.setSize(sf::Vector2f{55.0f, 55.0f});
	m_targetLocation = sf::Vector2f{ 420.0f,545.0f };
	m_target.setPosition(m_targetLocation);
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);
}

void Game::moveTarget()
{
	const float SPEED = 0.6f;
	const float LEFT_EDGE = 420.0f;
	const float RIGHT_EDGE = 740.0f;
	
	if (m_targetLocation.x < LEFT_EDGE)
	{
		m_targetVelocity.x = SPEED;
	}
	if (m_targetLocation.x > RIGHT_EDGE)
	{
		m_targetVelocity.x = -SPEED;
	}
	m_targetLocation += m_targetVelocity;
	m_target.setPosition(m_targetLocation);
}
