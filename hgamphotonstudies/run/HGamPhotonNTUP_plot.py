import ROOT 
import sys
import os
from math import sqrt
from AtlasStyle import *
ROOT.gROOT.LoadMacro("AtlasStyle.C") 

ROOT.gStyle.SetOptStat(0)

inputDataPath_full = "/bdata/bstamas/updatePhotonStudies/hgamphotonstudies/run/mergeddata/total_data.root"
inputMCPath_full = "/bdata/bstamas/updatePhotonStudies/hgamphotonstudies/run/mergedmc/total_mc_highmass.root"
inputBackgroundPath_full = "/bdata/bstamas/updatePhotonStudies/hgamphotonstudies/run/mergeddata/total_data.root"

inputDataPath_1516 = "/bdata/bstamas/updatePhotonStudies/hgamphotonstudies/run/1516data/1516_data.root"
inputMCPath_1516 = "/bdata/bstamas/updatePhotonStudies/hgamphotonstudies/run/mc16a/merged_mc16a.root"
inputBackgroundPath_1516 = "/bdata/bstamas/updatePhotonStudies/hgamphotonstudies/run/1516data/1516_data.root"

inputDataPath_17 = "/bdata/bstamas/updatePhotonStudies/hgamphotonstudies/run/data17/hist-data17.root"
inputMCPath_17 = "/bdata/bstamas/updatePhotonStudies/hgamphotonstudies/run/mc16d/merged_mc16d.root"
inputBackgroundPath_17 = "/bdata/bstamas/updatePhotonStudies/hgamphotonstudies/run/data17/hist-data17.root"

inputDataPath_18 = "/bdata/bstamas/updatePhotonStudies/hgamphotonstudies/run/data18/hist-data18.root"
inputMCPath_18 = "/bdata/bstamas/updatePhotonStudies/hgamphotonstudies/run/mc16e/merged_mc16e.root"
inputBackgroundPath_18 = "/bdata/bstamas/updatePhotonStudies/hgamphotonstudies/run/data18/hist-data18.root"


inputDataFile_full = ROOT.TFile(inputDataPath_full)
inputMCFile_full = ROOT.TFile(inputMCPath_full)
inputBackgroundFile_full = ROOT.TFile(inputBackgroundPath_full)

inputDataFile_1516 = ROOT.TFile(inputDataPath_1516)
inputMCFile_1516 = ROOT.TFile(inputMCPath_1516)
inputBackgroundFile_1516 = ROOT.TFile(inputBackgroundPath_1516)

inputDataFile_17 = ROOT.TFile(inputDataPath_17)
inputMCFile_17 = ROOT.TFile(inputMCPath_17)
inputBackgroundFile_17 = ROOT.TFile(inputBackgroundPath_17)

inputDataFile_18 = ROOT.TFile(inputDataPath_18)
inputMCFile_18 = ROOT.TFile(inputMCPath_18)
inputBackgroundFile_18 = ROOT.TFile(inputBackgroundPath_18)


def normalize(hdata, hmc, hjj, hjj_noweight, hyj, hyj_noweight):
	# print "normalize"
	data_norm = hdata.Integral()
	mc_norm = hmc.Integral()
	yj_norm = hyj_noweight.Integral()
	jj_norm = hjj_noweight.Integral()

	hdata.SetMarkerStyle(20)

	hmc.SetFillColor(6)
	hmc.SetLineColor(6)

	hjj.SetLineWidth(2)
	hyj.SetLineWidth(2)

	hyj.SetLineColor(7)
	hyj.SetFillColor(7)

	hjj.SetLineColor(3)
	hjj.SetFillColor(3)

	bkgd_norm = mc_norm

	if yj_norm != 0:
		hyj.Scale((mc_norm)/(yj_norm))
		bkgd_norm += hyj.Integral()
	else:
		print "No events in "+str(hyj.GetName())

	if jj_norm != 0:
		hjj.Scale((mc_norm)/(jj_norm))
		bkgd_norm += hjj.Integral()
	else:
		print "No events in "+str(hjj.GetName())

	hmc.Scale(data_norm/bkgd_norm)
	hyj.Scale(data_norm/bkgd_norm)
	hjj.Scale(data_norm/bkgd_norm)


def ptj1_ptj1_purities(mu, data):
	if data == "full":
		inputDataFile = inputDataFile_full
		inputMCFile = inputMCFile_full
		inputBackgroundFile = inputBackgroundFile_full
	elif data == "1516":
		inputDataFile = inputDataFile_1516
		inputMCFile = inputMCFile_1516
		inputBackgroundFile = inputBackgroundFile_1516
	elif data == "17":
		inputDataFile = inputDataFile_17
		inputMCFile = inputMCFile_17
		inputBackgroundFile = inputBackgroundFile_17
	elif data == "18":
		inputDataFile = inputDataFile_18
		inputMCFile = inputMCFile_18
		inputBackgroundFile = inputBackgroundFile_18

	if mu == 10:
		hist_yy_data_j1_pt = inputDataFile.Get("hist_j130_pt_010");
		hist_yy_mc_j1_pt = inputMCFile.Get("hist_j130_pt_010");
		hist_yy_pflowj1_pt = inputBackgroundFile.Get("hist_yy_pflowj1_pt_010");
		hist_jj_pflowj1_pt = inputBackgroundFile.Get("hist_jj_pflowj1_pt_010_ptj1_purityweight");
		hist_yj_pflowj1_pt = inputBackgroundFile.Get("hist_yj_pflowj1_pt_010_ptj1_purityweight");
		hist_jy_pflowj1_pt = inputBackgroundFile.Get("hist_jy_pflowj1_pt_010_ptj1_purityweight");
		hist_jj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jj_pflowj1_pt_010");
		hist_yj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_yj_pflowj1_pt_010");
		hist_jy_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jy_pflowj1_pt_010");
	elif mu == 1020:
		hist_yy_data_j1_pt = inputDataFile.Get("hist_j130_pt_1020");
		hist_yy_mc_j1_pt = inputMCFile.Get("hist_j130_pt_1020");
		hist_yy_pflowj1_pt = inputBackgroundFile.Get("hist_yy_pflowj1_pt_1020");
		hist_jj_pflowj1_pt = inputBackgroundFile.Get("hist_jj_pflowj1_pt_1020_ptj1_purityweight");
		hist_yj_pflowj1_pt = inputBackgroundFile.Get("hist_yj_pflowj1_pt_1020_ptj1_purityweight");
		hist_jy_pflowj1_pt = inputBackgroundFile.Get("hist_jy_pflowj1_pt_1020_ptj1_purityweight");
		hist_jj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jj_pflowj1_pt_1020");
		hist_yj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_yj_pflowj1_pt_1020");
		hist_jy_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jy_pflowj1_pt_1020");
	elif mu == 2030:
		hist_yy_data_j1_pt = inputDataFile.Get("hist_j130_pt_2030");
		hist_yy_mc_j1_pt = inputMCFile.Get("hist_j130_pt_2030");
		hist_yy_pflowj1_pt = inputBackgroundFile.Get("hist_yy_pflowj1_pt_2030");
		hist_jj_pflowj1_pt = inputBackgroundFile.Get("hist_jj_pflowj1_pt_2030_ptj1_purityweight");
		hist_yj_pflowj1_pt = inputBackgroundFile.Get("hist_yj_pflowj1_pt_2030_ptj1_purityweight");
		hist_jy_pflowj1_pt = inputBackgroundFile.Get("hist_jy_pflowj1_pt_2030_ptj1_purityweight");
		hist_jj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jj_pflowj1_pt_2030");
		hist_yj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_yj_pflowj1_pt_2030");
		hist_jy_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jy_pflowj1_pt_2030");
	elif mu == 3040:
		hist_yy_data_j1_pt = inputDataFile.Get("hist_j130_pt_3040");
		hist_yy_mc_j1_pt = inputMCFile.Get("hist_j130_pt_3040");
		hist_yy_pflowj1_pt = inputBackgroundFile.Get("hist_yy_pflowj1_pt_3040");
		hist_jj_pflowj1_pt = inputBackgroundFile.Get("hist_jj_pflowj1_pt_3040_ptj1_purityweight");
		hist_yj_pflowj1_pt = inputBackgroundFile.Get("hist_yj_pflowj1_pt_3040_ptj1_purityweight");
		hist_jy_pflowj1_pt = inputBackgroundFile.Get("hist_jy_pflowj1_pt_3040_ptj1_purityweight");
		hist_jj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jj_pflowj1_pt_3040");
		hist_yj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_yj_pflowj1_pt_3040");
		hist_jy_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jy_pflowj1_pt_3040");
	elif mu == 4060:
		hist_yy_data_j1_pt = inputDataFile.Get("hist_j130_pt_4060");
		hist_yy_mc_j1_pt = inputMCFile.Get("hist_j130_pt_4060");
		hist_yy_pflowj1_pt = inputBackgroundFile.Get("hist_yy_pflowj1_pt_4060");
		hist_jj_pflowj1_pt = inputBackgroundFile.Get("hist_jj_pflowj1_pt_4060_ptj1_purityweight");
		hist_yj_pflowj1_pt = inputBackgroundFile.Get("hist_yj_pflowj1_pt_4060_ptj1_purityweight");
		hist_jy_pflowj1_pt = inputBackgroundFile.Get("hist_jy_pflowj1_pt_4060_ptj1_purityweight");
		hist_jj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jj_pflowj1_pt_4060");
		hist_yj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_yj_pflowj1_pt_4060");
		hist_jy_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jy_pflowj1_pt_4060");

	histData_j130_pt = hist_yy_data_j1_pt.Clone("histData_j130_pt")

	hist_yj_pflowj1_pt.Add(hist_jy_pflowj1_pt)
	hist_yj_pflowj1_pt_noweight.Add(hist_jy_pflowj1_pt_noweight)

	pflowj1_pt = [hist_yy_mc_j1_pt, hist_yj_pflowj1_pt, hist_jj_pflowj1_pt]
	# pflowj1_pt = [hist_yj_pflowj1_pt, hist_jj_pflowj1_pt]
	data_norm = hist_yy_data_j1_pt.Integral()
	mc_norm = hist_yy_mc_j1_pt.Integral()
	yj_norm = hist_yj_pflowj1_pt_noweight.Integral()
	jj_norm = hist_jj_pflowj1_pt_noweight.Integral()
	
	hist_pflowj1_pt = ROOT.THStack("hist_pflowj1_pt", "")

	normalize(hist_yy_data_j1_pt, hist_yy_mc_j1_pt, hist_jj_pflowj1_pt, hist_jj_pflowj1_pt_noweight, hist_yj_pflowj1_pt, hist_yj_pflowj1_pt_noweight)

	hist_pflowj1_pt.Add(hist_yy_mc_j1_pt, "HIST")
	hist_pflowj1_pt.Add(hist_yj_pflowj1_pt, "HIST")
	hist_pflowj1_pt.Add(hist_jj_pflowj1_pt, "HIST")
	ROOT.gROOT.SetBatch(True)

	# hist_pflowj1_pt.Add(hist_yy_data_j1_pt)
	j1_pt_can = ROOT.TCanvas("j1_pt_can", "")
	pad1 = ROOT.TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
	pad1.SetBottomMargin(0.15)
	pad1.Draw()
	pad1.cd()
	maximum_data = hist_yy_data_j1_pt.GetMaximum() * 1.10; maximum_mc = hist_pflowj1_pt.GetMaximum() * 1.10
	if maximum_mc > maximum_data:
		maximum = maximum_mc
	elif maximum_data > maximum_mc:
		maximum = maximum_data
	hist_pflowj1_pt.Draw()
	hist_pflowj1_pt.SetMaximum(maximum)
	hist_yy_data_j1_pt.Draw("ep same")
	# hist_yy_mc_j1_pt.Draw("same")
	hist_pflowj1_pt.GetXaxis().SetTitle("Leading jet p_{T} [GeV]"); hist_pflowj1_pt.GetYaxis().SetTitle("Events"); hist_yy_data_j1_pt.SetTitle("")
	legend =  ROOT.TLegend(0.6,0.7,0.9,0.9);
	if data == "full":
		lumi = 138.9
		save_name = "_full.pdf"
		legend.AddEntry(hist_yy_data_j1_pt,"2015-2018 data","PL");
		legend.AddEntry(hist_jj_pflowj1_pt,"jet-jet (data driven)  %.2f %%" %(hist_jj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_pflowj1_pt,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_j1_pt,"#gamma#gamma (MC16)  %.2f %%" %(hist_yy_mc_j1_pt.Integral() * 100 / data_norm),"PL");
	elif data == "1516":
		lumi = 36.2
		save_name = "_1516.pdf"
		legend.AddEntry(hist_yy_data_j1_pt,"2015-2016 data","PL");
		legend.AddEntry(hist_jj_pflowj1_pt,"jet-jet (data driven)  %.2f %%" %(hist_jj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_pflowj1_pt,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_j1_pt,"#gamma#gamma (MC16a)  %.2f %%" %(hist_yy_mc_j1_pt.Integral() * 100 / data_norm),"PL");
	elif data == "17":
		lumi = 44.3
		save_name = "_17.pdf"
		legend.AddEntry(hist_yy_data_j1_pt,"2017 data","PL");
		legend.AddEntry(hist_jj_pflowj1_pt,"jet-jet (data driven)  %.2f %%" %(hist_jj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_pflowj1_pt,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_j1_pt,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_j1_pt.Integral() * 100 / data_norm),"PL");
	elif data == "18":
		lumi = 58.4
		save_name = "_18.pdf"
		legend.AddEntry(hist_yy_data_j1_pt,"2018 data","PL");
		legend.AddEntry(hist_jj_pflowj1_pt,"jet-jet (data driven)  %.2f %%" %(hist_jj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_pflowj1_pt,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_j1_pt,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_j1_pt.Integral() * 100 / data_norm),"PL");
	legend.Draw();
	if mu == 10:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "0 < #mu < 10")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
	elif mu == 1020:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "10 < #mu < 20")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
	elif mu == 2030:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "20 < #mu < 30")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
	elif mu == 3040:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "30 < #mu < 40")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
	elif mu == 4060:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "40 < #mu < 60")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")

	j1_pt_can.cd()
	pad2 = ROOT.TPad("pad2", "pad2", 0, 0, 1, 0.35)
	pad2.SetTopMargin(0.1)
	pad2.SetBottomMargin(0.25)
	pad2.Draw()
	pad2.SetTicks(0,1)
	pad2.cd()

	histData_j130_pt.Sumw2(); histData_j130_pt.SetStats(0); histData_j130_pt.Divide(hist_pflowj1_pt.GetStack().Last()); histData_j130_pt.SetTitle("")
	histData_j130_pt.GetYaxis().SetTitle("Data/MC"); histData_j130_pt.SetLineColor(1)
	histData_j130_pt.GetXaxis().SetLabelSize(0.1); histData_j130_pt.GetXaxis().SetTitleSize(0.1); histData_j130_pt.GetXaxis().SetTitle("Leading jet p_{T} [GeV]")
	histData_j130_pt.GetYaxis().SetLabelSize(0.1); histData_j130_pt.GetYaxis().SetTitleSize(0.1); histData_j130_pt.GetYaxis().SetTitleOffset(0.4)
	histData_j130_pt.SetMinimum(0.5); histData_j130_pt.SetMaximum(2)
	histData_j130_pt.Draw("ep")

	myLine = ROOT.TLine(0,1,450,1); myLine.SetLineStyle(2); myLine.Draw()

	j1_pt_can.cd()
	j1_pt_can.Update()

	if jj_norm != 0 and yj_norm != 0:
		if mu == 10:
			j1_pt_can.SaveAs("leading_jet_pt_ptj1_purities_010"+save_name)
		elif mu == 1020:
			j1_pt_can.SaveAs("leading_jet_pt_ptj1_purities_1020"+save_name)
		elif mu == 2030:
			j1_pt_can.SaveAs("leading_jet_pt_ptj1_purities_2030"+save_name)
		elif mu == 3040:
			j1_pt_can.SaveAs("leading_jet_pt_ptj1_purities_3040"+save_name)
		elif mu == 4060:
			j1_pt_can.SaveAs("leading_jet_pt_ptj1_purities_4060"+save_name)

	j1_pt_can.Close()

