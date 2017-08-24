/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2016, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file     encmain.cpp
    \brief    Encoder application main
*/

#include <time.h>
#include <iostream>
#include "TAppEncTop.h"
#include "TAppCommon/program_options_lite.h"

//! \ingroup TAppEncoder
//! \{

#include "../Lib/TLibCommon/Debug.h"



//...........................código vladimir..........................................

#include <stdio.h>
#include <stdlib.h>
#include "encmain.h"//minhas variáveis globais

// inicialização das globais

int matriz_skip[8][4]={{0}};
int matriz_inter[8][4]={{0}};
int matriz_intra[8][4]={{0}};
int codificacao=0;
double complexidade=0;
int vetor[22]={0};

double tempo_pred=0;
double tempo_first=0;
double tempo_raster=0;
double tempo_refinement=0;
double tempo_tz=0;

//...........................código vladimir..........................................



// ====================================================================================================================
// Main function
// ====================================================================================================================

int main(int argc, char* argv[])
{
  TAppEncTop  cTAppEncTop;


  //...........................código vladimir........................................

  const char *nome_particao[8] = {"0(2Nx2N)","1(2NxN) ","2(Nx2N) ","3(NxN)  "
                                  ,"4(2NxnU)","5(2NxnD)","6(nLx2N)","7(nRx2N)"};

  printf("\n***** Codificação da Sequência de Vídeo *****\n");
 
  //...........................código vladimir........................................


  // print information
  fprintf( stdout, "\n" );
  fprintf( stdout, "HM software: Encoder Version [%s] (including RExt)", NV_VERSION );
  fprintf( stdout, NVM_ONOS );
  fprintf( stdout, NVM_COMPILEDBY );
  fprintf( stdout, NVM_BITS );
  fprintf( stdout, "\n\n" );

  // create application encoder class
  cTAppEncTop.create();

  // parse configuration
  try
  {
    if(!cTAppEncTop.parseCfg( argc, argv ))
    {
      cTAppEncTop.destroy();
#if ENVIRONMENT_VARIABLE_DEBUG_AND_TEST
      EnvVar::printEnvVar();
#endif
      return 1;
    }
  }
  catch (df::program_options_lite::ParseFailure &e)
  {
    std::cerr << "Error parsing option \""<< e.arg <<"\" with argument \""<< e.val <<"\"." << std::endl;
    return 1;
  }

#if PRINT_MACRO_VALUES
  printMacroSettings();
#endif

#if ENVIRONMENT_VARIABLE_DEBUG_AND_TEST
  EnvVar::printEnvVarInUse();
#endif

  // starting time
  Double dResult;
  clock_t lBefore = clock();

  // call encoding function
  cTAppEncTop.encode();

  // ending time
  dResult = (Double)(clock()-lBefore) / CLOCKS_PER_SEC;
  printf("\n Total Time: %12.3f sec.\n", dResult);


  //...........................código vladimir........................................
  // Gera relatório de saída com a quantidade de PUs

  // Modo Intra

  printf("\n***** Avaliação dos tamanhos de partição mais selecionados durante a codificação no MODO INTRA *****");
  printf("\n\t\tProfundidade");
  printf("\nPartição\t0(N=32)\t\t1(N=16)\t\t2(N=8)\t\t3(N=4)\n----------------------------------------------------------------------");
  for (int particao=0; particao<=7; particao ++)
  { 
    printf("\n%s\t", nome_particao[particao]);  
    for(int profundidade=0; profundidade<=3;profundidade ++)
      printf("%i\t\t",matriz_intra[particao][profundidade]);
  }

// Modo Inter

  printf("\n\n***** Avaliação dos tamanhos de partição mais selecionados durante a codificação no MODO INTER *****");  
  printf("\n\t\tProfundidade");
  printf("\nPartição\t0(N=32)\t\t1(N=16)\t\t2(N=8)\t\t3(N=4)\n----------------------------------------------------------------------");
  for (int particao=0; particao<=7; particao ++)
  { 
    printf("\n%s\t", nome_particao[particao]);  
    for(int profundidade=0; profundidade<=3;profundidade ++)
      printf("%i\t\t",matriz_inter[particao][profundidade]);
  }

//Modo Skip

  printf("\n\n***** Avaliação dos tamanhos de partição mais selecionados durante a codificação no MODO SKIP *****");  
  printf("\n\t\tProfundidade");
  printf("\nPartição\t0(N=32)\t\t1(N=16)\t\t2(N=8)\t\t3(N=4)\n----------------------------------------------------------------------");
  for (int particao=0; particao<=7; particao ++)
  { 
    printf("\n%s\t", nome_particao[particao]);  
    for(int profundidade=0; profundidade<=3;profundidade ++)
      printf("%i\t\t",matriz_skip[particao][profundidade]);
  }
  
  printf("\n\n****** Sequência Analisada com Sucesso *****\n"); 

  printf("\n\n****** TEMPOS *****\n");  
  printf("Tempo Predction: %f\n", tempo_pred);
  printf("Tempo First: %f\n", tempo_first);
  printf("Tempo Raster: %f\n", tempo_raster);
  printf("Tempo Refinement: %f\n", tempo_refinement);
  printf("Tempo TZ: %f\n", tempo_tz);

  double aux = tempo_pred+tempo_first+tempo_raster+tempo_refinement;
  printf("TEMPO TOTAL: %f\n", aux);

//...........................código vladimir........................................




  // destroy application encoder class
  cTAppEncTop.destroy();

  return 0;
}

//! \}
