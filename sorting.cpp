#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

void
insertion_sort (std::vector<int>& values)
{
    for (int i = 1; i < values.size(); i++)
    {
        int value = values.at(i);
        int j = i - 1;

        while ((j >= 0) and (values.at(j) > value))
        {
            values[j + 1] = values[j];
            j--;
        }

        values.at(j + 1) = value;
    }
}

void
selection_sort (std::vector<int>& values)
{
    for (int i = 0; i < values.size() - 1; i++)
    {
        int min_index = i;


        // Find smallest value starting at i
        for(int j = i + 1; j < values.size(); j++)
        {
            if(values[j] < values[min_index]) min_index = j;
        }

        std::swap(values.at(i), values.at(min_index));
    }
}

void
bubble_sort(std::vector<int>& values)
{
    int n = values.size();

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (values[j] > values[j + 1])
                std::swap(values[j], values[j + 1]);
        }
    }
}

void
quick_sort (std::vector<int>& values, int min, int max)
{
    if (min >= max) return;

    //std::srand(0);
    //int div_ind = std::rand() % max;
    //int divider = values.at(div_ind);
    //std::swap(values.at(min), values.at(div_ind));
    //int divider = values.at(min);
    int divider = values.at(min + ((max - min) / 2));

    int low = min;
    int high = max;

    while (true)
    {
        while (values[high] >= divider)
        {
            high--;
            if (high <= low) break;
        }

        if (high <= low)
        {
            values[low] = divider;
            break;
        }

        values[low] = values[high];
        low++;

        while (values[low] < divider)
        {
            low++;
            if (low >= high) break;
        }

        if (low >= high)
        {
            low = high;
            values[high] = divider;
            break;
        }

        values[high] = values[low];
    }

    quick_sort(values, min, low - 1);
    quick_sort(values, low + 1, max);
}

void
quick_sort (std::vector<int>& values)
{
    quick_sort(values, 0, values.size() - 1);
}

void
merge_sort (std::vector<int>& values, std::vector<int>& scratch, int min, int max)
{
    if (min == max) return;

    int mid = min + ((max - min) / 2);

    merge_sort(values, scratch, min, mid);
    merge_sort(values, scratch, mid + 1, max);

    int left_ind = min;
    int right_ind = mid + 1;
    int scratch_ind = left_ind;

    while ((left_ind <= mid) and (right_ind <= max))
    {
        if (values[left_ind] <= values[right_ind])
        {
            scratch[scratch_ind] = values[left_ind];
            left_ind++;
        }
        else
        {
            scratch[scratch_ind] = values[right_ind];
            right_ind++;
        }

        scratch_ind++;
    }

    for (int i = left_ind; i <= mid; i++)
    {
        scratch[scratch_ind] = values[i];
        scratch_ind++;
    }

    for (int i = right_ind; i <= max; i++)
    {
        scratch[scratch_ind] = values[i];
        scratch_ind++;
    }

    for (int i = min; i <= max; i++)
    {
        values[i] = scratch[i];
    }
}

void
merge_sort (std::vector<int>& values)
{
    std::vector<int> scratch;
    scratch.reserve(values.capacity());
    scratch.resize(values.size());
    merge_sort(values, scratch, 0, values.size() - 1);
}

void
counting_sort(std::vector<int>& values)
{
    if (values.empty()) return;

    int max_val = *std::max_element(values.begin(), values.end());
    int range = max_val + 1;

    std::vector<int> count_values(range, 0);
    std::vector<int> output_values(values.size());

    for (int element : values)
    {
        count_values[element]++;
    }

    for (int i = 1; i < range; i++)
    {
        count_values[i] += count_values[i - 1];
    }

    for (int i = values.size() - 1; i >= 0; i--)
    {
        output_values[count_values[values[i]] - 1] = values[i];
        count_values[values[i]]--;
    }

    values = output_values;
}

//template<typename T> void
//print_vector (const std::vector<T>& v)
//{
//    if (v.size() == 0)
//    {
//        std::cout << "[]";
//        return;
//    }
//
//    std::cout << "[" << v.at(0);
//
//    for (int i = 1; i < v.size(); i++)
//    {
//        std::cout << ", " << v.at(i);
//    }
//
//    std::cout << "]";
//}

void
fill_random (std::vector<int>& values, int max_value)
{
    std::srand(0);
    for (int i = 0; i < values.size(); ++i)
    {
        values.at(i) = std::rand() % max_value;
    }
}

void
fill_incremental (std::vector<int>& values, int max_value)
{
    double section = max_value / static_cast<double>(values.size());
    double current = 0.0;
    for (int i = 0; i < values.size(); ++i)
    {
        values.at(i) = static_cast<int>(current);
        current += section;
    }
}

