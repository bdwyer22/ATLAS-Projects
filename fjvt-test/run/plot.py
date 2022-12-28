from ROOT import TFile, TCanvas, THStack, gROOT
from AtlasStyle import *

path_ggH125 = "PowhegPy8_NNLOPS_ggH125/hist-user.bstamas.PowhegPy8_NNLOPS_ggH125_fJVT_MxAOD.root.root "
path_ggH125_h024 = "PowhegPy8_NNLOPS_ggH125_h024/hist-Nominal.root"

path_vbf = "PowhegPy8_NNPDF30_VBFH125/hist-user.bstamas.PowhegPy8_NNPDF30_VBFH125_fJVT_MxAOD.root.root"
path_vbf_h024 = "PowhegPy8_NNPDF30_VBFH125_h024/hist-Nominal.root"

path_sherpa = "Sherpa2_diphoton_myy_90_175/hist-user.bstamas.Sherpa2_diphoton_myy_90_175_fJVT_MxAOD.root.root"
path_sherpa_h024 = "Sherpa2_diphoton_myy_90_175_h024/hist-user.bstamas.Sherpa2_diphoton_myy_90_175_fJVT_h024_MxAOD.root.root"

ggh125 = TFile(path_ggH125)
ggh125_h024 = TFile(path_ggH125_h024)
vbf = TFile(path_vbf)
vbf_h024 = TFile(path_vbf_h024)
sherpa = TFile(path_sherpa)
sherpa_h024 = TFile(path_sherpa_h024)

hist_j130_pt_015_vbf = vbf.Get("hist_j130_pt_015")
hist_j130_pt_1525_vbf = vbf.Get("hist_j130_pt_1525")
hist_j130_pt_2535_vbf = vbf.Get("hist_j130_pt_2535")
hist_j130_pt_3550_vbf = vbf.Get("hist_j130_pt_3550")
# hist_j130_pt_50_vbf = vbf.Get("hist_j130_pt_50")
hist_j130_y_015_vbf = vbf.Get("hist_j130_y_015")
hist_j130_y_1525_vbf = vbf.Get("hist_j130_y_1525")
hist_j130_y_2535_vbf = vbf.Get("hist_j130_y_2535")
hist_j130_y_3550_vbf = vbf.Get("hist_j130_y_3550")
# hist_j130_y_50_vbf = vbf.Get("hist_j130_y_50")
hist_j130_pt_015_fJVT_vbf = vbf.Get("hist_j130_pt_015_fJVT")
hist_j130_pt_1525_fJVT_vbf = vbf.Get("hist_j130_pt_1525_fJVT")
hist_j130_pt_2535_fJVT_vbf = vbf.Get("hist_j130_pt_2535_fJVT")
hist_j130_pt_3550_fJVT_vbf = vbf.Get("hist_j130_pt_3550_fJVT")
# hist_j130_pt_50_fJVT_vbf = vbf.Get("hist_j130_pt_50_fJVT")
hist_j130_y_015_fJVT_vbf = vbf.Get("hist_j130_y_015_fJVT")
hist_j130_y_1525_fJVT_vbf = vbf.Get("hist_j130_y_1525_fJVT")
hist_j130_y_2535_fJVT_vbf = vbf.Get("hist_j130_y_2535_fJVT")
hist_j130_y_3550_fJVT_vbf = vbf.Get("hist_j130_y_3550_fJVT")
# hist_j130_y_50_fJVT_vbf = vbf.Get("hist_j130_y_50_fJVT")
hist_pass_fJVT_vbf = vbf.Get("hist_pass_fJVT")
hist_fail_fJVT_vbf = vbf.Get("hist_fail_fJVT")
hist_n_jets_vbf = vbf.Get("hist_n_jets")
hist_n_jets_fJVT_vbf = vbf.Get("hist_n_jets_fJVT")
hist_alljet_pt_vbf = vbf.Get("hist_alljet_pt")
hist_alljet_pt_fJVT_vbf = vbf.Get("hist_alljet_p_fJVTt")
hist_alljet_eta_vbf = vbf.Get("hist_alljet_eta")
hist_forward_jet_pt_vbf = vbf.Get("hist_forward_jet_pt")
hist_forward_jet_eta_vbf = vbf.Get("hist_forward_jet_eta")
hist_central_jet_pt_vbf = vbf.Get("hist_central_jet_pt")
hist_central_jet_eta_vbf = vbf.Get("hist_central_jet_eta")
hist_forward_jet_pt_fJVT_vbf = vbf.Get("hist_forward_jet_pt_fJVT")
hist_forward_jet_eta_fJVT_vbf = vbf.Get("hist_forward_jet_eta_fJVT")
hist_central_jet_pt_fJVT_vbf = vbf.Get("hist_central_jet_pt_fJVT")
hist_central_jet_eta_fJVT_vbf = vbf.Get("hist_central_jet_eta_fJVT")

hist_j130_pt_015_vbf_h024 = vbf_h024.Get("hist_j130_pt_015")
hist_j130_pt_1525_vbf_h024 = vbf_h024.Get("hist_j130_pt_1525")
hist_j130_pt_2535_vbf_h024 = vbf_h024.Get("hist_j130_pt_2535")
hist_j130_pt_3550_vbf_h024 = vbf_h024.Get("hist_j130_pt_3550")
# hist_j130_pt_50_vbf_h024 = vbf_h024.Get("hist_j130_pt_50")
hist_j130_y_015_vbf_h024 = vbf_h024.Get("hist_j130_y_015")
hist_j130_y_1525_vbf_h024 = vbf_h024.Get("hist_j130_y_1525")
hist_j130_y_2535_vbf_h024 = vbf_h024.Get("hist_j130_y_2535")
hist_j130_y_3550_vbf_h024 = vbf_h024.Get("hist_j130_y_3550")
# hist_j130_y_50_vbf_h024 = vbf_h024.Get("hist_j130_y_50")
hist_j130_pt_015_fJVT_vbf_h024 = vbf_h024.Get("hist_j130_pt_015_fJVT")
hist_j130_pt_1525_fJVT_vbf_h024 = vbf_h024.Get("hist_j130_pt_1525_fJVT")
hist_j130_pt_2535_fJVT_vbf_h024 = vbf_h024.Get("hist_j130_pt_2535_fJVT")
hist_j130_pt_3550_fJVT_vbf_h024 = vbf_h024.Get("hist_j130_pt_3550_fJVT")
# hist_j130_pt_50_fJVT_vbf_h024 = vbf_h024.Get("hist_j130_pt_50_fJVT")
hist_j130_y_015_fJVT_vbf_h024 = vbf_h024.Get("hist_j130_y_015_fJVT")
hist_j130_y_1525_fJVT_vbf_h024 = vbf_h024.Get("hist_j130_y_1525_fJVT")
hist_j130_y_2535_fJVT_vbf_h024 = vbf_h024.Get("hist_j130_y_2535_fJVT")
hist_j130_y_3550_fJVT_vbf_h024 = vbf_h024.Get("hist_j130_y_3550_fJVT")
# hist_j130_y_50_fJVT_vbf_h024 = vbf_h024.Get("hist_j130_y_50_fJVT")
hist_pass_fJVT_vbf_h024 = vbf_h024.Get("hist_pass_fJVT")
hist_fail_fJVT_vbf_h024 = vbf_h024.Get("hist_fail_fJVT")
hist_n_jets_vbf_h024 = vbf_h024.Get("hist_n_jets")
hist_n_jets_fJVT_vbf_h024 = vbf_h024.Get("hist_n_jets_fJVT")
hist_alljet_pt_vbf_h024 = vbf_h024.Get("hist_alljet_pt")
hist_alljet_pt_fJVT_vbf_h024 = vbf_h024.Get("hist_alljet_p_fJVTt")
hist_alljet_eta_vbf_h024 = vbf_h024.Get("hist_alljet_eta")
hist_forward_jet_pt_vbf_h024 = vbf_h024.Get("hist_forward_jet_pt")
hist_forward_jet_eta_vbf_h024 = vbf_h024.Get("hist_forward_jet_eta")
hist_central_jet_pt_vbf_h024 = vbf_h024.Get("hist_central_jet_pt")
hist_central_jet_eta_vbf_h024 = vbf_h024.Get("hist_central_jet_eta")
hist_forward_jet_pt_fJVT_vbf_h024 = vbf_h024.Get("hist_forward_jet_pt_fJVT")
hist_forward_jet_eta_fJVT_vbf_h024 = vbf_h024.Get("hist_forward_jet_eta_fJVT")
hist_central_jet_pt_fJVT_vbf_h024 = vbf_h024.Get("hist_central_jet_pt_fJVT")
hist_central_jet_eta_fJVT_vbf_h024 = vbf_h024.Get("hist_central_jet_eta_fJVT")

