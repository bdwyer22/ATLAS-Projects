import ROOT
import sys
import os
import glob
import subprocess
import array

def read(obj, cpp_type, name):
	"""Document here."""
	raw_value = obj.auxdataConst[cpp_type](name)
	if cpp_type == "char":
		if (raw_value == '\x00'): return False
		else: return True
	if cpp_type == "float":
		return float(raw_value)
	if "int" in cpp_type:
		return int(raw_value)
	if "long" in cpp_type:
		return int(raw_value)
	return raw_value


def MakeHists(name,title,nbin,low,high):
	# print "in MakeHists"
	hists={}
	if name == "hist_myy":
		hists["nominal"] = ROOT.TH1F(name,title,nbin,low)
	else:
		hists["nominal"] = ROOT.TH1F(name,title,nbin,low,high)
	for variation in myVariations:	
		if variation == "nominal": continue
		if name == "hist_myy":
			hists[variation] = ROOT.TH1F(name+"_"+variation,title+"_"+variation,nbin,low)
		else:
			hists[variation] = ROOT.TH1F(name+"_"+variation,title+"_"+variation,nbin,low,high)
	# print "In MakeHists: ", hists
	return hists


def FillHists(hists,varName,binValue,myWeight):
	
	# print "in FillHists"
	# print hists[varName]

	hists[varName].Fill(binValue,myWeight)

def checkSingleJet(variation, varDict, eventweight):
	nElectrons = varDict["nElectrons"]
	nMuons = varDict["nMuons"]
	nLeptons = nMuons + nElectrons
	yyHF_met = varDict["yyHF_met"]
	LeadJet_truthlabel = varDict["LeadJet_truthlabel"]
	LeadJet_btagbin = varDict["LeadJet_btagbin"]
	Njet_central = varDict["Njet_central"]
	extraWeight = varDict["yyHFj_weight"]
	m_yy = varDict["m_yy"]
	# print "in checkSingleJet"

	# if (nLeptons == 0 and yyHF_met < 40): 
	if (nLeptons == 0): 
		if (LeadJet_truthlabel == 5):
			FillHists(histb_wHiggs,variation,LeadJet_btagbin,eventweight*extraWeight)
		elif (LeadJet_truthlabel == 4):
			FillHists(histc_wHiggs,variation,LeadJet_btagbin,eventweight*extraWeight)
		else:
			FillHists(histl_wHiggs,variation,LeadJet_btagbin,eventweight*extraWeight) 

	# if (nLeptons == 0): 
	# 	if (LeadJet_truthlabel == 5):
	# 		FillHists(histb_wHiggs_noMET,variation,LeadJet_btagbin,eventweight*extraWeight)
	# 	elif (LeadJet_truthlabel == 4):
	# 		FillHists(histc_wHiggs_noMET,variation,LeadJet_btagbin,eventweight*extraWeight)
	# 	else:
	# 		FillHists(histl_wHiggs_noMET,variation,LeadJet_btagbin,eventweight*extraWeight) 

	if (m_yy < 121 or m_yy > 129):  ## exclude higgs window
		# if (nLeptons == 0 and yyHF_met < 40): 
		if (nLeptons == 0): 
			if (LeadJet_truthlabel == 5):
				FillHists(histb,variation,LeadJet_btagbin,eventweight*extraWeight)
			elif (LeadJet_truthlabel == 4):
				FillHists(histc,variation,LeadJet_btagbin,eventweight*extraWeight)
			else:
				FillHists(histl,variation,LeadJet_btagbin,eventweight*extraWeight) 
		# if (nLeptons == 0): 
		# 	if (LeadJet_truthlabel == 5):
		# 		FillHists(histb_noMET,variation,LeadJet_btagbin,eventweight*extraWeight)
		# 	elif (LeadJet_truthlabel == 4):
		# 		FillHists(histc_noMET,variation,LeadJet_btagbin,eventweight*extraWeight)
		# 	else:
		# 		FillHists(histl_noMET,variation,LeadJet_btagbin,eventweight*extraWeight) 


