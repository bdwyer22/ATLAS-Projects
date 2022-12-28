# import argparse
import sys

from AthenaCommon.AthArgumentParser import AthArgumentParser
athArgParser = AthArgumentParser(description="whatever")

athArgParser.add_argument("--myArg",action="store",dest="myArg",help="My help message")

athArgParser.add_argument("--input",   type=str,  required=True, dest="input_file", help="Specify input file as hhbbbb, jz0, jz1, jz2, etc.")
athArgParser.add_argument("--test",   type=bool, required=False, default=False, dest="test_events", help="Flag --test True to only run over 10 events")
athArgParser.add_argument("--local",   type=bool, required=False, default=False, dest="local_test", help="Flag --local True to run over locally downloaded events")
athArgParser.add_argument("--fakes",   type=bool,  required=False, default=False, dest="fakes", help="Flag --fakes True to include fakes")
athArgParser.add_argument("--sm",   type=str,  required=False, default="None", dest="smearing_mode", help="Set the smearing mode as OfflineBased or L1TrackSimBased")
athArgParser.add_argument("--dm",   type=str,  required=False, default="None", dest="detector_mode", help="Set the detector mode as NoPix, MoU, TDR, or Tracking Performance")
athArgParser.add_argument("--randomseed",   type=int,  required=False, default=0, dest="random_seed", help="Set any integer to set the seed")
athArgParser.add_argument("--FakeKillerEnable",   type=bool,  required=False, default=False, dest="enable_fake", help="Set to true to remove broad fakes")
athArgParser.add_argument("--useCoinToss",   type=bool,  required=False, default=False, dest="cointoss", help="Set to enable cointoss")

athArgs = athArgParser.parse_args()

# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input jz0 --sm OB --dm NoPix --local True

# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --fakes True --randomseed 0 --FakeKillerEnable = True |&tee output_RandomSeed0_FakeKillerTrue_wFakes_500.log
# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --fakes True --randomseed 0 |&tee output_Original_wFakes_500.log

# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --fakes True --randomseed 1 --FakeKillerEnable = True |&tee output_RandomSeed1_FakeKillerTrue_wFakes_500.log
# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --fakes True --randomseed 1 |&tee output_RandomSeed1_FakeKillerFalse_wFake_500s.log


# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --randomseed 0 --FakeKillerEnable = True |&tee output_RandomSeed0_FakeKillerTrue_noFakes_500.log
# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --randomseed 0 |&tee output_Original_noFakes_500.log

# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --randomseed 1 --FakeKillerEnable = True |&tee output_RandomSeed1_FakeKillerTrue_noFakes_500.log
# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --randomseed 1 |&tee output_RandomSeed1_FakeKillerFalse_noFakes_500.log


# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --fakes True --randomseed 0 --FakeKillerEnable = True
# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --fakes True --randomseed 0
# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --fakes True --randomseed 1 --FakeKillerEnable = True
# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --fakes True --randomseed 1
# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --randomseed 0 --FakeKillerEnable = True
# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --randomseed 0
# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --randomseed 1 --FakeKillerEnable = True
# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --randomseed 1

input_file = athArgs.input_file
test_events = athArgs.test_events
local_test = athArgs.local_test
setFakes = athArgs.fakes
smearing_mode = athArgs.smearing_mode
detector_mode = athArgs.detector_mode
L1T_RandomSeed = athArgs.random_seed
L1T_FakeKillerEnable = athArgs.enable_fake
L1T_UseCoinToss = athArgs.cointoss


if "bbbb" in input_file or "hh" in input_file or "HH" in input_file:
	setSignal = True

elif "jz0" in input_file or "JZ0" in input_file: 
	setSignal = False

elif "jz1" in input_file or "JZ1" in input_file: 
	setSignal = False

elif "jz2" in input_file or "JZ2" in input_file: 
	setSignal = False

elif "tt" in input_file:
	setSignal = True
