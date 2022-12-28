MYUSERNAME="$USER"
NOTIFY_USER="$MYUSERNAME@nicadd.niu.edu"
BATCH_ROOT_DIR="/bdata/${MYUSERNAME}/batch"

#
#
JOBNAME="$1"
#
#
#
if [ "a$2" != "a" ]; then 
   PROJECT_CODE_DIR="$2"
#   
else 
# 
   PROJECT_CODE_DIR=""; 
fi

if [ "$3" != "any" ]; then 
   SHORT_NODE_NAME="$3"
   NODE_NAME="$3.nicadd.niu.edu"
else 
   NODE_NAME=""; 
fi
inputdir=$4
outputname=$5

PROJECT_SCRATCH_DIR="/disk/${MYUSERNAME}"
#DATA common for all subjobs of $jobnama
PROJECT_SCRATCH_DATADIR="/disk/${MYUSERNAME}/data_$JOBNAME"
#Condor cmd, job shell scripts and input archives are here
PROJECT_CONDOR_DIR="$BATCH_ROOT_DIR/condor"
#Store output from all jobs here
PROJECT_OUT_DIR="$BATCH_ROOT_DIR/results"
if [ ! -d $PROJECT_CONDOR_DIR ];  then mkdir -p $PROJECT_CONDOR_DIR; fi
if [ ! -d $PROJECT_OUT_DIR ];  then mkdir -p $PROJECT_OUT_DIR; fi
#
PROJECT_NAME="$(echo $PROJECT_CODE_DIR | sed 's/\// /g' | awk '{print $NF}')"
DATE="$(date | sed 's/:/ /g' | awk '{print $2$3"_"$4_$5_$6}')"
# 
JOBOUTDIR="$PROJECT_OUT_DIR/${JOBNAME}_${DATE}"
#
JOBLOGDIR="$JOBOUTDIR/log"
#To be submitted with condor_submit
JOBCMDCONDOR="${JOBNAME}_${DATE}.cmd"
#To be launhed by $JOBCMDCONDOR
JOBCMDSCRIPT="${JOBNAME}_${DATE}.sh"
#
if [ ! -d $JOBLOGDIR ]; then  mkdir -p $JOBLOGDIR; fi
echo "Preparing job $JOBNAME for user $MYUSERNAME, job information will be sent to $NOTIFY_USER"
echo "Input code and data will be taken from $PROJECT_CODE_DIR"
echo "Creating job shell script         : ${PROJECT_CONDOR_DIR}/${JOBCMDSCRIPT}"
echo "Creating condor description script: ${PROJECT_CONDOR_DIR}/${JOBCMDCONDOR}"
#
#SCRATCH area on a remote node
JOBSCRATCH="${PROJECT_SCRATCH_DIR}/${JOBNAME}_${DATE}"
#Consumables (anything that will be used by job shell script)
JOB_INPUT_ARCHIVE="${JOBNAME}_${DATE}.tgz"
#
#Create or use  an input archive 
if [ ! -f ${PROJECT_CODE_DIR}/project_archive.tgz ]; then 
 echo "Project archive (${PROJECT_CODE_DIR}/project_archive.tgz) is not found, creating"
 tar -czf ${PROJECT_CODE_DIR}/project_archive.tgz  $PROJECT_CODE_DIR/makeHist.py $PROJECT_CODE_DIR/setup.sh > /dev/null 2>&1
else
 echo "Will use ${PROJECT_CODE_DIR}/project_archive.tgz for the batch job"
fi 
#
# Create shell script (will run on the remote node)
if [ -f ${PROJECT_CONDOR_DIR}/${JOBCMDSCRIPT} ]; then rm -f ${PROJECT_CONDOR_DIR}/${JOBCMDSCRIPT}; fi
#==============================================================================================
cat > ${PROJECT_CONDOR_DIR}/${JOBCMDSCRIPT}  << EOF_USER_SCRIPT
#!/bin/bash
#===========Command script to be run on a remote node =========================================
#${JOBCMDSCRIPT} 
#The code below will be executed on a remote node - to be customized by user  
#
echo "--- node \$HOSTNAME"


#
#Creating scratch directory on a remote node
mkdir -p $JOBSCRATCH
#prepare common data
mkdir -p $PROJECT_SCRATCH_DATADIR
cd  $PROJECT_SCRATCH_DATADIR