def checkDijet(variation, varDict, eventweight, eventNumber):
	# print "in checkDijet"
	nElectrons = varDict["nElectrons"]
	nMuons = varDict["nMuons"]
	nLeptons = nMuons + nElectrons
	yyHF_met = varDict["yyHF_met"]
	LeadJet_truthlabel = varDict["LeadJet_truthlabel"]
	SubLeadJet_truthlabel = varDict["SubLeadJet_truthlabel"]
	LeadJet_btagbin = varDict["LeadJet_btagbin"]
	SubLeadJet_btagbin = varDict["SubLeadJet_btagbin"]
	Njet_central = varDict["Njet_central"]
	extraWeight = varDict["yyHFjj_weight"]
	m_yy = varDict["m_yy"]
	expanded_binning = LeadJet_btagbin * 5 + SubLeadJet_btagbin

	if SubLeadJet_truthlabel > -1:
		if ((LeadJet_btagbin == 4 and SubLeadJet_btagbin == 4) or (LeadJet_btagbin == 4 and SubLeadJet_btagbin == 3) or (LeadJet_btagbin == 3 and SubLeadJet_btagbin == 4) or (LeadJet_btagbin == 3 and SubLeadJet_btagbin == 3) or nLeptons == 0):
			# if   (nLeptons > 0 and expanded_binning == 24 and Njet_central <= 4): expanded_binning = 25
			# elif (nLeptons > 0 and expanded_binning == 24 and Njet_central > 4): expanded_binning = 26
			# if   (nLeptons > 0 and expanded_binning == 23 and Njet_central <= 4): expanded_binning = 25
			# elif (nLeptons > 0 and expanded_binning == 23 and Njet_central > 4): expanded_binning = 26
			# if   (nLeptons > 0 and expanded_binning == 18 and Njet_central <= 4): expanded_binning = 25
			# elif (nLeptons > 0 and expanded_binning == 18 and Njet_central > 4): expanded_binning = 26

			if   (nLeptons > 0 and expanded_binning == 24 and yyHF_met < 40): expanded_binning = 25
			if   (nLeptons > 0 and expanded_binning == 23 and yyHF_met < 40): expanded_binning = 25
			if   (nLeptons > 0 and expanded_binning == 18 and yyHF_met < 40): expanded_binning = 25
			if   (nLeptons > 0 and expanded_binning == 19 and yyHF_met < 40): expanded_binning = 25

			# if   (nLeptons > 0 and yyHF_met < 40): expanded_binning = 25

			# if expanded_binning > 24:
				# METpass = True

			# elif yyHF_met < 40: 
			# 	METpass = True

			# else:
			# 	METpass = False

			# if METpass == True:
			if (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 5):   ##bb
				FillHists(histbb_wHiggs,variation,expanded_binning,eventweight*extraWeight)
			elif (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 4): ##bc
				FillHists(histbc_wHiggs,variation,expanded_binning,eventweight*extraWeight)
			elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 5): ##cb
				FillHists(histbc_wHiggs,variation,expanded_binning,eventweight*extraWeight)
			elif (LeadJet_truthlabel == 5 or SubLeadJet_truthlabel == 5):  ##bl
				FillHists(histbl_wHiggs,variation,expanded_binning,eventweight*extraWeight)
			elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 4): ##cc
				FillHists(histcc_wHiggs,variation,expanded_binning,eventweight*extraWeight)
			elif (LeadJet_truthlabel == 4 or SubLeadJet_truthlabel == 4):  ##cl
				FillHists(histcl_wHiggs,variation,expanded_binning,eventweight*extraWeight)
			else:
				FillHists(histll_wHiggs,variation,expanded_binning,eventweight*extraWeight) 

			if (m_yy < 121 or m_yy > 129):  ## exclude higgs window
				if (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 5):   ##bb
					FillHists(histbb,variation,expanded_binning,eventweight*extraWeight)
				elif (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 4): ##bc
					FillHists(histbc,variation,expanded_binning,eventweight*extraWeight)
				elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 5): ##cb
					FillHists(histbc,variation,expanded_binning,eventweight*extraWeight)
				elif (LeadJet_truthlabel == 5 or SubLeadJet_truthlabel == 5):  ##bl
					FillHists(histbl,variation,expanded_binning,eventweight*extraWeight)
				elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 4): ##cc
					FillHists(histcc,variation,expanded_binning,eventweight*extraWeight)
				elif (LeadJet_truthlabel == 4 or SubLeadJet_truthlabel == 4):  ##cl
					FillHists(histcl,variation,expanded_binning,eventweight*extraWeight)
				else:
					FillHists(histll,variation,expanded_binning,eventweight*extraWeight) 
	# if SubLeadJet_truthlabel > -1:
	# 	if ((LeadJet_btagbin == 4 and SubLeadJet_btagbin == 4) or (LeadJet_btagbin == 4 and SubLeadJet_btagbin == 3) or (LeadJet_btagbin == 3 and SubLeadJet_btagbin == 3) or nLeptons == 0):

	# 		hist_HGeventweight.Fill(eventweight)
	# 		hist_fulleventweight.Fill(eventweight*extraWeight)
	# 		if   (nLeptons > 0 and expanded_binning == 24 and Njet_central <= 4): expanded_binning = 25
	# 		elif (nLeptons > 0 and expanded_binning == 24 and Njet_central > 4): expanded_binning = 26
	# 		if   (nLeptons > 0 and expanded_binning == 23 and Njet_central <= 4): expanded_binning = 25
	# 		elif (nLeptons > 0 and expanded_binning == 23 and Njet_central > 4): expanded_binning = 26
	# 		if   (nLeptons > 0 and expanded_binning == 18 and Njet_central <= 4): expanded_binning = 25
	# 		elif (nLeptons > 0 and expanded_binning == 18 and Njet_central > 4): expanded_binning = 26
	# 		# eventweight = 1;extraWeight=1

			if   (nLeptons > 0 and expanded_binning == 24): expanded_binning = 25
			if   (nLeptons > 0 and expanded_binning == 23): expanded_binning = 25
			if   (nLeptons > 0 and expanded_binning == 18): expanded_binning = 25
			if   (nLeptons > 0 and expanded_binning == 19): expanded_binning = 25

			if (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 5):   ##bb
				FillHists(histbb_wHiggs_noMET,variation,expanded_binning,eventweight*extraWeight)
			elif (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 4): ##bc
				FillHists(histbc_wHiggs_noMET,variation,expanded_binning,eventweight*extraWeight)
			elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 5): ##cb
				FillHists(histbc_wHiggs_noMET,variation,expanded_binning,eventweight*extraWeight)
			elif (LeadJet_truthlabel == 5 or SubLeadJet_truthlabel == 5):  ##bl
				FillHists(histbl_wHiggs_noMET,variation,expanded_binning,eventweight*extraWeight)
			elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 4): ##cc
				FillHists(histcc_wHiggs_noMET,variation,expanded_binning,eventweight*extraWeight)
			elif (LeadJet_truthlabel == 4 or SubLeadJet_truthlabel == 4):  ##cl
				FillHists(histcl_wHiggs_noMET,variation,expanded_binning,eventweight*extraWeight)
			else:
				FillHists(histll_wHiggs_noMET,variation,expanded_binning,eventweight*extraWeight) 

			if (m_yy < 121 or m_yy > 129):  ## exclude higgs window
				if (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 5):   ##bb
					FillHists(histbb_noMET,variation,expanded_binning,eventweight*extraWeight)
				elif (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 4): ##bc
					FillHists(histbc_noMET,variation,expanded_binning,eventweight*extraWeight)
				elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 5): ##cb
					FillHists(histbc_noMET,variation,expanded_binning,eventweight*extraWeight)
				elif (LeadJet_truthlabel == 5 or SubLeadJet_truthlabel == 5):  ##bl
					FillHists(histbl_noMET,variation,expanded_binning,eventweight*extraWeight)
				elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 4): ##cc
					FillHists(histcc_noMET,variation,expanded_binning,eventweight*extraWeight)
				elif (LeadJet_truthlabel == 4 or SubLeadJet_truthlabel == 4):  ##cl
					FillHists(histcl_noMET,variation,expanded_binning,eventweight*extraWeight)
				else:
					FillHists(histll_noMET,variation,expanded_binning,eventweight*extraWeight) 	

