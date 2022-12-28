#!/bin/bash


dirWithSamples=/home/bstamas/xdata/yyhf/makeDataHists
# dirWithSamples=/xdata/bstamas/yyhf/yyHFToolTest/run/outputs/backgrounds

# rm project_archive.tgz
# for sample in single_mc16a
for sample in data15 data16 data17 data18
do
	### this might be different depending on the dir you run in
    counter=0
    for file in `ls -1 ${dirWithSamples}/${sample}/*root`
    do
		### submit the job
		### First comes the job name
		### Then the "working" or "testarea" which for us is the current/present working directory
		### the "any" refers to the possibility to submit jobs to specific machines
		### then i pass the file i want to run over
		### and last is an additional argument (here for example I'm running over MxAODs but there is no cutflow name for data, but i still keep the format)

		./submit_job.sh makeDataHists_singlejet_${sample}_${counter} $PWD any $file makeDataHists_singlejet_${sample}_${counter}
		# ./submit_job.sh makeDataHists_${sample}_${counter} $PWD any $file makeDataHists_${sample}_${counter}
		# echo ./submit_job.sh makeDataHists_${sample}_${counter} $PWD any $file makeDataHists_${sample}_${counter}
 
 		# echo $file
        counter=$((counter + 1))
    done
done

rm .envBefore_asetup.sh-*

# ./submit_job.sh yyHF_makeHistfromMxAOD_mc16a_test3 $PWD any /xdata/bstamas/yyhf/yyHFToolTest/run/outputs/single_mc16a/ yyHF_makeHistfromMxAOD_mc16a_test3