hist_j130_pt_015_ggh125 = ggh125.Get("hist_j130_pt_015")
hist_j130_pt_1525_ggh125 = ggh125.Get("hist_j130_pt_1525")
hist_j130_pt_2535_ggh125 = ggh125.Get("hist_j130_pt_2535")
hist_j130_pt_3550_ggh125 = ggh125.Get("hist_j130_pt_3550")
# hist_j130_pt_50_ggh125 = ggh125.Get("hist_j130_pt_50")
hist_j130_y_015_ggh125 = ggh125.Get("hist_j130_y_015")
hist_j130_y_1525_ggh125 = ggh125.Get("hist_j130_y_1525")
hist_j130_y_2535_ggh125 = ggh125.Get("hist_j130_y_2535")
hist_j130_y_3550_ggh125 = ggh125.Get("hist_j130_y_3550")
# hist_j130_y_50_ggh125 = ggh125.Get("hist_j130_y_50")
hist_j130_pt_015_fJVT_ggh125 = ggh125.Get("hist_j130_pt_015_fJVT")
hist_j130_pt_1525_fJVT_ggh125 = ggh125.Get("hist_j130_pt_1525_fJVT")
hist_j130_pt_2535_fJVT_ggh125 = ggh125.Get("hist_j130_pt_2535_fJVT")
hist_j130_pt_3550_fJVT_ggh125 = ggh125.Get("hist_j130_pt_3550_fJVT")
# hist_j130_pt_50_fJVT_ggh125 = ggh125.Get("hist_j130_pt_50_fJVT")
hist_j130_y_015_fJVT_ggh125 = ggh125.Get("hist_j130_y_015_fJVT")
hist_j130_y_1525_fJVT_ggh125 = ggh125.Get("hist_j130_y_1525_fJVT")
hist_j130_y_2535_fJVT_ggh125 = ggh125.Get("hist_j130_y_2535_fJVT")
hist_j130_y_3550_fJVT_ggh125 = ggh125.Get("hist_j130_y_3550_fJVT")
# hist_j130_y_50_fJVT_ggh125 = ggh125.Get("hist_j130_y_50_fJVT")
hist_pass_fJVT_ggh125 = ggh125.Get("hist_pass_fJVT")
hist_fail_fJVT_ggh125 = ggh125.Get("hist_fail_fJVT")
hist_n_jets_ggh125 = ggh125.Get("hist_n_jets")
hist_n_jets_fJVT_ggh125 = ggh125.Get("hist_n_jets_fJVT")
hist_alljet_pt_ggh125 = ggh125.Get("hist_alljet_pt")
hist_alljet_pt_fJVT_ggh125 = ggh125.Get("hist_alljet_p_fJVTt")
hist_alljet_eta_ggh125 = ggh125.Get("hist_alljet_eta")
hist_forward_jet_pt_ggh125 = ggh125.Get("hist_forward_jet_pt")
hist_forward_jet_eta_ggh125 = ggh125.Get("hist_forward_jet_eta")
hist_central_jet_pt_ggh125 = ggh125.Get("hist_central_jet_pt")
hist_central_jet_eta_ggh125 = ggh125.Get("hist_central_jet_eta")
hist_forward_jet_pt_fJVT_ggh125 = ggh125.Get("hist_forward_jet_pt_fJVT")
hist_forward_jet_eta_fJVT_ggh125 = ggh125.Get("hist_forward_jet_eta_fJVT")
hist_central_jet_pt_fJVT_ggh125 = ggh125.Get("hist_central_jet_pt_fJVT")
hist_central_jet_eta_fJVT_ggh125 = ggh125.Get("hist_central_jet_eta_fJVT")

