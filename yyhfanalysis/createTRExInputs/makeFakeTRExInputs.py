import ROOT

ROOT.gROOT.SetBatch(True)

def Fix(hist):
  n = hist.GetNbinsX();
  for i in range(n+1):
    # print i, hist.GetBinContent(i)
    if (hist.GetBinContent(i) < 0): hist.SetBinContent(i,1e-6);


test = False
# test = True

binnumber = 1

mySherpa = ROOT.TFile("/home/bstamas/xdata/yyhf/inputHistMaker/outputs/master.Sherpa2_diphoton_myy_ALL_AF2.Nominal_combinedCR.root", "READ")
# mySherpa = ROOT.TFile("/home/bstamas/xdata/yyhf/inputHistMaker/outputs/mc16a.Sherpa2_diphoton_myy_ALL_AF2.Nominal_combinedCR.root", "READ")
# mySherpa = ROOT.TFile("/home/bstamas/xdata/yyhf/inputHistMaker/outputs/mc16a.Sh_2210_yybb_ALL_Nominal_combinedCR.root", "READ")

myDataFakeslp2 = ROOT.TFile("/home/bstamas/xdata/yyhf/makeDataHists/combinedData_lp2.root", "READ")
myDataFakeslp3 = ROOT.TFile("/home/bstamas/xdata/yyhf/makeDataHists/combinedData_lp3.root", "READ")
myDataFakeslp5 = ROOT.TFile("/home/bstamas/xdata/yyhf/makeDataHists/combinedData_lp5.root", "READ")
myMCSubtract = ROOT.TFile("/home/bstamas/xdata/yyhf/makeSubtractionHists/master.Sherpa2_diphoton_myy_ALL_AF2.subtractionResults.root")
myDecomp = ROOT.TFile("/home/bstamas/xdata/yyhf/makeTRExFitterInputs/HGam_13TeV_2x2DBkgDComp_SherpaAF2_139.0ifb_XSection_allInputs.root", "READ")

METoptions = ["_noMET", ""]

