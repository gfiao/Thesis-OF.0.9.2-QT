using namespace std;

#include "AuxFunc.h"

//auxiliary function to split a string
//code originally from http://ysonggit.github.io/coding/2014/12/16/split-a-string-using-c.html
vector<string> AuxFunc::split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

//checks if a string is a number
//code originally from http://stackoverflow.com/a/4654718
bool AuxFunc::is_number(const string& s) {
    string::const_iterator it = s.begin();

    while (it != s.end() && (isdigit(*it) || *it == '.'))
        ++it;

    return !s.empty() && it == s.end();
}

//formats seconds into the HH:MM:SS format
//example: 120 seconds formats to 00:02:00
string AuxFunc::formatSeconds(int seconds) {

    //code based on http://stackoverflow.com/a/25697134
    int minutes = seconds / 60;
    int hours = minutes / 60;
    seconds = seconds % 60;

    string stringHours = to_string(hours);
    string stringMinutes = to_string(minutes);
    string stringSeconds = to_string(seconds);

    //add 0 to the string
    if (stringHours.size() == 1) stringHours = "0" + stringHours;
    if (stringMinutes.size() == 1) stringMinutes = "0" + stringMinutes;
    if (stringSeconds.size() == 1) stringSeconds = "0" + stringSeconds;

    return stringHours + ":" + stringMinutes + ":" + stringSeconds;
}

int AuxFunc::getMax(vector<int> vec){
    int max = 0;
    for(int i : vec){
        if(i > max) max = i;
    }
    return max;
}
