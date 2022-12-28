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


def makehistograms(inputFile):
	ROOT.xAOD.Init()

	myFile = ROOT.TFile(inputFile, "READ") 
	# myTree = myFile.Get("CollectionTree")
	# nEntries = myTree.GetEntries()
	# print nEntries
	myTree = ROOT.xAOD.MakeTransientTree(myFile, "CollectionTree")
	nEntries = myTree.GetEntries()
	print nEntries


	eventweight = 1


	j = 0
	# nEntries = 10000
	for i in range(nEntries):
		if i % 100000 == 0:
			j += 1
			sys.stdout.write("\r{0}>  ".format("="*j)+str( round(i/float(nEntries) * 100, 1))+"%")
			sys.stdout.flush()
		elif i == nEntries:
			sys.stdout.write("\r{0}>  ".format("="*j)+str(100)+"%")
			sys.stdout.flush()

		myTree.GetEntry(i)
		# if not read(myTree.HGamEventInfo, "char", "isPassed"): continue

		isPassedTriggerMatch = read(myTree.HGamEventInfo,"char", "isPassedTriggerMatch")
		isPassedRelPtCuts = read(myTree.HGamEventInfo,"char", "isPassedRelPtCuts")
		isPassedPreselection = read(myTree.HGamEventInfo,"char", "isPassedPreselection")

		if (not isPassedTriggerMatch): continue
		if (not isPassedRelPtCuts): continue
		if (not isPassedPreselection): continue

		## can still used isPassed because myy window was expanded
		m_yy = (read(myTree.HGamEventInfo, "float", "m_yy")) * 0.001
		if (m_yy > 120 and m_yy < 130): continue ## exclude higgs window
		# print "outside higgs window"


		photon_pts = [read(photon,"float","pt") for photon in myTree.HGamPhotons]
		photon_etas = [read(photon,"float","eta") for photon in myTree.HGamPhotons]
		photon_phis = [read(photon,"float","phi") for photon in myTree.HGamPhotons]
		photon_isEMTights = [read(photon,"unsigned int","isEMTight") for photon in myTree.HGamPhotons]
		photon_isTights = [read(photon,"char","isTight") for photon in myTree.HGamPhotons]
		photon_isos = [read(photon,"char","isIsoFixedCutLoose") for photon in myTree.HGamPhotons]

		# photon_Origins = [read(photon,"int","truthOrigin") for photon in myTree.HGamPhotons]
		# photon_Types = [read(photon,"int","truthType") for photon in myTree.HGamPhotons]
		if (len(photon_pts) < 2): continue ## should be included in isPassed
		# print "has 2 photons"


		## defining what passes looseprime definitions 
		loose1_5 = not (photon_isEMTights[0] & PhotonLoosePrime5); 
		loose2_5 = not (photon_isEMTights[1] & PhotonLoosePrime5);
		loose1_3 = not (photon_isEMTights[0] & PhotonLoosePrime3);
		loose2_3 = not (photon_isEMTights[1] & PhotonLoosePrime3);
		loose1_2 = not (photon_isEMTights[0] & PhotonLoosePrime2);
		loose2_2 = not (photon_isEMTights[1] & PhotonLoosePrime2);



		tight1 = photon_isTights[0]
		tight2 = photon_isTights[1]
		# print "tight1:tight2 ",tight1, tight2
	

		iso1 = photon_isos[0]
		iso2 = photon_isos[1]
		# print "iso1:iso2 ",iso1, iso2

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

		# if (not passtight1 or not passtight2):
		# 	print "passtight1:passtight2 ",passtight1, passtight2
		# 	print "passloose1_5:passloose2_5 ",passloose1_5, passloose2_5
		# 	print "passloose1_3:passloose2_3 ",passloose1_3, passloose2_3
		# 	print "passloose1_2:passloose2_2 ",passloose1_2, passloose2_2
		# 	print "PhotonLoosePrime2: yj: ",isyj2,"jj: ",isjj2
		# 	print "PhotonLoosePrime3: yj: ",isyj3,"jj: ",isjj3
		# 	print "PhotonLoosePrime5: yj: ",isyj5,"jj: ",isjj5
		# if (not isyj5 and not isjj5 and not isyj3 and not isjj3 and not isyj2 and not isjj2): print("Not lp, skipping")
		if (not isyj5 and not isjj5 and not isyj3 and not isjj3 and not isyj2 and not isjj2): continue

		# LeadJet_truthlabel    = read(myTree.HGamEventInfo, "int", "yyHF_leadjet_truthlabel")
		# SubLeadJet_truthlabel = read(myTree.HGamEventInfo, "int", "yyHF_subleadjet_truthlabel")

		LeadJet_btagbin    = read(myTree.HGamEventInfo ,"int", "yyHF_leadjet_btagbin")
		SubLeadJet_btagbin = read(myTree.HGamEventInfo, "int", "yyHF_subleadjet_btagbin")

		expanded_binning = LeadJet_btagbin * 5 + SubLeadJet_btagbin

		yyHF_met = read(myTree.HGamEventInfo, "float", "yyHF_met") * 0.001 #convert to GeV
		# print "m_yy is ", m_yy

		nElectrons = read(myTree.HGamEventInfo ,"int", "yyHF_nelectron") 
		nMuons = read(myTree.HGamEventInfo ,"int", "yyHF_nmuon")
		nLeptons = nMuons + nElectrons

		Njet_central = read(myTree.HGamEventInfo ,"int", "yyHF_Njet_central")
         


		if SubLeadJet_btagbin > -1:
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


			# print "checking to fill"

			if expanded_binning > 24:
				METpass = True

			elif yyHF_met < 60: 
				METpass = True

			else:
				METpass = False

			if METpass == True:
				if (isyj2):
					histyj_lp2.Fill(expanded_binning);#print("filling histyj_lp2")
				elif (isjj2):
					histjj_lp2.Fill(expanded_binning);#print("filling histjj_lp2")
				elif (isyj3):
					histyj_lp3.Fill(expanded_binning);#print("filling histyj_lp3")
				elif (isjj3):
					histjj_lp3.Fill(expanded_binning);#print("filling histjj_lp3")
				elif (isyj5):
					histyj_lp5.Fill(expanded_binning);#print("filling histyj_lp5")
				elif (isjj5):
					histjj_lp5.Fill(expanded_binning);#print("filling histjj_lp5")
		if SubLeadJet_btagbin > -1:
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

			# print "checking to fill"
			if (isyj2):
				histyj_lp2_noMET.Fill(expanded_binning);#print("filling histyj_lp2")
			elif (isjj2):
				histjj_lp2_noMET.Fill(expanded_binning);#print("filling histjj_lp2")
			elif (isyj3):
				histyj_lp3_noMET.Fill(expanded_binning);#print("filling histyj_lp3")
			elif (isjj3):
				histjj_lp3_noMET.Fill(expanded_binning);#print("filling histjj_lp3")
			elif (isyj5):
				histyj_lp5_noMET.Fill(expanded_binning);#print("filling histyj_lp5")
			elif (isjj5):
				histjj_lp5_noMET.Fill(expanded_binning);#print("filling histjj_lp5")

	print

	ROOT.xAOD.ClearTransientTrees()	



