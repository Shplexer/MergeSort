#pragma once
#include<vector>
#include <iostream>
#include <random>




void giveWelcomeMenu();
int inputInt();
double inputDouble();
void giveArrayToUser(std::vector<double>);
void saveToFileMenu(std::vector<double>);
std::vector<double>arrayFillMethodMenu();
std::vector<double>fillArrayManual();
std::vector<double>fillArrayRandom();


enum class welcomeMenuChoice{start = 1, test, exit};
enum class arrayFillMethodChoice { manual = 1, random, file };
enum class saveChoice{yes = 1, no};