#include <rapidjson/document.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "String_convert.h"

using namespace std;

vector<string> readData(const char *file) {
	ifstream infile(file);
	if (infile.fail()) { 
		cerr << "cannot open file " << file << endl;
		exit(-1);
	} 
	rapidjson::Document document;
	string line;
	vector<string> vec;
	int64_t i = 0;
	while (getline(infile, line)) {
		document.Parse(line.c_str());
		assert(document.IsObject());
		assert(document.HasMember("originalText"));
		assert(document.HasMember("textId"));
		assert(document["originalText"].IsString());
		assert(document["textId"].IsInt64());
		assert(document["textId"].GetInt64() == i++);
		vec.emplace_back(document["originalText"].GetString());
	}
	return vec;
}

int main() {
	vector<string> vec = readData("实验二测试数据集.json");
	for (const auto &s : vec) {
		cout << String_convert::utf8_to_string(s) << endl;
	}
}