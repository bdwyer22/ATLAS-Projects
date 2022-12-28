import ROOT
import sys
import os
import glob
import subprocess
from array import array
from math import pi, sqrt

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
	hists["nominal"] = ROOT.TH1F(name,title,nbin,low,high)
	hists["nominal"].SetLineWidth(2)
	if "yyHF_OR" in name:
		hists["nominal"].SetLineColor(ROOT.kViolet+1)
		hists["nominal"].SetLineStyle(2)
	elif "yyHF_notOR" in name:
		hists["nominal"].SetLineColor(ROOT.kPink+9)
	elif "notOR" in name:
		hists["nominal"].SetLineColor(ROOT.kRed)
	elif "OR" in name:
		hists["nominal"].SetLineColor(ROOT.kSpring)
		hists["nominal"].SetLineStyle(2)
	elif "yyHF" in name:
		hists["nominal"].SetLineColor(ROOT.kAzure+10)
	else:
		hists["nominal"].SetLineColor(ROOT.kBlack)
	return hists


def FillHists(hists,varName,binValue,myWeight):
	hists[varName].Fill(binValue,myWeight)


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

	print sumweights

	j = 0
	# nEntries = 2000
	for i in range(nEntries):
		
		if i % 10000 == 0:
			j += 1
			sys.stdout.write("\r{0}>  ".format("="*j)+str( round(i/float(nEntries) * 100, 1))+"%")
			sys.stdout.flush()
		elif i == (nEntries-1):
			sys.stdout.write("\r{0}>  ".format("="*j)+str(100)+" %")
			sys.stdout.flush()

		myTree.GetEntry(i)


		isPassed = read(myTree.HGamEventInfo, "char", "isPassed")
		if not isPassed: continue

		eventNumber = read(myTree.EventInfo, "ULong64_t", "eventNumber")
		# print eventNumber

		XSWeight   = read(myTree.HGamEventInfo, "float", "crossSectionBRfilterEff");#print "XSWeight: ", XSWeight
		

		HGamWeight =  read(myTree.HGamEventInfo, "float", "weight")
		JVTWeight =  read(myTree.HGamEventInfo, "float", "weightJvt")

		eventweight = (XSWeight * HGamWeight * lumi_mc16) / sumweights;#print "eventweight: ", eventweight

		m_yy = read(myTree.HGamEventInfo, "float", "m_yy") * 0.001
		# if (m_yy > 120 and m_yy < 130): continue ## exclude higgs window
		FillHists(hist_myy,"nominal",m_yy,eventweight)

		j1_pt = read(myTree.HGamEventInfo, "float", "yyHF_leadjet_pt")
		j2_pt = read(myTree.HGamEventInfo, "float", "yyHF_subleadjet_pt")

		FillHists(hist_j1pt,"nominal",j1_pt,eventweight*JVTWeight)
		FillHists(hist_j2pt,"nominal",j2_pt,eventweight*JVTWeight)


		y1_pt = -999; y1_phi = -999; y1_eta = -999
		y2_pt = -999; y2_phi = -999; y2_eta = -999

		photon1 = myTree.HGamPhotons[0]
		photon2 = myTree.HGamPhotons[1]

		y1_pt = read(photon1,"float","pt");y1_eta = read(photon1,"float","eta");y1_phi = read(photon1,"float","phi");y1_m = read(photon1,"float","m")
		y2_pt = read(photon2,"float","pt");y2_eta = read(photon2,"float","eta");y2_phi = read(photon2,"float","phi");y2_m = read(photon2,"float","m")

		FillHists(hist_y1pt,"nominal",y1_pt,eventweight)
		FillHists(hist_y2pt,"nominal",y2_pt,eventweight)
		
		dR_y1 = 999
		dR_y2 = 999

		for electron in myTree.HGamElectrons:
			el_eta = read(electron,"float","eta")
			el_phi = read(electron,"float","phi")
			tmp_deta1 = y1_eta  - el_eta
			tmp_dphi1 = y1_phi  - el_phi

			tmp_deta2 = y2_eta - el_eta
			tmp_dphi2 = y2_phi - el_phi

			if(abs(tmp_dphi1) > pi): tmp_dphi1 = 2 * pi - abs(tmp_dphi1);
			if(abs(tmp_dphi2) > pi): tmp_dphi2 = 2 * pi - abs(tmp_dphi2);

			tmp_dR1 = (sqrt(tmp_dphi1**2 + tmp_deta1**2));
			tmp_dR2 = (sqrt(tmp_dphi2**2 + tmp_deta2**2));

			if tmp_dR1 < dR_y1:
				dR_y1 = tmp_dR1
			if tmp_dR2 < dR_y2:
				dR_y2 = tmp_dR2

		for muon in myTree.HGamMuons:
			mu_eta = read(muon,"float","eta")
			mu_phi = read(muon,"float","phi")
			tmp_deta1 = y1_eta  - mu_eta
			tmp_dphi1 = y1_phi  - mu_phi

			tmp_deta2 = y2_eta - mu_eta
			tmp_dphi2 = y2_phi - mu_phi

			if(abs(tmp_dphi1) > pi): tmp_dphi1 = 2 * pi - abs(tmp_dphi1);
			if(abs(tmp_dphi2) > pi): tmp_dphi2 = 2 * pi - abs(tmp_dphi2);

			tmp_dR1 = (sqrt(tmp_dphi1**2 + tmp_deta1**2));
			tmp_dR2 = (sqrt(tmp_dphi2**2 + tmp_deta2**2));

			if tmp_dR1 < dR_y1:
				dR_y1 = tmp_dR1
			if tmp_dR2 < dR_y2:
				dR_y2 = tmp_dR2

		for tau in myTree.HGamTauJets:
			tau_eta = read(tau,"float","eta")
			tau_phi = read(tau,"float","phi")
			tmp_deta1 = y1_eta  - tau_eta
			tmp_dphi1 = y1_phi  - tau_phi

			tmp_deta2 = y2_eta - tau_eta
			tmp_dphi2 = y2_phi - tau_phi

			if(abs(tmp_dphi1) > pi): tmp_dphi1 = 2 * pi - abs(tmp_dphi1);
			if(abs(tmp_dphi2) > pi): tmp_dphi2 = 2 * pi - abs(tmp_dphi2);

			tmp_dR1 = (sqrt(tmp_dphi1**2 + tmp_deta1**2));
			tmp_dR2 = (sqrt(tmp_dphi2**2 + tmp_deta2**2));

			if tmp_dR1 < dR_y1:
				dR_y1 = tmp_dR1
			if tmp_dR2 < dR_y2:
				dR_y2 = tmp_dR2

		FillHists(hist_dR1,"nominal",dR_y1,eventweight)
		FillHists(hist_dR2,"nominal",dR_y2,eventweight)

		if "MGPy8_ttgamma_nonallhadronic" in sampleType or "Sherpa_tt_dilepton" in sampleType:
			inOverlap = read(myTree.HGamTruthEventInfo, "int", "GammaOR_inOverlap")
		else:
			inOverlap = 0 

		if inOverlap == 1: 
			FillHists(hist_dR1_OR,"nominal",dR_y1,eventweight)
			FillHists(hist_dR2_OR,"nominal",dR_y2,eventweight)
			FillHists(hist_y1pt_OR,"nominal",y1_pt * 0.001,eventweight)
			FillHists(hist_y2pt_OR,"nominal",y2_pt * 0.001,eventweight)
			FillHists(hist_j1pt_OR,"nominal",j1_pt * 0.001,eventweight*JVTWeight)
			FillHists(hist_j2pt_OR,"nominal",j2_pt * 0.001,eventweight*JVTWeight)
			FillHists(hist_myy_OR,"nominal",m_yy,eventweight)
		elif inOverlap == 0: 
			FillHists(hist_dR1_notOR,"nominal",dR_y1,eventweight)
			FillHists(hist_dR2_notOR,"nominal",dR_y2,eventweight)
			FillHists(hist_y1pt_notOR,"nominal",y1_pt * 0.001,eventweight)
			FillHists(hist_y2pt_notOR,"nominal",y2_pt * 0.001,eventweight)
			FillHists(hist_j1pt_notOR,"nominal",j1_pt * 0.001,eventweight*JVTWeight)
			FillHists(hist_j2pt_notOR,"nominal",j2_pt * 0.001,eventweight*JVTWeight)
			FillHists(hist_myy_notOR,"nominal",m_yy,eventweight)

		yyHFleadCheck = read(myTree.HGamEventInfo, "int", "yyHF_leadjet_btagbin")
		yyHFsubleadCheck = read(myTree.HGamEventInfo, "int", "yyHF_subleadjet_btagbin")
		yyHF_cutFlow = read(myTree.HGamEventInfo, "int", "yyHF_cutFlow")
		yyHFjj_weight = read(myTree.HGamEventInfo, "float", "yyHFjj_weight")
		yyHFj_weight = read(myTree.HGamEventInfo, "float", "yyHFj_weight")


		yyHF_subleadjet_pt = read(myTree.HGamEventInfo, "float", "yyHF_subleadjet_pt")

		yyHF_leadjet_truthlabel = read(myTree.HGamEventInfo, "int", "yyHF_leadjet_truthlabel")
		yyHF_subleadjet_truthlabel = read(myTree.HGamEventInfo, "int", "yyHF_subleadjet_truthlabel")
		yyHFjj_weight = read(myTree.HGamEventInfo, "float", "yyHFjj_weight")

		if (j1_pt * 0.001 >= 25 and j2_pt * 0.001 >= 25):
			passPts = True
		else:
			passPts = False
		
		if (yyHFleadCheck >= 0 and yyHFsubleadCheck >= 0 and yyHF_cutFlow == 3 and passPts==True):

			FillHists(hist_dR1_yyHF,"nominal",dR_y1,eventweight*yyHFjj_weight)
			FillHists(hist_dR2_yyHF,"nominal",dR_y2,eventweight*yyHFjj_weight)
			FillHists(hist_y1pt_yyHF,"nominal",y1_pt * 0.001,eventweight*yyHFjj_weight)
			FillHists(hist_y2pt_yyHF,"nominal",y2_pt * 0.001,eventweight*yyHFjj_weight)
			FillHists(hist_j1pt_yyHF,"nominal",j1_pt * 0.001,eventweight*yyHFjj_weight)
			FillHists(hist_j2pt_yyHF,"nominal",j2_pt * 0.001,eventweight*yyHFjj_weight)
			FillHists(hist_myy_yyHF,"nominal",m_yy,eventweight*yyHFjj_weight)
			if inOverlap == 1: 
				FillHists(hist_dR1_yyHF_OR,"nominal",dR_y1,eventweight*yyHFjj_weight)
				FillHists(hist_dR2_yyHF_OR,"nominal",dR_y2,eventweight*yyHFjj_weight)
				FillHists(hist_y1pt_yyHF_OR,"nominal",y1_pt * 0.001,eventweight*yyHFjj_weight)
				FillHists(hist_y2pt_yyHF_OR,"nominal",y2_pt * 0.001,eventweight*yyHFjj_weight)
				FillHists(hist_j1pt_yyHF_OR,"nominal",j1_pt * 0.001,eventweight*yyHFjj_weight)
				FillHists(hist_j2pt_yyHF_OR,"nominal",j2_pt * 0.001,eventweight*yyHFjj_weight)
				FillHists(hist_myy_yyHF_OR,"nominal",m_yy,eventweight*yyHFjj_weight)
			elif inOverlap == 0: 
				FillHists(hist_dR1_yyHF_notOR,"nominal",dR_y1,eventweight*yyHFjj_weight)
				FillHists(hist_dR2_yyHF_notOR,"nominal",dR_y2,eventweight*yyHFjj_weight)
				FillHists(hist_y1pt_yyHF_notOR,"nominal",y1_pt * 0.001,eventweight*yyHFjj_weight)
				FillHists(hist_y2pt_yyHF_notOR,"nominal",y2_pt * 0.001,eventweight*yyHFjj_weight)
				FillHists(hist_j1pt_yyHF_notOR,"nominal",j1_pt * 0.001,eventweight*yyHFjj_weight)
				FillHists(hist_j2pt_yyHF_notOR,"nominal",j2_pt * 0.001,eventweight*yyHFjj_weight)
				FillHists(hist_myy_yyHF_notOR,"nominal",m_yy,eventweight*yyHFjj_weight)



		if (yyHFleadCheck >= 0 and yyHFsubleadCheck >= 0 and yyHF_cutFlow == 3 and passPts==True):
			eventweight *= yyHFjj_weight

			mu = read(myTree.HGamEventInfo, "float", "mu")
			yyHF_met = read(myTree.HGamEventInfo, "float", "yyHF_met")
			yyHF_Njet_central = read(myTree.HGamEventInfo, "int", "yyHF_Njet_central")
			yyHF_leadjet_btagbin = read(myTree.HGamEventInfo, "int", "yyHF_leadjet_btagbin")
			yyHF_subleadjet_btagbin = read(myTree.HGamEventInfo, "int", "yyHF_subleadjet_btagbin")
			yyHF_leadjet_eta = read(myTree.HGamEventInfo, "float", "yyHF_leadjet_eta")
			yyHF_subleadjet_eta = read(myTree.HGamEventInfo, "float", "yyHF_subleadjet_eta")
			yyHF_leadjet_m = read(myTree.HGamEventInfo, "float", "yyHF_leadjet_m")
			yyHF_subleadjet_m = read(myTree.HGamEventInfo, "float", "yyHF_subleadjet_m")
			yyHF_leadjet_phi = read(myTree.HGamEventInfo, "float", "yyHF_leadjet_phi")
			yyHF_subleadjet_phi = read(myTree.HGamEventInfo, "float", "yyHF_subleadjet_phi")

			FillHists(hist_mu, "nominal", mu, eventweight)
			FillHists(hist_yyHF_met, "nominal", yyHF_met * 0.001, eventweight)
			FillHists(hist_yyHF_Njet_central, "nominal", yyHF_Njet_central, eventweight)
			FillHists(hist_yyHF_leadjet_btagbin, "nominal", yyHF_leadjet_btagbin, eventweight)
			FillHists(hist_yyHF_subleadjet_btagbin, "nominal", yyHF_subleadjet_btagbin, eventweight)
			FillHists(hist_yyHF_leadjet_eta, "nominal", yyHF_leadjet_eta, eventweight)
			FillHists(hist_yyHF_subleadjet_eta, "nominal", yyHF_subleadjet_eta, eventweight)
			FillHists(hist_yyHF_leadjet_m, "nominal", yyHF_leadjet_m * 0.001, eventweight)
			FillHists(hist_yyHF_subleadjet_m, "nominal", yyHF_subleadjet_m * 0.001, eventweight)
			FillHists(hist_yyHF_leadjet_phi, "nominal", yyHF_leadjet_phi, eventweight)
			FillHists(hist_yyHF_subleadjet_phi, "nominal", yyHF_subleadjet_phi, eventweight)
			FillHists(hist_yyHF_leadjet_pt, "nominal", j1_pt * 0.001, eventweight)
			FillHists(hist_yyHF_subleadjet_pt, "nominal", j2_pt * 0.001, eventweight)
			FillHists(hist_yyHF_leadjet_truthlabel, "nominal", yyHF_leadjet_truthlabel, eventweight)
			FillHists(hist_yyHF_subleadjet_truthlabel, "nominal", yyHF_subleadjet_truthlabel, eventweight)

			#create TLV of j1, j2, y2, y2 to calculate. When doing dphi use DR trick
			j1 = ROOT.TLorentzVector();j1.SetPtEtaPhiM(j1_pt, yyHF_leadjet_eta, yyHF_leadjet_phi, yyHF_leadjet_m)
			j2 = ROOT.TLorentzVector();j2.SetPtEtaPhiM(j2_pt, yyHF_subleadjet_eta, yyHF_subleadjet_phi, yyHF_subleadjet_m)
			y1 = ROOT.TLorentzVector();y1.SetPtEtaPhiM(y1_pt, y1_eta, y1_phi, y1_m)
			y2 = ROOT.TLorentzVector();y2.SetPtEtaPhiM(y2_pt, y2_eta, y2_phi, y2_m)

			jj_system = j1 + j2
			yy_system = y1 + y2

			yyj_system = y1 + y2 + j1 
			yyjj_system = y1 + y2 + j1 + j2

			detayy = y1_eta  - y2_eta
			dphiyy = y1_phi  - y2_phi
			if(abs(dphiyy) > pi): dphiyy = 2 * pi - abs(dphiyy);
			dRyy = (sqrt(dphiyy**2 + detayy**2));

			detajj = yyHF_leadjet_eta  - yyHF_subleadjet_eta
			dphijj = yyHF_leadjet_phi  - yyHF_subleadjet_phi
			if(abs(dphijj) > pi): dphijj = 2 * pi - abs(dphijj);

			dphijjyy = yy_system.Phi()  - jj_system.Phi()
			if(abs(dphijjyy) > pi): dphijjyy = 2 * pi - abs(dphijjyy);

			mjj = jj_system.M() * 0.001
			myyj = yyj_system.M() * 0.001
			myyjj = yyjj_system.M() * 0.001
			pT_jj = jj_system.Pt() * 0.001
			pT_yy = yy_system.Pt() * 0.001
			pT_yyj = yyj_system.Pt() * 0.001
			pT_yyjj = yyjj_system.Pt() * 0.001
			DR_y_y = dRyy
			Deta_j_j = detajj
			Dphi_j_j = dphijj
			Dphi_y_y = dphiyy
			Dphi_yy_jj = dphijjyy

			FillHists(hist_mjj, "nominal", mjj, eventweight)
			FillHists(hist_myyj, "nominal", myyj, eventweight)
			FillHists(hist_myyjj, "nominal", myyjj, eventweight)
			FillHists(hist_pT_jj, "nominal", pT_jj, eventweight)
			FillHists(hist_pT_yy, "nominal", pT_yy, eventweight)
			FillHists(hist_pT_yyj, "nominal", pT_yyj, eventweight)
			FillHists(hist_pT_yyjj, "nominal", pT_yyjj, eventweight)
			FillHists(hist_DR_y_y, "nominal", DR_y_y, eventweight)
			FillHists(hist_Deta_j_j, "nominal", Deta_j_j, eventweight)
			FillHists(hist_Dphi_j_j, "nominal", Dphi_j_j, eventweight)
			FillHists(hist_Dphi_y_y, "nominal", Dphi_y_y, eventweight)
			FillHists(hist_Dphi_yy_jj, "nominal", Dphi_yy_jj, eventweight)

			if yyHF_leadjet_truthlabel == 5 and yyHF_subleadjet_truthlabel == 5:
				FillHists(hist_j1pt_truthbb, "nominal", j1_pt * 0.001, eventweight)
				FillHists(hist_j1eta_truthbb, "nominal", yyHF_leadjet_eta, eventweight)
				FillHists(hist_j1phi_truthbb, "nominal", yyHF_leadjet_phi, eventweight)
				FillHists(hist_j2pt_truthbb, "nominal", j2_pt * 0.001, eventweight)
				FillHists(hist_j2eta_truthbb, "nominal", yyHF_subleadjet_eta, eventweight)
				FillHists(hist_j2phi_truthbb, "nominal", yyHF_subleadjet_phi, eventweight)
				FillHists(hist_pT_yy_truthbb, "nominal", pT_yy, eventweight)
				FillHists(hist_pT_yyjj_truthbb, "nominal", pT_yyjj, eventweight)
				FillHists(hist_Dphi_yy_jj_truthbb, "nominal", Dphi_yy_jj, eventweight)

	print

	ROOT.xAOD.ClearTransientTrees()	


