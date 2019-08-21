#pragma once
#include "items/item.h"

namespace EquipmentSystem
{
	//Hat, can be equipped to the head
	class Hat : public EquipableItem
	{
	public:
		Hat();
		virtual ~Hat() {};
	};
}
