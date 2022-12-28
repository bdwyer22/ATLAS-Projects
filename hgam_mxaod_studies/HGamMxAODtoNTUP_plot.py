import ROOT 
import sys
import os
from math import sqrt
from AtlasStyle import *

# Given directory where root file is, 
# find the input file (hist-*.root) and
# then create a subdirectory from diven 
# directory and that's where the root file
# will be kept as well as pdf's 


inputDir = str(sys.argv[1])

for file in os.listdir(inputDir):
    if file.endswith(".root"):
        inputPath = os.path.join(inputDir, file)

inputFile = ROOT.TFile(inputPath)
print("Imported file "+inputPath)
try:  
    os.mkdir(inputDir+"/tmpOutput")
except OSError:  
    print ("Creation of the directory tmpOutput in %s failed, directory may already exist" %inputDir)
else:  
    print ("Successfully created the directory tmpOutput in %s " %inputDir)
print


# if "15" in inputDir:
# 	lowmu = True
# if 
## Testing to make sure it creates file in correct directory
# f= open("text.txt","w+")
# f.close() 
# ptbins = 100; 
# ybins = 100;   
# pt50min = 40;  pt50max = 240;
# pt30min = 20;  pt30max = 220;
# ymin = 0;      ymax = 5;

no3550 = False; #Flag to not fill 35 < mu < 50 histograms if no high mu values
no50 = False; #Flag to not fill mu > 50 histograms if no high mu values

# if "Data15" in inputDir:
# 	print "2015 Data, no mu > 50"
# 	no50 = True
# if "Data16" in inputDir:
# 	print "2016 Data, no mu > 50"
# 	no50 = True
hist_j130_pt_015  = inputFile.Get("hist_j130_pt_015")
hist_j130_pt_1525  = inputFile.Get("hist_j130_pt_1525")
hist_j130_pt_2535  = inputFile.Get("hist_j130_pt_2535")
hist_j130_pt_3550  = inputFile.Get("hist_j130_pt_3550")
hist_j130_pt_50   = inputFile.Get("hist_j130_pt_50")

# print hist_j130_pt_50
# print "test 1"

hist_j130_pt_015_loweta  = inputFile.Get("hist_j130_pt_015_loweta")
hist_j130_pt_1525_loweta  = inputFile.Get("hist_j130_pt_1525_loweta")
hist_j130_pt_2535_loweta  = inputFile.Get("hist_j130_pt_2535_loweta")
hist_j130_pt_3550_loweta  = inputFile.Get("hist_j130_pt_3550_loweta")
hist_j130_pt_50_loweta   = inputFile.Get("hist_j130_pt_50_loweta")

hist_j130_pt_015_higheta  = inputFile.Get("hist_j130_pt_015_higheta")
hist_j130_pt_1525_higheta  = inputFile.Get("hist_j130_pt_1525_higheta")
hist_j130_pt_2535_higheta  = inputFile.Get("hist_j130_pt_2535_higheta")
hist_j130_pt_3550_higheta  = inputFile.Get("hist_j130_pt_3550_higheta")
hist_j130_pt_50_higheta   = inputFile.Get("hist_j130_pt_50_higheta")

hist_j130_y_015  = inputFile.Get("hist_j130_y_015")
hist_j130_y_1525  = inputFile.Get("hist_j130_y_1525")
hist_j130_y_2535  = inputFile.Get("hist_j130_y_2535")
hist_j130_y_3550  = inputFile.Get("hist_j130_y_3550")
hist_j130_y_50   = inputFile.Get("hist_j130_y_50")

hist_j150_pt_015  = inputFile.Get("hist_j150_pt_015")
hist_j150_pt_1525  = inputFile.Get("hist_j150_pt_1525")
hist_j150_pt_2535  = inputFile.Get("hist_j150_pt_2535")
hist_j150_pt_3550  = inputFile.Get("hist_j150_pt_3550")
hist_j150_pt_50   = inputFile.Get("hist_j150_pt_50")

hist_j150_pt_015_loweta  = inputFile.Get("hist_j150_pt_015_loweta")
hist_j150_pt_1525_loweta  = inputFile.Get("hist_j150_pt_1525_loweta")
hist_j150_pt_2535_loweta  = inputFile.Get("hist_j150_pt_2535_loweta")
hist_j150_pt_3550_loweta  = inputFile.Get("hist_j150_pt_3550_loweta")
hist_j150_pt_50_loweta   = inputFile.Get("hist_j150_pt_50_loweta")

hist_j150_pt_015_higheta  = inputFile.Get("hist_j150_pt_015_higheta")
hist_j150_pt_1525_higheta  = inputFile.Get("hist_j150_pt_1525_higheta")
hist_j150_pt_2535_higheta  = inputFile.Get("hist_j150_pt_2535_higheta")
hist_j150_pt_3550_higheta  = inputFile.Get("hist_j150_pt_3550_higheta")
hist_j150_pt_50_higheta   = inputFile.Get("hist_j150_pt_50_higheta")

hist_j150_y_015  = inputFile.Get("hist_j150_y_015")
hist_j150_y_1525  = inputFile.Get("hist_j150_y_1525")
hist_j150_y_2535  = inputFile.Get("hist_j150_y_2535")
hist_j150_y_3550  = inputFile.Get("hist_j150_y_3550")
hist_j150_y_50  = inputFile.Get("hist_j150_y_50")

hist_j130_pt_015_fJVT  = inputFile.Get("hist_j130_pt_015_fJVT")
hist_j130_pt_1525_fJVT  = inputFile.Get("hist_j130_pt_1525_fJVT")
hist_j130_pt_2535_fJVT  = inputFile.Get("hist_j130_pt_2535_fJVT")
hist_j130_pt_3550_fJVT  = inputFile.Get("hist_j130_pt_3550_fJVT")
hist_j130_pt_50_fJVT  = inputFile.Get("hist_j130_pt_50_fJVT")

