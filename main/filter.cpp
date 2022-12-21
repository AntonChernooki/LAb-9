#include "filter.h"
#include "lab9-reports.h"
#include <cstring>
#include <fstream>
dok** filter(dok* array[], int size, bool (*check)(dok* element), int& result_size)
{
    dok** result = new dok * [size];
    result_size = 0;
    for (int i = 0; i < size; i++)
    {
        if (check(array[i]))
        {
            result[result_size++] = array[i];
        }
    }
    return result;
}
bool check_dok_by_author(dok* element)
{
    return strcmp(element->author.first_name, "Иван") == 0 &&
        strcmp(element->author.middle_name, "Иванович") == 0 &&
        strcmp(element->author.last_name, "Иванов") == 0;
}
bool check_dok_by_time(dok* element)
{
    return element->length > 15;
}
void siftDown(dok** report, int root, int bottom)
{
    int maxChild; // индекс максимального потомка
    int done = 0; // флаг того, что куча сформирована
    // Пока не дошли до последнего ряда
    while ((root * 2 <= bottom) && (!done))
    {
        if (root * 2 == bottom)    // если мы в последнем ряду,
            maxChild = root * 2;    // запоминаем левый потомок
        // иначе запоминаем больший потомок из двух
        else if (report[root * 2]->length < report[root * 2 + 1]->length)
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;
        // если элемент вершины меньше максимального потомка
        if (report[root]->length > report[maxChild]->length)
        {
            // меняем их местами
            std::swap(report[root], report[maxChild]);
            root = maxChild;
        }
        else // иначе
            done = 1; // пирамида сформирована
    }
}
// Функция сортировки на куче
void heapSort(dok** report, int size)
{
    // Формируем нижний ряд пирамиды
    for (int i = (size / 2); i >= 0; i--)
        siftDown(report, i, size - 1);
    // Просеиваем через пирамиду остальные элементы
    for (int i = size - 1; i >= 1; i--)
    {
        std::swap(report[0], report[i]);
        siftDown(report, 0, i - 1);
    }
}
void merge(dok** report, int size)
{
    int mid = size / 2; // находим середину сортируемой последовательности
    if (size % 2 == 1)
        mid++;
    int h = 1; // шаг
    // выделяем память под формируемую последовательность
    dok** c = new dok * [size];
    int step;
    while (h < size)
    {
        step = h;
        int i = 0;   // индекс первого пути
        int j = mid; // индекс второго пути
        int k = 0;   // индекс элемента в результирующей последовательности
        while (step <= mid)
        {
            while ((i < step) && (j < size) && (j < (mid + step)))
            { // пока не дошли до конца пути
              // заполняем следующий элемент формируемой последовательности
              // меньшим из двух просматриваемых
                if (report[i]->length > report[j]->length)
                {
                    c[k] = report[i];
                    i++; k++;
                }
                else {
                    c[k] = report[j];
                    j++; k++;
                }
            }
            while (i < step)
            { // переписываем оставшиеся элементы первого пути (если второй кончился раньше)
                c[k] = report[i];
                i++; k++;
            }
            while ((j < (mid + step)) && (j < size))
            {  // переписываем оставшиеся элементы второго пути (если первый кончился раньше)
                c[k] = report[j];
                j++; k++;
            }
            step = step + h; // переходим к следующему этапу
        }
        h = h * 2;
        // Переносим упорядоченную последовательность (промежуточный вариант) в исходный массив
        for (i = 0; i < size; i++)
            report[i] = c[i];
    }
}
void siftDown_str(dok** report, int root, int bottom)
{
    int maxChild; // индекс максимального потомка
    int done = 0; // флаг того, что куча сформирована
    // Пока не дошли до последнего ряда
    while ((root * 2 <= bottom) && (!done))
    {
        if (root * 2 == bottom)    // если мы в последнем ряду,
            maxChild = root * 2;    // запоминаем левый потомок
        // иначе запоминаем больший потомок из двух

        else if (strlen(report[root * 2]->author.last_name) > strlen(report[root * 2 + 1]->author.last_name))
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;
        // если элемент вершины меньше максимального потомка
        if (strlen(report[root]->author.last_name) < strlen(report[maxChild]->author.last_name))
        {
            // меняем их местами
            std::swap(report[root], report[maxChild]);
            root = maxChild;
        }
        else // иначе
            done = 1; // пирамида сформирована
    }
}
// Функция сортировки на куче
void heapSort_str(dok** report, int size)
{
    // Формируем нижний ряд пирамиды
    for (int i = (size / 2); i >= 0; i--)
        siftDown_str(report, i, size - 1);
    // Просеиваем через пирамиду остальные элементы
    for (int i = size - 1; i >= 1; i--)
    {
        std::swap(report[0], report[i]);
        siftDown_str(report, 0, i - 1);
    }
}
void merge_str(dok** report, int size)
{
    int mid = size / 2; // находим середину сортируемой последовательности
    if (size % 2 == 1)
        mid++;
    int h = 1; // шаг
    // выделяем память под формируемую последовательность
    dok** c = new dok * [size];
    int step;
    while (h < size)
    {
        step = h;
        int i = 0;   // индекс первого пути
        int j = mid; // индекс второго пути
        int k = 0;   // индекс элемента в результирующей последовательности
        while (step <= mid)
        {
            while ((i < step) && (j < size) && (j < (mid + step)))
            { // пока не дошли до конца пути
              // заполняем следующий элемент формируемой последовательности
              // меньшим из двух просматриваемых
                if (strlen(report[i]->author.last_name) < strlen(report[j]->author.last_name))
                {
                    c[k] = report[i];
                    i++; k++;
                }
                else {
                    c[k] = report[j];
                    j++; k++;
                }
            }
            while (i < step)
            { // переписываем оставшиеся элементы первого пути (если второй кончился раньше)
                c[k] = report[i];
                i++; k++;
            }
            while ((j < (mid + step)) && (j < size))
            {  // переписываем оставшиеся элементы второго пути (если первый кончился раньше)
                c[k] = report[j];
                j++; k++;
            }
            step = step + h; // переходим к следующему этапу
        }
        h = h * 2;
        // Переносим упорядоченную последовательность (промежуточный вариант) в исходный массив
        for (i = 0; i < size; i++)
            report[i] = c[i];
    }
}
void theme_sort(dok** report, int size)
{
    int i = 0;
    int buf;
    while (i < size)
    {
        int count = 0;
        char* author = report[i]->author.last_name;
        for (int j = 0; j < size; j++)
        {
            if (strcmp(report[j]->author.last_name, author) == 0)
                count++;
        }
        if (count == 1)
            i++;
        else
        {
            buf = i;
            dok** c = new dok * [count];
            for (int j = 0; j < count; j++)
            {
                c[j] = report[buf];
                buf++;

            }
            int min;
            for (int k = 0; k < count; k++)
            {
                min = k;
                for (int j = k + 1; j < count; j++)
                    if (strlen(c[j]->theme) < strlen(c[min]->theme))
                        min = j;
                std::swap(c[k], c[min]);
            }
            for (int l = 0; l < count; l++)
            {
                report[i] = c[l];
                i++;
            }
        }
    }
}