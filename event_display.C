#include <iostream>
#include "string.h"
#include "TFile.h"
#include "TStyle.h"
#include "TColor.h"
#include "TTree.h"
#include "math.h"
#include "TMultiGraph.h"
#include "TStopwatch.h"
#include "TApplication.h"
#include <gif_lib.h>

#include <thread>
#include <chrono>
#include "TSystem.h"

#include "EDVariable.hh"
#include "EDReadOut.hh"
#include "EDGraphicMod.hh"


#include <vector>


using namespace std;


void set_color_env(){   
  //******************************************************************
  //code to improve the color palette
  //from the root web page and color codes from:
  //http://ultrahigh.org/2007/08/20/making-pretty-root-color-palettes/
  //******************************************************************
  
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
  
  //******************************************************************
  

}


int main(int argc, char** argv)
{
  TApplication app("app", &argc, argv);

  set_color_env();

  gStyle->SetOptStat(0);
  
  TString dataname;
  dataname = "EventDisplay.ini";
 
  cout << "Compiled on: " __DATE__ " " __TIME__ "." << endl;

  Variable = new EDVariable(); 

  Variable -> LoadFromFile(dataname);
  cout<<"inputfile: "<<Variable->inputfile<<endl;

  ReadOut  = new EDReadOut(); //order IS important. Load the file and THEN declare the readout
  GraphModule = new EDGraphicMod();

  
  //Benchmark time test
  TStopwatch timer;
  timer.Start();
  
  if(argc < 1) return 1;

  //    tree(argv[1]);
  //  for(Int_t k=0;k<1000;k++)
  {
    GraphModule -> InitialProcess();
    
      //    event_display();
    //    cout<<"cycle: "<<k<<endl;
  }
    
  timer.Stop();
  
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();

  printf("RealTime=%f seconds, CpuTime=%f seconds\n",rtime,ctime);

  cout << "-----> CTRL+C to end" << endl;

  app.Run();

  return 0;
}
