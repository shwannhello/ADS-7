// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "train.h"

Train createTrain(int length, const std::string& pattern) {
    Train train;
    
    if (pattern == "all_off") {
        for (int i = 0; i < length; i++) {
            train.addCar(false);
        }
    } else if (pattern == "all_on") {
        for (int i = 0; i < length; i++) {
            train.addCar(true);
        }
    } else if (pattern == "random") {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);
        
        for (int i = 0; i < length; i++) {
            train.addCar(dis(gen) == 1);
        }
    }
    
    return train;
}

int main() {
    std::vector<int> lengths;
    for (int n = 2; n <= 200; n += 2) {
        lengths.push_back(n);
    }
    
    std::vector<std::pair<int, double>> results_all_off;
    std::vector<std::pair<int, double>> results_all_on;
    std::vector<std::pair<int, double>> results_random;
    
    for (int n : lengths) {
        Train train = createTrain(n, "all_off");
        int ops = train.getLength();
        results_all_off.push_back({n, (double)ops});
    }
    
    for (int n : lengths) {
        Train train = createTrain(n, "all_on");
        int ops = train.getLength();
        results_all_on.push_back({n, (double)ops});
    }
    
    for (int n : lengths) {
        double avgOps = 0;
        const int iterations = 10;
        
        for (int iter = 0; iter < iterations; iter++) {
            Train train = createTrain(n, "random");
            avgOps += train.getLength();
        }
        avgOps /= iterations;
        
        results_random.push_back({n, avgOps});
    }
    
    std::ofstream outFile("result/data.csv");
    outFile << "n,all_off,all_on,random" << std::endl;
    
    for (size_t i = 0; i < lengths.size(); i++) {
        outFile << lengths[i] << ","
                << results_all_off[i].second << ","
                << results_all_on[i].second << ","
                << results_random[i].second << std::endl;
    }
    outFile.close();
    
    return 0;
}