hist_j130_pt_015_ggh125_h024 = ggh125_h024.Get("hist_j130_pt_015")
hist_j130_pt_1525_ggh125_h024 = ggh125_h024.Get("hist_j130_pt_1525")
hist_j130_pt_2535_ggh125_h024 = ggh125_h024.Get("hist_j130_pt_2535")
hist_j130_pt_3550_ggh125_h024 = ggh125_h024.Get("hist_j130_pt_3550")
# hist_j130_pt_50_ggh125_h024 = ggh125_h024.Get("hist_j130_pt_50")
hist_j130_y_015_ggh125_h024 = ggh125_h024.Get("hist_j130_y_015")
hist_j130_y_1525_ggh125_h024 = ggh125_h024.Get("hist_j130_y_1525")
hist_j130_y_2535_ggh125_h024 = ggh125_h024.Get("hist_j130_y_2535")
hist_j130_y_3550_ggh125_h024 = ggh125_h024.Get("hist_j130_y_3550")
# hist_j130_y_50_ggh125_h024 = ggh125_h024.Get("hist_j130_y_50")
hist_j130_pt_015_fJVT_ggh125_h024 = ggh125_h024.Get("hist_j130_pt_015_fJVT")
hist_j130_pt_1525_fJVT_ggh125_h024 = ggh125_h024.Get("hist_j130_pt_1525_fJVT")
hist_j130_pt_2535_fJVT_ggh125_h024 = ggh125_h024.Get("hist_j130_pt_2535_fJVT")
hist_j130_pt_3550_fJVT_ggh125_h024 = ggh125_h024.Get("hist_j130_pt_3550_fJVT")
# hist_j130_pt_50_fJVT_ggh125_h024 = ggh125_h024.Get("hist_j130_pt_50_fJVT")
hist_j130_y_015_fJVT_ggh125_h024 = ggh125_h024.Get("hist_j130_y_015_fJVT")
hist_j130_y_1525_fJVT_ggh125_h024 = ggh125_h024.Get("hist_j130_y_1525_fJVT")
hist_j130_y_2535_fJVT_ggh125_h024 = ggh125_h024.Get("hist_j130_y_2535_fJVT")
hist_j130_y_3550_fJVT_ggh125_h024 = ggh125_h024.Get("hist_j130_y_3550_fJVT")
# hist_j130_y_50_fJVT_ggh125_h024 = ggh125_h024.Get("hist_j130_y_50_fJVT")
hist_pass_fJVT_ggh125_h024 = ggh125_h024.Get("hist_pass_fJVT")
hist_fail_fJVT_ggh125_h024 = ggh125_h024.Get("hist_fail_fJVT")
hist_n_jets_ggh125_h024 = ggh125_h024.Get("hist_n_jets")
hist_n_jets_fJVT_ggh125_h024 = ggh125_h024.Get("hist_n_jets_fJVT")
hist_alljet_pt_ggh125_h024 = ggh125_h024.Get("hist_alljet_pt")
hist_alljet_pt_fJVT_ggh125_h024 = ggh125_h024.Get("hist_alljet_p_fJVTt")
hist_alljet_eta_ggh125_h024 = ggh125_h024.Get("hist_alljet_eta")
hist_forward_jet_pt_ggh125_h024 = ggh125_h024.Get("hist_forward_jet_pt")
hist_forward_jet_eta_ggh125_h024 = ggh125_h024.Get("hist_forward_jet_eta")
hist_central_jet_pt_ggh125_h024 = ggh125_h024.Get("hist_central_jet_pt")
hist_central_jet_eta_ggh125_h024 = ggh125_h024.Get("hist_central_jet_eta")
hist_forward_jet_pt_fJVT_ggh125_h024 = ggh125_h024.Get("hist_forward_jet_pt_fJVT")
hist_forward_jet_eta_fJVT_ggh125_h024 = ggh125_h024.Get("hist_forward_jet_eta_fJVT")
hist_central_jet_pt_fJVT_ggh125_h024 = ggh125_h024.Get("hist_central_jet_pt_fJVT")
hist_central_jet_eta_fJVT_ggh125_h024 = ggh125_h024.Get("hist_central_jet_eta_fJVT")

hist_j130_pt_015_sherpa = sherpa.Get("hist_j130_pt_015")
hist_j130_pt_1525_sherpa = sherpa.Get("hist_j130_pt_1525")
hist_j130_pt_2535_sherpa = sherpa.Get("hist_j130_pt_2535")
hist_j130_pt_3550_sherpa = sherpa.Get("hist_j130_pt_3550")
# hist_j130_pt_50_sherpa = sherpa.Get("hist_j130_pt_50")
hist_j130_y_015_sherpa = sherpa.Get("hist_j130_y_015")
hist_j130_y_1525_sherpa = sherpa.Get("hist_j130_y_1525")
hist_j130_y_2535_sherpa = sherpa.Get("hist_j130_y_2535")
hist_j130_y_3550_sherpa = sherpa.Get("hist_j130_y_3550")
# hist_j130_y_50_sherpa = sherpa.Get("hist_j130_y_50")
hist_j130_pt_015_fJVT_sherpa = sherpa.Get("hist_j130_pt_015_fJVT")
hist_j130_pt_1525_fJVT_sherpa = sherpa.Get("hist_j130_pt_1525_fJVT")
hist_j130_pt_2535_fJVT_sherpa = sherpa.Get("hist_j130_pt_2535_fJVT")
hist_j130_pt_3550_fJVT_sherpa = sherpa.Get("hist_j130_pt_3550_fJVT")
# hist_j130_pt_50_fJVT_sherpa = sherpa.Get("hist_j130_pt_50_fJVT")
hist_j130_y_015_fJVT_sherpa = sherpa.Get("hist_j130_y_015_fJVT")
hist_j130_y_1525_fJVT_sherpa = sherpa.Get("hist_j130_y_1525_fJVT")
hist_j130_y_2535_fJVT_sherpa = sherpa.Get("hist_j130_y_2535_fJVT")
hist_j130_y_3550_fJVT_sherpa = sherpa.Get("hist_j130_y_3550_fJVT")
# hist_j130_y_50_fJVT_sherpa = sherpa.Get("hist_j130_y_50_fJVT")
hist_pass_fJVT_sherpa = sherpa.Get("hist_pass_fJVT")
hist_fail_fJVT_sherpa = sherpa.Get("hist_fail_fJVT")
hist_n_jets_sherpa = sherpa.Get("hist_n_jets")
hist_n_jets_fJVT_sherpa = sherpa.Get("hist_n_jets_fJVT")
hist_alljet_pt_sherpa = sherpa.Get("hist_alljet_pt")
hist_alljet_pt_fJVT_sherpa = sherpa.Get("hist_alljet_p_fJVTt")
hist_alljet_eta_sherpa = sherpa.Get("hist_alljet_eta")
hist_forward_jet_pt_sherpa = sherpa.Get("hist_forward_jet_pt")
hist_forward_jet_eta_sherpa = sherpa.Get("hist_forward_jet_eta")
hist_central_jet_pt_sherpa = sherpa.Get("hist_central_jet_pt")
hist_central_jet_eta_sherpa = sherpa.Get("hist_central_jet_eta")
hist_forward_jet_pt_fJVT_sherpa = sherpa.Get("hist_forward_jet_pt_fJVT")
hist_forward_jet_eta_fJVT_sherpa = sherpa.Get("hist_forward_jet_eta_fJVT")
hist_central_jet_pt_fJVT_sherpa = sherpa.Get("hist_central_jet_pt_fJVT")
hist_central_jet_eta_fJVT_sherpa = sherpa.Get("hist_central_jet_eta_fJVT")

