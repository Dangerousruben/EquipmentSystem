#include "stdafx.h"
#include "Items/Rock.h"

namespace EquipmentSystem
{
	Rock::Rock()
	{
		compatible_equip_types = { ItemEquipType::Arm };
		name = "Rock";
	}

	Rock::~Rock()
	{

	}
}