hist_j130_pt_015_loweta_fJVT  = inputFile.Get("hist_j130_pt_015_loweta_fJVT")
hist_j130_pt_1525_loweta_fJVT  = inputFile.Get("hist_j130_pt_1525_loweta_fJVT")
hist_j130_pt_2535_loweta_fJVT  = inputFile.Get("hist_j130_pt_2535_loweta_fJVT")
hist_j130_pt_3550_loweta_fJVT  = inputFile.Get("hist_j130_pt_3550_loweta_fJVT")
hist_j130_pt_50_loweta_fJVT  = inputFile.Get("hist_j130_pt_50_loweta_fJVT")

hist_j130_pt_015_higheta_fJVT  = inputFile.Get("hist_j130_pt_015_higheta_fJVT")
hist_j130_pt_1525_higheta_fJVT  = inputFile.Get("hist_j130_pt_1525_higheta_fJVT")
hist_j130_pt_2535_higheta_fJVT  = inputFile.Get("hist_j130_pt_2535_higheta_fJVT")
hist_j130_pt_3550_higheta_fJVT  = inputFile.Get("hist_j130_pt_3550_higheta_fJVT")
hist_j130_pt_50_higheta_fJVT  = inputFile.Get("hist_j130_pt_50_higheta_fJVT")

hist_j130_y_015_fJVT  = inputFile.Get("hist_j130_y_015_fJVT")
hist_j130_y_1525_fJVT  = inputFile.Get("hist_j130_y_1525_fJVT")
hist_j130_y_2535_fJVT  = inputFile.Get("hist_j130_y_2535_fJVT")
hist_j130_y_3550_fJVT  = inputFile.Get("hist_j130_y_3550_fJVT")
hist_j130_y_50_fJVT  = inputFile.Get("hist_j130_y_50_fJVT")

hist_j150_pt_015_fJVT  = inputFile.Get("hist_j150_pt_015_fJVT")
hist_j150_pt_1525_fJVT  = inputFile.Get("hist_j150_pt_1525_fJVT")
hist_j150_pt_2535_fJVT  = inputFile.Get("hist_j150_pt_2535_fJVT")
hist_j150_pt_3550_fJVT  = inputFile.Get("hist_j150_pt_3550_fJVT")
hist_j150_pt_50_fJVT  = inputFile.Get("hist_j150_pt_50_fJVT")

hist_j150_pt_015_loweta_fJVT  = inputFile.Get("hist_j150_pt_015_loweta_fJVT")
hist_j150_pt_1525_loweta_fJVT  = inputFile.Get("hist_j150_pt_1525_loweta_fJVT")
hist_j150_pt_2535_loweta_fJVT  = inputFile.Get("hist_j150_pt_2535_loweta_fJVT")
hist_j150_pt_3550_loweta_fJVT  = inputFile.Get("hist_j150_pt_3550_loweta_fJVT")
hist_j150_pt_50_loweta_fJVT  = inputFile.Get("hist_j150_pt_50_loweta_fJVT")

hist_j150_pt_015_higheta_fJVT  = inputFile.Get("hist_j150_pt_015_higheta_fJVT")
hist_j150_pt_1525_higheta_fJVT  = inputFile.Get("hist_j150_pt_1525_higheta_fJVT")
hist_j150_pt_2535_higheta_fJVT  = inputFile.Get("hist_j150_pt_2535_higheta_fJVT")
hist_j150_pt_3550_higheta_fJVT  = inputFile.Get("hist_j150_pt_3550_higheta_fJVT")
hist_j150_pt_50_higheta_fJVT  = inputFile.Get("hist_j150_pt_50_higheta_fJVT")

hist_j150_y_015_fJVT  = inputFile.Get("hist_j150_y_015_fJVT")
hist_j150_y_1525_fJVT  = inputFile.Get("hist_j150_y_1525_fJVT")
hist_j150_y_2535_fJVT  = inputFile.Get("hist_j150_y_2535_fJVT")
hist_j150_y_3550_fJVT  = inputFile.Get("hist_j150_y_3550_fJVT")
hist_j150_y_50_fJVT  = inputFile.Get("hist_j150_y_50_fJVT")

hist_pass_fJVT  = inputFile.Get("hist_pass_fJVT")
hist_fail_fJVT  = inputFile.Get("hist_fail_fJVT")



j150_pt_histos = [hist_j150_pt_015, hist_j150_pt_1525, hist_j150_pt_2535, hist_j150_pt_3550, hist_j150_pt_50, 
				hist_j150_pt_015_fJVT, hist_j150_pt_1525_fJVT, hist_j150_pt_2535_fJVT, hist_j150_pt_3550_fJVT, hist_j150_pt_50_fJVT]

j150_pt_histos_loweta = [hist_j150_pt_015_loweta, hist_j150_pt_1525_loweta, hist_j150_pt_2535_loweta, hist_j150_pt_3550_loweta, hist_j150_pt_50_loweta, 
				hist_j150_pt_015_loweta_fJVT, hist_j150_pt_1525_loweta_fJVT, hist_j150_pt_2535_loweta_fJVT, hist_j150_pt_3550_loweta_fJVT, hist_j150_pt_50_loweta_fJVT]

j150_pt_histos_higheta = [hist_j150_pt_015_higheta, hist_j150_pt_1525_higheta, hist_j150_pt_2535_higheta, hist_j150_pt_3550_higheta, hist_j150_pt_50_higheta, 
				hist_j150_pt_015_higheta_fJVT, hist_j150_pt_1525_higheta_fJVT, hist_j150_pt_2535_higheta_fJVT, hist_j150_pt_3550_higheta_fJVT, hist_j150_pt_50_higheta_fJVT]

j150_y_histos = [hist_j150_y_015, hist_j150_y_1525, hist_j150_y_2535, hist_j150_y_3550, hist_j150_y_50, 
				hist_j150_y_015_fJVT, hist_j150_y_1525_fJVT, hist_j150_y_2535_fJVT, hist_j150_y_3550_fJVT, hist_j150_y_50_fJVT]

j130_pt_histos = [hist_j130_pt_015, hist_j130_pt_1525, hist_j130_pt_2535, hist_j130_pt_3550, hist_j130_pt_50, 
				hist_j130_pt_015_fJVT, hist_j130_pt_1525_fJVT, hist_j130_pt_2535_fJVT, hist_j130_pt_3550_fJVT, hist_j130_pt_50_fJVT]

