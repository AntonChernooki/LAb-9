#include <iostream>

using namespace std;

#include "lab9-reports.h"
#include "file_reader.h"
#include "constans.h"
#include "filter.h"
void output(dok* reports)
{ /********** времени **********/
    cout << "Время........: " << endl;
    // вывод времени начала
    if (reports->start.hour < 10)
        cout << 0 << reports->start.hour << ' ';
    else
        cout << reports->start.hour << ' ';
    if (reports->start.minutes < 10)
        cout << 0 << reports->start.minutes << '\n';
    else
        cout << reports->start.minutes << '\n';
    //вывод времени окончания
    if (reports->finish.hour < 10)
        cout << 0 << reports->finish.hour << ' ';
    else
        cout << reports->finish.hour << ' ';
    if (reports->finish.minutes < 10)
        cout << 0 << reports->finish.minutes << '\n';
    else
        cout << reports->finish.minutes << '\n';
    /********** вывод докладчика **********/
    cout << "Докладчик........: " << endl;
    // вывод фамилии
    cout << reports->author.last_name << ' ';
    //вывод первой буквы имени
    cout << reports->author.first_name[0] << ' ';
    //вывод первой буквы отчества
    cout << reports->author.middle_name[0] << '\n';
    /********** вывод темы **********/
    cout << "Тема...........: " << endl;
    cout << reports->theme << '\n';
    cout << '\n';
}
int main()
{
    setlocale(LC_ALL, "");
    cout << "Лабараторная работа #9. GIT\n";
    cout << "Вариант №2. Доклад\n";
    cout << "Автор: Черноокий Антон\n";
    cout << "Группа: 11\n";
    dok* reports[MAX_FILE_ROWS_COUNT];
    int size;
    try {
        read("data.txt", reports, size);
        cout << "***** Доклад *****\n\n";
        for (int i = 0; i < size; i++)
        {
            output(reports[i]);
        }
        bool (*check_function)(dok*) = NULL;
        cout << "\nВыберите способ фильтрации или обработки данных:\n";
        cout << "1) Доклады Иванова Ивана Ивановича\n";
        cout << "2) Доклады длительностью больше 15 минут\n";
        cout << "\nВведите номер выбранного пункта: ";
        int item;
        cin >> item;
        cout << '\n';
        switch (item)
        {
        case 1:
            check_function = check_dok_by_author; // присваиваем в указатель на функцию соответствующую функцию
            cout << "***** Доклады Иванова Ивана Ивановича *****\n\n";
            break;
        case 2:
            check_function = check_dok_by_time; // присваиваем в указатель на функцию соответствующую функцию
            cout << "***** Доклады длительностью больше 15 минут *****\n\n";
            break;
        default:
            throw "Некорректный номер пункта";
        }
        if (check_function)
        {
            int new_size;
            dok** filtered = filter(reports, size, check_function, new_size);
            cout << "Выберите критерии:\n";
            cout << "1)Пирамидальная сортировка по убыванию длительности доклада\n";
            cout << "2)Сортировка слиянием по убыванию длительности доклада \n";
            cout << "3)Пирамидальная сортировка по возрастанию фамилии автора доклада\n";
            cout << "4)Сортировка слиянием по возрастанию фамилии автора доклада\n";
            cout << "\nВведите номер выбранного пункта: ";
            int sort;
            cin >> sort;
            switch (sort)
            {
            case 1:
                heapSort(filtered, new_size);
                break;
            case 2:
                merge(filtered, new_size);
                break;
            case 3:
                heapSort_str(filtered, new_size);
                theme_sort(filtered, new_size);
                break;
            case 4:
                merge_str(filtered, new_size);
                theme_sort(filtered, new_size);
                break;
            default:
                throw "Некорректный номер пункта";
            }
            for (int i = 0; i < new_size; i++)
            {
                output(filtered[i]);
            }
            delete[] filtered;
        }
        for (int i = 0; i < size; i++)
        {
            delete reports[i];
        }
    }
    catch (const char* error)
    {
        cout << error << '\n';
    }
    return 0;
}

