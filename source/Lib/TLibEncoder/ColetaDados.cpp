/* 
 * File:   ColetaDados.cpp
 * Author: mateuswn
 * 
 * Created on 24 de Agosto de 2015, 16:08
 */

#include <cmath>

#include "ColetaDados.h"

int ColetaDados::iBlocosCalculados;
int ColetaDados::partIndex;
int ColetaDados::step; // 0 = predictor; 1 = first search; 2 = raster; 3 = refinement;
int ColetaDados::raster;
int ColetaDados::refinement;
FILE *ColetaDados::fp;
int ColetaDados::firstLevel;
int ColetaDados::refinementLevel;
TComMv ColetaDados::predictorMv;
TComMv ColetaDados::firstMv;
TComMv ColetaDados::rasterMv;
TComMv ColetaDados::refinementMv;
TComMv ColetaDados::medianMv;
TComMv ColetaDados::integerMv;
int ColetaDados::pred;
int ColetaDados::maxLevel;
int ColetaDados::iteration;
int ColetaDados::totalLevel;

int ColetaDados::tamWidth;
int ColetaDados::tamHeight;
int ColetaDados::QP;
int ColetaDados::numPred;
int ColetaDados::numFirst;
int ColetaDados::numRaster;
int ColetaDados::numRefixFirst;
int ColetaDados::numRefixRaster;
unsigned int ColetaDados::predictorSAD;
unsigned int ColetaDados::firstSAD;
unsigned int ColetaDados::rasterSAD;
int ColetaDados::bestDistance;
unsigned int ColetaDados::RdCostPred;
unsigned int ColetaDados::RdCostFirst;
unsigned int ColetaDados::RdCostRaster;
unsigned int ColetaDados::partIdxTU;
unsigned int ColetaDados::numPUs;
unsigned int ColetaDados::partSize;
unsigned int ColetaDados::vectorY [4097];
unsigned int ColetaDados::vectorCb[4097];
unsigned int ColetaDados::vectorCr[4097];
unsigned int ColetaDados::vectorIndex;
double ColetaDados::mediaBlocoY;
double ColetaDados::mediaBlocoCb;
double ColetaDados::mediaBlocoCr;
double ColetaDados::varianciaBlocoY;
double ColetaDados::varianciaBlocoCb;
double ColetaDados::varianciaBlocoCr;
double ColetaDados::desvioBlocoY;
double ColetaDados::desvioBlocoCb;
double ColetaDados::desvioBlocoCr;
int ColetaDados::atualX;
int ColetaDados::atualY;
int ColetaDados::matrizCU[64][64];
int ColetaDados::matrizSobelVer[64][64];
int ColetaDados::matrizSobelHor[64][64];
bool ColetaDados::skipMatriz;
int ColetaDados::atualSpatialIndex;
int ColetaDados::xx;
int ColetaDados::yy;
ColetaDados::ColetaDados() {
    refinement=0;
    raster=0;
    step=0;
    partIndex=0;
    iBlocosCalculados=0;
    fp=NULL;
    firstLevel=0;
    refinementLevel=0;
    predictorMv.setZero();
    firstMv.setZero();
    rasterMv.setZero();
    refinementMv.setZero();
    medianMv.setZero();
    integerMv.setZero();
    pred=0;
    maxLevel=0;
    iteration=0;
    totalLevel=0;
    tamWidth=0;
    tamHeight=0;
    QP=0;
    numPred=0;
    numFirst=0;
    numRaster=0;
    numRefixFirst=0;
    numRefixRaster=0;
    predictorSAD=0;
    firstSAD=0;
    rasterSAD=0;
    bestDistance=0;
    RdCostPred=0;
    RdCostFirst=0;
    RdCostRaster=0;
    partIdxTU=0;
    numPUs=0;
    partSize=0;
    vectorIndex=0;
    mediaBlocoY=0;
    mediaBlocoCb=0;
    mediaBlocoCr=0;
    varianciaBlocoY=0;
    varianciaBlocoCb=0;
    varianciaBlocoCr=0;
    desvioBlocoY=0;
    desvioBlocoCb=0;
    desvioBlocoCr=0;
    atualX=0;
    atualY=0;
    skipMatriz=true;
    atualSpatialIndex=0;
    xx=0;
    yy=0;
}
int ColetaDados::getBlocosCalculados(){
    return iBlocosCalculados;
}
void ColetaDados::incrementaBlocosCalculados(){
    iBlocosCalculados++;
}
void ColetaDados::resetBlocosCalculados(){
    iBlocosCalculados=0;
}
FILE* ColetaDados::getFile(){
    return fp;
}
void ColetaDados::iniciaArquivo(std::string sequence, Double qp){
    std::string file;
    std::string filename;
    std::ostringstream strs;
    strs << qp;
    std::string str = strs.str();
    file=sequence;
    int pos=file.find_last_of("/");
    filename=file.substr(pos+1,(file.length()-4)-(pos+1))+"_"+str+".out";
    fp=fopen(filename.c_str(),"w");
}
int ColetaDados::getPartIndex(){
    return partIndex;
}
void ColetaDados::salvaPartIndex(int x){
    partIndex=x;
}
int ColetaDados::getStep(int bestX, int bestY){
    TComMv bestMv;
    bestMv.set(bestX, bestY);
    if(refinementMv==bestMv)
        step=3;
    if(rasterMv==bestMv)
        step=2;
    if(firstMv==bestMv)
        step=1;
    if(predictorMv==bestMv)
        step=0;
    
    return step;
}
int ColetaDados::getPred(int bestX, int bestY){
    TComMv bestMv;
    bestMv.set(bestX, bestY);
    if(integerMv==bestMv)
        pred=2;
    if(TComMv(0,0)==bestMv)
        pred=1;
    if(medianMv==bestMv)
        pred=0;
    
    return pred;
}
int ColetaDados::getRaster(){
    return raster;
}
void ColetaDados::setRaster(int x){
    raster=x;
}
int ColetaDados::getRefinement(){
    return refinement;
}
void ColetaDados::setRefinement(int x){
    refinement=x;
}
void ColetaDados::setFirstLevel(){
    firstLevel++;
}
void ColetaDados::resetFirstLevel(){
    firstLevel=0;
}
int ColetaDados::getFirstLevel(){
    return firstLevel;
}
void ColetaDados::setRefinementLevel(){
    refinementLevel++;
}
int ColetaDados::getRefinementLevel(){
    return refinementLevel;
}
void ColetaDados::resetRefinementLevel(){
    refinementLevel=0;;
}
TComMv& ColetaDados::getMv(int x){
    switch(x){
        case 1:
        {
            return firstMv;
        }
        case 2:
        {   
            return rasterMv;
        }
        case 3:
        {
            return refinementMv;
        }
        default:
        {
            return predictorMv;
        }
    }
}
TComMv& ColetaDados::getPredMv(int x){
    switch(x){
        case 1:
        {
            return integerMv;
        }
        default:
        {
            return medianMv;
        }
    }
}
void ColetaDados::setTotalLevel(int x){
    totalLevel+=x;
}
void ColetaDados::resetTotalLevel(){
    totalLevel=0;
}
int ColetaDados::getTotalLevel(){
    return totalLevel;
}
void ColetaDados::setMaxLevel(int x){
    maxLevel=x;
}
int ColetaDados::getMaxLevel(){
    return maxLevel;
}
void ColetaDados::setIteration(){
    iteration++;
}
void ColetaDados::resetIteration(){
    iteration=0;
}
int ColetaDados::getIteration(){
    return iteration;
}

