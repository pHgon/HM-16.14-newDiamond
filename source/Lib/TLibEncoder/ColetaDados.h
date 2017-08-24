/* 
 * File:   ColetaDados.h
 * Author: mateuswn
 *
 * Created on 24 de Agosto de 2015, 16:08
 */

#include <string>
#include <stdio.h>
#include <sstream>
#include "../TLibCommon/TComMv.h"

#define	COLETADADOS_H 1

class ColetaDados {
public:
    ColetaDados();
    static void incrementaBlocosCalculados();
    static int getBlocosCalculados();
    static void resetBlocosCalculados();
    static void setInter();
    static void setFalse();
    static bool isInter();
    static void salvaPartIndex(int x);
    static int getPartIndex();
    static FILE* getFile();
    static void iniciaArquivo(std::string sequence, Double qp);
    static int getStep(int bestX, int bestY);
    static int getPred(int bestX, int bestY);
    static int getRaster();
    static void setRaster(int x);
    static int getRefinement();
    static void setRefinement(int x);
    static void setRefinementLevel();
    static void setFirstLevel();
    static void resetRefinementLevel();
    static void resetFirstLevel();
    static int getRefinementLevel();
    static int getFirstLevel();
    static TComMv& getMv(int x); // 0 = pred; 1 = first; 2 = raster; 3 = refinement;
    static TComMv& getPredMv(int x); // 0 = Median; 1 = Zero; 2 = Integer;
    static void setTotalLevel(int x);
    static void resetTotalLevel();
    static int getTotalLevel();
    static void setMaxLevel(int x);
    static int getMaxLevel();
    static void setIteration();
    static void resetIteration();
    static int getIteration();
    static void setTamWidth(int x);
    static int getTamWidth();
    static void setTamHeight(int x);
    static int getTamHeight();
    static void setQP(int x);
    static int getQP();
    static void incrementaNumPred ();
    static int getNumPred ();
    static void incrementaNumFirst ();
    static int getNumFirst ();
    static void incrementaNumRaster ();
    static int getNumRaster ();
    static void incrementaNumRefixFirst ();
    static int getNumRefixFirst ();
    static void incrementaNumRefixRaster ();
    static int getNumRefixRaster ();
    static int getNumTotal ();
    static void setPredictorSAD(unsigned int x);
    static unsigned int getPredictorSAD();
    static void setFirstSAD(unsigned int x);
    static unsigned int getFirstSAD();
    static void setRasterSAD(unsigned int x);
    static unsigned int getRasterSAD();
    static void setBestDistance(int x);
    static int getBestDistance();
    static unsigned int getRdCostPred();
    static void setRdCostPred(unsigned int x);
    static unsigned int getRdCostFirst();
    static void setRdCostFirst(unsigned int x);
    static unsigned int getRdCostRaster();
    static void setRdCostRaster(unsigned int x);
    static int calcDistEuclidiana(int x, int y);
    static int calcDistCityBlock(int x, int y);
    static int calcDistChessboard(int x, int y);
    static unsigned int getPartIdxTU();
    static void setPartIdxTU(unsigned int x);
    static void incrementaNumPUs(void);
    static unsigned int getNumPUs(void);
    static unsigned int getPartSize();
    static void setPartSize(unsigned int x);
    static void setVectorYuv(unsigned int x, unsigned int cod);
    static void closeVectorYuv(void);
    static void incrementaVectorIndex(void);
    static void resetVectorIndex(void);
    static int getVectorIndex();
    static void calculaMediaBloco (int cod);
    static int getMedia (int cod);
    static int getVariancia (int cod);
    static int getDesvio (int cod);
    static void setAtualXeY(int x, int y);
    static void resetAtualXeY();
    static int getAtualX();
    static int getAtualY();
    static void setSobel(int x, int i, int j);
    static void calculaSpatialIndex();
    static int getAtualSpatialIndex();
    static void setSkipMatriz (bool x);
    static bool getSkipMatriz ();
    static int xx, yy;
   
private:
    static int iBlocosCalculados;
    static int partIndex;
    static int step; // 0 = predictor; 1 = first search; 2 = raster; 3 = refinement;
    static int raster; //if raster occurs;
    static int refinement; // if refinement occurs;
    static int firstLevel;
    static int refinementLevel;
    static FILE* fp;
    static TComMv predictorMv;
    static TComMv firstMv;
    static TComMv rasterMv;
    static TComMv refinementMv;
    static TComMv medianMv;
    static TComMv integerMv;
    static int pred;
    static int maxLevel;
    static int iteration;
    static int totalLevel;
    
    static int tamWidth;
    static int tamHeight;
    static int QP;
    static int numPred;
    static int numFirst;
    static int numRaster;
    static int numRefixFirst;
    static int numRefixRaster;
    static unsigned int predictorSAD;
    static unsigned int firstSAD;
    static unsigned int rasterSAD;
    static int bestDistance;
    static unsigned int RdCostPred;
    static unsigned int RdCostFirst;
    static unsigned int RdCostRaster;
    static unsigned int partIdxTU;
    static unsigned int numPUs;
    static unsigned int partSize;
    static unsigned int vectorY [4097];
    static unsigned int vectorCb[4097];
    static unsigned int vectorCr[4097];
    static unsigned int vectorIndex;
    static double mediaBlocoY;
    static double mediaBlocoCb;
    static double mediaBlocoCr;
    static double varianciaBlocoY;
    static double varianciaBlocoCb;
    static double varianciaBlocoCr;
    static double desvioBlocoY;
    static double desvioBlocoCb;
    static double desvioBlocoCr;
    static int atualX;
    static int atualY;
    static int atualSpatialIndex;
    static int matrizCU[64][64];
    static int matrizSobelVer[64][64];
    static int matrizSobelHor[64][64];
    static bool skipMatriz;
    static void calculaMediaVetor (unsigned int *pointerVector, double *pointerMedia, double *pointerVariancia, double *pointerDesvio, unsigned int index);
};
