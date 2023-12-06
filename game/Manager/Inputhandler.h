#pragma once
#include"game/Object/Player.h"
#include"game/Object/Unit.h"
#include "command.h"

class Inputhandler
{
public:
	Inputhandler();
	~Inputhandler();
	ICommand* PlayerHandleInput(Player* player);
	ICommand* UnitHandleInput(Unit* unit);

private:
	Player* player_;
	Unit* selectedUnit_;
};