void ColetaDados::setTamWidth(int x){
    tamWidth=x;
}
int ColetaDados::getTamWidth(){
    return tamWidth;
}

void ColetaDados::setTamHeight(int x){
    tamHeight=x;
}
int ColetaDados::getTamHeight(){
    return tamHeight;
}

void ColetaDados::setQP(int x){
    QP=x;
}
int ColetaDados::getQP(){
    return QP;
}

void ColetaDados::incrementaNumPred (){
    numPred++;
}
int ColetaDados::getNumPred (){
    return numPred;
}
void ColetaDados::incrementaNumFirst (){
    numFirst++;
}
int ColetaDados::getNumFirst (){
    return numFirst;
}
void ColetaDados::incrementaNumRaster (){
    numRaster++;
}
int ColetaDados::getNumRaster (){
    return numRaster;
}
void ColetaDados::incrementaNumRefixFirst (){
    numRefixFirst++;
}
int ColetaDados::getNumRefixFirst (){
    return numRefixFirst;
}
void ColetaDados::incrementaNumRefixRaster (){
    numRefixRaster++;
}
int ColetaDados::getNumRefixRaster (){
    return numRefixRaster;
}

int ColetaDados::getNumTotal(){
    return (numPred+numFirst+numRaster+numRefixFirst+numRefixRaster);
}

