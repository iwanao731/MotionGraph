//
//  Map.cpp
//  
//
//  Created by NAOYAIWAMOTO on 10/10/2016.
//
//

#include "Map.h"

Map::Map()
{
    
}

Map::Map(const int nMotions)
{
    this->mNRelations = 0;
    this->mMaxRelations = nMotions * nMotions; /* * 2 */
    this->mDifferenceMap = new float **[this->mMaxRelations];
    this->mRelations =  new std::string *[this->mMaxRelations];
}

Map::~Map()
{
    
}

void Map::constructMap(std::vector<Motion> motions, const int nMotions)
{
    std::cout << "start comparing each frame" << endl;
    this->mMotions = motions;

    for( auto &m1 : mMotions ) {
        for( auto &m2 : mMotions ) {
            this->compareMotions(m1, m2);
        }
    }
    std::cout << "end comparing each frame" << endl;
}

// Compare between two motions;
void Map::compareMotions(Motion &m1, Motion &m2)
{
    float **map;
    
    this->mRelations[this->mNRelations] = new string [2];
    this->mRelations[this->mNRelations][0] = m1.getLabel();
    this->mRelations[this->mNRelations][1] = m2.getLabel();
    
    map = new float *[m1.getNFrames()];
    for(int i = 0 ; i < m1.getNFrames() ; i++) {
        map[i] = new float [m2.getNFrames()];
    }
    
    for(int i=0; i<m1.getNFrames(); i++) {
        Pose p1 = m1.getPose(i);
        for(int j=0; j<m2.getNFrames(); j++) {
            Pose p2 = m2.getPose(j);
            map[i][j] = this->comparePoses(p1, p2);
        }
    }
    
    // export posture error between two motion(m1 and m2) at each frame as .txt file
    // this->exportMapFile(map, m1, m2);

    this->mDifferenceMap[this->mNRelations] = map;
    this->mNRelations++;
}

void Map::saveImage(bool **BMap, float **map, Motion &m1, Motion &m2)
{
    int w = m1.getNFrames();
    int h = m2.getNFrames();
    
    float maxError = 0;
    for(int i=0; i<w; i++) {
        for(int j=0; j<h; j++) {
            if(map[i][j] > maxError)
                maxError = map[i][j];
        }
    }
    
    ofTexture texColor;
    ofPixels colorPixels;
    
    colorPixels.allocate(w,h,OF_PIXELS_RGB);
    for(int y=0; y<h; y++) {
        for(int x=0; x<w; x++) {
            if(BMap[x][y] == true)
                colorPixels.setColor(x, y, ofColor(255, 0, 0));
            else
                colorPixels.setColor(x, y, ofColor(255 - map[x][y] / maxError * 255));
        }
    }
    
    texColor.allocate(colorPixels);
    
    ofPixels pixels;
    texColor.readToPixels(pixels);
    
    ofImage image;
    image.setFromPixels(pixels);
    
    std::stringstream ss;
    ss << m1.getLabel() << "_" << m2.getLabel() << ".png";
    image.save(ss.str());
}


void Map::exportMapFile(float **map, Motion &m1, Motion &m2)
{
    std::stringstream ss;
    ss << m1.getLabel() << "_" << m2.getLabel() << ".txt";
 
    // using openFrameworks utility function
    ofFile file;
    std::string label = file.getAbsolutePath() + "/" + ss.str();
    
    std::ofstream ofs(label);
    if(!ofs) {
        std::cerr << "Failed open file" << std::endl;
        std::exit(1);
    }else{
        cout << "export... " << ss.str() << endl;
    }
    
    for(int i=0; i<m1.getNFrames(); i++) {
        for(int j=0; j<m2.getNFrames(); j++) {
            ofs << map[i][j] << " ";
        }
        ofs << endl;
    }
    ofs.close();
}

float Map::comparePoses(Pose &pose1, Pose &pose2)
{
    assert(pose1.getNPoints() == pose2.getNPoints());
    
    int nPoints = pose1.getNPoints();
    
    float A,B,C,D;
    A = B = C = D = 0.0f;
    
    float _x1 = 0.0f;
    float _x2 = 0.0f;
    float _z1 = 0.0f;
    float _z2 = 0.0f;
    
    for (int i=0; i<nPoints; i++) {
        _x1 += pose1.getPoint(i).getWeight() * pose1.getPoint(i).getX();
        _x2 += pose1.getPoint(i).getWeight() * pose2.getPoint(i).getX();
        _z1 += pose1.getPoint(i).getWeight() * pose1.getPoint(i).getZ();
        _z2 += pose1.getPoint(i).getWeight() * pose2.getPoint(i).getZ();
    }
    
    float w = 0.0f;
    for (int i=0; i<nPoints; i++) {
        w += pose1.getPoint(i).getWeight();
    }
    
    for (int i=0; i<nPoints; i++) {
        float x1 = pose1.getPoint(i).getX();
        float x2 = pose2.getPoint(i).getX();
        float z1 = pose1.getPoint(i).getZ();
        float z2 = pose2.getPoint(i).getZ();
        
        A += pose1.getPoint(i).getWeight() * (x1*z2 - x2*z1);
        B += 1.0f/w * (_x1*_z2 - _x2*_z1);
        C += pose1.getPoint(i).getWeight() * (x1*x2 + z1*z2);
        D += 1.0f/w * (_x1*_x2 + _z1*_z2);
    }
    
    float theta = atan( (A-B)/(C-D) );
    float x0 = 1.0f/w * (_x1 - _x2 * cos(theta) - _z2 * sin(theta));
    float z0 = 1.0f/w * (_z1 + _x2 * sin(theta) - _z2 * cos(theta));
    
    ofMatrix4x4 mat;
    mat.makeRotationMatrix(ofRadToDeg(theta), 0, 1, 0);
    mat.translate(x0, 0.0f, z0);
    
    float error = 0.0f;
    for (int i=0; i<nPoints; i++) {
        error += pose1.getPoint(i).getWeight() * (pose1.getPoint(i).getPosition() - (mat.getRotate() * pose2.getPoint(i).getPosition() + mat.getTranslation())).length();
    }
    return error;
}

