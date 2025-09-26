// This code may be compiled to make a stand alone exe
// or it can be run from the ROOT command line as:

// root [0] .L cpp_example.cpp  or .L cpp_example.cpp+
// root [1] cpp_example

#include "TApplication.h"
#include "TROOT.h"
#include "TH2F.h"
#include "TF2.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TRandom3.h"
//#include <cstdlib>
//#include <cmath>
//#include <iostream>

using namespace std;
using namespace ROOT::Math;


// examples of various plots in C++ program
void cpp_example(int samples=10000){
  // gStyle->SetOptStat(0);  // turn off default stats box in histograms

  // Histogram filled with a normal distribution
  // used a chatGPT query to generate the formula in f2d and to help me better understand how to use root
  auto hist1 = new TH2F("hist1","random gauss;x;y",100,50,150,100,50,150);
  auto f2d = new TF2("f2d","exp(-0.5*(((x-[0])*(x-[0]))/([1]*[1])+((y-[2])*(y-[2]))/([3]*[3])))",50,150,50,150);
  f2d->SetParameters(100,6,100,6);
  hist1->FillRandom("f2d",samples);
  auto tc1 = new TCanvas("c1","Canvas1");
  hist1->Draw("COLZ");
  tc1->Update();
  tc1->SaveAs("canvas2d_cpp.png");
}
int main(int argc, char **argv) {
  int nsamples=10000;  // set sample sizes

  // This allows you to view ROOT-based graphics in your C++ program
  // If you don't want view graphics (eg just read/process/write data files), 
  // this can be ignored
  TApplication theApp("App", &argc, argv);

  if (argc>1) nsamples=atoi(argv[1]);
  
  cpp_example(nsamples);

  // view graphics in ROOT if we are in an interactive session
  if (!gROOT->IsBatch()) {
      cout << "To exit, quit ROOT from the File menu of the plot (or use control-C)" << endl;
    theApp.SetIdleTimer(30,".q"); // set up a failsafe timer to end the program
    theApp.Run(true);
  }
  return 0;
}
  
