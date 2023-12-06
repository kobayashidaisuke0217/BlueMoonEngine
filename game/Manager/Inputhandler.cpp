#include "Inputhandler.h"
#include "Input.h"
Inputhandler::Inputhandler()
{
}
Inputhandler::~Inputhandler()
{
}
ICommand* Inputhandler::PlayerHandleInput(Player* player)
{
	player_ = player;
	if (Input::GetInstance()->PushKey(DIK_D)) {
		return new PlayerMoveCommand(player,{ 1.0f,0.0f });
	}
	if (Input::GetInstance()->PushKey(DIK_A)) {
		return new PlayerMoveCommand(player, { -1.0f,0.0f });
	}

	if (Input::GetInstance()->PushKey(DIK_W)) {
		return new PlayerMoveCommand(player, {0.0f,-1.0f });
	}
	if (Input::GetInstance()->PushKey(DIK_S)) {
		return new PlayerMoveCommand(player, { 0.0f,1.0f });
	}
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		return new SelectUnitCommand(player);
	}
	return nullptr;
}

ICommand* Inputhandler::UnitHandleInput(Unit* unit)
{
	if (Input::GetInstance()->PushKey(DIK_D)) {
		return new UnitMoveCommand(unit, { 1.0f,0.0f });
	}
	if (Input::GetInstance()->PushKey(DIK_A)) {
		return new UnitMoveCommand(unit, { -1.0f,0.0f });
	}

	if (Input::GetInstance()->PushKey(DIK_W)) {
		return new UnitMoveCommand(unit, { 0.0f,-1.0f });
	}
	if (Input::GetInstance()->PushKey(DIK_S)) {
		return new UnitMoveCommand(unit, { 0.0f,1.0f });
	}
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		return new UnitMoveEndCommand(unit,player_);
	}
	return nullptr;
}


