#pragma once
#include "items/item.h"

namespace EquipmentSystem
{
	//Interface that toggles a state
	class Toggle
	{
	public:
		Toggle() {};
		virtual ~Toggle() {};

		virtual void ToggleState(InteractResult& a_Result) = 0;
	};
}
