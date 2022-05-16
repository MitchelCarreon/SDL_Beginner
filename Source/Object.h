#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
class FactoryLibrary;

class GUI;

struct Vector2D
{
	float x;
	float y;

	Vector2D& operator+=(const Vector2D& src)
	{
		x += src.x;
		y += src.y;
		return *this;
	}
	Vector2D& operator*= (const int& src)
	{
		x *= src;
		y *= src;
		return *this;
	}
	Vector2D& operator-=(const Vector2D& src)
	{
		x -= src.x;
		y -= src.y;
		return *this;
	}
	friend bool operator<(const Vector2D& srcL, const Vector2D& srcR)
	{
		return srcL.x < srcR.x;
	}
	friend bool operator>(const Vector2D& srcL, const Vector2D& srcR)	// for enemy : finals stuff
	{
		return srcL.x > srcR.x;
	}
	
	float length()
	{
		return sqrt(x * x + y * y);
	}
	void normalize()
	{
		float vectorLength = length();
		if (vectorLength != 0)
		{
			x /= vectorLength;
			y /= vectorLength;
		}

	}
	void vector2OtherPoint(Vector2D destination)
	{
		*this = { destination.x - x, destination.y - y };
	}
	void target(Vector2D targetPosition, int speed)
	{
		vector2OtherPoint(targetPosition);
		normalize();
		(*this) *= speed;
	}
};

class Object
{
public:
	enum class Command { up, down, left, right, attack, jump, shoot, NA }; 
	enum class Type 
	{ 
		none, 		
		bridge_center, 
		bridge_end, 
		bridge_start, 
		center_block, 
		top_block, 
		tree_background, 
		water, 
		water_shore, 
		water_top, 
		water_wall, 
		water_wall_corner,
		heart,	// NOTE TO SELF: if you're going to add here. make sure to check FactoryLibrary::FactoryLibrary() too.
		bullet,
		player=100,
		enemy=200,
		powerup=300
	};

	Object() = delete;
	Object(Vector2D position, Type name, const GUI* gui);


	Vector2D getPosition() const;
	void setPosition(Vector2D newPosition);
	Vector2D getDimensions() const;
	Type getName() const;

	bool getIsDead();
	void kill();

	virtual Object* update(Object::Command command, const std::vector<Object*> & object, FactoryLibrary* factories) = 0;
	virtual Object* copyMe() = 0;
	
protected:
	const Type name{ Type::none };
	Vector2D position{ 0,0 };	
	const GUI* gui;
	bool isDead{ false };
};

#endif