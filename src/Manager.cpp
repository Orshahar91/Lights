#pragma once
#include "Manager.h"

using sf::Event;

Manager::Manager()
{

}

void Manager::Run()
{
	m_Window.create(sf::VideoMode(800, 800), "Lights");

	LoadAssets();

	bool run = true;

	while (run)
	{
		m_LightBulbs.clear();

		ReadFile();

		FindNeigbors();

		while (m_Window.isOpen())
		{
			UpdateLights();

			m_Window.clear();
			for (auto& i : m_LightBulbs)
				i->Draw(m_Window);


			if (CheckLights())
			{
				if (m_Game)
				{
					m_Level_Completed.setString("         Well Done!\nYou completed the game.\nPress any KEY to exit.");
					run = false;
				}

				m_Window.draw(m_Level_Completed);
				m_Window.display();
				WaitForKey();
				break;

			}

			m_Window.display();

			HandleEvents();
		}
	}
}

void Manager::WaitForKey()
{
	Event event;
	bool a = false;

	while (m_Window.waitEvent(event) && !a)
	{
		if (event.type == sf::Event::KeyPressed)
		{
				a = true;
		}

		if (event.type == sf::Event::Closed)
		{
			m_Window.close();
		}

	}
}

void Manager::HandleEvents()
{
	Event event;
	sf::Vector2f mousePos;

	if (m_Window.waitEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_Window.close();
			break;
		case sf::Event::MouseButtonPressed:
		{
			mousePos = m_Window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				RotateVertex(mousePos, false);
			}

			else if (event.mouseButton.button == sf::Mouse::Left)
			{
				RotateVertex(mousePos, true);
			}
		}

		}
	}
}

void Manager::RotateVertex(const sf::Vector2f &pos, const bool &Clockwise)
{
	int Deg = 0;

	if (Clockwise)
		Deg = 60;
	else
		Deg = -60;

	for (auto& i : m_LightBulbs)
	{
		if (i->isPressed(pos))
		{
			i->Rotate(Deg);
			break;
		}
	}
}

void Manager::ReadFile()
{
	std::string line;
	sf::CircleShape Bulb;
	sf::Vector2f BulbPos = {300, 100};
	Bulb.setPosition(BulbPos);
	Bulb.setRadius(5);
	auto start = 300;

	int max = 0;

	while (std::getline(m_My_File, line))
	{

		if (line.empty()) // reached the end of the level
			return;

		auto lights = Split(line);

		if (lights.size() > max)
		{
			max = lights.size();
			start -= 30;
		}

		else
		{
			start += 30;
		}

		BulbPos.x = start;

		for (auto i : lights)
		{
			for (auto j : i)
			{
				if (j == 'O' || j == 'M')
				{
					BulbPos = { BulbPos.x + 60, BulbPos.y };
					Bulb.setPosition(BulbPos);
					Bulb.setOrigin(Bulb.getRadius(), Bulb.getRadius()); // set the origin of the vertex to the middle
					Vertex vertex;

					if (j == 'M')
					{
						vertex.SetMain();
						vertex.SetPower(true);
					}

					vertex.AddBulb(Bulb);

					i.erase(i.begin()); // delete the 1st char from the string in order to read edges

					vertex.AddEdges(i);
					m_LightBulbs.emplace_back(std::make_unique<Vertex>(vertex));
				}
			}
		}
		BulbPos = { BulbPos.x, BulbPos.y + 52 };
	}

	if (m_My_File.eof()) //  finished all levels
		m_Game = true;
}

vector<string> Manager::Split(const string &line) const
{
	std::istringstream iss(line);

	std::vector<std::string> results(std::istream_iterator<std::string>{iss}, // split entire line into words
		std::istream_iterator<std::string>());

	return results; // return vector of the words

}

void Manager::UpdateLights()
{
	for (auto& i : m_LightBulbs)
	{
		i->SetPower(false); // reset all vertex's power
	}


	int MainBulb = m_LightBulbs.size() / 2; 

	m_LightBulbs[MainBulb]->SetPower(true);

	std::vector<int> Lit;

	Lit = BFS();

	for (auto i : Lit)
	{
		m_LightBulbs[i]->SetPower(true);
	}
}

std::vector<int> Manager::BFS() const
{
	// Mark all the vertices as not visited 
	int size = m_LightBulbs.size();
	std::vector<bool> visited;
	visited.resize(size);

	int s = size / 2;

	std::vector<int> Connections;

	for (int i = 0; i < size; i++)
		visited[i] = false;

	// Create a queue for BFS 
	std::deque<int> queue;

	// Mark the current node as visited and enqueue it 
	visited[s] = true;
	queue.push_back(s);


	while (!queue.empty())
	{
		// Dequeue a vertex from queue  
		s = queue.front();
		queue.pop_front();


		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it 

		for (int i = 0; i < m_LightBulbs[s]->GetSize(); i++)
		{
			auto Neighbor = m_LightBulbs[s]->GetNeighbor(i);

			int place = CheckPosition(Neighbor);

			if (!visited[place] && m_LightBulbs[s]->CheckCollision(Neighbor)) // check current vertex's collision with he's neighbors.
			{
				visited[place] = true;
				queue.push_back(place);
				Connections.push_back(place);
			}
		}
	}
	return Connections; // indexes vector of the lit vertexes.
}

int Manager::CheckPosition(const Vertex* vertex) const
{
	for (int i = 0; i < m_LightBulbs.size(); i++)
	{
		if (vertex == m_LightBulbs[i].get()) // check the position of a give vertex inside the original vector 
		{
			return i;
		}
	}
}


bool Manager::CheckLights() const
{
	for (auto& i : m_LightBulbs)
	{
		if (!i->GetPower())
			return false;

	}
	return true;
}

void Manager::FindNeigbors()
{


	for (auto& i : m_LightBulbs)
	{
		sf::RectangleShape DistanceRect;
		DistanceRect.setSize({ 60.f,1.f }); // distance from one vertex to an adjacent vertex in pixels
		DistanceRect.setOrigin({ DistanceRect.getOrigin().x, DistanceRect.getGlobalBounds().height / 2 });

		sf::Vector2f CurVertex = i->GetPos();
		DistanceRect.setPosition(CurVertex);

		for (auto& j : m_LightBulbs)
		{
			if (j == i)
				continue;

			for (int k = 0; k < 6; k++) // rotate through the current vertex axis and find it's neighbors
			{
				if (j->GetVertex().getGlobalBounds().intersects(DistanceRect.getGlobalBounds()))
				{
					i->AddNeighbors(j.get());
				}
				DistanceRect.rotate(60);
			}
		}
	}
}

void Manager::LoadAssets()
{


	if (!m_Font.loadFromFile(FontName))
	{
		throw std::runtime_error::runtime_error("Unable to load this font: " + FontName + "\n");
	}

	m_My_File.open(FileName, std::ios::in);
	if (!m_My_File.is_open())
		throw std::runtime_error::runtime_error("Unable to open this file: " + FileName + "\n");

	m_Level_Completed.setFont(m_Font);
	m_Level_Completed.setString("       Level Completed!\nPress any KEY to continue.");
	m_Level_Completed.setOrigin(m_Level_Completed.getLocalBounds().width / 2, m_Level_Completed.getLocalBounds().height / 2);
	m_Level_Completed.setPosition(m_Window.getSize().x / 2, m_Window.getSize().y / 2);
	m_Level_Completed.setFillColor(sf::Color::Yellow);

}

Manager::~Manager()
{
}