void
fill_decremental (std::vector<int>& values, int max_value)
{
    double section = max_value / static_cast<double>(values.size());
    double current = 0.0;
    for (int i = values.size() - 1; i >= 0; --i)
    {
        values.at(i) = static_cast<int>(current);
        current += section;
    }
}

int
main ()
{
    // Declaring vectors to sort
    std::vector<int> vecran; // vector to sort with random values
    std::vector<int> vecinc; // vector to sort with incremental values
    std::vector<int> vecdec; // vector to sort with decremental values

    // Testing std::sort
    //for (int i = 100; i <= 10'000'000; i *= 10)
    //{
    //    vecran.resize(i);
    //    fill_random(vecran, 999);
    //    vecinc.resize(i);
    //    fill_incremental(vecinc, 999);
    //    vecdec.resize(i);
    //    fill_random(vecdec, 999);

    //    auto start = std::chrono::high_resolution_clock::now();
    //    std::sort(vecran.begin(), vecran.end());
    //    auto stop = std::chrono::high_resolution_clock::now();
    //    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    double total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecran.begin(), vecran.end())) std::cout << "std::sort, with " << i << " random values, took: " << total_time << " seconds\n";

    //    start = std::chrono::high_resolution_clock::now();
    //    std::sort(vecinc.begin(), vecinc.end());
    //    stop = std::chrono::high_resolution_clock::now();
    //    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecinc.begin(), vecinc.end())) std::cout << "std::sort, with " << i << " incremental values, took: " << total_time << " seconds\n";

    //    start = std::chrono::high_resolution_clock::now();
    //    std::sort(vecdec.begin(), vecdec.end());
    //    stop = std::chrono::high_resolution_clock::now();
    //    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecdec.begin(), vecdec.end()))
    //        std::cout << "std::sort, with " << i << " decremental values, took: " << total_time << " seconds\n\n";
    //}

    // Testing InsertionSort
    //for (int i = 100; i <= 10'000'000; i *= 10)
    //{
    //    vecran.resize(i);
    //    fill_random(vecran, 999);
    //    vecinc.resize(i);
    //    fill_incremental(vecinc, 999);
    //    vecdec.resize(i);
    //    fill_random(vecdec, 999);

    //    auto start = std::chrono::high_resolution_clock::now();
    //    insertion_sort(vecran);
    //    auto stop = std::chrono::high_resolution_clock::now();
    //    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    double total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecran.begin(), vecran.end())) std::cout << "InsertionSort, with " << i << " random values, took: " << total_time << " seconds\n";

    //    start = std::chrono::high_resolution_clock::now();
    //    insertion_sort(vecinc);
    //    stop = std::chrono::high_resolution_clock::now();
    //    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecinc.begin(), vecinc.end())) std::cout << "InsertionSort, with " << i << " incremental values, took: " << total_time << " seconds\n";

    //    start = std::chrono::high_resolution_clock::now();
    //    insertion_sort(vecdec);
    //    stop = std::chrono::high_resolution_clock::now();
    //    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecdec.begin(), vecdec.end())) std::cout << "InsertionSort, with " << i << " decremental values, took: " << total_time << " seconds\n\n";
    //}

    // Testing SelectionSort
    //for (int i = 100; i <= 10'000'000; i *= 10)
    //{
    //    vecran.resize(i);
    //    fill_random(vecran, 999);
    //    vecinc.resize(i);
    //    fill_incremental(vecinc, 999);
    //    vecdec.resize(i);
    //    fill_random(vecdec, 999);

    //    auto start = std::chrono::high_resolution_clock::now();
    //    selection_sort(vecran);
    //    auto stop = std::chrono::high_resolution_clock::now();
    //    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    double total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecran.begin(), vecran.end())) std::cout << "SelectionSort, with " << i << " random values, took: " << total_time << " seconds\n";

    //    start = std::chrono::high_resolution_clock::now();
    //    selection_sort(vecinc);
    //    stop = std::chrono::high_resolution_clock::now();
    //    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecinc.begin(), vecinc.end())) std::cout << "SelectionSort, with " << i << " incremental values, took: " << total_time << " seconds\n";

    //    start = std::chrono::high_resolution_clock::now();
    //    selection_sort(vecdec);
    //    stop = std::chrono::high_resolution_clock::now();
    //    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecdec.begin(), vecdec.end())) std::cout << "SelectionSort, with " << i << " decremental values, took: " << total_time << " seconds\n\n";
    //}

    // Testing QuickSort
    //for (int i = 100; i <= 10'000'000; i *= 10)
    //{
    //    vecran.resize(i);
    //    fill_random(vecran, 999);
    //    vecinc.resize(i);
    //    fill_incremental(vecinc, 999);
    //    vecdec.resize(i);
    //    fill_random(vecdec, 999);

    //    auto start = std::chrono::high_resolution_clock::now();
    //    quick_sort(vecran);
    //    auto stop = std::chrono::high_resolution_clock::now();
    //    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    double total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecran.begin(), vecran.end())) std::cout << "QuickSort, with " << i << " random values, took: " << total_time << " seconds\n";

    //    start = std::chrono::high_resolution_clock::now();
    //    quick_sort(vecinc);
    //    stop = std::chrono::high_resolution_clock::now();
    //    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecinc.begin(), vecinc.end())) std::cout << "QuickSort, with " << i << " incremental values, took: " << total_time << " seconds\n";

    //    start = std::chrono::high_resolution_clock::now();
    //    quick_sort(vecdec);
    //    stop = std::chrono::high_resolution_clock::now();
    //    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecdec.begin(), vecdec.end())) std::cout << "QuickSort, with " << i << " decremental values, took: " << total_time << " seconds\n\n";
    //}

    // Testing BubbleSort
    //for (int i = 100; i <= 10'000'000; i *= 10)
    //{
    //    vecran.resize(i);
    //    fill_random(vecran, 999);
    //    vecinc.resize(i);
    //    fill_incremental(vecinc, 999);
    //    vecdec.resize(i);
    //    fill_random(vecdec, 999);

    //    auto start = std::chrono::high_resolution_clock::now();
    //    bubble_sort(vecran);
    //    auto stop = std::chrono::high_resolution_clock::now();
    //    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    double total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecran.begin(), vecran.end())) std::cout << "BubbleSort, with " << i << " random values, took: " << total_time << " seconds\n";

    //    start = std::chrono::high_resolution_clock::now();
    //    bubble_sort(vecinc);
    //    stop = std::chrono::high_resolution_clock::now();
    //    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecinc.begin(), vecinc.end())) std::cout << "BubbleSort, with " << i << " incremental values, took: " << total_time << " seconds\n";

    //    start = std::chrono::high_resolution_clock::now();
    //    bubble_sort(vecdec);
    //    stop = std::chrono::high_resolution_clock::now();
    //    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecdec.begin(), vecdec.end())) std::cout << "BubbleSort, with " << i << " decremental values, took: " << total_time << " seconds\n\n";
    //}

    // Testing MergeSort
    //for (int i = 100; i <= 10'000'000; i *= 10)
    //{
    //    vecran.resize(i);
    //    fill_random(vecran, 999);
    //    vecinc.resize(i);
    //    fill_incremental(vecinc, 999);
    //    vecdec.resize(i);
    //    fill_random(vecdec, 999);

    //    auto start = std::chrono::high_resolution_clock::now();
    //    merge_sort(vecran);
    //    auto stop = std::chrono::high_resolution_clock::now();
    //    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    double total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecran.begin(), vecran.end())) std::cout << "MergeSort, with " << i << " random values, took: " << total_time << " seconds\n";

    //    start = std::chrono::high_resolution_clock::now();
    //    merge_sort(vecinc);
    //    stop = std::chrono::high_resolution_clock::now();
    //    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecinc.begin(), vecinc.end())) std::cout << "MergeSort, with " << i << " incremental values, took: " << total_time << " seconds\n";

    //    start = std::chrono::high_resolution_clock::now();
    //    merge_sort(vecdec);
    //    stop = std::chrono::high_resolution_clock::now();
    //    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecdec.begin(), vecdec.end())) std::cout << "MergeSort, with " << i << " decremental values, took: " << total_time << " seconds\n\n";
    //}

    // Testing CountingSort
    //for (int i = 100; i <= 10'000'000; i *= 10)
    //{
    //    vecran.resize(i);
    //    fill_random(vecran, 999);
    //    vecinc.resize(i);
    //    fill_incremental(vecinc, 999);
    //    vecdec.resize(i);
    //    fill_random(vecdec, 999);

    //    auto start = std::chrono::high_resolution_clock::now();
    //    counting_sort(vecran);
    //    auto stop = std::chrono::high_resolution_clock::now();
    //    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    double total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecran.begin(), vecran.end())) std::cout << "CountingSort, with " << i << " random values, took: " << total_time << " seconds\n";

    //    start = std::chrono::high_resolution_clock::now();
    //    counting_sort(vecinc);
    //    stop = std::chrono::high_resolution_clock::now();
    //    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecinc.begin(), vecinc.end())) std::cout << "CountingSort, with " << i << " incremental values, took: " << total_time << " seconds\n";

    //    start = std::chrono::high_resolution_clock::now();
    //    counting_sort(vecdec);
    //    stop = std::chrono::high_resolution_clock::now();
    //    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //    total_time = duration.count() / 1'000'000.0;
    //    if (std::is_sorted(vecdec.begin(), vecdec.end())) std::cout << "CountingSort, with " << i << " decremental values, took: " << total_time << " seconds\n\n";
    //}

    return 0;
}
