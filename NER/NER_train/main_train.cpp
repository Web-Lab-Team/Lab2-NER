#include <rapidjson/document.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include "../NER/String_convert.h"
#include "Output.h"

using namespace std;

constexpr const char *DATA_FILE = "subtask1_training_part1.json";

// 疾病和诊断 0、影像检查 1、实验室检验 2、药物 3、手术 4、解剖部位 5
const map<string, int> entity_idx_map =
			{ {u8"疾病和诊断", 0}, {u8"影像检查", 1}, {u8"实验室检验", 2}, 
			  {u8"药物", 3}, {u8"手术", 4}, {u8"解剖部位", 5} };

struct Record {
	string original_text;
	vector<pair<int64_t/*start_pos*/, int64_t/*end_pos*/>> entities[6];
};

Record read_record(const string &str) {
	static rapidjson::Document document;
	Record rec;
	document.Parse(str.c_str());
	assert(!document.HasParseError());
	assert(document.IsObject());
	assert(document.HasMember("originalText"));
	assert(document.HasMember("entities"));
	assert(document["originalText"].IsString());
	assert(document["entities"].IsArray());
	rec.original_text = document["originalText"].GetString();
	for (auto it = document["entities"].Begin(); it != document["entities"].End(); ++it) {
		assert(it->IsObject()); 
		auto entity = it->GetObject();
		assert(entity.HasMember("label_type"));
		assert(entity.HasMember("start_pos"));
		assert(entity.HasMember("end_pos"));
		assert(entity["label_type"].IsString());
		assert(entity["start_pos"].IsInt64());
		assert(entity["end_pos"].IsInt64());
		string label = entity["label_type"].GetString();
		auto map_it = entity_idx_map.find(label);
		assert(map_it != entity_idx_map.end());
		rec.entities[map_it->second].emplace_back(entity["start_pos"].GetInt64(), 
												  entity["end_pos"].GetInt64());
	}
	return rec; 
}

vector<Record> read_data(const char *file) {
	ifstream infile(file);
	if (infile.fail()) {
		cerr << "cannot open file " << file << endl;
		exit(-1);
	}
	string line;
	vector<Record> vec;
	while (getline(infile, line)) {
		vec.push_back(read_record(line));
	}
	return vec;
}

int main() {
	vector<Record> vec = read_data(DATA_FILE);
	String_convert::init();

	for (const Record &rec : vec) {
		wstring wtext = String_convert::utf8_to_wstring(rec.original_text);
		unique_ptr<int[]> color(new int[wtext.size()]);
		memset(color.get(), 0, wtext.size() * sizeof(int));
		for (int i = 0; i < 6; ++i)
			for (const auto &p : rec.entities[i]) 
				fill(color.get() + p.first, color.get() + p.second, i + 1);
		for (const auto &p : entity_idx_map)
			Output::print_color(String_convert::utf8_to_wstring(p.first), 
								(Output::Color)(p.second + 1)) << ' ';
		wcout << endl;
		for (int i = 0; i < wtext.size(); ++i)
			Output::print_color(wtext[i], (Output::Color)color[i]);
		wcout << endl << endl;
		cin.get();
	}
}