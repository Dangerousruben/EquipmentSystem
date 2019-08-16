#include "stdafx.h"
#include "Player.h"
#include "Item.h"
#include "Gun.h"
#include "Rock.h"
#include "AmmoClip.h"
#include "Hat.h"
#include "FlashLight.h"

void section_command(std::string Cmd, std::string &wd1, std::string &wd2, std::string &wd3)
{
	std::string sub_str;
	std::vector<std::string> words;
	char search = ' ';
	size_t i, j;
	for (i = 0; i < Cmd.size(); i++)
	{
		if (Cmd.at(i) != search)
		{
			sub_str.insert(sub_str.end(), Cmd.at(i));
		}
		if (i == Cmd.size() - 1)
		{
			words.push_back(sub_str);
			sub_str.clear();
		}
		if (Cmd.at(i) == search)
		{
			words.push_back(sub_str);
			sub_str.clear();
		}
	}
	// Clear out any blanks
	for (i = words.size() - 1; i > 0; i--)
	{
		if (words.at(i) == "")
		{
			words.erase(words.begin() + i);
		}
	}
	// Make words upper case
	for (i = 0; i < words.size(); i++)
	{
		for (j = 0; j < words.at(i).size(); j++)
		{
			if (islower(words.at(i).at(j)))
			{
				words.at(i).at(j) = toupper(words.at(i).at(j));
			}
		}
	}
	if (words.size() == 0)
	{
		std::cout << "No command given\n";
	}
	else if (words.size() == 1)
	{
		wd1 = words.at(0);
	}
	else if (words.size() == 2)
	{
		wd1 = words.at(0);
		wd2 = words.at(1);
	}
	else if (words.size() == 3)
	{
		wd1 = words.at(0);
		wd2 = words.at(1);
		wd3 = words.at(2);
	}
	else if (words.size() > 3)
	{
		std::cout << "Command too long. Only type a maximum of 3 words\n";
	}
}

bool parser(std::string wd1, std::string wd2, std::string wd3, std::shared_ptr<Player> a_Player)
{
	PlayerItemSlots selectedSlot;
	if (wd1 == "LEFTARM")
	{
		selectedSlot = PlayerItemSlots::LeftArmSlot;
	}
	else if (wd1 == "RIGHTARM")
	{
		selectedSlot = PlayerItemSlots::RightArmSlot;
	}
	else if (wd1 == "HEAD")
	{
		selectedSlot = PlayerItemSlots::HeadSlot;
	}
	else
	{
		throw InvalidItemSlot();
	}

	if (wd2 == "EQUIP")
	{
		if (wd3 == "GUN")
		{
			if (a_Player->EquipItem(std::shared_ptr<Item>(std::make_shared<Gun>()), selectedSlot))
			{
				std::cout << "Player has equipped the Gun\n";
				return true;
			}
		}
		else if ("ROCK" == wd3)
		{
			if (a_Player->EquipItem(std::shared_ptr<Item>(std::make_shared<Rock>()), selectedSlot))
			{
				std::cout << "Player has equipped the Rock\n";
				return true;
			}
		}
		else if ("AMMOCLIP" == wd3)
		{
			if (a_Player->EquipItem(std::shared_ptr<Item>(std::make_shared<AmmoClip>()), selectedSlot))
			{
				std::cout << "Player has equipped the AmmoClip\n";
				return true;
			}
		}
		else if ("HAT" == wd3)
		{
			if (a_Player->EquipItem(std::shared_ptr<Item>(std::make_shared<Hat>()), selectedSlot))
			{
				std::cout << "Player has equipped the Hat\n";
				return true;
			}
		}
		else if ("FLASHLIGHT" == wd3)
		{
			if (a_Player->EquipItem(std::shared_ptr<Item>(std::make_shared<FlashLight>()), selectedSlot))
			{
				std::cout << "Player has equipped the FlashLight\n";
				return true;
			}
		}
	}
	else if (wd2 == "INTERACT")
	{
		InteractResult result;
		a_Player->Interact(selectedSlot, result);
		std::cout << result.Message;
		if (result.Unequip)
		{
			std::cout << "Interacted item was unequipped\n";
		}
		return result.Success;
	}
	else if (wd2 == "RELOAD")
	{
		InteractResult result;
		a_Player->Reload(selectedSlot, result);
		std::cout << result.Message;
		return result.Success;
	}
	else if (wd2 == "SHOOT")
	{
		InteractResult result;
		a_Player->Shoot(selectedSlot, result);
		std::cout << result.Message;
		return result.Success;
	}
	else if (wd2 == "THROW")
	{
		InteractResult result;
		a_Player->Throw(selectedSlot, result);
		std::cout << result.Message;
		return result.Success;
	}
	else if (wd2 == "TURNONOFF")
	{
		InteractResult result;
		a_Player->TurnOnOff(selectedSlot, result);
		std::cout << result.Message;
		return result.Success;
	}
	else if (wd2 == "TOGGLEGUNMODE")
	{
		InteractResult result;
		a_Player->ToggleGunMode(selectedSlot, result);
		std::cout << result.Message;
		return result.Success;
	}
	else if (wd2 == "USE")
	{
		InteractResult result;
		a_Player->Use(selectedSlot, result);
		std::cout << result.Message;
		return result.Success;
	}
	else if (wd2 == "GET")
	{
		if (wd3 == "NAME")
		{
			std::cout << "The player has " << a_Player->GetItemNameOnSlot(selectedSlot) << " equipped\n";
			return true;
		}
		else if (wd3 == "AMMO")
		{
			std::cout<<"The gun has " << a_Player->GetAmmo(selectedSlot) << " bullets left\n";
			return true;
		}
	}
	else if (wd2 == "UNEQUIP")
	{
		if (a_Player->UnEquipItem(selectedSlot))
		{
			std::cout << "The selected item slot has been unequipped its item\n";
			return true;
		}
			
	}
	else if (wd2 == "SWAP")
	{
		if (wd3 == "LEFTARM")
		{
			a_Player->SwapItems(selectedSlot, LeftArmSlot);
			return true;
		}
		else if (wd3 == "RIGHTARM")
		{
			a_Player->SwapItems(selectedSlot, RightArmSlot);
			return true;
		}
		else if (wd3 == "HEAD")
		{
			a_Player->SwapItems(selectedSlot, HeadSlot);
			return true;
		}
	}
	return false;
}

int main()
{
	std::vector<std::string> AvailableItems = { "Gun", "Rock" };
	std::shared_ptr<Player> player(new Player());
	std::string command;
	std::string word1;
	std::string word2;
	std::string word3;
	std::cout << "Hello Player what do you want to do?\n";
	while (word1 != "QUIT")
	{
		try
		{
			command.clear();
			word1.clear();
			word2.clear();
			word3.clear();
			getline(std::cin, command);
			if (command != "")
			{
				section_command(command, word1, word2, word3);

				if (word1 != "QUIT")
				{
					if (!parser(word1, word2, word3, player))
					{
						std::cout << "No valid command entered.\n";
					}
				}
			}
		}
		catch (const std::exception& e) {
			std::cout << e.what();
		}
	}
	return 0;
}