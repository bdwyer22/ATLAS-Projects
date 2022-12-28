from ROOT import *
import os
import argparse


parser=argparse.ArgumentParser()
parser.add_argument("--file1",   type=str,  required=False, dest="input_file1", help="Specify the first input file")
parser.add_argument("--file2",   type=str,  required=False, dest="input_file2", help="Specify the second input file")
parser.add_argument("--data",   type=bool,  required=False, default=False, dest="event_type", help="Flag --data True for data events")
args = parser.parse_args()


input_file1 = args.input_file1
input_file2 = args.input_file2
isData = args.event_type


file1_label = "Run 00334993 lb100"
file2_label = "Run 00340453 lb80"


gROOT.SetBatch(True)

# c1 = TCanvas("c1", "c1")

f1 = TFile(input_file1)
f2 = TFile(input_file2)

# print(f1)
print("Getting files: "+input_file1+" and "+input_file2)
print("Setting legend labels: "+file1_label+" and "+file2_label)

print("Getting histograms")
if isData == False:
	h_truth_pt1 = f1.Get("h_truth_pt"); h_truth_pt2 = f2.Get("h_truth_pt")
	h_truth_eta1 = f1.Get("h_truth_eta"); h_truth_eta2 = f2.Get("h_truth_eta")
	h_truth_phi1 = f1.Get("h_truth_phi"); h_truth_phi2 = f2.Get("h_truth_phi")
	h_truth_m1 = f1.Get("h_truth_m"); h_truth_m2 = f2.Get("h_truth_m")
	h_truth_d01 = f1.Get("h_truth_d0"); h_truth_d02 = f2.Get("h_truth_d0")
	h_truth_z01 = f1.Get("h_truth_z0"); h_truth_z02 = f2.Get("h_truth_z0")
	h_truth_qop1 = f1.Get("h_truth_qop"); h_truth_qop2 = f2.Get("h_truth_qop")
	h_truth_charge1 = f1.Get("h_truth_charge"); h_truth_charge2 = f2.Get("h_truth_charge")

h_reco_accepted_pt1 = f1.Get("h_reco_accepted_pt"); h_reco_accepted_pt2 = f2.Get("h_reco_accepted_pt")
h_reco_accepted_eta1 = f1.Get("h_reco_accepted_eta"); h_reco_accepted_eta2 = f2.Get("h_reco_accepted_eta")
h_reco_accepted_phi1 = f1.Get("h_reco_accepted_phi"); h_reco_accepted_phi2 = f2.Get("h_reco_accepted_phi")
# h_reco_accepted_m1 = f1.Get("h_reco_accepted_m"); h_reco_accepted_m2 = f2.Get("h_reco_accepted_m")
h_reco_accepted_d01 = f1.Get("h_reco_accepted_d0"); h_reco_accepted_d02 = f2.Get("h_reco_accepted_d0")
h_reco_accepted_z01 = f1.Get("h_reco_accepted_z0"); h_reco_accepted_z02 = f2.Get("h_reco_accepted_z0")
h_reco_accepted_qop1 = f1.Get("h_reco_accepted_qop"); h_reco_accepted_qop2 = f2.Get("h_reco_accepted_qop")
h_reco_accepted_charge1 = f1.Get("h_reco_accepted_charge"); h_reco_accepted_charge2 = f2.Get("h_reco_accepted_charge")
h_reco_accepted_chi21 = f1.Get("h_reco_accepted_chi2"); h_reco_accepted_chi22 = f2.Get("h_reco_accepted_chi2")

h_reco_inclusive_pt1 = f1.Get("h_reco_inclusive_pt"); h_reco_inclusive_pt2 = f2.Get("h_reco_inclusive_pt")
h_reco_inclusive_eta1 = f1.Get("h_reco_inclusive_eta"); h_reco_inclusive_eta2 = f2.Get("h_reco_inclusive_eta")
h_reco_inclusive_phi1 = f1.Get("h_reco_inclusive_phi"); h_reco_inclusive_phi2 = f2.Get("h_reco_inclusive_phi")
# h_reco_inclusive_m1 = f1.Get("h_reco_inclusive_m"); h_reco_inclusive_m2 = f2.Get("h_reco_inclusive_m")
h_reco_inclusive_d01 = f1.Get("h_reco_inclusive_d0"); h_reco_inclusive_d02 = f2.Get("h_reco_inclusive_d0")
h_reco_inclusive_z01 = f1.Get("h_reco_inclusive_z0"); h_reco_inclusive_z02 = f2.Get("h_reco_inclusive_z0")
h_reco_inclusive_qop1 = f1.Get("h_reco_inclusive_qop"); h_reco_inclusive_qop2 = f2.Get("h_reco_inclusive_qop")
h_reco_inclusive_charge1 = f1.Get("h_reco_inclusive_charge"); h_reco_inclusive_charge2 = f2.Get("h_reco_inclusive_charge")
h_reco_inclusive_chi21 = f1.Get("h_reco_inclusive_chi2"); h_reco_inclusive_chi22 = f2.Get("h_reco_inclusive_chi2")

h_ftk_accepted_pt1 = f1.Get("h_ftk_accepted_pt"); h_ftk_accepted_pt2 = f2.Get("h_ftk_accepted_pt")
h_ftk_accepted_eta1 = f1.Get("h_ftk_accepted_eta"); h_ftk_accepted_eta2 = f2.Get("h_ftk_accepted_eta")
h_ftk_accepted_phi1 = f1.Get("h_ftk_accepted_phi"); h_ftk_accepted_phi2 = f2.Get("h_ftk_accepted_phi")
# h_ftk_accepted_m1 = f1.Get("h_ftk_accepted_m"); h_ftk_accepted_m2 = f2.Get("h_ftk_accepted_m")
h_ftk_accepted_d01 = f1.Get("h_ftk_accepted_d0"); h_ftk_accepted_d02 = f2.Get("h_ftk_accepted_d0")
h_ftk_accepted_corrected_d01 = f1.Get("h_ftk_accepted_corrected_d0"); h_ftk_accepted_corrected_d02 = f2.Get("h_ftk_accepted_corrected_d0")
h_ftk_accepted_z01 = f1.Get("h_ftk_accepted_z0"); h_ftk_accepted_z02 = f2.Get("h_ftk_accepted_z0")
h_ftk_accepted_qop1 = f1.Get("h_ftk_accepted_qop"); h_ftk_accepted_qop2 = f2.Get("h_ftk_accepted_qop")
h_ftk_accepted_charge1 = f1.Get("h_ftk_accepted_charge"); h_ftk_accepted_charge2 = f2.Get("h_ftk_accepted_charge")
h_ftk_accepted_chi21 = f1.Get("h_ftk_accepted_chi2"); h_ftk_accepted_chi22 = f2.Get("h_ftk_accepted_chi2")

h_ftk_inclusive_pt1 = f1.Get("h_ftk_inclusive_pt"); h_ftk_inclusive_pt2 = f2.Get("h_ftk_inclusive_pt")
h_ftk_inclusive_eta1 = f1.Get("h_ftk_inclusive_eta"); h_ftk_inclusive_eta2 = f2.Get("h_ftk_inclusive_eta")
h_ftk_inclusive_phi1 = f1.Get("h_ftk_inclusive_phi"); h_ftk_inclusive_phi2 = f2.Get("h_ftk_inclusive_phi")
# h_ftk_inclusive_m1 = f1.Get("h_ftk_inclusive_m"); h_ftk_inclusive_m2 = f2.Get("h_ftk_inclusive_m")
h_ftk_inclusive_d01 = f1.Get("h_ftk_inclusive_d0"); h_ftk_inclusive_d02 = f2.Get("h_ftk_inclusive_d0")
h_ftk_inclusive_corrected_d01 = f1.Get("h_ftk_inclusive_corrected_d0"); h_ftk_inclusive_corrected_d02 = f2.Get("h_ftk_inclusive_corrected_d0")
h_ftk_inclusive_z01 = f1.Get("h_ftk_inclusive_z0"); h_ftk_inclusive_z02 = f2.Get("h_ftk_inclusive_z0")
h_ftk_inclusive_qop1 = f1.Get("h_ftk_inclusive_qop"); h_ftk_inclusive_qop2 = f2.Get("h_ftk_inclusive_qop")
h_ftk_inclusive_charge1 = f1.Get("h_ftk_inclusive_charge"); h_ftk_inclusive_charge2 = f2.Get("h_ftk_inclusive_charge")
h_ftk_inclusive_chi21 = f1.Get("h_ftk_inclusive_chi2"); h_ftk_inclusive_chi22 = f2.Get("h_ftk_inclusive_chi2")

h_ftk_refit_accepted_pt1 = f1.Get("h_ftk_refit_accepted_pt"); h_ftk_refit_accepted_pt2 = f2.Get("h_ftk_refit_accepted_pt")
h_ftk_refit_accepted_eta1 = f1.Get("h_ftk_refit_accepted_eta"); h_ftk_refit_accepted_eta2 = f2.Get("h_ftk_refit_accepted_eta")
h_ftk_refit_accepted_phi1 = f1.Get("h_ftk_refit_accepted_phi"); h_ftk_refit_accepted_phi2 = f2.Get("h_ftk_refit_accepted_phi")
# h_ftk_refit_accepted_m1 = f1.Get("h_ftk_refit_accepted_m"); h_ftk_refit_accepted_m2 = f2.Get("h_ftk_refit_accepted_m")
h_ftk_refit_accepted_d01 = f1.Get("h_ftk_refit_accepted_d0"); h_ftk_refit_accepted_d02 = f2.Get("h_ftk_refit_accepted_d0")
h_ftk_refit_accepted_z01 = f1.Get("h_ftk_refit_accepted_z0"); h_ftk_refit_accepted_z02 = f2.Get("h_ftk_refit_accepted_z0")
h_ftk_refit_accepted_qop1 = f1.Get("h_ftk_refit_accepted_qop"); h_ftk_refit_accepted_qop2 = f2.Get("h_ftk_refit_accepted_qop")
h_ftk_refit_accepted_charge1 = f1.Get("h_ftk_refit_accepted_charge"); h_ftk_refit_accepted_charge2 = f2.Get("h_ftk_refit_accepted_charge")
h_ftk_refit_accepted_chi21 = f1.Get("h_ftk_refit_accepted_chi2"); h_ftk_refit_accepted_chi22 = f2.Get("h_ftk_refit_accepted_chi2")

h_ftk_refit_inclusive_pt1 = f1.Get("h_ftk_refit_inclusive_pt"); h_ftk_refit_inclusive_pt2 = f2.Get("h_ftk_refit_inclusive_pt")
h_ftk_refit_inclusive_eta1 = f1.Get("h_ftk_refit_inclusive_eta"); h_ftk_refit_inclusive_eta2 = f2.Get("h_ftk_refit_inclusive_eta")
h_ftk_refit_inclusive_phi1 = f1.Get("h_ftk_refit_inclusive_phi"); h_ftk_refit_inclusive_phi2 = f2.Get("h_ftk_refit_inclusive_phi")
# h_ftk_refit_inclusive_m1 = f1.Get("h_ftk_refit_inclusive_m"); h_ftk_refit_inclusive_m2 = f2.Get("h_ftk_refit_inclusive_m")
h_ftk_refit_inclusive_d01 = f1.Get("h_ftk_refit_inclusive_d0"); h_ftk_refit_inclusive_d02 = f2.Get("h_ftk_refit_inclusive_d0")
h_ftk_refit_inclusive_z01 = f1.Get("h_ftk_refit_inclusive_z0"); h_ftk_refit_inclusive_z02 = f2.Get("h_ftk_refit_inclusive_z0")
h_ftk_refit_inclusive_qop1 = f1.Get("h_ftk_refit_inclusive_qop"); h_ftk_refit_inclusive_qop2 = f2.Get("h_ftk_refit_inclusive_qop")
h_ftk_refit_inclusive_charge1 = f1.Get("h_ftk_refit_inclusive_charge"); h_ftk_refit_inclusive_charge2 = f2.Get("h_ftk_refit_inclusive_charge")
h_ftk_refit_inclusive_chi21 = f1.Get("h_ftk_refit_inclusive_chi2"); h_ftk_refit_inclusive_chi22 = f2.Get("h_ftk_refit_inclusive_chi2")

if isData == False:
	h_reco_truthMatched_pt_bias1 = f1.Get("h_reco_truthMatched_pt_bias"); h_reco_truthMatched_pt_bias2 = f2.Get("h_reco_truthMatched_pt_bias")
	h_reco_truthMatched_eta_bias1 = f1.Get("h_reco_truthMatched_eta_bias"); h_reco_truthMatched_eta_bias2 = f2.Get("h_reco_truthMatched_eta_bias")
	h_reco_truthMatched_phi_bias1 = f1.Get("h_reco_truthMatched_phi_bias"); h_reco_truthMatched_phi_bias2 = f2.Get("h_reco_truthMatched_phi_bias")
	h_reco_truthMatched_d0_bias1 = f1.Get("h_reco_truthMatched_d0_bias"); h_reco_truthMatched_d0_bias2 = f2.Get("h_reco_truthMatched_d0_bias")

	h_truth_recoMatch_track_eta1 = f1.Get("h_truth_recoMatch_track_eta"); h_truth_recoMatch_track_eta2 = f2.Get("h_truth_recoMatch_track_eta")
	h_truth_recoMatch_track_phi1 = f1.Get("h_truth_recoMatch_track_phi"); h_truth_recoMatch_track_phi2 = f2.Get("h_truth_recoMatch_track_phi")
	h_reco_truthMatch_track_eta1 = f1.Get("h_reco_truthMatch_track_eta"); h_reco_truthMatch_track_eta2 = f2.Get("h_reco_truthMatch_track_eta")
	h_reco_truthMatch_track_phi1 = f1.Get("h_reco_truthMatch_track_phi"); h_reco_truthMatch_track_phi2 = f2.Get("h_reco_truthMatch_track_phi")
	h_truth_recoMatch_track_pt1 = f1.Get("h_truth_recoMatch_track_pt"); h_truth_recoMatch_track_pt2 = f2.Get("h_truth_recoMatch_track_pt")
	h_truth_recoMatch_track_d01 = f1.Get("h_truth_recoMatch_track_d0"); h_truth_recoMatch_track_d02 = f2.Get("h_truth_recoMatch_track_d0")
	h_truth_recoMatch_track_z01 = f1.Get("h_truth_recoMatch_track_z0"); h_truth_recoMatch_track_z02 = f2.Get("h_truth_recoMatch_track_z0")

	h_truth_ftk_Matched_pt_bias1 = f1.Get("h_truth_ftk_Matched_pt_bias"); h_truth_ftk_Matched_pt_bias2 = f2.Get("h_truth_ftk_Matched_pt_bias")
	h_truth_ftk_Matched_eta_bias1 = f1.Get("h_truth_ftk_Matched_eta_bias"); h_truth_ftk_Matched_eta_bias2 = f2.Get("h_truth_ftk_Matched_eta_bias")
	h_truth_ftk_Matched_phi_bias1 = f1.Get("h_truth_ftk_Matched_phi_bias"); h_truth_ftk_Matched_phi_bias2 = f2.Get("h_truth_ftk_Matched_phi_bias")
	h_truth_ftk_Matched_d0_bias1 = f1.Get("h_truth_ftk_Matched_d0_bias"); h_truth_ftk_Matched_d0_bias2 = f2.Get("h_truth_ftk_Matched_d0_bias")
	h_truth_ftk_Matched_corrected_d0_bias1 = f1.Get("h_truth_ftk_Matched_corrected_d0_bias"); h_truth_ftk_Matched_corrected_d0_bias2 = f2.Get("h_truth_ftk_Matched_corrected_d0_bias")

	h_ftk_truthMatch_track_eta1 = f1.Get("h_ftk_truthMatch_track_eta"); h_ftk_truthMatch_track_eta2 = f2.Get("h_ftk_truthMatch_track_eta")
	h_ftk_truthMatch_track_phi1 = f1.Get("h_ftk_truthMatch_track_phi"); h_ftk_truthMatch_track_phi2 = f2.Get("h_ftk_truthMatch_track_phi")
	h_truth_ftkMatch_track_eta1 = f1.Get("h_truth_ftkMatch_track_eta"); h_truth_ftkMatch_track_eta2 = f2.Get("h_truth_ftkMatch_track_eta")
	h_truth_ftkMatch_track_phi1 = f1.Get("h_truth_ftkMatch_track_phi"); h_truth_ftkMatch_track_phi2 = f2.Get("h_truth_ftkMatch_track_phi")
	h_ftk_truthMatch_track_pt1 = f1.Get("h_ftk_truthMatch_track_pt"); h_ftk_truthMatch_track_pt2 = f2.Get("h_ftk_truthMatch_track_pt")
	h_ftk_truthMatch_track_d01 = f1.Get("h_ftk_truthMatch_track_d0"); h_ftk_truthMatch_track_d02 = f2.Get("h_ftk_truthMatch_track_d0")
	h_ftk_truthMatch_track_z01 = f1.Get("h_ftk_truthMatch_track_z0"); h_ftk_truthMatch_track_z02 = f2.Get("h_ftk_truthMatch_track_z0")

	h_truth_ftk_refitMatched_pt_bias1 = f1.Get("h_truth_ftk_refitMatched_pt_bias"); h_truth_ftk_refitMatched_pt_bias2 = f2.Get("h_truth_ftk_refitMatched_pt_bias")
	h_truth_ftk_refitMatched_eta_bias1 = f1.Get("h_truth_ftk_refitMatched_eta_bias"); h_truth_ftk_refitMatched_eta_bias2 = f2.Get("h_truth_ftk_refitMatched_eta_bias")
	h_truth_ftk_refitMatched_phi_bias1 = f1.Get("h_truth_ftk_refitMatched_phi_bias"); h_truth_ftk_refitMatched_phi_bias2 = f2.Get("h_truth_ftk_refitMatched_phi_bias")
	h_truth_ftk_refitMatched_d0_bias1 = f1.Get("h_truth_ftk_refitMatched_d0_bias"); h_truth_ftk_refitMatched_d0_bias2 = f2.Get("h_truth_ftk_refitMatched_d0_bias")

	h_ftk_refit_truthMatch_track_eta1 = f1.Get("h_ftk_refit_truthMatch_track_eta"); h_ftk_refit_truthMatch_track_eta2 = f2.Get("h_ftk_refit_truthMatch_track_eta")
	h_ftk_refit_truthMatch_track_phi1 = f1.Get("h_ftk_refit_truthMatch_track_phi"); h_ftk_refit_truthMatch_track_phi2 = f2.Get("h_ftk_refit_truthMatch_track_phi")
	h_truth_ftkrefitMatch_track_eta1 = f1.Get("h_truth_ftkrefitMatch_track_eta"); h_truth_ftkrefitMatch_track_eta2 = f2.Get("h_truth_ftkrefitMatch_track_eta")
	h_truth_ftkrefitMatch_track_phi1 = f1.Get("h_truth_ftkrefitMatch_track_phi"); h_truth_ftkrefitMatch_track_phi2 = f2.Get("h_truth_ftkrefitMatch_track_phi")
	h_ftk_refit_truthMatch_track_pt1 = f1.Get("h_ftk_refit_truthMatch_track_pt"); h_ftk_refit_truthMatch_track_pt2 = f2.Get("h_ftk_refit_truthMatch_track_pt")
	h_ftk_refit_truthMatch_track_d01 = f1.Get("h_ftk_refit_truthMatch_track_d0"); h_ftk_refit_truthMatch_track_d02 = f2.Get("h_ftk_refit_truthMatch_track_d0")
	h_ftk_refit_truthMatch_track_z01 = f1.Get("h_ftk_refit_truthMatch_track_z0"); h_ftk_refit_truthMatch_track_z02 = f2.Get("h_ftk_refit_truthMatch_track_z0")

h_reco_ftkMatched_pt_bias1 = f1.Get("h_reco_ftkMatched_pt_bias"); h_reco_ftkMatched_pt_bias2 = f2.Get("h_reco_ftkMatched_pt_bias")
h_reco_ftkMatched_eta_bias1 = f1.Get("h_reco_ftkMatched_eta_bias"); h_reco_ftkMatched_eta_bias2 = f2.Get("h_reco_ftkMatched_eta_bias")
h_reco_ftkMatched_phi_bias1 = f1.Get("h_reco_ftkMatched_phi_bias"); h_reco_ftkMatched_phi_bias2 = f2.Get("h_reco_ftkMatched_phi_bias")
h_reco_ftkMatched_d0_bias1 = f1.Get("h_reco_ftkMatched_d0_bias"); h_reco_ftkMatched_d0_bias2 = f2.Get("h_reco_ftkMatched_d0_bias")
h_reco_ftkMatched_corrected_d0_bias1 = f1.Get("h_reco_ftkMatched_corrected_d0_bias"); h_reco_ftkMatched_corrected_d0_bias2 = f2.Get("h_reco_ftkMatched_corrected_d0_bias")

h_ftk_recoMatch_track_eta1 = f1.Get("h_ftk_recoMatch_track_eta"); h_ftk_recoMatch_track_eta2 = f2.Get("h_ftk_recoMatch_track_eta")
h_ftk_recoMatch_track_phi1 = f1.Get("h_ftk_recoMatch_track_phi"); h_ftk_recoMatch_track_phi2 = f2.Get("h_ftk_recoMatch_track_phi")
h_reco_ftkMatch_track_eta1 = f1.Get("h_reco_ftkMatch_track_eta"); h_reco_ftkMatch_track_eta2 = f2.Get("h_reco_ftkMatch_track_eta")
h_reco_ftkMatch_track_phi1 = f1.Get("h_reco_ftkMatch_track_phi"); h_reco_ftkMatch_track_phi2 = f2.Get("h_reco_ftkMatch_track_phi")
h_ftk_recoMatch_track_pt1 = f1.Get("h_ftk_recoMatch_track_pt"); h_ftk_recoMatch_track_pt2 = f2.Get("h_ftk_recoMatch_track_pt")
h_ftk_recoMatch_track_d01 = f1.Get("h_ftk_recoMatch_track_d0"); h_ftk_recoMatch_track_d02 = f2.Get("h_ftk_recoMatch_track_d0")
# h_ftk_recoMatch_track_corrected_d01 = f1.Get("h_ftk_recoMatch_track_corrected_d0"); h_ftk_recoMatch_track_corrected_d02 = f2.Get("h_ftk_recoMatch_track_corrected_d0")
h_ftk_recoMatch_track_z01 = f1.Get("h_ftk_recoMatch_track_z0"); h_ftk_recoMatch_track_z02 = f2.Get("h_ftk_recoMatch_track_z0")

h_reco_ftk_refitMatched_pt_bias1 = f1.Get("h_reco_ftk_refitMatched_pt_bias"); h_reco_ftk_refitMatched_pt_bias2 = f2.Get("h_reco_ftk_refitMatched_pt_bias")
h_reco_ftk_refitMatched_eta_bias1 = f1.Get("h_reco_ftk_refitMatched_eta_bias"); h_reco_ftk_refitMatched_eta_bias2 = f2.Get("h_reco_ftk_refitMatched_eta_bias")
h_reco_ftk_refitMatched_phi_bias1 = f1.Get("h_reco_ftk_refitMatched_phi_bias"); h_reco_ftk_refitMatched_phi_bias2 = f2.Get("h_reco_ftk_refitMatched_phi_bias")
h_reco_ftk_refitMatched_d0_bias1 = f1.Get("h_reco_ftk_refitMatched_d0_bias"); h_reco_ftk_refitMatched_d0_bias2 = f2.Get("h_reco_ftk_refitMatched_d0_bias")

h_ftk_refit_recoMatch_track_eta1 = f1.Get("h_ftk_refit_recoMatch_track_eta"); h_ftk_refit_recoMatch_track_eta2 = f2.Get("h_ftk_refit_recoMatch_track_eta")
h_ftk_refit_recoMatch_track_phi1 = f1.Get("h_ftk_refit_recoMatch_track_phi"); h_ftk_refit_recoMatch_track_phi2 = f2.Get("h_ftk_refit_recoMatch_track_phi")
h_reco_ftkrefitMatch_track_eta1 = f1.Get("h_reco_ftkrefitMatch_track_eta"); h_reco_ftkrefitMatch_track_eta2 = f2.Get("h_reco_ftkrefitMatch_track_eta")
h_reco_ftkrefitMatch_track_phi1 = f1.Get("h_reco_ftkrefitMatch_track_phi"); h_reco_ftkrefitMatch_track_phi2 = f2.Get("h_reco_ftkrefitMatch_track_phi")
h_ftk_refit_recoMatch_track_pt1 = f1.Get("h_ftk_refit_recoMatch_track_pt"); h_ftk_refit_recoMatch_track_pt2 = f2.Get("h_ftk_refit_recoMatch_track_pt")
h_ftk_refit_recoMatch_track_d01 = f1.Get("h_ftk_refit_recoMatch_track_d0"); h_ftk_refit_recoMatch_track_d02 = f2.Get("h_ftk_refit_recoMatch_track_d0")
h_ftk_refit_recoMatch_track_z01 = f1.Get("h_ftk_refit_recoMatch_track_z0"); h_ftk_refit_recoMatch_track_z02 = f2.Get("h_ftk_refit_recoMatch_track_z0")

h_reco_accepted_hitPattern_EndCap1 = f1.Get("h_reco_accepted_hitPattern_EndCap"); h_reco_accepted_hitPattern_EndCap2 = f2.Get("h_reco_accepted_hitPattern_EndCap")
h_ftk_accepted_hitPattern_EndCap1 = f1.Get("h_ftk_accepted_hitPattern_EndCap"); h_ftk_accepted_hitPattern_EndCap2 = f2.Get("h_ftk_accepted_hitPattern_EndCap")
h_ftk_refit_accepted_hitPattern_EndCap1 = f1.Get("h_ftk_refit_accepted_hitPattern_EndCap"); h_ftk_refit_accepted_hitPattern_EndCap2 = f2.Get("h_ftk_refit_accepted_hitPattern_EndCap")

h_reco_accepted_hitPattern_Barrel1 = f1.Get("h_reco_accepted_hitPattern_Barrel"); h_reco_accepted_hitPattern_Barrel2 = f2.Get("h_reco_accepted_hitPattern_Barrel")
h_ftk_accepted_hitPattern_Barrel1 = f1.Get("h_ftk_accepted_hitPattern_Barrel"); h_ftk_accepted_hitPattern_Barrel2 = f2.Get("h_ftk_accepted_hitPattern_Barrel")
h_ftk_refit_accepted_hitPattern_Barrel1 = f1.Get("h_ftk_refit_accepted_hitPattern_Barrel"); h_ftk_refit_accepted_hitPattern_Barrel2 = f2.Get("h_ftk_refit_accepted_hitPattern_Barrel")

h_reco_accepted_hitPattern1 = f1.Get("h_reco_accepted_hitPattern"); h_reco_accepted_hitPattern2 = f2.Get("h_reco_accepted_hitPattern")
h_ftk_accepted_hitPattern1 = f1.Get("h_ftk_accepted_hitPattern"); h_ftk_accepted_hitPattern2 = f2.Get("h_ftk_accepted_hitPattern")
h_ftk_refit_accepted_hitPattern1 = f1.Get("h_ftk_refit_accepted_hitPattern"); h_ftk_refit_accepted_hitPattern2 = f2.Get("h_ftk_refit_accepted_hitPattern")

histocoordmasketa_reco_EndCap1 = f1.Get("histocoordmasketa_reco_EndCap"); histocoordmasketa_reco_EndCap2 = f2.Get("histocoordmasketa_reco_EndCap")
histocoordmaskphi_reco_EndCap1 = f1.Get("histocoordmaskphi_reco_EndCap"); histocoordmaskphi_reco_EndCap2 = f2.Get("histocoordmaskphi_reco_EndCap")
histocoordmaskz0_reco_EndCap1 = f1.Get("histocoordmaskz0_reco_EndCap"); histocoordmaskz0_reco_EndCap2 = f2.Get("histocoordmaskz0_reco_EndCap")
histocoordmasketa_ftk_EndCap1 = f1.Get("histocoordmasketa_ftk_EndCap"); histocoordmasketa_ftk_EndCap2 = f2.Get("histocoordmasketa_ftk_EndCap")
histocoordmaskphi_ftk_EndCap1 = f1.Get("histocoordmaskphi_ftk_EndCap"); histocoordmaskphi_ftk_EndCap2 = f2.Get("histocoordmaskphi_ftk_EndCap")
histocoordmaskz0_ftk_EndCap1 = f1.Get("histocoordmaskz0_ftk_EndCap"); histocoordmaskz0_ftk_EndCap2 = f2.Get("histocoordmaskz0_ftk_EndCap")
histocoordmasketa_ftkrefit_EndCap1 = f1.Get("histocoordmasketa_ftkrefit_EndCap"); histocoordmasketa_ftkrefit_EndCap2 = f2.Get("histocoordmasketa_ftkrefit_EndCap")
histocoordmaskphi_ftkrefit_EndCap1 = f1.Get("histocoordmaskphi_ftkrefit_EndCap"); histocoordmaskphi_ftkrefit_EndCap2 = f2.Get("histocoordmaskphi_ftkrefit_EndCap")
histocoordmaskz0_ftkrefit_EndCap1 = f1.Get("histocoordmaskz0_ftkrefit_EndCap"); histocoordmaskz0_ftkrefit_EndCap2 = f2.Get("histocoordmaskz0_ftkrefit_EndCap")

histocoordmasketa_reco_Barrel1 = f1.Get("histocoordmasketa_reco_Barrel"); histocoordmasketa_reco_Barrel2 = f2.Get("histocoordmasketa_reco_Barrel")
histocoordmaskphi_reco_Barrel1 = f1.Get("histocoordmaskphi_reco_Barrel"); histocoordmaskphi_reco_Barrel2 = f2.Get("histocoordmaskphi_reco_Barrel")
histocoordmaskz0_reco_Barrel1 = f1.Get("histocoordmaskz0_reco_Barrel"); histocoordmaskz0_reco_Barrel2 = f2.Get("histocoordmaskz0_reco_Barrel")
histocoordmasketa_ftk_Barrel1 = f1.Get("histocoordmasketa_ftk_Barrel"); histocoordmasketa_ftk_Barrel2 = f2.Get("histocoordmasketa_ftk_Barrel")
histocoordmaskphi_ftk_Barrel1 = f1.Get("histocoordmaskphi_ftk_Barrel"); histocoordmaskphi_ftk_Barrel2 = f2.Get("histocoordmaskphi_ftk_Barrel")
histocoordmaskz0_ftk_Barrel1 = f1.Get("histocoordmaskz0_ftk_Barrel"); histocoordmaskz0_ftk_Barrel2 = f2.Get("histocoordmaskz0_ftk_Barrel")
histocoordmasketa_ftkrefit_Barrel1 = f1.Get("histocoordmasketa_ftkrefit_Barrel"); histocoordmasketa_ftkrefit_Barrel2 = f2.Get("histocoordmasketa_ftkrefit_Barrel")
histocoordmaskphi_ftkrefit_Barrel1 = f1.Get("histocoordmaskphi_ftkrefit_Barrel"); histocoordmaskphi_ftkrefit_Barrel2 = f2.Get("histocoordmaskphi_ftkrefit_Barrel")
histocoordmaskz0_ftkrefit_Barrel1 = f1.Get("histocoordmaskz0_ftkrefit_Barrel"); histocoordmaskz0_ftkrefit_Barrel2 = f2.Get("histocoordmaskz0_ftkrefit_Barrel")

histocoordmasketa_reco1 = f1.Get("histocoordmasketa_reco"); histocoordmasketa_reco2 = f2.Get("histocoordmasketa_reco")
histocoordmaskphi_reco1 = f1.Get("histocoordmaskphi_reco"); histocoordmaskphi_reco2 = f2.Get("histocoordmaskphi_reco")
histocoordmaskz0_reco1 = f1.Get("histocoordmaskz0_reco"); histocoordmaskz0_reco2 = f2.Get("histocoordmaskz0_reco")
histocoordmasketa_ftk1 = f1.Get("histocoordmasketa_ftk"); histocoordmasketa_ftk2 = f2.Get("histocoordmasketa_ftk")
histocoordmaskphi_ftk1 = f1.Get("histocoordmaskphi_ftk"); histocoordmaskphi_ftk2 = f2.Get("histocoordmaskphi_ftk")
histocoordmaskz0_ftk1 = f1.Get("histocoordmaskz0_ftk"); histocoordmaskz0_ftk2 = f2.Get("histocoordmaskz0_ftk")
histocoordmasketa_ftkrefit1 = f1.Get("histocoordmasketa_ftkrefit"); histocoordmasketa_ftkrefit2 = f2.Get("histocoordmasketa_ftkrefit")
histocoordmaskphi_ftkrefit1 = f1.Get("histocoordmaskphi_ftkrefit"); histocoordmaskphi_ftkrefit2 = f2.Get("histocoordmaskphi_ftkrefit")
histocoordmaskz0_ftkrefit1 = f1.Get("histocoordmaskz0_ftkrefit"); histocoordmaskz0_ftkrefit2 = f2.Get("histocoordmaskz0_ftkrefit")

if isData == False:
	tgae_truth_reco_effi_vs_truth_pt1 = f1.Get("effi_truth_reco_pt");  tgae_truth_reco_effi_vs_truth_pt2 = f2.Get("effi_truth_reco_pt")
	tgae_truth_reco_effi_vs_truth_eta1 = f1.Get("effi_truth_reco_eta");  tgae_truth_reco_effi_vs_truth_eta2 = f2.Get("effi_truth_reco_eta")
	tgae_truth_reco_effi_vs_truth_phi1 = f1.Get("effi_truth_reco_phi");  tgae_truth_reco_effi_vs_truth_phi2 = f2.Get("effi_truth_reco_phi")
	tgae_truth_reco_effi_vs_truth_d01 = f1.Get("effi_truth_reco_d0");  tgae_truth_reco_effi_vs_truth_d02 = f2.Get("effi_truth_reco_d0")
	tgae_truth_reco_effi_vs_truth_z01 = f1.Get("effi_truth_reco_z0");  tgae_truth_reco_effi_vs_truth_z02 = f2.Get("effi_truth_reco_z0")
	tgae_truth_ftk_effi_vs_truth_pt1 = f1.Get("effi_truth_ftk_pt");  tgae_truth_ftk_effi_vs_truth_pt2 = f2.Get("effi_truth_ftk_pt")
	tgae_truth_ftk_effi_vs_truth_eta1 = f1.Get("effi_truth_ftk_eta");  tgae_truth_ftk_effi_vs_truth_eta2 = f2.Get("effi_truth_ftk_eta")
	tgae_truth_ftk_effi_vs_truth_phi1 = f1.Get("effi_truth_ftk_phi");  tgae_truth_ftk_effi_vs_truth_phi2 = f2.Get("effi_truth_ftk_phi")
	tgae_truth_ftk_effi_vs_truth_d01 = f1.Get("effi_truth_ftk_d0");  tgae_truth_ftk_effi_vs_truth_d02 = f2.Get("effi_truth_ftk_d0")
	tgae_truth_ftk_effi_vs_truth_z01 = f1.Get("effi_truth_ftk_z0");  tgae_truth_ftk_effi_vs_truth_z02 = f2.Get("effi_truth_ftk_z0")
	tgae_truth_ftk_refit_effi_vs_truth_pt1 = f1.Get("effi_truth_ftk_refit_pt");  tgae_truth_ftk_refit_effi_vs_truth_pt2 = f2.Get("effi_truth_ftk_refit_pt")
	tgae_truth_ftk_refit_effi_vs_truth_eta1 = f1.Get("effi_truth_ftk_refit_eta");  tgae_truth_ftk_refit_effi_vs_truth_eta2 = f2.Get("effi_truth_ftk_refit_eta")
	tgae_truth_ftk_refit_effi_vs_truth_phi1 = f1.Get("effi_truth_ftk_refit_phi");  tgae_truth_ftk_refit_effi_vs_truth_phi2 = f2.Get("effi_truth_ftk_refit_phi")
	tgae_truth_ftk_refit_effi_vs_truth_d01 = f1.Get("effi_truth_ftk_refit_d0");  tgae_truth_ftk_refit_effi_vs_truth_d02 = f2.Get("effi_truth_ftk_refit_d0")
	tgae_truth_ftk_refit_effi_vs_truth_z01 = f1.Get("effi_truth_ftk_refit_z0");  tgae_truth_ftk_refit_effi_vs_truth_z02 = f2.Get("effi_truth_ftk_refit_z0")

tgae_reco_ftk_effi_vs_reco_pt1 = f1.Get("effi_reco_ftk_pt");  tgae_reco_ftk_effi_vs_reco_pt2 = f2.Get("effi_reco_ftk_pt")
tgae_reco_ftk_effi_vs_reco_eta1 = f1.Get("effi_reco_ftk_eta");  tgae_reco_ftk_effi_vs_reco_eta2 = f2.Get("effi_reco_ftk_eta")
tgae_reco_ftk_effi_vs_reco_phi1 = f1.Get("effi_reco_ftk_phi");  tgae_reco_ftk_effi_vs_reco_phi2 = f2.Get("effi_reco_ftk_phi")
tgae_reco_ftk_effi_vs_reco_d01 = f1.Get("effi_reco_ftk_d0");  tgae_reco_ftk_effi_vs_reco_d02 = f2.Get("effi_reco_ftk_d0")
tgae_reco_ftk_effi_vs_reco_z01 = f1.Get("effi_reco_ftk_z0");  tgae_reco_ftk_effi_vs_reco_z02 = f2.Get("effi_reco_ftk_z0")

tgae_reco_ftk_refit_effi_vs_reco_pt1 = f1.Get("effi_reco_ftk_refit_pt");  tgae_reco_ftk_refit_effi_vs_reco_pt2 = f2.Get("effi_reco_ftk_refit_pt")
tgae_reco_ftk_refit_effi_vs_reco_eta1 = f1.Get("effi_reco_ftk_refit_eta");  tgae_reco_ftk_refit_effi_vs_reco_eta2 = f2.Get("effi_reco_ftk_refit_eta")
tgae_reco_ftk_refit_effi_vs_reco_phi1 = f1.Get("effi_reco_ftk_refit_phi");  tgae_reco_ftk_refit_effi_vs_reco_phi2 = f2.Get("effi_reco_ftk_refit_phi")
tgae_reco_ftk_refit_effi_vs_reco_d01 = f1.Get("effi_reco_ftk_refit_d0");  tgae_reco_ftk_refit_effi_vs_reco_d02 = f2.Get("effi_reco_ftk_refit_d0")
tgae_reco_ftk_refit_effi_vs_reco_z01 = f1.Get("effi_reco_ftk_refit_z0");  tgae_reco_ftk_refit_effi_vs_reco_z02 = f2.Get("effi_reco_ftk_refit_z0")



print("Creating THStack")
if isData == False:
	h_truth_pt_stack =THStack("h_truth_pt_stack ", "")
	h_truth_eta_stack =THStack("h_truth_eta_stack ", "")
	h_truth_phi_stack =THStack("h_truth_phi_stack ", "")
	h_truth_m_stack =THStack("h_truth_m_stack ", "")
	h_truth_d0_stack =THStack("h_truth_d0_stack ", "")
	h_truth_z0_stack =THStack("h_truth_z0_stack ", "")
	h_truth_qop_stack =THStack("h_truth_qop_stack ", "")
	h_truth_charge_stack =THStack("h_truth_charge_stack ", "")

