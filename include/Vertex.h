#pragma once

#include <vector>
#include <iterator>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using std::string;

class Vertex
{
public:
	Vertex();
	void AddBulb(const sf::CircleShape &bulb);
	bool isPressed(const sf::Vector2f & pos) const;
	void Rotate(const int &Deg);
	void AddEdges(const string &edges);
	sf::RectangleShape CreateEdge() const;
	bool CheckCollision(const Vertex* N) const;
	int GetSize() const;
	Vertex* GetNeighbor(const int &index) const;
	void Draw(sf::RenderWindow& window);
	void SetMain();
	void SetPower(const bool &p);
	bool GetPower() const;
	void AddNeighbors(Vertex *vertex);
	sf::CircleShape GetVertex() const;
	sf::Vector2f GetPos() const;
	~Vertex();

private:
	sf::CircleShape m_Vertex;
	std::vector<sf::RectangleShape> m_Lines;
	std::vector<Vertex*> m_Neighbors;
	bool m_MainBulb;
	bool m_is_Lit;

	enum class Direction
	{
		P, // Up Right
		R, // Right
		T, // Down Right
		S, // Down Left
		L, // Left
		W, // Up Left
	};

	Direction GetEnum(const char &);

};