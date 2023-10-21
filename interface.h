#pragma once
#include<vector>
#include <iostream>

void giveWelcomeMenu();
int inputInt();
double inputDouble();
std::vector<double> fillArr();

enum class welcomeMenuChoice{start = 1, test, exit};
