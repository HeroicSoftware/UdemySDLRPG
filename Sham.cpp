#include "Sham.h"

Sham::Sham()
{
    SetupCharacterAttributes(25, 6, 1, 2);
}

Sham::~Sham()
{
}

string Sham::GetName()
{
    return "Sham";
}
