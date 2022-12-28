


def getSysBranchNames(systematicType):

	if "PhotonAllSys1" in systematicType:
		return ["EG_RESOLUTION_AF2__1down", "EG_RESOLUTION_AF2__1up", "EG_RESOLUTION_MATERIALCALO__1down", 
		"EG_RESOLUTION_MATERIALCALO__1up", "EG_RESOLUTION_MATERIALCRYO__1down", "EG_RESOLUTION_MATERIALCRYO__1up", 
		"EG_RESOLUTION_MATERIALGAP__1down", "EG_RESOLUTION_MATERIALGAP__1up", "EG_RESOLUTION_MATERIALIBL__1down", 
		"EG_RESOLUTION_MATERIALIBL__1up", "EG_RESOLUTION_MATERIALID__1down", "EG_RESOLUTION_MATERIALID__1up", 
		"EG_RESOLUTION_MATERIALPP0__1down", "EG_RESOLUTION_MATERIALPP0__1up", "EG_RESOLUTION_PILEUP__1down", 
		"EG_RESOLUTION_PILEUP__1up", "EG_RESOLUTION_SAMPLINGTERM__1down", "EG_RESOLUTION_SAMPLINGTERM__1up", 
		"EG_RESOLUTION_ZSMEARING__1down", "EG_RESOLUTION_ZSMEARING__1up", "EG_SCALE_PEDESTAL__1down", 
		"EG_SCALE_PEDESTAL__1up", "EG_SCALE_PS__ETABIN0__1down", "EG_SCALE_PS__ETABIN0__1up", 
		"EG_SCALE_PS__ETABIN1__1down", "EG_SCALE_PS__ETABIN1__1up", "EG_SCALE_PS__ETABIN2__1down", 
		"EG_SCALE_PS__ETABIN2__1up", "EG_SCALE_PS__ETABIN3__1down", "EG_SCALE_PS__ETABIN3__1up", 
		"EG_SCALE_PS__ETABIN4__1down", "EG_SCALE_PS__ETABIN4__1up", "EG_SCALE_PS__ETABIN5__1down", 
		"EG_SCALE_PS__ETABIN5__1up", "EG_SCALE_PS__ETABIN6__1down", "EG_SCALE_PS__ETABIN6__1up", 
		"EG_SCALE_PS__ETABIN7__1down", "EG_SCALE_PS__ETABIN7__1up", "EG_SCALE_PS__ETABIN8__1down", 
		"EG_SCALE_PS__ETABIN8__1up", "EG_SCALE_PS_BARREL_B12__1down", "EG_SCALE_PS_BARREL_B12__1up"]

	if "PhotonAllSys2" in systematicType:
		return ["EG_SCALE_AF2__1down", "EG_SCALE_AF2__1up", "EG_SCALE_E4SCINTILLATOR__ETABIN0__1down", 
		"EG_SCALE_E4SCINTILLATOR__ETABIN0__1up", "EG_SCALE_E4SCINTILLATOR__ETABIN1__1down", 
		"EG_SCALE_E4SCINTILLATOR__ETABIN1__1up", "EG_SCALE_E4SCINTILLATOR__ETABIN2__1down", 
		"EG_SCALE_E4SCINTILLATOR__ETABIN2__1up", "EG_SCALE_G4__1down", "EG_SCALE_G4__1up", "EG_SCALE_L1GAIN__1down", 
		"EG_SCALE_L1GAIN__1up", "EG_SCALE_L2GAIN__1down", "EG_SCALE_L2GAIN__1up", "EG_SCALE_LARCALIB__ETABIN0__1down", 
		"EG_SCALE_LARCALIB__ETABIN0__1up", "EG_SCALE_LARCALIB__ETABIN1__1down", "EG_SCALE_LARCALIB__ETABIN1__1up", 
		"EG_SCALE_LARELECCALIB__1down", "EG_SCALE_LARELECCALIB__1up", "EG_SCALE_LARELECUNCONV__ETABIN0__1down", 
		"EG_SCALE_LARELECUNCONV__ETABIN0__1up", "EG_SCALE_LARELECUNCONV__ETABIN1__1down", "EG_SCALE_LARELECUNCONV__ETABIN1__1up", 
		"EG_SCALE_LARUNCONVCALIB__ETABIN0__1down", "EG_SCALE_LARUNCONVCALIB__ETABIN0__1up", "EG_SCALE_LARUNCONVCALIB__ETABIN1__1down", 
		"EG_SCALE_LARUNCONVCALIB__ETABIN1__1up", "EG_SCALE_S12__ETABIN0__1down", "EG_SCALE_S12__ETABIN0__1up", 
		"EG_SCALE_S12__ETABIN1__1down", "EG_SCALE_S12__ETABIN1__1up", "EG_SCALE_S12__ETABIN2__1down", 
		"EG_SCALE_S12__ETABIN2__1up", "EG_SCALE_S12__ETABIN3__1down", "EG_SCALE_S12__ETABIN3__1up", 
		"EG_SCALE_S12__ETABIN4__1down", "EG_SCALE_S12__ETABIN4__1up", "EG_SCALE_TOPOCLUSTER_THRES__1down", 
		"EG_SCALE_TOPOCLUSTER_THRES__1up", "EG_SCALE_WTOTS1__1down", "EG_SCALE_WTOTS1__1up"]

	if "PhotonAllSys3" in systematicType:
		return ["EG_SCALE_MATCALO__ETABIN0__1down", "EG_SCALE_MATCALO__ETABIN0__1up", "EG_SCALE_MATCALO__ETABIN1__1down", 
		"EG_SCALE_MATCALO__ETABIN1__1up", "EG_SCALE_MATCALO__ETABIN10__1down", "EG_SCALE_MATCALO__ETABIN10__1up", 
		"EG_SCALE_MATCALO__ETABIN11__1down", "EG_SCALE_MATCALO__ETABIN11__1up", "EG_SCALE_MATCALO__ETABIN2__1down", 
		"EG_SCALE_MATCALO__ETABIN2__1up", "EG_SCALE_MATCALO__ETABIN3__1down", "EG_SCALE_MATCALO__ETABIN3__1up", 
		"EG_SCALE_MATCALO__ETABIN4__1down", "EG_SCALE_MATCALO__ETABIN4__1up", "EG_SCALE_MATCALO__ETABIN5__1down", 
		"EG_SCALE_MATCALO__ETABIN5__1up", "EG_SCALE_MATCALO__ETABIN6__1down", "EG_SCALE_MATCALO__ETABIN6__1up", 
		"EG_SCALE_MATCALO__ETABIN7__1down", "EG_SCALE_MATCALO__ETABIN7__1up", "EG_SCALE_MATCALO__ETABIN8__1down", 
		"EG_SCALE_MATCALO__ETABIN8__1up", "EG_SCALE_MATCALO__ETABIN9__1down", "EG_SCALE_MATCALO__ETABIN9__1up", 
		"EG_SCALE_MATID__ETABIN0__1down", "EG_SCALE_MATID__ETABIN0__1up", "EG_SCALE_MATID__ETABIN1__1down", 
		"EG_SCALE_MATID__ETABIN1__1up", "EG_SCALE_MATID__ETABIN2__1down", "EG_SCALE_MATID__ETABIN2__1up", 
		"EG_SCALE_MATID__ETABIN3__1down", "EG_SCALE_MATID__ETABIN3__1up", "EG_SCALE_MATPP0__ETABIN0__1down", 
		"EG_SCALE_MATPP0__ETABIN0__1up", "EG_SCALE_MATPP0__ETABIN1__1down", "EG_SCALE_MATPP0__ETABIN1__1up", 
		"EG_SCALE_ZEESTAT__1down", "EG_SCALE_ZEESTAT__1up", "EG_SCALE_ZEESYST__1down", "EG_SCALE_ZEESYST__1up"]

	if "PhotonAllSys4" in systematicType:
		return ["EG_SCALE_MATCRYO__ETABIN0__1down", "EG_SCALE_MATCRYO__ETABIN0__1up", "EG_SCALE_MATCRYO__ETABIN1__1down", 
		"EG_SCALE_MATCRYO__ETABIN1__1up", "EG_SCALE_MATCRYO__ETABIN10__1down", "EG_SCALE_MATCRYO__ETABIN10__1up", "EG_SCALE_MATCRYO__ETABIN11__1down", 
		"EG_SCALE_MATCRYO__ETABIN11__1up", "EG_SCALE_MATCRYO__ETABIN2__1down", "EG_SCALE_MATCRYO__ETABIN2__1up", "EG_SCALE_MATCRYO__ETABIN3__1down", 
		"EG_SCALE_MATCRYO__ETABIN3__1up", "EG_SCALE_MATCRYO__ETABIN4__1down", "EG_SCALE_MATCRYO__ETABIN4__1up", "EG_SCALE_MATCRYO__ETABIN5__1down", 
		"EG_SCALE_MATCRYO__ETABIN5__1up", "EG_SCALE_MATCRYO__ETABIN6__1down", "EG_SCALE_MATCRYO__ETABIN6__1up", "EG_SCALE_MATCRYO__ETABIN7__1down", 
		"EG_SCALE_MATCRYO__ETABIN7__1up", "EG_SCALE_MATCRYO__ETABIN8__1down", "EG_SCALE_MATCRYO__ETABIN8__1up", "EG_SCALE_MATCRYO__ETABIN9__1down", 
		"EG_SCALE_MATCRYO__ETABIN9__1up", "PH_EFF_ID_Uncertainty__1down", "PH_EFF_ID_Uncertainty__1up", "PH_EFF_ISO_Uncertainty__1down", 
		"PH_EFF_ISO_Uncertainty__1up", "PH_EFF_TRIGGER_Uncertainty__1down", "PH_EFF_TRIGGER_Uncertainty__1up", "PH_SCALE_CONVEFFICIENCY__1down", 
		"PH_SCALE_CONVEFFICIENCY__1up", "PH_SCALE_CONVFAKERATE__1down", "PH_SCALE_CONVFAKERATE__1up", "PH_SCALE_CONVRADIUS__1down", 
		"PH_SCALE_CONVRADIUS__1up", "PH_SCALE_LEAKAGECONV__1down", "PH_SCALE_LEAKAGECONV__1up", "PH_SCALE_LEAKAGEUNCONV__1down", "PH_SCALE_LEAKAGEUNCONV__1up"]

	if "JetSys1" in systematicType:
		return ["JET_EffectiveNP_Detector1__1down", "JET_EffectiveNP_Detector1__1up", "JET_EffectiveNP_Detector2__1down", "JET_EffectiveNP_Detector2__1up", 
		"JET_EffectiveNP_Mixed1__1down", "JET_EffectiveNP_Mixed1__1up", "JET_EffectiveNP_Mixed2__1down", "JET_EffectiveNP_Mixed2__1up", 
		"JET_EffectiveNP_Mixed3__1down", "JET_EffectiveNP_Mixed3__1up", "JET_EffectiveNP_Modelling1__1down", "JET_EffectiveNP_Modelling1__1up", 
		"JET_EffectiveNP_Modelling2__1down", "JET_EffectiveNP_Modelling2__1up", "JET_EffectiveNP_Modelling3__1down", "JET_EffectiveNP_Modelling3__1up", 
		"JET_EffectiveNP_Modelling4__1down", "JET_EffectiveNP_Modelling4__1up", "JET_EffectiveNP_Statistical1__1down", "JET_EffectiveNP_Statistical1__1up", 
		"JET_EffectiveNP_Statistical2__1down", "JET_EffectiveNP_Statistical2__1up", "JET_EffectiveNP_Statistical3__1down", "JET_EffectiveNP_Statistical3__1up", 
		"JET_EffectiveNP_Statistical4__1down", "JET_EffectiveNP_Statistical4__1up", "JET_EffectiveNP_Statistical5__1down", "JET_EffectiveNP_Statistical5__1up", 
		"JET_EffectiveNP_Statistical6__1down", "JET_EffectiveNP_Statistical6__1up"]

	if "JetSys2" in systematicType:
		# "JET_PunchThrough_MC16__1down", "JET_PunchThrough_MC16__1up", 
		return ["JET_BJES_Response__1down", "JET_BJES_Response__1up", "JET_EtaIntercalibration_Modelling__1down", "JET_EtaIntercalibration_Modelling__1up", 
		"JET_EtaIntercalibration_NonClosure_2018data__1down", "JET_EtaIntercalibration_NonClosure_2018data__1up", "JET_EtaIntercalibration_NonClosure_highE__1down", 
		"JET_EtaIntercalibration_NonClosure_highE__1up", "JET_EtaIntercalibration_NonClosure_negEta__1down", "JET_EtaIntercalibration_NonClosure_negEta__1up", 
		"JET_EtaIntercalibration_NonClosure_posEta__1down", "JET_EtaIntercalibration_NonClosure_posEta__1up", "JET_EtaIntercalibration_TotalStat__1down", 
		"JET_EtaIntercalibration_TotalStat__1up", "JET_fJvtEfficiency__1down", "JET_fJvtEfficiency__1up", "JET_Flavor_Composition__1down", "JET_Flavor_Composition__1up", 
		"JET_Flavor_Response__1down", "JET_Flavor_Response__1up", "JET_JvtEfficiency__1down", "JET_JvtEfficiency__1up", "JET_Pileup_OffsetMu__1down", 
		"JET_Pileup_OffsetMu__1up", "JET_Pileup_OffsetNPV__1down", "JET_Pileup_OffsetNPV__1up", "JET_Pileup_PtTerm__1down", "JET_Pileup_PtTerm__1up", 
		"JET_Pileup_RhoTopology__1down", "JET_Pileup_RhoTopology__1up", "JET_SingleParticle_HighPt__1down", 
		"JET_SingleParticle_HighPt__1up"]
	 
	if "JetSys3" in systematicType:
		# "JET_JER_DataVsMC_MC16__1down", "JET_JER_DataVsMC_MC16__1up",
		return ["JET_JER_EffectiveNP_1__1down", "JET_JER_EffectiveNP_1__1up", 
		"JET_JER_EffectiveNP_10__1down", "JET_JER_EffectiveNP_10__1up", "JET_JER_EffectiveNP_11__1down", "JET_JER_EffectiveNP_11__1up", 
		"JET_JER_EffectiveNP_12restTerm__1down", "JET_JER_EffectiveNP_12restTerm__1up", "JET_JER_EffectiveNP_2__1down", "JET_JER_EffectiveNP_2__1up", 
		"JET_JER_EffectiveNP_3__1down", "JET_JER_EffectiveNP_3__1up", "JET_JER_EffectiveNP_4__1down", "JET_JER_EffectiveNP_4__1up", 
		"JET_JER_EffectiveNP_5__1down", "JET_JER_EffectiveNP_5__1up", "JET_JER_EffectiveNP_6__1down", "JET_JER_EffectiveNP_6__1up", 
		"JET_JER_EffectiveNP_7__1down", "JET_JER_EffectiveNP_7__1up", "JET_JER_EffectiveNP_8__1down", "JET_JER_EffectiveNP_8__1up", 
		"JET_JER_EffectiveNP_9__1down", "JET_JER_EffectiveNP_9__1up"]

	if "JetSys4" in systematicType:
		# "JET_JER_DataVsMC_MC16__1down", "JET_JER_DataVsMC_MC16__1up", 
		return ["JET_JER_EffectiveNP_1__1down", "JET_JER_EffectiveNP_1__1up", 
		"JET_JER_EffectiveNP_10__1down", "JET_JER_EffectiveNP_10__1up", "JET_JER_EffectiveNP_11__1down", "JET_JER_EffectiveNP_11__1up", 
		"JET_JER_EffectiveNP_12restTerm__1down", "JET_JER_EffectiveNP_12restTerm__1up", "JET_JER_EffectiveNP_2__1down", "JET_JER_EffectiveNP_2__1up", 
		"JET_JER_EffectiveNP_3__1down", "JET_JER_EffectiveNP_3__1up", "JET_JER_EffectiveNP_4__1down", "JET_JER_EffectiveNP_4__1up", 
		"JET_JER_EffectiveNP_5__1down", "JET_JER_EffectiveNP_5__1up", "JET_JER_EffectiveNP_6__1down", "JET_JER_EffectiveNP_6__1up", 
		"JET_JER_EffectiveNP_7__1down", "JET_JER_EffectiveNP_7__1up", "JET_JER_EffectiveNP_8__1down", "JET_JER_EffectiveNP_8__1up", 
		"JET_JER_EffectiveNP_9__1down", "JET_JER_EffectiveNP_9__1up"]

	if "FlavorAllSys1" in systematicType:
		return ["FT_EFF_Eigen_Light_0__1up", "FT_EFF_Eigen_Light_1__1up", "FT_EFF_Eigen_Light_2__1up", "FT_EFF_Eigen_Light_3__1up", "FT_EFF_Eigen_Light_4__1up"]

	if "FlavorAllSys2" in systematicType:
		return ["FT_EFF_extrapolation_from_charm__1up", "FT_EFF_extrapolation__1up", "FT_EFF_Eigen_C_3__1up", "FT_EFF_Eigen_C_2__1up", "FT_EFF_Eigen_C_1__1up", 
		"FT_EFF_Eigen_C_0__1up", "FT_EFF_Eigen_B_2__1up", "FT_EFF_Eigen_B_1__1up", "FT_EFF_Eigen_B_0__1up"]

	if "FlavorAllSys3" in systematicType:
		return ["FT_EFF_Eigen_Light_4__1down", "FT_EFF_Eigen_Light_3__1down", "FT_EFF_Eigen_Light_2__1down", "FT_EFF_Eigen_Light_1__1down", "FT_EFF_Eigen_Light_0__1down"]

	if "FlavorAllSys4" in systematicType:
		return ["FT_EFF_extrapolation_from_charm__1down", "FT_EFF_extrapolation__1down", "FT_EFF_Eigen_C_3__1down", "FT_EFF_Eigen_C_2__1down", 
		"FT_EFF_Eigen_C_1__1down", "FT_EFF_Eigen_C_0__1down", "FT_EFF_Eigen_B_2__1down", "FT_EFF_Eigen_B_1__1down", "FT_EFF_Eigen_B_0__1down"]

