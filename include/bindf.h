/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#pragma once

#include <vector>
#include <string>
#include <cstring>

typedef struct {
	const char* name;
	DWORD id;
} PatternData;

#define PATTERN_SIZE 14
const PatternData padPattern[] = {
	{"BOX_A",		XINPUT_GAMEPAD_A			},
	{"BOX_B",		XINPUT_GAMEPAD_B			},
	{"BOX_X",		XINPUT_GAMEPAD_X			},
	{"BOX_Y",		XINPUT_GAMEPAD_Y			},
	{"BOX_UP",		XINPUT_GAMEPAD_DPAD_UP		},
	{"BOX_DOWN",	XINPUT_GAMEPAD_DPAD_DOWN	},
	{"BOX_LEFT",	XINPUT_GAMEPAD_DPAD_LEFT	},
	{"BOX_RIGHT",	XINPUT_GAMEPAD_DPAD_RIGHT	},
	{"BOX_START",	XINPUT_GAMEPAD_START		},
	{"BOX_BACK",	XINPUT_GAMEPAD_BACK			},
	{"BOX_LT",		XINPUT_GAMEPAD_LEFT_THUMB	},
	{"BOX_RT",		XINPUT_GAMEPAD_RIGHT_THUMB	},
	{"BOX_LS",		XINPUT_GAMEPAD_LEFT_SHOULDER},
	{"BOX_RS",		XINPUT_GAMEPAD_RIGHT_SHOULDER}
};

typedef struct {
	char btn;
	DWORD btnPad;
} ParseData;

class BindF_File
{
public:
	~BindF_File();

	void ReadFile(string filename);
	void Parse();

	ParseData* pd;

private:
	bool CheckParse();
	void CheckPattern(string arr, int cur_line);

	vector<char> fData;
};
