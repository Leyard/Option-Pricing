#pragma once
#include <vector>

double mean(std::vector<double>& dataset);
double variance(std::vector<double>& dataset);
double covariance(std::vector<double>& dataset1, std::vector<double>& dataset2);
double correlation(std::vector<double>& dataset1, std::vector<double>& dataset2);

// template <typename T>
// T mean(std::vector<T>& dataset) {
//     return std::accumulate(dataset.begin(), dataset.end(), (T) 0) / dataset.size();
// }

template <typename T>
T max(T a, T b) {
    return 0.5*abs(a-b) - 0.5*(a-b);
}

template <typename T>
T min(T a, T b) {
    return 0.5*abs(a-b) + 0.5*(a-b);
}

