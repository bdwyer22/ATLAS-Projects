import ROOT


inputSignalSamples = ["Sherpa2_diphoton_myy_ALL_AF2", "Sh_2211_Zyy_myy95", "MGPy8_ttgammagamma_AF2", "aMCPy8_2a_2j_FxFx",  "H_yy"] #"Pythia8_2DP20_ALL"
inputBackgroundSamples = ["MGPy8_ttgamma_nonallhadronic_AF2", "Sherpa_tt_dilepton", "aMCPy8_2a_2j_FxFx"]#, "Pythia8_2DP20_ALL"]

def Fix(hist):
	n = hist.GetNbinsX();
	for i in range(n+1):
	  if (hist.GetBinContent(i) < 0): hist.SetBinContent(i,1e-6);

def BackgroundDijetHistograms(inputFile, sampleName):
	print "Creaing dijet histograms for background ", sampleName
	print "Using file: ", inputFile
	myHistoFile = ROOT.TFile(inputFile, "READ");
	hbb = myHistoFile.Get("histbb");hbb_noMET = myHistoFile.Get("histbb_noMET");
	hbc = myHistoFile.Get("histbc");hbc_noMET = myHistoFile.Get("histbc_noMET");
	hbl = myHistoFile.Get("histbl");hbl_noMET = myHistoFile.Get("histbl_noMET");
	hcc = myHistoFile.Get("histcc");hcc_noMET = myHistoFile.Get("histcc_noMET");
	hcl = myHistoFile.Get("histcl");hcl_noMET = myHistoFile.Get("histcl_noMET");
	hll = myHistoFile.Get("histll");hll_noMET = myHistoFile.Get("histll_noMET");

	mctot = hbb.Integral() + hbc.Integral() + hbl.Integral() + hcc.Integral() + hcl.Integral() + hll.Integral();

	hbb.Sumw2();hbb_noMET.Sumw2();
	hbc.Sumw2();hbc_noMET.Sumw2();
	hbl.Sumw2();hbl_noMET.Sumw2();
	hcc.Sumw2();hcc_noMET.Sumw2();
	hcl.Sumw2();hcl_noMET.Sumw2();
	hll.Sumw2();hll_noMET.Sumw2();

	if sampleName == "MGPy8_ttgamma_nonallhadronic_AF2": outputName = "tty"
	elif sampleName == "Sherpa_tt_dilepton": outputName = "tt"
	elif sampleName == "aMCPy8_2a_2j_FxFx": outputName = "yy_fxfx"
	elif sampleName == "Pythia8_2DP20_ALL": outputName = "yy_py"

	# ORoption = ""
	# if useOR == False and (sampleName == "Sherpa_tt_dilepton" or sampleName == "MGPy8_ttgamma_nonallhadronic_AF2"):
	# 	ORoption = "_noOR"

	myOutputFile = ROOT.TFile("inputs_"+outputName+".root","RECREATE")
	myOutputFile_noMET = ROOT.TFile("inputs_"+outputName+"_noMET.root","RECREATE")
	myOutputFile.cd();

	hist = hbb.Clone("hist_DL1")
	hist.Add(hbc);
	hist.Add(hbl);
	hist.Add(hcc);
	hist.Add(hcl);
	hist.Add(hll); 
	Fix(hist)
	hist.Write()

	myOutputFile_noMET.cd()
	hist_noMET = hbb_noMET.Clone("hist_DL1")
	hist_noMET.Add(hbc_noMET);
	hist_noMET.Add(hbl_noMET);
	hist_noMET.Add(hcc_noMET);
	hist_noMET.Add(hcl_noMET);
	hist_noMET.Add(hll_noMET); 
	Fix(hist_noMET)    
	hist_noMET.Write();

