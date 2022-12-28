#!/bin/bash

scriptName=$0

setupIssue() {
  echo
  echo "$1"
  echo
  echo "To setup do:"
  echo "  export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase"
  echo "  source \${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh"
  echo "  localSetupFAX"
  echo "  rcSetup -q"
  echo "  localSetupPandaClient --noAthenaCheck"
  exit 1
}

usage() {
  printf "\n%s\n" "$1"
  printf "\nUsage:\n   %s INPUT HTAG CONFIGFILE FILELIST\n" "$scriptName"
  printf "\nExample:\n  %s period2016 h017 MxAOD.config data_13TeV.txt\n" "$scriptName"
  printf "\nCONFIGS, see HGamTools/data/  examples:\n  MxAOD.config, MxAODAllSys.config\n"
  printf "\nINPUT, see HGamTools/data/input/  examples:\n  periodC, allMC, PowhegPy8_ggH125, PowhegPy8_VBF145 ...\n\n"
  printf "\nFILES, see HGamTools/data/input/  examples:\n  mc16a_HIGG1D1.txt, data_13TeV.txt ...\n\n"
  exit 1
}

# need to define $config, $sample, $dataset and $outputDS before
submit() {

  otherargs=""
  [[ ! -z "$official" ]] && otherargs+="nc_official: true nc_voms: atlas:/atlas/phys-higgs/Role=production nc_destSE: CERN-PROD_PHYS-HIGGS "
  [[ "$dataset" =~ _a[0-9][0-9][0-9]_a[0-9][0-9][0-9] ]] && otherargs+=" IsAFII: YES"
  [[ "$dataset" =~ debug ]] && otherargs+=" SkimmingCut: -1"
  [[ "$cfgName" =~ Sys   ]] && otherargs+=" nc_nFilesPerJob: 1  UseSkimAndSlimToMerge: Yes"
  # otherargs+=" EventHandler.GRL: GoodRunsLists/data16_13TeV/20161101/data16_13TeV.periodAllYear_DetStatus-v83-pro20-15_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns_ignore_TOROID_STATUS.xml"
  # otherargs+=" EventHandler.PRW.LumiCalcFiles: HGamAnalysisFramework/ilumicalc_histograms_HLT_g35_loose_g25_loose_297730-311481_ignore_TOROID_STATUS_OflLumi-13TeV-005.root"
  # otherargs+=" nc_excludedSite: ANALY_TRIUMF"
  # otherargs+=" nc_mergeOutput: false"
  # cmd="runHGamCutflowAndMxAOD $config SampleName: $sample OutputDir: grid-${sample}-DATE GridDS: $dataset OutputDS: $outputDS $otherargs"


  #BLS CHANGE
  cmd="runHGamCutflowAndMxAOD $config SampleName: $sample OutputDir: grid-${sample}-DATE GridDS: $dataset OutputDS: $outputDS $otherargs"
  # echo $outputDS
  echo
  # printing the command to the screen, can remove echo to do actual submission
  echo $cmd
  
  $cmd



  # echo $outputDS
  # JAA FIX
  # if ls ./*.tgz 1> /dev/null 2>&1; then
  #   echo "Local Tarball exists, will keep using it and not copy over new one"
  # else
  #   if ls grid-${sample}-*/elg/*.tgz 1> /dev/null 2>&1; then
  #     echo "Copying output tarball locally for reuse"
  #     cp grid-${sample}-*/elg/*.tgz ./
  #   else
  #     echo "Warning, output tarball was not found, will be slow again!"
  #   fi
  # fi
  # echo "Deleting output directory to save space"
  # echo "rm -r grid-${sample}-*"
  # rm -r grid-${sample}-*


  echo "Deleting output directory to save space"
  echo "rm -r grid-${sample}-*"
  rm -r grid-${sample}-*
}

