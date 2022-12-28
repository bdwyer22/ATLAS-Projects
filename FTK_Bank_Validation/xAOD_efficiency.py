from ROOT import *
from time import time
import argparse
from AtlasStyle import *

gROOT.SetBatch(True)
gStyle.SetPalette(1)
gStyle.SetOptStat(1)



def histLabelsEndCap(hist):
	hist.GetXaxis().SetBinLabel(1, "PIX0"); hist.GetXaxis().SetBinLabel(2, "PIX1"); hist.GetXaxis().SetBinLabel(3, "PIX2")
	hist.GetXaxis().SetBinLabel(4, "SCT0"); hist.GetXaxis().SetBinLabel(5, "SCT1"); hist.GetXaxis().SetBinLabel(6, "SCT2")
	hist.GetXaxis().SetBinLabel(7, "SCT3"); hist.GetXaxis().SetBinLabel(8, "SCT4"); hist.GetXaxis().SetBinLabel(9, "SCT5")
	hist.GetXaxis().SetBinLabel(10, "SCT6"); hist.GetXaxis().SetBinLabel(11, "SCT7"); hist.GetXaxis().SetBinLabel(12, "SCT8")
	return

def histLabelsBarrel(hist):
	hist.GetXaxis().SetBinLabel(1, "IBL"); hist.GetXaxis().SetBinLabel(2, "PIX0"); hist.GetXaxis().SetBinLabel(3, "PIX1")
	hist.GetXaxis().SetBinLabel(4, "PIX2"); hist.GetXaxis().SetBinLabel(5, "SCT0"); hist.GetXaxis().SetBinLabel(6, "SCT1")
	hist.GetXaxis().SetBinLabel(7, "SCT2"); hist.GetXaxis().SetBinLabel(8, "SCT3")
	return

def histLabelsInclusive(hist):
	hist.GetXaxis().SetBinLabel(1, "IBL"); hist.GetXaxis().SetBinLabel(2, "PIXB0"); hist.GetXaxis().SetBinLabel(3, "PIXB1")
	hist.GetXaxis().SetBinLabel(4, "PIXB2"); hist.GetXaxis().SetBinLabel(5, "PIXEC0"); hist.GetXaxis().SetBinLabel(6, "PIXEC1") 
	hist.GetXaxis().SetBinLabel(7, "PIXEC2"); hist.GetXaxis().SetBinLabel(8, "SCTB0"); hist.GetXaxis().SetBinLabel(9, "SCTB1") 
	hist.GetXaxis().SetBinLabel(10, "SCTB2"); hist.GetXaxis().SetBinLabel(11, "SCTB3"); hist.GetXaxis().SetBinLabel(12, "SCTEC0")
	hist.GetXaxis().SetBinLabel(13, "SCTEC1"); hist.GetXaxis().SetBinLabel(14, "SCTEC2"); hist.GetXaxis().SetBinLabel(15, "SCTEC3")
	hist.GetXaxis().SetBinLabel(16, "SCTEC4"); hist.GetXaxis().SetBinLabel(17, "SCTEC5"); hist.GetXaxis().SetBinLabel(18, "SCTE6")
	hist.GetXaxis().SetBinLabel(19, "SCTEC7"); hist.GetXaxis().SetBinLabel(20, "SCTEC8")
	return

def hist2dSettings(hist):
	hist.GetZaxis().SetTitleOffset(0.75)
	hist.SetMaximum(1)

start_time = time()


parser=argparse.ArgumentParser()
parser.add_argument("--file",   type=str,  required=False, dest="input_file", help="Specify an input file")
parser.add_argument("--tree",   type=str,  required=False, default="tracks", dest="input_tree", help="Select a tree within the file")
parser.add_argument("--m",      type=bool, required=False, default=False, dest="calc_m", help="Specity True if you wan to calculate mass")
parser.add_argument("--test",   type=bool, required=False, default=False, dest="test_events", help="Flag --test True to only run over 100 events")
parser.add_argument("--output", type=str,  required=False, default="mydXAOD_analysis_output_BLS.root", dest="output_name", help="Specify output file name")
parser.add_argument("--data",   type=bool,  required=False, default=False, dest="event_type", help="Flag --data True for data events")
args = parser.parse_args()


input_file = args.input_file
input_tree = args.input_tree
test_events = args.test_events
calc_m = args.calc_m
output_file = args.output_name
isData = args.event_type

ptmin = 0; ptmax = 20; ptbins = 50;
lptmin = 0; lptmax = 10; lptbins = 20;
hptmin = 0; hptmax = 100; hptbins = 20;
etamin = -2.5; etamax = 2.5; etabins = 50;
phimin = -3.2; phimax = 3.2; phibins = 50;
mmin = 20; mmax = 0; mbins = 50;
d0min = -10; d0max = 10; d0bins = 50;
z0min = -110; z0max = 110; z0bins = 50;
qopmin = -0.001; qopmax = 0.001; qopbins = 50;
chargemin = -2.5; chargemax = 2.5; chargebins = 5;
chimin = 0; chimax = 100; chibins = 50;

ptbiasbins = 50;  ptbiasmin = -0.6;  ptbiasmax = 0.6;
etabiasbins = 50; etabiasmin = -0.05; etabiasmax = 0.05;
phibiasbins = 50; phibiasmin = -0.05; phibiasmax = 0.05;
d0biasbins = 50;  d0biasmin = -0.6;  d0biasmax = 0.6;


print("Create Histograms")


h_ftk_reco_deltaR        = TH1F("h_ftk_reco_deltaR", "h_ftk_reco_deltaR;deltaR;Events", 20, 0, 0.5)
h_ftk_ftkrefit_deltaR    = TH1F("h_ftk_ftkrefit_deltaR", "h_ftk_ftkrefit_deltaR;deltaR;Events", 20, 0, 0.5)
h_truth_reco_deltaR      = TH1F("h_truth_reco_deltaR", "h_truth_reco_deltaR;deltaR;Events", 20, 0, 0.5)
h_ftk_truth_deltaR       = TH1F("h_ftk_truth_deltaR", "h_ftk_truth_deltaR;deltaR;Events", 20, 0, 0.5)
h_ftk_refit_truth_deltaR = TH1F("h_ftk_refit_truth_deltaR", "h_ftk_refit_truth_deltaR;deltaR;Events", 20, 0, 0.5)
h_ftk_refit_reco_deltaR  = TH1F("h_ftk_refit_reco_deltaR", "h_ftk_refit_reco_deltaR;deltaR;Events", 20, 0, 0.5)

