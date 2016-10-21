//
//  Point3D.cpp
//  
//
//  Created by NAOYAIWAMOTO on 13/10/2016.
//
//

#include "Point3D.h"

using namespace Euclid;

Point3D::Point3D()
{
    this->mWeight = 1.0f;
}

Point3D::Point3D(const float& x, const float& y, const float& z)
{
    this->setX(x);
    this->setY(y);
    this->setZ(z);
    this->mWeight = 1.0f;
}

Point3D::Point3D(const int x, const int y, const int z)
{
    this->setX(x);
    this->setY(y);
    this->setZ(z);
    this->mWeight = 1.0f;
}

Point3D::~Point3D()
{
    
}

void Point3D::setX(const float& x)
{
    this->mPos.x = x;
}

void Point3D::setY(const float& y)
{
    this->mPos.y = y;
}

void Point3D::setZ(const float& z)
{
    this->mPos.z = z;
}

void Point3D::setWeight(const float& w)
{
    this->mWeight = w;
}

void Point3D::setPosition(const ofPoint& p)
{
    this->mPos = p;
}

const float& Point3D::getX() const
{
    return this->mPos.x;
}

const float& Point3D::getY() const
{
    return this->mPos.y;
}

const float& Point3D::getZ() const
{
    return this->mPos.z;
}

const float& Point3D::getWeight() const
{
    return this->mWeight;
}

const ofPoint& Point3D::getPosition() const
{
    return mPos;
}


