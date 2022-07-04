#include <iostream>
#include<vector>
#include<Windows.h>
#include<functional>
#include<thread>
#include<chrono>
#include<string_view>
#include<mutex>
#include<atomic>

using namespace std;
using namespace::chrono;
// многопоточность в приложениях
//библиотека атомик
// управляющий поток
// атомарные операции
// гонки данных
// векторизованные вычисления


void Fill(vector<double>* course) {
    for (size_t i = 0; i < course->capacity(); i++)
    {
        this_thread::sleep_for(milliseconds(15));
        course->emplace_back(15 + (double)::rand() / (1 + ::rand()));

    }
}
mutex mt;
void Print(std::vector<double>::iterator start,std::vector<double>::iterator stop, string_view name) {
    while (start <= stop)
    {
        
        lock_guard lg(mt);
        cout <<  name <<"  Value " << *start << '\n';
        
        
        ++start;
       
    }
}


    int main()
    {
        system("chcp 1251>nul");
        
        this_thread::sleep_for(milliseconds(10));
        vector<double> udsCource;
        udsCource.reserve(540);
        vector<double> euroCource;
        euroCource.reserve(540);
        vector<double> phoundCource;
        phoundCource.reserve(540);
        thread tr1(Fill, &udsCource);
        thread tr2(Fill, &euroCource);
        thread tr3(Fill, &phoundCource);
        tr1.join();
        thread tr4(Print,udsCource.begin(), udsCource.begin() + 100,"USD");
       
        thread tr5([&tr2, &euroCource]() {
                tr2.join();
                Print(euroCource.begin(),euroCource.begin() + 100,"EURO");
            }
        );
        
        tr3.join();
        Print(phoundCource.begin(),phoundCource.begin() + 100,"PHOUND");
        tr5.join();
        tr4.join();
        cout <<"\nвремя работы программы: "<< clock();
        return 0;
    }