hist_j130_pt_015_sherpa_h024 = sherpa_h024.Get("hist_j130_pt_015")
hist_j130_pt_1525_sherpa_h024 = sherpa_h024.Get("hist_j130_pt_1525")
hist_j130_pt_2535_sherpa_h024 = sherpa_h024.Get("hist_j130_pt_2535")
hist_j130_pt_3550_sherpa_h024 = sherpa_h024.Get("hist_j130_pt_3550")
# hist_j130_pt_50_sherpa_h024 = sherpa_h024.Get("hist_j130_pt_50")
hist_j130_y_015_sherpa_h024 = sherpa_h024.Get("hist_j130_y_015")
hist_j130_y_1525_sherpa_h024 = sherpa_h024.Get("hist_j130_y_1525")
hist_j130_y_2535_sherpa_h024 = sherpa_h024.Get("hist_j130_y_2535")
hist_j130_y_3550_sherpa_h024 = sherpa_h024.Get("hist_j130_y_3550")
# hist_j130_y_50_sherpa_h024 = sherpa_h024.Get("hist_j130_y_50")
hist_j130_pt_015_fJVT_sherpa_h024 = sherpa_h024.Get("hist_j130_pt_015_fJVT")
hist_j130_pt_1525_fJVT_sherpa_h024 = sherpa_h024.Get("hist_j130_pt_1525_fJVT")
hist_j130_pt_2535_fJVT_sherpa_h024 = sherpa_h024.Get("hist_j130_pt_2535_fJVT")
hist_j130_pt_3550_fJVT_sherpa_h024 = sherpa_h024.Get("hist_j130_pt_3550_fJVT")
# hist_j130_pt_50_fJVT_sherpa_h024 = sherpa_h024.Get("hist_j130_pt_50_fJVT")
hist_j130_y_015_fJVT_sherpa_h024 = sherpa_h024.Get("hist_j130_y_015_fJVT")
hist_j130_y_1525_fJVT_sherpa_h024 = sherpa_h024.Get("hist_j130_y_1525_fJVT")
hist_j130_y_2535_fJVT_sherpa_h024 = sherpa_h024.Get("hist_j130_y_2535_fJVT")
hist_j130_y_3550_fJVT_sherpa_h024 = sherpa_h024.Get("hist_j130_y_3550_fJVT")
# hist_j130_y_50_fJVT_sherpa_h024 = sherpa_h024.Get("hist_j130_y_50_fJVT")
hist_pass_fJVT_sherpa_h024 = sherpa_h024.Get("hist_pass_fJVT")
hist_fail_fJVT_sherpa_h024 = sherpa_h024.Get("hist_fail_fJVT")
hist_n_jets_sherpa_h024 = sherpa_h024.Get("hist_n_jets")
hist_n_jets_fJVT_sherpa_h024 = sherpa_h024.Get("hist_n_jets_fJVT")
hist_alljet_pt_sherpa_h024 = sherpa_h024.Get("hist_alljet_pt")
hist_alljet_pt_fJVT_sherpa_h024 = sherpa_h024.Get("hist_alljet_p_fJVTt")
hist_alljet_eta_sherpa_h024 = sherpa_h024.Get("hist_alljet_eta")
hist_forward_jet_pt_sherpa_h024 = sherpa_h024.Get("hist_forward_jet_pt")
hist_forward_jet_eta_sherpa_h024 = sherpa_h024.Get("hist_forward_jet_eta")
hist_central_jet_pt_sherpa_h024 = sherpa_h024.Get("hist_central_jet_pt")
hist_central_jet_eta_sherpa_h024 = sherpa_h024.Get("hist_central_jet_eta")
hist_forward_jet_pt_fJVT_sherpa_h024 = sherpa_h024.Get("hist_forward_jet_pt_fJVT")
hist_forward_jet_eta_fJVT_sherpa_h024 = sherpa_h024.Get("hist_forward_jet_eta_fJVT")
hist_central_jet_pt_fJVT_sherpa_h024 = sherpa_h024.Get("hist_central_jet_pt_fJVT")
hist_central_jet_eta_fJVT_sherpa_h024 = sherpa_h024.Get("hist_central_jet_eta_fJVT")

# hist_alljet_pt_fJVT_vbf.Draw()
# raw_input("enter please")
# hist_j130_pt_sherpa_h024
# hist_j130_eta_sherpa_h024

# hist_j130_pt_fJVT_sherpa_h024
# hist_j130_eta_fJVT_sherpa_h024