h_reco_accepted_pt_stack =THStack("h_reco_accepted_pt_stack ", "")
h_reco_accepted_eta_stack =THStack("h_reco_accepted_eta_stack ", "")
h_reco_accepted_phi_stack =THStack("h_reco_accepted_phi_stack ", "")
# h_reco_accepted_m_stack =THStack("h_reco_accepted_m_stack ", "")
h_reco_accepted_d0_stack =THStack("h_reco_accepted_d0_stack ", "")
h_reco_accepted_z0_stack =THStack("h_reco_accepted_z0_stack ", "")
h_reco_accepted_qop_stack =THStack("h_reco_accepted_qop_stack ", "")
h_reco_accepted_charge_stack =THStack("h_reco_accepted_charge_stack ", "")
h_reco_accepted_chi2_stack =THStack("h_reco_accepted_chi2_stack ", "")

h_reco_inclusive_pt_stack =THStack("h_reco_inclusive_pt_stack ", "")
h_reco_inclusive_eta_stack =THStack("h_reco_inclusive_eta_stack ", "")
h_reco_inclusive_phi_stack =THStack("h_reco_inclusive_phi_stack ", "")
# h_reco_inclusive_m_stack =THStack("h_reco_inclusive_m_stack ", "")
h_reco_inclusive_d0_stack =THStack("h_reco_inclusive_d0_stack ", "")
h_reco_inclusive_z0_stack =THStack("h_reco_inclusive_z0_stack ", "")
h_reco_inclusive_qop_stack =THStack("h_reco_inclusive_qop_stack ", "")
h_reco_inclusive_charge_stack =THStack("h_reco_inclusive_charge_stack ", "")
h_reco_inclusive_chi2_stack =THStack("h_reco_inclusive_chi2_stack ", "")

h_ftk_accepted_pt_stack =THStack("h_ftk_accepted_pt_stack ", "")
h_ftk_accepted_eta_stack =THStack("h_ftk_accepted_eta_stack ", "")
h_ftk_accepted_phi_stack =THStack("h_ftk_accepted_phi_stack ", "")
# h_ftk_accepted_m_stack =THStack("h_ftk_accepted_m_stack ", "")
h_ftk_accepted_d0_stack =THStack("h_ftk_accepted_d0_stack ", "")
h_ftk_accepted_corrected_d0_stack =THStack("h_ftk_accepted_corrected_d0_stack ", "")
h_ftk_accepted_z0_stack =THStack("h_ftk_accepted_z0_stack ", "")
h_ftk_accepted_qop_stack =THStack("h_ftk_accepted_qop_stack ", "")
h_ftk_accepted_charge_stack =THStack("h_ftk_accepted_charge_stack ", "")
h_ftk_accepted_chi2_stack =THStack("h_ftk_accepted_chi2_stack ", "")

h_ftk_inclusive_pt_stack =THStack("h_ftk_inclusive_pt_stack ", "")
h_ftk_inclusive_eta_stack =THStack("h_ftk_inclusive_eta_stack ", "")
h_ftk_inclusive_phi_stack =THStack("h_ftk_inclusive_phi_stack ", "")
# h_ftk_inclusive_m_stack =THStack("h_ftk_inclusive_m_stack ", "")
h_ftk_inclusive_d0_stack =THStack("h_ftk_inclusive_d0_stack ", "")
h_ftk_inclusive_corrected_d0_stack =THStack("h_ftk_inclusive_corrected_d0_stack ", "")
h_ftk_inclusive_z0_stack =THStack("h_ftk_inclusive_z0_stack ", "")
h_ftk_inclusive_qop_stack =THStack("h_ftk_inclusive_qop_stack ", "")
h_ftk_inclusive_charge_stack =THStack("h_ftk_inclusive_charge_stack ", "")
h_ftk_inclusive_chi2_stack =THStack("h_ftk_inclusive_chi2_stack ", "")

h_ftk_refit_accepted_pt_stack =THStack("h_ftk_refit_accepted_pt_stack ", "")
h_ftk_refit_accepted_eta_stack =THStack("h_ftk_refit_accepted_eta_stack ", "")
h_ftk_refit_accepted_phi_stack =THStack("h_ftk_refit_accepted_phi_stack ", "")
# h_ftk_refit_accepted_m_stack =THStack("h_ftk_refit_accepted_m_stack ", "")
h_ftk_refit_accepted_d0_stack =THStack("h_ftk_refit_accepted_d0_stack ", "")
h_ftk_refit_accepted_z0_stack =THStack("h_ftk_refit_accepted_z0_stack ", "")
h_ftk_refit_accepted_qop_stack =THStack("h_ftk_refit_accepted_qop_stack ", "")
h_ftk_refit_accepted_charge_stack =THStack("h_ftk_refit_accepted_charge_stack ", "")
h_ftk_refit_accepted_chi2_stack =THStack("h_ftk_refit_accepted_chi2_stack ", "")

h_ftk_refit_inclusive_pt_stack =THStack("h_ftk_refit_inclusive_pt_stack ", "")
h_ftk_refit_inclusive_eta_stack =THStack("h_ftk_refit_inclusive_eta_stack ", "")
h_ftk_refit_inclusive_phi_stack =THStack("h_ftk_refit_inclusive_phi_stack ", "")
# h_ftk_refit_inclusive_m_stack =THStack("h_ftk_refit_inclusive_m_stack ", "")
h_ftk_refit_inclusive_d0_stack =THStack("h_ftk_refit_inclusive_d0_stack ", "")
h_ftk_refit_inclusive_z0_stack =THStack("h_ftk_refit_inclusive_z0_stack ", "")
h_ftk_refit_inclusive_qop_stack =THStack("h_ftk_refit_inclusive_qop_stack ", "")
h_ftk_refit_inclusive_charge_stack =THStack("h_ftk_refit_inclusive_charge_stack ", "")
h_ftk_refit_inclusive_chi2_stack =THStack("h_ftk_refit_inclusive_chi2_stack ", "")

if isData == False:
	h_reco_truthMatched_pt_bias_stack =THStack("h_reco_truthMatched_pt_bias_stack ", "")
	h_reco_truthMatched_eta_bias_stack =THStack("h_reco_truthMatched_eta_bias_stack ", "")
	h_reco_truthMatched_phi_bias_stack =THStack("h_reco_truthMatched_phi_bias_stack ", "")
	h_reco_truthMatched_d0_bias_stack =THStack("h_reco_truthMatched_d0_bias_stack ", "")

	h_truth_recoMatch_track_eta_stack =THStack("h_truth_recoMatch_track_eta_stack ", "")
	h_truth_recoMatch_track_phi_stack =THStack("h_truth_recoMatch_track_phi_stack ", "")
	h_reco_truthMatch_track_eta_stack =THStack("h_reco_truthMatch_track_eta_stack ", "")
	h_reco_truthMatch_track_phi_stack =THStack("h_reco_truthMatch_track_phi_stack ", "")
	h_truth_recoMatch_track_pt_stack =THStack("h_truth_recoMatch_track_pt_stack ", "")
	h_truth_recoMatch_track_d0_stack =THStack("h_truth_recoMatch_track_d0_stack ", "")
	h_truth_recoMatch_track_z0_stack =THStack("h_truth_recoMatch_track_z0_stack ", "")

	h_truth_ftk_Matched_pt_bias_stack =THStack("h_truth_ftk_Matched_pt_bias_stack ", "")
	h_truth_ftk_Matched_eta_bias_stack =THStack("h_truth_ftk_Matched_eta_bias_stack ", "")
	h_truth_ftk_Matched_phi_bias_stack =THStack("h_truth_ftk_Matched_phi_bias_stack ", "")
	h_truth_ftk_Matched_d0_bias_stack =THStack("h_truth_ftk_Matched_d0_bias_stack ", "")
	h_truth_ftk_Matched_corrected_d0_bias_stack =THStack("h_truth_ftk_Matched_corrected_d0_bias_stack ", "")

	h_ftk_truthMatch_track_eta_stack =THStack("h_ftk_truthMatch_track_eta_stack ", "")
	h_ftk_truthMatch_track_phi_stack =THStack("h_ftk_truthMatch_track_phi_stack ", "")
	h_truth_ftkMatch_track_eta_stack =THStack("h_truth_ftkMatch_track_eta_stack ", "")
	h_truth_ftkMatch_track_phi_stack =THStack("h_truth_ftkMatch_track_phi_stack ", "")
	h_ftk_truthMatch_track_pt_stack =THStack("h_ftk_truthMatch_track_pt_stack ", "")
	h_ftk_truthMatch_track_d0_stack =THStack("h_ftk_truthMatch_track_d0_stack ", "")
	h_ftk_truthMatch_track_z0_stack =THStack("h_ftk_truthMatch_track_z0_stack ", "")

	h_truth_ftk_refitMatched_pt_bias_stack =THStack("h_truth_ftk_refitMatched_pt_bias_stack ", "")
	h_truth_ftk_refitMatched_eta_bias_stack =THStack("h_truth_ftk_refitMatched_eta_bias_stack ", "")
	h_truth_ftk_refitMatched_phi_bias_stack =THStack("h_truth_ftk_refitMatched_phi_bias_stack ", "")
	h_truth_ftk_refitMatched_d0_bias_stack =THStack("h_truth_ftk_refitMatched_d0_bias_stack ", "")

	h_ftk_refit_truthMatch_track_eta_stack =THStack("h_ftk_refit_truthMatch_track_eta_stack ", "")
	h_ftk_refit_truthMatch_track_phi_stack =THStack("h_ftk_refit_truthMatch_track_phi_stack ", "")
	h_truth_ftkrefitMatch_track_eta_stack =THStack("h_truth_ftkrefitMatch_track_eta_stack ", "")
	h_truth_ftkrefitMatch_track_phi_stack =THStack("h_truth_ftkrefitMatch_track_phi_stack ", "")
	h_ftk_refit_truthMatch_track_pt_stack =THStack("h_ftk_refit_truthMatch_track_pt_stack ", "")
	h_ftk_refit_truthMatch_track_d0_stack =THStack("h_ftk_refit_truthMatch_track_d0_stack ", "")
	h_ftk_refit_truthMatch_track_z0_stack =THStack("h_ftk_refit_truthMatch_track_z0_stack ", "")

h_reco_ftkMatched_pt_bias_stack =THStack("h_reco_ftkMatched_pt_bias_stack ", "")
h_reco_ftkMatched_eta_bias_stack =THStack("h_reco_ftkMatched_eta_bias_stack ", "")
h_reco_ftkMatched_phi_bias_stack =THStack("h_reco_ftkMatched_phi_bias_stack ", "")
h_reco_ftkMatched_d0_bias_stack =THStack("h_reco_ftkMatched_d0_bias_stack ", "")
h_reco_ftkMatched_corrected_d0_bias_stack =THStack("h_reco_ftkMatched_corrected_d0_bias_stack ", "")

h_ftk_recoMatch_track_eta_stack =THStack("h_ftk_recoMatch_track_eta_stack ", "")
h_ftk_recoMatch_track_phi_stack =THStack("h_ftk_recoMatch_track_phi_stack ", "")
h_reco_ftkMatch_track_eta_stack =THStack("h_reco_ftkMatch_track_eta_stack ", "")
h_reco_ftkMatch_track_phi_stack =THStack("h_reco_ftkMatch_track_phi_stack ", "")
h_ftk_recoMatch_track_pt_stack =THStack("h_ftk_recoMatch_track_pt_stack ", "")
h_ftk_recoMatch_track_d0_stack =THStack("h_ftk_recoMatch_track_d0_stack ", "")
# h_ftk_recoMatch_track_corrected_d0_stack =THStack("h_ftk_recoMatch_track_corrected_d0_stack ", "")
h_ftk_recoMatch_track_z0_stack =THStack("h_ftk_recoMatch_track_z0_stack ", "")

h_reco_ftk_refitMatched_pt_bias_stack =THStack("h_reco_ftk_refitMatched_pt_bias_stack ", "")
h_reco_ftk_refitMatched_eta_bias_stack =THStack("h_reco_ftk_refitMatched_eta_bias_stack ", "")
h_reco_ftk_refitMatched_phi_bias_stack =THStack("h_reco_ftk_refitMatched_phi_bias_stack ", "")
h_reco_ftk_refitMatched_d0_bias_stack =THStack("h_reco_ftk_refitMatched_d0_bias_stack ", "")

h_ftk_refit_recoMatch_track_eta_stack =THStack("h_ftk_refit_recoMatch_track_eta_stack ", "")
h_ftk_refit_recoMatch_track_phi_stack =THStack("h_ftk_refit_recoMatch_track_phi_stack ", "")
h_reco_ftkrefitMatch_track_eta_stack =THStack("h_reco_ftkrefitMatch_track_eta_stack ", "")
h_reco_ftkrefitMatch_track_phi_stack =THStack("h_reco_ftkrefitMatch_track_phi_stack ", "")
h_ftk_refit_recoMatch_track_pt_stack =THStack("h_ftk_refit_recoMatch_track_pt_stack ", "")
h_ftk_refit_recoMatch_track_d0_stack =THStack("h_ftk_refit_recoMatch_track_d0_stack ", "")
h_ftk_refit_recoMatch_track_z0_stack =THStack("h_ftk_refit_recoMatch_track_z0_stack ", "")

h_reco_accepted_hitPattern_EndCap_stack =THStack("h_reco_accepted_hitPattern_EndCap_stack ", "")
h_ftk_accepted_hitPattern_EndCap_stack =THStack("h_ftk_accepted_hitPattern_EndCap_stack ", "")
h_ftk_refit_accepted_hitPattern_EndCap_stack =THStack("h_ftk_refit_accepted_hitPattern_EndCap_stack ", "")

h_reco_accepted_hitPattern_Barrel_stack =THStack("h_reco_accepted_hitPattern_Barrel_stack ", "")
h_ftk_accepted_hitPattern_Barrel_stack =THStack("h_ftk_accepted_hitPattern_Barrel_stack ", "")
h_ftk_refit_accepted_hitPattern_Barrel_stack =THStack("h_ftk_refit_accepted_hitPattern_Barrel_stack ", "")

h_reco_accepted_hitPattern_stack =THStack("h_reco_accepted_hitPattern_stack ", "")
h_ftk_accepted_hitPattern_stack =THStack("h_ftk_accepted_hitPattern_stack ", "")
h_ftk_refit_accepted_hitPattern_stack =THStack("h_ftk_refit_accepted_hitPattern_stack ", "")

if isData == False:
	tgae_truth_reco_effi_vs_truth_pt_stack = TMultiGraph()
	tgae_truth_reco_effi_vs_truth_eta_stack = TMultiGraph()
	tgae_truth_reco_effi_vs_truth_phi_stack = TMultiGraph()
	tgae_truth_reco_effi_vs_truth_d0_stack = TMultiGraph()
	tgae_truth_reco_effi_vs_truth_z0_stack = TMultiGraph()
	tgae_truth_ftk_effi_vs_truth_pt_stack = TMultiGraph()
	tgae_truth_ftk_effi_vs_truth_eta_stack = TMultiGraph()
	tgae_truth_ftk_effi_vs_truth_phi_stack = TMultiGraph()
	tgae_truth_ftk_effi_vs_truth_d0_stack = TMultiGraph()
	tgae_truth_ftk_effi_vs_truth_z0_stack = TMultiGraph()
	tgae_truth_ftk_refit_effi_vs_truth_pt_stack = TMultiGraph()
	tgae_truth_ftk_refit_effi_vs_truth_eta_stack = TMultiGraph()
	tgae_truth_ftk_refit_effi_vs_truth_phi_stack = TMultiGraph()
	tgae_truth_ftk_refit_effi_vs_truth_d0_stack = TMultiGraph()
	tgae_truth_ftk_refit_effi_vs_truth_z0_stack = TMultiGraph()

tgae_reco_ftk_effi_vs_reco_pt_stack = TMultiGraph()
tgae_reco_ftk_effi_vs_reco_eta_stack = TMultiGraph()
tgae_reco_ftk_effi_vs_reco_phi_stack = TMultiGraph()
tgae_reco_ftk_effi_vs_reco_d0_stack = TMultiGraph()
tgae_reco_ftk_effi_vs_reco_z0_stack = TMultiGraph()

tgae_reco_ftk_refit_effi_vs_reco_pt_stack = TMultiGraph()
tgae_reco_ftk_refit_effi_vs_reco_eta_stack = TMultiGraph()
tgae_reco_ftk_refit_effi_vs_reco_phi_stack = TMultiGraph()
tgae_reco_ftk_refit_effi_vs_reco_d0_stack = TMultiGraph()
tgae_reco_ftk_refit_effi_vs_reco_z0_stack = TMultiGraph()

print("Setting up histograms")
if isData == False:
	h_truth_pt1.SetLineColor(kRed); h_truth_pt2.SetLineColor(kBlue)
	h_truth_eta1.SetLineColor(kRed); h_truth_eta2.SetLineColor(kBlue)
	h_truth_phi1.SetLineColor(kRed); h_truth_phi2.SetLineColor(kBlue)
	h_truth_m1.SetLineColor(kRed); h_truth_m2.SetLineColor(kBlue)
	h_truth_d01.SetLineColor(kRed); h_truth_d02.SetLineColor(kBlue)
	h_truth_z01.SetLineColor(kRed); h_truth_z02.SetLineColor(kBlue)
	h_truth_qop1.SetLineColor(kRed); h_truth_qop2.SetLineColor(kBlue)
	h_truth_charge1.SetLineColor(kRed); h_truth_charge2.SetLineColor(kBlue)

h_reco_accepted_pt1.SetLineColor(kRed); h_reco_accepted_pt2.SetLineColor(kBlue)
h_reco_accepted_eta1.SetLineColor(kRed); h_reco_accepted_eta2.SetLineColor(kBlue)
h_reco_accepted_phi1.SetLineColor(kRed); h_reco_accepted_phi2.SetLineColor(kBlue)
# h_reco_accepted_m1.SetLineColor(kRed); h_reco_accepted_m2.SetLineColor(kBlue)
h_reco_accepted_d01.SetLineColor(kRed); h_reco_accepted_d02.SetLineColor(kBlue)
h_reco_accepted_z01.SetLineColor(kRed); h_reco_accepted_z02.SetLineColor(kBlue)
h_reco_accepted_qop1.SetLineColor(kRed); h_reco_accepted_qop2.SetLineColor(kBlue)
h_reco_accepted_charge1.SetLineColor(kRed); h_reco_accepted_charge2.SetLineColor(kBlue)
h_reco_accepted_chi21.SetLineColor(kRed); h_reco_accepted_chi22.SetLineColor(kBlue)

h_reco_inclusive_pt1.SetLineColor(kRed); h_reco_inclusive_pt2.SetLineColor(kBlue)
h_reco_inclusive_eta1.SetLineColor(kRed); h_reco_inclusive_eta2.SetLineColor(kBlue)
h_reco_inclusive_phi1.SetLineColor(kRed); h_reco_inclusive_phi2.SetLineColor(kBlue)
# h_reco_inclusive_m1.SetLineColor(kRed); h_reco_inclusive_m2.SetLineColor(kBlue)
h_reco_inclusive_d01.SetLineColor(kRed); h_reco_inclusive_d02.SetLineColor(kBlue)
h_reco_inclusive_z01.SetLineColor(kRed); h_reco_inclusive_z02.SetLineColor(kBlue)
h_reco_inclusive_qop1.SetLineColor(kRed); h_reco_inclusive_qop2.SetLineColor(kBlue)
h_reco_inclusive_charge1.SetLineColor(kRed); h_reco_inclusive_charge2.SetLineColor(kBlue)
h_reco_inclusive_chi21.SetLineColor(kRed); h_reco_inclusive_chi22.SetLineColor(kBlue)

h_ftk_accepted_pt1.SetLineColor(kRed); h_ftk_accepted_pt2.SetLineColor(kBlue)
h_ftk_accepted_eta1.SetLineColor(kRed); h_ftk_accepted_eta2.SetLineColor(kBlue)
h_ftk_accepted_phi1.SetLineColor(kRed); h_ftk_accepted_phi2.SetLineColor(kBlue)
# h_ftk_accepted_m1.SetLineColor(kRed); h_ftk_accepted_m2.SetLineColor(kBlue)
h_ftk_accepted_d01.SetLineColor(kRed); h_ftk_accepted_d02.SetLineColor(kBlue)
h_ftk_accepted_corrected_d01.SetLineColor(kRed); h_ftk_accepted_corrected_d02.SetLineColor(kBlue)
h_ftk_accepted_z01.SetLineColor(kRed); h_ftk_accepted_z02.SetLineColor(kBlue)
h_ftk_accepted_qop1.SetLineColor(kRed); h_ftk_accepted_qop2.SetLineColor(kBlue)
h_ftk_accepted_charge1.SetLineColor(kRed); h_ftk_accepted_charge2.SetLineColor(kBlue)
h_ftk_accepted_chi21.SetLineColor(kRed); h_ftk_accepted_chi22.SetLineColor(kBlue)

h_ftk_inclusive_pt1.SetLineColor(kRed); h_ftk_inclusive_pt2.SetLineColor(kBlue)
h_ftk_inclusive_eta1.SetLineColor(kRed); h_ftk_inclusive_eta2.SetLineColor(kBlue)
h_ftk_inclusive_phi1.SetLineColor(kRed); h_ftk_inclusive_phi2.SetLineColor(kBlue)
# h_ftk_inclusive_m1.SetLineColor(kRed); h_ftk_inclusive_m2.SetLineColor(kBlue)
h_ftk_inclusive_d01.SetLineColor(kRed); h_ftk_inclusive_d02.SetLineColor(kBlue)
h_ftk_inclusive_corrected_d01.SetLineColor(kRed); h_ftk_inclusive_corrected_d02.SetLineColor(kBlue)
h_ftk_inclusive_z01.SetLineColor(kRed); h_ftk_inclusive_z02.SetLineColor(kBlue)
h_ftk_inclusive_qop1.SetLineColor(kRed); h_ftk_inclusive_qop2.SetLineColor(kBlue)
h_ftk_inclusive_charge1.SetLineColor(kRed); h_ftk_inclusive_charge2.SetLineColor(kBlue)
h_ftk_inclusive_chi21.SetLineColor(kRed); h_ftk_inclusive_chi22.SetLineColor(kBlue)

h_ftk_refit_accepted_pt1.SetLineColor(kRed); h_ftk_refit_accepted_pt2.SetLineColor(kBlue)
h_ftk_refit_accepted_eta1.SetLineColor(kRed); h_ftk_refit_accepted_eta2.SetLineColor(kBlue)
h_ftk_refit_accepted_phi1.SetLineColor(kRed); h_ftk_refit_accepted_phi2.SetLineColor(kBlue)
# h_ftk_refit_accepted_m1.SetLineColor(kRed); h_ftk_refit_accepted_m2.SetLineColor(kBlue)
h_ftk_refit_accepted_d01.SetLineColor(kRed); h_ftk_refit_accepted_d02.SetLineColor(kBlue)
h_ftk_refit_accepted_z01.SetLineColor(kRed); h_ftk_refit_accepted_z02.SetLineColor(kBlue)
h_ftk_refit_accepted_qop1.SetLineColor(kRed); h_ftk_refit_accepted_qop2.SetLineColor(kBlue)
h_ftk_refit_accepted_charge1.SetLineColor(kRed); h_ftk_refit_accepted_charge2.SetLineColor(kBlue)
h_ftk_refit_accepted_chi21.SetLineColor(kRed); h_ftk_refit_accepted_chi22.SetLineColor(kBlue)

h_ftk_refit_inclusive_pt1.SetLineColor(kRed); h_ftk_refit_inclusive_pt2.SetLineColor(kBlue)
h_ftk_refit_inclusive_eta1.SetLineColor(kRed); h_ftk_refit_inclusive_eta2.SetLineColor(kBlue)
h_ftk_refit_inclusive_phi1.SetLineColor(kRed); h_ftk_refit_inclusive_phi2.SetLineColor(kBlue)
# h_ftk_refit_inclusive_m1.SetLineColor(kRed); h_ftk_refit_inclusive_m2.SetLineColor(kBlue)
h_ftk_refit_inclusive_d01.SetLineColor(kRed); h_ftk_refit_inclusive_d02.SetLineColor(kBlue)
h_ftk_refit_inclusive_z01.SetLineColor(kRed); h_ftk_refit_inclusive_z02.SetLineColor(kBlue)
h_ftk_refit_inclusive_qop1.SetLineColor(kRed); h_ftk_refit_inclusive_qop2.SetLineColor(kBlue)
h_ftk_refit_inclusive_charge1.SetLineColor(kRed); h_ftk_refit_inclusive_charge2.SetLineColor(kBlue)
h_ftk_refit_inclusive_chi21.SetLineColor(kRed); h_ftk_refit_inclusive_chi22.SetLineColor(kBlue)

if isData == False:
	h_reco_truthMatched_pt_bias1.SetLineColor(kRed); h_reco_truthMatched_pt_bias2.SetLineColor(kBlue)
	h_reco_truthMatched_eta_bias1.SetLineColor(kRed); h_reco_truthMatched_eta_bias2.SetLineColor(kBlue)
	h_reco_truthMatched_phi_bias1.SetLineColor(kRed); h_reco_truthMatched_phi_bias2.SetLineColor(kBlue)
	h_reco_truthMatched_d0_bias1.SetLineColor(kRed); h_reco_truthMatched_d0_bias2.SetLineColor(kBlue)

	h_truth_recoMatch_track_eta1.SetLineColor(kRed); h_truth_recoMatch_track_eta2.SetLineColor(kBlue)
	h_truth_recoMatch_track_phi1.SetLineColor(kRed); h_truth_recoMatch_track_phi2.SetLineColor(kBlue)
	h_reco_truthMatch_track_eta1.SetLineColor(kRed); h_reco_truthMatch_track_eta2.SetLineColor(kBlue)
	h_reco_truthMatch_track_phi1.SetLineColor(kRed); h_reco_truthMatch_track_phi2.SetLineColor(kBlue)
	h_truth_recoMatch_track_pt1.SetLineColor(kRed); h_truth_recoMatch_track_pt2.SetLineColor(kBlue)
	h_truth_recoMatch_track_d01.SetLineColor(kRed); h_truth_recoMatch_track_d02.SetLineColor(kBlue)
	h_truth_recoMatch_track_z01.SetLineColor(kRed); h_truth_recoMatch_track_z02.SetLineColor(kBlue)

	h_truth_ftk_Matched_pt_bias1.SetLineColor(kRed); h_truth_ftk_Matched_pt_bias2.SetLineColor(kBlue)
	h_truth_ftk_Matched_eta_bias1.SetLineColor(kRed); h_truth_ftk_Matched_eta_bias2.SetLineColor(kBlue)
	h_truth_ftk_Matched_phi_bias1.SetLineColor(kRed); h_truth_ftk_Matched_phi_bias2.SetLineColor(kBlue)
	h_truth_ftk_Matched_d0_bias1.SetLineColor(kRed); h_truth_ftk_Matched_d0_bias2.SetLineColor(kBlue)
	h_truth_ftk_Matched_corrected_d0_bias1.SetLineColor(kRed); h_truth_ftk_Matched_corrected_d0_bias2.SetLineColor(kBlue)

	h_ftk_truthMatch_track_eta1.SetLineColor(kRed); h_ftk_truthMatch_track_eta2.SetLineColor(kBlue)
	h_ftk_truthMatch_track_phi1.SetLineColor(kRed); h_ftk_truthMatch_track_phi2.SetLineColor(kBlue)
	h_truth_ftkMatch_track_eta1.SetLineColor(kRed); h_truth_ftkMatch_track_eta2.SetLineColor(kBlue)
	h_truth_ftkMatch_track_phi1.SetLineColor(kRed); h_truth_ftkMatch_track_phi2.SetLineColor(kBlue)
	h_ftk_truthMatch_track_pt1.SetLineColor(kRed); h_ftk_truthMatch_track_pt2.SetLineColor(kBlue)
	h_ftk_truthMatch_track_d01.SetLineColor(kRed); h_ftk_truthMatch_track_d02.SetLineColor(kBlue)
	h_ftk_truthMatch_track_z01.SetLineColor(kRed); h_ftk_truthMatch_track_z02.SetLineColor(kBlue)

	h_truth_ftk_refitMatched_pt_bias1.SetLineColor(kRed); h_truth_ftk_refitMatched_pt_bias2.SetLineColor(kBlue)
	h_truth_ftk_refitMatched_eta_bias1.SetLineColor(kRed); h_truth_ftk_refitMatched_eta_bias2.SetLineColor(kBlue)
	h_truth_ftk_refitMatched_phi_bias1.SetLineColor(kRed); h_truth_ftk_refitMatched_phi_bias2.SetLineColor(kBlue)
	h_truth_ftk_refitMatched_d0_bias1.SetLineColor(kRed); h_truth_ftk_refitMatched_d0_bias2.SetLineColor(kBlue)

	h_ftk_refit_truthMatch_track_eta1.SetLineColor(kRed); h_ftk_refit_truthMatch_track_eta2.SetLineColor(kBlue)
	h_ftk_refit_truthMatch_track_phi1.SetLineColor(kRed); h_ftk_refit_truthMatch_track_phi2.SetLineColor(kBlue)
	h_truth_ftkrefitMatch_track_eta1.SetLineColor(kRed); h_truth_ftkrefitMatch_track_eta2.SetLineColor(kBlue)
	h_truth_ftkrefitMatch_track_phi1.SetLineColor(kRed); h_truth_ftkrefitMatch_track_phi2.SetLineColor(kBlue)
	h_ftk_refit_truthMatch_track_pt1.SetLineColor(kRed); h_ftk_refit_truthMatch_track_pt2.SetLineColor(kBlue)
	h_ftk_refit_truthMatch_track_d01.SetLineColor(kRed); h_ftk_refit_truthMatch_track_d02.SetLineColor(kBlue)
	h_ftk_refit_truthMatch_track_z01.SetLineColor(kRed); h_ftk_refit_truthMatch_track_z02.SetLineColor(kBlue)

h_reco_ftkMatched_pt_bias1.SetLineColor(kRed); h_reco_ftkMatched_pt_bias2.SetLineColor(kBlue)
h_reco_ftkMatched_eta_bias1.SetLineColor(kRed); h_reco_ftkMatched_eta_bias2.SetLineColor(kBlue)
h_reco_ftkMatched_phi_bias1.SetLineColor(kRed); h_reco_ftkMatched_phi_bias2.SetLineColor(kBlue)
h_reco_ftkMatched_d0_bias1.SetLineColor(kRed); h_reco_ftkMatched_d0_bias2.SetLineColor(kBlue)
h_reco_ftkMatched_corrected_d0_bias1.SetLineColor(kRed); h_reco_ftkMatched_corrected_d0_bias2.SetLineColor(kBlue)

h_ftk_recoMatch_track_eta1.SetLineColor(kRed); h_ftk_recoMatch_track_eta2.SetLineColor(kBlue)
h_ftk_recoMatch_track_phi1.SetLineColor(kRed); h_ftk_recoMatch_track_phi2.SetLineColor(kBlue)
h_reco_ftkMatch_track_eta1.SetLineColor(kRed); h_reco_ftkMatch_track_eta2.SetLineColor(kBlue)
h_reco_ftkMatch_track_phi1.SetLineColor(kRed); h_reco_ftkMatch_track_phi2.SetLineColor(kBlue)
h_ftk_recoMatch_track_pt1.SetLineColor(kRed); h_ftk_recoMatch_track_pt2.SetLineColor(kBlue)
h_ftk_recoMatch_track_d01.SetLineColor(kRed); h_ftk_recoMatch_track_d02.SetLineColor(kBlue)
# h_ftk_recoMatch_track_corrected_d01.SetLineColor(kRed); h_ftk_recoMatch_track_corrected_d02.SetLineColor(kBlue)
h_ftk_recoMatch_track_z01.SetLineColor(kRed); h_ftk_recoMatch_track_z02.SetLineColor(kBlue)

h_reco_ftk_refitMatched_pt_bias1.SetLineColor(kRed); h_reco_ftk_refitMatched_pt_bias2.SetLineColor(kBlue)
h_reco_ftk_refitMatched_eta_bias1.SetLineColor(kRed); h_reco_ftk_refitMatched_eta_bias2.SetLineColor(kBlue)
h_reco_ftk_refitMatched_phi_bias1.SetLineColor(kRed); h_reco_ftk_refitMatched_phi_bias2.SetLineColor(kBlue)
h_reco_ftk_refitMatched_d0_bias1.SetLineColor(kRed); h_reco_ftk_refitMatched_d0_bias2.SetLineColor(kBlue)

h_ftk_refit_recoMatch_track_eta1.SetLineColor(kRed); h_ftk_refit_recoMatch_track_eta2.SetLineColor(kBlue)
h_ftk_refit_recoMatch_track_phi1.SetLineColor(kRed); h_ftk_refit_recoMatch_track_phi2.SetLineColor(kBlue)
h_reco_ftkrefitMatch_track_eta1.SetLineColor(kRed); h_reco_ftkrefitMatch_track_eta2.SetLineColor(kBlue)
h_reco_ftkrefitMatch_track_phi1.SetLineColor(kRed); h_reco_ftkrefitMatch_track_phi2.SetLineColor(kBlue)
h_ftk_refit_recoMatch_track_pt1.SetLineColor(kRed); h_ftk_refit_recoMatch_track_pt2.SetLineColor(kBlue)
h_ftk_refit_recoMatch_track_d01.SetLineColor(kRed); h_ftk_refit_recoMatch_track_d02.SetLineColor(kBlue)
h_ftk_refit_recoMatch_track_z01.SetLineColor(kRed); h_ftk_refit_recoMatch_track_z02.SetLineColor(kBlue)

h_reco_accepted_hitPattern_EndCap1.SetLineColor(kRed); h_reco_accepted_hitPattern_EndCap2.SetLineColor(kBlue)
h_ftk_accepted_hitPattern_EndCap1.SetLineColor(kRed); h_ftk_accepted_hitPattern_EndCap2.SetLineColor(kBlue)
h_ftk_refit_accepted_hitPattern_EndCap1.SetLineColor(kRed); h_ftk_refit_accepted_hitPattern_EndCap2.SetLineColor(kBlue)

h_reco_accepted_hitPattern_Barrel1.SetLineColor(kRed); h_reco_accepted_hitPattern_Barrel2.SetLineColor(kBlue)
h_ftk_accepted_hitPattern_Barrel1.SetLineColor(kRed); h_ftk_accepted_hitPattern_Barrel2.SetLineColor(kBlue)
h_ftk_refit_accepted_hitPattern_Barrel1.SetLineColor(kRed); h_ftk_refit_accepted_hitPattern_Barrel2.SetLineColor(kBlue)

h_reco_accepted_hitPattern1.SetLineColor(kRed); h_reco_accepted_hitPattern2.SetLineColor(kBlue)
h_ftk_accepted_hitPattern1.SetLineColor(kRed); h_ftk_accepted_hitPattern2.SetLineColor(kBlue)
h_ftk_refit_accepted_hitPattern1.SetLineColor(kRed); h_ftk_refit_accepted_hitPattern2.SetLineColor(kBlue)


if isData == False:
	tgae_truth_reco_effi_vs_truth_pt1.SetLineColor(kRed); tgae_truth_reco_effi_vs_truth_pt2.SetLineColor(kBlue)
	tgae_truth_reco_effi_vs_truth_eta1.SetLineColor(kRed); tgae_truth_reco_effi_vs_truth_eta2.SetLineColor(kBlue)
	tgae_truth_reco_effi_vs_truth_phi1.SetLineColor(kRed); tgae_truth_reco_effi_vs_truth_phi2.SetLineColor(kBlue)
	tgae_truth_reco_effi_vs_truth_d01.SetLineColor(kRed); tgae_truth_reco_effi_vs_truth_d02.SetLineColor(kBlue)
	tgae_truth_reco_effi_vs_truth_z01.SetLineColor(kRed); tgae_truth_reco_effi_vs_truth_z02.SetLineColor(kBlue)
	tgae_truth_ftk_effi_vs_truth_pt1.SetLineColor(kRed); tgae_truth_ftk_effi_vs_truth_pt2.SetLineColor(kBlue)
	tgae_truth_ftk_effi_vs_truth_eta1.SetLineColor(kRed); tgae_truth_ftk_effi_vs_truth_eta2.SetLineColor(kBlue)
	tgae_truth_ftk_effi_vs_truth_phi1.SetLineColor(kRed); tgae_truth_ftk_effi_vs_truth_phi2.SetLineColor(kBlue)
	tgae_truth_ftk_effi_vs_truth_d01.SetLineColor(kRed); tgae_truth_ftk_effi_vs_truth_d02.SetLineColor(kBlue)
	tgae_truth_ftk_effi_vs_truth_z01.SetLineColor(kRed); tgae_truth_ftk_effi_vs_truth_z02.SetLineColor(kBlue)
	tgae_truth_ftk_refit_effi_vs_truth_pt1.SetLineColor(kRed); tgae_truth_ftk_refit_effi_vs_truth_pt2.SetLineColor(kBlue)
	tgae_truth_ftk_refit_effi_vs_truth_eta1.SetLineColor(kRed); tgae_truth_ftk_refit_effi_vs_truth_eta2.SetLineColor(kBlue)
	tgae_truth_ftk_refit_effi_vs_truth_phi1.SetLineColor(kRed); tgae_truth_ftk_refit_effi_vs_truth_phi2.SetLineColor(kBlue)
	tgae_truth_ftk_refit_effi_vs_truth_d01.SetLineColor(kRed); tgae_truth_ftk_refit_effi_vs_truth_d02.SetLineColor(kBlue)
	tgae_truth_ftk_refit_effi_vs_truth_z01.SetLineColor(kRed); tgae_truth_ftk_refit_effi_vs_truth_z02.SetLineColor(kBlue)

tgae_reco_ftk_effi_vs_reco_pt1.SetLineColor(kRed); tgae_reco_ftk_effi_vs_reco_pt2.SetLineColor(kBlue)
tgae_reco_ftk_effi_vs_reco_eta1.SetLineColor(kRed); tgae_reco_ftk_effi_vs_reco_eta2.SetLineColor(kBlue)
tgae_reco_ftk_effi_vs_reco_phi1.SetLineColor(kRed); tgae_reco_ftk_effi_vs_reco_phi2.SetLineColor(kBlue)
tgae_reco_ftk_effi_vs_reco_d01.SetLineColor(kRed); tgae_reco_ftk_effi_vs_reco_d02.SetLineColor(kBlue)
tgae_reco_ftk_effi_vs_reco_z01.SetLineColor(kRed); tgae_reco_ftk_effi_vs_reco_z02.SetLineColor(kBlue)

tgae_reco_ftk_refit_effi_vs_reco_pt1.SetLineColor(kRed); tgae_reco_ftk_refit_effi_vs_reco_pt2.SetLineColor(kBlue)
tgae_reco_ftk_refit_effi_vs_reco_eta1.SetLineColor(kRed); tgae_reco_ftk_refit_effi_vs_reco_eta2.SetLineColor(kBlue)
tgae_reco_ftk_refit_effi_vs_reco_phi1.SetLineColor(kRed); tgae_reco_ftk_refit_effi_vs_reco_phi2.SetLineColor(kBlue)
tgae_reco_ftk_refit_effi_vs_reco_d01.SetLineColor(kRed); tgae_reco_ftk_refit_effi_vs_reco_d02.SetLineColor(kBlue)
tgae_reco_ftk_refit_effi_vs_reco_z01.SetLineColor(kRed); tgae_reco_ftk_refit_effi_vs_reco_z02.SetLineColor(kBlue)

