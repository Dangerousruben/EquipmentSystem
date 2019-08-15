#pragma once
#include "Item.h"

class Hat : public Item
{
public:
	Hat();
	virtual ~Hat();

	void Interact(InteractResult& a_Result) override {};

private:

};

