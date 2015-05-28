#include "TH1F.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"

Float_t jtpt_ak3[1000];
Float_t jtphi_ak3[1000];
Int_t njets_ak3;
Float_t jtpt_max=0;
Int_t max_index;

void pp_delta_phi(){
  TCanvas * c = new TCanvas("c","delta Phi",1);

  TH1F * hPt = new TH1F("hPt","Jet p_{T} (GeV/c)",100,0,1000);
  TH1F * hDelta_Phi = new TH1F("hPhi","Jet #phi (rad)",60,-3.14,3.14);

  TFile * fileA = TFile::Open("pp_2013_data_testfile.root");
  TTree * t = (TTree*)fileA->Get("hltanalysis/HltTree");
  TTree * ak3t = (TTree*)fileA->Get("akPu3PFJetAnalyzer/t");

  int Nevents = t->GetEntries();
  
  ak3t->SetBranchAddress("jtpt",jtpt_ak3);
  ak3t->SetBranchAddress("jtphi",jtphi_ak3);
  ak3t->SetBranchAddress("nref",&njets_ak3);
  
  for(int iev = 0; iev < Nevents; ++iev){
    t->GetEntry(iev);
    ak3t->GetEntry(iev);
    
    for(int i = 1; i < njets_ak3; ++i){
      hDelta_Phi -> Fill(jtphi_ak3[i]-jtphi_ak3[0]);
    }
    
  }
  hDelta_Phi->Draw();
  /*
  c->cd(1);
  c->cd(1)->SetLogy();

  hPt->GetXaxis()->SetTitle("Jet p_{T}");
  hPt->GetYaxis()->SetTitle("# Counts Per Event");
  hPt->Draw();

  c->cd(2);
  c->cd(2)->SetLogy();

  hEta->GetXaxis()->SetTitle("Jet #Eta");
  hEta->GetYaxis()->SetTitle("# Counts Per Event");
  hEta->Draw();  

  c->cd(3);
  c->cd(3)->SetLogy();

  hPhi->GetXaxis()->SetTitle("Jet #Phi");
  hPhi->GetYaxis()->SetTitle("# Counts Per Event");
  hPhi->Draw();
  
  c->cd(4);
  h2d->Draw("LEGO");
  c->SaveAs("4plots2.pdf","Recreate");

  */
}
