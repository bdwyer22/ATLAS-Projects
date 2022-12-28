# singleJet = True 
singleJet = False


jobName = "yyhf_v5.9"
inputPath = "/home/bstamas/xdata/yyhf/TRExFitter/inputs/currentInputs/noMET"


if singleJet == False:
  Label="DL1*2"
  VariableTitle="(DL1 bin leading)*5 + DL1 bin subleading. Bin25 = Lep"
  NormFactors = ["bb", "bc", "bl", "cc", "cl", "ll"]
  myColorDict = {
  "bb":"255,46,153",
  "bc":"255,102,102",
  "bl":"204,32,153",
  "cc":"153,102,255",
  "cl":"154,51,204",
  "ll":"102,252,255"}
  # allSignalNorms = "yy_bb, yy_bc, yy_bl, yy_cc, yy_cl, yy_ll, ttyy_bb, ttyy_bc, ttyy_bl, ttyy_cc, ttyy_cl, ttyy_ll, zyy_bb, zyy_bc, zyy_bl, zyy_cc, zyy_cl, zyy_ll"
  allSignalNorms = "yy_bb, yy_bc, yy_bl, yy_cc, yy_cl, yy_llttyy_bb, ttyy_bc, ttyy_bl, ttyy_cc, ttyy_cl, ttyy_ll, zyy_bb, zyy_bc, zyy_bl, zyy_cc, zyy_cl, zyy_ll"# , hyy_bb, hyy_bc, hyy_bl, hyy_cc, hyy_cl, hyy_ll"



if singleJet == True:
  Label="DL1"
  VariableTitle="Leading jet DL1 bin"
  NormFactors = ["b", "c", "l"]
  myColorDict = {
  "b":"255,46,153",
  "c":"153,102,255",
  "l":"153,102,255"}
  allSignalNorms = "yy_b, yy_c, yy_l, ttyy_b, ttyy_c, ttyy_l, zyy_b, zyy_b, zyy_l"


# SignalSamples = ["yy", "ttyy", "zbbyy", "zqqyy",
#     "HHbbyy",
#     "ggH",
#     "VBFH",
#     "WmH",
#     "WpH",
#     "ZH",
#     "ggZH",
#     "ttH",
#     "tWH",
#     "tHjb",
#     "bbH"]

SignalSamples = ["yy", "ttyy", "zyy", "hyy"]
# SignalSamples = ["yy", "ttyy", "zyy"]

# for signal in SignalSamples:
#   for norm in NormFactors:
#     print signal+"_"+norm+",",

myInputs = {
"yy":"inputs_yy_",
"ttyy":"inputs_ttyy_",
"zyy":"inputs_zyy_",
"hyy":"inputs_hyy_"
}

# myPhotonVariations = ["EG_RESOLUTION_ALL", "EG_SCALE_AF2", "EG_SCALE_ALL", "PH_EFF_ID_Uncertainty", "PH_EFF_ISO_Uncertainty",
# 	"PH_EFF_TRIGGER_Uncertainty", "PRW_DATASF"]


# myFlavorVariations = ["FT_EFF_Eigen_B_0", "FT_EFF_Eigen_B_1", "FT_EFF_Eigen_B_2", "FT_EFF_Eigen_C_0", "FT_EFF_Eigen_C_1",
# 	"FT_EFF_Eigen_C_2", "FT_EFF_Eigen_C_3", "FT_EFF_Eigen_Light_0", "FT_EFF_Eigen_Light_1", "FT_EFF_Eigen_Light_2",  
# 	"FT_EFF_Eigen_Light_3", "FT_EFF_Eigen_Light_4", "FT_EFF_extrapolation", "FT_EFF_extrapolation_from_charm"]

