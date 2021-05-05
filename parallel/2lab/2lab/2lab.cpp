﻿#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
using namespace std;

void test(float* t, float* t2)
{
	for (int i = 0; i < 10; i++)
		cout << t[i] << '+' << t2[i] << ' ';
	cout << endl;
}

int main()
{
	int N = 100;
	float* t = (float*)malloc(sizeof(float) * N);
	for (int i = 0; i < N; i++)
	{
		t[i] = i;
	}
	int i = 10;
	test(t, t + i);
	return 0;
}