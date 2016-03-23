//
//  main.cpp
//  Project2
//
//  Created by Samuel Donner on 1/24/16.
//  Copyright © 2016 Samuel Donner. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "Map.h"

using namespace std;

int main()
{
    //Assignment Operator
    
    Map m1,m2;
    m1.insert("Fred",123);
    m1.insert("Ethel",456);
    m1.insert("Lucy",789);
    
    m2.insert("Ricky",321);
    m2.insert("Lucy",789);
    m2=m1;
    m1.dump();
    m2.dump();
    
    // Combine Function Tester
    
     Map m1,m2,m3,m4,result;
     
     m1.insert("Fred",123);
     m1.insert("Ethel",456);
     m1.insert("Lucy",789);
     m1.insert("Lucy",233);
     
     m2.insert("Ricky",321);
     m2.insert("Lucy",789);
     m1.insert("Lucy",2333);
     
     
     assert(combine(m1, m2, result)); // If Same in both and same value
     result.dump();
     std::cerr<<std::endl;
     
     m3.insert("Lucy",654);
     m3.insert("Ricky",321);
     assert(!combine(m1, m3, result));// if same key but different value. Tests when result not empty when passed in
     result.dump();
     std::cerr<<std::endl;
     
     m4.insert("Kobe", 24);
     m4.insert("Lebron", 23);
     m4.insert("MJ",23);
     assert(combine(m1, m4, result)); // If no overlap in keys
     result.dump();
     combine(m1, m1, result); // To make sure aliasing doesnt make a difference in the result
     result.dump();
     
     combine(m2, m2, result); // To make sure aliasing doesnt make a difference in the result
     result.dump();
     
    
    
    // Subtract Function Tester
    
     Map m1,m2,m3,m4,result;
     
     m1.insert("Fred",123);
     m1.insert("Ethel",456);
     m1.insert("Lucy",789);
     
     m2.insert("Ethel",456);
     m2.insert("Lucy",789);
     m2.insert("Ricky",321);
     
     subtract(m1, m2, result); // To check if pairs exclusively present in m1 are in result.
     result.dump();
     
     subtract(m1, m1, result); // To make sure aliasing doesnt make a difference in the result
     result.dump();
     subtract(m2, m2, result); // To make sure aliasing doesnt make a difference in the result
     result.dump();
     
     m3.insert("Fred",123);
     m3.insert("Ethel",456); // Second one is not picked up
     m3.insert("Kanye",789);
     subtract(m1, m3, result); // If pairs are all different
     result.dump();
    
    // swap function
    
     Map m;
     m.insert("L",7);
     m.insert("G",7);
     m.insert("B",7);
     m.insert("T",7);
     
     Map l;
     l.insert("G",7);
     l.insert("O",7);
     l.insert("A",7);
     m.swap(l);
     assert(m.size()==3 && l.size()==4); // To see if sizes are swapped.
     m.dump();// To see if contents actually swapped
     std::cerr<<std::endl;
     l.dump(); // To see if contents actually swapped
     
    
    // 3 args get function
    
     Map m1;
     KeyType k;
     ValueType v;
     m1.insert("Fred",123);
     m1.insert("Ethel",456);
     m1.insert("Lucy",789);
     for (int i=0; i<m1.size(); i++)
     {
     m1.get(i, k, v);
     std::cerr<<"Key "<<k<<std::endl; // Checks to see if all values are retrieved.
     std::cerr<<"Value "<<v<<std::endl;
     }
     assert(!m1.get(5,k, v)); // If i greater than or equal tosize
     assert(!m1.get(-5,k, v)); // If i less than 0
     
    
    //Copy Constructor
    
     Map m1;
     m1.insert("Fred",123);
     m1.insert("Ethel",456);
     m1.insert("Lucy",789);
     Map m2=m1;
     assert(m1.size()==m2.size()); // makes sure that it copies correctly
     m2.dump(); // Makes sure that is copies correctly
    
    // insert function
    
     Map m;
     m.insert("the",3);
     assert(!m.insert("the",5)); // If key is already in the map
     assert(m.insert("food",7)); // If key is not already in the map
     
     Map l;
     assert(l.insert("cars",10)); // Checks to see if functions when map is empty and therefore linked list is empty
     m.dump();
     Map r;
     assert(r.insert("lebron",23)); // Insert when some are already present
     assert(r.insert("kobe",24));
     assert(r.insert("MJ",23));
     assert(r.insert("Steph",10));
     assert(r.insert("Iggy",10));
     r.dump();
    
    // erase function
    
     Map m;
     assert(!m.erase("the"));
     // Empty list so nothing should be deleted
     m.insert("Sam",7);
     assert(m.erase("Sam")); // Only one in list
     
     
     m.insert("case",7);
     m.insert("Ryan",7);
     m.insert("Dolev",7);
     m.insert("Jake",9);
     
     assert(m.erase("Dolev")); // Somewhere in the middle of the list
     assert(m.erase("Jake")); // End of the list
     assert(!m.erase("years")); // Key to be erased not in map
     m.dump();
     

    // get 2 args function test
    
     KeyType k;
     ValueType v;
     Map m; assert(!m.get("the",v)); // list is currently empty
     m.insert("the",7);
     assert(m.get("the",v)); // Key is currently in the list
     assert(v==7); // Checks to see if value is updated
     assert(!m.get("races",v)); // Key is not in the list
     
    
    // InsertOrUpdate function
    
     Map m; assert(m.insertOrUpdate("cool",19)); // Empty linked list
     m.insert("are",92);
     assert(m.insertOrUpdate("cool",25)); // Key already in map
     assert(m.insertOrUpdate("drake",25)); // Key not already in map
    
    // Update function
    
     Map m; m.insert("the",3);
     assert(m.update("the",7)); // Checks to see if the value is changed
     assert(!m.update("CoolAid",7)); // Key not in linked list
     m.dump();
    
    // Contains function
    
     Map m;
     assert(!m.contains("the")); // List is empty
     
     m.insert("the",3);
     assert(m.contains("the")); // Key is in the list
     assert(!m.contains("rare")); // Key is not in the list
     
    
    
}