#include <windows.h> // подключение winapi
#include <stdio.h> // библиотека ввода вывода
#include <tchar.h> // библиотека байтовых преобразований char
#include <strsafe.h> // библиотека дополнительной обработки буфера

#define BUFSIZE 512 // максимальная длина буфера

DWORD WINAPI InstanceThread(LPVOID); // прототип функции

int _tmain(VOID) // функция основной работы программы
{
    BOOL   fConnected = FALSE; // значение состояния подключенности
    DWORD  dwThreadId = 0; // id потока
    HANDLE hPipe = INVALID_HANDLE_VALUE, hThread = NULL; // дескриптор для канала и для потока
    LPCTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe"); // стандартное имя канала

    for (;;) // бесконечный цикл
    {
        _tprintf(TEXT("\nPipe Server: Main thread awaiting client connection on %s\n"), lpszPipename); // вывод сообщения
        hPipe = CreateNamedPipe( // создание именованого канала
            lpszPipename,             // имя канала 
            PIPE_ACCESS_DUPLEX,       // право доступа 
            PIPE_TYPE_MESSAGE |       // тип канала сообщений 
            PIPE_READMODE_MESSAGE |   // режим чтения сообщений 
            PIPE_WAIT,                // режим блокировки 
            PIPE_UNLIMITED_INSTANCES, // макс. кол-во экземляров  
            BUFSIZE,                  // размер выходного буфера 
            BUFSIZE,                  // размер входного буфера 
            0,                        // время тайм-аута клиента 
            NULL);     // атрибут безопасности по умолчанию 

        if (hPipe == INVALID_HANDLE_VALUE) // обработка ошибки при создании канала
        {
            _tprintf(TEXT("CreateNamedPipe failed, GLE=%d.\n"), GetLastError()); // вывод сообщения
            return -1; // вернуть код ошибки -1
        }

    	// ожидание подключения клиента; если успешно, то функция вернет не нулевое значение.
    	// если функция возвращает 0, GetLastError вернет ERROR_PIPE_CONNECTED

        fConnected = ConnectNamedPipe(hPipe, NULL) ?
            TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

        if (fConnected) // если клиент подключился
        {
            printf("Client connected, creating a processing thread.\n"); // вывод сообщения

            hThread = CreateThread( // создание потока для этого клиента
                NULL,              // атрибут безопасности 
                0,                 // размер стэка по умолчанию 
                InstanceThread,    // процедура потока
                (LPVOID)hPipe,    // параметр потока 
                0,                 // параметр приостановки
                &dwThreadId);      // возвращает id потока 

            if (hThread == NULL) // обработка ошибки создания потока
            {
                _tprintf(TEXT("CreateThread failed, GLE=%d.\n"), GetLastError()); // вывод сообщения
                return -1; // возврат кода ошибки -1
            }
            else 
                CloseHandle(hThread); // иначе закрыть дескриптор
        }
        else // клиент не смог подключится, закрываем канал
            CloseHandle(hPipe);
    }

    return 0;
}

DWORD WINAPI InstanceThread(LPVOID lpvParam)
// Эта функция обработки потока,
// которая позволяет читать и отвечать клиенту через соединение с открытым каналом,
// переданное из основного цикла.
{
    HANDLE hHeap = GetProcessHeap(); // получение "кучи" процесса
    TCHAR* pchRequest = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR)); // заполнение кучи на прием сообщений нулями, и выделение памяти под нее
    TCHAR* pchReply = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR)); // заполнение кучи на отправку сообщений нулями, и выделение памяти под нее

    DWORD cbBytesRead = 0, cbReplyBytes = 0, cbWritten = 0; // счетчики байтов для сообщений
    BOOL fSuccess = FALSE; // переменная успешности обменом сообщениями
    HANDLE hPipe = NULL; // инициализация переменной для канала

    if (lpvParam == NULL) // если название канала не существует
    {
        printf("\nERROR - Pipe Server Failure:\n"); // вывод сообщения
        printf("   InstanceThread got an unexpected NULL value in lpvParam.\n"); // вывод сообщения
        printf("   InstanceThread exitting.\n"); // вывод сообщения
        if (pchReply != NULL) HeapFree(hHeap, 0, pchReply); // освобождение памяти
        if (pchRequest != NULL) HeapFree(hHeap, 0, pchRequest); // освобождение памяти
        return (DWORD)-1; // возврат кода ошибки -1
    }

    if (pchRequest == NULL) // если не удалось выделить память по кучу
    {
        printf("\nERROR - Pipe Server Failure:\n");
        printf("   InstanceThread got an unexpected NULL heap allocation.\n");
        printf("   InstanceThread exitting.\n");
        if (pchReply != NULL) HeapFree(hHeap, 0, pchReply);
        return (DWORD)-1;
    }

    if (pchReply == NULL) // тоже что и сверху
    {
        printf("\nERROR - Pipe Server Failure:\n");
        printf("   InstanceThread got an unexpected NULL heap allocation.\n");
        printf("   InstanceThread exitting.\n");
        if (pchRequest != NULL) HeapFree(hHeap, 0, pchRequest);
        return (DWORD)-1;
    }

    printf("InstanceThread created, receiving and processing messages.\n"); // вывод сообщения

    hPipe = (HANDLE)lpvParam; // Параметр потока является дескриптором экземпляра объекта канала

    while (1) // цикл до тех пор пока не закончит читать
    {
        fSuccess = ReadFile( // чтение сообщение с клиента по каналу (сообщение ограничено bufsize)
            hPipe,        // дескриптор канала
            pchRequest,    // буфер для сообщения
            BUFSIZE * sizeof(TCHAR), // размер буфера 
            &cbBytesRead, // кол-во байт прочитанного сообщения
            NULL);        // ввод/вывод не перекрывается 

        if (!fSuccess || cbBytesRead == 0) // обработка пустого сообщения или ошибки при чтении
        {
            if (GetLastError() == ERROR_BROKEN_PIPE) // разрыв соеденения с клиентом
            {
                _tprintf(TEXT("InstanceThread: client disconnected.\n")); // вывод сообщения
            }
            else // ошибка при чтении
            {
                _tprintf(TEXT("InstanceThread ReadFile failed, GLE=%d.\n"), GetLastError()); // вывод сообщения
            }
            break; // выход из цикла
        }
        _tprintf(TEXT("Client Request String:\"%s\"\n"), pchRequest); // вывод сообщения
    }

    FlushFileBuffers(hPipe); // принудительная запись содержимого канала
    DisconnectNamedPipe(hPipe); // отсоединение от канала
    CloseHandle(hPipe); // закрытие дескриптора канала

    HeapFree(hHeap, 0, pchRequest); // освобождение памяти
    HeapFree(hHeap, 0, pchReply); // освобождение памяти

    printf("InstanceThread exiting.\n"); // вывод сообщения
    return 1; // возвращение кода программы 1
}

