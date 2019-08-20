#include "stdafx.h"
#include "Items/AmmoClip.h"
#include "Items/Gun.h"

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

void AmmoClip::DispenseBullet()
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
