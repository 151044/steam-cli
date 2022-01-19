#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include "Game.hpp"
#include "utils/fs.hpp"
int main(){
	std::vector<Game> games;
	std::cout << "Steam CLI, v0.0.1" << std::endl;
	system("pidof steam &> /dev/null || nohup steam -silent &> /dev/null &");
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
			std::cout << response << " " << games.size() - 1 << std::endl;
			std::cout << "Index out of range.\n" << std::endl;
		}else if(response >= 0){
			Game game = games.at(response);
			std::cout << "Launching game " << game.getName() << ".\n" << std::endl;
			std::string args = "steam steam://rungameid/" + std::to_string(game.getAppId()) + " &> /dev/null";	
			std::system(args.c_str());
		}
	}
	system("pidof steam &> /dev/null || steam -shutdown &> /dev/null &");
	return 0;
}
