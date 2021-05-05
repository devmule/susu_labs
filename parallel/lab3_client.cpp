#include <windows.h> // подклюение winapi
#include <synchapi.h> // библиотека синхронизации в winapi
#include <stdio.h> // библиотека ввода вывода
#include <conio.h> // функция для консольного ввода вывода
#include <tchar.h> // библиотека байтовых преобразований char

#define BUFSIZE 512 // максимальная длина буфера

int _tmain(int argc, TCHAR* argv[]) // функция основной работы программы
{
    HANDLE hPipe; // дескриптор для канала
    LPCWSTR lpvMessage = TEXT("Default message from client."); // переменная сообщения
    TCHAR  chBuf[BUFSIZE]; // буфер для ответа сервера
    BOOL   fSuccess = FALSE; // переменная состояния успешности передачи
    DWORD  cbRead, cbToWrite, cbWritten, dwMode; // переменные для подсчета кол-ва байт
    LPCWSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe"); // стандартное имя канала

    if (argc > 1) // если в программу передали канал, то используем его, а не по умолчанию
        lpvMessage = argv[1];

    while (true) // цикл установление соединения 
    {
        hPipe = CreateFile( // создаем канал
            lpszPipename,   // имя канала  
            GENERIC_READ |  // доступ на чтение и запись 
            GENERIC_WRITE,
            0,              // режим доступности 
            NULL,           // атрибуты безопасности по умолчанию
            OPEN_EXISTING,  // открытие существующего канала 
            0,              // атрибуты по умолчанию
            NULL);          // нет файла-шаблона

		// Break if the pipe handle is valid. 

        if (hPipe != INVALID_HANDLE_VALUE) // выход из цикла если соединение установлено
            break;

        // Exit if an error other than ERROR_PIPE_BUSY occurs. 

        if (GetLastError() != ERROR_PIPE_BUSY) // обработка ошибки, когда канал уже занят
        {
            _tprintf(TEXT("Could not open pipe. GLE=%d\n"), GetLastError());// вывод сообщения
            return -1; // вернуть код ошибки -1
        }

        // All pipe instances are busy, so wait for 20 seconds. 

        if (!WaitNamedPipe(lpszPipename, 20000)) // если канал не открылся в течение 20 секунд, отправить код -1
        {
            printf("Could not open pipe: 20 second wait timed out.");// вывод сообщения
            return -1; // вернуть код ошибки -1
        }
    }

    dwMode = PIPE_READMODE_MESSAGE; // новый режим канала
    fSuccess = SetNamedPipeHandleState( // меняем режим канала на чтение
        hPipe,    // дескриптор канала
        &dwMode,  // новый режим для канала
        NULL,     // максимальное кол-во байт
        NULL);    // максимальное время ожидания

	if (!fSuccess) // обработка ошибки, если сменить режим не удалось
    {
        _tprintf(TEXT("SetNamedPipeHandleState failed. GLE=%d\n"), GetLastError());// вывод сообщения
        return -1; // вернуть код ошибки -1
    }


	for(int i = 0; i < 10; i++) // 10 раз шлем на сервер сообщение
	{
		cbToWrite = (lstrlen(lpvMessage) + 1) * sizeof(TCHAR); // кол-во байт для отправки
		_tprintf(TEXT("Sending %d byte message: \"%s\"\n"), cbToWrite, lpvMessage);// вывод сообщения

		fSuccess = WriteFile( // пишем в канал
			hPipe,                  // дескриптор канала
			lpvMessage,             // сообщение 
			cbToWrite,              // длина сообщения 
			&cbWritten,             // кол-во записанных байт 
			NULL);                  // ввод/вывод не перекрывается 

		if (!fSuccess) // обработка ошибки при записи в канал
		{
			_tprintf(TEXT("WriteFile to pipe failed. GLE=%d\n"), GetLastError());// вывод сообщения
			return -1;// вернуть код ошибки -1
		}

		printf("Message sent to server\n");// вывод сообщения

        Sleep(1000); // прервать работу на 2 секунды
	}
    

    printf("\n<End of message, press ENTER to terminate connection and exit>");// вывод сообщения
    _getch(); // ожидание нажатия любой кнопки

    CloseHandle(hPipe); // закрываем дескриптор канала

    return 0;
}