Starting in your test directory:  
setupATLAS   
cd source; asetup AnalysisBase,21.2.10,here     
cd ../build  
cmake ../source; make  
source x86_64-slc6-gcc62-opt/setup.sh  
cd ../run/  
    
  
For simulation:  
AnalysisFTK_RunLocal $TestSampleDirectory AOD $OutputDirectory [optional]   
  
For data:  
AnalysisFTK_RunLocal $TestSampleDirectory data $OutputDirectory [optional]  
  
This creates output ntuple file beginning with "hist-"  
    
  
Plot the ntuple file using xAOD_efficiency from the run directory:  
simulation:  
	python ../source/FTK_Bank_Validation/xAOD_efficiency.py  --file $hist-file  
data:  
   python ../source/FTK_Bank_Validation/xAOD_efficiency.py  --file $hist-file --data True  
   
Which outputs a file mydXAOD_analysis_output_BLS.root  


To compare two files:  
simulation:  
	python ../source/FTK_Bank_Validation/compare.py --file1 $file1 --file2 $file2  
  
data:  
	python ../source/FTK_Bank_Validation/compare.py --file1 $file1 --file2 $file2 --data True  
