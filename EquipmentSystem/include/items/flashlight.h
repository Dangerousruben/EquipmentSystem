#pragma once
#include "items/item.h"
#include "items/toggle.h"

namespace EquipmentSystem
{
	//Flashlight that can be held and turned on
	class FlashLight : public EquipableItem, public Toggle
	{
	public:
		FlashLight();
		~FlashLight();

		//Toggles boolean is_on
		void ToggleState(InteractResult& a_Result) override;

	private:
		bool is_on = false;
	};
}
