#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include "structures/structure.h"
#include "structures/table/sequence_table.h"
#include "structures/table/sorted_sequence_table.h"
#include "UzemnaJednotka.h"

using namespace std;
using namespace structures;

class Input
{
public:
	Input();
	~Input();
	void nacitajUJ(UzemnaJednotka* stat, string nazovSuboru);
	void nacitajObyvatelov(UzemnaJednotka* stat, string nazovSuboru);
private:
	wifstream subor;

};