if isData == False:
	tgae_truth_reco_effi_vs_truth_pt1.SetFillStyle(0); tgae_truth_reco_effi_vs_truth_pt2.SetFillStyle(0)
	tgae_truth_reco_effi_vs_truth_eta1.SetFillStyle(0); tgae_truth_reco_effi_vs_truth_eta2.SetFillStyle(0)
	tgae_truth_reco_effi_vs_truth_phi1.SetFillStyle(0); tgae_truth_reco_effi_vs_truth_phi2.SetFillStyle(0)
	tgae_truth_reco_effi_vs_truth_d01.SetFillStyle(0); tgae_truth_reco_effi_vs_truth_d02.SetFillStyle(0)
	tgae_truth_reco_effi_vs_truth_z01.SetFillStyle(0); tgae_truth_reco_effi_vs_truth_z02.SetFillStyle(0)
	tgae_truth_ftk_effi_vs_truth_pt1.SetFillStyle(0); tgae_truth_ftk_effi_vs_truth_pt2.SetFillStyle(0)
	tgae_truth_ftk_effi_vs_truth_eta1.SetFillStyle(0); tgae_truth_ftk_effi_vs_truth_eta2.SetFillStyle(0)
	tgae_truth_ftk_effi_vs_truth_phi1.SetFillStyle(0); tgae_truth_ftk_effi_vs_truth_phi2.SetFillStyle(0)
	tgae_truth_ftk_effi_vs_truth_d01.SetFillStyle(0); tgae_truth_ftk_effi_vs_truth_d02.SetFillStyle(0)
	tgae_truth_ftk_effi_vs_truth_z01.SetFillStyle(0); tgae_truth_ftk_effi_vs_truth_z02.SetFillStyle(0)
	tgae_truth_ftk_refit_effi_vs_truth_pt1.SetFillStyle(0); tgae_truth_ftk_refit_effi_vs_truth_pt2.SetFillStyle(0)
	tgae_truth_ftk_refit_effi_vs_truth_eta1.SetFillStyle(0); tgae_truth_ftk_refit_effi_vs_truth_eta2.SetFillStyle(0)
	tgae_truth_ftk_refit_effi_vs_truth_phi1.SetFillStyle(0); tgae_truth_ftk_refit_effi_vs_truth_phi2.SetFillStyle(0)
	tgae_truth_ftk_refit_effi_vs_truth_d01.SetFillStyle(0); tgae_truth_ftk_refit_effi_vs_truth_d02.SetFillStyle(0)
	tgae_truth_ftk_refit_effi_vs_truth_z01.SetFillStyle(0); tgae_truth_ftk_refit_effi_vs_truth_z02.SetFillStyle(0)

tgae_reco_ftk_effi_vs_reco_pt1.SetFillStyle(0); tgae_reco_ftk_effi_vs_reco_pt2.SetFillStyle(0)
tgae_reco_ftk_effi_vs_reco_eta1.SetFillStyle(0); tgae_reco_ftk_effi_vs_reco_eta2.SetFillStyle(0)
tgae_reco_ftk_effi_vs_reco_phi1.SetFillStyle(0); tgae_reco_ftk_effi_vs_reco_phi2.SetFillStyle(0)
tgae_reco_ftk_effi_vs_reco_d01.SetFillStyle(0); tgae_reco_ftk_effi_vs_reco_d02.SetFillStyle(0)
tgae_reco_ftk_effi_vs_reco_z01.SetFillStyle(0); tgae_reco_ftk_effi_vs_reco_z02.SetFillStyle(0)

tgae_reco_ftk_refit_effi_vs_reco_pt1.SetFillStyle(0); tgae_reco_ftk_refit_effi_vs_reco_pt2.SetFillStyle(0)
tgae_reco_ftk_refit_effi_vs_reco_eta1.SetFillStyle(0); tgae_reco_ftk_refit_effi_vs_reco_eta2.SetFillStyle(0)
tgae_reco_ftk_refit_effi_vs_reco_phi1.SetFillStyle(0); tgae_reco_ftk_refit_effi_vs_reco_phi2.SetFillStyle(0)
tgae_reco_ftk_refit_effi_vs_reco_d01.SetFillStyle(0); tgae_reco_ftk_refit_effi_vs_reco_d02.SetFillStyle(0)
tgae_reco_ftk_refit_effi_vs_reco_z01.SetFillStyle(0); tgae_reco_ftk_refit_effi_vs_reco_z02.SetFillStyle(0)


print("Adding histograms to stack")
# h_truth_pt_stack.Add(h_truth_pt1); h_truth_pt_stack.Add(h_truth_pt2)
# h_truth_eta_stack.Add(h_truth_eta1); h_truth_eta_stack.Add(h_truth_eta2)
# h_truth_phi_stack.Add(h_truth_phi1); h_truth_phi_stack.Add(h_truth_phi2)
# h_truth_m_stack.Add(h_truth_m1); h_truth_m_stack.Add(h_truth_m2)
# h_truth_d0_stack.Add(h_truth_d01); h_truth_d0_stack.Add(h_truth_d02)
# h_truth_z0_stack.Add(h_truth_z01); h_truth_z0_stack.Add(h_truth_z02)
# h_truth_qop_stack.Add(h_truth_qop1); h_truth_qop_stack.Add(h_truth_qop2)
# h_truth_charge_stack.Add(h_truth_charge1); h_truth_charge_stack.Add(h_truth_charge2)
# h_reco_accepted_pt1.SetTitle(str(file1_label))
# h_reco_accepted_pt2.SetTitle(str(file2_label))

if isData == False:
	h_truth_pt1.SetTitle(str(file1_label));  h_truth_pt2.SetTitle(str(file2_label))
	h_truth_eta1.SetTitle(str(file1_label));  h_truth_eta2.SetTitle(str(file2_label))
	h_truth_phi1.SetTitle(str(file1_label));  h_truth_phi2.SetTitle(str(file2_label))
	h_truth_m1.SetTitle(str(file1_label));  h_truth_m2.SetTitle(str(file2_label))
	h_truth_d01.SetTitle(str(file1_label));  h_truth_d02.SetTitle(str(file2_label))
	h_truth_z01.SetTitle(str(file1_label));  h_truth_z02.SetTitle(str(file2_label))
	h_truth_qop1.SetTitle(str(file1_label));  h_truth_qop2.SetTitle(str(file2_label))
	h_truth_charge1.SetTitle(str(file1_label));  h_truth_charge2.SetTitle(str(file2_label))

	h_reco_truthMatched_pt_bias1.SetTitle(str(file1_label));  h_reco_truthMatched_pt_bias2.SetTitle(str(file2_label))
	h_reco_truthMatched_eta_bias1.SetTitle(str(file1_label));  h_reco_truthMatched_eta_bias2.SetTitle(str(file2_label))
	h_reco_truthMatched_phi_bias1.SetTitle(str(file1_label));  h_reco_truthMatched_phi_bias2.SetTitle(str(file2_label))
	h_reco_truthMatched_d0_bias1.SetTitle(str(file1_label));  h_reco_truthMatched_d0_bias2.SetTitle(str(file2_label))

	h_truth_recoMatch_track_eta1.SetTitle(str(file1_label));  h_truth_recoMatch_track_eta2.SetTitle(str(file2_label))
	h_truth_recoMatch_track_phi1.SetTitle(str(file1_label));  h_truth_recoMatch_track_phi2.SetTitle(str(file2_label))
	h_reco_truthMatch_track_eta1.SetTitle(str(file1_label));  h_reco_truthMatch_track_eta2.SetTitle(str(file2_label))
	h_reco_truthMatch_track_phi1.SetTitle(str(file1_label));  h_reco_truthMatch_track_phi2.SetTitle(str(file2_label))
	h_truth_recoMatch_track_pt1.SetTitle(str(file1_label));  h_truth_recoMatch_track_pt2.SetTitle(str(file2_label))
	h_truth_recoMatch_track_d01.SetTitle(str(file1_label));  h_truth_recoMatch_track_d02.SetTitle(str(file2_label))
	h_truth_recoMatch_track_z01.SetTitle(str(file1_label));  h_truth_recoMatch_track_z02.SetTitle(str(file2_label))

	h_truth_ftk_Matched_pt_bias1.SetTitle(str(file1_label));  h_truth_ftk_Matched_pt_bias2.SetTitle(str(file2_label))
	h_truth_ftk_Matched_eta_bias1.SetTitle(str(file1_label));  h_truth_ftk_Matched_eta_bias2.SetTitle(str(file2_label))
	h_truth_ftk_Matched_phi_bias1.SetTitle(str(file1_label));  h_truth_ftk_Matched_phi_bias2.SetTitle(str(file2_label))
	h_truth_ftk_Matched_d0_bias1.SetTitle(str(file1_label));  h_truth_ftk_Matched_d0_bias2.SetTitle(str(file2_label))
	h_truth_ftk_Matched_corrected_d0_bias1.SetTitle(str(file1_label));  h_truth_ftk_Matched_corrected_d0_bias2.SetTitle(str(file2_label))

	h_ftk_truthMatch_track_eta1.SetTitle(str(file1_label));  h_ftk_truthMatch_track_eta2.SetTitle(str(file2_label))
	h_ftk_truthMatch_track_phi1.SetTitle(str(file1_label));  h_ftk_truthMatch_track_phi2.SetTitle(str(file2_label))
	h_truth_ftkMatch_track_eta1.SetTitle(str(file1_label));  h_truth_ftkMatch_track_eta2.SetTitle(str(file2_label))
	h_truth_ftkMatch_track_phi1.SetTitle(str(file1_label));  h_truth_ftkMatch_track_phi2.SetTitle(str(file2_label))
	h_ftk_truthMatch_track_pt1.SetTitle(str(file1_label));  h_ftk_truthMatch_track_pt2.SetTitle(str(file2_label))
	h_ftk_truthMatch_track_d01.SetTitle(str(file1_label));  h_ftk_truthMatch_track_d02.SetTitle(str(file2_label))
	h_ftk_truthMatch_track_z01.SetTitle(str(file1_label));  h_ftk_truthMatch_track_z02.SetTitle(str(file2_label))

	h_truth_ftk_refitMatched_pt_bias1.SetTitle(str(file1_label));  h_truth_ftk_refitMatched_pt_bias2.SetTitle(str(file2_label))
	h_truth_ftk_refitMatched_eta_bias1.SetTitle(str(file1_label));  h_truth_ftk_refitMatched_eta_bias2.SetTitle(str(file2_label))
	h_truth_ftk_refitMatched_phi_bias1.SetTitle(str(file1_label));  h_truth_ftk_refitMatched_phi_bias2.SetTitle(str(file2_label))
	h_truth_ftk_refitMatched_d0_bias1.SetTitle(str(file1_label));  h_truth_ftk_refitMatched_d0_bias2.SetTitle(str(file2_label))

	h_ftk_refit_truthMatch_track_eta1.SetTitle(str(file1_label));  h_ftk_refit_truthMatch_track_eta2.SetTitle(str(file2_label))
	h_ftk_refit_truthMatch_track_phi1.SetTitle(str(file1_label));  h_ftk_refit_truthMatch_track_phi2.SetTitle(str(file2_label))
	h_truth_ftkrefitMatch_track_eta1.SetTitle(str(file1_label));  h_truth_ftkrefitMatch_track_eta2.SetTitle(str(file2_label))
	h_truth_ftkrefitMatch_track_phi1.SetTitle(str(file1_label));  h_truth_ftkrefitMatch_track_phi2.SetTitle(str(file2_label))
	h_ftk_refit_truthMatch_track_pt1.SetTitle(str(file1_label));  h_ftk_refit_truthMatch_track_pt2.SetTitle(str(file2_label))
	h_ftk_refit_truthMatch_track_d01.SetTitle(str(file1_label));  h_ftk_refit_truthMatch_track_d02.SetTitle(str(file2_label))
	h_ftk_refit_truthMatch_track_z01.SetTitle(str(file1_label));  h_ftk_refit_truthMatch_track_z02.SetTitle(str(file2_label))

	tgae_truth_reco_effi_vs_truth_pt1.SetTitle(str(file1_label));  tgae_truth_reco_effi_vs_truth_pt2.SetTitle(str(file2_label))
	tgae_truth_reco_effi_vs_truth_eta1.SetTitle(str(file1_label));  tgae_truth_reco_effi_vs_truth_eta2.SetTitle(str(file2_label))
	tgae_truth_reco_effi_vs_truth_phi1.SetTitle(str(file1_label));  tgae_truth_reco_effi_vs_truth_phi2.SetTitle(str(file2_label))
	tgae_truth_reco_effi_vs_truth_d01.SetTitle(str(file1_label));  tgae_truth_reco_effi_vs_truth_d02.SetTitle(str(file2_label))
	tgae_truth_reco_effi_vs_truth_z01.SetTitle(str(file1_label));  tgae_truth_reco_effi_vs_truth_z02.SetTitle(str(file2_label))
	tgae_truth_ftk_effi_vs_truth_pt1.SetTitle(str(file1_label));  tgae_truth_ftk_effi_vs_truth_pt2.SetTitle(str(file2_label))
	tgae_truth_ftk_effi_vs_truth_eta1.SetTitle(str(file1_label));  tgae_truth_ftk_effi_vs_truth_eta2.SetTitle(str(file2_label))
	tgae_truth_ftk_effi_vs_truth_phi1.SetTitle(str(file1_label));  tgae_truth_ftk_effi_vs_truth_phi2.SetTitle(str(file2_label))
	tgae_truth_ftk_effi_vs_truth_d01.SetTitle(str(file1_label));  tgae_truth_ftk_effi_vs_truth_d02.SetTitle(str(file2_label))
	tgae_truth_ftk_effi_vs_truth_z01.SetTitle(str(file1_label));  tgae_truth_ftk_effi_vs_truth_z02.SetTitle(str(file2_label))
	tgae_truth_ftk_refit_effi_vs_truth_pt1.SetTitle(str(file1_label));  tgae_truth_ftk_refit_effi_vs_truth_pt2.SetTitle(str(file2_label))
	tgae_truth_ftk_refit_effi_vs_truth_eta1.SetTitle(str(file1_label));  tgae_truth_ftk_refit_effi_vs_truth_eta2.SetTitle(str(file2_label))
	tgae_truth_ftk_refit_effi_vs_truth_phi1.SetTitle(str(file1_label));  tgae_truth_ftk_refit_effi_vs_truth_phi2.SetTitle(str(file2_label))
	tgae_truth_ftk_refit_effi_vs_truth_d01.SetTitle(str(file1_label));  tgae_truth_ftk_refit_effi_vs_truth_d02.SetTitle(str(file2_label))
	tgae_truth_ftk_refit_effi_vs_truth_z01.SetTitle(str(file1_label));  tgae_truth_ftk_refit_effi_vs_truth_z02.SetTitle(str(file2_label))

h_reco_accepted_pt1.SetTitle(str(file1_label));  h_reco_accepted_pt2.SetTitle(str(file2_label))
h_reco_accepted_eta1.SetTitle(str(file1_label));  h_reco_accepted_eta2.SetTitle(str(file2_label))
h_reco_accepted_phi1.SetTitle(str(file1_label));  h_reco_accepted_phi2.SetTitle(str(file2_label))
# h_reco_accepted_m1.SetTitle(str(file1_label));  h_reco_accepted_m2.SetTitle(str(file2_label))
h_reco_accepted_d01.SetTitle(str(file1_label));  h_reco_accepted_d02.SetTitle(str(file2_label))
h_reco_accepted_z01.SetTitle(str(file1_label));  h_reco_accepted_z02.SetTitle(str(file2_label))
h_reco_accepted_qop1.SetTitle(str(file1_label));  h_reco_accepted_qop2.SetTitle(str(file2_label))
h_reco_accepted_charge1.SetTitle(str(file1_label));  h_reco_accepted_charge2.SetTitle(str(file2_label))
h_reco_accepted_chi21.SetTitle(str(file1_label));  h_reco_accepted_chi22.SetTitle(str(file2_label))

h_reco_inclusive_pt1.SetTitle(str(file1_label));  h_reco_inclusive_pt2.SetTitle(str(file2_label))
h_reco_inclusive_eta1.SetTitle(str(file1_label));  h_reco_inclusive_eta2.SetTitle(str(file2_label))
h_reco_inclusive_phi1.SetTitle(str(file1_label));  h_reco_inclusive_phi2.SetTitle(str(file2_label))
# h_reco_inclusive_m1.SetTitle(str(file1_label));  h_reco_inclusive_m2.SetTitle(str(file2_label))
h_reco_inclusive_d01.SetTitle(str(file1_label));  h_reco_inclusive_d02.SetTitle(str(file2_label))
h_reco_inclusive_z01.SetTitle(str(file1_label));  h_reco_inclusive_z02.SetTitle(str(file2_label))
h_reco_inclusive_qop1.SetTitle(str(file1_label));  h_reco_inclusive_qop2.SetTitle(str(file2_label))
h_reco_inclusive_charge1.SetTitle(str(file1_label));  h_reco_inclusive_charge2.SetTitle(str(file2_label))
h_reco_inclusive_chi21.SetTitle(str(file1_label));  h_reco_inclusive_chi22.SetTitle(str(file2_label))

h_ftk_accepted_pt1.SetTitle(str(file1_label));  h_ftk_accepted_pt2.SetTitle(str(file2_label))
h_ftk_accepted_eta1.SetTitle(str(file1_label));  h_ftk_accepted_eta2.SetTitle(str(file2_label))
h_ftk_accepted_phi1.SetTitle(str(file1_label));  h_ftk_accepted_phi2.SetTitle(str(file2_label))
# h_ftk_accepted_m1.SetTitle(str(file1_label));  h_ftk_accepted_m2.SetTitle(str(file2_label))
h_ftk_accepted_d01.SetTitle(str(file1_label));  h_ftk_accepted_d02.SetTitle(str(file2_label))
h_ftk_accepted_corrected_d01.SetTitle(str(file1_label));  h_ftk_accepted_corrected_d02.SetTitle(str(file2_label))
h_ftk_accepted_z01.SetTitle(str(file1_label));  h_ftk_accepted_z02.SetTitle(str(file2_label))
h_ftk_accepted_qop1.SetTitle(str(file1_label));  h_ftk_accepted_qop2.SetTitle(str(file2_label))
h_ftk_accepted_charge1.SetTitle(str(file1_label));  h_ftk_accepted_charge2.SetTitle(str(file2_label))
h_ftk_accepted_chi21.SetTitle(str(file1_label));  h_ftk_accepted_chi22.SetTitle(str(file2_label))

h_ftk_inclusive_pt1.SetTitle(str(file1_label));  h_ftk_inclusive_pt2.SetTitle(str(file2_label))
h_ftk_inclusive_eta1.SetTitle(str(file1_label));  h_ftk_inclusive_eta2.SetTitle(str(file2_label))
h_ftk_inclusive_phi1.SetTitle(str(file1_label));  h_ftk_inclusive_phi2.SetTitle(str(file2_label))
# h_ftk_inclusive_m1.SetTitle(str(file1_label));  h_ftk_inclusive_m2.SetTitle(str(file2_label))
h_ftk_inclusive_d01.SetTitle(str(file1_label));  h_ftk_inclusive_d02.SetTitle(str(file2_label))
h_ftk_inclusive_corrected_d01.SetTitle(str(file1_label));  h_ftk_inclusive_corrected_d02.SetTitle(str(file2_label))
h_ftk_inclusive_z01.SetTitle(str(file1_label));  h_ftk_inclusive_z02.SetTitle(str(file2_label))
h_ftk_inclusive_qop1.SetTitle(str(file1_label));  h_ftk_inclusive_qop2.SetTitle(str(file2_label))
h_ftk_inclusive_charge1.SetTitle(str(file1_label));  h_ftk_inclusive_charge2.SetTitle(str(file2_label))
h_ftk_inclusive_chi21.SetTitle(str(file1_label));  h_ftk_inclusive_chi22.SetTitle(str(file2_label))

h_ftk_refit_accepted_pt1.SetTitle(str(file1_label));  h_ftk_refit_accepted_pt2.SetTitle(str(file2_label))
h_ftk_refit_accepted_eta1.SetTitle(str(file1_label));  h_ftk_refit_accepted_eta2.SetTitle(str(file2_label))
h_ftk_refit_accepted_phi1.SetTitle(str(file1_label));  h_ftk_refit_accepted_phi2.SetTitle(str(file2_label))
# h_ftk_refit_accepted_m1.SetTitle(str(file1_label));  h_ftk_refit_accepted_m2.SetTitle(str(file2_label))
h_ftk_refit_accepted_d01.SetTitle(str(file1_label));  h_ftk_refit_accepted_d02.SetTitle(str(file2_label))
h_ftk_refit_accepted_z01.SetTitle(str(file1_label));  h_ftk_refit_accepted_z02.SetTitle(str(file2_label))
h_ftk_refit_accepted_qop1.SetTitle(str(file1_label));  h_ftk_refit_accepted_qop2.SetTitle(str(file2_label))
h_ftk_refit_accepted_charge1.SetTitle(str(file1_label));  h_ftk_refit_accepted_charge2.SetTitle(str(file2_label))
h_ftk_refit_accepted_chi21.SetTitle(str(file1_label));  h_ftk_refit_accepted_chi22.SetTitle(str(file2_label))

h_ftk_refit_inclusive_pt1.SetTitle(str(file1_label));  h_ftk_refit_inclusive_pt2.SetTitle(str(file2_label))
h_ftk_refit_inclusive_eta1.SetTitle(str(file1_label));  h_ftk_refit_inclusive_eta2.SetTitle(str(file2_label))
h_ftk_refit_inclusive_phi1.SetTitle(str(file1_label));  h_ftk_refit_inclusive_phi2.SetTitle(str(file2_label))
# h_ftk_refit_inclusive_m1.SetTitle(str(file1_label));  h_ftk_refit_inclusive_m2.SetTitle(str(file2_label))
h_ftk_refit_inclusive_d01.SetTitle(str(file1_label));  h_ftk_refit_inclusive_d02.SetTitle(str(file2_label))
h_ftk_refit_inclusive_z01.SetTitle(str(file1_label));  h_ftk_refit_inclusive_z02.SetTitle(str(file2_label))
h_ftk_refit_inclusive_qop1.SetTitle(str(file1_label));  h_ftk_refit_inclusive_qop2.SetTitle(str(file2_label))
h_ftk_refit_inclusive_charge1.SetTitle(str(file1_label));  h_ftk_refit_inclusive_charge2.SetTitle(str(file2_label))
h_ftk_refit_inclusive_chi21.SetTitle(str(file1_label));  h_ftk_refit_inclusive_chi22.SetTitle(str(file2_label))

h_reco_ftkMatched_pt_bias1.SetTitle(str(file1_label));  h_reco_ftkMatched_pt_bias2.SetTitle(str(file2_label))
h_reco_ftkMatched_eta_bias1.SetTitle(str(file1_label));  h_reco_ftkMatched_eta_bias2.SetTitle(str(file2_label))
h_reco_ftkMatched_phi_bias1.SetTitle(str(file1_label));  h_reco_ftkMatched_phi_bias2.SetTitle(str(file2_label))
h_reco_ftkMatched_d0_bias1.SetTitle(str(file1_label));  h_reco_ftkMatched_d0_bias2.SetTitle(str(file2_label))
h_reco_ftkMatched_corrected_d0_bias1.SetTitle(str(file1_label));  h_reco_ftkMatched_corrected_d0_bias2.SetTitle(str(file2_label))

h_ftk_recoMatch_track_eta1.SetTitle(str(file1_label));  h_ftk_recoMatch_track_eta2.SetTitle(str(file2_label))
h_ftk_recoMatch_track_phi1.SetTitle(str(file1_label));  h_ftk_recoMatch_track_phi2.SetTitle(str(file2_label))
h_reco_ftkMatch_track_eta1.SetTitle(str(file1_label));  h_reco_ftkMatch_track_eta2.SetTitle(str(file2_label))
h_reco_ftkMatch_track_phi1.SetTitle(str(file1_label));  h_reco_ftkMatch_track_phi2.SetTitle(str(file2_label))
h_ftk_recoMatch_track_pt1.SetTitle(str(file1_label));  h_ftk_recoMatch_track_pt2.SetTitle(str(file2_label))
h_ftk_recoMatch_track_d01.SetTitle(str(file1_label));  h_ftk_recoMatch_track_d02.SetTitle(str(file2_label))
# h_ftk_recoMatch_track_corrected_d01.SetTitle(str(file1_label));  h_ftk_recoMatch_track_corrected_d02.SetTitle(str(file2_label))
h_ftk_recoMatch_track_z01.SetTitle(str(file1_label));  h_ftk_recoMatch_track_z02.SetTitle(str(file2_label))

h_reco_ftk_refitMatched_pt_bias1.SetTitle(str(file1_label));  h_reco_ftk_refitMatched_pt_bias2.SetTitle(str(file2_label))
h_reco_ftk_refitMatched_eta_bias1.SetTitle(str(file1_label));  h_reco_ftk_refitMatched_eta_bias2.SetTitle(str(file2_label))
h_reco_ftk_refitMatched_phi_bias1.SetTitle(str(file1_label));  h_reco_ftk_refitMatched_phi_bias2.SetTitle(str(file2_label))
h_reco_ftk_refitMatched_d0_bias1.SetTitle(str(file1_label));  h_reco_ftk_refitMatched_d0_bias2.SetTitle(str(file2_label))

h_ftk_refit_recoMatch_track_eta1.SetTitle(str(file1_label));  h_ftk_refit_recoMatch_track_eta2.SetTitle(str(file2_label))
h_ftk_refit_recoMatch_track_phi1.SetTitle(str(file1_label));  h_ftk_refit_recoMatch_track_phi2.SetTitle(str(file2_label))
h_reco_ftkrefitMatch_track_eta1.SetTitle(str(file1_label));  h_reco_ftkrefitMatch_track_eta2.SetTitle(str(file2_label))
h_reco_ftkrefitMatch_track_phi1.SetTitle(str(file1_label));  h_reco_ftkrefitMatch_track_phi2.SetTitle(str(file2_label))
h_ftk_refit_recoMatch_track_pt1.SetTitle(str(file1_label));  h_ftk_refit_recoMatch_track_pt2.SetTitle(str(file2_label))
h_ftk_refit_recoMatch_track_d01.SetTitle(str(file1_label));  h_ftk_refit_recoMatch_track_d02.SetTitle(str(file2_label))
h_ftk_refit_recoMatch_track_z01.SetTitle(str(file1_label));  h_ftk_refit_recoMatch_track_z02.SetTitle(str(file2_label))

h_reco_accepted_hitPattern_EndCap1.SetTitle(str(file1_label));  h_reco_accepted_hitPattern_EndCap2.SetTitle(str(file2_label))
h_ftk_accepted_hitPattern_EndCap1.SetTitle(str(file1_label));  h_ftk_accepted_hitPattern_EndCap2.SetTitle(str(file2_label))
h_ftk_refit_accepted_hitPattern_EndCap1.SetTitle(str(file1_label));  h_ftk_refit_accepted_hitPattern_EndCap2.SetTitle(str(file2_label))

h_reco_accepted_hitPattern_Barrel1.SetTitle(str(file1_label));  h_reco_accepted_hitPattern_Barrel2.SetTitle(str(file2_label))
h_ftk_accepted_hitPattern_Barrel1.SetTitle(str(file1_label));  h_ftk_accepted_hitPattern_Barrel2.SetTitle(str(file2_label))
h_ftk_refit_accepted_hitPattern_Barrel1.SetTitle(str(file1_label));  h_ftk_refit_accepted_hitPattern_Barrel2.SetTitle(str(file2_label))

h_reco_accepted_hitPattern1.SetTitle(str(file1_label));  h_reco_accepted_hitPattern2.SetTitle(str(file2_label))
h_ftk_accepted_hitPattern1.SetTitle(str(file1_label));  h_ftk_accepted_hitPattern2.SetTitle(str(file2_label))
h_ftk_refit_accepted_hitPattern1.SetTitle(str(file1_label));  h_ftk_refit_accepted_hitPattern2.SetTitle(str(file2_label))

tgae_reco_ftk_effi_vs_reco_pt1.SetTitle(str(file1_label));  tgae_reco_ftk_effi_vs_reco_pt2.SetTitle(str(file2_label))
tgae_reco_ftk_effi_vs_reco_eta1.SetTitle(str(file1_label));  tgae_reco_ftk_effi_vs_reco_eta2.SetTitle(str(file2_label))
tgae_reco_ftk_effi_vs_reco_phi1.SetTitle(str(file1_label));  tgae_reco_ftk_effi_vs_reco_phi2.SetTitle(str(file2_label))
tgae_reco_ftk_effi_vs_reco_d01.SetTitle(str(file1_label));  tgae_reco_ftk_effi_vs_reco_d02.SetTitle(str(file2_label))
tgae_reco_ftk_effi_vs_reco_z01.SetTitle(str(file1_label));  tgae_reco_ftk_effi_vs_reco_z02.SetTitle(str(file2_label))

tgae_reco_ftk_refit_effi_vs_reco_pt1.SetTitle(str(file1_label));  tgae_reco_ftk_refit_effi_vs_reco_pt2.SetTitle(str(file2_label))
tgae_reco_ftk_refit_effi_vs_reco_eta1.SetTitle(str(file1_label));  tgae_reco_ftk_refit_effi_vs_reco_eta2.SetTitle(str(file2_label))
tgae_reco_ftk_refit_effi_vs_reco_phi1.SetTitle(str(file1_label));  tgae_reco_ftk_refit_effi_vs_reco_phi2.SetTitle(str(file2_label))
tgae_reco_ftk_refit_effi_vs_reco_d01.SetTitle(str(file1_label));  tgae_reco_ftk_refit_effi_vs_reco_d02.SetTitle(str(file2_label))
tgae_reco_ftk_refit_effi_vs_reco_z01.SetTitle(str(file1_label));  tgae_reco_ftk_refit_effi_vs_reco_z02.SetTitle(str(file2_label))

h_reco_accepted_pt_stack.Add(h_reco_accepted_pt1); h_reco_accepted_pt_stack.Add(h_reco_accepted_pt2)
h_reco_accepted_eta_stack.Add(h_reco_accepted_eta1); h_reco_accepted_eta_stack.Add(h_reco_accepted_eta2)
h_reco_accepted_phi_stack.Add(h_reco_accepted_phi1); h_reco_accepted_phi_stack.Add(h_reco_accepted_phi2)
# h_reco_accepted_m_stack.Add(h_reco_accepted_m1); h_reco_accepted_m_stack.Add(h_reco_accepted_m2)
h_reco_accepted_d0_stack.Add(h_reco_accepted_d01); h_reco_accepted_d0_stack.Add(h_reco_accepted_d02)
h_reco_accepted_z0_stack.Add(h_reco_accepted_z01); h_reco_accepted_z0_stack.Add(h_reco_accepted_z02)
h_reco_accepted_qop_stack.Add(h_reco_accepted_qop1); h_reco_accepted_qop_stack.Add(h_reco_accepted_qop2)
h_reco_accepted_charge_stack.Add(h_reco_accepted_charge1); h_reco_accepted_charge_stack.Add(h_reco_accepted_charge2)
h_reco_accepted_chi2_stack.Add(h_reco_accepted_chi21); h_reco_accepted_chi2_stack.Add(h_reco_accepted_chi22)

h_reco_inclusive_pt_stack.Add(h_reco_inclusive_pt1); h_reco_inclusive_pt_stack.Add(h_reco_inclusive_pt2)
h_reco_inclusive_eta_stack.Add(h_reco_inclusive_eta1); h_reco_inclusive_eta_stack.Add(h_reco_inclusive_eta2)
h_reco_inclusive_phi_stack.Add(h_reco_inclusive_phi1); h_reco_inclusive_phi_stack.Add(h_reco_inclusive_phi2)
# h_reco_inclusive_m_stack.Add(h_reco_inclusive_m1); h_reco_inclusive_m_stack.Add(h_reco_inclusive_m2)
h_reco_inclusive_d0_stack.Add(h_reco_inclusive_d01); h_reco_inclusive_d0_stack.Add(h_reco_inclusive_d02)
h_reco_inclusive_z0_stack.Add(h_reco_inclusive_z01); h_reco_inclusive_z0_stack.Add(h_reco_inclusive_z02)
h_reco_inclusive_qop_stack.Add(h_reco_inclusive_qop1); h_reco_inclusive_qop_stack.Add(h_reco_inclusive_qop2)
h_reco_inclusive_charge_stack.Add(h_reco_inclusive_charge1); h_reco_inclusive_charge_stack.Add(h_reco_inclusive_charge2)
h_reco_inclusive_chi2_stack.Add(h_reco_inclusive_chi21); h_reco_inclusive_chi2_stack.Add(h_reco_inclusive_chi22)

h_ftk_accepted_pt_stack.Add(h_ftk_accepted_pt1); h_ftk_accepted_pt_stack.Add(h_ftk_accepted_pt2)
h_ftk_accepted_eta_stack.Add(h_ftk_accepted_eta1); h_ftk_accepted_eta_stack.Add(h_ftk_accepted_eta2)
h_ftk_accepted_phi_stack.Add(h_ftk_accepted_phi1); h_ftk_accepted_phi_stack.Add(h_ftk_accepted_phi2)
# h_ftk_accepted_m_stack.Add(h_ftk_accepted_m1); h_ftk_accepted_m_stack.Add(h_ftk_accepted_m2)
h_ftk_accepted_d0_stack.Add(h_ftk_accepted_d01); h_ftk_accepted_d0_stack.Add(h_ftk_accepted_d02)
h_ftk_accepted_corrected_d0_stack.Add(h_ftk_accepted_corrected_d01); h_ftk_accepted_corrected_d0_stack.Add(h_ftk_accepted_corrected_d02)
h_ftk_accepted_z0_stack.Add(h_ftk_accepted_z01); h_ftk_accepted_z0_stack.Add(h_ftk_accepted_z02)
h_ftk_accepted_qop_stack.Add(h_ftk_accepted_qop1); h_ftk_accepted_qop_stack.Add(h_ftk_accepted_qop2)
h_ftk_accepted_charge_stack.Add(h_ftk_accepted_charge1); h_ftk_accepted_charge_stack.Add(h_ftk_accepted_charge2)
h_ftk_accepted_chi2_stack.Add(h_ftk_accepted_chi21); h_ftk_accepted_chi2_stack.Add(h_ftk_accepted_chi22)

h_ftk_inclusive_pt_stack.Add(h_ftk_inclusive_pt1); h_ftk_inclusive_pt_stack.Add(h_ftk_inclusive_pt2)
h_ftk_inclusive_eta_stack.Add(h_ftk_inclusive_eta1); h_ftk_inclusive_eta_stack.Add(h_ftk_inclusive_eta2)
h_ftk_inclusive_phi_stack.Add(h_ftk_inclusive_phi1); h_ftk_inclusive_phi_stack.Add(h_ftk_inclusive_phi2)
# h_ftk_inclusive_m_stack.Add(h_ftk_inclusive_m1); h_ftk_inclusive_m_stack.Add(h_ftk_inclusive_m2)
h_ftk_inclusive_d0_stack.Add(h_ftk_inclusive_d01); h_ftk_inclusive_d0_stack.Add(h_ftk_inclusive_d02)
h_ftk_inclusive_corrected_d0_stack.Add(h_ftk_inclusive_corrected_d01); h_ftk_inclusive_corrected_d0_stack.Add(h_ftk_inclusive_corrected_d02)
h_ftk_inclusive_z0_stack.Add(h_ftk_inclusive_z01); h_ftk_inclusive_z0_stack.Add(h_ftk_inclusive_z02)
h_ftk_inclusive_qop_stack.Add(h_ftk_inclusive_qop1); h_ftk_inclusive_qop_stack.Add(h_ftk_inclusive_qop2)
h_ftk_inclusive_charge_stack.Add(h_ftk_inclusive_charge1); h_ftk_inclusive_charge_stack.Add(h_ftk_inclusive_charge2)
h_ftk_inclusive_chi2_stack.Add(h_ftk_inclusive_chi21); h_ftk_inclusive_chi2_stack.Add(h_ftk_inclusive_chi22)

h_ftk_refit_accepted_pt_stack.Add(h_ftk_refit_accepted_pt1); h_ftk_refit_accepted_pt_stack.Add(h_ftk_refit_accepted_pt2)
h_ftk_refit_accepted_eta_stack.Add(h_ftk_refit_accepted_eta1); h_ftk_refit_accepted_eta_stack.Add(h_ftk_refit_accepted_eta2)
h_ftk_refit_accepted_phi_stack.Add(h_ftk_refit_accepted_phi1); h_ftk_refit_accepted_phi_stack.Add(h_ftk_refit_accepted_phi2)
# h_ftk_refit_accepted_m_stack.Add(h_ftk_refit_accepted_m1); h_ftk_refit_accepted_m_stack.Add(h_ftk_refit_accepted_m2)
h_ftk_refit_accepted_d0_stack.Add(h_ftk_refit_accepted_d01); h_ftk_refit_accepted_d0_stack.Add(h_ftk_refit_accepted_d02)
h_ftk_refit_accepted_z0_stack.Add(h_ftk_refit_accepted_z01); h_ftk_refit_accepted_z0_stack.Add(h_ftk_refit_accepted_z02)
h_ftk_refit_accepted_qop_stack.Add(h_ftk_refit_accepted_qop1); h_ftk_refit_accepted_qop_stack.Add(h_ftk_refit_accepted_qop2)
h_ftk_refit_accepted_charge_stack.Add(h_ftk_refit_accepted_charge1); h_ftk_refit_accepted_charge_stack.Add(h_ftk_refit_accepted_charge2)
h_ftk_refit_accepted_chi2_stack.Add(h_ftk_refit_accepted_chi21); h_ftk_refit_accepted_chi2_stack.Add(h_ftk_refit_accepted_chi22)

h_ftk_refit_inclusive_pt_stack.Add(h_ftk_refit_inclusive_pt1); h_ftk_refit_inclusive_pt_stack.Add(h_ftk_refit_inclusive_pt2)
h_ftk_refit_inclusive_eta_stack.Add(h_ftk_refit_inclusive_eta1); h_ftk_refit_inclusive_eta_stack.Add(h_ftk_refit_inclusive_eta2)
h_ftk_refit_inclusive_phi_stack.Add(h_ftk_refit_inclusive_phi1); h_ftk_refit_inclusive_phi_stack.Add(h_ftk_refit_inclusive_phi2)
# h_ftk_refit_inclusive_m_stack.Add(h_ftk_refit_inclusive_m1); h_ftk_refit_inclusive_m_stack.Add(h_ftk_refit_inclusive_m2)
h_ftk_refit_inclusive_d0_stack.Add(h_ftk_refit_inclusive_d01); h_ftk_refit_inclusive_d0_stack.Add(h_ftk_refit_inclusive_d02)
h_ftk_refit_inclusive_z0_stack.Add(h_ftk_refit_inclusive_z01); h_ftk_refit_inclusive_z0_stack.Add(h_ftk_refit_inclusive_z02)
h_ftk_refit_inclusive_qop_stack.Add(h_ftk_refit_inclusive_qop1); h_ftk_refit_inclusive_qop_stack.Add(h_ftk_refit_inclusive_qop2)
h_ftk_refit_inclusive_charge_stack.Add(h_ftk_refit_inclusive_charge1); h_ftk_refit_inclusive_charge_stack.Add(h_ftk_refit_inclusive_charge2)
h_ftk_refit_inclusive_chi2_stack.Add(h_ftk_refit_inclusive_chi21); h_ftk_refit_inclusive_chi2_stack.Add(h_ftk_refit_inclusive_chi22)

