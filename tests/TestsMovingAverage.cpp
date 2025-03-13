#include "../MovingAverage.h"

#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>
#include <iomanip>

double random_double(double min, double max) {
    double random = static_cast<double>(rand()) / RAND_MAX;
    return min + random * (max - min);
}

std::vector<double> generate_random_data(size_t size, double min, double max) {
    std::vector<double> data(size);
    for (auto& value : data) {
        value = random_double(min, max);
    }
    return data;
}

TEST(MovingAverageTest, CorrectnessTest) {
    std::vector<double> input_data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::vector<double> output_data;
    size_t window_size = 3;
    output_data.resize(input_data.size() - window_size + 1);

    simple_moving_average(input_data.begin(), input_data.end(), output_data.begin(), window_size);

    std::vector<double> expected_output = {2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    ASSERT_EQ(output_data, expected_output);
}

TEST(MovingAverageTest, PerformanceTest) {
    srand(static_cast<unsigned int>(time(0)));

    double min_value = std::numeric_limits<double>::lowest();
    double max_value = std::numeric_limits<double>::max();
    std::vector<double> input_data = generate_random_data(1000000, min_value, max_value);

    std::vector<size_t> window_sizes = {4, 8, 16, 32, 64, 128};
    for (auto window_size : window_sizes) {
        std::vector<double> output_data(input_data.size() - window_size + 1);

        auto start = std::chrono::high_resolution_clock::now();
        simple_moving_average(input_data.begin(), input_data.end(), output_data.begin(), window_size);
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        double samples_per_second = static_cast<double>(input_data.size()) / (duration / 1000.0);

        // Вывод данных в фиксированном формате без экспоненциальной записи
        std::cout << "Размер окна: " << window_size << ", Отсчет/сек: "
                  << std::fixed << std::setprecision(0) << samples_per_second << std::endl;
    }
}

TEST(MovingAverageTest, AveragePerformanceTest) {
    srand(static_cast<unsigned int>(time(0)));

    double min_value = std::numeric_limits<double>::lowest();
    double max_value = std::numeric_limits<double>::max();
    std::vector<double> input_data = generate_random_data(1000000, min_value, max_value);

    std::vector<size_t> window_sizes = {4, 8, 16, 32, 64, 128};

    const size_t num_runs = 1000;

    std::vector<std::vector<double>> results(window_sizes.size());

    for (size_t i = 0; i < window_sizes.size(); ++i) {
        size_t window_size = window_sizes[i];
        results[i].resize(num_runs);

        for (size_t run = 0; run < num_runs; ++run) {
            std::vector<double> output_data(input_data.size() - window_size + 1);

            auto start = std::chrono::high_resolution_clock::now();
            simple_moving_average(input_data.begin(), input_data.end(), output_data.begin(), window_size);
            auto end = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            double samples_per_second = static_cast<double>(input_data.size()) / (duration / 1e9);

            results[i][run] = samples_per_second;
        }
    }

    for (size_t i = 0; i < window_sizes.size(); ++i) {
        size_t window_size = window_sizes[i];

        double sum = 0.0;
        for (const auto& value : results[i]) {
            sum += value;
        }
        double average = sum / num_runs;

        std::cout << "Размер окна: " << window_size << ", Среднее отсчет/сек: "
                  << std::fixed << std::setprecision(0) << average << std::endl;
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}