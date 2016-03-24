//
//  DiskMultiMap.h
//  CS32Project4Warmup
//
//  Created by Monil Patel on 3/5/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#ifndef DISKMULTIMAP_H_
#define DISKMULTIMAP_H_

#include "BinaryFile.h"
#include "MultiMapTuple.h"
#include <functional>

class DiskMultiMap
{
public:
    
    class Iterator
    {
    public:
        Iterator()
        {}
        bool isValid() const
        {
            return m_isValid;
        }
        // My defined constructor
        Iterator(string firstKey, long valOfRootNode,DiskMultiMap * diskMmap)
        {
            Node firstNode;
            diskMmap->m_file.read(firstNode, valOfRootNode);
            
            m_addOfFirst=valOfRootNode;
            
            m_mapTuple.context=firstNode.m_context;
            m_mapTuple.value=firstNode.m_value;
            m_mapTuple.key=firstKey;
            
            m_map=diskMmap;
        }
        // You may add additional constructors
        Iterator& operator++()
        {
            if (!isValid())
            {
                return *this;
            }
            
            Node first;
            m_map->m_file.read(first, m_addOfFirst);
            if (first.next==-1)
            {
                m_isValid=false;
                return *this;
            }
            
            Node second;
            m_map->m_file.read(second, first.next);
            
            bool compareKey=strcmp(second.m_key, first.m_key)==0;
            if (compareKey)
            {
                m_map->m_file.read(first, m_addOfFirst);
                m_mapTuple.key=second.m_key;
                m_mapTuple.value=second.m_value;
                m_mapTuple.context=second.m_context;
                return *this;
            }
    
            Node third;

            for (;;)
            {
                m_map->m_file.read(third, first.next);
                
                 bool compareKeyAgain=strcmp(third.m_key, first.m_key)==0;
                
                if (compareKeyAgain)
                {
                    m_map->m_file.read(second, second.next);
                }
                else
                {
                    m_addOfFirst=first.next;
                    m_mapTuple.key=third.m_key;
                    m_mapTuple.value=third.m_value;
                    m_mapTuple.context=third.m_context;
                    break;
                }
            }
               return *this;
        }
        MultiMapTuple operator*()
        {
            return m_mapTuple;
        }

    private:
        DiskMultiMap * m_map;
        long m_addOfFirst;
        bool m_isValid;
        MultiMapTuple m_mapTuple;
        // Your private member declarations will go here
    };
    
    DiskMultiMap();
    ~DiskMultiMap();
    bool createNew(const std::string& filename, unsigned int numBuckets);
    bool openExisting(const std::string& filename);
    void close();
    bool insert(const std::string& key, const std::string& value, const std::string& context);
    Iterator search(const std::string& key);
    int erase(const std::string& key, const std::string& value, const std::string& context);
    
private:
    
    BinaryFile m_file;
    unsigned long hashFunc(const std::string data)
    {
        std::hash<std::string> str_hash;
        unsigned long hashValue=str_hash(data);
        return hashValue%head.m_Buckets;
    }
    struct Node
    {
        char m_context[121];
        char m_value[121];
        char m_key [121];
        long next;
    };
    struct Header
    {
        int m_Buckets;
        BinaryFile::Offset nextSpot;
    };
    Header head;
    // Inputs the bucket number and locates its corresponding memory
    long convertMemLoc(int val)
    {
        return val*sizeof(long)+sizeof(Header);
    }
};
#endif // DISKMULTIMAP_H_