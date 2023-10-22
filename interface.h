#pragma once
#include<vector>
#include <iostream>
#include <random>




void giveWelcomeMenu();
int inputInt();
double inputDouble();
std::vector<double>arrayFillMethodMenu();
std::vector<double>fillArrayManual();
std::vector<double>fillArrayRandom();


enum class welcomeMenuChoice{start = 1, test, exit};
enum class arrayFillMethodChoice { manual = 1, random, file };