if isData == False:
	h_reco_truthMatched_pt_bias_stack.Add(h_reco_truthMatched_pt_bias1); h_reco_truthMatched_pt_bias_stack.Add(h_reco_truthMatched_pt_bias2)
	h_reco_truthMatched_eta_bias_stack.Add(h_reco_truthMatched_eta_bias1); h_reco_truthMatched_eta_bias_stack.Add(h_reco_truthMatched_eta_bias2)
	h_reco_truthMatched_phi_bias_stack.Add(h_reco_truthMatched_phi_bias1); h_reco_truthMatched_phi_bias_stack.Add(h_reco_truthMatched_phi_bias2)
	h_reco_truthMatched_d0_bias_stack.Add(h_reco_truthMatched_d0_bias1); h_reco_truthMatched_d0_bias_stack.Add(h_reco_truthMatched_d0_bias2)

	h_truth_recoMatch_track_eta_stack.Add(h_truth_recoMatch_track_eta1); h_truth_recoMatch_track_eta_stack.Add(h_truth_recoMatch_track_eta2)
	h_truth_recoMatch_track_phi_stack.Add(h_truth_recoMatch_track_phi1); h_truth_recoMatch_track_phi_stack.Add(h_truth_recoMatch_track_phi2)
	h_reco_truthMatch_track_eta_stack.Add(h_reco_truthMatch_track_eta1); h_reco_truthMatch_track_eta_stack.Add(h_reco_truthMatch_track_eta2)
	h_reco_truthMatch_track_phi_stack.Add(h_reco_truthMatch_track_phi1); h_reco_truthMatch_track_phi_stack.Add(h_reco_truthMatch_track_phi2)
	h_truth_recoMatch_track_pt_stack.Add(h_truth_recoMatch_track_pt1); h_truth_recoMatch_track_pt_stack.Add(h_truth_recoMatch_track_pt2)
	h_truth_recoMatch_track_d0_stack.Add(h_truth_recoMatch_track_d01); h_truth_recoMatch_track_d0_stack.Add(h_truth_recoMatch_track_d02)
	h_truth_recoMatch_track_z0_stack.Add(h_truth_recoMatch_track_z01); h_truth_recoMatch_track_z0_stack.Add(h_truth_recoMatch_track_z02)

	h_truth_ftk_Matched_pt_bias_stack.Add(h_truth_ftk_Matched_pt_bias1); h_truth_ftk_Matched_pt_bias_stack.Add(h_truth_ftk_Matched_pt_bias2)
	h_truth_ftk_Matched_eta_bias_stack.Add(h_truth_ftk_Matched_eta_bias1); h_truth_ftk_Matched_eta_bias_stack.Add(h_truth_ftk_Matched_eta_bias2)
	h_truth_ftk_Matched_phi_bias_stack.Add(h_truth_ftk_Matched_phi_bias1); h_truth_ftk_Matched_phi_bias_stack.Add(h_truth_ftk_Matched_phi_bias2)
	h_truth_ftk_Matched_d0_bias_stack.Add(h_truth_ftk_Matched_d0_bias1); h_truth_ftk_Matched_d0_bias_stack.Add(h_truth_ftk_Matched_d0_bias2)
	h_truth_ftk_Matched_corrected_d0_bias_stack.Add(h_truth_ftk_Matched_corrected_d0_bias1); h_truth_ftk_Matched_corrected_d0_bias_stack.Add(h_truth_ftk_Matched_corrected_d0_bias2)

	h_ftk_truthMatch_track_eta_stack.Add(h_ftk_truthMatch_track_eta1); h_ftk_truthMatch_track_eta_stack.Add(h_ftk_truthMatch_track_eta2)
	h_ftk_truthMatch_track_phi_stack.Add(h_ftk_truthMatch_track_phi1); h_ftk_truthMatch_track_phi_stack.Add(h_ftk_truthMatch_track_phi2)
	h_truth_ftkMatch_track_eta_stack.Add(h_truth_ftkMatch_track_eta1); h_truth_ftkMatch_track_eta_stack.Add(h_truth_ftkMatch_track_eta2)
	h_truth_ftkMatch_track_phi_stack.Add(h_truth_ftkMatch_track_phi1); h_truth_ftkMatch_track_phi_stack.Add(h_truth_ftkMatch_track_phi2)
	h_ftk_truthMatch_track_pt_stack.Add(h_ftk_truthMatch_track_pt1); h_ftk_truthMatch_track_pt_stack.Add(h_ftk_truthMatch_track_pt2)
	h_ftk_truthMatch_track_d0_stack.Add(h_ftk_truthMatch_track_d01); h_ftk_truthMatch_track_d0_stack.Add(h_ftk_truthMatch_track_d02)
	h_ftk_truthMatch_track_z0_stack.Add(h_ftk_truthMatch_track_z01); h_ftk_truthMatch_track_z0_stack.Add(h_ftk_truthMatch_track_z02)

	h_truth_ftk_refitMatched_pt_bias_stack.Add(h_truth_ftk_refitMatched_pt_bias1); h_truth_ftk_refitMatched_pt_bias_stack.Add(h_truth_ftk_refitMatched_pt_bias2)
	h_truth_ftk_refitMatched_eta_bias_stack.Add(h_truth_ftk_refitMatched_eta_bias1); h_truth_ftk_refitMatched_eta_bias_stack.Add(h_truth_ftk_refitMatched_eta_bias2)
	h_truth_ftk_refitMatched_phi_bias_stack.Add(h_truth_ftk_refitMatched_phi_bias1); h_truth_ftk_refitMatched_phi_bias_stack.Add(h_truth_ftk_refitMatched_phi_bias2)
	h_truth_ftk_refitMatched_d0_bias_stack.Add(h_truth_ftk_refitMatched_d0_bias1); h_truth_ftk_refitMatched_d0_bias_stack.Add(h_truth_ftk_refitMatched_d0_bias2)

	h_ftk_refit_truthMatch_track_eta_stack.Add(h_ftk_refit_truthMatch_track_eta1); h_ftk_refit_truthMatch_track_eta_stack.Add(h_ftk_refit_truthMatch_track_eta2)
	h_ftk_refit_truthMatch_track_phi_stack.Add(h_ftk_refit_truthMatch_track_phi1); h_ftk_refit_truthMatch_track_phi_stack.Add(h_ftk_refit_truthMatch_track_phi2)
	h_truth_ftkrefitMatch_track_eta_stack.Add(h_truth_ftkrefitMatch_track_eta1); h_truth_ftkrefitMatch_track_eta_stack.Add(h_truth_ftkrefitMatch_track_eta2)
	h_truth_ftkrefitMatch_track_phi_stack.Add(h_truth_ftkrefitMatch_track_phi1); h_truth_ftkrefitMatch_track_phi_stack.Add(h_truth_ftkrefitMatch_track_phi2)
	h_ftk_refit_truthMatch_track_pt_stack.Add(h_ftk_refit_truthMatch_track_pt1); h_ftk_refit_truthMatch_track_pt_stack.Add(h_ftk_refit_truthMatch_track_pt2)
	h_ftk_refit_truthMatch_track_d0_stack.Add(h_ftk_refit_truthMatch_track_d01); h_ftk_refit_truthMatch_track_d0_stack.Add(h_ftk_refit_truthMatch_track_d02)
	h_ftk_refit_truthMatch_track_z0_stack.Add(h_ftk_refit_truthMatch_track_z01); h_ftk_refit_truthMatch_track_z0_stack.Add(h_ftk_refit_truthMatch_track_z02)

h_reco_ftkMatched_pt_bias_stack.Add(h_reco_ftkMatched_pt_bias1); h_reco_ftkMatched_pt_bias_stack.Add(h_reco_ftkMatched_pt_bias2)
h_reco_ftkMatched_eta_bias_stack.Add(h_reco_ftkMatched_eta_bias1); h_reco_ftkMatched_eta_bias_stack.Add(h_reco_ftkMatched_eta_bias2)
h_reco_ftkMatched_phi_bias_stack.Add(h_reco_ftkMatched_phi_bias1); h_reco_ftkMatched_phi_bias_stack.Add(h_reco_ftkMatched_phi_bias2)
h_reco_ftkMatched_d0_bias_stack.Add(h_reco_ftkMatched_d0_bias1); h_reco_ftkMatched_d0_bias_stack.Add(h_reco_ftkMatched_d0_bias2)
h_reco_ftkMatched_corrected_d0_bias_stack.Add(h_reco_ftkMatched_corrected_d0_bias1); h_reco_ftkMatched_corrected_d0_bias_stack.Add(h_reco_ftkMatched_corrected_d0_bias2)

h_ftk_recoMatch_track_eta_stack.Add(h_ftk_recoMatch_track_eta1); h_ftk_recoMatch_track_eta_stack.Add(h_ftk_recoMatch_track_eta2)
h_ftk_recoMatch_track_phi_stack.Add(h_ftk_recoMatch_track_phi1); h_ftk_recoMatch_track_phi_stack.Add(h_ftk_recoMatch_track_phi2)
h_reco_ftkMatch_track_eta_stack.Add(h_reco_ftkMatch_track_eta1); h_reco_ftkMatch_track_eta_stack.Add(h_reco_ftkMatch_track_eta2)
h_reco_ftkMatch_track_phi_stack.Add(h_reco_ftkMatch_track_phi1); h_reco_ftkMatch_track_phi_stack.Add(h_reco_ftkMatch_track_phi2)
h_ftk_recoMatch_track_pt_stack.Add(h_ftk_recoMatch_track_pt1); h_ftk_recoMatch_track_pt_stack.Add(h_ftk_recoMatch_track_pt2)
h_ftk_recoMatch_track_d0_stack.Add(h_ftk_recoMatch_track_d01); h_ftk_recoMatch_track_d0_stack.Add(h_ftk_recoMatch_track_d02)
# h_ftk_recoMatch_track_corrected_d0_stack.Add(h_ftk_recoMatch_track_corrected_d01); h_ftk_recoMatch_track_corrected_d0_stack.Add(h_ftk_recoMatch_track_corrected_d02)
h_ftk_recoMatch_track_z0_stack.Add(h_ftk_recoMatch_track_z01); h_ftk_recoMatch_track_z0_stack.Add(h_ftk_recoMatch_track_z02)

h_reco_ftk_refitMatched_pt_bias_stack.Add(h_reco_ftk_refitMatched_pt_bias1); h_reco_ftk_refitMatched_pt_bias_stack.Add(h_reco_ftk_refitMatched_pt_bias2)
h_reco_ftk_refitMatched_eta_bias_stack.Add(h_reco_ftk_refitMatched_eta_bias1); h_reco_ftk_refitMatched_eta_bias_stack.Add(h_reco_ftk_refitMatched_eta_bias2)
h_reco_ftk_refitMatched_phi_bias_stack.Add(h_reco_ftk_refitMatched_phi_bias1); h_reco_ftk_refitMatched_phi_bias_stack.Add(h_reco_ftk_refitMatched_phi_bias2)
h_reco_ftk_refitMatched_d0_bias_stack.Add(h_reco_ftk_refitMatched_d0_bias1); h_reco_ftk_refitMatched_d0_bias_stack.Add(h_reco_ftk_refitMatched_d0_bias2)

h_ftk_refit_recoMatch_track_eta_stack.Add(h_ftk_refit_recoMatch_track_eta1); h_ftk_refit_recoMatch_track_eta_stack.Add(h_ftk_refit_recoMatch_track_eta2)
h_ftk_refit_recoMatch_track_phi_stack.Add(h_ftk_refit_recoMatch_track_phi1); h_ftk_refit_recoMatch_track_phi_stack.Add(h_ftk_refit_recoMatch_track_phi2)
h_reco_ftkrefitMatch_track_eta_stack.Add(h_reco_ftkrefitMatch_track_eta1); h_reco_ftkrefitMatch_track_eta_stack.Add(h_reco_ftkrefitMatch_track_eta2)
h_reco_ftkrefitMatch_track_phi_stack.Add(h_reco_ftkrefitMatch_track_phi1); h_reco_ftkrefitMatch_track_phi_stack.Add(h_reco_ftkrefitMatch_track_phi2)
h_ftk_refit_recoMatch_track_pt_stack.Add(h_ftk_refit_recoMatch_track_pt1); h_ftk_refit_recoMatch_track_pt_stack.Add(h_ftk_refit_recoMatch_track_pt2)
h_ftk_refit_recoMatch_track_d0_stack.Add(h_ftk_refit_recoMatch_track_d01); h_ftk_refit_recoMatch_track_d0_stack.Add(h_ftk_refit_recoMatch_track_d02)
h_ftk_refit_recoMatch_track_z0_stack.Add(h_ftk_refit_recoMatch_track_z01); h_ftk_refit_recoMatch_track_z0_stack.Add(h_ftk_refit_recoMatch_track_z02)

h_reco_accepted_hitPattern_EndCap_stack.Add(h_reco_accepted_hitPattern_EndCap1); h_reco_accepted_hitPattern_EndCap_stack.Add(h_reco_accepted_hitPattern_EndCap2)
h_ftk_accepted_hitPattern_EndCap_stack.Add(h_ftk_accepted_hitPattern_EndCap1); h_ftk_accepted_hitPattern_EndCap_stack.Add(h_ftk_accepted_hitPattern_EndCap2)
h_ftk_refit_accepted_hitPattern_EndCap_stack.Add(h_ftk_refit_accepted_hitPattern_EndCap1); h_ftk_refit_accepted_hitPattern_EndCap_stack.Add(h_ftk_refit_accepted_hitPattern_EndCap2)

h_reco_accepted_hitPattern_Barrel_stack.Add(h_reco_accepted_hitPattern_Barrel1); h_reco_accepted_hitPattern_Barrel_stack.Add(h_reco_accepted_hitPattern_Barrel2)
h_ftk_accepted_hitPattern_Barrel_stack.Add(h_ftk_accepted_hitPattern_Barrel1); h_ftk_accepted_hitPattern_Barrel_stack.Add(h_ftk_accepted_hitPattern_Barrel2)
h_ftk_refit_accepted_hitPattern_Barrel_stack.Add(h_ftk_refit_accepted_hitPattern_Barrel1); h_ftk_refit_accepted_hitPattern_Barrel_stack.Add(h_ftk_refit_accepted_hitPattern_Barrel2)

h_reco_accepted_hitPattern_stack.Add(h_reco_accepted_hitPattern1); h_reco_accepted_hitPattern_stack.Add(h_reco_accepted_hitPattern2)
h_ftk_accepted_hitPattern_stack.Add(h_ftk_accepted_hitPattern1); h_ftk_accepted_hitPattern_stack.Add(h_ftk_accepted_hitPattern2)
h_ftk_refit_accepted_hitPattern_stack.Add(h_ftk_refit_accepted_hitPattern1); h_ftk_refit_accepted_hitPattern_stack.Add(h_ftk_refit_accepted_hitPattern2)

if isData == False:
	tgae_truth_reco_effi_vs_truth_pt_stack.SetTitle(";Truth pT [GeV];Efficiency w.r.t. Truth");
	tgae_truth_reco_effi_vs_truth_eta_stack.SetTitle(";Truth phi;Efficiency w.r.t. Truth");
	tgae_truth_reco_effi_vs_truth_phi_stack.SetTitle(";Truth eta;Efficiency w.r.t. Truth");
	tgae_truth_reco_effi_vs_truth_d0_stack.SetTitle(";Truth d0 [mm];Efficiency w.r.t. Truth");
	tgae_truth_reco_effi_vs_truth_z0_stack.SetTitle(";Truth z0 [mm];Efficiency w.r.t. Truth");

	tgae_truth_ftk_effi_vs_truth_pt_stack.SetTitle(";Truth pT [GeV];Efficiency w.r.t. Truth");
	tgae_truth_ftk_effi_vs_truth_eta_stack.SetTitle(";Truth phi;Efficiency w.r.t. Truth");
	tgae_truth_ftk_effi_vs_truth_phi_stack.SetTitle(";Truth eta;Efficiency w.r.t. Truth");
	tgae_truth_ftk_effi_vs_truth_d0_stack.SetTitle(";Truth d0 [mm];Efficiency w.r.t. Truth");
	tgae_truth_ftk_effi_vs_truth_z0_stack.SetTitle(";Truth z0 [mm];Efficiency w.r.t. Truth");

	tgae_truth_ftk_refit_effi_vs_truth_pt_stack.SetTitle(";Truth pT [GeV];Efficiency w.r.t. Truth");
	tgae_truth_ftk_refit_effi_vs_truth_eta_stack.SetTitle(";Truth phi;Efficiency w.r.t. Truth");
	tgae_truth_ftk_refit_effi_vs_truth_phi_stack.SetTitle(";Truth eta;Efficiency w.r.t. Truth");
	tgae_truth_ftk_refit_effi_vs_truth_d0_stack.SetTitle(";Truth d0 [mm];Efficiency w.r.t. Truth");
	tgae_truth_ftk_refit_effi_vs_truth_z0_stack.SetTitle(";Truth z0 [mm];Efficiency w.r.t. Truth");

tgae_reco_ftk_effi_vs_reco_pt_stack.SetTitle(";Reco pT [GeV];Efficiency w.r.t. Reco");
tgae_reco_ftk_effi_vs_reco_eta_stack.SetTitle(";Reco phi;Efficiency w.r.t. Reco");
tgae_reco_ftk_effi_vs_reco_phi_stack.SetTitle(";Reco eta;Efficiency w.r.t. Reco");
tgae_reco_ftk_effi_vs_reco_d0_stack.SetTitle(";Reco d0 [mm];Efficiency w.r.t. Reco");
tgae_reco_ftk_effi_vs_reco_z0_stack.SetTitle(";Reco z0 [mm];Efficiency w.r.t. Reco");

tgae_reco_ftk_refit_effi_vs_reco_pt_stack.SetTitle(";Reco pT [GeV];Efficiency w.r.t. Reco");
tgae_reco_ftk_refit_effi_vs_reco_eta_stack.SetTitle(";Reco phi;Efficiency w.r.t. Reco");
tgae_reco_ftk_refit_effi_vs_reco_phi_stack.SetTitle(";Reco eta;Efficiency w.r.t. Reco");
tgae_reco_ftk_refit_effi_vs_reco_d0_stack.SetTitle(";Reco d0 [mm];Efficiency w.r.t. Reco");
tgae_reco_ftk_refit_effi_vs_reco_z0_stack.SetTitle(";Reco z0 [mm];Efficiency w.r.t. Reco");

if isData == False:
	tgae_truth_reco_effi_vs_truth_pt_stack.Add(tgae_truth_reco_effi_vs_truth_pt1); tgae_truth_reco_effi_vs_truth_pt_stack.Add(tgae_truth_reco_effi_vs_truth_pt2)
	tgae_truth_reco_effi_vs_truth_eta_stack.Add(tgae_truth_reco_effi_vs_truth_eta1); tgae_truth_reco_effi_vs_truth_eta_stack.Add(tgae_truth_reco_effi_vs_truth_eta2)
	tgae_truth_reco_effi_vs_truth_phi_stack.Add(tgae_truth_reco_effi_vs_truth_phi1); tgae_truth_reco_effi_vs_truth_phi_stack.Add(tgae_truth_reco_effi_vs_truth_phi2)
	tgae_truth_reco_effi_vs_truth_d0_stack.Add(tgae_truth_reco_effi_vs_truth_d01); tgae_truth_reco_effi_vs_truth_d0_stack.Add(tgae_truth_reco_effi_vs_truth_d02)
	tgae_truth_reco_effi_vs_truth_z0_stack.Add(tgae_truth_reco_effi_vs_truth_z01); tgae_truth_reco_effi_vs_truth_z0_stack.Add(tgae_truth_reco_effi_vs_truth_z02)

	tgae_truth_ftk_effi_vs_truth_pt_stack.Add(tgae_truth_ftk_effi_vs_truth_pt1); tgae_truth_ftk_effi_vs_truth_pt_stack.Add(tgae_truth_ftk_effi_vs_truth_pt2)
	tgae_truth_ftk_effi_vs_truth_eta_stack.Add(tgae_truth_ftk_effi_vs_truth_eta1); tgae_truth_ftk_effi_vs_truth_eta_stack.Add(tgae_truth_ftk_effi_vs_truth_eta2)
	tgae_truth_ftk_effi_vs_truth_phi_stack.Add(tgae_truth_ftk_effi_vs_truth_phi1); tgae_truth_ftk_effi_vs_truth_phi_stack.Add(tgae_truth_ftk_effi_vs_truth_phi2)
	tgae_truth_ftk_effi_vs_truth_d0_stack.Add(tgae_truth_ftk_effi_vs_truth_d01); tgae_truth_ftk_effi_vs_truth_d0_stack.Add(tgae_truth_ftk_effi_vs_truth_d02)
	tgae_truth_ftk_effi_vs_truth_z0_stack.Add(tgae_truth_ftk_effi_vs_truth_z01); tgae_truth_ftk_effi_vs_truth_z0_stack.Add(tgae_truth_ftk_effi_vs_truth_z02)

	tgae_truth_ftk_refit_effi_vs_truth_pt_stack.Add(tgae_truth_ftk_refit_effi_vs_truth_pt1); tgae_truth_ftk_refit_effi_vs_truth_pt_stack.Add(tgae_truth_ftk_refit_effi_vs_truth_pt2)
	tgae_truth_ftk_refit_effi_vs_truth_eta_stack.Add(tgae_truth_ftk_refit_effi_vs_truth_eta1); tgae_truth_ftk_refit_effi_vs_truth_eta_stack.Add(tgae_truth_ftk_refit_effi_vs_truth_eta2)
	tgae_truth_ftk_refit_effi_vs_truth_phi_stack.Add(tgae_truth_ftk_refit_effi_vs_truth_phi1); tgae_truth_ftk_refit_effi_vs_truth_phi_stack.Add(tgae_truth_ftk_refit_effi_vs_truth_phi2)
	tgae_truth_ftk_refit_effi_vs_truth_d0_stack.Add(tgae_truth_ftk_refit_effi_vs_truth_d01); tgae_truth_ftk_refit_effi_vs_truth_d0_stack.Add(tgae_truth_ftk_refit_effi_vs_truth_d02)
	tgae_truth_ftk_refit_effi_vs_truth_z0_stack.Add(tgae_truth_ftk_refit_effi_vs_truth_z01); tgae_truth_ftk_refit_effi_vs_truth_z0_stack.Add(tgae_truth_ftk_refit_effi_vs_truth_z02)

tgae_reco_ftk_effi_vs_reco_pt_stack.Add(tgae_reco_ftk_effi_vs_reco_pt1); tgae_reco_ftk_effi_vs_reco_pt_stack.Add(tgae_reco_ftk_effi_vs_reco_pt2)
tgae_reco_ftk_effi_vs_reco_eta_stack.Add(tgae_reco_ftk_effi_vs_reco_eta1); tgae_reco_ftk_effi_vs_reco_eta_stack.Add(tgae_reco_ftk_effi_vs_reco_eta2)
tgae_reco_ftk_effi_vs_reco_phi_stack.Add(tgae_reco_ftk_effi_vs_reco_phi1); tgae_reco_ftk_effi_vs_reco_phi_stack.Add(tgae_reco_ftk_effi_vs_reco_phi2)
tgae_reco_ftk_effi_vs_reco_d0_stack.Add(tgae_reco_ftk_effi_vs_reco_d01); tgae_reco_ftk_effi_vs_reco_d0_stack.Add(tgae_reco_ftk_effi_vs_reco_d02)
tgae_reco_ftk_effi_vs_reco_z0_stack.Add(tgae_reco_ftk_effi_vs_reco_z01); tgae_reco_ftk_effi_vs_reco_z0_stack.Add(tgae_reco_ftk_effi_vs_reco_z02)

tgae_reco_ftk_refit_effi_vs_reco_pt_stack.Add(tgae_reco_ftk_refit_effi_vs_reco_pt1); tgae_reco_ftk_refit_effi_vs_reco_pt_stack.Add(tgae_reco_ftk_refit_effi_vs_reco_pt2)
tgae_reco_ftk_refit_effi_vs_reco_eta_stack.Add(tgae_reco_ftk_refit_effi_vs_reco_eta1); tgae_reco_ftk_refit_effi_vs_reco_eta_stack.Add(tgae_reco_ftk_refit_effi_vs_reco_eta2)
tgae_reco_ftk_refit_effi_vs_reco_phi_stack.Add(tgae_reco_ftk_refit_effi_vs_reco_phi1); tgae_reco_ftk_refit_effi_vs_reco_phi_stack.Add(tgae_reco_ftk_refit_effi_vs_reco_phi2)
tgae_reco_ftk_refit_effi_vs_reco_d0_stack.Add(tgae_reco_ftk_refit_effi_vs_reco_d01); tgae_reco_ftk_refit_effi_vs_reco_d0_stack.Add(tgae_reco_ftk_refit_effi_vs_reco_d02)
tgae_reco_ftk_refit_effi_vs_reco_z0_stack.Add(tgae_reco_ftk_refit_effi_vs_reco_z01); tgae_reco_ftk_refit_effi_vs_reco_z0_stack.Add(tgae_reco_ftk_refit_effi_vs_reco_z02)

print("Cloning histograms")

if isData == False:
	h_truth_pt_new = h_truth_pt1.Clone("h_truth_pt_new")
	h_truth_eta_new = h_truth_eta1.Clone("h_truth_eta_new")
	h_truth_phi_new = h_truth_phi1.Clone("h_truth_phi_new")
	h_truth_m_new = h_truth_m1.Clone("h_truth_m_new")
	h_truth_d0_new = h_truth_d01.Clone("h_truth_d0_new")
	h_truth_z0_new = h_truth_z01.Clone("h_truth_z0_new")
	h_truth_qop_new = h_truth_qop1.Clone("h_truth_qop_new")
	h_truth_charge_new = h_truth_charge1.Clone("h_truth_charge_new")

h_reco_accepted_pt_new = h_reco_accepted_pt1.Clone("h_reco_accepted_pt_new")
h_reco_accepted_eta_new = h_reco_accepted_eta1.Clone("h_reco_accepted_eta_new")
h_reco_accepted_phi_new = h_reco_accepted_phi1.Clone("h_reco_accepted_phi_new")
# h_reco_accepted_m_new = h_reco_accepted_m1.Clone("h_reco_accepted_m_new")
h_reco_accepted_d0_new = h_reco_accepted_d01.Clone("h_reco_accepted_d0_new")
h_reco_accepted_z0_new = h_reco_accepted_z01.Clone("h_reco_accepted_z0_new")
h_reco_accepted_qop_new = h_reco_accepted_qop1.Clone("h_reco_accepted_qop_new")
h_reco_accepted_charge_new = h_reco_accepted_charge1.Clone("h_reco_accepted_charge_new")
h_reco_accepted_chi2_new = h_reco_accepted_chi21.Clone("h_reco_accepted_chi2_new")

h_reco_inclusive_pt_new = h_reco_inclusive_pt1.Clone("h_reco_inclusive_pt_new")
h_reco_inclusive_eta_new = h_reco_inclusive_eta1.Clone("h_reco_inclusive_eta_new")
h_reco_inclusive_phi_new = h_reco_inclusive_phi1.Clone("h_reco_inclusive_phi_new")
# h_reco_inclusive_m_new = h_reco_inclusive_m1.Clone("h_reco_inclusive_m_new")
h_reco_inclusive_d0_new = h_reco_inclusive_d01.Clone("h_reco_inclusive_d0_new")
h_reco_inclusive_z0_new = h_reco_inclusive_z01.Clone("h_reco_inclusive_z0_new")
h_reco_inclusive_qop_new = h_reco_inclusive_qop1.Clone("h_reco_inclusive_qop_new")
h_reco_inclusive_charge_new = h_reco_inclusive_charge1.Clone("h_reco_inclusive_charge_new")
h_reco_inclusive_chi2_new = h_reco_inclusive_chi21.Clone("h_reco_inclusive_chi2_new")

h_ftk_accepted_pt_new = h_ftk_accepted_pt1.Clone("h_ftk_accepted_pt_new")
h_ftk_accepted_eta_new = h_ftk_accepted_eta1.Clone("h_ftk_accepted_eta_new")
h_ftk_accepted_phi_new = h_ftk_accepted_phi1.Clone("h_ftk_accepted_phi_new")
# h_ftk_accepted_m_new = h_ftk_accepted_m1.Clone("h_ftk_accepted_m_new")
h_ftk_accepted_d0_new = h_ftk_accepted_d01.Clone("h_ftk_accepted_d0_new")
h_ftk_accepted_corrected_d0_new = h_ftk_accepted_corrected_d01.Clone("h_ftk_accepted_corrected_d0_new")
h_ftk_accepted_z0_new = h_ftk_accepted_z01.Clone("h_ftk_accepted_z0_new")
h_ftk_accepted_qop_new = h_ftk_accepted_qop1.Clone("h_ftk_accepted_qop_new")
h_ftk_accepted_charge_new = h_ftk_accepted_charge1.Clone("h_ftk_accepted_charge_new")
h_ftk_accepted_chi2_new = h_ftk_accepted_chi21.Clone("h_ftk_accepted_chi2_new")

h_ftk_inclusive_pt_new = h_ftk_inclusive_pt1.Clone("h_ftk_inclusive_pt_new")
h_ftk_inclusive_eta_new = h_ftk_inclusive_eta1.Clone("h_ftk_inclusive_eta_new")
h_ftk_inclusive_phi_new = h_ftk_inclusive_phi1.Clone("h_ftk_inclusive_phi_new")
# h_ftk_inclusive_m_new = h_ftk_inclusive_m1.Clone("h_ftk_inclusive_m_new")
h_ftk_inclusive_d0_new = h_ftk_inclusive_d01.Clone("h_ftk_inclusive_d0_new")
h_ftk_inclusive_corrected_d0_new = h_ftk_inclusive_corrected_d01.Clone("h_ftk_inclusive_corrected_d0_new")
h_ftk_inclusive_z0_new = h_ftk_inclusive_z01.Clone("h_ftk_inclusive_z0_new")
h_ftk_inclusive_qop_new = h_ftk_inclusive_qop1.Clone("h_ftk_inclusive_qop_new")
h_ftk_inclusive_charge_new = h_ftk_inclusive_charge1.Clone("h_ftk_inclusive_charge_new")
h_ftk_inclusive_chi2_new = h_ftk_inclusive_chi21.Clone("h_ftk_inclusive_chi2_new")

h_ftk_refit_accepted_pt_new = h_ftk_refit_accepted_pt1.Clone("h_ftk_refit_accepted_pt_new")
h_ftk_refit_accepted_eta_new = h_ftk_refit_accepted_eta1.Clone("h_ftk_refit_accepted_eta_new")
h_ftk_refit_accepted_phi_new = h_ftk_refit_accepted_phi1.Clone("h_ftk_refit_accepted_phi_new")
# h_ftk_refit_accepted_m_new = h_ftk_refit_accepted_m1.Clone("h_ftk_refit_accepted_m_new")
h_ftk_refit_accepted_d0_new = h_ftk_refit_accepted_d01.Clone("h_ftk_refit_accepted_d0_new")
h_ftk_refit_accepted_z0_new = h_ftk_refit_accepted_z01.Clone("h_ftk_refit_accepted_z0_new")
h_ftk_refit_accepted_qop_new = h_ftk_refit_accepted_qop1.Clone("h_ftk_refit_accepted_qop_new")
h_ftk_refit_accepted_charge_new = h_ftk_refit_accepted_charge1.Clone("h_ftk_refit_accepted_charge_new")
h_ftk_refit_accepted_chi2_new = h_ftk_refit_accepted_chi21.Clone("h_ftk_refit_accepted_chi2_new")

h_ftk_refit_inclusive_pt_new = h_ftk_refit_inclusive_pt1.Clone("h_ftk_refit_inclusive_pt_new")
h_ftk_refit_inclusive_eta_new = h_ftk_refit_inclusive_eta1.Clone("h_ftk_refit_inclusive_eta_new")
h_ftk_refit_inclusive_phi_new = h_ftk_refit_inclusive_phi1.Clone("h_ftk_refit_inclusive_phi_new")
# h_ftk_refit_inclusive_m_new = h_ftk_refit_inclusive_m1.Clone("h_ftk_refit_inclusive_m_new")
h_ftk_refit_inclusive_d0_new = h_ftk_refit_inclusive_d01.Clone("h_ftk_refit_inclusive_d0_new")
h_ftk_refit_inclusive_z0_new = h_ftk_refit_inclusive_z01.Clone("h_ftk_refit_inclusive_z0_new")
h_ftk_refit_inclusive_qop_new = h_ftk_refit_inclusive_qop1.Clone("h_ftk_refit_inclusive_qop_new")
h_ftk_refit_inclusive_charge_new = h_ftk_refit_inclusive_charge1.Clone("h_ftk_refit_inclusive_charge_new")
h_ftk_refit_inclusive_chi2_new = h_ftk_refit_inclusive_chi21.Clone("h_ftk_refit_inclusive_chi2_new")

if isData == False:
	h_reco_truthMatched_pt_bias_new = h_reco_truthMatched_pt_bias1.Clone("h_reco_truthMatched_pt_bias_new")
	h_reco_truthMatched_eta_bias_new = h_reco_truthMatched_eta_bias1.Clone("h_reco_truthMatched_eta_bias_new")
	h_reco_truthMatched_phi_bias_new = h_reco_truthMatched_phi_bias1.Clone("h_reco_truthMatched_phi_bias_new")
	h_reco_truthMatched_d0_bias_new = h_reco_truthMatched_d0_bias1.Clone("h_reco_truthMatched_d0_bias_new")

	h_truth_recoMatch_track_eta_new = h_truth_recoMatch_track_eta1.Clone("h_truth_recoMatch_track_eta_new")
	h_truth_recoMatch_track_phi_new = h_truth_recoMatch_track_phi1.Clone("h_truth_recoMatch_track_phi_new")
	h_reco_truthMatch_track_eta_new = h_reco_truthMatch_track_eta1.Clone("h_reco_truthMatch_track_eta_new")
	h_reco_truthMatch_track_phi_new = h_reco_truthMatch_track_phi1.Clone("h_reco_truthMatch_track_phi_new")
	h_truth_recoMatch_track_pt_new = h_truth_recoMatch_track_pt1.Clone("h_truth_recoMatch_track_pt_new")
	h_truth_recoMatch_track_d0_new = h_truth_recoMatch_track_d01.Clone("h_truth_recoMatch_track_d0_new")
	h_truth_recoMatch_track_z0_new = h_truth_recoMatch_track_z01.Clone("h_truth_recoMatch_track_z0_new")

	h_truth_ftk_Matched_pt_bias_new = h_truth_ftk_Matched_pt_bias1.Clone("h_truth_ftk_Matched_pt_bias_new")
	h_truth_ftk_Matched_eta_bias_new = h_truth_ftk_Matched_eta_bias1.Clone("h_truth_ftk_Matched_eta_bias_new")
	h_truth_ftk_Matched_phi_bias_new = h_truth_ftk_Matched_phi_bias1.Clone("h_truth_ftk_Matched_phi_bias_new")
	h_truth_ftk_Matched_d0_bias_new = h_truth_ftk_Matched_d0_bias1.Clone("h_truth_ftk_Matched_d0_bias_new")
	h_truth_ftk_Matched_corrected_d0_bias_new = h_truth_ftk_Matched_corrected_d0_bias1.Clone("h_truth_ftk_Matched_corrected_d0_bias_new")

	h_ftk_truthMatch_track_eta_new = h_ftk_truthMatch_track_eta1.Clone("h_ftk_truthMatch_track_eta_new")
	h_ftk_truthMatch_track_phi_new = h_ftk_truthMatch_track_phi1.Clone("h_ftk_truthMatch_track_phi_new")
	h_truth_ftkMatch_track_eta_new = h_truth_ftkMatch_track_eta1.Clone("h_truth_ftkMatch_track_eta_new")
	h_truth_ftkMatch_track_phi_new = h_truth_ftkMatch_track_phi1.Clone("h_truth_ftkMatch_track_phi_new")
	h_ftk_truthMatch_track_pt_new = h_ftk_truthMatch_track_pt1.Clone("h_ftk_truthMatch_track_pt_new")
	h_ftk_truthMatch_track_d0_new = h_ftk_truthMatch_track_d01.Clone("h_ftk_truthMatch_track_d0_new")
	h_ftk_truthMatch_track_z0_new = h_ftk_truthMatch_track_z01.Clone("h_ftk_truthMatch_track_z0_new")

	h_truth_ftk_refitMatched_pt_bias_new = h_truth_ftk_refitMatched_pt_bias1.Clone("h_truth_ftk_refitMatched_pt_bias_new")
	h_truth_ftk_refitMatched_eta_bias_new = h_truth_ftk_refitMatched_eta_bias1.Clone("h_truth_ftk_refitMatched_eta_bias_new")
	h_truth_ftk_refitMatched_phi_bias_new = h_truth_ftk_refitMatched_phi_bias1.Clone("h_truth_ftk_refitMatched_phi_bias_new")
	h_truth_ftk_refitMatched_d0_bias_new = h_truth_ftk_refitMatched_d0_bias1.Clone("h_truth_ftk_refitMatched_d0_bias_new")
	h_ftk_refit_truthMatch_track_eta_new = h_ftk_refit_truthMatch_track_eta1.Clone("h_ftk_refit_truthMatch_track_eta_new")
	h_ftk_refit_truthMatch_track_phi_new = h_ftk_refit_truthMatch_track_phi1.Clone("h_ftk_refit_truthMatch_track_phi_new")
	h_truth_ftkrefitMatch_track_eta_new = h_truth_ftkrefitMatch_track_eta1.Clone("h_truth_ftkrefitMatch_track_eta_new")
	h_truth_ftkrefitMatch_track_phi_new = h_truth_ftkrefitMatch_track_phi1.Clone("h_truth_ftkrefitMatch_track_phi_new")
	h_ftk_refit_truthMatch_track_pt_new = h_ftk_refit_truthMatch_track_pt1.Clone("h_ftk_refit_truthMatch_track_pt_new")
	h_ftk_refit_truthMatch_track_d0_new = h_ftk_refit_truthMatch_track_d01.Clone("h_ftk_refit_truthMatch_track_d0_new")
	h_ftk_refit_truthMatch_track_z0_new = h_ftk_refit_truthMatch_track_z01.Clone("h_ftk_refit_truthMatch_track_z0_new")

h_reco_ftkMatched_pt_bias_new = h_reco_ftkMatched_pt_bias1.Clone("h_reco_ftkMatched_pt_bias_new")
h_reco_ftkMatched_eta_bias_new = h_reco_ftkMatched_eta_bias1.Clone("h_reco_ftkMatched_eta_bias_new")
h_reco_ftkMatched_phi_bias_new = h_reco_ftkMatched_phi_bias1.Clone("h_reco_ftkMatched_phi_bias_new")
h_reco_ftkMatched_d0_bias_new = h_reco_ftkMatched_d0_bias1.Clone("h_reco_ftkMatched_d0_bias_new")
h_reco_ftkMatched_corrected_d0_bias_new = h_reco_ftkMatched_corrected_d0_bias1.Clone("h_reco_ftkMatched_corrected_d0_bias_new")

