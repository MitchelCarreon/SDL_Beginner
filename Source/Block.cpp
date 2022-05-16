#include "Block.h"

Block::Block(Vector2D position, Object::Type name, const GUI* gui): Object(position, name, gui)
{

}

Object* Block::copyMe()
{
	return new Block(*this);
}
