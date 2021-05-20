#include <iostream>

#include "Input.h"
#include "structures/structure.h"
#include "structures/table/sequence_table.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"
#include "UzemnaJednotka.h"
#include "Kriterium.h"
#include "KriteriumUJ.h"
#include "Filter.h"
#include "FilterUJ.h"
#include "structures/table/sorting/quick_sort.h"

#include <Windows.h>
#include <io.h>
#include <fcntl.h>

using namespace std;
using namespace structures;

int vyber = 0;
UzemnaJednotka* slovensko = new UzemnaJednotka(L"Slovensko", UzemnaJednotka::typUJ::štát, nullptr);


void menu();
void vyberFiltraVypis(bool vypisObec);
void vypisUJ(UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData);
template <typename T>
void zoradenieUJlogika(bool obec, KriteriumUJ<T, wstring>* kriterium);
void zoradenieUJ(bool obec);
template <typename T>
void prepisMedziPolami(UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData, UnsortedSequenceTable<wstring, T>* data);

int main() {
	//initHeapMonitor();
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	wcout << L"Nacitavaju sa udaje..." << endl;
	Input* in = new Input();
	in->nacitajUJ(slovensko, "files\\2_Tzemné_ƒlenenie_SR.csv");
	in->nacitajObyvatelov(slovensko, "files\\1_Obce_SR.csv");
	menu();
	delete in;
	in = nullptr;
	delete slovensko;
	slovensko = nullptr;
}

void vyberFiltraVypis(bool vypisObec) {
	wcout << L"Vyber si filter:" << endl;
	wcout << L"1: FujNazov" << endl;
	wcout << L"2: FujPocetObyvatelov" << endl;
	wcout << L"3: FujZastavanost " << endl;

	do
	{
		wcout << "Tvoj vyber: " << endl;
		wcin >> vyber;
	} while (vyber > 3 || vyber < 1);

	FilterUJ<wstring>* fujnazov = new FilterUJNazov();
	FilterUJ<int>* fujpocetObyvatelov = new FilterUJPocetObyvatelov();
	FilterUJ<double>* fujzastavanost = new FilterUJZastavanost();
	FilterUJ<UzemnaJednotka::typUJ>* fujtyp = new FilterUJTyp();
	FilterUJ<wstring>* fujprislusnost = new FilterUJPrislusnost();
	UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData = new UnsortedSequenceTable<wstring, UzemnaJednotka*>();

	wstring nazovObce;
	wstring prislusnost;
	int cislo;
	if (!vypisObec)
	{
		wcout << L"Vyber si typ" << endl;
		wcout << L"1-obec, 2-okres, 3-kraj, 4-stat" << endl;
		do
		{
			wcin >> cislo;
		} while (cislo < 1 || cislo > 4);
		wcout << L"Zadaj prislusnost" << endl;
		wcin.ignore();
		getline(wcin, prislusnost);
	}
	switch (vyber)
	{
	case 1:
		wcout << L"Nazov obce" << endl;
		wcin.ignore();
		getline(wcin, nazovObce);
		wcout << nazovObce << endl;
		if (!fujnazov->splnaFilter(slovensko, nazovObce, finalData, vypisObec))
		{
			wcout << nazovObce << L"Zadal si zly nazov UJ" << endl;
		}
		if (!vypisObec)
		{
			switch (cislo)
			{
			case 1 :
				fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::obec, finalData, vypisObec);
				break;
			case 2:
				fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::okres, finalData, vypisObec);
				break;
			case 3:
				fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::kraj, finalData, vypisObec);
				break;
			case 4:
				fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::štát, finalData, vypisObec);
				break;
			default:
				break;
			}
			if (finalData->size() == 0)
			{
				wcout << L"ziadne data na vypis" << endl;
				break;
			}
			fujprislusnost->splnaFilter(slovensko, prislusnost, finalData, vypisObec);
		}
		vypisUJ(finalData);
		break;
	case 2:
		wcout << L"Pocet obyvatelov" << endl;
		int pocetObyv;
		wcin >> pocetObyv;
		if (!fujpocetObyvatelov->splnaFilter(slovensko, pocetObyv, finalData, vypisObec))
		{
			wcout << pocetObyv << L"Neexistuje obec s vyssym poctom obyvatelov" << endl;
		}
		if (!vypisObec)
		{
			switch (cislo)
			{
			case 1:
				fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::obec, finalData, vypisObec);
				break;
			case 2:
				fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::okres, finalData, vypisObec);
				break;
			case 3:
				fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::kraj, finalData, vypisObec);
				break;
			case 4:
				fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::štát, finalData, vypisObec);
				break;
			default:
				break;
			}
			if (finalData->size() == 0)
			{
				wcout << L"ziadne data na vypis" << endl;
				break;
			}
			fujprislusnost->splnaFilter(slovensko, prislusnost, finalData, vypisObec);
		}
		vypisUJ(finalData);
		break;
	case 3:
		wcout << L"Zastavanost" << endl;
		double zastavanost;
		wcin >> zastavanost;
		if (!fujzastavanost->splnaFilter(slovensko, zastavanost, finalData, vypisObec))
		{
			wcout << zastavanost << L"Neexistuje obec s vyssou zastavanostou" << endl;
		}
		if (!vypisObec)
		{
			switch (cislo)
			{
			case 1:
				fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::obec, finalData, vypisObec);
				break;
			case 2:
				fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::okres, finalData, vypisObec);
				break;
			case 3:
				fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::kraj, finalData, vypisObec);
				break;
			case 4:
				fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::štát, finalData, vypisObec);
				break;
			default:
				break;
			}
			if (finalData->size() == 0)
			{
				wcout << L"ziadne data na vypis" << endl;
				break;
			}
			fujprislusnost->splnaFilter(slovensko, prislusnost, finalData, vypisObec);
		}
		vypisUJ(finalData);
		break;
	default:
		break;
	}
	delete fujnazov;
	fujnazov = nullptr;
	delete fujpocetObyvatelov;
	fujpocetObyvatelov = nullptr;
	delete fujzastavanost;
	fujzastavanost = nullptr;
	delete fujtyp;
	fujtyp = nullptr;
	delete fujprislusnost;
	fujprislusnost = nullptr;
	finalData = nullptr;
}

