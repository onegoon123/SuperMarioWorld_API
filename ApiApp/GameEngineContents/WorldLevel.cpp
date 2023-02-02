#include "WorldLevel.h"
#include "WorldImage.h"

WorldLevel::WorldLevel() {

}

WorldLevel::~WorldLevel() {

}

void WorldLevel::Loading()
{
	CreateActor<WorldImage>();
}

void WorldLevel::Update(float _DeltaTime)
{

}
