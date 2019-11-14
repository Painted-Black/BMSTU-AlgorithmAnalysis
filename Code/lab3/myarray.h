#ifndef MYARRAY_H
#define MYARRAY_H

#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <ctime>
#include <vector>

class MyArray
{
public:
    MyArray(int s, int defaultValue=0);
    MyArray(int s, std::initializer_list<int> l);
    MyArray(int s, int *arr);
    MyArray(std::vector<int> &vec);
    ~MyArray();
    int getSize() const;
    int at(int index);
    void randomize(int minVal=-100, int range=200);
    void insert(int value, int index);
    void insertionSort();
    void insertionSortDescending();
    void quickSort(int first, int last);
    void bubbleSort();
    bool compare(const MyArray &toCompare);
    bool compare(const MyArray &toCompare1, const MyArray &toCompare2);
    void print();
    void copy(const MyArray& arr);
private:
    int pivotList(int* list, int first, int last);
    int size;
    int* array;
};

#endif // MYARRAY_H
