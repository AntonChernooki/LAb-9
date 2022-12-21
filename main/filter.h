#ifndef FILTER_H
#define FILTER_H
#include "lab9-reports.h"
dok** filter(dok* array[], int size, bool (*check)(dok* element), int& result_size);
bool check_dok_by_author(dok* element);
bool check_dok_by_time(dok* element);
void siftDown(dok** report, int root, int bottom);
void heapSort(dok** report, int size);
void merge(dok** report, int size);
void siftDown_str(dok** report, int root, int bottom);
void heapSort_str(dok** report, int size);
void merge_str(dok** report, int size);
void theme_sort(dok** report, int size);
#endif