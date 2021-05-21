#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

#include <functional>

namespace structures
{

	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class QuickSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table, std::function<bool(T, T)> myOperator) override;

        int partition(UnsortedSequenceTable<K, T>& table, int low, int high, std::function<bool(T, T)> myOperator);
        void quickSort(UnsortedSequenceTable<K, T>& table, int low, int high, std::function<bool(T, T)> myOperator);
 };


    template <typename K, typename T>
	inline void QuickSort<K, T>::sort(UnsortedSequenceTable<K, T>& table, std::function<bool(T, T)> myOperator)
	{
        quickSort(table, 0, (table.size() - 1), myOperator);
	}

    template <typename K, typename T>
    inline int QuickSort<K, T>::partition(UnsortedSequenceTable<K, T>& table, int low, int high, std::function<bool(T, T)> myOperator)
    {
        T pivot = table.getItemAtIndex(high).accessData();
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (myOperator((table.getItemAtIndex(j).accessData()), pivot)) {
                i++;
                table.swap(i, j);
            }
        }
        table.swap((i + 1), high);
        return i + 1;
    }

    template <typename K, typename T>
    inline void QuickSort<K, T>::quickSort(UnsortedSequenceTable<K, T>& table, int low, int high, std::function<bool(T, T)> myOperator)
    {
        if (low < high) {
            int pivotIndex = partition(table, low, high, myOperator);
            quickSort(table, low, (pivotIndex - 1), myOperator);
            quickSort(table, (pivotIndex + 1), high, myOperator);
        }
    }
}