# myVariations.append("nominal")


myVariations = []
# print myVariations
# systematicType = "FlavorAllSys4"
# systematicType = "FlavorAllSys3"
# systematicType = "FlavorAllSys2"
systematicType = "FlavorAllSys1"

# systematicType = "PhotonAllSys4"
# systematicType = "PhotonAllSys3"
# systematicType = "PhotonAllSys2"
# systematicType = "PhotonAllSys1"

# systematicType = "JetSys4"
# systematicType = "JetSys3"
# systematicType = "JetSys2"
# systematicType = "JetSys1"

# mySysTypes = ["FlavorAllSys1", "FlavorAllSys2", "FlavorAllSys3", "FlavorAllSys4"] 
# mySysTypes = ["PhotonAllSys1", "PhotonAllSys2", "PhotonAllSys3", "PhotonAllSys4"]
# mySysTypes = ["JetSys1", "JetSys2", "JetSys3"]
mySysTypes = [ "PhotonAllSys4"]

# mySysTypes = ["FlavorAllSys1", "FlavorAllSys2", "FlavorAllSys3", "FlavorAllSys4",
# 			  "PhotonAllSys1", "PhotonAllSys2", "PhotonAllSys3", "PhotonAllSys4", 
# 			  "JetSys1", "JetSys2", "JetSys3", "JetSys4"]

