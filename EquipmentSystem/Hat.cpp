#include "stdafx.h"
#include "Hat.h"

Hat::Hat()
{
	compatible_equip_types = { ItemEquipType::Arm, ItemEquipType::Head };
	name = "Hat";
}

Hat::~Hat()
{
}