#include "Inputhandler.h"
#include "Input.h"
ICommand* Inputhandler::HandleInput()
{
	if (Input::GetInstance()->PressKey(DIK_D)) {
		return pressKeyD_;
	}
	if (Input::GetInstance()->PressKey(DIK_A)) {
		return pressKeyA_;
	}
	return nullptr;
}

void Inputhandler::AssignMoveLeftCommandToPressKeyA()
{
	this->pressKeyA_ = new MoveLeftCommand();
}

void Inputhandler::AssignMoveRightCommandToPressKeyD()
{
	this->pressKeyD_ = new MoveRightCommand();
}