int Map::getMinimums(const int level, std::vector<int> *m1, std::vector<int> *m2)
{
    int nPts = 0;
    int np1, np2;

    if(level >= this->mNRelations) return 0;
    
    this->mMotions[level].getNFrames();
    cout << "------" << endl;
    cout << this->getRelations(level, 0) << endl;
    cout << this->getRelations(level, 1) << endl;
    
    map<std::string, Motion> names;
    
    int i = 0;
    int index1, index2;
    
    for(auto m : mMotions) {
        if((this->getRelations(level, 0)) == m.getLabel()) {
            index1 = i;
        }
        
        if(this->getRelations(level, 1) == m.getLabel()) {
            index2 = i;
        }
        i++;
    }
    
    np1 = this->mMotions.at(index1).getNFrames();
    np2 = this->mMotions.at(index2).getNFrames();
    
    std::string s1 = this->getRelations(level, 0);
    std::string s2 = this->getRelations(level, 1);

#if 1
    bool **transPoint;
    transPoint = new bool *[np1];
    for(int i=0; i<np1; i++){
        transPoint[i] = new bool [np2];
        for(int j=0; j<np2; j++){
            if(this->mDifferenceMap[level][i][j] < this->mThreshold) {
                transPoint[i][j] = true;
            }else{
                transPoint[i][j] = false;
            }
        }
    }

    for(int i=0 ; i<np1; i++) {
        for(int j=0; j<np2; j++) {
            this->calcLocalMinimum(transPoint, level, i, j, this->mNSteps, np1, np2);
        }
    }
    
    for(int i=0 ; i<np1; i++) {
        for(int j=0; j<np2; j++) {
            if (transPoint[i][j] == true){
                m1->push_back(i);
                m2->push_back(j);
                //m2->push_back(j+this->mNSteps);
                nPts++;
            }
        }
    }
   
#else
    for(int i = 0 ; i < np1 - this->mNSteps ; i++) {
        for(int j = this->mNSteps ; j < np2 ; j++) {
            if(this->mDifferenceMap[level][i][j] < this->mThreshold) {
                if((i + this->mNSteps) < np1 && (j + this->mNSteps) < np2) {
                    //(np1 - i) >= this->nSteps && (np2 - j) >= this->nSteps ){
                    bool ok = true;
                    for(int l = 0 ; l < this->mNSteps && ok ; l++){
                        if(this->mDifferenceMap[level][i+l][j+l] >= this->mThreshold)
                            ok = false;
                    }
                    
                    if(ok){
                        m1->push_back(i);
                        m2->push_back(j+this->mNSteps);
                        nPts++;
                    }
                }
            }
        }
    }
    
#endif
    
    this->saveImage(transPoint, this->mDifferenceMap[level], this->mMotions.at(index1), this->mMotions.at(index2));
    
    cout << "correspondence point : " << m1->size() << "," << m2->size() << endl;

    return nPts;
}

void Map::calcLocalMinimum(bool **transPoint, const int motionIndex, const int i, const int j, const int range, const int sizeW, const int sizeH)
{
    if(transPoint[i][j] == true)
    {
        transPoint[i][j] = false;
        float value = mDifferenceMap[motionIndex][i][j];
        bool contin = false;
        int m, n;
        
        for (int k=i-range; k<i+range; k++) {
            for (int l=j-range; l<j+range; l++) {
                if(k >= 0 && k < sizeW && l >= 0 && l < sizeH) {
                    transPoint[k][l] = false;
                    if(this->mDifferenceMap[motionIndex][k][l] < value) {
                        value = this->mDifferenceMap[motionIndex][k][l];
                        m = k;
                        n = l;
                        contin = true;
                        transPoint[k][l] = false;
                    }
                }
            }
        }

        if(contin){
            transPoint[m][n] = true;
            this->calcLocalMinimum(transPoint, motionIndex, m, n, range, sizeW, sizeH);
        }else{
            transPoint[i][j] = true;
            return true;
        }
    }
}




