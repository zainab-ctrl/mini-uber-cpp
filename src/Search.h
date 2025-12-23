#pragma once
#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>
#include <chrono>
using namespace std;

class Search {
public:
    // ---------------- LINEAR SEARCH ----------------
    template <typename T>
    static int linearSearch(const vector<T>& arr,
                            const string& key,
                            function<string(const T&)> getId) {
        for (int i = 0; i < arr.size(); i++) {
            if (getId(arr[i]) == key)
                return i;  // Returns index in same vector
        }
        return -1;
    }

    // ---------------- BINARY SEARCH ----------------
    // Works on vector sorted by numeric part of ID
    template <typename T>
    static int binarySearch(const vector<T>& arr,
                            const string& key,
                            function<string(const T&)> getId) {
        int target = stoi(key.substr(1));  // numeric part
        int low = 0, high = arr.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int midVal = stoi(getId(arr[mid]).substr(1));

            if (midVal == target)
                return mid;
            else if (midVal < target)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return -1;
    }

    // ---------------- SEARCH + TIME COMPARISON ----------------
    template <typename T>
    static void searchCompare(vector<T>& originalList,
                              const string& searchKey,
                              function<string(const T&)> getId,
                              function<void(const T&)> printItem) {
        if (originalList.empty()) {
            cout << "No data available.\n";
            return;
        }

        // --------- Linear search on unsorted list ---------
        auto startLinear = chrono::high_resolution_clock::now();
        int linearIndex = linearSearch(originalList, searchKey, getId);
        auto endLinear = chrono::high_resolution_clock::now();
        auto linearTime =
            chrono::duration_cast<chrono::microseconds>(endLinear - startLinear).count();

        // --------- Print linear search result BEFORE sort ---------
        cout << "\n=== SEARCH RESULT ===\n";
        if (linearIndex != -1)
            printItem(originalList[linearIndex]);
        else
            cout << "Item not found.\n";

        // --------- Prepare sorted list for binary search ---------
        vector<T> sortedList = originalList;
        sort(sortedList.begin(), sortedList.end(),
             [&](const T& a, const T& b) {
                 return stoi(getId(a).substr(1)) < stoi(getId(b).substr(1));
             });

        // --------- Binary search ---------
        auto startBinary = chrono::high_resolution_clock::now();
        int binaryIndex = binarySearch(sortedList, searchKey, getId);
        auto endBinary = chrono::high_resolution_clock::now();
        auto binaryTime =
            chrono::duration_cast<chrono::microseconds>(endBinary - startBinary).count();

        cout << "\nTime Comparison:\n";
        cout << "Linear Search Time : " << linearTime << " microseconds\n";
        cout << "Binary Search Time : " << binaryTime << " microseconds\n";
    }
};