inputFile = sys.argv[1]
outputFile = sys.argv[2]
sampleType = sys.argv[3]
mcType = sys.argv[4]
systematicType = "Nominal"

print "input file: ", inputFile
print "output file: ", outputFile
print "sample: ", sampleType
print "mc campaign: ", mcType
print "sys type: ", systematicType

cutlfow_name = ""

outputFile += '_'+sampleType
if sampleType == "MGPy8_ttgamma_nonallhadronic_AF2":
	cutlfow_name = "CutFlow_MGPy8_ttgamma_nonallhadronic_noDalitz_weighted"
	cutflowPath = 'cutflows/'+systematicType+"/"+mcType+'.CutFlow_'+sampleType+'.root'
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

# cutflowPath = "~/xdata/yyhf/testingInputMakers/cutflows/Nominal/mc16e.CutFlow_Sherpa2_diphoton_myy_90_175_AF2NEWTESTINPUT.root"
# cutlfow_name = "CutFlow_Sherpa2_myy_90_175_noDalitz_weighted"

print "Using cutflow ", cutlfow_name, " from ",cutflowPath

print "Creating output " + outputFile + ".root for file " + inputFile
newFile = ROOT.TFile(outputFile+".root", "recreate")
newFile.cd()

hist_myy =  MakeHists("hist_myy","All Events;m_{#gamma#gamma} [GeV]",45, 50, 500)
hist_y1pt = MakeHists("hist_y1pt","All Events;p_{T}^{#gamma 1} [GeV]",59, 10, 600)
hist_y2pt = MakeHists("hist_y2pt","All Events;p_{T}^{#gamma 2} [GeV]",59, 10, 600)
hist_j1pt = MakeHists("hist_j1pt","All Events;p_{T}^{j1} [GeV]",59, 10, 600)
hist_j2pt = MakeHists("hist_j2pt","All Events;p_{T}^{j2} [GeV]",59, 10, 600)
hist_dR1 =  MakeHists("hist_dR1","All Events;#Delta R_{l, #gamma 1}",60, 0, 6)
hist_dR2 =  MakeHists("hist_dR2","All Events;#Delta R_{l, #gamma 2}",60, 0, 6)

