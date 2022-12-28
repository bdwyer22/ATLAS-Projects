
#!/bin/bash


###############################################

# HGamCore tag: v1.10.18-h026
# AnalysisBase: 21.2.162

###############################################

ptag=h026
extra=_test5_v2 #only increment if the job is in a broken state


MCtype=(
    mc16a
    # mc16d
    # mc16e
)

listOfConfigs=(
	Nominal
	PhotonAllSys1
	# PhotonAllSys2
	# PhotonAllSys3
	# PhotonAllSys4
	# FlavorAllSys1
	# FlavorAllSys2
	# FlavorAllSys3
	# FlavorAllSys4
	# JetSys1
	# JetSys2
	# JetSys3
	# JetSys4
	)

listOfSamples=(
	# Pythia8_2DP20_Mass_0_55
	# Pythia8_2DP20_Mass_55_100
	# Pythia8_2DP20_Mass_100_160
	# Pythia8_2DP20_Mass_160_250
	# Pythia8_2DP20_Mass_250_400
	# Pythia8_2DP20_Mass_400_650
	# Pythia8_2DP20_Mass_650_1000
	# Pythia8_2DP20_Mass_1000_1500

	# Pythia8_2DP20_Mass_1500_2000
	# Pythia8_2DP20_Mass_2000_2500
	# Pythia8_2DP20_Mass_2500_3000
	# Pythia8_2DP20_Mass_3000_3500
	# Pythia8_2DP20_Mass_3500_4000
	# Pythia8_2DP20_Mass_4000_4500
	# Pythia8_2DP20_Mass_4500_5000 
	# Pythia8_2DP20_Mass_5000_inf

	# Sherpa2_diphoton_myy_90_175_AF2
	# Sherpa2_diphoton_myy_175_2000_AF2 
	# Sherpa2_diphoton_myy_1400_2000_AF2 
	# Sherpa2_diphoton_myy_2000_ECMS_AF2 

	# MGPy8_ttgamma_nonallhadronic
	# MGPy8_ttgamma_nonallhadronic_AF2
	# MGPy8_ttgammagamma_noallhad_AF2
	# MGPy8_ttgammagamma_allhad_AF2
	# Sherpa_tt_dilepton

	aMCPy8_2a_2j_FxFx
	# Sh_2211_Zqqyy_myy95
	# Sh_2211_Zbbyy_myy95
	# PowhegPy8_HHbbyy_cHHH01d0
	# PowhegPy8_NNLOPS_ggH125
	# PowhegPy8EG_NNPDF30_VBFH125
	# PowhegPy8_WmH125J
	# PowhegPy8_WpH125J
	# PowhegPy8_ZH125J
	# PowhegPy8_ggZH125
	# PowhegPy8_ttH125_fixweight
	# aMCnloPy8_tWH125
	# aMCnloPy8_tHjb125_4fl_shw_fix
	# PowhegPy8_bbH125
	# Sh_2210_yybb_0Myy90 
	# Sh_2210_yybb_90Myy175
	# Sh_2210_yybb_175MyyECM
    )

for config in "${listOfConfigs[@]}"
do
	for mctype in "${MCtype[@]}"
	do
	    for sample in "${listOfSamples[@]}"
	    do
	    	if [ $config = "Nominal" ]
				then submitMxAOD.sh $sample ${ptag}${extra} MxAOD.config ${mctype}_HIGG1D1.txt
			else
	        submitMxAOD.sh $sample ${ptag}${extra} MxAOD${config}.config ${mctype}_HIGG1D1.txt
	    	fi
	    done
	done
done


# for mctype in "${MCtype[@]}"
# do
#     for sample in "${listOfSamples[@]}"
#     do
#         submitMxAOD.sh $sample ${ptag}${extra} MxAOD.config ${mctype}_HIGG1D1.txt
#     done
# done

# submitMxAOD.sh period2015 ${ptag}${extra} MxAOD.config data_13TeV_HIGG1D1.txt

# submitMxAOD.sh period2016 ${ptag}${extra} MxAOD.config data_13TeV_HIGG1D1.txt

# submitMxAOD.sh period2017 ${ptag}${extra} MxAOD.config data_13TeV_HIGG1D1.txt

# submitMxAOD.sh period2018 ${ptag}${extra} MxAOD.config data_13TeV_HIGG1D1.txt


