batchDir=/xdata/bstamas/batch/results

outputDir=/home/bstamas/xdata/yyhf/skimMxAODs/run/batchOutputs/

listofsampleTypes=(
    Sherpa2_diphoton_myy_90_175_AF2
    )
for mainSys in Jet FlavorAll PhotonAll
do
    for sys in 1 2 3 4 
    do
        for sample in mc16a mc16d mc16e 
        do
            for file in `ls -1 ${batchDir}/yyHF_skimMxAODs_Sherpa2_diphoton_myy_90_175_AF2_${sample}_${mainSys}Sys${sys}_*/*.root`
            do
                mv $file ~/xdata/yyhf/skimMxAODs/run/batchOutputs
            done
            # hadd ${outputDir}/${sample}.Sherpa2_diphoton_myy_90_175_AF2.${mainSys}Sys${sys}.skimmedMxAOD.root ${batchDir}/yyHF_skimMxAODs_Sherpa2_diphoton_myy_90_175_AF2_${sample}_${mainSys}Sys${sys}_*/*.root
        done
    # hadd ${outputDir}/master.Sherpa2_diphoton_myy_90_175_AF2.${mainSys}Sys${sys}_skimmed.root ${outputDir}/mc16a.Sherpa2_diphoton_myy_90_175_AF2.${mainSys}Sys${sys}_skimmed.root ${outputDir}/mc16d.Sherpa2_diphoton_myy_90_175_AF2.${mainSys}Sys${sys}_skimmed.root ${outputDir}/mc16e.Sherpa2_diphoton_myy_90_175_AF2.${mainSys}Sys${sys}_skimmed.root
    done
done

# # 