hist_myy_yyHF =  MakeHists("hist_myy_yyHF","All yyHF Events;m_{#gamma#gamma} [GeV]",45, 50, 500)
hist_y1pt_yyHF = MakeHists("hist_y1pt_yyHF","All yyHF Events;p_{T}^{#gamma 1} [GeV]",59, 10, 600)
hist_y2pt_yyHF = MakeHists("hist_y2pt_yyHF","All yyHF Events;p_{T}^{#gamma 2} [GeV]",59, 10, 600)
hist_j1pt_yyHF = MakeHists("hist_j1pt_yyHF","All yyHF Events;p_{T}^{j1} [GeV]",59, 10, 600)
hist_j2pt_yyHF = MakeHists("hist_j2pt_yyHF","All yyHF Events;p_{T}^{j2} [GeV]",59, 10, 600)
hist_dR1_yyHF =  MakeHists("hist_dR1_yyHF","All yyHF Events;#Delta R_{l, #gamma 1}",60, 0, 6)
hist_dR2_yyHF =  MakeHists("hist_dR2_yyHF","All yyHF Events;#Delta R_{l, #gamma 2}",60, 0, 6)


hist_myy_OR  =  MakeHists("hist_myy_OR",  "Overlap Region;m_{#gamma#gamma} [GeV]",  45, 50, 500)
hist_y1pt_OR =  MakeHists("hist_y1pt_OR", "Overlap Region;p_{T}^{#gamma 1} [GeV]", 59, 10, 600)
hist_y2pt_OR =  MakeHists("hist_y2pt_OR", "Overlap Region;p_{T}^{#gamma 2} [GeV]", 59, 10, 600)
hist_j1pt_OR =  MakeHists("hist_j1pt_OR", "Overlap Region;p_{T}^{j1} [GeV]", 59, 10, 600)
hist_j2pt_OR =  MakeHists("hist_j2pt_OR", "Overlap Region;p_{T}^{j2} [GeV]", 59, 10, 600)
hist_dR1_OR  =  MakeHists("hist_dR1_OR",  "Overlap Region;#Delta R_{l, #gamma 1}",  60, 0, 6)
hist_dR2_OR  =  MakeHists("hist_dR2_OR",  "Overlap Region;#Delta R_{l, #gamma 2}",  60, 0, 6)

