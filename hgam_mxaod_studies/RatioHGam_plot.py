import ROOT 
import sys
import os
import time
import numpy
from AtlasStyle import *

ROOT.gStyle.SetOptStat(0)
inputMCDir = str(sys.argv[1])+"/tmpOutput"
for file in os.listdir(inputMCDir):
    if file.endswith(".root"):
        inputMCPath = os.path.join(inputMCDir, file)

inputMCFile = ROOT.TFile(inputMCPath)
print("Imported MC file "+inputMCPath)

inputDataDir = str(sys.argv[2])+"/tmpOutput"
# print str(sys.argv[2])
for file in os.listdir(inputDataDir):
    if file.endswith(".root"):
        inputDataPath = os.path.join(inputDataDir, file)

inputDataFile = ROOT.TFile(inputDataPath)
print("Imported data file "+inputDataPath)


histMC_j130_pt_015  = inputMCFile.Get("hist_j130_pt_015_noNorm")
histData_j130_pt_015  = inputDataFile.Get("hist_j130_pt_015_noNorm")
histData_j130_pt_015.SetLineColor(1)
histMC_j130_pt_015.SetLineColor(2)
# histData_j130_pt_015.SetMarkers
histData_j130_pt_015.SetTitle("Data18")
histMC_j130_pt_015.SetTitle("MC16a")


# print histMC_j130_pt_015
# print histData_j130_pt_015
# histData_j130_pt_015.GetXaxis().SetLabelFont(63)
histData_j130_pt_015.GetXaxis().SetLabelSize(0.05)
histData_j130_pt_015.GetYaxis().SetLabelSize(0.05)
# histData_j130_pt_015.GetXaxis().SetTitleSize(0.05)
# histData_j130_pt_015.GetYaxis().SetTitleSize(0.05)
# histData_j130_pt_015.GetXaxis().SetTitle("p_{T}")
# histData_j130_pt_015.GetXaxis().SetTitleSize(16)
# histData_j130_pt_015.GetYaxis().SetLabelSize(16)
# histData_j130_pt_015.GetYaxis().SetLabelFont(63)
# histData_j130_pt_015.SetTitle("Leading Jet p_{T}")
c1 = ROOT.TCanvas("c1", "c1")
pad1 = ROOT.TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
pad1.SetBottomMargin(0.15)
pad1.Draw()
pad1.cd()
histMC_j130_pt_015.SetLineStyle(1)
histData_j130_pt_015.SetMarkerStyle(20)
histData_j130_pt_015.DrawCopy()
histMC_j130_pt_015.Draw("same")
pad1.BuildLegend()
c1.cd()


pad2 = ROOT.TPad("pad2", "pad2", 0, 0, 1, 0.35)
pad2.SetTopMargin(0.1)
pad2.SetBottomMargin(0.25)
pad2.SetGridy()
pad2.Draw()
pad2.SetTicks(0,1)
pad2.cd()

histData_j130_pt_015.Sumw2()
histData_j130_pt_015.SetStats(0)
histData_j130_pt_015.Divide(histMC_j130_pt_015)
histData_j130_pt_015.SetTitle("")

    # h_dataClone.GetYaxis().SetTitle(" Data/MC ")
    # h_dataClone.GetYaxis().SetNdivisions(505)
    # h_dataClone.GetYaxis().SetTitleSize(.1)
    # h_dataClone.GetYaxis().SetTitleOffset(.5)
    # h_dataClone.GetYaxis().SetLabelFont(43)
    # h_dataClone.GetYaxis().SetLabelSize(15)
    # h_dataClone.GetYaxis().SetRangeUser(0.,2.)



histData_j130_pt_015.GetYaxis().SetTitle("Data/MC")
histData_j130_pt_015.GetXaxis().SetTitle("p_{T}")
# histData_j130_pt_015.GetYaxis().SetLabelFont(63)
histData_j130_pt_015.GetXaxis().SetLabelSize(0.1)
histData_j130_pt_015.GetXaxis().SetTitle("p_{T}")
histData_j130_pt_015.GetYaxis().SetLabelSize(0.1)
histData_j130_pt_015.GetYaxis().SetTitleSize(0.1)
histData_j130_pt_015.GetYaxis().SetTitleOffset(0.5)
histData_j130_pt_015.GetYaxis().SetLabelFont(43)
histData_j130_pt_015.GetYaxis().SetLabelSize(15)
# histData_j130_pt_015.SetMarkerStyle(21)
histData_j130_pt_015.Draw("ep")
c1.cd()
# rp_j130_pt_015 = ROOT.TRatioPlot(histMC_j130_pt_015, histData_j130_pt_015)
# c1.SetTicks(0, 1)
# rp_j130_pt_015.SetGridlines(numpy.array(7.0)) 
# rp_j130_pt_015.Draw()
c1.Update()

raw_input("enter")

