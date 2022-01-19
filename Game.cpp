#include "Game.hpp"
#include "utils/str.hpp"
#include <vector>
Game::Game(const std::string& manifest){
	std::vector<std::string> split = cutil::str::split(manifest, "\n");
	appid = std::stoi(split.at(2).substr(11, split.at(2).length() - 12));
	name = split.at(4).substr(10, split.at(4).length() - 11);
}
int Game::getAppId() const{
	return appid;
}
const std::string& Game::getName() const{
	return name;
}
