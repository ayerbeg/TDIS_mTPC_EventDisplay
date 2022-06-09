#ifndef EDVariable_H
#define EDVariable_H 1
#include "TString.h"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

class EDVariable
{
public:
  EDVariable();
  ~EDVariable();

  void LoadFromFile(TString FileName);//IF WE DECLARE IT INT WE CAN GIVE AN ERROR CHECK

  ifstream infile;
  string line;

  TString inputfile;

  Int_t data2analyze;
  Int_t verbose;
  Int_t numevents;
};



extern EDVariable *Variable;

#endif
