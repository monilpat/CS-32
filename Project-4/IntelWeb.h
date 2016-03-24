//
//  IntelWeb.hpp
//  CS32Project4Warmup
//
//  Created by Monil Patel on 3/5/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#ifndef INTELWEB_H_
#define INTELWEB_H_

#include "InteractionTuple.h"
#include "DiskMultiMap.h"
#include <string>
#include <vector>
#include <map>
class IntelWeb
{
public:
    IntelWeb();
    ~IntelWeb();
    bool createNew(const std::string& filePrefix, unsigned int maxDataItems);
    bool openExisting(const std::string& filePrefix);
    void close();
    bool ingest(const std::string& telemetryFile);
    unsigned int crawl(const std::vector<std::string>& indicators,
                       unsigned int minPrevalenceToBeGood,
                       std::vector<std::string>& badEntitiesFound,
                       std::vector<InteractionTuple>& interactions
                       );
    bool purge(const std::string& entity);
    
private:
    DiskMultiMap toToFromMap;
    DiskMultiMap fromTotoMap;

    int findPrev(string entity)
    {
        int prevalence=0;
        
        DiskMultiMap::Iterator toToFromMapIterator=toToFromMap.search(entity);
        DiskMultiMap::Iterator fromToMapIterator=fromTotoMap.search(entity);
        
        for (;;)
        {
            if (toToFromMapIterator.isValid())
            {
                prevalence++;
                
                ++toToFromMapIterator;
            }
            else if (fromToMapIterator.isValid())
            {
                prevalence++;
                
                ++fromToMapIterator;
            }
            else
            {
                break;
            }
        }
        return prevalence;
    }
    bool foundMaliciousEntity(vector<string> found, string bad)
    {
        for (int i=0; i<found.size(); i++)
        {
            if (bad==found[i])
            {
                return true;
            }
        }
        return false;
    }
};

#endif // INTELWEB_H_