void vypisUJ(UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData)
{
	Kriterium<UzemnaJednotka*, wstring, wstring>* Knazov = new KriteriumUJNazov();
	Kriterium<UzemnaJednotka*, int, wstring>* KPocObyvatelov = new KriteriumUJPocetObyvatelov();
	Kriterium<UzemnaJednotka*, int, wstring>* KPocPredprodObyv = new KriteriumUJPocetPredproduktivnychObyvatelov();
	Kriterium<UzemnaJednotka*, int, wstring>* KPocProdObyv = new KriteriumUJPocetProduktivnychObyvatelov();
	Kriterium<UzemnaJednotka*, int, wstring>* KPocPoprodObyv = new KriteriumUJPocetPoproduktivnychObyvatelov();
	Kriterium<UzemnaJednotka*, double, wstring>* Kzastavanost = new KriteriumUJZastavanost();
	Kriterium<UzemnaJednotka*, double, wstring>* KcelkovaVymera = new KriteriumUJCelkovaVymera();
	Kriterium<UzemnaJednotka*, double, wstring>* kzastavanaPlocha = new KriteriumUJZastavanaPlocha();
	UzemnaJednotka* help;

	for (TableItem<wstring, UzemnaJednotka*>* item : *finalData)
	{
		help = item->accessData();
		while (help->getVyssiaUJ() != nullptr)
		{
			wcout << Knazov->getHodnotu(help, L"") << L" ";
			help = help->getVyssiaUJ();
		}
		wcout << endl;
		wcout << L"Pocet obyvatelov: " << KPocObyvatelov->getHodnotu(item->accessData(), L"") << endl;
		wcout << L"Pocet predproduktivnych obyvatelov: " << KPocPredprodObyv->getHodnotu(item->accessData(), L"") << endl;
		wcout << L"Pocet produktivnych obyvatelov: " << KPocProdObyv->getHodnotu(item->accessData(), L"") << endl;
		wcout << L"Pocet poproduktivnych obyvatelov: " << KPocPoprodObyv->getHodnotu(item->accessData(), L"") << endl;
		wcout << L"Zastavanost: " << Kzastavanost->getHodnotu(item->accessData(), L"") << endl;
		wcout << L"Celkova vymera: " << KcelkovaVymera->getHodnotu(item->accessData(), L"") << endl;
		wcout << L"Zastavana plocha: " << kzastavanaPlocha->getHodnotu(item->accessData(), L"") << endl;
		wcout << endl;
	}
	delete Knazov;
	Knazov = nullptr;
	delete KPocObyvatelov;
	KPocObyvatelov = nullptr;
	delete KPocPredprodObyv;
	KPocPredprodObyv = nullptr;
	delete KPocProdObyv;
	KPocProdObyv = nullptr;
	delete KPocPoprodObyv;
	KPocPoprodObyv = nullptr;
	delete Kzastavanost;
	Kzastavanost = nullptr;
	delete KcelkovaVymera;
	KcelkovaVymera = nullptr;
	delete KcelkovaVymera;
	KcelkovaVymera = nullptr;
	help = nullptr;
}

