#pragma once

#include "raylib.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <fstream>
#include <string>

using namespace std;

class DataFile
{
public:
	struct Record {
		Image image;
		string name;
		int age;
	};

private:
	int recordCount;

	float startOfRecords;
	float recordLength;
	ifstream infile;
	//std::vector<Record*> records;	// delete this vector. Load only the required record
	std::vector<int> starts;



public:
	DataFile();
	~DataFile();

	//void AddRecord(string imageFilename, string name, int age);
	//Record* GetRecord(int index);

	void GetPositions(string filename);
	unique_ptr<Record> LoadRecord(string filename, int index);

	int GetRecordCount() { return recordCount; };

	//void Save(string filename);
	//void Load(string filename);

private:
	//void Clear(); ///No longer needed as vector has been removed

};