void ColetaDados::setPredictorSAD(unsigned int x){
    predictorSAD = x;
}

unsigned int ColetaDados::getPredictorSAD(){
    return predictorSAD;
}

void ColetaDados::setFirstSAD(unsigned int x){
    firstSAD = x;
}

unsigned int ColetaDados::getFirstSAD(){
    return firstSAD;
}

void ColetaDados::setRasterSAD(unsigned int x){
    rasterSAD = x;
}

unsigned int ColetaDados::getRasterSAD(){
    return rasterSAD;
}

void ColetaDados::setBestDistance(int x){
    bestDistance = x;
}
int ColetaDados::getBestDistance(){
    return bestDistance;
}

void ColetaDados::setRdCostPred(unsigned int x){
    RdCostPred = x;
}

unsigned int ColetaDados::getRdCostPred(){
    return RdCostPred;
}

void ColetaDados::setRdCostFirst(unsigned int x){
    RdCostFirst = x;
}

unsigned int ColetaDados::getRdCostFirst(){
    return RdCostFirst;
}

void ColetaDados::setRdCostRaster(unsigned int x){
    RdCostRaster = x;
}

unsigned int ColetaDados::getRdCostRaster(){
    return RdCostRaster;
}

int ColetaDados::calcDistEuclidiana(int x, int y){
    return (int)sqrt(pow((double)x,2)+pow((double)y,2));
}

int ColetaDados::calcDistCityBlock(int x, int y){
    return abs(x)+abs(y);
}

int ColetaDados::calcDistChessboard(int x, int y){
    int a=abs(x);
    int b=abs(y);
    if (b>a)
        return b;
    else
        return a;
}

unsigned int ColetaDados::getPartIdxTU(){
    return partIdxTU;
}

void ColetaDados::setPartIdxTU(unsigned int x){
    partIdxTU = x;
}

void ColetaDados::incrementaNumPUs(void){
    numPUs++;
}
unsigned int ColetaDados::getNumPUs(void){
    return numPUs;
}

unsigned int ColetaDados::getPartSize(){
    return partSize;
}

void ColetaDados::setPartSize(unsigned int x){
    partSize = x;
}

void ColetaDados::setVectorYuv(unsigned int x, unsigned int cod){
    switch (cod){
        case 0:
            vectorY[vectorIndex] = x;
            break;
        case 1:
            vectorCb[vectorIndex] = x;
            break;
        case 2:
            vectorCr[vectorIndex] = x;
            break;
    }
}

void ColetaDados::closeVectorYuv(){
    vectorY[vectorIndex]  = -1;
    vectorCb[vectorIndex] = -1;
    vectorCr[vectorIndex] = -1;
}

void ColetaDados::incrementaVectorIndex(){
    vectorIndex++;
}

void ColetaDados::resetVectorIndex(){
    vectorIndex=0;
}

int ColetaDados::getVectorIndex(){
    return vectorIndex;
}

void ColetaDados::calculaMediaBloco(int cod){
    unsigned int *pointerVector;
    double *pointerMedia;
    double *pointerVariancia;
    double *pointerDesvio;
    switch(cod){
        case 0:
            pointerVector = vectorY;
            mediaBlocoY = 0;
            varianciaBlocoY = 0;
            desvioBlocoY = 0;
            pointerMedia = &mediaBlocoY;
            pointerVariancia = &varianciaBlocoY;
            pointerDesvio = &desvioBlocoY;
            break;
        case 1:
            pointerVector = vectorCb;
            mediaBlocoCb = 0;
            varianciaBlocoCb = 0;
            desvioBlocoCb = 0;
            pointerMedia = &mediaBlocoCb;
            pointerVariancia = &varianciaBlocoCb;
            pointerDesvio = &desvioBlocoCb;
            break;
        case 2:
            pointerVector = vectorCr;
            mediaBlocoCr = 0;
            varianciaBlocoCr = 0;
            desvioBlocoCr = 0;
            pointerMedia = &mediaBlocoCr;
            pointerVariancia = &varianciaBlocoCr;
            pointerDesvio = &desvioBlocoCr;
            break;
        default:
            pointerVector = NULL;
            pointerMedia = NULL;
            pointerVariancia = NULL;
            pointerDesvio = NULL;
            break;
    }
    calculaMediaVetor(pointerVector, pointerMedia, pointerVariancia, pointerDesvio, vectorIndex);
}

