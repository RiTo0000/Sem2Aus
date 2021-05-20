#pragma once
#include <iostream>
#include "UzemnaJednotka.h"
#include "Kriterium.h"
#include "KriteriumUJ.h"

template <typename O, typename T>
class Filter
{
public:
	virtual bool splnaFilter(O o, T t, UnsortedSequenceTable<wstring, O>* finalData, bool vypisOsob) = 0;

};