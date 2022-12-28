from ROOT import *
import sys
import os

gStyle.SetOptStat(0)
# gROOT.SetStyle("ATLAS")
gROOT.SetBatch(True)
gStyle.SetPaintTextFormat("4.2f")
input_file = TFile("mc16e.PowhegPy8_NNLOPS_ggH125/hist-mc16e.root")
# input_file = TFile("masterfile.root")

hist_samegood_btaggedjets_77 = input_file.Get("hist_samegood_btaggedjets_77")
hist_samewrong_btaggedjets_77 = input_file.Get("hist_samewrong_btaggedjets_77")
hist_diff_IDgood_btaggedjets_77 = input_file.Get("hist_diff_IDgood_btaggedjets_77")
hist_diff_yyNNgood_btaggedjets_77 = input_file.Get("hist_diff_yyNNgood_btaggedjets_77")
hist_diffwrong_btaggedjets_77 = input_file.Get("hist_diffwrong_btaggedjets_77")

hist_samegood_btaggedjets_70 = input_file.Get("hist_samegood_btaggedjets_70")
hist_samewrong_btaggedjets_70 = input_file.Get("hist_samewrong_btaggedjets_70")
hist_diff_IDgood_btaggedjets_70 = input_file.Get("hist_diff_IDgood_btaggedjets_70")
hist_diff_yyNNgood_btaggedjets_70 = input_file.Get("hist_diff_yyNNgood_btaggedjets_70")
hist_diffwrong_btaggedjets_70 = input_file.Get("hist_diffwrong_btaggedjets_70")

hist_samegood_btaggedjets_70_singlejet = input_file.Get("hist_samegood_btaggedjets_70_singlejet")
hist_samewrong_btaggedjets_70_singlejet = input_file.Get("hist_samewrong_btaggedjets_70_singlejet")
hist_diff_IDgood_btaggedjets_70_singlejet = input_file.Get("hist_diff_IDgood_btaggedjets_70_singlejet")
hist_diff_yyNNgood_btaggedjets_70_singlejet = input_file.Get("hist_diff_yyNNgood_btaggedjets_70_singlejet")
hist_diffwrong_btaggedjets_70_singlejet = input_file.Get("hist_diffwrong_btaggedjets_70_singlejet")

hist_samegood_btaggedjets_70_multijet = input_file.Get("hist_samegood_btaggedjets_70_multijet")
hist_samewrong_btaggedjets_70_multijet = input_file.Get("hist_samewrong_btaggedjets_70_multijet")
hist_diff_IDgood_btaggedjets_70_multijet = input_file.Get("hist_diff_IDgood_btaggedjets_70_multijet")
hist_diff_yyNNgood_btaggedjets_70_multijet = input_file.Get("hist_diff_yyNNgood_btaggedjets_70_multijet")
hist_diffwrong_btaggedjets_70_multijet = input_file.Get("hist_diffwrong_btaggedjets_70_multijet")

hist_samegood_btaggedjets_85 = input_file.Get("hist_samegood_btaggedjets_85")
hist_samewrong_btaggedjets_85 = input_file.Get("hist_samewrong_btaggedjets_85")
hist_diff_IDgood_btaggedjets_85 = input_file.Get("hist_diff_IDgood_btaggedjets_85")
hist_diff_yyNNgood_btaggedjets_85 = input_file.Get("hist_diff_yyNNgood_btaggedjets_85")
hist_diffwrong_btaggedjets_85 = input_file.Get("hist_diffwrong_btaggedjets_85")

hist_samegood_btaggedjets_60 = input_file.Get("hist_samegood_btaggedjets_60")
hist_samewrong_btaggedjets_60 = input_file.Get("hist_samewrong_btaggedjets_60")
hist_diff_IDgood_btaggedjets_60 = input_file.Get("hist_diff_IDgood_btaggedjets_60")
hist_diff_yyNNgood_btaggedjets_60 = input_file.Get("hist_diff_yyNNgood_btaggedjets_60")
hist_diffwrong_btaggedjets_60 = input_file.Get("hist_diffwrong_btaggedjets_60")

# histlist = [hist_samegood_btaggedjets_77, hist_samewrong_btaggedjets_77, hist_diff_IDgood_btaggedjets_77, 
# 			hist_diff_yyNNgood_btaggedjets_77, hist_diffwrong_btaggedjets_77, hist_samegood_btaggedjets_70, 
# 			hist_samewrong_btaggedjets_70, hist_diff_IDgood_btaggedjets_70, hist_diff_yyNNgood_btaggedjets_70, 
# 			hist_diffwrong_btaggedjets_70, hist_samegood_btaggedjets_85, hist_samewrong_btaggedjets_85, 
# 			hist_diff_IDgood_btaggedjets_85, hist_diff_yyNNgood_btaggedjets_85, hist_diffwrong_btaggedjets_85, 
# 			hist_samegood_btaggedjets_60, hist_samewrong_btaggedjets_60, hist_diff_IDgood_btaggedjets_60, 
# 			hist_diff_yyNNgood_btaggedjets_60, hist_diffwrong_btaggedjets_60]

histlist = [hist_samegood_btaggedjets_70_singlejet, hist_samewrong_btaggedjets_70_singlejet, 
			hist_diff_IDgood_btaggedjets_70_singlejet, hist_diff_yyNNgood_btaggedjets_70_singlejet, 
			hist_diffwrong_btaggedjets_70_singlejet, hist_samegood_btaggedjets_70_multijet, 
			hist_samewrong_btaggedjets_70_multijet, hist_diff_IDgood_btaggedjets_70_multijet, 
			hist_diff_yyNNgood_btaggedjets_70_multijet, hist_diffwrong_btaggedjets_70_multijet]


for hist in histlist:
	hist.SetMarkerSize(1.1)
	if "single" in hist.GetName():
		njets = " single-jet"
	elif "multi" in hist.GetName():
		njets = " multi-jet"
	else:
		njets = ""

	if "77" in hist.GetName():
		wp = " for 77WP"
	elif "70" in hist.GetName():
		wp = " for 70WP"
	elif "85" in hist.GetName():
		wp = " for 85WP"
	elif "60" in hist.GetName():
		wp = " for 60WP"
	
	if "samegood" in hist.GetName():
		hist.SetTitle("Same and good"+wp+njets)
	elif "samewrong" in hist.GetName():
		hist.SetTitle("Same and wrong"+wp+njets)
	elif "diffwrong" in hist.GetName():
		hist.SetTitle("Different and both wrong"+wp+njets)
	elif "diff_yyNNgood" in hist.GetName():
		hist.SetTitle("Different and NN good"+wp+njets)
	elif "diff_IDgood" in hist.GetName():
		hist.SetTitle("Different and ID good"+wp+njets)

	c1 = TCanvas("c1", "")
	hist.Draw("colz text E")
	c1.SaveAs(hist.GetName()+".pdf")
# hist_samegood_btaggedjets_77.Draw("colz")
# raw_input("enter")