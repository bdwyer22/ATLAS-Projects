
#!/bin/bash

myJetSysDir=/home/bstamas/xdata/yyhf/skimMxAODs/run/newDownloads/JetSys
myPhotonSysDir=/home/bstamas/xdata/yyhf/skimMxAODs/run/newDownloads/PhotonSys
myFlavorSysDir=/home/bstamas/xdata/yyhf/skimMxAODs/run/newDownloads/FlavorSys

myOutputDir=inputTextFiles


for sys in Sys1 Sys2 Sys3 Sys4
do
    for sample in mc16a mc16d mc16e
    do
        fileNameCounter=0
        fileCounter=0
        mySample=user.bstamas.${sample}.Sherpa2_diphoton_myy_90_175_AF2.MxAODJet${sys}_h026_test5_v1_MxAOD.root
        # nFiles=`ls -1 ${mySample}/ | wc -l`
        for file in `ls -1 $myJetSysDir/${mySample}/*root`
        do
            ((fileCounter = fileCounter + 1))
            if [[ $fileCounter -le 100 ]]
            then
                echo $file >> ${myOutputDir}/${sample}.Sherpa2_diphoton_myy_90_175_AF2.MxAODJet${sys}_INPUTS_${fileNameCounter}.txt
            else
                fileCounter=1
                ((fileNameCounter = fileNameCounter + 1))
                echo $file >> ${myOutputDir}/${sample}.Sherpa2_diphoton_myy_90_175_AF2.MxAODJet${sys}_INPUTS_${fileNameCounter}.txt
            fi 
        done
    done
done


for sys in Sys1 Sys2 Sys3 Sys4
do
    for sample in mc16a mc16d mc16e
    do
        fileNameCounter=0
        fileCounter=0
        mySample=user.bstamas.${sample}.Sherpa2_diphoton_myy_90_175_AF2.MxAODPhotonAll${sys}_h026_test5_v1_MxAOD.root
        # nFiles=`ls -1 ${mySample}/ | wc -l`
        for file in `ls -1 $myPhotonSysDir/${mySample}/*root`
        do
            ((fileCounter = fileCounter + 1))
            if [[ $fileCounter -le 100 ]]
            then
                echo $file >> ${myOutputDir}/${sample}.Sherpa2_diphoton_myy_90_175_AF2.MxAODPhotonAll${sys}_INPUTS_${fileNameCounter}.txt
            else
                fileCounter=1
                ((fileNameCounter = fileNameCounter + 1))
                echo $file >> ${myOutputDir}/${sample}.Sherpa2_diphoton_myy_90_175_AF2.MxAODPhotonAll${sys}_INPUTS_${fileNameCounter}.txt
            fi 
        done
    done
done


for sys in Sys1 Sys2 Sys3 Sys4
do
    for sample in mc16a mc16d mc16e
    do
        fileNameCounter=0
        fileCounter=0
        mySample=user.bstamas.${sample}.Sherpa2_diphoton_myy_90_175_AF2.MxAODFlavorAll${sys}_h026_test5_v1_MxAOD.root
        # nFiles=`ls -1 ${mySample}/ | wc -l`
        for file in `ls -1 $myFlavorSysDir/${mySample}/*root`
        do
            ((fileCounter = fileCounter + 1))
            if [[ $fileCounter -le 100 ]]
            then
                echo $file >> ${myOutputDir}/${sample}.Sherpa2_diphoton_myy_90_175_AF2.MxAODFlavorAll${sys}_INPUTS_${fileNameCounter}.txt
            else
                fileCounter=1
                ((fileNameCounter = fileNameCounter + 1))
                echo $file >> ${myOutputDir}/${sample}.Sherpa2_diphoton_myy_90_175_AF2.MxAODFlavorAll${sys}_INPUTS_${fileNameCounter}.txt
            fi 
        done
    done
done