# myJetVariations = ["JET_BJES_Response", "JET_EffectiveNP_Detector1", "JET_EffectiveNP_Detector2", 
# 	"JET_EffectiveNP_Mixed1", "JET_EffectiveNP_Mixed2", "JET_EffectiveNP_Mixed3", "JET_EffectiveNP_Modelling1", 
# 	"JET_EffectiveNP_Modelling2", "JET_EffectiveNP_Modelling3", "JET_EffectiveNP_Modelling4",
# 	"JET_EffectiveNP_Statistical1", "JET_EffectiveNP_Statistical2",	"JET_EffectiveNP_Statistical3", "JET_EffectiveNP_Statistical4",
# 	"JET_EffectiveNP_Statistical5", "JET_EffectiveNP_Statistical6",	"JET_EtaIntercalibration_Modelling", 
# 	"JET_EtaIntercalibration_NonClosure_2018data", "JET_EtaIntercalibration_NonClosure_highE", "JET_EtaIntercalibration_NonClosure_negEta", 
# 	"JET_EtaIntercalibration_NonClosure_posEta", "JET_EtaIntercalibration_TotalStat", "JET_fJvtEfficiency", "JET_Flavor_Composition", 
# 	"JET_Flavor_Response", "JET_JER_EffectiveNP_1", "JET_JER_EffectiveNP_10", "JET_JER_EffectiveNP_11", "JET_JER_EffectiveNP_12restTerm", 
# 	"JET_JER_EffectiveNP_2", "JET_JER_EffectiveNP_3", "JET_JER_EffectiveNP_4", "JET_JER_EffectiveNP_5", "JET_JER_EffectiveNP_6", 
# 	"JET_JER_EffectiveNP_7", "JET_JER_EffectiveNP_8", "JET_JER_EffectiveNP_9", "JET_JvtEfficiency", "JET_Pileup_OffsetMu", 
# 	"JET_Pileup_OffsetNPV", "JET_Pileup_PtTerm", "JET_Pileup_RhoTopology", "JET_SingleParticle_HighPt"]

myFlavorVariations = ["FT_EFF_Eigen_Light_0", "FT_EFF_Eigen_Light_1", "FT_EFF_Eigen_Light_2",  
      "FT_EFF_extrapolation_from_charm", "FT_EFF_Eigen_C_3", "FT_EFF_Eigen_C_2", "FT_EFF_Eigen_C_1", 
      "FT_EFF_Eigen_B_2", "FT_EFF_Eigen_Light_4", "FT_EFF_Eigen_Light_3",  
      "FT_EFF_extrapolation", "FT_EFF_Eigen_C_0", "FT_EFF_Eigen_B_1", "FT_EFF_Eigen_B_0"]


