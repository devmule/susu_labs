#include <iostream> //для удобного потокового вывода текст.сообщений
#include <thread> //для создания потоков исполнения
#include <string> //для работы со строками
#include <chrono> //для работы с временем - установкой временных задержек
#include <mutex> //для обеспецения синхронизации и защиты разделяемых потоками данных
#include <queue> //удобный контейнер для реализации буфера
#include <ctime> //для обновления времени в генераторе случ.чисел
using namespace std;

//объект класса mutex, для обеспечения синхронизации работы потоков и
//предотврацения конфликтов при обращении потоков к общим ресурсам
mutex mtx;
//константа, задающая размер буфера
int BUFF_SIZE = 10;
//переменная-счетчик, обозначающая заполненность буфера
int counter = 0;
//функция писателя
void write(queue<int> &buf,int speed_time ) {
    while (true) {
        //задержка времени, для регулировки скорости работы потоков
        this_thread::sleep_for(chrono::seconds(speed_time));
        //закрываем доступ к разделяемым ресурсам для др.потоков
        mtx.lock();
        if (counter != BUFF_SIZE) {
            //генерируем рандомное число, предварительно обновив ранд и добавляем в буфер
            srand(time(0));
            int rand_count = rand() % 1000;
            buf.push(rand_count);
            //обозначаем заполнение буфера, увеличением счетчика на 1
            counter++;
            //Выводим заполненность буфера после его заполнения
            cout<<"Bufer size = "<<counter<<endl;
            //выводим сообщение о сгенерированном числе
            cout << "WRITER-thread (id =" << this_thread::get_id() << ") generate number: " << rand_count << endl;

        }
        //открываем разделяемые ресурсы для других потоков
        mtx.unlock();
    }
}
//функция читателя
void read(queue<int> &buf, int speed_time) {
    while (true) {
        //задержка времени, для регулировки скорости работы потоков
        this_thread::sleep_for(chrono::seconds(speed_time));
        //закрываем доступ к разделяемым ресурсам для др.потоков
        mtx.lock();
        if (!buf.empty()) {
            //записываем в переменную значение последнего элемента буфера
            int number = buf.front();
            //удаляем этот элемент, сделав его тем самым прочитанным
            buf.pop();
            //счетчик размера буфера уменьшаем на 1
            counter--;
            //выводим сообщение о прочитанном числе
            cout << "Reader-thread (id ="<<this_thread::get_id()<< ") read number: " << number << endl;
        }
        //открываем разделяемые ресурсы для других потоков
        mtx.unlock();
    }
}
int main() {
    //данным выводом обозначим начало основного потока
    cout << "MAIN STARTS" << "(Thread id =" << this_thread::get_id() <<")"<< endl;
    //зададим скорости работы потоков: укажем временные задержки в секундах
    int time_writer_1 = 2;
    int time_writer_2 = 2;
    int time_reader = 5;
    //создаем буфер для хранения данных
    queue<int> buffer;
    //создаем 3 вычислительных потока
    thread writer_1(write,ref(buffer),time_writer_1);
    thread writer_2(write,ref(buffer),time_writer_2);
    thread reader(read,ref(buffer),time_reader);
    //используем join, чтобы поток main дождался окончания работы дочерних потоков
    writer_1.join();
    writer_2.join();
    reader.join();
    return 0;
}