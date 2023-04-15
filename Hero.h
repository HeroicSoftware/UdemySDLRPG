#pragma once
#include "Character.h"
// Inherits from Character.h base class
class Hero : public Character
{
private:
    string heroName;
    string classType;

public:
    Hero();
    ~Hero();

    void SetClassType(string newClassType);
    string GetClassType();
    void SetName(string newName);
    string GetName();
    void AttackBoostModifier(int boostAmount);
    void DefenseBoostModifier(int boostAmount);
    void Heal(int healAmount);
    void SetupPlayerAttributes(int hp, int strength, int defense, int agility, string name, string playerClassType);
    void DisplayPlayerAttributes();
};
