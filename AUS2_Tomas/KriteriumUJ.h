#pragma once
#include "Kriterium.h"

template <typename T, typename R>
class KriteriumUJ : public Kriterium<UzemnaJednotka*, T, R> {
public:
	virtual T getHodnotu(UzemnaJednotka* uzemnaJednotka, R r) = 0;
};

class KriteriumUJNazov : public KriteriumUJ<wstring, wstring> {
public:
	wstring getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter) override;
};

wstring KriteriumUJNazov::getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter)
{
	return uzemnaJednotka->getNazov();
}

class KriteriumUJTyp : public KriteriumUJ<UzemnaJednotka::typUJ, wstring> {
public:
	UzemnaJednotka::typUJ getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter) override;
};

UzemnaJednotka::typUJ KriteriumUJTyp::getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter)
{
	return uzemnaJednotka->getTyp();
}

class KriteriumUJPrislusnost : public KriteriumUJ<bool, wstring> {
public:
	bool getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter) override;
};

bool KriteriumUJPrislusnost::getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter)
{
	if (uzemnaJednotka->getVyssiaUJ() != nullptr)
	{
		return uzemnaJednotka->getVyssiaUJ()->getNazov() == pomParameter;
	}
	return false;
}

class KriteriumUJPocetPredproduktivnychObyvatelov : public KriteriumUJ<int, wstring> {
public:
	int getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter) override;
};

int KriteriumUJPocetPredproduktivnychObyvatelov::getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter)
{
	return uzemnaJednotka->getPredproduktivnyObyvatelia();
}

class KriteriumUJPocetProduktivnychObyvatelov : public KriteriumUJ<int, wstring> {
public:
	int getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter) override;
};

int KriteriumUJPocetProduktivnychObyvatelov::getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter)
{
	return uzemnaJednotka->getProduktivnyObyvatelia();
}

class KriteriumUJPocetPoproduktivnychObyvatelov : public KriteriumUJ<int, wstring> {
public:
	int getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter) override;
};

int KriteriumUJPocetPoproduktivnychObyvatelov::getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter)
{
	return uzemnaJednotka->getPoproduktivnyObyvatelia();
}

class KriteriumUJPocetObyvatelov : public KriteriumUJ<int, wstring> {
public:
	int getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter) override;
};

int KriteriumUJPocetObyvatelov::getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter)
{
	return uzemnaJednotka->getPredproduktivnyObyvatelia()  + uzemnaJednotka->getProduktivnyObyvatelia() + uzemnaJednotka->getPoproduktivnyObyvatelia();
}

class KriteriumUJCelkovaVymera : public KriteriumUJ<double, wstring> {
public:
	double getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter) override;
};

double KriteriumUJCelkovaVymera::getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter)
{
	return uzemnaJednotka->getCelkovaVymera();
}

class KriteriumUJZastavanaPlocha : public KriteriumUJ<double, wstring> {
public:
	double getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter) override;
};

double KriteriumUJZastavanaPlocha::getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter)
{
	return uzemnaJednotka->getZastavanaPlocha();
}

class KriteriumUJZastavanost : public KriteriumUJ<double, wstring> {
public:
	double getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter) override;
};

double KriteriumUJZastavanost::getHodnotu(UzemnaJednotka* uzemnaJednotka, wstring pomParameter)
{
	return (100 * (uzemnaJednotka->getZastavanaPlocha() / uzemnaJednotka->getCelkovaVymera()));
}