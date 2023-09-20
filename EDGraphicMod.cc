#include <sstream>
#include <fstream>
using namespace std;
#include "TFile.h"


#include "EDVariable.hh"
#include "EDGraphicMod.hh"
#include "EDReadOut.hh"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TPolyLine3D.h"
#include "TPolyLine.h"
#include "TGraph2D.h"
#include "TCanvas.h"
#include "TGraph.h"


EDGraphicMod::EDGraphicMod()
{
  cout << "<EDGraphicMod::EDGraphicMod>: Initializing." << endl;
  
  cout<<"Data to read: "<<Variable->data2analyze<<endl;
  
  switch(Variable->data2analyze) {
  case 0 :
    cout<<"G4SBS Data root"<<endl;
    ReadOut-> SBSRoot();
    Entries = ReadOut-> mTPCTree->GetEntries();
    break; //optional
  case 1 :
    cout<<"Digitized Data root"<<endl;
    ReadOut-> DigiRoot();
    Entries = ReadOut-> mTPCTree->GetEntries();
    break; //optional
  case 2 :
    cout<<"Aruni/Steve Data"<<endl;
    ReadOut-> AruniData();
    break; //optional
  case 3 :
    cout<<"Aruni/Steve Root Data"<<endl;
    ReadOut-> AruniDataRoot();
    Entries = ReadOut-> mTPCTree->GetEntries();
    break; //optional

  default :
    ReadOut-> SBSRoot();
    break; //optional
  }
    
    
   
  //  cout<<"Entries: "<<Entries<<endl;

  cGraph = new TCanvas("cGraph","Graph2D example",0,0,600,1200); 
  cGraphXY = new TCanvas("cGraphXY","GraphXY example",0,0,1000,1200); 

  
  
}

EDGraphicMod::~EDGraphicMod()
{
  cout << "<EDGraphicMod::~EDGraphicMod>: Finished" << endl;
}


void EDGraphicMod::InitialProcess()
{

  
  vector< TGraph2D* > vGraph;// a vector of graphs
       
  Int_t numeve = Variable -> numevents;

  
  if(Variable->data2analyze <= 1 ||
     Variable->data2analyze == 3 )
    {
      if(Entries < numeve) numeve = Entries;

      for (int neve = 0; neve < numeve; neve++)
	{
	  DataFillRoot(neve);
	  if(xv.size()!=0)
	    {
	      x_vec.push_back(xv);
	      y_vec.push_back(yv);
	      z_vec.push_back(zv);
	    }
	}
    }
  else
    {
      DataFillAruni();
      x_vec.push_back(xv);
      y_vec.push_back(yv);
      z_vec.push_back(zv);
    }

      
  cGraph->cd();
  graph2dfile(x_vec, y_vec, z_vec);

  cGraphXY->cd();
  graphXY(x_vec, y_vec);
  
}


void EDGraphicMod::graph2dfile(vector<vector<Double_t> > &vX,vector<vector<Double_t> > &vY, vector<vector<Double_t> > &vZ )
{
  Draw3DFrame();
  Draw3DCircles();



  
  Int_t NoG = vX.size();//number of graphs
    
  cout<< vX[0].size()<<endl;
  vector< TGraph2D* > vGraph;// a vector of graphs

  Int_t RealNoG =0;

  for(int idx = 0; idx< NoG; idx++)
    {
      if(vX[idx].size()>0) //This line avoids 0s which could cause errors constructing the TGraph
	{
	  vGraph.push_back(new TGraph2D(vX[idx].size(), &vX[idx][0], &vY[idx][0], &vZ[idx][0] ) );
	  RealNoG++;
	}
    }

  
  if(NoG == 1)
    {
     //      cout<<"ONE GRAPH"<<endl;
      vGraph[0] -> SetLineColor(color_wh[0]);
      vGraph[0] -> SetLineWidth(4);
      vGraph[0] -> SetMarkerStyle(20);
      vGraph[0] -> SetMarkerSize(.9);
      vGraph[0] -> SetMarkerColor(color_wh[0]);
      //      vGraph[0] -> Draw("PLINE same");
      vGraph[0] -> Draw("P same");
    }
  else
    {
      //      cout<<"MULTIPLE GRAPHS"<<endl;
      for(int kk = 0; kk < RealNoG; kk++)
	{
	  vGraph[kk] -> SetLineColor(color_wh[kk%27]);
	  vGraph[kk] -> SetLineWidth(4);
	  vGraph[kk] -> SetMarkerStyle(20);
	  vGraph[kk] -> SetMarkerSize(.9);
	  vGraph[kk] -> SetMarkerColor(color_wh[kk%27]);
	  //	  vGraph[kk] -> Draw("PLINE same");
	  vGraph[kk] -> Draw("P same");
	}
    }
  cGraph->Modified();
  cGraph->Update();
 
  return;
 
}


