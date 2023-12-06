#include "command.h"

PlayerMoveCommand::PlayerMoveCommand(Player* player, Vector2 velo)
{
	player_ = player;
	velocity_ = velo;
}

void PlayerMoveCommand::Exec()
{
	player_->Move(velocity_);
}

SelectUnitCommand::SelectUnitCommand(Player* player)
{
	player_ = player;
}

void SelectUnitCommand::Exec()
{
	player_->SelectUnit();
}

UnitMoveCommand::UnitMoveCommand(Unit* Unit, Vector2 velo)
{
	unit_ = Unit;
	velocity_ = velo;
}

void UnitMoveCommand::Exec()
{
	unit_->Move(velocity_);
}

UnitMoveEndCommand::UnitMoveEndCommand(Unit* Unit,Player* player)
{
	unit_ = Unit;
	player_ = player;
}

void UnitMoveEndCommand::Exec()
{
	unit_->MoveEnd(player_);
}