else:
	print "Did not recognize the input, exiting.";sys.exit()
#override next line on command line with: --filesInput=XXX
jps.AthenaCommonFlags.FilesInput = [] 
# jps.AthenaCommonFlags.FilesInput = [testFile1,  testFile2,  testFile3,  testFile4,  testFile5,  testFile6,  testFile7,  testFile8,  testFile9,  testFile10,
# 									testFile11, testFile12, testFile13, testFile14, testFile15, testFile16, testFile17, testFile18, testFile19, testFile20, 
# 									testFile21, testFile22, testFile23, testFile24, testFile25, testFile26, testFile27, testFile28, testFile29, testFile30] 
# jps.AthenaCommonFlags.FilesInput = [testFile] 


if local_test:

	# jps.AthenaCommonFlags.FilesInput = ['/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010748.pool.root.1']

	jps.AthenaCommonFlags.FilesInput = ['/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010569.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010570.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010571.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010572.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010573.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010574.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010575.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010576.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010577.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010578.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010579.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010580.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010581.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010582.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010583.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010584.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010585.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010586.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010587.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010588.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010589.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010590.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010591.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010592.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010593.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010594.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010595.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010596.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010597.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010598.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010599.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010600.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010601.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010602.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010603.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010604.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010605.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010606.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010607.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010608.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010609.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010610.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010611.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010612.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010613.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010615.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010616.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010618.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010619.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010620.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010621.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010622.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010623.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010624.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010625.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010626.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010627.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010628.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010629.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010630.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010631.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010647.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010650.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010652.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010653.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010654.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010655.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010656.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010658.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010659.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010662.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010663.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010665.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010666.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010667.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010668.pool.root.1',
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010669.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010670.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010671.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010672.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010673.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010674.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010675.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010676.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010677.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010678.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010679.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010680.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010681.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010682.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010683.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010684.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010685.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010686.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010687.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010688.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010689.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010690.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010691.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010692.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010693.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010694.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010695.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010696.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010697.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010698.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010699.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010700.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010701.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010702.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010703.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010704.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010705.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010706.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010707.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010708.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010709.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010710.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010711.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010712.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010713.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010714.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010715.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010716.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010717.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010718.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010719.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010720.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010721.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010725.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010728.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010729.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010730.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010731.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010732.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010733.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010734.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010735.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010737.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010738.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010739.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010740.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010741.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010742.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010743.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010744.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010745.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010746.pool.root.1', 
	'/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010747.pool.root.1', '/afs/cern.ch/user/b/bstamas/eos/httOutputs/jz0_in/mc15_14TeV/AOD.21146655._010748.pool.root.1']

	# jps.AthenaCommonFlags.FilesInput =['/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000101.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000180.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000227.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000232.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000277.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000279.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000377.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000453.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000476.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000616.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000657.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000661.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000681.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000719.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000774.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000800.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000920.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._000974.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001017.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001024.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001196.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001218.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001246.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001312.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001320.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001336.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001401.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001435.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001439.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001470.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001487.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001604.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001641.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001649.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001660.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001662.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001670.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001703.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001734.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001894.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001927.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._001959.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._002036.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._002070.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._002087.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._002132.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._002146.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._002154.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._002233.pool.root.1',
	# '/eos/atlas/atlascerngroupdisk/det-htt/HTTSim/HTTRefit/data/Marianna_sample/mc15_14TeV.450000.aMcAtNloHerwig7EvtGen_UEEE5_CTEQ6L1_CT10ME_hh_bbbb.recon.AOD.e7772_s3490_s3491_r11672/AOD.21146668._002256.pool.root.1']
#Specify AccessMode (read mode) ... ClassAccess is good default for xAOD
jps.AthenaCommonFlags.AccessMode = "ClassAccess" 


# Create the algorithm's configuration.
from AnaAlgorithm.DualUseConfig import createAlgorithm
alg = createAlgorithm ( 'MultiJetHTTxAODAnalysis', 'AnalysisAlg' )