j130_pt_histos_loweta = [hist_j130_pt_015_loweta, hist_j130_pt_1525_loweta, hist_j130_pt_2535_loweta, hist_j130_pt_3550_loweta, hist_j130_pt_50_loweta, 
				hist_j130_pt_015_loweta_fJVT, hist_j130_pt_1525_loweta_fJVT, hist_j130_pt_2535_loweta_fJVT, hist_j130_pt_3550_loweta_fJVT, hist_j130_pt_50_loweta_fJVT]

j130_pt_histos_higheta = [hist_j130_pt_015_higheta, hist_j130_pt_1525_higheta, hist_j130_pt_2535_higheta, hist_j130_pt_3550_higheta, hist_j130_pt_50_higheta,
				hist_j130_pt_015_higheta_fJVT, hist_j130_pt_1525_higheta_fJVT, hist_j130_pt_2535_higheta_fJVT, hist_j130_pt_3550_higheta_fJVT, hist_j130_pt_50_higheta_fJVT]

j130_y_histos = [hist_j130_y_015, hist_j130_y_1525, hist_j130_y_2535, hist_j130_y_3550, hist_j130_y_50,
				hist_j130_y_015_fJVT, hist_j130_y_1525_fJVT, hist_j130_y_2535_fJVT, hist_j130_y_3550_fJVT, hist_j130_y_50_fJVT]

fJVTHist = [hist_pass_fJVT, hist_fail_fJVT]


# a = inputFile.Get("hist_fail_fJVT") 
# for key in inputFile.GetListOfKeys():
# 	# print key.GetName()
# 	if "j150" in key.GetName():
# 		if "pt" in key.GetName():
# 			j150_pt_histos.append(key.GetName())
# 		if "y" in key.GetName():
# 			j150_y_histos.append(key.GetName())
# 	if "j130" in key.GetName():
# 		if "pt" in key.GetName():
# 			j130_pt_histos.append(key.GetName())
# 		if "y" in key.GetName():
# 			j130_y_histos.append(key.GetName())


# keys = d.viewkeys()
# histograms = d.viewvalues()
# print(j130_y_histos)
# print(j130_y_histos.viewvalues())
# for key, value in j130_y_histos.iteritems():
	# value.Draw()
	# raw_input("press enter")
# for hist in j150_pt_histos:

# # a.Draw()
# hist_j150_pt_015.Draw()
# raw_input("enter")

Means = {}
RMS = {}
NEntries = {}
SigmaRMS = {}
SigmaMu = {}


hist_j130_pt = ROOT.THStack("hist_j130_pt_fJVT", "")
hist_j130_pt_loweta = ROOT.THStack("hist_j130_pt_loweta_fJVT", "")
hist_j130_pt_higheta = ROOT.THStack("hist_j130_pt_higheta_fJVT", "")
hist_j130_y = ROOT.THStack("hist_j130_y_fJVT", "")

hist_j150_pt = ROOT.THStack("hist_j150_pt_fJVT", "")
hist_j150_pt_loweta = ROOT.THStack("hist_j150_pt_loweta_fJVT", "")
hist_j150_pt_higheta = ROOT.THStack("hist_j150_pt_higheta_fJVT", "")
hist_j150_y = ROOT.THStack("hist_j150_y_fJVT", "")

hist_j130_pt_fJVT = ROOT.THStack("hist_j130_pt_fJVT", "")
hist_j130_pt_loweta_fJVT = ROOT.THStack("hist_j130_pt_loweta_fJVT", "")
hist_j130_pt_higheta_fJVT = ROOT.THStack("hist_j130_pt_higheta_fJVT", "")
hist_j130_y_fJVT = ROOT.THStack("hist_j130_y_fJVT", "")

hist_j150_pt_fJVT = ROOT.THStack("hist_j150_p_fJVTt", "")
hist_j150_pt_loweta_fJVT = ROOT.THStack("hist_j150_pt_loweta_fJVT", "")
hist_j150_pt_higheta_fJVT = ROOT.THStack("hist_j150_pt_higheta_fJVT", "")
hist_j150_y_fJVT = ROOT.THStack("hist_j150_y_fJVT", "")


# hist_j130_pt_loweta = THStack("hist_j130_pt_loweta", "")
# hist_j130_pt_higheta = THStack("hist_j130_pt_higheta", "")


# hist_j150_pt_loweta = THStack("hist_j150_pt_loweta", "")
# hist_j150_pt_higheta = THStack("hist_j150_pt_higheta", "")

# print "norm of hist_j130_pt_50 is: " + str(hist_j130_pt_50.Integral())


for hist in j150_y_histos:
	exec( hist.GetName() + "_noNorm = hist.Clone(str(hist.GetName())+'_noNorm')")

for hist in j130_pt_histos:
	exec( hist.GetName() + "_noNorm = hist.Clone(str(hist.GetName())+'_noNorm')")

for hist in j130_y_histos:
	exec( hist.GetName() + "_noNorm = hist.Clone(str(hist.GetName())+'_noNorm')")

for hist in j150_pt_histos:
	exec( hist.GetName() + "_noNorm = hist.Clone(str(hist.GetName())+'_noNorm')")

for hist in j150_pt_histos:
	# print hist
	norm = hist.Integral(); #print norm
	if norm != 0:
		# print "norm is : "+str(norm)
		hist.Scale(1./norm)
	else:
		# print "norm is zero "+str(norm)
		if "3550" in hist.GetName():
			no3550 = True
			# print hist.GetName()
			# print no3550
		if "_50" in hist.GetName():
			no50 = True
			# print hist.GetName()
			# print no50
	Means[(str(hist.GetName()))] = hist.GetMean()
	RMS[(str(hist.GetName()))] = hist.GetRMS()
	NEntries[(str(hist.GetName()))] = hist.GetEntries()
	if hist.GetEntries() != 0:
		SigmaRMS[(str(hist.GetName()))] = hist.GetRMS()/sqrt(2*hist.GetEntries())
		SigmaMu[(str(hist.GetName()))] = hist.GetRMS()/sqrt(hist.GetEntries())
	# hist_j150_pt.Add(hist)
	# string_name = str(hist.Get)
	if "015" in hist.GetName():
		hist.SetLineColor(2) #kRed
	if "1525" in hist.GetName():
		hist.SetLineColor(4) #kBlue
	if "2535" in hist.GetName():
		hist.SetLineColor(3) #kGreen
	if "3550" in hist.GetName():
		hist.SetLineColor(1) #kBlack
	if "_50" in hist.GetName():
		hist.SetLineColor(6) #kMagenta
	if "JVT" in hist.GetName():
		hist_j150_pt_fJVT.Add(hist)
	else:
		hist_j150_pt.Add(hist)

