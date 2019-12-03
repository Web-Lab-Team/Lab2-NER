#include <rapidjson/document.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../NER/String_convert.h"

using namespace std;

constexpr const char *DATA_FILE = "subtask1_training_part1.json";

// ��������� 0��Ӱ���� 1��ʵ���Ҽ��� 2��ҩ�� 3������ 4�����ʲ�λ 5
const map<string, int> entity_idx_map =
			{ {u8"���������", 0}, {u8"Ӱ����", 1}, {u8"ʵ���Ҽ���", 2}, 
			  {u8"ҩ��", 3}, {u8"����", 4}, {u8"���ʲ�λ", 5} };

struct Record {
	string original_text;
	vector<pair<int64_t/*start_pos*/, int64_t/*end_pos*/>> entities[sizeof(entity_idx_map)];
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
	//for (const auto &s : vec) {
	//	cout << String_convert::utf8_to_string(s) << endl;
	//}
}