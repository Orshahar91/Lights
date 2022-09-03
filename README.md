# Gladiator Game

* The project was created in order to practice the use Object Oriented Programming, as well as a graphics library - 'SFML'.

## Prerequisites:
* SFML folder to be placed in C:\SFML, can be downloaded from : https://www.sfml-dev.org/download/sfml/2.5.1/

## Guidelines
* Run this project in Visual Studio
* Make sure SFML folder is placed under C:\SFML
* Run the Game.
* Enjoy :smiley:

## Gameplay
* Use the arrow keys to naviage the galidator through the map.
* Collect all the swords in order to advance to the next stage.
* Avoid the monsters aling the way.
* Collect treasure chests to gain health states or points.
* Avoid the skulls, only a certain amount can be tolerated.
* Advance through all the stages to complete the game.

## Design
### UML is avaiable in "ClassDiagram.png" 
* Asset_manager: For loading and managing the resources for the game such as audio files, fonts, images.
* Menu: The initial menu that show up before the game starts.
* Button: Class for a single button.
* Board: Stores an instance of every object in the game or vector of instances.
* Game: manages the main logic of the game, menu, keyboard events, etc.
* DataBar: Manages the HUD of the player.
* Object: Base calss of every object in the game.
* Statics, Moveables: Inherit from Object.
* Statics: Wall, Skull, Sword, Gift.
* Moveables: Gladiator, Monsters.

## Stages
* File is Board.txt
* All the stages are written in a single file.
* Every stage is seperated with a single line.
* First row of every stage represents the following information: Rows, Cols, Max Skulls, Timer(-1 for no limit), and then the object matrix.

## Data Structures
* Used Vector of Unique ptr for the Monsters and for the Statics.
* Used several Maps to store the sfml textures, soundbuffers and fonts.

## Algorithms
* In order to implement the monsters movement, iv'e used random direction for regular monsters. Generates a number 0-3 and every 2 seconds changes direction according to the number generated.
* The smart monsters movement is implemented by receiving the gladiator coordinates and calculating the relative distance using pythagoras theorem. The monsters starts the chase only if close enough to the player(< 400 px).

## Notes
*This is a C++ CMAKE project, created with Visual Studio 2019.*

*Written by : Or Shahar*


<p float="left">
  <img src="/Screenshots/Menu.png" width="400" />
  <img src="/Screenshots/StageOne.png" width="400" /> 
  <img src="/Screenshots/StageTwo.png" width="400" />
  <img src="/Screenshots/StageThree.png" width="400" />
</p>
