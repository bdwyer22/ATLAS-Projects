
#!/bin/bash
PathToTestFiles="/eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h026/mc16e/" 
# Declare an array of string with type
declare -a StringArray=("PhotonAllSys1" "PhotonAllSys2" "PhotonAllSys3" "PhotonAllSys4" "JetSys1" "JetSys2" "JetSys3" "JetSys4" "LeptonMETSys" "FlavorSys" "PhotonSys")

for val in ${StringArray[@]}; do
  checkxAOD.py ${PathToTestFiles}/$val/mc16e.PowhegPy8_NNLOPS_ggH125.MxAOD${val}.e5607_s3126_r10724_p4180_h026.root/mc16e.PowhegPy8_NNLOPS_ggH125.MxAOD${val}.e5607_s3126_r10724_p4180_h026.001.root | grep HGamEventInfo_ |awk '{print $9}' |sed 's/HGamEventInfo_/+SkimAndSlim.SystematicsToSave: _/g'
done


