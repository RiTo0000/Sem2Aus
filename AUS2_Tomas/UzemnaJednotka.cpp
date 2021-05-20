#include "UzemnaJednotka.h"

UzemnaJednotka::UzemnaJednotka(wstring nazov, UzemnaJednotka::typUJ typ, UzemnaJednotka* vyssiaUJ)
{
	this->nazov = nazov;
	this->typ = typ;
	this->vyssiaUJ = vyssiaUJ;
	this->nizsiaUJ = new SortedSequenceTable<wstring, UzemnaJednotka*>();
}

UzemnaJednotka::~UzemnaJednotka()
{
	delete this->vyssiaUJ;
	this->vyssiaUJ = nullptr;
	delete this->nizsiaUJ;
	this->nizsiaUJ = nullptr;
}

wstring UzemnaJednotka::getNazov()
{
	return this->nazov;
}

UzemnaJednotka::typUJ UzemnaJednotka::getTyp()
{
	return this->typ;
}

UzemnaJednotka* UzemnaJednotka::getVyssiaUJ()
{
	return vyssiaUJ;
}

void UzemnaJednotka::nastavudajeUJ(int predproduktivniObyvatelia, int produktivniObyvatelia, int poproduktivniObyvatelia, double celkovaVymera, double zastavanaPlocha)
{
	this->predproduktivniObyvatelia += predproduktivniObyvatelia;
	this->produktivniObyvatelia += produktivniObyvatelia;
	this->poproduktivniObyvatelia += poproduktivniObyvatelia;
	this->celkovaVymera += celkovaVymera;
	this->zastavanaPlocha += zastavanaPlocha;
}

void UzemnaJednotka::nastavNizsiuUJ(wstring kluc, UzemnaJednotka* uzemnaJednotka)
{
	this->nizsiaUJ->insert(kluc, uzemnaJednotka);
}

int UzemnaJednotka::getPredproduktivnyObyvatelia()
{
	return this->predproduktivniObyvatelia;
}

int UzemnaJednotka::getProduktivnyObyvatelia()
{
	return this->produktivniObyvatelia;
}

int UzemnaJednotka::getPoproduktivnyObyvatelia()
{
	return this->poproduktivniObyvatelia;
}

double UzemnaJednotka::getZastavanaPlocha()
{
	return this->zastavanaPlocha;
}

double UzemnaJednotka::getCelkovaVymera()
{
	return this->celkovaVymera;
}


SortedSequenceTable<wstring, UzemnaJednotka*>* UzemnaJednotka::vratNizsieUJ()
{
	return this->nizsiaUJ;
}
