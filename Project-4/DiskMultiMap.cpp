//
//  DiskMultiMap.cpp
//  CS32Project4Warmup
//
//  Created by Monil Patel on 3/5/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#ifndef MULTIMAPTUPLE_H_
#define MULTIMAPTUPLE_H_

#include "DiskMultiMap.h"
#include <cstring>

DiskMultiMap::~DiskMultiMap()
{
    close();
}

DiskMultiMap::DiskMultiMap()
{
}

bool DiskMultiMap::createNew(const std::string& filename, unsigned int numBuckets)
{
    close();
    
    head.m_Buckets=numBuckets;
    head.nextSpot=sizeof(Header)+sizeof(long)*numBuckets;
    
    if(!m_file.createNew(filename))
    {
        return false;
    }
    
    m_file.write(head,0); // Write the head at the beginning
    
    long positionForward=sizeof(Header);
    
    // Need to create the array
    for(int i=numBuckets;i>0;i--) 
    {
        long memLoc=-1;
        m_file.write(memLoc,positionForward);
        positionForward+=sizeof(int);
    }
    
    long nodePositionForward=sizeof(Header)+sizeof(long)*numBuckets;
    for (int i=numBuckets; i>0; i--)
    {
        Node addition;
        m_file.write(addition, nodePositionForward);
        nodePositionForward+=sizeof(Node);
    }
    return true;
}

bool DiskMultiMap::openExisting(const std::string& filename)
{
    close();
    if(!m_file.openExisting(filename))
    {
        return false;
    }
    return true;
}

void DiskMultiMap::close()
{
    if (m_file.isOpen())
    {
        m_file.close();
    }
}

bool DiskMultiMap::insert(const std::string& key, const std::string& value, const std::string& context)
{
    if (key.size()<=121)
    {
        long bucketNum=hashFunc(key);
        
        Node newNode;
        
        strcpy(newNode.m_key,key.c_str());
        strcpy(newNode.m_context,context.c_str());
        strcpy(newNode.m_value,value.c_str());
    
        long memLoc;
        long locationonDisk=convertMemLoc(bucketNum);
        m_file.read(memLoc,locationonDisk);
        
        bool result=false;
        
        if (memLoc!=-1)
        {
            long memLoc2;
            m_file.read(memLoc2, convertMemLoc(bucketNum));
            newNode.next=memLoc2;
            
            long locinDisk=convertMemLoc(bucketNum);
            m_file.write(head.nextSpot,locinDisk);
            
            result=m_file.write(newNode,head.nextSpot);
            
            if (result)
            {
                head.nextSpot+=sizeof(Node);
                return result;
            }
        }
        else
        {
            newNode.next=-1;
            long locinDisk=convertMemLoc(bucketNum);

            m_file.write(head.nextSpot, locinDisk);
            result=m_file.write(newNode,head.nextSpot);
                if (result)
                {
                    head.nextSpot+=sizeof(Node);
                    return result;
                }
        }
        return false;
    }
    else
    {
        return false;
    }
}
DiskMultiMap::Iterator DiskMultiMap::search(const std::string& key)
{
    long bucketNum=hashFunc(key);
    long locationToBeDeleted=convertMemLoc(bucketNum);
    
    long locationWeAreLookingFor=0;
    
    m_file.read(locationWeAreLookingFor, locationToBeDeleted);
    
    Node temp;
    
    m_file.read(temp, locationWeAreLookingFor);
    long anotherLocationWeAreLookingFor=locationWeAreLookingFor;
    
    int count =0;
    for (;;)
    {
        if(count==0 ||temp.next!=-1)
        {
            count++;
            m_file.read(temp,locationWeAreLookingFor);
            bool isSameKey=strcmp(temp.m_key, key.c_str())==0;
            
            if(isSameKey)
            {
                Iterator it=Iterator(key, anotherLocationWeAreLookingFor, this);
                return it;
            }
            anotherLocationWeAreLookingFor=locationWeAreLookingFor;
            locationWeAreLookingFor=temp.next; // Move it along
        }
        else
        {
            break;
        }
    }
    Iterator it=Iterator(key, -1, this);
    return it;
}

int DiskMultiMap::erase(const std::string& key, const std::string& value, const std::string& context)
{
    int num;
    int bucketNum=hashFunc(key);
    long locationToBeDeleted;
    long memLoc=convertMemLoc(bucketNum);
    
    m_file.read(locationToBeDeleted,memLoc);
    long temp=locationToBeDeleted;
    
    for (num=0;locationToBeDeleted!=-1;)
    {
        Node toBeAdded;
        m_file.read(toBeAdded,locationToBeDeleted);
        
        bool isKeySame=(strcmp(key.c_str(),toBeAdded.m_key)==0);
        bool isValueSame=(strcmp(value.c_str(),toBeAdded.m_value)==0);
        bool isContextSame=(strcmp(context.c_str(),toBeAdded.m_context)==0);
        
        if (isKeySame && isValueSame && isContextSame)
        {
            Node  anotherOne;
            m_file.read(anotherOne, temp);
            anotherOne.next=toBeAdded.next;
            num++;
        }
        temp=locationToBeDeleted;
        locationToBeDeleted=toBeAdded.next;
    }
    return num;
}
#endif // MULTIMAPTUPLE_H_