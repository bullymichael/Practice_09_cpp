#include <iostream>
#include <string>
#include <cstring>
using namespace std;

enum TrainType 
{
    freight_train,      //товарный
    passenger_train,    //пассажирский
    repair_train,       //ремонтный
    express_train       //экспресс

};


struct Time
{
    int hours;            //часы
    int minutes;          //минуты
};


struct Route 
{
    char name[50];          //название
    char departure[50];     //пункт отправления
    char destination[50];   //пункт назначения
    Time departure_time;    //время отправления
    Time arrival_time;      //время прибытия
    int wagons;             //количество вагонов
    TrainType type;         //тип поезда
};


void print_time(const Time& t)         //вывод времени в стандартном формате с ведущими нулями
{
    if (t.hours < 10) cout << "0";
    cout << t.hours << ":";

    if (t.minutes < 10) cout << "0";
    cout << t.minutes;
}


const char* make_train_string(TrainType type) //преобразование видов поездов в текст
{
    switch(type)
    {
    case freight_train: return "Товарный поезд";
    case passenger_train: return "Пассажирский поезд";
    case repair_train: return "Ремонтный поезд";
    case express_train: return "Экспресс";
    default: return "Другой";
    }
}


void print_route(const Route& r)        //вывод по одному маршруту
{
    cout << "Маршрут: " << r.name << endl;
    cout << "Отправление: " << r.departure << " в ";
    print_time(r.departure_time);
    cout << endl;

    cout << "Прибытие: " << r.destination << " в ";
    print_time(r.arrival_time);
    cout << endl;

    cout << "Вагонов: " << r.wagons << endl;
    cout << "Тип: " << make_train_string(r.type) << endl;
}


void print_routes(const Route routes[], int count) //вывод по всем
{
    for (int i = 0; i < count; ++i) 
    {
        print_route(routes[i]);
    }

    cout << endl;
}


bool seaside_city(const char* city)                 //проверка приморский ли
{
    const char* seaside[] = { "Владивосток", "Новороссийск", "Сочи", "Севастополь", "Калининград", "Мурманск", "Архангельск", "Махачкала", "Ялта", "Адлер" };
    int seaside_count = sizeof(seaside) / sizeof(seaside[0]);
    for (int i = 0; i < seaside_count; i++)
    {
        if (strcmp(city, seaside[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

int freight_seaside(const Route source[], int source_size, Route dest[], int max_dest) //переписывание товарных поездов едущих в приморские города в другой массив
{
    int count = 0;
    for (int i = 0; i < source_size; i++)
    {
        if (count < max_dest && source[i].type == freight_train && seaside_city(source[i].destination))
        {
            dest[count] = source[i];
            count++;
        }
    }

    return count;
}


void bubble_sort_wagons(Route arr[], int size) //сортировка вагонов по убыванию
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = size - 1; j > i; j--)
        {
            if (arr[j - 1].wagons < arr[j].wagons)
            {
                Route temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
    }

}

void display_filtered(const Route all_routes[], int total_count) //полная фильтрация
{
    Route filtered[20];

    int filtered_count = freight_seaside(all_routes, total_count, filtered, 20);

    if (filtered_count > 0)
    {
        bubble_sort_wagons(filtered, filtered_count);  
        print_routes(filtered, filtered_count);
    }
    else
    {
        cout << "Ничего" << endl;
    }
}


void name_route(const Route routes[], int size, const char* name) //информация о маршруте по названию
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(routes[i].name, name) == 0)
        {
            print_route(routes[i]);
            return;
        }
    }

    cout << "Маршрут не найден" << endl;

    cout << endl;
}


void top_3(const Route routes[], int size) //три длинных пассажирских
{
    Route passenger[20];
    int pass_count = 0;

    for (int i = 0; i < size; i++)
    {
        if (routes[i].type == passenger_train)
        {
            passenger[pass_count] = routes[i];
            pass_count++;
        }
    }

    if (pass_count == 0)
    {
        cout << "Пассажирских маршрутов нет." << endl;
        return;
    }
    bubble_sort_wagons(passenger, pass_count);
    
    for (int i = 0; i < pass_count && i < 3; i++)
        print_route(passenger[i]);
}


void edit(Route routes[], int size, const char* name) //редактирование информации о маршруте
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(routes[i].name, name) == 0)
        {
            cout << "Название маршрута: " << routes[i].name << endl;

            cout << "Отправление: ";
            cin.getline(routes[i].departure, 50);

            cout << "Прибытие: ";
            cin.getline(routes[i].destination, 50);

            cout << "Время отправления: "; 
            cin >> routes[i].departure_time.hours >> routes[i].departure_time.minutes;

            cout << "Время прибытия: "; 
            cin >> routes[i].arrival_time.hours >> routes[i].arrival_time.minutes;

            cout << "Вагоны: ";
            cin >> routes[i].wagons;

            int t; 
            cout << "Тип (0-товарный, 1-пассажирский,2-ремонтный,3-эксперт): "; 
            cin >> t;
            routes[i].type = (TrainType)t;

            cout << "Проверка: " << endl;
            print_route(routes[i]);

            cout << endl;

            return;
        }
    }
    cout << "Маршрут не найден";
}