# hist_n_jets_sherpa_h024
# hist_n_jets_fJVT_sherpa_h024
hist_list = [hist_j130_pt_015_vbf,
	hist_j130_pt_1525_vbf,
	hist_j130_pt_2535_vbf,
	hist_j130_pt_3550_vbf,
	# hist_j130_pt_50_vbf,
	hist_j130_y_015_vbf,
	hist_j130_y_1525_vbf,
	hist_j130_y_2535_vbf,
	hist_j130_y_3550_vbf,
	# hist_j130_y_50_vbf,
	hist_j130_pt_015_fJVT_vbf,
	hist_j130_pt_1525_fJVT_vbf,
	hist_j130_pt_2535_fJVT_vbf,
	hist_j130_pt_3550_fJVT_vbf,
	# hist_j130_pt_50_fJVT_vbf,
	hist_j130_y_015_fJVT_vbf,
	hist_j130_y_1525_fJVT_vbf,
	hist_j130_y_2535_fJVT_vbf,
	hist_j130_y_3550_fJVT_vbf,
	# hist_j130_y_50_fJVT_vbf,
	hist_pass_fJVT_vbf,
	hist_fail_fJVT_vbf,
	hist_n_jets_vbf,
	hist_n_jets_fJVT_vbf,
	hist_alljet_pt_vbf,
	hist_alljet_pt_fJVT_vbf,
	hist_alljet_eta_vbf,
	hist_forward_jet_pt_vbf,
	hist_forward_jet_eta_vbf,
	hist_central_jet_pt_vbf,
	hist_central_jet_eta_vbf,
	hist_forward_jet_pt_fJVT_vbf,
	hist_forward_jet_eta_fJVT_vbf,
	hist_central_jet_pt_fJVT_vbf,
	hist_central_jet_eta_fJVT_vbf,
	hist_j130_pt_015_vbf_h024,
	hist_j130_pt_1525_vbf_h024,
	hist_j130_pt_2535_vbf_h024,
	hist_j130_pt_3550_vbf_h024,
	# hist_j130_pt_50_vbf_h024,
	hist_j130_y_015_vbf_h024,
	hist_j130_y_1525_vbf_h024,
	hist_j130_y_2535_vbf_h024,
	hist_j130_y_3550_vbf_h024,
	# hist_j130_y_50_vbf_h024,
	hist_j130_pt_015_fJVT_vbf_h024,
	hist_j130_pt_1525_fJVT_vbf_h024,
	hist_j130_pt_2535_fJVT_vbf_h024,
	hist_j130_pt_3550_fJVT_vbf_h024,
	# hist_j130_pt_50_fJVT_vbf_h024,
	hist_j130_y_015_fJVT_vbf_h024,
	hist_j130_y_1525_fJVT_vbf_h024,
	hist_j130_y_2535_fJVT_vbf_h024,
	hist_j130_y_3550_fJVT_vbf_h024,
	# hist_j130_y_50_fJVT_vbf_h024,
	hist_pass_fJVT_vbf_h024,
	hist_fail_fJVT_vbf_h024,
	hist_n_jets_vbf_h024,
	hist_n_jets_fJVT_vbf_h024,
	hist_alljet_pt_vbf_h024,
	hist_alljet_pt_fJVT_vbf_h024,
	hist_alljet_eta_vbf_h024,
	hist_forward_jet_pt_vbf_h024,
	hist_forward_jet_eta_vbf_h024,
	hist_central_jet_pt_vbf_h024,
	hist_central_jet_eta_vbf_h024,
	hist_forward_jet_pt_fJVT_vbf_h024,
	hist_forward_jet_eta_fJVT_vbf_h024,
	hist_central_jet_pt_fJVT_vbf_h024,
	hist_central_jet_eta_fJVT_vbf_h024,
	hist_j130_pt_015_ggh125,
	hist_j130_pt_1525_ggh125,
	hist_j130_pt_2535_ggh125,
	hist_j130_pt_3550_ggh125,
	# hist_j130_pt_50_ggh125,
	hist_j130_y_015_ggh125,
	hist_j130_y_1525_ggh125,
	hist_j130_y_2535_ggh125,
	hist_j130_y_3550_ggh125,
	# hist_j130_y_50_ggh125,
	hist_j130_pt_015_fJVT_ggh125,
	hist_j130_pt_1525_fJVT_ggh125,
	hist_j130_pt_2535_fJVT_ggh125,
	hist_j130_pt_3550_fJVT_ggh125,
	# hist_j130_pt_50_fJVT_ggh125,
	hist_j130_y_015_fJVT_ggh125,
	hist_j130_y_1525_fJVT_ggh125,
	hist_j130_y_2535_fJVT_ggh125,
	hist_j130_y_3550_fJVT_ggh125,
	# hist_j130_y_50_fJVT_ggh125,
	hist_pass_fJVT_ggh125,
	hist_fail_fJVT_ggh125,
	hist_n_jets_ggh125,
	hist_n_jets_fJVT_ggh125,
	hist_alljet_pt_ggh125,
	hist_alljet_pt_fJVT_ggh125,
	hist_alljet_eta_ggh125,
	hist_forward_jet_pt_ggh125,
	hist_forward_jet_eta_ggh125,
	hist_central_jet_pt_ggh125,
	hist_central_jet_eta_ggh125,
	hist_forward_jet_pt_fJVT_ggh125,
	hist_forward_jet_eta_fJVT_ggh125,
	hist_central_jet_pt_fJVT_ggh125,
	hist_central_jet_eta_fJVT_ggh125,
	hist_j130_pt_015_ggh125_h024,
	hist_j130_pt_1525_ggh125_h024,
	hist_j130_pt_2535_ggh125_h024,
	hist_j130_pt_3550_ggh125_h024,
	# hist_j130_pt_50_ggh125_h024,
	hist_j130_y_015_ggh125_h024,
	hist_j130_y_1525_ggh125_h024,
	hist_j130_y_2535_ggh125_h024,
	hist_j130_y_3550_ggh125_h024,
	# hist_j130_y_50_ggh125_h024,
	hist_j130_pt_015_fJVT_ggh125_h024,
	hist_j130_pt_1525_fJVT_ggh125_h024,
	hist_j130_pt_2535_fJVT_ggh125_h024,
	hist_j130_pt_3550_fJVT_ggh125_h024,
	# hist_j130_pt_50_fJVT_ggh125_h024,
	hist_j130_y_015_fJVT_ggh125_h024,
	hist_j130_y_1525_fJVT_ggh125_h024,
	hist_j130_y_2535_fJVT_ggh125_h024,
	hist_j130_y_3550_fJVT_ggh125_h024,
	# hist_j130_y_50_fJVT_ggh125_h024,
	hist_pass_fJVT_ggh125_h024,
	hist_fail_fJVT_ggh125_h024,
	hist_n_jets_ggh125_h024,
	hist_n_jets_fJVT_ggh125_h024,
	hist_alljet_pt_ggh125_h024,
	hist_alljet_pt_fJVT_ggh125_h024,
	hist_alljet_eta_ggh125_h024,
	hist_forward_jet_pt_ggh125_h024,
	hist_forward_jet_eta_ggh125_h024,
	hist_central_jet_pt_ggh125_h024,
	hist_central_jet_eta_ggh125_h024,
	hist_forward_jet_pt_fJVT_ggh125_h024,
	hist_forward_jet_eta_fJVT_ggh125_h024,
	hist_central_jet_pt_fJVT_ggh125_h024,
	hist_central_jet_eta_fJVT_ggh125_h024,
	hist_j130_pt_015_sherpa,
	hist_j130_pt_1525_sherpa,
	hist_j130_pt_2535_sherpa,
	hist_j130_pt_3550_sherpa,
	# hist_j130_pt_50_sherpa,
	hist_j130_y_015_sherpa,
	hist_j130_y_1525_sherpa,
	hist_j130_y_2535_sherpa,
	hist_j130_y_3550_sherpa,
	# hist_j130_y_50_sherpa,
	hist_j130_pt_015_fJVT_sherpa,
	hist_j130_pt_1525_fJVT_sherpa,
	hist_j130_pt_2535_fJVT_sherpa,
	hist_j130_pt_3550_fJVT_sherpa,
	# hist_j130_pt_50_fJVT_sherpa,
	hist_j130_y_015_fJVT_sherpa,
	hist_j130_y_1525_fJVT_sherpa,
	hist_j130_y_2535_fJVT_sherpa,
	hist_j130_y_3550_fJVT_sherpa,
	# hist_j130_y_50_fJVT_sherpa,
	hist_pass_fJVT_sherpa,
	hist_fail_fJVT_sherpa,
	hist_n_jets_sherpa,
	hist_n_jets_fJVT_sherpa,
	hist_alljet_pt_sherpa,
	hist_alljet_pt_fJVT_sherpa,
	hist_alljet_eta_sherpa,
	hist_forward_jet_pt_sherpa,
	hist_forward_jet_eta_sherpa,
	hist_central_jet_pt_sherpa,
	hist_central_jet_eta_sherpa,
	hist_forward_jet_pt_fJVT_sherpa,
	hist_forward_jet_eta_fJVT_sherpa,
	hist_central_jet_pt_fJVT_sherpa,
	hist_central_jet_eta_fJVT_sherpa,
	hist_j130_pt_015_sherpa_h024,
	hist_j130_pt_1525_sherpa_h024,
	hist_j130_pt_2535_sherpa_h024,
	hist_j130_pt_3550_sherpa_h024,
	# hist_j130_pt_50_sherpa_h024,
	hist_j130_y_015_sherpa_h024,
	hist_j130_y_1525_sherpa_h024,
	hist_j130_y_2535_sherpa_h024,
	hist_j130_y_3550_sherpa_h024,
	# hist_j130_y_50_sherpa_h024,
	hist_j130_pt_015_fJVT_sherpa_h024,
	hist_j130_pt_1525_fJVT_sherpa_h024,
	hist_j130_pt_2535_fJVT_sherpa_h024,
	hist_j130_pt_3550_fJVT_sherpa_h024,
	# hist_j130_pt_50_fJVT_sherpa_h024,
	hist_j130_y_015_fJVT_sherpa_h024,
	hist_j130_y_1525_fJVT_sherpa_h024,
	hist_j130_y_2535_fJVT_sherpa_h024,
	hist_j130_y_3550_fJVT_sherpa_h024,
	# hist_j130_y_50_fJVT_sherpa_h024,
	hist_pass_fJVT_sherpa_h024,
	hist_fail_fJVT_sherpa_h024,
	hist_n_jets_sherpa_h024,
	hist_n_jets_fJVT_sherpa_h024,
	hist_alljet_pt_sherpa_h024,
	hist_alljet_pt_fJVT_sherpa_h024,
	hist_alljet_eta_sherpa_h024,
	hist_forward_jet_pt_sherpa_h024,
	hist_forward_jet_eta_sherpa_h024,
	hist_central_jet_pt_sherpa_h024,
	hist_central_jet_eta_sherpa_h024,
	hist_forward_jet_pt_fJVT_sherpa_h024,
	hist_forward_jet_eta_fJVT_sherpa_h024,
	hist_central_jet_pt_fJVT_sherpa_h024,
	hist_central_jet_eta_fJVT_sherpa_h024]

