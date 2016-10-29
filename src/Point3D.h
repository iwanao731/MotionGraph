//
//  Point3D.h
//
//
//  Created by NAOYAIWAMOTO on 13/10/2016.
//
//

#ifndef ____Euclid__Point3D____
#define ____Euclid__Point3D____

#include <stdio.h>
#include <ofMain.h>

namespace Euclid
{
    class Point3D
    {
    public:
        Point3D();
        Point3D(float x, float y, float z);
        ~Point3D();
        
        void setX(float& x);
        void setY(float& y);
        void setZ(float& z);
        void setWeight(float& w);
        void setPosition(const ofPoint& p);
        
        const float& getX() const;
        const float& getY() const;
        const float& getZ() const;
        const float& getWeight() const;
        const ofPoint& getPosition() const;
        
        // Future Work
//        const Point3D& getPosition() const;

//        Point3D  operator+( const Point3D& pnt ) const;
//        Point3D  operator+( const float f ) const;
//        Point3D& operator+=( const Point3D& pnt );
//        Point3D& operator+=( const float f );
//
//        Point3D  operator-( const Point3D& pnt ) const;
//        Point3D  operator-( const float f ) const;
//        Point3D& operator-=( const Point3D& pnt );
//        Point3D& operator-=( const float f );
//
//        Point3D  operator*( const Point3D& vec ) const;
//        Point3D  operator*( const float f ) const;
//        Point3D& operator*=( const Point3D& vec );
//        Point3D& operator*=( const float f );
//
//        Point3D  operator/( const Point3D& vec ) const;
//        Point3D  operator/( const float f ) const;
//        Point3D& operator/=( const Point3D& vec );
//        Point3D& operator/=( const float f );
        
    private:
        //float mX, mY, mZ;
        ofPoint mPos;
        float mWeight;
    };
}

#endif /* defined(____Euclid__Point3D____) */