myPhotonVariations = ["EG_RESOLUTION_AF2", "EG_RESOLUTION_MATERIALCALO", "EG_RESOLUTION_MATERIALCRYO", 
      "EG_RESOLUTION_MATERIALGAP", "EG_RESOLUTION_MATERIALIBL", "EG_RESOLUTION_MATERIALID",
      "EG_RESOLUTION_MATERIALPP0", "EG_RESOLUTION_PILEUP", "EG_RESOLUTION_SAMPLINGTERM", 
      "EG_RESOLUTION_ZSMEARING", "EG_SCALE_PEDESTAL", "EG_SCALE_PS__ETABIN0", 
      "EG_SCALE_PS__ETABIN1", "EG_SCALE_PS__ETABIN2", "EG_SCALE_PS__ETABIN3", 
      "EG_SCALE_PS__ETABIN4", "EG_SCALE_PS__ETABIN5", "EG_SCALE_PS__ETABIN6", 
      "EG_SCALE_PS__ETABIN7", "EG_SCALE_PS__ETABIN8", 
      "EG_SCALE_PS_BARREL_B12", "EG_SCALE_AF2", "EG_SCALE_E4SCINTILLATOR__ETABIN0", 
      "EG_SCALE_E4SCINTILLATOR__ETABIN1", "EG_SCALE_E4SCINTILLATOR__ETABIN2", "EG_SCALE_G4",  
      "EG_SCALE_L1GAIN", "EG_SCALE_L2GAIN", "EG_SCALE_LARCALIB__ETABIN0", "EG_SCALE_LARCALIB__ETABIN1", 
      "EG_SCALE_LARELECCALIB", "EG_SCALE_LARELECUNCONV__ETABIN0", "EG_SCALE_LARELECUNCONV__ETABIN1", 
      "EG_SCALE_LARUNCONVCALIB__ETABIN0", "EG_SCALE_LARUNCONVCALIB__ETABIN1", "EG_SCALE_S12__ETABIN0", 
      "EG_SCALE_S12__ETABIN1", "EG_SCALE_S12__ETABIN2", "EG_SCALE_S12__ETABIN3", 
      "EG_SCALE_S12__ETABIN4", "EG_SCALE_TOPOCLUSTER_THRES", "EG_SCALE_WTOTS1",
      "EG_SCALE_MATCALO__ETABIN0", "EG_SCALE_MATCALO__ETABIN1", "EG_SCALE_MATCALO__ETABIN10", 
      "EG_SCALE_MATCALO__ETABIN11", "EG_SCALE_MATCALO__ETABIN2", "EG_SCALE_MATCALO__ETABIN3", 
      "EG_SCALE_MATCALO__ETABIN4", "EG_SCALE_MATCALO__ETABIN5", "EG_SCALE_MATCALO__ETABIN6", 
      "EG_SCALE_MATCALO__ETABIN7", "EG_SCALE_MATCALO__ETABIN8", "EG_SCALE_MATCALO__ETABIN9", 
      "EG_SCALE_MATID__ETABIN0", "EG_SCALE_MATID__ETABIN1", "EG_SCALE_MATID__ETABIN2", 
      "EG_SCALE_MATID__ETABIN3", "EG_SCALE_MATPP0__ETABIN0", "EG_SCALE_MATPP0__ETABIN1", 
      "EG_SCALE_ZEESTAT", "EG_SCALE_ZEESTAT", "EG_SCALE_ZEESYST", "EG_SCALE_ZEESYST",
      "EG_SCALE_MATCRYO__ETABIN0", "EG_SCALE_MATCRYO__ETABIN1", "EG_SCALE_MATCRYO__ETABIN10", 
      "EG_SCALE_MATCRYO__ETABIN11", "EG_SCALE_MATCRYO__ETABIN2","EG_SCALE_MATCRYO__ETABIN3", 
      "EG_SCALE_MATCRYO__ETABIN4", "EG_SCALE_MATCRYO__ETABIN5", "EG_SCALE_MATCRYO__ETABIN6",
      "EG_SCALE_MATCRYO__ETABIN7", "EG_SCALE_MATCRYO__ETABIN8", "EG_SCALE_MATCRYO__ETABIN9", 
      "PH_EFF_ID_Uncertainty", "PH_EFF_ISO_Uncertainty", "PH_EFF_TRIGGER_Uncertainty", 
      "PH_SCALE_CONVEFFICIENCY", "PH_SCALE_CONVFAKERATE", "PH_SCALE_CONVRADIUS", 
      "PH_SCALE_LEAKAGECONV", "PH_SCALE_LEAKAGEUNCONV"]


myJetVariations = ["JET_EffectiveNP_Detector1", "JET_EffectiveNP_Detector2", 
      "JET_EffectiveNP_Mixed1", "JET_EffectiveNP_Mixed2", 
      "JET_EffectiveNP_Mixed3", "JET_EffectiveNP_Modelling1", 
      "JET_EffectiveNP_Modelling2", "JET_EffectiveNP_Modelling3", 
      "JET_EffectiveNP_Modelling4", "JET_EffectiveNP_Statistical1", 
      "JET_EffectiveNP_Statistical2", "JET_EffectiveNP_Statistical3", 
      "JET_EffectiveNP_Statistical4", "JET_EffectiveNP_Statistical5", 
      "JET_EffectiveNP_Statistical6", "JET_BJES_Response", 
      "JET_EtaIntercalibration_Modelling", "JET_EtaIntercalibration_NonClosure_2018data", 
      "JET_EtaIntercalibration_NonClosure_highE", "JET_EtaIntercalibration_NonClosure_negEta", 
      "JET_EtaIntercalibration_NonClosure_posEta", "JET_EtaIntercalibration_TotalStat", 
      "JET_fJvtEfficiency", "JET_Flavor_Composition", "JET_Flavor_Response", 
      "JET_JvtEfficiency", "JET_Pileup_OffsetMu", "JET_Pileup_OffsetNPV", "JET_Pileup_PtTerm", 
      "JET_Pileup_RhoTopology", "JET_SingleParticle_HighPt", "JET_JER_EffectiveNP_1", 
      "JET_JER_EffectiveNP_10", "JET_JER_EffectiveNP_11", "JET_JER_EffectiveNP_12restTerm", 
      "JET_JER_EffectiveNP_2", "JET_JER_EffectiveNP_3", "JET_JER_EffectiveNP_4", 
      "JET_JER_EffectiveNP_5", "JET_JER_EffectiveNP_6", "JET_JER_EffectiveNP_7",
      "JET_JER_EffectiveNP_8", "JET_JER_EffectiveNP_9"]

    # if "JetSys4" in systematicType:
    #   myVariations = ["JET_JER_EffectiveNP_1", "JET_JER_EffectiveNP_1", 
    #   "JET_JER_EffectiveNP_10", "JET_JER_EffectiveNP_10", "JET_JER_EffectiveNP_11", "JET_JER_EffectiveNP_11", 
    #   "JET_JER_EffectiveNP_12restTerm", "JET_JER_EffectiveNP_12restTerm", "JET_JER_EffectiveNP_2", "JET_JER_EffectiveNP_2", 
    #   "JET_JER_EffectiveNP_3", "JET_JER_EffectiveNP_3", "JET_JER_EffectiveNP_4", "JET_JER_EffectiveNP_4", 
    #   "JET_JER_EffectiveNP_5", "JET_JER_EffectiveNP_5", "JET_JER_EffectiveNP_6", "JET_JER_EffectiveNP_6", 
    #   "JET_JER_EffectiveNP_7", "JET_JER_EffectiveNP_7", "JET_JER_EffectiveNP_8", "JET_JER_EffectiveNP_8", 
    #   "JET_JER_EffectiveNP_9", "JET_JER_EffectiveNP_9"]