void EDGraphicMod::graphXY(vector<vector<Double_t> > &vX,vector<vector<Double_t> > &vY)
{
  DrawFrame();
  DrawCircles();
  
  Int_t NoG = vX.size();//number of graphs
  
  vector< TGraph* > vGraph;// a vector of graphs
  
  Int_t RealNoG =0;
      
  for(int idx = 0; idx< NoG; idx++)
    {
      if(vX[idx].size()>0) //This line avoids 0's which could cause errors constructing the TGraph
	{
	  vGraph.push_back(new TGraph(vX[idx].size(), &vX[idx][0], &vY[idx][0]) );
	  RealNoG++;
	}
      }
  
  if(NoG == 1)
    {
      //  cout<<"ONE GRAPH"<<endl;
      vGraph[0] -> SetLineColor(color_wh[0]);
      vGraph[0] -> SetLineWidth(4);
      vGraph[0] -> SetMarkerStyle(20);
      vGraph[0] -> SetMarkerSize(.9);
      vGraph[0] -> SetMarkerColor(color_wh[0]);
      vGraph[0] -> Draw("P same");
    }
  else
    {
      //      cout<<"MULTIPLE GRAPHS"<<endl;
      for(int kk = 0; kk < RealNoG; kk++)
	{
	  vGraph[kk] -> SetLineColor(color_wh[kk%27]);
	  vGraph[kk] -> SetLineWidth(4);
	  vGraph[kk] -> SetMarkerStyle(20);
	  vGraph[kk] -> SetMarkerSize(.9);
	  vGraph[kk] -> SetMarkerColor(color_wh[kk%27]);
	  vGraph[kk] -> Draw("PLINE same");
	}
    }
  cGraphXY->Modified();
  cGraphXY->Update();
  
  return;
  
}

void EDGraphicMod::animatedXY(vector<vector<Double_t> > &vX, vector<vector<Double_t> > &vY)
{
  DrawFrame();
  DrawCircles();
  
  TGraph*  vGraph;// a vector of graphs
    
  for(int idx = 0; idx< 2; idx++)
    {
      Int_t Size =  vX[idx].size();
      for(int NoHits = 0; NoHits < Size; NoHits++)
	{
	  vGraph = new TGraph(NoHits, &vX[idx][0], &vY[idx][0]) ;
	  vGraph -> SetLineColor(color_wh[idx]);
	  vGraph -> SetLineWidth(4);
	  vGraph -> SetMarkerStyle(20);
	  vGraph -> SetMarkerSize(.9);
	  vGraph -> SetMarkerColor(color_wh[idx]);
	  vGraph -> Draw("PLINE same");
	  
	  // vGraph.push_back(new TGraph(NoHits, &vX[idx][0], &vY[idx][0]) );
	  // vGraph[NoHits] -> SetLineColor(color_wh[0]);
	  // vGraph[NoHits] -> SetLineWidth(4);
	  // vGraph[NoHits] -> SetMarkerStyle(20);
	  // vGraph[NoHits] -> SetMarkerSize(.9);
	  // vGraph[NoHits] -> SetMarkerColor(color_wh[0]);
	  // vGraph[NoHits] -> Draw("PLINE same");
	  // cAnimation -> Update();
	  
	  //	  cAnimation -> Print("file.gif+1"); 
	}
    }
  //     cAnimation -> Print("file.gif++"); 
  // cAnimation -> Modified();
  // 
  
  return;
  
  
}




void EDGraphicMod::Draw3DFrame()
{
  // This histogram is neccesary to plot the axis and keep the multi graph2D 
  frame3d = new TH3F("frame3d","mTPC - Hits/Event",10,-0.15, 0.15, 10, -0.15, 0.15, 10,-0.28,0.28);
  
  frame3d->GetXaxis()->SetTitle("X (m)");
  frame3d->GetXaxis()->SetTitleOffset(1.4);
  frame3d->GetXaxis()->CenterTitle() ;

  frame3d->GetYaxis()->SetTitle("Y (m)");
  frame3d->GetYaxis()->SetTitleOffset(1.4);
  frame3d->GetYaxis()->CenterTitle() ;

  frame3d->GetZaxis()->SetTitle("Z (m)");
  frame3d->GetZaxis()->SetTitleOffset(1.4);
  frame3d->GetZaxis()->CenterTitle() ;
  
  frame3d->Draw();

  return;
}



void EDGraphicMod::DrawFrame()
{
  frame2d = new TH2F("frame2d","mTPC - Hits/Chains XY",10,-0.15,0.15, 10,-0.15,0.15);
  
  frame2d->GetXaxis()->SetTitle("X (m)");
  frame2d->GetXaxis()->SetTitleOffset(1.4);
  frame2d->GetXaxis()->CenterTitle() ;

  frame2d->GetYaxis()->SetTitle("Y (m)");
  frame2d->GetYaxis()->SetTitleOffset(1.4);
  frame2d->GetYaxis()->CenterTitle() ;
  
  frame2d->Draw();

  return;
}