hist_myy_yyHF_OR  =  MakeHists("hist_myy_yyHF_OR",  "yyHF Overlap Region;m_{#gamma#gamma} [GeV]",  45, 50, 500)
hist_y1pt_yyHF_OR =  MakeHists("hist_y1pt_yyHF_OR", "yyHF Overlap Region;p_{T}^{#gamma 1} [GeV]", 59, 10, 600)
hist_y2pt_yyHF_OR =  MakeHists("hist_y2pt_yyHF_OR", "yyHF Overlap Region;p_{T}^{#gamma 2} [GeV]", 59, 10, 600)
hist_j1pt_yyHF_OR =  MakeHists("hist_j1pt_yyHF_OR", "yyHF Overlap Region;p_{T}^{j1} [GeV]", 59, 10, 600)
hist_j2pt_yyHF_OR =  MakeHists("hist_j2pt_yyHF_OR", "yyHF Overlap Region;p_{T}^{j2} [GeV]", 59, 10, 600)
hist_dR1_yyHF_OR  =  MakeHists("hist_dR1_yyHF_OR",  "yyHF Overlap Region;#Delta R_{l, #gamma 1}",  60, 0, 6)
hist_dR2_yyHF_OR  =  MakeHists("hist_dR2_yyHF_OR",  "yyHF Overlap Region;#Delta R_{l, #gamma 2}",  60, 0, 6)


