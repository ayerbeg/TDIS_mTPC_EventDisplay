#include <sstream>
#include <fstream>
using namespace std;
#include "TFile.h"
#include "EDVariable.hh"
#include "EDReadOut.hh"

EDReadOut::EDReadOut()
{
  cout << "<EDReadOut::EDReadOut>: Initializing." << endl;

  TString fileName = Variable->inputfile; // could be simplified

  cout<<"inputfile: "<< Variable -> inputfile<<endl;

  file = new TFile(fileName,"READ"); 

}

EDReadOut::~EDReadOut()
{
  cout << "<EDReadOut::~EDReadOut>: Finished" << endl;
}


// READOUT FROM G4SBS SIMULATION 
void EDReadOut::SBSRoot()
{

  mTPCTree = (TTree*)file->Get("T"); 
  if(!mTPCTree) return;


  //  NB: In the following replace "track" with the real branch name
  mTPCTree -> SetBranchAddress("SBS.mTPC.hit.nhits", &nHits, &b_nHits);
  mTPCTree -> SetBranchAddress("SBS.mTPC.hit.xhitg", &xHits, &b_xHits);
  mTPCTree -> SetBranchAddress("SBS.mTPC.hit.yhitg", &yHits, &b_yHits);
  mTPCTree -> SetBranchAddress("SBS.mTPC.hit.zhitg", &zHits, &b_zHits);

  mTPCTree -> SetBranchAddress("SBS.mTPC.hit.pid", &pid, &b_pid);
  mTPCTree -> SetBranchAddress("SBS.mTPC.hit.mid", &mid, &b_mid);

}


// READOUT FROM RACHEL DIGITIZED DATA CONVERTED TO ROOT
// THIS COULD BE CHANGED DEPENDING OF THE DATA STORED AND THE 
// NEEDS OF THE ANALYSIS. 
// BUT FOR VISUAL PURPOSES, IT JUST NEED X, Y, Z
void EDReadOut::DigiRoot()
{

  mTPCTree = (TTree*)file->Get("mTPCdigi"); 
  if(!mTPCTree) return;

  // Rachel's data

  mTPCTree -> SetBranchAddress("i_NoHits",  &nHits); 
  mTPCTree -> SetBranchAddress("v_XHitPos", &xHits, &b_xHits);
  mTPCTree -> SetBranchAddress("v_YHitPos", &yHits, &b_yHits);
  mTPCTree -> SetBranchAddress("v_ZHitPos", &zHits, &b_zHits);

}

EDReadOut *ReadOut=NULL;