PhotonLoosePrime2 = 2620417
PhotonLoosePrime3 = 2489345
PhotonLoosePrime5 = 2227201

inputFile = sys.argv[1]
outputFile = sys.argv[2]


print "Creating output files"
newFile_lp2 = ROOT.TFile("data_lp2.root", "recreate")
newFile_lp3 = ROOT.TFile("data_lp3.root", "recreate")
newFile_lp5 = ROOT.TFile("data_lp5.root", "recreate")

nbins = 26
binmin = -0.5
binmax=25.5

newFile_lp2.cd()
histyj_lp2 = ROOT.TH1F("histyj_lp2","histyj_lp2",nbins,binmin,binmax)
histjj_lp2 = ROOT.TH1F("histjj_lp2","histjj_lp2",nbins,binmin,binmax)
histyj_lp2_noMET = ROOT.TH1F("histyj_lp2_noMET","histyj_lp2_noMET",nbins,binmin,binmax)
histjj_lp2_noMET = ROOT.TH1F("histjj_lp2_noMET","histjj_lp2_noMET",nbins,binmin,binmax)

newFile_lp3.cd()
histyj_lp3 = ROOT.TH1F("histyj_lp3","histyj_lp3",nbins,binmin,binmax)
histjj_lp3 = ROOT.TH1F("histjj_lp3","histjj_lp3",nbins,binmin,binmax)
histyj_lp3_noMET = ROOT.TH1F("histyj_lp3_noMET","histyj_lp3_noMET",nbins,binmin,binmax)
histjj_lp3_noMET = ROOT.TH1F("histjj_lp3_noMET","histjj_lp3_noMET",nbins,binmin,binmax)

newFile_lp5.cd()
histyj_lp5 = ROOT.TH1F("histyj_lp5","histyj_lp5",nbins,binmin,binmax)
histjj_lp5 = ROOT.TH1F("histjj_lp5","histjj_lp5",nbins,binmin,binmax)
histyj_lp5_noMET = ROOT.TH1F("histyj_lp5_noMET","histyj_lp5_noMET",nbins,binmin,binmax)
histjj_lp5_noMET = ROOT.TH1F("histjj_lp5_noMET","histjj_lp5_noMET",nbins,binmin,binmax)


makehistograms(inputFile)

newFile_lp2.cd()
histyj_lp2.Write()
histjj_lp2.Write()
histyj_lp2_noMET.Write()
histjj_lp2_noMET.Write()
newFile_lp2.Close()

newFile_lp3.cd()
histyj_lp3.Write()
histjj_lp3.Write()
histyj_lp3_noMET.Write()
histjj_lp3_noMET.Write()
newFile_lp3.Close()

newFile_lp5.cd()
histyj_lp5.Write()
histjj_lp5.Write()
histyj_lp5_noMET.Write()
histjj_lp5_noMET.Write()
newFile_lp5.Close()