print('Job: "{}" \n\
  Label: "{}" \n\
  CmeLabel: "13 TeV" \n\
  LumiLabel: "139 fb^{}" \n\
  ReadFrom: HIST \n\
  HistoPath: "{}" \n\
  DebugLevel: 2 \n\
  SystControlPlots: TRUE \n\
  ImageFormat: pdf \n\
  UseGammaPulls: TRUE \n\
  SuppressNegativeBinWarnings: TRUE \n\
  HistoChecks: NOCRASH \n\
  SystCategoryTables: TRUE \n\
  POI: "Mubb", "Mubc", "Mubl", "Mucc", "Mucl", "Mull"'.format(jobName, jobName, "{-1}", inputPath))

print('\nFit: "myFit" \n\
  FitType: SPLUSB\n\
  FitRegion: CRSR\n\
  POIAsimov: 1\n\
  UseMinos: all\n\
  FitBlind: TRUE')

print('\nRegion: "CR"\n\
  Type: CONTROL\n\
  LogScale: TRUE\n\
  HistoName: "hist_DL1"\n\
  Label: "{}"\n\
  VariableTitle: "{}"\n\
  ShortLabel: "hist_DL1"\n'.format(Label,VariableTitle)
)
for flavor in NormFactors:
	print('NormFactor: Mu{}\n\
    Samples: {}_{},{}_{},{}_{},{}_{}\n\
    Regions: "CR"\n\
    Nominal: 1.0\n\
    Min: 0\n\
    Max: 3\n'.format(flavor, SignalSamples[0], flavor, SignalSamples[1], flavor, SignalSamples[2], flavor, SignalSamples[3], flavor))

for flavor in NormFactors:
	for sig in SignalSamples:
		print ('Sample: "{}_{}"\n\
      Type: BACKGROUND\n\
      Title: "{}"\n\
      FillColorRGB: {}\n\
      LineColorRGB: {}\n\
      NormFactor: "Mu{}",1.0,0,3\n\
      HistoFile: "{}{}"\n'.format(sig, flavor, flavor, myColorDict[flavor], myColorDict[flavor], flavor, myInputs[sig], flavor))

if singleJet == False:
	for i in range(len(SignalSamples)):
		if i == 0:
			continue
		# print SignalSamples[i]
		print('Systematic: "{}_norm"\n\
      Title: "{} norm"\n\
      Type: OVERALL\n\
      OverallUp: 1.0\n\
      OverallDown: -1.0\n\
      Samples: {}_{}, {}_{}, {}_{}, {}_{}, {}_{}, {}_{}\n\
      Regions: CR\n'.format(SignalSamples[i], SignalSamples[i], SignalSamples[i], NormFactors[0], SignalSamples[i], NormFactors[1], SignalSamples[i], NormFactors[2], SignalSamples[i], NormFactors[3], SignalSamples[i], NormFactors[4], SignalSamples[i], NormFactors[5]))

