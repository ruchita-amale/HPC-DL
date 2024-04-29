#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace chrono;

// Sequential implementation of Min, Max, Sum, and Average
void sequentialOperations(vector<int>& data, int& minVal, int& maxVal, int& sum, double& average) {
    minVal = data[0];
    maxVal = data[0];
    sum = data[0];
    for (int i = 1; i < data.size(); ++i) {
        if (data[i] < minVal) minVal = data[i];
        if (data[i] > maxVal) maxVal = data[i];
        sum += data[i];
    }
    average = static_cast<double>(sum) / data.size();
}

// Parallel implementation of Min, Max, Sum, and Average using OpenMP reduction\
void parallelOperations(const vector<int>& data, int& minVal, int& maxVal, int& sum, double& average) {
    minVal = data[0];
    maxVal = data[0];
    sum = data[0];
    #pragma omp parallel for reduction(min:minVal) reduction(max:maxVal) reduction(+:sum)
    for (int i = 1; i < data.size(); ++i) {
        if (data[i] < minVal) minVal = data[i];
        if (data[i] > maxVal) maxVal = data[i];
        sum += data[i];
    }
    average = static_cast<double>(sum) / data.size();
}

int main() {
    // Generate some random data
    int size = 10000000;
    vector<int> data(size);
    for (int i = 0; i < size; ++i) {
        data[i] = rand() % 1000;
    }

    // Sequential operations
    int minValSeq, maxValSeq, sumSeq;
    double averageSeq;
    auto startSeq = high_resolution_clock::now();
    sequentialOperations(data, minValSeq, maxValSeq, sumSeq, averageSeq);
    auto stopSeq = high_resolution_clock::now();
    auto durationSeq = duration_cast<milliseconds>(stopSeq - startSeq);

    // Parallel operations
    int minValPar, maxValPar, sumPar;
    double averagePar;
    auto startPar = high_resolution_clock::now();
    parallelOperations(data, minValPar, maxValPar, sumPar, averagePar);
    auto stopPar = high_resolution_clock::now();
    auto durationPar = duration_cast<milliseconds>(stopPar - startPar);

    // Output results
    cout << "Sequential Min: " << minValSeq << endl;
    cout << "Sequential Max: " << maxValSeq << endl;
    cout << "Sequential Sum: " << sumSeq << endl;
    cout << "Sequential Average: " << averageSeq << endl;
    cout << "Sequential Execution Time: " << durationSeq.count() << " milliseconds" << endl;

    cout << "\nParallel Min: " << minValPar << endl;
    cout << "Parallel Max: " << maxValPar << endl;
    cout << "Parallel Sum: " << sumPar << endl;
    cout << "Parallel Average: " << averagePar << endl;
    cout << "Parallel Execution Time: " << durationPar.count() << " milliseconds" << endl;

    return 0;
}
