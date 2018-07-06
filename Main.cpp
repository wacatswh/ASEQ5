#include <iostream>
#include <ctime>
#include <cstdlib>
#include "HardySort.h"

int main()
{
	clock_t time = clock();
	HardySort("10alphabets.txt", "10fixed.txt");
	std::cout << "Time elapsed: " << float(clock() - time) / CLOCKS_PER_SEC << std::endl;

	time = clock(); 
	HardySort("50messyData.txt", "50fixed.txt");
	std::cout << "Time elapsed: " << float(clock() - time) / CLOCKS_PER_SEC << std::endl;

	time = clock();
	HardySort("1K.txt", "1Kfixed.txt");
	std::cout << "Time elapsed: " << float(clock() - time) / CLOCKS_PER_SEC << std::endl;

	system("pause");
}