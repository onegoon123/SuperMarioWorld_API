#pragma once
enum class PowerState
{
	Normal, Super, Fire, Cape
};
enum class ItemType
{
	Coin, UpMushroom, SuperMushroom, FireFlower, Feather
};
enum class RenderOrder
{
	Sky,
	BackGround,
	Map,
	Block,
	Monster,
	Player,
	Item,
	ForeGround,
	UI
};
enum class CollisionOrder
{
	Player,
	Block,
	Item,
	Monster,
	PlayerAttack,
	MonsterAttack
};