def BackgroundMonojetHistograms(inputFile, sampleName):
	print "Creaing single jet histograms for background ", sampleName
	print "Using file: ", inputFile
	myHistoFile = ROOT.TFile(inputFile, "READ");
	hb = myHistoFile.Get("histb");hb_noMET = myHistoFile.Get("histb_noMET");
	hc = myHistoFile.Get("histc");hc_noMET = myHistoFile.Get("histc_noMET");
	hl = myHistoFile.Get("histl");hl_noMET = myHistoFile.Get("histl_noMET");
	
	mctot = hb.Integral() + hc.Integral() + hl.Integral()
	
	hb.Sumw2();hb_noMET.Sumw2();
	hc.Sumw2();hc_noMET.Sumw2();
	hl.Sumw2();hl_noMET.Sumw2();

	if sampleName == "MGPy8_ttgamma_nonallhadronic_AF2": outputName = "tty"
	elif sampleName == "Sherpa_tt_dilepton": outputName = "tt"
	elif sampleName == "aMCPy8_2a_2j_FxFx": outputName = "yy_fxfx"
	elif sampleName == "Pythia8_2DP20_ALL": outputName = "yy_py"

	# ORoption = ""
	# if useOR == False and (sampleName == "Sherpa_tt_dilepton" or sampleName == "MGPy8_ttgamma_nonallhadronic_AF2"):
	# 	ORoption = "_noOR"

	myOutputFile = ROOT.TFile("singlejet_inputs_"+outputName+".root","RECREATE")
	myOutputFile_noMET = ROOT.TFile("singlejet_inputs_"+outputName+"_noMET.root","RECREATE")
	myOutputFile.cd();

	hist = hb.Clone("hist_DL1")
	hist.Add(hc);
	hist.Add(hl);
	Fix(hist)
	hist.Write()

	myOutputFile_noMET.cd()
	hist_noMET = hb_noMET.Clone("hist_DL1")
	hist_noMET.Add(hc_noMET);
	hist_noMET.Add(hl_noMET);
	Fix(hist_noMET)    
	hist_noMET.Write();


def SignalDijetHistograms(inputFile, sampleName):
	print "Creaing dijet histograms for signal ", sampleName
	print "Using file: ", inputFile
	myHistoFile = ROOT.TFile(inputFile, "READ");
	hbb = myHistoFile.Get("histbb");hbb_noMET = myHistoFile.Get("histbb_noMET");
	hbc = myHistoFile.Get("histbc");hbc_noMET = myHistoFile.Get("histbc_noMET");
	hbl = myHistoFile.Get("histbl");hbl_noMET = myHistoFile.Get("histbl_noMET");
	hcc = myHistoFile.Get("histcc");hcc_noMET = myHistoFile.Get("histcc_noMET");
	hcl = myHistoFile.Get("histcl");hcl_noMET = myHistoFile.Get("histcl_noMET");
	hll = myHistoFile.Get("histll");hll_noMET = myHistoFile.Get("histll_noMET");

	mctot = hbb.Integral() + hbc.Integral() + hbl.Integral() + hcc.Integral() + hcl.Integral() + hll.Integral();

	hbb.Sumw2();hbb_noMET.Sumw2();
	hbc.Sumw2();hbc_noMET.Sumw2();
	hbl.Sumw2();hbl_noMET.Sumw2();
	hcc.Sumw2();hcc_noMET.Sumw2();
	hcl.Sumw2();hcl_noMET.Sumw2();
	hll.Sumw2();hll_noMET.Sumw2();

	if sampleName == "Sherpa2_diphoton_myy_ALL_AF2": outputName = "yy"
	elif sampleName == "Sh_2211_Zyy_myy95": outputName = "zyy"
	elif sampleName == "MGPy8_ttgammagamma_AF2": outputName = "ttyy"
	elif sampleName == "aMCPy8_2a_2j_FxFx": outputName = "yy_fxfx"
	elif sampleName == "Pythia8_2DP20_ALL": outputName = "yy_py"
	elif sampleName == "H_yy": outputName = "hyy"

	METoptions = ["_noMET", ""]

	for MET in METoptions:
		fbb = ROOT.TFile("inputs_"+outputName+"_bb"+str(MET)+".root","RECREATE");fbb.cd();hbbtrue = hbb.Clone("hist_DL1");hbbtrue.Write();
		fbc = ROOT.TFile("inputs_"+outputName+"_bc"+str(MET)+".root","RECREATE");fbc.cd();hbctrue = hbc.Clone("hist_DL1");hbctrue.Write();
		fbl = ROOT.TFile("inputs_"+outputName+"_bl"+str(MET)+".root","RECREATE");fbl.cd();hbltrue = hbl.Clone("hist_DL1");hbltrue.Write();
		fcc = ROOT.TFile("inputs_"+outputName+"_cc"+str(MET)+".root","RECREATE");fcc.cd();hcctrue = hcc.Clone("hist_DL1");hcctrue.Write();
		fcl = ROOT.TFile("inputs_"+outputName+"_cl"+str(MET)+".root","RECREATE");fcl.cd();hcltrue = hcl.Clone("hist_DL1");hcltrue.Write();
		fll = ROOT.TFile("inputs_"+outputName+"_ll"+str(MET)+".root","RECREATE");fll.cd();hlltrue = hll.Clone("hist_DL1");hlltrue.Write();