def ptj1_ptj1_purities_central(mu, data):
	if data == "full":
		inputDataFile = inputDataFile_full
		inputMCFile = inputMCFile_full
		inputBackgroundFile = inputBackgroundFile_full
	elif data == "1516":
		inputDataFile = inputDataFile_1516
		inputMCFile = inputMCFile_1516
		inputBackgroundFile = inputBackgroundFile_1516
	elif data == "17":
		inputDataFile = inputDataFile_17
		inputMCFile = inputMCFile_17
		inputBackgroundFile = inputBackgroundFile_17
	elif data == "18":
		inputDataFile = inputDataFile_18
		inputMCFile = inputMCFile_18
		inputBackgroundFile = inputBackgroundFile_18
	if mu == 10:
		hist_yy_data_j1_pt = inputDataFile.Get("hist_j130_pt_010_central");
		hist_yy_mc_j1_pt = inputMCFile.Get("hist_j130_pt_010_central");
		hist_yy_pflowj1_pt = inputBackgroundFile.Get("hist_yy_pflowj1_pt_010_central");
		hist_jj_pflowj1_pt = inputBackgroundFile.Get("hist_jj_pflowj1_pt_010_ptj1_purityweight_central");
		hist_yj_pflowj1_pt = inputBackgroundFile.Get("hist_yj_pflowj1_pt_010_ptj1_purityweight_central");
		hist_jy_pflowj1_pt = inputBackgroundFile.Get("hist_jy_pflowj1_pt_010_ptj1_purityweight_central");
		hist_jj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jj_pflowj1_pt_010_central");
		hist_yj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_yj_pflowj1_pt_010_central");
		hist_jy_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jy_pflowj1_pt_010_central");
	elif mu == 1020:
		hist_yy_data_j1_pt = inputDataFile.Get("hist_j130_pt_1020_central");
		hist_yy_mc_j1_pt = inputMCFile.Get("hist_j130_pt_1020_central");
		hist_yy_pflowj1_pt = inputBackgroundFile.Get("hist_yy_pflowj1_pt_1020_central");
		hist_jj_pflowj1_pt = inputBackgroundFile.Get("hist_jj_pflowj1_pt_1020_ptj1_purityweight_central");
		hist_yj_pflowj1_pt = inputBackgroundFile.Get("hist_yj_pflowj1_pt_1020_ptj1_purityweight_central");
		hist_jy_pflowj1_pt = inputBackgroundFile.Get("hist_jy_pflowj1_pt_1020_ptj1_purityweight_central");
		hist_jj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jj_pflowj1_pt_1020_central");
		hist_yj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_yj_pflowj1_pt_1020_central");
		hist_jy_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jy_pflowj1_pt_1020_central");
	elif mu == 2030:
		hist_yy_data_j1_pt = inputDataFile.Get("hist_j130_pt_2030_central");
		hist_yy_mc_j1_pt = inputMCFile.Get("hist_j130_pt_2030_central");
		hist_yy_pflowj1_pt = inputBackgroundFile.Get("hist_yy_pflowj1_pt_2030_central");
		hist_jj_pflowj1_pt = inputBackgroundFile.Get("hist_jj_pflowj1_pt_2030_ptj1_purityweight_central");
		hist_yj_pflowj1_pt = inputBackgroundFile.Get("hist_yj_pflowj1_pt_2030_ptj1_purityweight_central");
		hist_jy_pflowj1_pt = inputBackgroundFile.Get("hist_jy_pflowj1_pt_2030_ptj1_purityweight_central");
		hist_jj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jj_pflowj1_pt_2030_central");
		hist_yj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_yj_pflowj1_pt_2030_central");
		hist_jy_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jy_pflowj1_pt_2030_central");
	elif mu == 3040:
		hist_yy_data_j1_pt = inputDataFile.Get("hist_j130_pt_3040_central");
		hist_yy_mc_j1_pt = inputMCFile.Get("hist_j130_pt_3040_central");
		hist_yy_pflowj1_pt = inputBackgroundFile.Get("hist_yy_pflowj1_pt_3040_central");
		hist_jj_pflowj1_pt = inputBackgroundFile.Get("hist_jj_pflowj1_pt_3040_ptj1_purityweight_central");
		hist_yj_pflowj1_pt = inputBackgroundFile.Get("hist_yj_pflowj1_pt_3040_ptj1_purityweight_central");
		hist_jy_pflowj1_pt = inputBackgroundFile.Get("hist_jy_pflowj1_pt_3040_ptj1_purityweight_central");
		hist_jj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jj_pflowj1_pt_3040_central");
		hist_yj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_yj_pflowj1_pt_3040_central");
		hist_jy_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jy_pflowj1_pt_3040_central");
	elif mu == 4060:
		hist_yy_data_j1_pt = inputDataFile.Get("hist_j130_pt_4060_central");
		hist_yy_mc_j1_pt = inputMCFile.Get("hist_j130_pt_4060_central");
		hist_yy_pflowj1_pt = inputBackgroundFile.Get("hist_yy_pflowj1_pt_4060_central");
		hist_jj_pflowj1_pt = inputBackgroundFile.Get("hist_jj_pflowj1_pt_4060_ptj1_purityweight_central");
		hist_yj_pflowj1_pt = inputBackgroundFile.Get("hist_yj_pflowj1_pt_4060_ptj1_purityweight_central");
		hist_jy_pflowj1_pt = inputBackgroundFile.Get("hist_jy_pflowj1_pt_4060_ptj1_purityweight_central");
		hist_jj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jj_pflowj1_pt_4060_central");
		hist_yj_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_yj_pflowj1_pt_4060_central");
		hist_jy_pflowj1_pt_noweight = inputBackgroundFile.Get("hist_jy_pflowj1_pt_4060_central");

	histData_j130_pt = hist_yy_data_j1_pt.Clone("histData_j130_pt")

	hist_yj_pflowj1_pt.Add(hist_jy_pflowj1_pt)
	hist_yj_pflowj1_pt_noweight.Add(hist_jy_pflowj1_pt_noweight)

	pflowj1_pt = [hist_yy_mc_j1_pt, hist_yj_pflowj1_pt, hist_jj_pflowj1_pt]
	# pflowj1_pt = [hist_yj_pflowj1_pt, hist_jj_pflowj1_pt]

	data_norm = hist_yy_data_j1_pt.Integral()
	mc_norm = hist_yy_mc_j1_pt.Integral()
	yj_norm = hist_yj_pflowj1_pt_noweight.Integral()
	jj_norm = hist_jj_pflowj1_pt_noweight.Integral()
	# print jj_norm
	# print hist_jj_pflowj1_pt_noweight.GetName()
	
	hist_pflowj1_pt = ROOT.THStack("hist_pflowj1_pt", "")
	
	normalize(hist_yy_data_j1_pt, hist_yy_mc_j1_pt, hist_jj_pflowj1_pt, hist_jj_pflowj1_pt_noweight, hist_yj_pflowj1_pt, hist_yj_pflowj1_pt_noweight)

	hist_pflowj1_pt.Add(hist_yy_mc_j1_pt, "HIST")
	hist_pflowj1_pt.Add(hist_yj_pflowj1_pt, "HIST")
	hist_pflowj1_pt.Add(hist_jj_pflowj1_pt, "HIST")
	ROOT.gROOT.SetBatch(True)

	# hist_pflowj1_pt.Add(hist_yy_data_j1_pt)
	j1_pt_can = ROOT.TCanvas("j1_pt_can", "")
	pad1 = ROOT.TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
	pad1.SetBottomMargin(0.15)
	pad1.Draw()
	pad1.cd()
	maximum_data = hist_yy_data_j1_pt.GetMaximum() * 1.10; maximum_mc = hist_pflowj1_pt.GetMaximum() * 1.10
	if maximum_mc > maximum_data:
		maximum = maximum_mc
	elif maximum_data > maximum_mc:
		maximum = maximum_data
	hist_pflowj1_pt.Draw()
	hist_pflowj1_pt.SetMaximum(maximum)
	hist_yy_data_j1_pt.Draw("ep same")
	# hist_yy_mc_j1_pt.Draw("same")
	hist_pflowj1_pt.GetXaxis().SetTitle("Leading jet p_{T} [GeV]"); hist_pflowj1_pt.GetYaxis().SetTitle("Events"); hist_yy_data_j1_pt.SetTitle("")
	legend =  ROOT.TLegend(0.6,0.7,0.9,0.9);
	if data == "full":
		lumi = 138.9
		save_name = "_full.pdf"
		legend.AddEntry(hist_yy_data_j1_pt,"2015-2018 data","PL");
		legend.AddEntry(hist_jj_pflowj1_pt,"jet-jet (data driven)  %.2f %%" %(hist_jj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_pflowj1_pt,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_j1_pt,"#gamma#gamma (MC16)  %.2f %%" %(hist_yy_mc_j1_pt.Integral() * 100 / data_norm),"PL");
	elif data == "1516":
		lumi = 36.2
		save_name = "_1516.pdf"
		legend.AddEntry(hist_yy_data_j1_pt,"2015-2016 data","PL");
		legend.AddEntry(hist_jj_pflowj1_pt,"jet-jet (data driven)  %.2f %%" %(hist_jj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_pflowj1_pt,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_j1_pt,"#gamma#gamma (MC16a)  %.2f %%" %(hist_yy_mc_j1_pt.Integral() * 100 / data_norm),"PL");
	elif data == "17":
		lumi = 44.3
		save_name = "_17.pdf"
		legend.AddEntry(hist_yy_data_j1_pt,"2017 data","PL");
		legend.AddEntry(hist_jj_pflowj1_pt,"jet-jet (data driven)  %.2f %%" %(hist_jj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_pflowj1_pt,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_j1_pt,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_j1_pt.Integral() * 100 / data_norm),"PL");
	elif data == "18":
		lumi = 58.4
		save_name = "_18.pdf"
		legend.AddEntry(hist_yy_data_j1_pt,"2018 data","PL");
		legend.AddEntry(hist_jj_pflowj1_pt,"jet-jet (data driven)  %.2f %%" %(hist_jj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_pflowj1_pt,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_pflowj1_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_j1_pt,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_j1_pt.Integral() * 100 / data_norm),"PL");
	legend.Draw();
	if mu == 10:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "0 < #mu < 10")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
		myLabel(0.61, 0.40, 1, "jet eta < 2.5")
	elif mu == 1020:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "10 < #mu < 20")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
		myLabel(0.61, 0.40, 1, "jet eta < 2.5")

	elif mu == 2030:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "20 < #mu < 30")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
		myLabel(0.61, 0.40, 1, "jet eta < 2.5")

	elif mu == 3040:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "30 < #mu < 40")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
		myLabel(0.61, 0.40, 1, "jet eta < 2.5")

	elif mu == 4060:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "40 < #mu < 60")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
		myLabel(0.61, 0.40, 1, "jet eta < 2.5")


	j1_pt_can.cd()
	pad2 = ROOT.TPad("pad2", "pad2", 0, 0, 1, 0.35)
	pad2.SetTopMargin(0.1)
	pad2.SetBottomMargin(0.25)
	pad2.Draw()
	pad2.SetTicks(0,1)
	pad2.cd()

	histData_j130_pt.Sumw2(); histData_j130_pt.SetStats(0); histData_j130_pt.Divide(hist_pflowj1_pt.GetStack().Last()); histData_j130_pt.SetTitle("")
	histData_j130_pt.GetYaxis().SetTitle("Data/MC"); histData_j130_pt.SetLineColor(1)
	histData_j130_pt.GetXaxis().SetLabelSize(0.1); histData_j130_pt.GetXaxis().SetTitleSize(0.1); histData_j130_pt.GetXaxis().SetTitle("Leading jet p_{T} [GeV]")
	histData_j130_pt.GetYaxis().SetLabelSize(0.1); histData_j130_pt.GetYaxis().SetTitleSize(0.1); histData_j130_pt.GetYaxis().SetTitleOffset(0.4)
	histData_j130_pt.SetMinimum(0.5); histData_j130_pt.SetMaximum(2)
	histData_j130_pt.Draw("ep")

	myLine = ROOT.TLine(0,1,450,1); myLine.SetLineStyle(2); myLine.Draw()

	j1_pt_can.cd()
	j1_pt_can.Update()

	if jj_norm != 0 and yj_norm != 0:
		if mu == 10:
			j1_pt_can.SaveAs("leading_jet_pt_ptj1_purities_central_010"+save_name)
		elif mu == 1020:
			j1_pt_can.SaveAs("leading_jet_pt_ptj1_purities_central_1020"+save_name)
		elif mu == 2030:
			j1_pt_can.SaveAs("leading_jet_pt_ptj1_purities_central_2030"+save_name)
		elif mu == 3040:
			j1_pt_can.SaveAs("leading_jet_pt_ptj1_purities_central_3040"+save_name)
		elif mu == 4060:
			j1_pt_can.SaveAs("leading_jet_pt_ptj1_purities_central_4060"+save_name)

	j1_pt_can.Close()

