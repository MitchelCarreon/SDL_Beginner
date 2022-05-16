#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>
#include <tuple>

class GUI;
class Object;

class FactoryLibrary;
//Game Utilities
class Engine
{
public:
	Engine(GUI* gui,const std::string& levelFile);

	bool getGameOver() const;
	bool getGameWon() const;
	void changeGameState(Object::Command command);
	std::vector<Object*> getObjects() const;

	~Engine();
	Engine(const Engine& src);
	Engine(Engine&& src);

	Engine& operator=(const Engine& src) noexcept;
	Engine& operator=(Engine&& src) noexcept;
private:
	bool gameOver{ false };
	bool gameWon{ false };
	std::vector<Object*> objects;
	FactoryLibrary* factories{ nullptr };
	const GUI* gui;
};

#endif