h_ftk_recoMatch_track_eta_new = h_ftk_recoMatch_track_eta1.Clone("h_ftk_recoMatch_track_eta_new")
h_ftk_recoMatch_track_phi_new = h_ftk_recoMatch_track_phi1.Clone("h_ftk_recoMatch_track_phi_new")
h_reco_ftkMatch_track_eta_new = h_reco_ftkMatch_track_eta1.Clone("h_reco_ftkMatch_track_eta_new")
h_reco_ftkMatch_track_phi_new = h_reco_ftkMatch_track_phi1.Clone("h_reco_ftkMatch_track_phi_new")
h_ftk_recoMatch_track_pt_new = h_ftk_recoMatch_track_pt1.Clone("h_ftk_recoMatch_track_pt_new")
h_ftk_recoMatch_track_d0_new = h_ftk_recoMatch_track_d01.Clone("h_ftk_recoMatch_track_d0_new")
# h_ftk_recoMatch_track_corrected_d0_new = h_ftk_recoMatch_track_corrected_d01.Clone("h_ftk_recoMatch_track_corrected_d0_new")
h_ftk_recoMatch_track_z0_new = h_ftk_recoMatch_track_z01.Clone("h_ftk_recoMatch_track_z0_new")

h_reco_ftk_refitMatched_pt_bias_new = h_reco_ftk_refitMatched_pt_bias1.Clone("h_reco_ftk_refitMatched_pt_bias_new")
h_reco_ftk_refitMatched_eta_bias_new = h_reco_ftk_refitMatched_eta_bias1.Clone("h_reco_ftk_refitMatched_eta_bias_new")
h_reco_ftk_refitMatched_phi_bias_new = h_reco_ftk_refitMatched_phi_bias1.Clone("h_reco_ftk_refitMatched_phi_bias_new")
h_reco_ftk_refitMatched_d0_bias_new = h_reco_ftk_refitMatched_d0_bias1.Clone("h_reco_ftk_refitMatched_d0_bias_new")

h_ftk_refit_recoMatch_track_eta_new = h_ftk_refit_recoMatch_track_eta1.Clone("h_ftk_refit_recoMatch_track_eta_new")
h_ftk_refit_recoMatch_track_phi_new = h_ftk_refit_recoMatch_track_phi1.Clone("h_ftk_refit_recoMatch_track_phi_new")
h_reco_ftkrefitMatch_track_eta_new = h_reco_ftkrefitMatch_track_eta1.Clone("h_reco_ftkrefitMatch_track_eta_new")
h_reco_ftkrefitMatch_track_phi_new = h_reco_ftkrefitMatch_track_phi1.Clone("h_reco_ftkrefitMatch_track_phi_new")
h_ftk_refit_recoMatch_track_pt_new = h_ftk_refit_recoMatch_track_pt1.Clone("h_ftk_refit_recoMatch_track_pt_new")
h_ftk_refit_recoMatch_track_d0_new = h_ftk_refit_recoMatch_track_d01.Clone("h_ftk_refit_recoMatch_track_d0_new")
h_ftk_refit_recoMatch_track_z0_new = h_ftk_refit_recoMatch_track_z01.Clone("h_ftk_refit_recoMatch_track_z0_new")

h_reco_accepted_hitPattern_EndCap_new = h_reco_accepted_hitPattern_EndCap1.Clone("h_reco_accepted_hitPattern_EndCap_new")
h_ftk_accepted_hitPattern_EndCap_new = h_ftk_accepted_hitPattern_EndCap1.Clone("h_ftk_accepted_hitPattern_EndCap_new")
h_ftk_refit_accepted_hitPattern_EndCap_new = h_ftk_refit_accepted_hitPattern_EndCap1.Clone("h_ftk_refit_accepted_hitPattern_EndCap_new")

h_reco_accepted_hitPattern_Barrel_new = h_reco_accepted_hitPattern_Barrel1.Clone("h_reco_accepted_hitPattern_Barrel_new")
h_ftk_accepted_hitPattern_Barrel_new = h_ftk_accepted_hitPattern_Barrel1.Clone("h_ftk_accepted_hitPattern_Barrel_new")
h_ftk_refit_accepted_hitPattern_Barrel_new = h_ftk_refit_accepted_hitPattern_Barrel1.Clone("h_ftk_refit_accepted_hitPattern_Barrel_new")

h_reco_accepted_hitPattern_new = h_reco_accepted_hitPattern1.Clone("h_reco_accepted_hitPattern_new")
h_ftk_accepted_hitPattern_new = h_ftk_accepted_hitPattern1.Clone("h_ftk_accepted_hitPattern_new")
h_ftk_refit_accepted_hitPattern_new = h_ftk_refit_accepted_hitPattern1.Clone("h_ftk_refit_accepted_hitPattern_new")


histocoordmasketa_reco_EndCap_new = histocoordmasketa_reco_EndCap1.Clone("histocoordmasketa_reco_EndCap_new")
histocoordmaskphi_reco_EndCap_new = histocoordmaskphi_reco_EndCap1.Clone("histocoordmaskphi_reco_EndCap_new")
histocoordmaskz0_reco_EndCap_new = histocoordmaskz0_reco_EndCap1.Clone("histocoordmaskz0_reco_EndCap_new")
histocoordmasketa_ftk_EndCap_new = histocoordmasketa_ftk_EndCap1.Clone("histocoordmasketa_ftk_EndCap_new")
histocoordmaskphi_ftk_EndCap_new = histocoordmaskphi_ftk_EndCap1.Clone("histocoordmaskphi_ftk_EndCap_new")
histocoordmaskz0_ftk_EndCap_new = histocoordmaskz0_ftk_EndCap1.Clone("histocoordmaskz0_ftk_EndCap_new")
histocoordmasketa_ftkrefit_EndCap_new = histocoordmasketa_ftkrefit_EndCap1.Clone("histocoordmasketa_ftkrefit_EndCap_new")
histocoordmaskphi_ftkrefit_EndCap_new = histocoordmaskphi_ftkrefit_EndCap1.Clone("histocoordmaskphi_ftkrefit_EndCap_new")
histocoordmaskz0_ftkrefit_EndCap_new = histocoordmaskz0_ftkrefit_EndCap1.Clone("histocoordmaskz0_ftkrefit_EndCap_new")

histocoordmasketa_reco_Barrel_new = histocoordmasketa_reco_Barrel1.Clone("histocoordmasketa_reco_Barrel_new")
histocoordmaskphi_reco_Barrel_new = histocoordmaskphi_reco_Barrel1.Clone("histocoordmaskphi_reco_Barrel_new")
histocoordmaskz0_reco_Barrel_new = histocoordmaskz0_reco_Barrel1.Clone("histocoordmaskz0_reco_Barrel_new")
histocoordmasketa_ftk_Barrel_new = histocoordmasketa_ftk_Barrel1.Clone("histocoordmasketa_ftk_Barrel_new")
histocoordmaskphi_ftk_Barrel_new = histocoordmaskphi_ftk_Barrel1.Clone("histocoordmaskphi_ftk_Barrel_new")
histocoordmaskz0_ftk_Barrel_new = histocoordmaskz0_ftk_Barrel1.Clone("histocoordmaskz0_ftk_Barrel_new")
histocoordmasketa_ftkrefit_Barrel_new = histocoordmasketa_ftkrefit_Barrel1.Clone("histocoordmasketa_ftkrefit_Barrel_new")
histocoordmaskphi_ftkrefit_Barrel_new = histocoordmaskphi_ftkrefit_Barrel1.Clone("histocoordmaskphi_ftkrefit_Barrel_new")
histocoordmaskz0_ftkrefit_Barrel_new = histocoordmaskz0_ftkrefit_Barrel1.Clone("histocoordmaskz0_ftkrefit_Barrel_new")

histocoordmasketa_reco_new = histocoordmasketa_reco1.Clone("histocoordmasketa_reco_new")
histocoordmaskphi_reco_new = histocoordmaskphi_reco1.Clone("histocoordmaskphi_reco_new")
histocoordmaskz0_reco_new = histocoordmaskz0_reco1.Clone("histocoordmaskz0_reco_new")
histocoordmasketa_ftk_new = histocoordmasketa_ftk1.Clone("histocoordmasketa_ftk_new")
histocoordmaskphi_ftk_new = histocoordmaskphi_ftk1.Clone("histocoordmaskphi_ftk_new")
histocoordmaskz0_ftk_new = histocoordmaskz0_ftk1.Clone("histocoordmaskz0_ftk_new")
histocoordmasketa_ftkrefit_new = histocoordmasketa_ftkrefit1.Clone("histocoordmasketa_ftkrefit_new")
histocoordmaskphi_ftkrefit_new = histocoordmaskphi_ftkrefit1.Clone("histocoordmaskphi_ftkrefit_new")
histocoordmaskz0_ftkrefit_new = histocoordmaskz0_ftkrefit1.Clone("histocoordmaskz0_ftkrefit_new")

print("Divding histograms")
if isData == False:
	h_truth_pt_new.Divide(h_truth_pt2)
	h_truth_eta_new.Divide(h_truth_eta2)
	h_truth_phi_new.Divide(h_truth_phi2)
	h_truth_m_new.Divide(h_truth_m2)
	h_truth_d0_new.Divide(h_truth_d02)
	h_truth_z0_new.Divide(h_truth_z02)
	h_truth_qop_new.Divide(h_truth_qop2)
	h_truth_charge_new.Divide(h_truth_charge2)

h_reco_accepted_pt_new.Divide(h_reco_accepted_pt2)
h_reco_accepted_eta_new.Divide(h_reco_accepted_eta2)
h_reco_accepted_phi_new.Divide(h_reco_accepted_phi2)
# h_reco_accepted_m_new.Divide(h_reco_accepted_m2)
h_reco_accepted_d0_new.Divide(h_reco_accepted_d02)
h_reco_accepted_z0_new.Divide(h_reco_accepted_z02)
h_reco_accepted_qop_new.Divide(h_reco_accepted_qop2)
h_reco_accepted_charge_new.Divide(h_reco_accepted_charge2)
h_reco_accepted_chi2_new.Divide(h_reco_accepted_chi22)

h_reco_inclusive_pt_new.Divide(h_reco_inclusive_pt2)
h_reco_inclusive_eta_new.Divide(h_reco_inclusive_eta2)
h_reco_inclusive_phi_new.Divide(h_reco_inclusive_phi2)
# h_reco_inclusive_m_new.Divide(h_reco_inclusive_m2)
h_reco_inclusive_d0_new.Divide(h_reco_inclusive_d02)
h_reco_inclusive_z0_new.Divide(h_reco_inclusive_z02)
h_reco_inclusive_qop_new.Divide(h_reco_inclusive_qop2)
h_reco_inclusive_charge_new.Divide(h_reco_inclusive_charge2)
h_reco_inclusive_chi2_new.Divide(h_reco_inclusive_chi22)
h_ftk_accepted_pt_new.Divide(h_ftk_accepted_pt2)
h_ftk_accepted_eta_new.Divide(h_ftk_accepted_eta2)
h_ftk_accepted_phi_new.Divide(h_ftk_accepted_phi2)
# h_ftk_accepted_m_new.Divide(h_ftk_accepted_m2)
h_ftk_accepted_d0_new.Divide(h_ftk_accepted_d02)
h_ftk_accepted_corrected_d0_new.Divide(h_ftk_accepted_corrected_d02)
h_ftk_accepted_z0_new.Divide(h_ftk_accepted_z02)
h_ftk_accepted_qop_new.Divide(h_ftk_accepted_qop2)
h_ftk_accepted_charge_new.Divide(h_ftk_accepted_charge2)
h_ftk_accepted_chi2_new.Divide(h_ftk_accepted_chi2)


h_ftk_inclusive_pt_new.Divide(h_ftk_inclusive_pt2)
h_ftk_inclusive_eta_new.Divide(h_ftk_inclusive_eta2)
h_ftk_inclusive_phi_new.Divide(h_ftk_inclusive_phi2)
# h_ftk_inclusive_m_new.Divide(h_ftk_inclusive_m2)
h_ftk_inclusive_d0_new.Divide(h_ftk_inclusive_d02)
h_ftk_inclusive_corrected_d0_new.Divide(h_ftk_inclusive_corrected_d02)
h_ftk_inclusive_z0_new.Divide(h_ftk_inclusive_z02)
h_ftk_inclusive_qop_new.Divide(h_ftk_inclusive_qop2)
h_ftk_inclusive_charge_new.Divide(h_ftk_inclusive_charge2)
h_ftk_inclusive_chi2_new.Divide(h_ftk_inclusive_chi22)

h_ftk_refit_accepted_pt_new.Divide(h_ftk_refit_accepted_pt2)
h_ftk_refit_accepted_eta_new.Divide(h_ftk_refit_accepted_eta2)
h_ftk_refit_accepted_phi_new.Divide(h_ftk_refit_accepted_phi2)
# h_ftk_refit_accepted_m_new.Divide(h_ftk_refit_accepted_m2)
h_ftk_refit_accepted_d0_new.Divide(h_ftk_refit_accepted_d02)
h_ftk_refit_accepted_z0_new.Divide(h_ftk_refit_accepted_z02)
h_ftk_refit_accepted_qop_new.Divide(h_ftk_refit_accepted_qop2)
h_ftk_refit_accepted_charge_new.Divide(h_ftk_refit_accepted_charge2)
h_ftk_refit_accepted_chi2_new.Divide(h_ftk_refit_accepted_chi22)

h_ftk_refit_inclusive_pt_new.Divide(h_ftk_refit_inclusive_pt2)
h_ftk_refit_inclusive_eta_new.Divide(h_ftk_refit_inclusive_eta2)
h_ftk_refit_inclusive_phi_new.Divide(h_ftk_refit_inclusive_phi2)
# h_ftk_refit_inclusive_m_new.Divide(h_ftk_refit_inclusive_m2)
h_ftk_refit_inclusive_d0_new.Divide(h_ftk_refit_inclusive_d02)
h_ftk_refit_inclusive_z0_new.Divide(h_ftk_refit_inclusive_z02)
h_ftk_refit_inclusive_qop_new.Divide(h_ftk_refit_inclusive_qop2)
h_ftk_refit_inclusive_charge_new.Divide(h_ftk_refit_inclusive_charge2)
h_ftk_refit_inclusive_chi2_new.Divide(h_ftk_refit_inclusive_chi22)

if isData == False:
	h_reco_truthMatched_pt_bias_new.Divide(h_reco_truthMatched_pt_bias2)
	h_reco_truthMatched_eta_bias_new.Divide(h_reco_truthMatched_eta_bias2)
	h_reco_truthMatched_phi_bias_new.Divide(h_reco_truthMatched_phi_bias2)
	h_reco_truthMatched_d0_bias_new.Divide(h_reco_truthMatched_d0_bias2)

	h_truth_recoMatch_track_eta_new.Divide(h_truth_recoMatch_track_eta2)
	h_truth_recoMatch_track_phi_new.Divide(h_truth_recoMatch_track_phi2)
	h_reco_truthMatch_track_eta_new.Divide(h_reco_truthMatch_track_eta2)
	h_reco_truthMatch_track_phi_new.Divide(h_reco_truthMatch_track_phi2)
	h_truth_recoMatch_track_pt_new.Divide(h_truth_recoMatch_track_pt2)
	h_truth_recoMatch_track_d0_new.Divide(h_truth_recoMatch_track_d02)
	h_truth_recoMatch_track_z0_new.Divide(h_truth_recoMatch_track_z02)

	h_truth_ftk_Matched_pt_bias_new.Divide(h_truth_ftk_Matched_pt_bias2)
	h_truth_ftk_Matched_eta_bias_new.Divide(h_truth_ftk_Matched_eta_bias2)
	h_truth_ftk_Matched_phi_bias_new.Divide(h_truth_ftk_Matched_phi_bias2)
	h_truth_ftk_Matched_d0_bias_new.Divide(h_truth_ftk_Matched_d0_bias2)
	h_truth_ftk_Matched_corrected_d0_bias_new.Divide(h_truth_ftk_Matched_corrected_d0_bias2)

	h_ftk_truthMatch_track_eta_new.Divide(h_ftk_truthMatch_track_eta2)
	h_ftk_truthMatch_track_phi_new.Divide(h_ftk_truthMatch_track_phi2)
	h_truth_ftkMatch_track_eta_new.Divide(h_truth_ftkMatch_track_eta2)
	h_truth_ftkMatch_track_phi_new.Divide(h_truth_ftkMatch_track_phi2)
	h_ftk_truthMatch_track_pt_new.Divide(h_ftk_truthMatch_track_pt2)
	h_ftk_truthMatch_track_d0_new.Divide(h_ftk_truthMatch_track_d02)
	h_ftk_truthMatch_track_z0_new.Divide(h_ftk_truthMatch_track_z02)
	h_truth_ftk_refitMatched_pt_bias_new.Divide(h_truth_ftk_refitMatched_pt_bias2)
	h_truth_ftk_refitMatched_eta_bias_new.Divide(h_truth_ftk_refitMatched_eta_bias2)
	h_truth_ftk_refitMatched_phi_bias_new.Divide(h_truth_ftk_refitMatched_phi_bias2)
	h_truth_ftk_refitMatched_d0_bias_new.Divide(h_truth_ftk_refitMatched_d0_bias2)

	h_ftk_refit_truthMatch_track_eta_new.Divide(h_ftk_refit_truthMatch_track_eta2)
	h_ftk_refit_truthMatch_track_phi_new.Divide(h_ftk_refit_truthMatch_track_phi2)
	h_truth_ftkrefitMatch_track_eta_new.Divide(h_truth_ftkrefitMatch_track_eta2)
	h_truth_ftkrefitMatch_track_phi_new.Divide(h_truth_ftkrefitMatch_track_phi2)
	h_ftk_refit_truthMatch_track_pt_new.Divide(h_ftk_refit_truthMatch_track_pt2)
	h_ftk_refit_truthMatch_track_d0_new.Divide(h_ftk_refit_truthMatch_track_d02)
	h_ftk_refit_truthMatch_track_z0_new.Divide(h_ftk_refit_truthMatch_track_z02)

h_reco_ftkMatched_pt_bias_new.Divide(h_reco_ftkMatched_pt_bias2)
h_reco_ftkMatched_eta_bias_new.Divide(h_reco_ftkMatched_eta_bias2)
h_reco_ftkMatched_phi_bias_new.Divide(h_reco_ftkMatched_phi_bias2)
h_reco_ftkMatched_d0_bias_new.Divide(h_reco_ftkMatched_d0_bias2)
h_reco_ftkMatched_corrected_d0_bias_new.Divide(h_reco_ftkMatched_corrected_d0_bias2)

h_ftk_recoMatch_track_eta_new.Divide(h_ftk_recoMatch_track_eta2)
h_ftk_recoMatch_track_phi_new.Divide(h_ftk_recoMatch_track_phi2)
h_reco_ftkMatch_track_eta_new.Divide(h_reco_ftkMatch_track_eta2)
h_reco_ftkMatch_track_phi_new.Divide(h_reco_ftkMatch_track_phi2)
h_ftk_recoMatch_track_pt_new.Divide(h_ftk_recoMatch_track_pt2)
h_ftk_recoMatch_track_d0_new.Divide(h_ftk_recoMatch_track_d02)
# h_ftk_recoMatch_track_corrected_d0_new.Divide(h_ftk_recoMatch_track_corrected_d02)
h_ftk_recoMatch_track_z0_new.Divide(h_ftk_recoMatch_track_z02)

h_reco_ftk_refitMatched_pt_bias_new.Divide(h_reco_ftk_refitMatched_pt_bias2)
h_reco_ftk_refitMatched_eta_bias_new.Divide(h_reco_ftk_refitMatched_eta_bias2)
h_reco_ftk_refitMatched_phi_bias_new.Divide(h_reco_ftk_refitMatched_phi_bias2)
h_reco_ftk_refitMatched_d0_bias_new.Divide(h_reco_ftk_refitMatched_d0_bias2)

h_ftk_refit_recoMatch_track_eta_new.Divide(h_ftk_refit_recoMatch_track_eta2)
h_ftk_refit_recoMatch_track_phi_new.Divide(h_ftk_refit_recoMatch_track_phi2)
h_reco_ftkrefitMatch_track_eta_new.Divide(h_reco_ftkrefitMatch_track_eta2)
h_reco_ftkrefitMatch_track_phi_new.Divide(h_reco_ftkrefitMatch_track_phi2)
h_ftk_refit_recoMatch_track_pt_new.Divide(h_ftk_refit_recoMatch_track_pt2)
h_ftk_refit_recoMatch_track_d0_new.Divide(h_ftk_refit_recoMatch_track_d02)
h_ftk_refit_recoMatch_track_z0_new.Divide(h_ftk_refit_recoMatch_track_z02)

h_reco_accepted_hitPattern_EndCap_new.Divide(h_reco_accepted_hitPattern_EndCap2)
h_ftk_accepted_hitPattern_EndCap_new.Divide(h_ftk_accepted_hitPattern_EndCap2)
h_ftk_refit_accepted_hitPattern_EndCap_new.Divide(h_ftk_refit_accepted_hitPattern_EndCap2)

h_reco_accepted_hitPattern_Barrel_new.Divide(h_reco_accepted_hitPattern_Barrel2)
h_ftk_accepted_hitPattern_Barrel_new.Divide(h_ftk_accepted_hitPattern_Barrel2)
h_ftk_refit_accepted_hitPattern_Barrel_new.Divide(h_ftk_refit_accepted_hitPattern_Barrel2)

h_reco_accepted_hitPattern_new.Divide(h_reco_accepted_hitPattern2)
h_ftk_accepted_hitPattern_new.Divide(h_ftk_accepted_hitPattern2)
h_ftk_refit_accepted_hitPattern_new.Divide(h_ftk_refit_accepted_hitPattern2)

histocoordmasketa_reco_EndCap_new.Divide(histocoordmasketa_reco_EndCap2)
histocoordmaskphi_reco_EndCap_new.Divide(histocoordmaskphi_reco_EndCap2)
histocoordmaskz0_reco_EndCap_new.Divide(histocoordmaskz0_reco_EndCap2)
histocoordmasketa_ftk_EndCap_new.Divide(histocoordmasketa_ftk_EndCap2)
histocoordmaskphi_ftk_EndCap_new.Divide(histocoordmaskphi_ftk_EndCap2)
histocoordmaskz0_ftk_EndCap_new.Divide(histocoordmaskz0_ftk_EndCap2)
histocoordmasketa_ftkrefit_EndCap_new.Divide(histocoordmasketa_ftkrefit_EndCap2)
histocoordmaskphi_ftkrefit_EndCap_new.Divide(histocoordmaskphi_ftkrefit_EndCap2)
histocoordmaskz0_ftkrefit_EndCap_new.Divide(histocoordmaskz0_ftkrefit_EndCap2)

histocoordmasketa_reco_Barrel_new.Divide(histocoordmasketa_reco_Barrel2)
histocoordmaskphi_reco_Barrel_new.Divide(histocoordmaskphi_reco_Barrel2)
histocoordmaskz0_reco_Barrel_new.Divide(histocoordmaskz0_reco_Barrel2)
histocoordmasketa_ftk_Barrel_new.Divide(histocoordmasketa_ftk_Barrel2)
histocoordmaskphi_ftk_Barrel_new.Divide(histocoordmaskphi_ftk_Barrel2)
histocoordmaskz0_ftk_Barrel_new.Divide(histocoordmaskz0_ftk_Barrel2)
histocoordmasketa_ftkrefit_Barrel_new.Divide(histocoordmasketa_ftkrefit_Barrel2)
histocoordmaskphi_ftkrefit_Barrel_new.Divide(histocoordmaskphi_ftkrefit_Barrel2)
histocoordmaskz0_ftkrefit_Barrel_new.Divide(histocoordmaskz0_ftkrefit_Barrel2)

histocoordmasketa_reco_new.Divide(histocoordmasketa_reco2)
histocoordmaskphi_reco_new.Divide(histocoordmaskphi_reco2)
histocoordmaskz0_reco_new.Divide(histocoordmaskz0_reco2)
histocoordmasketa_ftk_new.Divide(histocoordmasketa_ftk2)
histocoordmaskphi_ftk_new.Divide(histocoordmaskphi_ftk2)
histocoordmaskz0_ftk_new.Divide(histocoordmaskz0_ftk2)
histocoordmasketa_ftkrefit_new.Divide(histocoordmasketa_ftkrefit2)
histocoordmaskphi_ftkrefit_new.Divide(histocoordmaskphi_ftkrefit2)
histocoordmaskz0_ftkrefit_new.Divide(histocoordmaskz0_ftkrefit2)

# newFile = TFile("comparison.root", "recreate")
# newFile.cd()

# # newFile.Add(h_ftk_accepted_hitPattern_EndCap_new)
# # newFile.Add(h_ftk_refit_accepted_hitPattern_EndCap_new)
# # newFile.Add(h_reco_accepted_hitPattern_EndCap_new)
# newFile.Add(histocoordmasketa_ftk_EndCap_new)
# newFile.Add(histocoordmaskphi_ftk_EndCap_new)
# newFile.Add(histocoordmaskz0_ftk_EndCap_new)
# newFile.Add(histocoordmasketa_ftkrefit_EndCap_new)
# newFile.Add(histocoordmaskphi_ftkrefit_EndCap_new)
# newFile.Add(histocoordmaskz0_ftkrefit_EndCap_new)
# newFile.Add(histocoordmasketa_reco_EndCap_new)
# newFile.Add(histocoordmaskphi_reco_EndCap_new)
# newFile.Add(histocoordmaskz0_reco_EndCap_new)

# # newFile.Add(h_ftk_accepted_hitPattern_Barrel_new)
# # newFile.Add(h_ftk_refit_accepted_hitPattern_Barrel_new)
# # newFile.Add(h_reco_accepted_hitPattern_Barrel_new)
# newFile.Add(histocoordmasketa_ftk_Barrel_new)
# newFile.Add(histocoordmaskphi_ftk_Barrel_new)
# newFile.Add(histocoordmaskz0_ftk_Barrel_new)
# newFile.Add(histocoordmasketa_ftkrefit_Barrel_new)
# newFile.Add(histocoordmaskphi_ftkrefit_Barrel_new)
# newFile.Add(histocoordmaskz0_ftkrefit_Barrel_new)
# newFile.Add(histocoordmasketa_reco_Barrel_new)
# newFile.Add(histocoordmaskphi_reco_Barrel_new)
# newFile.Add(histocoordmaskz0_reco_Barrel_new)

# # newFile.Add(h_ftk_accepted_hitPattern_new)
# # newFile.Add(h_ftk_refit_accepted_hitPattern_new)
# # newFile.Add(h_reco_accepted_hitPattern_new)
# newFile.Add(histocoordmasketa_ftk_new)
# newFile.Add(histocoordmaskphi_ftk_new)
# newFile.Add(histocoordmaskz0_ftk_new)
# newFile.Add(histocoordmasketa_ftkrefit_new)
# newFile.Add(histocoordmaskphi_ftkrefit_new)
# newFile.Add(histocoordmaskz0_ftkrefit_new)
# newFile.Add(histocoordmasketa_reco_new)
# newFile.Add(histocoordmaskphi_reco_new)
# newFile.Add(histocoordmaskz0_reco_new)

# # # if isData == False:
# # newFile.Add(h_truth_pt_new)
# # newFile.Add(h_truth_eta_new)
# # newFile.Add(h_truth_phi_new)
# # newFile.Add(h_truth_m_new)
# # newFile.Add(h_truth_d0_new)
# # newFile.Add(h_truth_z0_new)
# # newFile.Add(h_truth_qop_new)
# # newFile.Add(h_truth_charge_new)

# # newFile.Add(h_reco_accepted_pt_new)
# # newFile.Add(h_reco_accepted_eta_new)
# # newFile.Add(h_reco_accepted_phi_new)
# # newFile.Add(h_reco_accepted_m_new)
# # newFile.Add(h_reco_accepted_d0_new)
# # newFile.Add(h_reco_accepted_z0_new)
# # newFile.Add(h_reco_accepted_qop_new)
# # newFile.Add(h_reco_accepted_charge_new)
# # newFile.Add(h_reco_accepted_chi2_new)

# # newFile.Add(h_reco_inclusive_pt_new)
# # newFile.Add(h_reco_inclusive_eta_new)
# # newFile.Add(h_reco_inclusive_phi_new)
# # newFile.Add(h_reco_inclusive_m_new)
# # newFile.Add(h_reco_inclusive_d0_new)
# # newFile.Add(h_reco_inclusive_z0_new)
# # newFile.Add(h_reco_inclusive_qop_new)
# # newFile.Add(h_reco_inclusive_charge_new)
# # newFile.Add(h_reco_inclusive_chi2_new)

# # newFile.Add(h_ftk_accepted_pt_new)
# # newFile.Add(h_ftk_accepted_eta_new)
# # newFile.Add(h_ftk_accepted_phi_new)
# # newFile.Add(h_ftk_accepted_m_new)
# # newFile.Add(h_ftk_accepted_d0_new)
# # newFile.Add(h_ftk_accepted_corrected_d0_new)
# # newFile.Add(h_ftk_accepted_z0_new)
# # newFile.Add(h_ftk_accepted_qop_new)
# # newFile.Add(h_ftk_accepted_charge_new)
# # newFile.Add(h_ftk_accepted_chi2_new)

# # newFile.Add(h_ftk_inclusive_pt_new)
# # newFile.Add(h_ftk_inclusive_eta_new)
# # newFile.Add(h_ftk_inclusive_phi_new)
# # newFile.Add(h_ftk_inclusive_m_new)
# # newFile.Add(h_ftk_inclusive_d0_new)
# # newFile.Add(h_ftk_inclusive_corrected_d0_new)
# # newFile.Add(h_ftk_inclusive_z0_new)
# # newFile.Add(h_ftk_inclusive_qop_new)
# # newFile.Add(h_ftk_inclusive_charge_new)
# # newFile.Add(h_ftk_inclusive_chi2_new)

# # newFile.Add(h_ftk_refit_accepted_pt_new)
# # newFile.Add(h_ftk_refit_accepted_eta_new)
# # newFile.Add(h_ftk_refit_accepted_phi_new)
# # newFile.Add(h_ftk_refit_accepted_m_new)
# # newFile.Add(h_ftk_refit_accepted_d0_new)
# # newFile.Add(h_ftk_refit_accepted_z0_new)
# # newFile.Add(h_ftk_refit_accepted_qop_new)
# # newFile.Add(h_ftk_refit_accepted_charge_new)
# # newFile.Add(h_ftk_refit_accepted_chi2_new)

# # newFile.Add(h_ftk_refit_inclusive_pt_new)
# # newFile.Add(h_ftk_refit_inclusive_eta_new)
# # newFile.Add(h_ftk_refit_inclusive_phi_new)
# # newFile.Add(h_ftk_refit_inclusive_m_new)
# # newFile.Add(h_ftk_refit_inclusive_d0_new)
# # newFile.Add(h_ftk_refit_inclusive_z0_new)
# # newFile.Add(h_ftk_refit_inclusive_qop_new)
# # newFile.Add(h_ftk_refit_inclusive_charge_new)
# # newFile.Add(h_ftk_refit_inclusive_chi2_new)

# # newFile.Add(h_reco_ftk_refitMatched_pt_bias_new)
# # newFile.Add(h_reco_ftk_refitMatched_eta_bias_new)
# # newFile.Add(h_reco_ftk_refitMatched_phi_bias_new)
# # newFile.Add(h_reco_ftk_refitMatched_d0_bias_new)
# # newFile.Add(h_ftk_refit_recoMatch_track_eta_new)
# # newFile.Add(h_ftk_refit_recoMatch_track_phi_new)
# # newFile.Add(h_reco_ftkrefitMatch_track_eta_new)
# # newFile.Add(h_reco_ftkrefitMatch_track_phi_new)
# # newFile.Add(h_ftk_refit_recoMatch_track_pt_new)
# # newFile.Add(h_ftk_refit_recoMatch_track_d0_new)
# # newFile.Add(h_ftk_refit_recoMatch_track_z0_new)


# # newFile.Add(h_reco_ftkMatched_pt_bias_new)
# # newFile.Add(h_reco_ftkMatched_eta_bias_new)
# # newFile.Add(h_reco_ftkMatched_phi_bias_new)
# # newFile.Add(h_reco_ftkMatched_d0_bias_new)
# # newFile.Add(h_reco_ftkMatched_corrected_d0_bias_new)
# # newFile.Add(h_ftk_recoMatch_track_eta_new)
# # newFile.Add(h_ftk_recoMatch_track_phi_new)
# # newFile.Add(h_reco_ftkMatch_track_eta_new)
# # newFile.Add(h_reco_ftkMatch_track_phi_new)
# # newFile.Add(h_ftk_recoMatch_track_pt_new)
# # newFile.Add(h_ftk_recoMatch_track_d0_new)
# # newFile.Add(h_ftk_recoMatch_track_corrected_d0_new)
# # newFile.Add(h_ftk_recoMatch_track_z0_new)




# # # if isData == False:
# # newFile.Add(h_truth_ftk_refitMatched_pt_bias_new)
# # newFile.Add(h_truth_ftk_refitMatched_eta_bias_new)
# # newFile.Add(h_truth_ftk_refitMatched_phi_bias_new)
# # newFile.Add(h_truth_ftk_refitMatched_d0_bias_new)
# # newFile.Add(h_ftk_refit_truthMatch_track_eta_new)
# # newFile.Add(h_ftk_refit_truthMatch_track_phi_new)
# # newFile.Add(h_truth_ftkrefitMatch_track_eta_new)
# # newFile.Add(h_truth_ftkrefitMatch_track_phi_new)
# # newFile.Add(h_ftk_refit_truthMatch_track_pt_new)
# # newFile.Add(h_ftk_refit_truthMatch_track_d0_new)
# # newFile.Add(h_ftk_refit_truthMatch_track_z0_new)

# # newFile.Add(h_truth_ftk_Matched_pt_bias_new)
# # newFile.Add(h_truth_ftk_Matched_eta_bias_new)
# # newFile.Add(h_truth_ftk_Matched_phi_bias_new)
# # newFile.Add(h_truth_ftk_Matched_d0_bias_new)
# # newFile.Add(h_truth_ftk_Matched_corrected_d0_bias_new)
# # newFile.Add(h_ftk_truthMatch_track_eta_new)
# # newFile.Add(h_ftk_truthMatch_track_phi_new)
# # newFile.Add(h_truth_ftkMatch_track_eta_new)
# # newFile.Add(h_truth_ftkMatch_track_phi_new)
# # newFile.Add(h_ftk_truthMatch_track_pt_new)
# # newFile.Add(h_ftk_truthMatch_track_d0_new)
# # newFile.Add(h_ftk_truthMatch_track_z0_new)

# # newFile.Add(h_reco_truthMatched_pt_bias_new)
# # newFile.Add(h_reco_truthMatched_eta_bias_new)
# # newFile.Add(h_reco_truthMatched_phi_bias_new)
# # newFile.Add(h_reco_truthMatched_d0_bias_new)
# # newFile.Add(h_truth_recoMatch_track_eta_new)
# # newFile.Add(h_truth_recoMatch_track_phi_new)
# # newFile.Add(h_reco_truthMatch_track_eta_new)
# # newFile.Add(h_reco_truthMatch_track_phi_new)
# # newFile.Add(h_truth_recoMatch_track_pt_new)
# # newFile.Add(h_truth_recoMatch_track_d0_new)
# # newFile.Add(h_truth_recoMatch_track_z0_new)


# # # newFile.Add(tgae_truth_reco_effi_vs_truth_pt_new)
# # # newFile.Add(tgae_truth_reco_effi_vs_truth_eta_new)
# # # newFile.Add(tgae_truth_reco_effi_vs_truth_phi_new)
# # # newFile.Add(tgae_truth_reco_effi_vs_truth_d0_new)
# # # newFile.Add(tgae_truth_reco_effi_vs_truth_z0_new)
# # # newFile.Add(tgae_truth_ftk_effi_vs_truth_pt_new)
# # # newFile.Add(tgae_truth_ftk_effi_vs_truth_eta_new)
# # # newFile.Add(tgae_truth_ftk_effi_vs_truth_phi_new)
# # # newFile.Add(tgae_truth_ftk_effi_vs_truth_d0_new)
# # # newFile.Add(tgae_truth_ftk_effi_vs_truth_z0_new)
# # # newFile.Add(tgae_truth_ftk_refit_effi_vs_truth_pt_new)
# # # newFile.Add(tgae_truth_ftk_refit_effi_vs_truth_eta_new)
# # # newFile.Add(tgae_truth_ftk_refit_effi_vs_truth_phi_new)
# # # newFile.Add(tgae_truth_ftk_refit_effi_vs_truth_d0_new)
# # # newFile.Add(tgae_truth_ftk_refit_effi_vs_truth_z0_new)

# # # newFile.Add(tgae_reco_ftk_effi_vs_reco_pt_new)
# # # newFile.Add(tgae_reco_ftk_effi_vs_reco_eta_new)
# # # newFile.Add(tgae_reco_ftk_effi_vs_reco_phi_new)
# # # # newFile.Add(tgae_reco_ftk_effi_vs_reco_low_pt_new)
# # # # newFile.Add(tgae_reco_ftk_effi_vs_reco_high_pt_new)
# # # newFile.Add(tgae_reco_ftk_effi_vs_reco_d0_new)
# # # newFile.Add(tgae_reco_ftk_effi_vs_reco_z0_new)

# # # newFile.Add(tgae_reco_ftk_refit_effi_vs_reco_pt_new)
# # # newFile.Add(tgae_reco_ftk_refit_effi_vs_reco_eta_new)
# # # newFile.Add(tgae_reco_ftk_refit_effi_vs_reco_phi_new)
# # # newFile.Add(tgae_reco_ftk_refit_effi_vs_reco_d0_new)
# # # newFile.Add(tgae_reco_ftk_refit_effi_vs_reco_z0_new)

# # newFile.Add(h_truth_pt_stack)
# # newFile.Add(h_truth_eta_stack)
# # newFile.Add(h_truth_phi_stack)
# # newFile.Add(h_truth_m_stack)
# # newFile.Add(h_truth_d0_stack)
# # newFile.Add(h_truth_z0_stack)
# # newFile.Add(h_truth_qop_stack)
# # newFile.Add(h_truth_charge_stack)

# # newFile.Add(h_reco_accepted_pt_stack)
# # newFile.Add(h_reco_accepted_eta_stack)
# # newFile.Add(h_reco_accepted_phi_stack)
# # newFile.Add(h_reco_accepted_m_stack)
# # newFile.Add(h_reco_accepted_d0_stack)
# # newFile.Add(h_reco_accepted_z0_stack)
# # newFile.Add(h_reco_accepted_qop_stack)
# # newFile.Add(h_reco_accepted_charge_stack)
# # newFile.Add(h_reco_accepted_chi2_stack)

# # newFile.Add(h_reco_inclusive_pt_stack)
# # newFile.Add(h_reco_inclusive_eta_stack)
# # newFile.Add(h_reco_inclusive_phi_stack)
# # newFile.Add(h_reco_inclusive_m_stack)
# # newFile.Add(h_reco_inclusive_d0_stack)
# # newFile.Add(h_reco_inclusive_z0_stack)
# # newFile.Add(h_reco_inclusive_qop_stack)
# # newFile.Add(h_reco_inclusive_charge_stack)
# # newFile.Add(h_reco_inclusive_chi2_stack)

# # newFile.Add(h_ftk_accepted_pt_stack)
# # newFile.Add(h_ftk_accepted_eta_stack)
# # newFile.Add(h_ftk_accepted_phi_stack)
# # newFile.Add(h_ftk_accepted_m_stack)
# # newFile.Add(h_ftk_accepted_d0_stack)
# # newFile.Add(h_ftk_accepted_corrected_d0_stack)
# # newFile.Add(h_ftk_accepted_z0_stack)
# # newFile.Add(h_ftk_accepted_qop_stack)
# # newFile.Add(h_ftk_accepted_charge_stack)
# # newFile.Add(h_ftk_accepted_chi2_stack)

