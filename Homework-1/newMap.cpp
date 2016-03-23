//
//  newMap.cpp
//  CS32Homework1
//
//  Created by Monil Patel on 1/18/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#include "newMap.h"

Map::Map()
{
    nsize=0;
    maxSize=DEFAULT_MAX_ITEMS;
    keys=new KeyValue[maxSize];
}
Map::Map(int s)
{
    if (s<0)
    {
        std::cout<<"Negative numbers are not allowed.";
        exit(0);
    }
    nsize=0;
    maxSize=s;
    keys=new KeyValue[maxSize];
}
// Destructor
Map::~Map()
{
    delete []keys;
}
// Copy Constructor
Map::Map(const Map & mp)
{
    maxSize=mp.maxSize;
    nsize=0;
    keys=new KeyValue[maxSize];
    
    for (int i =0; i<mp.nsize; i++)
    {
        KeyType k;
        ValueType v;
        mp.get(i, k, v);
        insert(k,v);
    }
}
// Assignment Operator
Map& Map:: operator=(const Map &mp)
{
    if (&mp==this)
    {
        return *this;
    }
    
    delete [] keys;
    nsize=0;
    maxSize=mp.maxSize;
    keys=new KeyValue[mp.maxSize];
    
    for (int i =0; i<mp.nsize; i++)
    {
        KeyType k;
        ValueType v;
        mp.get(i, k, v);
        insert(k,v);
    }
    return *this;
}
// Return true if the map is empty, otherwise false.
bool Map::empty() const
{
    if (nsize==0) // If Map is empty
    {
        return true;
    }
    return false;
}
// Return the number of key/value pairs in the map.
int Map::size() const
{
    return nsize;
}
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).
bool Map::insert(const KeyType& key, const ValueType& value)
{
    if (nsize>=maxSize)
    {
        return false;
    }
    
    for (int i = 0; i<nsize; i++)
    {
        if(keys[i].m_key==key)
        {
            return false;
        }
    }
    keys[nsize].m_key=key;
    keys[nsize].m_value=value;
    nsize++;
    return true;
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
bool Map::update(const KeyType& key, const ValueType& value)
{
    for (int i=0; i<nsize; i++)
    {
        if (keys[i].m_key==key)
        {
            keys[i].m_value=value;
            return true;
        }
    }
    return false;
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    if (update(key, value) || insert(key,value))
    {
        return true;
    }
    return false;
}
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
bool Map::erase(const KeyType& key)
{
    for (int i=0; i<nsize-1; i++)
    {
        if (keys[i].m_key==key)
        {
            KeyValue temp=keys[i];
            keys[i]=keys[nsize-1];
            keys[nsize-1]=temp;
            
            nsize--;
            return true;
        }
    }
    return false;
}
// Return true if key is equal to a key currently in the map, otherwise
// false.
bool Map::contains (const KeyType& key) const
{
    for (int i=0; i<nsize; i++)
    {
        if (keys[i].m_key==key)
        {
            return true;
        }
    }
    return false;
}
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
bool Map::get(const KeyType& key, ValueType& value) const
{
    for (int i=0; i<nsize; i++)
    {
        if (keys[i].m_key==key)
        {
            value=keys[i].m_value;
            return true;
        }
    }
    return false;
}
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)
bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i>=0 && i<nsize)
    {
        key=keys[i].m_key;
        value=keys[i].m_value;
        return true;
    }
    return false;
}
// Exchange the contents of this map with the other one.
void Map::swap(Map& other)
{
    Map temp=*this;
    *this=other;
    other=temp;
}
void Map::dump()const
{
    for (int i=0; i<nsize; i++)
    {
        std::cerr<<keys[i].m_key<< "        "<<keys[i].m_value<<std::endl;
    }
}