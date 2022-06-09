#ifndef EDGraphicMod_H
#define EDGraphicMod_H 1

#include <sstream>
#include <fstream>
#include <iostream>

#include "TString.h"
#include "TTree.h"

#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TPolyLine3D.h"
#include "TPolyLine.h"
#include "TGraph2D.h"
#include "TCanvas.h"
#include "TGraph.h"


#include "EDVariable.hh"
#include "EDReadOut.hh"

using namespace std;

class EDGraphicMod
{
public:
  EDGraphicMod();
  ~EDGraphicMod();

  void InitialProcess();

  void Draw3DFrame();
  void Draw3DCircles();
  void DrawFrame();
  void DrawCircles();
  void DataFill(Int_t);
  void graph2dfile(vector<vector<Double_t> > &vX,vector<vector<Double_t> > &vY, vector<vector<Double_t> > &vZ );
  void graphXY(vector<vector<Double_t> > &vX,vector<vector<Double_t> > &vY);
  void animatedXY(vector<vector<Double_t> > &vX, vector<vector<Double_t> > &vY);


  TCanvas *cGraph;
  TCanvas *cGraphXY;
  
  //  TCanvas *cAnimation; //If we want the animation, we can reuse cGraphXY

  TH3F *frame3d;

  TH2F *frame2d;

  Int_t ncol = 100;
  Int_t nrow = 200;



  static const int steps_cir = 45;

  static const int planes = 11;
  
  Double_t pi = 4*atan(1);

  Double_t x_cir[steps_cir], y_cir[steps_cir];
  Double_t x_cir_sm[steps_cir], y_cir_sm[steps_cir]; //small circle

  Double_t x_cir_3D[planes][steps_cir], y_cir_3D[planes][steps_cir], z_cir_3D[planes][steps_cir]; 
  Double_t x_cir_sm_3D[planes][steps_cir], y_cir_sm_3D[planes][steps_cir], z_cir_sm_3D[planes][steps_cir]; //small circle

  
  Double_t ar;//Will be used inside a loop BEWARE!!
  TPolyLine *OuterCircle;
  TPolyLine *InnerCircle;

  Int_t EventHits;
  Int_t nHits;


  std::vector<Double_t> xv ;
  std::vector<Double_t> yv ;
  std::vector<Double_t> zv ;

  std::vector<vector<Double_t> > x_vec ;
  std::vector<vector<Double_t> > y_vec ;
  std::vector<vector<Double_t> > z_vec ;



  Color_t color_wh[27]={kRed,     //0
			kViolet,
			kGreen-2,
			kOrange+7,
			kBlue,
			kOrange+7,//5
			kCyan+2,
			kSpring-5,
			kMagenta,
			kRed+3,
			kViolet-7,//10
			kGreen-6,
			kOrange+3,
			kBlue-2,
			kPink-9,
			kCyan+2, //15
			kYellow-6,
			kMagenta-9,
			kRed,
			kViolet,
			kGreen+4,//20
			kOrange,
			kBlue,
			kPink,
			kCyan+2,
			kSpring-5, //25
			kRed-2};


};

extern EDGraphicMod *GraphModule;

#endif
