#! /bin/tcsh
source /uscmst1/prod/sw/cms/setup/cshrc prod
setenv SCRAM_ARCH slc5_amd64_gcc472
cd /uscms_data/d3/tnorbert/MC_GEN/WORKING_RELEASE/CMSSW_6_1_2/src/JetTimingAnalyzer/DPAnalysis 
eval `scramv1 runtime -csh`
cd ${_CONDOR_SCRATCH_DIR}
#cmsRun /uscms_data/d3/tnorbert/MC_GEN/WORKING_RELEASE/CMSSW_6_1_2/src/JetTimingAnalyzer/DPAnalysis/step2_DIGI_L1_DIGI2RAW_HLT_PU.py
cmsRun /uscms_data/d3/tnorbert/MC_GEN/WORKING_RELEASE/CMSSW_6_1_2/src/JetTimingAnalyzer/DPAnalysis/step3_RAW2DIGI_L1Reco_RECO.py
 
 

