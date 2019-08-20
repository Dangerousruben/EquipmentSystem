#include "stdafx.h"
#include "items/ammoClip.h"
#include "items/gun.h"

namespace EquipmentSystem
{
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
}
