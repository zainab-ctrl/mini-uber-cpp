#pragma once
#include <vector>
#include <algorithm>
using namespace std;

class Sort {
public:

    // ================== BUBBLE SORT ==================
    template <typename T, typename Compare>
    static void bubbleSort(vector<T>& arr, Compare comp) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (comp(arr[j + 1], arr[j])) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    // ================== SELECTION SORT ==================
    template <typename T, typename Compare>
    static void selectionSort(vector<T>& arr, Compare comp) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            int best = i;
            for (int j = i + 1; j < n; j++) {
                if (comp(arr[j], arr[best])) {
                    best = j;
                }
            }
            swap(arr[i], arr[best]);
        }
    }

    // ================== INSERTION SORT ==================
    template <typename T, typename Compare>
    static void insertionSort(vector<T>& arr, Compare comp) {
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && comp(key, arr[j])) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // ================== MERGE SORT ==================
    template <typename T, typename Compare>
    static void mergeSort(vector<T>& arr, Compare comp) {
        mergeSortHelper(arr, 0, arr.size() - 1, comp);
    }

    // ================== QUICK SORT ==================
    template <typename T, typename Compare>
    static void quickSort(vector<T>& arr, Compare comp) {
        quickSortHelper(arr, 0, arr.size() - 1, comp);
    }

private:
    // ---------- Merge Sort Helpers ----------
    template <typename T, typename Compare>
    static void merge(vector<T>& arr, int l, int m, int r, Compare comp) {
        int n1 = m - l + 1;
        int n2 = r - m;

        vector<T> L(n1), R(n2);
        for (int i = 0; i < n1; i++) L[i] = arr[l + i];
        for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (comp(L[i], R[j])) arr[k++] = L[i++];
            else arr[k++] = R[j++];
        }

        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

    template <typename T, typename Compare>
    static void mergeSortHelper(vector<T>& arr, int l, int r, Compare comp) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSortHelper(arr, l, m, comp);
            mergeSortHelper(arr, m + 1, r, comp);
            merge(arr, l, m, r, comp);
        }
    }

    // ---------- Quick Sort Helpers ----------
    template <typename T, typename Compare>
    static int partition(vector<T>& arr, int low, int high, Compare comp) {
        T pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (comp(arr[j], pivot)) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    template <typename T, typename Compare>
    static void quickSortHelper(vector<T>& arr, int low, int high, Compare comp) {
        if (low < high) {
            int pi = partition(arr, low, high, comp);
            quickSortHelper(arr, low, pi - 1, comp);
            quickSortHelper(arr, pi + 1, high, comp);
        }
    }
};
