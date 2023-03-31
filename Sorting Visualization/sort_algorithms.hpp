#ifndef SORT_ALGORITHMS_HPP
#define SORT_ALGORITHMS_HPP

#include <vector>
#include <queue>
#include <iostream>

// Enum Event Tasks
const int _SWAP = 0;
const int _REPLACE = 1;

// Enum sort algorithms
const int _BUBBLE_SORT = 1;
const int _INSERTION_SORT = 2;
const int _MERGE_SORT = 3;

struct Event {
	int a;
	int b;
	int task;
};

// Events array
inline std::queue<Event> events_queue;

// Number array
inline std::vector<int> number_array;

inline int total_swaps = 0;

void run_bubble_sort(std::vector<int> num);
void run_bubble_sort(std::vector<int> num);
void run_insertion_sort(std::vector<int> num);
void merge(int array[], int const left, int const mid, int const right);
void run_merge_sort(int array[], int const begin, int const end);

#endif