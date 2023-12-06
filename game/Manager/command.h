#pragma once
#include "game/Object/Player.h"
class Player;

class ICommand
{
public:
	
	virtual ~ICommand() = default;
	virtual void Exec() = 0;
};

class UnitMoveCommand :public ICommand {
public:
	UnitMoveCommand(Unit* Unit, Vector2 velo);
	void Exec()override;
private:
	Unit* unit_;
	Vector2 velocity_;
};

class UnitMoveEndCommand :public ICommand {
public:
	UnitMoveEndCommand(Unit* Unit, Player* player);
	void Exec()override;
private:
	Unit* unit_;
	Player* player_;
};


class PlayerMoveCommand :public ICommand {
public:
	PlayerMoveCommand(Player* player, Vector2 velo);
	void Exec()override;
private:
	Player* player_;
	Vector2 velocity_;
};
class SelectUnitCommand : public ICommand {
public:
	SelectUnitCommand(Player* player);
	void Exec()override;
private:
	Player* player_;
};

