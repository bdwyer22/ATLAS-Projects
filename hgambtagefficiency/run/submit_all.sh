#!/bin/bash
rm -rf mc16e.PowhegPy8_NNLOPS_ggH125/
MCtype=(
    # mc16a
    # mc16d
    mc16e
)

listOfSamples=(
    # Sherpa2_diphoton_myy_90_175
    # PowhegPy8EG_NNPDF30_VBFH125
    PowhegPy8_NNLOPS_ggH125
    # PowhegPy8_WmH125J
    # PowhegPy8_WpH125J
    # PowhegPy8_ZH125J
    # PowhegPy8_ggZH125
    # PowhegPy8_bbH125
    # PowhegPy8_ttH125
    # aMCnloHwpp_tWH125_yt_plus1
    )

sampleDir=/afs/cern.ch/user/b/bstamas/work/private/H+HF/samples/

for mctype in "${MCtype[@]}"
do
    for sample in "${listOfSamples[@]}"
    do
        echo AnalysisHGam_RunLocal ${sampleDir}${mctype} $mctype $sample ${mctype}.${sample} 
        AnalysisHGam_RunLocal ${sampleDir}${mctype} $mctype $sample ${mctype}.${sample} 
    done

done
