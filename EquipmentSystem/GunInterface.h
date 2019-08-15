#pragma once
#include "Item.h"


class IGunInterface
{
public:
	IGunInterface() {};
	virtual ~IGunInterface() {};

	virtual void Shoot(InteractResult &a_Result) = 0;

private:

};