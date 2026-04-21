/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#include "bindf.h"
#include "main.h"

#include <fstream>

BindF_File::~BindF_File()
{
	delete[] pd;
}

void BindF_File::ReadFile(string filename)
{
	ifstream file(filename, ios::binary);

	if (!file) throw runtime_error("file read err");
	
	file.seekg(0, ios::end);
	size_t size = file.tellg();
	file.seekg(0, ios::beg);

	vector<char> timely(size);

	file.read(reinterpret_cast<char*>(timely.data()), size);

	if (file.gcount() != size)
		throw runtime_error("file read err");

	fData = timely;
}

void BindF_File::Parse()
{
	// W: BOX_A

	if (fData.size() < 1)
		throw runtime_error("file is incorrect");

	//if (CheckParse() != true)
	//	throw runtime_error("file is incorrect");
	
	string arr = "";

	int lines = 0;
	for (int i = 0; i < fData.size(); i++)
	{
		if (fData[i] == '\n') lines++;
	}

	iData.pd_lines = lines;

	pd = new ParseData[lines+1];

	int cur_line = 0;

	for (int i = 0; i < fData.size(); i++) {
		switch (fData[i])
		{
		case '\n':
			CheckPattern(arr, cur_line);
			arr = "";
			cur_line++;
			continue;
			break;
		case ':':
			if (arr.length() > 1) {
				CheckKeysPattern(arr, cur_line);
			}
			else pd[cur_line].btn = arr.c_str()[0];
			arr = "";
			continue;
			break;
		}
		arr += fData[i];
	}
}

bool BindF_File::CheckParse()
{
	bool p2 = true;
	bool end = true;

	for (int i = 0; i < fData.size(); i++) {
		if (fData[i] != ':') {
			p2 = false;
		}
		if (fData[i] != '\n') {
			end = false;
		}
	}

	return bool(p2 && end);
}

void BindF_File::CheckPattern(string arr, int cur_line)
{
	for (int i = 0; i < PATTERN_SIZE; i++) {
		if (memcmp(arr.c_str(), padPattern[i].name, strlen(padPattern[i].name)) == 0) {
			pd[cur_line].btnPad = padPattern[i].id;
			break;
		}
	}
}

void BindF_File::CheckKeysPattern(string arr, int cur_line)
{
	for (int i = 0; i < PATTERN_SIZE; i++) {
		if (memcmp(arr.c_str(),Keys[i].name, strlen(Keys[i].name)) == 0) {
			pd[cur_line].btn = Keys[i].id;
			break;
		}
	}
}
