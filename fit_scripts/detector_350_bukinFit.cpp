#include <TFile.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1F.h>

void detector_350_bukinFit()
{
  Double_t bukin(Double_t *x, Double_t *par);
  TFile *file = new TFile("/afs/cern.ch/work/k/ktauqeer/private/MadGraph/madanalysis5/rootFiles/detector_level_350.root","READ");
  TFile *f1 = new TFile("/afs/cern.ch/work/k/ktauqeer/private/MadGraph/madanalysis5/rootFiles_fit/detector_level_350.root","RECREATE");
  TCanvas* c1 = new TCanvas("c1");
  TH1F* hist;
  file -> GetObject("hist",hist);
  hist -> Sumw2();
  Double_t x = {1.};
  Double_t par[6] = {1.,120.,20.-0.2,0.01,0.01};
  TF1* f = new TF1("fit",bukin,100,700,6);  
  f -> SetParameters(1.,288.6,146.7,-0.2,0.01,0.01);
  //TF1* f = new TF1("gauss","gausn",72,88);
  //f -> SetParameters(3,81.93,22.31);
  hist -> Fit("fit","R");

  // Cosmetics
  gStyle -> SetOptStat(0);
  //gStyle-> SetOptFit(1100);
  //gStyle-> SetStatW(0.6);
  //gStyle-> SetStatH(0.6);

  hist -> SetTitle("");
  hist -> GetXaxis() -> SetRangeUser(100,700);
  hist -> GetXaxis() -> SetTitle("M_{jj} [GeV]");
  hist -> GetXaxis() -> SetTitleSize(0.05);
  hist -> GetXaxis() -> SetTitleOffset(0.8);

  hist -> GetYaxis() -> SetTitle("Events / (10 GeV)");
  hist -> GetYaxis() -> SetTitleSize(0.05);
  hist -> GetYaxis() -> SetTitleOffset(0.9);

  hist -> SetMarkerStyle(20);
  hist -> SetMarkerSize(0.85);
  hist -> SetLineColor(1);
  hist -> SetLineWidth(1);
  hist -> Draw("PE1X0");

  f -> SetFillStyle(1001);
  f -> Draw("fc same");

  hist -> Draw("PE1X0 same");

  auto leg = new TLegend(0.7,0.7,0.85,0.85);
  leg->AddEntry(hist,"MC data","P");
  leg->AddEntry(f,"Bukin fit","l");
  leg->Draw("same");

  auto tbox = new TPaveText(0.7,0.4,0.85,0.6,"blNDC");
  tbox -> SetFillStyle(0);
  tbox -> SetBorderSize(0);
  tbox -> SetTextAlign(12);
  tbox -> SetTextSize(0.030);
  tbox -> AddText(Form("#chi^{2}_{#nu}=%4.2f/%d",f->GetChisquare(),f->GetNDF()));
  tbox -> AddText(Form("#mu=%4.2f",f->GetParameter(1)));
  tbox -> AddText(Form("#sigma=%4.2f",f->GetParameter(2)));
  tbox -> Draw("same");

  c1 -> SaveAs("detector_level_350_fit.pdf");
  hist -> Write();
  cout << "chi square =  " << f -> GetChisquare() << endl;
  cout << "mean = " << f -> GetParameter(1) << endl;
  cout << "sigma = " << f -> GetParameter(2) << endl;
  //c1 -> SaveAs("fitted_histogram.pdf");
  //file -> Close();
  return;
}
 

Double_t bukin(Double_t *x, Double_t *par)
 {
   Double_t xx =x[0]; 
   Double_t norm = par[0]; //100.
   Double_t x0 = par[1]; //120.
   Double_t sigma = par[2]; //20.
   Double_t xi = par[3]; //-0.2
   Double_t rhoL = par[4]; //0.01
   Double_t rhoR = par[5]; //0.01
  

   double r1=0,r2=0,r3=0,r4=0,r5=0,hp=0;
   double x1 = 0,x2 = 0;
   double fit_result = 0;
   
   double consts = 2*sqrt(2*log(2.));
   hp=sigma*consts;
   r3=log(2.);
   r4=sqrt(TMath::Power(xi,2)+1);
   r1=xi/r4;  

  if(TMath::Abs(xi) > exp(-6.)){
     r5=xi/log(r4+xi);
   }
   else
     r5=1;
     
   x1 = x0 + (hp / 2) * (r1-1);
   x2 = x0 + (hp / 2) * (r1+1);
   

   //--- Left Side
      if(xx < x1)
		{
           r2=rhoL*TMath::Power((xx-x1)/(x0-x1),2)-r3 + 4 * r3 * (xx-x1)/hp * r5 * r4/TMath::Power((r4-xi),2 );
		}

   //--- Center
      else if(xx < x2) 
		{
                  if(TMath::Abs(xi) > exp(-6.)) 
	          	{
                  	r2=log(1 + 4 * xi * r4 * (xx-x0)/hp)/log(1+2*xi*(xi-r4));
                  	r2=-r3*(TMath::Power(r2,2));
	         	}	
                  else
	          	{
                  	r2=-4*r3*TMath::Power(((xx-x0)/hp),2);  
                  	}	
        	}



   //--- Right Side

      else 
                {
               r2=rhoR*TMath::Power((xx-x2)/(x0-x2),2)-r3 - 4 * r3 * (xx-x2)/hp * r5 * r4/TMath::Power((r4+xi),2);
                }

      if(TMath::Abs(r2) > 100)
                {
                fit_result = 0;  
                }
      else
                {

    //---- Normalize the result
                fit_result = exp(r2);
                }

   return norm*fit_result;
 }
                                                
