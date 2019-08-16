#pragma once
#include "Item.h"

class Gun;

struct Ammo
{
	const int AmmoCapacity;
	int CurrentAmmo;

	Ammo(int a_AmmoCapacity)
		: AmmoCapacity(a_AmmoCapacity), CurrentAmmo(AmmoCapacity)
	{

	}
};

class AmmoClip : public Item
{
	friend Gun;
public:
	AmmoClip();
	virtual ~AmmoClip();

private:
	Ammo m_Ammo;
};
