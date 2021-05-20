#pragma once
#include "UzemnaJednotka.h"

template <typename O, typename T, typename R>
class Kriterium
{
public:
	virtual T getHodnotu(O o, R r) = 0;
private:
};

