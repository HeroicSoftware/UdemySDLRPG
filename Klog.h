#pragma once
#include "Character.h"
class Klog : public Character
{
public:
    Klog();
    ~Klog();
    string GetName() const;
    void MakeDeathNoise() const;
};
