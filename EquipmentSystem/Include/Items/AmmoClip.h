#pragma once
#include "Items/Item.h"


//Ammoclip class which is put inside the Gun Class
class AmmoClip : public EquipableItem
{
public:
	AmmoClip();
	virtual ~AmmoClip();

	int GetCurrentAmmo() const { return current_ammo; }

	//Reduces current_ammo by one
	void DispenseBullet();

private:
	const int kAmmoCapacity;
	int current_ammo;
};