def makehistograms(inputFile, cutflowPath):
	ROOT.xAOD.Init()

	myFile = ROOT.TFile(inputFile, "READ") 
	myCutflow = ROOT.TFile(cutflowPath, "READ") 
	# myTree = myFile.Get("CollectionTree")
	# nEntries = myTree.GetEntries()
	# print nEntries
	myTree = ROOT.xAOD.MakeTransientTree(myFile, "CollectionTree")
	nEntries = myTree.GetEntries()
	print nEntries

	lumi_mc16 = 0
	if mcType == "mc16a":
		lumi_mc16 = 36205.26
	if mcType == "mc16d":
		lumi_mc16 = 44307.4
	if mcType == "mc16e":
		lumi_mc16 = 58450.1

	sumweights = (myCutflow.Get(cutlfow_name).GetBinContent(1) / myCutflow.Get(cutlfow_name).GetBinContent(2) ) * myCutflow.Get(cutlfow_name).GetBinContent(3)

	hist_sumofweights.Fill(sumweights)
	print sumweights

	j = 0
	# nEntries = 2000
	# myCount = 0

	for i in range(nEntries):
		
		if i % 10000 == 0:
			j += 1
			sys.stdout.write("\r{0}>  ".format("="*j)+str( round(i/float(nEntries) * 100, 1))+"%")
			sys.stdout.flush()
		elif i == (nEntries-1):
			sys.stdout.write("\r{0}>  ".format("="*j)+str(100)+" %")
			sys.stdout.flush()

		myTree.GetEntry(i)

		eventNumber = read(myTree.EventInfo, "ULong64_t", "eventNumber")

		if "Sherpa_tt_dilepton" in inputFile or "MGPy8_ttgamma_nonallhadronic" in inputFile:
			inOverlap = read(myTree.HGamTruthEventInfo, "int", "GammaOR_inOverlap")
			if inOverlap: continue;
		
		# eventweight = 1;#print "eventweight: ", eventweight

		for variation in myVariations:	
			# print "my variation is ", variation
			branchName = 'HGamEventInfo_'+str(variation)
			if "nominal" in variation:
				branchName = 'HGamEventInfo'

			isPassed = read(eval('myTree.'+str(branchName)), "char", "isPassed")
			if not isPassed: continue
			
			XSWeight   = read(myTree.HGamEventInfo, "float", "crossSectionBRfilterEff");#print "XSWeight: ", XSWeight
			HGamWeight =  read(eval('myTree.'+str(branchName)), "float", "weight")
			# eval('myTree.'+str(branchName)+'HGamWeight')#myTree.HGamWeight;

			eventweight = (XSWeight * HGamWeight * lumi_mc16) / sumweights;#print "eventweight: ", eventweight

			m_yy = read(eval('myTree.'+str(branchName)), "float", "m_yy") * 0.001
			# if (m_yy > 120 and m_yy < 130): continue ## exclude higgs window
			FillHists(hist_myy,variation,m_yy,eventweight)
			
			
			mySysDict[variation] =  {"LeadJet_truthlabel":    read(eval('myTree.'+str(branchName)), "int", "yyHF_leadjet_truthlabel"),
									 "SubLeadJet_truthlabel": read(eval('myTree.'+str(branchName)), "int", "yyHF_subleadjet_truthlabel"),
									 "LeadJet_btagbin":       read(eval('myTree.'+str(branchName)) ,"int", "yyHF_leadjet_btagbin"),
									 "SubLeadJet_btagbin":    read(eval('myTree.'+str(branchName)), "int", "yyHF_subleadjet_btagbin"),
									 "Njet_central":          read(eval('myTree.'+str(branchName)), "int", "yyHF_Njet_central"),
									 "yyHFjj_weight":         read(eval('myTree.'+str(branchName)), "float", "yyHFjj_weight"),
									 "yyHFj_weight":          read(eval('myTree.'+str(branchName)), "float", "yyHFj_weight"),
									 "yyHF_met":              read(eval('myTree.'+str(branchName)), "float", "yyHF_met") * 0.001,
									 "nElectrons":            read(eval('myTree.'+str(branchName)), "int", "yyHF_nelectron"),
									 "nMuons":                read(eval('myTree.'+str(branchName)), "int", "yyHF_nmuon"),
									 "isPassed":              read(eval('myTree.'+str(branchName)), "char", "isPassed"),
									 "m_yy":                  read(eval('myTree.'+str(branchName)), "float", "m_yy") * 0.001
									}

			checkSingleJet(variation, mySysDict[variation], eventweight)
			checkDijet(variation, mySysDict[variation],eventweight, eventNumber)
        
	print

	ROOT.xAOD.ClearTransientTrees()	

def makehistogramsNTUP(inputFile, cutflowPath):

	myFile = ROOT.TFile(inputFile, "READ") 
	myCutflow = ROOT.TFile(cutflowPath, "READ") 

	myTree = myFile.Get("CollectionTree")

	nEntries = myTree.GetEntries()
	print nEntries

	lumi_mc16 = 0
	if mcType == "mc16a":
		lumi_mc16 = 36205.26
	if mcType == "mc16d":
		lumi_mc16 = 44307.4
	if mcType == "mc16e":
		lumi_mc16 = 58450.1

	sumweights = (myCutflow.Get(cutlfow_name).GetBinContent(1) / myCutflow.Get(cutlfow_name).GetBinContent(2) ) * myCutflow.Get(cutlfow_name).GetBinContent(3)
	hist_sumofweights.Fill(sumweights)
	print sumweights

	j = 0
	# nEntries = 50
	for i in range(nEntries):
		
		if i % 100000 == 0:
			j += 1
			sys.stdout.write("\r{0}>  ".format("="*j)+str( round(i/float(nEntries) * 100, 1))+"%")
			sys.stdout.flush()
		elif i == (nEntries-1):
			sys.stdout.write("\r{0}>  ".format("="*j)+str(100)+" %")
			sys.stdout.flush()

		myTree.GetEntry(i)


		for variation in myVariations:	
			# print "my variation is ", variation
			branchName = str(variation)+'.'
			if "nominal" in variation:
				branchName = ''


			isPassed = getattr(myTree, branchName+'isPassed')
			if not isPassed: continue
			HGamWeight = getattr(myTree, branchName+'HGamWeight')
			XSWeight = getattr(myTree, 'XSWeight')

			# isPassed = eval('myTree.'+str(branchName)+'isPassed')
			# if not isPassed: continue
			
			# HGamWeight =  eval('myTree.'+str(branchName)+'HGamWeight')#myTree.HGamWeight;
			# XSWeight   = eval('myTree.XSWeight')#myTree.HGamWeight;

			eventweight = (XSWeight * HGamWeight * lumi_mc16) / sumweights;#print "eventweight: ", eventweight

			# m_yy = eval('myTree.'+str(branchName)+'m_yy') * 0.001
			m_yy = getattr(myTree, branchName+'m_yy') * 0.001
			# if (m_yy > 120 and m_yy < 130): continue ## exclude higgs window
			FillHists(hist_myy,variation,m_yy,eventweight)
			

			mySysDict[variation] =  {"LeadJet_truthlabel":    getattr(myTree, branchName+'yyHF_leadjet_truthlabel'),
									 "SubLeadJet_truthlabel": getattr(myTree, branchName+'yyHF_subleadjet_truthlabel'),
									 "LeadJet_btagbin":       getattr(myTree, branchName+'yyHF_leadjet_btagbin'),
									 "SubLeadJet_btagbin":    getattr(myTree, branchName+'yyHF_subleadjet_btagbin'),
									 "Njet_central":          getattr(myTree, branchName+'yyHF_Njet_central'),
									 "yyHFjj_weight":         getattr(myTree, branchName+'yyHFjj_weight'),
									 "yyHFj_weight":          getattr(myTree, branchName+'yyHFj_weight'),
									 "yyHF_met":              getattr(myTree, branchName+'yyHF_met') * 0.001,
									 "nElectrons":            getattr(myTree, branchName+'yyHF_nelectron'),
									 "nMuons":                getattr(myTree, branchName+'yyHF_nmuon'),
									 "isPassed":              getattr(myTree, branchName+'isPassed'),
									 "m_yy":                  getattr(myTree, branchName+'m_yy') * 0.001
									}

			# mySysDict[variation] =  {"LeadJet_truthlabel":    eval('myTree.'+str(branchName)+'yyHF_leadjet_truthlabel'),
			# 						 "SubLeadJet_truthlabel": eval('myTree.'+str(branchName)+'yyHF_subleadjet_truthlabel'),
			# 						 "LeadJet_btagbin":       eval('myTree.'+str(branchName)+'yyHF_leadjet_btagbin'),
			# 						 "SubLeadJet_btagbin":    eval('myTree.'+str(branchName)+'yyHF_subleadjet_btagbin'),
			# 						 "Njet_central":          eval('myTree.'+str(branchName)+'yyHF_Njet_central'),
			# 						 "yyHFjj_weight":         eval('myTree.'+str(branchName)+'yyHFjj_weight'),
			# 						 "yyHFj_weight":          eval('myTree.'+str(branchName)+'yyHFj_weight'),
			# 						 "yyHF_met":              eval('myTree.'+str(branchName)+'yyHF_met') * 0.001,
			# 						 "nElectrons":            eval('myTree.'+str(branchName)+'yyHF_nelectron'),
			# 						 "nMuons":                eval('myTree.'+str(branchName)+'yyHF_nmuon'),
			# 						 "isPassed":              eval('myTree.'+str(branchName)+'isPassed'),
			# 						 "m_yy":                  eval('myTree.'+str(branchName)+'m_yy') * 0.001
			# 						}

			checkSingleJet(variation, mySysDict[variation], eventweight)
			checkDijet(variation, mySysDict[variation],eventweight, 1)
        
	print

	ROOT.xAOD.ClearTransientTrees()	

