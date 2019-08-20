#include "stdafx.h"
#include "items/rock.h"

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
