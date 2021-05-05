#include <iostream> // подключение библиотеки потокового ввода-вывода
#include <thread> // подключение библиотеки для использования потоков
#include <chrono> // подключение библиотеки отсчета времени
using namespace std; // используем пространсво имен std для большей читаемости кода
void writer_func(int &message) // функция, не возвращающая значений, занимается чтением сообщения из консоли
{
	cout << "Write some number:\n"; // вывод строки
	cin >> message; // ввод сообщения из консоли в переменную message
	cout << "Writing done!\n"; // вывод строки
}
void reader_func(int &message)// функция, не возвращающая значений, занимается выводом полученного сообщения в консоль
{
	while (message == NULL) // цикл while проверяющий отклонения значения message
	{
		cout << "Sleeping...\n"; // вывод строки
		this_thread::sleep_for(chrono::seconds(3)); // заставляет поток, выполняющий эту функцию, "спать" на протяжении 3 секунд
	}
	cout << "Receiving message...\n"; // вывод строки
	cout << message << endl; // вывод полученного сообщения
	cout << "Message received!\n"; // вывод строки
}
int main() // функция main, с которой начинается программа
{
	cout << "Main thread started" << endl;
	int message = NULL; // объявления переменной для хранения сообщения
	thread writer(writer_func, ref(message)); // создание потока для выполнения функции writer_func
	thread reader(reader_func, ref(message)); // создание потока для выполнения функции reader_func
	reader.join(); // функция блокировки основного потока, ожидающей выполнения потока reader
	writer.join(); // функция блокировки основного потока, ожидающей выполнения потока writer
	cout << "Main thread ended!" << endl;
	return 0; // возвращение значения успешного выполнения программы без ошибок
}

