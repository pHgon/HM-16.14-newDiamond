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
#include "../TLibCommon/TComPattern.h"
#include "TEncSearch.h"



#define	XPAULO_H 1

class xPaulo {
public:
    xPaulo();
    static void xTZDiamondSearch( const TComPattern*const  pcPatternKey,
                                  IntTZSearchStruct& rcStruct,
                                  const TComMv*const  pcMvSrchRngLT,
                                  const TComMv*const  pcMvSrchRngRB,
                                  const Int iStartX,
                                  const Int iStartY,
                                  const Int iDist,
                                  const Bool bCheckCornersAtDist1);
    
   
private:
    
};


-8   8

0    0

1

iTop =  -1
iBot =   1
iLeft = -1
iRigh =  1

LT = (-8,-8)
RB = ( 8, 8)