alg.FlatTrackInefficiency = 0.05
alg.TrackPtCut = 4.0 # GeV 
alg.SmearFactor = 1.0

alg.isfixedwindow = True
alg.isHTTtracks = True
alg.isleadingtracks = False

alg.isSignal = setSignal
alg.SetRandomSeed = L1T_RandomSeed
alg.EnableFakeKiller = L1T_FakeKillerEnable
L1T_IncludeDuplicatesAndFakes = setFakes

#DetectorMode
# 0 NOPIX
# 1 MOU2in
# 2 Minimal
# 3 forward
# 4 forward_upgrade
# 5 tracking_perf
# 6 Modified_Baseline
# L1T_DetectorMode=[0,1,5,6]

if "NOPIX" in detector_mode or "NoPix" in detector_mode or "nopix" in detector_mode:
	L1T_DetectorMode=[0]; alg.geometry = "NoPix"
elif "MoU" in detector_mode or "MOU" in detector_mode or "mou" in detector_mode:
	L1T_DetectorMode=[1]; alg.geometry = "MoU2in"
elif "TDR" in detector_mode or "tdr" in detector_mode:
	L1T_DetectorMode=[1]; alg.geometry = "TDR"
elif "tracking" in detector_mode or "Tracking" in detector_mode or "TP" in detector_mode:
	L1T_DetectorMode=[5]; alg.geometry = "tracking_perf"
elif "Modified" in detector_mode or "modified" in detector_mode or "MB" in detector_mode:
	L1T_DetectorMode=[6]; alg.geometry = "Modified_Baseline"
elif "None" in detector_mode :
	print "No detector mode, using offline tracks"
	alg.geometry = "Nominal"
else:
	print "Did not recognize the detector mode, exiting.";sys.exit()

# Smearing mode:
# 0 OfflineBased
# 1 L1TrackSimBased
# 2 L1TrackSimBasedWithOfflinePtDependency
# L1T_SmearingMode=[0,2]
# L1T_SmearingMode=[0]

if "Offline" in smearing_mode or "offline" in smearing_mode or "OB" in smearing_mode:
	L1T_SmearingMode=[0]
elif "L1T" in smearing_mode or "l1t" in smearing_mode:
	L1T_SmearingMode=[1]
else:
	print "Not smearing, using offline tracks"


if (alg.isfixedwindow):
	window = "_fixedwindow"
else:
	window = ""

if (alg.isHTTtracks):
	tracktype = "_HTT_"+str(alg.geometry)
else:
	tracktype = ""

if (alg.isleadingtracks):
	tracks = "_leadingtrk"
else:
	tracks = "_alltrk"
samplename=str(input_file)
# if "hh_bbbb" in testFile1:
# 	# alg.isSignal = True 
# 	samplename = "hhbbbb"
# else:
# 	# alg.isSignal = False
# 	if "JZ0" in testFile1:
# 		samplename = "JZ0"
# 	if "JZ1" in testFile1:
# 		samplename = "JZ1"
# 	if "JZ2" in testFile1:
# 		samplename = "JZ2"
# 	if "JZ3" in testFile1:
# 		samplename = "JZ3"
# 	if "JZ4" in testFile1:
# 		samplename = "JZ4"

# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --fakes True --randomseed 0 --FakeKillerEnable = True |&tee output_RandomSeed0_FakeKillerTrue_wFakes_500.log
# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --fakes True --randomseed 0 |&tee output_Original_wFakes_500.log

# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --fakes True --randomseed 1 --FakeKillerEnable = True |&tee output_RandomSeed1_FakeKillerTrue_wFakes_500.log
# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --fakes True --randomseed 1 |&tee output_RandomSeed1_FakeKillerFalse_wFake_500s.log


# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --randomseed 0 --FakeKillerEnable = True |&tee output_RandomSeed0_FakeKillerTrue_noFakes_500.log
# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --randomseed 0 |&tee output_Original_noFakes_500.log

# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --randomseed 1 --FakeKillerEnable = True |&tee output_RandomSeed1_FakeKillerTrue_noFakes_500.log
# athena MultiJetHTTAnalysis/ATestRun_jobOptions.py - --input hhbbbb --sm OB --dm NoPix --local True --randomseed 1 |&tee output_RandomSeed1_FakeKillerFalse_noFakes_500.log




if L1T_RandomSeed != 0:
	addition1 = "_RandomSeed"+str(L1T_RandomSeed)
addition2 = ""
if L1T_FakeKillerEnable == True:
	addition2 = "_FakeKillerTrue"
if L1T_FakeKillerEnable == False:
	if L1T_RandomSeed == 0:
		addition1 = "_Original"
if L1T_UseCoinToss == True:
	addition1 = "_CoinToss"


svcMgr.THistSvc.MaxFileSize=-1 #speeds up jobs that output lots of histograms

SmearingMode=["OfflineBased","L1TrackSimBased","L1TrackSimBasedWithOfflinePtDependency"]
DMode=["NOPIX","MOU2in","Minimal","forward","forward_upgrade","tracking_perf","Modified_Baseline"]

#### Configure L1TrackSmearingAlg
L1T_InputTrackContainerName="InDetTrackParticles"

if L1T_IncludeDuplicatesAndFakes:
	isFake = "wFakes"
else:
	isFake = "noFakes"
jps.AthenaCommonFlags.HistOutputs = ["ANALYSIS:MyxAODAnalysis.outputs_"+samplename+"_4j_asymm_"+tracktype+addition1+addition2+"_"+isFake+".root"]

from OutputStreamAthenaPool.MultipleStreamManager import MSMgr
	
if (alg.isHTTtracks):
	for DM in L1T_DetectorMode:
	   for SM in L1T_SmearingMode:

	      L1TParamName=DMode[DM]+"_"+SmearingMode[SM]
	      if L1T_IncludeDuplicatesAndFakes:
	         L1TParamName=L1TParamName+"_wFakes"
	      else:
	         L1TParamName=L1TParamName+"_noFakes"

	      rootStreamName = "L1TrackSmearingAlgStream_"
	      rootFileName   = "L1TrackSmearingAlg_"+L1TParamName+".root" 
	      L1T_OutputTrackContainerName = "L1TrackLikeTracks_"+DMode[DM]+"_"+SmearingMode[SM]
	      L1TrackSmearingAlgInstanceName="L1TrackSmearingAlg_"+DMode[DM]+"_"+SmearingMode[SM]
	      athAlgSeq += CfgMgr.L1TrackSmearingAlg (
	         L1TrackSmearingAlgInstanceName,
	         OutputLevel = INFO,
	         OutputTrackContainerName = L1T_OutputTrackContainerName,
	         InputTrackContainerName = L1T_InputTrackContainerName,
	         SmearingMode=SM,
	         DetectorMode=DM,
	         RandomSeed=L1T_RandomSeed,
	         FakeKillerEnable=L1T_FakeKillerEnable,
	         IncludeDuplicatesAndFakes=L1T_IncludeDuplicatesAndFakes,
	         UseCoinToss=L1T_UseCoinToss,
	         RootStreamName=rootStreamName
	      )
	      histoxAODStream = MSMgr.NewRootStream( rootStreamName, rootFileName )

	alg.OutputTrackContainerName = "L1TrackLikeTracks_"+DMode[L1T_DetectorMode[0]]+"_"+SmearingMode[L1T_SmearingMode[0]]

athAlgSeq += alg

# limit the number of events (for testing purposes)
# theApp.EvtMax = 100
svcMgr.MessageSvc.defaultLimit = 9999999
# svcMgr.MessageSvc.OutputLevel = DEBUG
# optional include for reducing printout from athena
include("AthAnalysisBaseComps/SuppressLogging.py")