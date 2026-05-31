// Copyright 2022 NNTU-CS
#include "train.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <cmath>

Train* createTrain(int n, const std::vector<bool>& lightStates) {
    Train* train = new Train();
    for (int i = 0; i < n; i++) {
        train->addCar(lightStates[i]);
    }
    return train;
}

std::vector<std::pair<int, int>> runExperiment(
    const std::vector<int>& lengths,
    const std::string& type,
    std::mt19937& rng) {
    
    std::vector<std::pair<int, int>> results;
    std::uniform_int_distribution<> dist(0, 1);
    
    for (int n : lengths) {
        long long totalOps = 0;
        const int NUM_TESTS = 10;
        
        for (int test = 0; test < NUM_TESTS; test++) {
            std::vector<bool> states(n);
            
            if (type == "all_off") {
                for (int i = 0; i < n; i++) states[i] = false;
            } 
            else if (type == "all_on") {
                for (int i = 0; i < n; i++) states[i] = true;
            }
            else {
                for (int i = 0; i < n; i++) states[i] = dist(rng);
            }
            
            Train* train = createTrain(n, states);
            int ops = train->getLength();
            totalOps += ops;
            delete train;
        }
        
        int avgOps = totalOps / NUM_TESTS;
        results.push_back({n, avgOps});
        
        std::cout << "n=" << n << ", " << type << ", avg ops=" << avgOps << std::endl;
    }
    
    return results;
}

int main() {
    std::cout << "=== Вычислительный эксперимент ===\n\n";
    
    std::vector<int> lengths;
    for (int n = 2; n <= 100; n += 2) {
        lengths.push_back(n);
    }
    
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    
    std::cout << "Эксперимент 1: Все лампочки выключены\n";
    auto resultsOff = runExperiment(lengths, "all_off", rng);
    
    std::cout << "\nЭксперимент 2: Все лампочки включены\n";
    auto resultsOn = runExperiment(lengths, "all_on", rng);
    
    std::cout << "\nЭксперимент 3: Случайное распределение\n";
    auto resultsRand = runExperiment(lengths, "random", rng);
    
    std::ofstream outFile("result/data.csv");
    outFile << "n,all_off,all_on,random\n";
    for (size_t i = 0; i < resultsOff.size(); i++) {
        outFile << resultsOff[i].first << ","
                << resultsOff[i].second << ","
                << resultsOn[i].second << ","
                << resultsRand[i].second << "\n";
    }
    outFile.close();
    
    std::cout << "\nРезультаты сохранены в result/data.csv\n";
    
    return 0;
}
