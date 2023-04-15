#include "Hero.h"

Hero::Hero()
{
}

Hero::~Hero()
{
}

void Hero::SetClassType(string newClassType)
{
    this->classType = newClassType;
}

string Hero::GetClassType()
{
    return this->classType;
}

void Hero::SetName(string newName)
{
    this->heroName = newName;
}

string Hero::GetName()
{
    return (this->heroName);
}

void Hero::AttackBoostModifier(int boostAmount)
{
    SetStrength(GetStrength() + boostAmount);
}

void Hero::DefenseBoostModifier(int boostAmount)
{
    SetDefense(GetDefense() + boostAmount);
}

void Hero::Heal(int healAmount)
{
    int newHP = GetHitPoints() + healAmount;
    if (newHP > hitPoints)
    {
        SetHitPoints(GetMaximumHitPoints());
    }
    else
    {
        // Get the current HP and add healAmount
        SetHitPoints(newHP);
    }
}

void Hero::SetupPlayerAttributes(int hp, int strength, int defense, int agility, string name, string playerClassType)
{
    Character::SetupCharacterAttributes(hp, strength, defense, agility);
    this->SetName(name);
    this->SetClassType(playerClassType);
}

void Hero::DisplayPlayerAttributes()
{
    cout << "Name: " << heroName << endl;
    cout << "Class: " << classType << endl;
    cout << "HP: " << hitPoints << "/" << maximumHitPoints << endl;
    cout << "STR: " << strength << endl;
    cout << "DEF: " << defense << endl;
    cout << "AGL: " << agility << endl;
}