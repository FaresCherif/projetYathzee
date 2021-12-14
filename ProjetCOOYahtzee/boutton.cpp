#include "boutton.h"
namespace COO {

	Button::Button(float x, float y, float width, float height, std::string tit, sf::Color col)
	{

		this->rectangle.setSize(sf::Vector2f(width, height));
		this->rectangle.setPosition(sf::Vector2f(x, y));


		this->couleur = col;
		this->rectangle.setFillColor(this->couleur);


		this->titre.setString(tit);
		this->titre.setFillColor(sf::Color::White);
		sf::Font font;
		font.loadFromFile("font/arial.ttf");
		this->titre.setFont(font);
		
		this->titre.setPosition(
			this->rectangle.getPosition().x + this->titre.getGlobalBounds().height / 2.f,
			this->rectangle.getPosition().y 
		);
		
	}
	void Button::render(sf::RenderWindow* target)
	{
		target->draw(this->rectangle);
		//target->draw(this->titre);
		sf::Text text=this->titre;

		sf::Font font;
		font.loadFromFile("font/arial.ttf");
		text.setFont(font);
		target->draw(text);

	}
	bool Button::clicked(sf::Vector2f mousePos)
	{
		if (this->rectangle.getGlobalBounds().contains(mousePos)) {
			std::cout << "clieck" << std::endl;
			return true;
		}
		return false;

	}
}