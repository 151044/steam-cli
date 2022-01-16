#pragma once
#include <string>
class Game{
        int appid;
        std::string name;
    public:
        std::string getName();
        int getAppId();
		Game(const std::string&);
};
