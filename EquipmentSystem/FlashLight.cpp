#include "stdafx.h"
#include "FlashLight.h"


FlashLight::FlashLight()
{
	CompatibleEquipTypes = { ItemEquipType::Arm };
	Name = "FlashLight";
}

FlashLight::~FlashLight()
{
}

void FlashLight::PressButton(InteractResult& a_Result)
{
	IsOn = !IsOn;
	a_Result.Success = true;
	a_Result.Unequip = false;
	a_Result.Message = "Flashlight is turned " + std::string(IsOn ? "On" : "Off") + "\n";
}
