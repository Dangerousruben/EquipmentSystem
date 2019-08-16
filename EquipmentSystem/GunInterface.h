#pragma once
#include "Item.h"

enum GunMode
{
	Single,
	Automatic,
	Burst
};

static std::string ToString(GunMode a_GunMode)
{
	switch (a_GunMode)
	{
	case Single:
		return "Single";
	case Automatic:
		return "Automatic";
	case Burst:
		return "Burst";
	default:
		return "";
	}
}

class IGunInterface
{
public:
	IGunInterface() {};
	virtual ~IGunInterface() {};

	virtual void Shoot(InteractResult &a_Result) = 0;

	virtual void ToggleMode(InteractResult& a_Result) = 0;

protected:
	virtual void SwitchMode(InteractResult& a_Result, GunMode a_NewGunMode) = 0;

private:

};