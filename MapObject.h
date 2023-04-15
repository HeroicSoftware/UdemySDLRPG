#pragma once

/*
1 = hero
2 = door
3 = klog
4 = sham
5 = chest (A chest can look like a sham)
*/
enum OBJECT_TYPES
{
    HERO,
    KLOG,
    SHAM,
    DOOR,
    CHEST
};

class MapObject
{
public:
    int objectType;
    // Position on the map Grid
    int xPosition, yPosition;
    // When Not active, destroy the object
    bool isActive;
};
