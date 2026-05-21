// Copyright 2022 NNTU-CS
#include "../include/train.h"
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <fstream>

using namespace std;

vector<pair<int, double>> runExperiment(
    const vector<int>& lengths,
    const string& distribution,
    int experimentsPerLength = 10) {
    
    vector<pair<int, double>> results;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);

    cout << "\n--- Распределение: " << distribution << " ---\n";
    
    for (int n : lengths) {
        long long totalOps = 0;
        int successfulTests = 0;

        for (int exp = 0; exp < experimentsPerLength; ++exp) {
            Train train;

            for (int i = 0; i < n; ++i) {
                bool lightState;
                if (distribution == "all_off") {
                    lightState = false;
                } else if (distribution == "all_on") {
                    lightState = true;
                } else {  // random
                    lightState = dis(gen);
                }
                train.addCar(lightState);
            }

            int length = train.getLength();
            int ops = train.getOpCount();
            
            if (length == n) {
                totalOps += ops;
                successfulTests++;
            } else {
                cerr << "  Предупреждение: для n=" << n 
                     << ", получено length=" << length << endl;
            }
        }

        double avgOps = (successfulTests > 0) ? 
                        static_cast<double>(totalOps) / successfulTests : 0;
        results.push_back({n, avgOps});
        
        cout << "  n=" << setw(3) << n 
             << " | среднее операций: " << setw(8) << fixed << setprecision(1) << avgOps
             << " | успешно: " << successfulTests << "/" << experimentsPerLength << endl;
    }
    
    return results;
}

void saveToCSV(const vector<pair<int, double>>& allOff,
               const vector<pair<int, double>>& allOn,
               const vector<pair<int, double>>& randomDist) {
    ofstream file("result/experiment_data.csv");
    
    file << "n,all_off,all_on,random\n";
    
    for (size_t i = 0; i < allOff.size(); ++i) {
        file << allOff[i].first << ","
             << allOff[i].second << ","
             << allOn[i].second << ","
             << randomDist[i].second << "\n";
    }
    
    file.close();
    cout << "\nДанные сохранены в result/experiment_data.csv\n";
}

void printSummary(const vector<pair<int, double>>& allOff,
                  const vector<pair<int, double>>& allOn,
                  const vector<pair<int, double>>& randomDist) {
    cout << "\n\n";
    cout << "================== СВОДНАЯ ТАБЛИЦА ==================\n";
    cout << "   n   |  все выкл.  |  все вкл.  |  случайные  |\n";
    cout << "-------+------------+------------+-------------+\n";
    
    for (size_t i = 0; i < allOff.size(); ++i) {
        if (i % 5 == 0 || i == allOff.size() - 1) {
            cout << "  " << setw(3) << allOff[i].first << "  |"
                 << "  " << setw(8) << fixed << setprecision(1) << allOff[i].second << "   |"
                 << "  " << setw(8) << fixed << setprecision(1) << allOn[i].second << "   |"
                 << "  " << setw(9) << fixed << setprecision(1) << randomDist[i].second << "   |\n";
        }
    }
}

int main() {
    cout << "   ВЫЧИСЛИТЕЛЬНЫЙ ЭКСПЕРИМЕНТ\n";
    cout << "   Подсчёт вагонов в кольцевом поезде\n";

    vector<int> lengths;
    for (int n = 2; n <= 50; ++n) {
        lengths.push_back(n);
    }

    int experimentsPerLength = 20;
    
    cout << "\nПараметры эксперимента:\n";
    cout << "  - Диапазон длин поездов: от 2 до " << lengths.back() << "\n";
    cout << "  - Экспериментов на каждую длину: " << experimentsPerLength << "\n";
    cout << "  - Всего экспериментов: " << lengths.size() * experimentsPerLength * 3 << "\n\n";
    
    cout << "Начинаем эксперимент...\n";
    
    auto allOff = runExperiment(lengths, "all_off", experimentsPerLength);
    auto allOn = runExperiment(lengths, "all_on", experimentsPerLength);
    auto randomDist = runExperiment(lengths, "random", experimentsPerLength);
    
    saveToCSV(allOff, allOn, randomDist);
    
    printSummary(allOff, allOn, randomDist);
    
    cout << "\n Эксперимент успешно завершён \n";
    cout << "\nДля построения графика импортируйте файл result/experiment_data.csv\n";
    cout << "в Excel, Google Sheets или любой другой инструмент для визуализации.\n";
    
    return 0;
}