################
#
cd $JOBSCRATCH
#
#
#Copy/unpack the input archive
rsync -av ${PROJECT_CODE_DIR}/project_archive.tgz ./
tar -xzf project_archive.tgz
rm project_archive.tgz

ln -s $PROJECT_SCRATCH_DATADIR
#
export ATLAS_LOCAL_ROOT_BASE="/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase"
echo "ATLAS_LOCAL_ROOT_BASE = $ATLAS_LOCAL_ROOT_BASE"
echo "doing atlasLocalSetup"
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh

source setup.sh
cd $JOBSCRATCH

#

nCPUmin=20;
ok2run=0;
while [ \$ok2run == 0 ]; do
    nAthena="\$(pgrep -l -u jahreda | grep athena | wc -l)"
    #
    if [ \$nAthena -ge \$nCPUmin ]; then
        echo "No free CPU, waiting ..."
        sleep 60;
    else
        ok2run=1
        echo "bls got it!"
    fi
done

outDir=./output/

echo "BLS input dir = " $inputdir
echo "bls outputname = " $outputname
echo "bls in directory" ${PWD}
## python makeDataHists.py $inputdir $outputname

python makeDataHists_singlejet.py $inputdir $outputname

#
echo "Done and ls is"
ls -l
echo "BLS output"

 #
  echo "Finished, copy results to  $JOBOUTDIR "
  rsync -av  *   $JOBOUTDIR/
############################## fi 
cd ${PROJECT_SCRATCH_DIR}
ls -l
#Clean-up (please do not comment, except for debug)
rm -rf ./${JOBNAME}_${DATE}
#
EOF_USER_SCRIPT
#
###
chmod 755 ${PROJECT_CONDOR_DIR}/${JOBCMDSCRIPT}
#Prepare condor command file
if [ -f ${PROJECT_CONDOR_DIR}/${JOBCMDCONDOR} ]; then rm -f ${PROJECT_CONDOR_DIR}/${JOBCMDCONDOR}; fi
#==============================================================================================
if [ "0$NODE_NAME" == "0" ]; then
cat > ${PROJECT_CONDOR_DIR}/${JOBCMDCONDOR}  <<EOF
#==============================================================================================
## Condor job description file to launch ${PROJECT_CONDOR_DIR}/${JOBCMDSCRIPT} on any free node
#==============================================================================================
requirements = (Arch == "SL7x64")
#
executable                = ${PROJECT_CONDOR_DIR}/${JOBCMDSCRIPT}
output                    = ${JOBLOGDIR}/${JOBNAME}.out
error                     = ${JOBLOGDIR}/${JOBNAME}.err
log                       = ${JOBLOGDIR}/${JOBNAME}.log
universe                  = vanilla
should_transfer_files     = YES
when_to_transfer_output   = ON_EXIT
notify_user               = ${NOTIFY_USER}
RequestMemory             = 3600
queue
EOF
#
else
cat > ${PROJECT_CONDOR_DIR}/${JOBCMDCONDOR} <<EOF
#==============================================================================================
## Condor job description file to launch ${PROJECT_CONDOR_DIR}/${JOBCMDSCRIPT} on $NODE_NAME
#==============================================================================================
#
requirements              = (Arch == "SL7x64")
#
executable                = ${PROJECT_CONDOR_DIR}/${JOBCMDSCRIPT}
output                    = ${JOBLOGDIR}/${JOBNAME}.out
error                     = ${JOBLOGDIR}/${JOBNAME}.err
log                       = ${JOBLOGDIR}/${JOBNAME}.log
universe                  = vanilla
should_transfer_files     = YES
when_to_transfer_output   = ON_EXIT
notify_user               = ${NOTIFY_USER}
RequestMemory             = 3600
queue
EOF
fi
#
echo "Submitting job ${PROJECT_CONDOR_DIR}/${JOBCMDCONDOR} to run ${PROJECT_CONDOR_DIR}/${JOBCMDSCRIPT}"
echo "Remote working directory /nfs/work/${SHORT_NODE_NAME}/$MYUSERNAME/${JOBNAME}_${DATE}" 
sleep 5
condor_submit  ${PROJECT_CONDOR_DIR}/${JOBCMDCONDOR}
echo "Done, job output will be copied to $JOBOUTDIR"
echo "Job stat will be written to $JOBLOGDIR"
echo "To check job status please run :"
echo "condor_q -global" 
echo "#------------#"
#
