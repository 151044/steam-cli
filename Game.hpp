#pragma once
#include <string>
class Game{
        int appid;
        std::string name;
    public:
        const std::string& getName() const;
        int getAppId() const;
		Game(const std::string&);
};
