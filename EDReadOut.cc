#include <sstream>
#include <fstream>
using namespace std;
#include "TFile.h"
#include "EDVariable.hh"
#include "EDReadOut.hh"

EDReadOut::EDReadOut()
{
  cout << "<EDReadOut::EDReadOut>: Initializing." << endl;

  fileName = Variable->inputfile; // could be simplified

  cout<<"inputfile: "<< Variable -> inputfile<<endl;

 

}

EDReadOut::~EDReadOut()
{
  cout << "<EDReadOut::~EDReadOut>: Finished" << endl;
}


// READOUT FROM G4SBS SIMULATION 
void EDReadOut::SBSRoot()
{


  file = new TFile(fileName,"READ"); 
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

  file = new TFile(fileName,"READ"); 
  mTPCTree = (TTree*)file->Get("mTPCdigi"); 
  if(!mTPCTree) return;

  // Rachel's data

  mTPCTree -> SetBranchAddress("i_NoHits",  &nHits); 
  mTPCTree -> SetBranchAddress("v_XHitPos", &xHits, &b_xHits);
  mTPCTree -> SetBranchAddress("v_YHitPos", &yHits, &b_yHits);
  mTPCTree -> SetBranchAddress("v_ZHitPos", &zHits, &b_zHits);

}


void EDReadOut::AruniData()
{
  ifstream  ReadFile(fileName);
  
  if (ReadFile) // it controls that the file exists
    {
      while (!ReadFile.eof()) // loop until the end of the file (eof)
	{
	  while ( getline( ReadFile, line )) // take a full line from the file
	    {
	      	  stringstream ss( line );      // Set up up a stream from this line

		  // I read 11 columns since this is the data from Murchana (rc-externals)
		  // probably, I don't need to read beyond 7, except if I want to make use
		  // of a different cross-section
		  ss >> it1 >> it2 >> it3; //


		  if (it1 == "hitxyz") continue; 


		  dx = stod(it1);
		  dy = stod(it2);
		  dz = stod(it3);

		  vx.push_back(dx);
		  vy.push_back(dy);
		  vz.push_back(dz);
		  		  
	    }
	}
    }

}

EDReadOut *ReadOut=NULL;
