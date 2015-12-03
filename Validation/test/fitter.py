import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing
import sys

options = VarParsing('analysis')

options.register(
    "isMC",
    True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Compute MC efficiencies"
    )

options.register(
    "inputFileName",
    "TnPTree_mc.root",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Input filename"
    )

options.register(
    "outputFileName",
    "test",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output filename"
    )

options.register(
    "idName",
    "passingTight",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "ID variable name as in the fitter_tree"
    )

options.register(
    "dirName",
    "GsfElectronToRECO",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Folder name containing the fitter_tree"
    )

options.register(
    "doCutAndCount",
    True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Perform cut and count efficiency measurement"
    )

options.parseArguments()


process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

################################################

InputFileName = options.inputFileName
OutputFile = "efficiency-mc-"+options.idName
if (not options.isMC):
    OutputFile = "efficiency-data-"+options.idName

if (options.outputFileName != ""):
    OutputFile = OutputFile+"-"+options.outputFileName+".root"
else:
    OutputFile = OutputFile+".root"

################################################

EfficiencyBins = cms.PSet(
    #probe_sc_et = cms.vdouble( 20.,22.5, 25. ,27.5, 30.,33.33, 35., 40., 45., 50., 60., 70., 90., 130., 180.,250. ),
#    event_nPV = cms.vdouble( 0,2,4,6,8,10,12,14,16,18,20,30),
    probe_sc_eta = cms.vdouble( -3.0,-2.5,-2.2,-1.9,-1.75,-1.566,-1.444,-1.2,-1.0,-0.8,-0.5,-0.25,0,0.25,0.5,0.8,1.0,1.2,1.444,1.566,1.75,1.9,2.2, 2.5,3.0 ),
    probe_sc_et = cms.vdouble( 33.3333,250. ),
    #probe_sc_abseta = cms.vdouble( 0,0.25,0.5,0.8,1.0,1.2,1.444,1.566,1.75,1.9,2.2, 2.5 ),
    #probe_sc_eta = cms.vdouble( -2.5, 0.0, 2.5 ),
    )

EfficiencyBinningSpecification = cms.PSet(
    UnbinnedVariables = cms.vstring("mass", "totWeight", "Ele_dRTau", "probe_dRTau"),
    BinnedVariables = cms.PSet(EfficiencyBins,
                               mcTrue = cms.vstring("true")
                               ),
    BinToPDFmap = cms.vstring("pdfSignalPlusBackground")  
    )

if (not options.isMC):
    EfficiencyBinningSpecification.UnbinnedVariables = cms.vstring("mass")
    EfficiencyBinningSpecification.BinnedVariables = cms.PSet(EfficiencyBins)

mcTruthModules = cms.PSet()
if (options.isMC):
    setattr(mcTruthModules, "MCtruth_" + options.idName, cms.PSet(EfficiencyBinningSpecification))
    setattr(getattr(mcTruthModules, "MCtruth_" + options.idName), "EfficiencyCategoryAndState", cms.vstring(options.idName, "pass"))

############################################################################################

