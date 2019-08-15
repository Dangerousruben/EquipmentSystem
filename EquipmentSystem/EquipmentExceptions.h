#pragma once
#include <exception>
#include <string>

class ImcompatibleItem : public std::exception
{
	const char* what() const throw()
	{
		return "Imcompatible Item type for slot\n";
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
		return "Cannot interact with item using the given itemslot\n";
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
		: ItemName(a_ItemName) {};

private:
	const char* what() const throw()
	{
		std::string message = "Item " + ItemName + " cannot be consumed";
		return message.c_str();
	}

	std::string ItemName;
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
		return "Itemslot does not have gun equipped\n";
	}
};

class NoAmmoClipEquipped : public std::exception
{
	const char* what() const throw()
	{
		return "Itemslot does not have AmmoClip equipped\n";
	}
};