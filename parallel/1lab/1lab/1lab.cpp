﻿#include <thread>
#include <iostream>
#include <chrono>
void write(int& mess, int value, int waitTime)
{
    std::cout << "Go write, thread_id = " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(waitTime));
    mess = value;

    std::cout << "End write\n";
}
void read(int& mess, int waitTime)
{
    std::cout << "Go read, thread_id = " << std::this_thread::get_id() << std::endl;
    while (mess == NULL) std::cout << "Wait\n";
    std::cout << "Message: " << mess << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(waitTime));
    std::cout << "End read\n";
}
int main()
{
    int mes = NULL;
    std::thread t_write(write, std::ref(mes), 100, 1);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::thread t_read(read, std::ref(mes), 1);
    t_write.join();
    //t_read.join();
}