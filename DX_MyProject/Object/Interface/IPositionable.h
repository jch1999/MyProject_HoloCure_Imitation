#pragma once
class IPositionable
{
public:
	virtual ~IPositionable() = default;
	virtual Vector2 GetPosition() const = 0;
	virtual void SetPosition(const Vector2& position) = 0;
};