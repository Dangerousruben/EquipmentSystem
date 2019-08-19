#include "stdafx.h"
#include "AmmoClip.h"
#include "Gun.h"

AmmoClip::AmmoClip() : 
	kAmmoCapacity(10)
{
	current_ammo = kAmmoCapacity;
	compatible_equip_types = { ItemEquipType::Arm };
	name = "Ammo Clip";
}

AmmoClip::~AmmoClip()
{
}

void AmmoClip::FireBullet()
{
	if (current_ammo > 0)
	{
		current_ammo--;
	}
	else
	{
		throw OutOfAmmo();
	}
}
