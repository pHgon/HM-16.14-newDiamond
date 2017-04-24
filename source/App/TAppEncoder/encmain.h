
//...........................código vladimir................................

//.................. variáveis globais para contagem de PUs ................

  extern int contador1;
  extern int contador2;
  extern bool luma; 

  extern int matriz_skip[8][4];// matriz para contar PUs Skip
  extern int matriz_inter[8][4];// matriz para contar PUs Inter
  extern int matriz_intra[8][4];// matriz para contar PUs Intra
  extern int codificacao;// para habilitar e desabilitar a contagem, evita contar a PU na compressão e também na codificação

//...........................código vladimir................................

  extern double complexidade;

  extern double tempo_pred;
  extern double tempo_first;
  extern double tempo_raster;
  extern double tempo_refinement;
  extern double tempo_tz;
  
  extern float QP;