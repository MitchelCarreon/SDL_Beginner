#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

#include <map>
#include "AnimatedObject.h"
#include "IShootStrategy.h"

class GUI;
class Block;
class Player: public AnimatedObject
{
public:
	Player() = delete;
	Player(std::string animationFile, Vector2D columnRow, const GUI* gui);
	
	Object* update(Object::Command command, const std::vector<Object*>& objects, FactoryLibrary* factories) override;
	virtual Object* copyMe() override;

		// finals stuff : getLife(), decrementLife(), addLife()
	int getLife() const {return life;}
	void decrementLife(){life -= 1;}
	void addLife() { life += 1; }

		// finals stuff : strategy pattern (shoot)
	std::map<char, IShootStrategy*> behaviors;
	
private:
		//Helper functions
	void moveDown();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveJump();
	bool moveShoot();
	void noAction();

		// finals stuff : life
	int life{ 0 };		// NOTE: to change life, all you have to do is add "12" (hearts) in the upper left corner in background.txt
		



	
	


	
};
#endif // !PLAYER_H
