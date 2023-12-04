#pragma once
#include "game/Object/command.h"
class Inputhandler
{
public:
	ICommand* HandleInput();
	void AssignMoveLeftCommandToPressKeyA();
	void AssignMoveRightCommandToPressKeyD();
private:
	ICommand* pressKeyD_;
	ICommand* pressKeyA_;
};

