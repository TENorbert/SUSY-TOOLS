import FWCore.ParameterSet.Config as cms

process = cms.Process("Analysis")

# run the input file through the end;
# for a limited number of events, replace -1 with the desired number 
#
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load( "SimGeneral.HepPDTESSource.pythiapdt_cfi" )

process.source = cms.Source( "PoolSource",
                             fileNames = cms.untracked.vstring(
			     #'file:../../GMSB_Lambda140_CTau6000_8TeV_pythia6_cff_py_GEN_SIM.root'
			     #'file:../../GMSB_Lambda100_CTau7000_8TeV_pythia6_cff_py_GEN.root'
			     #'file:../../GMSB_Lambda180_CTau6000_8TeV_pythia6_cff_py_GEN.root'
			     #'file:../../GMSB_Lambda180_CTau4000_8TeV_pythia6_cff_py_GEN.root'
			     #'file:../../GMSB_Lambda180_CTau3000_8TeV_pythia6_cff_py_GEN.root'
			    # 'file:../../GMSB_Lambda180_CTau12000_8TeV_pythia6_cff_py_GEN.root'
			     #'file:../../GMSB_Lambda160_CTau250_8TeV_pythia6_cff_py_GEN.root'
			     #'file:../../GMSB_Lambda140_CTau500_8TeV_pythia6_cff_py_GEN.root'
			     #'file:../../GMSB_Lambda120_CTau1000_8TeV_pythia6_cff_py_GEN.root'
			     #'file:../../GMSB_Lambda120_CTau2000_8TeV_pythia6_cff_py_GEN.root'
			    # 'file:../../GMSB_Lambda160_CTau3000_8TeV_pythia6_cff_py_GEN.root'
			    #'file:../../GMSB_Lambda160_CTau4000_8TeV_pythia6_cff_py_GEN.root'
			     #'file:../../GMSB_Lambda160_CTau6000_8TeV_pythia6_cff_py_GEN.root'
			     #'file:../../GMSB_Lambda180_CTau2000_8TeV_pythia6_cff_py_GEN.root'
			     #'file:../../GMSB_Lambda180_CTau1000_8TeV_pythia6_cff_py_GEN.root'
			     #'file:../../GMSB_Lambda180_CTau500_8TeV_pythia6_cff_py_GEN.root'
			    # 'file:../../GMSB_Lambda180_CTau250_8TeV_pythia6_cff_py_GEN.root'
			     #'file:GMSB_Lambda180_CTau6000_8TeV_pythia6_cff_py_GEN_SIM.root'
			     #'file:GMSB_Lambda100_CTau6000_8TeV_Cgrav329_pythia6_cff_py_GEN_SIM.root'
			     #'file:GMSB_Lambda100_CTau20000_8TeV_pythia6_cff_py_GEN_SIM.root'
#'file:GMSB_Lambda160_CTau250_8TeV_pythia6_cff_py_GEN_SIM_Sum12_PU_50ns_RECO.root'

#'file:../../GMSB_Lambda100_CTau4000_8TeV_pythia6_cff_py_GEN_PU.root')
'file:../../GMSB_Lambda300_CTau4000_8TeV_pythia6_cff_py_GEN_PU.root')
#'file:../../GMSB_Lambda140_CTau4000_8TeV_pythia6_cff_py_GEN_PU.root')
#'file:../../GMSB_Lambda160_CTau4000_8TeV_pythia6_cff_py_GEN_PU.root')
#'file:../../GMSB_Lambda180_CTau4000_8TeV_pythia6_cff_py_GEN_PU.root')
#'file:../../GMSB_Lambda220_CTau4000_8TeV_pythia6_cff_py_GEN_PU.root')
#'file:../../GMSB_Lambda260_CTau4000_8TeV_pythia6_cff_py_GEN_PU.root')
#'file:../../GMSB_Lambda300_CTau4000_8TeV_pythia6_cff_py_GEN_PU.root')
)	      
# FileService is mandatory, as the following analyzer module 
# will want it, to create output histogram file 
process.TFileService = cms.Service("TFileService",
        fileName = cms.string("gmsb-L300-Ctau4000.root")
)

# the analyzer itself - empty parameter set 
#
process.TestHepMCEvt = cms.EDAnalyzer("MyGenAnalyzer")

process.p1 = cms.Path( process.TestHepMCEvt )

