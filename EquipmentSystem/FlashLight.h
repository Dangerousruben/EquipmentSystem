#pragma once
#include "Item.h"
#include "IButtonInterface.h"

class FlashLight : public Item, public IButtonInterface
{
public:
	FlashLight();
	~FlashLight();

	void PressButton(InteractResult &a_Result) override;

private:

	bool IsOn = false;
};