void zoradenieUJ(bool obec)
{
	wcout << L"Vyber si kriterium zoradenia:" << endl;
	wcout << L"1: KujNazov" << endl;
	wcout << L"2: KujPocetObyvatelov" << endl;
	wcout << L"3: KujZastavanost " << endl;

	do
	{
		wcout << "Tvoj vyber: " << endl;
		wcin >> vyber;
	} while (vyber > 3 || vyber < 1);

	KriteriumUJ<wstring, wstring>* kujnazov = new KriteriumUJNazov();
	KriteriumUJ<int, wstring>* kujpocetObyvatelov = new KriteriumUJPocetObyvatelov();
	KriteriumUJ<double, wstring>* kujzastavanost = new KriteriumUJZastavanost();
	
	switch (vyber)
	{
	case 1:
		zoradenieUJlogika(obec, kujnazov);
		break;
	case 2:
		zoradenieUJlogika(obec, kujpocetObyvatelov);
		break;
	case 3:
		zoradenieUJlogika(obec, kujzastavanost);
		break;
	default:
		break;
	}
	delete kujnazov;
	kujnazov = nullptr;
	delete kujpocetObyvatelov;
	kujpocetObyvatelov = nullptr;
	delete kujzastavanost;
	kujzastavanost = nullptr;
}

