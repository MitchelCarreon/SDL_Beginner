#ifndef BLOCK_H
#define BLOCK_H
#include "Object.h"
class Player;
class Block:public Object
{
public:
	Block() = delete;
	Block(Vector2D columnRow, Object::Type name, const GUI* gui);	
	Object* update(Object::Command command, const std::vector<Object*>& objects, FactoryLibrary* factories) override { return nullptr; }
	virtual Object* copyMe() override;
private:
	
};
#endif // !BLOCK_H