inputFile = sys.argv[1]
outputFile = sys.argv[2]
sampleType = sys.argv[3]
mcType = sys.argv[4]
systematicType = sys.argv[5]

print "input file: ", inputFile
print "output file: ", outputFile
print "sample: ", sampleType
print "mc campaign: ", mcType
print "sys type: ", systematicType

cutlfow_name = ""

outputFile += '_'+sampleType
if sampleType == "MGPy8_ttgamma_nonallhadronic_AF2":
	cutlfow_name = "CutFlow_MGPy8_ttgamma_nonallhadronic_noDalitz_weighted"
	cutflowPath = 'cutflows/'+systematicType+"/"+mcType+'.CutFlow_MGPy8_ttgamma_nonallhadronic.root'
elif sampleType == "Sherpa2_diphoton_myy_2000_ECMS_AF2":
	cutlfow_name = "CutFlow_Sherpa2_myy_2000_ECMS_noDalitz_weighted"
	cutflowPath = 'cutflows/'+systematicType+"/"+mcType+'.CutFlow_'+sampleType+'.root'
elif sampleType == "Sherpa2_diphoton_myy_1400_2000_AF2":
	cutlfow_name = "CutFlow_Sherpa2_myy_1400_2000_noDalitz_weighted"
	cutflowPath = 'cutflows/'+systematicType+"/"+mcType+'.CutFlow_'+sampleType+'.root'
elif sampleType == "Sherpa2_diphoton_myy_175_2000_AF2":
	cutlfow_name = "CutFlow_Sherpa2_myy_175_2000_noDalitz_weighted"
	cutflowPath = 'cutflows/'+systematicType+"/"+mcType+'.CutFlow_'+sampleType+'.root'
elif sampleType == "Sherpa2_diphoton_myy_90_175_AF2":
	cutlfow_name = "CutFlow_Sherpa2_myy_90_175_noDalitz_weighted"
	# cutlfow_name = "hist_cutflow_noDalitz_weighted"
	cutflowPath = 'cutflows/'+systematicType+"/"+mcType+'.CutFlow_'+sampleType+'.root'
else:
	cutlfow_name = "CutFlow_"+sampleType+"_noDalitz_weighted"
	cutflowPath = 'cutflows/'+systematicType+"/"+mcType+'.CutFlow_'+sampleType+'.root'

# cutflowPath = "~/xdata/yyhf/testingInputMakers/cutflows/Nominal/mc16e.CutFlow_Sherpa2_diphoton_myy_90_175_AF2NEWTESTINPUT.root"
# cutlfow_name = "CutFlow_Sherpa2_myy_90_175_noDalitz_weighted"

print "Using cutflow ", cutlfow_name, " from ",cutflowPath

print "Creating output " + outputFile + ".root for file " + inputFile
newFile = ROOT.TFile(outputFile+".root", "recreate")
newFile.cd()

mySysDict = {}
myVariations = []
if "PhotonSys" in systematicType:
	myVariations = ["EG_RESOLUTION_ALL__1down","EG_RESOLUTION_ALL__1up","EG_SCALE_AF2__1down","EG_SCALE_AF2__1up",
	"EG_SCALE_ALL__1down","EG_SCALE_ALL__1up","PH_EFF_ID_Uncertainty__1down","PH_EFF_ID_Uncertainty__1up","PH_EFF_ISO_Uncertainty__1down",
	"PH_EFF_ISO_Uncertainty__1up","PH_EFF_TRIGGER_Uncertainty__1down","PH_EFF_TRIGGER_Uncertainty__1up","PRW_DATASF__1down","PRW_DATASF__1up"]

if "FlavorSys" in systematicType:
	myVariations = ["FT_EFF_Eigen_B_0__1down","FT_EFF_Eigen_B_0__1up", "FT_EFF_Eigen_B_1__1down", "FT_EFF_Eigen_B_1__1up", "FT_EFF_Eigen_B_2__1down", 
	"FT_EFF_Eigen_B_2__1up", "FT_EFF_Eigen_C_0__1down", "FT_EFF_Eigen_C_0__1up", "FT_EFF_Eigen_C_1__1down", "FT_EFF_Eigen_C_1__1up", "FT_EFF_Eigen_C_2__1down", 
	"FT_EFF_Eigen_C_2__1up", "FT_EFF_Eigen_C_3__1down", "FT_EFF_Eigen_C_3__1up", "FT_EFF_Eigen_Light_0__1down", "FT_EFF_Eigen_Light_0__1up", 
	"FT_EFF_Eigen_Light_1__1down", "FT_EFF_Eigen_Light_1__1up", "FT_EFF_Eigen_Light_2__1down", "FT_EFF_Eigen_Light_2__1up", "FT_EFF_Eigen_Light_3__1down", 
	"FT_EFF_Eigen_Light_3__1up", "FT_EFF_Eigen_Light_4__1down", "FT_EFF_Eigen_Light_4__1up", "FT_EFF_extrapolation__1down", "FT_EFF_extrapolation__1up", 
	"FT_EFF_extrapolation_from_charm__1down", "FT_EFF_extrapolation_from_charm__1up"]

