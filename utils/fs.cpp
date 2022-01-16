#include "fs.hpp"
namespace cutil::fs{
	std::string getHomeDir(){
		#ifdef _WIN32
			return std::getenv("HOMEDRIVE") + std::getenv("HOMEDIR");	
		#else
			return std::getenv("HOME");
		#endif
	}
}
