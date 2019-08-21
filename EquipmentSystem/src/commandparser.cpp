#include "stdafx.h"
#include "commandparser.h"
#include "player.h"
#include "items/item.h"
#include "items/gun.h"
#include "items/rock.h"
#include "items/flashlight.h"
#include "items/hat.h"
#include "items/ammoclip.h"

namespace EquipmentSystem
{
	void CommandParser::PrintHelp()
	{
		std::cout << "The Player has 3 available item slots (Leftarm, RightArm and Head)\nItems can be equipped to slots and Leftarm and RightArm can use the items\n";
		std::cout << "The available items are: Gun, AmmoClip FlashLight, Rock, and Hat\n\n";
		std::cout << "Available commands:\n";
		std::cout << "status - Displays the players itemslots\n";
		std::cout << "quit - Quits the game\n";
		std::cout << "help - Displays the insructions\n";
		std::cout << "[ItemSlot] equip [Item] - equips the item\n";
		std::cout << "[ItemSlot] unequip - Unequips the item held\n";
		std::cout << "[ItemSlot] get name - Gets name of held item\n";
		std::cout << "[ItemSlot] get ammo - If you are holding a gun displays the ammo left\n";
		std::cout << "[ItemSlot] reload - If you are holding a gun in one arm and an ammoclip in the other, it will reload the weapon\n";
		std::cout << "[ItemSlot] shoot - Shoots gun if you are holding one\n";
		std::cout << "[ItemSlot] swap [ItemSlot] - swaps held items\n";
		std::cout << "[ItemSlot] throw - Throw held item\n";
		std::cout << "[ItemSlot] toggle - Toggle item mode, usable on flashlight and gun\n";
		std::cout << "[ItemSlot] use - Uses the held items default action\n";
	}

	void CommandParser::SectionCommand(std::string a_Cmd, std::string& a_Word1, std::string& a_Word2, std::string& a_Word3)
	{
		std::string sub_str;
		std::vector<std::string> words;
		char search = ' ';

		//Seperate commands into words by searching for instances of spaces
		for (size_t i = 0; i < a_Cmd.size(); i++)
		{
			if (a_Cmd.at(i) != search)
			{
				sub_str.insert(sub_str.end(), a_Cmd.at(i));
			}
			if (i == a_Cmd.size() - 1)
			{
				words.push_back(sub_str);
				sub_str.clear();
			}
			if (a_Cmd.at(i) == search)
			{
				words.push_back(sub_str);
				sub_str.clear();
			}
		}

		//Erase any empty words
		for (size_t i = words.size() - size_t(1); i > 0; i--)
		{
			if (words.at(i) == "")
			{
				words.erase(words.begin() + i);
			}
		}

		//Make all words upper case
		for (size_t i = 0; i < words.size(); i++)
		{
			for (int j = 0; j < words.at(i).size(); j++)
			{
				if (islower(words.at(i).at(j)))
				{
					words.at(i).at(j) = toupper(words.at(i).at(j));
				}
			}
		}
		
		if (words.size() == 1)
		{
			a_Word1 = words.at(0);
		}
		else if (words.size() == 2)
		{
			a_Word1 = words.at(0);
			a_Word2 = words.at(1);
		}
		else if (words.size() == 3)
		{
			a_Word1 = words.at(0);
			a_Word2 = words.at(1);
			a_Word3 = words.at(2);
		}
		else if (words.size() > 3)
		{
			std::cout << "Command too long. Only type a maximum of 3 words\n";
		}
	}

	PlayerItemSlots CommandParser::ParseItemSlots(std::string a_Word1)
	{
		if (a_Word1 == "LEFTARM")
		{
			return PlayerItemSlots::LeftArmSlot;
		}
		else if (a_Word1 == "RIGHTARM")
		{
			return PlayerItemSlots::RightArmSlot;
		}
		else if (a_Word1 == "HEAD")
		{
			return PlayerItemSlots::HeadSlot;
		}
		else
		{
			throw InvalidItemSlot();
		}
	}

