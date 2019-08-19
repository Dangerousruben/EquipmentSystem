#pragma once
#include "Item.h"
#include "ToggleInterface.h"

class FlashLight : public EquipableItem, public ToggleInterface
{
public:
	FlashLight();
	~FlashLight();

	void ToggleState(InteractResult &a_Result) override;

private:

	bool is_on = false;
};