for hist in j150_y_histos:
	# print hist
	norm = hist.Integral(); #print norm
	if norm != 0:
		hist.Scale(1./norm)
	else:
		if "3550" in hist.GetName():
			no3550 = True
		if "_50" in hist.GetName():
			no50 = True
	Means[(str(hist.GetName()))] = hist.GetMean()
	RMS[(str(hist.GetName()))] = hist.GetRMS()
	NEntries[(str(hist.GetName()))] = hist.GetEntries()
	if hist.GetEntries() != 0:
		SigmaRMS[(str(hist.GetName()))] = hist.GetRMS()/sqrt(2*hist.GetEntries())
		SigmaMu[(str(hist.GetName()))] = hist.GetRMS()/sqrt(hist.GetEntries())
	# hist_j150_y.Add(hist)
	if "015" in hist.GetName():
		hist.SetLineColor(2) #kRed
	if "1525" in hist.GetName():
		hist.SetLineColor(4) #kBlue
	if "2535" in hist.GetName():
		hist.SetLineColor(3) #kGreen
	if "3550" in hist.GetName():
		hist.SetLineColor(1) #kBlack
	if "_50" in hist.GetName():
		hist.SetLineColor(6) #kMagenta
	if "JVT" in hist.GetName():
		hist_j150_y_fJVT.Add(hist)
	else:
		hist_j150_y.Add(hist)

for hist in j130_pt_histos:
	# print hist
	norm = hist.Integral(); 
	# print hist.GetName()
	# print norm, hist.GetName()
	if norm != 0:
		hist.Scale(1./norm)
	else:
		# print norm, hist.GetName()
		if "3550" in hist.GetName():
			no3550 = True
		if "_50" in hist.GetName():
			no50 = True
	Means[(str(hist.GetName()))] = hist.GetMean()
	RMS[(str(hist.GetName()))] = hist.GetRMS()
	NEntries[(str(hist.GetName()))] = hist.GetEntries()
	if hist.GetEntries() != 0:
		SigmaRMS[(str(hist.GetName()))] = hist.GetRMS()/sqrt(2*hist.GetEntries())
		SigmaMu[(str(hist.GetName()))] = hist.GetRMS()/sqrt(hist.GetEntries())
	if "015" in hist.GetName():
		hist.SetLineColor(2) #kRed
	if "1525" in hist.GetName():
		hist.SetLineColor(4) #kBlue
	if "2535" in hist.GetName():
		hist.SetLineColor(3) #kGreen
	if "3550" in hist.GetName():
		hist.SetLineColor(1) #kBlack
	if "_50" in hist.GetName():
		hist.SetLineColor(6) #kMagenta
	if "JVT" in hist.GetName():
		hist_j130_pt_fJVT.Add(hist)
	else:
		hist_j130_pt.Add(hist)


for hist in j130_y_histos:
	# print hist
	norm = hist.Integral(); #print norm
	if norm != 0:
		hist.Scale(1./norm)
	else:
		if "3550" in hist.GetName():
			no3550 = True
		if "_50" in hist.GetName():
			no50 = True
	Means[(str(hist.GetName()))] = hist.GetMean()
	RMS[(str(hist.GetName()))] = hist.GetRMS()
	NEntries[(str(hist.GetName()))] = hist.GetEntries()
	if hist.GetEntries() != 0:
		SigmaRMS[(str(hist.GetName()))] = hist.GetRMS()/sqrt(2*hist.GetEntries())
		SigmaMu[(str(hist.GetName()))] = hist.GetRMS()/sqrt(hist.GetEntries())
	# hist_j130_y.Add(hist)
	if "015" in hist.GetName():
		hist.SetLineColor(2) #kRed
	if "1525" in hist.GetName():
		hist.SetLineColor(4) #kBlue
	if "2535" in hist.GetName():
		hist.SetLineColor(3) #kGreen
	if "3550" in hist.GetName():
		hist.SetLineColor(1) #kBlack
	if "_50" in hist.GetName():
		hist.SetLineColor(6) #kMagenta
	if "JVT" in hist.GetName():
		hist_j130_y_fJVT.Add(hist)
	else:
		hist_j130_y.Add(hist)

for hist in j130_pt_histos_loweta:
	# print hist
	norm = hist.Integral(); #print norm
	if norm != 0:
		hist.Scale(1./norm)
	else:
		if "3550" in hist.GetName():
			no3550 = True
		if "_50" in hist.GetName():
			no50 = True
	Means[(str(hist.GetName()))] = hist.GetMean()
	RMS[(str(hist.GetName()))] = hist.GetRMS()
	NEntries[(str(hist.GetName()))] = hist.GetEntries()
	if hist.GetEntries() != 0:
		SigmaRMS[(str(hist.GetName()))] = hist.GetRMS()/sqrt(2*hist.GetEntries())
		SigmaMu[(str(hist.GetName()))] = hist.GetRMS()/sqrt(hist.GetEntries())
	# hist_j130_pt_loweta.Add(hist)
	if "015" in hist.GetName():
		hist.SetLineColor(2) #kRed
	if "1525" in hist.GetName():
		hist.SetLineColor(4) #kBlue
	if "2535" in hist.GetName():
		hist.SetLineColor(3) #kGreen
	if "3550" in hist.GetName():
		hist.SetLineColor(1) #kBlack
	if "_50" in hist.GetName():
		hist.SetLineColor(6) #kMagenta
	if "JVT" in hist.GetName():
		hist_j130_pt_loweta_fJVT.Add(hist)
	else:
		hist_j130_pt_loweta.Add(hist)