void EDGraphicMod::DrawCircles()
{
  
  for (Int_t pp=0; pp < steps_cir; pp++)
    {
      ar =  pp*0.05*pi;
      x_cir[pp] = 0.15*cos(ar);
      y_cir[pp] = 0.15*sin(ar);

      x_cir_sm[pp] = 0.05*cos(ar);
      y_cir_sm[pp] = 0.05*sin(ar);

    }
     
  OuterCircle = new TPolyLine(steps_cir,x_cir,y_cir);
  InnerCircle = new TPolyLine(steps_cir,x_cir_sm, y_cir_sm);
  
  OuterCircle -> SetLineWidth(2);
  OuterCircle -> SetLineColor(kBlack);
  InnerCircle -> SetLineWidth(2);
  InnerCircle -> SetLineColor(kBlack);

  OuterCircle -> Draw("same");
  InnerCircle -> Draw("same");

  return;

}


void EDGraphicMod::Draw3DCircles()
{
   
  for (Int_t pl=0; pl < planes; pl++)
    {
      for (Int_t pp=0; pp < steps_cir; pp++)
	{
	  ar =  pp*0.05*pi;
	  x_cir_3D[pl][pp] = 0.15*cos(ar);
	  y_cir_3D[pl][pp] = 0.15*sin(ar);
	  z_cir_3D[pl][pp] = -0.25+(0.05*pl);
	  
	  x_cir_sm_3D[pl][pp] = 0.05*cos(ar);
	  y_cir_sm_3D[pl][pp] = 0.05*sin(ar);
	  z_cir_sm_3D[pl][pp]  = -0.25+(0.05*pl);
	}
    }
  
  Color_t cathode;

  for (Int_t pl=0; pl < planes; pl++)
    {
      TPolyLine3D *OuterCircle3D = new TPolyLine3D(steps_cir, x_cir_3D[pl],    y_cir_3D[pl],    z_cir_3D[pl]);
      TPolyLine3D *InnerCircle3D = new TPolyLine3D(steps_cir, x_cir_sm_3D[pl], y_cir_sm_3D[pl], z_cir_sm_3D[pl]);
  
      if (pl%2 == 0)
	{    
	  cathode = kBlack;
	}
      else
	{      
	  cathode = kRed;
	}

      OuterCircle3D -> SetLineWidth(2);
      OuterCircle3D -> SetLineColor(cathode);
      InnerCircle3D -> SetLineWidth(2);
      InnerCircle3D -> SetLineColor(cathode);

      OuterCircle3D->Draw("same");
      InnerCircle3D->Draw("same");
    }
  return;

}




void EDGraphicMod::DataFillRoot(Int_t TreeEntry)
{
  xv.clear();
  yv.clear();
  zv.clear();

  //  cout<<"Entry: "<< TreeEntry << endl;

  ReadOut -> mTPCTree -> GetEntry(TreeEntry);

  nHits = ReadOut -> xHits->size();

  if(nHits != 0) 
    {
      for(int j=0; j<nHits; j++)
	{
	  if(Variable->verbose == 1)
	    {
	      cout<< " x: " <<ReadOut -> xHits->at(j)
		  << " y: " <<ReadOut -> yHits->at(j)
		  << " z: " <<ReadOut -> zHits->at(j) << endl;
	    }

	  if(  Variable->data2analyze !=3)
	    {
	      xv.push_back(ReadOut -> xHits->at(j));
	      yv.push_back(ReadOut -> yHits->at(j));
	      zv.push_back(ReadOut -> zHits->at(j));
	    }
	  else
	    {
	      xv.push_back(ReadOut -> xHits->at(j)/100.);// units in m
	      yv.push_back(ReadOut -> yHits->at(j)/100.);
	      zv.push_back(ReadOut -> zHits->at(j)/100.);
	    }
	}
    }

  return;

}

void EDGraphicMod::DataFillAruni()
{
  xv.clear();
  yv.clear();
  zv.clear();


  nHits = ReadOut -> vx.size();

  for(int j=0; j<nHits; j++)
    {
      if(Variable->verbose == 1)
	{
	  cout<< " x: " <<ReadOut -> vx.at(j)
	      << " y: " <<ReadOut -> vy.at(j)
	      << " z: " <<ReadOut -> vz.at(j) << endl;
	}
      xv.push_back(ReadOut -> vx.at(j)/100.);// units in m
      yv.push_back(ReadOut -> vy.at(j)/100.);
      zv.push_back(ReadOut -> vz.at(j)/100.);
      
  
    }
  
  return;

}



EDGraphicMod *GraphModule = NULL;
