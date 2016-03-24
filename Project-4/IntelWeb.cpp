//
//  IntelWeb.cpp
//  CS32Project4Warmup
//
//  Created by Monil Patel on 3/5/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#include "IntelWeb.h"
#include <iostream> // needed for any I/O
#include <fstream>  // needed in addition to <iostream> for file I/O
#include <sstream>  // needed in addition to <iostream> for string stream I/O
#include <map>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
using namespace std;

IntelWeb::IntelWeb()
{}

IntelWeb::~IntelWeb()
{
    close();
}

bool IntelWeb::createNew(const std::string &filePrefix, unsigned int maxDataItems)
{
    close();
    int numBuckets=maxDataItems/.70;
        if(!toToFromMap.createNew(filePrefix+"ForwardsMap", numBuckets))
        {
            return false;
        }
        if (!fromTotoMap.createNew(filePrefix+"BackwardsMap", numBuckets))
        {
            return false;
        }
    return true;
}

bool IntelWeb::openExisting(const std::string &filePrefix)
{
    close();
    if (!toToFromMap.openExisting(filePrefix+"ForwardsMap"))
    {
        return false;
    }
    if (!fromTotoMap.openExisting(filePrefix+"BackwardsMap"))
    {
        return false;
    }
    return true;
}

void IntelWeb::close()
{
    toToFromMap.close();
    fromTotoMap.close();
}

bool IntelWeb::ingest(const std::string &telemetryFile)
{
    ifstream inf(telemetryFile);
    		  // Test for failure to open
        if ( ! inf)
        {
            cout << "Cannot open expenses file!" << endl;
            return 1;
        }
    		  // This will hold the telemetry 3 different strings using old architecture.

        string line;
        while (getline(inf, line))
        {
            // To extract the information from the line, we'll
            // create an input stringstream from it, which acts
            // like a source of input for operator>>
            istringstream iss(line);
    
            string value,key,context;
                    if ( ! (iss >> context >> key>> value))
                    {
                        cout << "Ignoring badly-formatted input line: " << line << endl;
                        continue;
                    }
           
                    char dummy;
                    if (iss >> dummy) // succeeds if there a non-whitespace char
                        cout << "Ignoring extra data in line: " << line << endl;
            
                    // Add key value contest to expenses map
            
            toToFromMap.insert(key, value, context);
            fromTotoMap.insert(value, key, context);
            
        }
    return 0;
}
unsigned int IntelWeb:: crawl(const std::vector<std::string>& indicators,unsigned int minPrevalenceToBeGood, std::vector<std::string>& badEntitiesFound, std::vector<InteractionTuple>& badInteractions)
{
    badEntitiesFound.clear();
    badInteractions.clear();
    // Make sure that the two items are empty regardless of what is passed in.
    
    // Next need to do breadth first search
    std::vector<string> maliciousEntitiesFound;
    queue<string> maliciousEntities;
    
    for (int i=0; i<indicators.size(); i++)
    {
        maliciousEntities.push(indicators.at(i));
    }
    while (!maliciousEntities.empty())
    {
        if (findPrev(maliciousEntities.front())<minPrevalenceToBeGood && foundMaliciousEntity(maliciousEntitiesFound,maliciousEntities.front()))
        {
            maliciousEntitiesFound.push_back(maliciousEntities.front());
        }
        maliciousEntities.pop();
        
        DiskMultiMap::Iterator toToFromMapIterator=toToFromMap.search(maliciousEntities.front());
        while (foundMaliciousEntity(maliciousEntitiesFound,maliciousEntities.front()) && toToFromMapIterator.isValid())
        {
            const InteractionTuple temp=InteractionTuple((*toToFromMapIterator).key, (*toToFromMapIterator).value, (*toToFromMapIterator).context);
            
            maliciousEntities.push(temp.from);
            badInteractions.push_back(temp);
            maliciousEntitiesFound.push_back(temp.from);
            
            ++toToFromMapIterator;
        }
        
        DiskMultiMap::Iterator FromtoToMapIterator=fromTotoMap.search(maliciousEntities.front());
        while (foundMaliciousEntity(maliciousEntitiesFound,maliciousEntities.front()) && FromtoToMapIterator.isValid())
        {
            const InteractionTuple temp=InteractionTuple((*FromtoToMapIterator).key, (*FromtoToMapIterator).value, (*FromtoToMapIterator).context);

            maliciousEntities.push(temp.from);
            badInteractions.push_back(temp);
            maliciousEntitiesFound.push_back(temp.from);
            
            ++toToFromMapIterator;
        }
    }
    return badEntitiesFound.size();
}

bool IntelWeb::purge(const std::string &entity)
{
    DiskMultiMap::Iterator itForwards=toToFromMap.search(entity);
    DiskMultiMap::Iterator itBackwards=fromTotoMap.search(entity);
    
    vector<DiskMultiMap::Iterator> listForwards;
    vector<DiskMultiMap::Iterator> listBackwards;
    
    if(!itForwards.isValid() || !itBackwards.isValid())
    {
        return false;
    }
    while (itForwards.isValid())
    {
        listForwards.push_back(itForwards);
        
        string tempKey=(*itForwards).key;
        string tempVal=(*itForwards).value;
        string tempContext=(*itForwards).context;

        ++itForwards;
        
        toToFromMap.erase(tempKey, tempVal, tempContext);
    }
    for (int i=0;i<listForwards.size();i++)
    {
        fromTotoMap.erase((*listForwards[i]).value, (*listForwards[i]).key, (*listForwards[i]).context);
    }
    
    while (itBackwards.isValid())
    {
        listBackwards.push_back(itBackwards);
        
        string tempKey=(*itBackwards).key;
        string tempVal=(*itBackwards).value;
        string tempContext=(*itBackwards).context;

        ++itBackwards;
        
        toToFromMap.erase(tempKey, tempVal, tempContext);
    }

    for (int i=0;i<listBackwards.size();i++)
    {
        toToFromMap.erase( (*listBackwards[i]).value, (*listBackwards[i]).key, (*listBackwards[i]).context);
    }
    return true;
}