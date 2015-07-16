
{

// Attention :
// This example will ONLY work if you execute GenH190... cfg
// with the option of writing edm::Event out (via PoolOutputModule)


// No need for this here anymore, 
// since it already in the rootlogon.C
//
//   gSystem->Load("libFWCoreFWLite") ;
//   AutoLibraryLoader::enable() ;
   
   TFile* f = new TFile("GMSB_Lambda140_CTau6000_8TeV_pythia6_cff_py_GEN_SIM.root") ;
   
   TTree* tevt = f->Get("Events") ;
   
   int nevt = tevt->GetEntries() ;
   std::cout << " Number of Events = " << nevt << std::endl ;
   
   cout << " We will print out some information for the 1st event" << endl ;
   
   
   edm::HepMCProduct EvtProd ;
   TBranch* bhepmc =
      tevt->GetBranch( "edmHepMCProduct_generator__GEN.obj") ;

   bhepmc->SetAddress( & EvtProd ) ;
   
   HepMC::GenEvent*    Evt = 0 ;
   HepMC::GenParticle* Part = 0 ;
   HepMC::GenParticle* daughters = 0 ;
  // int                 NVtx = 0 ;
  // int                 NPrt = 0 ;
   
   HepMC::GenVertex*   NeutDecVtx = 0 ;
   HepMC::GenVertex*   NeutProdVtx = 0 ;
   HepMC::FourVector   NeutDecPos = 0 ;
   HepMC::FourVector   NeutProdPos = 0 ;
   HepMC::FourVector   NeutP4 = 0 ;
   HepMC::GenVertex*   phoVtx = 0 ;
   HepMC::FourVector   phoP4 = 0 ;
   HepMC::FourVector   phoPos = 0 ;
   
   HepMC::GenEvent::particle_iterator pit ;
   HepMC::GenEvent::vertex_iterator vit ;
   HepMC::GenVertex::particle_iterator vpit ;
      
   // Somehow I'm having problems when trying to store (pointers to) selected muons
   // in a containers std::vector<HepMC::GenParticle*> (despite existing dictionary...),
   // thus I'm doing a dirty trick of storing momenta in one container (std::vector) 
   // and the PDG's (for checking charge) in another (TArrayI)
   //
   // I'm still using vector of CLHEP 4-vectors because there's NO dictionary for
   // std::vector<HepMC::FourVector>
   // I'll fix it later   
   //
   //std::vector<CLHEP::HepLorentzVector> StableMuMom ;
      
   //
   // I'm reserving it for 20 int's... I wish it was automatic
   //
   //TArrayI StablePDG(20) ;
   
  // TH1D* Hist2muMass = new TH1D( "Hist2muMass", "test 2-mu mass", 100,  60., 120. ) ;
  // TH1D* Hist4muMass = new TH1D( "Hist4muMass", "test 4-mu mass", 100, 170., 210. ) ;
   
   TH1D* timeNeut = new TH1D( "timeNeut", "Neutralino Ctau", 100,  -5.0, 25.0 ) ;
   TH1D* betaNeut = new TH1D( "betaNeut", "Neutralino Beta=|p|/E", 1000, 0.0, 500.0 ) ;
   TH1D* ptNeut = new TH1D( "ptNeut", "Neutralino Pt", 100,  0.0, 4000.0 ) ;
   TH1D* massNeut = new TH1D( "massNeut", "Neutralino Mass", 100, 0.0, 4000.0 ) ;
   TH1D* eNeut = new TH1D( "eNeut", "Neutralino Energy", 100, 0.0, 4000.0 ) ;

   TH1D* pho_time = new TH1D( "pho_time", " PhoTime= d/beta*C", 100,  -5.0, 25.0 ) ;
   TH1D* pho_pt = new TH1D( "pho_pt", " Pho Pt", 100,  0.0, 4000.0 ) ;
   TH1D* pho_mass = new TH1D( "pho_mass", "Pho Mass", 100, 0.0, 4000.0 ) ;
  
 for ( int iev=0; iev<nevt; iev++ )
   {

      bhepmc->GetEntry(iev) ;
      
      Evt = EvtProd->GetEvent() ;

      if ( iev == 0 ) Evt->print() ;       

      NeutDecVtx = 0 ;
      NeutProdVtx = 0 ;
      phoVtx = 0 ;
      //StableMuMom.clear() ;
      
      for ( pit=Evt->particles_begin(); pit!=Evt->particles_end(); pit++)
      {
	 Part = (*pit) ;
	 if ( ( Part->pdg_id() == 1000022 ) || (Part->status() == 3 ))
	 {
	    NeutDecVtx = Part->end_vertex() ;
	    NeutProdPos = Part->production_vertex()->position() ;
	    NeutDecPos = Part->end_vertex()->position() ;
	    NeutDecP4  = Part->end_vertex()->momentum(); ;
	    if ( NeutDecVtx != 0 )
	    {
	       if ( iev == 0 ) cout << " Found Higgs with valid decay vertex : " 
	                            << NeutDecVtx->barcode() 
		                    << " in event " << iev << endl ;
	       break ;
	    }
	 }
    } 

      if ( NeutDecVtx == 0 )
      {
         cout << "There is NO Higgs in the event " << iev << endl ;
      }
      else
      {  //if found a Neut with stable vertex: Get info:
       
        double Px, Py, Pz, e, m, t_Neut, Pt;
        double Vx, Vy, Vz;
        double pVx, pVy, pVz;
        double px, py, pz, ep, mp, pt, t_pho;
        double vx, vy, vz ;

        Px = NeutDecP4.px() ;
        Py = NeutDecP4.py() ;
        Pz = NeutDecP4.pz() ;
        e  = NeutDecP4.e() ;
        m  = NeutDecP4.m(); // (*it)->generatedMass() ;
        Vx = NeutDecPos.x() ;
        Vy = NeutDecPos.y();
        Vz = NeutDecPos.z();
        pVx = NeutProdPos.x() ;
        pVy = NeutProdPos.y();
        pVz = NeutProdPos.z();
        Pt = sqrt( (Px*Px) + (Py*Py));
        double beta  = (e == 0 )? 0 : sqrt( (Px*Px) + (Py*Py) + (Pz*Pz) ) /e ;
         
	phoVtx = Part->end_vertex() ;
	phoPos = Part->end_vertex()->position() ;
	phoP4  = Part->end_vertex()->momentum(); ;
        // Loop over photons
        for ( pit=Evt->particles_begin(); pit!=Evt->particles_end(); pit++)
	 {
	    daughters = (*pit) ;
	    if ( (abs(daughters->pdg_id()) == 22 ) && (daughters->status() == 1) )
	    {
             px = phoP4.px() ;
             py = phoP4.py() ;
             pz = phoP4.pz() ;
             ep  = phoP4.e() ;
             mp  = phoP4.m(); // (*it)->generatedMass() ;
             vx = phoPos.x() ;
             vy = phoPos.y();
             vz = phoPos.z();
             pt = sqrt( (px*px) + (py*py));

             t_Neut = (NeutDecPos.t() - phoPos.t()) /300.

             t_pho  = sqrt((pVx-Vx) + (pVy-Vy) + (pVz-Vz))/(beta*29979245800);     
	       // here's the "dirty trick" itself, storing info
	       // in 2 differnt containers...
	     /*
	       StableMuMom.push_back( CLHEP::HepLorentzVector(Part->momentum().px(),
	                                                      Part->momentum().py(),
							      Part->momentum().pz(),
							      Part->momentum().e() ) ) ;
	       StablePDG[StableMuMom.size()-1] = Part->pdg_id() ;
	      */
               //Fill Histograms
               pho_time->Fill(t_pho);
               pho_pt->Fill(pt);
               pho_mass->Fill(mp);
              } 
         timeNeut->Fill(t_Neut);
         betaNeut->Fill(bete);
         ptNeut->Fill(Pt);
         massNeut->Fill(m); 
         eNeut->Fill(e);            
	 }
      
      }
      
    //  if ( iev == 0 ) cout << " Found " << StableMuMom.size() << " stable muons" << endl ;
      
     // HepMC::FourVector Mom2mu ;
                  
      

/*
     for ( unsigned int i=0; i<StableMuMom.size(); i++ )
      {
	 for ( unsigned int j=i+1; j<StableMuMom.size(); j++ )
	 {
	    if ( StablePDG.At(i)*StablePDG.At(j) > 0 ) continue ; // skip same charge pairs
	    if ( iev == 0 )
	    {
	       cout << " Stable particles id-s: " << StablePDG.At(i) << " " 
	                                          << StablePDG.At(j) << endl ;
            }				  
	    double XMass2mu = HepMC::FourVector( (StableMuMom[i].px()+StableMuMom[j].px()),
	                                (StableMuMom[i].py()+StableMuMom[j].py()),
		                        (StableMuMom[i].pz()+StableMuMom[j].pz()),
			                (StableMuMom[i].e() +StableMuMom[j].e()) ).m() ;
	    if ( iev == 0 ) cout << " 2-mu inv.mass = " << XMass2mu << endl ;
	    Hist2muMass->Fill( XMass2mu ) ;
	 }
      } 

      
      if ( StableMuMom.size() == 4 )
      {
         double px, py, pz, e ;
	 px=py=pz=e=0. ;
	 for ( unsigned int i=0; i<4; i++ )
	 {
	    //Mom4mu += StableMuMom[i] ;
	    px += StableMuMom[i].px() ;
	    py += StableMuMom[i].py() ;
	    pz += StableMuMom[i].pz() ;
	    e  += StableMuMom[i].e() ;
	 }
	 double XMass4mu = HepMC::FourVector( px, py, pz, e ).m() ;
	 Hist4muMass->Fill( XMass4mu ) ;
         if ( iev == 0 ) cout << " 4-mu inv.mass = " << XMass4mu << endl ;                    
      }

      */


  } // end of loop over events


   
   TCanvas* cnv = new TCanvas("cnv") ;
   
   cnv->Divide(2,1) ;
   
   cnv->cd(1) ;
   Hist2muMass->Draw() ;
   cnv->cd(2) ;
   Hist4muMass->Draw() ;
   
   
}