for MET in METoptions:


  hist_relative_fraction_yy = ROOT.TH1F("hist_relative_fraction_yy","hist_relative_fraction_yy",28,-0.5,27.5)
  hist_relative_fraction_yj = ROOT.TH1F("hist_relative_fraction_yj","hist_relative_fraction_yj",28,-0.5,27.5)
  hist_relative_fraction_jj = ROOT.TH1F("hist_relative_fraction_jj","hist_relative_fraction_jj",28,-0.5,27.5)

  hist_total = ROOT.TH1F("hist_total","hist_total",28,-0.5,27.5)

  print "Getting sherpa intput histograms"
  hbb = mySherpa.Get("histbb"+str(MET));
  hbc = mySherpa.Get("histbc"+str(MET));
  hbl = mySherpa.Get("histbl"+str(MET));
  hcc = mySherpa.Get("histcc"+str(MET));
  hcl = mySherpa.Get("histcl"+str(MET));
  hll = mySherpa.Get("histll"+str(MET));
  yymctot = hbb.Integral() + hbc.Integral() + hbl.Integral() + hcc.Integral() + hcl.Integral() + hll.Integral();
  print "My yymctot is " + str(yymctot)

  hbb.Sumw2();hbc.Sumw2();hbl.Sumw2();hcc.Sumw2();hcl.Sumw2();hll.Sumw2();

  hyy = hbb.Clone("hist_DL1");hyy.Add(hbc);hyy.Add(hbl);hyy.Add(hcc);hyy.Add(hcl);hyy.Add(hll);   
  # hyy_alt = hbb_alt.Clone("hist_DL1");hyy_alt.Add(hbc_alt);hyy_alt.Add(hbl_alt);hyy_alt.Add(hcc_alt);hyy_alt.Add(hcl_alt);hyy_alt.Add(hll_alt);   
  my_yy = hyy.GetBinContent(binnumber) 
  hist_total = hyy.Clone("hist_DL1")
  hist_relative_fraction_yy = hyy.Clone("hist_DL1")



  print "Getting fakes histograms"
  hbbMCSubtract_yjlp2 = myMCSubtract.Get("histbb"+str(MET)+"_yjlp2");hbbMCSubtract_yjlp3 = myMCSubtract.Get("histbb"+str(MET)+"_yjlp3");hbbMCSubtract_yjlp5 = myMCSubtract.Get("histbb"+str(MET)+"_yjlp5")
  hbcMCSubtract_yjlp2 = myMCSubtract.Get("histbc"+str(MET)+"_yjlp2");hbcMCSubtract_yjlp3 = myMCSubtract.Get("histbc"+str(MET)+"_yjlp3");hbcMCSubtract_yjlp5 = myMCSubtract.Get("histbc"+str(MET)+"_yjlp5")
  hblMCSubtract_yjlp2 = myMCSubtract.Get("histbl"+str(MET)+"_yjlp2");hblMCSubtract_yjlp3 = myMCSubtract.Get("histbl"+str(MET)+"_yjlp3");hblMCSubtract_yjlp5 = myMCSubtract.Get("histbl"+str(MET)+"_yjlp5")
  hccMCSubtract_yjlp2 = myMCSubtract.Get("histcc"+str(MET)+"_yjlp2");hccMCSubtract_yjlp3 = myMCSubtract.Get("histcc"+str(MET)+"_yjlp3");hccMCSubtract_yjlp5 = myMCSubtract.Get("histcc"+str(MET)+"_yjlp5")
  hclMCSubtract_yjlp2 = myMCSubtract.Get("histcl"+str(MET)+"_yjlp2");hclMCSubtract_yjlp3 = myMCSubtract.Get("histcl"+str(MET)+"_yjlp3");hclMCSubtract_yjlp5 = myMCSubtract.Get("histcl"+str(MET)+"_yjlp5")
  hllMCSubtract_yjlp2 = myMCSubtract.Get("histll"+str(MET)+"_yjlp2");hllMCSubtract_yjlp3 = myMCSubtract.Get("histll"+str(MET)+"_yjlp3");hllMCSubtract_yjlp5 = myMCSubtract.Get("histll"+str(MET)+"_yjlp5")
  hbbMCSubtract_jjlp2 = myMCSubtract.Get("histbb"+str(MET)+"_jjlp2");hbbMCSubtract_jjlp3 = myMCSubtract.Get("histbb"+str(MET)+"_jjlp3");hbbMCSubtract_jjlp5 = myMCSubtract.Get("histbb"+str(MET)+"_jjlp5")
  hbcMCSubtract_jjlp2 = myMCSubtract.Get("histbc"+str(MET)+"_jjlp2");hbcMCSubtract_jjlp3 = myMCSubtract.Get("histbc"+str(MET)+"_jjlp3");hbcMCSubtract_jjlp5 = myMCSubtract.Get("histbc"+str(MET)+"_jjlp5")
  hblMCSubtract_jjlp2 = myMCSubtract.Get("histbl"+str(MET)+"_jjlp2");hblMCSubtract_jjlp3 = myMCSubtract.Get("histbl"+str(MET)+"_jjlp3");hblMCSubtract_jjlp5 = myMCSubtract.Get("histbl"+str(MET)+"_jjlp5")
  hccMCSubtract_jjlp2 = myMCSubtract.Get("histcc"+str(MET)+"_jjlp2");hccMCSubtract_jjlp3 = myMCSubtract.Get("histcc"+str(MET)+"_jjlp3");hccMCSubtract_jjlp5 = myMCSubtract.Get("histcc"+str(MET)+"_jjlp5")
  hclMCSubtract_jjlp2 = myMCSubtract.Get("histcl"+str(MET)+"_jjlp2");hclMCSubtract_jjlp3 = myMCSubtract.Get("histcl"+str(MET)+"_jjlp3");hclMCSubtract_jjlp5 = myMCSubtract.Get("histcl"+str(MET)+"_jjlp5")
  hllMCSubtract_jjlp2 = myMCSubtract.Get("histll"+str(MET)+"_jjlp2");hllMCSubtract_jjlp3 = myMCSubtract.Get("histll"+str(MET)+"_jjlp3");hllMCSubtract_jjlp5 = myMCSubtract.Get("histll"+str(MET)+"_jjlp5")


  # hbbMCSubtract_yjlp2.Sumw2();hbbMCSubtract_yjlp3.Sumw2();hbbMCSubtract_yjlp5.Sumw2()
  # hbcMCSubtract_yjlp2.Sumw2();hbcMCSubtract_yjlp3.Sumw2();hbcMCSubtract_yjlp5.Sumw2()
  # hblMCSubtract_yjlp2.Sumw2();hblMCSubtract_yjlp3.Sumw2();hblMCSubtract_yjlp5.Sumw2()
  # hccMCSubtract_yjlp2.Sumw2();hccMCSubtract_yjlp3.Sumw2();hccMCSubtract_yjlp5.Sumw2()
  # hclMCSubtract_yjlp2.Sumw2();hclMCSubtract_yjlp3.Sumw2();hclMCSubtract_yjlp5.Sumw2()
  # hllMCSubtract_yjlp2.Sumw2();hllMCSubtract_yjlp3.Sumw2();hllMCSubtract_yjlp5.Sumw2()
  # hbbMCSubtract_jjlp2.Sumw2();hbbMCSubtract_jjlp3.Sumw2();hbbMCSubtract_jjlp5.Sumw2()
  # hbcMCSubtract_jjlp2.Sumw2();hbcMCSubtract_jjlp3.Sumw2();hbcMCSubtract_jjlp5.Sumw2()
  # hblMCSubtract_jjlp2.Sumw2();hblMCSubtract_jjlp3.Sumw2();hblMCSubtract_jjlp5.Sumw2()
  # hccMCSubtract_jjlp2.Sumw2();hccMCSubtract_jjlp3.Sumw2();hccMCSubtract_jjlp5.Sumw2()
  # hclMCSubtract_jjlp2.Sumw2();hclMCSubtract_jjlp3.Sumw2();hclMCSubtract_jjlp5.Sumw2()
  # hllMCSubtract_jjlp2.Sumw2();hllMCSubtract_jjlp3.Sumw2();hllMCSubtract_jjlp5.Sumw2()

  ## Combining all flavor combinations into single histogram hbb* for each lp WP
  hbbMCSubtract_yjlp2.Add(hbcMCSubtract_yjlp2);hbbMCSubtract_yjlp3.Add(hbcMCSubtract_yjlp3);hbbMCSubtract_yjlp5.Add(hbcMCSubtract_yjlp5);
  hbbMCSubtract_yjlp2.Add(hblMCSubtract_yjlp2);hbbMCSubtract_yjlp3.Add(hblMCSubtract_yjlp3);hbbMCSubtract_yjlp5.Add(hblMCSubtract_yjlp5);
  hbbMCSubtract_yjlp2.Add(hccMCSubtract_yjlp2);hbbMCSubtract_yjlp3.Add(hccMCSubtract_yjlp3);hbbMCSubtract_yjlp5.Add(hccMCSubtract_yjlp5);
  hbbMCSubtract_yjlp2.Add(hclMCSubtract_yjlp2);hbbMCSubtract_yjlp3.Add(hclMCSubtract_yjlp3);hbbMCSubtract_yjlp5.Add(hclMCSubtract_yjlp5);
  hbbMCSubtract_yjlp2.Add(hllMCSubtract_yjlp2);hbbMCSubtract_yjlp3.Add(hllMCSubtract_yjlp3);hbbMCSubtract_yjlp5.Add(hllMCSubtract_yjlp5);
  hbbMCSubtract_jjlp2.Add(hbcMCSubtract_jjlp2);hbbMCSubtract_jjlp3.Add(hbcMCSubtract_jjlp3);hbbMCSubtract_jjlp5.Add(hbcMCSubtract_jjlp5);
  hbbMCSubtract_jjlp2.Add(hblMCSubtract_jjlp2);hbbMCSubtract_jjlp3.Add(hblMCSubtract_jjlp3);hbbMCSubtract_jjlp5.Add(hblMCSubtract_jjlp5);
  hbbMCSubtract_jjlp2.Add(hccMCSubtract_jjlp2);hbbMCSubtract_jjlp3.Add(hccMCSubtract_jjlp3);hbbMCSubtract_jjlp5.Add(hccMCSubtract_jjlp5);
  hbbMCSubtract_jjlp2.Add(hclMCSubtract_jjlp2);hbbMCSubtract_jjlp3.Add(hclMCSubtract_jjlp3);hbbMCSubtract_jjlp5.Add(hclMCSubtract_jjlp5);
  hbbMCSubtract_jjlp2.Add(hllMCSubtract_jjlp2);hbbMCSubtract_jjlp3.Add(hllMCSubtract_jjlp3);hbbMCSubtract_jjlp5.Add(hllMCSubtract_jjlp5);

  if test == True:
    ROOT.gROOT.SetBatch(True)
    ROOT.gStyle.SetPaintTextFormat("4.2f")
    c1 = ROOT.TCanvas("c1")
    hbbMCSubtract_jjlp3.Draw("hist text65")
    hbbMCSubtract_jjlp3.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hbbMCSubtract_jjlp3.pdf")
    del c1
    c1 = ROOT.TCanvas("c1")
    hbbMCSubtract_jjlp2.Draw("hist text65")
    hbbMCSubtract_jjlp2.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hbbMCSubtract_jjlp2.pdf")
    del c1
    c1 = ROOT.TCanvas("c1")
    hbbMCSubtract_jjlp5.Draw("hist text65")
    hbbMCSubtract_jjlp5.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hbbMCSubtract_jjlp5.pdf")
    del c1
    c1 = ROOT.TCanvas("c1")
    hbbMCSubtract_yjlp3.Draw("hist text65")
    hbbMCSubtract_yjlp3.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hbbMCSubtract_yjlp3.pdf")
    del c1
    c1 = ROOT.TCanvas("c1")
    hbbMCSubtract_yjlp2.Draw("hist text65")
    hbbMCSubtract_yjlp2.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hbbMCSubtract_yjlp2.pdf")
    del c1
    c1 = ROOT.TCanvas("c1")
    hbbMCSubtract_yjlp5.Draw("hist text65")
    hbbMCSubtract_yjlp5.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hbbMCSubtract_yjlp5.pdf")
    del c1

  fyj = ROOT.TFile("inputs_yj"+str(MET)+".root","RECREATE");fyj.cd();hyjtrue = myDataFakeslp3.Get("histyj_lp3"+str(MET));hyjtrue.SetName("hist_DL1");
  # print "original yj"
  # hyjtrue.Print("all")
  fyj_nosub = ROOT.TFile("inputs_yj_nosub"+str(MET)+".root","RECREATE");fyj_nosub.cd();hyjtrue_nosub = hyjtrue.Clone("hist_DL1");
  # print "nosub cloned yj"
  # hyjtrue_nosub.Print("all") 

  fyj_lp2 = ROOT.TFile("inputs_yj_lp2"+str(MET)+".root","RECREATE");fyj_lp2.cd();hyjtrue_lp2 = myDataFakeslp2.Get("histyj_lp2"+str(MET));hyjtrue_lp2.SetName("hist_DL1");
  fyj_lp5 = ROOT.TFile("inputs_yj_lp5"+str(MET)+".root","RECREATE");fyj_lp5.cd();hyjtrue_lp5 = myDataFakeslp5.Get("histyj_lp5"+str(MET));hyjtrue_lp5.SetName("hist_DL1");
  fyj_systup = ROOT.TFile("inputs_yj_systup"+str(MET)+".root","RECREATE");fyj_systup.cd();hyjtrue_systup = hyjtrue.Clone("hist_DL1");
  fyj_systdown = ROOT.TFile("inputs_yj_systdown"+str(MET)+".root","RECREATE");fyj_systdown.cd();hyjtrue_systdown = hyjtrue.Clone("hist_DL1");


  fjj = ROOT.TFile("inputs_jj"+str(MET)+".root","RECREATE");fjj.cd();hjjtrue = myDataFakeslp3.Get("histjj_lp3"+str(MET));hjjtrue.SetName("hist_DL1");
  # print "original jj"
  # hjjtrue.Print("all")

  fjj_nosub = ROOT.TFile("inputs_jj_nosub"+str(MET)+".root","RECREATE");fjj_nosub.cd();hjjtrue_nosub = hjjtrue.Clone("hist_DL1");
  # print "nosub cloned jj"
  # hjjtrue_nosub.Print("all") 

  fjj_lp2 = ROOT.TFile("inputs_jj_lp2"+str(MET)+".root","RECREATE");fjj_lp2.cd();hjjtrue_lp2 = myDataFakeslp2.Get("histjj_lp2"+str(MET));hjjtrue_lp2.SetName("hist_DL1");
  fjj_lp5 = ROOT.TFile("inputs_jj_lp5"+str(MET)+".root","RECREATE");fjj_lp5.cd();hjjtrue_lp5 = myDataFakeslp5.Get("histjj_lp5"+str(MET));hjjtrue_lp5.SetName("hist_DL1");
  fjj_systup = ROOT.TFile("inputs_jj_systup"+str(MET)+".root","RECREATE");fjj_systup.cd();hjjtrue_systup = hjjtrue.Clone("hist_DL1");
  fjj_systdown = ROOT.TFile("inputs_jj_systdown"+str(MET)+".root","RECREATE");fjj_systdown.cd();hjjtrue_systdown = hjjtrue.Clone("hist_DL1");

  if test == True:
    # ROOT.gROOT.SetBatch(True)
    c1 = ROOT.TCanvas("c1")
    hjjtrue_nosub.Draw("hist text45")
    hjjtrue_nosub.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hjjtrue_nosub.pdf")
    del c1

    # ROOT.gROOT.SetBatch(True)
    c1 = ROOT.TCanvas("c1")
    hjjtrue.Draw("hist text45")
    hjjtrue.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hjjtrue_presubtraction.pdf")
    del c1

    c1 = ROOT.TCanvas("c1")
    hyjtrue_nosub.Draw("hist text45")
    hyjtrue_nosub.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hyjtrue_nosub.pdf")
    del c1

    # ROOT.gROOT.SetBatch(True)
    c1 = ROOT.TCanvas("c1")
    hyjtrue.Draw("hist text45")
    hyjtrue.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hyjtrue_presubtraction.pdf")
    del c1

    c1 = ROOT.TCanvas("c1")
    hjjtrue_lp2.Draw("hist text45")
    hjjtrue_lp2.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hjjtrue_lp2_presubtraction.pdf")
    del c1
    c1 = ROOT.TCanvas("c1")
    hjjtrue_lp5.Draw("hist text45")
    hjjtrue_lp5.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hjjtrue_lp5_presubtraction.pdf")
    del c1

    c1 = ROOT.TCanvas("c1")
    hyjtrue_lp5.Draw("hist text45")
    hyjtrue_lp5.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hyjtrue_lp5_presubtraction.pdf")
    del c1
    c1 = ROOT.TCanvas("c1")
    hyjtrue_lp2.Draw("hist text45")
    hyjtrue_lp2.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hyjtrue_lp2_presubtraction.pdf")
    del c1


    print "Integrals:  jj: ", hjjtrue.Integral(), "  jj_nosub: ", hjjtrue_nosub.Integral(), "  jjsubtraction: ", hbbMCSubtract_jjlp3.Integral()
  # #Integrals:  jj:  123332.0   jj_nosub:  49429.0
  # # Integrals:  jj:  -2.07956691254e+12   jj_nosub:  49429.0 (post subtraction)
  # # print "subtracted from"
  # # hbbMCSubtract_yjlp3.Print("all")
  # # hbbMCSubtract_yjlp2.Print("all")
  # # hbbMCSubtract_yjlp5.Print("all")
  # # hbbMCSubtract_jjlp3.Print("all")
  # # hbbMCSubtract_jjlp2.Print("all")
  # # hbbMCSubtract_jjlp5.Print("all")
  # print "modifying true - subtraction"
  # # hjjtrue.Print("all")
  # ##Subtracting mc yy from data fakes
  # # hyjtrue.Print("all")
  # hjjtrue.Print("all")#has value in bin 26


  hyjtrue.Add(hbbMCSubtract_yjlp3,-1);hyjtrue_lp2.Add(hbbMCSubtract_yjlp2,-1);hyjtrue_lp5.Add(hbbMCSubtract_yjlp5,-1);
  hjjtrue.Add(hbbMCSubtract_jjlp3,-1);hjjtrue_lp2.Add(hbbMCSubtract_jjlp2,-1);hjjtrue_lp5.Add(hbbMCSubtract_jjlp5,-1);
  # hjjtrue.Print("all")
  hyjtrue_systup.Add(hbbMCSubtract_yjlp3,-1);hyjtrue_systdown.Add(hbbMCSubtract_yjlp3,-1);
  hjjtrue_systup.Add(hbbMCSubtract_jjlp3,-1);hjjtrue_systdown.Add(hbbMCSubtract_jjlp3,-1);

  # hyjtrue.Sumw2();hyjtrue_lp2.Sumw2();hyjtrue_lp5.Sumw2();hjjtrue.Sumw2();hjjtrue_lp2.Sumw2();hjjtrue_lp5.Sumw2();
  # hyjtrue_systup.Sumw2();hjjtrue_systup.Sumw2();hyjtrue_systdown.Sumw2();hjjtrue_systdown.Sumw2();

  if test == True:
    # ROOT.gROOT.SetBatch(True)
    c1 = ROOT.TCanvas("c1")
    hjjtrue.Draw("hist text45")
    hjjtrue.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hjjtrue_postsubtraction.pdf")
    del c1
    c1 = ROOT.TCanvas("c1")
    hyjtrue.Draw("hist text45")
    hyjtrue.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hyjtrue_postsubtraction.pdf")
    del c1
    c1 = ROOT.TCanvas("c1")
    hyjtrue_lp2.Draw("hist text45")
    hyjtrue_lp2.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hyjtrue_lp2_postsubtraction.pdf")
    del c1
    c1 = ROOT.TCanvas("c1")
    hyjtrue_lp5.Draw("hist text45")
    hyjtrue_lp5.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hyjtrue_lp5_postsubtraction.pdf")
    del c1
    c1 = ROOT.TCanvas("c1")
    hjjtrue_lp2.Draw("hist text45")
    hjjtrue_lp2.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hjjtrue_lp2_postsubtraction.pdf")
    del c1
    c1 = ROOT.TCanvas("c1")
    hjjtrue_lp5.Draw("hist text45")
    hjjtrue_lp5.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hjjtrue_lp5_postsubtraction.pdf")
    del c1


    print "bls printing"
    # hjjtrue.Print("all")


  print "Getting pruities from decomp file"
  yy_purity = myDecomp.Get("gr_inclusive_gg_purity_TotErr");
  yj_purity = myDecomp.Get("gr_inclusive_gjjg_purity_TotErr");
  jj_purity = myDecomp.Get("gr_inclusive_jj_purity_TotErr");

  yj_purity_syst = myDecomp.Get("gr_inclusive_gjjg_purity_SystErr");
  jj_purity_syst = myDecomp.Get("gr_inclusive_jj_purity_SystErr");


  yy_purityval = yy_purity.GetPointY(0)
  yj_purityval = yj_purity.GetPointY(0)
  jj_purityval = jj_purity.GetPointY(0)
  print yy_purityval
  print yj_purityval
  print jj_purityval
  print "bls check up"
  yj_purityval_statup = yj_purityval + yj_purity.GetErrorYhigh(0);
  yj_purityval_statdown = yj_purityval - yj_purity.GetErrorYlow(0);
  yj_purityval_systup = yj_purityval + yj_purity_syst.GetErrorYhigh(0);
  yj_purityval_systdown = yj_purityval - yj_purity_syst.GetErrorYlow(0);
  jj_purityval_statup = jj_purityval + jj_purity.GetErrorYhigh(0);
  jj_purityval_statdown = jj_purityval - jj_purity.GetErrorYlow(0);
  jj_purityval_systup = jj_purityval + jj_purity_syst.GetErrorYhigh(0);
  jj_purityval_systdown = jj_purityval - jj_purity_syst.GetErrorYlow(0);

  # # hjjtrue_nosub.Print("all")
  # print "precaling"
  # # hyjtrue.Print("all")
  # hjjtrue.Print("all")#has value in bin 26
  # # hyjtrue_nosub.Print("all")
  # hjjtrue_nosub.Print("all")

  # print "scale factor: ", jj_purityval * (yymctot/yy_purityval)
  # print "Integrals:  jj: ", hjjtrue.Integral(), "  jj_nosub: ", hjjtrue_nosub.Integral()
  hyjtrue.Scale(yj_purityval * (yymctot/yy_purityval)/hyjtrue.Integral());
  hjjtrue.Scale(jj_purityval * (yymctot/yy_purityval)/hjjtrue.Integral());
  hyjtrue_nosub.Scale(yj_purityval * (yymctot/yy_purityval)/hyjtrue_nosub.Integral());
  hjjtrue_nosub.Scale(jj_purityval * (yymctot/yy_purityval)/hjjtrue_nosub.Integral());
  # print "post-scaling"
  # # hyjtrue.Print("all")
  # hjjtrue.Print("all")#bin value is -4.25227e-05
  # # hyjtrue_nosub.Print("all")
  # hjjtrue_nosub.Print("all")#bin value is 27.3779

  hyjtrue_lp2.Scale(yj_purityval * (yymctot/yy_purityval)/hyjtrue_lp2.Integral());
  hjjtrue_lp2.Scale(jj_purityval * (yymctot/yy_purityval)/hjjtrue_lp2.Integral());
  hyjtrue_lp5.Scale(yj_purityval * (yymctot/yy_purityval)/hyjtrue_lp5.Integral());
  hjjtrue_lp5.Scale(jj_purityval * (yymctot/yy_purityval)/hjjtrue_lp5.Integral());

  # hjjtrue_nosub.Print("all")

  hyjtrue_systup.Scale(yj_purityval_systup * (yymctot/yy_purityval)/hyjtrue_systup.Integral());
  hyjtrue_systdown.Scale(yj_purityval_systdown * (yymctot/yy_purityval)/hyjtrue_systdown.Integral());

  hjjtrue_systup.Scale(jj_purityval_systup * (yymctot/yy_purityval)/hjjtrue_systup.Integral());
  hjjtrue_systdown.Scale(jj_purityval_systdown * (yymctot/yy_purityval)/hjjtrue_systdown.Integral());

  if test == True:
    # ROOT.gROOT.SetBatch(True)
    c1 = ROOT.TCanvas("c1")
    hjjtrue.Draw("hist text45")
    hjjtrue.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hjjtrue_postscaling.pdf")
    del c1

    # ROOT.gROOT.SetBatch(True)
    c1 = ROOT.TCanvas("c1")
    hjjtrue_nosub.Draw("hist text45")
    hjjtrue_nosub.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hjjtrue_nosub_postscaling.pdf")
    del c1


    c1 = ROOT.TCanvas("c1")
    hyjtrue.Draw("hist text45")
    hyjtrue.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hyjtrue_postscaling.pdf")
    del c1

    # ROOT.gROOT.SetBatch(True)
    c1 = ROOT.TCanvas("c1")
    hyjtrue_nosub.Draw("hist text45")
    hyjtrue_nosub.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hyjtrue_nosub_postscaling.pdf")
    del c1

    c1 = ROOT.TCanvas("c1")
    hyjtrue_lp2.Draw("hist text45")
    hyjtrue_lp2.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hyjtrue_lp2_postscaling.pdf")
    del c1
    c1 = ROOT.TCanvas("c1")
    hyjtrue_lp5.Draw("hist text45")
    hyjtrue_lp5.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hyjtrue_lp5_postscaling.pdf")
    del c1

    c1 = ROOT.TCanvas("c1")
    hjjtrue_lp2.Draw("hist text45")
    hjjtrue_lp2.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hjjtrue_lp2_postscaling.pdf")
    del c1
    c1 = ROOT.TCanvas("c1")
    hjjtrue_lp5.Draw("hist text45")
    hjjtrue_lp5.SetMarkerSize(1.6)
    c1.SetLogy()
    c1.SaveAs("hjjtrue_lp5_postscaling.pdf")
    del c1

  # hjjtrue.Print("all")
  print "Checking for negative values in histograms"
  Fix(hyjtrue);
  Fix(hyjtrue_nosub);
  Fix(hyjtrue_lp2);
  Fix(hyjtrue_lp5);
  Fix(hyjtrue_systup);
  Fix(hyjtrue_systdown);
  Fix(hjjtrue);
  Fix(hjjtrue_nosub);
  Fix(hjjtrue_lp2);
  Fix(hjjtrue_lp5);
  Fix(hjjtrue_systup);
  Fix(hjjtrue_systdown);

  # hjjtrue.Print("all")
  # hjjtrue_nosub.Print("all")



  my_yj = hyjtrue.GetBinContent(binnumber) 
  my_jj = hjjtrue.GetBinContent(binnumber) 



  # hist_total.Add(hyjtrue)
  # hist_total.Add(hjjtrue)


  
  # print "My yjtot is " + str(hyjtrue.Integral())
  # print "My jjmctot is " + str(hjjtrue.Integral())
  
  # hist_relative_fraction_yj = hyjtrue.Clone("hist_DL1")
  # hist_relative_fraction_jj = hjjtrue.Clone("hist_DL1")


  # hist_relative_fraction_yy.Divide(hist_total)
  # hist_relative_fraction_yj.Divide(hist_total)
  # hist_relative_fraction_jj.Divide(hist_total)


  # hist_relative_fraction_yy.SetFillColorAlpha(ROOT.kOrange+2,0.6);hist_relative_fraction_yy.SetTitle("yy")
  # hist_relative_fraction_yj.SetFillColorAlpha(ROOT.kCyan+3,0.6);hist_relative_fraction_yj.SetTitle("yj")
  # hist_relative_fraction_jj.SetFillColorAlpha(ROOT.kMagenta+2,0.6);hist_relative_fraction_jj.SetTitle("jj")

  # c1 = ROOT.TCanvas("c1", "")
  # relyieldStack = ROOT.THStack("yieldStack", "Relative Yields")
  # relyieldStack.Add(hist_relative_fraction_yy);
  # relyieldStack.Add(hist_relative_fraction_yj);
  # relyieldStack.Add(hist_relative_fraction_jj);
  # relyieldStack.Draw("HIST");
  # relyieldStack.GetXaxis().SetRangeUser(-0.5, 24.5)
  # # relyieldStack.GetYaxis().SetRangeUser(0.6, 1.)
  # relyieldStack.GetXaxis().SetTitle("(Leading DL1 bin * 5) + Subleading DL1")

  # c1.BuildLegend()
  # c1.SaveAs("fakesrelativeStack"+str(MET)+".pdf")


  print "Creating output files"
  fyj.cd();
  hyjtrue.Write();

  fyj_nosub.cd();
  hyjtrue_nosub.Write();

  fjj_nosub.cd();
  hjjtrue_nosub.Write();

  fyj_lp2.cd();
  hyjtrue_lp2.Write();

  fyj_lp5.cd();
  hyjtrue_lp5.Write();


  fyj_systup.cd();
  hyjtrue_systup.Write();

  fyj_systdown.cd();
  hyjtrue_systdown.Write();


  fjj.cd();
  hjjtrue.Write();

  fjj_lp2.cd();
  hjjtrue_lp2.Write();

  fjj_lp5.cd();
  hjjtrue_lp5.Write();

  fjj_systup.cd();
  hjjtrue_systup.Write();

  fjj_systdown.cd();
  hjjtrue_systdown.Write();




  # print "Done."
  # print "yy in bin ", binnumber, " : ", my_yy
  # print "yj in bin ", binnumber, " : ", my_yj
  # print "jj in bin ", binnumber, " : ", my_jj
  # my_total = my_yy + my_yj + my_jj
  # print "total sum is ",my_total
  # print "yy fraction: ", my_yy/my_total
  # print "yj fraction: ", my_yj/my_total
  # print "jj fraction: ", my_jj/my_total
