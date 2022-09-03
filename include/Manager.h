#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <istream>
#include <sstream>
#include <iterator>
#include <SFML/Graphics.hpp>
#include "Vertex.h"
#include <queue>
#include <iostream>

using std::unique_ptr;
using std::vector;
using std::string;

class Manager
{
public:
	Manager();
	void Run();
	~Manager();

private:
	void WaitForKey();
	void LoadAssets();
	int CheckPosition(const Vertex* vertex) const;
	std::vector<int> BFS() const;
	void FindNeigbors();
	void HandleEvents();
	void RotateVertex(const sf::Vector2f &, const bool &Clockwise);
	void ReadFile();
	vector<string> Split(const string &line) const;
	void UpdateLights();
	bool CheckLights() const;
	
	std::ifstream m_My_File;
	vector<std::unique_ptr<Vertex>> m_LightBulbs;
	sf::RenderWindow m_Window;
	sf::Font m_Font;
	const std::string FileName = "Levels.txt";
	const std::string FontName = "Snap.ttf";
	sf::Text m_Level_Completed;
	bool m_Game = false;

};