for hist in j130_pt_histos_higheta:
	# print hist
	norm = hist.Integral(); #print norm
	if norm != 0:
		hist.Scale(1./norm)
	else:
		if "3550" in hist.GetName():
			no3550 = True
		if "_50" in hist.GetName():
			no50 = True
	Means[(str(hist.GetName()))] = hist.GetMean()
	RMS[(str(hist.GetName()))] = hist.GetRMS()
	NEntries[(str(hist.GetName()))] = hist.GetEntries()
	if hist.GetEntries() != 0:
		SigmaRMS[(str(hist.GetName()))] = hist.GetRMS()/sqrt(2*hist.GetEntries())
		SigmaMu[(str(hist.GetName()))] = hist.GetRMS()/sqrt(hist.GetEntries())
	# hist_j130_pt_higheta.Add(hist)
	if "015" in hist.GetName():
		hist.SetLineColor(2) #kRed
	if "1525" in hist.GetName():
		hist.SetLineColor(4) #kBlue
	if "2535" in hist.GetName():
		hist.SetLineColor(3) #kGreen
	if "3550" in hist.GetName():
		hist.SetLineColor(1) #kBlack
	if "_50" in hist.GetName():
		hist.SetLineColor(6) #kMagenta
	if "JVT" in hist.GetName():
		hist_j130_pt_higheta_fJVT.Add(hist)
	else:
		hist_j130_pt_higheta.Add(hist)

for hist in j150_pt_histos_loweta:
	# print hist
	norm = hist.Integral(); #print norm
	if norm != 0:
		hist.Scale(1./norm)
	else:
		if "3550" in hist.GetName():
			no3550 = True
		if "_50" in hist.GetName():
			no50 = True
	Means[(str(hist.GetName()))] = hist.GetMean()
	RMS[(str(hist.GetName()))] = hist.GetRMS()
	NEntries[(str(hist.GetName()))] = hist.GetEntries()
	if hist.GetEntries() != 0:
		SigmaRMS[(str(hist.GetName()))] = hist.GetRMS()/sqrt(2*hist.GetEntries())
		SigmaMu[(str(hist.GetName()))] = hist.GetRMS()/sqrt(hist.GetEntries())
	# hist_j150_pt_loweta.Add(hist)
	if "015" in hist.GetName():
		hist.SetLineColor(2) #kRed
	if "1525" in hist.GetName():
		hist.SetLineColor(4) #kBlue
	if "2535" in hist.GetName():
		hist.SetLineColor(3) #kGreen
	if "3550" in hist.GetName():
		hist.SetLineColor(1) #kBlack
	if "_50" in hist.GetName():
		hist.SetLineColor(6) #kMagenta
	if "JVT" in hist.GetName():
		hist_j150_pt_loweta_fJVT.Add(hist)
	else:
		hist_j150_pt_loweta.Add(hist)

for hist in j150_pt_histos_higheta:
	# print hist
	norm = hist.Integral(); #print norm
	if norm != 0:
		hist.Scale(1./norm)
	else:
		if "3550" in hist.GetName():
			no3550 = True
		if "_50" in hist.GetName():
			no50 = True
	Means[(str(hist.GetName()))] = hist.GetMean()
	RMS[(str(hist.GetName()))] = hist.GetRMS()
	NEntries[(str(hist.GetName()))] = hist.GetEntries()
	if hist.GetEntries() != 0:
		SigmaRMS[(str(hist.GetName()))] = hist.GetRMS()/sqrt(2*hist.GetEntries())
		SigmaMu[(str(hist.GetName()))] = hist.GetRMS()/sqrt(hist.GetEntries())
	# hist_j150_pt_higheta.Add(hist)
	if "015" in hist.GetName():
		hist.SetLineColor(2) #kRed
	if "1525" in hist.GetName():
		hist.SetLineColor(4) #kBlue
	if "2535" in hist.GetName():
		hist.SetLineColor(3) #kGreen
	if "3550" in hist.GetName():
		hist.SetLineColor(1) #kBlack
	if "_50" in hist.GetName():
		hist.SetLineColor(6) #kMagenta
	if "JVT" in hist.GetName():
		hist_j150_pt_higheta_fJVT.Add(hist)
	else:
		hist_j150_pt_higheta.Add(hist)		
# hist_j150_pt_015.Draw()
# raw_input("enter")

# print Means["hist_j130_pt_015"]


os.chdir(inputDir+"/tmpOutput")

gROOT.SetBatch(True)
# print no50
# print hist_j130_pt_50.Integral()
ptcan30 = ROOT.TCanvas("ptcan30", "")
hist_j130_pt.Draw("nostack")
# raw_input("press enter")

legend =  ROOT.TLegend(0.3,0.7,0.9,0.9);
# legend.SetHeader("The Legend Title","C"); # option "C" allows to center the header
legend.AddEntry(hist_j130_pt_015,"#mu < 15;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j130_pt_015"], SigmaMu["hist_j130_pt_015"], RMS["hist_j130_pt_015"], SigmaRMS["hist_j130_pt_015"]),"PL");
legend.AddEntry(hist_j130_pt_1525,"15 < #mu < 25;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j130_pt_1525"], SigmaMu["hist_j130_pt_1525"], RMS["hist_j130_pt_1525"], SigmaRMS["hist_j130_pt_1525"]),"PL");
legend.AddEntry(hist_j130_pt_2535,"25 < #mu < 35;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j130_pt_2535"], SigmaMu["hist_j130_pt_2535"], RMS["hist_j130_pt_2535"], SigmaRMS["hist_j130_pt_2535"]),"PL");
if no3550 == False:
	legend.AddEntry(hist_j130_pt_3550,"35 < #mu < 50;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j130_pt_3550"], SigmaMu["hist_j130_pt_3550"], RMS["hist_j130_pt_3550"], SigmaRMS["hist_j130_pt_3550"]),"PL");
