batchDir=/xdata/bstamas/batch/results
outputDir=/home/bstamas/xdata/yyhf/makeSubtractionHists


for  sample in Sherpa2_diphoton_myy_90_175_AF2 Sherpa2_diphoton_myy_175_2000_AF2 Sherpa2_diphoton_myy_2000_ECMS_AF2
do
    for mcType in mc16a mc16d mc16e
    do
        hadd ${outputDir}/${mcType}.${sample}.subtractionResults.root ${batchDir}/makeDecompSubtractHist_${sample}_${mcType}*/makeDecompSubtractHist_${sample}_${mcType}*.root
    done
    hadd master.${sample}.subtractionResults.root mc16a.${sample}.subtractionResults.root mc16d.${sample}.subtractionResults.root mc16e.${sample}.subtractionResults.root
done


hadd master.Sherpa2_diphoton_myy_ALL_AF2.subtractionResults.root master.Sherpa2_diphoton_myy_90_175_AF2.subtractionResults.root master.Sherpa2_diphoton_myy_175_2000_AF2.subtractionResults.root master.Sherpa2_diphoton_myy_2000_ECMS_AF2.subtractionResults.root