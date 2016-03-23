//
//  testWeightMap.cpp
//  CS32Homework1
//
//  Created by Monil Patel on 1/18/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#include <stdio.h>
#include "WeightMap.h"
#include <iostream>
using namespace std;

int main()
{
    WeightMap w_map;
    w_map.enroll("Monil", 135);
    w_map.print();
};