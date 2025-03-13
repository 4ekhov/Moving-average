#include "MovingAverage.h"

#include <vector>
#include <iostream>

int main() {
    std::vector<double> input_data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::vector<double> output_data;

    size_t window_size = 3;
    output_data.resize(input_data.size() - window_size + 1);

    simple_moving_average(input_data.begin(), input_data.end(), output_data.begin(), window_size);

    std::cout << "Простое скользящее среднее (размер окна = " << window_size << "):" << std::endl;
    for (const auto& value : output_data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}