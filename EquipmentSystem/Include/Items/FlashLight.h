#pragma once
#include "Items/Item.h"
#include "Items/ToggleInterface.h"

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