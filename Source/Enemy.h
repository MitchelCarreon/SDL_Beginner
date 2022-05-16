#ifndef ENEMY_H
#define ENEMY_H
#include <algorithm>
#include "Object.h"
#include "AnimatedObject.h"



class GUI;
class Player;
class Enemy :public AnimatedObject
{
public:
	Enemy() = delete;
	Enemy(std::string animationFile, Vector2D columnRow, const GUI* gui);


	Object* update(Object::Command command, const std::vector<Object*>& objects, FactoryLibrary* factories) override;
	virtual Object* copyMe() override;

	
private:
	// finals stuff
	bool isWithinRange(const std::vector<Object*>& objects);	// this defines the attack range of the enemy.
	bool canShoot(const std::vector<Object*>& objects);	// enemy can only shoot after his last shot bullet is gone.

};
#endif // !ENEMY_H