hist_myy_notOR  =  MakeHists("hist_myy_notOR",  "Outside OR;m_{#gamma#gamma} [GeV]",  45, 50, 500)
hist_y1pt_notOR =  MakeHists("hist_y1pt_notOR", "Outside OR;p_{T}^{#gamma 1} [GeV]", 59, 10, 600)
hist_y2pt_notOR =  MakeHists("hist_y2pt_notOR", "Outside OR;p_{T}^{#gamma 2} [GeV]", 59, 10, 600)
hist_j1pt_notOR =  MakeHists("hist_j1pt_notOR", "Outside OR;p_{T}^{j1} [GeV]", 59, 10, 600)
hist_j2pt_notOR =  MakeHists("hist_j2pt_notOR", "Outside OR;p_{T}^{j2} [GeV]", 59, 10, 600)
hist_dR1_notOR  =  MakeHists("hist_dR1_notOR",  "Outside OR;#Delta R_{l, #gamma 1}",  60, 0, 6)
hist_dR2_notOR  =  MakeHists("hist_dR2_notOR",  "Outside OR;#Delta R_{l, #gamma 2}",  60, 0, 6)

hist_myy_yyHF_notOR  =  MakeHists("hist_myy_yyHF_notOR",  "yyHF outside OR;m_{#gamma#gamma} [GeV]",  45, 50, 500)
hist_y1pt_yyHF_notOR =  MakeHists("hist_y1pt_yyHF_notOR", "yyHF outside OR;p_{T}^{#gamma 1} [GeV]", 59, 10, 600)
hist_y2pt_yyHF_notOR =  MakeHists("hist_y2pt_yyHF_notOR", "yyHF outside OR;p_{T}^{#gamma 2} [GeV]", 59, 10, 600)
hist_j1pt_yyHF_notOR =  MakeHists("hist_j1pt_yyHF_notOR", "yyHF outside OR;p_{T}^{j1} [GeV]", 59, 10, 600)
hist_j2pt_yyHF_notOR =  MakeHists("hist_j2pt_yyHF_notOR", "yyHF outside OR;p_{T}^{j2} [GeV]", 59, 10, 600)
hist_dR1_yyHF_notOR  =  MakeHists("hist_dR1_yyHF_notOR",  "yyHF outside OR;#Delta R_{l, #gamma 1}",  60, 0, 6)
hist_dR2_yyHF_notOR  =  MakeHists("hist_dR2_yyHF_notOR",  "yyHF outside OR;#Delta R_{l, #gamma 2}",  60, 0, 6)


