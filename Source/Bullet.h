#ifndef BULLET_H
#define BULLET_H
#include "AnimatedObject.h"

class Bullet : public AnimatedObject
{
public:
	Bullet() = delete;
	Bullet(Vector2D position, Object* shooter, Vector2D target, const GUI* gui);
	Object* update(Object::Command command, const std::vector<Object*>& objects, FactoryLibrary* factories) override;
	virtual Object* copyMe() override;
	const Object* shooter{ nullptr };

	// finals stuff: trying strategy pattern?
	//void extendRange();		// this is for sniping / specialShotStrategy. if you want life to be a private data member.				
	int life{ 10 };
	
private:
	const int speed{ 20 };
};
#endif // !BULLET_H