def SignalMonojetHistograms(inputFile, sampleName):
	print "Creaing single jet histograms for signal ", sampleName
	print "Using file: ", inputFile
	myHistoFile = ROOT.TFile(inputFile, "READ");
	hb = myHistoFile.Get("histb");hb_noMET = myHistoFile.Get("histb_noMET");
	hc = myHistoFile.Get("histc");hc_noMET = myHistoFile.Get("histc_noMET");
	hl = myHistoFile.Get("histl");hl_noMET = myHistoFile.Get("histl_noMET");
	
	mctot = hb.Integral() + hc.Integral() + hl.Integral()
	
	hb.Sumw2();hb_noMET.Sumw2();
	hc.Sumw2();hc_noMET.Sumw2();
	hl.Sumw2();hl_noMET.Sumw2();

	if sampleName == "Sherpa2_diphoton_myy_ALL_AF2": outputName = "yy"
	elif sampleName == "Sh_2211_Zyy_myy95": outputName = "zyy"
	elif sampleName == "MGPy8_ttgammagamma_AF2": outputName = "ttyy"
	elif sampleName == "aMCPy8_2a_2j_FxFx": outputName = "yy_fxfx"
	elif sampleName == "Pythia8_2DP20_ALL": outputName = "yy_py"
	elif sampleName == "H_yy": outputName = "hyy"

	METoptions = ["_noMET", ""]
	# print outputName

	for MET in METoptions:
		fb = ROOT.TFile("inputs_"+outputName+"_b"+str(MET)+".root","RECREATE");fb.cd();hbtrue = hb.Clone("hist_DL1");hbtrue.Write();
		fc = ROOT.TFile("inputs_"+outputName+"_c"+str(MET)+".root","RECREATE");fc.cd();hctrue = hc.Clone("hist_DL1");hctrue.Write();
		fl = ROOT.TFile("inputs_"+outputName+"_l"+str(MET)+".root","RECREATE");fl.cd();hltrue = hl.Clone("hist_DL1");hltrue.Write();

def DijetSherpaFlavorUncertainty():
	print "Creaing single jet histograms for sherpa uncertainty "

	mySherpaNom = "/home/bstamas/xdata/yyhf/inputHistMaker/outputs/mc16a.Sherpa2_diphoton_myy_ALL_AF2.Nominal_combinedCR.root"
	mySherpaHF  = "/home/bstamas/xdata/yyhf/inputHistMaker/outputs/mc16a.Sh_2210_yybb_ALL_Nominal_combinedCR.root"
	myFullSherpa = "/home/bstamas/xdata/yyhf/makeTRExFitterInputs/inputs_yy_bb_noMET.root"

	print "Using nominal file: ", mySherpaNom
	print "Using flavor  file: ", mySherpaHF

	myNomFile = ROOT.TFile(mySherpaNom, "READ");
	myHFFile = ROOT.TFile(mySherpaHF, "READ");

	myFullFile = ROOT.TFile(myFullSherpa, "READ");


	hbb_Nom = myNomFile.Get("histbb");
	hbb_Nom_noMET = myNomFile.Get("histbb_noMET");
	hbb_HF = myHFFile.Get("histbb");
	hbb_HF_noMET = myHFFile.Get("histbb_noMET");

	# hbb_Full = myFullFile.Get("histbb");
	hbb_Full_noMET = myFullFile.Get("hist_DL1");


	hbb_Nom_noMET_nEntries = hbb_Nom_noMET.Integral()
	hbb_HF_noMET_nEntries = hbb_HF_noMET.Integral()
	hbb_Full_noMET_nEntries = hbb_Full_noMET.Integral()




	hbb_mc16a_subtracted_noMET = hbb_Nom_noMET.Clone("hist_DL1");
	hbb_mc16a_subtracted_noMET.Add(hbb_HF_noMET, -1)


	print "hbb_subtracted_noMET: ", hbb_mc16a_subtracted_noMET.Integral()
	print "hbb_Nom_noMET: ", hbb_Nom_noMET_nEntries
	print "hbb_HF_noMET: ", hbb_HF_noMET_nEntries
	print "hbb_Full_noMET: ", hbb_Full_noMET_nEntries


	hbb_Full_noMET.Add(hbb_mc16a_subtracted_noMET, -1)
	hbb_FullSubtracted_noMET_nEntries = hbb_Full_noMET.Integral()

	# myScaleFactor = (hbb_Full_noMET_nEntries / hbb_FullSubtracted_noMET_nEntries) * (hbb_HF_noMET_nEntries / hbb_Nom_noMET_nEntries)
	myScaleFactor = hbb_Full_noMET_nEntries / hbb_HF_noMET_nEntries

	hbb_Full_noMET.Scale(myScaleFactor)

	myOutputFile = ROOT.TFile("inputs_yy_bb_sherpa_HF_Uncertainty.root","RECREATE")
	# hbb_subtracted_noMET.Scale(1/myScaleFactor)

	# myNomOut = ROOT.TFile("inputs_yy_bb_sherpa_HF_Uncertainty__1up.root","RECREATE")
	# myNomOut_noMET = ROOT.TFile("inputs_yy_bb_sherpa_HF_Uncertainty__1up_noMET.root","RECREATE")

	# hist_HF = hbb_HF.Clone("hist_DL1")
	# hist_Nom = hbb_Nom.Clone("hist_DL1")
	# hist_Nom_noMET = hbb_Nom_noMET.Clone("hist_DL1")
	# hist_HF_noMET = hbb_HF_noMET.Clone("hist_DL1")
	hist_Final = hbb_Full_noMET.Clone("hist_DL1")

	myOutputFile.cd();hist_Final.Write()
	

	# myNomOut.cd(); hist_Nom.Write()
	# myNomOut_noMET.cd(); hist_Nom_noMET.Write()

	# myHFOut = ROOT.TFile("inputs_yy_bb_sherpa_HF_Uncertainty__1down.root","RECREATE")
	# myHFOut_noMET = ROOT.TFile("inputs_yy_bb_sherpa_HF_Uncertainty__1down_noMET.root","RECREATE")

	# myHFOut.cd(); hist_HF.Write()
	# myHFOut_noMET.cd(); hist_HF_noMET.Write()

