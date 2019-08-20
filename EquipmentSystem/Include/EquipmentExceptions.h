#pragma once
#include <exception>
#include <string>

namespace EquipmentSystem
{
	class IncompatibleItem : public std::exception
	{
		const char* what() const throw()
		{
			return "Incompatible Item type for slot\n";
		}
	};

	class ItemSlotEmpty : public std::exception
	{
		const char* what() const throw()
		{
			return "Item slot is empty\n";
		}
	};

	class EquipItemEmpty : public std::exception
	{
		const char* what() const throw()
		{
			return "Can't equip empty item\n";
		}
	};

	class InvalidItemSlot : public std::exception
	{
		const char* what() const throw()
		{
			return "Itemslot does not exist on object\n";
		}
	};

	class CannotInteractWithSlot : public std::exception
	{
		const char* what() const throw()
		{
			return "Cannot interact with item in the itemslot\n";
		}
	};

	class InteractionFailed : public std::exception
	{
	public:
		InteractionFailed(std::string a_Message)
			: Message(a_Message) {};

	private:
		const char* what() const throw()
		{
			return Message.c_str();
		}

		std::string Message;
	};

	class ItemCannotBeConsumed : public std::exception
	{
	public:
		ItemCannotBeConsumed(std::string a_ItemName)
			: item_name(a_ItemName) {};

	private:
		const char* what() const throw()
		{
			std::string message = "Item " + item_name + " cannot be consumed";
			return message.c_str();
		}

		std::string item_name;
	};

	class OutOfAmmo : public std::exception
	{
		const char* what() const throw()
		{
			return "The gun has no more ammo\n";
		}
	};

	class NoGunEquipped : public std::exception
	{
		const char* what() const throw()
		{
			return "The player has no gun equipped\n";
		}
	};

	class NoAmmoClipEquipped : public std::exception
	{
		const char* what() const throw()
		{
			return "The player has no ammoclip equipped\n";
		}
	};

	class NoValidItem : public std::exception
	{
		NoValidItem(std::string a_ItemName)
			: item_name(a_ItemName) {};
		const char* what() const throw()
		{
			std::string message = "Item " + item_name + " is not valid\n";
			return message.c_str();
		}
		std::string item_name;
	};
}