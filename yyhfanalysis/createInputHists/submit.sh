
#!/bin/bash


dirWithSamples=/xdata/bstamas/yyhf/inputHistMaker/newInputs

## for OR ##
# dirWithSamples=/xdata/bstamas/yyhf/inputHistMaker/ORInputs/2photons/
# dirWithSamples=/xdata/bstamas/yyhf/inputHistMaker/ORInputs/1photon/
# dirWithSamples=/xdata/bstamas/yyhf/inputHistMaker/manual_Sherpa2_diphoton_myy_90_175_AF2_PhotonAllSys_inputs

listOfMCCampaigns=(
	mc16a
	# mc16d
	# mc16e
	)

listOfSystematics=(
	Nominal
	# PhotonAllSys1
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
	# # Sh_2210_yybb_0Myy90
	Sh_2210_yybb_90Myy175
	Sh_2210_yybb_175MyyECM

	# # Sherpa2_diphoton_myy_1400_2000_AF2 


	# Sherpa2_diphoton_myy_2000_ECMS_AF2 
	# Sherpa2_diphoton_myy_175_2000_AF2 

	# # Sherpa2_diphoton_myy_90_175_AF2


	# Sh_2211_Zbbyy_myy95
	# Sh_2211_Zqqyy_myy95

	# MGPy8_ttgammagamma_allhad_AF2
	# MGPy8_ttgammagamma_noallhad_AF2

	# aMCPy8_2a_2j_FxFx

	# Pythia8_2DP20_Mass_0_55
	# Pythia8_2DP20_Mass_55_100
	# Pythia8_2DP20_Mass_100_160
	# Pythia8_2DP20_Mass_160_250
	# Pythia8_2DP20_Mass_250_400
	# Pythia8_2DP20_Mass_400_650
	# Pythia8_2DP20_Mass_650_1000
	# Pythia8_2DP20_Mass_1000_1500

	# MGPy8_ttgamma_nonallhadronic #Use ORInputs
	# MGPy8_ttgamma_nonallhadronic_AF2 #Use ORInputs
	# Sherpa_tt_dilepton #Use ORInputs

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
    )

for sys in "${listOfSystematics[@]}"
do
	for sample in "${listOfSamples[@]}"
	do
		for mcType in "${listOfMCCampaigns[@]}"
		do
		    counter=0
		    for file in `ls -1 ${dirWithSamples}/${sample}/${sys}/${mcType}/*root`
		    do
		    	# echo $file
		    	# ./submit_job.sh yyHF_inputHistMaker_wOR_${sample}_${sys}_${mcType}_${counter} $PWD any $file yyHF_inputHistMaker_wOR_${sample}_${sys}_${mcType}_${counter} $sample $mcType $sys 
				./submit_job.sh yyHF_inputHistMaker_${sample}_${sys}_${mcType}_${counter} $PWD any $file yyHF_inputHistMaker_${sample}_${sys}_${mcType}_${counter} $sample $mcType $sys 
		        counter=$((counter + 1))
		    done
		done
	done
done


##  LOCAL RUN ##
# for sys in "${listOfSystematics[@]}"
# do
# 	for sample in "${listOfSamples[@]}"
# 	do
# 		for mcType in "${listOfMCCampaigns[@]}"
# 		do
# 		    counter=0
# 		    for file in `ls -1 ${dirWithSamples}/${sample}/${sys}/${mcType}/*root`
# 		    do
# 		    	# echo $file
# 				# echo ./submit_job.sh yyHF_inputHistMaker_${sample}_${sys}_${mcType}_${counter} $PWD any $file yyHF_inputHistMaker_${sample}_${sys}_${mcType}_${counter} $sample $mcType $sys 
# 				python makeAllHists.py $file yyHF_inputHistMaker_${sample}_${sys}_${mcType}_${counter} $sample $mcType $sys
# 		        counter=$((counter + 1))
# 		    done
# 		done
# 	done
# done


# rm .envBefore_asetup.sh-*

# python makeAllHists.py /xdata/bstamas/yyhf/inputHistMaker//Sh_2210_yybb_90Myy175/Nominal/mc16a/user.bstamas.29248462._000001.MxAOD.root yyHF_inputHistMaker_Sh_2210_yybb_90Myy175_Nominal_mc16a_0 Sh_2210_yybb_90Myy175 mc16a Nominal
# python makeAllHists.py /xdata/bstamas/yyhf/inputHistMaker//Sh_2210_yybb_90Myy175/Nominal/mc16a/user.bstamas.29248462._000002.MxAOD.root yyHF_inputHistMaker_Sh_2210_yybb_90Myy175_Nominal_mc16a_1 Sh_2210_yybb_90Myy175 mc16a Nominal
# python makeAllHists.py /xdata/bstamas/yyhf/inputHistMaker//Sh_2210_yybb_90Myy175/Nominal/mc16a/user.bstamas.29248462._000003.MxAOD.root yyHF_inputHistMaker_Sh_2210_yybb_90Myy175_Nominal_mc16a_2 Sh_2210_yybb_90Myy175 mc16a Nominal
# python makeAllHists.py /xdata/bstamas/yyhf/inputHistMaker//Sh_2210_yybb_90Myy175/Nominal/mc16a/user.bstamas.29248462._000004.MxAOD.root yyHF_inputHistMaker_Sh_2210_yybb_90Myy175_Nominal_mc16a_3 Sh_2210_yybb_90Myy175 mc16a Nominal
# python makeAllHists.py /xdata/bstamas/yyhf/inputHistMaker//Sh_2210_yybb_90Myy175/Nominal/mc16a/user.bstamas.29248462._000005.MxAOD.root yyHF_inputHistMaker_Sh_2210_yybb_90Myy175_Nominal_mc16a_4 Sh_2210_yybb_90Myy175 mc16a Nominal
# python makeAllHists.py /xdata/bstamas/yyhf/inputHistMaker//Sh_2210_yybb_175MyyECM/Nominal/mc16a/user.bstamas.29248472._000001.MxAOD.root yyHF_inputHistMaker_Sh_2210_yybb_175MyyECM_Nominal_mc16a_0 Sh_2210_yybb_175MyyECM mc16a Nominal
