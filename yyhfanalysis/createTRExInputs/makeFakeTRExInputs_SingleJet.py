import ROOT


def Fix(hist):
  n = hist.GetNbinsX();
  for i in range(n+1):
    # print i, hist.GetBinContent(i)
    if (hist.GetBinContent(i) < 0): hist.SetBinContent(i,1e-6);



mySherpa = ROOT.TFile("/home/bstamas/xdata/yyhf/inputHistMaker/outputs/master.Sherpa2_diphoton_myy_ALL_AF2.Nominal_combinedCR.root", "READ")

# myZqqyy = ROOT.TFile("/home/bstamas/xdata/yyhf/testingInputMakers/outputs/master.Sh_2211_Zqqyy_myy95.Nominal_combinedCR.root", "READ")
# myZbbyy = ROOT.TFile("/home/bstamas/xdata/yyhf/testingInputMakers/outputs/master.Sh_2211_Zbbyy_myy95.Nominal_combinedCR.root", "READ")
# myttyy = ROOT.TFile("/home/bstamas/xdata/yyhf/testingInputMakers/outputs/master.MGPy8_ttgammagamma_AF2.Nominal_combinedCR.root", "READ")

myDataFakeslp2 = ROOT.TFile("/home/bstamas/xdata/yyhf/makeDataHists/combinedData_lp2_singlejet.root", "READ")#don't need to redo with new CRs
myDataFakeslp3 = ROOT.TFile("/home/bstamas/xdata/yyhf/makeDataHists/combinedData_lp3_singlejet.root", "READ")#don't need to redo with new CRs
myDataFakeslp5 = ROOT.TFile("/home/bstamas/xdata/yyhf/makeDataHists/combinedData_lp5_singlejet.root", "READ")#don't need to redo with new CRs
myMCSubtract = ROOT.TFile("/home/bstamas/xdata/yyhf/makeSubtractionHists/master.Sherpa2_diphoton_myy_ALL_AF2.subtractionResults.root")
myDecomp = ROOT.TFile("/home/bstamas/xdata/yyhf/makeTRExFitterInputs/HGam_13TeV_2x2DBkgDComp_SherpaAF2_139.0ifb_XSection_allInputs.root", "READ")

METoptions = ["_noMET", ""]

