#include "stdafx.h"
#include "Hat.h"

Hat::Hat()
{
	CompatibleEquipTypes = { ItemEquipType::Arm, ItemEquipType::Head };
	Name = "Hat";
}

Hat::~Hat()
{
}