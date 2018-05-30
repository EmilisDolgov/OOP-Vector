// Vectorius.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vector.h"
#include <vector>
#include <chrono>
#include <iostream>


int main()
{
	Vector<int> a;
	std::vector<int> b;
	auto start = std::chrono::high_resolution_clock::now();
	for (auto i = 1; i <= 100000000; i++)
	{
		a.push_back(i);
	}
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Mano vectoriaus uzpildymas reiksmemis " << elapsed.count() << "s" << std::endl;
	start = std::chrono::high_resolution_clock::now();
	for (auto i = 1; i <= 100000000; i++)
	{
		b.push_back(i);
	}
	finish = std::chrono::high_resolution_clock::now();
	elapsed = finish - start;
	std::cout << "std::vectoriaus uzpildymas reiksmemis " << elapsed.count() << "s" << std::endl;
	return 0;
}

