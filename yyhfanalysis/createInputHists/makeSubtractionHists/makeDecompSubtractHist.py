import ROOT
import sys
import os
import glob
import subprocess


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

# HGamEventInfo_EG_RESOLUTION_ALL__1downAuxDyn


def Make1DHists(name,title,nbin,low,high):
	# print "in Make1DHists"
	hists={}
	hists["nominal"] = ROOT.TH1F(name,title,nbin,low,high)
	return hists


def MakeHists(name,title,nbin,low,high):
	# print "in MakeHists"
	hists = {}
	hists["yj_lp2"] = Make1DHists(name+"_yjlp2",title,nbin,low,high)
	hists["yj_lp3"] = Make1DHists(name+"_yjlp3",title,nbin,low,high)
	hists["yj_lp5"] = Make1DHists(name+"_yjlp5",title,nbin,low,high)
	hists["jj_lp2"] = Make1DHists(name+"_jjlp2",title,nbin,low,high)
	hists["jj_lp3"] = Make1DHists(name+"_jjlp3",title,nbin,low,high)
	hists["jj_lp5"] = Make1DHists(name+"_jjlp5",title,nbin,low,high)
	return hists

def FillHists(tree,hists,file,value,yj2,yj3,yj5,jj2,jj3,jj5,otherweight,dijet):
	# print "in FillHists"
	if (yj2): 
		FillHist(tree,hists,file,value,otherweight,"yj_lp2",dijet);#print "is yj2"
	if (yj3): 
		FillHist(tree,hists,file,value,otherweight,"yj_lp3",dijet);#print "is yj3"
	if (yj5): 
		FillHist(tree,hists,file,value,otherweight,"yj_lp5",dijet);#print "is yj5"
	if (jj2): 
		FillHist(tree,hists,file,value,otherweight,"jj_lp2",dijet);#print "is jj2"
	if (jj3): 
		FillHist(tree,hists,file,value,otherweight,"jj_lp3",dijet);#print "is jj3"
	if (jj5): 
		FillHist(tree,hists,file,value,otherweight,"jj_lp5",dijet);#print "is jj5"

def FillHist(tree,hists,file,value,myweight,type,dijet):
	# print "in FillHist"
	WeightName = "yyHFj_weight"
	if (dijet): WeightName = "yyHFjj_weight"

	# print WeightName
	hists[type]["nominal"].Fill(value,myweight)


