batchDir=/bdata/bstamas/batch/results
outputDir=/home/bstamas/xdata/yyhf/makeDataHists


for sample in lp2 lp3 lp5
do
    # for file in `ls -1 ${batchDir}/yyHF_makedecompInputs_${sample}*/yyHF_decompInputDir_${sample}*/hist-*.root`
    # do
 
        # echo $file
        # # mv -v $file ${sample}/

    # done
    # echo hadd ${batchDir}/${sample}.decompCombinedResults.root ${batchDir}/yyHF_makedecompInputs_${sample}*/yyHF_decompInputDir_${sample}*/hist-*.root
    # hadd ${outputDir}/combinedData_${sample}.root ${batchDir}/makeDataHists_data1*/data_${sample}.root
    hadd ${outputDir}/combinedData_${sample}_singlejet.root ${batchDir}/makeDataHists_singlejet_*/data_${sample}_singlejet.root

done