def myy_myy_purities(mu, data):
	if data == "full":
		inputDataFile = inputDataFile_full
		inputMCFile = inputMCFile_full
		inputBackgroundFile = inputBackgroundFile_full
	elif data == "1516":
		inputDataFile = inputDataFile_1516
		inputMCFile = inputMCFile_1516
		inputBackgroundFile = inputBackgroundFile_1516
	elif data == "17":
		inputDataFile = inputDataFile_17
		inputMCFile = inputMCFile_17
		inputBackgroundFile = inputBackgroundFile_17
	elif data == "18":
		inputDataFile = inputDataFile_18
		inputMCFile = inputMCFile_18
		inputBackgroundFile = inputBackgroundFile_18

	if mu == 10:
		hist_yy_data_myy = inputDataFile.Get("hist_myy_010");
		hist_yy_mc_myy = inputMCFile.Get("hist_myy_010");
		hist_yy_myy = inputBackgroundFile.Get("hist_yy_myy_010");
		hist_jj_myy = inputBackgroundFile.Get("hist_jj_myy_010_myy_purityweight");
		hist_yj_myy = inputBackgroundFile.Get("hist_yj_myy_010_myy_purityweight");
		hist_jy_myy = inputBackgroundFile.Get("hist_jy_myy_010_myy_purityweight");
		hist_jj_myy_noweight = inputBackgroundFile.Get("hist_jj_myy_010");
		hist_yj_myy_noweight = inputBackgroundFile.Get("hist_yj_myy_010");
		hist_jy_myy_noweight = inputBackgroundFile.Get("hist_jy_myy_010");
	elif mu == 1020:
		hist_yy_data_myy = inputDataFile.Get("hist_myy_1020");
		hist_yy_mc_myy = inputMCFile.Get("hist_myy_1020");
		hist_yy_myy = inputBackgroundFile.Get("hist_yy_myy_1020");
		hist_jj_myy = inputBackgroundFile.Get("hist_jj_myy_1020_myy_purityweight");
		hist_yj_myy = inputBackgroundFile.Get("hist_yj_myy_1020_myy_purityweight");
		hist_jy_myy = inputBackgroundFile.Get("hist_jy_myy_1020_myy_purityweight");
		hist_jj_myy_noweight = inputBackgroundFile.Get("hist_jj_myy_1020");
		hist_yj_myy_noweight = inputBackgroundFile.Get("hist_yj_myy_1020");
		hist_jy_myy_noweight = inputBackgroundFile.Get("hist_jy_myy_1020");
	elif mu == 2030:
		hist_yy_data_myy = inputDataFile.Get("hist_myy_2030");
		hist_yy_mc_myy = inputMCFile.Get("hist_myy_2030");
		hist_yy_myy = inputBackgroundFile.Get("hist_yy_myy_2030");
		hist_jj_myy = inputBackgroundFile.Get("hist_jj_myy_2030_myy_purityweight");
		hist_yj_myy = inputBackgroundFile.Get("hist_yj_myy_2030_myy_purityweight");
		hist_jy_myy = inputBackgroundFile.Get("hist_jy_myy_2030_myy_purityweight");
		hist_jj_myy_noweight = inputBackgroundFile.Get("hist_jj_myy_2030");
		hist_yj_myy_noweight = inputBackgroundFile.Get("hist_yj_myy_2030");
		hist_jy_myy_noweight = inputBackgroundFile.Get("hist_jy_myy_2030");
	elif mu == 3040:
		hist_yy_data_myy = inputDataFile.Get("hist_myy_3040");
		hist_yy_mc_myy = inputMCFile.Get("hist_myy_3040");
		hist_yy_myy = inputBackgroundFile.Get("hist_yy_myy_3040");
		hist_jj_myy = inputBackgroundFile.Get("hist_jj_myy_3040_myy_purityweight");
		hist_yj_myy = inputBackgroundFile.Get("hist_yj_myy_3040_myy_purityweight");
		hist_jy_myy = inputBackgroundFile.Get("hist_jy_myy_3040_myy_purityweight");
		hist_jj_myy_noweight = inputBackgroundFile.Get("hist_jj_myy_3040");
		hist_yj_myy_noweight = inputBackgroundFile.Get("hist_yj_myy_3040");
		hist_jy_myy_noweight = inputBackgroundFile.Get("hist_jy_myy_3040");
	elif mu == 4060:
		hist_yy_data_myy = inputDataFile.Get("hist_myy_4060");
		hist_yy_mc_myy = inputMCFile.Get("hist_myy_4060");
		hist_yy_myy = inputBackgroundFile.Get("hist_yy_myy_4060");
		hist_jj_myy = inputBackgroundFile.Get("hist_jj_myy_4060_myy_purityweight");
		hist_yj_myy = inputBackgroundFile.Get("hist_yj_myy_4060_myy_purityweight");
		hist_jy_myy = inputBackgroundFile.Get("hist_jy_myy_4060_myy_purityweight");
		hist_jj_myy_noweight = inputBackgroundFile.Get("hist_jj_myy_4060");
		hist_yj_myy_noweight = inputBackgroundFile.Get("hist_yj_myy_4060");
		hist_jy_myy_noweight = inputBackgroundFile.Get("hist_jy_myy_4060");

	histData_myy = hist_yy_data_myy.Clone("histData_myy")

	hist_yj_myy.Add(hist_jy_myy)
	hist_yj_myy_noweight.Add(hist_jy_myy_noweight)

	myy = [hist_yy_mc_myy, hist_yj_myy, hist_jj_myy]
	# myy = [hist_yj_myy, hist_jj_myy]

	data_norm = hist_yy_data_myy.Integral()
	mc_norm = hist_yy_mc_myy.Integral()
	yj_norm = hist_yj_myy_noweight.Integral()
	jj_norm = hist_jj_myy_noweight.Integral()
	
	hist_myy = ROOT.THStack("hist_myy", "")
	
	normalize(hist_yy_data_myy, hist_yy_mc_myy, hist_jj_myy, hist_jj_myy_noweight, hist_yj_myy, hist_yj_myy_noweight)

	hist_myy.Add(hist_yy_mc_myy, "HIST")
	hist_myy.Add(hist_yj_myy, "HIST")
	hist_myy.Add(hist_jj_myy, "HIST")
	ROOT.gROOT.SetBatch(True)

	# hist_myy.Add(hist_yy_data_myy)
	myy_can = ROOT.TCanvas("myy_can", "")
	pad1 = ROOT.TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
	pad1.SetBottomMargin(0.15)
	pad1.Draw()
	pad1.cd()
	maximum_data = hist_yy_data_myy.GetMaximum() * 1.10; maximum_mc = hist_myy.GetMaximum() * 1.10
	if maximum_mc > maximum_data:
		maximum = maximum_mc
	elif maximum_data > maximum_mc:
		maximum = maximum_data
	hist_myy.Draw()
	hist_myy.SetMaximum(maximum)
	hist_yy_data_myy.Draw("ep same")
	# hist_yy_mc_myy.Draw("same")
	hist_myy.GetXaxis().SetTitle("m_{#gamma#gamma} [GeV]"); hist_myy.GetYaxis().SetTitle("Events"); hist_yy_data_myy.SetTitle("")
	legend =  ROOT.TLegend(0.6,0.7,0.9,0.9);
	if data == "full":
		lumi = 138.9
		save_name = "_full.pdf"
		legend.AddEntry(hist_yy_data_myy,"2015-2018 data","PL");
		legend.AddEntry(hist_jj_myy,"jet-jet (data driven)  %.2f %%" %(hist_jj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_myy,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_myy,"#gamma#gamma (MC16)  %.2f %%" %(hist_yy_mc_myy.Integral() * 100 / data_norm),"PL");
	elif data == "1516":
		lumi = 36.2
		save_name = "_1516.pdf"
		legend.AddEntry(hist_yy_data_myy,"2015-2016 data","PL");
		legend.AddEntry(hist_jj_myy,"jet-jet (data driven)  %.2f %%" %(hist_jj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_myy,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_myy,"#gamma#gamma (MC16a)  %.2f %%" %(hist_yy_mc_myy.Integral() * 100 / data_norm),"PL");
	elif data == "17":
		lumi = 44.3
		save_name = "_17.pdf"
		legend.AddEntry(hist_yy_data_myy,"2017 data","PL");
		legend.AddEntry(hist_jj_myy,"jet-jet (data driven)  %.2f %%" %(hist_jj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_myy,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_myy,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_myy.Integral() * 100 / data_norm),"PL");
	elif data == "18":
		lumi = 58.4
		save_name = "_18.pdf"
		legend.AddEntry(hist_yy_data_myy,"2018 data","PL");
		legend.AddEntry(hist_jj_myy,"jet-jet (data driven)  %.2f %%" %(hist_jj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_myy,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_myy,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_myy.Integral() * 100 / data_norm),"PL");
	legend.Draw();
	if mu == 10:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "0 < #mu < 10")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
	elif mu == 1020:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "10 < #mu < 20")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
	elif mu == 2030:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "20 < #mu < 30")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
	elif mu == 3040:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "30 < #mu < 40")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
	elif mu == 4060:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "40 < #mu < 60")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")

	myy_can.cd()
	pad2 = ROOT.TPad("pad2", "pad2", 0, 0, 1, 0.35)
	pad2.SetTopMargin(0.1)
	pad2.SetBottomMargin(0.25)
	pad2.Draw()
	pad2.SetTicks(0,1)
	pad2.cd()

	histData_myy.Sumw2(); histData_myy.SetStats(0); histData_myy.Divide(hist_myy.GetStack().Last()); histData_myy.SetTitle("")
	histData_myy.GetYaxis().SetTitle("Data/MC"); histData_myy.SetLineColor(1)
	histData_myy.GetXaxis().SetLabelSize(0.1); histData_myy.GetXaxis().SetTitleSize(0.1); histData_myy.GetXaxis().SetTitle("m_{#gamma#gamma} [GeV]")
	histData_myy.GetYaxis().SetLabelSize(0.1); histData_myy.GetYaxis().SetTitleSize(0.1); histData_myy.GetYaxis().SetTitleOffset(0.4)
	histData_myy.SetMinimum(0.5); histData_myy.SetMaximum(1.5)
	histData_myy.Draw("ep")

	myLine = ROOT.TLine(105,1,160,1); myLine.SetLineStyle(2); myLine.Draw()

	myy_can.cd()
	myy_can.Update()
	if jj_norm != 0 and yj_norm != 0:
		if mu == 10:
			myy_can.SaveAs("myy_myy_purities_010"+save_name)
		elif mu == 1020:
			myy_can.SaveAs("myy_myy_purities_1020"+save_name)
		elif mu == 2030:
			myy_can.SaveAs("myy_myy_purities_2030"+save_name)
		elif mu == 3040:
			myy_can.SaveAs("myy_myy_purities_3040"+save_name)
		elif mu == 4060:
			myy_can.SaveAs("myy_myy_purities_4060"+save_name)

	myy_can.Close()

