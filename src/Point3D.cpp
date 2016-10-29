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

Point3D::Point3D(float x, float y, float z)
{
    this->setX(x);
    this->setY(y);
    this->setZ(z);
    this->mWeight = 1.0f;
}

Point3D::~Point3D()
{
    
}

void Point3D::setX(float& x)
{
    this->mPos.x = x;
}

void Point3D::setY(float& y)
{
    this->mPos.y = y;
}

void Point3D::setZ(float& z)
{
    this->mPos.z = z;
}

void Point3D::setWeight(float& w)
{
    this->mWeight = w;
}

void Point3D::setPosition(const ofPoint& p)
{
    mPos = p;
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

//const Point3D& Point3D::getPosition() const
//{
//    return *this;
//}
//
//Point3D  Point3D::operator+( const Point3D& pnt ) const
//{
//    return Point3D( mX+pnt.mX, mY+pnt.mY, mZ+pnt.mZ );
//}
//
//Point3D  Point3D::operator+( const float f ) const
//{
//    return Point3D( mX+f, mY+f, mZ+f );
//}
//
//Point3D& Point3D::operator+=( const Point3D& pnt )
//{
//    mX += pnt.mX;
//    mY += pnt.mY;
//    mZ += pnt.mZ;
//    return *this;
//}
//
//Point3D& Point3D::operator+=( const float f )
//{
//    mX += f;
//    mY += f;
//    mZ += f;
//    return *this;
//}
//
//Point3D  Point3D::operator-( const Point3D& pnt ) const
//{
//    return Point3D( mX-pnt.mX, mY-pnt.mY, mZ-pnt.mZ );
//}
//
//Point3D  Point3D::operator-( const float f ) const
//{
//    return Point3D( mX-f, mY-f, mZ-f );
//}
//
//Point3D& Point3D::operator-=( const Point3D& pnt )
//{
//    mX -= pnt.mX;
//    mY -= pnt.mY;
//    mZ -= pnt.mZ;
//}
//
//Point3D& Point3D::operator-=( const float f )
//{
//
//}
//
//Point3D  Point3D::operator*( const Point3D& vec ) const
//{
//
//}
//
//Point3D  Point3D::operator*( const float f ) const
//{
//
//}
//
//Point3D& Point3D::operator*=( const Point3D& vec )
//{
//
//}
//
//Point3D& Point3D::operator*=( const float f )
//{
//
//}
//
//Point3D  Point3D::operator/( const Point3D& vec ) const
//{
//
//}
//
//Point3D  Point3D::operator/( const float f ) const
//{
//
//}
//
//Point3D& Point3D::operator/=( const Point3D& vec )
//{
//
//}
//
//Point3D& Point3D::operator/=( const float f )
//{
//
//}
//

