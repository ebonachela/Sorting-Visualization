#include <SFML/Graphics.hpp>
#include "sort_algorithms.hpp"
#include <functional>
#include <random>

int last_swap_i = 0, last_swap_p = 0;
int swap_counts_num = 0;

const sf::Time wait_between_swaps = sf::milliseconds(10);
const int max_rec_size = 650;
const int rec_y_pos = 720;
const int sort_algorithm = _QUICK_SORT;

void handle_events() {
	if (events_queue.size() > 0) {
		Event e = events_queue.front();
		events_queue.pop();

		int i = e.a;
		int p = e.b;
		int task = e.task;

		if (task == _SWAP) {
			if (i >= number_array.size() || p >= number_array.size() || i < 0 || p < 0) return;

			int temp = number_array[i];
			number_array[i] = number_array[p];
			number_array[p] = temp;

			last_swap_i = i;
			last_swap_p = p;
		}
		else if (task == _REPLACE) {
			if (i >= number_array.size() || i < 0) return;

			number_array[i] = p;

			last_swap_i = i;
			last_swap_p = -1;
		}

		swap_counts_num++;

		sf::sleep(wait_between_swaps);
	}

	if (total_swaps == swap_counts_num) {
		last_swap_i = -1;
		last_swap_p = -1;
	}
}

void draw_number_rectangles(sf::RenderWindow &window) {
	int n = number_array.size();

	for (int i = 0; i < n; i++) {
		sf::RectangleShape rec(sf::Vector2f(10, max_rec_size));
		rec.setPosition(sf::Vector2f(i * 15, rec_y_pos));
		rec.setSize(sf::Vector2f(10, -max_rec_size * number_array[i] * 1.0 / n));

		if (i == last_swap_i || i == last_swap_p) rec.setFillColor(sf::Color::Red);
		window.draw(rec);
	}
}

int main()
{
	// Sorting logic
	int n = 85;
	int index_row = 0, index_column = 0;

	for (int i = 0; i < n; i++) {
		number_array.push_back(i + 1);
	}

	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(number_array), std::end(number_array), rng);

	// SFML
	int tick = 0;
	int max_tick = 25;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Sorting Visualization");

	// Text
	sf::Font open_sans;
	open_sans.loadFromFile("C:\\Users\\elite\\Downloads\\Poppins\\Poppins-Medium.ttf");

	sf::Text swap_count;
	swap_count.setString("Swaps: 0");
	swap_count.setPosition(0, 0);
	swap_count.setFillColor(sf::Color::White);
	swap_count.setFont(open_sans);
	swap_count.setScale(sf::Vector2f(0.5, 0.5));

	sf::Event event;

	if (sort_algorithm == _BUBBLE_SORT) {
		sf::Thread thread(&run_bubble_sort, number_array);
		thread.launch();
	}
	else if (sort_algorithm == _INSERTION_SORT) {
		sf::Thread thread(&run_insertion_sort, number_array);
		thread.launch();
	}
	else if (sort_algorithm == _MERGE_SORT) {
		int* arr = new int[n];
		std::copy(number_array.begin(), number_array.end(), arr);

		sf::Thread thread(std::bind(&run_merge_sort, arr, 0, n - 1));
		thread.launch();
	}
	else if (sort_algorithm == _QUICK_SORT) {
		int* arr = new int[n];
		std::copy(number_array.begin(), number_array.end(), arr);

		sf::Thread thread(std::bind(&run_quick_sort, arr, 0, n - 1));
		thread.launch();
	}

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}
		}

		window.clear();

		handle_events();

		draw_number_rectangles(window);

		swap_count.setString("Swaps: " + std::to_string(swap_counts_num));

		window.draw(swap_count);

		window.display();
	}

	return 0;
}