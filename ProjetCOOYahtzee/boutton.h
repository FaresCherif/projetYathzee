#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace COO {
	class Button
	{
	public:
		Button(float x,float y,float width,float height,std::string titre, sf::Color);
		void render(sf::RenderWindow* target);
		bool clicked(sf::Vector2f mousePos);
		sf::RectangleShape getRectangle();
	private:
		sf::RectangleShape rectangle;
		sf::Text titre;

		sf::Color couleur;
	};

}