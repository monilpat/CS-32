//
//  Map.h
//  CS32Project2
//
//  Created by Monil Patel on 1/19/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include <iostream>
#include <string>

typedef std::string KeyType;
typedef double ValueType;

class Map
{
public:
    Map();         // Create an empty map (i.e., one with no key/value pairs)
    
    Map(int size); // Creates a map of size
    
    ~Map(); // Destructs a map
    
    Map(const Map & mp); // Copy Constructor
    
    Map& operator=(const Map & mp); // Assignment Operator
    
    bool empty() const; // Return true if the map is empty, otherwise false.
    
    int size() const;   // Return the number of key/value pairs in the map.
    
    bool insert(const KeyType& key, const ValueType& value);
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map, or the map has a fixed
    // capacity and is full).
    
    bool update(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.
    
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // If key is not equal to any key currently in the map and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that the key is not already in the map and the map has a fixed
    // capacity and is full).
    
    bool erase(const KeyType& key);
    // If key is equal to a key currently in the map, remove the key/value
    // pair with that key from the map and return true.  Otherwise, make
    // no change to the map and return false.
    
    bool contains(const KeyType& key) const;
    // Return true if key is equal to a key currently in the map, otherwise
    // false.
    
    bool get(const KeyType& key, ValueType& value) const;
    // If key is equal to a key currently in the map, set value to the
    // value in the map that that key maps to, and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.
    
    bool get(int i, KeyType& key, ValueType& value) const;
    // If 0 <= i < size(), copy into the key and value parameters the
    // key and value of one of the key/value pairs in the map and return
    // true.  Otherwise, leave the key and value parameters unchanged and
    // return false.  (See below for details about this function.)
    
    void swap(Map& other);
    // Exchange the contents of this map with the other one.
    
    void dump()const;
    // Display the contents of each of the key/value pairs

private:
    int nsize;
    struct Node
    {
        KeyType m_key;
        ValueType m_value;
        Node * next;
        Node * prev;
        
    };
    Node * head;
};
bool combine(const Map& m1, const Map& m2, Map& result);
/* When this function returns, result must consist of pairs determined by these rules:
 If a key appears in exactly one of m1 and m2, then result must contain a pair consisting of that key and its corresponding value.
 If a key appears in both m1 and m2, with the same corresponding value in both, then result must contain a pair with that key and value.
 When this function returns, result must contain no pairs other than those required by these rules. (You must not assume result is empty when it is passed in to this function; it might not be.)
 If there exists a key that appears in both m1 and m2, but with different corresponding values, then this function returns false; if there is no key like this, the function returns true. Even if the function returns false, result must be constituted as defined by the above rules.
 */
void subtract(const Map& m1, const Map& m2, Map& result);
//When this function returns, result must contain a copy of all the pairs in m1 whose keys don't appear in m2; it must not contain any other pairs. (You must not assume result is empty when it is passed in to this function; it may not be.)
#endif