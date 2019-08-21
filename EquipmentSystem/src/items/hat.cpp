#include "stdafx.h"
#include "items/hat.h"

namespace EquipmentSystem
{
	Hat::Hat()
	{
		compatible_equip_types = { ItemEquipType::Arm, ItemEquipType::Head };
		name = "Hat";
	}
}
