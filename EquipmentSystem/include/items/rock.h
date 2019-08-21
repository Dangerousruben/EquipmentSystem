#pragma once
#include "items/item.h"

namespace EquipmentSystem
{
	//An item whose default action is throwing it away
	class Rock : public EquipableItem
	{
	public:
		Rock();
		virtual ~Rock() {};

	private:

	};
}
