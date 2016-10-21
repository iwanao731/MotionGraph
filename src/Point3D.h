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
    Point3D(const float x, const float y, const float z);
    Point3D(const int x, const int y, const int z);
    ~Point3D();
    
    void setX(const float x) { this->mPos.x = x; }
    void setY(const float y) { this->mPos.y = y; }
    void setZ(const float z) { this->mPos.z = z; }
    void setWeight(const float w) { this->mWeight = w; }
    void setPosition(const ofPoint p) { this->mPos = p; }
    
    float getX() { return this->mPos.x; }
    float getY() { return this->mPos.y; }
    float getZ() { return this->mPos.z; }
    float getWeight() { return this->mWeight; }
    ofPoint getPosition() { return mPos; }
    
private:
    ofPoint mPos;
    float mWeight;
};

#endif /* defined(____Point3D__) */