void ColetaDados::calculaMediaVetor (unsigned int *pointerVector, double *pointerMedia, double *pointerVariancia, double *pointerDesvio, unsigned int index){
    unsigned int i = 0;
    while (i < index ){
        *pointerMedia += (double)pointerVector[i]; 
        i++;
    }
    *pointerMedia = *pointerMedia/index;
    
    i = 0;
    while (i < index){
        *pointerVariancia = *pointerVariancia + pow(((double)pointerVector[i] - *pointerMedia), 2);
        i++;
    }
    *pointerVariancia = *pointerVariancia/index;
    *pointerDesvio = sqrt(*pointerVariancia);
    //printf("%.2f\n", *pointerVariancia);
}

int ColetaDados::getMedia (int cod){
    switch(cod){
        case 0:
            return (int)mediaBlocoY;
            break;
        case 1:
            return (int)mediaBlocoCb;
            break;
        case 2:
            return (int)mediaBlocoCr;
            break;
    }
    return -1;
}

int ColetaDados::getVariancia (int cod){
    switch(cod){
        case 0:
            return (int)varianciaBlocoY;
            break;
        case 1:
            return (int)varianciaBlocoCb;
            break;
        case 2:
            return (int)varianciaBlocoCr;
            break;
    }
    return -1;
}

int ColetaDados::getDesvio (int cod){
    switch(cod){
        case 0:
            return (int)desvioBlocoY;
            break;
        case 1:
            return (int)desvioBlocoCb;
            break;
        case 2:
            return (int)desvioBlocoCr;
            break;
    }
    return -1;
}

void ColetaDados::setAtualXeY(int x, int y){
    atualX=x;
    atualY=y;
}

void ColetaDados::resetAtualXeY(){
    atualX=0;
    atualY=0;
}

int ColetaDados::getAtualX(){
    return atualX;
}

int ColetaDados::getAtualY(){
    return atualY;
}

void ColetaDados::setSobel(int x, int i, int j){
    matrizCU[i][j] = x;
    //printf("%d\n", matrizCU[i][j]);
}

void ColetaDados::calculaSpatialIndex(){
    float index = 0;
    float aux;
    for(int i=1; i<64-1; i++){
        for(int j=1; j<64-1; j++){
            matrizSobelVer[i][j] = (1 * matrizCU[i-1][j-1]) +(0 * matrizCU[i-1][j]) + (-1 * matrizCU[i-1][j+1]) +
                             (2 * matrizCU[i][j-1])   +(0 * matrizCU[i][j])   + (-2 * matrizCU[i][j+1])   +
                             (1 * matrizCU[i+1][j-1]) +(0 * matrizCU[i+1][j]) + (-1 * matrizCU[i+1][j+1]);
            
            matrizSobelHor[i][j] = (1 * matrizCU[i-1][j-1])  +(2 * matrizCU[i-1][j]) + (1 * matrizCU[i-1][j+1]) +
                             (0 * matrizCU[i][j-1])    +(0 * matrizCU[i][j])   + (0 * matrizCU[i][j+1])   +
                             (-1 * matrizCU[i+1][j-1]) +(-2 * matrizCU[i+1][j]) + (-1 * matrizCU[i+1][j+1]);
        }
    }
    for(int i=1; i<64-1; i++){
        for(int j=1; j<64-1; j++){
            matrizCU[i][j] = sqrt(pow(matrizSobelVer[i][j], 2) + pow(matrizSobelHor[i][j], 2));
        }
    }

    int media=0;
    for(int i=1; i<7; i++){
        for(int j=1; j<7; j++){
            media+=matrizCU[i][j];
        }
    }
    media = media/3844;
    //printf("media: %d\n", media);
    for(int i=1; i<64-1; i++){
        for(int j=1; j<64-1; j++){
            aux = abs(matrizCU[i][j] - media);
            if (aux>index)
                index=aux;
        }
    }
    atualSpatialIndex=index;
//    return (int)index;
}

void ColetaDados::setSkipMatriz(bool x){
    skipMatriz=x;
}

bool ColetaDados::getSkipMatriz(){
    return skipMatriz;
}

int ColetaDados::getAtualSpatialIndex(){
    return atualSpatialIndex;
}