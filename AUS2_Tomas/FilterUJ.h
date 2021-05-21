#pragma once
#include "Filter.h"

template <typename T>
class FilterUJ : public Filter<UzemnaJednotka*, T>
{
public:
	virtual bool splnaFilter(UzemnaJednotka* stat, T filterKriterium, UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData, bool vypisOsob) = 0;
};


class FilterUJNazov : public FilterUJ<wstring>
{
public:
	bool splnaFilter(UzemnaJednotka* stat, wstring filterKriterium, UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData, bool vypisOsob) override;
};

bool FilterUJNazov::splnaFilter(UzemnaJednotka* stat, wstring filterKriterium, UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData, bool vypisOsob)
{

	Kriterium<UzemnaJednotka*, wstring, wstring>* kriterium = new KriteriumUJNazov();

	if (kriterium->getHodnotu(stat, L"") == filterKriterium && !vypisOsob)
	{
		finalData->insert(stat->getNazov(), stat);
		return true;
	}
	for (TableItem<wstring, UzemnaJednotka*>* kraj : *stat->vratNizsieUJ())
	{
		if (kriterium->getHodnotu(kraj->accessData(), L"") == filterKriterium && !vypisOsob)
		{
			finalData->insert(kraj->getKey(), kraj->accessData());
			return true;
		}
		for (TableItem<wstring, UzemnaJednotka*>* okres : *kraj->accessData()->vratNizsieUJ())
		{
			if (kriterium->getHodnotu(okres->accessData(), L"") == filterKriterium && !vypisOsob)
			{
				finalData->insert(okres->getKey(), okres->accessData());
				return true;
			}
			for (TableItem<wstring, UzemnaJednotka*>* obec : *okres->accessData()->vratNizsieUJ())
			{
				if (kriterium->getHodnotu(obec->accessData(), L"") == filterKriterium)
				{
					finalData->insert(obec->getKey(), obec->accessData());
					return true;
				}
			}
		}
	}
	delete kriterium;
	kriterium = nullptr;
	return false;
}

class FilterUJPocetObyvatelov : public FilterUJ<int>
{
public:
	bool splnaFilter(UzemnaJednotka*, int filterKriterium, UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData, bool vypisOsob) override;
};

bool FilterUJPocetObyvatelov::splnaFilter(UzemnaJednotka* stat, int filterKriterium, UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData, bool vypisOsob)
{
	Kriterium<UzemnaJednotka*, int, wstring>* KPocObyvatelov = new KriteriumUJPocetObyvatelov();
	bool vypis = false;
	if (KPocObyvatelov->getHodnotu(stat, L"") >= filterKriterium && !vypisOsob)
	{
		finalData->insert(stat->getNazov(), stat);
		vypis = true;
	}
	for (TableItem<wstring, UzemnaJednotka*>* kraj : *stat->vratNizsieUJ())
	{
		if (KPocObyvatelov->getHodnotu(kraj->accessData(), L"") >= filterKriterium && !vypisOsob)
		{
			finalData->insert(kraj->getKey(), kraj->accessData());
			vypis = true;
		}
		for (TableItem<wstring, UzemnaJednotka*>* okres : *kraj->accessData()->vratNizsieUJ())
		{
			if (KPocObyvatelov->getHodnotu(okres->accessData(), L"") >= filterKriterium && !vypisOsob)
			{
				finalData->insert(okres->getKey(), okres->accessData());
				vypis = true;
			}
			for (TableItem<wstring, UzemnaJednotka*>* obec : *okres->accessData()->vratNizsieUJ())
			{
				if (KPocObyvatelov->getHodnotu(obec->accessData(), L"") >= filterKriterium)
				{
					finalData->insert(obec->getKey(), obec->accessData());
					vypis = true;
				}
			}
		}
	}
	delete KPocObyvatelov;
	KPocObyvatelov = nullptr;
	return vypis;
}

class FilterUJZastavanost : public FilterUJ<double>
{
public:
	bool splnaFilter(UzemnaJednotka*, double filterKriterium, UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData, bool vypisOsob) override;
};

