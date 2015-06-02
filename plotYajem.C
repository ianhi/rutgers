#include "TCanvas.h"
#include "TFile.h"

void plotYajem(){

  TFile * _file0 = TFile::Open("treefile2000.root");
  TCanvas * c = new TCanvas("c","Yajem",1);
  c -> Divide(2,2);
  TTree *yaj = (TTree*)_file0 -> Get("dijet/t");
  TH1F * hPt = new TH1F("hPt","Jet p_{T} (GeV/c)",100,0,1000);
  TH1F * hEta = new TH1F("hEta","Jet #eta (rad)",60,-2,2);
  TH1F * hPhi = new TH1F ("hPhi","Jet #phi (rad)",60,-3.14,3.14);  
  hPt->GetXaxis()->SetRange(0,400);
  yaj -> Draw("jtpt>>hPt","","goff");
  yaj -> Draw("jteta>>hEta","","goff");
  yaj -> Draw("jtphi>>hPhi","","goff");
  yaj -> Draw("jtphi:jteta>>hAll","jtpt>10","goff");

  c->cd(1);
  hPt->Draw();

  c->cd(2);
  hEta->Draw();  

  c->cd(3);
  hPhi->Draw();
  c->SaveAs("yaj.pdf","RECREATE");
}