for systematicType in mySysTypes:			  
	# print ''systematicType
	myVariations = getSysBranchNames(systematicType)
	# for variation in myVariations:
	# 	print "\item ", variation

	# myLeaves = ["XSWeight", "HGamWeight", "yyHF_leadjet_truthlabel", "yyHF_subleadjet_truthlabel", "yyHF_leadjet_btagbin", "yyHF_subleadjet_btagbin", "yyHF_Njet_central", "yyHFjj_weight", 
	# 			"yyHFj_weight", "yyHF_met", "yyHF_nelectron", "yyHF_nmuon", "isPassed", "m_yy", "yyHF_cutFlow", "m_yyjj",
	# 			"yyHF_subleadjet_pt", "yyHF_subleadjet_phi", "yyHF_subleadjet_m", "yyHF_subleadjet_eta",
	# 			"yyHF_leadjet_pt", "yyHF_leadjet_phi", "yyHF_leadjet_m", "yyHF_leadjet_eta", "pT_yy"]


	# # myLeaves = ["pT_yy"]


	# myTruthLeaves = ["yyHF_N_bjets", "yyHF_N_cjets", "yyHF_Njet_central", "yyHF_cutFlow", "yyHF_jcat", "yyHF_jjcat", 
	# 			"yyHF_met", "yyHF_nelectron", "yyHF_nmuon",]

	# # for leaf in myLeaves:
	# # 	# print leaf
	# # 	print 'tree->Branch("{}",     &{});'.format(leaf, leaf)

	# # for leaf in myTruthLeaves:
	# # 	# print leaf
	# # 	print 'tree->Branch("Truth_{}",     &Truth_{});'.format(leaf, leaf)

	# # print "float HGamWeight; //!"
	# # print "float XSWeight; //!"

	# # print "int yyHF_leadjet_truthlabel; //!"
	# # print "int yyHF_subleadjet_truthlabel; //!"
	# # print "int yyHF_leadjet_btagbin; //!"
	# # print "int yyHF_subleadjet_btagbin; //!"
	# # print "int yyHF_Njet_central; //!"
	# # print "float yyHFjj_weight; //!"
	# # print "float yyHFj_weight; //!"
	# # print "float yyHF_met; //!"
	# # print "int yyHF_nelectron; //!"
	# # print "int yyHF_nmuon; //!"
	# # print "bool isPassed; //!"	
	# # print "int yyHF_cutFlow; //!"	
	# # print "float m_yy; //!"
	# # print "float m_yyjj; //!"
	# # print "float pT_yy; //!"

	# # print "float yyHF_subleadjet_pt; //!"
	# # print "float yyHF_subleadjet_phi; //!"
	# # print "float yyHF_subleadjet_m; //!"
	# # print "float yyHF_subleadjet_eta; //!"

	# # print "float Truth_yyHF_N_bjets; //!"
	# # print "float yyHF_leadjet_phi; //!"
	# # print "float yyHF_leadjet_m; //!"
	# # print "float yyHF_leadjet_eta; //!"



	# # print "int Truth_yyHF_Njet_central; //!"
	# # print "int Truth_yyHF_N_bjets; //!"
	# # print "int Truth_yyHF_N_cjets; //!"
	# # print "int Truth_yyHF_cutFlow; //!"
	# # print "int Truth_yyHF_jcat; //!"
	# # print "int Truth_yyHF_jjcat; //!"

	# # print "int Truth_yyHF_nelectron; //!"
	# # print "int Truth_yyHF_nmuon; //!"

	# # print "float Truth_yyHF_met; //!"

	# # print
	# # print
	# # print
	# # print
	# # print 'if (m_sysType == {})'.format(systematicType)+"{"
	# # for variation in myVariations:
	# # 	for leaf in myLeaves:
	# # 		# print leaf
	# # 		print 'tree->Branch("{}_{}",     &{}_{});'.format(variation, leaf, variation, leaf)
	# # print '}'
	# for variation in myVariations:
	# 	print "float {}_HGamWeight; //!".format(variation)
	# 	# print "float {}_XSWeight; //!".format(variation)

	# 	print "int {}_yyHF_leadjet_truthlabel; //!".format(variation)
	# 	print "int {}_yyHF_subleadjet_truthlabel; //!".format(variation)
	# 	print "int {}_yyHF_leadjet_btagbin; //!".format(variation)
	# 	print "int {}_yyHF_subleadjet_btagbin; //!".format(variation)
	# 	print "int {}_yyHF_Njet_central; //!".format(variation)
	# 	print "float {}_yyHFjj_weight; //!".format(variation)
	# 	print "float {}_yyHFj_weight; //!".format(variation)
	# 	print "float {}_yyHF_met; //!".format(variation)
	# 	print "int {}_yyHF_nelectron; //!".format(variation)
	# 	print "int {}_yyHF_nmuon; //!".format(variation)
	# 	print "bool {}_isPassed; //!".format(variation)	
	# 	print "int {}_yyHF_cutFlow; //!".format(variation)	
	# 	print "float {}_m_yy; //!".format(variation)
	# 	print "float {}_m_yyjj; //!".format(variation)
	# 	print "float {}_pT_yy; //!".format(variation)

	# 	print "float {}_yyHF_subleadjet_pt; //!".format(variation)
	# 	print "float {}_yyHF_subleadjet_phi; //!".format(variation)
	# 	print "float {}_yyHF_subleadjet_m; //!".format(variation)
	# 	print "float {}_yyHF_subleadjet_eta; //!".format(variation)

	# 	print "float {}_yyHF_leadjet_pt; //!".format(variation)
	# 	print "float {}_yyHF_leadjet_phi; //!".format(variation)
	# 	print "float {}_yyHF_leadjet_m; //!".format(variation)
	# 	print "float {}_yyHF_leadjet_eta; //!".format(variation)

	# # print
	# # print
	# # print
	# # print
	# print
	# print 'if (m_sysType == {})'.format(systematicType)+"{"
	# for variation in myVariations:
	# 	# print '  const xAOD::EventInfo *HGamEventInfo_{} = NULL;'.format(variation)
	# 	print '  if (! event->retrieve(HGamEventInfo_{}, "HGamEventInfo_{}").isSuccess()) '.format(variation, variation)+"{"
	# 	print '    Error("execute()", "Failed to retrieve HGamEventInfo_{}. Exiting.");'.format(variation, variation, variation)
	# 	print '    return EL::StatusCode::FAILURE;'
	# 	print '  }'
	# print '}'

	# # print
	# # print
	# # print
	# # print

	# # print 'Truth_yyHF_Njet_central = HGamTruthEventInfo->auxdata<int>("yyHF_Njet_central");'
	# # print 'Truth_yyHF_N_bjets = HGamTruthEventInfo->auxdata<int>("yyHF_N_bjets");'
	# # print 'Truth_yyHF_N_cjets = HGamTruthEventInfo->auxdata<int>("yyHF_N_cjets");'
	# # print 'Truth_yyHF_cutFlow = HGamTruthEventInfo->auxdata<int>("yyHF_cutFlow");'
	# # print 'Truth_yyHF_jcat = HGamTruthEventInfo->auxdata<int>("yyHF_jcat");'
	# # print 'Truth_yyHF_jjcat = HGamTruthEventInfo->auxdata<int>("yyHF_jjcat");'
	# # print 'Truth_yyHF_nelectron = HGamTruthEventInfo->auxdata<int>("yyHF_nelectron");'
	# # print 'Truth_yyHF_nmuon = HGamTruthEventInfo->auxdata<int>("yyHF_nmuon");'
	# # print 'Truth_yyHF_met = HGamTruthEventInfo->auxdata<float>("yyHF_met");'




	# # print 'yyHF_leadjet_truthlabel = HGamEventInfo->auxdata<int>("yyHF_leadjet_truthlabel");'
	# # print 'yyHF_subleadjet_truthlabel = HGamEventInfo->auxdata<int>("yyHF_subleadjet_truthlabel");'
	# # print 'yyHF_leadjet_btagbin = HGamEventInfo->auxdata<int>("yyHF_leadjet_btagbin");'
	# # print 'yyHF_subleadjet_btagbin = HGamEventInfo->auxdata<int>("yyHF_subleadjet_btagbin");'
	# # print 'yyHF_Njet_central = HGamEventInfo->auxdata<int>("yyHF_Njet_central");'
	# # print 'yyHFjj_weight = HGamEventInfo->auxdata<float>("yyHFjj_weight");'
	# # print 'yyHFj_weight = HGamEventInfo->auxdata<float>("yyHFj_weight");'
	# # print 'yyHF_met = HGamEventInfo->auxdata<float>("yyHF_met");'
	# # print 'yyHF_nelectron = HGamEventInfo->auxdata<int>("yyHF_nelectron");'
	# # print 'yyHF_nmuon = HGamEventInfo->auxdata<int>("yyHF_nmuon");'
	# # print 'isPassed = HGamEventInfo->auxdata<char>("isPassed");'
	# # print 'yyHF_cutFlow = HGamEventInfo->auxdata<int>("yyHF_cutFlow");'
	# # print 'm_yy = HGamEventInfo->auxdata<float>("m_yy");'
	# # print 'm_yyjj = HGamEventInfo->auxdata<float>("m_yyjj");'
	# # print 'pT_yy = HGamEventInfo->auxdata<float>("pT_yy");'

	# # print 'yyHF_subleadjet_pt = HGamEventInfo->auxdata<float>("yyHF_subleadjet_pt");'
	# # print 'yyHF_subleadjet_phi = HGamEventInfo->auxdata<float>("yyHF_subleadjet_phi");'
	# # print 'yyHF_subleadjet_m = HGamEventInfo->auxdata<float>("yyHF_subleadjet_m");'
	# # print 'yyHF_subleadjet_eta = HGamEventInfo->auxdata<float>("yyHF_subleadjet_eta");'

	# # print 'yyHF_leadjet_pt = HGamEventInfo->auxdata<float>("yyHF_leadjet_pt");'
	# # print 'yyHF_leadjet_phi = HGamEventInfo->auxdata<float>("yyHF_leadjet_phi");'
	# # print 'yyHF_leadjet_m = HGamEventInfo->auxdata<float>("yyHF_leadjet_m");'
	# # print 'yyHF_leadjet_eta = HGamEventInfo->auxdata<float>("yyHF_leadjet_eta");'
	# # print
	# # print 'if (m_sysType == {})'.format(systematicType)+"{"

	# # for variation in myVariations:
	# # 	print '{}_HGamWeight = HGamEventInfo_{}->auxdataConst<float>("weight");'.format(variation, variation)
	# # 	# print '{}_XSWeight = HGamEventInfo_{}->auxdataConst<float>("crossSectionBRfilterEff");'.format(variation, variation)
	# # 	print '{}_yyHF_leadjet_truthlabel = HGamEventInfo_{}->auxdata<int>("yyHF_leadjet_truthlabel");'.format(variation, variation)
	# # 	print '{}_yyHF_subleadjet_truthlabel = HGamEventInfo_{}->auxdata<int>("yyHF_subleadjet_truthlabel");'.format(variation, variation)
	# # 	print '{}_yyHF_leadjet_btagbin = HGamEventInfo_{}->auxdata<int>("yyHF_leadjet_btagbin");'.format(variation, variation)
	# # 	print '{}_yyHF_subleadjet_btagbin = HGamEventInfo_{}->auxdata<int>("yyHF_subleadjet_btagbin");'.format(variation, variation)
	# # 	print '{}_yyHF_Njet_central = HGamEventInfo_{}->auxdata<int>("yyHF_Njet_central");'.format(variation, variation)
	# # 	print '{}_yyHFjj_weight = HGamEventInfo_{}->auxdata<float>("yyHFjj_weight");'.format(variation, variation)
	# # 	print '{}_yyHFj_weight = HGamEventInfo_{}->auxdata<float>("yyHFj_weight");'.format(variation, variation)
	# # 	print '{}_yyHF_met = HGamEventInfo_{}->auxdata<float>("yyHF_met");'.format(variation, variation)
	# # 	print '{}_yyHF_nelectron = HGamEventInfo_{}->auxdata<int>("yyHF_nelectron");'.format(variation, variation)
	# # 	print '{}_yyHF_nmuon = HGamEventInfo_{}->auxdata<int>("yyHF_nmuon");'.format(variation, variation)
	# # 	print '{}_isPassed = HGamEventInfo_{}->auxdata<char>("isPassed");'.format(variation, variation)
	# # 	print '{}_yyHF_cutFlow = HGamEventInfo_{}->auxdata<int>("yyHF_cutFlow");'.format(variation, variation)
	# # 	print '{}_m_yy = HGamEventInfo_{}->auxdata<float>("m_yy");'.format(variation, variation)
	# # 	print '{}_m_yyjj = HGamEventInfo_{}->auxdata<float>("m_yyjj");'.format(variation, variation)
	# # 	print '{}_pT_yy = HGamEventInfo_{}->auxdata<float>("pT_yy");'.format(variation, variation)
	# # 	print '{}_yyHF_subleadjet_pt = HGamEventInfo_{}->auxdata<float>("yyHF_subleadjet_pt");'.format(variation, variation)
	# # 	print '{}_yyHF_subleadjet_phi = HGamEventInfo_{}->auxdata<float>("yyHF_subleadjet_phi");'.format(variation, variation)
	# # 	print '{}_yyHF_subleadjet_m = HGamEventInfo_{}->auxdata<float>("yyHF_subleadjet_m");'.format(variation, variation)
	# # 	print '{}_yyHF_subleadjet_eta = HGamEventInfo_{}->auxdata<float>("yyHF_subleadjet_eta");'.format(variation, variation)
	# # 	print '{}_yyHF_leadjet_pt = HGamEventInfo_{}->auxdata<float>("yyHF_leadjet_pt");'.format(variation, variation)
	# # 	print '{}_yyHF_leadjet_phi = HGamEventInfo_{}->auxdata<float>("yyHF_leadjet_phi");'.format(variation, variation)
	# # 	print '{}_yyHF_leadjet_m = HGamEventInfo_{}->auxdata<float>("yyHF_leadjet_m");'.format(variation, variation)
	# # 	print '{}_yyHF_leadjet_eta = HGamEventInfo_{}->auxdata<float>("yyHF_leadjet_eta");'.format(variation, variation)
	# # print '}'
	# # print
	# # print
	# # print
	# # print





	# for variation in myVariations:
	# 	print 'myNewTree->Branch("{}_yyHF_leadjet_truthlabel",     &{}_yyHF_leadjet_truthlabel);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHF_subleadjet_truthlabel",  &{}_yyHF_subleadjet_truthlabel);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHF_leadjet_btagbin",        &{}_yyHF_leadjet_btagbin);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHF_subleadjet_btagbin",     &{}_yyHF_subleadjet_btagbin);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHF_Njet_central",           &{}_yyHF_Njet_central);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHF_cutFlow",                &{}_yyHF_cutFlow);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHF_nelectron",              &{}_yyHF_nelectron);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHF_nmuon",                  &{}_yyHF_nmuon);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_isPassed",                    &{}_isPassed);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHFjj_weight",               &{}_yyHFjj_weight);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHFj_weight",                &{}_yyHFj_weight);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHF_met",                    &{}_yyHF_met);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_m_yy",                        &{}_m_yy);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_m_yyjj",                      &{}_m_yyjj);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_pT_yy",                       &{}_pT_yy);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_HGamWeight",                  &{}_HGamWeight);'.format(variation, variation)

	# 	print 'myNewTree->Branch("{}_yyHF_subleadjet_pt",          &{}_yyHF_subleadjet_pt);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHF_subleadjet_phi",         &{}_yyHF_subleadjet_phi);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHF_subleadjet_m",           &{}_yyHF_subleadjet_m);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHF_subleadjet_eta",         &{}_yyHF_subleadjet_eta);'.format(variation, variation)

	# 	print 'myNewTree->Branch("{}_yyHF_leadjet_pt",             &{}_yyHF_leadjet_pt);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHF_leadjet_phi",            &{}_yyHF_leadjet_phi);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHF_leadjet_m",              &{}_yyHF_leadjet_m);'.format(variation, variation)
	# 	print 'myNewTree->Branch("{}_yyHF_leadjet_eta",            &{}_yyHF_leadjet_eta);'.format(variation, variation)


	# for variation in myVariations:
	# 	print 'int NEW_{}_yyHF_leadjet_truthlabel;    myNewTree->Branch("{}_yyHF_leadjet_truthlabel",     &NEW_{}_yyHF_leadjet_truthlabel);'.format(variation, variation, variation)
	# 	print 'int NEW_{}_yyHF_subleadjet_truthlabel; myNewTree->Branch("{}_yyHF_subleadjet_truthlabel",  &NEW_{}_yyHF_subleadjet_truthlabel);'.format(variation, variation, variation)
	# 	print 'int NEW_{}_yyHF_leadjet_btagbin;       myNewTree->Branch("{}_yyHF_leadjet_btagbin",        &NEW_{}_yyHF_leadjet_btagbin);'.format(variation, variation, variation)
	# 	print 'int NEW_{}_yyHF_subleadjet_btagbin;    myNewTree->Branch("{}_yyHF_subleadjet_btagbin",     &NEW_{}_yyHF_subleadjet_btagbin);'.format(variation, variation, variation)
	# 	print 'int NEW_{}_yyHF_Njet_central;          myNewTree->Branch("{}_yyHF_Njet_central",           &NEW_{}_yyHF_Njet_central);'.format(variation, variation, variation)
	# 	print 'int NEW_{}_yyHF_cutFlow;               myNewTree->Branch("{}_yyHF_cutFlow",                &NEW_{}_yyHF_cutFlow);'.format(variation, variation, variation)
	# 	print 'int NEW_{}_yyHF_nelectron;             myNewTree->Branch("{}_yyHF_nelectron",              &NEW_{}_yyHF_nelectron);'.format(variation, variation, variation)
	# 	print 'int NEW_{}_yyHF_nmuon;                 myNewTree->Branch("{}_yyHF_nmuon",                  &NEW_{}_yyHF_nmuon);'.format(variation, variation, variation)
	# 	print 'bool  NEW_{}_isPassed;                 myNewTree->Branch("{}_isPassed",                    &NEW_{}_isPassed);'.format(variation, variation, variation)
	# 	print 'float NEW_{}_yyHFjj_weight;            myNewTree->Branch("{}_yyHFjj_weight",               &NEW_{}_yyHFjj_weight);'.format(variation, variation, variation)
	# 	print 'float NEW_{}_yyHFj_weight;             myNewTree->Branch("{}_yyHFj_weight",                &NEW_{}_yyHFj_weight);'.format(variation, variation, variation)
	# 	print 'float NEW_{}_yyHF_met;                 myNewTree->Branch("{}_yyHF_met",                    &NEW_{}_yyHF_met);'.format(variation, variation, variation)
	# 	print 'float NEW_{}_m_yy;                     myNewTree->Branch("{}_m_yy",                        &NEW_{}_m_yy);'.format(variation, variation, variation)
	# 	print 'float NEW_{}_m_yyjj;                   myNewTree->Branch("{}_m_yyjj",                      &NEW_{}_m_yyjj);'.format(variation, variation, variation)
	# 	print 'float NEW_{}_pT_yy;                    myNewTree->Branch("{}_pT_yy",                       &NEW_{}_pT_yy);'.format(variation, variation, variation)
	# 	print 'float NEW_{}_HGamWeight;               myNewTree->Branch("{}_HGamWeight",                  &NEW_{}_HGamWeight);'.format(variation, variation, variation)

	# 	print 'float NEW_{}_yyHF_subleadjet_pt;       myNewTree->Branch("{}_yyHF_subleadjet_pt",          &NEW_{}_yyHF_subleadjet_pt);'.format(variation, variation, variation)
	# 	print 'float NEW_{}_yyHF_subleadjet_phi;      myNewTree->Branch("{}_yyHF_subleadjet_phi",         &NEW_{}_yyHF_subleadjet_phi);'.format(variation, variation, variation)
	# 	print 'float NEW_{}_yyHF_subleadjet_m;        myNewTree->Branch("{}_yyHF_subleadjet_m",           &NEW_{}_yyHF_subleadjet_m);'.format(variation, variation, variation)
	# 	print 'float NEW_{}_yyHF_subleadjet_eta;      myNewTree->Branch("{}_yyHF_subleadjet_eta",         &NEW_{}_yyHF_subleadjet_eta);'.format(variation, variation, variation)

	# 	print 'float NEW_{}_yyHF_leadjet_pt;          myNewTree->Branch("{}_yyHF_leadjet_pt",             &NEW_{}_yyHF_leadjet_pt);'.format(variation, variation, variation)
	# 	print 'float NEW_{}_yyHF_leadjet_phi;         myNewTree->Branch("{}_yyHF_leadjet_phi",            &NEW_{}_yyHF_leadjet_phi);'.format(variation, variation, variation)
	# 	print 'float NEW_{}_yyHF_leadjet_m;           myNewTree->Branch("{}_yyHF_leadjet_m",              &NEW_{}_yyHF_leadjet_m);'.format(variation, variation, variation)
	# 	print 'float NEW_{}_yyHF_leadjet_eta;         myNewTree->Branch("{}_yyHF_leadjet_eta",            &NEW_{}_yyHF_leadjet_eta);'.format(variation, variation, variation)

	# for variation in myVariations:
	# 	print 'NEW_{}_yyHF_leadjet_truthlabel = {}_yyHF_leadjet_truthlabel;'.format(variation, variation)
	# 	print 'NEW_{}_yyHF_subleadjet_truthlabel = {}_yyHF_subleadjet_truthlabel;'.format(variation, variation)
	# 	print 'NEW_{}_yyHF_leadjet_btagbin = {}_yyHF_leadjet_btagbin;'.format(variation, variation)
	# 	print 'NEW_{}_yyHF_subleadjet_btagbin = {}_yyHF_subleadjet_btagbin;'.format(variation, variation)
	# 	print 'NEW_{}_yyHF_Njet_central = {}_yyHF_Njet_central;'.format(variation, variation)
	# 	print 'NEW_{}_yyHF_cutFlow = {}_yyHF_cutFlow;'.format(variation, variation)
	# 	print 'NEW_{}_yyHF_nelectron = {}_yyHF_nelectron;'.format(variation, variation)
	# 	print 'NEW_{}_yyHF_nmuon = {}_yyHF_nmuon;'.format(variation, variation)
	# 	print 'NEW_{}_isPassed = {}_isPassed;'.format(variation, variation)
	# 	print 'NEW_{}_yyHFjj_weight = {}_yyHFjj_weight;'.format(variation, variation)
	# 	print 'NEW_{}_yyHFj_weight = {}_yyHFj_weight;'.format(variation, variation)
	# 	print 'NEW_{}_yyHF_met = {}_yyHF_met;'.format(variation, variation)
	# 	print 'NEW_{}_m_yy = {}_m_yy;'.format(variation, variation)
	# 	print 'NEW_{}_m_yyjj = {}_m_yyjj;'.format(variation, variation)
	# 	print 'NEW_{}_pT_yy = {}_pT_yy;'.format(variation, variation)
	# 	print 'NEW_{}_HGamWeight = {}_HGamWeight;'.format(variation, variation)

	# 	print 'NEW_{}_yyHF_subleadjet_pt = {}_yyHF_subleadjet_pt;'.format(variation, variation)
	# 	print 'NEW_{}_yyHF_subleadjet_phi = {}_yyHF_subleadjet_phi;'.format(variation, variation)
	# 	print 'NEW_{}_yyHF_subleadjet_m = {}_yyHF_subleadjet_m;'.format(variation, variation)
	# 	print 'NEW_{}_yyHF_subleadjet_eta = {}_yyHF_subleadjet_eta;'.format(variation, variation)

	# 	print 'NEW_{}_yyHF_leadjet_pt  = {}_yyHF_leadjet_pt;'.format(variation, variation, variation)
	# 	print 'NEW_{}_yyHF_leadjet_phi  = {}_yyHF_leadjet_phi;'.format(variation, variation, variation)
	# 	print 'NEW_{}_yyHF_leadjet_m  = {}_yyHF_leadjet_m;'.format(variation, variation, variation)
	# 	print 'NEW_{}_yyHF_leadjet_eta  = {}_yyHF_leadjet_eta;'.format(variation, variation, variation)

	for variation in myVariations:
		print 'int {}_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("{}.yyHF_leadjet_truthlabel",     &{}_yyHF_leadjet_truthlabel);'.format(variation, variation, variation)
		print 'int {}_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("{}.yyHF_subleadjet_truthlabel",  &{}_yyHF_subleadjet_truthlabel);'.format(variation, variation, variation)
		print 'int {}_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("{}.yyHF_leadjet_btagbin",        &{}_yyHF_leadjet_btagbin);'.format(variation, variation, variation)
		print 'int {}_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("{}.yyHF_subleadjet_btagbin",     &{}_yyHF_subleadjet_btagbin);'.format(variation, variation, variation)
		print 'int {}_yyHF_Njet_central;          myTree->SetBranchAddress("{}.yyHF_Njet_central",           &{}_yyHF_Njet_central);'.format(variation, variation, variation)
		print 'int {}_yyHF_cutFlow;               myTree->SetBranchAddress("{}.yyHF_cutFlow",                &{}_yyHF_cutFlow);'.format(variation, variation, variation)
		print 'int {}_yyHF_nelectron;             myTree->SetBranchAddress("{}.yyHF_nelectron",              &{}_yyHF_nelectron);'.format(variation, variation, variation)
		print 'int {}_yyHF_nmuon;                 myTree->SetBranchAddress("{}.yyHF_nmuon",                  &{}_yyHF_nmuon);'.format(variation, variation, variation)
		print 'bool {}_isPassed;                  myTree->SetBranchAddress("{}.isPassed",                    &{}_isPassed);'.format(variation, variation, variation)
		print 'float {}_yyHFjj_weight;            myTree->SetBranchAddress("{}.yyHFjj_weight",               &{}_yyHFjj_weight);'.format(variation, variation, variation)
		print 'float {}_yyHFj_weight;             myTree->SetBranchAddress("{}.yyHFj_weight",                &{}_yyHFj_weight);'.format(variation, variation, variation)
		print 'float {}_yyHF_met;                 myTree->SetBranchAddress("{}.yyHF_met",                    &{}_yyHF_met);'.format(variation, variation, variation)
		print 'float {}_m_yy;                     myTree->SetBranchAddress("{}.m_yy",                        &{}_m_yy);'.format(variation, variation, variation)
		print 'float {}_m_yyjj;                   myTree->SetBranchAddress("{}.m_yyjj",                      &{}_m_yyjj);'.format(variation, variation, variation)
		print 'float {}_pT_yy;                    myTree->SetBranchAddress("{}.pT_yy",                       &{}_pT_yy);'.format(variation, variation, variation)
		print 'float {}_HGamWeight;               myTree->SetBranchAddress("{}.HGamWeight",                  &{}_HGamWeight);'.format(variation, variation, variation)

		print 'float {}_yyHF_subleadjet_pt;       myTree->SetBranchAddress("{}.yyHF_subleadjet_pt",          &{}_yyHF_subleadjet_pt);'.format(variation, variation, variation)
		print 'float {}_yyHF_subleadjet_phi;      myTree->SetBranchAddress("{}.yyHF_subleadjet_phi",         &{}_yyHF_subleadjet_phi);'.format(variation, variation, variation)
		print 'float {}_yyHF_subleadjet_m;        myTree->SetBranchAddress("{}.yyHF_subleadjet_m",           &{}_yyHF_subleadjet_m);'.format(variation, variation, variation)
		print 'float {}_yyHF_subleadjet_eta;      myTree->SetBranchAddress("{}.yyHF_subleadjet_eta",         &{}_yyHF_subleadjet_eta);'.format(variation, variation, variation)

		print 'float {}_yyHF_leadjet_pt;          myTree->SetBranchAddress("{}.yyHF_leadjet_pt",             &{}_yyHF_leadjet_pt);'.format(variation, variation, variation)
		print 'float {}_yyHF_leadjet_phi;         myTree->SetBranchAddress("{}.yyHF_leadjet_phi",            &{}_yyHF_leadjet_phi);'.format(variation, variation, variation)
		print 'float {}_yyHF_leadjet_m;           myTree->SetBranchAddress("{}.yyHF_leadjet_m",              &{}_yyHF_leadjet_m);'.format(variation, variation, variation)
		print 'float {}_yyHF_leadjet_eta;         myTree->SetBranchAddress("{}.yyHF_leadjet_eta",            &{}_yyHF_leadjet_eta);'.format(variation, variation, variation)

	print
	print 
	print
	print 


	nbins = 27
	binmin = -0.5
	binmax=26.5

	for variation in myVariations:
		print 'TH1F *histbb_noMET_{} = new TH1F("histbb_noMET_{}", "histbb_noMET_{}", {}, {}, {});'.format(variation, variation, variation, nbins, binmin, binmax)
		print 'TH1F *histbc_noMET_{} = new TH1F("histbc_noMET_{}", "histbc_noMET_{}", {}, {}, {});'.format(variation, variation, variation, nbins, binmin, binmax)
		print 'TH1F *histbl_noMET_{} = new TH1F("histbl_noMET_{}", "histbl_noMET_{}", {}, {}, {});'.format(variation, variation, variation, nbins, binmin, binmax)
		print 'TH1F *histcc_noMET_{} = new TH1F("histcc_noMET_{}", "histcc_noMET_{}", {}, {}, {});'.format(variation, variation, variation, nbins, binmin, binmax)
		print 'TH1F *histcl_noMET_{} = new TH1F("histcl_noMET_{}", "histcl_noMET_{}", {}, {}, {});'.format(variation, variation, variation, nbins, binmin, binmax)
		print 'TH1F *histll_noMET_{} = new TH1F("histll_noMET_{}", "histll_noMET_{}", {}, {}, {});'.format(variation, variation, variation, nbins, binmin, binmax)
		print 'TH1F *histb_noMET_{} = new TH1F("histb_noMET_{}", "histb_noMET_{}", 5, -0.5, 4.5);'.format(variation, variation, variation)
		print 'TH1F *histc_noMET_{} = new TH1F("histc_noMET_{}", "histc_noMET_{}", 5, -0.5, 4.5);'.format(variation, variation, variation)
		print 'TH1F *histl_noMET_{} = new TH1F("histl_noMET_{}", "histl_noMET_{}", 5, -0.5, 4.5);'.format(variation, variation, variation)

	print
	print 
	print
	print 

	for variation in myVariations:
		print 'output_file->Add(histbb_noMET_{});'.format(variation)
		print 'output_file->Add(histbc_noMET_{});'.format(variation)
		print 'output_file->Add(histbl_noMET_{});'.format(variation)
		print 'output_file->Add(histcc_noMET_{});'.format(variation)
		print 'output_file->Add(histcl_noMET_{});'.format(variation)
		print 'output_file->Add(histll_noMET_{});'.format(variation)
		print 'output_file->Add(histb_noMET_{});'.format(variation)
		print 'output_file->Add(histc_noMET_{});'.format(variation)
		print 'output_file->Add(histl_noMET_{});'.format(variation)

	print
	print 
	print
	print 

	for variation in myVariations:
		print 'checkDijet(histbb_noMET_{}, histbc_noMET_{}, histbl_noMET_{}, histcc_noMET_{}, histcl_noMET_{}, histll_noMET_{}, '.format(variation, variation, variation, variation, variation, variation)
		print '		   {}_HGamWeight, XSWeight, lumi_mc16, sumweights, {}_isPassed, {}_yyHF_leadjet_truthlabel, '.format(variation, variation, variation)
		print '		   {}_yyHF_subleadjet_truthlabel, {}_yyHF_leadjet_btagbin, {}_yyHF_subleadjet_btagbin, {}_yyHF_Njet_central, {}_yyHFjj_weight, {}_yyHF_met, '.format(variation, variation, variation, variation, variation, variation)
		print '		   {}_yyHF_nelectron, {}_yyHF_nmuon, {}_m_yy);'.format(variation, variation, variation)

		# print ' checkSingleJet(histb_noMET_{}, histc_noMET_{}, histl_noMET_{}, '.format(variation, variation, variation)
		# print ' 		   {}_HGamWeight, XSWeight, lumi_mc16, sumweights, {}_isPassed, {}_yyHF_leadjet_truthlabel, '.format(variation, variation, variation, variation)
		# print ' 		   {}_yyHF_leadjet_btagbin, {}_yyHF_Njet_central, {}_yyHFj_weight, {}_yyHF_met, '.format(variation, variation, variation, variation)
		# print ' 		   {}_yyHF_nelectron, {}_yyHF_nmuon, {}_m_yy);'.format(variation, variation, variation)

	print
	print 
	print
	print 

	for variation in myVariations:
		# print 'checkDijet(histbb_noMET_{}, histbc_noMET_{}, histbl_noMET_{}, histcc_noMET_{}, histcl_noMET_{}, histll_noMET_{}, '.format(variation, variation, variation, variation, variation, variation)
		# print '		   {}_HGamWeight, XSWeight, lumi_mc16, sumweights, {}_isPassed, {}_yyHF_leadjet_truthlabel, '.format(variation, variation, variation)
		# print '		   {}_yyHF_subleadjet_truthlabel, {}_yyHF_leadjet_btagbin, {}_yyHF_subleadjet_btagbin, {}_yyHF_Njet_central, {}_yyHFjj_weight, {}_yyHF_met, '.format(variation, variation, variation, variation, variation, variation)
		# print '		   {}_yyHF_nelectron, {}_yyHF_nmuon, {}_m_yy);'.format(variation, variation, variation)

		print ' checkSingleJet(histb_noMET_{}, histc_noMET_{}, histl_noMET_{}, '.format(variation, variation, variation)
		print ' 		   {}_HGamWeight, XSWeight, lumi_mc16, sumweights, {}_isPassed, {}_yyHF_leadjet_truthlabel, '.format(variation, variation, variation, variation)
		print ' 		   {}_yyHF_leadjet_btagbin, {}_yyHF_Njet_central, {}_yyHFj_weight, {}_yyHF_met, '.format(variation, variation, variation, variation)
		print ' 		   {}_yyHF_nelectron, {}_yyHF_nmuon, {}_m_yy);'.format(variation, variation, variation)