hist_mu                      =  MakeHists("hist_mu",  "pileup;#mu",  100, 0, 100)
hist_yyHF_met                =  MakeHists("hist_yyHF_met",  "yyHF_met;E_{T}^{miss}",  40, 0, 80)
hist_yyHF_Njet_central       =  MakeHists("hist_yyHF_Njet_central",  "hist_yyHF_Njet_central;N_{jets}^{central}",  10, 0, 10)
hist_yyHF_leadjet_btagbin    =  MakeHists("hist_yyHF_leadjet_btagbin",  "yyHF_leadjet_btagbin;Leading jet DL1r bin",  5, 0, 5)
hist_yyHF_subleadjet_btagbin =  MakeHists("hist_yyHF_subleadjet_btagbin",  "yyHF_subleadjet_btagbin;Subleading jet DL1r bin",  5, 0, 5)
hist_yyHF_leadjet_eta        =  MakeHists("hist_yyHF_leadjet_eta",  "yyHF_leadjet_eta;#eta_{j1}",  32, -3.2, 3.2)
hist_yyHF_subleadjet_eta     =  MakeHists("hist_yyHF_subleadjet_eta",  "yyHF_subleadjet_eta;#eta_{j2}",  26, -2.6, 2.6)
hist_yyHF_leadjet_m          =  MakeHists("hist_yyHF_leadjet_m",  "yyHF_leadjet_m;m_{j1} [GeV]",  15, 0, 30)
hist_yyHF_subleadjet_m       =  MakeHists("hist_yyHF_subleadjet_m",  "yyHF_subleadjet_m;m_{j2} [GeV]",  15, 0, 30)
hist_yyHF_leadjet_phi        =  MakeHists("hist_yyHF_leadjet_phi",  "yyHF_leadjet_phi;#phi_{j1}",  32, -3.2, 3.2)
hist_yyHF_subleadjet_phi     =  MakeHists("hist_yyHF_subleadjet_phi",  "yyHF_subleadjet_phi;#phi_{j1}",  32, -3.2, 3.2)
hist_yyHF_leadjet_pt         =  MakeHists("hist_yyHF_leadjet_pt",  "yyHF_leadjet_pt;p_{T}^{j1}",  25, 0, 250)
hist_yyHF_subleadjet_pt      =  MakeHists("hist_yyHF_subleadjet_pt",  "yyHF_subleadjet_pt;p_{T}^{j2}",  25, 0, 250)
hist_yyHF_leadjet_truthlabel =  MakeHists("hist_yyHF_leadjet_truthlabel",  "yyHF_leadjet_truthlabel;Leading jet truth label",  6, 0, 6)
hist_yyHF_subleadjet_truthlabel =  MakeHists("hist_yyHF_subleadjet_truthlabel",  "yyHF_subleadjet_truthlabel;Subleading jet truth label",  6, 0, 6)


