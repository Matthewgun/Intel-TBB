#include <tbb/tbb.h>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

double parallel_average(const std::vector<double>& nums) {
    double sum = tbb::parallel_reduce(
        tbb::blocked_range<size_t>(0, nums.size()),
        0.0,
        [&nums](const tbb::blocked_range<size_t>& r, double init) {
            for (size_t i = r.begin(); i != r.end(); ++i) {
                init += nums[i];
            }
            return init;
        },
        std::plus<double>()
    );
    return sum / nums.size();
}

double sequential_average(const std::vector<double>& nums) {
    double sum = 0.0;
    for (const auto& num : nums) {
        sum += num;
    }
    return sum / nums.size();
}

int main() {
    const size_t array_size = 10000000; // размер массива
    std::vector<double> data(array_size);

    // Генерация случайных положительных чисел
    std::random_device rd; // устройство для генерации случайных чисел
    std::mt19937 gen(rd()); // инициализация генератора
    std::uniform_real_distribution<> dis(1.0, 100.0); // распределение от 1.0 до 100.0

    for (size_t i = 0; i < array_size; ++i) {
        data[i] = dis(gen); // заполнение массива случайными числами
    }

    // Вычисление среднего значения с использованием TBB
    auto start_tbb = std::chrono::high_resolution_clock::now();
    double average_tbb = parallel_average(data);
    auto end_tbb = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_tbb = end_tbb - start_tbb;

    // Вычисление среднего значения обычным способом
    auto start_seq = std::chrono::high_resolution_clock::now();
    double average_seq = sequential_average(data);
    auto end_seq = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seq = end_seq - start_seq;

    // Вывод результатов
    std::cout << "Среднее значение (TBB): " << average_tbb 
              << ", время: " << elapsed_tbb.count() * 1000 << " миллисекунд" << std::endl;
    std::cout << "Среднее значение (обычный способ): " << average_seq 
              << ", время: " << elapsed_seq.count() * 1000 << " миллисекунд" << std::endl;

    return 0;
}