if no50 == False:
	# print hist_j130_pt_50
	legend.AddEntry(hist_j130_pt_50,"#mu > 50;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j130_pt_50"], SigmaMu["hist_j130_pt_50"], RMS["hist_j130_pt_50"], SigmaRMS["hist_j130_pt_50"]),"PL");
legend.Draw();
hist_j130_pt.GetXaxis().SetTitle("p_{T} [GeV]");
hist_j130_pt.GetYaxis().SetTitle("Normalized A.U.");
ATLASLabel(0.6, 0.65, "Internal", 1)
ptcan30.SaveAs("hist_j130_pt.pdf")


ycan30 = ROOT.TCanvas("ycan30", "")
hist_j130_y.Draw("nostack")
legend =  ROOT.TLegend(0.5,0.7,0.9,0.9);
# legend.SetHeader("The Legend Title","C"); # option "C" allows to center the header
legend.AddEntry(hist_j130_y_015,"#mu < 15","PL");
legend.AddEntry(hist_j130_y_1525,"15 < #mu < 25","PL");
legend.AddEntry(hist_j130_y_2535,"25 < #mu < 35","PL");
if no3550 == False:
	legend.AddEntry(hist_j130_y_3550,"35 < #mu < 50","PL");
if no50 == False:
	legend.AddEntry(hist_j130_y_50,"#mu > 50","PL");
legend.Draw();
hist_j130_y.GetXaxis().SetTitle("Rapidity");
hist_j130_y.GetYaxis().SetTitle("Normalized A.U.");
ATLASLabel(0.6, 0.65, "Internal", 1)
ycan30.SaveAs("hist_j130_y.pdf")

ptcan_loweta30 = ROOT.TCanvas("ptcan_loweta30", "")
hist_j130_pt_loweta.Draw("nostack")
# raw_input("press enter")

legend =  ROOT.TLegend(0.3,0.7,0.9,0.9);
# legend.SetHeader("The Legend Title","C"); # option "C" allows to center the header
legend.AddEntry(hist_j130_pt_015_loweta,"#mu < 15;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j130_pt_015_loweta"], SigmaMu["hist_j130_pt_015_loweta"], RMS["hist_j130_pt_015_loweta"], SigmaRMS["hist_j130_pt_015_loweta"]),"PL");
legend.AddEntry(hist_j130_pt_1525_loweta,"15 < #mu < 25;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j130_pt_1525_loweta"], SigmaMu["hist_j130_pt_1525_loweta"], RMS["hist_j130_pt_1525_loweta"], SigmaRMS["hist_j130_pt_1525_loweta"]),"PL");
legend.AddEntry(hist_j130_pt_2535_loweta,"25 < #mu < 35;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j130_pt_2535_loweta"], SigmaMu["hist_j130_pt_2535_loweta"], RMS["hist_j130_pt_2535_loweta"], SigmaRMS["hist_j130_pt_2535_loweta"]),"PL");
if no3550 == False:
	legend.AddEntry(hist_j130_pt_3550_loweta,"35 < #mu < 50;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j130_pt_3550_loweta"], SigmaMu["hist_j130_pt_3550_loweta"], RMS["hist_j130_pt_3550_loweta"], SigmaRMS["hist_j130_pt_3550_loweta"]),"PL");
if no50 == False:
	legend.AddEntry(hist_j130_pt_50_loweta,"#mu > 50;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j130_pt_50_loweta"], SigmaMu["hist_j130_pt_50_loweta"], RMS["hist_j130_pt_50_loweta"], SigmaRMS["hist_j130_pt_50_loweta"]),"PL");
legend.Draw();
hist_j130_pt_loweta.GetXaxis().SetTitle("p_{T} [GeV]");
hist_j130_pt_loweta.GetYaxis().SetTitle("Normalized A.U.");
ATLASLabel(0.6, 0.65, "Internal", 1)
ptcan_loweta30.SaveAs("hist_j130_pt_loweta.pdf")


ptcan_higheta30 = ROOT.TCanvas("ptcan_higheta30", "")
hist_j130_pt_higheta.Draw("nostack")
# raw_input("press enter")

legend =  ROOT.TLegend(0.3,0.7,0.9,0.9);
# legend.SetHeader("The Legend Title","C"); # option "C" allows to center the header
legend.AddEntry(hist_j130_pt_015_higheta,"#mu < 15;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j130_pt_015_higheta"], SigmaMu["hist_j130_pt_015_higheta"], RMS["hist_j130_pt_015_higheta"], SigmaRMS["hist_j130_pt_015_higheta"]),"PL");
legend.AddEntry(hist_j130_pt_1525_higheta,"15 < #mu < 25;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j130_pt_1525_higheta"], SigmaMu["hist_j130_pt_1525_higheta"], RMS["hist_j130_pt_1525_higheta"], SigmaRMS["hist_j130_pt_1525_higheta"]),"PL");
legend.AddEntry(hist_j130_pt_2535_higheta,"25 < #mu < 35;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j130_pt_2535_higheta"], SigmaMu["hist_j130_pt_2535_higheta"], RMS["hist_j130_pt_2535_higheta"], SigmaRMS["hist_j130_pt_2535_higheta"]),"PL");
if no3550 == False:
	legend.AddEntry(hist_j130_pt_3550_higheta,"35 < #mu < 50;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j130_pt_3550_higheta"], SigmaMu["hist_j130_pt_3550_higheta"], RMS["hist_j130_pt_3550_higheta"], SigmaRMS["hist_j130_pt_3550_higheta"]),"PL");
if no50 == False:
	legend.AddEntry(hist_j130_pt_50_higheta,"#mu > 50;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j130_pt_50_higheta"], SigmaMu["hist_j130_pt_50_higheta"], RMS["hist_j130_pt_50_higheta"], SigmaRMS["hist_j130_pt_50_higheta"]),"PL");
legend.Draw();
hist_j130_pt_higheta.GetXaxis().SetTitle("p_{T} [GeV]");
hist_j130_pt_higheta.GetYaxis().SetTitle("Normalized A.U.");
ATLASLabel(0.6, 0.65, "Internal", 1)
ptcan_higheta30.SaveAs("hist_j130_pt_higheta.pdf")


