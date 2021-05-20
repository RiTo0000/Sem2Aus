#pragma once
#include <string>
#include "structures/structure.h"
#include "structures/table/sequence_table.h"
#include "structures/table/sorted_sequence_table.h"

using namespace std;
using namespace structures;

class UzemnaJednotka
{
public:
	enum typUJ
	{
		štát,
		kraj,
		okres,
		obec
	};

	UzemnaJednotka(wstring nazov, UzemnaJednotka::typUJ typ, UzemnaJednotka* vyssiaUJ);
	~UzemnaJednotka();
	wstring getNazov();
	UzemnaJednotka::typUJ getTyp();
	UzemnaJednotka* getVyssiaUJ();
	void nastavudajeUJ(int predproduktivniObyvatelia, int produktivniObyvatelia, int poproduktivniObyvatelia, double celkovaVymera, double zastavanaPlocha);
	void nastavNizsiuUJ(wstring kluc, UzemnaJednotka* uzemnaJednotka);
	int getPredproduktivnyObyvatelia();
	int getProduktivnyObyvatelia();
	int getPoproduktivnyObyvatelia();
	double getZastavanaPlocha();
	double getCelkovaVymera();
	SortedSequenceTable<wstring, UzemnaJednotka*>* vratNizsieUJ();

private:
	wstring nazov;
	int predproduktivniObyvatelia = 0;
	int produktivniObyvatelia = 0;
	int poproduktivniObyvatelia = 0;
	double celkovaVymera = 0;
	double zastavanaPlocha = 0;
	UzemnaJednotka::typUJ typ;
	UzemnaJednotka* vyssiaUJ = nullptr;
	SortedSequenceTable<wstring, UzemnaJednotka*>* nizsiaUJ = nullptr;
};

