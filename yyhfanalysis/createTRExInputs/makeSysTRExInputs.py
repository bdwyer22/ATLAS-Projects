import ROOT


# mySysList = ["PhotonSys", "FlavorSys", "JetSys"]

mySysList = [
			"PhotonAllSys1",
			"PhotonAllSys2",
			"PhotonAllSys3",
			"PhotonAllSys4",
			"FlavorAllSys1",
			"FlavorAllSys2",
			"FlavorAllSys3",
			"FlavorAllSys4",
			"JetSys1",
			"JetSys2",
			"JetSys3",
			"JetSys4"]

singeJet = True
# singeJet = False

# inputSignalSamples = ["Sh_2211_Zyy_myy95", "MGPy8_ttgammagamma_AF2"]
inputSignalSamples = ["Sherpa2_diphoton_myy_ALL_AF2", "Sh_2211_Zyy_myy95", "MGPy8_ttgammagamma_AF2"]

for sample in inputSignalSamples:
	for systematicType in mySysList:
		myInputFile = ROOT.TFile("/home/bstamas/xdata/yyhf/inputHistMaker/outputs/master."+sample+"."+systematicType+"_combinedCR.root", "READ")

		if sample == "Sherpa2_diphoton_myy_ALL_AF2": outputName = "yy"
		elif sample == "Sh_2211_Zyy_myy95": outputName = "zyy"
		elif sample == "MGPy8_ttgammagamma_AF2": outputName = "ttyy"

		mySysDict = {}
		myVariations = []
		# if "PhotonSys" in systematicType:
		# 	myVariations = ["EG_RESOLUTION_ALL__1down","EG_RESOLUTION_ALL__1up","EG_SCALE_AF2__1down","EG_SCALE_AF2__1up",
		# 	"EG_SCALE_ALL__1down","EG_SCALE_ALL__1up","PH_EFF_ID_Uncertainty__1down","PH_EFF_ID_Uncertainty__1up","PH_EFF_ISO_Uncertainty__1down",
		# 	"PH_EFF_ISO_Uncertainty__1up","PH_EFF_TRIGGER_Uncertainty__1down","PH_EFF_TRIGGER_Uncertainty__1up","PRW_DATASF__1down","PRW_DATASF__1up"]

		# if "FlavorSys" in systematicType:
		# 	myVariations = ["FT_EFF_Eigen_B_0__1down","FT_EFF_Eigen_B_0__1up", "FT_EFF_Eigen_B_1__1down", "FT_EFF_Eigen_B_1__1up", "FT_EFF_Eigen_B_2__1down", 
		# 	"FT_EFF_Eigen_B_2__1up", "FT_EFF_Eigen_C_0__1down", "FT_EFF_Eigen_C_0__1up", "FT_EFF_Eigen_C_1__1down", "FT_EFF_Eigen_C_1__1up", "FT_EFF_Eigen_C_2__1down", 
		# 	"FT_EFF_Eigen_C_2__1up", "FT_EFF_Eigen_C_3__1down", "FT_EFF_Eigen_C_3__1up", "FT_EFF_Eigen_Light_0__1down", "FT_EFF_Eigen_Light_0__1up", 
		# 	"FT_EFF_Eigen_Light_1__1down", "FT_EFF_Eigen_Light_1__1up", "FT_EFF_Eigen_Light_2__1down", "FT_EFF_Eigen_Light_2__1up", "FT_EFF_Eigen_Light_3__1down", 
		# 	"FT_EFF_Eigen_Light_3__1up", "FT_EFF_Eigen_Light_4__1down", "FT_EFF_Eigen_Light_4__1up", "FT_EFF_extrapolation__1down", "FT_EFF_extrapolation__1up", 
		# 	"FT_EFF_extrapolation_from_charm__1down", "FT_EFF_extrapolation_from_charm__1up"]

		# if "JetSys" in systematicType:
		# 	myVariations = ["JET_BJES_Response__1down", "JET_BJES_Response__1up", "JET_EffectiveNP_Detector1__1down", "JET_EffectiveNP_Detector1__1up", 
		# 	"JET_EffectiveNP_Detector2__1down", "JET_EffectiveNP_Detector2__1up", "JET_EffectiveNP_Mixed1__1down", "JET_EffectiveNP_Mixed1__1up", 
		# 	"JET_EffectiveNP_Mixed2__1down", "JET_EffectiveNP_Mixed2__1up", "JET_EffectiveNP_Mixed3__1down", "JET_EffectiveNP_Mixed3__1up", 
		# 	"JET_EffectiveNP_Modelling1__1down", "JET_EffectiveNP_Modelling1__1up", "JET_EffectiveNP_Modelling2__1down", "JET_EffectiveNP_Modelling2__1up", 
		# 	"JET_EffectiveNP_Modelling3__1down", "JET_EffectiveNP_Modelling3__1up", "JET_EffectiveNP_Modelling4__1down", "JET_EffectiveNP_Modelling4__1up", 
		# 	"JET_EffectiveNP_Statistical1__1down", "JET_EffectiveNP_Statistical1__1up", "JET_EffectiveNP_Statistical2__1down", "JET_EffectiveNP_Statistical2__1up", 
		# 	"JET_EffectiveNP_Statistical3__1down", "JET_EffectiveNP_Statistical3__1up", "JET_EffectiveNP_Statistical4__1down", "JET_EffectiveNP_Statistical4__1up", 
		# 	"JET_EffectiveNP_Statistical5__1down", "JET_EffectiveNP_Statistical5__1up", "JET_EffectiveNP_Statistical6__1down", "JET_EffectiveNP_Statistical6__1up", 
		# 	"JET_EtaIntercalibration_Modelling__1down", "JET_EtaIntercalibration_Modelling__1up", "JET_EtaIntercalibration_NonClosure_2018data__1down", 
		# 	"JET_EtaIntercalibration_NonClosure_2018data__1up", "JET_EtaIntercalibration_NonClosure_highE__1down", "JET_EtaIntercalibration_NonClosure_highE__1up", 
		# 	"JET_EtaIntercalibration_NonClosure_negEta__1down", "JET_EtaIntercalibration_NonClosure_negEta__1up", "JET_EtaIntercalibration_NonClosure_posEta__1down", 
		# 	"JET_EtaIntercalibration_NonClosure_posEta__1up", "JET_EtaIntercalibration_TotalStat__1down", "JET_EtaIntercalibration_TotalStat__1up", "JET_fJvtEfficiency__1down", 
		# 	"JET_fJvtEfficiency__1up", "JET_Flavor_Composition__1down", "JET_Flavor_Composition__1up", "JET_Flavor_Response__1down", 
		# 	"JET_Flavor_Response__1up", "JET_JER_EffectiveNP_1__1down", "JET_JER_EffectiveNP_1__1up", "JET_JER_EffectiveNP_10__1down", 
		# 	"JET_JER_EffectiveNP_10__1up", "JET_JER_EffectiveNP_11__1down", "JET_JER_EffectiveNP_11__1up", "JET_JER_EffectiveNP_12restTerm__1down", 
		# 	"JET_JER_EffectiveNP_12restTerm__1up", "JET_JER_EffectiveNP_2__1down", "JET_JER_EffectiveNP_2__1up", "JET_JER_EffectiveNP_3__1down", 
		# 	"JET_JER_EffectiveNP_3__1up", "JET_JER_EffectiveNP_4__1down", "JET_JER_EffectiveNP_4__1up", "JET_JER_EffectiveNP_5__1down", 
		# 	"JET_JER_EffectiveNP_5__1up", "JET_JER_EffectiveNP_6__1down", "JET_JER_EffectiveNP_6__1up", "JET_JER_EffectiveNP_7__1down", 
		# 	"JET_JER_EffectiveNP_7__1up", "JET_JER_EffectiveNP_8__1down", "JET_JER_EffectiveNP_8__1up", "JET_JER_EffectiveNP_9__1down", 
		# 	"JET_JER_EffectiveNP_9__1up", "JET_JvtEfficiency__1down", "JET_JvtEfficiency__1up", "JET_Pileup_OffsetMu__1down", "JET_Pileup_OffsetMu__1up", 
		# 	"JET_Pileup_OffsetNPV__1down", "JET_Pileup_OffsetNPV__1up", "JET_Pileup_PtTerm__1down", "JET_Pileup_PtTerm__1up", "JET_Pileup_RhoTopology__1down", 
		# 	"JET_Pileup_RhoTopology__1up", "JET_SingleParticle_HighPt__1down", "JET_SingleParticle_HighPt__1up"]

		if "PhotonAllSys1" in systematicType:
			myVariations = ["EG_RESOLUTION_AF2__1down", 
			"EG_RESOLUTION_AF2__1up", 
			"EG_RESOLUTION_MATERIALCALO__1down", 
			"EG_RESOLUTION_MATERIALCALO__1up", 
			"EG_RESOLUTION_MATERIALCRYO__1down", 
			"EG_RESOLUTION_MATERIALCRYO__1up", 
			"EG_RESOLUTION_MATERIALGAP__1down", 
			"EG_RESOLUTION_MATERIALGAP__1up", 
			"EG_RESOLUTION_MATERIALIBL__1down", 
			"EG_RESOLUTION_MATERIALIBL__1up", 
			"EG_RESOLUTION_MATERIALID__1down", 
			"EG_RESOLUTION_MATERIALID__1up", 
			"EG_RESOLUTION_MATERIALPP0__1down", 
			"EG_RESOLUTION_MATERIALPP0__1up", 
			"EG_RESOLUTION_PILEUP __1down", 
			"EG_RESOLUTION_PILEUP __1up", 
			"EG_RESOLUTION_SAMPLINGTERM__1down", 
			"EG_RESOLUTION_SAMPLINGTERM__1up", 
			"EG_RESOLUTION_ZSMEARING__1down", 
			"EG_RESOLUTION_ZSMEARING__1up", 
			"EG_SCALE_PEDESTAL__1down", 
			"EG_SCALE_PEDESTAL__1up", 
			"EG_SCALE_PS__ETABIN0__1down", 
			"EG_SCALE_PS__ETABIN0__1up", 
			"EG_SCALE_PS__ETABIN1__1down", 
			"EG_SCALE_PS__ETABIN1__1up", 
			"EG_SCALE_PS__ETABIN2__1down", 
			"EG_SCALE_PS__ETABIN2__1up", 
			"EG_SCALE_PS__ETABIN3__1down", 
			"EG_SCALE_PS__ETABIN3__1up", 
			"EG_SCALE_PS__ETABIN4__1down", 
			"EG_SCALE_PS__ETABIN4__1up", 
			"EG_SCALE_PS__ETABIN5__1down", 
			"EG_SCALE_PS__ETABIN5__1up", 
			"EG_SCALE_PS__ETABIN6__1down", 
			"EG_SCALE_PS__ETABIN6__1up", 
			"EG_SCALE_PS__ETABIN7__1down", 
			"EG_SCALE_PS__ETABIN7__1up", 
			"EG_SCALE_PS__ETABIN8__1down", 
			"EG_SCALE_PS__ETABIN8__1up", 
			"EG_SCALE_PS_BARREL_B12__1down", 
			"EG_SCALE_PS_BARREL_B12__1up"]

		if "PhotonAllSys2" in systematicType:
			myVariations = ["EG_SCALE_AF2__1down", 
			"EG_SCALE_AF2__1up", 
			"EG_SCALE_E4SCINTILLATOR__ETABIN0__1down", 
			"EG_SCALE_E4SCINTILLATOR__ETABIN0__1up", 
			"EG_SCALE_E4SCINTILLATOR__ETABIN1__1down", 
			"EG_SCALE_E4SCINTILLATOR__ETABIN1__1up", 
			"EG_SCALE_E4SCINTILLATOR__ETABIN2__1down", 
			"EG_SCALE_E4SCINTILLATOR__ETABIN2__1up", 
			"EG_SCALE_G4__1down", 
			"EG_SCALE_G4__1up", 
			"EG_SCALE_L1GAIN__1down", 
			"EG_SCALE_L1GAIN__1up", 
			"EG_SCALE_L2GAIN__1down", 
			"EG_SCALE_L2GAIN__1up", 
			"EG_SCALE_LARCALIB__ETABIN0__1down", 
			"EG_SCALE_LARCALIB__ETABIN0__1up", 
			"EG_SCALE_LARCALIB__ETABIN1__1down", 
			"EG_SCALE_LARCALIB__ETABIN1__1up", 
			"EG_SCALE_LARELECCALIB__1down", 
			"EG_SCALE_LARELECCALIB__1up", 
			"EG_SCALE_LARELECUNCONV__ETABIN0__1down", 
			"EG_SCALE_LARELECUNCONV__ETABIN0__1up", 
			"EG_SCALE_LARELECUNCONV__ETABIN1__1down", 
			"EG_SCALE_LARELECUNCONV__ETABIN1__1up", 
			"EG_SCALE_LARUNCONVCALIB__ETABIN0__1down", 
			"EG_SCALE_LARUNCONVCALIB__ETABIN0__1up", 
			"EG_SCALE_LARUNCONVCALIB__ETABIN1__1down", 
			"EG_SCALE_LARUNCONVCALIB__ETABIN1__1up", 
			"EG_SCALE_S12__ETABIN0__1down", 
			"EG_SCALE_S12__ETABIN0__1up", 
			"EG_SCALE_S12__ETABIN1__1down", 
			"EG_SCALE_S12__ETABIN1__1up", 
			"EG_SCALE_S12__ETABIN2__1down", 
			"EG_SCALE_S12__ETABIN2__1up", 
			"EG_SCALE_S12__ETABIN3__1down", 
			"EG_SCALE_S12__ETABIN3__1up", 
			"EG_SCALE_S12__ETABIN4__1down", 
			"EG_SCALE_S12__ETABIN4__1up", 
			"EG_SCALE_TOPOCLUSTER_THRES__1down", 
			"EG_SCALE_TOPOCLUSTER_THRES__1up", 
			"EG_SCALE_WTOTS1__1down", 
			"EG_SCALE_WTOTS1__1up"]

		if "PhotonAllSys3" in systematicType:
			myVariations = ["EG_SCALE_MATCALO__ETABIN0__1down", 
			"EG_SCALE_MATCALO__ETABIN0__1up", 
			"EG_SCALE_MATCALO__ETABIN1__1down", 
			"EG_SCALE_MATCALO__ETABIN1__1up", 
			"EG_SCALE_MATCALO__ETABIN10__1down", 
			"EG_SCALE_MATCALO__ETABIN10__1up", 
			"EG_SCALE_MATCALO__ETABIN11__1down", 
			"EG_SCALE_MATCALO__ETABIN11__1up", 
			"EG_SCALE_MATCALO__ETABIN2__1down", 
			"EG_SCALE_MATCALO__ETABIN2__1up", 
			"EG_SCALE_MATCALO__ETABIN3__1down", 
			"EG_SCALE_MATCALO__ETABIN3__1up", 
			"EG_SCALE_MATCALO__ETABIN4__1down", 
			"EG_SCALE_MATCALO__ETABIN4__1up", 
			"EG_SCALE_MATCALO__ETABIN5__1down", 
			"EG_SCALE_MATCALO__ETABIN5__1up", 
			"EG_SCALE_MATCALO__ETABIN6__1down", 
			"EG_SCALE_MATCALO__ETABIN6__1up", 
			"EG_SCALE_MATCALO__ETABIN7__1down", 
			"EG_SCALE_MATCALO__ETABIN7__1up", 
			"EG_SCALE_MATCALO__ETABIN8__1down", 
			"EG_SCALE_MATCALO__ETABIN8__1up", 
			"EG_SCALE_MATCALO__ETABIN9__1down", 
			"EG_SCALE_MATCALO__ETABIN9__1up", 
			"EG_SCALE_MATID__ETABIN0__1down", 
			"EG_SCALE_MATID__ETABIN0__1up", 
			"EG_SCALE_MATID__ETABIN1__1down", 
			"EG_SCALE_MATID__ETABIN1__1up", 
			"EG_SCALE_MATID__ETABIN2__1down", 
			"EG_SCALE_MATID__ETABIN2__1up", 
			"EG_SCALE_MATID__ETABIN3__1down", 
			"EG_SCALE_MATID__ETABIN3__1up", 
			"EG_SCALE_MATPP0__ETABIN0__1down", 
			"EG_SCALE_MATPP0__ETABIN0__1up", 
			"EG_SCALE_MATPP0__ETABIN1__1down", 
			"EG_SCALE_MATPP0__ETABIN1__1up", 
			"EG_SCALE_ZEESTAT__1down", 
			"EG_SCALE_ZEESTAT__1up", 
			"EG_SCALE_ZEESYST__1down", 
			"EG_SCALE_ZEESYST__1up"]

		if "PhotonAllSys4" in systematicType:
			myVariations = ["EG_SCALE_MATCRYO__ETABIN0__1down", 
			"EG_SCALE_MATCRYO__ETABIN0__1up", 
			"EG_SCALE_MATCRYO__ETABIN1__1down", 
			"EG_SCALE_MATCRYO__ETABIN1__1up", 
			"EG_SCALE_MATCRYO__ETABIN10__1down", 
			"EG_SCALE_MATCRYO__ETABIN10__1up", 
			"EG_SCALE_MATCRYO__ETABIN11__1down", 
			"EG_SCALE_MATCRYO__ETABIN11__1up", 
			"EG_SCALE_MATCRYO__ETABIN2__1down", 
			"EG_SCALE_MATCRYO__ETABIN2__1up", 
			"EG_SCALE_MATCRYO__ETABIN3__1down", 
			"EG_SCALE_MATCRYO__ETABIN3__1up", 
			"EG_SCALE_MATCRYO__ETABIN4__1down", 
			"EG_SCALE_MATCRYO__ETABIN4__1up", 
			"EG_SCALE_MATCRYO__ETABIN5__1down", 
			"EG_SCALE_MATCRYO__ETABIN5__1up", 
			"EG_SCALE_MATCRYO__ETABIN6__1down", 
			"EG_SCALE_MATCRYO__ETABIN6__1up", 
			"EG_SCALE_MATCRYO__ETABIN7__1down", 
			"EG_SCALE_MATCRYO__ETABIN7__1up", 
			"EG_SCALE_MATCRYO__ETABIN8__1down", 
			"EG_SCALE_MATCRYO__ETABIN8__1up", 
			"EG_SCALE_MATCRYO__ETABIN9__1down", 
			"EG_SCALE_MATCRYO__ETABIN9__1up", 
			"PH_EFF_ID_Uncertainty__1down", 
			"PH_EFF_ID_Uncertainty__1up", 
			"PH_EFF_ISO_Uncertainty__1down", 
			"PH_EFF_ISO_Uncertainty__1up", 
			"PH_EFF_TRIGGER_Uncertainty__1down", 
			"PH_EFF_TRIGGER_Uncertainty__1up", 
			"PH_SCALE_CONVEFFICIENCY__1down", 
			"PH_SCALE_CONVEFFICIENCY__1up", 
			"PH_SCALE_CONVFAKERATE__1down", 
			"PH_SCALE_CONVFAKERATE__1up", 
			"PH_SCALE_CONVRADIUS__1down", 
			"PH_SCALE_CONVRADIUS__1up", 
			"PH_SCALE_LEAKAGECONV__1down", 
			"PH_SCALE_LEAKAGECONV__1up", 
			"PH_SCALE_LEAKAGEUNCONV__1down", 
			"PH_SCALE_LEAKAGEUNCONV__1up"]

		if "JetSys1" in systematicType:
			myVariations = ["JET_EffectiveNP_Detector1__1down", "JET_EffectiveNP_Detector1__1up", "JET_EffectiveNP_Detector2__1down", "JET_EffectiveNP_Detector2__1up", 
			"JET_EffectiveNP_Mixed1__1down", "JET_EffectiveNP_Mixed1__1up", "JET_EffectiveNP_Mixed2__1down", "JET_EffectiveNP_Mixed2__1up", 
			"JET_EffectiveNP_Mixed3__1down", "JET_EffectiveNP_Mixed3__1up", "JET_EffectiveNP_Modelling1__1down", "JET_EffectiveNP_Modelling1__1up", 
			"JET_EffectiveNP_Modelling2__1down", "JET_EffectiveNP_Modelling2__1up", "JET_EffectiveNP_Modelling3__1down", "JET_EffectiveNP_Modelling3__1up", 
			"JET_EffectiveNP_Modelling4__1down", "JET_EffectiveNP_Modelling4__1up", "JET_EffectiveNP_Statistical1__1down", "JET_EffectiveNP_Statistical1__1up", 
			"JET_EffectiveNP_Statistical2__1down", "JET_EffectiveNP_Statistical2__1up", "JET_EffectiveNP_Statistical3__1down", "JET_EffectiveNP_Statistical3__1up", 
			"JET_EffectiveNP_Statistical4__1down", "JET_EffectiveNP_Statistical4__1up", "JET_EffectiveNP_Statistical5__1down", "JET_EffectiveNP_Statistical5__1up", 
			"JET_EffectiveNP_Statistical6__1down", "JET_EffectiveNP_Statistical6__1up"]

		if "JetSys2" in systematicType:#"JET_PunchThrough_MC16__1down", "JET_PunchThrough_MC16__1up",
			myVariations = ["JET_BJES_Response__1down", "JET_BJES_Response__1up", "JET_EtaIntercalibration_Modelling__1down", "JET_EtaIntercalibration_Modelling__1up", 
			"JET_EtaIntercalibration_NonClosure_2018data__1down", "JET_EtaIntercalibration_NonClosure_2018data__1up", "JET_EtaIntercalibration_NonClosure_highE__1down", 
			"JET_EtaIntercalibration_NonClosure_highE__1up", "JET_EtaIntercalibration_NonClosure_negEta__1down", "JET_EtaIntercalibration_NonClosure_negEta__1up", 
			"JET_EtaIntercalibration_NonClosure_posEta__1down", "JET_EtaIntercalibration_NonClosure_posEta__1up", "JET_EtaIntercalibration_TotalStat__1down", 
			"JET_EtaIntercalibration_TotalStat__1up", "JET_fJvtEfficiency__1down", "JET_fJvtEfficiency__1up", "JET_Flavor_Composition__1down", "JET_Flavor_Composition__1up", 
			"JET_Flavor_Response__1down", "JET_Flavor_Response__1up", "JET_JvtEfficiency__1down", "JET_JvtEfficiency__1up", "JET_Pileup_OffsetMu__1down", 
			"JET_Pileup_OffsetMu__1up", "JET_Pileup_OffsetNPV__1down", "JET_Pileup_OffsetNPV__1up", "JET_Pileup_PtTerm__1down", "JET_Pileup_PtTerm__1up", 
			"JET_Pileup_RhoTopology__1down", "JET_Pileup_RhoTopology__1up", "JET_SingleParticle_HighPt__1down", "JET_SingleParticle_HighPt__1up"]
		 
		if "JetSys3" in systematicType:
			myVariations = ["JET_JER_EffectiveNP_1__1down", "JET_JER_EffectiveNP_1__1up", 
			"JET_JER_EffectiveNP_10__1down", "JET_JER_EffectiveNP_10__1up", "JET_JER_EffectiveNP_11__1down", "JET_JER_EffectiveNP_11__1up", 
			"JET_JER_EffectiveNP_12restTerm__1down", "JET_JER_EffectiveNP_12restTerm__1up", "JET_JER_EffectiveNP_2__1down", "JET_JER_EffectiveNP_2__1up", 
			"JET_JER_EffectiveNP_3__1down", "JET_JER_EffectiveNP_3__1up", "JET_JER_EffectiveNP_4__1down", "JET_JER_EffectiveNP_4__1up", 
			"JET_JER_EffectiveNP_5__1down", "JET_JER_EffectiveNP_5__1up", "JET_JER_EffectiveNP_6__1down", "JET_JER_EffectiveNP_6__1up", 
			"JET_JER_EffectiveNP_7__1down", "JET_JER_EffectiveNP_7__1up", "JET_JER_EffectiveNP_8__1down", "JET_JER_EffectiveNP_8__1up", 
			"JET_JER_EffectiveNP_9__1down", "JET_JER_EffectiveNP_9__1up"]

		if "JetSys4" in systematicType:
			myVariations = ["JET_JER_EffectiveNP_1__1down", "JET_JER_EffectiveNP_1__1up", 
			"JET_JER_EffectiveNP_10__1down", "JET_JER_EffectiveNP_10__1up", "JET_JER_EffectiveNP_11__1down", "JET_JER_EffectiveNP_11__1up", 
			"JET_JER_EffectiveNP_12restTerm__1down", "JET_JER_EffectiveNP_12restTerm__1up", "JET_JER_EffectiveNP_2__1down", "JET_JER_EffectiveNP_2__1up", 
			"JET_JER_EffectiveNP_3__1down", "JET_JER_EffectiveNP_3__1up", "JET_JER_EffectiveNP_4__1down", "JET_JER_EffectiveNP_4__1up", 
			"JET_JER_EffectiveNP_5__1down", "JET_JER_EffectiveNP_5__1up", "JET_JER_EffectiveNP_6__1down", "JET_JER_EffectiveNP_6__1up", 
			"JET_JER_EffectiveNP_7__1down", "JET_JER_EffectiveNP_7__1up", "JET_JER_EffectiveNP_8__1down", "JET_JER_EffectiveNP_8__1up", 
			"JET_JER_EffectiveNP_9__1down", "JET_JER_EffectiveNP_9__1up"]

		if "FlavorAllSys1" in systematicType:
			myVariations = ["FT_EFF_Eigen_Light_0__1up", "FT_EFF_Eigen_Light_1__1up", "FT_EFF_Eigen_Light_2__1up", "FT_EFF_Eigen_Light_3__1up", "FT_EFF_Eigen_Light_4__1up"]

		if "FlavorAllSys2" in systematicType:
			myVariations = ["FT_EFF_extrapolation_from_charm__1up", "FT_EFF_extrapolation__1up", "FT_EFF_Eigen_C_3__1up", "FT_EFF_Eigen_C_2__1up", "FT_EFF_Eigen_C_1__1up", 
			"FT_EFF_Eigen_C_0__1up", "FT_EFF_Eigen_B_2__1up", "FT_EFF_Eigen_B_1__1up", "FT_EFF_Eigen_B_0__1up"]

		if "FlavorAllSys3" in systematicType:
			myVariations = ["FT_EFF_Eigen_Light_4__1down", "FT_EFF_Eigen_Light_3__1down", "FT_EFF_Eigen_Light_2__1down", "FT_EFF_Eigen_Light_1__1down", "FT_EFF_Eigen_Light_0__1down"]

		if "FlavorAllSys4" in systematicType:
			myVariations = ["FT_EFF_extrapolation_from_charm__1down", "FT_EFF_extrapolation__1down", "FT_EFF_Eigen_C_3__1down", "FT_EFF_Eigen_C_2__1down", 
			"FT_EFF_Eigen_C_1__1down", "FT_EFF_Eigen_C_0__1down", "FT_EFF_Eigen_B_2__1down", "FT_EFF_Eigen_B_1__1down", "FT_EFF_Eigen_B_0__1down"]

		# METoptions = ["_noMET", ""]
		METoptions = ["_noMET"]
		# myVariations.append("nominal")
		for MET in METoptions:
			for variation in myVariations:
				print "Getting intput histograms for systematic: " + str(variation)
				# if variation != "nominal":
					# print variation
				if singeJet == True:
					hb = myInputFile.Get("histb"+str(MET)+"_"+str(variation));
					hc = myInputFile.Get("histc"+str(MET)+"_"+str(variation));
					hl = myInputFile.Get("histl"+str(MET)+"_"+str(variation));

					yymctot = hb.Integral() + hc.Integral() + hl.Integral()
				
					# hb.Sumw2();hc.Sumw2();hl.Sumw2()
					hyy = hb.Clone("hist_DL1");hyy.Add(hc);hyy.Add(hl);   

					print "Creating new output files for", sample
					fb = ROOT.TFile("inputs_"+outputName+"_b"+str(MET)+"_"+str(variation)+".root","RECREATE");fb.cd();hbtrue = hb.Clone("hist_DL1");
					fc = ROOT.TFile("inputs_"+outputName+"_c"+str(MET)+"_"+str(variation)+".root","RECREATE");fc.cd();hctrue = hc.Clone("hist_DL1");
					fl = ROOT.TFile("inputs_"+outputName+"_l"+str(MET)+"_"+str(variation)+".root","RECREATE");fl.cd();hltrue = hl.Clone("hist_DL1");

					# hbtrue.Sumw2();hctrue.Sumw2();hltrue.Sumw2();

					# print "Writing output files"
					fb.cd();hbtrue.Write();
					fc.cd();hctrue.Write();
					fl.cd();hltrue.Write();

				else:

					hbb = myInputFile.Get("histbb"+str(MET)+"_"+str(variation));
					hbc = myInputFile.Get("histbc"+str(MET)+"_"+str(variation));
					hbl = myInputFile.Get("histbl"+str(MET)+"_"+str(variation));
					hcc = myInputFile.Get("histcc"+str(MET)+"_"+str(variation));
					hcl = myInputFile.Get("histcl"+str(MET)+"_"+str(variation));
					hll = myInputFile.Get("histll"+str(MET)+"_"+str(variation));
					yymctot = hbb.Integral() + hbc.Integral() + hbl.Integral() + hcc.Integral() + hcl.Integral() + hll.Integral();
				
					# hbb.Sumw2();hbc.Sumw2();hbl.Sumw2();hcc.Sumw2();hcl.Sumw2();hll.Sumw2();
					hyy = hbb.Clone("hist_DL1");hyy.Add(hbc);hyy.Add(hbl);hyy.Add(hcc);hyy.Add(hcl);hyy.Add(hll);    

					print "Creating new output files for", sample
					fbb = ROOT.TFile("inputs_"+outputName+"_bb"+str(MET)+"_"+str(variation)+".root","RECREATE");fbb.cd();hbbtrue = hbb.Clone("hist_DL1");
					fbc = ROOT.TFile("inputs_"+outputName+"_bc"+str(MET)+"_"+str(variation)+".root","RECREATE");fbc.cd();hbctrue = hbc.Clone("hist_DL1");
					fbl = ROOT.TFile("inputs_"+outputName+"_bl"+str(MET)+"_"+str(variation)+".root","RECREATE");fbl.cd();hbltrue = hbl.Clone("hist_DL1");
					fcc = ROOT.TFile("inputs_"+outputName+"_cc"+str(MET)+"_"+str(variation)+".root","RECREATE");fcc.cd();hcctrue = hcc.Clone("hist_DL1");
					fcl = ROOT.TFile("inputs_"+outputName+"_cl"+str(MET)+"_"+str(variation)+".root","RECREATE");fcl.cd();hcltrue = hcl.Clone("hist_DL1");
					fll = ROOT.TFile("inputs_"+outputName+"_ll"+str(MET)+"_"+str(variation)+".root","RECREATE");fll.cd();hlltrue = hll.Clone("hist_DL1");

					# hbbtrue.Sumw2();hbctrue.Sumw2();hbltrue.Sumw2();hcctrue.Sumw2();hcltrue.Sumw2();hlltrue.Sumw2();

					# print "Writing sherpa output files"
					fbb.cd();hbbtrue.Write();
					fbc.cd();hbctrue.Write();
					fbl.cd();hbltrue.Write();
					fcc.cd();hcctrue.Write();
					fcl.cd();hcltrue.Write();
					fll.cd();hlltrue.Write();

				print "My yymctot is " + str(yymctot)

				print "Done."
				# elif variation == "nominal":
				# 	# print variation
				# 	if singeJet == True:
				# 		hb = myInputFile.Get("histb"+str(MET));
				# 		hc = myInputFile.Get("histc"+str(MET));
				# 		hl = myInputFile.Get("histl"+str(MET));
				# 		yymctot = hb.Integral() + hc.Integral() + hl.Integral() 
				# 		print "My yymctot is " + str(yymctot)

				# 		hb.Sumw2();hc.Sumw2();hl.Sumw2();

				# 		hyy = hb.Clone("hist_DL1");hyy.Add(hc);hyy.Add(hl);  

				# 		print "Creating new output files for sherpa"
				# 		fb = ROOT.TFile("inputs_b"+str(MET)+"_"+str(variation)+".root","RECREATE");fb.cd();hbtrue = hb.Clone("hist_DL1");
				# 		fc = ROOT.TFile("inputs_c"+str(MET)+"_"+str(variation)+".root","RECREATE");fc.cd();hctrue = hc.Clone("hist_DL1");
				# 		fl = ROOT.TFile("inputs_l"+str(MET)+"_"+str(variation)+".root","RECREATE");fl.cd();hltrue = hl.Clone("hist_DL1");

				# 		hbtrue.Sumw2();hctrue.Sumw2();hltrue.Sumw2();

				# 		print "Writing sherpa output files"
				# 		fb.cd();hbtrue.Write();
				# 		fc.cd();hctrue.Write();
				# 		fl.cd();hltrue.Write();

				# 		print "Done."
				# 	else:
				# 		hbb = myInputFile.Get("histbb"+str(MET));
				# 		hbc = myInputFile.Get("histbc"+str(MET));
				# 		hbl = myInputFile.Get("histbl"+str(MET));
				# 		hcc = myInputFile.Get("histcc"+str(MET));
				# 		hcl = myInputFile.Get("histcl"+str(MET));
				# 		hll = myInputFile.Get("histll"+str(MET));
				# 		yymctot = hbb.Integral() + hbc.Integral() + hbl.Integral() + hcc.Integral() + hcl.Integral() + hll.Integral();
				# 		print "My yymctot is " + str(yymctot)

				# 		hbb.Sumw2();hbc.Sumw2();hbl.Sumw2();hcc.Sumw2();hcl.Sumw2();hll.Sumw2();

				# 		hyy = hbb.Clone("hist_DL1");hyy.Add(hbc);hyy.Add(hbl);hyy.Add(hcc);hyy.Add(hcl);hyy.Add(hll);    

				# 		print "Creating new output files for sherpa"
				# 		fbb = ROOT.TFile("inputs_bb"+str(MET)+"_"+str(variation)+".root","RECREATE");fbb.cd();hbbtrue = hbb.Clone("hist_DL1");
				# 		fbc = ROOT.TFile("inputs_bc"+str(MET)+"_"+str(variation)+".root","RECREATE");fbc.cd();hbctrue = hbc.Clone("hist_DL1");
				# 		fbl = ROOT.TFile("inputs_bl"+str(MET)+"_"+str(variation)+".root","RECREATE");fbl.cd();hbltrue = hbl.Clone("hist_DL1");
				# 		fcc = ROOT.TFile("inputs_cc"+str(MET)+"_"+str(variation)+".root","RECREATE");fcc.cd();hcctrue = hcc.Clone("hist_DL1");
				# 		fcl = ROOT.TFile("inputs_cl"+str(MET)+"_"+str(variation)+".root","RECREATE");fcl.cd();hcltrue = hcl.Clone("hist_DL1");
				# 		fll = ROOT.TFile("inputs_ll"+str(MET)+"_"+str(variation)+".root","RECREATE");fll.cd();hlltrue = hll.Clone("hist_DL1");

				# 		hbbtrue.Sumw2();hbctrue.Sumw2();hbltrue.Sumw2();hcctrue.Sumw2();hcltrue.Sumw2();hlltrue.Sumw2();

				# 		print "Writing sherpa output files"
				# 		fbb.cd();hbbtrue.Write();
				# 		fbc.cd();hbctrue.Write();
				# 		fbl.cd();hbltrue.Write();
				# 		fcc.cd();hcctrue.Write();
				# 		fcl.cd();hcltrue.Write();
				# 		fll.cd();hlltrue.Write();
				# 		print "Done."