ptcan50 = ROOT.TCanvas("ptcan50", "")
hist_j150_pt.Draw("nostack")
# raw_input("press enter")

legend =  ROOT.TLegend(0.3,0.7,0.9,0.9);
# legend.SetHeader("The Legend Title","C"); # option "C" allows to center the header
legend.AddEntry(hist_j150_pt_015,"#mu < 15;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j150_pt_015"], SigmaMu["hist_j150_pt_015"], RMS["hist_j150_pt_015"], SigmaRMS["hist_j150_pt_015"]),"PL");
legend.AddEntry(hist_j150_pt_1525,"15 < #mu < 25;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j150_pt_1525"], SigmaMu["hist_j150_pt_1525"], RMS["hist_j150_pt_1525"], SigmaRMS["hist_j150_pt_1525"]),"PL");
legend.AddEntry(hist_j150_pt_2535,"25 < #mu < 35;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j150_pt_2535"], SigmaMu["hist_j150_pt_2535"], RMS["hist_j150_pt_2535"], SigmaRMS["hist_j150_pt_2535"]),"PL");
if no3550 == False:
	legend.AddEntry(hist_j150_pt_3550,"35 < #mu < 50;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j150_pt_3550"], SigmaMu["hist_j150_pt_3550"], RMS["hist_j150_pt_3550"], SigmaRMS["hist_j150_pt_3550"]),"PL");
if no50 == False:
	legend.AddEntry(hist_j150_pt_50,"#mu > 50;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j150_pt_50"], SigmaMu["hist_j150_pt_50"], RMS["hist_j150_pt_50"], SigmaRMS["hist_j150_pt_50"]),"PL");
legend.Draw();
hist_j150_pt.GetXaxis().SetTitle("p_{T} [GeV]");
hist_j150_pt.GetYaxis().SetTitle("Normalized A.U.");
ATLASLabel(0.6, 0.65, "Internal", 1)
ptcan50.SaveAs("hist_j150_pt.pdf")


ycan50 = ROOT.TCanvas("ycan50", "")
hist_j150_y.Draw("nostack")
legend =  ROOT.TLegend(0.5,0.7,0.9,0.9);
# legend.SetHeader("The Legend Title","C"); # option "C" allows to center the header
legend.AddEntry(hist_j150_y_015,"#mu < 15","PL");
legend.AddEntry(hist_j150_y_1525,"15 < #mu < 25","PL");
legend.AddEntry(hist_j150_y_2535,"25 < #mu < 35","PL");
if no3550 == False:
	legend.AddEntry(hist_j150_y_3550,"35 < #mu < 50","PL");
if no50 == False:
	legend.AddEntry(hist_j150_y_50,"#mu > 50","PL");
legend.Draw();
hist_j150_y.GetXaxis().SetTitle("Rapidity");
hist_j150_y.GetYaxis().SetTitle("Normalized A.U.");
ATLASLabel(0.6, 0.65, "Internal", 1)
ycan50.SaveAs("hist_j150_y.pdf")

ptcan_loweta50 = ROOT.TCanvas("ptcan_loweta50", "")
hist_j150_pt_loweta.Draw("nostack")
# raw_input("press enter")

legend =  ROOT.TLegend(0.3,0.7,0.9,0.9);
# legend.SetHeader("The Legend Title","C"); # option "C" allows to center the header
legend.AddEntry(hist_j150_pt_015_loweta,"#mu < 15;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j150_pt_015_loweta"], SigmaMu["hist_j150_pt_015_loweta"], RMS["hist_j150_pt_015_loweta"], SigmaRMS["hist_j150_pt_015_loweta"]),"PL");
legend.AddEntry(hist_j150_pt_1525_loweta,"15 < #mu < 25;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j150_pt_1525_loweta"], SigmaMu["hist_j150_pt_1525_loweta"], RMS["hist_j150_pt_1525_loweta"], SigmaRMS["hist_j150_pt_1525_loweta"]),"PL");
legend.AddEntry(hist_j150_pt_2535_loweta,"25 < #mu < 35;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j150_pt_2535_loweta"], SigmaMu["hist_j150_pt_2535_loweta"], RMS["hist_j150_pt_2535_loweta"], SigmaRMS["hist_j150_pt_2535_loweta"]),"PL");
if no3550 == False:
	legend.AddEntry(hist_j150_pt_3550_loweta,"35 < #mu < 50;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j150_pt_3550_loweta"], SigmaMu["hist_j150_pt_3550_loweta"], RMS["hist_j150_pt_3550_loweta"], SigmaRMS["hist_j150_pt_3550_loweta"]),"PL");
if no50 == False:
	legend.AddEntry(hist_j150_pt_50_loweta,"#mu > 50;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j150_pt_50_loweta"], SigmaMu["hist_j150_pt_50_loweta"], RMS["hist_j150_pt_50_loweta"], SigmaRMS["hist_j150_pt_50_loweta"]),"PL");
legend.Draw();
hist_j150_pt_loweta.GetXaxis().SetTitle("p_{T} [GeV]");
hist_j150_pt_loweta.GetYaxis().SetTitle("Normalized A.U.");
ATLASLabel(0.6, 0.65, "Internal", 1)
ptcan_loweta50.SaveAs("hist_j150_pt_loweta.pdf")


ptcan_higheta50 = ROOT.TCanvas("ptcan_higheta50", "")
hist_j150_pt_higheta.Draw("nostack")
# raw_input("press enter")

