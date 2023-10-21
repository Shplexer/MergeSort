#include "main.h"
#include "interface.h"
#include "sort.h"

int main() {
	bool exitFlag = false;
	giveWelcomeMenu();
	while (!exitFlag) {
		welcomeMenuChoice choice = static_cast<welcomeMenuChoice>(inputInt());
		switch (choice)
		{
		case welcomeMenuChoice::start:
			mergeSort();
			exitFlag = true;
			break;
		case welcomeMenuChoice::test:

			exitFlag = true;
			break;
		case welcomeMenuChoice::exit:

			exitFlag = true;
			break;
		default:
			std::cout << "cringe" << std::endl;
			break;
		}
	}

	return 0;
}