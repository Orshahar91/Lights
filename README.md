# :bulb:Lights Game:bulb:

* The project was created in order to practice Data structures, Iterator, STL algorithms and SFML.

## Prerequisites:
* SFML folder to be placed in C:\SFML, can be downloaded from : https://www.sfml-dev.org/download/sfml/2.5.1/

## Guidelines
* Run this project in Visual Studio
* Make sure SFML folder is placed under C:\SFML
* Run the Game.
* Enjoy :smiley:

## Gameplay
* Use the Left/Right Mouse click to rotate the light bulbs clockwise/counter-clockwise.
* The center light bulb provides 'Power'.
* The goal is to provide power to all the lightbulbs to advance to the next stage. 

## Levels
* File is Levels.txt
* All the stages are written in a single file.
* Every stage is seperated with a single line.
* Every light bulb is represented by 'O' character, 'M' represents the center light bulb that alawys has power.
* Right next to these characters there is a digit(1-6) to represent the number of edges for the vertex.
* After the digit there are characters to determine the direction of each vertex.
* Example: O2RL - vertex with 2 edges, one is facing right and the other is facing left.

## Data Structures & Algorithms
* Used a vecotr of unique pointers for the vertexes and the edges
* Each vertex has a vector of *vertex for its neigbors.
* Used a bidirectional queue in order to flag an alreday visited vertex.

## Notes
*This is a C++ CMAKE project, created with Visual Studio 2019.*

*Written by : Or Shahar*

![Lights](/Images/1.png)