for hist in hist_list:
	# print(hist)
	norm = hist.Integral(); #print norm
	if norm != 0:
		hist.Scale(1./norm)
	else:
		print("no events in "+str(hist.GetName()))

def passtack():
	c1 = TCanvas("c1", "")
	pass_stack = THStack("pass_stack", "")
	hist_pass_fJVT_sherpa_h024.SetLineWidth(2)
	hist_pass_fJVT_sherpa_h024.SetLineColor(1)
	hist_pass_fJVT_sherpa_h024.SetTitle("Sherpa2_diphoton_h024")
	hist_pass_fJVT_sherpa_h024.SetLineStyle(2)
	hist_pass_fJVT_sherpa.SetLineWidth(2)
	hist_pass_fJVT_sherpa.SetLineColor(1)
	hist_pass_fJVT_sherpa.SetTitle("Sherpa2_diphoton_fJVT")

	hist_pass_fJVT_vbf_h024.SetLineColor(2)
	hist_pass_fJVT_vbf_h024.SetLineWidth(2)
	hist_pass_fJVT_vbf_h024.SetTitle("PowhegPy8_NNPDF30_VBFH125_h024")
	hist_pass_fJVT_vbf_h024.SetLineStyle(2)
	hist_pass_fJVT_vbf.SetLineColor(2)
	hist_pass_fJVT_vbf.SetLineWidth(2)
	hist_pass_fJVT_vbf.SetTitle("PowhegPy8_NNPDF30_VBFH125_fJVT")

	hist_pass_fJVT_ggh125_h024.SetLineColor(4)
	hist_pass_fJVT_ggh125_h024.SetLineWidth(2)
	hist_pass_fJVT_ggh125_h024.SetTitle("PowhegPy8_NNLOPS_ggH125_h024")
	hist_pass_fJVT_ggh125_h024.SetLineStyle(2)
	hist_pass_fJVT_ggh125.SetLineColor(4)
	hist_pass_fJVT_ggh125.SetLineWidth(2)
	hist_pass_fJVT_ggh125.SetTitle("PowhegPy8_NNLOPS_ggH125_fJVT")

	pass_stack.Add(hist_pass_fJVT_sherpa_h024, "HIST")
	pass_stack.Add(hist_pass_fJVT_ggh125_h024, "HIST")
	pass_stack.Add(hist_pass_fJVT_vbf_h024, "HIST")
	pass_stack.Add(hist_pass_fJVT_sherpa, "HIST")
	pass_stack.Add(hist_pass_fJVT_ggh125, "HIST")
	pass_stack.Add(hist_pass_fJVT_vbf, "HIST")
	pass_stack.Draw("nostack")
	pass_stack.GetXaxis().SetTitle("#eta");
	pass_stack.GetYaxis().SetTitle("Normalized A.U.");
	pass_stack.SetTitle("Passed fJVT")
	c1.BuildLegend()
	c1.SaveAs("pass_fjvt_eta.pdf")
	# raw_input("enter plz")

def failstack():
	c2 = TCanvas("c2", "")
	fail_stack = THStack("fail_stack", "")
	hist_fail_fJVT_sherpa_h024.SetLineColor(1)
	hist_fail_fJVT_sherpa_h024.SetLineWidth(2)
	hist_fail_fJVT_sherpa_h024.SetTitle("Sherpa2_diphoton_h024")
	hist_fail_fJVT_sherpa_h024.SetLineStyle(2)
	hist_fail_fJVT_sherpa.SetLineColor(1)
	hist_fail_fJVT_sherpa.SetLineWidth(2)
	hist_fail_fJVT_sherpa.SetTitle("Sherpa2_diphoton_fJVT")

	hist_fail_fJVT_vbf_h024.SetLineColor(2)
	hist_fail_fJVT_vbf_h024.SetLineWidth(2)
	hist_fail_fJVT_vbf_h024.SetTitle("PowhegPy8_NNPDF30_VBFH125_h024")
	hist_fail_fJVT_vbf_h024.SetLineStyle(2)
	hist_fail_fJVT_vbf.SetLineColor(2)
	hist_fail_fJVT_vbf.SetLineWidth(2)
	hist_fail_fJVT_vbf.SetTitle("PowhegPy8_NNPDF30_VBFH125_fJVT")

	hist_fail_fJVT_ggh125_h024.SetLineColor(4)
	hist_fail_fJVT_ggh125_h024.SetLineWidth(2)
	hist_fail_fJVT_ggh125_h024.SetTitle("PowhegPy8_NNLOPS_ggH125_h024")
	hist_fail_fJVT_ggh125_h024.SetLineStyle(2)
	hist_fail_fJVT_ggh125.SetLineColor(4)
	hist_fail_fJVT_ggh125.SetLineWidth(2)
	hist_fail_fJVT_ggh125.SetTitle("PowhegPy8_NNLOPS_ggH125_fJVT")

	fail_stack.Add(hist_fail_fJVT_sherpa_h024, "HIST")
	fail_stack.Add(hist_fail_fJVT_ggh125_h024, "HIST")
	fail_stack.Add(hist_fail_fJVT_vbf_h024, "HIST")
	fail_stack.Add(hist_fail_fJVT_sherpa, "HIST")
	fail_stack.Add(hist_fail_fJVT_ggh125, "HIST")
	fail_stack.Add(hist_fail_fJVT_vbf, "HIST")
	fail_stack.Draw("nostack")
	fail_stack.GetXaxis().SetTitle("#eta");
	fail_stack.GetYaxis().SetTitle("Normalized A.U.");
	fail_stack.SetTitle("Failed fJVT")
	c2.BuildLegend()
	c2.SaveAs("fail_fjvt_eta.pdf")
	# raw_input("enter plz")

