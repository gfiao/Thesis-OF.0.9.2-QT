#include "EmotionInterval.h"
#include <iostream>
#include <map>
#include <algorithm>

//code from http://stackoverflow.com/a/15056107
std::string most_occurred(const std::vector<std::string> &vec) {
	if (vec.size() == 0)
		return "";

	std::map<std::string, unsigned long> str_map;
	for (const auto &str : vec)
		++str_map[str];

	typedef decltype(std::pair<std::string, unsigned long>()) pair_type;

	auto comp = [](const pair_type &pair1, const pair_type &pair2) -> bool {
		return pair1.second < pair2.second; };
	return std::max_element(str_map.cbegin(), str_map.cend(), comp)->first;
}

EmotionInterval::EmotionInterval(int timestamp, vector<string> emotions) {
	this->timestamp = timestamp;
	this->emotions = emotions;

	//if there is only 2 emotions, the second one will be the dominant one
	dominantEmotion = most_occurred(this->emotions);
}

int EmotionInterval::getTimestamp() {
	return timestamp;
}

string EmotionInterval::getDominantEmotion() {
	return dominantEmotion;
}

int EmotionInterval::getNumberOfEmotions() {
	return emotions.size();
}

vector<string> EmotionInterval::getEmotions() {
	return emotions;
}