def myy_myy_purities_inclusive(mu, data):
	if data == "full":
		inputDataFile = inputDataFile_full
		inputMCFile = inputMCFile_full
		inputBackgroundFile = inputBackgroundFile_full
	elif data == "1516":
		inputDataFile = inputDataFile_1516
		inputMCFile = inputMCFile_1516
		inputBackgroundFile = inputBackgroundFile_1516
	elif data == "17":
		inputDataFile = inputDataFile_17
		inputMCFile = inputMCFile_17
		inputBackgroundFile = inputBackgroundFile_17
	elif data == "18":
		inputDataFile = inputDataFile_18
		inputMCFile = inputMCFile_18
		inputBackgroundFile = inputBackgroundFile_18

	if mu == 10:
		hist_yy_data_myy = inputDataFile.Get("hist_myy_010_inclusive");
		hist_yy_mc_myy = inputMCFile.Get("hist_myy_010_inclusive");
		hist_yy_myy = inputBackgroundFile.Get("hist_yy_myy_010_inclusive");
		hist_jj_myy = inputBackgroundFile.Get("hist_jj_myy_010_myy_purityweight_inclusive");
		hist_yj_myy = inputBackgroundFile.Get("hist_yj_myy_010_myy_purityweight_inclusive");
		hist_jy_myy = inputBackgroundFile.Get("hist_jy_myy_010_myy_purityweight_inclusive");
		hist_jj_myy_noweight = inputBackgroundFile.Get("hist_jj_myy_010_inclusive");
		hist_yj_myy_noweight = inputBackgroundFile.Get("hist_yj_myy_010_inclusive");
		hist_jy_myy_noweight = inputBackgroundFile.Get("hist_jy_myy_010_inclusive");
	elif mu == 1020:
		hist_yy_data_myy = inputDataFile.Get("hist_myy_1020_inclusive");
		hist_yy_mc_myy = inputMCFile.Get("hist_myy_1020_inclusive");
		hist_yy_myy = inputBackgroundFile.Get("hist_yy_myy_1020_inclusive");
		hist_jj_myy = inputBackgroundFile.Get("hist_jj_myy_1020_myy_purityweight_inclusive");
		hist_yj_myy = inputBackgroundFile.Get("hist_yj_myy_1020_myy_purityweight_inclusive");
		hist_jy_myy = inputBackgroundFile.Get("hist_jy_myy_1020_myy_purityweight_inclusive");
		hist_jj_myy_noweight = inputBackgroundFile.Get("hist_jj_myy_1020_inclusive");
		hist_yj_myy_noweight = inputBackgroundFile.Get("hist_yj_myy_1020_inclusive");
		hist_jy_myy_noweight = inputBackgroundFile.Get("hist_jy_myy_1020_inclusive");
	elif mu == 2030:
		hist_yy_data_myy = inputDataFile.Get("hist_myy_2030_inclusive");
		hist_yy_mc_myy = inputMCFile.Get("hist_myy_2030_inclusive");
		hist_yy_myy = inputBackgroundFile.Get("hist_yy_myy_2030_inclusive");
		hist_jj_myy = inputBackgroundFile.Get("hist_jj_myy_2030_myy_purityweight_inclusive");
		hist_yj_myy = inputBackgroundFile.Get("hist_yj_myy_2030_myy_purityweight_inclusive");
		hist_jy_myy = inputBackgroundFile.Get("hist_jy_myy_2030_myy_purityweight_inclusive");
		hist_jj_myy_noweight = inputBackgroundFile.Get("hist_jj_myy_2030_inclusive");
		hist_yj_myy_noweight = inputBackgroundFile.Get("hist_yj_myy_2030_inclusive");
		hist_jy_myy_noweight = inputBackgroundFile.Get("hist_jy_myy_2030_inclusive");
	elif mu == 3040:
		hist_yy_data_myy = inputDataFile.Get("hist_myy_3040_inclusive");
		hist_yy_mc_myy = inputMCFile.Get("hist_myy_3040_inclusive");
		hist_yy_myy = inputBackgroundFile.Get("hist_yy_myy_3040_inclusive");
		hist_jj_myy = inputBackgroundFile.Get("hist_jj_myy_3040_myy_purityweight_inclusive");
		hist_yj_myy = inputBackgroundFile.Get("hist_yj_myy_3040_myy_purityweight_inclusive");
		hist_jy_myy = inputBackgroundFile.Get("hist_jy_myy_3040_myy_purityweight_inclusive");
		hist_jj_myy_noweight = inputBackgroundFile.Get("hist_jj_myy_3040_inclusive");
		hist_yj_myy_noweight = inputBackgroundFile.Get("hist_yj_myy_3040_inclusive");
		hist_jy_myy_noweight = inputBackgroundFile.Get("hist_jy_myy_3040_inclusive");
	elif mu == 4060:
		hist_yy_data_myy = inputDataFile.Get("hist_myy_4060_inclusive");
		hist_yy_mc_myy = inputMCFile.Get("hist_myy_4060_inclusive");
		hist_yy_myy = inputBackgroundFile.Get("hist_yy_myy_4060_inclusive");
		hist_jj_myy = inputBackgroundFile.Get("hist_jj_myy_4060_myy_purityweight_inclusive");
		hist_yj_myy = inputBackgroundFile.Get("hist_yj_myy_4060_myy_purityweight_inclusive");
		hist_jy_myy = inputBackgroundFile.Get("hist_jy_myy_4060_myy_purityweight_inclusive");
		hist_jj_myy_noweight = inputBackgroundFile.Get("hist_jj_myy_4060_inclusive");
		hist_yj_myy_noweight = inputBackgroundFile.Get("hist_yj_myy_4060_inclusive");
		hist_jy_myy_noweight = inputBackgroundFile.Get("hist_jy_myy_4060_inclusive");

	histData_myy = hist_yy_data_myy.Clone("histData_myy")

	hist_yj_myy.Add(hist_jy_myy)
	hist_yj_myy_noweight.Add(hist_jy_myy_noweight)

	myy = [hist_yy_mc_myy, hist_yj_myy, hist_jj_myy]
	# myy = [hist_yj_myy, hist_jj_myy]

	data_norm = hist_yy_data_myy.Integral()
	mc_norm = hist_yy_mc_myy.Integral()
	yj_norm = hist_yj_myy_noweight.Integral()
	jj_norm = hist_jj_myy_noweight.Integral()
	
	hist_myy = ROOT.THStack("hist_myy", "")
	
	normalize(hist_yy_data_myy, hist_yy_mc_myy, hist_jj_myy, hist_jj_myy_noweight, hist_yj_myy, hist_yj_myy_noweight)
	hist_myy.Add(hist_yy_mc_myy, "HIST")
	hist_myy.Add(hist_yj_myy, "HIST")
	hist_myy.Add(hist_jj_myy, "HIST")
	ROOT.gROOT.SetBatch(True)

	# total_bkgd_norm = hist_myy.GetStack().Last().Integral()
	# hist_myy.GetStack().Last().Scale(data_norm/total_bkgd_norm)
	# print total_bkgd_norm

	# hist_myy.Add(hist_yy_data_myy)
	myy_can = ROOT.TCanvas("myy_can", "")
	pad1 = ROOT.TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
	pad1.SetBottomMargin(0.15)
	pad1.Draw()
	pad1.cd()
	maximum_data = hist_yy_data_myy.GetMaximum() * 1.10; maximum_mc = hist_myy.GetMaximum() * 1.10
	# print maximum_mc, maximum_data
	if maximum_mc > maximum_data:
		maximum = maximum_mc
	elif maximum_data > maximum_mc:
		maximum = maximum_data
	hist_myy.Draw()
	hist_myy.SetMaximum(maximum)
	hist_yy_data_myy.Draw("ep same")
	# hist_yy_mc_myy.Draw("same")
	hist_myy.GetXaxis().SetTitle("m_{#gamma#gamma} [GeV]"); hist_myy.GetYaxis().SetTitle("Events"); hist_yy_data_myy.SetTitle("")
	legend =  ROOT.TLegend(0.6,0.7,0.9,0.9);
	if data == "full":
		lumi = 138.9
		save_name = "_full.pdf"
		legend.AddEntry(hist_yy_data_myy,"2015-2018 data","PL");
		legend.AddEntry(hist_jj_myy,"jet-jet (data driven)  %.2f %%" %(hist_jj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_myy,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_myy,"#gamma#gamma (MC16)  %.2f %%" %(hist_yy_mc_myy.Integral() * 100 / data_norm),"PL");
	elif data == "1516":
		lumi = 36.2
		save_name = "_1516.pdf"
		legend.AddEntry(hist_yy_data_myy,"2015-2016 data","PL");
		legend.AddEntry(hist_jj_myy,"jet-jet (data driven)  %.2f %%" %(hist_jj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_myy,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_myy,"#gamma#gamma (MC16a)  %.2f %%" %(hist_yy_mc_myy.Integral() * 100 / data_norm),"PL");
	elif data == "17":
		lumi = 44.3
		save_name = "_17.pdf"
		legend.AddEntry(hist_yy_data_myy,"2017 data","PL");
		legend.AddEntry(hist_jj_myy,"jet-jet (data driven)  %.2f %%" %(hist_jj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_myy,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_myy,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_myy.Integral() * 100 / data_norm),"PL");
	elif data == "18":
		lumi = 58.4
		save_name = "_18.pdf"
		legend.AddEntry(hist_yy_data_myy,"2018 data","PL");
		legend.AddEntry(hist_jj_myy,"jet-jet (data driven)  %.2f %%" %(hist_jj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_myy,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_myy,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_myy.Integral() * 100 / data_norm),"PL");
	legend.Draw();
	if mu == 10:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "0 < #mu < 10")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
		myLabel(0.60, 0.40, 1, "No jet requirement")
	elif mu == 1020:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "10 < #mu < 20")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
		myLabel(0.60, 0.40, 1, "No jet requirement")
	elif mu == 2030:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "20 < #mu < 30")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
		myLabel(0.60, 0.40, 1, "No jet requirement")
	elif mu == 3040:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "30 < #mu < 40")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
		myLabel(0.60, 0.40, 1, "No jet requirement")
	elif mu == 4060:
		ATLASLabel(0.59, 0.6, "Internal", 1) 
		myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
		myLabel(0.62, 0.5, 1, "40 < #mu < 60")
		myLabel(0.60, 0.45, 1, "105 < m_{#gamma#gamma} < 160")
		myLabel(0.60, 0.40, 1, "No jet requirement")

	myy_can.cd()
	pad2 = ROOT.TPad("pad2", "pad2", 0, 0, 1, 0.35)
	pad2.SetTopMargin(0.1)
	pad2.SetBottomMargin(0.25)
	pad2.Draw()
	pad2.SetTicks(0,1)
	pad2.cd()

	histData_myy.Sumw2(); histData_myy.SetStats(0); histData_myy.Divide(hist_myy.GetStack().Last()); histData_myy.SetTitle("")
	histData_myy.GetYaxis().SetTitle("Data/MC"); histData_myy.SetLineColor(1)
	histData_myy.GetXaxis().SetLabelSize(0.1); histData_myy.GetXaxis().SetTitleSize(0.1); histData_myy.GetXaxis().SetTitle("m_{#gamma#gamma} [GeV]")
	histData_myy.GetYaxis().SetLabelSize(0.1); histData_myy.GetYaxis().SetTitleSize(0.1); histData_myy.GetYaxis().SetTitleOffset(0.4)
	histData_myy.SetMinimum(0.5); histData_myy.SetMaximum(1.5)
	histData_myy.Draw("ep")

	myLine = ROOT.TLine(105,1,160,1); myLine.SetLineStyle(2); myLine.Draw()

	myy_can.cd()
	myy_can.Update()
	if jj_norm != 0 and yj_norm != 0:
		if mu == 10:
			myy_can.SaveAs("myy_myy_purities_inclusive_010"+save_name)
		elif mu == 1020:
			myy_can.SaveAs("myy_myy_purities_inclusive_1020"+save_name)
		elif mu == 2030:
			myy_can.SaveAs("myy_myy_purities_inclusive_2030"+save_name)
		elif mu == 3040:
			myy_can.SaveAs("myy_myy_purities_inclusive_3040"+save_name)
		elif mu == 4060:
			myy_can.SaveAs("myy_myy_purities_inclusive_4060"+save_name)

	myy_can.Close()