def makehistograms(inputFile):
	ROOT.xAOD.Init()

	myFile = ROOT.TFile(inputFile, "READ") 
	myCutflow = ROOT.TFile(cutflowPath, "READ") 
	# myTree = myFile.Get("CollectionTree")
	# nEntries = myTree.GetEntries()
	# print nEntries
	myTree = ROOT.xAOD.MakeTransientTree(myFile, "CollectionTree")
	nEntries = myTree.GetEntries()
	print nEntries

	
	# cutlfow_name = 'CutFlow_MGPy8_ttgammagamma_noallhad_AF2_noDalitz_weighted'
	lumi_mc16 = 0
	if "mc16a" in inputFile:
		lumi_mc16 = 36205.26
	if "mc16d" in inputFile:
		lumi_mc16 = 44307.4
	if "mc16e" in inputFile:
		lumi_mc16 = 58450.1

	# if sampleType == "Sherpa2_myy_90_175":
	# XSWeight = 51.823001;
	# if "Nominal" in inputFile:
	# if "mc16a" in inputFile:
	# 	sumweights = 170568910.236 #170568894.59
	# elif "mc16d" in inputFile:
	# 	sumweights = 260134451.316 #260134530.932
	# elif "mc16e" in inputFile:
	# 	sumweights = 217301645.679 #217301764.774	

	# else:
	# # 	# sumweights = (myFile.Get(cutlfow_name).GetBinContent(1) / myFile.Get(cutlfow_name).GetBinContent(2) ) * myFile.Get(cutlfow_name).GetBinContent(3)	
	# 	sumweights = 1;
	# # 	XSWeight = 1;

	sumweights = (myCutflow.Get(cutlfow_name).GetBinContent(1) / myCutflow.Get(cutlfow_name).GetBinContent(2) ) * myCutflow.Get(cutlfow_name).GetBinContent(3)
	print sumweights

	j = 0
	# nEntries = 5
	for i in range(nEntries):
		if i % 10000 == 0:
			j += 1
			sys.stdout.write("\r{0}>  ".format("="*j)+str( round(i/float(nEntries) * 100, 1))+"%")
			sys.stdout.flush()
		elif i == nEntries:
			sys.stdout.write("\r{0}>  ".format("="*j)+str(100)+"%")
			sys.stdout.flush()

		myTree.GetEntry(i)

		isPassedTriggerMatch = read(myTree.HGamEventInfo,"char", "isPassedTriggerMatch")
		isPassedRelPtCuts = read(myTree.HGamEventInfo,"char", "isPassedRelPtCuts")
		isPassedPreselection = read(myTree.HGamEventInfo,"char", "isPassedPreselection")
		isPassedJetEventClean = read(myTree.HGamEventInfo,"char", "isPassedJetEventClean")

		if (not isPassedTriggerMatch): continue
		if (not isPassedRelPtCuts): continue
		if (not isPassedPreselection): continue
		if (not isPassedJetEventClean): continue

		# if not read(myTree.HGamEventInfo, "char", "isPassed"): continue
		## can still used isPassed because myy window was expanded
		m_yy = (read(myTree.HGamEventInfo, "float", "m_yy")) * 0.001
		if (m_yy > 120 and m_yy < 130): continue ## exclude higgs window


		HGamWeight = read(myTree.HGamEventInfo, "float", "weight");#print "HGamWeight: ", HGamWeight
		# JvtWeight  = read(myTree.HGamEventInfo, "float", "weightJvt");#print "JvtWeight: ", JvtWeight
		XSWeight   = read(myTree.HGamEventInfo, "float", "crossSectionBRfilterEff");#print "XSWeight: ", XSWeight
		# if "data1" in inputFile:
		# 	eventweight = 1;print "data eventweight: ", eventweight
		# else:
		# print "sumweights: ", sumweights, "   XSWeight: ", XSWeight, "  lumi: ", lumi_mc16
		eventweight = (XSWeight * HGamWeight * lumi_mc16) / sumweights;#print "eventweight: ", eventweight
		# print eventweight



		photon_pts = [read(photon,"float","pt") for photon in myTree.HGamPhotons]
		photon_etas = [read(photon,"float","eta") for photon in myTree.HGamPhotons]
		photon_phis = [read(photon,"float","phi") for photon in myTree.HGamPhotons]
		photon_isEMTights = [read(photon,"unsigned int","isEMTight") for photon in myTree.HGamPhotons]
		photon_isTights = [read(photon,"char","isTight") for photon in myTree.HGamPhotons]
		photon_isos = [read(photon,"char","isIsoFixedCutLoose") for photon in myTree.HGamPhotons]

		photon_Origins = [read(photon,"int","truthOrigin") for photon in myTree.HGamPhotons]
		photon_Types = [read(photon,"int","truthType") for photon in myTree.HGamPhotons]
		if (len(photon_pts) < 2): continue ## should be included in isPassed


		## defining what passes looseprime definitions 
		loose1_5 = not (photon_isEMTights[0] & PhotonLoosePrime5); 
		loose2_5 = not (photon_isEMTights[1] & PhotonLoosePrime5);
		loose1_3 = not (photon_isEMTights[0] & PhotonLoosePrime3);
		loose2_3 = not (photon_isEMTights[1] & PhotonLoosePrime3);
		loose1_2 = not (photon_isEMTights[0] & PhotonLoosePrime2);
		loose2_2 = not (photon_isEMTights[1] & PhotonLoosePrime2);

		tight1 = photon_isTights[0]
		tight2 = photon_isTights[1]

		iso1 = photon_isos[0]
		iso2 = photon_isos[1]

		passtight1 = (tight1 and iso1)
		passtight2 = (tight2 and iso2)

		passloose1_5 = (loose1_5 and not tight1)
		passloose2_5 = (loose2_5 and not tight2)
		passloose1_3 = (loose1_3 and not tight1)
		passloose2_3 = (loose2_3 and not tight2)
		passloose1_2 = (loose1_2 and not tight1)
		passloose2_2 = (loose2_2 and not tight2)

		isyj5 = False
		isjj5 = False
		isyj3 = False
		isjj3 = False
		isyj2 = False
		isjj2 = False

		if ( (passtight1 and passloose2_5) or (passtight2 and passloose1_5) ): isyj5 = True
		if ( passloose1_5 and passloose2_5 ): isjj5 = True

		if ( (passtight1 and passloose2_3) or (passtight2 and passloose1_3) ): isyj3 = True
		if ( passloose1_3 and passloose2_3 ): isjj3 = True

		if ( (passtight1 and passloose2_2) or (passtight2 and passloose1_2) ): isyj2 = True
		if ( passloose1_2 and passloose2_2 ): isjj2 = True

		if (not isyj5 and not isjj5 and not isyj3 and not isjj3 and not isyj2 and not isjj2): continue


		LeadJet_truthlabel    = read(myTree.HGamEventInfo, "int", "yyHF_leadjet_truthlabel")
		SubLeadJet_truthlabel = read(myTree.HGamEventInfo, "int", "yyHF_subleadjet_truthlabel")

		LeadJet_btagbin    = read(myTree.HGamEventInfo ,"int", "yyHF_leadjet_btagbin")
		SubLeadJet_btagbin = read(myTree.HGamEventInfo, "int", "yyHF_subleadjet_btagbin")

		expanded_binning = LeadJet_btagbin * 5 + SubLeadJet_btagbin

		yyHF_met = read(myTree.HGamEventInfo, "float", "yyHF_met") * 0.001 #convert to GeV
		# print "m_yy is ", m_yy

		yyHFjj_weight = read(myTree.HGamEventInfo ,"float", "yyHFjj_weight") 
		yyHFj_weight  = read(myTree.HGamEventInfo ,"float", "yyHFj_weight") 

		nElectrons = read(myTree.HGamEventInfo ,"int", "yyHF_nelectron") 
		nMuons = read(myTree.HGamEventInfo ,"int", "yyHF_nmuon")
		nLeptons = nMuons + nElectrons

		Njet_central = read(myTree.HGamEventInfo ,"int", "yyHF_Njet_central")


		if (nLeptons == 0 and yyHF_met < 40): 
			# if (nLeptons == 0): 
			if (LeadJet_truthlabel == 5):
				FillHists(myTree,histb,file,LeadJet_btagbin,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFj_weight,False)
			elif (LeadJet_truthlabel == 4):
				FillHists(myTree,histc,file,LeadJet_btagbin,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFj_weight,False)
			else:
				FillHists(myTree,histl,file,LeadJet_btagbin,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFj_weight,False) 

		if (nLeptons == 0): 
			# if (nLeptons == 0): 
			if (LeadJet_truthlabel == 5):
				FillHists(myTree,histb_noMET,file,LeadJet_btagbin,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFj_weight,False)
			elif (LeadJet_truthlabel == 4):
				FillHists(myTree,histc_noMET,file,LeadJet_btagbin,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFj_weight,False)
			else:
				FillHists(myTree,histl_noMET,file,LeadJet_btagbin,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFj_weight,False) 

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

				if expanded_binning > 24:
					METpass = True

				elif yyHF_met < 60: 
					METpass = True

				else:
					METpass = False

				if METpass == True:
					if (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 5):   ##bb
						FillHists(myTree,histbb,file,expanded_binning,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFjj_weight,True)
					elif (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 4): ##bc
						FillHists(myTree,histbc,file,expanded_binning,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFjj_weight,True)
					elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 5): ##cb
						FillHists(myTree,histbc,file,expanded_binning,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFjj_weight,True)
					elif (LeadJet_truthlabel == 5 or SubLeadJet_truthlabel == 5):  ##bl
						FillHists(myTree,histbl,file,expanded_binning,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFjj_weight,True)
					elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 4): ##cc
						FillHists(myTree,histcc,file,expanded_binning,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFjj_weight,True)
					elif (LeadJet_truthlabel == 4 or SubLeadJet_truthlabel == 4):  ##cl
						FillHists(myTree,histcl,file,expanded_binning,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFjj_weight,True)
					else:
						FillHists(myTree,histll,file,expanded_binning,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFjj_weight,True)    

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

				if (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 5):   ##bb
					FillHists(myTree,histbb_noMET,file,expanded_binning,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFjj_weight,True)
				elif (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 4): ##bc
					FillHists(myTree,histbc_noMET,file,expanded_binning,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFjj_weight,True)
				elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 5): ##cb
					FillHists(myTree,histbc_noMET,file,expanded_binning,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFjj_weight,True)
				elif (LeadJet_truthlabel == 5 or SubLeadJet_truthlabel == 5):  ##bl
					FillHists(myTree,histbl_noMET,file,expanded_binning,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFjj_weight,True)
				elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 4): ##cc
					FillHists(myTree,histcc_noMET,file,expanded_binning,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFjj_weight,True)
				elif (LeadJet_truthlabel == 4 or SubLeadJet_truthlabel == 4):  ##cl
					FillHists(myTree,histcl_noMET,file,expanded_binning,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFjj_weight,True)
				else:
					FillHists(myTree,histll_noMET,file,expanded_binning,isyj2,isyj3,isyj5,isjj2,isjj3,isjj5,eventweight*yyHFjj_weight,True)         
	print

	ROOT.xAOD.ClearTransientTrees()	

