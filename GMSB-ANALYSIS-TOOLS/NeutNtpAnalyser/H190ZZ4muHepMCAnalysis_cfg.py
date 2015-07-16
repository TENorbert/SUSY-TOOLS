import FWCore.ParameterSet.Config as cms

process = cms.Process("Analysis")

# run the input file through the end;
# for a limited number of events, replace -1 with the desired number 
#
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load( "SimGeneral.HepPDTESSource.pythiapdt_cfi" )

process.source = cms.Source( "PoolSource",
                             fileNames = cms.untracked.vstring(
			     #'file:PythiaH190ZZ4mu_cfi_py_GEN.root'
			     'file:GMSB_Lambda140_CTau6000_8TeV_pythia6_cff_py_GEN_SIM.root'
			     #'file:/uscms_data/d3/tnorbert/MC_GEN/WORKING_RELEASE/CMSSW_6_1_2/src/GMSB_Lambda140_CTau6000_8TeV_pythia6_cff_py_GEN.root'
			     )
                           )
	      
# FileService is mandatory, as the following analyzer module 
# will want it, to create output histogram file
# 
process.TFileService = cms.Service("TFileService",
        fileName = cms.string("Neutralino2ZGMass.root")
)

# the analyzer itself - empty parameter set 
#
process.TestHepMCEvt = cms.EDAnalyzer( "HZZ4muExampleAnalyzer" )

process.p1 = cms.Path( process.TestHepMCEvt )

