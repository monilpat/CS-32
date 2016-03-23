//
//  Map.cpp
//  CS32Project2
//
//  Created by Monil Patel on 1/19/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//
#include "Map.h"
Map::Map()
{
    head=nullptr;
    nsize=0;
}
Map::~Map()
{
    Node * p=head;
    while (p!=nullptr)
    {
        Node *n=p->next;
        delete p;
        p=n; // deleted node points to current node
    }
    head=nullptr;
}
// Copy Constructor
Map::Map(const Map & mp)
{
    Node * other=mp.head;
    head = nullptr;
    nsize=0;
    while (other!=nullptr)
    {
        insert(other->m_key, other->m_value); //Fills new map
        other=other->next;
    }
}
// Assignment Operator
Map& Map:: operator=(const Map &mp)
{
    if (this!=&mp)
    {
        Map temp(mp);
        swap(temp); // Swaps the values so they are equal to each other
    }
    return *this;
}
// Return true if the map is empty, otherwise false.
bool Map::empty() const
{
    if (head==nullptr) // If Map is empty
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
    if (contains(key)) // If key is present, no need to insert
    {
        return false;
    }
    
    Node *p=new Node;
    p->m_key=key;
    p->m_value=value;
    p->next=head;
    p->prev=nullptr;
    
    if (head!=nullptr) // Valid Nodes present
    {
        head->prev=p;// Newly added node
    }
    head=p;
    nsize++; // increments the size
    return true;
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
//
bool Map::update(const KeyType& key, const ValueType& value)
{
    Node *p=head;
    while(p!=nullptr)
    {
        if (p->m_key==key)
        {
            p->m_value=value; // Changes value of the pair
            return true;
        }
        p=p->next;
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
    return true;
}
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
bool Map::erase(const KeyType& key)
{
    if (!contains(key))
    {
        return false;
    }
    Node *p=new Node;
    p=head;
    
    if (head==nullptr) // Empty list
    {
        return false;
    }
    if (p!=nullptr && p->next==nullptr)//If only one item in the list
    {
        head=nullptr;
        delete p;
        nsize--;
        return true;
    }
    if (p->prev==nullptr && p->next!=nullptr && p->m_key==key) // Deleting head pointer when more nodes afterwards
    {
        head=head->next;
        delete p;
        nsize--;
        return true;
    }
    while (p!=nullptr)
    {
        if (p->m_key==key)
        {
            break;
        }
        p=p->next;
    }
    if (p->next==nullptr) // Reaches end
    {
        if (p->m_key!=key)
        {
            return false; // Reaches end and key isnt present
        }
        else
        {
            p->prev->next=nullptr; // Deletes last node
            delete p;
            nsize--;
            return true;
        }
    }
    else // Node is present in the middle
    {
        p->prev->next=p->next;
        p->next->prev=p->prev;
        delete p;
        nsize--;
        return true;
    }
    return false;
     
   }
// Return true if key is equal to a key currently in the map, otherwise
// false.
bool Map::contains (const KeyType& key) const
{
    Node *p=head;
    while(p!=nullptr)
    {
        if (p->m_key==key)
        {
            return true;
        }
        p=p->next;
    }
    return false;
}
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
bool Map::get(const KeyType& key, ValueType& value) const
{
    Node *p=head;
    while(p!=nullptr)
    {
        if (p->m_key==key)
        {
            value=p->m_value; // Returns the value of the key
            return true;
        }
        p=p->next;
    }
    return false;
}
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    Node *p=head;
    if (i<0 || i>=size())
    {
        return false;
    }
    while(p!=nullptr)
    {
        for (int r=0; r<i; r++)
        {
            if (p->next!=nullptr) // Cycles through p until reaches the point desired
            {
                p=p->next;
            }
        }
        if (p!=nullptr)
        {
            key=p->m_key;
            value=p->m_value;
            return true;
        }
    }
    return false;
}
// Exchange the contents of this map with the other one.
//Another requirement is that as in Problem 5 of Homework 1, the number of statement executions when swapping two maps must be the same no matter how many key/value pairs are in the maps.
void Map::swap(Map& other)
{
    // Swaps the heads of the linked lists.
    Node * head1=other.head;
    other.head=this->head;
    this->head=head1;
    
    // Swaps the sizes of the linked lists
    int temp=nsize;
    nsize=other.nsize;
    other.nsize=temp;
}
void Map::dump()const
{
    Node *p=head;
    while (p!=nullptr)
    {
        std::cerr<<"Key: "<<p->m_key<<std::endl;
        std::cerr<<"Value: "<<p->m_value<<std::endl;
        p=p->next;
    }
}
/*
 When this function returns, result must consist of pairs determined by these rules:
 If a key appears in exactly one of m1 and m2, then result must contain a pair consisting of that key and its corresponding value.
 If a key appears in both m1 and m2, with the same corresponding value in both, then result must contain a pair with that key and value.
 When this function returns, result must contain no pairs other than those required by these rules. (You must not assume result is empty when it is passed in to this function; it might not be.)
 If there exists a key that appears in both m1 and m2, but with different corresponding values, then this function returns false; if there is no key like this, the function returns true. Even if the function returns false, result must be constituted as defined by the above rules.
 */
bool combine(const Map& m1, const Map& m2, Map& result)
{
    KeyType keyR,key1,key2;
    ValueType value1,value2;
    Map temp;
    bool retFalse=true;
    // Empties the result map
    if( m2.size() == 0 )
    {
        result = m1;
        return true;
    }
    else if( m1.size() == 0 )
    {
        result = m2;
        return true;
    }
    // Inserts if appears in both m1 and m2 and same value
    for (int i=0; i<m1.size(); i++)
    {
        m1.get(i, key1, value1);
        for (int j=0; j<m2.size(); j++)
        {
            m2.get(j, key2, value2);
            if (key1==key2)
            {
                if (value1==value2)
                {
                    temp.insert(key1, value1);
                    break;
                }
                else // Otherwise return set to be false;
                {
                    retFalse=false;
                    break;
                }
            }
        }
    }
        for (int t=0; t<m1.size(); t++)
        {
            m1.get(t, key1, value1);
            if (!temp.contains(key1)) // Adds values to temp from m1 that arenot already added
            {
                temp.insert(key1, value1);
            }
        }
        for (int j=0; j<m2.size(); j++)
        {
            m2.get(j, key2, value2);
            if(!temp.contains(key2))// Adds values to temp from m1 that arenot already added
            {
                temp.insert(key2, value2);
            }
        }
    for (int i=0; i<m1.size(); i++)
    {
        m1.get(i, key1, value1);
        for (int j=0; j<m2.size(); j++)
        {
            m2.get(j, key2, value2);
            if (key1==key2 && value1!=value2) // Gets rid of the duplicate keys with different values
            {
                temp.erase(key1);
            }
        }
    }
    result=temp;
    return retFalse;
}
/* 
 When this function returns, result must contain a copy of all the pairs in m1 whose keys don't appear in m2; it must not contain any other pairs. (You must not assume result is empty when it is passed in to this function; it may not be.)
  */
void subtract(const Map& m1, const Map& m2, Map& result)
{
    KeyType keyR,key1,key2;
    ValueType value1;
    Map temp;
    if (m1.empty()) // Cannot add to result
    {
        return;
    }
    for (int i=0; i<m1.size(); i++)
    {
        m1.get(i, key1, value1); // Adds all the pairs in m1 that aren't in m2
        if (m1.contains(key1)&& !m2.contains(key1))
        {
            temp.insert(key1, value1);
        }
    }
    result=temp;
}