inputFile = sys.argv[1]
outputFile = sys.argv[2]
sampleType = sys.argv[3]
mcType = sys.argv[4]
systematicType = "Nominal"
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
	cutflowPath = 'cutflows/'+systematicType+"/"+mcType+'.CutFlow_'+sampleType+'.root'
else:
	cutlfow_name = "CutFlow_"+sampleType+"_noDalitz_weighted"
	cutflowPath = 'cutflows/'+systematicType+"/"+mcType+'.CutFlow_'+sampleType+'.root'

print "Using cutflow ", cutlfow_name, " from ",cutflowPath

# print "Creating output " + outputFile + ".root for file " + inputFile
newFile = ROOT.TFile(outputFile+".root", "recreate")
newFile.cd()

nbins = 26
binmin = -0.5
binmax = 25.5

histb = MakeHists("histb","histb",5,-0.5,4.5)
histc = MakeHists("histc","histc",5,-0.5,4.5)
histl = MakeHists("histl","histl",5,-0.5,4.5)

histb_noMET = MakeHists("histb_noMET","histb_noMET",5,-0.5,4.5)
histc_noMET = MakeHists("histc_noMET","histc_noMET",5,-0.5,4.5)
histl_noMET = MakeHists("histl_noMET","histl_noMET",5,-0.5,4.5)