template<typename T>
void zoradenieUJlogika(bool obec, KriteriumUJ<T, wstring>* kriterium)
{
	UnsortedSequenceTable<wstring, UzemnaJednotka*>* dataUJ = new UnsortedSequenceTable<wstring, UzemnaJednotka*>();
	UnsortedSequenceTable<wstring, T>* data = new UnsortedSequenceTable<wstring, T>();
	QuickSort<wstring, T>* quickSort = new QuickSort<wstring, T>();
	FilterUJ<UzemnaJednotka::typUJ>* fujtyp = new FilterUJTyp();
	FilterUJ<wstring>* fujprislusnost = new FilterUJPrislusnost();
	
	wstring prislusnost;
	int cislo;
	if (!obec)
	{
		wcout << L"Vyber si typ" << endl;
		wcout << L"1-obec, 2-okres, 3-kraj, 4-stat" << endl;
		do
		{
			wcin >> cislo;
		} while (cislo < 1 || cislo > 4);
		wcout << L"Zadaj prislusnost" << endl;
		wcin.ignore();
		getline(wcin, prislusnost);
	}
	for (TableItem<wstring, UzemnaJednotka*>* kraj : *slovensko->vratNizsieUJ())
	{
		if (!obec)
		{
			data->insert(kraj->getKey(), kriterium->getHodnotu(kraj->accessData(), L""));
			dataUJ->insert(kraj->getKey(), kraj->accessData());
		}
		for (TableItem<wstring, UzemnaJednotka*>* okres : *kraj->accessData()->vratNizsieUJ())
		{
			if (!obec)
			{
				data->insert(okres->getKey(), kriterium->getHodnotu(okres->accessData(), L""));
				dataUJ->insert(okres->getKey(), okres->accessData());
			}
			for (TableItem<wstring, UzemnaJednotka*>* obec : *okres->accessData()->vratNizsieUJ())
			{
				data->insert(obec->getKey(), kriterium->getHodnotu(obec->accessData(), L""));
				dataUJ->insert(obec->getKey(), obec->accessData());
			}
		}
	}
	if (!obec)
	{
		switch (cislo)
		{
		case 1:
			fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::obec, dataUJ, obec);
			break;
		case 2:
			fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::okres, dataUJ, obec);
			break;
		case 3:
			fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::kraj, dataUJ, obec);
			break;
		case 4:
			fujtyp->splnaFilter(slovensko, UzemnaJednotka::typUJ::štát, dataUJ, obec);
			break;
		default:
			break;
		}
		if (dataUJ->size() == 0)
		{
			wcout << L"ziadne data na vypis" << endl;
		}
		fujprislusnost->splnaFilter(slovensko, prislusnost, dataUJ, obec);
		prepisMedziPolami(dataUJ, data);
	}
	quickSort->sort(*data);
	for (TableItem<wstring, T>* item : *data)
	{
		wcout << item->getKey() << L" " << item->accessData() << endl;
	}
	delete data;
	data = nullptr;
	dataUJ = nullptr;
	delete quickSort;
	quickSort = nullptr;
	delete fujtyp;
	fujtyp = nullptr;
	delete fujprislusnost;
	fujprislusnost = nullptr;
}

template <typename T>
void prepisMedziPolami(UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData, UnsortedSequenceTable<wstring, T>* data)
{
	UnsortedSequenceTable<wstring, T>* deleteData = new UnsortedSequenceTable<wstring, T>();
	for (TableItem<wstring, T>* item : *data)
	{
		if (!finalData->containsKey(item->getKey()))
		{
			deleteData->insert(item->getKey(), item->accessData());
		}
	}
	for (TableItem<wstring, T>* item : *deleteData)
	{
		data->remove(item->getKey());
	}
	delete deleteData;
	deleteData = nullptr;
}

void menu()
{
	wcout << L"Vyber si operáciu:" << endl;
	wcout << L"1: Vypísanie informácií o obciach" << endl;
	wcout << L"2: Zoradenie obcí" << endl;
	wcout << L"3: Vypísanie informácií o územných jednotkách " << endl;
	wcout << L"4: Zoradenie územných jednotiek sĺňajúcich daný filter " << endl;
	wcout << L"0: Koniec / Exit" << endl << endl;

	do
	{
		wcout << L"Tvoj vyber: " << endl;
		wcin >> vyber;
	} while (vyber > 4 || vyber < 0);

	if (vyber == 0)
	{
		exit(0);
	}

	switch (vyber)
	{
	case 1:
		vyberFiltraVypis(true);
		break;
	case 2:
		zoradenieUJ(true);
		break;
	case 3:
		vyberFiltraVypis(false);
		break;
	case 4:
		zoradenieUJ(false);
		break;
	default:
		break;
	}

	wcout << L"Ak chcete v programe pokracovat stlacte 0: ";
	wcin >> vyber;
	if (vyber == 0)
	{
		menu();
	}
}