legend =  ROOT.TLegend(0.3,0.7,0.9,0.9);
# legend.SetHeader("The Legend Title","C"); # option "C" allows to center the header
legend.AddEntry(hist_j150_pt_015_higheta,"#mu < 15;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j150_pt_015_higheta"], SigmaMu["hist_j150_pt_015_higheta"], RMS["hist_j150_pt_015_higheta"], SigmaRMS["hist_j150_pt_015_higheta"]),"PL");
legend.AddEntry(hist_j150_pt_1525_higheta,"15 < #mu < 25;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j150_pt_1525_higheta"], SigmaMu["hist_j150_pt_1525_higheta"], RMS["hist_j150_pt_1525_higheta"], SigmaRMS["hist_j150_pt_1525_higheta"]),"PL");
legend.AddEntry(hist_j150_pt_2535_higheta,"25 < #mu < 35;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j150_pt_2535_higheta"], SigmaMu["hist_j150_pt_2535_higheta"], RMS["hist_j150_pt_2535_higheta"], SigmaRMS["hist_j150_pt_2535_higheta"]),"PL");
if no3550 == False:
	legend.AddEntry(hist_j150_pt_3550_higheta,"35 < #mu < 50;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j150_pt_3550_higheta"], SigmaMu["hist_j150_pt_3550_higheta"], RMS["hist_j150_pt_3550_higheta"], SigmaRMS["hist_j150_pt_3550_higheta"]),"PL");
if no50 == False:
	legend.AddEntry(hist_j150_pt_50_higheta,"#mu > 50;  mean: %.3f +/- %.3f RMS: %.3f +/- %.3f"%(Means["hist_j150_pt_50_higheta"], SigmaMu["hist_j150_pt_50_higheta"], RMS["hist_j150_pt_50_higheta"], SigmaRMS["hist_j150_pt_50_higheta"]),"PL");
legend.Draw();
hist_j150_pt_higheta.GetXaxis().SetTitle("p_{T} [GeV]");
hist_j150_pt_higheta.GetYaxis().SetTitle("Normalized A.U.");
ATLASLabel(0.6, 0.65, "Internal", 1)
ptcan_higheta50.SaveAs("hist_j150_pt_higheta.pdf")

newFile = ROOT.TFile("output_histograms.root", "RECREATE")

fullHistList = [hist_j130_pt_015_higheta, hist_j130_pt_1525_higheta, hist_j130_pt_2535_higheta, hist_j130_pt_3550_higheta,
				hist_j130_pt_015_higheta_fJVT, hist_j130_pt_1525_higheta_fJVT, hist_j130_pt_2535_higheta_fJVT, hist_j130_pt_3550_higheta_fJVT, 
				hist_j130_y_015, hist_j130_y_1525, hist_j130_y_2535, hist_j130_y_3550, 
				hist_j130_y_015_fJVT, hist_j130_y_1525_fJVT, hist_j130_y_2535_fJVT, hist_j130_y_3550_fJVT, hist_pass_fJVT, hist_fail_fJVT, 
				hist_j130_pt_015_loweta_fJVT, hist_j130_pt_1525_loweta_fJVT, hist_j130_pt_2535_loweta_fJVT, hist_j130_pt_3550_loweta_fJVT, 
				hist_j130_pt_015_loweta, hist_j130_pt_1525_loweta, hist_j130_pt_2535_loweta, hist_j130_pt_3550_loweta, 
				hist_j130_pt_015_fJVT, hist_j130_pt_1525_fJVT, hist_j130_pt_2535_fJVT, hist_j130_pt_3550_fJVT, 
				hist_j130_pt_015, hist_j130_pt_1525, hist_j130_pt_2535, hist_j130_pt_3550, 
				hist_j150_y_015_fJVT, hist_j150_y_1525_fJVT, hist_j150_y_2535_fJVT, hist_j150_y_3550_fJVT, 
				hist_j150_y_015, hist_j150_y_1525, hist_j150_y_2535, hist_j150_y_3550, 
				hist_j150_pt_015_higheta_fJVT, hist_j150_pt_1525_higheta_fJVT, hist_j150_pt_2535_higheta_fJVT, hist_j150_pt_3550_higheta_fJVT, 
				hist_j150_pt_015_higheta, hist_j150_pt_1525_higheta, hist_j150_pt_2535_higheta, hist_j150_pt_3550_higheta, 
				hist_j150_pt_015_loweta_fJVT, hist_j150_pt_1525_loweta_fJVT, hist_j150_pt_2535_loweta_fJVT, hist_j150_pt_3550_loweta_fJVT, 
				hist_j150_pt_015_loweta, hist_j150_pt_1525_loweta, hist_j150_pt_2535_loweta, hist_j150_pt_3550_loweta, 
				hist_j150_pt_015_fJVT, hist_j150_pt_1525_fJVT, hist_j150_pt_2535_fJVT, hist_j150_pt_3550_fJVT, 
				hist_j150_pt_015, hist_j150_pt_1525, hist_j150_pt_2535, hist_j150_pt_3550,
				hist_j130_y_015_noNorm, hist_j130_y_1525_noNorm, hist_j130_y_2535_noNorm, hist_j130_y_3550_noNorm, 
				hist_j130_y_015_fJVT_noNorm, hist_j130_y_1525_fJVT_noNorm, hist_j130_y_2535_fJVT_noNorm, hist_j130_y_3550_fJVT_noNorm,
				hist_j130_pt_015_fJVT_noNorm, hist_j130_pt_1525_fJVT_noNorm, hist_j130_pt_2535_fJVT_noNorm, hist_j130_pt_3550_fJVT_noNorm, 
				hist_j130_pt_015_noNorm, hist_j130_pt_1525_noNorm, hist_j130_pt_2535_noNorm, hist_j130_pt_3550_noNorm, 
				hist_j150_y_015_fJVT_noNorm, hist_j150_y_1525_fJVT_noNorm, hist_j150_y_2535_fJVT_noNorm, hist_j150_y_3550_fJVT_noNorm, 
				hist_j150_y_015_noNorm, hist_j150_y_1525_noNorm, hist_j150_y_2535_noNorm, hist_j150_y_3550_noNorm, 
				hist_j150_pt_015_fJVT_noNorm, hist_j150_pt_1525_fJVT_noNorm, hist_j150_pt_2535_fJVT_noNorm, hist_j150_pt_3550_fJVT_noNorm, 
				hist_j150_pt_015_noNorm, hist_j150_pt_1525_noNorm, hist_j150_pt_2535_noNorm, hist_j150_pt_3550_noNorm]


for hist in fullHistList:
	hist.Write()

newFile.Write()
newFile.Close()