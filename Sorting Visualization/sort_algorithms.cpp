#include "sort_algorithms.hpp"

void run_bubble_sort(std::vector<int> num) {
	for (int i = 0; i < num.size(); i++) {
		for (int p = i + 1; p < num.size(); p++) {
			// Swap numbers
			if (num[i] > num[p]) {
				int temp = num[i];
				num[i] = num[p];
				num[p] = temp;

				events_queue.push(Event{ i, p, _SWAP });
				total_swaps++;
			}
		}
	}
}

void run_insertion_sort(std::vector<int> num) {
	int key, j;

	for (int i = 1; i < num.size(); i++) {
		key = num[i];
		j = i - 1;

		while (j >= 0 && num[j] > key)
		{
			num[j + 1] = num[j];
			events_queue.push(Event{ j + 1, num[j], _REPLACE });
			total_swaps++;

			j = j - 1;
		}

		num[j + 1] = key;
		events_queue.push(Event{ j + 1, key, _REPLACE });
		total_swaps++;
	}
}

void merge(int array[], int const left, int const mid, int const right) {
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	auto* leftArray = new int[subArrayOne], * rightArray = new int[subArrayTwo];

	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];

	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0,
		indexOfSubArrayTwo = 0;
	int indexOfMergedArray = left;

	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			events_queue.push(Event{ indexOfMergedArray, leftArray[indexOfSubArrayOne], _REPLACE });
			total_swaps++;

			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			events_queue.push(Event{ indexOfMergedArray, rightArray[indexOfSubArrayTwo], _REPLACE });
			total_swaps++;

			indexOfSubArrayTwo++;
		}

		indexOfMergedArray++;
	}

	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		events_queue.push(Event{ indexOfMergedArray, leftArray[indexOfSubArrayOne], _REPLACE });
		total_swaps++;

		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}

	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		events_queue.push(Event{ indexOfMergedArray, rightArray[indexOfSubArrayTwo], _REPLACE });
		total_swaps++;

		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}

	delete[] leftArray;
	delete[] rightArray;
}

void run_merge_sort(int array[], int const begin, int const end) {
	if (begin >= end)
		return;

	auto mid = begin + (end - begin) / 2;
	run_merge_sort(array, begin, mid);
	run_merge_sort(array, mid + 1, end);
	merge(array, begin, mid, end);
}