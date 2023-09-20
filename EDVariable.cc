#include <sstream>
#include <fstream>
using namespace std;

#include "EDVariable.hh"

EDVariable::EDVariable()
{
  cout << "<EDVariable::EDVariable>: Initializing." << endl;
}

EDVariable::~EDVariable()
{
  cout << "<EDVariable::~EDVariable>: Finished" << endl;
}

void EDVariable::LoadFromFile(TString FileName)
{


  infile.open(FileName);
  if (infile)
    {
      while (!infile.eof())
	{
	  if (getline(infile,line))
	    {
	      string buf;
	      string wert;
	      //	      double doublewert;
	      stringstream ss(line);
	      //		cout << ">" << line << endl;
	      ss >> buf;

	      if (buf == "inputfile")	 
		{			
		  ss >> inputfile;

		}
	      

	      if (buf == "Rootdata")	 
	       	{			
	       	  ss >> data2analyze;
		  //0 = SBS data. 1= Rachel digidata. 
	       	  if ( data2analyze != 0 &&
		       data2analyze != 1 &&
		       data2analyze != 2 &&
		       data2analyze != 3 )
		    {
		      cout<<"**************************************"<<endl;
		      cout<<"            Rootdata                  "<<endl;
		      cout<<"VALUE NOT ACCEPTED (USING DEFAULT = 1)"<<endl;
		      cout<<"**************************************"<<endl;
		      data2analyze = 1; //DEFAULT VALUE
		    }
	       	}

	      if (buf == "NoOfEvents")	 
	       	{			
	       	  ss >> numevents;
		  // 1 event to read by default
	       	  if ( numevents <= 0)
		    {
		      cout<<"**************************************"<<endl;
		      cout<<"            NoOfEvents                "<<endl;
		      cout<<"VALUE NOT ACCEPTED (USING DEFAULT = 1)"<<endl;
		      cout<<"**************************************"<<endl;
		      numevents = 1; //DEFAULT VALUE
		    }
	       	}

	    }
	}
    }
}


EDVariable *Variable=NULL;
