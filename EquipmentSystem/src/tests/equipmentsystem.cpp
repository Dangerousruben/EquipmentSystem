#include "stdafx.h"
#include "player.h"
#include "commandparser.h"

int main()
{
	std::shared_ptr<EquipmentSystem::Player> player(std::make_shared<EquipmentSystem::Player>());
	std::shared_ptr<EquipmentSystem::CommandParser> command_parser(std::make_shared<EquipmentSystem::CommandParser>());
	std::string command = "";
	std::string word1 = "";
	std::string word2 = "";
	std::string word3 = "";
	std::cout << "Welcome to this demonstration of the equipment system\n";
	command_parser->PrintHelp();
	while (true)
	{
		try
		{
			command.clear();
			word1.clear();
			word2.clear();
			word3.clear();
			std::cout << ">>> ";
			getline(std::cin, command);
			if (command == "")
			{
				continue;
			}
			command_parser->SectionCommand(command, word1, word2, word3);

			if (word1 == "QUIT")
			{
				break;
			}
			command_parser->Parse(word1, word2, word3, player);
		}
		catch (const std::exception& e) {
			std::cout << e.what();
		}
	}
	return 0;
}