## Calculate variables below ##
hist_mjj =  MakeHists("hist_mjj",  "mjj;m_{jj}",  25, 0, 500)
hist_myyj =  MakeHists("hist_myyj",  "myyj;m_{#gamma#gamma j}",  50, 0, 1000)
hist_myyjj =  MakeHists("hist_myyjj",  "myyjj;m_{#gamma#gamma jj}",  50, 0, 1000)
hist_pT_jj =  MakeHists("hist_pT_jj",  "pT_jj;p_{T}^{jj}",  30, 0, 300)
hist_pT_yy =  MakeHists("hist_pT_yy",  "pT_yy;p_{T}^{#gamma#gamma}",  30, 0, 300)
hist_pT_yyj =  MakeHists("hist_pT_yyj",  "pT_yyj;p_{T}^{#gamma#gamma j}",  30, 0, 300)
hist_pT_yyjj =  MakeHists("hist_pT_yyjj",  "pT_yyjj;p_{T}^{#gamma#gamma jj}",  30, 0, 300)
hist_DR_y_y =  MakeHists("hist_DR_y_y",  "hist_DR_y_y;#Delta R(#gamma#gamma)",  120, 0, 6)
hist_Deta_j_j =  MakeHists("hist_Deta_j_j",  "Deta_j_j;#Delta #eta(jj)",  100, 0, 10)
hist_Dphi_j_j =  MakeHists("hist_Dphi_j_j",  "Dphi_j_j;#Delta #phi(jj)",  32, 0, 3.2)
hist_Dphi_y_y =  MakeHists("hist_Dphi_y_y",  "Dphi_y_y;#Delta #phi(#gamma#gamma)",  32, 0, 3.2)
hist_Dphi_yy_jj =  MakeHists("hist_Dphi_yy_jj",  "Dphi_yy_jj;#Delta #phi(#gamma#gamma jj)",  32, 0, 3.2)

