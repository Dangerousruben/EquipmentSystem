#include "stdafx.h"
#include "AmmoClip.h"
#include "Gun.h"

AmmoClip::AmmoClip() : 
	m_Ammo(10)
{
	CompatibleEquipTypes = { ItemEquipType::Arm };
	Name = "Ammo Clip";
}

AmmoClip::~AmmoClip()
{
}