# histbb_noMET = MakeHists("histbb_noMET","histbb_noMET",nbins,binmin,binmax)
# histbc_noMET = MakeHists("histbc_noMET","histbc_noMET",nbins,binmin,binmax)
# histbl_noMET = MakeHists("histbl_noMET","histbl_noMET",nbins,binmin,binmax)
# histcc_noMET = MakeHists("histcc_noMET","histcc_noMET",nbins,binmin,binmax)
# histcl_noMET = MakeHists("histcl_noMET","histcl_noMET",nbins,binmin,binmax)
# histll_noMET = MakeHists("histll_noMET","histll_noMET",nbins,binmin,binmax)

# histb_noMET = MakeHists("histb_noMET","histb_noMET",5,-0.5,4.5)
# histc_noMET = MakeHists("histc_noMET","histc_noMET",5,-0.5,4.5)
# histl_noMET = MakeHists("histl_noMET","histl_noMET",5,-0.5,4.5)


# hists[variation] = ROOT.TH1F(name+"_"+variation,title+"_"+variation,nbin,low,high)

# TH1F	histll;1	histll
# TH1F	histll_FT_EFF_Eigen_Light_0__1up;1	histll_FT_EFF_Eigen_Light_0__1up
# TH1F	histll_FT_EFF_Eigen_Light_1__1up;1	histll_FT_EFF_Eigen_Light_1__1up
# TH1F	histll_FT_EFF_Eigen_Light_2__1up;1	histll_FT_EFF_Eigen_Light_2__1up
# TH1F	histll_FT_EFF_Eigen_Light_3__1up;1	histll_FT_EFF_Eigen_Light_3__1up
# TH1F	histll_FT_EFF_Eigen_Light_4__1up;1	histll_FT_EFF_Eigen_Light_4__1up