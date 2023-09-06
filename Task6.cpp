
// Taskk5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

struct Vehicles
{   
    int Number;
    Vehicles* Next; // Указываем на следующую структуру
    char Case;
    union
    {
        struct
        {  double  EngineMotoVolume; } Motorbike;

        struct
        {
            double EngineAutoVolume; } Auto;
    };
    int Price;
    char Brand[10];
};

Vehicles* DataBase = nullptr; // Нулевой указатель на начало списка - нашей БД

Vehicles inputVehiclesInfo(char value) // ввод информации о структурах
{
    Vehicles vehicle;
    vehicle.Case = value;

    if (value > 1) {
        cout << "Error, please enter num from 0 to 1!" << endl;
        return vehicle;
    }

    if (vehicle.Case == 1)
    {
        cout << "Engine Moto volume: "; cin >> vehicle.Motorbike.EngineMotoVolume;
       
    }
    else
    {
        cout << "Engine Auto volume: "; cin >> vehicle.Auto.EngineAutoVolume;
        
    }
    // Ввод общих элементов вариантов;
    cout << "Brand of Vehicle: "; cin >> vehicle.Brand;
    cout << "Price of Vehicle ($): "; cin >> vehicle.Price;

    return vehicle;

}
// Вывод информации в консоль;
void printVehicleInfo(Vehicles vehicle)
{
    if (vehicle.Case == 1)
    {
        cout << "Engine Moto volume: " << vehicle.Motorbike.EngineMotoVolume << endl;
    }
    else
    {
        cout << "Engine Auto volume: " << vehicle.Auto.EngineAutoVolume << endl;
    }
    cout << "Brand of Vehicle: " << vehicle.Brand << endl;
    cout << "Price of Vehicle($): " << vehicle.Price << endl;
}




Vehicles* FoundVehiclesNumbers(int num) {
    Vehicles* p = DataBase;
    while (p != nullptr) // Пока не конец спискаи пока номер не найден, идём вдоль списка
    {
        if (p->Number == num) {
            break;
        }
        
        p = p->Next;
    }
    return p; // Вернём указатель на найденный элемент
}





// Добавить новое т/c по номеру 
void addVehicle(int num, char value)
{
    Vehicles* q = new Vehicles;
    *q = inputVehiclesInfo(value); // Заполняем информацией
    q->Number = num;

    if (DataBase == nullptr) num = 0;
    if (num > 1) {
        Vehicles* p = DataBase;
        while (p->Next != nullptr && --num > 1) {
            p = p->Next;
            q->Next = p->Next;
            p->Next = q;
        }
    }
    else {
        q->Next = DataBase;
        DataBase = q;
    }
}




// Удалить т/c по номеру;
void deleteVehicles(int num) {
    Vehicles* q;
    if (DataBase == nullptr) {
        return;
    }

    if (num) {
        Vehicles* p = DataBase;
        while (p->Next != nullptr && --num) {
            p = p->Next;
        }
        if ((q = p->Next) != nullptr) {
            p->Next = q->Next;
            delete q;
        }
    }
    else {
        q = DataBase;
        DataBase = q->Next;
        delete q;
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");
    Vehicles* p;
    int i, j;

    while (true)
    {
        cout << "Выберите действие: " << endl 
            << "1. Ввод информации о т/c." << endl
            << "2. Вывод информации о т/c." << endl
            << "3. Вывод всей информации." << endl
            << "4. Удаление информации о т/c." << endl
            << "5. Удаление всей информации." << endl
            << "6. Завершить" << endl
            << ">";

        cin >> i;

        switch (i)
        {
        case 1:
            cout << "Введите номер т/c: ";
            cin >> i;
            cout << "Выберите (1 - moto, 2 - auto): ";
            cin >> j;
            addVehicle(i, (j));
            break;


        case 2: cout << "Введите номер т/c: ";
            cin >> i;
            if ((p = FoundVehiclesNumbers(i)) != nullptr) {
                printVehicleInfo(*p);
            }
            else {
                cout << "т/c не найдено!" << endl;
            }

            break;

        case 3:
            p = DataBase;
            i = 0;
            while (p != nullptr) {
                cout << "Номер т/c: " << i + 1 << ":" << endl;
                printVehicleInfo(*p);;
                p = p->Next;
                cout << endl;
            }
            break;

        case 4:
            cout << "Номер т/c: ";
            cin >> i;

            deleteVehicles(i);
            break;

         
        case 5:
            while (DataBase != nullptr) {
                p = DataBase;
                DataBase = p->Next;
                delete p;
            }
            break;


        case 6: return 1;
        default: cout << "Попробуйте ещё раз!" << endl;
        }
    }


}