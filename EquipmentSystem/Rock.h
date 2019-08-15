#pragma once
#include "Item.h"

class Rock : public Item
{
public:
	Rock();
	virtual ~Rock();

	void Interact(InteractResult& a_Result) override;

private:

};