if "JetSys" in systematicType:
	myVariations = ["JET_BJES_Response__1down", "JET_BJES_Response__1up", "JET_EffectiveNP_Detector1__1down", "JET_EffectiveNP_Detector1__1up", 
	"JET_EffectiveNP_Detector2__1down", "JET_EffectiveNP_Detector2__1up", "JET_EffectiveNP_Mixed1__1down", "JET_EffectiveNP_Mixed1__1up", 
	"JET_EffectiveNP_Mixed2__1down", "JET_EffectiveNP_Mixed2__1up", "JET_EffectiveNP_Mixed3__1down", "JET_EffectiveNP_Mixed3__1up", 
	"JET_EffectiveNP_Modelling1__1down", "JET_EffectiveNP_Modelling1__1up", "JET_EffectiveNP_Modelling2__1down", "JET_EffectiveNP_Modelling2__1up", 
	"JET_EffectiveNP_Modelling3__1down", "JET_EffectiveNP_Modelling3__1up", "JET_EffectiveNP_Modelling4__1down", "JET_EffectiveNP_Modelling4__1up", 
	"JET_EffectiveNP_Statistical1__1down", "JET_EffectiveNP_Statistical1__1up", "JET_EffectiveNP_Statistical2__1down", "JET_EffectiveNP_Statistical2__1up", 
	"JET_EffectiveNP_Statistical3__1down", "JET_EffectiveNP_Statistical3__1up", "JET_EffectiveNP_Statistical4__1down", "JET_EffectiveNP_Statistical4__1up", 
	"JET_EffectiveNP_Statistical5__1down", "JET_EffectiveNP_Statistical5__1up", "JET_EffectiveNP_Statistical6__1down", "JET_EffectiveNP_Statistical6__1up", 
	"JET_EtaIntercalibration_Modelling__1down", "JET_EtaIntercalibration_Modelling__1up", "JET_EtaIntercalibration_NonClosure_2018data__1down", 
	"JET_EtaIntercalibration_NonClosure_2018data__1up", "JET_EtaIntercalibration_NonClosure_highE__1down", "JET_EtaIntercalibration_NonClosure_highE__1up", 
	"JET_EtaIntercalibration_NonClosure_negEta__1down", "JET_EtaIntercalibration_NonClosure_negEta__1up", "JET_EtaIntercalibration_NonClosure_posEta__1down", 
	"JET_EtaIntercalibration_NonClosure_posEta__1up", "JET_EtaIntercalibration_TotalStat__1down", "JET_EtaIntercalibration_TotalStat__1up", "JET_fJvtEfficiency__1down", 
	"JET_fJvtEfficiency__1up", "JET_Flavor_Composition__1down", "JET_Flavor_Composition__1up", "JET_Flavor_Response__1down", 
	"JET_Flavor_Response__1up", "JET_JER_EffectiveNP_1__1down", "JET_JER_EffectiveNP_1__1up", "JET_JER_EffectiveNP_10__1down", 
	"JET_JER_EffectiveNP_10__1up", "JET_JER_EffectiveNP_11__1down", "JET_JER_EffectiveNP_11__1up", "JET_JER_EffectiveNP_12restTerm__1down", 
	"JET_JER_EffectiveNP_12restTerm__1up", "JET_JER_EffectiveNP_2__1down", "JET_JER_EffectiveNP_2__1up", "JET_JER_EffectiveNP_3__1down", 
	"JET_JER_EffectiveNP_3__1up", "JET_JER_EffectiveNP_4__1down", "JET_JER_EffectiveNP_4__1up", "JET_JER_EffectiveNP_5__1down", 
	"JET_JER_EffectiveNP_5__1up", "JET_JER_EffectiveNP_6__1down", "JET_JER_EffectiveNP_6__1up", "JET_JER_EffectiveNP_7__1down", 
	"JET_JER_EffectiveNP_7__1up", "JET_JER_EffectiveNP_8__1down", "JET_JER_EffectiveNP_8__1up", "JET_JER_EffectiveNP_9__1down", 
	"JET_JER_EffectiveNP_9__1up", "JET_JvtEfficiency__1down", "JET_JvtEfficiency__1up", "JET_Pileup_OffsetMu__1down", "JET_Pileup_OffsetMu__1up", 
	"JET_Pileup_OffsetNPV__1down", "JET_Pileup_OffsetNPV__1up", "JET_Pileup_PtTerm__1down", "JET_Pileup_PtTerm__1up", "JET_Pileup_RhoTopology__1down", 
	"JET_Pileup_RhoTopology__1up", "JET_SingleParticle_HighPt__1down", "JET_SingleParticle_HighPt__1up"]

if "PhotonAllSys1" in systematicType:
	myVariations = ["EG_RESOLUTION_AF2__1down", "EG_RESOLUTION_AF2__1up", "EG_RESOLUTION_MATERIALCALO__1down", 
	"EG_RESOLUTION_MATERIALCALO__1up", "EG_RESOLUTION_MATERIALCRYO__1down", "EG_RESOLUTION_MATERIALCRYO__1up", 
	"EG_RESOLUTION_MATERIALGAP__1down", "EG_RESOLUTION_MATERIALGAP__1up", "EG_RESOLUTION_MATERIALIBL__1down", 
	"EG_RESOLUTION_MATERIALIBL__1up", "EG_RESOLUTION_MATERIALID__1down", "EG_RESOLUTION_MATERIALID__1up", 
	"EG_RESOLUTION_MATERIALPP0__1down", "EG_RESOLUTION_MATERIALPP0__1up", "EG_RESOLUTION_PILEUP__1down", 
	"EG_RESOLUTION_PILEUP__1up", "EG_RESOLUTION_SAMPLINGTERM__1down", "EG_RESOLUTION_SAMPLINGTERM__1up", 
	"EG_RESOLUTION_ZSMEARING__1down", "EG_RESOLUTION_ZSMEARING__1up", "EG_SCALE_PEDESTAL__1down", 
	"EG_SCALE_PEDESTAL__1up", "EG_SCALE_PS__ETABIN0__1down", "EG_SCALE_PS__ETABIN0__1up", 
	"EG_SCALE_PS__ETABIN1__1down", "EG_SCALE_PS__ETABIN1__1up", "EG_SCALE_PS__ETABIN2__1down", 
	"EG_SCALE_PS__ETABIN2__1up", "EG_SCALE_PS__ETABIN3__1down", "EG_SCALE_PS__ETABIN3__1up", 
	"EG_SCALE_PS__ETABIN4__1down", "EG_SCALE_PS__ETABIN4__1up", "EG_SCALE_PS__ETABIN5__1down", 
	"EG_SCALE_PS__ETABIN5__1up", "EG_SCALE_PS__ETABIN6__1down", "EG_SCALE_PS__ETABIN6__1up", 
	"EG_SCALE_PS__ETABIN7__1down", "EG_SCALE_PS__ETABIN7__1up", "EG_SCALE_PS__ETABIN8__1down", 
	"EG_SCALE_PS__ETABIN8__1up", "EG_SCALE_PS_BARREL_B12__1down", "EG_SCALE_PS_BARREL_B12__1up"]

