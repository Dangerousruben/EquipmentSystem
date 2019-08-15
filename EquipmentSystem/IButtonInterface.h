#pragma once
#include "Item.h"

class IButtonInterface
{
public:
	IButtonInterface() {};
	virtual ~IButtonInterface() {};

	virtual void PressButton(InteractResult &a_Result) = 0;

private:

};