if singleJet == True:
	for i in range(len(SignalSamples)):
		if i == 0:
			continue
		# print SignalSamples[i]
		print('Systematic: "{}_norm"\n\
      Title: "{} norm"\n\
      Type: OVERALL\n\
      OverallUp: 1.0\n\
      OverallDown: -1.0\n\
      Samples: {}_{}, {}_{}, {}_{}\n\
      Regions: CR\n'.format(SignalSamples[i], SignalSamples[i], SignalSamples[i], NormFactors[0], SignalSamples[i], NormFactors[1], SignalSamples[i], NormFactors[2]))

print('Sample: "tty"\n\
  Type: BACKGROUND\n\
  Title: "tty"\n\
  FillColorRGB: 102,1,255\n\
  LineColorRGB: 102,1,255\n\
  HistoFile: "inputs_tty"\n\
  \n\
Systematic: "ttynorm"\n\
  Title: "tty norm"\n\
  Type: OVERALL\n\
  OverallUp: 0.3\n\
  OverallDown: -0.3\n\
  Samples: tty\n\
  Regions: CR\n\
\n\
Sample: "tt"\n\
  Type: BACKGROUND\n\
  Title: "tt"\n\
  FillColorRGB: 0,153,255\n\
  LineColorRGB: 0,153,255\n\
  HistoFile: "inputs_tt"\n\
\n\
Systematic: "ttnorm"\n\
  Title: "tt norm"\n\
  Type: OVERALL\n\
  OverallUp: 0.5\n\
  OverallDown: -0.5\n\
  Samples: tt\n\
  Regions: CR\n\
\n\
Sample: "yj"\n  Type: BACKGROUND\n  Title: "yj"\n  FillColorRGB: 255,102,255\n  LineColorRGB: 255,102,255\n  HistoFile: "inputs_yj"\n\
\n\
Sample: "jj"\n  Type: BACKGROUND\n  Title: "jj"\n  FillColorRGB: 204,15,255\n  LineColorRGB: 204,15,255\n  HistoFile: "inputs_jj"\n\
\n\
Systematic: "yjnorm"\n  Title: "yj norm"\n  Type: HISTO\n  HistoFileUp: inputs_yj_systup\n  HistoFileDown: inputs_yj_systdown\n  Samples: yj\n  Regions: CR\n\
\n\
Systematic: "jjnorm"\n  Title: "jj norm"\n  Type: HISTO\n  HistoFileUp: inputs_jj_systup\n  HistoFileDown: inputs_jj_systdown\n  Samples: jj\n  Regions: CR\n\
\n\
Systematic: "yj_nofakesubtract"\n  Title: "yj_nofakesubtract"\n  Type: HISTO\n  Symmetrisation: ONESIDED\n  HistoFileUp: inputs_yj_nosub\n  Samples: yj\n  Regions: CR\n\
\n\
Systematic: "jj_nofakesubtract"\n  Title: "jj_nofakesubtract"\n  Type: HISTO\n  Symmetrisation: ONESIDED\n  HistoFileUp: inputs_jj_nosub\n  Samples: jj\n  Regions: CR\n\
\n\
Systematic: "yjlp2"\n  Title: "yjlp2"\n  Type: HISTO\n  Symmetrisation: ONESIDED\n  HistoFileUp: inputs_yj_lp2\n  Samples: yj\n  Regions: CR\n\
\n\
Systematic: "yjlp5"\n  Title: "yjlp5"\n  Type: HISTO\n  Symmetrisation: ONESIDED\n  HistoFileUp: inputs_yj_lp5\n  Samples: yj\n  Regions: CR\n\
\n\
Systematic: "jjlp2"\n  Title: "jjlp2"\n  Type: HISTO\n  Symmetrisation: ONESIDED\n  HistoFileUp: inputs_jj_lp2\n  Samples: jj\n  Regions: CR\n\
\n\
Systematic: "jjlp5"\n  Title: "jjlp5"\n  Type: HISTO\n  Symmetrisation: ONESIDED\n  HistoFileUp: inputs_jj_lp5\n  Samples: jj\n  Regions: CR\n')

