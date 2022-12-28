import ROOT
import sys
import os


# Sherpa2_myy_90_175
# MGPy8_ttgammagamma_noallhad_AF2
# MGPy8_ttgammagamma_allhad_AF2
# MGPy8_ttgamma_nonallhadronic #remove _AF2
# MGPy8_ttgamma_nonallhadronic
# Sherpa_tt_dilepton
# aMCPy8_2a_2j_FxFx
# Pythia8_2DP20_Mass_0_55
# Pythia8_2DP20_Mass_55_100
# Pythia8_2DP20_Mass_100_160
# Pythia8_2DP20_Mass_160_250
# Pythia8_2DP20_Mass_250_400
# Pythia8_2DP20_Mass_400_650
# Pythia8_2DP20_Mass_650_1000
# Pythia8_2DP20_Mass_1000_1500

# py create_cutflows.py testingInputMakers/Sherpa2_myy_90_175/Nominal/mc16a/ Sherpa2_myy_90_175 Nominal
# py create_cutflows.py testingInputMakers/Sherpa2_myy_90_175/Nominal/mc16a/ Sherpa2_myy_90_175 PhotonSys
# py create_cutflows.py testingInputMakers/Sherpa2_myy_90_175/Nominal/mc16a/ Sherpa2_myy_90_175 JetSys
# py create_cutflows.py testingInputMakers/Sherpa2_myy_90_175/Nominal/mc16a/ Sherpa2_myy_90_175 FlavorSys


s_cutDescs = ["#it{N}_{xAOD}", "#it{N}_{DxAOD}", "All events", "No duplicates", "GRL", "Pass trigger", "Detector DQ", "Has PV",
    "2 loose photons", "e-#gamma ambiguity", "Trigger match", "tight ID", "isolation", "rel. #it{p}_{T} cuts",
    "#it{m}_{#gamma#gamma} #in [105,160] GeV"]


# inputDir = str(sys.argv[1])
# sampleType = str(sys.argv[2])
# sysType =  str(sys.argv[3])

mcTypes = ["mc16a", "mc16d", "mc16e"]
# mcTypes = ["mc16a"]

# samples = ["MGPy8_ttgammagamma_noallhad_AF2", "MGPy8_ttgammagamma_allhad_AF2",
# 		   "MGPy8_ttgamma_nonallhadronic_AF2", "Sherpa_tt_dilepton", "aMCPy8_2a_2j_FxFx", "Pythia8_2DP20_Mass_0_55",
# 		   "Pythia8_2DP20_Mass_55_100", "Pythia8_2DP20_Mass_100_160", "Pythia8_2DP20_Mass_160_250", "Pythia8_2DP20_Mass_250_400",
# 		   "Pythia8_2DP20_Mass_400_650", "Pythia8_2DP20_Mass_650_1000", "Pythia8_2DP20_Mass_1000_1500",
# 			"Sh_2211_Zbbyy_myy95", "Sh_2211_Zqqyy_myy95", "PowhegPy8_HHbbyy_cHHH01d0", "PowhegPy8_NNLOPS_ggH125", 
# 			"PowhegPy8EG_NNPDF30_VBFH125", "PowhegPy8_WmH125J", "PowhegPy8_WpH125J", "PowhegPy8_ZH125J", "PowhegPy8_ggZH125", 
# 			"PowhegPy8_ttH125_fixweight", "aMCnloPy8_tWH125", "aMCnloPy8_tHjb125_4fl_shw_fix", "PowhegPy8_bbH125"]


# samples = ["Sh_2210_yybb_0Myy90",
# 		   "Sh_2210_yybb_90Myy175",
# 		   "Sh_2210_yybb_175MyyECM"]

# samples = [	"Sherpa2_diphoton_myy_175_2000_AF2", 
# 			"Sherpa2_diphoton_myy_2000_ECMS_AF2", 
# 			"Sherpa2_diphoton_myy_90_175_AF2", 
# 			"Sh_2211_Zbbyy_myy95", 
# 			"Sh_2211_Zqqyy_myy95", 
# 			"MGPy8_ttgammagamma_allhad_AF2", 
# 			"MGPy8_ttgammagamma_noallhad_AF2", 
# 			"aMCPy8_2a_2j_FxFx", 
# 			"Pythia8_2DP20_Mass_0_55", 
# 			"Pythia8_2DP20_Mass_55_100", 
# 			"Pythia8_2DP20_Mass_100_160", 
# 			"Pythia8_2DP20_Mass_160_250", 
# 			"Pythia8_2DP20_Mass_250_400", 
# 			"Pythia8_2DP20_Mass_400_650", 
# 			"Pythia8_2DP20_Mass_650_1000", 
# 			"Pythia8_2DP20_Mass_1000_1500", 
# 			"MGPy8_ttgamma_nonallhadronic", 
# 			"MGPy8_ttgamma_nonallhadronic_AF2", 
# 			"Sherpa_tt_dilepton", 
# 			"PowhegPy8_HHbbyy_cHHH01d0", 
# 			"PowhegPy8_NNLOPS_ggH125", 
# 			"PowhegPy8EG_NNPDF30_VBFH125", 
# 			"PowhegPy8_WmH125J", 
# 			"PowhegPy8_WpH125J", 
# 			"PowhegPy8_ZH125J", 
# 			"PowhegPy8_ggZH125", 
# 			"PowhegPy8_ttH125_fixweight", 
# 			"aMCnloPy8_tWH125", 
# 			"aMCnloPy8_tHjb125_4fl_shw_fix", 
# 			"PowhegPy8_bbH125"
# 		   ]

