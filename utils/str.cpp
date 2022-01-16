#include "str.hpp"
#include <iostream>
namespace cutil::str{
	std::vector<std::string> split(const std::string& input, const std::string& delimiter){
		std::vector<std::string> vec;
		int delim_len = delimiter.length();
		int delim_pos = input.find(delimiter);
		int pos = 0;
		while(delim_pos != std::string::npos){
			vec.push_back(input.substr(pos, delim_pos - pos));
			pos = delim_pos + delim_len;	
			delim_pos = input.find(delimiter, pos);
		}
		return vec;
	}
}
