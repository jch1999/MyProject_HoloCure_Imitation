#pragma once
class IHealth
{
public:
	float DefaultMaxHealth;
	float NowMaxHealth;
	float NowHealth;

public:
	virtual float GetHealthRate() = 0;
	virtual float GetDefaultMaxHealth() = 0;
	virtual float GetMaxHealth() = 0;
	virtual void SetMaxHealth() = 0;
	virtual float GetNowHealth() = 0;
	
	virtual void ChangeHealth(float amount) = 0;
};