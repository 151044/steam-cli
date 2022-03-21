#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <cstring>
#include "Game.hpp"
#include "utils/fs.hpp"
int main(int argc, char *argv[]){
	std::vector<Game> games;
	std::cout << "Steam CLI, v0.0.1" << std::endl;
	std::string toDevNull = "&> /dev/null";
	if(argc > 1){
		for(int i = 1; i < argc; i++){
			if(std::strcmp(argv[i],"--show-output") == 0 || std::strcmp(argv[i],"-o") == 0){
				toDevNull = "";
			}
		}
	}
	std::string command = "pidof steam &> /dev/null || ";
	if(toDevNull != ""){
		command += "nohup "; 
	}
	command += "steam -silent " + toDevNull + " &";
	system(command.c_str());
	for(auto&& entry: std::filesystem::directory_iterator(cutil::fs::getHomeDir() + "/.steam/steam/steamapps")){
		std::filesystem::path path = entry.path();
		if(path.extension() == ".acf"){
			std::string buf, str;
			std::ifstream stream(path.string());
			while(std::getline(stream, str)){
				buf += str;
				buf += "\n";
			}
			games.push_back(Game(buf));
		}
	}
	int response = 999;
	while(response >= 0){
		std::cout << "0 - Exit" << std::endl;
		for(int i = 0; i < games.size(); i++){
			std::cout << i + 1 << " - " << games.at(i).getName() << std::endl;
		}
		std::cout << ">> ";
		std::cin >> response;
		response--;
		if(response > static_cast<int>(games.size() - 1)){
			std::cout << "Index out of range.\n" << std::endl;
		}else if(response >= 0){
			Game game = games.at(response);
			std::cout << "Launching game " << game.getName() << ".\n" << std::endl;
			std::string args = "steam steam://rungameid/" + std::to_string(game.getAppId()) + " " + toDevNull;	
			std::system(args.c_str());
		}
	}
	command = "pidof steam &> /dev/null && steam -shutdown " + toDevNull + " &";
	system(command.c_str());
	return 0;
}