def MonoSherpaFlavorUncertainty():
	print "Creaing single jet histograms for sherpa uncertainty "

	mySherpaNom = "/home/bstamas/xdata/yyhf/inputHistMaker/outputs/mc16a.Sherpa2_diphoton_myy_ALL_AF2.Nominal_combinedCR.root"
	mySherpaHF  = "/home/bstamas/xdata/yyhf/inputHistMaker/outputs/mc16a.Sh_2210_yybb_ALL_Nominal_combinedCR.root"

	print "Using nominal file: ", mySherpaNom
	print "Using falvor  file: ", mySherpaHF

	myNomFile = ROOT.TFile(mySherpaNom, "READ");
	myHFFile = ROOT.TFile(mySherpaHF, "READ");

	hb_Nom = myNomFile.Get("histb");
	hb_Nom_noMET = myNomFile.Get("histb_noMET");
	hb_HF = myHFFile.Get("histb");
	hb_HF_noMET = myHFFile.Get("histb_noMET");

	hist_HF = hb_HF.Clone("hist_DL1")
	hist_Nom = hb_Nom.Clone("hist_DL1")
	hist_Nom_noMET = hb_Nom_noMET.Clone("hist_DL1")
	hist_HF_noMET = hb_HF_noMET.Clone("hist_DL1")

	myNomOut = ROOT.TFile("inputs_yy_b_sherpa_HF_Uncertainty__1up.root","RECREATE")
	myNomOut_noMET = ROOT.TFile("inputs_yy_b_sherpa_HF_Uncertainty__1up_noMET.root","RECREATE")

	myNomOut.cd(); hb_Nom.Write()
	myNomOut_noMET.cd(); hb_Nom_noMET.Write()

	myHFOut = ROOT.TFile("inputs_yy_b_sherpa_HF_Uncertainty__1down.root","RECREATE")
	myHFOut_noMET = ROOT.TFile("inputs_yy_b_sherpa_HF_Uncertainty__1down_noMET.root","RECREATE")

	myHFOut.cd(); hb_HF.Write()
	myHFOut_noMET.cd(); hb_HF_noMET.Write()


if __name__ == '__main__':
	# DijetSherpaFlavorUncertainty()
	
	# for myInput in inputSignalSamples:
	# 	inputFile = "/home/bstamas/xdata/yyhf/inputHistMaker/outputs/master."+myInput+".Nominal_combinedCR.root"
	# 	SignalDijetHistograms(inputFile, myInput)

	# for myInput in inputBackgroundSamples:
	# 	inputFile = "/home/bstamas/xdata/yyhf/inputHistMaker/outputs/master."+myInput+".Nominal_combinedCR.root"
	# 	BackgroundDijetHistograms(inputFile, myInput)
	

	# MonoSherpaFlavorUncertainty()
	for myInput in inputSignalSamples:
		inputFile = "/home/bstamas/xdata/yyhf/inputHistMaker/outputs/master."+myInput+".Nominal_combinedCR.root"
		SignalMonojetHistograms(inputFile, myInput)

	for myInput in inputBackgroundSamples:
		inputFile = "/home/bstamas/xdata/yyhf/inputHistMaker/outputs/master."+myInput+".Nominal_combinedCR.root"
		BackgroundMonojetHistograms(inputFile, myInput)
