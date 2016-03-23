//
//  WeightMap.cpp
//  CS32Homework1
//
//  Created by Monil Patel on 1/17/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#include "WeightMap.h"

WeightMap::WeightMap()
{
}
bool WeightMap::enroll(std::string name, double startWeight)
{
    if (startWeight>=0 && map.insert(name, startWeight))
    {
        return true;
    }
    return false;
}
// If a person with the given name is not currently in the map,
// there is room in the map, and the startWeight is not negative,
// add an entry for that person and weight and return true.
// Otherwise make no change to the map and return false.

double WeightMap::weight(std::string name) const
{
    double weight=0;
    const std::string  r=name;
    if (map.get(r,weight))
    {
        return weight;
    }
    return -1;
}
// If a person with the given name is in the map, return that
// person's weight; otherwise, return -1.

bool WeightMap::adjustWeight(std::string name, double amt)
{
    double wght=0;
    if (!map.contains(name) || (weight(name)+amt)<0)
    {
        return false;
    }
    if (map.get(name, wght))
    {
        wght+=amt;
        map.update(name, wght);
        
        return true;
    }
    return false;
}
// If no person with the given name is in the map or if
// weight() + amt is negative, make no change to the map and return
// false.  Otherwise, change the weight of the indicated person by
// the given amount and return true.  For example, if amt is -8.2,
// the person loses 8.2 pounds; if it's 3.7, the person gains 3.7
// pounds.
int WeightMap::size() const
{
    return map.size();
}
// Return the number of people in the WeightMap.

void WeightMap::print() const
{
     std::string name;
    double wght=0;
    for (int i=0; i<size(); i++)
    {
        map.get(i,name,wght);
        std::cout<<name<<" "<<wght<<std::endl;
    }
}
// Write to cout one line for every person in the map.  Each line
// has the person's name, followed by one space, followed by that
// person's weight.