for MET in METoptions:
  print "Getting sherpa intput histograms"
  hb = mySherpa.Get("histb"+str(MET));
  hc = mySherpa.Get("histc"+str(MET));
  hl = mySherpa.Get("histl"+str(MET));

  yymctot = hb.Integral() + hc.Integral() +hl.Integral()
  print "My yymctot is " + str(yymctot)

  hb.Sumw2();hc.Sumw2();hl.Sumw2();

  hyy = hb.Clone("hist_DL1");hyy.Add(hc);hyy.Add(hl);

  print "Creating new output files for sherpa"
  fb = ROOT.TFile("inputs_b"+str(MET)+".root","RECREATE");fb.cd();hbtrue = hb.Clone("hist_DL1");
  fc = ROOT.TFile("inputs_c"+str(MET)+".root","RECREATE");fc.cd();hctrue = hc.Clone("hist_DL1");
  fl = ROOT.TFile("inputs_l"+str(MET)+".root","RECREATE");fl.cd();hltrue = hl.Clone("hist_DL1");


  hbtrue.Sumw2();hctrue.Sumw2();hltrue.Sumw2();

  # print "Writing sherpa output files"
  # fb.cd();hbtrue.Write();
  # fc.cd();hctrue.Write();
  # fl.cd();hltrue.Write();

  print "Done"

  print "Getting fakes histograms"
  hbMCSubtract_yjlp2 = myMCSubtract.Get("histb"+str(MET)+"_yjlp2");hbMCSubtract_yjlp3 = myMCSubtract.Get("histb"+str(MET)+"_yjlp3");hbMCSubtract_yjlp5 = myMCSubtract.Get("histb"+str(MET)+"_yjlp5")
  hcMCSubtract_yjlp2 = myMCSubtract.Get("histc"+str(MET)+"_yjlp2");hcMCSubtract_yjlp3 = myMCSubtract.Get("histc"+str(MET)+"_yjlp3");hcMCSubtract_yjlp5 = myMCSubtract.Get("histc"+str(MET)+"_yjlp5")
  hlMCSubtract_yjlp2 = myMCSubtract.Get("histl"+str(MET)+"_yjlp2");hlMCSubtract_yjlp3 = myMCSubtract.Get("histl"+str(MET)+"_yjlp3");hlMCSubtract_yjlp5 = myMCSubtract.Get("histl"+str(MET)+"_yjlp5")
  hbMCSubtract_jjlp2 = myMCSubtract.Get("histb"+str(MET)+"_jjlp2");hbMCSubtract_jjlp3 = myMCSubtract.Get("histb"+str(MET)+"_jjlp3");hbMCSubtract_jjlp5 = myMCSubtract.Get("histb"+str(MET)+"_jjlp5")
  hcMCSubtract_jjlp2 = myMCSubtract.Get("histc"+str(MET)+"_jjlp2");hcMCSubtract_jjlp3 = myMCSubtract.Get("histc"+str(MET)+"_jjlp3");hcMCSubtract_jjlp5 = myMCSubtract.Get("histc"+str(MET)+"_jjlp5")
  hlMCSubtract_jjlp2 = myMCSubtract.Get("histl"+str(MET)+"_jjlp2");hlMCSubtract_jjlp3 = myMCSubtract.Get("histl"+str(MET)+"_jjlp3");hlMCSubtract_jjlp5 = myMCSubtract.Get("histl"+str(MET)+"_jjlp5")

  hbMCSubtract_yjlp2.Sumw2();hbMCSubtract_yjlp3.Sumw2();hbMCSubtract_yjlp5.Sumw2()
  hcMCSubtract_yjlp2.Sumw2();hcMCSubtract_yjlp3.Sumw2();hcMCSubtract_yjlp5.Sumw2()
  hlMCSubtract_yjlp2.Sumw2();hlMCSubtract_yjlp3.Sumw2();hlMCSubtract_yjlp5.Sumw2()
  hbMCSubtract_jjlp2.Sumw2();hbMCSubtract_jjlp3.Sumw2();hbMCSubtract_jjlp5.Sumw2()
  hcMCSubtract_jjlp2.Sumw2();hcMCSubtract_jjlp3.Sumw2();hcMCSubtract_jjlp5.Sumw2()
  hlMCSubtract_jjlp2.Sumw2();hlMCSubtract_jjlp3.Sumw2();hlMCSubtract_jjlp5.Sumw2()

  ## Combining all flavor combinations into single histogram hb* for each lp WP
  hbMCSubtract_yjlp2.Add(hcMCSubtract_yjlp2);hbMCSubtract_yjlp3.Add(hcMCSubtract_yjlp3);hbMCSubtract_yjlp5.Add(hcMCSubtract_yjlp5);
  hbMCSubtract_yjlp2.Add(hlMCSubtract_yjlp2);hbMCSubtract_yjlp3.Add(hlMCSubtract_yjlp3);hbMCSubtract_yjlp5.Add(hlMCSubtract_yjlp5);
  hbMCSubtract_jjlp2.Add(hcMCSubtract_jjlp2);hbMCSubtract_jjlp3.Add(hcMCSubtract_jjlp3);hbMCSubtract_jjlp5.Add(hcMCSubtract_jjlp5);
  hbMCSubtract_jjlp2.Add(hlMCSubtract_jjlp2);hbMCSubtract_jjlp3.Add(hlMCSubtract_jjlp3);hbMCSubtract_jjlp5.Add(hlMCSubtract_jjlp5);

  fyj = ROOT.TFile("inputs_yj"+str(MET)+".root","RECREATE");fyj.cd();hyjtrue = myDataFakeslp3.Get("histyj_lp3"+str(MET));hyjtrue.SetName("hist_DL1");
  fyj_nosub = ROOT.TFile("inputs_yj_nosub"+str(MET)+".root","RECREATE");fyj_nosub.cd();hyjtrue_nosub = hyjtrue.Clone("hist_DL1");
  fyj_lp2 = ROOT.TFile("inputs_yj_lp2"+str(MET)+".root","RECREATE");fyj_lp2.cd();hyjtrue_lp2 = myDataFakeslp2.Get("histyj_lp2"+str(MET));hyjtrue_lp2.SetName("hist_DL1");
  fyj_lp5 = ROOT.TFile("inputs_yj_lp5"+str(MET)+".root","RECREATE");fyj_lp5.cd();hyjtrue_lp5 = myDataFakeslp5.Get("histyj_lp5"+str(MET));hyjtrue_lp5.SetName("hist_DL1");
  fyj_systup = ROOT.TFile("inputs_yj_systup"+str(MET)+".root","RECREATE");fyj_systup.cd();hyjtrue_systup = hyjtrue.Clone("hist_DL1");
  fyj_systdown = ROOT.TFile("inputs_yj_systdown"+str(MET)+".root","RECREATE");fyj_systdown.cd();hyjtrue_systdown = hyjtrue.Clone("hist_DL1");


  fjj = ROOT.TFile("inputs_jj"+str(MET)+".root","RECREATE");fjj.cd();hjjtrue = myDataFakeslp3.Get("histjj_lp3"+str(MET));hjjtrue.SetName("hist_DL1");
  fjj_nosub = ROOT.TFile("inputs_jj_nosub"+str(MET)+".root","RECREATE");fjj_nosub.cd();hjjtrue_nosub = hjjtrue.Clone("hist_DL1");
  fjj_lp2 = ROOT.TFile("inputs_jj_lp2"+str(MET)+".root","RECREATE");fjj_lp2.cd();hjjtrue_lp2 = myDataFakeslp2.Get("histjj_lp2"+str(MET));hjjtrue_lp2.SetName("hist_DL1");
  fjj_lp5 = ROOT.TFile("inputs_jj_lp5"+str(MET)+".root","RECREATE");fjj_lp5.cd();hjjtrue_lp5 = myDataFakeslp5.Get("histjj_lp5"+str(MET));hjjtrue_lp5.SetName("hist_DL1");
  fjj_systup = ROOT.TFile("inputs_jj_systup"+str(MET)+".root","RECREATE");fjj_systup.cd();hjjtrue_systup = hjjtrue.Clone("hist_DL1");
  fjj_systdown = ROOT.TFile("inputs_jj_systdown"+str(MET)+".root","RECREATE");fjj_systdown.cd();hjjtrue_systdown = hjjtrue.Clone("hist_DL1");

  # hjjtrue.Print("all")
  ##Subtracting mc yy from data fakes
  # print("bls1")
  hyjtrue.Add(hbMCSubtract_yjlp3,-1);hyjtrue_lp2.Add(hbMCSubtract_yjlp2,-1);hyjtrue_lp5.Add(hbMCSubtract_yjlp5,-1);
  hjjtrue.Add(hbMCSubtract_jjlp3,-1);hjjtrue_lp2.Add(hbMCSubtract_jjlp2,-1);hjjtrue_lp5.Add(hbMCSubtract_jjlp5,-1);
  # print("bls2")

  # hjjtrue.Print("all")
  hyjtrue_systup.Add(hbMCSubtract_yjlp3,-1);hyjtrue_systdown.Add(hbMCSubtract_yjlp3,-1);
  hjjtrue_systup.Add(hbMCSubtract_jjlp3,-1);hjjtrue_systdown.Add(hbMCSubtract_jjlp3,-1);

  hyjtrue.Sumw2();hyjtrue_lp2.Sumw2();hyjtrue_lp5.Sumw2();hjjtrue.Sumw2();hjjtrue_lp2.Sumw2();hjjtrue_lp5.Sumw2();
  hyjtrue_systup.Sumw2();hjjtrue_systup.Sumw2();hyjtrue_systdown.Sumw2();hjjtrue_systdown.Sumw2();

  print "Getting pruities from decomp file"
  yy_purity = myDecomp.Get("gr_inclusive_gg_purity_TotErr");
  yj_purity = myDecomp.Get("gr_inclusive_gjjg_purity_TotErr");
  jj_purity = myDecomp.Get("gr_inclusive_jj_purity_TotErr");

  yj_purity_syst = myDecomp.Get("gr_inclusive_gjjg_purity_SystErr");
  jj_purity_syst = myDecomp.Get("gr_inclusive_jj_purity_SystErr");


  yy_purityval = yy_purity.GetPointY(0)
  yj_purityval = yj_purity.GetPointY(0)
  jj_purityval = jj_purity.GetPointY(0)

  yj_purityval_statup = yj_purityval + yj_purity.GetErrorYhigh(0);
  yj_purityval_statdown = yj_purityval - yj_purity.GetErrorYlow(0);
  yj_purityval_systup = yj_purityval + yj_purity_syst.GetErrorYhigh(0);
  yj_purityval_systdown = yj_purityval - yj_purity_syst.GetErrorYlow(0);
  jj_purityval_statup = jj_purityval + jj_purity.GetErrorYhigh(0);
  jj_purityval_statdown = jj_purityval - jj_purity.GetErrorYlow(0);
  jj_purityval_systup = jj_purityval + jj_purity_syst.GetErrorYhigh(0);
  jj_purityval_systdown = jj_purityval - jj_purity_syst.GetErrorYlow(0);

  # hjjtrue_nosub.Print("all")

  hyjtrue.Scale(yj_purityval * (yymctot/yy_purityval)/hyjtrue.Integral());
  hjjtrue.Scale(jj_purityval * (yymctot/yy_purityval)/hjjtrue.Integral());
  hyjtrue_nosub.Scale(yj_purityval * (yymctot/yy_purityval)/hyjtrue_nosub.Integral());
  hjjtrue_nosub.Scale(jj_purityval * (yymctot/yy_purityval)/hjjtrue_nosub.Integral());
  hyjtrue_lp2.Scale(yj_purityval * (yymctot/yy_purityval)/hyjtrue_lp2.Integral());
  hjjtrue_lp2.Scale(jj_purityval * (yymctot/yy_purityval)/hjjtrue_lp2.Integral());
  hyjtrue_lp5.Scale(yj_purityval * (yymctot/yy_purityval)/hyjtrue_lp5.Integral());
  hjjtrue_lp5.Scale(jj_purityval * (yymctot/yy_purityval)/hjjtrue_lp5.Integral());

  # hjjtrue_nosub.Print("all")

  hyjtrue_systup.Scale(yj_purityval_systup * (yymctot/yy_purityval)/hyjtrue_systup.Integral());
  hyjtrue_systdown.Scale(yj_purityval_systdown * (yymctot/yy_purityval)/hyjtrue_systdown.Integral());

  hjjtrue_systup.Scale(jj_purityval_systup * (yymctot/yy_purityval)/hjjtrue_systup.Integral());
  hjjtrue_systdown.Scale(jj_purityval_systdown * (yymctot/yy_purityval)/hjjtrue_systdown.Integral());

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

  # fb.cd();
  # hbtrue.Write();

  # fc.cd();
  # hctrue.Write();

  # fl.cd();
  # hltrue.Write();



  print "Done."