process.TnPMeasurement = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
                                        InputFileNames = cms.vstring(InputFileName),
                                        InputDirectoryName = cms.string(options.dirName),
                                        InputTreeName = cms.string("fitter_tree"), 
                                        OutputFileName = cms.string(OutputFile),
                                        NumCPU = cms.uint32(1),
                                        SaveWorkspace = cms.bool(False), #VERY TIME CONSUMING FOR MC
                                        doCutAndCount = cms.bool(options.doCutAndCount),
                                        floatShapeParameters = cms.bool(True),
                                        binnedFit = cms.bool(True),
                                        binsForFit = cms.uint32(60),
                                        #WeightVariable = cms.string("totWeight"),
                                        #fixVars = cms.vstring("meanP", "meanF", "sigmaP", "sigmaF", "sigmaP_2", "sigmaF_2"),
                                        
                                        # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
                                        Variables = cms.PSet(mass = cms.vstring("Tag-Probe Mass", "70.0", "110.0", "GeV/c^{2}"),
                                                             probe_sc_eta = cms.vstring("Probe #eta", "-2.5", "2.5", ""), 
                                                             event_nPV = cms.vstring("nvtx ", "0", "30", ""), 
                                                             probe_sc_et = cms.vstring("Probe E_{T}", "33.333", "1000", "GeV/c"),
                                                             #totWeight = cms.vstring("totWeight", "-1000000000", "100000000", ""),
                                                             #Ele_dRTau = cms.vstring("Ele_dRTau", "0.2", "100000", ""),
                                                             #probe_dRTau = cms.vstring("probe_dRTau", "0.2", "100000", ""),
                                                             ),
                                        
                                        # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
                                        Categories = cms.PSet(),
                                        
                                        # defines all the PDFs that will be available for the efficiency calculations; 
                                        # uses RooFit's "factory" syntax;
                                        # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" 
                                        # and "signalFractionInPassing[0.9]" are used for initial values  
                                        PDFs = cms.PSet(pdfSignalPlusBackground = cms.vstring(
            "RooCBExGaussShape::signalResPass(mass,meanP[-0.0,-5.000,5.000],sigmaP[0.956,0.00,10.000],alphaP[0.999, 0.0,50.0],nP[2.405,0.000,50.000],sigmaP_2[1.000,0.500,15.00])",
            "RooCBExGaussShape::signalResFail(mass,meanF[-0.0,-5.000,5.000],sigmaF[0.010,0.00,10.000],alphaF[1.112, 0.0,50.0],nF[1.987,0.000,30.00], sigmaF_2[2.675,0.500,12.000])",
            "ZGeneratorLineShape::signalPhy(mass, \"..\/..\/..\/PhysicsTools\/TagAndProbe\/data\/ZeeGenLevel.root\")", 
            "RooCMSShape::backgroundPass(mass, alphaPass[60.,50.,70.], betaPass[0.001, 0.,0.1], gammaPass[0.1, 0, 1], peakPass[90.0])",
            "RooCMSShape::backgroundFail(mass, alphaFail[60.,50.,70.], betaFail[0.100, 0.,0.1], gammaFail[0.7, 0, 1], peakFail[90.0])",
            "FCONV::signalPass(mass, signalPhy, signalResPass)",
            "FCONV::signalFail(mass, signalPhy, signalResFail)",     
            "efficiency[0.5,0,1]",
            "signalFractionInPassing[1.0]"     
            ),
                                                        ),
                                        
                                        # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
                                        # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
                                        Efficiencies = cms.PSet(mcTruthModules)
                                        )

setattr(process.TnPMeasurement.Categories, options.idName, cms.vstring(options.idName, "dummy[pass=1,fail=0]"))
setattr(process.TnPMeasurement.Categories, "mcTrue", cms.vstring("MC true", "dummy[true=1,false=0]"))

if (not options.isMC):
    for pdf in process.TnPMeasurement.PDFs.__dict__:
        param =  process.TnPMeasurement.PDFs.getParameter(pdf)
        if (type(param) is not cms.vstring):
            continue
        for i, l in enumerate(getattr(process.TnPMeasurement.PDFs, pdf)):
            if l.find("signalFractionInPassing") != -1:
                getattr(process.TnPMeasurement.PDFs, pdf)[i] = l.replace("[1.0]","[0.5,0.,1.]")
        
    setattr(process.TnPMeasurement.Efficiencies, options.idName, EfficiencyBinningSpecification)    
    setattr(getattr(process.TnPMeasurement.Efficiencies, options.idName) , "EfficiencyCategoryAndState", cms.vstring(options.idName, "pass"))
else:
    for pdf in process.TnPMeasurement.PDFs.__dict__:
        param =  process.TnPMeasurement.PDFs.getParameter(pdf)
        if (type(param) is not cms.vstring):
            continue
        for i, l in enumerate(getattr(process.TnPMeasurement.PDFs, pdf)):
            if l.find("backgroundPass") != -1:
                getattr(process.TnPMeasurement.PDFs, pdf)[i] = "RooPolynomial::backgroundPass(mass, a[0.0])"
            if l.find("backgroundFail") != -1:
                getattr(process.TnPMeasurement.PDFs, pdf)[i] = "RooPolynomial::backgroundFail(mass, a[0.0])"

process.fit = cms.Path(
    process.TnPMeasurement  
    )

