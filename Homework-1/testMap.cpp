//
//  testMap.cpp
//  CS32Homework1
//
//  Created by Monil Patel on 1/18/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#include "Map.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Map gpas;
    gpas.insert("Fred", 2.956);
    assert(!gpas.contains(""));
    gpas.insert("Ethel", 3.538);
    gpas.insert("", 4.000);
    gpas.insert("Lucy", 2.956);
    assert(gpas.contains(""));
    gpas.erase("Fred");
    assert(gpas.size() == 3  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
           gpas.contains(""));}
int main()
{
    test();
    cout << "Passed all tests" << endl;
}