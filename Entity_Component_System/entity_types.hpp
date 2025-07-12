#pragma once
enum class EntityType{ Base, Enemy, Player };
enum class EntityState
{
    Idle, Jumping, Walking, Attacking, Hurt, Dying
};