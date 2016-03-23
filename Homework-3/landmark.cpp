//
//  Landmark.cpp
//  CS32Homework3
//
//  Created by Monil Patel on 2/4/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#include <string>
#include <iostream>
using namespace std;

// Class Declarations
class Landmark
{
public:
    Landmark(string  s);
    
    string name() const;
    virtual string color() const;
    virtual string icon()const =0;
    
    // Destructor
    virtual ~Landmark();
    
private:
    string m_name;
    string m_color;
};


class Hotel: public Landmark
{
public:
    Hotel(string  l);
    ~Hotel();
    string icon()const;
};
class Restaurant: public Landmark
{
public:
    Restaurant( string  l, int cap);
    ~Restaurant();
    string icon()const;
private:
    int m_capacity;

};
class Hospital: public Landmark
{
public:
    Hospital( string  l);
    string icon()const;
    ~Hospital();
    string color() const;
};

// Class Implementations

//LANDMARK CLASS
Landmark::Landmark( string name)
{
    m_name=name;
}
 Landmark::~Landmark()
{
}
string Landmark:: name() const
{
    return m_name;
}
string Landmark:: color() const
{
    return "yellow";
}

// HOTEL CLASS
Hotel::Hotel( string l)
:Landmark(l)
{
}
Hotel::~Hotel()
{
    cout<<"Destroying the "<<"hotel "<<Landmark::name()<<"."<<endl;
}
string Hotel::icon() const
{
    return "bed";
}

//RESTAURANT CLASS
Restaurant::Restaurant( string l, int cap)
:Landmark(l)
{
    m_capacity=cap;
}
Restaurant::~Restaurant()
{
    cout<<"Destroying the "<<"restaurant "<<Landmark::name()<<"."<<endl;
}
 string Restaurant::icon() const
{
    if (m_capacity>40)
    {
        return "large knife/fork icon";
    }
    else
    {
        return "small knife/fork icon";
    }
}
// HOSPITAL CLASS
Hospital::Hospital( string l)
:Landmark(l)
{
}
Hospital::~Hospital()
{
    cout<<"Destroying the "<<"hospital "<<Landmark::name()<<"."<<endl;
}
string Hospital::color() const
{
    return "blue";
}
string Hospital::icon() const
{
    return "H";
}