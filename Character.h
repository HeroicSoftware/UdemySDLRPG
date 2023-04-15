#pragma once
#include <iostream>
#include <string>
using namespace std;
class Character
{
protected:
    int hitPoints, maximumHitPoints, strength, defense, agility;

public:
    int GetAgility() const;
    int GetDefense() const;
    int GetHitPoints() const;
    int GetMaximumHitPoints() const;
    int GetStrength() const;
    void SetAgility(int agility);
    void SetDefense(int defense);
    void SetHitPoints(int hit_points);
    void SetMaximumHitPoints(int maximum_hit_points);
    void SetStrength(int strength);

public:
    Character();
    ~Character();
    void SetupCharacterAttributes(int hitPoints, int strength, int defense, int agility);
    void DisplayCharacterAttributes();
    void TakeDamage(int damageReceived);
    int DealDamage();
};
