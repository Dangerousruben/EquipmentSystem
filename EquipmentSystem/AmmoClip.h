#pragma once
#include "Item.h"


//Ammoclip class which is put inside the Gun Class
class AmmoClip : public EquipableItem
{
public:
	AmmoClip();
	virtual ~AmmoClip();

	int GetCurrentAmmo() const { return current_ammo; }

	//Fires bullet and 
	void FireBullet();

private:
	const int kAmmoCapacity;
	int current_ammo;
};