int main()
{
    setlocale(LC_ALL, "");
    system("chcp 1251 > nul");

    Route all_routes[20] = 
    {
        {"Экспресс-1", "Москва", "Санкт-Петербург", {8, 0}, {12, 30}, 8, express_train},
        {"Товарный-2", "Екатеринбург", "Владивосток", {5, 15}, {23, 45}, 25, freight_train},
        {"Пригород-3", "Краснодар", "Сочи", {7, 30}, {10, 15}, 4, passenger_train},
        {"Ремонт-4", "Новосибирск", "Омск", {9, 0}, {13, 0}, 3, repair_train},
        {"Грузовой-5", "Ростов-на-Дону", "Новороссийск", {6, 45}, {12, 20}, 30, freight_train},
        {"Экспресс-6", "Казань", "Москва", {10, 0}, {15, 30}, 10, express_train},
        {"Товарный-7", "Челябинск", "Мурманск", {4, 0}, {20, 15}, 28,  freight_train},
        {"Пригород-8", "Симферополь", "Севастополь", {8, 15}, {9, 45}, 5, passenger_train},
        {"Ремонт-9", "Волгоград", "Астрахань", {12, 0}, {18, 0}, 2, repair_train},
        {"Грузовой-10", "Оренбург", "Архангельск", {3, 30}, {19, 45}, 35,  freight_train},
        {"Экспресс-11", "Нижний Новгород", "Санкт-Петербург", {7, 0}, {13, 0}, 12, express_train},
        {"Товарный-12", "Пермь", "Калининград", {1, 0}, {22, 0}, 40,  freight_train},
        {"Пригород-13", "Владивосток", "Уссурийск", {6, 0}, {7, 30}, 6, passenger_train},
        {"Ремонт-14", "Самара", "Уфа", {11, 0}, {15, 30}, 4, repair_train},
        {"Грузовой-15", "Красноярск", "Махачкала", {2, 0}, {18, 0}, 32,  freight_train},
        {"Экспресс-16", "Екатеринбург", "Новосибирск", {9, 45}, {18, 15}, 9, express_train},
        {"Товарный-17", "Иркутск", "Ялта", {0, 30}, {23, 59}, 27,  freight_train},
        {"Пригород-18", "Сочи", "Адлер", {7, 0}, {7, 45}, 7, passenger_train},
        {"Ремонт-19", "Тюмень", "Омск", {14, 0}, {18, 30}, 3, repair_train},
        {"Грузовой-20", "Воронеж", "Новороссийск", {5, 0}, {14, 0}, 33,  freight_train}
    };

    display_filtered(all_routes, 20);

    cout << "Конкретный маршрут: " << '\n';
    name_route(all_routes, 20, "Экспресс-1");
    cout << endl;

    cout << "Три самых длинных пассажирских: " << '\n';
    top_3(all_routes, 20);
    cout << endl;

    cout << "Редактирование: " << '\n';
    edit(all_routes, 20, "Товарный-2");
    cout << endl;

    return 0;
}
