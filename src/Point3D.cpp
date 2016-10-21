//
//  Point3D.cpp
//  
//
//  Created by NAOYAIWAMOTO on 13/10/2016.
//
//

#include "Point3D.h"

Point3D::Point3D()
{
    this->mWeight = 1.0f;
}

Point3D::Point3D(const float x, const float y, const float z)
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
