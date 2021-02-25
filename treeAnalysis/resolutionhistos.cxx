
// ANCHOR debug output verbosity
Int_t verbosityRH = 2;

// ANCHOR create histograms globally
TH2F*  h_pion_fhcal_E 	= new TH2F("h_pion_fhcal_E", "", 120, 0,60, 100, 0, 2);

// ANCHOR main function to be called in event loop
void resolutionhistos(){


  for(Int_t iclus=0; iclus<_nclusters_FHCAL; iclus++){
    // if(verbosityRH>1) cout << "\tFHCAL: cluster " << iclus << "\twith E = " << _cluster_FHCAL_E[iclus] << " GeV" << endl;
    // if(verbosityRH>1) cout << "\tFHCAL: cluster MC ID " << _cluster_FHCAL_trueID[iclus] << endl;

    // cluster should have at least 2 towers
    if(_cluster_FHCAL_NTower[iclus]<2) continue;

    // loop over MC particles
    for(Int_t imc=0; imc<_nMCPart; imc++){

      // find true MC particle for given cluster
      if(_cluster_FHCAL_trueID[iclus]==_mcpart_ID[imc]){
        // if(verbosityRH>1) cout << "\tfound MC:  particle " << imc << "\twith E = " << _mcpart_E[imc] << " GeV" << endl;

        h_pion_fhcal_E->Fill(_mcpart_E[imc],_cluster_FHCAL_E[iclus]/_mcpart_E[imc]);
      }
    }
  }

}

// ANCHOR save function after event loop
void resolutionhistosSave(){
  // make output directory
  gSystem->Exec("mkdir -p treeProcessing/resolutionhistos");
  // define output file
  TFile* fileOutput = new TFile("treeProcessing/resolutionhistos/output_RH.root","RECREATE");

  // write histograms
  h_pion_fhcal_E->Write();

  // write output file
  fileOutput->Write();
  fileOutput->Close();
}