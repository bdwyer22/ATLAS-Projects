batchDir=/xdata/bstamas/batch/results
# ^^ for new only, else reset below for old ^^ ##

outputDir=/home/bstamas/xdata/yyhf/inputHistMaker/outputs

listofSysTypes=(
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

listofsampleTypes=(
    # Sh_2210_yybb_0Myy90
    # Sh_2210_yybb_90Myy175 #only mc16a
    # Sh_2210_yybb_175MyyECM #only mc16a

    # # # Sherpa2_diphoton_myy_1400_2000_AF2 
    Sherpa2_diphoton_myy_175_2000_AF2 
    Sherpa2_diphoton_myy_2000_ECMS_AF2 
    Sherpa2_diphoton_myy_90_175_AF2

    Sh_2211_Zbbyy_myy95
    Sh_2211_Zqqyy_myy95

    MGPy8_ttgammagamma_allhad_AF2
    MGPy8_ttgammagamma_noallhad_AF2

    aMCPy8_2a_2j_FxFx

    # Pythia8_2DP20_Mass_0_55
    # Pythia8_2DP20_Mass_55_100
    # Pythia8_2DP20_Mass_100_160
    # Pythia8_2DP20_Mass_160_250
    # Pythia8_2DP20_Mass_250_400
    # Pythia8_2DP20_Mass_400_650
    # Pythia8_2DP20_Mass_650_1000
    # Pythia8_2DP20_Mass_1000_1500

    MGPy8_ttgamma_nonallhadronic
    MGPy8_ttgamma_nonallhadronic_AF2
    Sherpa_tt_dilepton

    PowhegPy8_HHbbyy_cHHH01d0
    PowhegPy8_NNLOPS_ggH125
    PowhegPy8EG_NNPDF30_VBFH125
    PowhegPy8_WmH125J
    PowhegPy8_WpH125J
    PowhegPy8_ZH125J
    PowhegPy8_ggZH125
    PowhegPy8_ttH125_fixweight
    aMCnloPy8_tWH125
    aMCnloPy8_tHjb125_4fl_shw_fix
    PowhegPy8_bbH125
    )

# ## main ##
# # batchDir=/xdata/bstamas/batch/inputHistMakerResults
# for sysType in "${listofSysTypes[@]}"
# do
#     for sampleType in "${listofsampleTypes[@]}"
#     do
#         for sample in mc16a mc16d mc16e
#         do
#             hadd ${outputDir}/${sample}.${sampleType}.${sysType}_combinedCR.root ${batchDir}/yyHF_inputHistMaker_${sampleType}_${sysType}_${sample}*/yyHF_inputHistMaker_${sampleType}_${sysType}_${sample}*.root
#         done
#         hadd ${outputDir}/master.${sampleType}.${sysType}_combinedCR.root ${outputDir}/mc16a.${sampleType}.${sysType}_combinedCR.root ${outputDir}/mc16d.${sampleType}.${sysType}_combinedCR.root ${outputDir}/mc16e.${sampleType}.${sysType}_combinedCR.root
#     done
#     # optional:
#     hadd ${outputDir}/master.MGPy8_ttgammagamma_AF2.${sysType}_combinedCR.root ${outputDir}/master.MGPy8_ttgammagamma_allhad_AF2.${sysType}_combinedCR.root ${outputDir}/master.MGPy8_ttgammagamma_noallhad_AF2.${sysType}_combinedCR.root
#     hadd ${outputDir}/master.Sherpa2_diphoton_myy_ALL_AF2.${sysType}_combinedCR.root ${outputDir}/master.Sherpa2_diphoton_myy_90_175_AF2.${sysType}_combinedCR.root ${outputDir}/master.Sherpa2_diphoton_myy_175_2000_AF2.${sysType}_combinedCR.root ${outputDir}/master.Sherpa2_diphoton_myy_2000_ECMS_AF2.${sysType}_combinedCR.root
#     hadd ${outputDir}/master.Sh_2211_Zyy_myy95.${sysType}_combinedCR.root ${outputDir}/master.Sh_2211_Zbbyy_myy95.${sysType}_combinedCR.root ${outputDir}/master.Sh_2211_Zqqyy_myy95.${sysType}_combinedCR.root
#     # # # hadd ${outputDir}/master.Pythia8_2DP20_ALL.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_0_55.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_55_100.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_100_160.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_160_250.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_250_400.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_400_650.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_650_1000.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_1000_1500.${sysType}_combinedCR.root
#     hadd ${outputDir}/master.H_yy.${sysType}_combinedCR.root ${outputDir}/master.PowhegPy8_HHbbyy_cHHH01d0.${sysType}_combinedCR.root ${outputDir}/master.PowhegPy8_NNLOPS_ggH125.${sysType}_combinedCR.root ${outputDir}/master.PowhegPy8EG_NNPDF30_VBFH125.${sysType}_combinedCR.root ${outputDir}/master.PowhegPy8_WmH125J.${sysType}_combinedCR.root ${outputDir}/master.PowhegPy8_WpH125J.${sysType}_combinedCR.root ${outputDir}/master.PowhegPy8_ZH125J.${sysType}_combinedCR.root ${outputDir}/master.PowhegPy8_ggZH125.${sysType}_combinedCR.root ${outputDir}/master.PowhegPy8_ttH125_fixweight.${sysType}_combinedCR.root ${outputDir}/master.aMCnloPy8_tWH125.${sysType}_combinedCR.root ${outputDir}/master.aMCnloPy8_tHjb125_4fl_shw_fix.${sysType}_combinedCR.root ${outputDir}/master.PowhegPy8_bbH125.${sysType}_combinedCR.root
#     hadd ${outputDir}/master.Sh_2210_yybb_ALL.${sysType}_combinedCR.root ${outputDir}/master.Sh_2210_yybb_90Myy175.${sysType}_combinedCR.root  ${outputDir}/master.Sh_2210_yybb_175MyyECM.${sysType}_combinedCR.root
# done

# ## For kinematics ##
# outputDir=/home/bstamas/xdata/yyhf/inputHistMaker/kinematicORoutputs
# for sysType in "${listofSysTypes[@]}"
# do
#     for sampleType in "${listofsampleTypes[@]}"
#     do
#         for sample in mc16a mc16d mc16e
#         do
#             hadd ${outputDir}/${sample}.${sampleType}.${sysType}_kinematicORchecks.root ${batchDir}/yyHF_checkORkinematics_${sampleType}_Nominal_${sample}*/yyHF_checkORkinematics_${sampleType}_Nominal_${sample}*.root
#         done
#         # hadd ${outputDir}/master.${sampleType}.${sysType}_kinematicORchecks.root ${outputDir}/mc16a.${sampleType}.${sysType}_kinematicORchecks.root ${outputDir}/mc16d.${sampleType}.${sysType}_kinematicORchecks.root ${outputDir}/mc16e.${sampleType}.${sysType}_kinematicORchecks.root
#     done
#     # # optional:
#     # hadd ${outputDir}/mc16a.Sherpa2_diphoton_myy_ALL_AF2.${sysType}_kinematicORchecks.root ${outputDir}/mc16a.Sherpa2_diphoton_myy_90_175_AF2.${sysType}_kinematicORchecks.root ${outputDir}/mc16a.Sherpa2_diphoton_myy_175_2000_AF2.${sysType}_kinematicORchecks.root ${outputDir}/mc16a.Sherpa2_diphoton_myy_2000_ECMS_AF2.${sysType}_kinematicORchecks.root
#     # hadd ${outputDir}/mc16a.Sh_2210_yybb_ALL.${sysType}_kinematicORchecks.root ${outputDir}/mc16a.Sh_2210_yybb_90Myy175.${sysType}_kinematicORchecks.root ${outputDir}/mc16a.Sh_2210_yybb_175MyyECM.${sysType}_kinematicORchecks.root
# done



# ## for OR ##
# for sysType in "${listofSysTypes[@]}"
# do
#     for sampleType in "${listofsampleTypes[@]}"
#     do
#         for sample in mc16a mc16d mc16e
#         do
#             hadd ${outputDir}/${sample}.${sampleType}.${sysType}_combinedCR_wOR.root ${batchDir}/yyHF_inputHistMaker_wOR_${sampleType}_${sysType}_${sample}*/yyHF_inputHistMaker_wOR_${sampleType}_${sysType}_${sample}*.root

#         done
#         hadd ${outputDir}/master.${sampleType}.${sysType}_combinedCR_wOR.root ${outputDir}/mc16a.${sampleType}.${sysType}_combinedCR_wOR.root ${outputDir}/mc16d.${sampleType}.${sysType}_combinedCR_wOR.root ${outputDir}/mc16e.${sampleType}.${sysType}_combinedCR_wOR.root
#     done
# done



# ## for fastHists ##
# batchDir=/home/bstamas/xdata/yyhf/inputHistMaker/fastHistsOut/
# for sysType in "${listofSysTypes[@]}"
# do
#     for sampleType in "${listofsampleTypes[@]}"
#     do
#         for sample in mc16a mc16d mc16e
#         do
#             # yyHF_fastHists_Sherpa2_diphoton_myy_90_175_AF2_FlavorAllSys1_mc16a_0.root
#             hadd ${outputDir}/${sample}.${sampleType}.${sysType}_combinedCR.root ${batchDir}/yyHF_fastHists_${sampleType}_${sysType}_${sample}*.root
#         done
#         hadd ${outputDir}/master.${sampleType}.${sysType}_combinedCR.root ${outputDir}/mc16a.${sampleType}.${sysType}_combinedCR.root ${outputDir}/mc16d.${sampleType}.${sysType}_combinedCR.root ${outputDir}/mc16e.${sampleType}.${sysType}_combinedCR.root
#     done
#     # # optional:
#     # hadd ${outputDir}/master.MGPy8_ttgammagamma_AF2.${sysType}_combinedCR.root ${outputDir}/master.MGPy8_ttgammagamma_allhad_AF2.${sysType}_combinedCR.root ${outputDir}/master.MGPy8_ttgammagamma_noallhad_AF2.${sysType}_combinedCR.root
#     # hadd ${outputDir}/master.Pythia8_2DP20_ALL.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_0_55.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_55_100.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_100_160.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_160_250.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_250_400.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_400_650.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_650_1000.${sysType}_combinedCR.root ${outputDir}/master.Pythia8_2DP20_Mass_1000_1500.${sysType}_combinedCR.root
#     # hadd ${outputDir}/master.Sherpa2_diphoton_myy_ALL_AF2.${sysType}_combinedCR.root ${outputDir}/master.Sherpa2_diphoton_myy_90_175_AF2.${sysType}_combinedCR.root ${outputDir}/master.Sherpa2_diphoton_myy_175_2000_AF2.${sysType}_combinedCR.root ${outputDir}/master.Sherpa2_diphoton_myy_2000_ECMS_AF2.${sysType}_combinedCR.root
# done