if "PhotonAllSys2" in systematicType:
	myVariations = ["EG_SCALE_AF2__1down", "EG_SCALE_AF2__1up", "EG_SCALE_E4SCINTILLATOR__ETABIN0__1down", 
	"EG_SCALE_E4SCINTILLATOR__ETABIN0__1up", "EG_SCALE_E4SCINTILLATOR__ETABIN1__1down", 
	"EG_SCALE_E4SCINTILLATOR__ETABIN1__1up", "EG_SCALE_E4SCINTILLATOR__ETABIN2__1down", 
	"EG_SCALE_E4SCINTILLATOR__ETABIN2__1up", "EG_SCALE_G4__1down", "EG_SCALE_G4__1up", "EG_SCALE_L1GAIN__1down", 
	"EG_SCALE_L1GAIN__1up", "EG_SCALE_L2GAIN__1down", "EG_SCALE_L2GAIN__1up", "EG_SCALE_LARCALIB__ETABIN0__1down", 
	"EG_SCALE_LARCALIB__ETABIN0__1up", "EG_SCALE_LARCALIB__ETABIN1__1down", "EG_SCALE_LARCALIB__ETABIN1__1up", 
	"EG_SCALE_LARELECCALIB__1down", "EG_SCALE_LARELECCALIB__1up", "EG_SCALE_LARELECUNCONV__ETABIN0__1down", 
	"EG_SCALE_LARELECUNCONV__ETABIN0__1up", "EG_SCALE_LARELECUNCONV__ETABIN1__1down", "EG_SCALE_LARELECUNCONV__ETABIN1__1up", 
	"EG_SCALE_LARUNCONVCALIB__ETABIN0__1down", "EG_SCALE_LARUNCONVCALIB__ETABIN0__1up", "EG_SCALE_LARUNCONVCALIB__ETABIN1__1down", 
	"EG_SCALE_LARUNCONVCALIB__ETABIN1__1up", "EG_SCALE_S12__ETABIN0__1down", "EG_SCALE_S12__ETABIN0__1up", 
	"EG_SCALE_S12__ETABIN1__1down", "EG_SCALE_S12__ETABIN1__1up", "EG_SCALE_S12__ETABIN2__1down", 
	"EG_SCALE_S12__ETABIN2__1up", "EG_SCALE_S12__ETABIN3__1down", "EG_SCALE_S12__ETABIN3__1up", 
	"EG_SCALE_S12__ETABIN4__1down", "EG_SCALE_S12__ETABIN4__1up", "EG_SCALE_TOPOCLUSTER_THRES__1down", 
	"EG_SCALE_TOPOCLUSTER_THRES__1up", "EG_SCALE_WTOTS1__1down", "EG_SCALE_WTOTS1__1up"]

if "PhotonAllSys3" in systematicType:
	myVariations = ["EG_SCALE_MATCALO__ETABIN0__1down", "EG_SCALE_MATCALO__ETABIN0__1up", "EG_SCALE_MATCALO__ETABIN1__1down", 
	"EG_SCALE_MATCALO__ETABIN1__1up", "EG_SCALE_MATCALO__ETABIN10__1down", "EG_SCALE_MATCALO__ETABIN10__1up", 
	"EG_SCALE_MATCALO__ETABIN11__1down", "EG_SCALE_MATCALO__ETABIN11__1up", "EG_SCALE_MATCALO__ETABIN2__1down", 
	"EG_SCALE_MATCALO__ETABIN2__1up", "EG_SCALE_MATCALO__ETABIN3__1down", "EG_SCALE_MATCALO__ETABIN3__1up", 
	"EG_SCALE_MATCALO__ETABIN4__1down", "EG_SCALE_MATCALO__ETABIN4__1up", "EG_SCALE_MATCALO__ETABIN5__1down", 
	"EG_SCALE_MATCALO__ETABIN5__1up", "EG_SCALE_MATCALO__ETABIN6__1down", "EG_SCALE_MATCALO__ETABIN6__1up", 
	"EG_SCALE_MATCALO__ETABIN7__1down", "EG_SCALE_MATCALO__ETABIN7__1up", "EG_SCALE_MATCALO__ETABIN8__1down", 
	"EG_SCALE_MATCALO__ETABIN8__1up", "EG_SCALE_MATCALO__ETABIN9__1down", "EG_SCALE_MATCALO__ETABIN9__1up", 
	"EG_SCALE_MATID__ETABIN0__1down", "EG_SCALE_MATID__ETABIN0__1up", "EG_SCALE_MATID__ETABIN1__1down", 
	"EG_SCALE_MATID__ETABIN1__1up", "EG_SCALE_MATID__ETABIN2__1down", "EG_SCALE_MATID__ETABIN2__1up", 
	"EG_SCALE_MATID__ETABIN3__1down", "EG_SCALE_MATID__ETABIN3__1up", "EG_SCALE_MATPP0__ETABIN0__1down", 
	"EG_SCALE_MATPP0__ETABIN0__1up", "EG_SCALE_MATPP0__ETABIN1__1down", "EG_SCALE_MATPP0__ETABIN1__1up", 
	"EG_SCALE_ZEESTAT__1down", "EG_SCALE_ZEESTAT__1up", "EG_SCALE_ZEESYST__1down", "EG_SCALE_ZEESYST__1up"]

if "PhotonAllSys4" in systematicType:
	myVariations = ["EG_SCALE_MATCRYO__ETABIN0__1down", "EG_SCALE_MATCRYO__ETABIN0__1up", "EG_SCALE_MATCRYO__ETABIN1__1down", 
	"EG_SCALE_MATCRYO__ETABIN1__1up", "EG_SCALE_MATCRYO__ETABIN10__1down", "EG_SCALE_MATCRYO__ETABIN10__1up", "EG_SCALE_MATCRYO__ETABIN11__1down", 
	"EG_SCALE_MATCRYO__ETABIN11__1up", "EG_SCALE_MATCRYO__ETABIN2__1down", "EG_SCALE_MATCRYO__ETABIN2__1up", "EG_SCALE_MATCRYO__ETABIN3__1down", 
	"EG_SCALE_MATCRYO__ETABIN3__1up", "EG_SCALE_MATCRYO__ETABIN4__1down", "EG_SCALE_MATCRYO__ETABIN4__1up", "EG_SCALE_MATCRYO__ETABIN5__1down", 
	"EG_SCALE_MATCRYO__ETABIN5__1up", "EG_SCALE_MATCRYO__ETABIN6__1down", "EG_SCALE_MATCRYO__ETABIN6__1up", "EG_SCALE_MATCRYO__ETABIN7__1down", 
	"EG_SCALE_MATCRYO__ETABIN7__1up", "EG_SCALE_MATCRYO__ETABIN8__1down", "EG_SCALE_MATCRYO__ETABIN8__1up", "EG_SCALE_MATCRYO__ETABIN9__1down", 
	"EG_SCALE_MATCRYO__ETABIN9__1up", "PH_EFF_ID_Uncertainty__1down", "PH_EFF_ID_Uncertainty__1up", "PH_EFF_ISO_Uncertainty__1down", 
	"PH_EFF_ISO_Uncertainty__1up", "PH_EFF_TRIGGER_Uncertainty__1down", "PH_EFF_TRIGGER_Uncertainty__1up", "PH_SCALE_CONVEFFICIENCY__1down", 
	"PH_SCALE_CONVEFFICIENCY__1up", "PH_SCALE_CONVFAKERATE__1down", "PH_SCALE_CONVFAKERATE__1up", "PH_SCALE_CONVRADIUS__1down", 
	"PH_SCALE_CONVRADIUS__1up", "PH_SCALE_LEAKAGECONV__1down", "PH_SCALE_LEAKAGECONV__1up", "PH_SCALE_LEAKAGEUNCONV__1down", "PH_SCALE_LEAKAGEUNCONV__1up"]