## btagbin leading*5 + btagbin subleading, last bins are "has electron and then has muon"
histbb = MakeHists("histbb","histbb",nbins,binmin,binmax)
histbc = MakeHists("histbc","histbc",nbins,binmin,binmax)
histbl = MakeHists("histbl","histbl",nbins,binmin,binmax)
histcc = MakeHists("histcc","histcc",nbins,binmin,binmax)
histcl = MakeHists("histcl","histcl",nbins,binmin,binmax)
histll = MakeHists("histll","histll",nbins,binmin,binmax)

histbb_noMET = MakeHists("histbb_noMET","histbb_noMET",nbins,binmin,binmax)
histbc_noMET = MakeHists("histbc_noMET","histbc_noMET",nbins,binmin,binmax)
histbl_noMET = MakeHists("histbl_noMET","histbl_noMET",nbins,binmin,binmax)
histcc_noMET = MakeHists("histcc_noMET","histcc_noMET",nbins,binmin,binmax)
histcl_noMET = MakeHists("histcl_noMET","histcl_noMET",nbins,binmin,binmax)
histll_noMET = MakeHists("histll_noMET","histll_noMET",nbins,binmin,binmax)

PhotonLoosePrime2 = 2620417
PhotonLoosePrime3 = 2489345
PhotonLoosePrime5 = 2227201

makehistograms(inputFile)

newFile.Write()
newFile.Close()
