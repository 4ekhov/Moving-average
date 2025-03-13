#pragma once

#include <cstddef>

#pragma once

#include <cstddef>
#include <iterator>
#include <type_traits>
#include <stdexcept>

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