samples = [	"Sherpa2_diphoton_myy_90_175_AF2"]
			# "Sherpa2_diphoton_myy_175_2000_AF2", 
			# "Sherpa2_diphoton_myy_2000_ECMS_AF2", 
			# "Sherpa2_diphoton_myy_90_175_AF2", 
			# "Sh_2211_Zbbyy_myy95", 
			# "Sh_2211_Zqqyy_myy95", 
			# "MGPy8_ttgammagamma_allhad_AF2", 
			# "MGPy8_ttgammagamma_noallhad_AF2", 
		 #   ]

# # sysTypes = ["Nominal", "PhotonSys", "FlavorSys", "JetSys"]
# sysTypes = ["PhotonAllSys1",
# 			"PhotonAllSys2",
# 			"PhotonAllSys3",
# 			"PhotonAllSys4"]
# # sysTypes = ["FlavorAllSys1",
# # 			"FlavorAllSys2",
# # 			"FlavorAllSys3",
# # 			"FlavorAllSys4",
# # 			"JetSys1",
# # 			"JetSys2",
# # 			"JetSys3",
# # 			"JetSys4"
# # 			]

sysTypes = ["Nominal"]



for mcType in mcTypes:
	for sysType in sysTypes:
		for sample in samples:
			inputDir = "/home/bstamas/xdata/yyhf/inputHistMaker/newInputs/"+sample+"/"+sysType+"/"+mcType
			print inputDir
			# inputDir = "/home/bstamas/xdata/yyhf/testCutflows/"
			# print inputDir
			if os.path.exists(inputDir):
				# print inputDir
				# continue
				cutflowName = "hist_cutflow_noDalitz_weighted" ## for NTUPS ONLY!!

				# cutflowName = "CutFlow_"+sample+"_noDalitz_weighted"
				# if sample == "aMCnloPy8_tHjb125_4fl_shw_fix":
				# 	cutflowName = "CutFlow_aMCnloPy8_tHjb125_4fl_noDalitz_weighted"
				# if sample == "MGPy8_ttgamma_nonallhadronic_AF2":
				# 	cutflowName = "CutFlow_MGPy8_ttgamma_nonallhadronic_noDalitz_weighted"
				# if sample == "Sherpa2_diphoton_myy_90_175_AF2":
				# 	cutflowName = "CutFlow_Sherpa2_myy_90_175_noDalitz_weighted"
				# if sample == "Sherpa2_diphoton_myy_1400_2000_AF2":
				# 	cutflowName = "CutFlow_Sherpa2_myy_1400_2000_noDalitz_weighted"
				# if sample == "Sherpa2_diphoton_myy_175_2000_AF2":
				# 	cutflowName = "CutFlow_Sherpa2_myy_175_2000_noDalitz_weighted"
				# if sample == "Sherpa2_diphoton_myy_2000_ECMS_AF2":
				# 	cutflowName = "CutFlow_Sherpa2_myy_2000_ECMS_noDalitz_weighted"
				print "cutflow name : " + cutflowName
			# CutFlow_Sh_2210_yybb_0Myy90_noDalitz_weighted

				print "Creating output: /home/bstamas/xdata/yyhf/inputHistMaker/cutflows/"+sysType+"/"+mcType+".CutFlow_"+sample+".root"
				newFile = ROOT.TFile("/home/bstamas/xdata/yyhf/inputHistMaker/cutflows/"+sysType+"/"+mcType+".CutFlow_"+sample+".root", "recreate")
				newFile.cd()

				myCutflow = ROOT.TH1F(cutflowName, cutflowName, 15, 0, 15)
				myCutflow.GetXaxis().SetBinLabel(1, s_cutDescs[0])
				myCutflow.GetXaxis().SetBinLabel(2, s_cutDescs[1])
				myCutflow.GetXaxis().SetBinLabel(3, s_cutDescs[2])
				myCutflow.GetXaxis().SetBinLabel(4, s_cutDescs[3])
				myCutflow.GetXaxis().SetBinLabel(5, s_cutDescs[4])
				myCutflow.GetXaxis().SetBinLabel(6, s_cutDescs[5])
				myCutflow.GetXaxis().SetBinLabel(7, s_cutDescs[6])
				myCutflow.GetXaxis().SetBinLabel(8, s_cutDescs[7])
				myCutflow.GetXaxis().SetBinLabel(9, s_cutDescs[8])
				myCutflow.GetXaxis().SetBinLabel(10, s_cutDescs[9])
				myCutflow.GetXaxis().SetBinLabel(11, s_cutDescs[10])
				myCutflow.GetXaxis().SetBinLabel(12, s_cutDescs[11])
				myCutflow.GetXaxis().SetBinLabel(13, s_cutDescs[12])
				myCutflow.GetXaxis().SetBinLabel(14, s_cutDescs[13])
				myCutflow.GetXaxis().SetBinLabel(15, s_cutDescs[14])

				# print inputDir 
				if os.path.isdir(inputDir):
					print "isDir: "+str(inputDir)
					for file in os.listdir(inputDir):
						print file
						# if file == "yyHF_skimMxAODs_Sherpa2_diphoton_myy_90_175_AF2_mc16d_PhotonAllSys2_15.root":
						# 	continue
						# 	error:///home/bstamas/xdata/yyhf/skimMxAODs/run/newDownloads/PhotonSys/user.bstamas.mc16d.Sherpa2_diphoton_myy_90_175_AF2.MxAODPhotonAllSys2_h026_test5_v1_MxAOD.root/user.bstamas.28470229._001865.MxAOD.root
						# if file == "yyHF_skimMxAODs_Sherpa2_diphoton_myy_90_175_AF2_mc16d_PhotonAllSys4_10.root":
						# 	continue 
						# 	remove an input file
						# if file == "yyHF_skimMxAODs_Sherpa2_diphoton_myy_90_175_AF2_mc16d_PhotonAllSys4_11.root":
						# 	continue
						# 	error:///home/bstamas/xdata/yyhf/skimMxAODs/run/newDownloads/PhotonSys/user.bstamas.mc16d.Sherpa2_diphoton_myy_90_175_AF2.MxAODPhotonAllSys4_h026_test5_v1_MxAOD.root/user.bstamas.28471921._001152.MxAOD.root
						# if file == "yyHF_skimMxAODs_Sherpa2_diphoton_myy_90_175_AF2_mc16d_PhotonAllSys4_12.root":
						# 	continue
						# 	error:///home/bstamas/xdata/yyhf/skimMxAODs/run/newDownloads/PhotonSys/user.bstamas.mc16d.Sherpa2_diphoton_myy_90_175_AF2.MxAODPhotonAllSys4_h026_test5_v1_MxAOD.root/user.bstamas.28471921._001308.MxAOD.root
						# if file == "yyHF_skimMxAODs_Sherpa2_diphoton_myy_90_175_AF2_mc16e_PhotonAllSys2_20.root":
						# 	continue
						# 	error:///home/bstamas/xdata/yyhf/skimMxAODs/run/newDownloads/PhotonSys/user.bstamas.mc16e.Sherpa2_diphoton_myy_90_175_AF2.MxAODPhotonAllSys2_h026_test5_v1_MxAOD.root/user.bstamas.28470413._002898.MxAOD.root
						# if file == "yyHF_skimMxAODs_Sherpa2_diphoton_myy_90_175_AF2_mc16e_PhotonAllSys3_19.root":
						# 	continue
						# 	remove an input file
						# if file == "yyHF_skimMxAODs_Sherpa2_diphoton_myy_90_175_AF2_mc16e_PhotonAllSys4_18.root":
						# 	continue
						# 	remove an input file
						if file.endswith(".root"):
							inputPath = os.path.join(inputDir, file)
						# print inputPath
						f = ROOT.TFile(inputPath)
						cutflow = f.Get(cutflowName)
						myCutflow.Add(cutflow)

				elif os.path.isfile(inputDir):  
					print "isFile"
					f = ROOT.TFile(inputDir)
					cutflow = f.Get(cutflowName)
					myCutflow.Add(cutflow)
				else:
					print "neither - recheck inputs"

				newFile.Write()
				newFile.Close()

			# else:
			# 	# print
			# 	print "********FILE DOES NOT EXIST******** "
			# 	print inputDir
			# 	# print