if "JetSys1" in systematicType:
	myVariations = ["JET_EffectiveNP_Detector1__1down", "JET_EffectiveNP_Detector1__1up", "JET_EffectiveNP_Detector2__1down", "JET_EffectiveNP_Detector2__1up", 
	"JET_EffectiveNP_Mixed1__1down", "JET_EffectiveNP_Mixed1__1up", "JET_EffectiveNP_Mixed2__1down", "JET_EffectiveNP_Mixed2__1up", 
	"JET_EffectiveNP_Mixed3__1down", "JET_EffectiveNP_Mixed3__1up", "JET_EffectiveNP_Modelling1__1down", "JET_EffectiveNP_Modelling1__1up", 
	"JET_EffectiveNP_Modelling2__1down", "JET_EffectiveNP_Modelling2__1up", "JET_EffectiveNP_Modelling3__1down", "JET_EffectiveNP_Modelling3__1up", 
	"JET_EffectiveNP_Modelling4__1down", "JET_EffectiveNP_Modelling4__1up", "JET_EffectiveNP_Statistical1__1down", "JET_EffectiveNP_Statistical1__1up", 
	"JET_EffectiveNP_Statistical2__1down", "JET_EffectiveNP_Statistical2__1up", "JET_EffectiveNP_Statistical3__1down", "JET_EffectiveNP_Statistical3__1up", 
	"JET_EffectiveNP_Statistical4__1down", "JET_EffectiveNP_Statistical4__1up", "JET_EffectiveNP_Statistical5__1down", "JET_EffectiveNP_Statistical5__1up", 
	"JET_EffectiveNP_Statistical6__1down", "JET_EffectiveNP_Statistical6__1up"]

if "JetSys2" in systematicType:#"JET_PunchThrough_MC16__1down", "JET_PunchThrough_MC16__1up",
	myVariations = ["JET_BJES_Response__1down", "JET_BJES_Response__1up", "JET_EtaIntercalibration_Modelling__1down", "JET_EtaIntercalibration_Modelling__1up", 
	"JET_EtaIntercalibration_NonClosure_2018data__1down", "JET_EtaIntercalibration_NonClosure_2018data__1up", "JET_EtaIntercalibration_NonClosure_highE__1down", 
	"JET_EtaIntercalibration_NonClosure_highE__1up", "JET_EtaIntercalibration_NonClosure_negEta__1down", "JET_EtaIntercalibration_NonClosure_negEta__1up", 
	"JET_EtaIntercalibration_NonClosure_posEta__1down", "JET_EtaIntercalibration_NonClosure_posEta__1up", "JET_EtaIntercalibration_TotalStat__1down", 
	"JET_EtaIntercalibration_TotalStat__1up", "JET_fJvtEfficiency__1down", "JET_fJvtEfficiency__1up", "JET_Flavor_Composition__1down", "JET_Flavor_Composition__1up", 
	"JET_Flavor_Response__1down", "JET_Flavor_Response__1up", "JET_JvtEfficiency__1down", "JET_JvtEfficiency__1up", "JET_Pileup_OffsetMu__1down", 
	"JET_Pileup_OffsetMu__1up", "JET_Pileup_OffsetNPV__1down", "JET_Pileup_OffsetNPV__1up", "JET_Pileup_PtTerm__1down", "JET_Pileup_PtTerm__1up", 
	"JET_Pileup_RhoTopology__1down", "JET_Pileup_RhoTopology__1up", "JET_SingleParticle_HighPt__1down", "JET_SingleParticle_HighPt__1up"]
 
if "JetSys3" in systematicType:
	myVariations = ["JET_JER_EffectiveNP_1__1down", "JET_JER_EffectiveNP_1__1up", 
	"JET_JER_EffectiveNP_10__1down", "JET_JER_EffectiveNP_10__1up", "JET_JER_EffectiveNP_11__1down", "JET_JER_EffectiveNP_11__1up", 
	"JET_JER_EffectiveNP_12restTerm__1down", "JET_JER_EffectiveNP_12restTerm__1up", "JET_JER_EffectiveNP_2__1down", "JET_JER_EffectiveNP_2__1up", 
	"JET_JER_EffectiveNP_3__1down", "JET_JER_EffectiveNP_3__1up", "JET_JER_EffectiveNP_4__1down", "JET_JER_EffectiveNP_4__1up", 
	"JET_JER_EffectiveNP_5__1down", "JET_JER_EffectiveNP_5__1up", "JET_JER_EffectiveNP_6__1down", "JET_JER_EffectiveNP_6__1up", 
	"JET_JER_EffectiveNP_7__1down", "JET_JER_EffectiveNP_7__1up", "JET_JER_EffectiveNP_8__1down", "JET_JER_EffectiveNP_8__1up", 
	"JET_JER_EffectiveNP_9__1down", "JET_JER_EffectiveNP_9__1up"]

if "JetSys4" in systematicType:
	myVariations = ["JET_JER_EffectiveNP_1__1down", "JET_JER_EffectiveNP_1__1up", 
	"JET_JER_EffectiveNP_10__1down", "JET_JER_EffectiveNP_10__1up", "JET_JER_EffectiveNP_11__1down", "JET_JER_EffectiveNP_11__1up", 
	"JET_JER_EffectiveNP_12restTerm__1down", "JET_JER_EffectiveNP_12restTerm__1up", "JET_JER_EffectiveNP_2__1down", "JET_JER_EffectiveNP_2__1up", 
	"JET_JER_EffectiveNP_3__1down", "JET_JER_EffectiveNP_3__1up", "JET_JER_EffectiveNP_4__1down", "JET_JER_EffectiveNP_4__1up", 
	"JET_JER_EffectiveNP_5__1down", "JET_JER_EffectiveNP_5__1up", "JET_JER_EffectiveNP_6__1down", "JET_JER_EffectiveNP_6__1up", 
	"JET_JER_EffectiveNP_7__1down", "JET_JER_EffectiveNP_7__1up", "JET_JER_EffectiveNP_8__1down", "JET_JER_EffectiveNP_8__1up", 
	"JET_JER_EffectiveNP_9__1down", "JET_JER_EffectiveNP_9__1up"]

if "FlavorAllSys1" in systematicType:
	myVariations = ["FT_EFF_Eigen_Light_0__1up", "FT_EFF_Eigen_Light_1__1up", "FT_EFF_Eigen_Light_2__1up", "FT_EFF_Eigen_Light_3__1up", "FT_EFF_Eigen_Light_4__1up"]