hist_pT_yy_truthbb =  MakeHists("hist_pT_yy_truthbb",  "All bb events;p_{T}^{#gamma#gamma}",  30, 0, 300)
hist_pT_yyjj_truthbb =  MakeHists("hist_pT_yyjj_truthbb",  "All bb events;p_{T}^{#gamma#gamma bb}",  30, 0, 300)
hist_Dphi_yy_jj_truthbb =  MakeHists("hist_Dphi_yy_jj_truthbb",  "All bb events;#Delta #phi(#gamma#gamma bb)",  32, 0, 3.2)
hist_j1pt_truthbb = MakeHists("hist_j1pt_truthbb","All bb Events;Leading b-jet p_{T} [GeV]", 59, 10, 600)
hist_j2pt_truthbb = MakeHists("hist_j2pt_truthbb","All bb Events;Subleading b-jet p_{T} [GeV]", 59, 10, 600)
hist_j1eta_truthbb = MakeHists("hist_j1eta_truthbb","All bb Events;Leading b-jet #eta", 25, -2.5, 2.5)
hist_j2eta_truthbb = MakeHists("hist_j2eta_truthbb","All bbEvents;Subleading b-jet #eta", 25, -2.5, 2.5)
hist_j1phi_truthbb = MakeHists("hist_j1phi_truthbb","All bb Events;Leading b-jet #phi", 32, -3.2, 3.2)
hist_j2phi_truthbb = MakeHists("hist_j2phi_truthbb","All bb Events;Subleading b-jet #phi", 32, -3.2, 3.2)


# hist_yyHF_nelectron
# hist_yyHF_nmuon

# hist_yyHFj_weight
# hist_yyHFjj_weight

makehistograms(inputFile, cutflowPath)

newFile.Write()
newFile.Close()
