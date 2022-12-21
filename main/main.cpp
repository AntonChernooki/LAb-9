#include <iostream>

using namespace std;

#include "lab9-reports.h"
#include "file_reader.h"
#include "constans.h"
#include "filter.h"
void output(dok* reports)
{ /********** ������� **********/
    cout << "�����........: " << endl;
    // ����� ������� ������
    if (reports->start.hour < 10)
        cout << 0 << reports->start.hour << ' ';
    else
        cout << reports->start.hour << ' ';
    if (reports->start.minutes < 10)
        cout << 0 << reports->start.minutes << '\n';
    else
        cout << reports->start.minutes << '\n';
    //����� ������� ���������
    if (reports->finish.hour < 10)
        cout << 0 << reports->finish.hour << ' ';
    else
        cout << reports->finish.hour << ' ';
    if (reports->finish.minutes < 10)
        cout << 0 << reports->finish.minutes << '\n';
    else
        cout << reports->finish.minutes << '\n';
    /********** ����� ���������� **********/
    cout << "���������........: " << endl;
    // ����� �������
    cout << reports->author.last_name << ' ';
    //����� ������ ����� �����
    cout << reports->author.first_name[0] << ' ';
    //����� ������ ����� ��������
    cout << reports->author.middle_name[0] << '\n';
    /********** ����� ���� **********/
    cout << "����...........: " << endl;
    cout << reports->theme << '\n';
    cout << '\n';
}
int main()
{
    setlocale(LC_ALL, "");
    cout << "������������ ������ #9. GIT\n";
    cout << "������� �2. ������\n";
    cout << "�����: ��������� �����\n";
    cout << "������: 11\n";
    dok* reports[MAX_FILE_ROWS_COUNT];
    int size;
    try {
        read("data.txt", reports, size);
        cout << "***** ������ *****\n\n";
        for (int i = 0; i < size; i++)
        {
            output(reports[i]);
        }
        bool (*check_function)(dok*) = NULL;
        cout << "\n�������� ������ ���������� ��� ��������� ������:\n";
        cout << "1) ������� ������� ����� ���������\n";
        cout << "2) ������� ������������� ������ 15 �����\n";
        cout << "\n������� ����� ���������� ������: ";
        int item;
        cin >> item;
        cout << '\n';
        switch (item)
        {
        case 1:
            check_function = check_dok_by_author; // ����������� � ��������� �� ������� ��������������� �������
            cout << "***** ������� ������� ����� ��������� *****\n\n";
            break;
        case 2:
            check_function = check_dok_by_time; // ����������� � ��������� �� ������� ��������������� �������
            cout << "***** ������� ������������� ������ 15 ����� *****\n\n";
            break;
        default:
            throw "������������ ����� ������";
        }
        if (check_function)
        {
            int new_size;
            dok** filtered = filter(reports, size, check_function, new_size);
            cout << "�������� ��������:\n";
            cout << "1)������������� ���������� �� �������� ������������ �������\n";
            cout << "2)���������� �������� �� �������� ������������ ������� \n";
            cout << "3)������������� ���������� �� ����������� ������� ������ �������\n";
            cout << "4)���������� �������� �� ����������� ������� ������ �������\n";
            cout << "\n������� ����� ���������� ������: ";
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
                throw "������������ ����� ������";
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

