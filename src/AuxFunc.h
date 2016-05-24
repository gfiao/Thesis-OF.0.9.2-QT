#pragma once

#include <vector>
#include <string>
#include <sstream>

class AuxFunc {

public:

	static vector<string> split(const string &s, char delim);
	static bool is_number(const std::string& s);
	static string formatSeconds(int seconds);
    static int getMax(vector<int> vec);
};