if "FlavorAllSys2" in systematicType:
	myVariations = ["FT_EFF_extrapolation_from_charm__1up", "FT_EFF_extrapolation__1up", "FT_EFF_Eigen_C_3__1up", "FT_EFF_Eigen_C_2__1up", "FT_EFF_Eigen_C_1__1up", 
	"FT_EFF_Eigen_C_0__1up", "FT_EFF_Eigen_B_2__1up", "FT_EFF_Eigen_B_1__1up", "FT_EFF_Eigen_B_0__1up"]

if "FlavorAllSys3" in systematicType:
	myVariations = ["FT_EFF_Eigen_Light_4__1down", "FT_EFF_Eigen_Light_3__1down", "FT_EFF_Eigen_Light_2__1down", "FT_EFF_Eigen_Light_1__1down", "FT_EFF_Eigen_Light_0__1down"]

if "FlavorAllSys4" in systematicType:
	myVariations = ["FT_EFF_extrapolation_from_charm__1down", "FT_EFF_extrapolation__1down", "FT_EFF_Eigen_C_3__1down", "FT_EFF_Eigen_C_2__1down", 
	"FT_EFF_Eigen_C_1__1down", "FT_EFF_Eigen_C_0__1down", "FT_EFF_Eigen_B_2__1down", "FT_EFF_Eigen_B_1__1down", "FT_EFF_Eigen_B_0__1down"]

myVariations.append("nominal")
# print myVariations
histb = MakeHists("histb","histb",5,-0.5,4.5)
histc = MakeHists("histc","histc",5,-0.5,4.5)
histl = MakeHists("histl","histl",5,-0.5,4.5)

histb_noMET = MakeHists("histb_noMET","histb_noMET",5,-0.5,4.5)
histc_noMET = MakeHists("histc_noMET","histc_noMET",5,-0.5,4.5)
histl_noMET = MakeHists("histl_noMET","histl_noMET",5,-0.5,4.5)

histb_wHiggs = MakeHists("histb_wHiggs","histb_wHiggs",5,-0.5,4.5)
histc_wHiggs = MakeHists("histc_wHiggs","histc_wHiggs",5,-0.5,4.5)
histl_wHiggs = MakeHists("histl_wHiggs","histl_wHiggs",5,-0.5,4.5)

histb_wHiggs_noMET = MakeHists("histb_wHiggs_noMET","histb_wHiggs_noMET",5,-0.5,4.5)
histc_wHiggs_noMET = MakeHists("histc_wHiggs_noMET","histc_wHiggs_noMET",5,-0.5,4.5)
histl_wHiggs_noMET = MakeHists("histl_wHiggs_noMET","histl_wHiggs_noMET",5,-0.5,4.5)

nbins = 26
binmin = -0.5
binmax = 25.5

histbb = MakeHists("histbb","histbb",nbins,binmin,binmax)
histbc = MakeHists("histbc","histbc",nbins,binmin,binmax)
histbl = MakeHists("histbl","histbl",nbins,binmin,binmax)
histcc = MakeHists("histcc","histcc",nbins,binmin,binmax)
histcl = MakeHists("histcl","histcl",nbins,binmin,binmax)
histll = MakeHists("histll","histll",nbins,binmin,binmax)

histbb_noHGWeight = MakeHists("histbb_noHGWeight","histbb_noHGWeight",nbins,binmin,binmax)
histbc_noHGWeight = MakeHists("histbc_noHGWeight","histbc_noHGWeight",nbins,binmin,binmax)
histbl_noHGWeight = MakeHists("histbl_noHGWeight","histbl_noHGWeight",nbins,binmin,binmax)
histcc_noHGWeight = MakeHists("histcc_noHGWeight","histcc_noHGWeight",nbins,binmin,binmax)
histcl_noHGWeight = MakeHists("histcl_noHGWeight","histcl_noHGWeight",nbins,binmin,binmax)
histll_noHGWeight = MakeHists("histll_noHGWeight","histll_noHGWeight",nbins,binmin,binmax)

histbb_noMET = MakeHists("histbb_noMET","histbb_noMET",nbins,binmin,binmax)
histbc_noMET = MakeHists("histbc_noMET","histbc_noMET",nbins,binmin,binmax)
histbl_noMET = MakeHists("histbl_noMET","histbl_noMET",nbins,binmin,binmax)
histcc_noMET = MakeHists("histcc_noMET","histcc_noMET",nbins,binmin,binmax)
histcl_noMET = MakeHists("histcl_noMET","histcl_noMET",nbins,binmin,binmax)
histll_noMET = MakeHists("histll_noMET","histll_noMET",nbins,binmin,binmax)

histbb_wHiggs = MakeHists("histbb_wHiggs","histbb_wHiggs",nbins,binmin,binmax)
histbc_wHiggs = MakeHists("histbc_wHiggs","histbc_wHiggs",nbins,binmin,binmax)
histbl_wHiggs = MakeHists("histbl_wHiggs","histbl_wHiggs",nbins,binmin,binmax)
histcc_wHiggs = MakeHists("histcc_wHiggs","histcc_wHiggs",nbins,binmin,binmax)
histcl_wHiggs = MakeHists("histcl_wHiggs","histcl_wHiggs",nbins,binmin,binmax)
histll_wHiggs = MakeHists("histll_wHiggs","histll_wHiggs",nbins,binmin,binmax)

histbb_wHiggs_noMET = MakeHists("histbb_wHiggs_noMET","histbb_wHiggs_noMET",nbins,binmin,binmax)
histbc_wHiggs_noMET = MakeHists("histbc_wHiggs_noMET","histbc_wHiggs_noMET",nbins,binmin,binmax)
histbl_wHiggs_noMET = MakeHists("histbl_wHiggs_noMET","histbl_wHiggs_noMET",nbins,binmin,binmax)
histcc_wHiggs_noMET = MakeHists("histcc_wHiggs_noMET","histcc_wHiggs_noMET",nbins,binmin,binmax)
histcl_wHiggs_noMET = MakeHists("histcl_wHiggs_noMET","histcl_wHiggs_noMET",nbins,binmin,binmax)
histll_wHiggs_noMET = MakeHists("histll_wHiggs_noMET","histll_wHiggs_noMET",nbins,binmin,binmax)

hist_sumofweights = ROOT.TH1F("hist_sumofweights", "hist_sumofweights", 1000, 0, 10e12)
hist_HGeventweight = ROOT.TH1F("hist_HGeventweight", "hist_HGeventweight", 1000, -100, 100)
hist_fulleventweight = ROOT.TH1F("hist_fulleventweight", "hist_fulleventweight", 1000, -100, 100)

bins_myy = array.array('d', [90, 105, 120, 130, 140, 150, 175, 200, 250, 300, 350, 400, 500, 600, 700, 1000, 1500, 2000, 3000, 5000, 140000])
hist_myy = MakeHists("hist_myy","hist_myy",20, bins_myy, bins_myy)

# makehistogramsNTUP(inputFile, cutflowPath) #for 90-175 systeamtics only
makehistograms(inputFile, cutflowPath)

newFile.Write()
newFile.Close()


