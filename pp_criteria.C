#include "TH1F.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include <iostream>

Float_t jtpt_ak3[1000];
Float_t jteta_ak3[1000];
Float_t jtphi_ak3[1000];
Int_t jt80;
Int_t jt60;
Int_t jt40;
Int_t jt80_pre;
Int_t jt60_pre;
Int_t jt40_pre;
Int_t njets_ak3;
void pp_criteria(){

  //Define and Divide Canvas
  TCanvas * c = new TCanvas("c","4 Plots",1);
  c -> Divide(2,2);

  //Define Histograms
  TH1F * h80 = new TH1F("h80","Jet p_{T} (GeV/c)>80",100,0,500);
  TH1F * h60 = new TH1F("h60","Jet p_{T} (GeV/c)>60",100,0,500);
  TH1F * h40 = new TH1F("h40","Jet p_{T} (GeV/c)>40",100,0,500);

  //Access File
  TFile * fileA = TFile::Open("pp_2013_data_testfile.root");
  
  //Create Trees
  TTree * hlt = (TTree*)fileA->Get("hltanalysis/HltTree");
  TTree * ak3t = (TTree*)fileA->Get("akPu3PFJetAnalyzer/t");

  //Add Friends
  ak3t ->AddFriend(hlt);
 
  int Nevents = ak3t->GetEntries();
  cout << Nevents;

  //Set Branch address

  ak3t->SetBranchAddress("jtpt",jtpt_ak3);
  ak3t->SetBranchAddress("jteta",jteta_ak3);
  ak3t->SetBranchAddress("jtphi",jtphi_ak3);
  ak3t->SetBranchAddress("nref",&njets_ak3);
  ak3t->SetBranchAddress("HLT_PAJet80_NoJetID_v1",&jt80);
  ak3t->SetBranchAddress("HLT_PAJet60_NoJetID_v1",&jt60);
  ak3t->SetBranchAddress("HLT_PAJet40_NoJetID_v1",&jt40);
  ak3t->SetBranchAddress("HLT_PAJet80_NoJetID_v1_Prescl",&jt80_pre);
  ak3t->SetBranchAddress("HLT_PAJet60_NoJetID_v1_Prescl",&jt60_pre);
  ak3t->SetBranchAddress("HLT_PAJet40_NoJetID_v1_Prescl",&jt40_pre);
for(int iev = 0; iev < Nevents; ++iev){
  //  t->GetEntry(iev);
  ak3t->GetEntry(iev);

  for(int i = 0; i < njets_ak3; ++i){
    if(jt80)
      h80 -> Fill(jtpt_ak3[i],jt80_pre);
    if(jt60)
      h60 -> Fill(jtpt_ak3[i],jt60_pre);
    if(jt40)
      h40 -> Fill(jtpt_ak3[i],jt40_pre);
  }
 }

 c->cd(1);
 c->cd(1)->SetLogy();
 h80->SetDrawOption("G"); 
 h80->GetXaxis()->SetTitle("Jet p_{T}");
 h80->GetYaxis()->SetTitle("# Counts");
 h80->Draw();

 c->cd(2);
 c->cd(2)->SetLogy();
 h60->SetDrawOption("G"); 
 h60->GetXaxis()->SetTitle("Jet p_{T}");
 h60->GetYaxis()->SetTitle("# Counts");
 h60->Draw("HIST");  
 
 c->cd(3);
 c->cd(3)->SetLogy();
 h40->GetXaxis()->SetTitle("Jet p_{T}");
 h40->GetYaxis()->SetTitle("# Counts");
 h40->Draw("HIST");

 c->SaveAs("4plots2.pdf","Recreate");
}
