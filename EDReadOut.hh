#ifndef EDReadOut_H
#define EDReadOut_H 1

#include <sstream>
#include <fstream>
#include <iostream>

#include "TString.h"
#include "TTree.h"

#include "EDVariable.hh"


using namespace std;

class EDReadOut
{
public:
  EDReadOut();
  ~EDReadOut();


  void SBSRoot();
  void DigiRoot();

  TFile *file; 
  TTree *mTPCTree;

  TBranch *b_nHits;
  TBranch *b_xHits;
  TBranch *b_yHits;
  TBranch *b_zHits;  
  TBranch *b_pid;  
  TBranch *b_mid;

 // Declaration of leaf type
  int nHits;
  std::vector<Double_t> *xHits = 0;
  std::vector<Double_t> *yHits = 0;
  std::vector<Double_t> *zHits = 0;
  std::vector<Double_t> *pid = 0;
  std::vector<Double_t> *mid = 0;
  
  // std::vector<Double_t> xv ;
  // std::vector<Double_t> yv ;
  // std::vector<Double_t> zv ;

  // std::vector<vector<Double_t> > x_vec ;
  // std::vector<vector<Double_t> > y_vec ;
  // std::vector<vector<Double_t> > z_vec ;


};

extern EDReadOut *ReadOut;

#endif