# # newFile.Add(h_ftk_inclusive_pt_stack)
# # newFile.Add(h_ftk_inclusive_eta_stack)
# # newFile.Add(h_ftk_inclusive_phi_stack)
# # newFile.Add(h_ftk_inclusive_m_stack)
# # newFile.Add(h_ftk_inclusive_d0_stack)
# # newFile.Add(h_ftk_inclusive_corrected_d0_stack)
# # newFile.Add(h_ftk_inclusive_z0_stack)
# # newFile.Add(h_ftk_inclusive_qop_stack)
# # newFile.Add(h_ftk_inclusive_charge_stack)
# # newFile.Add(h_ftk_inclusive_chi2_stack)

# # newFile.Add(h_ftk_refit_accepted_pt_stack)
# # newFile.Add(h_ftk_refit_accepted_eta_stack)
# # newFile.Add(h_ftk_refit_accepted_phi_stack)
# # newFile.Add(h_ftk_refit_accepted_m_stack)
# # newFile.Add(h_ftk_refit_accepted_d0_stack)
# # newFile.Add(h_ftk_refit_accepted_z0_stack)
# # newFile.Add(h_ftk_refit_accepted_qop_stack)
# # newFile.Add(h_ftk_refit_accepted_charge_stack)
# # newFile.Add(h_ftk_refit_accepted_chi2_stack)

# # newFile.Add(h_ftk_refit_inclusive_pt_stack)
# # newFile.Add(h_ftk_refit_inclusive_eta_stack)
# # newFile.Add(h_ftk_refit_inclusive_phi_stack)
# # newFile.Add(h_ftk_refit_inclusive_m_stack)
# # newFile.Add(h_ftk_refit_inclusive_d0_stack)
# # newFile.Add(h_ftk_refit_inclusive_z0_stack)
# # newFile.Add(h_ftk_refit_inclusive_qop_stack)
# # newFile.Add(h_ftk_refit_inclusive_charge_stack)
# # newFile.Add(h_ftk_refit_inclusive_chi2_stack)

# # newFile.Add(h_reco_truthMatched_pt_bias_stack)
# # newFile.Add(h_reco_truthMatched_eta_bias_stack)
# # newFile.Add(h_reco_truthMatched_phi_bias_stack)
# # newFile.Add(h_reco_truthMatched_d0_bias_stack)

# # newFile.Add(h_truth_recoMatch_track_eta_stack)
# # newFile.Add(h_truth_recoMatch_track_phi_stack)
# # newFile.Add(h_reco_truthMatch_track_eta_stack)
# # newFile.Add(h_reco_truthMatch_track_phi_stack)
# # newFile.Add(h_truth_recoMatch_track_pt_stack)
# # newFile.Add(h_truth_recoMatch_track_d0_stack)
# # newFile.Add(h_truth_recoMatch_track_z0_stack)

# # newFile.Add(h_truth_ftk_Matched_pt_bias_stack)
# # newFile.Add(h_truth_ftk_Matched_eta_bias_stack)
# # newFile.Add(h_truth_ftk_Matched_phi_bias_stack)
# # newFile.Add(h_truth_ftk_Matched_d0_bias_stack)
# # newFile.Add(h_truth_ftk_Matched_corrected_d0_bias_stack)

# # newFile.Add(h_ftk_truthMatch_track_eta_stack)
# # newFile.Add(h_ftk_truthMatch_track_phi_stack)
# # newFile.Add(h_truth_ftkMatch_track_eta_stack)
# # newFile.Add(h_truth_ftkMatch_track_phi_stack)
# # newFile.Add(h_ftk_truthMatch_track_pt_stack)
# # newFile.Add(h_ftk_truthMatch_track_d0_stack)
# # newFile.Add(h_ftk_truthMatch_track_z0_stack)

# # newFile.Add(h_truth_ftk_refitMatched_pt_bias_stack)
# # newFile.Add(h_truth_ftk_refitMatched_eta_bias_stack)
# # newFile.Add(h_truth_ftk_refitMatched_phi_bias_stack)
# # newFile.Add(h_truth_ftk_refitMatched_d0_bias_stack)

# # newFile.Add(h_ftk_refit_truthMatch_track_eta_stack)
# # newFile.Add(h_ftk_refit_truthMatch_track_phi_stack)
# # newFile.Add(h_truth_ftkrefitMatch_track_eta_stack)
# # newFile.Add(h_truth_ftkrefitMatch_track_phi_stack)
# # newFile.Add(h_ftk_refit_truthMatch_track_pt_stack)
# # newFile.Add(h_ftk_refit_truthMatch_track_d0_stack)
# # newFile.Add(h_ftk_refit_truthMatch_track_z0_stack)

# # newFile.Add(h_reco_ftkMatched_pt_bias_stack)
# # newFile.Add(h_reco_ftkMatched_eta_bias_stack)
# # newFile.Add(h_reco_ftkMatched_phi_bias_stack)
# # newFile.Add(h_reco_ftkMatched_d0_bias_stack)
# # newFile.Add(h_reco_ftkMatched_corrected_d0_bias_stack)

# # newFile.Add(h_ftk_recoMatch_track_eta_stack)
# # newFile.Add(h_ftk_recoMatch_track_phi_stack)
# # newFile.Add(h_reco_ftkMatch_track_eta_stack)
# # newFile.Add(h_reco_ftkMatch_track_phi_stack)
# # newFile.Add(h_ftk_recoMatch_track_pt_stack)
# # newFile.Add(h_ftk_recoMatch_track_d0_stack)
# # newFile.Add(h_ftk_recoMatch_track_corrected_d0_stack)
# # newFile.Add(h_ftk_recoMatch_track_z0_stack)

# # newFile.Add(h_reco_ftk_refitMatched_pt_bias_stack)
# # newFile.Add(h_reco_ftk_refitMatched_eta_bias_stack)
# # newFile.Add(h_reco_ftk_refitMatched_phi_bias_stack)
# # newFile.Add(h_reco_ftk_refitMatched_d0_bias_stack)

# # newFile.Add(h_ftk_refit_recoMatch_track_eta_stack)
# # newFile.Add(h_ftk_refit_recoMatch_track_phi_stack)
# # newFile.Add(h_reco_ftkrefitMatch_track_eta_stack)
# # newFile.Add(h_reco_ftkrefitMatch_track_phi_stack)
# # newFile.Add(h_ftk_refit_recoMatch_track_pt_stack)
# # newFile.Add(h_ftk_refit_recoMatch_track_d0_stack)
# # newFile.Add(h_ftk_refit_recoMatch_track_z0_stack)

# # newFile.Add(h_reco_accepted_hitPattern_EndCap_stack)
# # newFile.Add(h_ftk_accepted_hitPattern_EndCap_stack)
# # newFile.Add(h_ftk_refit_accepted_hitPattern_EndCap_stack)

# # newFile.Add(h_reco_accepted_hitPattern_Barrel_stack)
# # newFile.Add(h_ftk_accepted_hitPattern_Barrel_stack)
# # newFile.Add(h_ftk_refit_accepted_hitPattern_Barrel_stack)

# # newFile.Add(h_reco_accepted_hitPattern_stack)
# # newFile.Add(h_ftk_accepted_hitPattern_stack)
# # newFile.Add(h_ftk_refit_accepted_hitPattern_stack)
# # raw_input("press enter to quit")
# newFile.Write()
# newFile.Close()

print("Creating tempDir")
os.makedirs("tempDir")
os.chdir("tempDir")
''
print("Saving histograms")
# def SaveStackedHistogram(histo):
# 	canvasname = str(histo)
# 	c1 = TCanvas(canvasname, canvasname)
# 	histo.Draw("nostack")
# 	histoname = str(histo)+".pdf"
# 	print(histoname)
# 	c1.SaveAs(histoname)
if isData == False:
	truth_pt_stack = TCanvas("h_truth_pt_stack", ""); h_truth_pt_stack.Draw("nostack"); truth_pt_stack.SaveAs("h_truth_pt_stack.pdf")
	truth_eta_stack = TCanvas("h_truth_eta_stack", ""); h_truth_eta_stack.Draw("nostack"); truth_eta_stack.SaveAs("h_truth_eta_stack.pdf")
	truth_phi_stack = TCanvas("h_truth_phi_stack", ""); h_truth_phi_stack.Draw("nostack"); truth_phi_stack.SaveAs("h_truth_phi_stack.pdf")
	truth_m_stack = TCanvas("h_truth_m_stack", ""); h_truth_m_stack.Draw("nostack"); truth_m_stack.SaveAs("h_truth_m_stack.pdf")
	truth_d0_stack = TCanvas("h_truth_d0_stack", ""); h_truth_d0_stack.Draw("nostack"); truth_d0_stack.SaveAs("h_truth_d0_stack.pdf")
	truth_z0_stack = TCanvas("h_truth_z0_stack", ""); h_truth_z0_stack.Draw("nostack"); truth_z0_stack.SaveAs("h_truth_z0_stack.pdf")
	truth_qop_stack = TCanvas("h_truth_qop_stack", ""); h_truth_qop_stack.Draw("nostack"); truth_qop_stack.SaveAs("h_truth_qop_stack.pdf")
	truth_charge_stack = TCanvas("h_truth_charge_stack", ""); h_truth_charge_stack.Draw("nostack"); truth_charge_stack.SaveAs("h_truth_charge_stack.pdf")

reco_accepted_pt_stack = TCanvas("h_reco_accepted_pt_stack", ""); h_reco_accepted_pt_stack.Draw("nostack"); h_reco_accepted_pt_stack.GetXaxis().SetTitle("p_{T}"); h_reco_accepted_pt_stack.GetYaxis().SetTitle("Events"); #reco_accepted_pt_stack.BuildLegend(); 
reco_accepted_pt_stack.SaveAs("h_reco_accepted_pt_stack.pdf")
reco_accepted_eta_stack = TCanvas("h_reco_accepted_eta_stack", ""); h_reco_accepted_eta_stack.Draw("nostack"); h_reco_accepted_eta_stack.GetXaxis().SetTitle("#eta");  h_reco_accepted_eta_stack.GetYaxis().SetTitle("Events"); #reco_accepted_eta_stack.BuildLegend(); 
reco_accepted_eta_stack.SaveAs("h_reco_accepted_eta_stack.pdf")
reco_accepted_phi_stack = TCanvas("h_reco_accepted_phi_stack", ""); h_reco_accepted_phi_stack.Draw("nostack"); h_reco_accepted_phi_stack.GetXaxis().SetTitle("#phi");  h_reco_accepted_phi_stack.GetYaxis().SetTitle("Events"); #reco_accepted_phi_stack.BuildLegend(); 
reco_accepted_phi_stack.SaveAs("h_reco_accepted_phi_stack.pdf")
# reco_accepted_m_stack = TCanvas("h_reco_accepted_m_stack", ""); h_reco_accepted_m_stack.Draw("nostack"); reco_accepted_m_stack.SaveAs("h_reco_accepted_m_stack.pdf")
reco_accepted_d0_stack = TCanvas("h_reco_accepted_d0_stack", ""); h_reco_accepted_d0_stack.Draw("nostack"); h_reco_accepted_d0_stack.GetXaxis().SetTitle("d0 [mm]");  h_reco_accepted_d0_stack.GetYaxis().SetTitle("Events"); #reco_accepted_d0_stack.BuildLegend(); 
reco_accepted_d0_stack.SaveAs("h_reco_accepted_d0_stack.pdf")
reco_accepted_z0_stack = TCanvas("h_reco_accepted_z0_stack", ""); h_reco_accepted_z0_stack.Draw("nostack"); h_reco_accepted_z0_stack.GetXaxis().SetTitle("z0 [mm]");  h_reco_accepted_z0_stack.GetYaxis().SetTitle("Events"); #reco_accepted_z0_stack.BuildLegend(); 
reco_accepted_z0_stack.SaveAs("h_reco_accepted_z0_stack.pdf")
reco_accepted_qop_stack = TCanvas("h_reco_accepted_qop_stack", ""); h_reco_accepted_qop_stack.Draw("nostack"); h_reco_accepted_qop_stack.GetXaxis().SetTitle("qop");  h_reco_accepted_qop_stack.GetYaxis().SetTitle("Events"); #reco_accepted_qop_stack.BuildLegend(); 
reco_accepted_qop_stack.SaveAs("h_reco_accepted_qop_stack.pdf")
reco_accepted_charge_stack = TCanvas("h_reco_accepted_charge_stack", ""); h_reco_accepted_charge_stack.Draw("nostack"); h_reco_accepted_charge_stack.GetXaxis().SetTitle("charge"); h_reco_accepted_charge_stack.GetYaxis().SetTitle("Events"); #reco_accepted_charge_stack.BuildLegend(); 
reco_accepted_charge_stack.SaveAs("h_reco_accepted_charge_stack.pdf")
reco_accepted_chi2_stack = TCanvas("h_reco_accepted_chi2_stack", ""); h_reco_accepted_chi2_stack.Draw("nostack"); h_reco_accepted_chi2_stack.GetXaxis().SetTitle("#Chi^{2}");  h_reco_accepted_chi2_stack.GetYaxis().SetTitle("Events"); #reco_accepted_chi2_stack.BuildLegend(); 
reco_accepted_chi2_stack.SaveAs("h_reco_accepted_chi2_stack.pdf")

reco_inclusive_pt_stack = TCanvas("h_reco_inclusive_pt_stack", ""); h_reco_inclusive_pt_stack.Draw("nostack"); h_reco_inclusive_pt_stack.GetXaxis().SetTitle("p_{T}"); h_reco_inclusive_pt_stack.GetYaxis().SetTitle("Events"); #reco_inclusive_pt_stack.BuildLegend(); 
reco_inclusive_pt_stack.SaveAs("h_reco_inclusive_pt_stack.pdf")
reco_inclusive_eta_stack = TCanvas("h_reco_inclusive_eta_stack", ""); h_reco_inclusive_eta_stack.Draw("nostack"); h_reco_inclusive_eta_stack.GetXaxis().SetTitle("#eta");  h_reco_inclusive_eta_stack.GetYaxis().SetTitle("Events"); #reco_inclusive_eta_stack.BuildLegend(); 
reco_inclusive_eta_stack.SaveAs("h_reco_inclusive_eta_stack.pdf")
reco_inclusive_phi_stack = TCanvas("h_reco_inclusive_phi_stack", ""); h_reco_inclusive_phi_stack.Draw("nostack"); h_reco_inclusive_phi_stack.GetXaxis().SetTitle("#phi");  h_reco_inclusive_phi_stack.GetYaxis().SetTitle("Events");# reco_inclusive_phi_stack.BuildLegend(); 
reco_inclusive_phi_stack.SaveAs("h_reco_inclusive_phi_stack.pdf")
# reco_inclusive_m_stack = TCanvas("h_reco_inclusive_m_stack", ""); h_reco_inclusive_m_stack.Draw("nostack"); reco_inclusive_m_stack.SaveAs("h_reco_inclusive_m_stack.pdf")
reco_inclusive_d0_stack = TCanvas("h_reco_inclusive_d0_stack", ""); h_reco_inclusive_d0_stack.Draw("nostack"); h_reco_inclusive_d0_stack.GetXaxis().SetTitle("d0 [mm]");  h_reco_inclusive_d0_stack.GetYaxis().SetTitle("Events");# reco_inclusive_d0_stack.BuildLegend(); 
reco_inclusive_d0_stack.SaveAs("h_reco_inclusive_d0_stack.pdf")
reco_inclusive_z0_stack = TCanvas("h_reco_inclusive_z0_stack", ""); h_reco_inclusive_z0_stack.Draw("nostack"); h_reco_inclusive_z0_stack.GetXaxis().SetTitle("z0 [mm]");  h_reco_inclusive_z0_stack.GetYaxis().SetTitle("Events"); #reco_inclusive_z0_stack.BuildLegend(); 
reco_inclusive_z0_stack.SaveAs("h_reco_inclusive_z0_stack.pdf")
reco_inclusive_qop_stack = TCanvas("h_reco_inclusive_qop_stack", ""); h_reco_inclusive_qop_stack.Draw("nostack"); #reco_inclusive_qop_stack.BuildLegend();

reco_inclusive_qop_stack.SaveAs("h_reco_inclusive_qop_stack.pdf")
reco_inclusive_charge_stack = TCanvas("h_reco_inclusive_charge_stack", ""); h_reco_inclusive_charge_stack.Draw("nostack"); #reco_inclusive_charge_stack.BuildLegend(); 
reco_inclusive_charge_stack.SaveAs("h_reco_inclusive_charge_stack.pdf")
reco_inclusive_chi2_stack = TCanvas("h_reco_inclusive_chi2_stack", ""); h_reco_inclusive_chi2_stack.Draw("nostack"); h_reco_inclusive_chi2_stack.GetXaxis().SetTitle("#Chi^{2}");  h_reco_inclusive_chi2_stack.GetYaxis().SetTitle("Events"); #reco_inclusive_chi2_stack.BuildLegend(); 
reco_inclusive_chi2_stack.SaveAs("h_reco_inclusive_chi2_stack.pdf")

ftk_accepted_pt_stack = TCanvas("h_ftk_accepted_pt_stack", ""); h_ftk_accepted_pt_stack.Draw("nostack"); h_ftk_accepted_pt_stack.GetXaxis().SetTitle("p_{T}"); h_ftk_accepted_pt_stack.GetYaxis().SetTitle("Events"); #ftk_accepted_pt_stack.BuildLegend(); 
ftk_accepted_pt_stack.SaveAs("h_ftk_accepted_pt_stack.pdf")
ftk_accepted_eta_stack = TCanvas("h_ftk_accepted_eta_stack", "");h_ftk_accepted_eta_stack.Draw("nostack");  h_ftk_accepted_eta_stack.GetXaxis().SetTitle("#eta");  h_ftk_accepted_eta_stack.GetYaxis().SetTitle("Events"); #ftk_accepted_eta_stack.BuildLegend();
ftk_accepted_eta_stack.SaveAs("h_ftk_accepted_eta_stack.pdf")
ftk_accepted_phi_stack = TCanvas("h_ftk_accepted_phi_stack", ""); h_ftk_accepted_phi_stack.Draw("nostack"); h_ftk_accepted_phi_stack.GetXaxis().SetTitle("#phi");  h_ftk_accepted_phi_stack.GetYaxis().SetTitle("Events"); #ftk_accepted_phi_stack.BuildLegend(); 
ftk_accepted_phi_stack.SaveAs("h_ftk_accepted_phi_stack.pdf")
# ftk_accepted_m_stack = TCanvas("h_ftk_accepted_m_stack", ""); h_ftk_accepted_m_stack.Draw("nostack"); ftk_accepted_m_stack.SaveAs("h_ftk_accepted_m_stack.pdf")
ftk_accepted_d0_stack = TCanvas("h_ftk_accepted_d0_stack", ""); h_ftk_accepted_d0_stack.Draw("nostack"); h_ftk_accepted_d0_stack.GetXaxis().SetTitle("d0 [mm]");  h_ftk_accepted_d0_stack.GetYaxis().SetTitle("Events"); #ftk_accepted_d0_stack.BuildLegend(); 
ftk_accepted_d0_stack.SaveAs("h_ftk_accepted_d0_stack.pdf")
ftk_accepted_corrected_d0_stack = TCanvas("h_ftk_accepted_corrected_d0_stack", ""); h_ftk_accepted_corrected_d0_stack.Draw("nostack"); #ftk_accepted_corrected_d0_stack.BuildLegend(); 
ftk_accepted_corrected_d0_stack.SaveAs("h_ftk_accepted_corrected_d0_stack.pdf")
ftk_accepted_z0_stack = TCanvas("h_ftk_accepted_z0_stack", ""); h_ftk_accepted_z0_stack.Draw("nostack"); h_ftk_accepted_z0_stack.GetXaxis().SetTitle("z0 [mm]");  h_ftk_accepted_z0_stack.GetYaxis().SetTitle("Events"); #ftk_accepted_z0_stack.BuildLegend(); 
ftk_accepted_z0_stack.SaveAs("h_ftk_accepted_z0_stack.pdf")
ftk_accepted_qop_stack = TCanvas("h_ftk_accepted_qop_stack", ""); h_ftk_accepted_qop_stack.Draw("nostack"); #ftk_accepted_qop_stack.BuildLegend(); 
ftk_accepted_qop_stack.SaveAs("h_ftk_accepted_qop_stack.pdf")
ftk_accepted_charge_stack = TCanvas("h_ftk_accepted_charge_stack", ""); h_ftk_accepted_charge_stack.Draw("nostack"); #ftk_accepted_charge_stack.BuildLegend(); 
ftk_accepted_charge_stack.SaveAs("h_ftk_accepted_charge_stack.pdf")
ftk_accepted_chi2_stack = TCanvas("h_ftk_accepted_chi2_stack", ""); h_ftk_accepted_chi2_stack.Draw("nostack"); h_ftk_accepted_chi2_stack.GetXaxis().SetTitle("#Chi^{2}");  h_ftk_accepted_chi2_stack.GetYaxis().SetTitle("Events"); #ftk_accepted_chi2_stack.BuildLegend(); 
ftk_accepted_chi2_stack.SaveAs("h_ftk_accepted_chi2_stack.pdf")

ftk_inclusive_pt_stack = TCanvas("h_ftk_inclusive_pt_stack", ""); h_ftk_inclusive_pt_stack.Draw("nostack"); h_ftk_inclusive_pt_stack.GetXaxis().SetTitle("p_{T}"); h_ftk_inclusive_pt_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_inclusive_pt_stack.SaveAs("h_ftk_inclusive_pt_stack.pdf")
ftk_inclusive_eta_stack = TCanvas("h_ftk_inclusive_eta_stack", ""); h_ftk_inclusive_eta_stack.Draw("nostack"); h_ftk_inclusive_eta_stack.GetXaxis().SetTitle("#eta");  h_ftk_inclusive_eta_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_inclusive_eta_stack.SaveAs("h_ftk_inclusive_eta_stack.pdf")
ftk_inclusive_phi_stack = TCanvas("h_ftk_inclusive_phi_stack", ""); h_ftk_inclusive_phi_stack.Draw("nostack"); h_ftk_inclusive_phi_stack.GetXaxis().SetTitle("#phi");  h_ftk_inclusive_phi_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_inclusive_phi_stack.SaveAs("h_ftk_inclusive_phi_stack.pdf")
# ftk_inclusive_m_stack = TCanvas("h_ftk_inclusive_m_stack", ""); h_ftk_inclusive_m_stack.Draw("nostack"); ftk_inclusive_m_stack.SaveAs("h_ftk_inclusive_m_stack.pdf")
ftk_inclusive_d0_stack = TCanvas("h_ftk_inclusive_d0_stack", ""); h_ftk_inclusive_d0_stack.Draw("nostack"); h_ftk_inclusive_d0_stack.GetXaxis().SetTitle("d0 [mm]");  h_ftk_inclusive_d0_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_inclusive_d0_stack.SaveAs("h_ftk_inclusive_d0_stack.pdf")
ftk_inclusive_corrected_d0_stack = TCanvas("h_ftk_inclusive_corrected_d0_stack", ""); h_ftk_inclusive_corrected_d0_stack.Draw("nostack"); h_ftk_inclusive_corrected_d0_stack.GetXaxis().SetTitle("d0 [mm]");  h_ftk_inclusive_corrected_d0_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_inclusive_corrected_d0_stack.SaveAs("h_ftk_inclusive_corrected_d0_stack.pdf")
ftk_inclusive_z0_stack = TCanvas("h_ftk_inclusive_z0_stack", ""); h_ftk_inclusive_z0_stack.Draw("nostack"); h_ftk_inclusive_z0_stack.GetXaxis().SetTitle("z0 [mm]");  h_ftk_inclusive_z0_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_inclusive_z0_stack.SaveAs("h_ftk_inclusive_z0_stack.pdf")
ftk_inclusive_qop_stack = TCanvas("h_ftk_inclusive_qop_stack", ""); h_ftk_inclusive_qop_stack.Draw("nostack"); #.BuildLegend(); 
ftk_inclusive_qop_stack.SaveAs("h_ftk_inclusive_qop_stack.pdf")
ftk_inclusive_charge_stack = TCanvas("h_ftk_inclusive_charge_stack", ""); h_ftk_inclusive_charge_stack.Draw("nostack"); #.BuildLegend(); 
ftk_inclusive_charge_stack.SaveAs("h_ftk_inclusive_charge_stack.pdf")
ftk_inclusive_chi2_stack = TCanvas("h_ftk_inclusive_chi2_stack", ""); h_ftk_inclusive_chi2_stack.Draw("nostack"); h_ftk_inclusive_chi2_stack.GetXaxis().SetTitle("#Chi^{2}");  h_ftk_inclusive_chi2_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_inclusive_chi2_stack.SaveAs("h_ftk_inclusive_chi2_stack.pdf")

ftk_refit_accepted_pt_stack = TCanvas("h_ftk_refit_accepted_pt_stack", ""); h_ftk_refit_accepted_pt_stack.Draw("nostack"); h_ftk_refit_accepted_pt_stack.GetXaxis().SetTitle("p_{T}"); h_ftk_refit_accepted_pt_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_refit_accepted_pt_stack.SaveAs("h_ftk_refit_accepted_pt_stack.pdf")
ftk_refit_accepted_eta_stack = TCanvas("h_ftk_refit_accepted_eta_stack", ""); h_ftk_refit_accepted_eta_stack.Draw("nostack"); h_ftk_refit_accepted_eta_stack.GetXaxis().SetTitle("#eta");  h_ftk_refit_accepted_eta_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_refit_accepted_eta_stack.SaveAs("h_ftk_refit_accepted_eta_stack.pdf")
ftk_refit_accepted_phi_stack = TCanvas("h_ftk_refit_accepted_phi_stack", ""); h_ftk_refit_accepted_phi_stack.Draw("nostack"); h_ftk_refit_accepted_phi_stack.GetXaxis().SetTitle("#phi");  h_ftk_refit_accepted_phi_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_refit_accepted_phi_stack.SaveAs("h_ftk_refit_accepted_phi_stack.pdf")
# ftk_refit_accepted_m_stack = TCanvas("h_ftk_refit_accepted_m_stack", ""); h_ftk_refit_accepted_m_stack.Draw("nostack"); ftk_refit_accepted_m_stack.SaveAs("h_ftk_refit_accepted_m_stack.pdf")
ftk_refit_accepted_d0_stack = TCanvas("h_ftk_refit_accepted_d0_stack", ""); h_ftk_refit_accepted_d0_stack.Draw("nostack"); h_ftk_refit_accepted_d0_stack.GetXaxis().SetTitle("d0 [mm]");  h_ftk_refit_accepted_d0_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_refit_accepted_d0_stack.SaveAs("h_ftk_refit_accepted_d0_stack.pdf")
ftk_refit_accepted_z0_stack = TCanvas("h_ftk_refit_accepted_z0_stack", ""); h_ftk_refit_accepted_z0_stack.Draw("nostack"); h_ftk_refit_accepted_z0_stack.GetXaxis().SetTitle("z0 [mm]");  h_ftk_refit_accepted_z0_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_refit_accepted_z0_stack.SaveAs("h_ftk_refit_accepted_z0_stack.pdf")
ftk_refit_accepted_qop_stack = TCanvas("h_ftk_refit_accepted_qop_stack", ""); h_ftk_refit_accepted_qop_stack.Draw("nostack"); #.BuildLegend(); 
ftk_refit_accepted_qop_stack.SaveAs("h_ftk_refit_accepted_qop_stack.pdf")
ftk_refit_accepted_charge_stack = TCanvas("h_ftk_refit_accepted_charge_stack", ""); h_ftk_refit_accepted_charge_stack.Draw("nostack"); #.BuildLegend(); 
ftk_refit_accepted_charge_stack.SaveAs("h_ftk_refit_accepted_charge_stack.pdf")
ftk_refit_accepted_chi2_stack = TCanvas("h_ftk_refit_accepted_chi2_stack", ""); h_ftk_refit_accepted_chi2_stack.Draw("nostack"); h_ftk_refit_accepted_chi2_stack.GetXaxis().SetTitle("#Chi^{2}");  h_ftk_refit_accepted_chi2_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_refit_accepted_chi2_stack.SaveAs("h_ftk_refit_accepted_chi2_stack.pdf")

ftk_refit_inclusive_pt_stack = TCanvas("h_ftk_refit_inclusive_pt_stack", ""); h_ftk_refit_inclusive_pt_stack.Draw("nostack"); h_ftk_refit_inclusive_pt_stack.GetXaxis().SetTitle("p_{T}"); h_ftk_refit_inclusive_pt_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_refit_inclusive_pt_stack.SaveAs("h_ftk_refit_inclusive_pt_stack.pdf")
ftk_refit_inclusive_eta_stack = TCanvas("h_ftk_refit_inclusive_eta_stack", ""); h_ftk_refit_inclusive_eta_stack.Draw("nostack"); h_ftk_refit_inclusive_eta_stack.GetXaxis().SetTitle("#eta");  h_ftk_refit_inclusive_eta_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_refit_inclusive_eta_stack.SaveAs("h_ftk_refit_inclusive_eta_stack.pdf")
ftk_refit_inclusive_phi_stack = TCanvas("h_ftk_refit_inclusive_phi_stack", ""); h_ftk_refit_inclusive_phi_stack.Draw("nostack"); h_ftk_refit_inclusive_phi_stack.GetXaxis().SetTitle("#phi");  h_ftk_refit_inclusive_phi_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_refit_inclusive_phi_stack.SaveAs("h_ftk_refit_inclusive_phi_stack.pdf")
# ftk_refit_inclusive_m_stack = TCanvas("h_ftk_refit_inclusive_m_stack", ""); h_ftk_refit_inclusive_m_stack.Draw("nostack"); ftk_refit_inclusive_m_stack.SaveAs("h_ftk_refit_inclusive_m_stack.pdf")
ftk_refit_inclusive_d0_stack = TCanvas("h_ftk_refit_inclusive_d0_stack", ""); h_ftk_refit_inclusive_d0_stack.Draw("nostack"); h_ftk_refit_inclusive_d0_stack.GetXaxis().SetTitle("d0 [mm]");  h_ftk_refit_inclusive_d0_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_refit_inclusive_d0_stack.SaveAs("h_ftk_refit_inclusive_d0_stack.pdf")
ftk_refit_inclusive_z0_stack = TCanvas("h_ftk_refit_inclusive_z0_stack", ""); h_ftk_refit_inclusive_z0_stack.Draw("nostack"); h_ftk_refit_inclusive_z0_stack.GetXaxis().SetTitle("z0 [mm]");  h_ftk_refit_inclusive_z0_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_refit_inclusive_z0_stack.SaveAs("h_ftk_refit_inclusive_z0_stack.pdf")
ftk_refit_inclusive_qop_stack = TCanvas("h_ftk_refit_inclusive_qop_stack", ""); h_ftk_refit_inclusive_qop_stack.Draw("nostack"); #.BuildLegend(); 
ftk_refit_inclusive_qop_stack.SaveAs("h_ftk_refit_inclusive_qop_stack.pdf")
ftk_refit_inclusive_charge_stack = TCanvas("h_ftk_refit_inclusive_charge_stack", ""); h_ftk_refit_inclusive_charge_stack.Draw("nostack"); #.BuildLegend(); 
ftk_refit_inclusive_charge_stack.SaveAs("h_ftk_refit_inclusive_charge_stack.pdf")
ftk_refit_inclusive_chi2_stack = TCanvas("h_ftk_refit_inclusive_chi2_stack", ""); h_ftk_refit_inclusive_chi2_stack.Draw("nostack"); h_ftk_refit_inclusive_chi2_stack.GetXaxis().SetTitle("#Chi^{2}");  h_ftk_refit_inclusive_chi2_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
ftk_refit_inclusive_chi2_stack.SaveAs("h_ftk_refit_inclusive_chi2_stack.pdf")