# print'Systematic: "tt_noOR"\n  Title: "tt_noOR"\n  Type: HISTO\n  Symmetrisation: ONESIDED\n  HistoFileUp: inputs_tt_noOR\n  Samples: tt\n  Regions: CR\n'

# print'Systematic: "tty_noOR"\n  Title: "tty_noOR"\n  Type: HISTO\n  Symmetrisation: ONESIDED\n  HistoFileUp: inputs_tty_noOR\n  Samples: tty\n  Regions: CR\n'

# print'Systematic: "Sherpa_HF_Uncertainty"\n\
#   Title: "Sherpa_HF_Uncertainty"\n\
#   Type: HISTO\n\
#   HistoFileSufUp: _sherpa_HF_Uncertainty__1up\n\
#   HistoFileSufDown: _sherpa_HF_Uncertainty__1down\n\
#   Samples: yy_bb\n\
#   Regions: CR'

print("##########################################################################################\n\
################################### PHOTON SYSTEMATICS ###################################\n\
##########################################################################################\n\
")
if singleJet == False:
	for i in range(len(SignalSamples)):
		if i > 0:
			continue
		for myVar in myPhotonVariations:
			print('Systematic: "{}"\n\
        Title: "{}"\n\
        Type: HISTO\n\
        HistoFileSufUp: _{}__1up\n\
        HistoFileSufDown: _{}__1down\n\
        Samples: {}\n\
        Regions: CR\n\
        Category: "Photon"\n'.format(myVar, myVar, myVar, myVar, allSignalNorms))

if singleJet == True:
	for i in range(len(SignalSamples)):
		if i > 0:
			continue
		for myVar in myPhotonVariations:
			print('Systematic: "{}"\n\
        Title: "{}"\n\
        Type: HISTO\n\
        HistoFileSufUp: _{}__1up\n\
        HistoFileSufDown: _{}__1down\n\
        Samples: {}\n\
        Regions: CR\n\
        Category: "Photon"\n'.format(myVar, myVar, myVar, myVar, allSignalNorms))



print('##########################################################################################\n\
################################### FLAVOR SYSTEMATICS ###################################\n\
##########################################################################################\n\
'
)
if singleJet == False:

		for myVar in myFlavorVariations:
			print('Systematic: "{}"\n\
        Title: "{}"\n\
        Type: HISTO\n\
        HistoFileSufUp: _{}__1up\n\
        HistoFileSufDown: _{}__1down\n\
        Samples: {}\n\
        Regions: CR\n\
        Category: "Flavor"\n'.format(myVar, myVar, myVar, myVar, allSignalNorms))

if singleJet == True:
		for myVar in myFlavorVariations:
			print('Systematic: "{}"\n\
        Title: "{}"\n\
        Type: HISTO\n\
        HistoFileSufUp: _{}__1up\n\
        HistoFileSufDown: _{}__1down\n\
        Samples: {}\n\
        Regions: CR\n\
        Category: "Flavor"\n'.format(myVar, myVar, myVar, myVar, allSignalNorms))

print('# ##########################################################################################\n\
#################################### JET SYSTEMATICS ####################################\n\
##########################################################################################\n\
')

if singleJet == False:
	for i in range(len(SignalSamples)):
		# if i > 0:
		# 	continue
		for myVar in myJetVariations:
			print('Systematic: "{}"\n\
        Title: "{}"\n\
        Type: HISTO\n\
        HistoFileSufUp: _{}__1up\n\
        HistoFileSufDown: _{}__1down\n\
        Samples: {}\n\
        Regions: CR\n\
        Category: "Jet"\n'.format(myVar, myVar, myVar, myVar, allSignalNorms))

if singleJet == True:
	for i in range(len(SignalSamples)):
		if i > 0:
			continue
		for myVar in myJetVariations:
			print('Systematic: "{}"\n\
        Title: "{}"\n\
        Type: HISTO\n\
        HistoFileSufUp: _{}__1up\n\
        HistoFileSufDown: _{}__1down\n\
        Samples: {}\n\
        Regions: CR\n\
        Category: "Jet"\n'.format(myVar, myVar, myVar, myVar, allSignalNorms))