def njetstack():
	c3 = TCanvas("c3", "")
	njet_stack = THStack("njet_stack", "")
	hist_n_jets_sherpa_h024.SetLineColor(1)
	hist_n_jets_sherpa_h024.SetTitle("Sherpa2_diphoton_h024")
	hist_n_jets_sherpa_h024.SetLineStyle(5)
	hist_n_jets_sherpa.SetLineColor(1)
	hist_n_jets_sherpa.SetTitle("Sherpa2_diphoton_fJVT")

	hist_n_jets_vbf_h024.SetLineColor(2)
	hist_n_jets_vbf_h024.SetTitle("PowhegPy8_NNPDF30_VBFH125_h024")
	hist_n_jets_vbf_h024.SetLineStyle(5)
	hist_n_jets_vbf.SetLineColor(2)
	hist_n_jets_vbf.SetTitle("PowhegPy8_NNPDF30_VBFH125_fJVT")

	hist_n_jets_ggh125_h024.SetLineColor(4)
	hist_n_jets_ggh125_h024.SetTitle("PowhegPy8_NNLOPS_ggH125_h024")
	hist_n_jets_ggh125_h024.SetLineStyle(5)
	hist_n_jets_ggh125.SetLineColor(4)
	hist_n_jets_ggh125.SetTitle("PowhegPy8_NNLOPS_ggH125_fJVT")

	njet_stack.Add(hist_n_jets_sherpa_h024, "HIST")
	njet_stack.Add(hist_n_jets_ggh125_h024, "HIST")
	njet_stack.Add(hist_n_jets_vbf_h024, "HIST")
	njet_stack.Add(hist_n_jets_sherpa, "HIST")
	njet_stack.Add(hist_n_jets_ggh125, "HIST")
	njet_stack.Add(hist_n_jets_vbf, "HIST")
	njet_stack.Draw("nostack")
	njet_stack.GetXaxis().SetTitle("Number of Jets");
	njet_stack.GetYaxis().SetTitle("Normalized A.U.");
	c3.BuildLegend()
	c3.SaveAs("njets_nofJVT.pdf")
	# raw_input("enter plz")

def njetfjvtstack():
	c4 = TCanvas("c4", "")
	njet_stack = THStack("njet_stack", "")
	hist_n_jets_fJVT_sherpa_h024.SetLineColor(1)
	hist_n_jets_fJVT_sherpa_h024.SetTitle("Sherpa2_diphoton_h024")
	hist_n_jets_fJVT_sherpa_h024.SetLineStyle(5)
	hist_n_jets_fJVT_sherpa.SetLineColor(1)
	hist_n_jets_fJVT_sherpa.SetTitle("Sherpa2_diphoton_fJVT")

	hist_n_jets_fJVT_vbf_h024.SetLineColor(2)
	hist_n_jets_fJVT_vbf_h024.SetTitle("PowhegPy8_NNPDF30_VBFH125_h024")
	hist_n_jets_fJVT_vbf_h024.SetLineStyle(5)
	hist_n_jets_fJVT_vbf.SetLineColor(2)
	hist_n_jets_fJVT_vbf.SetTitle("PowhegPy8_NNPDF30_VBFH125_fJVT")

	hist_n_jets_fJVT_ggh125_h024.SetLineColor(4)
	hist_n_jets_fJVT_ggh125_h024.SetTitle("PowhegPy8_NNLOPS_ggH125_h024")
	hist_n_jets_fJVT_ggh125_h024.SetLineStyle(5)
	hist_n_jets_fJVT_ggh125.SetLineColor(4)
	hist_n_jets_fJVT_ggh125.SetTitle("PowhegPy8_NNLOPS_ggH125_fJVT")

	njet_stack.Add(hist_n_jets_fJVT_sherpa_h024, "HIST")
	njet_stack.Add(hist_n_jets_fJVT_ggh125_h024, "HIST")
	njet_stack.Add(hist_n_jets_fJVT_vbf_h024, "HIST")
	njet_stack.Add(hist_n_jets_fJVT_sherpa, "HIST")
	njet_stack.Add(hist_n_jets_fJVT_ggh125, "HIST")
	njet_stack.Add(hist_n_jets_fJVT_vbf, "HIST")
	njet_stack.Draw("nostack")
	njet_stack.GetXaxis().SetTitle("Number of Jets");
	njet_stack.GetYaxis().SetTitle("Normalized A.U.");
	c4.BuildLegend()
	c4.SaveAs("njets.pdf")
	# raw_input("enter plz")

def j1ptstack():
	c4 = TCanvas("c4", "")
	pt_stack = THStack("pt_stack", "")
	hist_j130_pt_sherpa_h024.SetLineColor(1)
	hist_j130_pt_sherpa_h024.SetTitle("Sherpa2_diphoton_h024")
	hist_j130_pt_sherpa_h024.SetLineStyle(5)
	hist_j130_pt_sherpa.SetLineColor(1)
	hist_j130_pt_sherpa.SetTitle("Sherpa2_diphoton_fJVT")

	hist_j130_pt_vbf_h024.SetLineColor(2)
	hist_j130_pt_vbf_h024.SetTitle("PowhegPy8_NNPDF30_VBFH125_h024")
	hist_j130_pt_vbf_h024.SetLineStyle(5)
	hist_j130_pt_vbf.SetLineColor(2)
	hist_j130_pt_vbf.SetTitle("PowhegPy8_NNPDF30_VBFH125_fJVT")

	hist_j130_pt_ggh125_h024.SetLineColor(4)
	hist_j130_pt_ggh125_h024.SetTitle("PowhegPy8_NNLOPS_ggH125_h024")
	hist_j130_pt_ggh125_h024.SetLineStyle(5)
	hist_j130_pt_ggh125.SetLineColor(4)
	hist_j130_pt_ggh125.SetTitle("PowhegPy8_NNLOPS_ggH125_fJVT")

	pt_stack.Add(hist_j130_pt_sherpa_h024, "HIST")
	pt_stack.Add(hist_j130_pt_ggh125_h024, "HIST")
	pt_stack.Add(hist_j130_pt_vbf_h024, "HIST")
	pt_stack.Add(hist_j130_pt_sherpa, "HIST")
	pt_stack.Add(hist_j130_pt_ggh125, "HIST")
	pt_stack.Add(hist_j130_pt_vbf, "HIST")
	pt_stack.Draw("nostack")
	pt_stack.GetXaxis().SetTitle("p_{T}");
	pt_stack.GetYaxis().SetTitle("Normalized A.U.");
	c4.BuildLegend()
	c4.SaveAs("leadingjet_pt_nofJVT.pdf")
	# raw_input("enter plz")

