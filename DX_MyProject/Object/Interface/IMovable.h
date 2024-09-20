#pragma once
class IMovable
{
public:
	float move_speed;
	Vector2 move_dir;

public:
	virtual void Move() = 0;
};