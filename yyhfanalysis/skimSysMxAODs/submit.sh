
#!/bin/bash


dirWithSamples=/home/bstamas/xdata/yyhf/skimMxAODs/run/inputTextFiles


for mainSys in FlavorAll
do
	for sys in 1 2 3 4 
	do
		# rm /home/bstamas/xdata/yyhf/skimMxAODs/run/project_archive.tgz
		# if   [[ $mainSys == "FlavorAll" ]]; then tar -cvzf project_archive.tgz  ../sourceFS${sys} #cp project_archiveFS${sys}.tgz project_archive.tgz
		# elif [[ $mainSys == "PhotonAll" ]]; then tar -cvzf project_archive.tgz  ../sourcePS${sys} #cp project_archivePS${sys}.tgz project_archive.tgz
		# elif [[ $mainSys == "Jet" ]];    then tar -cvzf project_archive.tgz  ../sourceJS${sys}  #cp project_archiveJS${sys}.tgz project_archive.tgz
		# fi
		for sample in mc16a mc16d mc16e 
		do
		    counter=0
		    for file in `find ${dirWithSamples}/ -maxdepth 1 -name "*${sample}*MxAOD${mainSys}Sys${sys}*" -printf "%f\n"`
		    # for file in `ls -1 ${dirWithSamples}/${sample}/*root`
		    do
				echo $file
				./submit_job.sh yyHF_skimMxAODs_Sherpa2_diphoton_myy_90_175_AF2_${sample}_${mainSys}Sys${sys}_${counter} $PWD any ${dirWithSamples}/ yyHF_skimMxAODs_Sherpa2_diphoton_myy_90_175_AF2_${sample}_${mainSys}Sys${sys}_${counter} ${sample} ${dirWithSamples}/$file ${mainSys}Sys${sys}
		        counter=$((counter + 1))
		    done
		done
		# sleep 1m
	done
done