if isData == False:
	reco_truthMatched_pt_bias_stack = TCanvas("h_reco_truthMatched_pt_bias_stack", ""); h_reco_truthMatched_pt_bias_stack.Draw("nostack"); h_reco_truthMatched_pt_bias_stack.GetXaxis().SetTitle("Reco p_{T} - Truth P_{T} [GeV]"); #.BuildLegend(); 
	reco_truthMatched_pt_bias_stack.SaveAs("h_reco_truthMatched_pt_bias_stack.pdf")
	reco_truthMatched_eta_bias_stack = TCanvas("h_reco_truthMatched_eta_bias_stack", ""); h_reco_truthMatched_eta_bias_stack.Draw("nostack"); h_reco_truthMatched_eta_bias_stack.GetXaxis().SetTitle("Reco #eta - Truth #eta"); #.BuildLegend(); 
	reco_truthMatched_eta_bias_stack.SaveAs("h_reco_truthMatched_eta_bias_stack.pdf")
	reco_truthMatched_phi_bias_stack = TCanvas("h_reco_truthMatched_phi_bias_stack", ""); h_reco_truthMatched_phi_bias_stack.Draw("nostack"); h_reco_truthMatched_phi_bias_stack.GetXaxis().SetTitle("Reco #phi - Truth #phi"); #.BuildLegend(); 
	reco_truthMatched_phi_bias_stack.SaveAs("h_reco_truthMatched_phi_bias_stack.pdf")
	reco_truthMatched_d0_bias_stack = TCanvas("h_reco_truthMatched_d0_bias_stack", ""); h_reco_truthMatched_d0_bias_stack.Draw("nostack"); h_reco_truthMatched_d0_bias_stack.GetXaxis().SetTitle("Reco d0 - Truth d0 [mm]"); #.BuildLegend(); 
	reco_truthMatched_d0_bias_stack.SaveAs("h_reco_truthMatched_d0_bias_stack.pdf")

	truth_recoMatch_track_eta_stack = TCanvas("h_truth_recoMatch_track_eta_stack", ""); h_truth_recoMatch_track_eta_stack.Draw("nostack"); h_truth_recoMatch_track_eta_stack.GetXaxis().SetTitle("#eta"); h_truth_recoMatch_track_eta_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
	truth_recoMatch_track_eta_stack.SaveAs("h_truth_recoMatch_track_eta_stack.pdf")
	truth_recoMatch_track_phi_stack = TCanvas("h_truth_recoMatch_track_phi_stack", ""); h_truth_recoMatch_track_phi_stack.Draw("nostack"); h_truth_recoMatch_track_phi_stack.GetXaxis().SetTitle("#phi"); h_truth_recoMatch_track_phi_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
	truth_recoMatch_track_phi_stack.SaveAs("h_truth_recoMatch_track_phi_stack.pdf")
	reco_truthMatch_track_eta_stack = TCanvas("h_reco_truthMatch_track_eta_stack", ""); h_reco_truthMatch_track_eta_stack.Draw("nostack"); h_reco_truthMatch_track_eta_stack.GetXaxis().SetTitle("#eta"); h_reco_truthMatch_track_eta_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
	reco_truthMatch_track_eta_stack.SaveAs("h_reco_truthMatch_track_eta_stack.pdf")
	reco_truthMatch_track_phi_stack = TCanvas("h_reco_truthMatch_track_phi_stack", ""); h_reco_truthMatch_track_phi_stack.Draw("nostack"); h_reco_truthMatch_track_phi_stack.GetXaxis().SetTitle("#phi"); h_reco_truthMatch_track_phi_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
	reco_truthMatch_track_phi_stack.SaveAs("h_reco_truthMatch_track_phi_stack.pdf")
	truth_recoMatch_track_pt_stack = TCanvas("h_truth_recoMatch_track_pt_stack", ""); h_truth_recoMatch_track_pt_stack.Draw("nostack");h_truth_recoMatch_track_pt_stack.GetXaxis().SetTitle("p_{T} [GeV]"); h_truth_recoMatch_track_pt_stack.GetYaxis().SetTitle("Events");  #.BuildLegend(); 
	truth_recoMatch_track_pt_stack.SaveAs("h_truth_recoMatch_track_pt_stack.pdf")
	truth_recoMatch_track_d0_stack = TCanvas("h_truth_recoMatch_track_d0_stack", ""); h_truth_recoMatch_track_d0_stack.Draw("nostack");h_truth_recoMatch_track_d0_stack.GetXaxis().SetTitle("d0 [mm]"); h_truth_recoMatch_track_d0_stack.GetYaxis().SetTitle("Events");  #.BuildLegend(); 
	truth_recoMatch_track_d0_stack.SaveAs("h_truth_recoMatch_track_d0_stack.pdf")
	truth_recoMatch_track_z0_stack = TCanvas("h_truth_recoMatch_track_z0_stack", ""); h_truth_recoMatch_track_z0_stack.Draw("nostack");h_truth_recoMatch_track_z0_stack.GetXaxis().SetTitle("z0 [mm]"); h_truth_recoMatch_track_z0_stack.GetYaxis().SetTitle("Events");  #.BuildLegend(); 
	truth_recoMatch_track_z0_stack.SaveAs("h_truth_recoMatch_track_z0_stack.pdf")

	truth_ftk_Matched_pt_bias_stack = TCanvas("h_truth_ftk_Matched_pt_bias_stack", ""); h_truth_ftk_Matched_pt_bias_stack.Draw("nostack"); h_truth_ftk_Matched_pt_bias_stack.GetXaxis().SetTitle("FTK p_{T} - Truth P_{T} [GeV]"); #.BuildLegend(); 
	truth_ftk_Matched_pt_bias_stack.SaveAs("h_truth_ftk_Matched_pt_bias_stack.pdf")
	truth_ftk_Matched_eta_bias_stack = TCanvas("h_truth_ftk_Matched_eta_bias_stack", ""); h_truth_ftk_Matched_eta_bias_stack.Draw("nostack"); h_truth_ftk_Matched_eta_bias_stack.GetXaxis().SetTitle("FTK #eta - Truth #eta"); #.BuildLegend(); 
	truth_ftk_Matched_eta_bias_stack.SaveAs("h_truth_ftk_Matched_eta_bias_stack.pdf")
	truth_ftk_Matched_phi_bias_stack = TCanvas("h_truth_ftk_Matched_phi_bias_stack", ""); h_truth_ftk_Matched_phi_bias_stack.Draw("nostack"); h_truth_ftk_Matched_phi_bias_stack.GetXaxis().SetTitle("FTK #phi - Truth #phi"); #.BuildLegend(); 
	truth_ftk_Matched_phi_bias_stack.SaveAs("h_truth_ftk_Matched_phi_bias_stack.pdf")
	truth_ftk_Matched_d0_bias_stack = TCanvas("h_truth_ftk_Matched_d0_bias_stack", ""); h_truth_ftk_Matched_d0_bias_stack.Draw("nostack"); h_truth_ftk_Matched_d0_bias_stack.GetXaxis().SetTitle("FTK d0 - Truth d0 [mm]"); #.BuildLegend(); 
	truth_ftk_Matched_d0_bias_stack.SaveAs("h_truth_ftk_Matched_d0_bias_stack.pdf")
	truth_ftk_Matched_corrected_d0_bias_stack = TCanvas("h_truth_ftk_Matched_corrected_d0_bias_stack", ""); h_truth_ftk_Matched_corrected_d0_bias_stack.Draw("nostack"); h_truth_ftk_Matched_corrected_d0_bias_stack.GetXaxis().SetTitle("FTK d0 - Truth d0 [mm]"); #.BuildLegend(); 
	truth_ftk_Matched_corrected_d0_bias_stack.SaveAs("h_truth_ftk_Matched_corrected_d0_bias_stack.pdf")

	ftk_truthMatch_track_eta_stack = TCanvas("h_ftk_truthMatch_track_eta_stack", ""); h_ftk_truthMatch_track_eta_stack.Draw("nostack"); h_ftk_truthMatch_track_eta_stack.GetXaxis().SetTitle("#eta"); h_ftk_truthMatch_track_eta_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
	ftk_truthMatch_track_eta_stack.SaveAs("h_ftk_truthMatch_track_eta_stack.pdf")
	ftk_truthMatch_track_phi_stack = TCanvas("h_ftk_truthMatch_track_phi_stack", ""); h_ftk_truthMatch_track_phi_stack.Draw("nostack"); h_ftk_truthMatch_track_phi_stack.GetXaxis().SetTitle("#phi"); h_ftk_truthMatch_track_phi_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
	ftk_truthMatch_track_phi_stack.SaveAs("h_ftk_truthMatch_track_phi_stack.pdf")
	truth_ftkMatch_track_eta_stack = TCanvas("h_truth_ftkMatch_track_eta_stack", ""); h_truth_ftkMatch_track_eta_stack.Draw("nostack"); h_truth_ftkMatch_track_eta_stack.GetXaxis().SetTitle("#eta"); h_truth_ftkMatch_track_eta_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
	truth_ftkMatch_track_eta_stack.SaveAs("h_truth_ftkMatch_track_eta_stack.pdf")
	truth_ftkMatch_track_phi_stack = TCanvas("h_truth_ftkMatch_track_phi_stack", ""); h_truth_ftkMatch_track_phi_stack.Draw("nostack"); h_truth_ftkMatch_track_phi_stack.GetXaxis().SetTitle("#phi"); h_truth_ftkMatch_track_phi_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
	truth_ftkMatch_track_phi_stack.SaveAs("h_truth_ftkMatch_track_phi_stack.pdf")
	ftk_truthMatch_track_pt_stack = TCanvas("h_ftk_truthMatch_track_pt_stack", ""); h_ftk_truthMatch_track_pt_stack.Draw("nostack"); h_ftk_truthMatch_track_pt_stack.GetXaxis().SetTitle("p_{T} [GeV]"); h_ftk_truthMatch_track_pt_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
	ftk_truthMatch_track_pt_stack.SaveAs("h_ftk_truthMatch_track_pt_stack.pdf")
	ftk_truthMatch_track_d0_stack = TCanvas("h_ftk_truthMatch_track_d0_stack", ""); h_ftk_truthMatch_track_d0_stack.Draw("nostack"); h_ftk_truthMatch_track_d0_stack.GetXaxis().SetTitle("d0 [mm]"); h_ftk_truthMatch_track_d0_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
	ftk_truthMatch_track_d0_stack.SaveAs("h_ftk_truthMatch_track_d0_stack.pdf")
	ftk_truthMatch_track_z0_stack = TCanvas("h_ftk_truthMatch_track_z0_stack", ""); h_ftk_truthMatch_track_z0_stack.Draw("nostack"); h_ftk_truthMatch_track_z0_stack.GetXaxis().SetTitle("z0 [mm]"); h_ftk_truthMatch_track_z0_stack.GetYaxis().SetTitle("Events"); #.BuildLegend(); 
	ftk_truthMatch_track_z0_stack.SaveAs("h_ftk_truthMatch_track_z0_stack.pdf")

	truth_ftk_refitMatched_pt_bias_stack = TCanvas("h_truth_ftk_refitMatched_pt_bias_stack", ""); h_truth_ftk_refitMatched_pt_bias_stack.Draw("nostack"); h_truth_ftk_refitMatched_pt_bias_stack.GetXaxis().SetTitle("FTK refit p_{T} - Truth P_{T} [GeV]"); #.BuildLegend(); 
	truth_ftk_refitMatched_pt_bias_stack.SaveAs("h_truth_ftk_refitMatched_pt_bias_stack.pdf")
	truth_ftk_refitMatched_eta_bias_stack = TCanvas("h_truth_ftk_refitMatched_eta_bias_stack", ""); h_truth_ftk_refitMatched_eta_bias_stack.Draw("nostack"); h_truth_ftk_refitMatched_eta_bias_stack.GetXaxis().SetTitle("FTK refit #eta - Truth #eta"); #.BuildLegend(); 
	truth_ftk_refitMatched_eta_bias_stack.SaveAs("h_truth_ftk_refitMatched_eta_bias_stack.pdf")
	truth_ftk_refitMatched_phi_bias_stack = TCanvas("h_truth_ftk_refitMatched_phi_bias_stack", ""); h_truth_ftk_refitMatched_phi_bias_stack.Draw("nostack"); h_truth_ftk_refitMatched_phi_bias_stack.GetXaxis().SetTitle("FTK refit #phi - Truth #phi"); #.BuildLegend(); 
	truth_ftk_refitMatched_phi_bias_stack.SaveAs("h_truth_ftk_refitMatched_phi_bias_stack.pdf")
	truth_ftk_refitMatched_d0_bias_stack = TCanvas("h_truth_ftk_refitMatched_d0_bias_stack", ""); h_truth_ftk_refitMatched_d0_bias_stack.Draw("nostack"); h_truth_ftk_refitMatched_d0_bias_stack.GetXaxis().SetTitle("FTK refit d0 - Truth d0 [mm]"); #.BuildLegend(); 
	truth_ftk_refitMatched_d0_bias_stack.SaveAs("h_truth_ftk_refitMatched_d0_bias_stack.pdf")

	ftk_refit_truthMatch_track_eta_stack = TCanvas("h_ftk_refit_truthMatch_track_eta_stack", ""); h_ftk_refit_truthMatch_track_eta_stack.Draw("nostack"); h_ftk_refit_truthMatch_track_eta_stack.GetXaxis().SetTitle("#eta"); h_ftk_refit_truthMatch_track_eta_stack.GetYaxiso().SetTitle("Events"); ftk_refit_truthMatch_track_eta_stack.SaveAs("h_ftk_refit_truthMatch_track_eta_stack.pdf")
	ftk_refit_truthMatch_track_phi_stack = TCanvas("h_ftk_refit_truthMatch_track_phi_stack", ""); h_ftk_refit_truthMatch_track_phi_stack.Draw("nostack"); h_ftk_refit_truthMatch_track_phi_stack.GetXaxis().SetTitle("#phi"); h_ftk_refit_truthMatch_track_phi_stack.GetYaxiso().SetTitle("Events"); ftk_refit_truthMatch_track_phi_stack.SaveAs("h_ftk_refit_truthMatch_track_phi_stack.pdf")
	truth_ftkrefitMatch_track_eta_stack = TCanvas("h_truth_ftkrefitMatch_track_eta_stack", ""); h_truth_ftkrefitMatch_track_eta_stack.Draw("nostack"); h_truth_ftkrefitMatch_track_eta_stack.GetXaxis().SetTitle("#eta"); h_truth_ftkrefitMatch_track_eta_stack.GetYaxiso().SetTitle("Events"); truth_ftkrefitMatch_track_eta_stack.SaveAs("h_truth_ftkrefitMatch_track_eta_stack.pdf")
	truth_ftkrefitMatch_track_phi_stack = TCanvas("h_truth_ftkrefitMatch_track_phi_stack", ""); h_truth_ftkrefitMatch_track_phi_stack.Draw("nostack"); h_truth_ftkrefitMatch_track_phi_stack.GetXaxis().SetTitle("#phi"); h_truth_ftkrefitMatch_track_phi_stack.GetYaxiso().SetTitle("Events"); truth_ftkrefitMatch_track_phi_stack.SaveAs("h_truth_ftkrefitMatch_track_phi_stack.pdf")
	ftk_refit_truthMatch_track_pt_stack = TCanvas("h_ftk_refit_truthMatch_track_pt_stack", ""); h_ftk_refit_truthMatch_track_pt_stack.Draw("nostack"); h_ftk_refit_truthMatch_track_pt_stack.GetXaxis().SetTitle("p_{T} [GeV]"); h_ftk_refit_truthMatch_track_pt_stack.GetYaxiso().SetTitle("Events"); ftk_refit_truthMatch_track_pt_stack.SaveAs("h_ftk_refit_truthMatch_track_pt_stack.pdf")
	ftk_refit_truthMatch_track_d0_stack = TCanvas("h_ftk_refit_truthMatch_track_d0_stack", ""); h_ftk_refit_truthMatch_track_d0_stack.Draw("nostack"); h_ftk_refit_truthMatch_track_d0_stack.GetXaxis().SetTitle("d0 [mm]"); h_ftk_refit_truthMatch_track_d0_stack.GetYaxiso().SetTitle("Events"); ftk_refit_truthMatch_track_d0_stack.SaveAs("h_ftk_refit_truthMatch_track_d0_stack.pdf")
	ftk_refit_truthMatch_track_z0_stack = TCanvas("h_ftk_refit_truthMatch_track_z0_stack", ""); h_ftk_refit_truthMatch_track_z0_stack.Draw("nostack"); h_ftk_refit_truthMatch_track_z0_stack.GetXaxis().SetTitle("z0 [mm]"); h_ftk_refit_truthMatch_track_z0_stack.GetYaxiso().SetTitle("Events"); ftk_refit_truthMatch_track_z0_stack.SaveAs("h_ftk_refit_truthMatch_track_z0_stack.pdf")

reco_ftkMatched_pt_bias_stack = TCanvas("h_reco_ftkMatched_pt_bias_stack", ""); h_reco_ftkMatched_pt_bias_stack.Draw("nostack"); h_reco_ftkMatched_pt_bias_stack.GetXaxis().SetTitle("FTK p_{T} - Reco p_{T} [GeV]"); reco_ftkMatched_pt_bias_stack.SaveAs("h_reco_ftkMatched_pt_bias_stack.pdf")
reco_ftkMatched_eta_bias_stack = TCanvas("h_reco_ftkMatched_eta_bias_stack", ""); h_reco_ftkMatched_eta_bias_stack.Draw("nostack"); h_reco_ftkMatched_eta_bias_stack.GetXaxis().SetTitle("FTK #eta - Reco #eta"); reco_ftkMatched_eta_bias_stack.SaveAs("h_reco_ftkMatched_eta_bias_stack.pdf")
reco_ftkMatched_phi_bias_stack = TCanvas("h_reco_ftkMatched_phi_bias_stack", ""); h_reco_ftkMatched_phi_bias_stack.Draw("nostack"); h_reco_ftkMatched_phi_bias_stack.GetXaxis().SetTitle("FTK #phi - Reco #phi"); reco_ftkMatched_phi_bias_stack.SaveAs("h_reco_ftkMatched_phi_bias_stack.pdf")
reco_ftkMatched_d0_bias_stack = TCanvas("h_reco_ftkMatched_d0_bias_stack", ""); h_reco_ftkMatched_d0_bias_stack.Draw("nostack"); h_reco_ftkMatched_d0_bias_stack.GetXaxis().SetTitle("FTK d0 - Reco d0 [mm]"); reco_ftkMatched_d0_bias_stack.SaveAs("h_reco_ftkMatched_d0_bias_stack.pdf")
reco_ftkMatched_corrected_d0_bias_stack = TCanvas("h_reco_ftkMatched_corrected_d0_bias_stack", ""); h_reco_ftkMatched_corrected_d0_bias_stack.Draw("nostack"); h_reco_ftkMatched_corrected_d0_bias_stack.GetXaxis().SetTitle("FTK d0 - Reco d0 [mm]"); reco_ftkMatched_corrected_d0_bias_stack.SaveAs("h_reco_ftkMatched_corrected_d0_bias_stack.pdf")

ftk_recoMatch_track_eta_stack = TCanvas("h_ftk_recoMatch_track_eta_stack", ""); h_ftk_recoMatch_track_eta_stack.Draw("nostack"); h_ftk_recoMatch_track_eta_stack.GetXaxis().SetTitle("#eta"); h_ftk_recoMatch_track_eta_stack.GetYaxis().SetTitle("Events"); ftk_recoMatch_track_eta_stack.SaveAs("h_ftk_recoMatch_track_eta_stack.pdf")
ftk_recoMatch_track_phi_stack = TCanvas("h_ftk_recoMatch_track_phi_stack", ""); h_ftk_recoMatch_track_phi_stack.Draw("nostack"); h_ftk_recoMatch_track_phi_stack.GetXaxis().SetTitle("#phi"); h_ftk_recoMatch_track_phi_stack.GetYaxis().SetTitle("Events"); ftk_recoMatch_track_phi_stack.SaveAs("h_ftk_recoMatch_track_phi_stack.pdf")
reco_ftkMatch_track_eta_stack = TCanvas("h_reco_ftkMatch_track_eta_stack", ""); h_reco_ftkMatch_track_eta_stack.Draw("nostack"); h_reco_ftkMatch_track_eta_stack.GetXaxis().SetTitle("#eta"); h_reco_ftkMatch_track_eta_stack.GetYaxis().SetTitle("Events"); reco_ftkMatch_track_eta_stack.SaveAs("h_reco_ftkMatch_track_eta_stack.pdf")
reco_ftkMatch_track_phi_stack = TCanvas("h_reco_ftkMatch_track_phi_stack", ""); h_reco_ftkMatch_track_phi_stack.Draw("nostack"); h_reco_ftkMatch_track_phi_stack.GetXaxis().SetTitle("#phi"); h_reco_ftkMatch_track_phi_stack.GetYaxis().SetTitle("Events"); reco_ftkMatch_track_phi_stack.SaveAs("h_reco_ftkMatch_track_phi_stack.pdf")
ftk_recoMatch_track_pt_stack = TCanvas("h_ftk_recoMatch_track_pt_stack", ""); h_ftk_recoMatch_track_pt_stack.Draw("nostack"); h_ftk_recoMatch_track_pt_stack.GetXaxis().SetTitle("p_{T} [GeV]"); h_ftk_recoMatch_track_pt_stack.GetYaxis().SetTitle("Events"); ftk_recoMatch_track_pt_stack.SaveAs("h_ftk_recoMatch_track_pt_stack.pdf")
ftk_recoMatch_track_d0_stack = TCanvas("h_ftk_recoMatch_track_d0_stack", ""); h_ftk_recoMatch_track_d0_stack.Draw("nostack"); h_ftk_recoMatch_track_d0_stack.GetXaxis().SetTitle("d0 [mm]"); h_ftk_recoMatch_track_d0_stack.GetYaxis().SetTitle("Events"); ftk_recoMatch_track_d0_stack.SaveAs("h_ftk_recoMatch_track_d0_stack.pdf")
# ftk_recoMatch_track_corrected_d0_stack = TCanvas("h_ftk_recoMatch_track_corrected_d0_stack", ""); h_ftk_recoMatch_track_corrected_d0_stack.Draw("nostack"); ftk_recoMatch_track_corrected_d0_stack.SaveAs("h_ftk_recoMatch_track_corrected_d0_stack.pdf")
ftk_recoMatch_track_z0_stack = TCanvas("h_ftk_recoMatch_track_z0_stack", ""); h_ftk_recoMatch_track_z0_stack.Draw("nostack"); h_ftk_recoMatch_track_z0_stack.GetXaxis().SetTitle("z0 [mm]"); h_ftk_recoMatch_track_z0_stack.GetYaxis().SetTitle("Events"); ftk_recoMatch_track_z0_stack.SaveAs("h_ftk_recoMatch_track_z0_stack.pdf")

reco_ftk_refitMatched_pt_bias_stack = TCanvas("h_reco_ftk_refitMatched_pt_bias_stack", ""); h_reco_ftk_refitMatched_pt_bias_stack.Draw("nostack"); h_reco_ftk_refitMatched_pt_bias_stack.GetXaxis().SetTitle("FTK refit p_{T} - Reco p_{T} [GeV]"); reco_ftk_refitMatched_pt_bias_stack.SaveAs("h_reco_ftk_refitMatched_pt_bias_stack.pdf")
reco_ftk_refitMatched_eta_bias_stack = TCanvas("h_reco_ftk_refitMatched_eta_bias_stack", ""); h_reco_ftk_refitMatched_eta_bias_stack.Draw("nostack"); h_reco_ftk_refitMatched_eta_bias_stack.GetXaxis().SetTitle("FTK refit #eta - Reco #eta"); reco_ftk_refitMatched_eta_bias_stack.SaveAs("h_reco_ftk_refitMatched_eta_bias_stack.pdf")
reco_ftk_refitMatched_phi_bias_stack = TCanvas("h_reco_ftk_refitMatched_phi_bias_stack", ""); h_reco_ftk_refitMatched_phi_bias_stack.Draw("nostack"); h_reco_ftk_refitMatched_phi_bias_stack.GetXaxis().SetTitle("FTK refit #phi - Reco #phi"); reco_ftk_refitMatched_phi_bias_stack.SaveAs("h_reco_ftk_refitMatched_phi_bias_stack.pdf")
reco_ftk_refitMatched_d0_bias_stack = TCanvas("h_reco_ftk_refitMatched_d0_bias_stack", ""); h_reco_ftk_refitMatched_d0_bias_stack.Draw("nostack"); h_reco_ftk_refitMatched_d0_bias_stack.GetXaxis().SetTitle("FTK refit d0 - Reco d0 [mm]"); reco_ftk_refitMatched_d0_bias_stack.SaveAs("h_reco_ftk_refitMatched_d0_bias_stack.pdf")

ftk_refit_recoMatch_track_eta_stack = TCanvas("h_ftk_refit_recoMatch_track_eta_stack", ""); h_ftk_refit_recoMatch_track_eta_stack.Draw("nostack"); h_ftk_refit_recoMatch_track_eta_stack.GetXaxis().SetTitle("#eta"); h_ftk_refit_recoMatch_track_eta_stack.GetYaxis().SetTitle("Events"); ftk_refit_recoMatch_track_eta_stack.SaveAs("h_ftk_refit_recoMatch_track_eta_stack.pdf")
ftk_refit_recoMatch_track_phi_stack = TCanvas("h_ftk_refit_recoMatch_track_phi_stack", ""); h_ftk_refit_recoMatch_track_phi_stack.Draw("nostack"); h_ftk_refit_recoMatch_track_phi_stack.GetXaxis().SetTitle("#phi"); h_ftk_refit_recoMatch_track_phi_stack.GetYaxis().SetTitle("Events"); ftk_refit_recoMatch_track_phi_stack.SaveAs("h_ftk_refit_recoMatch_track_phi_stack.pdf")
reco_ftkrefitMatch_track_eta_stack = TCanvas("h_reco_ftkrefitMatch_track_eta_stack", ""); h_reco_ftkrefitMatch_track_eta_stack.Draw("nostack"); h_reco_ftkrefitMatch_track_eta_stack.GetXaxis().SetTitle("#eta"); h_reco_ftkrefitMatch_track_eta_stack.GetYaxis().SetTitle("Events"); reco_ftkrefitMatch_track_eta_stack.SaveAs("h_reco_ftkrefitMatch_track_eta_stack.pdf")
reco_ftkrefitMatch_track_phi_stack = TCanvas("h_reco_ftkrefitMatch_track_phi_stack", ""); h_reco_ftkrefitMatch_track_phi_stack.Draw("nostack"); h_reco_ftkrefitMatch_track_phi_stack.GetXaxis().SetTitle("#phi"); h_reco_ftkrefitMatch_track_phi_stack.GetYaxis().SetTitle("Events"); reco_ftkrefitMatch_track_phi_stack.SaveAs("h_reco_ftkrefitMatch_track_phi_stack.pdf")
ftk_refit_recoMatch_track_pt_stack = TCanvas("h_ftk_refit_recoMatch_track_pt_stack", ""); h_ftk_refit_recoMatch_track_pt_stack.Draw("nostack"); h_ftk_refit_recoMatch_track_pt_stack.GetXaxis().SetTitle("p_{T} [GeV]"); h_ftk_refit_recoMatch_track_pt_stack.GetYaxis().SetTitle("Events"); ftk_refit_recoMatch_track_pt_stack.SaveAs("h_ftk_refit_recoMatch_track_pt_stack.pdf")
ftk_refit_recoMatch_track_d0_stack = TCanvas("h_ftk_refit_recoMatch_track_d0_stack", ""); h_ftk_refit_recoMatch_track_d0_stack.Draw("nostack"); h_ftk_refit_recoMatch_track_d0_stack.GetXaxis().SetTitle("d0 [mm]"); h_ftk_refit_recoMatch_track_d0_stack.GetYaxis().SetTitle("Events"); ftk_refit_recoMatch_track_d0_stack.SaveAs("h_ftk_refit_recoMatch_track_d0_stack.pdf")
ftk_refit_recoMatch_track_z0_stack = TCanvas("h_ftk_refit_recoMatch_track_z0_stack", ""); h_ftk_refit_recoMatch_track_z0_stack.Draw("nostack"); h_ftk_refit_recoMatch_track_z0_stack.GetXaxis().SetTitle("z0 [mm]"); h_ftk_refit_recoMatch_track_z0_stack.GetYaxis().SetTitle("Events"); ftk_refit_recoMatch_track_z0_stack.SaveAs("h_ftk_refit_recoMatch_track_z0_stack.pdf")

reco_accepted_hitPattern_EndCap_stack = TCanvas("h_reco_accepted_hitPattern_EndCap_stack", ""); h_reco_accepted_hitPattern_EndCap_stack.Draw("nostack"); #reco_accepted_hitPattern_EndCap_stack.BuildLegend(); 
reco_accepted_hitPattern_EndCap_stack.SaveAs("h_reco_accepted_hitPattern_EndCap_stack.pdf")
ftk_accepted_hitPattern_EndCap_stack = TCanvas("h_ftk_accepted_hitPattern_EndCap_stack", ""); h_ftk_accepted_hitPattern_EndCap_stack.Draw("nostack"); #ftk_accepted_hitPattern_EndCap_stack.BuildLegend(); 
ftk_accepted_hitPattern_EndCap_stack.SaveAs("h_ftk_accepted_hitPattern_EndCap_stack.pdf")
ftk_refit_accepted_hitPattern_EndCap_stack = TCanvas("h_ftk_refit_accepted_hitPattern_EndCap_stack", ""); h_ftk_refit_accepted_hitPattern_EndCap_stack.Draw("nostack"); #ftk_refit_accepted_hitPattern_EndCap_stack.BuildLegend(); 
ftk_refit_accepted_hitPattern_EndCap_stack.SaveAs("h_ftk_refit_accepted_hitPattern_EndCap_stack.pdf")
reco_accepted_hitPattern_Barrel_stack = TCanvas("h_reco_accepted_hitPattern_Barrel_stack", ""); h_reco_accepted_hitPattern_Barrel_stack.Draw("nostack"); #reco_accepted_hitPattern_Barrel_stack.BuildLegend(); 
reco_accepted_hitPattern_Barrel_stack.SaveAs("h_reco_accepted_hitPattern_Barrel_stack.pdf")
ftk_accepted_hitPattern_Barrel_stack = TCanvas("h_ftk_accepted_hitPattern_Barrel_stack", ""); h_ftk_accepted_hitPattern_Barrel_stack.Draw("nostack"); #ftk_accepted_hitPattern_Barrel_stack.BuildLegend(); 
ftk_accepted_hitPattern_Barrel_stack.SaveAs("h_ftk_accepted_hitPattern_Barrel_stack.pdf")
ftk_refit_accepted_hitPattern_Barrel_stack = TCanvas("h_ftk_refit_accepted_hitPattern_Barrel_stack", ""); h_ftk_refit_accepted_hitPattern_Barrel_stack.Draw("nostack"); #ftk_refit_accepted_hitPattern_Barrel_stack.BuildLegend(); 
ftk_refit_accepted_hitPattern_Barrel_stack.SaveAs("h_ftk_refit_accepted_hitPattern_Barrel_stack.pdf")
reco_accepted_hitPattern_stack = TCanvas("h_reco_accepted_hitPattern_stack", ""); h_reco_accepted_hitPattern_stack.Draw("nostack"); #reco_accepted_hitPattern_stack.BuildLegend(); 
reco_accepted_hitPattern_stack.SaveAs("h_reco_accepted_hitPattern_stack.pdf")
ftk_accepted_hitPattern_stack = TCanvas("h_ftk_accepted_hitPattern_stack", ""); h_ftk_accepted_hitPattern_stack.Draw("nostack"); #ftk_accepted_hitPattern_stack.BuildLegend(); 
ftk_accepted_hitPattern_stack.SaveAs("h_ftk_accepted_hitPattern_stack.pdf")
ftk_refit_accepted_hitPattern_stack = TCanvas("h_ftk_refit_accepted_hitPattern_stack", ""); h_ftk_refit_accepted_hitPattern_stack.Draw("nostack"); #ftk_refit_accepted_hitPattern_stack.BuildLegend(); 
ftk_refit_accepted_hitPattern_stack.SaveAs("h_ftk_refit_accepted_hitPattern_stack.pdf")

# newFile = TFile("comparison.root", "recreate")
# newFile.cd()

histocoordmasketa_reco_EndCap = TCanvas("histocoordmasketa_reco_EndCap_new", ""); histocoordmasketa_reco_EndCap_new.Draw("COLZ"); histocoordmasketa_reco_EndCap.SaveAs("divided_histocoordmasketa_reco_EndCap.pdf")
histocoordmaskphi_reco_EndCap = TCanvas("histocoordmaskphi_reco_EndCap_new", ""); histocoordmaskphi_reco_EndCap_new.Draw("COLZ"); histocoordmaskphi_reco_EndCap.SaveAs("divided_histocoordmaskphi_reco_EndCap.pdf")
histocoordmaskz0_reco_EndCap = TCanvas("histocoordmaskz0_reco_EndCap_new", ""); histocoordmaskz0_reco_EndCap_new.Draw("COLZ"); histocoordmaskz0_reco_EndCap.SaveAs("divided_histocoordmaskz0_reco_EndCap.pdf")
histocoordmasketa_ftk_EndCap = TCanvas("histocoordmasketa_ftk_EndCap_new", ""); histocoordmasketa_ftk_EndCap_new.Draw("COLZ"); histocoordmasketa_ftk_EndCap.SaveAs("hdivided_istocoordmasketa_ftk_EndCap.pdf")
histocoordmaskphi_ftk_EndCap = TCanvas("histocoordmaskphi_ftk_EndCap_new", ""); histocoordmaskphi_ftk_EndCap_new.Draw("COLZ"); histocoordmaskphi_ftk_EndCap.SaveAs("hdivided_istocoordmaskphi_ftk_EndCap.pdf")
histocoordmaskz0_ftk_EndCap = TCanvas("histocoordmaskz0_ftk_EndCap_new", ""); histocoordmaskz0_ftk_EndCap_new.Draw("COLZ"); histocoordmaskz0_ftk_EndCap.SaveAs("divided_histocoordmaskz0_ftk_EndCap.pdf")
histocoordmasketa_ftkrefit_EndCap = TCanvas("histocoordmasketa_ftkrefit_EndCap_new", ""); histocoordmasketa_ftkrefit_EndCap_new.Draw("COLZ"); histocoordmasketa_ftkrefit_EndCap.SaveAs("divided_histocoordmasketa_ftkrefit_EndCap.pdf")
histocoordmaskphi_ftkrefit_EndCap = TCanvas("histocoordmaskphi_ftkrefit_EndCap_new", ""); histocoordmaskphi_ftkrefit_EndCap_new.Draw("COLZ"); histocoordmaskphi_ftkrefit_EndCap.SaveAs("divided_histocoordmaskphi_ftkrefit_EndCap.pdf")
histocoordmaskz0_ftkrefit_EndCap = TCanvas("histocoordmaskz0_ftkrefit_EndCap_new", ""); histocoordmaskz0_ftkrefit_EndCap_new.Draw("COLZ"); histocoordmaskz0_ftkrefit_EndCap.SaveAs("divided_histocoordmaskz0_ftkrefit_EndCap.pdf")

histocoordmasketa_reco_Barrel = TCanvas("histocoordmasketa_reco_Barrel_new", ""); histocoordmasketa_reco_Barrel_new.Draw("COLZ"); histocoordmasketa_reco_Barrel.SaveAs("divided_histocoordmasketa_reco_Barrel.pdf")
histocoordmaskphi_reco_Barrel = TCanvas("histocoordmaskphi_reco_Barrel_new", ""); histocoordmaskphi_reco_Barrel_new.Draw("COLZ"); histocoordmaskphi_reco_Barrel.SaveAs("divided_histocoordmaskphi_reco_Barrel.pdf")
histocoordmaskz0_reco_Barrel = TCanvas("histocoordmaskz0_reco_Barrel_new", ""); histocoordmaskz0_reco_Barrel_new.Draw("COLZ"); histocoordmaskz0_reco_Barrel.SaveAs("hdivided_istocoordmaskz0_reco_Barrel.pdf")
histocoordmasketa_ftk_Barrel = TCanvas("histocoordmasketa_ftk_Barrel_new", ""); histocoordmasketa_ftk_Barrel_new.Draw("COLZ"); histocoordmasketa_ftk_Barrel.SaveAs("divided_histocoordmasketa_ftk_Barrel.pdf")
histocoordmaskphi_ftk_Barrel = TCanvas("histocoordmaskphi_ftk_Barrel_new", ""); histocoordmaskphi_ftk_Barrel_new.Draw("COLZ"); histocoordmaskphi_ftk_Barrel.SaveAs("divided_histocoordmaskphi_ftk_Barrel.pdf")
histocoordmaskz0_ftk_Barrel = TCanvas("histocoordmaskz0_ftk_Barrel_new", ""); histocoordmaskz0_ftk_Barrel_new.Draw("COLZ"); histocoordmaskz0_ftk_Barrel.SaveAs("divided_histocoordmaskz0_ftk_Barrel.pdf")
histocoordmasketa_ftkrefit_Barrel = TCanvas("histocoordmasketa_ftkrefit_Barrel_new", ""); histocoordmasketa_ftkrefit_Barrel_new.Draw("COLZ"); histocoordmasketa_ftkrefit_Barrel.SaveAs("hdivided_istocoordmasketa_ftkrefit_Barrel.pdf")
histocoordmaskphi_ftkrefit_Barrel = TCanvas("histocoordmaskphi_ftkrefit_Barrel_new", ""); histocoordmaskphi_ftkrefit_Barrel_new.Draw("COLZ"); histocoordmaskphi_ftkrefit_Barrel.SaveAs("divided_histocoordmaskphi_ftkrefit_Barrel.pdf")
histocoordmaskz0_ftkrefit_Barrel = TCanvas("histocoordmaskz0_ftkrefit_Barrel_new", ""); histocoordmaskz0_ftkrefit_Barrel_new.Draw("COLZ"); histocoordmaskz0_ftkrefit_Barrel.SaveAs("hdivided_istocoordmaskz0_ftkrefit_Barrel.pdf")

histocoordmasketa_reco = TCanvas("histocoordmasketa_reco_new", ""); histocoordmasketa_reco_new.Draw("COLZ"); histocoordmasketa_reco.SaveAs("divided_histocoordmasketa_reco.pdf")
histocoordmaskphi_reco = TCanvas("histocoordmaskphi_reco_new", ""); histocoordmaskphi_reco_new.Draw("COLZ"); histocoordmaskphi_reco.SaveAs("divided_histocoordmaskphi_reco.pdf")
histocoordmaskz0_reco = TCanvas("histocoordmaskz0_reco_new", ""); histocoordmaskz0_reco_new.Draw("COLZ"); histocoordmaskz0_reco.SaveAs("divided_histocoordmaskz0_reco.pdf")
histocoordmasketa_ftk = TCanvas("histocoordmasketa_ftk_new", ""); histocoordmasketa_ftk_new.Draw("COLZ"); histocoordmasketa_ftk.SaveAs("divided_histocoordmasketa_ftk.pdf")
histocoordmaskphi_ftk = TCanvas("histocoordmaskphi_ftk_new", ""); histocoordmaskphi_ftk_new.Draw("COLZ"); histocoordmaskphi_ftk.SaveAs("divided_histocoordmaskphi_ftk.pdf")
histocoordmaskz0_ftk = TCanvas("histocoordmaskz0_ftk_new", ""); histocoordmaskz0_ftk_new.Draw("COLZ"); histocoordmaskz0_ftk.SaveAs("divided_histocoordmaskz0_ftk.pdf")
histocoordmasketa_ftkrefit = TCanvas("histocoordmasketa_ftkrefit_new", ""); histocoordmasketa_ftkrefit_new.Draw("COLZ"); histocoordmasketa_ftkrefit.SaveAs("divided_histocoordmasketa_ftkrefit.pdf")
histocoordmaskphi_ftkrefit = TCanvas("histocoordmaskphi_ftkrefit_new", ""); histocoordmaskphi_ftkrefit_new.Draw("COLZ"); histocoordmaskphi_ftkrefit.SaveAs("divided_histocoordmaskphi_ftkrefit.pdf")
histocoordmaskz0_ftkrefit = TCanvas("histocoordmaskz0_ftkrefit_new", ""); histocoordmaskz0_ftkrefit_new.Draw("COLZ"); histocoordmaskz0_ftkrefit.SaveAs("divided_histocoordmaskz0_ftkrefit.pdf")


reco_accepted_pt_new = TCanvas("h_reco_accepted_pt_new", ""); h_reco_accepted_pt_new.Draw(); reco_accepted_pt_new.SaveAs("h_divided_reco_accepted_pt.pdf")
reco_accepted_eta_new = TCanvas("h_reco_accepted_eta_new", ""); h_reco_accepted_eta_new.Draw(); reco_accepted_eta_new.SaveAs("h_divided_reco_accepted_eta.pdf")
reco_accepted_phi_new = TCanvas("h_reco_accepted_phi_new", ""); h_reco_accepted_phi_new.Draw(); reco_accepted_phi_new.SaveAs("h_divided_reco_accepted_phi.pdf")
# reco_accepted_m_new = TCanvas("h_reco_accepted_m_new", ""); h_reco_accepted_m_new.Draw(); reco_accepted_m_new.SaveAs("h_divided_reco_accepted_m.pdf")
reco_accepted_d0_new = TCanvas("h_reco_accepted_d0_new", ""); h_reco_accepted_d0_new.Draw(); reco_accepted_d0_new.SaveAs("h_divided_reco_accepted_d0.pdf")
reco_accepted_z0_new = TCanvas("h_reco_accepted_z0_new", ""); h_reco_accepted_z0_new.Draw(); reco_accepted_z0_new.SaveAs("h_divided_reco_accepted_z0.pdf")
reco_accepted_qop_new = TCanvas("h_reco_accepted_qop_new", ""); h_reco_accepted_qop_new.Draw(); reco_accepted_qop_new.SaveAs("h_divided_reco_accepted_qop.pdf")
reco_accepted_charge_new = TCanvas("h_reco_accepted_charge_new", ""); h_reco_accepted_charge_new.Draw(); reco_accepted_charge_new.SaveAs("h_divided_reco_accepted_charge.pdf")
reco_accepted_chi2_new = TCanvas("h_reco_accepted_chi2_new", ""); h_reco_accepted_chi2_new.Draw(); reco_accepted_chi2_new.SaveAs("h_divided_reco_accepted_chi2.pdf")

reco_inclusive_pt_new = TCanvas("h_reco_inclusive_pt_new", ""); h_reco_inclusive_pt_new.Draw(); reco_inclusive_pt_new.SaveAs("h_divided_reco_inclusive_pt.pdf")
reco_inclusive_eta_new = TCanvas("h_reco_inclusive_eta_new", ""); h_reco_inclusive_eta_new.Draw(); reco_inclusive_eta_new.SaveAs("h_divided_reco_inclusive_eta.pdf")
reco_inclusive_phi_new = TCanvas("h_reco_inclusive_phi_new", ""); h_reco_inclusive_phi_new.Draw(); reco_inclusive_phi_new.SaveAs("h_divided_reco_inclusive_phi.pdf")
# reco_inclusive_m_new = TCanvas("h_reco_inclusive_m_new", ""); h_reco_inclusive_m_new.Draw(); reco_inclusive_m_new.SaveAs("h_divided_reco_inclusive_m.pdf")
reco_inclusive_d0_new = TCanvas("h_reco_inclusive_d0_new", ""); h_reco_inclusive_d0_new.Draw(); reco_inclusive_d0_new.SaveAs("h_divided_reco_inclusive_d0.pdf")
reco_inclusive_z0_new = TCanvas("h_reco_inclusive_z0_new", ""); h_reco_inclusive_z0_new.Draw(); reco_inclusive_z0_new.SaveAs("h_divided_reco_inclusive_z0.pdf")
reco_inclusive_qop_new = TCanvas("h_reco_inclusive_qop_new", ""); h_reco_inclusive_qop_new.Draw(); reco_inclusive_qop_new.SaveAs("h_divided_reco_inclusive_qop.pdf")
reco_inclusive_charge_new = TCanvas("h_reco_inclusive_charge_new", ""); h_reco_inclusive_charge_new.Draw(); reco_inclusive_charge_new.SaveAs("h_divided_reco_inclusive_charge.pdf")
reco_inclusive_chi2_new = TCanvas("h_reco_inclusive_chi2_new", ""); h_reco_inclusive_chi2_new.Draw(); reco_inclusive_chi2_new.SaveAs("h_divided_reco_inclusive_chi2.pdf")

ftk_accepted_pt_new = TCanvas("h_ftk_accepted_pt_new", ""); h_ftk_accepted_pt_new.Draw(); ftk_accepted_pt_new.SaveAs("h_divided_ftk_accepted_pt.pdf")
ftk_accepted_eta_new = TCanvas("h_ftk_accepted_eta_new", ""); h_ftk_accepted_eta_new.Draw(); ftk_accepted_eta_new.SaveAs("h_divided_ftk_accepted_eta.pdf")
ftk_accepted_phi_new = TCanvas("h_ftk_accepted_phi_new", ""); h_ftk_accepted_phi_new.Draw(); ftk_accepted_phi_new.SaveAs("h_divided_ftk_accepted_phi.pdf")
# ftk_accepted_m_new = TCanvas("h_ftk_accepted_m_new", ""); h_ftk_accepted_m_new.Draw(); ftk_accepted_m_new.SaveAs("h_divided_ftk_accepted_m.pdf")
ftk_accepted_d0_new = TCanvas("h_ftk_accepted_d0_new", ""); h_ftk_accepted_d0_new.Draw(); ftk_accepted_d0_new.SaveAs("h_divided_ftk_accepted_d0.pdf")
ftk_accepted_corrected_d0_new = TCanvas("h_ftk_accepted_corrected_d0_new", ""); h_ftk_accepted_corrected_d0_new.Draw(); ftk_accepted_corrected_d0_new.SaveAs("h_divided_ftk_accepted_corrected_d0.pdf")
ftk_accepted_z0_new = TCanvas("h_ftk_accepted_z0_new", ""); h_ftk_accepted_z0_new.Draw(); ftk_accepted_z0_new.SaveAs("h_divided_ftk_accepted_z0.pdf")
ftk_accepted_qop_new = TCanvas("h_ftk_accepted_qop_new", ""); h_ftk_accepted_qop_new.Draw(); ftk_accepted_qop_new.SaveAs("h_divided_ftk_accepted_qop.pdf")
ftk_accepted_charge_new = TCanvas("h_ftk_accepted_charge_new", ""); h_ftk_accepted_charge_new.Draw(); ftk_accepted_charge_new.SaveAs("h_divided_ftk_accepted_charge.pdf")
ftk_accepted_chi2_new = TCanvas("h_ftk_accepted_chi2_new", ""); h_ftk_accepted_chi2_new.Draw(); ftk_accepted_chi2_new.SaveAs("h_divided_ftk_accepted_chi2.pdf")

