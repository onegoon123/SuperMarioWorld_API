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
	Item,
	Monster,
	Player,
	ForeGround,
	UI
};
enum class CollisionOrder
{
	Check,
	Player,
	Block,
	Item,
	Monster,
	PlayerAttack,
	MonsterAttack
};