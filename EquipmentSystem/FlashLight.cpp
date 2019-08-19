#include "stdafx.h"
#include "FlashLight.h"


FlashLight::FlashLight()
{
	compatible_equip_types = { ItemEquipType::Arm };
	name = "FlashLight";
}

FlashLight::~FlashLight()
{
}

void FlashLight::ToggleState(InteractResult& a_Result)
{
	is_on = !is_on;
	a_Result.success = true;
	a_Result.message = name + " is turned " + std::string(is_on ? "on" : "off") + "\n";
}
