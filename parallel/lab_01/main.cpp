#include <iostream> // потоковый ввод-вывод
#include <thread> // создание потоков исполнения
#include <string> // работа со строками
#include <chrono> // работа с временем - установкой временных задержек

using namespace std;

string write(string msg, int time) {
    // выводим id потока, в котором функция вызвана
    cout << endl << "Thread # " << this_thread::get_id() << endl << "Sending..." << endl;
    // ставим задержку времени,чтобы сэмулировать выполнение сложной задачи.
    // Время подается параметром time на вход функции, при вызове.
    this_thread::sleep_for(chrono::seconds(time));
    // выводим сообщение, которое получили на вход функции
    cout << "Send '" << msg << "'" << endl;
    // фунция возвращает сообщение, полученное на вход
    return msg;
}

void read(string &msg, int time) {
    // эту временную "заглушку" time(в секундах) ставим, чтобы процессы потока-читателя
    // и потока-оправителя не начались единовременно, пока сообщение пустое
    cout << "Reader is waiting for data..." << endl;
    while (msg.empty()) this_thread::sleep_for(chrono::seconds(time)); // активное ожидание
    // вывод строк, для наглядности границ функции выводим id потока, в котором функция вызвана
    cout << endl << "Thread # " << this_thread::get_id() << endl << "Reading..." << endl;
    // Выводим сообщение полученное на вход функции
    cout << "Get '" << msg << "'" << endl;
}

int main(int argc, char *argv[]) {
    // данным выводом обозначим начало основного потока и выведем его id
    cout << endl << "Thread # " << this_thread::get_id() << endl;
    string phrase; // переменная, в которую будет записано сообщение для передачи
    cout << "Enter your message: ";
    getline(cin, phrase);
    // переменная, в которую поместится сообщение, после обработки "писателем"
    string message = "";
    // создадим поток-писатель. на месте передаваемого параметра записана
    // лябмда-функция, которая результат работы функции write присваивает переменной message
    // после работы писателя.
    // В качестве времени передадим в потоки 3 сек
    thread writer([&message, phrase]() { message = write(phrase, 3); });
    thread reader(read, ref(message), 3);

    // используем join, чтобы поток main дождался окончания работы
    // дочерних потоков writer и reader
    reader.join();
    writer.join();
    return 0;
}