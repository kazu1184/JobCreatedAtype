#include "pch.h"
#include "Enemy.h"

#include "Transform.h"
#include "MapPosition.h"
#include "Player.h"

#include "CharacterState.h"
#include "Idling.h"
#include "Chasing.h"
#include "Searching.h"

Enemy::Enemy(Player * player)
	:GameObject("Enemy")
{
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	GameObject::Update();
}

void Enemy::Render()
{
}

void Enemy::OnCollision(GameObject * object)
{
}