def mu_mu_purities(data):
	if data == "full":
		inputDataFile = inputDataFile_full
		inputMCFile = inputMCFile_full
		inputBackgroundFile = inputBackgroundFile_full
	elif data == "1516":
		inputDataFile = inputDataFile_1516
		inputMCFile = inputMCFile_1516
		inputBackgroundFile = inputBackgroundFile_1516
	elif data == "17":
		inputDataFile = inputDataFile_17
		inputMCFile = inputMCFile_17
		inputBackgroundFile = inputBackgroundFile_17
	elif data == "18":
		inputDataFile = inputDataFile_18
		inputMCFile = inputMCFile_18
		inputBackgroundFile = inputBackgroundFile_18

	hist_yy_data_mu = inputDataFile.Get("hist_mu");
	hist_yy_mc_mu = inputMCFile.Get("hist_mu");
	hist_yy_mu = inputBackgroundFile.Get("hist_yy_mu");
	hist_jj_mu = inputBackgroundFile.Get("hist_jj_mu_mu_purityweight");
	hist_yj_mu = inputBackgroundFile.Get("hist_yj_mu_mu_purityweight");
	hist_jy_mu = inputBackgroundFile.Get("hist_jy_mu_mu_purityweight");
	hist_jj_mu_noweight = inputBackgroundFile.Get("hist_jj_mu");
	hist_yj_mu_noweight = inputBackgroundFile.Get("hist_yj_mu");
	hist_jy_mu_noweight = inputBackgroundFile.Get("hist_jy_mu");

	histData_mu = hist_yy_data_mu.Clone("histData_mu")

	hist_yj_mu.Add(hist_jy_mu)
	hist_yj_mu_noweight.Add(hist_jy_mu_noweight)

	mu = [hist_yy_mc_mu, hist_yj_mu, hist_jj_mu]
	# mu = [hist_yj_mu, hist_jj_mu]

	data_norm = hist_yy_data_mu.Integral()
	mc_norm = hist_yy_mc_mu.Integral()
	yj_norm = hist_yj_mu_noweight.Integral()
	jj_norm = hist_jj_mu_noweight.Integral()
	
	hist_mu = ROOT.THStack("hist_mu", "")

	normalize(hist_yy_data_mu, hist_yy_mc_mu, hist_jj_mu, hist_jj_mu_noweight, hist_yj_mu, hist_yj_mu_noweight)

	hist_mu.Add(hist_yy_mc_mu, "HIST")
	hist_mu.Add(hist_yj_mu, "HIST")
	hist_mu.Add(hist_jj_mu, "HIST")
	ROOT.gROOT.SetBatch(True)

	# hist_mu.Add(hist_yy_data_mu)
	mu_can = ROOT.TCanvas("mu_can", "")
	pad1 = ROOT.TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
	pad1.SetBottomMargin(0.15)
	pad1.Draw()
	pad1.cd()
	maximum_data = hist_yy_data_mu.GetMaximum() * 1.10; maximum_mc = hist_mu.GetMaximum() * 1.10
	if maximum_mc > maximum_data:
		maximum = maximum_mc
	elif maximum_data > maximum_mc:
		maximum = maximum_data
	hist_mu.Draw()
	hist_mu.SetMaximum(maximum)
	hist_yy_data_mu.Draw("ep same")
	# hist_yy_mc_myuDraw("same")
	hist_mu.GetXaxis().SetTitle("<#mu>"); hist_mu.GetYaxis().SetTitle("Events"); hist_yy_data_mu.SetTitle("")
	legend =  ROOT.TLegend(0.15,0.7,0.45,0.9);
	# legend =  ROOT.TLegend(0.6,0.7,0.9,0.9);
	if data == "full":
		lumi = 138.9
		save_name = "_full.pdf"
		legend.AddEntry(hist_yy_data_mu,"2015-2018 data","PL");
		legend.AddEntry(hist_jj_mu,"jet-jet (data driven)  %.2f %%" %(hist_jj_mu.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_mu,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_mu.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_mu,"#gamma#gamma (MC16)  %.2f %%" %(hist_yy_mc_mu.Integral() * 100 / data_norm),"PL");
	elif data == "1516":
		lumi = 36.2
		save_name = "_1516.pdf"
		legend.AddEntry(hist_yy_data_mu,"2015-2016 data","PL");
		legend.AddEntry(hist_jj_mu,"jet-jet (data driven)  %.2f %%" %(hist_jj_mu.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_mu,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_mu.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_mu,"#gamma#gamma (MC16a)  %.2f %%" %(hist_yy_mc_mu.Integral() * 100 / data_norm),"PL");
	elif data == "17":
		lumi = 44.3
		save_name = "_17.pdf"
		legend.AddEntry(hist_yy_data_mu,"2017 data","PL");
		legend.AddEntry(hist_jj_mu,"jet-jet (data driven)  %.2f %%" %(hist_jj_mu.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_mu,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_mu.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_mu,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_mu.Integral() * 100 / data_norm),"PL");
	elif data == "18":
		lumi = 58.4
		save_name = "_18.pdf"
		legend.AddEntry(hist_yy_data_mu,"2018 data","PL");
		legend.AddEntry(hist_jj_mu,"jet-jet (data driven)  %.2f %%" %(hist_jj_mu.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_mu,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_mu.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_mu,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_mu.Integral() * 100 / data_norm),"PL");
	legend.Draw();
	ATLASLabel(0.7, 0.6, "Internal", 1) 
	myLabel(0.66, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
	myLabel(0.70, 0.5, 1, "105 < m_{#gamma#gamma} < 160")
	mu_can.cd()
	pad2 = ROOT.TPad("pad2", "pad2", 0, 0, 1, 0.35)
	pad2.SetTopMargin(0.1)
	pad2.SetBottomMargin(0.25)
	pad2.Draw()
	pad2.SetTicks(0,1)
	pad2.cd()

	histData_mu.Sumw2(); histData_mu.SetStats(0); histData_mu.Divide(hist_mu.GetStack().Last()); histData_mu.SetTitle("")
	histData_mu.GetYaxis().SetTitle("Data/MC"); histData_mu.SetLineColor(1)
	histData_mu.GetXaxis().SetLabelSize(0.1); histData_mu.GetXaxis().SetTitleSize(0.1); histData_mu.GetXaxis().SetTitle("<#mu>")
	histData_mu.GetYaxis().SetLabelSize(0.1); histData_mu.GetYaxis().SetTitleSize(0.1); histData_mu.GetYaxis().SetTitleOffset(0.4)
	histData_mu.SetMinimum(0.5); histData_mu.SetMaximum(1.5)
	histData_mu.Draw("ep")

	myLine = ROOT.TLine(0,1,60,1); myLine.SetLineStyle(2); myLine.Draw()

	mu_can.cd()
	mu_can.Update()

	mu_can.SaveAs("mu_mu_purities"+save_name)
	mu_can.Close()

def myy_myy_purities_inclusive_all(data):
	if data == "full":
		inputDataFile = inputDataFile_full
		inputMCFile = inputMCFile_full
		inputBackgroundFile = inputBackgroundFile_full
	elif data == "1516":
		inputDataFile = inputDataFile_1516
		inputMCFile = inputMCFile_1516
		inputBackgroundFile = inputBackgroundFile_1516
	elif data == "17":
		inputDataFile = inputDataFile_17
		inputMCFile = inputMCFile_17
		inputBackgroundFile = inputBackgroundFile_17
	elif data == "18":
		inputDataFile = inputDataFile_18
		inputMCFile = inputMCFile_18
		inputBackgroundFile = inputBackgroundFile_18

	hist_yy_data_myy = inputDataFile.Get("hist_myy_inclusive");
	hist_yy_mc_myy = inputMCFile.Get("hist_myy_inclusive");
	hist_yy_myy = inputBackgroundFile.Get("hist_yy_myy_inclusive");
	hist_jj_myy = inputBackgroundFile.Get("hist_jj_myy_myy_purityweight_inclusive");
	hist_yj_myy = inputBackgroundFile.Get("hist_yj_myy_myy_purityweight_inclusive");
	hist_jy_myy = inputBackgroundFile.Get("hist_jy_myy_myy_purityweight_inclusive");
	hist_jj_myy_noweight = inputBackgroundFile.Get("hist_jj_myy_inclusive");
	hist_yj_myy_noweight = inputBackgroundFile.Get("hist_yj_myy_inclusive");
	hist_jy_myy_noweight = inputBackgroundFile.Get("hist_jy_myy_inclusive");
	histData_myy = hist_yy_data_myy.Clone("histData_myy")

	hist_yj_myy.Add(hist_jy_myy)
	hist_yj_myy_noweight.Add(hist_jy_myy_noweight)

	myy = [hist_yy_mc_myy, hist_yj_myy, hist_jj_myy]
	# myy = [hist_yj_myy, hist_jj_myy]

	data_norm = hist_yy_data_myy.Integral()
	mc_norm = hist_yy_mc_myy.Integral()
	yj_norm = hist_yj_myy_noweight.Integral()
	jj_norm = hist_jj_myy_noweight.Integral()

	# print jj_norm + yj_norm + mc_norm

	# print mc_norm
	
	hist_myy = ROOT.THStack("hist_myy", "")

	normalize(hist_yy_data_myy, hist_yy_mc_myy, hist_jj_myy, hist_jj_myy_noweight, hist_yj_myy, hist_yj_myy_noweight)
	hist_myy.Add(hist_yy_mc_myy, "HIST")
	hist_myy.Add(hist_yj_myy, "HIST")
	hist_myy.Add(hist_jj_myy, "HIST")
	ROOT.gROOT.SetBatch(True)

	# hist_myy.Add(hist_yy_data_myy)
	myy_can = ROOT.TCanvas("myy_can", "")
	pad1 = ROOT.TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
	pad1.SetBottomMargin(0.15)
	pad1.Draw()
	pad1.cd()
	maximum_data = hist_yy_data_myy.GetMaximum() * 1.10; maximum_mc = hist_myy.GetMaximum() * 1.10
	# print maximum_mc, maximum_data
	if maximum_mc > maximum_data:
		maximum = maximum_mc
	elif maximum_data > maximum_mc:
		maximum = maximum_data
	hist_myy.Draw()
	hist_myy.SetMaximum(maximum)
	hist_yy_data_myy.Draw("ep same")
	# hist_yy_mc_myy.Draw("same")
	hist_myy.GetXaxis().SetTitle("m_{#gamma#gamma} [GeV]"); hist_myy.GetYaxis().SetTitle("Events"); hist_yy_data_myy.SetTitle("")
	legend =  ROOT.TLegend(0.6,0.7,0.9,0.9);
	if data == "full":
		lumi = 138.9
		save_name = "_full.pdf"
		legend.AddEntry(hist_yy_data_myy,"2015-2018 data","PL");
		legend.AddEntry(hist_jj_myy,"jet-jet (data driven)  %.2f %%" %(hist_jj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_myy,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_myy,"#gamma#gamma (MC16)  %.2f %%" %(hist_yy_mc_myy.Integral() * 100 / data_norm),"PL");
	elif data == "1516":
		lumi = 36.2
		save_name = "_1516.pdf"
		legend.AddEntry(hist_yy_data_myy,"2015-2016 data","PL");
		legend.AddEntry(hist_jj_myy,"jet-jet (data driven)  %.2f %%" %(hist_jj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_myy,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_myy,"#gamma#gamma (MC16a)  %.2f %%" %(hist_yy_mc_myy.Integral() * 100 / data_norm),"PL");
	elif data == "17":
		lumi = 44.3
		save_name = "_17.pdf"
		legend.AddEntry(hist_yy_data_myy,"2017 data","PL");
		legend.AddEntry(hist_jj_myy,"jet-jet (data driven)  %.2f %%" %(hist_jj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_myy,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_myy,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_myy.Integral() * 100 / data_norm),"PL");
	elif data == "18":
		lumi = 58.4
		save_name = "_18.pdf"
		legend.AddEntry(hist_yy_data_myy,"2018 data","PL");
		legend.AddEntry(hist_jj_myy,"jet-jet (data driven)  %.2f %%" %(hist_jj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_myy,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_myy.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_myy,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_myy.Integral() * 100 / data_norm),"PL");
	legend.Draw();

	ATLASLabel(0.59, 0.6, "Internal", 1) 
	myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
	myLabel(0.60, 0.50, 1, "105 < m_{#gamma#gamma} < 160")
	myLabel(0.60, 0.45, 1, "No jet requirement")

	myy_can.cd()
	pad2 = ROOT.TPad("pad2", "pad2", 0, 0, 1, 0.35)
	pad2.SetTopMargin(0.1)
	pad2.SetBottomMargin(0.25)
	pad2.Draw()
	pad2.SetTicks(0,1)
	pad2.cd()

	histData_myy.Sumw2(); histData_myy.SetStats(0); histData_myy.Divide(hist_myy.GetStack().Last()); histData_myy.SetTitle("")
	histData_myy.GetYaxis().SetTitle("Data/MC"); histData_myy.SetLineColor(1)
	histData_myy.GetXaxis().SetLabelSize(0.1); histData_myy.GetXaxis().SetTitleSize(0.1); histData_myy.GetXaxis().SetTitle("m_{#gamma#gamma} [GeV]")
	histData_myy.GetYaxis().SetLabelSize(0.1); histData_myy.GetYaxis().SetTitleSize(0.1); histData_myy.GetYaxis().SetTitleOffset(0.4)
	histData_myy.SetMinimum(0.5); histData_myy.SetMaximum(1.5)
	histData_myy.Draw("ep")

	myLine = ROOT.TLine(105,1,160,1); myLine.SetLineStyle(2); myLine.Draw()

	myy_can.cd()
	myy_can.Update()
	myy_can.SaveAs("myy_myy_purities_inclusive"+save_name)
	myy_can.Close()

def eta_ptj1_purities_all(data):
	if data == "full":
		inputDataFile = inputDataFile_full
		inputMCFile = inputMCFile_full
		inputBackgroundFile = inputBackgroundFile_full
	elif data == "1516":
		inputDataFile = inputDataFile_1516
		inputMCFile = inputMCFile_1516
		inputBackgroundFile = inputBackgroundFile_1516
	elif data == "17":
		inputDataFile = inputDataFile_17
		inputMCFile = inputMCFile_17
		inputBackgroundFile = inputBackgroundFile_17
	elif data == "18":
		inputDataFile = inputDataFile_18
		inputMCFile = inputMCFile_18
		inputBackgroundFile = inputBackgroundFile_18

	hist_yy_data_eta = inputDataFile.Get("hist_j130_eta");
	hist_yy_mc_eta = inputMCFile.Get("hist_j130_eta");

	hist_yy_eta = inputBackgroundFile.Get("hist_yy_pflowj1_eta");

	hist_jj_eta = inputBackgroundFile.Get("hist_jj_pflowj1_eta_purityweight"); 
	hist_yj_eta = inputBackgroundFile.Get("hist_yj_pflowj1_eta_purityweight");  
	hist_jy_eta = inputBackgroundFile.Get("hist_jy_pflowj1_eta_purityweight"); 

	hist_jj_eta_noweight = inputBackgroundFile.Get("hist_jj_pflowj1_eta");
	hist_yj_eta_noweight = inputBackgroundFile.Get("hist_yj_pflowj1_eta");
	hist_jy_eta_noweight = inputBackgroundFile.Get("hist_jy_pflowj1_eta");

	histData_eta = hist_yy_data_eta.Clone("histData_eta")

	# print hist_yy_data_eta, hist_yy_mc_eta, hist_yy_eta, hist_jj_eta, hist_yj_eta, hist_jy_eta, hist_jj_eta_noweight, hist_yj_eta_noweight, hist_jy_eta_noweight

	hist_yj_eta.Add(hist_jy_eta)
	hist_yj_eta_noweight.Add(hist_jy_eta_noweight)

	eta = [hist_yy_mc_eta, hist_yj_eta, hist_jj_eta]
	# eta = [hist_yj_eta, hist_jj_eta]

	data_norm = hist_yy_data_eta.Integral()
	mc_norm = hist_yy_mc_eta.Integral()
	yj_norm = hist_yj_eta_noweight.Integral()
	jj_norm = hist_jj_eta_noweight.Integral()

	total_mc_norm = mc_norm + yj_norm + jj_norm
	
	hist_eta = ROOT.THStack("hist_eta", "")

	normalize(hist_yy_data_eta, hist_yy_mc_eta, hist_jj_eta, hist_jj_eta_noweight, hist_yj_eta, hist_yj_eta_noweight)

	hist_eta.Add(hist_yy_mc_eta, "HIST")
	hist_eta.Add(hist_yj_eta, "HIST")
	hist_eta.Add(hist_jj_eta, "HIST")
	ROOT.gROOT.SetBatch(True)

	# hist_eta.Add(hist_yy_data_eta)
	eta_can = ROOT.TCanvas("eta_can", "")
	pad1 = ROOT.TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
	pad1.SetBottomMargin(0.15)
	pad1.Draw()
	pad1.cd()
	maximum_data = hist_yy_data_eta.GetMaximum() * 1.10; maximum_mc = hist_eta.GetMaximum() * 1.10
	# print maximum_mc, maximum_data
	if maximum_mc > maximum_data:
		maximum = maximum_mc
	elif maximum_data > maximum_mc:
		maximum = maximum_data
	hist_eta.Draw()
	hist_eta.SetMaximum(maximum)
	hist_yy_data_eta.Draw("ep same")
	# hist_yy_mc_eta.Draw("same")
	hist_eta.GetXaxis().SetTitle("#eta"); hist_eta.GetYaxis().SetTitle("Events"); hist_yy_data_eta.SetTitle("")
	legend =  ROOT.TLegend(0.6,0.7,0.9,0.9);
	if data == "full":
		lumi = 138.9
		save_name = "_full.pdf"
		legend.AddEntry(hist_yy_data_eta,"2015-2018 data","PL");
		legend.AddEntry(hist_jj_eta,"jet-jet (data driven)  %.2f %%" %(hist_jj_eta.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_eta,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_eta.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_eta,"#gamma#gamma (MC16)  %.2f %%" %(hist_yy_mc_eta.Integral() * 100 / data_norm),"PL");
	elif data == "1516":
		lumi = 36.2
		save_name = "_1516.pdf"
		legend.AddEntry(hist_yy_data_eta,"2015-2016 data","PL");
		legend.AddEntry(hist_jj_eta,"jet-jet (data driven)  %.2f %%" %(hist_jj_eta.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_eta,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_eta.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_eta,"#gamma#gamma (MC16a)  %.2f %%" %(hist_yy_mc_eta.Integral() * 100 / data_norm),"PL");
	elif data == "17":
		lumi = 44.3
		save_name = "_17.pdf"
		legend.AddEntry(hist_yy_data_eta,"2017 data","PL");
		legend.AddEntry(hist_jj_eta,"jet-jet (data driven)  %.2f %%" %(hist_jj_eta.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_eta,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_eta.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_eta,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_eta.Integral() * 100 / data_norm),"PL");
	elif data == "18":
		lumi = 58.4
		save_name = "_18.pdf"
		legend.AddEntry(hist_yy_data_eta,"2018 data","PL");
		legend.AddEntry(hist_jj_eta,"jet-jet (data driven)  %.2f %%" %(hist_jj_eta.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_eta,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_eta.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_eta,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_eta.Integral() * 100 / data_norm),"PL");
	legend.Draw();

	ATLASLabel(0.2, 0.8, "Internal", 1) 
	myLabel(0.15, 0.75, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
	myLabel(0.2, 0.70, 1, "105 < m_{#gamma#gamma} < 160")
	myLabel(0.2, 0.65, 1, "No jet requirement")

	eta_can.cd()
	pad2 = ROOT.TPad("pad2", "pad2", 0, 0, 1, 0.35)
	pad2.SetTopMargin(0.1)
	pad2.SetBottomMargin(0.25)
	pad2.Draw()
	pad2.SetTicks(0,1)
	pad2.cd()

	histData_eta.Sumw2(); histData_eta.SetStats(0); histData_eta.Divide(hist_eta.GetStack().Last()); histData_eta.SetTitle("")
	histData_eta.GetYaxis().SetTitle("Data/MC"); histData_eta.SetLineColor(1)
	histData_eta.GetXaxis().SetLabelSize(0.1); histData_eta.GetXaxis().SetTitleSize(0.1); histData_eta.GetXaxis().SetTitle("#eta")
	histData_eta.GetYaxis().SetLabelSize(0.1); histData_eta.GetYaxis().SetTitleSize(0.1); histData_eta.GetYaxis().SetTitleOffset(0.4)
	histData_eta.SetMinimum(0.5); histData_eta.SetMaximum(1.5)
	histData_eta.Draw("ep")

	myLine = ROOT.TLine(-4,1,4,1); myLine.SetLineStyle(2); myLine.Draw()

	eta_can.cd()
	eta_can.Update()
	eta_can.SaveAs("eta_ptj1_purities"+save_name)
	eta_can.Close()

def ptj1_ptj1_purities_all(data):
	if data == "full":
		inputDataFile = inputDataFile_full
		inputMCFile = inputMCFile_full
		inputBackgroundFile = inputBackgroundFile_full
	elif data == "1516":
		inputDataFile = inputDataFile_1516
		inputMCFile = inputMCFile_1516
		inputBackgroundFile = inputBackgroundFile_1516
	elif data == "17":
		inputDataFile = inputDataFile_17
		inputMCFile = inputMCFile_17
		inputBackgroundFile = inputBackgroundFile_17
	elif data == "18":
		inputDataFile = inputDataFile_18
		inputMCFile = inputMCFile_18
		inputBackgroundFile = inputBackgroundFile_18

	hist_yy_data_pt = inputDataFile.Get("hist_j130_pt");
	hist_yy_mc_pt = inputMCFile.Get("hist_j130_pt");
	hist_yy_pt = inputBackgroundFile.Get("hist_yy_pflowj1_pt");
	hist_jj_pt = inputBackgroundFile.Get("hist_jj_pflowj1_pt_ptj1_purityweight");
	hist_yj_pt = inputBackgroundFile.Get("hist_yj_pflowj1_pt_ptj1_purityweight");
	hist_jy_pt = inputBackgroundFile.Get("hist_jy_pflowj1_pt_ptj1_purityweight");

	hist_jj_pt_noweight = inputBackgroundFile.Get("hist_jj_pflowj1_pt");
	hist_yj_pt_noweight = inputBackgroundFile.Get("hist_yj_pflowj1_pt");
	hist_jy_pt_noweight = inputBackgroundFile.Get("hist_jy_pflowj1_pt");

	histData_pt = hist_yy_data_pt.Clone("histData_pt")

	hist_yj_pt.Add(hist_jy_pt)
	hist_yj_pt_noweight.Add(hist_jy_pt_noweight)

	pt = [hist_yy_mc_pt, hist_yj_pt, hist_jj_pt]
	# pt = [hist_yj_pt, hist_jj_pt]

	data_norm = hist_yy_data_pt.Integral()
	mc_norm = hist_yy_mc_pt.Integral()
	yj_norm = hist_yj_pt_noweight.Integral()
	jj_norm = hist_jj_pt_noweight.Integral()

	total_mc_norm = mc_norm + yj_norm + jj_norm
	
	hist_pt = ROOT.THStack("hist_pt", "")

	normalize(hist_yy_data_pt, hist_yy_mc_pt, hist_jj_pt, hist_jj_pt_noweight, hist_yj_pt, hist_yj_pt_noweight)
	
	hist_pt.Add(hist_yy_mc_pt, "HIST")
	hist_pt.Add(hist_yj_pt, "HIST")
	hist_pt.Add(hist_jj_pt, "HIST")
	ROOT.gROOT.SetBatch(True)

	# hist_pt.Add(hist_yy_data_pt)
	pt_can = ROOT.TCanvas("pt_can", "")
	pad1 = ROOT.TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
	pad1.SetBottomMargin(0.15)
	pad1.Draw()
	pad1.cd()
	maximum_data = hist_yy_data_pt.GetMaximum() * 1.10; maximum_mc = hist_pt.GetMaximum() * 1.10
	# print maximum_mc, maximum_data
	if maximum_mc > maximum_data:
		maximum = maximum_mc
	elif maximum_data > maximum_mc:
		maximum = maximum_data
	hist_pt.Draw()
	hist_pt.SetMaximum(maximum)
	hist_yy_data_pt.Draw("ep same")
	# hist_yy_mc_pt.Draw("same")
	hist_pt.GetXaxis().SetTitle("Leading jet p_{T} [GeV]"); hist_pt.GetYaxis().SetTitle("Events"); hist_yy_data_pt.SetTitle("")
	legend =  ROOT.TLegend(0.6,0.7,0.9,0.9);
	if data == "full":
		lumi = 138.9
		save_name = "_full.pdf"
		legend.AddEntry(hist_yy_data_pt,"2015-2018 data","PL");
		legend.AddEntry(hist_jj_pt,"jet-jet (data driven)  %.2f %%" %(hist_jj_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_pt,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_pt,"#gamma#gamma (MC16)  %.2f %%" %(hist_yy_mc_pt.Integral() * 100 / data_norm),"PL");
	elif data == "1516":
		lumi = 36.2
		save_name = "_1516.pdf"
		legend.AddEntry(hist_yy_data_pt,"2015-2016 data","PL");
		legend.AddEntry(hist_jj_pt,"jet-jet (data driven)  %.2f %%" %(hist_jj_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_pt,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_pt,"#gamma#gamma (MC16a)  %.2f %%" %(hist_yy_mc_pt.Integral() * 100 / data_norm),"PL");
	elif data == "17":
		lumi = 44.3
		save_name = "_17.pdf"
		legend.AddEntry(hist_yy_data_pt,"2017 data","PL");
		legend.AddEntry(hist_jj_pt,"jet-jet (data driven)  %.2f %%" %(hist_jj_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_pt,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_pt,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_pt.Integral() * 100 / data_norm),"PL");
	elif data == "18":
		lumi = 58.4
		save_name = "_18.pdf"
		legend.AddEntry(hist_yy_data_pt,"2018 data","PL");
		legend.AddEntry(hist_jj_pt,"jet-jet (data driven)  %.2f %%" %(hist_jj_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yj_pt,"#gamma-jet (data driven)  %.2f %%" %(hist_yj_pt.Integral() * 100 / data_norm),"PL");
		legend.AddEntry(hist_yy_mc_pt,"#gamma#gamma (MC16d)  %.2f %%" %(hist_yy_mc_pt.Integral() * 100 / data_norm),"PL");
	legend.Draw();

	ATLASLabel(0.59, 0.6, "Internal", 1) 
	myLabel(0.55, 0.55, 1, "#sqrt{s}= 13 TeV   #int L dt = %.1f fb^{-1}"%(lumi))
	myLabel(0.60, 0.50, 1, "105 < m_{#gamma#gamma} < 160")
	myLabel(0.60, 0.45, 1, "No jet requirement")

	pt_can.cd()
	pad2 = ROOT.TPad("pad2", "pad2", 0, 0, 1, 0.35)
	pad2.SetTopMargin(0.1)
	pad2.SetBottomMargin(0.25)
	pad2.Draw()
	pad2.SetTicks(0,1)
	pad2.cd()

	histData_pt.Sumw2(); histData_pt.SetStats(0); histData_pt.Divide(hist_pt.GetStack().Last()); histData_pt.SetTitle("")
	histData_pt.GetYaxis().SetTitle("Data/MC"); histData_pt.SetLineColor(1)
	histData_pt.GetXaxis().SetLabelSize(0.1); histData_pt.GetXaxis().SetTitleSize(0.1); histData_pt.GetXaxis().SetTitle("Leading jet p_{T} [GeV]")
	histData_pt.GetYaxis().SetLabelSize(0.1); histData_pt.GetYaxis().SetTitleSize(0.1); histData_pt.GetYaxis().SetTitleOffset(0.4)
	histData_pt.SetMinimum(0.5); histData_pt.SetMaximum(1.5)
	histData_pt.Draw("ep")

	myLine = ROOT.TLine(0,1,450,1); myLine.SetLineStyle(2); myLine.Draw()

	pt_can.cd()
	pt_can.Update()
	pt_can.SaveAs("pt_ptj1_purities_all"+save_name)
	pt_can.Close()


def run_ptj1_ptj1_purities():
	ptj1_ptj1_purities(10, "18")
	ptj1_ptj1_purities(1020, "18")
	ptj1_ptj1_purities(2030, "18")
	ptj1_ptj1_purities(3040, "18")
	ptj1_ptj1_purities(4060, "18")

	ptj1_ptj1_purities(10, "17")
	ptj1_ptj1_purities(1020, "17")
	ptj1_ptj1_purities(2030, "17")
	ptj1_ptj1_purities(3040, "17")
	ptj1_ptj1_purities(4060, "17")
	
	ptj1_ptj1_purities(10, "1516")
	ptj1_ptj1_purities(1020, "1516")
	ptj1_ptj1_purities(2030, "1516")
	ptj1_ptj1_purities(3040, "1516")
	ptj1_ptj1_purities(4060, "1516")

	ptj1_ptj1_purities(10, "full")
	ptj1_ptj1_purities(1020, "full")
	ptj1_ptj1_purities(2030, "full")
	ptj1_ptj1_purities(3040, "full")
	ptj1_ptj1_purities(4060, "full")

def run_myy_myy_purities():
	myy_myy_purities(10, "18")
	myy_myy_purities(1020, "18")
	myy_myy_purities(2030, "18")
	myy_myy_purities(3040, "18")
	myy_myy_purities(4060, "18")

	myy_myy_purities(10, "17")
	myy_myy_purities(1020, "17")
	myy_myy_purities(2030, "17")
	myy_myy_purities(3040, "17")
	myy_myy_purities(4060, "17")
	
	myy_myy_purities(10, "1516")
	myy_myy_purities(1020, "1516")
	myy_myy_purities(2030, "1516")
	myy_myy_purities(3040, "1516")
	myy_myy_purities(4060, "1516")

	myy_myy_purities(10, "full")
	myy_myy_purities(1020, "full")
	myy_myy_purities(2030, "full")
	myy_myy_purities(3040, "full")
	myy_myy_purities(4060, "full")

def run_myy_myy_purities_inclusive():
	myy_myy_purities_inclusive(10, "18")
	myy_myy_purities_inclusive(1020, "18")
	myy_myy_purities_inclusive(2030, "18")
	myy_myy_purities_inclusive(3040, "18")
	myy_myy_purities_inclusive(4060, "18")

	myy_myy_purities_inclusive(10, "17")
	myy_myy_purities_inclusive(1020, "17")
	myy_myy_purities_inclusive(2030, "17")
	myy_myy_purities_inclusive(3040, "17")
	myy_myy_purities_inclusive(4060, "17")
	
	myy_myy_purities_inclusive(10, "1516")
	myy_myy_purities_inclusive(1020, "1516")
	myy_myy_purities_inclusive(2030, "1516")
	myy_myy_purities_inclusive(3040, "1516")
	myy_myy_purities_inclusive(4060, "1516")

	myy_myy_purities_inclusive(10, "full")
	myy_myy_purities_inclusive(1020, "full")
	myy_myy_purities_inclusive(2030, "full")
	myy_myy_purities_inclusive(3040, "full")
	myy_myy_purities_inclusive(4060, "full")

def run_ptj1_ptj1_purities_central():
	ptj1_ptj1_purities_central(10, "18")
	ptj1_ptj1_purities_central(1020, "18")
	ptj1_ptj1_purities_central(2030, "18")
	ptj1_ptj1_purities_central(3040, "18")
	ptj1_ptj1_purities_central(4060, "18")

	ptj1_ptj1_purities_central(10, "17")
	ptj1_ptj1_purities_central(1020, "17")
	ptj1_ptj1_purities_central(2030, "17")
	ptj1_ptj1_purities_central(3040, "17")
	ptj1_ptj1_purities_central(4060, "17")
	
	ptj1_ptj1_purities_central(10, "1516")
	ptj1_ptj1_purities_central(1020, "1516")
	ptj1_ptj1_purities_central(2030, "1516")
	ptj1_ptj1_purities_central(3040, "1516")
	ptj1_ptj1_purities_central(4060, "1516")

	ptj1_ptj1_purities_central(10, "full")
	ptj1_ptj1_purities_central(1020, "full")
	ptj1_ptj1_purities_central(2030, "full")
	ptj1_ptj1_purities_central(3040, "full")
	ptj1_ptj1_purities_central(4060, "full")

def run_mu_mu_purities():
	mu_mu_purities("18")
	mu_mu_purities("17")
	mu_mu_purities("1516")
	mu_mu_purities("full")

def run_myy_myy_purities_inclusive_all():
	myy_myy_purities_inclusive_all("18")
	myy_myy_purities_inclusive_all("17")
	myy_myy_purities_inclusive_all("1516")
	myy_myy_purities_inclusive_all("full")

def run_eta_ptj1_purities_all():
	eta_ptj1_purities_all("18")
	eta_ptj1_purities_all("17")
	eta_ptj1_purities_all("1516")
	eta_ptj1_purities_all("full")

def run_ptj1_ptj1_purities_all():
	ptj1_ptj1_purities_all("18")
	ptj1_ptj1_purities_all("17")
	ptj1_ptj1_purities_all("1516")
	ptj1_ptj1_purities_all("full")


if __name__ == '__main__':
	run_ptj1_ptj1_purities()
	run_myy_myy_purities()
	run_myy_myy_purities_inclusive()
	run_ptj1_ptj1_purities_central()
	run_mu_mu_purities()
	run_myy_myy_purities_inclusive_all()
	run_eta_ptj1_purities_all()
	run_ptj1_ptj1_purities_all()