if isData == False:
	h_truth_pt  =  TH1F("h_truth_pt",  "h_truth_pt; p_{T};Events;",  ptbins, ptmin, ptmax)
	h_truth_eta =  TH1F("h_truth_eta", "h_truth_eta; #eta;Events;", etabins, etamin, etamax)
	h_truth_phi =  TH1F("h_truth_phi", "h_truth_phi; #phi;Events;", phibins, phimin, phimax)
	h_truth_m   =  TH1F("h_truth_m",   "h_truth_m; mass;Events;",   mbins, mmin, mmax)
	h_truth_d0  =  TH1F("h_truth_d0",  "h_truth_d0; d0; Events",  d0bins, d0min, d0max)
	h_truth_z0  =  TH1F("h_truth_z0",  "h_truth_z0; z0; Events;",  z0bins, z0min, z0max)
	h_truth_qop =  TH1F("h_truth_qop", "h_truth_qop", qopbins, qopmin, qopmax)
	h_truth_charge  =  TH1F("h_truth_charge",  "h_truth_charge",  chargebins, chargemin, chargemax)
	h_truth_EtaPhi = TH2F("h_truth_EtaPhi", "h_truth_EtaPhi;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)

h_reco_accepted_pt   =  TH1F("h_reco_accepted_pt",  "h_reco_accepted_pt; p_{T};Events;",  ptbins, ptmin, ptmax)
h_reco_accepted_eta  =  TH1F("h_reco_accepted_eta", "h_reco_accepted_eta; #eta;Events;", etabins, etamin, etamax)
h_reco_accepted_eta_barrel  =  TH1F("h_reco_accepted_eta_barrel", "h_reco_accepted_eta_barrel; #eta;Events;", etabins, etamin, etamax)
h_reco_accepted_eta_endcap  =  TH1F("h_reco_accepted_eta_endcap", "h_reco_accepted_eta_endcap; #eta;Events;", etabins, etamin, etamax)
h_reco_accepted_phi  =  TH1F("h_reco_accepted_phi", "h_reco_accepted_phi; #phi;Events;", phibins, phimin, phimax)
h_reco_accepted_phi_barrel  =  TH1F("h_reco_accepted_phi_barrel", "h_reco_accepted_phi_barrel; #phi;Events;", phibins, phimin, phimax)
h_reco_accepted_phi_endcap  =  TH1F("h_reco_accepted_phi_endcap", "h_reco_accepted_phi_endcap; #phi;Events;", phibins, phimin, phimax)
h_reco_accepted_m    =  TH1F("h_reco_accepted_m",   "h_reco_accepted_m; mass;Events;",   mbins, mmin, mmax)
h_reco_accepted_d0   =  TH1F("h_reco_accepted_d0",  "h_reco_accepted_d0; d0; Events",  d0bins, d0min, d0max)
h_reco_accepted_d0_barrel   =  TH1F("h_reco_accepted_d0_barrel",  "h_reco_accepted_d0; d0; Events",  d0bins, d0min, d0max)
h_reco_accepted_d0_endcap   =  TH1F("h_reco_accepted_d0_endcap",  "h_reco_accepted_d0; d0; Events",  d0bins, d0min, d0max)
h_reco_accepted_z0   =  TH1F("h_reco_accepted_z0",  "h_reco_accepted_z0; z0; Events;",  z0bins, z0min, z0max)
h_reco_accepted_z0_barrel   =  TH1F("h_reco_accepted_z0_barrel",  "h_reco_accepted_z0_barrel; z0; Events;",  z0bins, z0min, z0max)
h_reco_accepted_z0_endcap   =  TH1F("h_reco_accepted_z0_endcap",  "h_reco_accepted_z0_endcap; z0; Events;",  z0bins, z0min, z0max)
h_reco_accepted_qop  =  TH1F("h_reco_accepted_qop", "h_reco_accepted_qop", qopbins, qopmin, qopmax)
h_reco_accepted_charge   =  TH1F("h_reco_accepted_charge",  "h_reco_accepted_charge",  chargebins, chargemin, chargemax)
h_reco_accepted_chi2     =  TH1F("h_reco_accepted_chi2",    "h_reco_accepted_chi2",    chibins, chimin, chimax)
h_reco_accepted_EtaPhi = TH2F("h_reco_accepted_EtaPhi", "h_reco_accepted_EtaPhi;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)

h_reco_inclusive_pt   =  TH1F("h_reco_inclusive_pt",  "h_reco_inclusive_pt; p_{T};Events;",  ptbins, ptmin, ptmax)
h_reco_inclusive_eta  =  TH1F("h_reco_inclusive_eta", "h_reco_inclusive_eta; #eta;Events;", etabins, etamin, etamax)
h_reco_inclusive_phi  =  TH1F("h_reco_inclusive_phi", "h_reco_inclusive_phi; #phi;Events;", phibins, phimin, phimax)
h_reco_inclusive_m    =  TH1F("h_reco_inclusive_m",   "h_reco_inclusive_m; mass;Events;",   mbins, mmin, mmax)
h_reco_inclusive_d0   =  TH1F("h_reco_inclusive_d0",  "h_reco_inclusive_d0; d0; Events",  d0bins, d0min, d0max)
h_reco_inclusive_z0   =  TH1F("h_reco_inclusive_z0",  "h_reco_inclusive_z0; z0; Events;",  z0bins, z0min, z0max)
h_reco_inclusive_qop  =  TH1F("h_reco_inclusive_qop", "h_reco_inclusive_qop", qopbins, qopmin, qopmax)
h_reco_inclusive_charge   =  TH1F("h_reco_inclusive_charge",  "h_reco_inclusive_charge",  chargebins, chargemin, chargemax)
h_reco_inclusive_chi2     =  TH1F("h_reco_inclusive_chi2",    "h_reco_inclusive_chi2",    chibins, chimin, chimax)
h_reco_inclusive_EtaPhi = TH2F("h_reco_inclusive_EtaPhi", "h_reco_inclusive_EtaPhi;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)

h_ftk_accepted_pt   =  TH1F("h_ftk_accepted_pt",  "h_ftk_accepted_pt; p_{T};Events;",  ptbins, ptmin, ptmax)
h_ftk_accepted_eta  =  TH1F("h_ftk_accepted_eta", "h_ftk_accepted_eta; #eta;Events;", etabins, etamin, etamax)
h_ftk_accepted_eta_barrel  =  TH1F("h_ftk_accepted_eta_barrel", "h_ftk_accepted_eta_barrel; #eta;Events;", etabins, etamin, etamax)
h_ftk_accepted_eta_endcap  =  TH1F("h_ftk_accepted_eta_endcap", "h_ftk_accepted_eta_endcap; #eta;Events;", etabins, etamin, etamax)
h_ftk_accepted_phi  =  TH1F("h_ftk_accepted_phi", "h_ftk_accepted_phi; #phi;Events;", phibins, phimin, phimax)
h_ftk_accepted_phi_barrel  =  TH1F("h_ftk_accepted_phi_barrel", "h_ftk_accepted_phi_barrel; #phi;Events;", phibins, phimin, phimax)
h_ftk_accepted_phi_endcap  =  TH1F("h_ftk_accepted_phi_endcap", "h_ftk_accepted_phi_endcap; #phi;Events;", phibins, phimin, phimax)
h_ftk_accepted_m    =  TH1F("h_ftk_accepted_m",   "h_ftk_accepted_m; mass;Events;",   mbins, mmin, mmax)
h_ftk_accepted_d0   =  TH1F("h_ftk_accepted_d0",  "h_ftk_accepted_d0; d0; Events",  d0bins, d0min, d0max)
h_ftk_accepted_d0_barrel   =  TH1F("h_ftk_accepted_d0_barrel",  "h_ftk_accepted_d0; d0; Events",  d0bins, d0min, d0max)
h_ftk_accepted_d0_endcap   =  TH1F("h_ftk_accepted_d0_endcap",  "h_ftk_accepted_d0; d0; Events",  d0bins, d0min, d0max)
h_ftk_accepted_corrected_d0   =  TH1F("h_ftk_accepted_corrected_d0",  "h_ftk_accepted_corrected_d0; d0; Events",  d0bins, d0min, d0max)
h_ftk_accepted_z0   =  TH1F("h_ftk_accepted_z0",  "h_ftk_accepted_z0; z0; Events;",  z0bins, z0min, z0max)
h_ftk_accepted_z0_barrel   =  TH1F("h_ftk_accepted_z0_barrel",  "h_ftk_accepted_z0_barrel; z0; Events;",  z0bins, z0min, z0max)
h_ftk_accepted_z0_endcap   =  TH1F("h_ftk_accepted_z0_endcap",  "h_ftk_accepted_z0_endcap; z0; Events;",  z0bins, z0min, z0max)
h_ftk_accepted_qop  =  TH1F("h_ftk_accepted_qop", "h_ftk_accepted_qop", qopbins, qopmin, qopmax)
h_ftk_accepted_charge   =  TH1F("h_ftk_accepted_charge",  "h_ftk_accepted_charge",  chargebins, chargemin, chargemax)
h_ftk_accepted_chi2     =  TH1F("h_ftk_accepted_chi2",    "h_ftk_accepted_chi2",    chibins, chimin, chimax)
h_ftk_accepted_EtaPhi = TH2F("h_ftk_accepted_EtaPhi", "h_ftk_accepted_EtaPhi;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)

h_ftk_inclusive_pt   =  TH1F("h_ftk_inclusive_pt",  "h_ftk_inclusive_pt; p_{T};Events;",  ptbins, ptmin, ptmax)
h_ftk_inclusive_eta  =  TH1F("h_ftk_inclusive_eta", "h_ftk_inclusive_eta; #eta;Events;", etabins, etamin, etamax)
h_ftk_inclusive_phi  =  TH1F("h_ftk_inclusive_phi", "h_ftk_inclusive_phi; #phi;Events;", phibins, phimin, phimax)
h_ftk_inclusive_m    =  TH1F("h_ftk_inclusive_m",   "h_ftk_inclusive_m; mass;Events;",   mbins, mmin, mmax)
h_ftk_inclusive_d0   =  TH1F("h_ftk_inclusive_d0",  "h_ftk_inclusive_d0; d0; Events",  d0bins, d0min, d0max)
h_ftk_inclusive_corrected_d0   =  TH1F("h_ftk_inclusive_corrected_d0",  "h_ftk_inclusive_corrected_d0; d0; Events",  d0bins, d0min, d0max)
h_ftk_inclusive_z0   =  TH1F("h_ftk_inclusive_z0",  "h_ftk_inclusive_z0; z0; Events;",  z0bins, z0min, z0max)
h_ftk_inclusive_qop  =  TH1F("h_ftk_inclusive_qop", "h_ftk_inclusive_qop", qopbins, qopmin, qopmax)
h_ftk_inclusive_charge   =  TH1F("h_ftk_inclusive_charge",  "h_ftk_inclusive_charge",  chargebins, chargemin, chargemax)
h_ftk_inclusive_chi2     =  TH1F("h_ftk_inclusive_chi2",    "h_ftk_inclusive_chi2",    chibins, chimin, chimax)
h_ftk_inclusive_EtaPhi = TH2F("h_ftk_inclusive_EtaPhi", "h_ftk_inclusive_EtaPhi;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
# print("BLS test 1")
h_ftk_refit_accepted_pt   =  TH1F("h_ftk_refit_accepted_pt",  "h_ftk_refit_accepted_pt; p_{T};Events;",  ptbins, ptmin, ptmax)
h_ftk_refit_accepted_eta  =  TH1F("h_ftk_refit_accepted_eta", "h_ftk_refit_accepted_eta; #eta;Events;", etabins, etamin, etamax)
h_ftk_refit_accepted_eta_barrel  =  TH1F("h_ftk_refit_accepted_eta_barrel", "h_ftk_refit_accepted_eta_barrel; #eta;Events;", etabins, etamin, etamax)
h_ftk_refit_accepted_eta_endcap  =  TH1F("h_ftk_refit_accepted_eta_endcap", "h_ftk_refit_accepted_eta_endcap; #eta;Events;", etabins, etamin, etamax)
h_ftk_refit_accepted_phi  =  TH1F("h_ftk_refit_accepted_phi", "h_ftk_refit_accepted_phi; #phi;Events;", phibins, phimin, phimax)
h_ftk_refit_accepted_phi_barrel  =  TH1F("h_ftk_refit_accepted_phi_barrel", "h_ftk_refit_accepted_phi_barrel; #phi;Events;", phibins, phimin, phimax)
h_ftk_refit_accepted_phi_endcap  =  TH1F("h_ftk_refit_accepted_phi_endcap", "h_ftk_refit_accepted_phi_endcap; #phi;Events;", phibins, phimin, phimax)
h_ftk_refit_accepted_m    =  TH1F("h_ftk_refit_accepted_m",   "h_ftk_refit_accepted_m; mass;Events;",   mbins, mmin, mmax)
h_ftk_refit_accepted_d0   =  TH1F("h_ftk_refit_accepted_d0",  "h_ftk_refit_accepted_d0; d0; Events",  d0bins, d0min, d0max)
h_ftk_refit_accepted_d0_barrel   =  TH1F("h_ftk_refit_accepted_d0_barrel",  "h_ftk_refit_accepted_d0; d0; Events",  d0bins, d0min, d0max)
h_ftk_refit_accepted_d0_endcap   =  TH1F("h_ftk_refit_accepted_d0_endcap",  "h_ftk_refit_accepted_d0; d0; Events",  d0bins, d0min, d0max)
h_ftk_refit_accepted_z0   =  TH1F("h_ftk_refit_accepted_z0",  "h_ftk_refit_accepted_z0; z0; Events;",  z0bins, z0min, z0max)
h_ftk_refit_accepted_z0_barrel   =  TH1F("h_ftk_refit_accepted_z0_barrel",  "h_ftk_refit_accepted_z0_barrel; z0; Events;",  z0bins, z0min, z0max)
h_ftk_refit_accepted_z0_endcap   =  TH1F("h_ftk_refit_accepted_z0_endcap",  "h_ftk_refit_accepted_z0_endcap; z0; Events;",  z0bins, z0min, z0max)
h_ftk_refit_accepted_qop  =  TH1F("h_ftk_refit_accepted_qop", "h_ftk_refit_accepted_qop", qopbins, qopmin, qopmax)
h_ftk_refit_accepted_charge   =  TH1F("h_ftk_refit_accepted_charge",  "h_ftk_refit_accepted_charge",  chargebins, chargemin, chargemax)
h_ftk_refit_accepted_chi2     =  TH1F("h_ftk_refit_accepted_chi2",    "h_ftk_refit_accepted_chi2",    chibins, chimin, chimax)
h_ftk_refit_accepted_EtaPhi = TH2F("h_ftk_refit_accepted_EtaPhi", "h_ftk_refit_accepted_EtaPhi;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)


h_ftk_refit_inclusive_pt   =  TH1F("h_ftk_refit_inclusive_pt",  "h_ftk_refit_inclusive_pt; p_{T};Events;",  ptbins, ptmin, ptmax)
h_ftk_refit_inclusive_eta  =  TH1F("h_ftk_refit_inclusive_eta", "h_ftk_refit_inclusive_eta; #eta;Events;", etabins, etamin, etamax)
h_ftk_refit_inclusive_phi  =  TH1F("h_ftk_refit_inclusive_phi", "h_ftk_refit_inclusive_phi; #phi;Events;", phibins, phimin, phimax)
h_ftk_refit_inclusive_m    =  TH1F("h_ftk_refit_inclusive_m",   "h_ftk_refit_inclusive_m; mass;Events;",   mbins, mmin, mmax)
h_ftk_refit_inclusive_d0   =  TH1F("h_ftk_refit_inclusive_d0",  "h_ftk_refit_inclusive_d0; d0; Events",  d0bins, d0min, d0max)
h_ftk_refit_inclusive_z0   =  TH1F("h_ftk_refit_inclusive_z0",  "h_ftk_refit_inclusive_z0; z0; Events;",  z0bins, z0min, z0max)
h_ftk_refit_inclusive_qop  =  TH1F("h_ftk_refit_inclusive_qop", "h_ftk_refit_inclusive_qop", qopbins, qopmin, qopmax)
h_ftk_refit_inclusive_charge   =  TH1F("h_ftk_refit_inclusive_charge",  "h_ftk_refit_inclusive_charge",  chargebins, chargemin, chargemax)
h_ftk_refit_inclusive_chi2     =  TH1F("h_ftk_refit_inclusive_chi2",    "h_ftk_refit_inclusive_chi2",    chibins, chimin, chimax)
h_ftk_refit_inclusive_EtaPhi = TH2F("h_ftk_refit_inclusive_EtaPhi", "h_ftk_refit_inclusive_EtaPhi;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)

if isData == False:
	h_reco_truthMatched_pt_bias  = TH1F("h_reco_truthMatched_pt_bias",  "h_reco_truthMatched_pt_bias; Reco p_{T} - Truth p_{T};Events;",  ptbiasbins, ptbiasmin, ptbiasmax)
	h_reco_truthMatched_eta_bias = TH1F("h_reco_truthMatched_eta_bias", "h_reco_truthMatched_eta_bias; FTKrefit #eta - Reco #eta;Events;", etabiasbins, etabiasmin, etabiasmax)
	h_reco_truthMatched_phi_bias = TH1F("h_reco_truthMatched_phi_bias", "h_reco_truthMatched_phi_bias; FTKrefit #phi - Reco #phi;Events;", phibiasbins, phibiasmin, phibiasmax)
	h_reco_truthMatched_d0_bias  = TH1F("h_reco_truthMatched_d0_bias",  "h_reco_truthMatched_d0_bias; FTKrefit d0 - Reco d0;Events;",  d0biasbins, d0biasmin, d0biasmax)
	h_truth_recoMatch_track_eta  = TH1F("h_truth_recoMatch_track_eta",  "h_truth_recoMatch_track_eta; #eta;Events;",  etabins, etamin, etamax)
	h_truth_recoMatch_track_phi  = TH1F("h_truth_recoMatch_track_phi",  "h_truth_recoMatch_track_phi; #phi;Events;",  phibins, phimin, phimax)
	h_reco_truthMatch_track_eta  = TH1F("h_reco_truthMatch_track_eta",  "h_reco_truthMatch_track_eta; #eta;Events;",  etabins, etamin, etamax)
	h_reco_truthMatch_track_phi  = TH1F("h_reco_truthMatch_track_phi",  "h_reco_truthMatch_track_phi; #phi;Events;",  phibins, phimin, phimax)
	h_truth_recoMatch_track_pt   = TH1F("h_truth_recoMatch_track_pt",   "h_truth_recoMatch_track_pt; p_{T};Events;",   ptbins, ptmin, ptmax)
	h_truth_recoMatch_track_d0   = TH1F("h_truth_recoMatch_track_d0",   "h_truth_recoMatch_track_d0; d0; Events",   d0bins, d0min, d0max)
	h_truth_recoMatch_track_z0   = TH1F("h_truth_recoMatch_track_z0",   "h_truth_recoMatch_track_z0; z0; Events;",   z0bins, z0min, z0max)
	h_truth_recoMatch_track_EtaPhi = TH2F("h_truth_recoMatch_track_EtaPhi", "h_truth_recoMatch_track_EtaPhi;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)


	h_truth_ftk_Matched_pt_bias  = TH1F("h_truth_ftk_Matched_pt_bias",  "h_truth_ftk_Matched_pt_bias; FTK p_{T} - Truth p_{T};Events;",  ptbiasbins, ptbiasmin, ptbiasmax)
	h_truth_ftk_Matched_eta_bias = TH1F("h_truth_ftk_Matched_eta_bias", "h_truth_ftk_Matched_eta_bias; FTKrefit #eta - Reco #eta;Events;", etabiasbins, etabiasmin, etabiasmax)
	h_truth_ftk_Matched_phi_bias = TH1F("h_truth_ftk_Matched_phi_bias", "h_truth_ftk_Matched_phi_bias; FTKrefit #phi - Reco #phi;Events;", phibiasbins, phibiasmin, phibiasmax)
	h_truth_ftk_Matched_d0_bias  = TH1F("h_truth_ftk_Matched_d0_bias",  "h_truth_ftk_Matched_d0_bias; FTKrefit d0 - Reco d0;Events;",  d0biasbins, d0biasmin, d0biasmax)
	h_truth_ftk_Matched_corrected_d0_bias  = TH1F("h_truth_ftk_Matched_corrected_d0_bias",  "h_truth_ftk_Matched_corrected_d0_bias",  d0biasbins, d0biasmin, d0biasmax)
	h_ftk_truthMatch_track_eta   = TH1F("h_ftk_truthMatch_track_eta",   "h_ftk_truthMatch_track_eta; #eta;Events;",   etabins, etamin, etamax)
	h_ftk_truthMatch_track_phi   = TH1F("h_ftk_truthMatch_track_phi",   "h_ftk_truthMatch_track_phi; #phi;Events;",   phibins, phimin, phimax)
	h_truth_ftkMatch_track_eta   = TH1F("h_truth_ftkMatch_track_eta",   "h_truth_ftkMatch_track_eta; #eta;Events;",   etabins, etamin, etamax)
	h_truth_ftkMatch_track_phi   = TH1F("h_truth_ftkMatch_track_phi",   "h_truth_ftkMatch_track_phi; #phi;Events;",   phibins, phimin, phimax)
	h_ftk_truthMatch_track_pt    = TH1F("h_ftk_truthMatch_track_pt",    "h_ftk_truthMatch_track_pt; p_{T};Events;",    ptbins, ptmin, ptmax)
	h_ftk_truthMatch_track_d0    = TH1F("h_ftk_truthMatch_track_d0",    "h_ftk_truthMatch_track_d0; d0; Events",    d0bins, d0min, d0max)
	# h_ftk_truthMatch_track_corrected_d0    = TH1F("h_ftk_truthMatch_track_corrected_d0",    "h_ftk_truthMatch_track_corrected_d0",    d0bins, d0min, d0max)
	h_ftk_truthMatch_track_z0    = TH1F("h_ftk_truthMatch_track_z0",    "h_ftk_truthMatch_track_z0; z0; Events;",    z0bins, z0min, z0max)
	h_ftk_truthMatch_track_EtaPhi = TH2F("h_ftk_truthMatch_track_EtaPhi", "h_ftk_truthMatch_track_EtaPhi;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)


	h_truth_ftk_refitMatched_pt_bias  = TH1F("h_truth_ftk_refitMatched_pt_bias",  "h_truth_ftk_refitMatched_pt_bias; FTKrefit p_{T} - Truth p_{T};Events;",  ptbiasbins, ptbiasmin, ptbiasmax)
	h_truth_ftk_refitMatched_eta_bias = TH1F("h_truth_ftk_refitMatched_eta_bias", "h_truth_ftk_refitMatched_eta_bias; FTKrefit #eta - Reco #eta;Events;", etabiasbins, etabiasmin, etabiasmax)
	h_truth_ftk_refitMatched_phi_bias = TH1F("h_truth_ftk_refitMatched_phi_bias", "h_truth_ftk_refitMatched_phi_bias; FTKrefit #phi - Reco #phi;Events;", phibiasbins, phibiasmin, phibiasmax)
	h_truth_ftk_refitMatched_d0_bias  = TH1F("h_truth_ftk_refitMatched_d0_bias",  "h_truth_ftk_refitMatched_d0_bias; FTKrefit d0 - Reco d0;Events;",  d0biasbins, d0biasmin, d0biasmax)
	h_ftk_refit_truthMatch_track_eta  = TH1F("h_ftk_refit_truthMatch_track_eta",  "h_ftk_refit_truthMatch_track_eta; #eta;Events;",  etabins, etamin, etamax)
	h_ftk_refit_truthMatch_track_phi  = TH1F("h_ftk_refit_truthMatch_track_phi",  "h_ftk_refit_truthMatch_track_phi; #phi;Events;",  phibins, phimin, phimax)
	h_truth_ftkrefitMatch_track_eta   = TH1F("h_truth_ftkrefitMatch_track_eta",   "h_truth_ftkrefitMatch_track_eta; #eta;Events;",   etabins, etamin, etamax)
	h_truth_ftkrefitMatch_track_phi   = TH1F("h_truth_ftkrefitMatch_track_phi",   "h_truth_ftkrefitMatch_track_phi; #phi;Events;",   phibins, phimin, phimax)
	h_ftk_refit_truthMatch_track_pt   = TH1F("h_ftk_refit_truthMatch_track_pt",   "h_ftk_refit_truthMatch_track_pt; p_{T};Events;",   ptbins, ptmin, ptmax)
	h_ftk_refit_truthMatch_track_d0   = TH1F("h_ftk_refit_truthMatch_track_d0",   "h_ftk_refit_truthMatch_track_d0; d0; Events",   d0bins, d0min, d0max)
	h_ftk_refit_truthMatch_track_z0   = TH1F("h_ftk_refit_truthMatch_track_z0",   "h_ftk_refit_truthMatch_track_z0; z0; Events;",   z0bins, z0min, z0max)
	h_ftk_refit_truthMatch_track_EtaPhi = TH2F("h_ftk_refit_truthMatch_track_EtaPhi", "h_ftk_refit_truthMatch_track_EtaPhi;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)


h_reco_ftkMatched_pt_bias  = TH1F("h_reco_ftkMatched_pt_bias",  "h_reco_ftkMatched_pt_bias; FTK p_{T} - Reco p_{T};Events;",  ptbiasbins, ptbiasmin, ptbiasmax)
h_reco_ftkMatched_eta_bias = TH1F("h_reco_ftkMatched_eta_bias", "h_reco_ftkMatched_eta_bias; FTKrefit #eta - Reco #eta;Events;", etabiasbins, etabiasmin, etabiasmax)
h_reco_ftkMatched_phi_bias = TH1F("h_reco_ftkMatched_phi_bias", "h_reco_ftkMatched_phi_bias; FTKrefit #phi - Reco #phi;Events;", phibiasbins, phibiasmin, phibiasmax)
h_reco_ftkMatched_d0_bias  = TH1F("h_reco_ftkMatched_d0_bias",  "h_reco_ftkMatched_d0_bias; FTKrefit d0 - Reco d0;Events;",  d0biasbins, d0biasmin, d0biasmax)
h_reco_ftkMatched_corrected_d0_bias  = TH1F("h_reco_ftkMatched_corrected_d0_bias",  "h_reco_ftkMatched_corrected_d0_bias",  d0biasbins, d0biasmin, d0biasmax)
h_ftk_recoMatch_track_eta  = TH1F("h_ftk_recoMatch_track_eta",  "h_ftk_recoMatch_track_eta; #eta;Events;",  etabins, etamin, etamax)
h_ftk_recoMatch_track_phi  = TH1F("h_ftk_recoMatch_track_phi",  "h_ftk_recoMatch_track_phi; #phi;Events;",  phibins, phimin, phimax)
h_reco_ftkMatch_track_eta  = TH1F("h_reco_ftkMatch_track_eta",  "h_reco_ftkMatch_track_eta; #eta;Events;",  etabins, etamin, etamax)
h_reco_ftkMatch_track_phi  = TH1F("h_reco_ftkMatch_track_phi",  "h_reco_ftkMatch_track_phi; #phi;Events;",  phibins, phimin, phimax)
h_ftk_recoMatch_track_pt   = TH1F("h_ftk_recoMatch_track_pt",   "h_ftk_recoMatch_track_pt; p_{T};Events;",   ptbins, ptmin, ptmax)
h_ftk_recoMatch_track_d0   = TH1F("h_ftk_recoMatch_track_d0",   "h_ftk_recoMatch_track_d0; d0; Events",   d0bins, d0min, d0max)
# h_ftk_recoMatch_track_corrected_d0   = TH1F("h_ftk_recoMatch_track_corrected_d0",   "h_ftk_recoMatch_track_corrected_d0",   d0bins, d0min, d0max)
h_ftk_recoMatch_track_z0   = TH1F("h_ftk_recoMatch_track_z0",   "h_ftk_recoMatch_track_z0; z0; Events;",   z0bins, z0min, z0max)
h_ftk_recoMatch_track_EtaPhi = TH2F("h_ftk_recoMatch_track_EtaPhi", "h_ftk_recoMatch_track_EtaPhi;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)


h_reco_ftk_refitMatched_pt_bias  = TH1F("h_reco_ftk_refitMatched_pt_bias",  "h_reco_ftk_refitMatched_pt_bias; FTKrefit p_{T} - Reco p_{T};Events;",  ptbiasbins, ptbiasmin, ptbiasmax)
h_reco_ftk_refitMatched_eta_bias = TH1F("h_reco_ftk_refitMatched_eta_bias", "h_reco_ftk_refitMatched_eta_bias; FTKrefit #eta - Reco #eta;Events;", etabiasbins, etabiasmin, etabiasmax)
h_reco_ftk_refitMatched_phi_bias = TH1F("h_reco_ftk_refitMatched_phi_bias", "h_reco_ftk_refitMatched_phi_bias; FTKrefit #phi - Reco #phi;Events;", phibiasbins, phibiasmin, phibiasmax)
h_reco_ftk_refitMatched_d0_bias  = TH1F("h_reco_ftk_refitMatched_d0_bias",  "h_reco_ftk_refitMatched_d0_bias; FTKrefit d0 - Reco d0;Events;",  d0biasbins, d0biasmin, d0biasmax)
h_ftk_refit_recoMatch_track_eta  = TH1F("h_ftk_refit_recoMatch_track_eta",  "h_ftk_refit_recoMatch_track_eta; #eta;Events;",  etabins, etamin, etamax)
h_ftk_refit_recoMatch_track_phi  = TH1F("h_ftk_refit_recoMatch_track_phi",  "h_ftk_refit_recoMatch_track_phi; #phi;Events;",  phibins, phimin, phimax)
h_reco_ftkrefitMatch_track_eta   = TH1F("h_reco_ftkrefitMatch_track_eta",   "h_reco_ftkrefitMatch_track_eta; #eta;Events;",   etabins, etamin, etamax)
h_reco_ftkrefitMatch_track_phi   = TH1F("h_reco_ftkrefitMatch_track_phi",   "h_reco_ftkrefitMatch_track_phi; #phi;Events;",   phibins, phimin, phimax)
h_ftk_refit_recoMatch_track_pt = TH1F("h_ftk_refit_recoMatch_track_pt", "h_ftk_refit_recoMatch_track_pt; p_{T};Events;", ptbins, ptmin, ptmax)
h_ftk_refit_recoMatch_track_d0 = TH1F("h_ftk_refit_recoMatch_track_d0", "h_ftk_refit_recoMatch_track_d0; d0; Events", d0bins, d0min, d0max)
h_ftk_refit_recoMatch_track_z0 = TH1F("h_ftk_refit_recoMatch_track_z0", "h_ftk_refit_recoMatch_track_z0; z0; Events;", z0bins, z0min, z0max)
h_ftk_refit_recoMatch_track_EtaPhi = TH2F("h_ftk_refit_recoMatch_track_EtaPhi", "h_ftk_refit_recoMatch_track_EtaPhi;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)


h_reco_accepted_hitPattern_EndCap = TH1I("h_reco_accepted_hitPattern_EndCap", "Reco EndCap Hit Pattern", 12, 0, 12)
h_ftk_accepted_hitPattern_EndCap = TH1I("h_ftk_accepted_hitPattern_EndCap", "FTK EndCap Hit Pattern", 12, 0, 12)
h_ftk_refit_accepted_hitPattern_EndCap = TH1I("h_ftk_refit_accepted_hitPattern_EndCap", "FTK Refit EndCap Hit Pattern", 12, 0, 12)
h_reco_accepted_hitPattern_Barrel = TH1I("h_reco_accepted_hitPattern_Barrel", "Reco Barrel Hit Pattern", 8, 0, 8)
h_ftk_accepted_hitPattern_Barrel = TH1I("h_ftk_accepted_hitPattern_Barrel", "FTK Barrel Hit Pattern", 8, 0, 8)
h_ftk_refit_accepted_hitPattern_Barrel = TH1I("h_ftk_refit_accepted_hitPattern_Barrel", "FTK Refit Barrel Hit Pattern", 8, 0, 8)
h_reco_accepted_hitPattern = TH1I("h_reco_accepted_hitPattern", "Reco Hit Pattern", 20, 0, 20)
h_ftk_accepted_hitPattern = TH1I("h_ftk_accepted_hitPattern", "FTK Hit Pattern", 20, 0, 20)
h_ftk_refit_accepted_hitPattern = TH1I("h_ftk_refit_accepted_hitPattern", "FTK Refit Hit Pattern", 20, 0, 20)

# print("BLS test 2")
h_ftk_refit_accepted_EtaPhi0 = TH2F("h_ftk_refit_accepted_EtaPhi0", "h_ftk_refit_accepted_EtaPhi0;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi1 = TH2F("h_ftk_refit_accepted_EtaPhi1", "h_ftk_refit_accepted_EtaPhi1;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi2 = TH2F("h_ftk_refit_accepted_EtaPhi2", "h_ftk_refit_accepted_EtaPhi2;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi3 = TH2F("h_ftk_refit_accepted_EtaPhi3", "h_ftk_refit_accepted_EtaPhi3;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi4 = TH2F("h_ftk_refit_accepted_EtaPhi4", "h_ftk_refit_accepted_EtaPhi4;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi5 = TH2F("h_ftk_refit_accepted_EtaPhi5", "h_ftk_refit_accepted_EtaPhi5;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi6 = TH2F("h_ftk_refit_accepted_EtaPhi6", "h_ftk_refit_accepted_EtaPhi6;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi7 = TH2F("h_ftk_refit_accepted_EtaPhi7", "h_ftk_refit_accepted_EtaPhi7;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi8 = TH2F("h_ftk_refit_accepted_EtaPhi8", "h_ftk_refit_accepted_EtaPhi8;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi9 = TH2F("h_ftk_refit_accepted_EtaPhi9", "h_ftk_refit_accepted_EtaPhi9;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi10 = TH2F("h_ftk_refit_accepted_EtaPhi10", "h_ftk_refit_accepted_EtaPhi10;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi11 = TH2F("h_ftk_refit_accepted_EtaPhi11", "h_ftk_refit_accepted_EtaPhi11;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi12 = TH2F("h_ftk_refit_accepted_EtaPhi12", "h_ftk_refit_accepted_EtaPhi12;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi13 = TH2F("h_ftk_refit_accepted_EtaPhi13", "h_ftk_refit_accepted_EtaPhi13;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi14 = TH2F("h_ftk_refit_accepted_EtaPhi14", "h_ftk_refit_accepted_EtaPhi14;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi15 = TH2F("h_ftk_refit_accepted_EtaPhi15", "h_ftk_refit_accepted_EtaPhi15;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi16 = TH2F("h_ftk_refit_accepted_EtaPhi16", "h_ftk_refit_accepted_EtaPhi16;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi17 = TH2F("h_ftk_refit_accepted_EtaPhi17", "h_ftk_refit_accepted_EtaPhi17;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi18 = TH2F("h_ftk_refit_accepted_EtaPhi18", "h_ftk_refit_accepted_EtaPhi18;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_refit_accepted_EtaPhi19 = TH2F("h_ftk_refit_accepted_EtaPhi19", "h_ftk_refit_accepted_EtaPhi19;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
# print("BLS test 3")
h_ftk_accepted_EtaPhi0 = TH2F("h_ftk_accepted_EtaPhi0", "h_ftk_accepted_EtaPhi0;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi1 = TH2F("h_ftk_accepted_EtaPhi1", "h_ftk_accepted_EtaPhi1;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi2 = TH2F("h_ftk_accepted_EtaPhi2", "h_ftk_accepted_EtaPhi2;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi3 = TH2F("h_ftk_accepted_EtaPhi3", "h_ftk_accepted_EtaPhi3;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi4 = TH2F("h_ftk_accepted_EtaPhi4", "h_ftk_accepted_EtaPhi4;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi5 = TH2F("h_ftk_accepted_EtaPhi5", "h_ftk_accepted_EtaPhi5;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi6 = TH2F("h_ftk_accepted_EtaPhi6", "h_ftk_accepted_EtaPhi6;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi7 = TH2F("h_ftk_accepted_EtaPhi7", "h_ftk_accepted_EtaPhi7;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi8 = TH2F("h_ftk_accepted_EtaPhi8", "h_ftk_accepted_EtaPhi8;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi9 = TH2F("h_ftk_accepted_EtaPhi9", "h_ftk_accepted_EtaPhi9;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi10 = TH2F("h_ftk_accepted_EtaPhi10", "h_ftk_accepted_EtaPhi10;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi11 = TH2F("h_ftk_accepted_EtaPhi11", "h_ftk_accepted_EtaPhi11;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi12 = TH2F("h_ftk_accepted_EtaPhi12", "h_ftk_accepted_EtaPhi12;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi13 = TH2F("h_ftk_accepted_EtaPhi13", "h_ftk_accepted_EtaPhi13;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi14 = TH2F("h_ftk_accepted_EtaPhi14", "h_ftk_accepted_EtaPhi14;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi15 = TH2F("h_ftk_accepted_EtaPhi15", "h_ftk_accepted_EtaPhi15;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi16 = TH2F("h_ftk_accepted_EtaPhi16", "h_ftk_accepted_EtaPhi16;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi17 = TH2F("h_ftk_accepted_EtaPhi17", "h_ftk_accepted_EtaPhi17;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi18 = TH2F("h_ftk_accepted_EtaPhi18", "h_ftk_accepted_EtaPhi18;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_ftk_accepted_EtaPhi19 = TH2F("h_ftk_accepted_EtaPhi19", "h_ftk_accepted_EtaPhi19;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
# print("BLS test 4")
h_reco_accepted_EtaPhi0 = TH2F("h_reco_accepted_EtaPhi0", "h_reco_accepted_EtaPhi0;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi1 = TH2F("h_reco_accepted_EtaPhi1", "h_reco_accepted_EtaPhi1;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi2 = TH2F("h_reco_accepted_EtaPhi2", "h_reco_accepted_EtaPhi2;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi3 = TH2F("h_reco_accepted_EtaPhi3", "h_reco_accepted_EtaPhi3;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi4 = TH2F("h_reco_accepted_EtaPhi4", "h_reco_accepted_EtaPhi4;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi5 = TH2F("h_reco_accepted_EtaPhi5", "h_reco_accepted_EtaPhi5;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi6 = TH2F("h_reco_accepted_EtaPhi6", "h_reco_accepted_EtaPhi6;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi7 = TH2F("h_reco_accepted_EtaPhi7", "h_reco_accepted_EtaPhi7;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi8 = TH2F("h_reco_accepted_EtaPhi8", "h_reco_accepted_EtaPhi8;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi9 = TH2F("h_reco_accepted_EtaPhi9", "h_reco_accepted_EtaPhi9;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi10 = TH2F("h_reco_accepted_EtaPhi10", "h_reco_accepted_EtaPhi10;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi11 = TH2F("h_reco_accepted_EtaPhi11", "h_reco_accepted_EtaPhi11;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi12 = TH2F("h_reco_accepted_EtaPhi12", "h_reco_accepted_EtaPhi12;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi13 = TH2F("h_reco_accepted_EtaPhi13", "h_reco_accepted_EtaPhi13;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi14 = TH2F("h_reco_accepted_EtaPhi14", "h_reco_accepted_EtaPhi14;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi15 = TH2F("h_reco_accepted_EtaPhi15", "h_reco_accepted_EtaPhi15;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi16 = TH2F("h_reco_accepted_EtaPhi16", "h_reco_accepted_EtaPhi16;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi17 = TH2F("h_reco_accepted_EtaPhi17", "h_reco_accepted_EtaPhi17;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi18 = TH2F("h_reco_accepted_EtaPhi18", "h_reco_accepted_EtaPhi18;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)
h_reco_accepted_EtaPhi19 = TH2F("h_reco_accepted_EtaPhi19", "h_reco_accepted_EtaPhi19;#eta;#phi;Events;", etabins, etamin, etamax, phibins, phimin, phimax)


gStyle.SetOptStat(0)

nbins = 50

histocoordmasketa_reco_EndCap = TH2F("histocoordmasketa_reco_EndCap", "EndCap Track probability of using a coordinate; ;#eta;Prob." ,12,0,12, nbins, -2.5, 2.5)
histocoordmaskphi_reco_EndCap = TH2F("histocoordmaskphi_reco_EndCap", "EndCap Track probability of using a coordinate; ;#phi;Prob." ,12,0,12, nbins, -3.2, 3.2)
histocoordmaskz0_reco_EndCap  = TH2F("histocoordmaskz0_reco_EndCap",  "EndCap Track probability of using a coordinate; ;z0;Prob."  ,12,0,12, nbins, -110, 110)
histocoordmaskd0_reco_EndCap  = TH2F("histocoordmaskd0_reco_EndCap",  "EndCap Track probability of using a coordinate; ;d0;Prob."  ,12,0,12, nbins, -10, 10)
histocoordmasketa_ftk_EndCap = TH2F("histocoordmasketa_ftk_EndCap", "EndCap Track probability of using a coordinate; ;#eta;Prob." ,12,0,12, nbins, -2.5, 2.5)
histocoordmaskphi_ftk_EndCap = TH2F("histocoordmaskphi_ftk_EndCap", "EndCap Track probability of using a coordinate; ;#phi;Prob." ,12,0,12, nbins, -3.2, 3.2)
histocoordmaskz0_ftk_EndCap  = TH2F("histocoordmaskz0_ftk_EndCap",  "EndCap Track probability of using a coordinate; ;z0;Prob."  ,12,0,12, nbins, -110, 110)
histocoordmaskd0_ftk_EndCap  = TH2F("histocoordmaskd0_ftk_EndCap",  "EndCap Track probability of using a coordinate; ;d0;Prob."  ,12,0,12, nbins, -10, 10)
histocoordmasketa_ftkrefit_EndCap = TH2F("histocoordmasketa_ftkrefit_EndCap", "EndCap Track probability of using a coordinate; ;#eta;Prob." ,12,0,12, nbins, -2.5, 2.5)
histocoordmaskphi_ftkrefit_EndCap = TH2F("histocoordmaskphi_ftkrefit_EndCap", "EndCap Track probability of using a coordinate; ;#phi;Prob." ,12,0,12, nbins, -3.2, 3.2)
histocoordmaskz0_ftkrefit_EndCap  = TH2F("histocoordmaskz0_ftkrefit_EndCap",  "EndCap Track probability of using a coordinate; ;z0;Prob."  ,12,0,12, nbins, -110, 110)
histocoordmaskd0_ftkrefit_EndCap  = TH2F("histocoordmaskd0_ftkrefit_EndCap",  "EndCap Track probability of using a coordinate; ;d0;Prob."  ,12,0,12, nbins, -10, 10)

histocoordmasketa_reco_Barrel = TH2F("histocoordmasketa_reco_Barrel", "Barrel Track probability of using a coordinate; ;#eta;Prob." ,8,0,8, nbins, -2.5, 2.5)
histocoordmaskphi_reco_Barrel = TH2F("histocoordmaskphi_reco_Barrel", "Barrel Track probability of using a coordinate; ;#phi;Prob." ,8,0,8, nbins, -3.2, 3.2)
histocoordmaskz0_reco_Barrel  = TH2F("histocoordmaskz0_reco_Barrel",  "Barrel Track probability of using a coordinate; ;z0;Prob."  ,8,0,8, nbins, -110, 110)
histocoordmaskd0_reco_Barrel  = TH2F("histocoordmaskd0_reco_Barrel",  "Barrel Track probability of using a coordinate; ;d0;Prob."  ,8,0,8, nbins, -10, 10)
histocoordmasketa_ftk_Barrel = TH2F("histocoordmasketa_ftk_Barrel", "Barrel Track probability of using a coordinate; ;#eta;Prob." ,8,0,8, nbins, -2.5, 2.5)
histocoordmaskphi_ftk_Barrel = TH2F("histocoordmaskphi_ftk_Barrel", "Barrel Track probability of using a coordinate; ;#phi;Prob." ,8,0,8, nbins, -3.2, 3.2)
histocoordmaskz0_ftk_Barrel  = TH2F("histocoordmaskz0_ftk_Barrel",  "Barrel Track probability of using a coordinate; ;z0;Prob."  ,8,0,8, nbins, -110, 110)
histocoordmaskd0_ftk_Barrel  = TH2F("histocoordmaskd0_ftk_Barrel",  "Barrel Track probability of using a coordinate; ;d0;Prob."  ,8,0,8, nbins, -10, 10)
histocoordmasketa_ftkrefit_Barrel = TH2F("histocoordmasketa_ftkrefit_Barrel", "Barrel Track probability of using a coordinate; ;#eta;Prob." ,8,0,8, nbins, -2.5, 2.5)
histocoordmaskphi_ftkrefit_Barrel = TH2F("histocoordmaskphi_ftkrefit_Barrel", "Barrel Track probability of using a coordinate; ;#phi;Prob." ,8,0,8, nbins, -3.2, 3.2)
histocoordmaskz0_ftkrefit_Barrel  = TH2F("histocoordmaskz0_ftkrefit_Barrel",  "Barrel Track probability of using a coordinate; ;z0;Prob."  ,8,0,8, nbins, -110, 110)
histocoordmaskd0_ftkrefit_Barrel  = TH2F("histocoordmaskd0_ftkrefit_Barrel",  "Barrel Track probability of using a coordinate; ;d0;Prob."  ,8,0,8, nbins, -10, 10)


histocoordmasketa_reco_EndCap_noNorm = TH2F("histocoordmasketa_reco_EndCap_noNorm", "EndCap Track probability of using a coordinate; ;#eta;Prob." ,12,0,12, nbins, -2.5, 2.5)
histocoordmaskphi_reco_EndCap_noNorm = TH2F("histocoordmaskphi_reco_EndCap_noNorm", "EndCap Track probability of using a coordinate; ;#phi;Prob." ,12,0,12, nbins, -3.2, 3.2)
histocoordmaskz0_reco_EndCap_noNorm  = TH2F("histocoordmaskz0_reco_EndCap_noNorm",  "EndCap Track probability of using a coordinate; ;z0;Prob."  ,12,0,12, nbins, -110, 110)
histocoordmaskd0_reco_EndCap_noNorm  = TH2F("histocoordmaskd0_reco_EndCap_noNorm",  "EndCap Track probability of using a coordinate; ;d0;Prob."  ,12,0,12, nbins, -10, 10)
histocoordmasketa_ftk_EndCap_noNorm = TH2F("histocoordmasketa_ftk_EndCap_noNorm", "EndCap Track probability of using a coordinate; ;#eta;Prob." ,12,0,12, nbins, -2.5, 2.5)
histocoordmaskphi_ftk_EndCap_noNorm = TH2F("histocoordmaskphi_ftk_EndCap_noNorm", "EndCap Track probability of using a coordinate; ;#phi;Prob." ,12,0,12, nbins, -3.2, 3.2)
histocoordmaskz0_ftk_EndCap_noNorm  = TH2F("histocoordmaskz0_ftk_EndCap_noNorm",  "EndCap Track probability of using a coordinate; ;z0;Prob."  ,12,0,12, nbins, -110, 110)
histocoordmaskd0_ftk_EndCap_noNorm  = TH2F("histocoordmaskd0_ftk_EndCap_noNorm",  "EndCap Track probability of using a coordinate; ;d0;Prob."  ,12,0,12, nbins, -10, 10)
histocoordmasketa_ftkrefit_EndCap_noNorm = TH2F("histocoordmasketa_ftkrefit_EndCap_noNorm", "EndCap Track probability of using a coordinate; ;#eta;Prob." ,12,0,12, nbins, -2.5, 2.5)
histocoordmaskphi_ftkrefit_EndCap_noNorm = TH2F("histocoordmaskphi_ftkrefit_EndCap_noNorm", "EndCap Track probability of using a coordinate; ;#phi;Prob." ,12,0,12, nbins, -3.2, 3.2)
histocoordmaskz0_ftkrefit_EndCap_noNorm  = TH2F("histocoordmaskz0_ftkrefit_EndCap_noNorm",  "EndCap Track probability of using a coordinate; ;z0;Prob."  ,12,0,12, nbins, -110, 110)
histocoordmaskd0_ftkrefit_EndCap_noNorm  = TH2F("histocoordmaskd0_ftkrefit_EndCap_noNorm",  "EndCap Track probability of using a coordinate; ;d0;Prob."  ,12,0,12, nbins, -10, 10)

histocoordmasketa_reco_Barrel_noNorm = TH2F("histocoordmasketa_reco_Barrel_noNorm", "Barrel Track probability of using a coordinate; ;#eta;Prob." ,8,0,8, nbins, -2.5, 2.5)
histocoordmaskphi_reco_Barrel_noNorm = TH2F("histocoordmaskphi_reco_Barrel_noNorm", "Barrel Track probability of using a coordinate; ;#phi;Prob." ,8,0,8, nbins, -3.2, 3.2)
histocoordmaskd0_reco_Barrel_noNorm  = TH2F("histocoordmaskd0_reco_Barrel_noNorm",  "Barrel Track probability of using a coordinate; ;d0;Prob."  ,8,0,8, nbins, -10, 10)
histocoordmaskz0_reco_Barrel_noNorm  = TH2F("histocoordmaskz0_reco_Barrel_noNorm",  "Barrel Track probability of using a coordinate; ;z0;Prob."  ,8,0,8, nbins, -110, 110)
histocoordmasketa_ftk_Barrel_noNorm = TH2F("histocoordmasketa_ftk_Barrel_noNorm", "Barrel Track probability of using a coordinate; ;#eta;Prob." ,8,0,8, nbins, -2.5, 2.5)
histocoordmaskphi_ftk_Barrel_noNorm = TH2F("histocoordmaskphi_ftk_Barrel_noNorm", "Barrel Track probability of using a coordinate; ;#phi;Prob." ,8,0,8, nbins, -3.2, 3.2)
histocoordmaskz0_ftk_Barrel_noNorm  = TH2F("histocoordmaskz0_ftk_Barrel_noNorm",  "Barrel Track probability of using a coordinate; ;z0;Prob."  ,8,0,8, nbins, -110, 110)
histocoordmaskd0_ftk_Barrel_noNorm  = TH2F("histocoordmaskd0_ftk_Barrel_noNorm",  "Barrel Track probability of using a coordinate; ;d0;Prob."  ,8,0,8, nbins, -10, 10)
histocoordmasketa_ftkrefit_Barrel_noNorm = TH2F("histocoordmasketa_ftkrefit_Barrel_noNorm", "Barrel Track probability of using a coordinate; ;#eta;Prob." ,8,0,8, nbins, -2.5, 2.5)
histocoordmaskphi_ftkrefit_Barrel_noNorm = TH2F("histocoordmaskphi_ftkrefit_Barrel_noNorm", "Barrel Track probability of using a coordinate; ;#phi;Prob." ,8,0,8, nbins, -3.2, 3.2)
histocoordmaskz0_ftkrefit_Barrel_noNorm  = TH2F("histocoordmaskz0_ftkrefit_Barrel_noNorm",  "Barrel Track probability of using a coordinate; ;z0;Prob."  ,8,0,8, nbins, -110, 110)
histocoordmaskd0_ftkrefit_Barrel_noNorm  = TH2F("histocoordmaskd0_ftkrefit_Barrel_noNorm",  "Barrel Track probability of using a coordinate; ;d0;Prob."  ,8,0,8, nbins, -10, 10)


histocoordmasketa_reco = TH2F("histocoordmasketa_reco", "Track probability of using a coordinate; ;#eta;Prob." ,20,0,20, nbins, -2.5, 2.5)
histocoordmaskphi_reco = TH2F("histocoordmaskphi_reco", "Track probability of using a coordinate; ;#phi;Prob." ,20,0,20, nbins, -3.2, 3.2)
histocoordmaskz0_reco  = TH2F("histocoordmaskz0_reco",  "Track probability of using a coordinate; ;z0;Prob."  ,20,0,20, nbins, -110, 110)
histocoordmaskd0_reco = TH2F("histocoordmaskd0_reco", "Track probability of using a coordinate; ;z0;Prob." ,20,0,20, nbins, -10, 10)

histocoordmasketa_ftk = TH2F("histocoordmasketa_ftk", "Track probability of using a coordinate; ;#eta;Prob." ,20,0,20, nbins, -2.5, 2.5)
histocoordmaskphi_ftk = TH2F("histocoordmaskphi_ftk", "Track probability of using a coordinate; ;#phi;Prob." ,20,0,20, nbins, -3.2, 3.2)
histocoordmaskz0_ftk  = TH2F("histocoordmaskz0_ftk",  "Track probability of using a coordinate; ;z0;Prob."  ,20,0,20, nbins, -110, 110)
histocoordmaskd0_ftk  = TH2F("histocoordmaskd0_ftk",  "Track probability of using a coordinate; ;d0;Prob."  ,20,0,20, nbins, -10, 10)

histocoordmasketa_ftkrefit = TH2F("histocoordmasketa_ftkrefit", "Track probability of using a coordinate; ;#eta;Prob." ,20,0,20, nbins, -2.5, 2.5)
histocoordmaskphi_ftkrefit = TH2F("histocoordmaskphi_ftkrefit", "Track probability of using a coordinate; ;#phi;Prob." ,20,0,20, nbins, -3.2, 3.2)
histocoordmaskz0_ftkrefit  = TH2F("histocoordmaskz0_ftkrefit",  "Track probability of using a coordinate; ;z0;Prob."  ,20,0,20, nbins, -110, 110)
histocoordmaskd0_ftkrefit  = TH2F("histocoordmaskd0_ftkrefit",  "Track probability of using a coordinate; ;d0;Prob."  ,20,0,20, nbins, -10, 10)


# histListBarrel = [h_reco_accepted_hitPattern_Barrel, histocoordmasketa_reco_Barrel, histocoordmaskphi_reco_Barrel, histocoordmaskz0_reco_Barrel, 
# 			h_ftk_accepted_hitPattern_Barrel, histocoordmasketa_ftk_Barrel, histocoordmaskphi_ftk_Barrel, histocoordmaskz0_ftk_Barrel, 
# 			h_ftk_refit_accepted_hitPattern_Barrel, histocoordmasketa_ftkrefit_Barrel, histocoordmaskphi_ftkrefit_Barrel, histocoordmaskz0_ftkrefit_Barrel]

# histListEndCap = [h_reco_accepted_hitPattern_EndCap, histocoordmasketa_reco_EndCap, histocoordmaskphi_reco_EndCap, histocoordmaskz0_reco_EndCap, 
# 			h_ftk_accepted_hitPattern_EndCap, histocoordmasketa_ftk_EndCap, histocoordmaskphi_ftk_EndCap, histocoordmaskz0_ftk_EndCap, 
# 			h_ftk_refit_accepted_hitPattern_EndCap, histocoordmasketa_ftkrefit_EndCap, histocoordmaskphi_ftkrefit_EndCap, histocoordmaskz0_ftkrefit_EndCap]

histListEndCap = [histocoordmasketa_reco_EndCap, histocoordmaskphi_reco_EndCap, histocoordmaskz0_reco_EndCap, histocoordmaskd0_reco_EndCap, histocoordmasketa_ftk_EndCap, 
			histocoordmaskphi_ftk_EndCap, histocoordmaskz0_ftk_EndCap, histocoordmaskd0_ftk_EndCap, histocoordmasketa_ftkrefit_EndCap, histocoordmaskphi_ftkrefit_EndCap, 
			histocoordmaskz0_ftkrefit_EndCap, histocoordmaskd0_ftkrefit_EndCap, h_reco_accepted_hitPattern_EndCap, h_ftk_accepted_hitPattern_EndCap, 
			h_ftk_refit_accepted_hitPattern_EndCap]

histListBarrel = [histocoordmasketa_reco_Barrel, histocoordmaskphi_reco_Barrel, histocoordmaskz0_reco_Barrel, histocoordmaskd0_reco_Barrel, histocoordmasketa_ftk_Barrel, 
			histocoordmaskphi_ftk_Barrel, histocoordmaskz0_ftk_Barrel, histocoordmaskd0_ftk_Barrel, histocoordmasketa_ftkrefit_Barrel, histocoordmaskphi_ftkrefit_Barrel, 
			histocoordmaskz0_ftkrefit_Barrel, histocoordmaskd0_ftkrefit_Barrel, h_reco_accepted_hitPattern_Barrel, h_ftk_accepted_hitPattern_Barrel, 
			h_ftk_refit_accepted_hitPattern_Barrel]

histListInclusive = [h_reco_accepted_hitPattern, histocoordmasketa_reco, histocoordmaskphi_reco, histocoordmaskz0_reco, histocoordmaskd0_reco, h_ftk_accepted_hitPattern, 
			histocoordmasketa_ftk, histocoordmaskphi_ftk, histocoordmaskz0_ftk, histocoordmaskd0_ftk, h_ftk_refit_accepted_hitPattern, histocoordmasketa_ftkrefit, 
			histocoordmaskphi_ftkrefit, histocoordmaskz0_ftkrefit, histocoordmaskd0_ftkrefit]

# hist2D = [histocoordmasketa_reco_EndCap, histocoordmaskphi_reco_EndCap, histocoordmaskz0_reco_EndCap, histocoordmasketa_ftk_EndCap, histocoordmaskphi_ftk_EndCap, 
# 			histocoordmaskz0_ftk_EndCap, histocoordmasketa_ftkrefit_EndCap, histocoordmaskphi_ftkrefit_EndCap, histocoordmaskz0_ftkrefit_EndCap, 
# 			histocoordmasketa_reco_Barrel, histocoordmaskphi_reco_Barrel, histocoordmaskz0_reco_Barrel, histocoordmasketa_ftk_Barrel, histocoordmaskphi_ftk_Barrel, 
# 			histocoordmaskz0_ftk_Barrel, histocoordmasketa_ftkrefit_Barrel, histocoordmaskphi_ftkrefit_Barrel, histocoordmaskz0_ftkrefit_Barrel, 
# 			histocoordmasketa_reco, histocoordmaskphi_reco, histocoordmaskz0_reco, histocoordmasketa_ftk, histocoordmaskphi_ftk, 
# 			histocoordmaskz0_ftk, histocoordmasketa_ftkrefit, histocoordmaskphi_ftkrefit, histocoordmaskz0_ftkrefit]

hist2D = [histocoordmasketa_reco_EndCap, histocoordmaskphi_reco_EndCap, histocoordmaskz0_reco_EndCap, histocoordmaskd0_reco_EndCap, histocoordmasketa_ftk_EndCap, 
			histocoordmaskphi_ftk_EndCap, histocoordmaskz0_ftk_EndCap, histocoordmaskd0_ftk_EndCap, histocoordmasketa_ftkrefit_EndCap, histocoordmaskphi_ftkrefit_EndCap, 
			histocoordmaskz0_ftkrefit_EndCap, histocoordmaskd0_ftkrefit_EndCap, histocoordmasketa_reco_Barrel, histocoordmaskphi_reco_Barrel, histocoordmaskz0_reco_Barrel, 
			histocoordmaskd0_reco_Barrel, histocoordmasketa_ftk_Barrel, histocoordmaskphi_ftk_Barrel, histocoordmaskz0_ftk_Barrel, histocoordmaskd0_ftk_Barrel, 
			histocoordmasketa_ftkrefit_Barrel, histocoordmaskphi_ftkrefit_Barrel, histocoordmaskz0_ftkrefit_Barrel, histocoordmaskd0_ftkrefit_Barrel, histocoordmasketa_reco, 
			histocoordmaskphi_reco, histocoordmaskz0_reco, histocoordmasketa_ftk, histocoordmaskphi_ftk, histocoordmaskz0_ftk, histocoordmasketa_ftkrefit, 
			histocoordmaskphi_ftkrefit, histocoordmaskz0_ftkrefit]





print("Adding files to chain")



chain = TChain("tracks")
chain.Add(input_file)

# run_number = chain.run_number(0)

if test_events == True:
	nentries = 100
else:
	nentries = chain.GetEntries()

# c1 = TCanvas("c1", "")

# nentries = 500

chain.Draw("ftk_refit_reco_pt_bias>>h_reco_ftk_refitMatched_pt_bias")
chain.Draw("ftk_refit_reco_eta_bias>>h_reco_ftk_refitMatched_eta_bias")
chain.Draw("ftk_refit_reco_phi_bias>>h_reco_ftk_refitMatched_phi_bias")
chain.Draw("ftk_refit_reco_d0_bias>>h_reco_ftk_refitMatched_d0_bias")

chain.Draw("ftk_reco_pt_bias>>h_reco_ftkMatched_pt_bias")
chain.Draw("ftk_reco_eta_bias>>h_reco_ftkMatched_eta_bias")
chain.Draw("ftk_reco_phi_bias>>h_reco_ftkMatched_phi_bias")
chain.Draw("ftk_reco_d0_bias>>h_reco_ftkMatched_d0_bias")
chain.Draw("ftk_reco_corrected_d0_bias>>h_reco_ftkMatched_corrected_d0_bias")

if isData == False:
	chain.Draw("ftk_refit_truth_pt_bias>>h_truth_ftk_refitMatched_pt_bias")
	chain.Draw("ftk_refit_truth_eta_bias>>h_truth_ftk_refitMatched_eta_bias")
	chain.Draw("ftk_refit_truth_phi_bias>>h_truth_ftk_refitMatched_phi_bias")
	chain.Draw("ftk_refit_truth_d0_bias>>h_truth_ftk_refitMatched_d0_bias")

	chain.Draw("ftk_truth_pt_bias>>	h_truth_ftk_Matched_pt_bias")
	chain.Draw("ftk_truth_eta_bias>>h_truth_ftk_Matched_eta_bias")
	chain.Draw("ftk_truth_phi_bias>>h_truth_ftk_Matched_phi_bias")
	chain.Draw("ftk_truth_d0_bias>>	h_truth_ftk_Matched_d0_bias")
	chain.Draw("ftk_truth_corrected_d0_bias>>h_truth_ftk_Matched_corrected_d0_bias")

	chain.Draw("truth_reco_pt_bias>>h_reco_truthMatched_pt_bias")
	chain.Draw("truth_reco_eta_bias>>h_reco_truthMatched_eta_bias")
	chain.Draw("truth_reco_phi_bias>>h_reco_truthMatched_phi_bias")
	chain.Draw("truth_reco_d0_bias>>h_reco_truthMatched_d0_bias")

# ibl = 0
# pixBarrel1 = 1
# pixBarrel2 = 2
# pixBarrel3 = 3
# pixEndCap0 = 4
# pixEndCap1 = 5
# pixEndCap2 = 6
# sctBarrel0 = 7
# sctBarrel1 = 8
# sctBarrel2 = 9
# sctBarrel3 = 10
# sctEndCap0 = 11
# sctEndCap1 = 12
# sctEndCap2 = 13
# sctEndCap3 = 14
# sctEndCap4 = 15
# sctEndCap5 = 16
# sctEndCap6 = 17
# sctEndCap7 = 18
# sctEndCap8 = 19
# trtBarrel = 20
# trtEndCap = 21
# DBM0 = 22
# DBM1 = 23
# DBM2 = 24


print("Starting loop")
for i in range(nentries):
	# if i % 2 == 1:

	chain.GetEntry(i)
	if nentries > 100:
		if i % 50 == 0:
			print("processing event "+str(i)+" out of "+str(nentries))
	else:
		if i % 10 == 0:
			print("processing event "+str(i)+" out of "+str(nentries))

	if isData == False:
		n_truth_tracks = chain.truth_track_n

	n_reco_accepted_tracks = chain.reco_accepted_track_n
	n_reco_inclusive_tracks = chain.reco_inclusive_track_n

	n_ftk_accepted_tracks = chain.ftk_accepted_track_n
	n_ftk_inclusive_tracks = chain.ftk_inclusive_track_n

	n_ftk_refit_accepted_tracks = chain.ftk_refit_accepted_track_n
	n_ftk_refit_inclusive_tracks = chain.ftk_refit_inclusive_track_n

	if isData == False:
		n_truth_recoMatch_tracks = chain.truth_recoMatch_track_n
		n_truth_ftkMatch_tracks = chain.truth_ftkMatch_track_n
		n_truth_ftkrefitMatch_tracks = chain.truth_ftkrefitMatch_track_n

	n_reco_ftkMatch_tracks = chain.reco_ftkMatch_track_n
	n_reco_ftkrefitMatch_tracks = chain.reco_ftkrefitMatch_track_n

	# hits = []

	for iftk in range(n_ftk_accepted_tracks):
		h_ftk_accepted_pt.Fill(chain.ftk_accepted_track_pt[iftk])
		h_ftk_accepted_eta.Fill(chain.ftk_accepted_track_eta[iftk])

		if abs(chain.ftk_accepted_track_eta[iftk]) <= 1:
			h_ftk_accepted_eta_barrel.Fill(chain.ftk_accepted_track_eta[iftk])
			h_ftk_accepted_phi_barrel.Fill(chain.ftk_accepted_track_phi[iftk])
			h_ftk_accepted_z0_barrel.Fill(chain.ftk_accepted_track_z0[iftk])
			h_ftk_accepted_d0_barrel.Fill(chain.ftk_accepted_track_d0[iftk])
		if abs(chain.ftk_accepted_track_eta[iftk]) >= 1.5:
			h_ftk_accepted_eta_endcap.Fill(chain.ftk_accepted_track_eta[iftk])
			h_ftk_accepted_phi_endcap.Fill(chain.ftk_accepted_track_phi[iftk])
			h_ftk_accepted_z0_endcap.Fill(chain.ftk_accepted_track_z0[iftk])
			h_ftk_accepted_d0_endcap.Fill(chain.ftk_accepted_track_d0[iftk])

		h_ftk_accepted_phi.Fill(chain.ftk_accepted_track_phi[iftk])

		h_ftk_accepted_EtaPhi.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])

		h_ftk_accepted_m.Fill(chain.ftk_accepted_track_m[iftk])
		h_ftk_accepted_d0.Fill(chain.ftk_accepted_track_d0[iftk])
		h_ftk_accepted_corrected_d0.Fill(chain.ftk_accepted_track_corrected_d0[iftk])
		h_ftk_accepted_z0.Fill(chain.ftk_accepted_track_z0[iftk])
		h_ftk_accepted_qop.Fill(chain.ftk_accepted_track_qop[iftk])
		h_ftk_accepted_charge.Fill(chain.ftk_accepted_track_charge[iftk])
		h_ftk_accepted_chi2.Fill(chain.ftk_accepted_track_chi2[iftk])
		hit = int(chain.ftk_accepted_track_hitPattern[iftk])
		ncoords = len(bin(hit))-2
		for icoord in range(ncoords):
			if (hit >> icoord & 0x1):
				h_ftk_accepted_hitPattern.Fill(icoord)
				histocoordmasketa_ftk.Fill(icoord,chain.ftk_accepted_track_eta[iftk])
				histocoordmaskz0_ftk.Fill(icoord,chain.ftk_accepted_track_z0[iftk])
				histocoordmaskd0_ftk.Fill(icoord,chain.ftk_accepted_track_corrected_d0[iftk])
				histocoordmaskphi_ftk.Fill(icoord,chain.ftk_accepted_track_phi[iftk])

				if icoord == 0:
					h_ftk_accepted_EtaPhi0.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 1:
					h_ftk_accepted_EtaPhi1.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 2:
					h_ftk_accepted_EtaPhi2.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 3:
					h_ftk_accepted_EtaPhi3.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 4:
					h_ftk_accepted_EtaPhi4.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 5:
					h_ftk_accepted_EtaPhi5.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 6:
					h_ftk_accepted_EtaPhi6.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 7:
					h_ftk_accepted_EtaPhi7.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 8:
					h_ftk_accepted_EtaPhi8.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 9:
					h_ftk_accepted_EtaPhi9.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 10:
					h_ftk_accepted_EtaPhi10.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 11:
					h_ftk_accepted_EtaPhi11.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 12:
					h_ftk_accepted_EtaPhi12.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 13:
					h_ftk_accepted_EtaPhi13.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 14:
					h_ftk_accepted_EtaPhi14.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 15:
					h_ftk_accepted_EtaPhi15.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 16:
					h_ftk_accepted_EtaPhi16.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 17:
					h_ftk_accepted_EtaPhi17.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 18:
					h_ftk_accepted_EtaPhi18.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])
				if icoord == 19:
					h_ftk_accepted_EtaPhi19.Fill(chain.ftk_accepted_track_eta[iftk], chain.ftk_accepted_track_phi[iftk])

				if icoord == 0 or icoord == 1 or icoord == 2 or icoord == 3 or icoord == 7 or icoord == 8 or icoord == 9 or icoord == 10 or icoord == 20:
					if abs(chain.ftk_accepted_track_eta[iftk]) <= 1:
						if icoord == 0:
							newcoord = 0
						if icoord == 1:
							newcoord = 1
						if icoord == 2:
							newcoord = 2
						if icoord == 3:
							newcoord = 3
						if icoord == 7:
							newcoord = 4
						if icoord == 8:
							newcoord = 5
						if icoord == 9:
							newcoord = 6
						if icoord == 10:
							newcoord = 7
						h_ftk_accepted_hitPattern_Barrel.Fill(newcoord)
						histocoordmasketa_ftk_Barrel.Fill(newcoord,chain.ftk_accepted_track_eta[iftk])
						histocoordmaskz0_ftk_Barrel.Fill(newcoord,chain.ftk_accepted_track_z0[iftk])
						histocoordmaskd0_ftk_Barrel.Fill(newcoord,chain.ftk_accepted_track_corrected_d0[iftk])
						histocoordmaskphi_ftk_Barrel.Fill(newcoord,chain.ftk_accepted_track_phi[iftk])

						histocoordmasketa_ftk_Barrel_noNorm.Fill(newcoord,chain.ftk_accepted_track_eta[iftk])
						histocoordmaskz0_ftk_Barrel_noNorm.Fill(newcoord,chain.ftk_accepted_track_z0[iftk])
						histocoordmaskd0_ftk_Barrel_noNorm.Fill(newcoord,chain.ftk_accepted_track_corrected_d0[iftk])
						histocoordmaskphi_ftk_Barrel_noNorm.Fill(newcoord,chain.ftk_accepted_track_phi[iftk])


				else:
					if abs(chain.ftk_accepted_track_eta[iftk]) >= 1.5:
						if icoord == 4:
							newcoord = 0
						if icoord == 5:
							newcoord = 1
						if icoord == 6:
							newcoord = 2
						if icoord == 11:
							newcoord = 3
						if icoord == 12:
							newcoord = 4
						if icoord == 13:
							newcoord = 5
						if icoord == 14:
							newcoord = 6
						if icoord == 15:
							newcoord = 7
						if icoord == 16:
							newcoord = 8
						if icoord == 17:
							newcoord = 9
						if icoord == 18:
							newcoord = 10
						if icoord == 19:
							newcoord = 11
						h_ftk_accepted_hitPattern_EndCap.Fill(newcoord)
						histocoordmasketa_ftk_EndCap.Fill(newcoord,chain.ftk_accepted_track_eta[iftk])
						histocoordmaskz0_ftk_EndCap.Fill(newcoord,chain.ftk_accepted_track_z0[iftk])
						histocoordmaskd0_ftk_EndCap.Fill(newcoord,chain.ftk_accepted_track_corrected_d0[iftk])
						histocoordmaskphi_ftk_EndCap.Fill(newcoord,chain.ftk_accepted_track_phi[iftk])

						histocoordmasketa_ftk_EndCap_noNorm.Fill(newcoord,chain.ftk_accepted_track_eta[iftk])
						histocoordmaskz0_ftk_EndCap_noNorm.Fill(newcoord,chain.ftk_accepted_track_z0[iftk])
						histocoordmaskd0_ftk_EndCap_noNorm.Fill(newcoord,chain.ftk_accepted_track_corrected_d0[iftk])
						histocoordmaskphi_ftk_EndCap_noNorm.Fill(newcoord,chain.ftk_accepted_track_phi[iftk])

	for iftk in range(n_ftk_inclusive_tracks):
		h_ftk_inclusive_pt.Fill(chain.ftk_inclusive_track_pt[iftk])
		h_ftk_inclusive_eta.Fill(chain.ftk_inclusive_track_eta[iftk])
		h_ftk_inclusive_phi.Fill(chain.ftk_inclusive_track_phi[iftk])
		h_ftk_inclusive_m.Fill(chain.ftk_inclusive_track_m[iftk])
		h_ftk_inclusive_d0.Fill(chain.ftk_inclusive_track_d0[iftk])
		h_ftk_inclusive_corrected_d0.Fill(chain.ftk_inclusive_track_corrected_d0[iftk])
		h_ftk_inclusive_z0.Fill(chain.ftk_inclusive_track_z0[iftk])
		h_ftk_inclusive_qop.Fill(chain.ftk_inclusive_track_qop[iftk])
		h_ftk_inclusive_chi2.Fill(chain.ftk_inclusive_track_chi2[iftk])
		h_ftk_inclusive_charge.Fill(chain.ftk_inclusive_track_charge[iftk])
		h_ftk_inclusive_EtaPhi.Fill(chain.ftk_inclusive_track_eta[iftk], chain.ftk_inclusive_track_phi[iftk])


	# print("ntracks: ", n_ftk_refit_accepted_tracks)
	for iftk in range(n_ftk_refit_accepted_tracks):
		h_ftk_refit_accepted_pt.Fill(chain.ftk_refit_accepted_track_pt[iftk])
		h_ftk_refit_accepted_eta.Fill(chain.ftk_refit_accepted_track_eta[iftk])

		if abs(chain.ftk_refit_accepted_track_eta[iftk]) <= 1:
			h_ftk_refit_accepted_eta_barrel.Fill(chain.ftk_refit_accepted_track_eta[iftk])
			h_ftk_refit_accepted_phi_barrel.Fill(chain.ftk_refit_accepted_track_phi[iftk])
			h_ftk_refit_accepted_z0_barrel.Fill(chain.ftk_refit_accepted_track_z0[iftk])
		if abs(chain.ftk_refit_accepted_track_eta[iftk]) >= 1.5:
			h_ftk_refit_accepted_eta_endcap.Fill(chain.ftk_refit_accepted_track_eta[iftk])
			h_ftk_refit_accepted_phi_endcap.Fill(chain.ftk_refit_accepted_track_phi[iftk])
			h_ftk_refit_accepted_z0_endcap.Fill(chain.ftk_refit_accepted_track_z0[iftk])

		# h_ftk_refit_accepted_eta_barrel.Fill(chain.ftk_refit_accepted_track_eta_barrel[iftk])
		# h_ftk_refit_accepted_eta_endcap.Fill(chain.ftk_refit_accepted_track_eta_endcap[iftk])
		h_ftk_refit_accepted_phi.Fill(chain.ftk_refit_accepted_track_phi[iftk])
		h_ftk_refit_accepted_m.Fill(chain.ftk_refit_accepted_track_m[iftk])
		h_ftk_refit_accepted_d0.Fill(chain.ftk_refit_accepted_track_d0[iftk])
		h_ftk_refit_accepted_z0.Fill(chain.ftk_refit_accepted_track_z0[iftk])
		h_ftk_refit_accepted_qop.Fill(chain.ftk_refit_accepted_track_qop[iftk])
		h_ftk_refit_accepted_charge.Fill(chain.ftk_refit_accepted_track_charge[iftk])
		h_ftk_refit_accepted_chi2.Fill(chain.ftk_refit_accepted_track_chi2[iftk])
		h_ftk_refit_accepted_EtaPhi.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])

		hit = int(chain.ftk_refit_accepted_track_hitPattern[iftk])
		# print("hit: ", hit)
		ncoords = len(bin(hit))-2
		# print(ncoords)
		for icoord in range(ncoords):
			if (hit >> icoord & 0x1):
				# print("hit in layer ", icoord)
				h_ftk_refit_accepted_hitPattern.Fill(icoord)
				histocoordmasketa_ftkrefit.Fill(icoord,chain.ftk_refit_accepted_track_eta[iftk])
				histocoordmaskz0_ftkrefit.Fill(icoord,chain.ftk_refit_accepted_track_z0[iftk])
				histocoordmaskd0_ftkrefit.Fill(icoord,chain.ftk_refit_accepted_track_d0[iftk])
				histocoordmaskphi_ftkrefit.Fill(icoord,chain.ftk_refit_accepted_track_phi[iftk])

				if icoord == 0:
					h_ftk_refit_accepted_EtaPhi0.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 1:
					h_ftk_refit_accepted_EtaPhi1.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 2:
					h_ftk_refit_accepted_EtaPhi2.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 3:
					h_ftk_refit_accepted_EtaPhi3.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 4:
					h_ftk_refit_accepted_EtaPhi4.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 5:
					h_ftk_refit_accepted_EtaPhi5.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 6:
					h_ftk_refit_accepted_EtaPhi6.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 7:
					h_ftk_refit_accepted_EtaPhi7.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 8:
					h_ftk_refit_accepted_EtaPhi8.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 9:
					h_ftk_refit_accepted_EtaPhi9.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 10:
					h_ftk_refit_accepted_EtaPhi10.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 11:
					h_ftk_refit_accepted_EtaPhi11.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 12:
					h_ftk_refit_accepted_EtaPhi12.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 13:
					h_ftk_refit_accepted_EtaPhi13.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 14:
					h_ftk_refit_accepted_EtaPhi14.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 15:
					h_ftk_refit_accepted_EtaPhi15.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 16:
					h_ftk_refit_accepted_EtaPhi16.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 17:
					h_ftk_refit_accepted_EtaPhi17.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 18:
					h_ftk_refit_accepted_EtaPhi18.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])
				if icoord == 19:
					h_ftk_refit_accepted_EtaPhi19.Fill(chain.ftk_refit_accepted_track_eta[iftk], chain.ftk_refit_accepted_track_phi[iftk])

				if icoord == 0 or icoord == 1 or icoord == 2 or icoord == 3 or icoord == 7 or icoord == 8 or icoord == 9 or icoord == 10 or icoord == 20:
					if abs(chain.ftk_refit_accepted_track_eta[iftk]) <= 1:
						if icoord == 0:
							newcoord = 0
						if icoord == 1:
							newcoord = 1
						if icoord == 2:
							newcoord = 2
						if icoord == 3:
							newcoord = 3
						if icoord == 7:
							newcoord = 4
						if icoord == 8:
							newcoord = 5
						if icoord == 9:
							newcoord = 6
						if icoord == 10:
							newcoord = 7
						h_ftk_refit_accepted_hitPattern_Barrel.Fill(newcoord)
						histocoordmasketa_ftkrefit_Barrel.Fill(newcoord,chain.ftk_refit_accepted_track_eta[iftk])
						histocoordmaskz0_ftkrefit_Barrel.Fill(newcoord,chain.ftk_refit_accepted_track_z0[iftk])
						histocoordmaskd0_ftkrefit_Barrel.Fill(newcoord,chain.ftk_refit_accepted_track_d0[iftk])
						histocoordmaskphi_ftkrefit_Barrel.Fill(newcoord,chain.ftk_refit_accepted_track_phi[iftk])

						histocoordmasketa_ftkrefit_Barrel_noNorm.Fill(newcoord,chain.ftk_refit_accepted_track_eta[iftk])
						histocoordmaskz0_ftkrefit_Barrel_noNorm.Fill(newcoord,chain.ftk_refit_accepted_track_z0[iftk])
						histocoordmaskd0_ftkrefit_Barrel_noNorm.Fill(newcoord,chain.ftk_refit_accepted_track_d0[iftk])
						histocoordmaskphi_ftkrefit_Barrel_noNorm.Fill(newcoord,chain.ftk_refit_accepted_track_phi[iftk])
				else:
					if abs(chain.ftk_refit_accepted_track_eta[iftk]) >= 1.5:
						if icoord == 4:
							newcoord = 0
						if icoord == 5:
							newcoord = 1
						if icoord == 6:
							newcoord = 2
						if icoord == 11:
							newcoord = 3
						if icoord == 12:
							newcoord = 4
						if icoord == 13:
							newcoord = 5
						if icoord == 14:
							newcoord = 6
						if icoord == 15:
							newcoord = 7
						if icoord == 16:
							newcoord = 8
						if icoord == 17:
							newcoord = 9
						if icoord == 18:
							newcoord = 10
						if icoord == 19:
							newcoord = 11
						h_ftk_refit_accepted_hitPattern_EndCap.Fill(newcoord)
						histocoordmasketa_ftkrefit_EndCap.Fill(newcoord,chain.ftk_refit_accepted_track_eta[iftk])
						histocoordmaskz0_ftkrefit_EndCap.Fill(newcoord,chain.ftk_refit_accepted_track_z0[iftk])
						histocoordmaskd0_ftkrefit_EndCap.Fill(newcoord,chain.ftk_refit_accepted_track_d0[iftk])
						histocoordmaskphi_ftkrefit_EndCap.Fill(newcoord,chain.ftk_refit_accepted_track_phi[iftk])

						histocoordmasketa_ftkrefit_EndCap_noNorm.Fill(newcoord,chain.ftk_refit_accepted_track_eta[iftk])
						histocoordmaskz0_ftkrefit_EndCap_noNorm.Fill(newcoord,chain.ftk_refit_accepted_track_z0[iftk])
						histocoordmaskd0_ftkrefit_EndCap_noNorm.Fill(newcoord,chain.ftk_refit_accepted_track_d0[iftk])
						histocoordmaskphi_ftkrefit_EndCap_noNorm.Fill(newcoord,chain.ftk_refit_accepted_track_phi[iftk])


	for iftk in range(n_ftk_refit_inclusive_tracks):
		h_ftk_refit_inclusive_pt.Fill(chain.ftk_refit_inclusive_track_pt[iftk])
		h_ftk_refit_inclusive_eta.Fill(chain.ftk_refit_inclusive_track_eta[iftk])
		h_ftk_refit_inclusive_phi.Fill(chain.ftk_refit_inclusive_track_phi[iftk])
		h_ftk_refit_inclusive_m.Fill(chain.ftk_refit_inclusive_track_m[iftk])
		h_ftk_refit_inclusive_d0.Fill(chain.ftk_refit_inclusive_track_d0[iftk])
		h_ftk_refit_inclusive_z0.Fill(chain.ftk_refit_inclusive_track_z0[iftk])
		h_ftk_refit_inclusive_qop.Fill(chain.ftk_refit_inclusive_track_qop[iftk])
		h_ftk_refit_inclusive_chi2.Fill(chain.ftk_refit_inclusive_track_chi2[iftk])
		h_ftk_refit_inclusive_charge.Fill(chain.ftk_refit_inclusive_track_charge[iftk])
		h_ftk_refit_inclusive_EtaPhi.Fill(chain.ftk_refit_inclusive_track_eta[iftk], chain.ftk_refit_inclusive_track_phi[iftk])

	for ireco in range(n_reco_accepted_tracks):
		h_reco_accepted_pt.Fill(chain.reco_accepted_track_pt[ireco])
		h_reco_accepted_eta.Fill(chain.reco_accepted_track_eta[ireco])

		if abs(chain.reco_accepted_track_eta[ireco]) <= 1:
			h_reco_accepted_eta_barrel.Fill(chain.reco_accepted_track_eta[ireco])
			h_reco_accepted_phi_barrel.Fill(chain.reco_accepted_track_phi[ireco])
			h_reco_accepted_z0_barrel.Fill(chain.reco_accepted_track_z0[ireco])
		if abs(chain.reco_accepted_track_eta[ireco]) >= 1.5:
			h_reco_accepted_eta_endcap.Fill(chain.reco_accepted_track_eta[ireco])
			h_reco_accepted_phi_endcap.Fill(chain.reco_accepted_track_phi[ireco])
			h_reco_accepted_z0_endcap.Fill(chain.reco_accepted_track_z0[ireco])

		# h_reco_accepted_eta_barrel.Fill(chain.reco_accepted_track_eta_barrel[ireco])
		# h_reco_accepted_eta_endcap.Fill(chain.reco_accepted_track_eta_endcap[ireco])
		h_reco_accepted_phi.Fill(chain.reco_accepted_track_phi[ireco])
		h_reco_accepted_m.Fill(chain.reco_accepted_track_m[ireco])
		h_reco_accepted_d0.Fill(chain.reco_accepted_track_d0[ireco])
		h_reco_accepted_z0.Fill(chain.reco_accepted_track_z0[ireco])
		h_reco_accepted_qop.Fill(chain.reco_accepted_track_qop[ireco])
		h_reco_accepted_charge.Fill(chain.reco_accepted_track_charge[ireco])
		h_reco_accepted_chi2.Fill(chain.reco_accepted_track_chi2[ireco])
		h_reco_accepted_EtaPhi.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])


		hit = int(chain.reco_accepted_track_hitPattern[ireco])
		ncoords = len(bin(hit))-2
		for icoord in range(ncoords): 
			if (hit >> icoord & 0x1):
				h_reco_accepted_hitPattern.Fill(icoord)
				histocoordmasketa_reco.Fill(icoord,chain.reco_accepted_track_eta[ireco])
				histocoordmaskz0_reco.Fill(icoord,chain.reco_accepted_track_z0[ireco])
				histocoordmaskd0_reco.Fill(icoord,chain.reco_accepted_track_d0[ireco])
				histocoordmaskphi_reco.Fill(icoord,chain.reco_accepted_track_phi[ireco])

				if icoord == 0:
					h_reco_accepted_EtaPhi0.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 1:
					h_reco_accepted_EtaPhi1.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 2:
					h_reco_accepted_EtaPhi2.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 3:
					h_reco_accepted_EtaPhi3.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 4:
					h_reco_accepted_EtaPhi4.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 5:
					h_reco_accepted_EtaPhi5.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 6:
					h_reco_accepted_EtaPhi6.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 7:
					h_reco_accepted_EtaPhi7.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 8:
					h_reco_accepted_EtaPhi8.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 9:
					h_reco_accepted_EtaPhi9.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 10:
					h_reco_accepted_EtaPhi10.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 11:
					h_reco_accepted_EtaPhi11.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 12:
					h_reco_accepted_EtaPhi12.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 13:
					h_reco_accepted_EtaPhi13.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 14:
					h_reco_accepted_EtaPhi14.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 15:
					h_reco_accepted_EtaPhi15.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 16:
					h_reco_accepted_EtaPhi16.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 17:
					h_reco_accepted_EtaPhi17.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 18:
					h_reco_accepted_EtaPhi18.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])
				if icoord == 19:
					h_reco_accepted_EtaPhi19.Fill(chain.reco_accepted_track_eta[ireco], chain.reco_accepted_track_phi[ireco])

				if icoord == 0 or icoord == 1 or icoord == 2 or icoord == 3 or icoord == 7 or icoord == 8 or icoord == 9 or icoord == 10 or icoord == 20:
					if abs(chain.reco_accepted_track_eta[ireco]) <= 1:
						if icoord == 0:
							newcoord = 0
						if icoord == 1:
							newcoord = 1
						if icoord == 2:
							newcoord = 2
						if icoord == 3:
							newcoord = 3
						if icoord == 7:
							newcoord = 4
						if icoord == 8:
							newcoord = 5
						if icoord == 9:
							newcoord = 6
						if icoord == 10:
							newcoord = 7
						h_reco_accepted_hitPattern_Barrel.Fill(newcoord)
						histocoordmasketa_reco_Barrel.Fill(newcoord,chain.reco_accepted_track_eta[ireco])
						histocoordmaskz0_reco_Barrel.Fill(newcoord,chain.reco_accepted_track_z0[ireco])
						histocoordmaskd0_reco_Barrel.Fill(newcoord,chain.reco_accepted_track_d0[ireco])
						histocoordmaskphi_reco_Barrel.Fill(newcoord,chain.reco_accepted_track_phi[ireco])

						histocoordmasketa_reco_Barrel_noNorm.Fill(newcoord,chain.reco_accepted_track_eta[ireco])
						histocoordmaskz0_reco_Barrel_noNorm.Fill(newcoord,chain.reco_accepted_track_z0[ireco])
						histocoordmaskd0_reco_Barrel_noNorm.Fill(newcoord,chain.reco_accepted_track_d0[ireco])
						histocoordmaskphi_reco_Barrel_noNorm.Fill(newcoord,chain.reco_accepted_track_phi[ireco])
				else:
					if abs(chain.reco_accepted_track_eta[ireco]) >= 1.5:
						if icoord == 4:
							newcoord = 0
						if icoord == 5:
							newcoord = 1
						if icoord == 6:
							newcoord = 2
						if icoord == 11:
							newcoord = 3
						if icoord == 12:
							newcoord = 4
						if icoord == 13:
							newcoord = 5
						if icoord == 14:
							newcoord = 6
						if icoord == 15:
							newcoord = 7
						if icoord == 16:
							newcoord = 8
						if icoord == 17:
							newcoord = 9
						if icoord == 18:
							newcoord = 10
						if icoord == 19:
							newcoord = 11
						h_reco_accepted_hitPattern_EndCap.Fill(newcoord)
						histocoordmasketa_reco_EndCap.Fill(newcoord,chain.reco_accepted_track_eta[ireco])
						histocoordmaskz0_reco_EndCap.Fill(newcoord,chain.reco_accepted_track_z0[ireco])
						histocoordmaskd0_reco_EndCap.Fill(newcoord,chain.reco_accepted_track_d0[ireco])
						histocoordmaskphi_reco_EndCap.Fill(newcoord,chain.reco_accepted_track_phi[ireco])

						histocoordmasketa_reco_EndCap_noNorm.Fill(newcoord,chain.reco_accepted_track_eta[ireco])
						histocoordmaskz0_reco_EndCap_noNorm.Fill(newcoord,chain.reco_accepted_track_z0[ireco])
						histocoordmaskd0_reco_EndCap_noNorm.Fill(newcoord,chain.reco_accepted_track_d0[ireco])
						histocoordmaskphi_reco_EndCap_noNorm.Fill(newcoord,chain.reco_accepted_track_phi[ireco])


	for ireco in range(n_reco_inclusive_tracks):
		h_reco_inclusive_pt.Fill(chain.reco_inclusive_track_pt[ireco])
		h_reco_inclusive_eta.Fill(chain.reco_inclusive_track_eta[ireco])
		h_reco_inclusive_phi.Fill(chain.reco_inclusive_track_phi[ireco])
		h_reco_inclusive_m.Fill(chain.reco_inclusive_track_m[ireco])
		h_reco_inclusive_d0.Fill(chain.reco_inclusive_track_d0[ireco])
		h_reco_inclusive_z0.Fill(chain.reco_inclusive_track_z0[ireco])
		h_reco_inclusive_qop.Fill(chain.reco_inclusive_track_qop[ireco])
		h_reco_inclusive_charge.Fill(chain.reco_inclusive_track_charge[ireco])
		h_reco_inclusive_chi2.Fill(chain.reco_inclusive_track_chi2[ireco])
		h_reco_inclusive_EtaPhi.Fill(chain.reco_inclusive_track_eta[ireco], chain.reco_inclusive_track_phi[ireco])

	if isData == False:
		for itruth in range(n_truth_recoMatch_tracks):
			h_truth_reco_deltaR.Fill(chain.truth_reco_deltaR[itruth])
			h_truth_recoMatch_track_pt.Fill(chain.truth_recoMatch_track_pt[itruth])
			h_truth_recoMatch_track_eta.Fill(chain.truth_recoMatch_track_eta[itruth])
			h_truth_recoMatch_track_phi.Fill(chain.truth_recoMatch_track_phi[itruth])
			h_reco_truthMatch_track_eta.Fill(chain.reco_truthMatch_track_eta[itruth])		
			h_reco_truthMatch_track_phi.Fill(chain.reco_truthMatch_track_phi[itruth])
			h_truth_recoMatch_track_d0.Fill(chain.truth_recoMatch_track_d0[itruth])
			h_truth_recoMatch_track_z0.Fill(chain.truth_recoMatch_track_z0[itruth])
			h_truth_recoMatch_track_EtaPhi.Fill(chain.truth_recoMatch_track_eta[itruth], chain.truth_recoMatch_track_phi[itruth])

		for itruth in range(n_truth_ftkMatch_tracks):
			h_ftk_truth_deltaR.Fill(chain.ftk_truth_deltaR[itruth])
			h_ftk_truthMatch_track_pt.Fill(chain.truth_ftkMatch_track_pt[itruth])
			h_ftk_truthMatch_track_eta.Fill(chain.ftk_truthMatch_track_eta[itruth])
			h_ftk_truthMatch_track_phi.Fill(chain.ftk_truthMatch_track_phi[itruth])
			h_truth_ftkMatch_track_eta.Fill(chain.truth_ftkMatch_track_eta[itruth])
			h_truth_ftkMatch_track_phi.Fill(chain.truth_ftkMatch_track_phi[itruth])
			h_ftk_truthMatch_track_d0.Fill(chain.truth_ftkMatch_track_d0[itruth])
			# h_ftk_truthMatch_track_corrected_d0.Fill(chain.truth_ftkMatch_track_corrected_d0[itruth])
			h_ftk_truthMatch_track_z0.Fill(chain.truth_ftkMatch_track_z0[itruth])
			h_ftk_truthMatch_track_EtaPhi.Fill(chain.ftk_truthMatch_track_eta[itruth], chain.ftk_truthMatch_track_phi[itruth])

		for itruth in range(n_truth_ftkrefitMatch_tracks):
			h_ftk_refit_truth_deltaR.Fill(chain.ftk_refit_reco_deltaR[itruth])
			h_ftk_refit_truthMatch_track_pt.Fill(chain.truth_ftkrefitMatch_track_pt[itruth])
			h_ftk_refit_truthMatch_track_eta.Fill(chain.ftk_refit_truthMatch_track_eta[itruth])
			h_ftk_refit_truthMatch_track_phi.Fill(chain.ftk_refit_truthMatch_track_phi[itruth])
			h_truth_ftkrefitMatch_track_eta.Fill(chain.truth_ftkrefitMatch_track_eta[itruth])
			h_truth_ftkrefitMatch_track_phi.Fill(chain.truth_ftkrefitMatch_track_phi[itruth])
			h_ftk_refit_truthMatch_track_d0.Fill(chain.truth_ftkrefitMatch_track_d0[itruth])
			h_ftk_refit_truthMatch_track_z0.Fill(chain.truth_ftkrefitMatch_track_z0[itruth])
			h_ftk_refit_truthMatch_track_EtaPhi.Fill(chain.ftk_refit_truthMatch_track_eta[itruth], chain.ftk_refit_truthMatch_track_phi[itruth])

	for ireco in range(n_reco_ftkMatch_tracks):
		h_ftk_reco_deltaR.Fill(chain.ftk_reco_deltaR[ireco])
		h_ftk_recoMatch_track_pt.Fill(chain.reco_ftkMatch_track_pt[ireco])
		h_ftk_recoMatch_track_eta.Fill(chain.ftk_recoMatch_track_eta[ireco])
		h_ftk_recoMatch_track_phi.Fill(chain.ftk_recoMatch_track_phi[ireco])
		h_reco_ftkMatch_track_eta.Fill(chain.reco_ftkMatch_track_eta[ireco])
		h_reco_ftkMatch_track_phi.Fill(chain.reco_ftkMatch_track_phi[ireco])
		h_ftk_recoMatch_track_d0.Fill(chain.reco_ftkMatch_track_d0[ireco])
		# h_ftk_recoMatch_track_corrected_d0.Fill(chain.reco_ftkMatch_track_corrected_d0[ireco])
		h_ftk_recoMatch_track_z0.Fill(chain.reco_ftkMatch_track_z0[ireco])
		h_ftk_recoMatch_track_EtaPhi.Fill(chain.ftk_recoMatch_track_eta[ireco], chain.ftk_recoMatch_track_phi[ireco])

	for ireco in range(n_reco_ftkrefitMatch_tracks):
		h_ftk_refit_reco_deltaR.Fill(chain.ftk_refit_reco_deltaR[ireco])
		h_ftk_refit_recoMatch_track_pt.Fill(chain.reco_ftkrefitMatch_track_pt[ireco])
		h_ftk_refit_recoMatch_track_eta.Fill(chain.ftk_refit_recoMatch_track_eta[ireco])
		h_ftk_refit_recoMatch_track_phi.Fill(chain.ftk_refit_recoMatch_track_phi[ireco])
		h_reco_ftkrefitMatch_track_eta.Fill(chain.reco_ftkrefitMatch_track_eta[ireco])
		h_reco_ftkrefitMatch_track_phi.Fill(chain.reco_ftkrefitMatch_track_phi[ireco])
		h_ftk_refit_recoMatch_track_d0.Fill(chain.reco_ftkrefitMatch_track_d0[ireco])
		h_ftk_refit_recoMatch_track_z0.Fill(chain.reco_ftkrefitMatch_track_z0[ireco])
		h_ftk_refit_recoMatch_track_EtaPhi.Fill(chain.ftk_refit_recoMatch_track_eta[ireco], chain.ftk_refit_recoMatch_track_phi[ireco])

	if isData == False:

		for itruth in range(n_truth_tracks):

			h_truth_pt.Fill(chain.truth_track_pt[itruth])
			h_truth_eta.Fill(chain.truth_track_eta[itruth])
			h_truth_phi.Fill(chain.truth_track_phi[itruth])
			h_truth_m.Fill(chain.truth_track_m[itruth])
			h_truth_d0.Fill(chain.truth_track_d0[itruth])
			h_truth_z0.Fill(chain.truth_track_z0[itruth])
			h_truth_qop.Fill(chain.truth_track_qop[itruth])
			h_truth_charge.Fill(chain.truth_track_charge[itruth])
			h_truth_EtaPhi.Fill(chain.truth_track_eta[itruth], chain.truth_track_phi[itruth])

		# if (chain.truth_track_reco_match_prob[itruth]) > 0.5:
		# 	recomatch = chain.truth_track_reco_match[itruth]
		# 	accepted = chain.reco_accepted[recomatch]
		# 	if accepted == 1:
		# 		h_recoMatched_truth_pt.Fill(chain.truth_track_pt[itruth])
		# 		h_recoMatched_truth_eta.Fill(chain.truth_track_eta[itruth])
		# 		h_recoMatched_truth_phi.Fill(chain.truth_track_phi[itruth])
		# 		h_recoMatched_truth_m.Fill(chain.truth_track_m[itruth])
		# 		h_recoMatched_truth_charge.Fill(chain.truth_track_charge[itruth])

		# if (chain.truth_track_ftk_match_prob[itruth]) > 0.5:
		# 	if (chain.ftk_accepted[int(chain.truth_track_ftk_match[itruth])]) == 1:
		# 		h_ftkMatched_truth_pt.Fill(chain.truth_track_pt[itruth])
		# 		h_ftkMatched_truth_eta.Fill(chain.truth_track_eta[itruth])
		# 		h_ftkMatched_truth_phi.Fill(chain.truth_track_phi[itruth])
		# 		h_ftkMatched_truth_m.Fill(chain.truth_track_m[itruth])
		# 		h_ftkMatched_truth_charge.Fill(chain.truth_track_charge[itruth])

		# if (chain.truth_track_ftk_refit_match_prob[itruth] > 0.5):
		# 	if (chain.ftk_refit_accepted[int(chain.truth_track_ftk_refit_match[itruth])] == 1):
		# 		h_ftk_refitMatched_truth_pt.Fill(chain.truth_track_pt[itruth])
		# 		h_ftk_refitMatched_truth_eta.Fill(chain.truth_track_eta[itruth])
		# 		h_ftk_refitMatched_truth_phi.Fill(chain.truth_track_phi[itruth])
		# 		h_ftk_refitMatched_truth_m.Fill(chain.truth_track_m[itruth])
		# 		h_ftk_refitMatched_truth_charge.Fill(chain.truth_track_charge[itruth])


# if isData == False:
## Inclusive
ibinPhi_ftk = 1
while ibinPhi_ftk != nbins+1:
	# print(ibinPhi_ftk)
	# print("bin content", h_ftk_accepted_phi.GetBinContent(ibinPhi_ftk))
	# print("integral", h_ftk_accepted_phi.Integral(ibinPhi_ftk,ibinPhi_ftk))
	# print(h_ftk_accepted_phi.Integral(ibinPhi_ftk,ibinPhi_ftk))
	if h_ftk_accepted_phi.Integral(ibinPhi_ftk,ibinPhi_ftk) == 0:
		colnormPhi_ftk = 1
	else:
		colnormPhi_ftk = 1.0/h_ftk_accepted_phi.Integral(ibinPhi_ftk,ibinPhi_ftk);
	# print(colnormPhi_ftk)
	xbinsPhi_ftk = histocoordmaskphi_ftk.GetNbinsX()
	# print(xbinsPhi_ftk)
	jbin = 1
	while jbin != xbinsPhi_ftk+1:
		# print jbin
		histocoordmaskphi_ftk.SetBinContent(jbin,ibinPhi_ftk,histocoordmaskphi_ftk.GetBinContent(jbin,ibinPhi_ftk)*colnormPhi_ftk);
		jbin += 1
	ibinPhi_ftk+=1
ibinEta_ftk = 1
while ibinEta_ftk != nbins+1:
	if h_ftk_accepted_eta.Integral(ibinEta_ftk,ibinEta_ftk) == 0:
		colnormEta_ftk = 1
	else:
		colnormEta_ftk = 1.0/h_ftk_accepted_eta.Integral(ibinEta_ftk,ibinEta_ftk);
	xbinsEta_ftk = histocoordmasketa_ftk.GetNbinsX()
	jbin = 1
	while jbin != xbinsEta_ftk+1:
		histocoordmasketa_ftk.SetBinContent(jbin,ibinEta_ftk,histocoordmasketa_ftk.GetBinContent(jbin,ibinEta_ftk)*colnormEta_ftk);
		jbin += 1
	ibinEta_ftk+=1
ibinZ0_ftk = 1
while ibinZ0_ftk != nbins+1:
	if h_ftk_accepted_z0.Integral(ibinZ0_ftk,ibinZ0_ftk) == 0:
		colnormZ0_ftk = 1
	else:
		colnormZ0_ftk = 1.0/h_ftk_accepted_z0.Integral(ibinZ0_ftk,ibinZ0_ftk);
	xbinsZ0_ftk = histocoordmaskz0_ftk.GetNbinsX()
	jbin = 1
	while jbin != xbinsZ0_ftk+1:
		histocoordmaskz0_ftk.SetBinContent(jbin,ibinZ0_ftk,histocoordmaskz0_ftk.GetBinContent(jbin,ibinZ0_ftk)*colnormZ0_ftk);
		jbin += 1
	ibinZ0_ftk+=1
ibinPhi_ftkrefit = 1
while ibinPhi_ftkrefit != nbins+1:
	if h_ftk_refit_accepted_phi.Integral(ibinPhi_ftkrefit,ibinPhi_ftkrefit) == 0:
		colnormPhi_ftkrefit = 1
	else:
		colnormPhi_ftkrefit = 1.0/h_ftk_refit_accepted_phi.Integral(ibinPhi_ftkrefit,ibinPhi_ftkrefit);
	xbinsPhi_ftkrefit = histocoordmaskphi_ftkrefit.GetNbinsX()
	jbin = 1
	while jbin != xbinsPhi_ftkrefit+1:
		histocoordmaskphi_ftkrefit.SetBinContent(jbin,ibinPhi_ftkrefit,histocoordmaskphi_ftkrefit.GetBinContent(jbin,ibinPhi_ftkrefit)*colnormPhi_ftkrefit);
		jbin += 1
	ibinPhi_ftkrefit+=1
ibinEta_ftkrefit = 1
while ibinEta_ftkrefit != nbins+1:
	if h_ftk_refit_accepted_eta.Integral(ibinEta_ftkrefit,ibinEta_ftkrefit) == 0:
		colnormEta_ftkrefit = 1
	else:
		colnormEta_ftkrefit = 1.0/h_ftk_refit_accepted_eta.Integral(ibinEta_ftkrefit,ibinEta_ftkrefit);
	xbinsEta_ftkrefit = histocoordmasketa_ftkrefit.GetNbinsX()
	jbin = 1
	while jbin != xbinsEta_ftkrefit+1:
		histocoordmasketa_ftkrefit.SetBinContent(jbin,ibinEta_ftkrefit,histocoordmasketa_ftkrefit.GetBinContent(jbin,ibinEta_ftkrefit)*colnormEta_ftkrefit);
		jbin += 1
	ibinEta_ftkrefit+=1
ibinZ0_ftkrefit = 1
while ibinZ0_ftkrefit != nbins+1:
	if h_ftk_refit_accepted_z0.Integral(ibinZ0_ftkrefit,ibinZ0_ftkrefit) == 0:
		colnormZ0_ftkrefit = 1
	else:
		colnormZ0_ftkrefit = 1.0/h_ftk_refit_accepted_z0.Integral(ibinZ0_ftkrefit,ibinZ0_ftkrefit);
	xbinsZ0_ftkrefit = histocoordmaskz0_ftkrefit.GetNbinsX()
	jbin = 1
	while jbin != xbinsZ0_ftkrefit+1:
		histocoordmaskz0_ftkrefit.SetBinContent(jbin,ibinZ0_ftkrefit,histocoordmaskz0_ftkrefit.GetBinContent(jbin,ibinZ0_ftkrefit)*colnormZ0_ftkrefit);
		jbin += 1
	ibinZ0_ftkrefit+=1
ibinPhi_reco = 1
while ibinPhi_reco != nbins+1:
	if h_reco_accepted_phi.Integral(ibinPhi_reco,ibinPhi_reco) == 0:
		colnormPhi_reco = 1
	else:
		colnormPhi_reco = 1.0/h_reco_accepted_phi.Integral(ibinPhi_reco,ibinPhi_reco);
	xbinsPhi_reco = histocoordmaskphi_reco.GetNbinsX()
	jbin = 1
	while jbin != xbinsPhi_reco+1:
		histocoordmaskphi_reco.SetBinContent(jbin,ibinPhi_reco,histocoordmaskphi_reco.GetBinContent(jbin,ibinPhi_reco)*colnormPhi_reco);
		jbin += 1
	ibinPhi_reco+=1
ibinEta_reco = 1
while ibinEta_reco != nbins+1:
	if h_reco_accepted_eta.Integral(ibinEta_reco,ibinEta_reco) == 0:
		colnormEta_reco = 1
	else:
		colnormEta_reco = 1.0/h_reco_accepted_eta.Integral(ibinEta_reco,ibinEta_reco);
	xbinsEta_reco = histocoordmasketa_reco.GetNbinsX()
	jbin = 1
	while jbin != xbinsEta_reco+1:
		histocoordmasketa_reco.SetBinContent(jbin,ibinEta_reco,histocoordmasketa_reco.GetBinContent(jbin,ibinEta_reco)*colnormEta_reco);
		jbin += 1
	ibinEta_reco+=1
ibinZ0_reco = 1
while ibinZ0_reco != nbins+1:
	if h_reco_accepted_z0.Integral(ibinZ0_reco,ibinZ0_reco) == 0:
		colnormZ0_reco = 1
	else:
		colnormZ0_reco = 1.0/h_reco_accepted_z0.Integral(ibinZ0_reco,ibinZ0_reco);
	xbinsZ0_reco = histocoordmaskz0_reco.GetNbinsX()
	jbin = 1
	while jbin != xbinsZ0_reco+1:
		histocoordmaskz0_reco.SetBinContent(jbin,ibinZ0_reco,histocoordmaskz0_reco.GetBinContent(jbin,ibinZ0_reco)*colnormZ0_reco);
		jbin += 1
	ibinZ0_reco+=1


######### EndCap
ibinPhi_ftk = 1
while ibinPhi_ftk != nbins+1:
	if h_ftk_accepted_phi_endcap.Integral(ibinPhi_ftk,ibinPhi_ftk) == 0:
		colnormPhi_ftk == 1
	else:
		colnormPhi_ftk = 1.0/h_ftk_accepted_phi_endcap.Integral(ibinPhi_ftk,ibinPhi_ftk);
	xbinsPhi_ftk = histocoordmaskphi_ftk_EndCap.GetNbinsX()
	jbin = 1
	while jbin != xbinsPhi_ftk+1:
		histocoordmaskphi_ftk_EndCap.SetBinContent(jbin,ibinPhi_ftk,histocoordmaskphi_ftk_EndCap.GetBinContent(jbin,ibinPhi_ftk)*colnormPhi_ftk);
		jbin += 1
	ibinPhi_ftk+=1

ibinEta_ftk = 1
while ibinEta_ftk != nbins+1:
	if h_ftk_accepted_eta_endcap.Integral(ibinEta_ftk,ibinEta_ftk) == 0:
		colnormEta_ftk = 1
	else:
		colnormEta_ftk = 1.0/h_ftk_accepted_eta_endcap.Integral(ibinEta_ftk,ibinEta_ftk);
	xbinsEta_ftk = histocoordmasketa_ftk_EndCap.GetNbinsX()
	jbin = 1
	while jbin != xbinsEta_ftk+1:
		histocoordmasketa_ftk_EndCap.SetBinContent(jbin,ibinEta_ftk,histocoordmasketa_ftk_EndCap.GetBinContent(jbin,ibinEta_ftk)*colnormEta_ftk);
		jbin += 1
	ibinEta_ftk+=1
ibinZ0_ftk = 1
while ibinZ0_ftk != nbins+1:
	if h_ftk_accepted_z0_endcap.Integral(ibinZ0_ftk,ibinZ0_ftk) == 0:
		colnormZ0_ftk = 1
	else:
		colnormZ0_ftk = 1.0/h_ftk_accepted_z0_endcap.Integral(ibinZ0_ftk,ibinZ0_ftk);
	xbinsZ0_ftk = histocoordmaskz0_ftk_EndCap.GetNbinsX()
	jbin = 1
	while jbin != xbinsZ0_ftk+1:
		histocoordmaskz0_ftk_EndCap.SetBinContent(jbin,ibinZ0_ftk,histocoordmaskz0_ftk_EndCap.GetBinContent(jbin,ibinZ0_ftk)*colnormZ0_ftk);
		jbin += 1
	ibinZ0_ftk+=1
ibinD0_ftk = 1
while ibinD0_ftk != nbins+1:
	if h_ftk_accepted_d0_endcap.Integral(ibinD0_ftk,ibinD0_ftk) == 0:
		colnormD0_ftk = 1
	else:
		colnormD0_ftk = 1.0/h_ftk_accepted_d0_endcap.Integral(ibinD0_ftk,ibinD0_ftk);
	xbinsD0_ftk = histocoordmaskd0_ftk_EndCap.GetNbinsX()
	jbin = 1
	while jbin != xbinsD0_ftk+1:
		histocoordmaskd0_ftk_EndCap.SetBinContent(jbin,ibinD0_ftk,histocoordmaskd0_ftk_EndCap.GetBinContent(jbin,ibinD0_ftk)*colnormD0_ftk);
		jbin += 1
	ibinD0_ftk+=1

ibinPhi_ftkrefit = 1
while ibinPhi_ftkrefit != nbins+1:
	if h_ftk_refit_accepted_phi_endcap.Integral(ibinPhi_ftkrefit,ibinPhi_ftkrefit) == 0:
		colnormPhi_ftkrefit = 1
	else:
		colnormPhi_ftkrefit = 1.0/h_ftk_refit_accepted_phi_endcap.Integral(ibinPhi_ftkrefit,ibinPhi_ftkrefit);
	xbinsPhi_ftkrefit = histocoordmaskphi_ftkrefit_EndCap.GetNbinsX()
	jbin = 1
	while jbin != xbinsPhi_ftkrefit+1:
		histocoordmaskphi_ftkrefit_EndCap.SetBinContent(jbin,ibinPhi_ftkrefit,histocoordmaskphi_ftkrefit_EndCap.GetBinContent(jbin,ibinPhi_ftkrefit)*colnormPhi_ftkrefit);
		jbin += 1
	ibinPhi_ftkrefit+=1
ibinEta_ftkrefit = 1
while ibinEta_ftkrefit != nbins+1:
	if h_ftk_refit_accepted_eta_endcap.Integral(ibinEta_ftkrefit,ibinEta_ftkrefit) == 0:
		colnormEta_ftkrefit = 1
	else: 
		colnormEta_ftkrefit = 1.0/h_ftk_refit_accepted_eta_endcap.Integral(ibinEta_ftkrefit,ibinEta_ftkrefit);
	xbinsEta_ftkrefit = histocoordmasketa_ftkrefit_EndCap.GetNbinsX()
	jbin = 1
	while jbin != xbinsEta_ftkrefit+1:
		histocoordmasketa_ftkrefit_EndCap.SetBinContent(jbin,ibinEta_ftkrefit,histocoordmasketa_ftkrefit_EndCap.GetBinContent(jbin,ibinEta_ftkrefit)*colnormEta_ftkrefit);
		jbin += 1
	ibinEta_ftkrefit+=1
ibinZ0_ftkrefit = 1
while ibinZ0_ftkrefit != nbins+1:
	if h_ftk_refit_accepted_z0_endcap.Integral(ibinZ0_ftkrefit,ibinZ0_ftkrefit) == 0:
		colnormZ0_ftkrefit = 1
	else:
		colnormZ0_ftkrefit = 1.0/h_ftk_refit_accepted_z0_endcap.Integral(ibinZ0_ftkrefit,ibinZ0_ftkrefit);
	xbinsZ0_ftkrefit = histocoordmaskz0_ftkrefit_EndCap.GetNbinsX()
	jbin = 1
	while jbin != xbinsZ0_ftkrefit+1:
		histocoordmaskz0_ftkrefit_EndCap.SetBinContent(jbin,ibinZ0_ftkrefit,histocoordmaskz0_ftkrefit_EndCap.GetBinContent(jbin,ibinZ0_ftkrefit)*colnormZ0_ftkrefit);
		jbin += 1
	ibinZ0_ftkrefit+=1
ibinD0_ftkrefit = 1
while ibinD0_ftkrefit != nbins+1:
	if h_ftk_refit_accepted_d0_endcap.Integral(ibinD0_ftkrefit,ibinD0_ftkrefit) == 0:
		colnormD0_ftkrefit = 1
	else:
		colnormD0_ftkrefit = 1.0/h_ftk_refit_accepted_d0_endcap.Integral(ibinD0_ftkrefit,ibinD0_ftkrefit);
	xbinsD0_ftkrefit = histocoordmaskd0_ftkrefit_EndCap.GetNbinsX()
	jbin = 1
	while jbin != xbinsD0_ftkrefit+1:
		histocoordmaskd0_ftkrefit_EndCap.SetBinContent(jbin,ibinD0_ftkrefit,histocoordmaskd0_ftkrefit_EndCap.GetBinContent(jbin,ibinD0_ftkrefit)*colnormD0_ftkrefit);
		jbin += 1
	ibinD0_ftkrefit+=1
ibinPhi_reco = 1
while ibinPhi_reco != nbins+1:
	if h_reco_accepted_phi_endcap.Integral(ibinPhi_reco,ibinPhi_reco) == 0:
		colnormPhi_reco = 1
	else: 
		colnormPhi_reco = 1.0/h_reco_accepted_phi_endcap.Integral(ibinPhi_reco,ibinPhi_reco);
	xbinsPhi_reco = histocoordmaskphi_reco_EndCap.GetNbinsX()
	jbin = 1
	while jbin != xbinsPhi_reco+1:
		histocoordmaskphi_reco_EndCap.SetBinContent(jbin,ibinPhi_reco,histocoordmaskphi_reco_EndCap.GetBinContent(jbin,ibinPhi_reco)*colnormPhi_reco);
		jbin += 1
	ibinPhi_reco+=1
ibinEta_reco = 1
while ibinEta_reco != nbins+1:
	if h_reco_accepted_eta_endcap.Integral(ibinEta_reco,ibinEta_reco) == 0:
		colnormEta_reco = 1
	else:
		colnormEta_reco = 1.0/h_reco_accepted_eta_endcap.Integral(ibinEta_reco,ibinEta_reco);
	xbinsEta_reco = histocoordmasketa_reco_EndCap.GetNbinsX()
	jbin = 1
	while jbin != xbinsEta_reco+1:
		histocoordmasketa_reco_EndCap.SetBinContent(jbin,ibinEta_reco,histocoordmasketa_reco_EndCap.GetBinContent(jbin,ibinEta_reco)*colnormEta_reco);
		jbin += 1
	ibinEta_reco+=1
ibinZ0_reco = 1
while ibinZ0_reco != nbins+1:
	if h_reco_accepted_z0_endcap.Integral(ibinZ0_reco,ibinZ0_reco) == 0:
		colnormZ0_reco = 1
	else:
		colnormZ0_reco = 1.0/h_reco_accepted_z0_endcap.Integral(ibinZ0_reco,ibinZ0_reco);
	xbinsZ0_reco = histocoordmaskz0_reco_EndCap.GetNbinsX()
	jbin = 1
	while jbin != xbinsZ0_reco+1:
		histocoordmaskz0_reco_EndCap.SetBinContent(jbin,ibinZ0_reco,histocoordmaskz0_reco_EndCap.GetBinContent(jbin,ibinZ0_reco)*colnormZ0_reco);
		jbin += 1
	ibinZ0_reco+=1
ibinD0_reco = 1
while ibinD0_reco != nbins+1:
	if h_reco_accepted_d0_endcap.Integral(ibinD0_reco,ibinD0_reco) == 0:
		colnormD0_reco = 1
	else:
		colnormD0_reco = 1.0/h_reco_accepted_d0_endcap.Integral(ibinD0_reco,ibinD0_reco);
	xbinsD0_reco = histocoordmaskd0_reco_EndCap.GetNbinsX()
	jbin = 1
	while jbin != xbinsD0_reco+1:
		histocoordmaskd0_reco_EndCap.SetBinContent(jbin,ibinD0_reco,histocoordmaskd0_reco_EndCap.GetBinContent(jbin,ibinD0_reco)*colnormD0_reco);
		jbin += 1
	ibinD0_reco+=1
## Barrel
ibinPhi_ftk = 1
while ibinPhi_ftk != nbins+1:
	if h_ftk_accepted_phi_barrel.Integral(ibinPhi_ftk,ibinPhi_ftk) == 0:
		colnormPhi_ftk = 1
	else:
		colnormPhi_ftk = 1.0/h_ftk_accepted_phi_barrel.Integral(ibinPhi_ftk,ibinPhi_ftk);
	xbinsPhi_ftk = histocoordmaskphi_ftk_Barrel.GetNbinsX()
	jbin = 1
	while jbin != xbinsPhi_ftk+1:
		histocoordmaskphi_ftk_Barrel.SetBinContent(jbin,ibinPhi_ftk,histocoordmaskphi_ftk_Barrel.GetBinContent(jbin,ibinPhi_ftk)*colnormPhi_ftk);
		jbin += 1
	ibinPhi_ftk+=1
ibinEta_ftk = 1
while ibinEta_ftk != nbins+1:
	if h_ftk_accepted_eta_barrel.Integral(ibinEta_ftk,ibinEta_ftk) == 0:
		colnormEta_ftk = 1
	else:
		colnormEta_ftk = 1.0/h_ftk_accepted_eta_barrel.Integral(ibinEta_ftk,ibinEta_ftk);
	xbinsEta_ftk = histocoordmasketa_ftk_Barrel.GetNbinsX()
	jbin = 1
	while jbin != xbinsEta_ftk+1:
		histocoordmasketa_ftk_Barrel.SetBinContent(jbin,ibinEta_ftk,histocoordmasketa_ftk_Barrel.GetBinContent(jbin,ibinEta_ftk)*colnormEta_ftk);
		jbin += 1
	ibinEta_ftk+=1
ibinZ0_ftk = 1
while ibinZ0_ftk != nbins+1:
	if h_ftk_accepted_z0_barrel.Integral(ibinZ0_ftk,ibinZ0_ftk) == 0:
		colnormZ0_ftk = 1
	else:
		colnormZ0_ftk = 1.0/h_ftk_accepted_z0_barrel.Integral(ibinZ0_ftk,ibinZ0_ftk);
	xbinsZ0_ftk = histocoordmaskz0_ftk_Barrel.GetNbinsX()
	jbin = 1
	while jbin != xbinsZ0_ftk+1:
		histocoordmaskz0_ftk_Barrel.SetBinContent(jbin,ibinZ0_ftk,histocoordmaskz0_ftk_Barrel.GetBinContent(jbin,ibinZ0_ftk)*colnormZ0_ftk);
		jbin += 1
	ibinZ0_ftk+=1
ibinD0_ftk = 1
while ibinD0_ftk != nbins+1:
	if h_ftk_accepted_d0_barrel.Integral(ibinD0_ftk,ibinD0_ftk) == 0:
		colnormD0_ftk = 1
	else:
		colnormD0_ftk = 1.0/h_ftk_accepted_d0_barrel.Integral(ibinD0_ftk,ibinD0_ftk);
	xbinsD0_ftk = histocoordmaskd0_ftk_Barrel.GetNbinsX()
	jbin = 1
	while jbin != xbinsD0_ftk+1:
		histocoordmaskd0_ftk_Barrel.SetBinContent(jbin,ibinD0_ftk,histocoordmaskd0_ftk_Barrel.GetBinContent(jbin,ibinD0_ftk)*colnormD0_ftk);
		jbin += 1
	ibinD0_ftk+=1
ibinPhi_ftkrefit = 1
while ibinPhi_ftkrefit != nbins+1:
	if h_ftk_refit_accepted_phi_barrel.Integral(ibinPhi_ftkrefit,ibinPhi_ftkrefit) == 0:
		colnormPhi_ftkrefit = 1
	else:
		colnormPhi_ftkrefit = 1.0/h_ftk_refit_accepted_phi_barrel.Integral(ibinPhi_ftkrefit,ibinPhi_ftkrefit);
	xbinsPhi_ftkrefit = histocoordmaskphi_ftkrefit_Barrel.GetNbinsX()
	jbin = 1
	while jbin != xbinsPhi_ftkrefit+1:
		histocoordmaskphi_ftkrefit_Barrel.SetBinContent(jbin,ibinPhi_ftkrefit,histocoordmaskphi_ftkrefit_Barrel.GetBinContent(jbin,ibinPhi_ftkrefit)*colnormPhi_ftkrefit);
		jbin += 1
	ibinPhi_ftkrefit+=1
ibinEta_ftkrefit = 1
while ibinEta_ftkrefit != nbins+1:
	if h_ftk_refit_accepted_eta_barrel.Integral(ibinEta_ftkrefit,ibinEta_ftkrefit) == 0:
		colnormEta_ftkrefit = 1
	else:
		colnormEta_ftkrefit = 1.0/h_ftk_refit_accepted_eta_barrel.Integral(ibinEta_ftkrefit,ibinEta_ftkrefit);
	xbinsEta_ftkrefit = histocoordmasketa_ftkrefit_Barrel.GetNbinsX()
	jbin = 1
	while jbin != xbinsEta_ftkrefit+1:
		histocoordmasketa_ftkrefit_Barrel.SetBinContent(jbin,ibinEta_ftkrefit,histocoordmasketa_ftkrefit_Barrel.GetBinContent(jbin,ibinEta_ftkrefit)*colnormEta_ftkrefit);
		jbin += 1
	ibinEta_ftkrefit+=1
ibinZ0_ftkrefit = 1
while ibinZ0_ftkrefit != nbins+1:
	if h_ftk_refit_accepted_z0_barrel.Integral(ibinZ0_ftkrefit,ibinZ0_ftkrefit) == 0:
		colnormZ0_ftkrefit = 1
	else:
		colnormZ0_ftkrefit = 1.0/h_ftk_refit_accepted_z0_barrel.Integral(ibinZ0_ftkrefit,ibinZ0_ftkrefit);
	xbinsZ0_ftkrefit = histocoordmaskz0_ftkrefit_Barrel.GetNbinsX()
	jbin = 1
	while jbin != xbinsZ0_ftkrefit+1:
		histocoordmaskz0_ftkrefit_Barrel.SetBinContent(jbin,ibinZ0_ftkrefit,histocoordmaskz0_ftkrefit_Barrel.GetBinContent(jbin,ibinZ0_ftkrefit)*colnormZ0_ftkrefit);
		jbin += 1
	ibinZ0_ftkrefit+=1
ibinD0_ftkrefit = 1
while ibinD0_ftkrefit != nbins+1:
	if h_ftk_refit_accepted_d0_barrel.Integral(ibinD0_ftkrefit,ibinD0_ftkrefit) == 0:
		colnormD0_ftkrefit = 1
	else:
		colnormD0_ftkrefit = 1.0/h_ftk_refit_accepted_d0_barrel.Integral(ibinD0_ftkrefit,ibinD0_ftkrefit);
	xbinsD0_ftkrefit = histocoordmaskd0_ftkrefit_Barrel.GetNbinsX()
	jbin = 1
	while jbin != xbinsD0_ftkrefit+1:
		histocoordmaskd0_ftkrefit_Barrel.SetBinContent(jbin,ibinD0_ftkrefit,histocoordmaskd0_ftkrefit_Barrel.GetBinContent(jbin,ibinD0_ftkrefit)*colnormD0_ftkrefit);
		jbin += 1
	ibinD0_ftkrefit+=1
ibinPhi_reco = 1
while ibinPhi_reco != nbins+1:
	if h_reco_accepted_phi_barrel.Integral(ibinPhi_reco,ibinPhi_reco) == 0:
		colnormPhi_reco = 1
	else:
		colnormPhi_reco = 1.0/h_reco_accepted_phi_barrel.Integral(ibinPhi_reco,ibinPhi_reco);
	xbinsPhi_reco = histocoordmaskphi_reco_Barrel.GetNbinsX()
	jbin = 1
	while jbin != xbinsPhi_reco+1:
		histocoordmaskphi_reco_Barrel.SetBinContent(jbin,ibinPhi_reco,histocoordmaskphi_reco_Barrel.GetBinContent(jbin,ibinPhi_reco)*colnormPhi_reco);
		jbin += 1
	ibinPhi_reco+=1
ibinEta_reco = 1
while ibinEta_reco != nbins+1:
	if h_reco_accepted_eta_barrel.Integral(ibinEta_reco,ibinEta_reco) == 0:
		colnormEta_reco = 1
	else:
		colnormEta_reco = 1.0/h_reco_accepted_eta_barrel.Integral(ibinEta_reco,ibinEta_reco);
	xbinsEta_reco = histocoordmasketa_reco_Barrel.GetNbinsX()
	jbin = 1
	while jbin != xbinsEta_reco+1:
		histocoordmasketa_reco_Barrel.SetBinContent(jbin,ibinEta_reco,histocoordmasketa_reco_Barrel.GetBinContent(jbin,ibinEta_reco)*colnormEta_reco);
		jbin += 1
	ibinEta_reco+=1
ibinZ0_reco = 1
while ibinZ0_reco != nbins+1:
	if h_reco_accepted_z0_barrel.Integral(ibinZ0_reco,ibinZ0_reco) == 0:
		colnormZ0_reco = 1
	else:
		colnormZ0_reco = 1.0/h_reco_accepted_z0_barrel.Integral(ibinZ0_reco,ibinZ0_reco);
	xbinsZ0_reco = histocoordmaskz0_reco_Barrel.GetNbinsX()
	jbin = 1
	while jbin != xbinsZ0_reco+1:
		histocoordmaskz0_reco_Barrel.SetBinContent(jbin,ibinZ0_reco,histocoordmaskz0_reco_Barrel.GetBinContent(jbin,ibinZ0_reco)*colnormZ0_reco);
		jbin += 1
	ibinZ0_reco+=1
ibinD0_reco = 1
while ibinD0_reco != nbins+1:
	if h_reco_accepted_d0_barrel.Integral(ibinD0_reco,ibinD0_reco) == 0:
		colnormD0_reco = 1
	else:
		colnormD0_reco = 1.0/h_reco_accepted_d0_barrel.Integral(ibinD0_reco,ibinD0_reco);
	xbinsD0_reco = histocoordmaskd0_reco_Barrel.GetNbinsX()
	jbin = 1
	while jbin != xbinsD0_reco+1:
		histocoordmaskd0_reco_Barrel.SetBinContent(jbin,ibinD0_reco,histocoordmaskd0_reco_Barrel.GetBinContent(jbin,ibinD0_reco)*colnormD0_reco);
		jbin += 1
	ibinD0_reco+=1

for hist in hist2D:
	hist2dSettings(hist)

for hist in histListInclusive:
	histLabelsInclusive(hist)

for hist in histListBarrel:
	histLabelsBarrel(hist)

for hist in histListEndCap:
	histLabelsEndCap(hist)

if isData == False:
	tgae_truth_reco_effi_vs_truth_pt       =  TGraphAsymmErrors()
	tgae_truth_reco_effi_vs_truth_eta      =  TGraphAsymmErrors()
	tgae_truth_reco_effi_vs_truth_phi      =  TGraphAsymmErrors()
	tgae_truth_reco_effi_vs_truth_m        =  TGraphAsymmErrors()
	tgae_truth_reco_effi_vs_truth_d0       =  TGraphAsymmErrors()
	tgae_truth_reco_effi_vs_truth_z0       =  TGraphAsymmErrors()

	tgae_truth_ftk_effi_vs_truth_pt        =  TGraphAsymmErrors()
	tgae_truth_ftk_effi_vs_truth_eta       =  TGraphAsymmErrors()
	tgae_truth_ftk_effi_vs_truth_phi       =  TGraphAsymmErrors()
	tgae_truth_ftk_effi_vs_truth_m         =  TGraphAsymmErrors()
	tgae_truth_ftk_effi_vs_truth_d0        =  TGraphAsymmErrors()
	tgae_truth_ftk_effi_vs_truth_z0        =  TGraphAsymmErrors()

	tgae_truth_ftk_refit_effi_vs_truth_pt  =  TGraphAsymmErrors()
	tgae_truth_ftk_refit_effi_vs_truth_eta =  TGraphAsymmErrors()
	tgae_truth_ftk_refit_effi_vs_truth_phi =  TGraphAsymmErrors()
	tgae_truth_ftk_refit_effi_vs_truth_m   =  TGraphAsymmErrors()
	tgae_truth_ftk_refit_effi_vs_truth_d0  =  TGraphAsymmErrors()
	tgae_truth_ftk_refit_effi_vs_truth_z0  =  TGraphAsymmErrors()

# tgae_muon_truth_reco_effi_vs_truth_pt       =  TGraphAsymmErrors()
# tgae_muon_truth_reco_effi_vs_truth_eta      =  TGraphAsymmErrors()
# tgae_muon_truth_reco_effi_vs_truth_phi      =  TGraphAsymmErrors()
# tgae_muon_truth_reco_effi_vs_truth_m        =  TGraphAsymmErrors()
# tgae_muon_truth_reco_effi_vs_truth_d0       =  TGraphAsymmErrors()
# tgae_muon_truth_reco_effi_vs_truth_z0       =  TGraphAsymmErrors()

# tgae_muon_truth_ftk_effi_vs_truth_pt        =  TGraphAsymmErrors()
# tgae_muon_truth_ftk_effi_vs_truth_eta       =  TGraphAsymmErrors()
# tgae_muon_truth_ftk_effi_vs_truth_phi       =  TGraphAsymmErrors()
# tgae_muon_truth_ftk_effi_vs_truth_m         =  TGraphAsymmErrors()
# tgae_muon_truth_ftk_effi_vs_truth_d0        =  TGraphAsymmErrors()
# tgae_muon_truth_ftk_effi_vs_truth_z0        =  TGraphAsymmErrors()

# tgae_muon_truth_ftk_refit_effi_vs_truth_pt  =  TGraphAsymmErrors()
# tgae_muon_truth_ftk_refit_effi_vs_truth_eta =  TGraphAsymmErrors()
# tgae_muon_truth_ftk_refit_effi_vs_truth_phi =  TGraphAsymmErrors()
# tgae_muon_truth_ftk_refit_effi_vs_truth_m   =  TGraphAsymmErrors()
# tgae_muon_truth_ftk_refit_effi_vs_truth_d0  =  TGraphAsymmErrors()
# tgae_muon_truth_ftk_refit_effi_vs_truth_z0  =  TGraphAsymmErrors()

tgae_reco_ftk_effi_vs_reco_pt        =  TGraphAsymmErrors()
tgae_reco_ftk_effi_vs_reco_eta       =  TGraphAsymmErrors()
tgae_reco_ftk_effi_vs_reco_phi       =  TGraphAsymmErrors()
# tgae_reco_ftk_effi_vs_reco_m         =  TGraphAsymmErrors()
tgae_reco_ftk_effi_vs_reco_d0        =  TGraphAsymmErrors()
tgae_reco_ftk_effi_vs_reco_z0        =  TGraphAsymmErrors()

tgae_reco_ftk_refit_effi_vs_reco_pt  =  TGraphAsymmErrors()
tgae_reco_ftk_refit_effi_vs_reco_eta =  TGraphAsymmErrors()
tgae_reco_ftk_refit_effi_vs_reco_phi =  TGraphAsymmErrors()
# tgae_reco_ftk_refit_effi_vs_reco_m   =  TGraphAsymmErrors()
tgae_reco_ftk_refit_effi_vs_reco_d0  =  TGraphAsymmErrors()
tgae_reco_ftk_refit_effi_vs_reco_z0  =  TGraphAsymmErrors()

if isData == False:
	tgae_truth_reco_effi_vs_truth_pt.Divide(h_truth_recoMatch_track_pt, h_truth_pt, "e0")    ;tgae_truth_reco_effi_vs_truth_pt.SetNameTitle("effi_truth_reco_pt",";Truth pT [GeV];Efficiency w.r.t. Truth")
	tgae_truth_reco_effi_vs_truth_eta.Divide(h_truth_recoMatch_track_eta, h_truth_eta, "e0") ;tgae_truth_reco_effi_vs_truth_eta.SetNameTitle("effi_truth_reco_eta",";Truth eta;Efficiency w.r.t. Truth")
	tgae_truth_reco_effi_vs_truth_phi.Divide(h_truth_recoMatch_track_phi, h_truth_phi, "e0") ;tgae_truth_reco_effi_vs_truth_phi.SetNameTitle("effi_truth_reco_phi",";Truth phi;Efficiency w.r.t. Truth")
	# tgae_truth_reco_effi_vs_truth_m.Divide(h_recoMatched_truth_m, h_truth_m, "e0")         ;tgae_truth_reco_effi_vs_truth_m.SetNameTitle("effi_truth_reco_m",";m [GeV];Efficiency w.r.t. Truth")
	tgae_truth_reco_effi_vs_truth_d0.Divide(h_truth_recoMatch_track_d0, h_truth_d0, "e0")    ;tgae_truth_reco_effi_vs_truth_d0.SetNameTitle("effi_truth_reco_d0",";Truth d0 [mm];Efficiency w.r.t. Truth")
	tgae_truth_reco_effi_vs_truth_z0.Divide(h_truth_recoMatch_track_z0, h_truth_z0, "e0")    ;tgae_truth_reco_effi_vs_truth_z0.SetNameTitle("effi_truth_reco_z0",";Truth z0 [mm];Efficiency w.r.t. Truth")

	tgae_truth_ftk_effi_vs_truth_pt.Divide(h_ftk_truthMatch_track_pt, h_truth_pt, "e0")     ;tgae_truth_ftk_effi_vs_truth_pt.SetNameTitle("effi_truth_ftk_pt",";Truth pT [GeV];Efficiency w.r.t. Truth")
	tgae_truth_ftk_effi_vs_truth_eta.Divide(h_truth_ftkMatch_track_eta, h_truth_eta, "e0")  ;tgae_truth_ftk_effi_vs_truth_eta.SetNameTitle("effi_truth_ftk_eta",";Truth eta;Efficiency w.r.t. Truth")
	tgae_truth_ftk_effi_vs_truth_phi.Divide(h_truth_ftkMatch_track_phi, h_truth_phi, "e0")  ;tgae_truth_ftk_effi_vs_truth_phi.SetNameTitle("effi_truth_ftk_phi",";Truth phi;Efficiency w.r.t. Truth")
	# tgae_truth_ftk_effi_vs_truth_m.Divide(h_ftkMatched_truth_m, h_truth_m, "e0")          ;tgae_truth_ftk_effi_vs_truth_m.SetNameTitle("effi_truth_ftk_m",";m [GeV];Efficiency w.r.t. Truth")
	tgae_truth_ftk_effi_vs_truth_d0.Divide(h_ftk_truthMatch_track_d0, h_truth_d0, "e0")     ;tgae_truth_ftk_effi_vs_truth_d0.SetNameTitle("effi_truth_ftk_d0",";Truth d0 [mm];Efficiency w.r.t. Truth")
	tgae_truth_ftk_effi_vs_truth_z0.Divide(h_ftk_truthMatch_track_z0, h_truth_z0, "e0")     ;tgae_truth_ftk_effi_vs_truth_z0.SetNameTitle("effi_truth_ftk_z0",";Truth z0 [mm];Efficiency w.r.t. Truth")

	tgae_truth_ftk_refit_effi_vs_truth_pt.Divide(h_ftk_refit_truthMatch_track_pt, h_truth_pt, "e0")    ;tgae_truth_ftk_refit_effi_vs_truth_pt.SetNameTitle("effi_truth_ftk_refit_pt",";Truth pT [GeV];Efficiency w.r.t. Truth")
	tgae_truth_ftk_refit_effi_vs_truth_eta.Divide(h_truth_ftkrefitMatch_track_eta, h_truth_eta, "e0")  ;tgae_truth_ftk_refit_effi_vs_truth_eta.SetNameTitle("effi_truth_ftk_refit_eta",";Truth eta;Efficiency w.r.t. Truth")
	tgae_truth_ftk_refit_effi_vs_truth_phi.Divide(h_truth_ftkrefitMatch_track_phi, h_truth_phi, "e0")  ;tgae_truth_ftk_refit_effi_vs_truth_phi.SetNameTitle("effi_truth_ftk_refit_phi",";Truth phi;Efficiency w.r.t. Truth")
	# tgae_truth_ftk_refit_effi_vs_truth_m.Divide(h_ftk_refitMatched_truth_m, h_truth_m, "e0")         ;tgae_truth_ftk_refit_effi_vs_truth_m.SetNameTitle("effi_truth_ftk_refit_m",";m [GeV];Efficiency w.r.t. Truth")
	tgae_truth_ftk_refit_effi_vs_truth_d0.Divide(h_ftk_refit_truthMatch_track_d0, h_truth_d0, "e0")    ;tgae_truth_ftk_refit_effi_vs_truth_d0.SetNameTitle("effi_truth_ftk_refit_d0",";d0 [mm];Efficiency w.r.t. Truth")
	tgae_truth_ftk_refit_effi_vs_truth_z0.Divide(h_ftk_refit_truthMatch_track_z0, h_truth_z0, "e0")    ;tgae_truth_ftk_refit_effi_vs_truth_z0.SetNameTitle("effi_truth_ftk_refit_z0",";z0 [mm];Efficiency w.r.t. Truth")

tgae_reco_ftk_effi_vs_reco_pt.Divide(h_ftk_recoMatch_track_pt, h_reco_accepted_pt, "e0")     ;tgae_reco_ftk_effi_vs_reco_pt.SetNameTitle("effi_reco_ftk_pt",";Reco pT [GeV];Efficiency w.r.t. Reco")
# tgae_reco_ftk_effi_vs_reco_low_pt.Divide(h_reco_ftkMatched_low_pt, h_reco_low_pt, "e0")    ;tgae_reco_ftk_effi_vs_reco_low_pt.SetNameTitle("effi_reco_ftk_low_pt",";pT [GeV];Efficiency w.r.t. Reco")
# tgae_reco_ftk_effi_vs_reco_high_pt.Divide(h_reco_ftkMatched_high_pt, h_reco_high_pt, "e0") ;tgae_reco_ftk_effi_vs_reco_high_pt.SetNameTitle("effi_reco_ftk_high_pt",";pT [GeV];Efficiency w.r.t. Reco")
tgae_reco_ftk_effi_vs_reco_eta.Divide(h_reco_ftkMatch_track_eta, h_reco_accepted_eta, "e0")  ;tgae_reco_ftk_effi_vs_reco_eta.SetNameTitle("effi_reco_ftk_eta",";Reco eta;Efficiency w.r.t. Reco")
tgae_reco_ftk_effi_vs_reco_phi.Divide(h_reco_ftkMatch_track_phi, h_reco_accepted_phi, "e0")  ;tgae_reco_ftk_effi_vs_reco_phi.SetNameTitle("effi_reco_ftk_phi",";Reco phi;Efficiency w.r.t. Reco")
# tgae_reco_ftk_effi_vs_reco_m.Divide(h_reco_ftkMatched_m, h_reco_m, "e0")                   ;tgae_reco_ftk_effi_vs_reco_m.SetNameTitle("effi_reco_ftk_m",";m [GeV];Efficiency w.r.t. Reco")
tgae_reco_ftk_effi_vs_reco_d0.Divide(h_ftk_recoMatch_track_d0, h_reco_accepted_d0, "e0")     ;tgae_reco_ftk_effi_vs_reco_d0.SetNameTitle("effi_reco_ftk_d0",";Reco d0 [mm];Efficiency w.r.t. Reco")
tgae_reco_ftk_effi_vs_reco_z0.Divide(h_ftk_recoMatch_track_z0, h_reco_accepted_z0, "e0")     ;tgae_reco_ftk_effi_vs_reco_z0.SetNameTitle("effi_reco_ftk_z0",";Reco z0 [mm];Efficiency w.r.t. Reco")

tgae_reco_ftk_refit_effi_vs_reco_pt.Divide(h_ftk_refit_recoMatch_track_pt, h_reco_accepted_pt, "e0")     ;tgae_reco_ftk_refit_effi_vs_reco_pt.SetNameTitle("effi_reco_ftk_refit_pt",";Reco pT [GeV];Efficiency w.r.t. Reco")
tgae_reco_ftk_refit_effi_vs_reco_eta.Divide(h_reco_ftkrefitMatch_track_eta, h_reco_accepted_eta, "e0")   ;tgae_reco_ftk_refit_effi_vs_reco_eta.SetNameTitle("effi_reco_ftk_refit_eta",";Reco eta;Efficiency w.r.t. Reco")
tgae_reco_ftk_refit_effi_vs_reco_phi.Divide(h_reco_ftkrefitMatch_track_phi, h_reco_accepted_phi, "e0")   ;tgae_reco_ftk_refit_effi_vs_reco_phi.SetNameTitle("effi_reco_ftk_refit_phi",";Reco phi;Efficiency w.r.t. Reco")
# tgae_reco_ftk_refit_effi_vs_reco_m.Divide(h_reco_ftk_refitMatched_m, h_reco_m, "e0")                   ;tgae_reco_ftk_refit_effi_vs_reco_m.SetNameTitle("effi_reco_ftk_refit_m",";m [GeV];Efficiency w.r.t. Reco")
tgae_reco_ftk_refit_effi_vs_reco_d0.Divide(h_ftk_refit_recoMatch_track_d0, h_reco_accepted_d0, "e0")     ;tgae_reco_ftk_refit_effi_vs_reco_d0.SetNameTitle("effi_reco_ftk_refit_d0",";Reco d0 [mm];Efficiency w.r.t. Reco")
tgae_reco_ftk_refit_effi_vs_reco_z0.Divide(h_ftk_refit_recoMatch_track_z0, h_reco_accepted_z0, "e0")     ;tgae_reco_ftk_refit_effi_vs_reco_z0.SetNameTitle("effi_reco_ftk_refit_z0",";Reco z0 [mm];Efficiency w.r.t. Reco")


print("Creating file "+ str(output_file)+" and adding histograms")
newFile = TFile(output_file, "recreate")
newFile.cd()

# ATLASLabel(0.56, 0.88, "Internal", 1)
# myLabel(0.50, 0.83, 1, "Run 363400")
# myLabel(0.53, 0.78, 1, "#sqrt{s}= 13 TeV")
# myLabel(0.63,0.83,1,"<#mu> = 42.3")

newFile.Add(h_ftk_reco_deltaR)
newFile.Add(h_ftk_ftkrefit_deltaR)
newFile.Add(h_truth_reco_deltaR)
newFile.Add(h_ftk_truth_deltaR)
newFile.Add(h_ftk_refit_truth_deltaR)
newFile.Add(h_ftk_refit_reco_deltaR)

newFile.Add(h_ftk_accepted_hitPattern_EndCap)
newFile.Add(h_ftk_refit_accepted_hitPattern_EndCap)
newFile.Add(h_reco_accepted_hitPattern_EndCap)
newFile.Add(histocoordmasketa_ftk_EndCap)
newFile.Add(histocoordmaskphi_ftk_EndCap)
newFile.Add(histocoordmaskz0_ftk_EndCap)
newFile.Add(histocoordmaskd0_ftk_EndCap)
newFile.Add(histocoordmasketa_ftkrefit_EndCap)
newFile.Add(histocoordmaskphi_ftkrefit_EndCap)
newFile.Add(histocoordmaskz0_ftkrefit_EndCap)
newFile.Add(histocoordmaskd0_ftkrefit_EndCap)
newFile.Add(histocoordmasketa_reco_EndCap)
newFile.Add(histocoordmaskphi_reco_EndCap)
newFile.Add(histocoordmaskz0_reco_EndCap)
newFile.Add(histocoordmaskd0_reco_EndCap)

newFile.Add(histocoordmasketa_ftk_EndCap_noNorm)
newFile.Add(histocoordmaskphi_ftk_EndCap_noNorm)
newFile.Add(histocoordmaskz0_ftk_EndCap_noNorm)
newFile.Add(histocoordmaskd0_ftk_EndCap_noNorm)
newFile.Add(histocoordmasketa_ftkrefit_EndCap_noNorm)
newFile.Add(histocoordmaskphi_ftkrefit_EndCap_noNorm)
newFile.Add(histocoordmaskz0_ftkrefit_EndCap_noNorm)
newFile.Add(histocoordmaskd0_ftkrefit_EndCap_noNorm)
newFile.Add(histocoordmasketa_reco_EndCap_noNorm)
newFile.Add(histocoordmaskphi_reco_EndCap_noNorm)
newFile.Add(histocoordmaskz0_reco_EndCap_noNorm)
newFile.Add(histocoordmaskd0_reco_EndCap_noNorm)

newFile.Add(h_ftk_accepted_hitPattern_Barrel)
newFile.Add(h_ftk_refit_accepted_hitPattern_Barrel)
newFile.Add(h_reco_accepted_hitPattern_Barrel)
newFile.Add(histocoordmasketa_ftk_Barrel)
newFile.Add(histocoordmaskphi_ftk_Barrel)
newFile.Add(histocoordmaskz0_ftk_Barrel)
newFile.Add(histocoordmaskd0_ftk_Barrel)
newFile.Add(histocoordmasketa_ftkrefit_Barrel)
newFile.Add(histocoordmaskphi_ftkrefit_Barrel)
newFile.Add(histocoordmaskz0_ftkrefit_Barrel)
newFile.Add(histocoordmaskd0_ftkrefit_Barrel)
newFile.Add(histocoordmasketa_reco_Barrel)
newFile.Add(histocoordmaskphi_reco_Barrel)
newFile.Add(histocoordmaskz0_reco_Barrel)
newFile.Add(histocoordmaskd0_reco_Barrel)

newFile.Add(histocoordmasketa_ftk_Barrel_noNorm)
newFile.Add(histocoordmaskphi_ftk_Barrel_noNorm)
newFile.Add(histocoordmaskz0_ftk_Barrel_noNorm)
newFile.Add(histocoordmaskd0_ftk_Barrel_noNorm)
newFile.Add(histocoordmasketa_ftkrefit_Barrel_noNorm)
newFile.Add(histocoordmaskphi_ftkrefit_Barrel_noNorm)
newFile.Add(histocoordmaskz0_ftkrefit_Barrel_noNorm)
newFile.Add(histocoordmaskd0_ftkrefit_Barrel_noNorm)
newFile.Add(histocoordmasketa_reco_Barrel_noNorm)
newFile.Add(histocoordmaskphi_reco_Barrel_noNorm)
newFile.Add(histocoordmaskz0_reco_Barrel_noNorm)
newFile.Add(histocoordmaskd0_reco_Barrel_noNorm)

newFile.Add(h_ftk_accepted_hitPattern)
newFile.Add(h_ftk_refit_accepted_hitPattern)
newFile.Add(h_reco_accepted_hitPattern)
newFile.Add(histocoordmasketa_ftk)
newFile.Add(histocoordmaskphi_ftk)
newFile.Add(histocoordmaskz0_ftk)
newFile.Add(histocoordmasketa_ftkrefit)
newFile.Add(histocoordmaskphi_ftkrefit)
newFile.Add(histocoordmaskz0_ftkrefit)
newFile.Add(histocoordmasketa_reco)
newFile.Add(histocoordmaskphi_reco)
newFile.Add(histocoordmaskz0_reco)

newFile.Add(h_ftk_refit_accepted_EtaPhi0)
newFile.Add(h_ftk_refit_accepted_EtaPhi1)
newFile.Add(h_ftk_refit_accepted_EtaPhi2)
newFile.Add(h_ftk_refit_accepted_EtaPhi3)
newFile.Add(h_ftk_refit_accepted_EtaPhi4)
newFile.Add(h_ftk_refit_accepted_EtaPhi5)
newFile.Add(h_ftk_refit_accepted_EtaPhi6)
newFile.Add(h_ftk_refit_accepted_EtaPhi7)
newFile.Add(h_ftk_refit_accepted_EtaPhi8)
newFile.Add(h_ftk_refit_accepted_EtaPhi9)
newFile.Add(h_ftk_refit_accepted_EtaPhi10)
newFile.Add(h_ftk_refit_accepted_EtaPhi11)
newFile.Add(h_ftk_refit_accepted_EtaPhi12)
newFile.Add(h_ftk_refit_accepted_EtaPhi13)
newFile.Add(h_ftk_refit_accepted_EtaPhi14)
newFile.Add(h_ftk_refit_accepted_EtaPhi15)
newFile.Add(h_ftk_refit_accepted_EtaPhi16)
newFile.Add(h_ftk_refit_accepted_EtaPhi17)
newFile.Add(h_ftk_refit_accepted_EtaPhi18)
newFile.Add(h_ftk_refit_accepted_EtaPhi19)

newFile.Add(h_ftk_accepted_EtaPhi0)
newFile.Add(h_ftk_accepted_EtaPhi1)
newFile.Add(h_ftk_accepted_EtaPhi2)
newFile.Add(h_ftk_accepted_EtaPhi3)
newFile.Add(h_ftk_accepted_EtaPhi4)
newFile.Add(h_ftk_accepted_EtaPhi5)
newFile.Add(h_ftk_accepted_EtaPhi6)
newFile.Add(h_ftk_accepted_EtaPhi7)
newFile.Add(h_ftk_accepted_EtaPhi8)
newFile.Add(h_ftk_accepted_EtaPhi9)
newFile.Add(h_ftk_accepted_EtaPhi10)
newFile.Add(h_ftk_accepted_EtaPhi11)
newFile.Add(h_ftk_accepted_EtaPhi12)
newFile.Add(h_ftk_accepted_EtaPhi13)
newFile.Add(h_ftk_accepted_EtaPhi14)
newFile.Add(h_ftk_accepted_EtaPhi15)
newFile.Add(h_ftk_accepted_EtaPhi16)
newFile.Add(h_ftk_accepted_EtaPhi17)
newFile.Add(h_ftk_accepted_EtaPhi18)
newFile.Add(h_ftk_accepted_EtaPhi19)

newFile.Add(h_reco_accepted_EtaPhi0)
newFile.Add(h_reco_accepted_EtaPhi1)
newFile.Add(h_reco_accepted_EtaPhi2)
newFile.Add(h_reco_accepted_EtaPhi3)
newFile.Add(h_reco_accepted_EtaPhi4)
newFile.Add(h_reco_accepted_EtaPhi5)
newFile.Add(h_reco_accepted_EtaPhi6)
newFile.Add(h_reco_accepted_EtaPhi7)
newFile.Add(h_reco_accepted_EtaPhi8)
newFile.Add(h_reco_accepted_EtaPhi9)
newFile.Add(h_reco_accepted_EtaPhi10)
newFile.Add(h_reco_accepted_EtaPhi11)
newFile.Add(h_reco_accepted_EtaPhi12)
newFile.Add(h_reco_accepted_EtaPhi13)
newFile.Add(h_reco_accepted_EtaPhi14)
newFile.Add(h_reco_accepted_EtaPhi15)
newFile.Add(h_reco_accepted_EtaPhi16)
newFile.Add(h_reco_accepted_EtaPhi17)
newFile.Add(h_reco_accepted_EtaPhi18)
newFile.Add(h_reco_accepted_EtaPhi19)

if isData == False:
	newFile.Add(h_truth_pt)
	newFile.Add(h_truth_eta)
	newFile.Add(h_truth_phi)
	newFile.Add(h_truth_m)
	newFile.Add(h_truth_d0)
	newFile.Add(h_truth_z0)
	newFile.Add(h_truth_qop)
	newFile.Add(h_truth_charge)
	newFile.Add(h_truth_EtaPhi)

newFile.Add(h_reco_accepted_pt)
newFile.Add(h_reco_accepted_eta)
newFile.Add(h_reco_accepted_phi)
newFile.Add(h_reco_accepted_EtaPhi)
newFile.Add(h_reco_accepted_m)
newFile.Add(h_reco_accepted_d0)
newFile.Add(h_reco_accepted_z0)
newFile.Add(h_reco_accepted_qop)
newFile.Add(h_reco_accepted_charge)
newFile.Add(h_reco_accepted_chi2)

newFile.Add(h_reco_inclusive_pt)
newFile.Add(h_reco_inclusive_eta)
newFile.Add(h_reco_inclusive_phi)
newFile.Add(h_reco_inclusive_EtaPhi)
newFile.Add(h_reco_inclusive_m)
newFile.Add(h_reco_inclusive_d0)
newFile.Add(h_reco_inclusive_z0)
newFile.Add(h_reco_inclusive_qop)
newFile.Add(h_reco_inclusive_charge)
newFile.Add(h_reco_inclusive_chi2)

newFile.Add(h_ftk_accepted_pt)
newFile.Add(h_ftk_accepted_eta)
newFile.Add(h_ftk_accepted_phi)
newFile.Add(h_ftk_accepted_EtaPhi)
newFile.Add(h_ftk_accepted_m)
newFile.Add(h_ftk_accepted_d0)
newFile.Add(h_ftk_accepted_corrected_d0)
newFile.Add(h_ftk_accepted_z0)
newFile.Add(h_ftk_accepted_qop)
newFile.Add(h_ftk_accepted_charge)
newFile.Add(h_ftk_accepted_chi2)

newFile.Add(h_ftk_inclusive_pt)
newFile.Add(h_ftk_inclusive_eta)
newFile.Add(h_ftk_inclusive_phi)
newFile.Add(h_ftk_inclusive_EtaPhi)
newFile.Add(h_ftk_inclusive_m)
newFile.Add(h_ftk_inclusive_d0)
newFile.Add(h_ftk_inclusive_corrected_d0)
newFile.Add(h_ftk_inclusive_z0)
newFile.Add(h_ftk_inclusive_qop)
newFile.Add(h_ftk_inclusive_charge)
newFile.Add(h_ftk_inclusive_chi2)

newFile.Add(h_ftk_refit_accepted_pt)
newFile.Add(h_ftk_refit_accepted_eta)
newFile.Add(h_ftk_refit_accepted_phi)
newFile.Add(h_ftk_refit_accepted_EtaPhi)
newFile.Add(h_ftk_refit_accepted_m)
newFile.Add(h_ftk_refit_accepted_d0)
newFile.Add(h_ftk_refit_accepted_z0)
newFile.Add(h_ftk_refit_accepted_qop)
newFile.Add(h_ftk_refit_accepted_charge)
newFile.Add(h_ftk_refit_accepted_chi2)

newFile.Add(h_ftk_refit_inclusive_pt)
newFile.Add(h_ftk_refit_inclusive_eta)
newFile.Add(h_ftk_refit_inclusive_phi)
newFile.Add(h_ftk_refit_inclusive_EtaPhi)
newFile.Add(h_ftk_refit_inclusive_m)
newFile.Add(h_ftk_refit_inclusive_d0)
newFile.Add(h_ftk_refit_inclusive_z0)
newFile.Add(h_ftk_refit_inclusive_qop)
newFile.Add(h_ftk_refit_inclusive_charge)
newFile.Add(h_ftk_refit_inclusive_chi2)

newFile.Add(h_reco_ftk_refitMatched_pt_bias)
newFile.Add(h_reco_ftk_refitMatched_eta_bias)
newFile.Add(h_reco_ftk_refitMatched_phi_bias)
newFile.Add(h_reco_ftk_refitMatched_d0_bias)

newFile.Add(h_ftk_refit_recoMatch_track_eta)
newFile.Add(h_ftk_refit_recoMatch_track_EtaPhi)
newFile.Add(h_ftk_refit_recoMatch_track_phi)
newFile.Add(h_reco_ftkrefitMatch_track_eta)
newFile.Add(h_reco_ftkrefitMatch_track_phi)
newFile.Add(h_ftk_refit_recoMatch_track_pt)
newFile.Add(h_ftk_refit_recoMatch_track_d0)
newFile.Add(h_ftk_refit_recoMatch_track_z0)


newFile.Add(h_reco_ftkMatched_pt_bias)
newFile.Add(h_reco_ftkMatched_eta_bias)
newFile.Add(h_reco_ftkMatched_phi_bias)
newFile.Add(h_reco_ftkMatched_d0_bias)
newFile.Add(h_reco_ftkMatched_corrected_d0_bias)

newFile.Add(h_ftk_recoMatch_track_eta)
newFile.Add(h_ftk_recoMatch_track_EtaPhi)
newFile.Add(h_ftk_recoMatch_track_phi)
newFile.Add(h_reco_ftkMatch_track_eta)
newFile.Add(h_reco_ftkMatch_track_phi)
newFile.Add(h_ftk_recoMatch_track_pt)
newFile.Add(h_ftk_recoMatch_track_d0)
# newFile.Add(h_ftk_recoMatch_track_corrected_d0)
newFile.Add(h_ftk_recoMatch_track_z0)




if isData == False:
	newFile.Add(h_truth_ftk_refitMatched_pt_bias)
	newFile.Add(h_truth_ftk_refitMatched_eta_bias)
	newFile.Add(h_truth_ftk_refitMatched_phi_bias)
	newFile.Add(h_truth_ftk_refitMatched_d0_bias)
	newFile.Add(h_ftk_refit_truthMatch_track_eta)
	newFile.Add(h_ftk_refit_truthMatch_track_EtaPhi)
	newFile.Add(h_ftk_refit_truthMatch_track_phi)
	newFile.Add(h_truth_ftkrefitMatch_track_eta)
	newFile.Add(h_truth_ftkrefitMatch_track_phi)
	newFile.Add(h_ftk_refit_truthMatch_track_pt)
	newFile.Add(h_ftk_refit_truthMatch_track_d0)
	newFile.Add(h_ftk_refit_truthMatch_track_z0)

	newFile.Add(h_truth_ftk_Matched_pt_bias)
	newFile.Add(h_truth_ftk_Matched_eta_bias)
	newFile.Add(h_truth_ftk_Matched_phi_bias)
	newFile.Add(h_truth_ftk_Matched_d0_bias)
	newFile.Add(h_truth_ftk_Matched_corrected_d0_bias)
	newFile.Add(h_ftk_truthMatch_track_eta)
	newFile.Add(h_ftk_truthMatch_track_EtaPhi)
	newFile.Add(h_ftk_truthMatch_track_phi)
	newFile.Add(h_truth_ftkMatch_track_eta)
	newFile.Add(h_truth_ftkMatch_track_phi)
	newFile.Add(h_ftk_truthMatch_track_pt)
	newFile.Add(h_ftk_truthMatch_track_d0)
	newFile.Add(h_ftk_truthMatch_track_z0)

	newFile.Add(h_reco_truthMatched_pt_bias)
	newFile.Add(h_reco_truthMatched_eta_bias)
	newFile.Add(h_reco_truthMatched_phi_bias)
	newFile.Add(h_reco_truthMatched_d0_bias)
	newFile.Add(h_truth_recoMatch_track_eta)
	newFile.Add(h_truth_recoMatch_track_EtaPhi)
	newFile.Add(h_truth_recoMatch_track_phi)
	newFile.Add(h_reco_truthMatch_track_eta)
	newFile.Add(h_reco_truthMatch_track_phi)
	newFile.Add(h_truth_recoMatch_track_pt)
	newFile.Add(h_truth_recoMatch_track_d0)
	newFile.Add(h_truth_recoMatch_track_z0)


	newFile.Add(tgae_truth_reco_effi_vs_truth_pt)
	newFile.Add(tgae_truth_reco_effi_vs_truth_eta)
	newFile.Add(tgae_truth_reco_effi_vs_truth_phi)
	newFile.Add(tgae_truth_reco_effi_vs_truth_d0)
	newFile.Add(tgae_truth_reco_effi_vs_truth_z0)
	newFile.Add(tgae_truth_ftk_effi_vs_truth_pt)
	newFile.Add(tgae_truth_ftk_effi_vs_truth_eta)
	newFile.Add(tgae_truth_ftk_effi_vs_truth_phi)
	newFile.Add(tgae_truth_ftk_effi_vs_truth_d0)
	newFile.Add(tgae_truth_ftk_effi_vs_truth_z0)
	newFile.Add(tgae_truth_ftk_refit_effi_vs_truth_pt)
	newFile.Add(tgae_truth_ftk_refit_effi_vs_truth_eta)
	newFile.Add(tgae_truth_ftk_refit_effi_vs_truth_phi)
	newFile.Add(tgae_truth_ftk_refit_effi_vs_truth_d0)
	newFile.Add(tgae_truth_ftk_refit_effi_vs_truth_z0)

# tgae_reco_ftk_effi_vs_reco_pt.Draw('ap')
newFile.Add(tgae_reco_ftk_effi_vs_reco_pt)
newFile.Add(tgae_reco_ftk_effi_vs_reco_eta)
newFile.Add(tgae_reco_ftk_effi_vs_reco_phi)
# newFile.Add(tgae_reco_ftk_effi_vs_reco_low_pt)
# newFile.Add(tgae_reco_ftk_effi_vs_reco_high_pt)
newFile.Add(tgae_reco_ftk_effi_vs_reco_d0)
newFile.Add(tgae_reco_ftk_effi_vs_reco_z0)

newFile.Add(tgae_reco_ftk_refit_effi_vs_reco_pt)
newFile.Add(tgae_reco_ftk_refit_effi_vs_reco_eta)
newFile.Add(tgae_reco_ftk_refit_effi_vs_reco_phi)
newFile.Add(tgae_reco_ftk_refit_effi_vs_reco_d0)
newFile.Add(tgae_reco_ftk_refit_effi_vs_reco_z0)


if calc_m == True:
	newFile.Add(tgae_truth_reco_effi_vs_truth_m)
	newFile.Add(tgae_truth_ftk_effi_vs_truth_m)
	newFile.Add(tgae_truth_ftk_refit_effi_vs_truth_m)
	newFile.Add(tgae_muon_truth_reco_effi_vs_truth_m)
	newFile.Add(tgae_muon_truth_ftk_effi_vs_truth_m)
	newFile.Add(tgae_muon_truth_ftk_refit_effi_vs_truth_m)
	newFile.Add(tgae_reco_ftk_effi_vs_reco_m)
	newFile.Add(tgae_reco_ftk_refit_effi_vs_reco_m)



gStyle.SetOptStat(0);
legend_canvas = TCanvas("legend", "");
# legend = TLegend(0.1,0.7,0.48,0.9);
# legend.AddEntry(h_reco_accepted_pt1, file1_label);
# legend.AddEntry(h_reco_accepted_pt2, file2_label);
# legend.Draw();
ATLASLabel(0.1, 0.9, "Internal", 1) 
myLabel(0.1, 0.85, 1, "#sqrt{s}= 13 TeV")
myLabel(0.1, 0.8, 1, "Run 366805 Heavy Ions")
# legend_canvas.SaveAs("legend.pdf")
legend_canvas.Write()


newFile.Write()
newFile.Close()

print "Runtime: %s" %(time() - start_time)
