#include "MovingAverage.h"

#include <iostream>
#include <vector>

template<typename InputIt, typename OutputIt>
void simple_moving_average(InputIt first, InputIt last, OutputIt d_first, size_t window_size) {
    using InputValueType = typename std::iterator_traits<InputIt>::value_type;
    using ResultType = typename std::iterator_traits<OutputIt>::value_type;

    static_assert(std::is_same_v<InputValueType, float> || std::is_same_v<InputValueType, double>,
                  "Входной итератор должен указывать на float или double");

    static_assert(std::is_same_v<ResultType, float> || std::is_same_v<ResultType, double>,
                  "Выходной итератор должен указывать на float или double");

    auto input_size = std::distance(first, last);
    if (input_size == 0) {
        throw std::invalid_argument("Входные данные пусты");
    }

    if (window_size == 0 || window_size > static_cast<size_t>(input_size)) {
        throw std::invalid_argument("Некорректный размер окна");
    }

    double sum = 0.0;

    InputIt window_end = first;
    for (size_t i = 0; i < window_size; ++i, ++window_end) {
        sum += static_cast<double>(*window_end);
    }

    *d_first++ = static_cast<ResultType>(sum / window_size);

    while (window_end != last) {
        sum += static_cast<double>(*window_end) - static_cast<double>(*first++);
        *d_first++ = static_cast<ResultType>(sum / window_size);
        ++window_end;
    }
}

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