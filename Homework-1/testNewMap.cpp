//
//  testNewMap.cpp
//  CS32Homework1
//
//  Created by Monil Patel on 1/18/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//
#include "newMap.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Map a(1000);   // a can hold at most 1000 key/value pairs
    Map b(5);      // b can hold at most 5 key/value pairs
    Map c;         // c can hold at most DEFAULT_MAX_ITEMS key/value pairs
    KeyType k[6] = { "A","B","C","D","E","F"};
    ValueType v  = 5;
    
    // No failures inserting pairs with 5 distinct keys into b
    for (int n = 0; n < 5; n++)
        assert(b.insert(k[n], v));
   
    // Failure if we try to insert a pair with a sixth distinct key into b
    assert(!b.insert(k[5], v));
    
    // When two Maps' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    
    assert(!a.insert(k[5], v)  &&  b.insert(k[5], v));
}
int main()
{
    test();
    cout << "Passed all tests" << endl;
}