ftk_inclusive_pt_new = TCanvas("h_ftk_inclusive_pt_new", ""); h_ftk_inclusive_pt_new.Draw(); ftk_inclusive_pt_new.SaveAs("h_divided_ftk_inclusive_pt.pdf")
ftk_inclusive_eta_new = TCanvas("h_ftk_inclusive_eta_new", ""); h_ftk_inclusive_eta_new.Draw(); ftk_inclusive_eta_new.SaveAs("h_divided_ftk_inclusive_eta.pdf")
ftk_inclusive_phi_new = TCanvas("h_ftk_inclusive_phi_new", ""); h_ftk_inclusive_phi_new.Draw(); ftk_inclusive_phi_new.SaveAs("h_divided_ftk_inclusive_phi.pdf")
# ftk_inclusive_m_new = TCanvas("h_ftk_inclusive_m_new", ""); h_ftk_inclusive_m_new.Draw(); ftk_inclusive_m_new.SaveAs("h_divided_ftk_inclusive_m.pdf")
ftk_inclusive_d0_new = TCanvas("h_ftk_inclusive_d0_new", ""); h_ftk_inclusive_d0_new.Draw(); ftk_inclusive_d0_new.SaveAs("h_divided_ftk_inclusive_d0.pdf")
ftk_inclusive_corrected_d0_new = TCanvas("h_ftk_inclusive_corrected_d0_new", ""); h_ftk_inclusive_corrected_d0_new.Draw(); ftk_inclusive_corrected_d0_new.SaveAs("h_divided_ftk_inclusive_corrected_d0.pdf")
ftk_inclusive_z0_new = TCanvas("h_ftk_inclusive_z0_new", ""); h_ftk_inclusive_z0_new.Draw(); ftk_inclusive_z0_new.SaveAs("h_divided_ftk_inclusive_z0.pdf")
ftk_inclusive_qop_new = TCanvas("h_ftk_inclusive_qop_new", ""); h_ftk_inclusive_qop_new.Draw(); ftk_inclusive_qop_new.SaveAs("h_divided_ftk_inclusive_qop.pdf")
ftk_inclusive_charge_new = TCanvas("h_ftk_inclusive_charge_new", ""); h_ftk_inclusive_charge_new.Draw(); ftk_inclusive_charge_new.SaveAs("h_divided_ftk_inclusive_charge.pdf")
ftk_inclusive_chi2_new = TCanvas("h_ftk_inclusive_chi2_new", ""); h_ftk_inclusive_chi2_new.Draw(); ftk_inclusive_chi2_new.SaveAs("h_divided_ftk_inclusive_chi2.pdf")

ftk_refit_accepted_pt_new = TCanvas("h_ftk_refit_accepted_pt_new", ""); h_ftk_refit_accepted_pt_new.Draw(); ftk_refit_accepted_pt_new.SaveAs("h_divided_ftk_refit_accepted_pt.pdf")
ftk_refit_accepted_eta_new = TCanvas("h_ftk_refit_accepted_eta_new", ""); h_ftk_refit_accepted_eta_new.Draw(); ftk_refit_accepted_eta_new.SaveAs("h_divided_ftk_refit_accepted_eta.pdf")
ftk_refit_accepted_phi_new = TCanvas("h_ftk_refit_accepted_phi_new", ""); h_ftk_refit_accepted_phi_new.Draw(); ftk_refit_accepted_phi_new.SaveAs("h_divided_ftk_refit_accepted_phi.pdf")
# ftk_refit_accepted_m_new = TCanvas("h_ftk_refit_accepted_m_new", ""); h_ftk_refit_accepted_m_new.Draw(); ftk_refit_accepted_m_new.SaveAs("h_divided_ftk_refit_accepted_m.pdf")
ftk_refit_accepted_d0_new = TCanvas("h_ftk_refit_accepted_d0_new", ""); h_ftk_refit_accepted_d0_new.Draw(); ftk_refit_accepted_d0_new.SaveAs("h_divided_ftk_refit_accepted_d0.pdf")
ftk_refit_accepted_z0_new = TCanvas("h_ftk_refit_accepted_z0_new", ""); h_ftk_refit_accepted_z0_new.Draw(); ftk_refit_accepted_z0_new.SaveAs("h_divided_ftk_refit_accepted_z0.pdf")
ftk_refit_accepted_qop_new = TCanvas("h_ftk_refit_accepted_qop_new", ""); h_ftk_refit_accepted_qop_new.Draw(); ftk_refit_accepted_qop_new.SaveAs("h_divided_ftk_refit_accepted_qop.pdf")
ftk_refit_accepted_charge_new = TCanvas("h_ftk_refit_accepted_charge_new", ""); h_ftk_refit_accepted_charge_new.Draw(); ftk_refit_accepted_charge_new.SaveAs("h_divided_ftk_refit_accepted_charge.pdf")
ftk_refit_accepted_chi2_new = TCanvas("h_ftk_refit_accepted_chi2_new", ""); h_ftk_refit_accepted_chi2_new.Draw(); ftk_refit_accepted_chi2_new.SaveAs("h_divided_ftk_refit_accepted_chi2.pdf")

ftk_refit_inclusive_pt_new = TCanvas("h_ftk_refit_inclusive_pt_new", ""); h_ftk_refit_inclusive_pt_new.Draw(); ftk_refit_inclusive_pt_new.SaveAs("h_divided_ftk_refit_inclusive_pt.pdf")
ftk_refit_inclusive_eta_new = TCanvas("h_ftk_refit_inclusive_eta_new", ""); h_ftk_refit_inclusive_eta_new.Draw(); ftk_refit_inclusive_eta_new.SaveAs("h_divided_ftk_refit_inclusive_eta.pdf")
ftk_refit_inclusive_phi_new = TCanvas("h_ftk_refit_inclusive_phi_new", ""); h_ftk_refit_inclusive_phi_new.Draw(); ftk_refit_inclusive_phi_new.SaveAs("h_divided_ftk_refit_inclusive_phi.pdf")
# ftk_refit_inclusive_m_new = TCanvas("h_ftk_refit_inclusive_m_new", ""); h_ftk_refit_inclusive_m_new.Draw(); ftk_refit_inclusive_m_new.SaveAs("h_divided_ftk_refit_inclusive_m.pdf")
ftk_refit_inclusive_d0_new = TCanvas("h_ftk_refit_inclusive_d0_new", ""); h_ftk_refit_inclusive_d0_new.Draw(); ftk_refit_inclusive_d0_new.SaveAs("h_divided_ftk_refit_inclusive_d0.pdf")
ftk_refit_inclusive_z0_new = TCanvas("h_ftk_refit_inclusive_z0_new", ""); h_ftk_refit_inclusive_z0_new.Draw(); ftk_refit_inclusive_z0_new.SaveAs("h_divided_ftk_refit_inclusive_z0.pdf")
ftk_refit_inclusive_qop_new = TCanvas("h_ftk_refit_inclusive_qop_new", ""); h_ftk_refit_inclusive_qop_new.Draw(); ftk_refit_inclusive_qop_new.SaveAs("h_divided_ftk_refit_inclusive_qop.pdf")
ftk_refit_inclusive_charge_new = TCanvas("h_ftk_refit_inclusive_charge_new", ""); h_ftk_refit_inclusive_charge_new.Draw(); ftk_refit_inclusive_charge_new.SaveAs("h_divided_ftk_refit_inclusive_charge.pdf")
ftk_refit_inclusive_chi2_new = TCanvas("h_ftk_refit_inclusive_chi2_new", ""); h_ftk_refit_inclusive_chi2_new.Draw(); ftk_refit_inclusive_chi2_new.SaveAs("h_divided_ftk_refit_inclusive_chi2.pdf")

if isData == False:
	reco_truthMatched_pt_bias_new = TCanvas("h_reco_truthMatched_pt_bias_new", ""); h_reco_truthMatched_pt_bias_new.Draw(); reco_truthMatched_pt_bias_new.SaveAs("h_divided_reco_truthMatched_pt_bias.pdf")
	reco_truthMatched_eta_bias_new = TCanvas("h_reco_truthMatched_eta_bias_new", ""); h_reco_truthMatched_eta_bias_new.Draw(); reco_truthMatched_eta_bias_new.SaveAs("h_divided_reco_truthMatched_eta_bias.pdf")
	reco_truthMatched_phi_bias_new = TCanvas("h_reco_truthMatched_phi_bias_new", ""); h_reco_truthMatched_phi_bias_new.Draw(); reco_truthMatched_phi_bias_new.SaveAs("h_divided_reco_truthMatched_phi_bias.pdf")
	reco_truthMatched_d0_bias_new = TCanvas("h_reco_truthMatched_d0_bias_new", ""); h_reco_truthMatched_d0_bias_new.Draw(); reco_truthMatched_d0_bias_new.SaveAs("h_divided_reco_truthMatched_d0_bias.pdf")

	truth_recoMatch_track_eta_new = TCanvas("h_truth_recoMatch_track_eta_new", ""); h_truth_recoMatch_track_eta_new.Draw(); truth_recoMatch_track_eta_new.SaveAs("h_divided_truth_recoMatch_track_eta.pdf")
	truth_recoMatch_track_phi_new = TCanvas("h_truth_recoMatch_track_phi_new", ""); h_truth_recoMatch_track_phi_new.Draw(); truth_recoMatch_track_phi_new.SaveAs("h_divided_truth_recoMatch_track_phi.pdf")
	reco_truthMatch_track_eta_new = TCanvas("h_reco_truthMatch_track_eta_new", ""); h_reco_truthMatch_track_eta_new.Draw(); reco_truthMatch_track_eta_new.SaveAs("h_divided_reco_truthMatch_track_eta.pdf")
	reco_truthMatch_track_phi_new = TCanvas("h_reco_truthMatch_track_phi_new", ""); h_reco_truthMatch_track_phi_new.Draw(); reco_truthMatch_track_phi_new.SaveAs("h_divided_reco_truthMatch_track_phi.pdf")
	truth_recoMatch_track_pt_new = TCanvas("h_truth_recoMatch_track_pt_new", ""); h_truth_recoMatch_track_pt_new.Draw(); truth_recoMatch_track_pt_new.SaveAs("h_divided_truth_recoMatch_track_pt.pdf")
	truth_recoMatch_track_d0_new = TCanvas("h_truth_recoMatch_track_d0_new", ""); h_truth_recoMatch_track_d0_new.Draw(); truth_recoMatch_track_d0_new.SaveAs("h_divided_truth_recoMatch_track_d0.pdf")
	truth_recoMatch_track_z0_new = TCanvas("h_truth_recoMatch_track_z0_new", ""); h_truth_recoMatch_track_z0_new.Draw(); truth_recoMatch_track_z0_new.SaveAs("h_divided_truth_recoMatch_track_z0.pdf")

	truth_ftk_Matched_pt_bias_new = TCanvas("h_truth_ftk_Matched_pt_bias_new", ""); h_truth_ftk_Matched_pt_bias_new.Draw(); truth_ftk_Matched_pt_bias_new.SaveAs("h_divided_truth_ftk_Matched_pt_bias.pdf")
	truth_ftk_Matched_eta_bias_new = TCanvas("h_truth_ftk_Matched_eta_bias_new", ""); h_truth_ftk_Matched_eta_bias_new.Draw(); truth_ftk_Matched_eta_bias_new.SaveAs("h_divided_truth_ftk_Matched_eta_bias.pdf")
	truth_ftk_Matched_phi_bias_new = TCanvas("h_truth_ftk_Matched_phi_bias_new", ""); h_truth_ftk_Matched_phi_bias_new.Draw(); truth_ftk_Matched_phi_bias_new.SaveAs("h_divided_truth_ftk_Matched_phi_bias.pdf")
	truth_ftk_Matched_d0_bias_new = TCanvas("h_truth_ftk_Matched_d0_bias_new", ""); h_truth_ftk_Matched_d0_bias_new.Draw(); truth_ftk_Matched_d0_bias_new.SaveAs("h_divided_truth_ftk_Matched_d0_bias.pdf")
	truth_ftk_Matched_corrected_d0_bias_new = TCanvas("h_truth_ftk_Matched_corrected_d0_bias_new", ""); h_truth_ftk_Matched_corrected_d0_bias_new.Draw(); truth_ftk_Matched_corrected_d0_bias_new.SaveAs("h_divided_truth_ftk_Matched_corrected_d0_bias.pdf")

	ftk_truthMatch_track_eta_new = TCanvas("h_ftk_truthMatch_track_eta_new", ""); h_ftk_truthMatch_track_eta_new.Draw(); ftk_truthMatch_track_eta_new.SaveAs("h_divided_ftk_truthMatch_track_eta.pdf")
	ftk_truthMatch_track_phi_new = TCanvas("h_ftk_truthMatch_track_phi_new", ""); h_ftk_truthMatch_track_phi_new.Draw(); ftk_truthMatch_track_phi_new.SaveAs("h_divided_ftk_truthMatch_track_phi.pdf")
	truth_ftkMatch_track_eta_new = TCanvas("h_truth_ftkMatch_track_eta_new", ""); h_truth_ftkMatch_track_eta_new.Draw(); truth_ftkMatch_track_eta_new.SaveAs("h_divided_truth_ftkMatch_track_eta.pdf")
	truth_ftkMatch_track_phi_new = TCanvas("h_truth_ftkMatch_track_phi_new", ""); h_truth_ftkMatch_track_phi_new.Draw(); truth_ftkMatch_track_phi_new.SaveAs("h_divided_truth_ftkMatch_track_phi.pdf")
	ftk_truthMatch_track_pt_new = TCanvas("h_ftk_truthMatch_track_pt_new", ""); h_ftk_truthMatch_track_pt_new.Draw(); ftk_truthMatch_track_pt_new.SaveAs("h_divided_ftk_truthMatch_track_pt.pdf")
	ftk_truthMatch_track_d0_new = TCanvas("h_ftk_truthMatch_track_d0_new", ""); h_ftk_truthMatch_track_d0_new.Draw(); ftk_truthMatch_track_d0_new.SaveAs("h_divided_ftk_truthMatch_track_d0.pdf")
	ftk_truthMatch_track_z0_new = TCanvas("h_ftk_truthMatch_track_z0_new", ""); h_ftk_truthMatch_track_z0_new.Draw(); ftk_truthMatch_track_z0_new.SaveAs("h_divided_ftk_truthMatch_track_z0.pdf")

	truth_ftk_refitMatched_pt_bias_new = TCanvas("h_truth_ftk_refitMatched_pt_bias_new", ""); h_truth_ftk_refitMatched_pt_bias_new.Draw(); truth_ftk_refitMatched_pt_bias_new.SaveAs("h_divided_truth_ftk_refitMatched_pt_bias.pdf")
	truth_ftk_refitMatched_eta_bias_new = TCanvas("h_truth_ftk_refitMatched_eta_bias_new", ""); h_truth_ftk_refitMatched_eta_bias_new.Draw(); truth_ftk_refitMatched_eta_bias_new.SaveAs("h_divided_truth_ftk_refitMatched_eta_bias.pdf")
	truth_ftk_refitMatched_phi_bias_new = TCanvas("h_truth_ftk_refitMatched_phi_bias_new", ""); h_truth_ftk_refitMatched_phi_bias_new.Draw(); truth_ftk_refitMatched_phi_bias_new.SaveAs("h_divided_truth_ftk_refitMatched_phi_bias.pdf")
	truth_ftk_refitMatched_d0_bias_new = TCanvas("h_truth_ftk_refitMatched_d0_bias_new", ""); h_truth_ftk_refitMatched_d0_bias_new.Draw(); truth_ftk_refitMatched_d0_bias_new.SaveAs("h_divided_truth_ftk_refitMatched_d0_bias.pdf")

	ftk_refit_truthMatch_track_eta_new = TCanvas("h_ftk_refit_truthMatch_track_eta_new", ""); h_ftk_refit_truthMatch_track_eta_new.Draw(); ftk_refit_truthMatch_track_eta_new.SaveAs("h_divided_ftk_refit_truthMatch_track_eta.pdf")
	ftk_refit_truthMatch_track_phi_new = TCanvas("h_ftk_refit_truthMatch_track_phi_new", ""); h_ftk_refit_truthMatch_track_phi_new.Draw(); ftk_refit_truthMatch_track_phi_new.SaveAs("h_divided_ftk_refit_truthMatch_track_phi.pdf")
	truth_ftkrefitMatch_track_eta_new = TCanvas("h_truth_ftkrefitMatch_track_eta_new", ""); h_truth_ftkrefitMatch_track_eta_new.Draw(); truth_ftkrefitMatch_track_eta_new.SaveAs("h_divided_truth_ftkrefitMatch_track_eta.pdf")
	truth_ftkrefitMatch_track_phi_new = TCanvas("h_truth_ftkrefitMatch_track_phi_new", ""); h_truth_ftkrefitMatch_track_phi_new.Draw(); truth_ftkrefitMatch_track_phi_new.SaveAs("h_divided_truth_ftkrefitMatch_track_phi.pdf")
	ftk_refit_truthMatch_track_pt_new = TCanvas("h_ftk_refit_truthMatch_track_pt_new", ""); h_ftk_refit_truthMatch_track_pt_new.Draw(); ftk_refit_truthMatch_track_pt_new.SaveAs("h_divided_ftk_refit_truthMatch_track_pt.pdf")
	ftk_refit_truthMatch_track_d0_new = TCanvas("h_ftk_refit_truthMatch_track_d0_new", ""); h_ftk_refit_truthMatch_track_d0_new.Draw(); ftk_refit_truthMatch_track_d0_new.SaveAs("h_divided_ftk_refit_truthMatch_track_d0.pdf")
	ftk_refit_truthMatch_track_z0_new = TCanvas("h_ftk_refit_truthMatch_track_z0_new", ""); h_ftk_refit_truthMatch_track_z0_new.Draw(); ftk_refit_truthMatch_track_z0_new.SaveAs("h_divided_ftk_refit_truthMatch_track_z0.pdf")

reco_ftkMatched_pt_bias_new = TCanvas("h_reco_ftkMatched_pt_bias_new", ""); h_reco_ftkMatched_pt_bias_new.Draw(); reco_ftkMatched_pt_bias_new.SaveAs("h_divided_reco_ftkMatched_pt_bias.pdf")
reco_ftkMatched_eta_bias_new = TCanvas("h_reco_ftkMatched_eta_bias_new", ""); h_reco_ftkMatched_eta_bias_new.Draw(); reco_ftkMatched_eta_bias_new.SaveAs("h_divided_reco_ftkMatched_eta_bias.pdf")
reco_ftkMatched_phi_bias_new = TCanvas("h_reco_ftkMatched_phi_bias_new", ""); h_reco_ftkMatched_phi_bias_new.Draw(); reco_ftkMatched_phi_bias_new.SaveAs("h_divided_reco_ftkMatched_phi_bias.pdf")
reco_ftkMatched_d0_bias_new = TCanvas("h_reco_ftkMatched_d0_bias_new", ""); h_reco_ftkMatched_d0_bias_new.Draw(); reco_ftkMatched_d0_bias_new.SaveAs("h_divided_reco_ftkMatched_d0_bias.pdf")
reco_ftkMatched_corrected_d0_bias_new = TCanvas("h_reco_ftkMatched_corrected_d0_bias_new", ""); h_reco_ftkMatched_corrected_d0_bias_new.Draw(); reco_ftkMatched_corrected_d0_bias_new.SaveAs("h_divided_reco_ftkMatched_corrected_d0_bias.pdf")

ftk_recoMatch_track_eta_new = TCanvas("h_ftk_recoMatch_track_eta_new", ""); h_ftk_recoMatch_track_eta_new.Draw(); ftk_recoMatch_track_eta_new.SaveAs("h_divided_ftk_recoMatch_track_eta.pdf")
ftk_recoMatch_track_phi_new = TCanvas("h_ftk_recoMatch_track_phi_new", ""); h_ftk_recoMatch_track_phi_new.Draw(); ftk_recoMatch_track_phi_new.SaveAs("h_divided_ftk_recoMatch_track_phi.pdf")
reco_ftkMatch_track_eta_new = TCanvas("h_reco_ftkMatch_track_eta_new", ""); h_reco_ftkMatch_track_eta_new.Draw(); reco_ftkMatch_track_eta_new.SaveAs("h_divided_reco_ftkMatch_track_eta.pdf")
reco_ftkMatch_track_phi_new = TCanvas("h_reco_ftkMatch_track_phi_new", ""); h_reco_ftkMatch_track_phi_new.Draw(); reco_ftkMatch_track_phi_new.SaveAs("h_divided_reco_ftkMatch_track_phi.pdf")
ftk_recoMatch_track_pt_new = TCanvas("h_ftk_recoMatch_track_pt_new", ""); h_ftk_recoMatch_track_pt_new.Draw(); ftk_recoMatch_track_pt_new.SaveAs("h_divided_ftk_recoMatch_track_pt.pdf")
ftk_recoMatch_track_d0_new = TCanvas("h_ftk_recoMatch_track_d0_new", ""); h_ftk_recoMatch_track_d0_new.Draw(); ftk_recoMatch_track_d0_new.SaveAs("h_divided_ftk_recoMatch_track_d0.pdf")
# ftk_recoMatch_track_corrected_d0_new = TCanvas("h_ftk_recoMatch_track_corrected_d0_new", ""); h_ftk_recoMatch_track_corrected_d0_new.Draw(); ftk_recoMatch_track_corrected_d0_new.SaveAs("h_divided_ftk_recoMatch_track_corrected_d0.pdf")
ftk_recoMatch_track_z0_new = TCanvas("h_ftk_recoMatch_track_z0_new", ""); h_ftk_recoMatch_track_z0_new.Draw(); ftk_recoMatch_track_z0_new.SaveAs("h_divided_ftk_recoMatch_track_z0.pdf")

reco_ftk_refitMatched_pt_bias_new = TCanvas("h_reco_ftk_refitMatched_pt_bias_new", ""); h_reco_ftk_refitMatched_pt_bias_new.Draw(); reco_ftk_refitMatched_pt_bias_new.SaveAs("h_divided_reco_ftk_refitMatched_pt_bias.pdf")
reco_ftk_refitMatched_eta_bias_new = TCanvas("h_reco_ftk_refitMatched_eta_bias_new", ""); h_reco_ftk_refitMatched_eta_bias_new.Draw(); reco_ftk_refitMatched_eta_bias_new.SaveAs("h_divided_reco_ftk_refitMatched_eta_bias.pdf")
reco_ftk_refitMatched_phi_bias_new = TCanvas("h_reco_ftk_refitMatched_phi_bias_new", ""); h_reco_ftk_refitMatched_phi_bias_new.Draw(); reco_ftk_refitMatched_phi_bias_new.SaveAs("h_divided_reco_ftk_refitMatched_phi_bias.pdf")
reco_ftk_refitMatched_d0_bias_new = TCanvas("h_reco_ftk_refitMatched_d0_bias_new", ""); h_reco_ftk_refitMatched_d0_bias_new.Draw(); reco_ftk_refitMatched_d0_bias_new.SaveAs("h_divided_reco_ftk_refitMatched_d0_bias.pdf")

ftk_refit_recoMatch_track_eta_new = TCanvas("h_ftk_refit_recoMatch_track_eta_new", ""); h_ftk_refit_recoMatch_track_eta_new.Draw(); ftk_refit_recoMatch_track_eta_new.SaveAs("h_divided_ftk_refit_recoMatch_track_eta.pdf")
ftk_refit_recoMatch_track_phi_new = TCanvas("h_ftk_refit_recoMatch_track_phi_new", ""); h_ftk_refit_recoMatch_track_phi_new.Draw(); ftk_refit_recoMatch_track_phi_new.SaveAs("h_divided_ftk_refit_recoMatch_track_phi.pdf")
reco_ftkrefitMatch_track_eta_new = TCanvas("h_reco_ftkrefitMatch_track_eta_new", ""); h_reco_ftkrefitMatch_track_eta_new.Draw(); reco_ftkrefitMatch_track_eta_new.SaveAs("h_divided_reco_ftkrefitMatch_track_eta.pdf")
reco_ftkrefitMatch_track_phi_new = TCanvas("h_reco_ftkrefitMatch_track_phi_new", ""); h_reco_ftkrefitMatch_track_phi_new.Draw(); reco_ftkrefitMatch_track_phi_new.SaveAs("h_divided_reco_ftkrefitMatch_track_phi.pdf")
ftk_refit_recoMatch_track_pt_new = TCanvas("h_ftk_refit_recoMatch_track_pt_new", ""); h_ftk_refit_recoMatch_track_pt_new.Draw(); ftk_refit_recoMatch_track_pt_new.SaveAs("h_divided_ftk_refit_recoMatch_track_pt.pdf")
ftk_refit_recoMatch_track_d0_new = TCanvas("h_ftk_refit_recoMatch_track_d0_new", ""); h_ftk_refit_recoMatch_track_d0_new.Draw(); ftk_refit_recoMatch_track_d0_new.SaveAs("h_divided_ftk_refit_recoMatch_track_d0.pdf")
ftk_refit_recoMatch_track_z0_new = TCanvas("h_ftk_refit_recoMatch_track_z0_new", ""); h_ftk_refit_recoMatch_track_z0_new.Draw(); ftk_refit_recoMatch_track_z0_new.SaveAs("h_divided_ftk_refit_recoMatch_track_z0.pdf")

reco_accepted_hitPattern_EndCap_new = TCanvas("h_reco_accepted_hitPattern_EndCap_new", ""); h_reco_accepted_hitPattern_EndCap_new.Draw(); reco_accepted_hitPattern_EndCap_new.SaveAs("h_divided_reco_accepted_hitPattern_EndCap.pdf")
ftk_accepted_hitPattern_EndCap_new = TCanvas("h_ftk_accepted_hitPattern_EndCap_new", ""); h_ftk_accepted_hitPattern_EndCap_new.Draw(); ftk_accepted_hitPattern_EndCap_new.SaveAs("h_divided_ftk_accepted_hitPattern_EndCap.pdf")
ftk_refit_accepted_hitPattern_EndCap_new = TCanvas("h_ftk_refit_accepted_hitPattern_EndCap_new", ""); h_ftk_refit_accepted_hitPattern_EndCap_new.Draw(); ftk_refit_accepted_hitPattern_EndCap_new.SaveAs("h_divided_ftk_refit_accepted_hitPattern_EndCap.pdf")
reco_accepted_hitPattern_Barrel_new = TCanvas("h_reco_accepted_hitPattern_Barrel_new", ""); h_reco_accepted_hitPattern_Barrel_new.Draw(); reco_accepted_hitPattern_Barrel_new.SaveAs("h_divided_reco_accepted_hitPattern_Barrel.pdf")
ftk_accepted_hitPattern_Barrel_new = TCanvas("h_ftk_accepted_hitPattern_Barrel_new", ""); h_ftk_accepted_hitPattern_Barrel_new.Draw(); ftk_accepted_hitPattern_Barrel_new.SaveAs("h_divided_ftk_accepted_hitPattern_Barrel.pdf")
ftk_refit_accepted_hitPattern_Barrel_new = TCanvas("h_ftk_refit_accepted_hitPattern_Barrel_new", ""); h_ftk_refit_accepted_hitPattern_Barrel_new.Draw(); ftk_refit_accepted_hitPattern_Barrel_new.SaveAs("h_divided_ftk_refit_accepted_hitPattern_Barrel.pdf")
reco_accepted_hitPattern_new = TCanvas("h_reco_accepted_hitPattern_new", ""); h_reco_accepted_hitPattern_new.Draw(); reco_accepted_hitPattern_new.SaveAs("h_divided_reco_accepted_hitPattern.pdf")
ftk_accepted_hitPattern_new = TCanvas("h_ftk_accepted_hitPattern_new", ""); h_ftk_accepted_hitPattern_new.Draw(); ftk_accepted_hitPattern_new.SaveAs("h_divided_ftk_accepted_hitPattern.pdf")
ftk_refit_accepted_hitPattern_new = TCanvas("h_ftk_refit_accepted_hitPattern_new", ""); h_ftk_refit_accepted_hitPattern_new.Draw(); ftk_refit_accepted_hitPattern_new.SaveAs("h_divided_ftk_refit_accepted_hitPattern.pdf")

if isData == False:
	tgae_truth_reco_effi_vs_truth_pt = TCanvas("tgae_truth_reco_effi_vs_truth_pt", "");  tgae_truth_reco_effi_vs_truth_pt_stack.Draw("A");  #tgae_truth_reco_effi_vs_truth_pt.BuildLegend(); 
	tgae_truth_reco_effi_vs_truth_pt.SaveAs("tgae_truth_reco_effi_vs_truth_pt.pdf")
	tgae_truth_reco_effi_vs_truth_eta = TCanvas("tgae_truth_reco_effi_vs_truth_eta", "");  tgae_truth_reco_effi_vs_truth_eta_stack.Draw("A");  #tgae_truth_reco_effi_vs_truth_eta.BuildLegend(); 
	tgae_truth_reco_effi_vs_truth_eta.SaveAs("tgae_truth_reco_effi_vs_truth_eta.pdf")
	tgae_truth_reco_effi_vs_truth_phi = TCanvas("tgae_truth_reco_effi_vs_truth_phi", "");  tgae_truth_reco_effi_vs_truth_phi_stack.Draw("A");  #tgae_truth_reco_effi_vs_truth_phi.BuildLegend(); 
	tgae_truth_reco_effi_vs_truth_phi.SaveAs("tgae_truth_reco_effi_vs_truth_phi.pdf")
	tgae_truth_reco_effi_vs_truth_d0 = TCanvas("tgae_truth_reco_effi_vs_truth_d0", "");  tgae_truth_reco_effi_vs_truth_d0_stack.Draw("A");  #tgae_truth_reco_effi_vs_truth_d0.BuildLegend(); 
	tgae_truth_reco_effi_vs_truth_d0.SaveAs("tgae_truth_reco_effi_vs_truth_d0.pdf")
	tgae_truth_reco_effi_vs_truth_z0 = TCanvas("tgae_truth_reco_effi_vs_truth_z0", "");  tgae_truth_reco_effi_vs_truth_z0_stack.Draw("A");  #tgae_truth_reco_effi_vs_truth_z0.BuildLegend(); 
	tgae_truth_reco_effi_vs_truth_z0.SaveAs("tgae_truth_reco_effi_vs_truth_z0.pdf")

	tgae_truth_ftk_effi_vs_truth_pt = TCanvas("tgae_truth_ftk_effi_vs_truth_pt", "");  tgae_truth_ftk_effi_vs_truth_pt_stack.Draw("A");  #tgae_truth_ftk_effi_vs_truth_pt.BuildLegend(); 
	tgae_truth_ftk_effi_vs_truth_pt.SaveAs("tgae_truth_ftk_effi_vs_truth_pt.pdf")
	tgae_truth_ftk_effi_vs_truth_eta = TCanvas("tgae_truth_ftk_effi_vs_truth_eta", "");  tgae_truth_ftk_effi_vs_truth_eta_stack.Draw("A");  #tgae_truth_ftk_effi_vs_truth_eta.BuildLegend(); 
	tgae_truth_ftk_effi_vs_truth_eta.SaveAs("tgae_truth_ftk_effi_vs_truth_eta.pdf")
	tgae_truth_ftk_effi_vs_truth_phi = TCanvas("tgae_truth_ftk_effi_vs_truth_phi", "");  tgae_truth_ftk_effi_vs_truth_phi_stack.Draw("A"); # tgae_truth_ftk_effi_vs_truth_phi.BuildLegend(); 
	tgae_truth_ftk_effi_vs_truth_phi.SaveAs("tgae_truth_ftk_effi_vs_truth_phi.pdf")
	tgae_truth_ftk_effi_vs_truth_d0 = TCanvas("tgae_truth_ftk_effi_vs_truth_d0", "");  tgae_truth_ftk_effi_vs_truth_d0_stack.Draw("A"); # tgae_truth_ftk_effi_vs_truth_d0.BuildLegend(); 
	tgae_truth_ftk_effi_vs_truth_d0.SaveAs("tgae_truth_ftk_effi_vs_truth_d0.pdf")
	tgae_truth_ftk_effi_vs_truth_z0 = TCanvas("tgae_truth_ftk_effi_vs_truth_z0", "");  tgae_truth_ftk_effi_vs_truth_z0_stack.Draw("A"); # tgae_truth_ftk_effi_vs_truth_z0.BuildLegend(); 
	tgae_truth_ftk_effi_vs_truth_z0.SaveAs("tgae_truth_ftk_effi_vs_truth_z0.pdf")

	tgae_truth_ftk_refit_effi_vs_truth_pt = TCanvas("tgae_truth_ftk_refit_effi_vs_truth_pt", "");  tgae_truth_ftk_refit_effi_vs_truth_pt_stack.Draw("A");  #tgae_truth_ftk_refit_effi_vs_truth_pt.BuildLegend(); 
	tgae_truth_ftk_refit_effi_vs_truth_pt.SaveAs("tgae_truth_ftk_refit_effi_vs_truth_pt.pdf")
	tgae_truth_ftk_refit_effi_vs_truth_eta = TCanvas("tgae_truth_ftk_refit_effi_vs_truth_eta", "");  tgae_truth_ftk_refit_effi_vs_truth_eta_stack.Draw("A"); # tgae_truth_ftk_refit_effi_vs_truth_eta.BuildLegend(); 
	tgae_truth_ftk_refit_effi_vs_truth_eta.SaveAs("tgae_truth_ftk_refit_effi_vs_truth_eta.pdf")
	tgae_truth_ftk_refit_effi_vs_truth_phi = TCanvas("tgae_truth_ftk_refit_effi_vs_truth_phi", "");  tgae_truth_ftk_refit_effi_vs_truth_phi_stack.Draw("A"); # tgae_truth_ftk_refit_effi_vs_truth_phi.BuildLegend(); 
	tgae_truth_ftk_refit_effi_vs_truth_phi.SaveAs("tgae_truth_ftk_refit_effi_vs_truth_phi.pdf")
	tgae_truth_ftk_refit_effi_vs_truth_d0 = TCanvas("tgae_truth_ftk_refit_effi_vs_truth_d0", "");  tgae_truth_ftk_refit_effi_vs_truth_d0_stack.Draw("A"); # tgae_truth_ftk_refit_effi_vs_truth_d0.BuildLegend(); 
	tgae_truth_ftk_refit_effi_vs_truth_d0.SaveAs("tgae_truth_ftk_refit_effi_vs_truth_d0.pdf")
	tgae_truth_ftk_refit_effi_vs_truth_z0 = TCanvas("tgae_truth_ftk_refit_effi_vs_truth_z0", "");  tgae_truth_ftk_refit_effi_vs_truth_z0_stack.Draw("A"); # tgae_truth_ftk_refit_effi_vs_truth_z0.BuildLegend();
	tgae_truth_ftk_refit_effi_vs_truth_z0.SaveAs("tgae_truth_ftk_refit_effi_vs_truth_z0.pdf")

tgae_reco_ftk_effi_vs_reco_pt = TCanvas("tgae_reco_ftk_effi_vs_reco_pt", "");  tgae_reco_ftk_effi_vs_reco_pt_stack.Draw("A"); # tgae_reco_ftk_effi_vs_reco_pt.BuildLegend(); 
tgae_reco_ftk_effi_vs_reco_pt.SaveAs("tgae_reco_ftk_effi_vs_reco_pt.pdf")
tgae_reco_ftk_effi_vs_reco_eta = TCanvas("tgae_reco_ftk_effi_vs_reco_eta", "");  tgae_reco_ftk_effi_vs_reco_eta_stack.Draw("A"); # tgae_reco_ftk_effi_vs_reco_eta.BuildLegend(); 
tgae_reco_ftk_effi_vs_reco_eta.SaveAs("tgae_reco_ftk_effi_vs_reco_eta.pdf")
tgae_reco_ftk_effi_vs_reco_phi = TCanvas("tgae_reco_ftk_effi_vs_reco_phi", "");  tgae_reco_ftk_effi_vs_reco_phi_stack.Draw("A"); # tgae_reco_ftk_effi_vs_reco_phi.BuildLegend(); 
tgae_reco_ftk_effi_vs_reco_phi.SaveAs("tgae_reco_ftk_effi_vs_reco_phi.pdf")
tgae_reco_ftk_effi_vs_reco_d0 = TCanvas("tgae_reco_ftk_effi_vs_reco_d0", "");  tgae_reco_ftk_effi_vs_reco_d0_stack.Draw("A"); # tgae_reco_ftk_effi_vs_reco_d0.BuildLegend(); 
tgae_reco_ftk_effi_vs_reco_d0.SaveAs("tgae_reco_ftk_effi_vs_reco_d0.pdf")
tgae_reco_ftk_effi_vs_reco_z0 = TCanvas("tgae_reco_ftk_effi_vs_reco_z0", "");  tgae_reco_ftk_effi_vs_reco_z0_stack.Draw("A"); # tgae_reco_ftk_effi_vs_reco_z0.BuildLegend(); 
tgae_reco_ftk_effi_vs_reco_z0.SaveAs("tgae_reco_ftk_effi_vs_reco_z0.pdf")

tgae_reco_ftk_refit_effi_vs_reco_pt = TCanvas("tgae_reco_ftk_refit_effi_vs_reco_pt", "");  tgae_reco_ftk_refit_effi_vs_reco_pt_stack.Draw("A"); # tgae_reco_ftk_refit_effi_vs_reco_pt.BuildLegend(); 
tgae_reco_ftk_refit_effi_vs_reco_pt.SaveAs("tgae_reco_ftk_refit_effi_vs_reco_pt.pdf")
tgae_reco_ftk_refit_effi_vs_reco_eta = TCanvas("tgae_reco_ftk_refit_effi_vs_reco_eta", "");  tgae_reco_ftk_refit_effi_vs_reco_eta_stack.Draw("A");  #tgae_reco_ftk_refit_effi_vs_reco_eta.BuildLegend(); 
tgae_reco_ftk_refit_effi_vs_reco_eta.SaveAs("tgae_reco_ftk_refit_effi_vs_reco_eta.pdf")
tgae_reco_ftk_refit_effi_vs_reco_phi = TCanvas("tgae_reco_ftk_refit_effi_vs_reco_phi", "");  tgae_reco_ftk_refit_effi_vs_reco_phi_stack.Draw("A"); # tgae_reco_ftk_refit_effi_vs_reco_phi.BuildLegend(); 
tgae_reco_ftk_refit_effi_vs_reco_phi.SaveAs("tgae_reco_ftk_refit_effi_vs_reco_phi.pdf")
tgae_reco_ftk_refit_effi_vs_reco_d0 = TCanvas("tgae_reco_ftk_refit_effi_vs_reco_d0", "");  tgae_reco_ftk_refit_effi_vs_reco_d0_stack.Draw("A"); # tgae_reco_ftk_refit_effi_vs_reco_d0.BuildLegend(); 
tgae_reco_ftk_refit_effi_vs_reco_d0.SaveAs("tgae_reco_ftk_refit_effi_vs_reco_d0.pdf")
tgae_reco_ftk_refit_effi_vs_reco_z0 = TCanvas("tgae_reco_ftk_refit_effi_vs_reco_z0", "");  tgae_reco_ftk_refit_effi_vs_reco_z0_stack.Draw("A"); # tgae_reco_ftk_refit_effi_vs_reco_z0.BuildLegend(); 
tgae_reco_ftk_refit_effi_vs_reco_z0.SaveAs("tgae_reco_ftk_refit_effi_vs_reco_z0.pdf")

gStyle.SetOptStat(0);legend_canvas = TCanvas("legend", "");legend = TLegend(0.1,0.7,0.48,0.9);legend.AddEntry(h_reco_accepted_pt1, file1_label);legend.AddEntry(h_reco_accepted_pt2, file2_label);legend.Draw(); legend_canvas.SaveAs("legend.pdf")