def j1ptfjvtstack():
	c4 = TCanvas("c4", "")
	ptfjvt_stack = THStack("ptfjvt_stack", "")
	hist_j130_pt_fJVT_sherpa_h024.SetLineColor(1)
	hist_j130_pt_fJVT_sherpa_h024.SetTitle("Sherpa2_diphoton_h024")
	hist_j130_pt_fJVT_sherpa_h024.SetLineStyle(5)
	hist_j130_pt_fJVT_sherpa.SetLineColor(1)
	hist_j130_pt_fJVT_sherpa.SetTitle("Sherpa2_diphoton_fJVT")

	hist_j130_pt_fJVT_vbf_h024.SetLineColor(2)
	hist_j130_pt_fJVT_vbf_h024.SetTitle("PowhegPy8_NNPDF30_VBFH125_h024")
	hist_j130_pt_fJVT_vbf_h024.SetLineStyle(5)
	hist_j130_pt_fJVT_vbf.SetLineColor(2)
	hist_j130_pt_fJVT_vbf.SetTitle("PowhegPy8_NNPDF30_VBFH125_fJVT")

	hist_j130_pt_fJVT_ggh125_h024.SetLineColor(4)
	hist_j130_pt_fJVT_ggh125_h024.SetTitle("PowhegPy8_NNLOPS_ggH125_h024")
	hist_j130_pt_fJVT_ggh125_h024.SetLineStyle(5)
	hist_j130_pt_fJVT_ggh125.SetLineColor(4)
	hist_j130_pt_fJVT_ggh125.SetTitle("PowhegPy8_NNLOPS_ggH125_fJVT")

	ptfjvt_stack.Add(hist_j130_pt_fJVT_sherpa_h024, "HIST")
	ptfjvt_stack.Add(hist_j130_pt_fJVT_ggh125_h024, "HIST")
	ptfjvt_stack.Add(hist_j130_pt_fJVT_vbf_h024, "HIST")
	ptfjvt_stack.Add(hist_j130_pt_fJVT_sherpa, "HIST")
	ptfjvt_stack.Add(hist_j130_pt_fJVT_ggh125, "HIST")
	ptfjvt_stack.Add(hist_j130_pt_fJVT_vbf, "HIST")
	ptfjvt_stack.Draw("nostack")
	ptfjvt_stack.GetXaxis().SetTitle("p_{T}");
	ptfjvt_stack.GetYaxis().SetTitle("Normalized A.U.");
	c4.BuildLegend()
	c4.SaveAs("leadingjet_pt.pdf")
	# raw_input("enter plz")

def alljetpt():
	c1 = TCanvas("c1", "")
	alljet_stack = THStack("alljet_stack", "")
	hist_alljet_pt_fJVT_sherpa_h024.SetLineColor(1)
	hist_alljet_pt_fJVT_sherpa_h024.SetTitle("Sherpa2_diphoton_h024")
	hist_alljet_pt_fJVT_sherpa_h024.SetLineStyle(5)
	hist_alljet_pt_fJVT_sherpa.SetLineColor(1)
	hist_alljet_pt_fJVT_sherpa.SetTitle("Sherpa2_diphoton_fJVT")

	hist_alljet_pt_fJVT_vbf_h024.SetLineColor(2)
	hist_alljet_pt_fJVT_vbf_h024.SetTitle("PowhegPy8_NNPDF30_VBFH125_h024")
	hist_alljet_pt_fJVT_vbf_h024.SetLineStyle(5)
	hist_alljet_pt_fJVT_vbf.SetTitle("PowhegPy8_NNPDF30_VBFH125_fJVT")
	hist_alljet_pt_fJVT_vbf.SetLineColor(2)

	hist_alljet_pt_fJVT_ggh125_h024.SetLineColor(4)
	hist_alljet_pt_fJVT_ggh125_h024.SetTitle("PowhegPy8_NNLOPS_ggH125_h024")
	hist_alljet_pt_fJVT_ggh125_h024.SetLineStyle(5)
	hist_alljet_pt_fJVT_ggh125.SetLineColor(4)
	hist_alljet_pt_fJVT_ggh125.SetTitle("PowhegPy8_NNLOPS_ggH125_fJVT")
	alljet_stack.Add(hist_alljet_pt_fJVT_sherpa_h024, "HIST")
	alljet_stack.Add(hist_alljet_pt_fJVT_ggh125_h024, "HIST")
	alljet_stack.Add(hist_alljet_pt_fJVT_vbf_h024, "HIST")
	alljet_stack.Add(hist_alljet_pt_fJVT_sherpa, "HIST")
	alljet_stack.Add(hist_alljet_pt_fJVT_ggh125, "HIST")
	alljet_stack.Add(hist_alljet_pt_fJVT_vbf, "HIST")
	alljet_stack.Draw("nostack")
	alljet_stack.GetXaxis().SetTitle("p_{T}");
	alljet_stack.GetYaxis().SetTitle("Normalized A.U.");
	c1.BuildLegend()
	c1.SaveAs("alljet_pt.pdf")
	# raw_input("enter plz")

def forward_jeteta():
	c1 = TCanvas("c1", "")
	forward_jet_stack = THStack("forward_jet_stack", "")
	hist_forward_jet_eta_fJVT_sherpa_h024.SetLineColor(1)
	hist_forward_jet_eta_fJVT_sherpa_h024.SetTitle("Sherpa2_diphoton_h024")
	hist_forward_jet_eta_fJVT_sherpa_h024.SetLineStyle(5)
	hist_forward_jet_eta_fJVT_sherpa.SetLineColor(1)
	hist_forward_jet_eta_fJVT_sherpa.SetTitle("Sherpa2_diphoton_fJVT")

	hist_forward_jet_eta_fJVT_vbf_h024.SetLineColor(2)
	hist_forward_jet_eta_fJVT_vbf_h024.SetTitle("PowhegPy8_NNPDF30_VBFH125_h024")
	hist_forward_jet_eta_fJVT_vbf_h024.SetLineStyle(5)
	hist_forward_jet_eta_fJVT_vbf.SetTitle("PowhegPy8_NNPDF30_VBFH125_fJVT")
	hist_forward_jet_eta_fJVT_vbf.SetLineColor(2)

	hist_forward_jet_eta_fJVT_ggh125_h024.SetLineColor(4)
	hist_forward_jet_eta_fJVT_ggh125_h024.SetTitle("PowhegPy8_NNLOPS_ggH125_h024")
	hist_forward_jet_eta_fJVT_ggh125_h024.SetLineStyle(5)
	hist_forward_jet_eta_fJVT_ggh125.SetLineColor(4)
	hist_forward_jet_eta_fJVT_ggh125.SetTitle("PowhegPy8_NNLOPS_ggH125_fJVT")
	forward_jet_stack.Add(hist_forward_jet_eta_fJVT_sherpa_h024, "HIST")
	forward_jet_stack.Add(hist_forward_jet_eta_fJVT_ggh125_h024, "HIST")
	forward_jet_stack.Add(hist_forward_jet_eta_fJVT_vbf_h024, "HIST")
	forward_jet_stack.Add(hist_forward_jet_eta_fJVT_sherpa, "HIST")
	forward_jet_stack.Add(hist_forward_jet_eta_fJVT_ggh125, "HIST")
	forward_jet_stack.Add(hist_forward_jet_eta_fJVT_vbf, "HIST")
	forward_jet_stack.Draw("nostack")
	forward_jet_stack.GetXaxis().SetTitle("#eta");
	forward_jet_stack.GetYaxis().SetTitle("Normalized A.U.");
	c1.BuildLegend()
	c1.SaveAs("forwardjet_eta.pdf")
	# raw_input("enter plz")



if __name__ == '__main__':
	gROOT.SetBatch(True)
	# AtlasStyle.SetAtlasStyle()
	gROOT.SetStyle("ATLAS")
	njetfjvtstack()
	# j1ptstack()
	# j1ptfjvtstack()
	failstack()
	passtack()
	alljetpt()
	forward_jeteta()
	