#pragma once
#include "items/item.h"


namespace EquipmentSystem
{
	enum GunMode
	{
		Single,
		Automatic,
		Burst
	};

	static std::string ToString(GunMode a_GunMode)
	{
		switch (a_GunMode)
		{
		case Single:
			return "Single";
		case Automatic:
			return "Automatic";
		case Burst:
			return "Burst";
		default:
			return "";
		}
	}

	class GunInterface
	{
	public:
		GunInterface() {};
		virtual ~GunInterface() {};

		virtual void Shoot(InteractResult& a_Result) = 0;

	private:


	};
}
