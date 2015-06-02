/*
  This will plot a histogram of Aj jet assymetry using the outputs of the MC generators.
  Aj = (pt1-pt2)/(pt1+pt2)
  where pt1 is momentum of leading jet and pt2 is momentum of subleading jet


*/
#include "TCanvas.h"
#include "TFile.h"
#include "THStack.h"

Int_t nBins = 100;
Float_t pyq_pt[1000];
Float_t pyt_pt[1000];
Float_t tf_pt[1000];

void AjMC{
  THStack *hsA = new THStack("hsA","Stacked A_{J}");
  TFile * file0 = TFile::Open("Pyquen10000.root");
  TFile * file1 = TFile::Open("PythiaZ2Star.root");
  TFile * file2 = TFile::Open("treefile10000.root"); 

  TCanvas * c = new TCanvas("c","Aj Comparison",1);
  
  TTree *Tpyq = (TTree*)file0 -> Get("dijet/t");
  TTree *Tpyt = (TTree*)file1 -> Get("dijet/t");
  TTree *Ttf = (TTree*)file2 -> Get("dijet/t"); 

  TH1F * hPyqA = new TH1F ("hPyqA","PYQUEN Jet A_{j}",nBins,0,1);  
  TH1F * hPytA = new TH1F ("hPytA","PYTHIA Z2 Jet A_{j}",nBins,0,1);  
  TH1F * hTfA = new TH1F ("hTfA","Tree File Jet A_{j}",nBins,0,1);

  Int_t Npyq = Tpyq->GetEntries();
  Int_t Npyt = Tpyt->GetEntries();
  Int_t Ntf = Ttf->GetEntries();

  Tpyq ->SetBranchAddress("jtpt",pyq_pt);
  Tpyq ->SetBranchAddress("nref",&pyq_njets);

  Tpyt ->SetBranchAddress("jtpt",pyt_pt);
  Tpyt ->SetBranchAddress("nref",&pyt_njets);

  Ttf  ->SetBranchAddress("jtpt",tf_pt);
  Ttf  ->SetBranchAddress("nref",&tf_njets);

  
  for(int iev = 0; iev < Npyt; ++iev){
    Tpyq ->GetEntry(iev);
    Tpyt ->GetEntry(iev);
    Ttf  ->GetEntry(iev);
    hPyqA ->Fill((pyq_pt[0]-pyq_pt[1])/(pyq_pt[0]+pyq_pt[1]));
    hPytA ->Fill((pyq_pt[0]-pyq_pt[1])/(pyq_pt[0]+pyq_pt[1]));
    htfA  ->Fill((tf_pt[0]-tf_pt[1])/(tf_pt[0]+tf_pt[1])); 
   /*
    for(int i=0;i<pyq_njets;++i){
      
      hPyqA ->Fill(pyq_pt[i]);
    }
    for(int i=0;i<pyt_njets;++i){
      hPytA ->Fill(pyt_pt[i]);
    }
    for(int i=0;i<tf_njets;++i){
      hTfA ->Fill(tf_pt[i]);
      }*/
  }
  hsA ->Add(hPyqA);
  hsA ->Add(hPytA);
  hsA ->Add(hTfA);
  hsA ->Draw();


}