# need to define $config, $sample, $dataset before
submitData() {
  # user.NAME.INPUTDATASET.htag   %? removes last character of input dataset /
  # cut between first ':' and first '.merge'
  ds=$(echo $dataset | cut -f2 -d:)
  ds2=$(echo $ds | awk -F '.deriv' {'print $1'})
  ds3=$(echo $ds2 | awk -F '.PhysCont' {'print $1'})
  ptag=${dataset/\//}
  ptag=${ptag: -5}
  #BLS CHANGE
  # outputDS=user.${RUCIO_ACCOUNT}.${ds3}.${cfgName}.${ptag}.$htag
  # [[ ! -z "$official" ]] && outputDS=group.phys-higgs.${ds3}.${cfgName}.${ptag}.$htag
  outputDS=user.${RUCIO_ACCOUNT}.${ds3}.${ptag}.$htag
  [[ ! -z "$official" ]] && outputDS=group.phys-higgs.${ds3}.${ptag}.$htag
  submit
}

# need to define $config, $sample, $dataset before
submitMC() {
  prodtags=${dataset##*.}

  mcprod=mc15a
  [[ "$dataset" =~ r7326 ]] && mcprod=mc15b
  [[ "$dataset" =~ r7267 ]] && mcprod=mc15b
  [[ "$dataset" =~ r7725 ]] && mcprod=mc15c
  [[ "$dataset" =~ a818 ]] && mcprod=mc15c
  [[ "$dataset" =~ r9364 ]] && mcprod=mc16a
  [[ "$dataset" =~ r9781 ]] && mcprod=mc16c
  [[ "$dataset" =~ r9778 ]] && mcprod=mc16c
  [[ "$dataset" =~ r10201 ]] && mcprod=mc16d
  [[ "$dataset" =~ r10724 ]] && mcprod=mc16e

  # sampname=${sample/_AF2/}
  sampname=${sample}


  outname=${mcprod}.${sampname}.${cfgName}_${htag}
  outputDS=user.${RUCIO_ACCOUNT}.${outname}
  [[ ! -z "$official" ]] && outputDS=group.phys-higgs.${outname}
  submit
}


# make sure there are 3 arguments
[[ $# < 4 ]] && usage "Not enough options !"

sample=$1
htag=$2

[ "$5" == "-official" ] && official="yes"
# make sure rootCore is seutp
[[ -z $AnalysisBase_DIR ]] && setupIssue "You need to setup AnalysisBase prior to running"

# make sure rootCore is seutp
[[ -z "$(command -v rucio)" ]] && setupIssue "You need to setup rucio prior to running: lsetup \"rucio -w\""

cfg=$WorkDir_DIR/data/HGamTools/$3

# make sure the config file exist
[[ ! -e $cfg ]] && usage "Cannot find $3 in this location: $config"
cfgName=${3%.*}
config=HGamTools/$3

list=$WorkDir_DIR/data/HGamTools/input/$4
# make sure the input list exist
[[ ! -e $list ]] && usage "Cannot find $4 in $WorkDir_DIR/data/HGamTools/input"

campaign=${4%_*}

if [[ $sample = periodAll25ns ]]; then
    n=$(grep -c "^period. " $list)
    [[ $n = 0 ]] && usage "No samples of type $sample in $list"
    datasets=$(grep "^period. " $list | awk '{print $2}')
    for dataset in $datasets ; do
      sample=$(grep "$dataset" $list | awk '{print $1}')
      submitData
    done

elif [[ $sample = period* ]] ; then

    n=$(grep -c "^$sample " $list)
    [[ $n = 0 ]] && usage "No samples of type $sample in $list"

    datasets=$(grep "^$sample " $list | awk '{print $2}')
    for dataset in $datasets ; do
	submitData
    done

elif [[ $sample = run* ]] ; then

  n=$(grep -c "${sample/run/}" $list)
  [[ $n = 0 ]] && usage "No samples of type $sample in $list"

  datasets=$(grep "${sample/run/}" $list | awk '{print $2}')
  for dataset in $datasets ; do
  submitData
  done


elif [[ $sample = allMC ]] || [[ $sample = allDetailed ]] ; then

    samples=$(cat $list | grep -v ^\# | awk '{print $1}')
    for sample in $samples ; do
	n=$(grep -c "^$sample " $list)
	[[ $n -gt 1 ]] && usage "$n samples of type $sample in $list ?"
	dataset=$(grep "^$sample " $list | awk '{print $2}')
	submitMC
    done
elif [[ $sample = all* ]] ; then

    samplist=$WorkDir_DIR/data/HGamTools/input/${campaign}_${sample/all/}.txt
    samples=$(cat $samplist | grep -v ^\# | awk '{print $1}')
    for sample in $samples ; do
	n=$(grep -c "^$sample " $list)
	[[ $n -gt 1 ]] && usage "$n samples of type $sample in $list ?"
	dataset=$(grep "^$sample " $list | awk '{print $2}')
	submitMC
    done
elif [[ $sample = nominalMC ]] ; then
  samples=$(cat $list | awk '{print $1}'| grep "125")
  for sample in $samples ; do
    n=$(grep -c "^$sample " $list)
    [[ $n -gt 1 ]] && usage "$n samples of type $sample in $list ?"
    dataset=$(grep "^$sample " $list | awk '{print $2}')
    submitMC
  done
else

  # MC submission
  n=$(grep -c "^$sample " $list)
  [[ $n = 0   ]] && usage "No samples of type $sample in $list"
  [[ $n -gt 1 ]] && usage "$n samples of type $sample in $list ?"
  dataset=$(grep "^$sample " $list | awk '{print $2}')
  submitMC

fi
