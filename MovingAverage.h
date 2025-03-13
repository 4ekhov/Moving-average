#pragma once

#include <cstddef>

template<typename InputIt, typename OutputIt>
void simple_moving_average(InputIt first, InputIt last, OutputIt d_first, size_t window_size);