#include "Input.h"
#include "structures/structure_iterator.h"

Input::Input()
{
}

Input::~Input()
{
}

void Input::nacitajUJ(UzemnaJednotka* stat, string nazovSuboru)
{
	subor.open(nazovSuboru);
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	setlocale(LC_ALL, "slovak");
	subor.imbue(locale("zh_CN.UTF-8"));

	wstring nazovObec;
	wstring nazovOkres;
	wstring nazovKraj;

	UzemnaJednotka* kraj = new UzemnaJednotka(nazovKraj, UzemnaJednotka::typUJ::kraj, nullptr);
	UzemnaJednotka* okres = new UzemnaJednotka(nazovOkres, UzemnaJednotka::typUJ::okres, nullptr);
	UzemnaJednotka* obec = new UzemnaJednotka(nazovObec, UzemnaJednotka::typUJ::obec, nullptr);

	getline(subor, nazovObec, L'\n');

	if (!subor.is_open())
		cout << "subor nie je otvoreny" << endl;


	while (getline(subor, nazovObec, L';'))
	{
		getline(subor, nazovOkres, L';');
		getline(subor, nazovKraj, L'\n');
		if (!stat->vratNizsieUJ()->containsKey(nazovKraj))
		{
			kraj = new UzemnaJednotka(nazovKraj, UzemnaJednotka::typUJ::kraj, stat);
			stat->nastavNizsiuUJ(nazovKraj, kraj);
		}
		else
		{
			kraj = (*stat->vratNizsieUJ())[nazovKraj];
		}

		if (!kraj->vratNizsieUJ()->containsKey(nazovOkres))
		{
			okres = new UzemnaJednotka(nazovOkres, UzemnaJednotka::typUJ::okres, kraj);
			kraj->nastavNizsiuUJ(nazovOkres, okres);
		}
		else
		{
			okres = (*kraj->vratNizsieUJ())[nazovOkres];
		}

		obec = new UzemnaJednotka(nazovObec, UzemnaJednotka::typUJ::obec, okres);
		okres->nastavNizsiuUJ(nazovObec, obec);
		
		//wcout << (*(*kraj->vratNizsieUJ())[nazovOkres]->vratNizsieUJ())[nazovObec]->getNazov() << L" " << (*kraj->vratNizsieUJ())[nazovOkres]->getNazov() << L" " << kraj->getNazov() << L" " << endl;
		kraj = nullptr;
		okres = nullptr;
		obec = nullptr;
	}

	
	subor.close();
	
}

void Input::nacitajObyvatelov(UzemnaJednotka* stat, string nazovSuboru)
{
	subor.open(nazovSuboru);
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	setlocale(LC_ALL, "slovak");
	subor.imbue(locale("zh_CN.UTF-8"));

	wstring nazovObec;

	wstring cislo;

	int predproduktivniObyvatelia = 0;
	int produktivniObyvatelia = 0;
	int poproduktivniObyvatelia = 0;
	double celkovaVymera = 0;
	double zastavanaPlocha = 0;
	getline(subor, nazovObec, L'\n');

	while (getline(subor, nazovObec, L';'))
	{
		getline(subor, cislo, L';');
		predproduktivniObyvatelia = stoi(cislo);
		getline(subor, cislo, L';');
		produktivniObyvatelia = stoi(cislo);
		getline(subor, cislo, L';');
		poproduktivniObyvatelia = stoi(cislo);
		getline(subor, cislo, L';');
		celkovaVymera = stod(cislo);
		getline(subor, cislo, L'\n');
		zastavanaPlocha = stod(cislo);
		boolean obecNajdena = false;
		for (TableItem<wstring, UzemnaJednotka*>* kraj : *stat->vratNizsieUJ())
		{
			for (TableItem<wstring, UzemnaJednotka*>* okres : *kraj->accessData()->vratNizsieUJ())
			{
				for (TableItem<wstring, UzemnaJednotka*>* obec : *okres->accessData()->vratNizsieUJ())
				{
					if (obec->accessData()->getNazov() == nazovObec)
					{
						obec->accessData()->nastavudajeUJ(predproduktivniObyvatelia, produktivniObyvatelia, poproduktivniObyvatelia, celkovaVymera, zastavanaPlocha);
						okres->accessData()->nastavudajeUJ(predproduktivniObyvatelia, produktivniObyvatelia, poproduktivniObyvatelia, celkovaVymera, zastavanaPlocha);
						kraj->accessData()->nastavudajeUJ(predproduktivniObyvatelia, produktivniObyvatelia, poproduktivniObyvatelia, celkovaVymera, zastavanaPlocha);
						stat->nastavudajeUJ(predproduktivniObyvatelia, produktivniObyvatelia, poproduktivniObyvatelia, celkovaVymera, zastavanaPlocha);
						obecNajdena = true;
					}
					if (obecNajdena)
						break;
				}
				if (obecNajdena)
					break;
			}
			if (obecNajdena)
				break;
		}
	}
	subor.close();
	/*for (TableItem<wstring, UzemnaJednotka*>* kraj : *stat->vratNizsieUJ())
	{
		for (TableItem<wstring, UzemnaJednotka*>* okres : *kraj->accessData()->vratNizsieUJ())
		{
			for (TableItem<wstring, UzemnaJednotka*>* obec : *okres->accessData()->vratNizsieUJ())
			{
				if (obec->accessData()->getNazov() == nazovObec)
				{
					obec->accessData()->nastavudajeUJ(predproduktivniObyvatelia, produktivniObyvatelia, poproduktivniObyvatelia, celkovaVymera, zastavanaPlocha);
					okres->accessData()->nastavudajeUJ(predproduktivniObyvatelia, produktivniObyvatelia, poproduktivniObyvatelia, celkovaVymera, zastavanaPlocha);
					kraj->accessData()->nastavudajeUJ(predproduktivniObyvatelia, produktivniObyvatelia, poproduktivniObyvatelia, celkovaVymera, zastavanaPlocha);
					
				}
				wcout << kraj->accessData()->getNazov() << " " << okres->accessData()->getNazov() << okres->accessData()->getPredproduktivnyObyvatelia() << " " << obec->accessData()->getNazov() << endl;
			}
		}
	}*/
}