	void CommandParser::ParseEquip(std::string a_Word3, PlayerItemSlots a_SelectedSlot, std::shared_ptr<Player> a_Player, InteractResult& a_Result)
	{
		if (a_Word3 == "GUN")
		{
			a_Player->EquipItem(std::shared_ptr<EquipableItem>(std::make_shared<Gun>()), a_SelectedSlot, a_Result);
		}
		else if ("ROCK" == a_Word3)
		{
			a_Player->EquipItem(std::shared_ptr<EquipableItem>(std::make_shared<Rock>()), a_SelectedSlot, a_Result);
		}
		else if ("AMMOCLIP" == a_Word3)
		{
			a_Player->EquipItem(std::shared_ptr<EquipableItem>(std::make_shared<AmmoClip>()), a_SelectedSlot, a_Result);
		}
		else if ("HAT" == a_Word3)
		{
			a_Player->EquipItem(std::shared_ptr<EquipableItem>(std::make_shared<Hat>()), a_SelectedSlot, a_Result);
		}
		else if ("FLASHLIGHT" == a_Word3)
		{
			a_Player->EquipItem(std::shared_ptr<EquipableItem>(std::make_shared<FlashLight>()), a_SelectedSlot, a_Result);
		}
	}

	void CommandParser::ParseActions(std::string a_Word2, PlayerItemSlots a_SelectedSlot, std::shared_ptr<Player> a_Player, InteractResult& a_Result)
	{
		if (a_Word2 == "RELOAD")
		{
			a_Player->Reload(a_SelectedSlot, a_Result);
		}
		else if (a_Word2 == "SHOOT")
		{
			a_Player->Shoot(a_SelectedSlot, a_Result);
		}
		else if (a_Word2 == "THROW")
		{
			a_Player->Throw(a_SelectedSlot, a_Result);
		}
		else if (a_Word2 == "TOGGLE")
		{
			a_Player->ToggleState(a_SelectedSlot, a_Result);
		}
		else if (a_Word2 == "USE")
		{
		a_Player->Use(a_SelectedSlot, a_Result);
		}
	}

	void CommandParser::ParseGet(std::string a_Word3, PlayerItemSlots a_SelectedSlot, std::shared_ptr<Player> a_Player, InteractResult& a_Result)
	{
		if (a_Word3 == "NAME")
		{
			a_Result.message = "The player has " + a_Player->GetItemNameOnSlot(a_SelectedSlot) + " equipped\n";
			a_Result.success = true;
		}
		else if (a_Word3 == "AMMO")
		{
			a_Result.message =  "The gun has " + std::to_string(a_Player->GetAmmo(a_SelectedSlot)) + " bullets left\n";
			a_Result.success = true;
		}
	}

	void CommandParser::ParseSwap(std::string a_Word1, std::string a_Word3, PlayerItemSlots a_SelectedSlot, std::shared_ptr<Player> a_Player, InteractResult& a_Result)
	{
		if (a_Word3 == a_Word1)
		{
			"Cannot swap using the same itemslot\n";
			return;
		}
		else if (a_Word3 == "LEFTARM")
		{
			a_Player->SwapItems(a_SelectedSlot, LeftArmSlot, a_Result);
		}
		else if (a_Word3 == "RIGHTARM")
		{
			a_Player->SwapItems(a_SelectedSlot, RightArmSlot, a_Result);
		}
		else if (a_Word3 == "HEAD")
		{
			a_Player->SwapItems(a_SelectedSlot, HeadSlot, a_Result);
		}
	}

	void CommandParser::Parse(std::string a_Word1, std::string a_Word2, std::string a_Word3, std::shared_ptr<Player> a_Player)
	{
		if (a_Word1 == "HELP")
		{
			PrintHelp();
			return;
		}

		if (a_Word1 == "STATUS")
		{
			std::cout << "\n" << a_Player->GetStatus();
			return;
		}

		PlayerItemSlots selectedSlot = ParseItemSlots(a_Word1);
		InteractResult result;

		if (a_Word2 == "EQUIP")
		{
			ParseEquip(a_Word3, selectedSlot, a_Player, result);
		}
		else if (a_Word2 == "GET")
		{
			ParseGet(a_Word3, selectedSlot, a_Player, result);
		}
		else if (a_Word2 == "UNEQUIP")
		{
			a_Player->EquipItem(std::shared_ptr<EquipableItem>(std::make_shared<Gun>()), selectedSlot, result);
		}
		else if (a_Word2 == "SWAP")
		{
			ParseSwap(a_Word1, a_Word3, selectedSlot, a_Player, result);
		}
		else
		{
			ParseActions(a_Word2, selectedSlot, a_Player, result);
		}
		
		if (result.success)
		{
			std::cout << result.message;
		}
		else
		{
			std::cout << "Invalid command given\n";
		}
	}
}