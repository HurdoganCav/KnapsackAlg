#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void traceItems(const vector<int>& weights, const vector<int>& values, const vector<vector<int>>& dp, int W) {
    cout << "Items included in the knapsack to achieve maximum value:" << endl;
    int w = W;
    int n = weights.size();
    int totalValue = 0;  // Variable to store total value of included items
    int totalWeight = 0;  // Variable to store total weight of included items

    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << "Item " << i << " (Value: " << values[i - 1] << ", Weight: " << weights[i - 1] << ")" << endl;
            totalValue += values[i - 1];
            totalWeight += weights[i - 1];
            w -= weights[i - 1];
        }
    }

    cout << "Total value of the selected items: " << totalValue << endl;
    cout << "Total weight of the selected items: " << totalWeight << endl;
}

vector<vector<int>> knapsack(int W, const vector<int>& weights, const vector<int>& values) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp;
}

void processDataset(const string& filename) {
    int n, W;
    vector<int> weights, values;

    ifstream file(filename);

    if (!file) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    file >> n >> W;

    int value, weight;
    while (file >> value >> weight) {
        values.push_back(value);
        weights.push_back(weight);
    }

    file.close();

    vector<vector<int>> dp = knapsack(W, weights, values);
    cout << "Processing file: " << filename << endl;
    cout << "Maximum value that can be achieved within the weight limit is: " << dp[n][W] << endl;

    traceItems(weights, values, dp, W);
    cout << "----------------------------------------------------" << endl;
}

int main() {
    vector<string> filenames = {"ks_19_0.txt", "ks_50_0.txt", "ks_100_2.txt", "ks_500_0.txt", "ks_10000_0.txt"};

    for (const string& filename : filenames) {
        processDataset(filename);
    }

    return 0;
}
