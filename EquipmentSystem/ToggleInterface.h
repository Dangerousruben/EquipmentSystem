#pragma once
#include "Item.h"

//Toggle Interface
class ToggleInterface
{
public:
	ToggleInterface() {};
	virtual ~ToggleInterface() {};

	virtual void ToggleState(InteractResult &a_Result) = 0;
};