// Copyright 2022 NNTU-CS
#include "train.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

Train* CreateTrain(int n, const std::vector<bool>& light_states) {
    Train* train = new Train();
    for (int i = 0; i < n; ++i) {
        train->addCar(light_states[i]);
    }
    return train;
}

std::vector<std::pair<int, int>> RunExperiment(
    const std::vector<int>& lengths,
    const std::string& type,
    std::mt19937& rng) {
    std::vector<std::pair<int, int>> results;
    std::uniform_int_distribution<> dist(0, 1);
    const int kNumTests = 10;

    for (int n : lengths) {
        long long total_ops = 0;

        for (int test = 0; test < kNumTests; ++test) {
            std::vector<bool> states(n);

            if (type == "all_off") {
                std::fill(states.begin(), states.end(), false);
            } else if (type == "all_on") {
                std::fill(states.begin(), states.end(), true);
            } else {
                for (int i = 0; i < n; ++i) {
                    states[i] = dist(rng);
                }
            }

            Train* train = CreateTrain(n, states);
            int ops = train->getLength();
            total_ops += ops;
            delete train;
        }

        int avg_ops = total_ops / kNumTests;
        results.push_back({n, avg_ops});

        std::cout << "n=" << n << ", " << type << ", avg ops=" << avg_ops
                  << std::endl;
    }

    return results;
}

int main() {
    std::cout << "=== Вычислительный эксперимент ===\n\n";

    std::vector<int> lengths;
    for (int n = 2; n <= 100; n += 2) {
        lengths.push_back(n);
    }

    std::mt19937 rng(
        static_cast<unsigned>(
            std::chrono::steady_clock::now().time_since_epoch().count()));

    std::cout << "Эксперимент 1: Все лампочки выключены\n";
    std::vector<std::pair<int, int>> results_off =
        RunExperiment(lengths, "all_off", rng);

    std::cout << "\nЭксперимент 2: Все лампочки включены\n";
    std::vector<std::pair<int, int>> results_on =
        RunExperiment(lengths, "all_on", rng);

    std::cout << "\nЭксперимент 3: Случайное распределение\n";
    std::vector<std::pair<int, int>> results_rand =
        RunExperiment(lengths, "random", rng);

    std::ofstream out_file("result/data.csv");
    out_file << "n,all_off,all_on,random\n";
    for (size_t i = 0; i < results_off.size(); ++i) {
        out_file << results_off[i].first << ","
                 << results_off[i].second << ","
                 << results_on[i].second << ","
                 << results_rand[i].second << "\n";
    }
    out_file.close();

    std::cout << "\nРезультаты сохранены в result/data.csv\n";

    return 0;
}
