//
//  Point3D.h
//  
//
//  Created by NAOYAIWAMOTO on 13/10/2016.
//
//

#ifndef ____Point3D__
#define ____Point3D__

#include <stdio.h>
#include <ofMain.h>

class Point3D
{
public:
    Point3D();
    Point3D(const float& x, const float& y, const float& z);
    Point3D(const int x, const int y, const int z);
    ~Point3D();
    
    void setX(const float& x);
    void setY(const float& y);
    void setZ(const float& z);
    void setWeight(const float& w);
    void setPosition(const ofPoint& p);
    
    const float getX() const;
    const float getY() const;
    const float getZ() const;
    const float getWeight() const;
    const ofPoint getPosition() const;
    
private:
    ofPoint mPos;
    float mWeight;
};

#endif /* defined(____Point3D__) */
