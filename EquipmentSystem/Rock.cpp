#include "stdafx.h"
#include "Rock.h"


Rock::Rock()
{
	CompatibleEquipTypes = { ItemEquipType::Arm };
	Name = "Rock";
}

Rock::~Rock()
{
	
}

void Rock::Interact(InteractResult& a_Result)
{
	a_Result.Success = true;
	a_Result.Unequip = true;
	a_Result.Message = "You throw a rock\n";
}
