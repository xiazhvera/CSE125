#include "stdafx.h"
#include "guiGameInput.h"

using namespace std;

// extends the guiGameInput class
class mainMenuInput : public guiGameInput{
	
	public:
		mainMenuInput();
		~mainMenuInput();

		// need to handle user input robot name
		void VProcessKeyInput(unsigned char key, int x, int y);
		void VProcessSpecialKey(int key, int x, int y);
};