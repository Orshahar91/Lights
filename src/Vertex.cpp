#include "Vertex.h"

Vertex::Vertex() : m_MainBulb(false), m_is_Lit(false)
{
}

void Vertex::AddBulb(const sf::CircleShape &bulb)
{
	m_Vertex = bulb;
}

bool Vertex::isPressed(const sf::Vector2f &pos) const
{
	if (m_Vertex.getGlobalBounds().contains(pos))
	{
		return true;
	}
	return false;

}

void Vertex::Rotate(const int &Deg)
{
	for (int i = 0; i < m_Lines.size(); i++)
	{
		m_Lines[i].rotate(Deg);
	}
}

Vertex::Direction Vertex::GetEnum(const char &c)
{
	if (c == 'W')
		return Direction::W;
	if (c == 'P')
		return Direction::P;
	if (c == 'R')
		return Direction::R;
	if (c == 'L')
		return Direction::L;
	if (c == 'S')
		return Direction::S;
	if (c == 'T')
		return Direction::T;
}

void Vertex::AddEdges(const string &edges)
{
	int num_of_edges = edges[0] - 48; 
		
	for (size_t i = 0; i < num_of_edges; i++)
	{
		sf::RectangleShape edge = CreateEdge();

		auto direction = GetEnum(edges[i+1]);

		switch (direction)
		{
		case Direction::L:
			edge.setRotation(180);
			break;
		case Direction::R:
			break;
		case Direction::P:
			edge.setRotation(-60);
			break;
		case Direction::T:
			edge.setRotation(60);
			break;
		case Direction::S:
			edge.setRotation(120);
			break;
		case Direction::W:
			edge.setRotation(-120);
			break;
		default:
			break;
		}
		m_Lines.push_back(edge);
	}
}

sf::RectangleShape Vertex::CreateEdge() const
{
	sf::RectangleShape edge;
	edge.setSize({ 31,2 });
	edge.setFillColor(sf::Color(47, 79, 79));
	edge.setPosition(m_Vertex.getPosition().x, m_Vertex.getPosition().y);
	edge.setOrigin(edge.getOrigin().x, edge.getGlobalBounds().height / 2);

	return edge;
}

void Vertex::Draw(sf::RenderWindow& window)
{
	if (m_is_Lit)
		m_Vertex.setFillColor(sf::Color::Yellow);

	else
		m_Vertex.setFillColor(sf::Color(47, 79, 79));

	for (auto i : m_Lines)
	{
		window.draw(i);
	}

	window.draw(m_Vertex);
}

bool Vertex::CheckCollision(const Vertex* N) const
{

	for (auto Vedge : m_Lines)
	{
		for (auto Nedge : N->m_Lines)
		{
			if (Vedge.getGlobalBounds().intersects(Nedge.getGlobalBounds()))
				return true;
		}
	}

	return false;
}

int Vertex::GetSize() const
{
	return m_Neighbors.size();
}

Vertex* Vertex::GetNeighbor(const int &index) const
{
	return m_Neighbors[index];
}

void Vertex::SetMain()
{
	m_MainBulb = true;
}

void Vertex::SetPower(const bool& p)
{
	m_is_Lit = p;
}

bool Vertex::GetPower() const
{
	return m_is_Lit;
}

void Vertex::AddNeighbors(Vertex *vertex)
{
	m_Neighbors.push_back(vertex);
}

sf::CircleShape Vertex::GetVertex() const
{
	return m_Vertex;
}

sf::Vector2f Vertex::GetPos() const
{
	return m_Vertex.getPosition();
}


Vertex::~Vertex()
{
}
