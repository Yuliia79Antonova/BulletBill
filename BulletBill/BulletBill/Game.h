/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processMouseMove(sf::Event t_event);
	void processMouseUp(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void moveTarget();
	void animateTarget();
	void setAimLine();


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game

	bool m_graphics{ false }; //draw fancy pictures [or not]

	sf::RectangleShape m_wall; //box for the wall
	sf::RectangleShape m_target;//boxfor target to fire at
	sf::Vector2f m_targetLocation; //location of target
	sf::Vector2f m_targetVelocity{0.6f, 0.0f};// velocity of the target


	sf::Texture m_wallTexture;
	sf::Sprite m_wallSprite;
	sf::Texture m_backgroundTexture;
	sf::Sprite m_gumbaTexture;
	sf::Sprite m_gumbaSprite;
	sf::Sprite m_backgroundSprite;

	sf::Texture m_gumballTexture; // texture for the gumba

	sf::RectangleShape m_canon;
	sf::Vector2f m_mouseEnd;
	sf::Vector2f m_canonEnd{ 100.0f, 550.0f };

	sf::VertexArray m_aimLine{ sf::Lines }; //line to show path
	bool m_aiming{ false }; // are we aiming


	int m_gumbaFrame{ -1 };
	const int GUMBA_FRAMES = 20; 
	float m_gumbaFrameCounter = 0.0f;
	float m_gumbaFrameIncrement = 0.3f;



};

#endif // !GAME_HPP