bool FilterUJZastavanost::splnaFilter(UzemnaJednotka* stat, double filterKriterium, UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData, bool vypisOsob)
{
	Kriterium<UzemnaJednotka*, double, wstring>* Kzastavanost = new KriteriumUJZastavanost();
	bool vypis = false;
	if (Kzastavanost->getHodnotu(stat, L"") >= filterKriterium && !vypisOsob)
	{
		finalData->insert(stat->getNazov(), stat);
		vypis = true;
	}
	for (TableItem<wstring, UzemnaJednotka*>* kraj : *stat->vratNizsieUJ())
	{
		if (Kzastavanost->getHodnotu(kraj->accessData(), L"") >= filterKriterium && !vypisOsob)
		{
			finalData->insert(kraj->getKey(), kraj->accessData());
			vypis = true;
		}
		for (TableItem<wstring, UzemnaJednotka*>* okres : *kraj->accessData()->vratNizsieUJ())
		{
			if (Kzastavanost->getHodnotu(okres->accessData(), L"") >= filterKriterium && !vypisOsob)
			{
				finalData->insert(okres->getKey(), okres->accessData());
				vypis = true;
			}
			for (TableItem<wstring, UzemnaJednotka*>* obec : *okres->accessData()->vratNizsieUJ())
			{
				if (Kzastavanost->getHodnotu(obec->accessData(), L"") >= filterKriterium)
				{
					finalData->insert(obec->getKey(), obec->accessData());
					vypis = true;
				}
			}
		}
	}
	delete Kzastavanost;
	Kzastavanost = nullptr;
	return vypis;
}

class FilterUJTyp : public FilterUJ<UzemnaJednotka::typUJ>
{
public:
	bool splnaFilter(UzemnaJednotka*, UzemnaJednotka::typUJ filterKriterium, UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData, bool vypisOsob) override;
};

bool FilterUJTyp::splnaFilter(UzemnaJednotka* stat, UzemnaJednotka::typUJ filterKriterium, UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData, bool vypisOsob)
{
	Kriterium<UzemnaJednotka*, UzemnaJednotka::typUJ, wstring>* Ktyp = new KriteriumUJTyp();
	UnsortedSequenceTable<wstring, UzemnaJednotka*>* deleteData = new UnsortedSequenceTable<wstring, UzemnaJednotka*>();
	for (TableItem<wstring, UzemnaJednotka*>* item : *finalData)
	{
		if (Ktyp->getHodnotu(item->accessData(), L"") != filterKriterium)
		{
			deleteData->insert(item->getKey(), item->accessData());
		}
	}
	for (TableItem<wstring, UzemnaJednotka*>* item : *deleteData)
	{
			finalData->remove(item->getKey());
	}
	delete Ktyp;
	Ktyp = nullptr;
	delete deleteData;
	deleteData = nullptr;
	return true;
}

class FilterUJPrislusnost : public FilterUJ<wstring>
{
public:
	bool splnaFilter(UzemnaJednotka*, wstring filterKriterium, UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData, bool vypisOsob) override;
};

bool FilterUJPrislusnost::splnaFilter(UzemnaJednotka* stat, wstring filterKriterium, UnsortedSequenceTable<wstring, UzemnaJednotka*>* finalData, bool vypisOsob)
{
	Kriterium<UzemnaJednotka*, bool, wstring>* Kpripustnost = new KriteriumUJPrislusnost();
	UnsortedSequenceTable<wstring, UzemnaJednotka*>* deleteData = new UnsortedSequenceTable<wstring, UzemnaJednotka*>();
	for (TableItem<wstring, UzemnaJednotka*>* item : *finalData)
	{
		if (!Kpripustnost->getHodnotu(item->accessData(), filterKriterium))
		{
			deleteData->insert(item->getKey(), item->accessData());
		}
	}
	for (TableItem<wstring, UzemnaJednotka*>* item : *deleteData)
	{
		finalData->remove(item->getKey());
	}
	delete Kpripustnost;
	Kpripustnost = nullptr;
	delete deleteData;
	deleteData = nullptr;
	return true;
}