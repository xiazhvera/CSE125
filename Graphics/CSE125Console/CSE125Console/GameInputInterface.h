#pragma once

class GameInputInterface
{
public:
	GameInputInterface();
	~GameInputInterface();

	virtual void VProcessKeyInput(unsigned char key, int x, int y);

	virtual void VProcessMouseClick(int button, int state, int x, int y);
};

