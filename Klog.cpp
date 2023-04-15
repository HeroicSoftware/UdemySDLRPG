#include "Klog.h"

Klog::Klog()
{
    SetupCharacterAttributes(10, 4, 2, 5);
}

Klog::~Klog()
{
}

string Klog::GetName() const
{
    return "Klog";
}

void Klog::MakeDeathNoise() const
{
    std::cout << "The Klog let's an unsettling noise. It fleshy body stops moving. It is certainly dead." << endl;
}
