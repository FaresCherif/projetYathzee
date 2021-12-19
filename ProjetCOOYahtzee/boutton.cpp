//Fares Cherif 
#include "boutton.h"
namespace COO {

	Button::Button(float x, float y, float width, float height, std::string tit, sf::Color col) // constructeur des boutton pour le visuel
	{

		this->rectangle.setSize(sf::Vector2f(width, height));  //cree le rectangle du bouton
		this->rectangle.setPosition(sf::Vector2f(x, y)); //place le rectangle du bouton 


		this->couleur = col; //defini la couleur du bouton
		this->rectangle.setFillColor(this->couleur); // colorie le rectangle selon la couleur du bouton


		this->titre.setString(tit); //donne un text au titre
		this->titre.setFillColor(sf::Color::White); //donne une couelur au titre
		sf::Font font;
		font.loadFromFile("font/arial.ttf"); 
		this->titre.setFont(font); //donne une font au titre
		
		this->titre.setPosition( //place le titre au milieu du rectangle
			this->rectangle.getPosition().x + this->titre.getGlobalBounds().height / 2.f,
			this->rectangle.getPosition().y 
		);
		
	}
	void Button::render(sf::RenderWindow* target)
	{
		target->draw(this->rectangle); //affiche le rectangle
		sf::Text text=this->titre;

		sf::Font font;
		font.loadFromFile("font/arial.ttf");
		text.setFont(font);
		target->draw(text); // affiche le titre

	}
	bool Button::clicked(sf::Vector2f mousePos)
	{
		if (this->rectangle.getGlobalBounds().contains(mousePos)) { //return si la souris est sur le rectangle du bouton
			//std::cout << "clieck" << std::endl;
			return true;
		}
		return false;

	}
	sf::RectangleShape Button::getRectangle() //retourne le rectangle du bouton
	{
		return this->rectangle;
	}
}