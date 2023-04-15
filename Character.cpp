#include "Character.h"
Character::Character()
{
}
Character::~Character()
{
}
void Character::SetupCharacterAttributes(int hp, int strength, int defense, int agility)
{
    SetHitPoints(hp);
    SetMaximumHitPoints(hp);
    SetStrength(strength);
    SetDefense(defense);
    SetAgility(agility);
}
void Character::DisplayCharacterAttributes()
{
    cout << "HP: " << hitPoints << "/" << maximumHitPoints << endl;
    cout << "STR: " << strength << endl;
    cout << "DEF: " << defense << endl;
    cout << "AGL: " << agility << endl;
}
int Character::GetHitPoints() const
{
    return hitPoints;
}
int Character::GetMaximumHitPoints() const
{
    return maximumHitPoints;
}
int Character::GetStrength() const
{
    return strength;
}
int Character::GetDefense() const
{
    return defense;
}
int Character::GetAgility() const
{
    return agility;
}
void Character::SetHitPoints(int hit_points)
{
    hitPoints = hit_points;
}
void Character::SetMaximumHitPoints(int maximum_hit_points)
{
    maximumHitPoints = maximum_hit_points;
}
void Character::SetStrength(int strength)
{
    Character::strength = strength;
}
void Character::SetDefense(int defense)
{
    Character::defense = defense;
}
void Character::SetAgility(int agility)
{
    Character::agility = agility;
}
int Character::DealDamage()
{
    return (GetStrength());
}
void Character::TakeDamage(int damageReceived)
{
    int damageAfterDefense = damageReceived - GetDefense();
    if (damageAfterDefense < 1)
    {
        damageAfterDefense = 1;
    }
    // Prevent "Overkill" damage
    if (GetHitPoints() - damageAfterDefense < 0)
    {
        SetHitPoints(0);
    }
    else
    {
        // Update the player hit points
        SetHitPoints((GetHitPoints() - damageAfterDefense));
    }
}
