#pragma once
#include "items/item.h"
#include "items/toggle.h"

namespace EquipmentSystem
{
	class FlashLight : public EquipableItem, public ToggleInterface
	{
	public:
		FlashLight();
		~FlashLight();

		void ToggleState(InteractResult& a_Result) override;

	private:

		bool is_on = false;
	};
}
