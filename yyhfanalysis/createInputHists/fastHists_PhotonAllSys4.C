void checkDijet(TH1F * histbb, TH1F * histbc, TH1F * histbl, TH1F * histcc, TH1F * histcl, TH1F * histll, 
				float HGamWeight, float XSWeight, float lumi_mc16, float sumweights, bool isPassed, int LeadJet_truthlabel, 
				int SubLeadJet_truthlabel, int LeadJet_btagbin, int SubLeadJet_btagbin, int Njet_central, float yyHFjj_weight, float yyHF_met, 
				int nElectrons, int nMuons, float m_yy) {
	// cout << "in checkDijet" << endl;

	// cout << "is passed? " << isPassed << endl;

	if (isPassed == true){
		// cout << "in isPassed" << endl;

		int nLeptons = nMuons + nElectrons;
		float eventweight = (XSWeight * HGamWeight * lumi_mc16) / sumweights;
		int expanded_binning = LeadJet_btagbin * 5 + SubLeadJet_btagbin;

		if (SubLeadJet_truthlabel > -1){
			// cout << "has 2nd jet" << endl;
			// cout << nLeptons << endl;
			if ((LeadJet_btagbin == 4 && SubLeadJet_btagbin == 4) || (LeadJet_btagbin == 4 && SubLeadJet_btagbin == 3) || (LeadJet_btagbin == 3 && SubLeadJet_btagbin == 4) || (LeadJet_btagbin == 3 && SubLeadJet_btagbin == 3) || nLeptons == 0){
				// cout << "passes lep" << endl;
				if   (nLeptons > 0 && expanded_binning == 24 && yyHF_met < 40){expanded_binning = 25;}
				if   (nLeptons > 0 && expanded_binning == 23 && yyHF_met < 40){expanded_binning = 25;}
				if   (nLeptons > 0 && expanded_binning == 18 && yyHF_met < 40){expanded_binning = 25;}
				if   (nLeptons > 0 && expanded_binning == 19 && yyHF_met < 40){expanded_binning = 25;}

				// bool METpass; 

				// if (expanded_binning > 24){
				// 	METpass = true;
				// }

				// else if (yyHF_met < 60){ 
				// 	METpass = true;
				// }
				// else{
				// 	METpass = false;}

				// if (METpass == true){
					// if (LeadJet_truthlabel == 5 && SubLeadJet_truthlabel == 5):   //bb
					// 	FillHists(histbb_wHiggs,variation,expanded_binning,eventweight*extraWeight)
					// elif (LeadJet_truthlabel == 5 && SubLeadJet_truthlabel == 4): //bc
					// 	FillHists(histbc_wHiggs,variation,expanded_binning,eventweight*extraWeight)
					// elif (LeadJet_truthlabel == 4 && SubLeadJet_truthlabel == 5): //cb
					// 	FillHists(histbc_wHiggs,variation,expanded_binning,eventweight*extraWeight)
					// elif (LeadJet_truthlabel == 5 || SubLeadJet_truthlabel == 5):  //bl
					// 	FillHists(histbl_wHiggs,variation,expanded_binning,eventweight*extraWeight)
					// elif (LeadJet_truthlabel == 4 && SubLeadJet_truthlabel == 4): //cc
					// 	FillHists(histcc_wHiggs,variation,expanded_binning,eventweight*extraWeight)
					// elif (LeadJet_truthlabel == 4 || SubLeadJet_truthlabel == 4):  //cl
					// 	FillHists(histcl_wHiggs,variation,expanded_binning,eventweight*extraWeight)
					// else:
					// 	FillHists(histll_wHiggs,variation,expanded_binning,eventweight*extraWeight) 
					// cout << "higgs mass: " << m_yy << endl;

					if (m_yy * 0.001 < 121 || m_yy * 0.001 > 129){  // exclude higgs window
						// cout << "passes higgs" << endl;
						if (LeadJet_truthlabel == 5 && SubLeadJet_truthlabel == 5){   //bb
							histbb->Fill(expanded_binning,eventweight*yyHFjj_weight);}
						else if (LeadJet_truthlabel == 5 && SubLeadJet_truthlabel == 4){ //bc
							histbc->Fill(expanded_binning,eventweight*yyHFjj_weight);}
						else if (LeadJet_truthlabel == 4 && SubLeadJet_truthlabel == 5){ //cb
							histbc->Fill(expanded_binning,eventweight*yyHFjj_weight);}
						else if (LeadJet_truthlabel == 5 || SubLeadJet_truthlabel == 5){  //bl
							histcl->Fill(expanded_binning,eventweight*yyHFjj_weight);}
						else if (LeadJet_truthlabel == 4 && SubLeadJet_truthlabel == 4){ //cc
							histcc->Fill(expanded_binning,eventweight*yyHFjj_weight);}
						else if (LeadJet_truthlabel == 4 || SubLeadJet_truthlabel == 4){  //cl
							histcl->Fill(expanded_binning,eventweight*yyHFjj_weight);}
						else{
							histll->Fill(expanded_binning,eventweight*yyHFjj_weight);
						}
					}
				// }
			}
		}
		// if (SubLeadJet_truthlabel > -1){
		// 	if ((LeadJet_btagbin == 4 and SubLeadJet_btagbin == 4) or (LeadJet_btagbin == 4 and SubLeadJet_btagbin == 3) or (LeadJet_btagbin == 3 and SubLeadJet_btagbin == 3) or nLeptons == 0):

		// 		hist_HGeventweight.Fill(eventweight)
		// 		hist_fulleventweight.Fill(eventweight*extraWeight)
		// 		if   (nLeptons > 0 and expanded_binning == 24 and Njet_central <= 4): expanded_binning = 25
		// 		elif (nLeptons > 0 and expanded_binning == 24 and Njet_central > 4): expanded_binning = 26
		// 		if   (nLeptons > 0 and expanded_binning == 23 and Njet_central <= 4): expanded_binning = 25
		// 		elif (nLeptons > 0 and expanded_binning == 23 and Njet_central > 4): expanded_binning = 26
		// 		if   (nLeptons > 0 and expanded_binning == 18 and Njet_central <= 4): expanded_binning = 25
		// 		elif (nLeptons > 0 and expanded_binning == 18 and Njet_central > 4): expanded_binning = 26
		// 		// eventweight = 1;extraWeight=1

		// 		if (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 5):   //bb
		// 			FillHists(histbb_wHiggs_noMET,variation,expanded_binning,eventweight*extraWeight)
		// 		elif (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 4): //bc
		// 			FillHists(histbc_wHiggs_noMET,variation,expanded_binning,eventweight*extraWeight)
		// 		elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 5): //cb
		// 			FillHists(histbc_wHiggs_noMET,variation,expanded_binning,eventweight*extraWeight)
		// 		elif (LeadJet_truthlabel == 5 or SubLeadJet_truthlabel == 5):  //bl
		// 			FillHists(histbl_wHiggs_noMET,variation,expanded_binning,eventweight*extraWeight)
		// 		elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 4): //cc
		// 			FillHists(histcc_wHiggs_noMET,variation,expanded_binning,eventweight*extraWeight)
		// 		elif (LeadJet_truthlabel == 4 or SubLeadJet_truthlabel == 4):  //cl
		// 			FillHists(histcl_wHiggs_noMET,variation,expanded_binning,eventweight*extraWeight)
		// 		else:
		// 			FillHists(histll_wHiggs_noMET,variation,expanded_binning,eventweight*extraWeight) 

		// 		if (m_yy < 121 or m_yy > 129):  // exclude higgs window
		// 			if (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 5):   //bb
		// 				FillHists(histbb_noMET,variation,expanded_binning,eventweight*extraWeight)
		// 			elif (LeadJet_truthlabel == 5 and SubLeadJet_truthlabel == 4): //bc
		// 				FillHists(histbc_noMET,variation,expanded_binning,eventweight*extraWeight)
		// 			elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 5): //cb
		// 				FillHists(histbc_noMET,variation,expanded_binning,eventweight*extraWeight)
		// 			elif (LeadJet_truthlabel == 5 or SubLeadJet_truthlabel == 5):  //bl
		// 				FillHists(histbl_noMET,variation,expanded_binning,eventweight*extraWeight)
		// 			elif (LeadJet_truthlabel == 4 and SubLeadJet_truthlabel == 4): //cc
		// 				FillHists(histcc_noMET,variation,expanded_binning,eventweight*extraWeight)
		// 			elif (LeadJet_truthlabel == 4 or SubLeadJet_truthlabel == 4):  //cl
		// 				FillHists(histcl_noMET,variation,expanded_binning,eventweight*extraWeight)
		// 			else:
		// 				FillHists(histll_noMET,variation,expanded_binning,eventweight*extraWeight) 	
		// }
	}// isPassed
}//end function

void checkSingleJet(TH1F * histb, TH1F * histc, TH1F * histl,
				float HGamWeight, float XSWeight, float lumi_mc16, float sumweights, bool isPassed, int LeadJet_truthlabel, 
				int LeadJet_btagbin, int Njet_central, float yyHFj_weight, float yyHF_met, 
				int nElectrons, int nMuons, float m_yy) {
	if (isPassed == true){
		int nLeptons = nMuons + nElectrons;
		float eventweight = (XSWeight * HGamWeight * lumi_mc16) / sumweights;

		// if (nLeptons == 0 and yyHF_met < 40): 
		// 	if (LeadJet_truthlabel == 5):
		// 		FillHists(histb_wHiggs,variation,LeadJet_btagbin,eventweight*extraWeight)
		// 	elif (LeadJet_truthlabel == 4):
		// 		FillHists(histc_wHiggs,variation,LeadJet_btagbin,eventweight*extraWeight)
		// 	else:
		// 		FillHists(histl_wHiggs,variation,LeadJet_btagbin,eventweight*extraWeight) 

		// if (nLeptons == 0): 
		// 	if (LeadJet_truthlabel == 5):
		// 		FillHists(histb_wHiggs_noMET,variation,LeadJet_btagbin,eventweight*extraWeight)
		// 	elif (LeadJet_truthlabel == 4):
		// 		FillHists(histc_wHiggs_noMET,variation,LeadJet_btagbin,eventweight*extraWeight)
		// 	else:
		// 		FillHists(histl_wHiggs_noMET,variation,LeadJet_btagbin,eventweight*extraWeight) 

		if (m_yy * 0.001 < 121 or m_yy * 0.001 > 129){  // exclude higgs window
			// if (nLeptons == 0 and yyHF_met < 40): 
			// 	if (LeadJet_truthlabel == 5):
			// 		FillHists(histb,variation,LeadJet_btagbin,eventweight*extraWeight)
			// 	elif (LeadJet_truthlabel == 4):
			// 		FillHists(histc,variation,LeadJet_btagbin,eventweight*extraWeight)
			// 	else:
			// 		FillHists(histl,variation,LeadJet_btagbin,eventweight*extraWeight) 
			if (nLeptons == 0){
				if (LeadJet_truthlabel == 5){
					histb->Fill(LeadJet_btagbin,eventweight*yyHFj_weight);}
				else if (LeadJet_truthlabel == 4){
					histc->Fill(LeadJet_btagbin,eventweight*yyHFj_weight);}
				else{
					histl->Fill(LeadJet_btagbin,eventweight*yyHFj_weight);}
			}
		}
	}

}

void makeInputHists()
{
	std::vector<TString> systematicType = {"PhotonAllSys4"};//, "JetSys2", "JetSys3",   "JetSys4"};
	std::vector<TString> mcType = {"mc16a", "mc16d", "mc16e"};

	for(TString sys : systematicType){
		for(TString mc : mcType){
			int nInputs;
			if (mc == "mc16a"){nInputs = 11;}
			if (mc == "mc16d"){nInputs = 15;}
			if (mc == "mc16e"){nInputs = 22;}
			for (int num = 0; num < nInputs; num++){
				TString inputFile = "/xdata/bstamas/yyhf/inputHistMaker/newInputs/Sherpa2_diphoton_myy_90_175_AF2/"+sys+"/"+mc+"/yyHF_skimMxAODs_Sherpa2_diphoton_myy_90_175_AF2_"+mc+"_"+sys+"_"+num+".root";

				cout << "running over file " << inputFile << endl;

				TFile *myFile = new TFile(inputFile, "READ") ;

				TString cutflowPath = "cutflows/"+sys+"/"+mc+".CutFlow_Sherpa2_diphoton_myy_90_175_AF2.root";
				TString cutlfow_name = "hist_cutflow_noDalitz_weighted";
				TFile *myCutflowFile = new TFile(cutflowPath, "READ");

				TH1F *myCutflow = new TH1F("myCutflow", "myCutflow", 15, 0, 15);
				myCutflow =  (TH1F*)myCutflowFile->Get(cutlfow_name);


				TTree *myTree = (TTree*)myFile->Get("CollectionTree");

				TString output_name("yyHF_fastHists_Sherpa2_diphoton_myy_90_175_AF2_"+sys+"_"+mc+"_"+num+".root");

				int nEntries = myTree->GetEntries();
				// myTree->SetBranchStatus("*", 0);
				cout << sys+"_"+mc+"_0 nEntries:  " << nEntries << endl;

				float XSWeight; myTree->SetBranchAddress("XSWeight", &XSWeight);

				int EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN0__1down_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.isPassed",                    &EG_SCALE_MATCRYO__ETABIN0__1down_isPassed);
				float EG_SCALE_MATCRYO__ETABIN0__1down_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN0__1down_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN0__1down_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN0__1down_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN0__1down_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.m_yy",                        &EG_SCALE_MATCRYO__ETABIN0__1down_m_yy);
				float EG_SCALE_MATCRYO__ETABIN0__1down_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN0__1down_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN0__1down_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN0__1down_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN0__1down_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN0__1down_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1down.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN0__1up_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.isPassed",                    &EG_SCALE_MATCRYO__ETABIN0__1up_isPassed);
				float EG_SCALE_MATCRYO__ETABIN0__1up_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN0__1up_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN0__1up_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN0__1up_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN0__1up_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.m_yy",                        &EG_SCALE_MATCRYO__ETABIN0__1up_m_yy);
				float EG_SCALE_MATCRYO__ETABIN0__1up_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN0__1up_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN0__1up_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN0__1up_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN0__1up_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN0__1up_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN0__1up.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN1__1down_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.isPassed",                    &EG_SCALE_MATCRYO__ETABIN1__1down_isPassed);
				float EG_SCALE_MATCRYO__ETABIN1__1down_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN1__1down_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN1__1down_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN1__1down_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN1__1down_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.m_yy",                        &EG_SCALE_MATCRYO__ETABIN1__1down_m_yy);
				float EG_SCALE_MATCRYO__ETABIN1__1down_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN1__1down_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN1__1down_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN1__1down_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN1__1down_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN1__1down_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1down.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN1__1up_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.isPassed",                    &EG_SCALE_MATCRYO__ETABIN1__1up_isPassed);
				float EG_SCALE_MATCRYO__ETABIN1__1up_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN1__1up_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN1__1up_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN1__1up_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN1__1up_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.m_yy",                        &EG_SCALE_MATCRYO__ETABIN1__1up_m_yy);
				float EG_SCALE_MATCRYO__ETABIN1__1up_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN1__1up_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN1__1up_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN1__1up_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN1__1up_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN1__1up_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN1__1up.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN10__1down_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.isPassed",                    &EG_SCALE_MATCRYO__ETABIN10__1down_isPassed);
				float EG_SCALE_MATCRYO__ETABIN10__1down_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN10__1down_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN10__1down_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN10__1down_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN10__1down_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.m_yy",                        &EG_SCALE_MATCRYO__ETABIN10__1down_m_yy);
				float EG_SCALE_MATCRYO__ETABIN10__1down_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN10__1down_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN10__1down_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN10__1down_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN10__1down_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN10__1down_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1down.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN10__1up_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.isPassed",                    &EG_SCALE_MATCRYO__ETABIN10__1up_isPassed);
				float EG_SCALE_MATCRYO__ETABIN10__1up_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN10__1up_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN10__1up_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN10__1up_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN10__1up_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.m_yy",                        &EG_SCALE_MATCRYO__ETABIN10__1up_m_yy);
				float EG_SCALE_MATCRYO__ETABIN10__1up_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN10__1up_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN10__1up_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN10__1up_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN10__1up_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN10__1up_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN10__1up.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN11__1down_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.isPassed",                    &EG_SCALE_MATCRYO__ETABIN11__1down_isPassed);
				float EG_SCALE_MATCRYO__ETABIN11__1down_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN11__1down_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN11__1down_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN11__1down_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN11__1down_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.m_yy",                        &EG_SCALE_MATCRYO__ETABIN11__1down_m_yy);
				float EG_SCALE_MATCRYO__ETABIN11__1down_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN11__1down_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN11__1down_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN11__1down_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN11__1down_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN11__1down_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1down.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN11__1up_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.isPassed",                    &EG_SCALE_MATCRYO__ETABIN11__1up_isPassed);
				float EG_SCALE_MATCRYO__ETABIN11__1up_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN11__1up_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN11__1up_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN11__1up_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN11__1up_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.m_yy",                        &EG_SCALE_MATCRYO__ETABIN11__1up_m_yy);
				float EG_SCALE_MATCRYO__ETABIN11__1up_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN11__1up_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN11__1up_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN11__1up_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN11__1up_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN11__1up_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN11__1up.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN2__1down_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.isPassed",                    &EG_SCALE_MATCRYO__ETABIN2__1down_isPassed);
				float EG_SCALE_MATCRYO__ETABIN2__1down_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN2__1down_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN2__1down_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN2__1down_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN2__1down_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.m_yy",                        &EG_SCALE_MATCRYO__ETABIN2__1down_m_yy);
				float EG_SCALE_MATCRYO__ETABIN2__1down_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN2__1down_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN2__1down_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN2__1down_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN2__1down_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN2__1down_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1down.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN2__1up_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.isPassed",                    &EG_SCALE_MATCRYO__ETABIN2__1up_isPassed);
				float EG_SCALE_MATCRYO__ETABIN2__1up_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN2__1up_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN2__1up_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN2__1up_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN2__1up_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.m_yy",                        &EG_SCALE_MATCRYO__ETABIN2__1up_m_yy);
				float EG_SCALE_MATCRYO__ETABIN2__1up_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN2__1up_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN2__1up_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN2__1up_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN2__1up_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN2__1up_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN2__1up.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN3__1down_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.isPassed",                    &EG_SCALE_MATCRYO__ETABIN3__1down_isPassed);
				float EG_SCALE_MATCRYO__ETABIN3__1down_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN3__1down_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN3__1down_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN3__1down_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN3__1down_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.m_yy",                        &EG_SCALE_MATCRYO__ETABIN3__1down_m_yy);
				float EG_SCALE_MATCRYO__ETABIN3__1down_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN3__1down_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN3__1down_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN3__1down_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN3__1down_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN3__1down_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1down.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN3__1up_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.isPassed",                    &EG_SCALE_MATCRYO__ETABIN3__1up_isPassed);
				float EG_SCALE_MATCRYO__ETABIN3__1up_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN3__1up_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN3__1up_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN3__1up_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN3__1up_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.m_yy",                        &EG_SCALE_MATCRYO__ETABIN3__1up_m_yy);
				float EG_SCALE_MATCRYO__ETABIN3__1up_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN3__1up_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN3__1up_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN3__1up_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN3__1up_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN3__1up_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN3__1up.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN4__1down_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.isPassed",                    &EG_SCALE_MATCRYO__ETABIN4__1down_isPassed);
				float EG_SCALE_MATCRYO__ETABIN4__1down_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN4__1down_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN4__1down_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN4__1down_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN4__1down_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.m_yy",                        &EG_SCALE_MATCRYO__ETABIN4__1down_m_yy);
				float EG_SCALE_MATCRYO__ETABIN4__1down_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN4__1down_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN4__1down_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN4__1down_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN4__1down_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN4__1down_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1down.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN4__1up_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.isPassed",                    &EG_SCALE_MATCRYO__ETABIN4__1up_isPassed);
				float EG_SCALE_MATCRYO__ETABIN4__1up_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN4__1up_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN4__1up_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN4__1up_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN4__1up_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.m_yy",                        &EG_SCALE_MATCRYO__ETABIN4__1up_m_yy);
				float EG_SCALE_MATCRYO__ETABIN4__1up_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN4__1up_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN4__1up_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN4__1up_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN4__1up_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN4__1up_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN4__1up.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN5__1down_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.isPassed",                    &EG_SCALE_MATCRYO__ETABIN5__1down_isPassed);
				float EG_SCALE_MATCRYO__ETABIN5__1down_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN5__1down_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN5__1down_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN5__1down_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN5__1down_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.m_yy",                        &EG_SCALE_MATCRYO__ETABIN5__1down_m_yy);
				float EG_SCALE_MATCRYO__ETABIN5__1down_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN5__1down_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN5__1down_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN5__1down_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN5__1down_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN5__1down_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1down.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN5__1up_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.isPassed",                    &EG_SCALE_MATCRYO__ETABIN5__1up_isPassed);
				float EG_SCALE_MATCRYO__ETABIN5__1up_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN5__1up_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN5__1up_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN5__1up_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN5__1up_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.m_yy",                        &EG_SCALE_MATCRYO__ETABIN5__1up_m_yy);
				float EG_SCALE_MATCRYO__ETABIN5__1up_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN5__1up_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN5__1up_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN5__1up_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN5__1up_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN5__1up_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN5__1up.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN6__1down_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.isPassed",                    &EG_SCALE_MATCRYO__ETABIN6__1down_isPassed);
				float EG_SCALE_MATCRYO__ETABIN6__1down_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN6__1down_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN6__1down_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN6__1down_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN6__1down_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.m_yy",                        &EG_SCALE_MATCRYO__ETABIN6__1down_m_yy);
				float EG_SCALE_MATCRYO__ETABIN6__1down_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN6__1down_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN6__1down_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN6__1down_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN6__1down_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN6__1down_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1down.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN6__1up_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.isPassed",                    &EG_SCALE_MATCRYO__ETABIN6__1up_isPassed);
				float EG_SCALE_MATCRYO__ETABIN6__1up_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN6__1up_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN6__1up_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN6__1up_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN6__1up_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.m_yy",                        &EG_SCALE_MATCRYO__ETABIN6__1up_m_yy);
				float EG_SCALE_MATCRYO__ETABIN6__1up_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN6__1up_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN6__1up_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN6__1up_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN6__1up_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN6__1up_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN6__1up.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN7__1down_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.isPassed",                    &EG_SCALE_MATCRYO__ETABIN7__1down_isPassed);
				float EG_SCALE_MATCRYO__ETABIN7__1down_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN7__1down_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN7__1down_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN7__1down_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN7__1down_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.m_yy",                        &EG_SCALE_MATCRYO__ETABIN7__1down_m_yy);
				float EG_SCALE_MATCRYO__ETABIN7__1down_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN7__1down_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN7__1down_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN7__1down_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN7__1down_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN7__1down_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1down.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN7__1up_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.isPassed",                    &EG_SCALE_MATCRYO__ETABIN7__1up_isPassed);
				float EG_SCALE_MATCRYO__ETABIN7__1up_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN7__1up_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN7__1up_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN7__1up_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN7__1up_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.m_yy",                        &EG_SCALE_MATCRYO__ETABIN7__1up_m_yy);
				float EG_SCALE_MATCRYO__ETABIN7__1up_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN7__1up_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN7__1up_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN7__1up_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN7__1up_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN7__1up_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN7__1up.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN8__1down_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.isPassed",                    &EG_SCALE_MATCRYO__ETABIN8__1down_isPassed);
				float EG_SCALE_MATCRYO__ETABIN8__1down_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN8__1down_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN8__1down_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN8__1down_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN8__1down_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.m_yy",                        &EG_SCALE_MATCRYO__ETABIN8__1down_m_yy);
				float EG_SCALE_MATCRYO__ETABIN8__1down_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN8__1down_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN8__1down_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN8__1down_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN8__1down_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN8__1down_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1down.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN8__1up_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.isPassed",                    &EG_SCALE_MATCRYO__ETABIN8__1up_isPassed);
				float EG_SCALE_MATCRYO__ETABIN8__1up_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN8__1up_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN8__1up_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN8__1up_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN8__1up_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.m_yy",                        &EG_SCALE_MATCRYO__ETABIN8__1up_m_yy);
				float EG_SCALE_MATCRYO__ETABIN8__1up_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN8__1up_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN8__1up_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN8__1up_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN8__1up_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN8__1up_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN8__1up.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN9__1down_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.isPassed",                    &EG_SCALE_MATCRYO__ETABIN9__1down_isPassed);
				float EG_SCALE_MATCRYO__ETABIN9__1down_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN9__1down_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN9__1down_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN9__1down_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN9__1down_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.m_yy",                        &EG_SCALE_MATCRYO__ETABIN9__1down_m_yy);
				float EG_SCALE_MATCRYO__ETABIN9__1down_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN9__1down_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN9__1down_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN9__1down_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN9__1down_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN9__1down_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1down.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_eta);
				int EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_leadjet_truthlabel",     &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_subleadjet_truthlabel",  &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_subleadjet_truthlabel);
				int EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_leadjet_btagbin",        &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_subleadjet_btagbin",     &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_subleadjet_btagbin);
				int EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_Njet_central;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_Njet_central",           &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_Njet_central);
				int EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_cutFlow;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_cutFlow",                &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_cutFlow);
				int EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_nelectron;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_nelectron",              &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_nelectron);
				int EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_nmuon;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_nmuon",                  &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_nmuon);
				bool EG_SCALE_MATCRYO__ETABIN9__1up_isPassed;                  myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.isPassed",                    &EG_SCALE_MATCRYO__ETABIN9__1up_isPassed);
				float EG_SCALE_MATCRYO__ETABIN9__1up_yyHFjj_weight;            myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHFjj_weight",               &EG_SCALE_MATCRYO__ETABIN9__1up_yyHFjj_weight);
				float EG_SCALE_MATCRYO__ETABIN9__1up_yyHFj_weight;             myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHFj_weight",                &EG_SCALE_MATCRYO__ETABIN9__1up_yyHFj_weight);
				float EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_met;                 myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_met",                    &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_met);
				float EG_SCALE_MATCRYO__ETABIN9__1up_m_yy;                     myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.m_yy",                        &EG_SCALE_MATCRYO__ETABIN9__1up_m_yy);
				float EG_SCALE_MATCRYO__ETABIN9__1up_m_yyjj;                   myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.m_yyjj",                      &EG_SCALE_MATCRYO__ETABIN9__1up_m_yyjj);
				float EG_SCALE_MATCRYO__ETABIN9__1up_pT_yy;                    myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.pT_yy",                       &EG_SCALE_MATCRYO__ETABIN9__1up_pT_yy);
				float EG_SCALE_MATCRYO__ETABIN9__1up_HGamWeight;               myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.HGamWeight",                  &EG_SCALE_MATCRYO__ETABIN9__1up_HGamWeight);
				float EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_subleadjet_pt",          &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_subleadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_subleadjet_phi",         &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_subleadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_subleadjet_m",           &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_subleadjet_m);
				float EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_subleadjet_eta",         &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_subleadjet_eta);
				float EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_leadjet_pt",             &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_pt);
				float EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_leadjet_phi",            &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_phi);
				float EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_leadjet_m",              &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_m);
				float EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("EG_SCALE_MATCRYO__ETABIN9__1up.yyHF_leadjet_eta",            &EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_eta);
				int PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_leadjet_truthlabel",     &PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_truthlabel);
				int PH_EFF_ID_Uncertainty__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_subleadjet_truthlabel",  &PH_EFF_ID_Uncertainty__1down_yyHF_subleadjet_truthlabel);
				int PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_leadjet_btagbin",        &PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_btagbin);
				int PH_EFF_ID_Uncertainty__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_subleadjet_btagbin",     &PH_EFF_ID_Uncertainty__1down_yyHF_subleadjet_btagbin);
				int PH_EFF_ID_Uncertainty__1down_yyHF_Njet_central;          myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_Njet_central",           &PH_EFF_ID_Uncertainty__1down_yyHF_Njet_central);
				int PH_EFF_ID_Uncertainty__1down_yyHF_cutFlow;               myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_cutFlow",                &PH_EFF_ID_Uncertainty__1down_yyHF_cutFlow);
				int PH_EFF_ID_Uncertainty__1down_yyHF_nelectron;             myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_nelectron",              &PH_EFF_ID_Uncertainty__1down_yyHF_nelectron);
				int PH_EFF_ID_Uncertainty__1down_yyHF_nmuon;                 myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_nmuon",                  &PH_EFF_ID_Uncertainty__1down_yyHF_nmuon);
				bool PH_EFF_ID_Uncertainty__1down_isPassed;                  myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.isPassed",                    &PH_EFF_ID_Uncertainty__1down_isPassed);
				float PH_EFF_ID_Uncertainty__1down_yyHFjj_weight;            myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHFjj_weight",               &PH_EFF_ID_Uncertainty__1down_yyHFjj_weight);
				float PH_EFF_ID_Uncertainty__1down_yyHFj_weight;             myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHFj_weight",                &PH_EFF_ID_Uncertainty__1down_yyHFj_weight);
				float PH_EFF_ID_Uncertainty__1down_yyHF_met;                 myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_met",                    &PH_EFF_ID_Uncertainty__1down_yyHF_met);
				float PH_EFF_ID_Uncertainty__1down_m_yy;                     myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.m_yy",                        &PH_EFF_ID_Uncertainty__1down_m_yy);
				float PH_EFF_ID_Uncertainty__1down_m_yyjj;                   myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.m_yyjj",                      &PH_EFF_ID_Uncertainty__1down_m_yyjj);
				float PH_EFF_ID_Uncertainty__1down_pT_yy;                    myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.pT_yy",                       &PH_EFF_ID_Uncertainty__1down_pT_yy);
				float PH_EFF_ID_Uncertainty__1down_HGamWeight;               myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.HGamWeight",                  &PH_EFF_ID_Uncertainty__1down_HGamWeight);
				float PH_EFF_ID_Uncertainty__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_subleadjet_pt",          &PH_EFF_ID_Uncertainty__1down_yyHF_subleadjet_pt);
				float PH_EFF_ID_Uncertainty__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_subleadjet_phi",         &PH_EFF_ID_Uncertainty__1down_yyHF_subleadjet_phi);
				float PH_EFF_ID_Uncertainty__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_subleadjet_m",           &PH_EFF_ID_Uncertainty__1down_yyHF_subleadjet_m);
				float PH_EFF_ID_Uncertainty__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_subleadjet_eta",         &PH_EFF_ID_Uncertainty__1down_yyHF_subleadjet_eta);
				float PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_leadjet_pt",             &PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_pt);
				float PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_leadjet_phi",            &PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_phi);
				float PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_leadjet_m",              &PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_m);
				float PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1down.yyHF_leadjet_eta",            &PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_eta);
				int PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_leadjet_truthlabel",     &PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_truthlabel);
				int PH_EFF_ID_Uncertainty__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_subleadjet_truthlabel",  &PH_EFF_ID_Uncertainty__1up_yyHF_subleadjet_truthlabel);
				int PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_leadjet_btagbin",        &PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_btagbin);
				int PH_EFF_ID_Uncertainty__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_subleadjet_btagbin",     &PH_EFF_ID_Uncertainty__1up_yyHF_subleadjet_btagbin);
				int PH_EFF_ID_Uncertainty__1up_yyHF_Njet_central;          myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_Njet_central",           &PH_EFF_ID_Uncertainty__1up_yyHF_Njet_central);
				int PH_EFF_ID_Uncertainty__1up_yyHF_cutFlow;               myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_cutFlow",                &PH_EFF_ID_Uncertainty__1up_yyHF_cutFlow);
				int PH_EFF_ID_Uncertainty__1up_yyHF_nelectron;             myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_nelectron",              &PH_EFF_ID_Uncertainty__1up_yyHF_nelectron);
				int PH_EFF_ID_Uncertainty__1up_yyHF_nmuon;                 myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_nmuon",                  &PH_EFF_ID_Uncertainty__1up_yyHF_nmuon);
				bool PH_EFF_ID_Uncertainty__1up_isPassed;                  myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.isPassed",                    &PH_EFF_ID_Uncertainty__1up_isPassed);
				float PH_EFF_ID_Uncertainty__1up_yyHFjj_weight;            myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHFjj_weight",               &PH_EFF_ID_Uncertainty__1up_yyHFjj_weight);
				float PH_EFF_ID_Uncertainty__1up_yyHFj_weight;             myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHFj_weight",                &PH_EFF_ID_Uncertainty__1up_yyHFj_weight);
				float PH_EFF_ID_Uncertainty__1up_yyHF_met;                 myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_met",                    &PH_EFF_ID_Uncertainty__1up_yyHF_met);
				float PH_EFF_ID_Uncertainty__1up_m_yy;                     myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.m_yy",                        &PH_EFF_ID_Uncertainty__1up_m_yy);
				float PH_EFF_ID_Uncertainty__1up_m_yyjj;                   myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.m_yyjj",                      &PH_EFF_ID_Uncertainty__1up_m_yyjj);
				float PH_EFF_ID_Uncertainty__1up_pT_yy;                    myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.pT_yy",                       &PH_EFF_ID_Uncertainty__1up_pT_yy);
				float PH_EFF_ID_Uncertainty__1up_HGamWeight;               myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.HGamWeight",                  &PH_EFF_ID_Uncertainty__1up_HGamWeight);
				float PH_EFF_ID_Uncertainty__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_subleadjet_pt",          &PH_EFF_ID_Uncertainty__1up_yyHF_subleadjet_pt);
				float PH_EFF_ID_Uncertainty__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_subleadjet_phi",         &PH_EFF_ID_Uncertainty__1up_yyHF_subleadjet_phi);
				float PH_EFF_ID_Uncertainty__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_subleadjet_m",           &PH_EFF_ID_Uncertainty__1up_yyHF_subleadjet_m);
				float PH_EFF_ID_Uncertainty__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_subleadjet_eta",         &PH_EFF_ID_Uncertainty__1up_yyHF_subleadjet_eta);
				float PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_leadjet_pt",             &PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_pt);
				float PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_leadjet_phi",            &PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_phi);
				float PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_leadjet_m",              &PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_m);
				float PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_EFF_ID_Uncertainty__1up.yyHF_leadjet_eta",            &PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_eta);
				int PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_leadjet_truthlabel",     &PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_truthlabel);
				int PH_EFF_ISO_Uncertainty__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_subleadjet_truthlabel",  &PH_EFF_ISO_Uncertainty__1down_yyHF_subleadjet_truthlabel);
				int PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_leadjet_btagbin",        &PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_btagbin);
				int PH_EFF_ISO_Uncertainty__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_subleadjet_btagbin",     &PH_EFF_ISO_Uncertainty__1down_yyHF_subleadjet_btagbin);
				int PH_EFF_ISO_Uncertainty__1down_yyHF_Njet_central;          myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_Njet_central",           &PH_EFF_ISO_Uncertainty__1down_yyHF_Njet_central);
				int PH_EFF_ISO_Uncertainty__1down_yyHF_cutFlow;               myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_cutFlow",                &PH_EFF_ISO_Uncertainty__1down_yyHF_cutFlow);
				int PH_EFF_ISO_Uncertainty__1down_yyHF_nelectron;             myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_nelectron",              &PH_EFF_ISO_Uncertainty__1down_yyHF_nelectron);
				int PH_EFF_ISO_Uncertainty__1down_yyHF_nmuon;                 myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_nmuon",                  &PH_EFF_ISO_Uncertainty__1down_yyHF_nmuon);
				bool PH_EFF_ISO_Uncertainty__1down_isPassed;                  myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.isPassed",                    &PH_EFF_ISO_Uncertainty__1down_isPassed);
				float PH_EFF_ISO_Uncertainty__1down_yyHFjj_weight;            myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHFjj_weight",               &PH_EFF_ISO_Uncertainty__1down_yyHFjj_weight);
				float PH_EFF_ISO_Uncertainty__1down_yyHFj_weight;             myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHFj_weight",                &PH_EFF_ISO_Uncertainty__1down_yyHFj_weight);
				float PH_EFF_ISO_Uncertainty__1down_yyHF_met;                 myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_met",                    &PH_EFF_ISO_Uncertainty__1down_yyHF_met);
				float PH_EFF_ISO_Uncertainty__1down_m_yy;                     myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.m_yy",                        &PH_EFF_ISO_Uncertainty__1down_m_yy);
				float PH_EFF_ISO_Uncertainty__1down_m_yyjj;                   myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.m_yyjj",                      &PH_EFF_ISO_Uncertainty__1down_m_yyjj);
				float PH_EFF_ISO_Uncertainty__1down_pT_yy;                    myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.pT_yy",                       &PH_EFF_ISO_Uncertainty__1down_pT_yy);
				float PH_EFF_ISO_Uncertainty__1down_HGamWeight;               myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.HGamWeight",                  &PH_EFF_ISO_Uncertainty__1down_HGamWeight);
				float PH_EFF_ISO_Uncertainty__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_subleadjet_pt",          &PH_EFF_ISO_Uncertainty__1down_yyHF_subleadjet_pt);
				float PH_EFF_ISO_Uncertainty__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_subleadjet_phi",         &PH_EFF_ISO_Uncertainty__1down_yyHF_subleadjet_phi);
				float PH_EFF_ISO_Uncertainty__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_subleadjet_m",           &PH_EFF_ISO_Uncertainty__1down_yyHF_subleadjet_m);
				float PH_EFF_ISO_Uncertainty__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_subleadjet_eta",         &PH_EFF_ISO_Uncertainty__1down_yyHF_subleadjet_eta);
				float PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_leadjet_pt",             &PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_pt);
				float PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_leadjet_phi",            &PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_phi);
				float PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_leadjet_m",              &PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_m);
				float PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1down.yyHF_leadjet_eta",            &PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_eta);
				int PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_leadjet_truthlabel",     &PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_truthlabel);
				int PH_EFF_ISO_Uncertainty__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_subleadjet_truthlabel",  &PH_EFF_ISO_Uncertainty__1up_yyHF_subleadjet_truthlabel);
				int PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_leadjet_btagbin",        &PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_btagbin);
				int PH_EFF_ISO_Uncertainty__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_subleadjet_btagbin",     &PH_EFF_ISO_Uncertainty__1up_yyHF_subleadjet_btagbin);
				int PH_EFF_ISO_Uncertainty__1up_yyHF_Njet_central;          myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_Njet_central",           &PH_EFF_ISO_Uncertainty__1up_yyHF_Njet_central);
				int PH_EFF_ISO_Uncertainty__1up_yyHF_cutFlow;               myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_cutFlow",                &PH_EFF_ISO_Uncertainty__1up_yyHF_cutFlow);
				int PH_EFF_ISO_Uncertainty__1up_yyHF_nelectron;             myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_nelectron",              &PH_EFF_ISO_Uncertainty__1up_yyHF_nelectron);
				int PH_EFF_ISO_Uncertainty__1up_yyHF_nmuon;                 myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_nmuon",                  &PH_EFF_ISO_Uncertainty__1up_yyHF_nmuon);
				bool PH_EFF_ISO_Uncertainty__1up_isPassed;                  myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.isPassed",                    &PH_EFF_ISO_Uncertainty__1up_isPassed);
				float PH_EFF_ISO_Uncertainty__1up_yyHFjj_weight;            myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHFjj_weight",               &PH_EFF_ISO_Uncertainty__1up_yyHFjj_weight);
				float PH_EFF_ISO_Uncertainty__1up_yyHFj_weight;             myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHFj_weight",                &PH_EFF_ISO_Uncertainty__1up_yyHFj_weight);
				float PH_EFF_ISO_Uncertainty__1up_yyHF_met;                 myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_met",                    &PH_EFF_ISO_Uncertainty__1up_yyHF_met);
				float PH_EFF_ISO_Uncertainty__1up_m_yy;                     myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.m_yy",                        &PH_EFF_ISO_Uncertainty__1up_m_yy);
				float PH_EFF_ISO_Uncertainty__1up_m_yyjj;                   myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.m_yyjj",                      &PH_EFF_ISO_Uncertainty__1up_m_yyjj);
				float PH_EFF_ISO_Uncertainty__1up_pT_yy;                    myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.pT_yy",                       &PH_EFF_ISO_Uncertainty__1up_pT_yy);
				float PH_EFF_ISO_Uncertainty__1up_HGamWeight;               myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.HGamWeight",                  &PH_EFF_ISO_Uncertainty__1up_HGamWeight);
				float PH_EFF_ISO_Uncertainty__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_subleadjet_pt",          &PH_EFF_ISO_Uncertainty__1up_yyHF_subleadjet_pt);
				float PH_EFF_ISO_Uncertainty__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_subleadjet_phi",         &PH_EFF_ISO_Uncertainty__1up_yyHF_subleadjet_phi);
				float PH_EFF_ISO_Uncertainty__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_subleadjet_m",           &PH_EFF_ISO_Uncertainty__1up_yyHF_subleadjet_m);
				float PH_EFF_ISO_Uncertainty__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_subleadjet_eta",         &PH_EFF_ISO_Uncertainty__1up_yyHF_subleadjet_eta);
				float PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_leadjet_pt",             &PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_pt);
				float PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_leadjet_phi",            &PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_phi);
				float PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_leadjet_m",              &PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_m);
				float PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_EFF_ISO_Uncertainty__1up.yyHF_leadjet_eta",            &PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_eta);
				int PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_leadjet_truthlabel",     &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_truthlabel);
				int PH_EFF_TRIGGER_Uncertainty__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_subleadjet_truthlabel",  &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_subleadjet_truthlabel);
				int PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_leadjet_btagbin",        &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_btagbin);
				int PH_EFF_TRIGGER_Uncertainty__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_subleadjet_btagbin",     &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_subleadjet_btagbin);
				int PH_EFF_TRIGGER_Uncertainty__1down_yyHF_Njet_central;          myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_Njet_central",           &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_Njet_central);
				int PH_EFF_TRIGGER_Uncertainty__1down_yyHF_cutFlow;               myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_cutFlow",                &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_cutFlow);
				int PH_EFF_TRIGGER_Uncertainty__1down_yyHF_nelectron;             myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_nelectron",              &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_nelectron);
				int PH_EFF_TRIGGER_Uncertainty__1down_yyHF_nmuon;                 myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_nmuon",                  &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_nmuon);
				bool PH_EFF_TRIGGER_Uncertainty__1down_isPassed;                  myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.isPassed",                    &PH_EFF_TRIGGER_Uncertainty__1down_isPassed);
				float PH_EFF_TRIGGER_Uncertainty__1down_yyHFjj_weight;            myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHFjj_weight",               &PH_EFF_TRIGGER_Uncertainty__1down_yyHFjj_weight);
				float PH_EFF_TRIGGER_Uncertainty__1down_yyHFj_weight;             myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHFj_weight",                &PH_EFF_TRIGGER_Uncertainty__1down_yyHFj_weight);
				float PH_EFF_TRIGGER_Uncertainty__1down_yyHF_met;                 myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_met",                    &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_met);
				float PH_EFF_TRIGGER_Uncertainty__1down_m_yy;                     myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.m_yy",                        &PH_EFF_TRIGGER_Uncertainty__1down_m_yy);
				float PH_EFF_TRIGGER_Uncertainty__1down_m_yyjj;                   myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.m_yyjj",                      &PH_EFF_TRIGGER_Uncertainty__1down_m_yyjj);
				float PH_EFF_TRIGGER_Uncertainty__1down_pT_yy;                    myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.pT_yy",                       &PH_EFF_TRIGGER_Uncertainty__1down_pT_yy);
				float PH_EFF_TRIGGER_Uncertainty__1down_HGamWeight;               myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.HGamWeight",                  &PH_EFF_TRIGGER_Uncertainty__1down_HGamWeight);
				float PH_EFF_TRIGGER_Uncertainty__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_subleadjet_pt",          &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_subleadjet_pt);
				float PH_EFF_TRIGGER_Uncertainty__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_subleadjet_phi",         &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_subleadjet_phi);
				float PH_EFF_TRIGGER_Uncertainty__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_subleadjet_m",           &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_subleadjet_m);
				float PH_EFF_TRIGGER_Uncertainty__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_subleadjet_eta",         &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_subleadjet_eta);
				float PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_leadjet_pt",             &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_pt);
				float PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_leadjet_phi",            &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_phi);
				float PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_leadjet_m",              &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_m);
				float PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1down.yyHF_leadjet_eta",            &PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_eta);
				int PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_leadjet_truthlabel",     &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_truthlabel);
				int PH_EFF_TRIGGER_Uncertainty__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_subleadjet_truthlabel",  &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_subleadjet_truthlabel);
				int PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_leadjet_btagbin",        &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_btagbin);
				int PH_EFF_TRIGGER_Uncertainty__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_subleadjet_btagbin",     &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_subleadjet_btagbin);
				int PH_EFF_TRIGGER_Uncertainty__1up_yyHF_Njet_central;          myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_Njet_central",           &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_Njet_central);
				int PH_EFF_TRIGGER_Uncertainty__1up_yyHF_cutFlow;               myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_cutFlow",                &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_cutFlow);
				int PH_EFF_TRIGGER_Uncertainty__1up_yyHF_nelectron;             myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_nelectron",              &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_nelectron);
				int PH_EFF_TRIGGER_Uncertainty__1up_yyHF_nmuon;                 myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_nmuon",                  &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_nmuon);
				bool PH_EFF_TRIGGER_Uncertainty__1up_isPassed;                  myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.isPassed",                    &PH_EFF_TRIGGER_Uncertainty__1up_isPassed);
				float PH_EFF_TRIGGER_Uncertainty__1up_yyHFjj_weight;            myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHFjj_weight",               &PH_EFF_TRIGGER_Uncertainty__1up_yyHFjj_weight);
				float PH_EFF_TRIGGER_Uncertainty__1up_yyHFj_weight;             myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHFj_weight",                &PH_EFF_TRIGGER_Uncertainty__1up_yyHFj_weight);
				float PH_EFF_TRIGGER_Uncertainty__1up_yyHF_met;                 myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_met",                    &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_met);
				float PH_EFF_TRIGGER_Uncertainty__1up_m_yy;                     myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.m_yy",                        &PH_EFF_TRIGGER_Uncertainty__1up_m_yy);
				float PH_EFF_TRIGGER_Uncertainty__1up_m_yyjj;                   myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.m_yyjj",                      &PH_EFF_TRIGGER_Uncertainty__1up_m_yyjj);
				float PH_EFF_TRIGGER_Uncertainty__1up_pT_yy;                    myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.pT_yy",                       &PH_EFF_TRIGGER_Uncertainty__1up_pT_yy);
				float PH_EFF_TRIGGER_Uncertainty__1up_HGamWeight;               myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.HGamWeight",                  &PH_EFF_TRIGGER_Uncertainty__1up_HGamWeight);
				float PH_EFF_TRIGGER_Uncertainty__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_subleadjet_pt",          &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_subleadjet_pt);
				float PH_EFF_TRIGGER_Uncertainty__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_subleadjet_phi",         &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_subleadjet_phi);
				float PH_EFF_TRIGGER_Uncertainty__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_subleadjet_m",           &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_subleadjet_m);
				float PH_EFF_TRIGGER_Uncertainty__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_subleadjet_eta",         &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_subleadjet_eta);
				float PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_leadjet_pt",             &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_pt);
				float PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_leadjet_phi",            &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_phi);
				float PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_leadjet_m",              &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_m);
				float PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_EFF_TRIGGER_Uncertainty__1up.yyHF_leadjet_eta",            &PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_eta);
				int PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_leadjet_truthlabel",     &PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_truthlabel);
				int PH_SCALE_CONVEFFICIENCY__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_subleadjet_truthlabel",  &PH_SCALE_CONVEFFICIENCY__1down_yyHF_subleadjet_truthlabel);
				int PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_leadjet_btagbin",        &PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_btagbin);
				int PH_SCALE_CONVEFFICIENCY__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_subleadjet_btagbin",     &PH_SCALE_CONVEFFICIENCY__1down_yyHF_subleadjet_btagbin);
				int PH_SCALE_CONVEFFICIENCY__1down_yyHF_Njet_central;          myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_Njet_central",           &PH_SCALE_CONVEFFICIENCY__1down_yyHF_Njet_central);
				int PH_SCALE_CONVEFFICIENCY__1down_yyHF_cutFlow;               myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_cutFlow",                &PH_SCALE_CONVEFFICIENCY__1down_yyHF_cutFlow);
				int PH_SCALE_CONVEFFICIENCY__1down_yyHF_nelectron;             myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_nelectron",              &PH_SCALE_CONVEFFICIENCY__1down_yyHF_nelectron);
				int PH_SCALE_CONVEFFICIENCY__1down_yyHF_nmuon;                 myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_nmuon",                  &PH_SCALE_CONVEFFICIENCY__1down_yyHF_nmuon);
				bool PH_SCALE_CONVEFFICIENCY__1down_isPassed;                  myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.isPassed",                    &PH_SCALE_CONVEFFICIENCY__1down_isPassed);
				float PH_SCALE_CONVEFFICIENCY__1down_yyHFjj_weight;            myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHFjj_weight",               &PH_SCALE_CONVEFFICIENCY__1down_yyHFjj_weight);
				float PH_SCALE_CONVEFFICIENCY__1down_yyHFj_weight;             myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHFj_weight",                &PH_SCALE_CONVEFFICIENCY__1down_yyHFj_weight);
				float PH_SCALE_CONVEFFICIENCY__1down_yyHF_met;                 myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_met",                    &PH_SCALE_CONVEFFICIENCY__1down_yyHF_met);
				float PH_SCALE_CONVEFFICIENCY__1down_m_yy;                     myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.m_yy",                        &PH_SCALE_CONVEFFICIENCY__1down_m_yy);
				float PH_SCALE_CONVEFFICIENCY__1down_m_yyjj;                   myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.m_yyjj",                      &PH_SCALE_CONVEFFICIENCY__1down_m_yyjj);
				float PH_SCALE_CONVEFFICIENCY__1down_pT_yy;                    myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.pT_yy",                       &PH_SCALE_CONVEFFICIENCY__1down_pT_yy);
				float PH_SCALE_CONVEFFICIENCY__1down_HGamWeight;               myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.HGamWeight",                  &PH_SCALE_CONVEFFICIENCY__1down_HGamWeight);
				float PH_SCALE_CONVEFFICIENCY__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_subleadjet_pt",          &PH_SCALE_CONVEFFICIENCY__1down_yyHF_subleadjet_pt);
				float PH_SCALE_CONVEFFICIENCY__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_subleadjet_phi",         &PH_SCALE_CONVEFFICIENCY__1down_yyHF_subleadjet_phi);
				float PH_SCALE_CONVEFFICIENCY__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_subleadjet_m",           &PH_SCALE_CONVEFFICIENCY__1down_yyHF_subleadjet_m);
				float PH_SCALE_CONVEFFICIENCY__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_subleadjet_eta",         &PH_SCALE_CONVEFFICIENCY__1down_yyHF_subleadjet_eta);
				float PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_leadjet_pt",             &PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_pt);
				float PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_leadjet_phi",            &PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_phi);
				float PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_leadjet_m",              &PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_m);
				float PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1down.yyHF_leadjet_eta",            &PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_eta);
				int PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_leadjet_truthlabel",     &PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_truthlabel);
				int PH_SCALE_CONVEFFICIENCY__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_subleadjet_truthlabel",  &PH_SCALE_CONVEFFICIENCY__1up_yyHF_subleadjet_truthlabel);
				int PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_leadjet_btagbin",        &PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_btagbin);
				int PH_SCALE_CONVEFFICIENCY__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_subleadjet_btagbin",     &PH_SCALE_CONVEFFICIENCY__1up_yyHF_subleadjet_btagbin);
				int PH_SCALE_CONVEFFICIENCY__1up_yyHF_Njet_central;          myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_Njet_central",           &PH_SCALE_CONVEFFICIENCY__1up_yyHF_Njet_central);
				int PH_SCALE_CONVEFFICIENCY__1up_yyHF_cutFlow;               myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_cutFlow",                &PH_SCALE_CONVEFFICIENCY__1up_yyHF_cutFlow);
				int PH_SCALE_CONVEFFICIENCY__1up_yyHF_nelectron;             myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_nelectron",              &PH_SCALE_CONVEFFICIENCY__1up_yyHF_nelectron);
				int PH_SCALE_CONVEFFICIENCY__1up_yyHF_nmuon;                 myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_nmuon",                  &PH_SCALE_CONVEFFICIENCY__1up_yyHF_nmuon);
				bool PH_SCALE_CONVEFFICIENCY__1up_isPassed;                  myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.isPassed",                    &PH_SCALE_CONVEFFICIENCY__1up_isPassed);
				float PH_SCALE_CONVEFFICIENCY__1up_yyHFjj_weight;            myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHFjj_weight",               &PH_SCALE_CONVEFFICIENCY__1up_yyHFjj_weight);
				float PH_SCALE_CONVEFFICIENCY__1up_yyHFj_weight;             myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHFj_weight",                &PH_SCALE_CONVEFFICIENCY__1up_yyHFj_weight);
				float PH_SCALE_CONVEFFICIENCY__1up_yyHF_met;                 myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_met",                    &PH_SCALE_CONVEFFICIENCY__1up_yyHF_met);
				float PH_SCALE_CONVEFFICIENCY__1up_m_yy;                     myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.m_yy",                        &PH_SCALE_CONVEFFICIENCY__1up_m_yy);
				float PH_SCALE_CONVEFFICIENCY__1up_m_yyjj;                   myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.m_yyjj",                      &PH_SCALE_CONVEFFICIENCY__1up_m_yyjj);
				float PH_SCALE_CONVEFFICIENCY__1up_pT_yy;                    myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.pT_yy",                       &PH_SCALE_CONVEFFICIENCY__1up_pT_yy);
				float PH_SCALE_CONVEFFICIENCY__1up_HGamWeight;               myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.HGamWeight",                  &PH_SCALE_CONVEFFICIENCY__1up_HGamWeight);
				float PH_SCALE_CONVEFFICIENCY__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_subleadjet_pt",          &PH_SCALE_CONVEFFICIENCY__1up_yyHF_subleadjet_pt);
				float PH_SCALE_CONVEFFICIENCY__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_subleadjet_phi",         &PH_SCALE_CONVEFFICIENCY__1up_yyHF_subleadjet_phi);
				float PH_SCALE_CONVEFFICIENCY__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_subleadjet_m",           &PH_SCALE_CONVEFFICIENCY__1up_yyHF_subleadjet_m);
				float PH_SCALE_CONVEFFICIENCY__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_subleadjet_eta",         &PH_SCALE_CONVEFFICIENCY__1up_yyHF_subleadjet_eta);
				float PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_leadjet_pt",             &PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_pt);
				float PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_leadjet_phi",            &PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_phi);
				float PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_leadjet_m",              &PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_m);
				float PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_SCALE_CONVEFFICIENCY__1up.yyHF_leadjet_eta",            &PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_eta);
				int PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_leadjet_truthlabel",     &PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_truthlabel);
				int PH_SCALE_CONVFAKERATE__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_subleadjet_truthlabel",  &PH_SCALE_CONVFAKERATE__1down_yyHF_subleadjet_truthlabel);
				int PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_leadjet_btagbin",        &PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_btagbin);
				int PH_SCALE_CONVFAKERATE__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_subleadjet_btagbin",     &PH_SCALE_CONVFAKERATE__1down_yyHF_subleadjet_btagbin);
				int PH_SCALE_CONVFAKERATE__1down_yyHF_Njet_central;          myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_Njet_central",           &PH_SCALE_CONVFAKERATE__1down_yyHF_Njet_central);
				int PH_SCALE_CONVFAKERATE__1down_yyHF_cutFlow;               myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_cutFlow",                &PH_SCALE_CONVFAKERATE__1down_yyHF_cutFlow);
				int PH_SCALE_CONVFAKERATE__1down_yyHF_nelectron;             myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_nelectron",              &PH_SCALE_CONVFAKERATE__1down_yyHF_nelectron);
				int PH_SCALE_CONVFAKERATE__1down_yyHF_nmuon;                 myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_nmuon",                  &PH_SCALE_CONVFAKERATE__1down_yyHF_nmuon);
				bool PH_SCALE_CONVFAKERATE__1down_isPassed;                  myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.isPassed",                    &PH_SCALE_CONVFAKERATE__1down_isPassed);
				float PH_SCALE_CONVFAKERATE__1down_yyHFjj_weight;            myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHFjj_weight",               &PH_SCALE_CONVFAKERATE__1down_yyHFjj_weight);
				float PH_SCALE_CONVFAKERATE__1down_yyHFj_weight;             myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHFj_weight",                &PH_SCALE_CONVFAKERATE__1down_yyHFj_weight);
				float PH_SCALE_CONVFAKERATE__1down_yyHF_met;                 myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_met",                    &PH_SCALE_CONVFAKERATE__1down_yyHF_met);
				float PH_SCALE_CONVFAKERATE__1down_m_yy;                     myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.m_yy",                        &PH_SCALE_CONVFAKERATE__1down_m_yy);
				float PH_SCALE_CONVFAKERATE__1down_m_yyjj;                   myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.m_yyjj",                      &PH_SCALE_CONVFAKERATE__1down_m_yyjj);
				float PH_SCALE_CONVFAKERATE__1down_pT_yy;                    myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.pT_yy",                       &PH_SCALE_CONVFAKERATE__1down_pT_yy);
				float PH_SCALE_CONVFAKERATE__1down_HGamWeight;               myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.HGamWeight",                  &PH_SCALE_CONVFAKERATE__1down_HGamWeight);
				float PH_SCALE_CONVFAKERATE__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_subleadjet_pt",          &PH_SCALE_CONVFAKERATE__1down_yyHF_subleadjet_pt);
				float PH_SCALE_CONVFAKERATE__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_subleadjet_phi",         &PH_SCALE_CONVFAKERATE__1down_yyHF_subleadjet_phi);
				float PH_SCALE_CONVFAKERATE__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_subleadjet_m",           &PH_SCALE_CONVFAKERATE__1down_yyHF_subleadjet_m);
				float PH_SCALE_CONVFAKERATE__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_subleadjet_eta",         &PH_SCALE_CONVFAKERATE__1down_yyHF_subleadjet_eta);
				float PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_leadjet_pt",             &PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_pt);
				float PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_leadjet_phi",            &PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_phi);
				float PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_leadjet_m",              &PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_m);
				float PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1down.yyHF_leadjet_eta",            &PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_eta);
				int PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_leadjet_truthlabel",     &PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_truthlabel);
				int PH_SCALE_CONVFAKERATE__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_subleadjet_truthlabel",  &PH_SCALE_CONVFAKERATE__1up_yyHF_subleadjet_truthlabel);
				int PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_leadjet_btagbin",        &PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_btagbin);
				int PH_SCALE_CONVFAKERATE__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_subleadjet_btagbin",     &PH_SCALE_CONVFAKERATE__1up_yyHF_subleadjet_btagbin);
				int PH_SCALE_CONVFAKERATE__1up_yyHF_Njet_central;          myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_Njet_central",           &PH_SCALE_CONVFAKERATE__1up_yyHF_Njet_central);
				int PH_SCALE_CONVFAKERATE__1up_yyHF_cutFlow;               myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_cutFlow",                &PH_SCALE_CONVFAKERATE__1up_yyHF_cutFlow);
				int PH_SCALE_CONVFAKERATE__1up_yyHF_nelectron;             myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_nelectron",              &PH_SCALE_CONVFAKERATE__1up_yyHF_nelectron);
				int PH_SCALE_CONVFAKERATE__1up_yyHF_nmuon;                 myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_nmuon",                  &PH_SCALE_CONVFAKERATE__1up_yyHF_nmuon);
				bool PH_SCALE_CONVFAKERATE__1up_isPassed;                  myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.isPassed",                    &PH_SCALE_CONVFAKERATE__1up_isPassed);
				float PH_SCALE_CONVFAKERATE__1up_yyHFjj_weight;            myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHFjj_weight",               &PH_SCALE_CONVFAKERATE__1up_yyHFjj_weight);
				float PH_SCALE_CONVFAKERATE__1up_yyHFj_weight;             myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHFj_weight",                &PH_SCALE_CONVFAKERATE__1up_yyHFj_weight);
				float PH_SCALE_CONVFAKERATE__1up_yyHF_met;                 myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_met",                    &PH_SCALE_CONVFAKERATE__1up_yyHF_met);
				float PH_SCALE_CONVFAKERATE__1up_m_yy;                     myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.m_yy",                        &PH_SCALE_CONVFAKERATE__1up_m_yy);
				float PH_SCALE_CONVFAKERATE__1up_m_yyjj;                   myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.m_yyjj",                      &PH_SCALE_CONVFAKERATE__1up_m_yyjj);
				float PH_SCALE_CONVFAKERATE__1up_pT_yy;                    myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.pT_yy",                       &PH_SCALE_CONVFAKERATE__1up_pT_yy);
				float PH_SCALE_CONVFAKERATE__1up_HGamWeight;               myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.HGamWeight",                  &PH_SCALE_CONVFAKERATE__1up_HGamWeight);
				float PH_SCALE_CONVFAKERATE__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_subleadjet_pt",          &PH_SCALE_CONVFAKERATE__1up_yyHF_subleadjet_pt);
				float PH_SCALE_CONVFAKERATE__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_subleadjet_phi",         &PH_SCALE_CONVFAKERATE__1up_yyHF_subleadjet_phi);
				float PH_SCALE_CONVFAKERATE__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_subleadjet_m",           &PH_SCALE_CONVFAKERATE__1up_yyHF_subleadjet_m);
				float PH_SCALE_CONVFAKERATE__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_subleadjet_eta",         &PH_SCALE_CONVFAKERATE__1up_yyHF_subleadjet_eta);
				float PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_leadjet_pt",             &PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_pt);
				float PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_leadjet_phi",            &PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_phi);
				float PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_leadjet_m",              &PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_m);
				float PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_SCALE_CONVFAKERATE__1up.yyHF_leadjet_eta",            &PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_eta);
				int PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_leadjet_truthlabel",     &PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_truthlabel);
				int PH_SCALE_CONVRADIUS__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_subleadjet_truthlabel",  &PH_SCALE_CONVRADIUS__1down_yyHF_subleadjet_truthlabel);
				int PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_leadjet_btagbin",        &PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_btagbin);
				int PH_SCALE_CONVRADIUS__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_subleadjet_btagbin",     &PH_SCALE_CONVRADIUS__1down_yyHF_subleadjet_btagbin);
				int PH_SCALE_CONVRADIUS__1down_yyHF_Njet_central;          myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_Njet_central",           &PH_SCALE_CONVRADIUS__1down_yyHF_Njet_central);
				int PH_SCALE_CONVRADIUS__1down_yyHF_cutFlow;               myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_cutFlow",                &PH_SCALE_CONVRADIUS__1down_yyHF_cutFlow);
				int PH_SCALE_CONVRADIUS__1down_yyHF_nelectron;             myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_nelectron",              &PH_SCALE_CONVRADIUS__1down_yyHF_nelectron);
				int PH_SCALE_CONVRADIUS__1down_yyHF_nmuon;                 myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_nmuon",                  &PH_SCALE_CONVRADIUS__1down_yyHF_nmuon);
				bool PH_SCALE_CONVRADIUS__1down_isPassed;                  myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.isPassed",                    &PH_SCALE_CONVRADIUS__1down_isPassed);
				float PH_SCALE_CONVRADIUS__1down_yyHFjj_weight;            myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHFjj_weight",               &PH_SCALE_CONVRADIUS__1down_yyHFjj_weight);
				float PH_SCALE_CONVRADIUS__1down_yyHFj_weight;             myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHFj_weight",                &PH_SCALE_CONVRADIUS__1down_yyHFj_weight);
				float PH_SCALE_CONVRADIUS__1down_yyHF_met;                 myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_met",                    &PH_SCALE_CONVRADIUS__1down_yyHF_met);
				float PH_SCALE_CONVRADIUS__1down_m_yy;                     myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.m_yy",                        &PH_SCALE_CONVRADIUS__1down_m_yy);
				float PH_SCALE_CONVRADIUS__1down_m_yyjj;                   myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.m_yyjj",                      &PH_SCALE_CONVRADIUS__1down_m_yyjj);
				float PH_SCALE_CONVRADIUS__1down_pT_yy;                    myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.pT_yy",                       &PH_SCALE_CONVRADIUS__1down_pT_yy);
				float PH_SCALE_CONVRADIUS__1down_HGamWeight;               myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.HGamWeight",                  &PH_SCALE_CONVRADIUS__1down_HGamWeight);
				float PH_SCALE_CONVRADIUS__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_subleadjet_pt",          &PH_SCALE_CONVRADIUS__1down_yyHF_subleadjet_pt);
				float PH_SCALE_CONVRADIUS__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_subleadjet_phi",         &PH_SCALE_CONVRADIUS__1down_yyHF_subleadjet_phi);
				float PH_SCALE_CONVRADIUS__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_subleadjet_m",           &PH_SCALE_CONVRADIUS__1down_yyHF_subleadjet_m);
				float PH_SCALE_CONVRADIUS__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_subleadjet_eta",         &PH_SCALE_CONVRADIUS__1down_yyHF_subleadjet_eta);
				float PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_leadjet_pt",             &PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_pt);
				float PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_leadjet_phi",            &PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_phi);
				float PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_leadjet_m",              &PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_m);
				float PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1down.yyHF_leadjet_eta",            &PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_eta);
				int PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_leadjet_truthlabel",     &PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_truthlabel);
				int PH_SCALE_CONVRADIUS__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_subleadjet_truthlabel",  &PH_SCALE_CONVRADIUS__1up_yyHF_subleadjet_truthlabel);
				int PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_leadjet_btagbin",        &PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_btagbin);
				int PH_SCALE_CONVRADIUS__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_subleadjet_btagbin",     &PH_SCALE_CONVRADIUS__1up_yyHF_subleadjet_btagbin);
				int PH_SCALE_CONVRADIUS__1up_yyHF_Njet_central;          myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_Njet_central",           &PH_SCALE_CONVRADIUS__1up_yyHF_Njet_central);
				int PH_SCALE_CONVRADIUS__1up_yyHF_cutFlow;               myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_cutFlow",                &PH_SCALE_CONVRADIUS__1up_yyHF_cutFlow);
				int PH_SCALE_CONVRADIUS__1up_yyHF_nelectron;             myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_nelectron",              &PH_SCALE_CONVRADIUS__1up_yyHF_nelectron);
				int PH_SCALE_CONVRADIUS__1up_yyHF_nmuon;                 myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_nmuon",                  &PH_SCALE_CONVRADIUS__1up_yyHF_nmuon);
				bool PH_SCALE_CONVRADIUS__1up_isPassed;                  myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.isPassed",                    &PH_SCALE_CONVRADIUS__1up_isPassed);
				float PH_SCALE_CONVRADIUS__1up_yyHFjj_weight;            myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHFjj_weight",               &PH_SCALE_CONVRADIUS__1up_yyHFjj_weight);
				float PH_SCALE_CONVRADIUS__1up_yyHFj_weight;             myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHFj_weight",                &PH_SCALE_CONVRADIUS__1up_yyHFj_weight);
				float PH_SCALE_CONVRADIUS__1up_yyHF_met;                 myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_met",                    &PH_SCALE_CONVRADIUS__1up_yyHF_met);
				float PH_SCALE_CONVRADIUS__1up_m_yy;                     myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.m_yy",                        &PH_SCALE_CONVRADIUS__1up_m_yy);
				float PH_SCALE_CONVRADIUS__1up_m_yyjj;                   myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.m_yyjj",                      &PH_SCALE_CONVRADIUS__1up_m_yyjj);
				float PH_SCALE_CONVRADIUS__1up_pT_yy;                    myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.pT_yy",                       &PH_SCALE_CONVRADIUS__1up_pT_yy);
				float PH_SCALE_CONVRADIUS__1up_HGamWeight;               myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.HGamWeight",                  &PH_SCALE_CONVRADIUS__1up_HGamWeight);
				float PH_SCALE_CONVRADIUS__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_subleadjet_pt",          &PH_SCALE_CONVRADIUS__1up_yyHF_subleadjet_pt);
				float PH_SCALE_CONVRADIUS__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_subleadjet_phi",         &PH_SCALE_CONVRADIUS__1up_yyHF_subleadjet_phi);
				float PH_SCALE_CONVRADIUS__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_subleadjet_m",           &PH_SCALE_CONVRADIUS__1up_yyHF_subleadjet_m);
				float PH_SCALE_CONVRADIUS__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_subleadjet_eta",         &PH_SCALE_CONVRADIUS__1up_yyHF_subleadjet_eta);
				float PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_leadjet_pt",             &PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_pt);
				float PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_leadjet_phi",            &PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_phi);
				float PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_leadjet_m",              &PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_m);
				float PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_SCALE_CONVRADIUS__1up.yyHF_leadjet_eta",            &PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_eta);
				int PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_leadjet_truthlabel",     &PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_truthlabel);
				int PH_SCALE_LEAKAGECONV__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_subleadjet_truthlabel",  &PH_SCALE_LEAKAGECONV__1down_yyHF_subleadjet_truthlabel);
				int PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_leadjet_btagbin",        &PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_btagbin);
				int PH_SCALE_LEAKAGECONV__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_subleadjet_btagbin",     &PH_SCALE_LEAKAGECONV__1down_yyHF_subleadjet_btagbin);
				int PH_SCALE_LEAKAGECONV__1down_yyHF_Njet_central;          myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_Njet_central",           &PH_SCALE_LEAKAGECONV__1down_yyHF_Njet_central);
				int PH_SCALE_LEAKAGECONV__1down_yyHF_cutFlow;               myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_cutFlow",                &PH_SCALE_LEAKAGECONV__1down_yyHF_cutFlow);
				int PH_SCALE_LEAKAGECONV__1down_yyHF_nelectron;             myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_nelectron",              &PH_SCALE_LEAKAGECONV__1down_yyHF_nelectron);
				int PH_SCALE_LEAKAGECONV__1down_yyHF_nmuon;                 myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_nmuon",                  &PH_SCALE_LEAKAGECONV__1down_yyHF_nmuon);
				bool PH_SCALE_LEAKAGECONV__1down_isPassed;                  myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.isPassed",                    &PH_SCALE_LEAKAGECONV__1down_isPassed);
				float PH_SCALE_LEAKAGECONV__1down_yyHFjj_weight;            myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHFjj_weight",               &PH_SCALE_LEAKAGECONV__1down_yyHFjj_weight);
				float PH_SCALE_LEAKAGECONV__1down_yyHFj_weight;             myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHFj_weight",                &PH_SCALE_LEAKAGECONV__1down_yyHFj_weight);
				float PH_SCALE_LEAKAGECONV__1down_yyHF_met;                 myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_met",                    &PH_SCALE_LEAKAGECONV__1down_yyHF_met);
				float PH_SCALE_LEAKAGECONV__1down_m_yy;                     myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.m_yy",                        &PH_SCALE_LEAKAGECONV__1down_m_yy);
				float PH_SCALE_LEAKAGECONV__1down_m_yyjj;                   myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.m_yyjj",                      &PH_SCALE_LEAKAGECONV__1down_m_yyjj);
				float PH_SCALE_LEAKAGECONV__1down_pT_yy;                    myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.pT_yy",                       &PH_SCALE_LEAKAGECONV__1down_pT_yy);
				float PH_SCALE_LEAKAGECONV__1down_HGamWeight;               myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.HGamWeight",                  &PH_SCALE_LEAKAGECONV__1down_HGamWeight);
				float PH_SCALE_LEAKAGECONV__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_subleadjet_pt",          &PH_SCALE_LEAKAGECONV__1down_yyHF_subleadjet_pt);
				float PH_SCALE_LEAKAGECONV__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_subleadjet_phi",         &PH_SCALE_LEAKAGECONV__1down_yyHF_subleadjet_phi);
				float PH_SCALE_LEAKAGECONV__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_subleadjet_m",           &PH_SCALE_LEAKAGECONV__1down_yyHF_subleadjet_m);
				float PH_SCALE_LEAKAGECONV__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_subleadjet_eta",         &PH_SCALE_LEAKAGECONV__1down_yyHF_subleadjet_eta);
				float PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_leadjet_pt",             &PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_pt);
				float PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_leadjet_phi",            &PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_phi);
				float PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_leadjet_m",              &PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_m);
				float PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1down.yyHF_leadjet_eta",            &PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_eta);
				int PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_leadjet_truthlabel",     &PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_truthlabel);
				int PH_SCALE_LEAKAGECONV__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_subleadjet_truthlabel",  &PH_SCALE_LEAKAGECONV__1up_yyHF_subleadjet_truthlabel);
				int PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_leadjet_btagbin",        &PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_btagbin);
				int PH_SCALE_LEAKAGECONV__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_subleadjet_btagbin",     &PH_SCALE_LEAKAGECONV__1up_yyHF_subleadjet_btagbin);
				int PH_SCALE_LEAKAGECONV__1up_yyHF_Njet_central;          myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_Njet_central",           &PH_SCALE_LEAKAGECONV__1up_yyHF_Njet_central);
				int PH_SCALE_LEAKAGECONV__1up_yyHF_cutFlow;               myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_cutFlow",                &PH_SCALE_LEAKAGECONV__1up_yyHF_cutFlow);
				int PH_SCALE_LEAKAGECONV__1up_yyHF_nelectron;             myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_nelectron",              &PH_SCALE_LEAKAGECONV__1up_yyHF_nelectron);
				int PH_SCALE_LEAKAGECONV__1up_yyHF_nmuon;                 myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_nmuon",                  &PH_SCALE_LEAKAGECONV__1up_yyHF_nmuon);
				bool PH_SCALE_LEAKAGECONV__1up_isPassed;                  myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.isPassed",                    &PH_SCALE_LEAKAGECONV__1up_isPassed);
				float PH_SCALE_LEAKAGECONV__1up_yyHFjj_weight;            myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHFjj_weight",               &PH_SCALE_LEAKAGECONV__1up_yyHFjj_weight);
				float PH_SCALE_LEAKAGECONV__1up_yyHFj_weight;             myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHFj_weight",                &PH_SCALE_LEAKAGECONV__1up_yyHFj_weight);
				float PH_SCALE_LEAKAGECONV__1up_yyHF_met;                 myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_met",                    &PH_SCALE_LEAKAGECONV__1up_yyHF_met);
				float PH_SCALE_LEAKAGECONV__1up_m_yy;                     myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.m_yy",                        &PH_SCALE_LEAKAGECONV__1up_m_yy);
				float PH_SCALE_LEAKAGECONV__1up_m_yyjj;                   myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.m_yyjj",                      &PH_SCALE_LEAKAGECONV__1up_m_yyjj);
				float PH_SCALE_LEAKAGECONV__1up_pT_yy;                    myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.pT_yy",                       &PH_SCALE_LEAKAGECONV__1up_pT_yy);
				float PH_SCALE_LEAKAGECONV__1up_HGamWeight;               myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.HGamWeight",                  &PH_SCALE_LEAKAGECONV__1up_HGamWeight);
				float PH_SCALE_LEAKAGECONV__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_subleadjet_pt",          &PH_SCALE_LEAKAGECONV__1up_yyHF_subleadjet_pt);
				float PH_SCALE_LEAKAGECONV__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_subleadjet_phi",         &PH_SCALE_LEAKAGECONV__1up_yyHF_subleadjet_phi);
				float PH_SCALE_LEAKAGECONV__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_subleadjet_m",           &PH_SCALE_LEAKAGECONV__1up_yyHF_subleadjet_m);
				float PH_SCALE_LEAKAGECONV__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_subleadjet_eta",         &PH_SCALE_LEAKAGECONV__1up_yyHF_subleadjet_eta);
				float PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_leadjet_pt",             &PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_pt);
				float PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_leadjet_phi",            &PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_phi);
				float PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_leadjet_m",              &PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_m);
				float PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_SCALE_LEAKAGECONV__1up.yyHF_leadjet_eta",            &PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_eta);
				int PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_leadjet_truthlabel",     &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_truthlabel);
				int PH_SCALE_LEAKAGEUNCONV__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_subleadjet_truthlabel",  &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_subleadjet_truthlabel);
				int PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_leadjet_btagbin",        &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_btagbin);
				int PH_SCALE_LEAKAGEUNCONV__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_subleadjet_btagbin",     &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_subleadjet_btagbin);
				int PH_SCALE_LEAKAGEUNCONV__1down_yyHF_Njet_central;          myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_Njet_central",           &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_Njet_central);
				int PH_SCALE_LEAKAGEUNCONV__1down_yyHF_cutFlow;               myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_cutFlow",                &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_cutFlow);
				int PH_SCALE_LEAKAGEUNCONV__1down_yyHF_nelectron;             myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_nelectron",              &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_nelectron);
				int PH_SCALE_LEAKAGEUNCONV__1down_yyHF_nmuon;                 myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_nmuon",                  &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_nmuon);
				bool PH_SCALE_LEAKAGEUNCONV__1down_isPassed;                  myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.isPassed",                    &PH_SCALE_LEAKAGEUNCONV__1down_isPassed);
				float PH_SCALE_LEAKAGEUNCONV__1down_yyHFjj_weight;            myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHFjj_weight",               &PH_SCALE_LEAKAGEUNCONV__1down_yyHFjj_weight);
				float PH_SCALE_LEAKAGEUNCONV__1down_yyHFj_weight;             myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHFj_weight",                &PH_SCALE_LEAKAGEUNCONV__1down_yyHFj_weight);
				float PH_SCALE_LEAKAGEUNCONV__1down_yyHF_met;                 myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_met",                    &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_met);
				float PH_SCALE_LEAKAGEUNCONV__1down_m_yy;                     myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.m_yy",                        &PH_SCALE_LEAKAGEUNCONV__1down_m_yy);
				float PH_SCALE_LEAKAGEUNCONV__1down_m_yyjj;                   myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.m_yyjj",                      &PH_SCALE_LEAKAGEUNCONV__1down_m_yyjj);
				float PH_SCALE_LEAKAGEUNCONV__1down_pT_yy;                    myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.pT_yy",                       &PH_SCALE_LEAKAGEUNCONV__1down_pT_yy);
				float PH_SCALE_LEAKAGEUNCONV__1down_HGamWeight;               myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.HGamWeight",                  &PH_SCALE_LEAKAGEUNCONV__1down_HGamWeight);
				float PH_SCALE_LEAKAGEUNCONV__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_subleadjet_pt",          &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_subleadjet_pt);
				float PH_SCALE_LEAKAGEUNCONV__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_subleadjet_phi",         &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_subleadjet_phi);
				float PH_SCALE_LEAKAGEUNCONV__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_subleadjet_m",           &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_subleadjet_m);
				float PH_SCALE_LEAKAGEUNCONV__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_subleadjet_eta",         &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_subleadjet_eta);
				float PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_leadjet_pt",             &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_pt);
				float PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_leadjet_phi",            &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_phi);
				float PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_leadjet_m",              &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_m);
				float PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1down.yyHF_leadjet_eta",            &PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_eta);
				int PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_leadjet_truthlabel",     &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_truthlabel);
				int PH_SCALE_LEAKAGEUNCONV__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_subleadjet_truthlabel",  &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_subleadjet_truthlabel);
				int PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_leadjet_btagbin",        &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_btagbin);
				int PH_SCALE_LEAKAGEUNCONV__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_subleadjet_btagbin",     &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_subleadjet_btagbin);
				int PH_SCALE_LEAKAGEUNCONV__1up_yyHF_Njet_central;          myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_Njet_central",           &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_Njet_central);
				int PH_SCALE_LEAKAGEUNCONV__1up_yyHF_cutFlow;               myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_cutFlow",                &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_cutFlow);
				int PH_SCALE_LEAKAGEUNCONV__1up_yyHF_nelectron;             myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_nelectron",              &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_nelectron);
				int PH_SCALE_LEAKAGEUNCONV__1up_yyHF_nmuon;                 myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_nmuon",                  &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_nmuon);
				bool PH_SCALE_LEAKAGEUNCONV__1up_isPassed;                  myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.isPassed",                    &PH_SCALE_LEAKAGEUNCONV__1up_isPassed);
				float PH_SCALE_LEAKAGEUNCONV__1up_yyHFjj_weight;            myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHFjj_weight",               &PH_SCALE_LEAKAGEUNCONV__1up_yyHFjj_weight);
				float PH_SCALE_LEAKAGEUNCONV__1up_yyHFj_weight;             myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHFj_weight",                &PH_SCALE_LEAKAGEUNCONV__1up_yyHFj_weight);
				float PH_SCALE_LEAKAGEUNCONV__1up_yyHF_met;                 myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_met",                    &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_met);
				float PH_SCALE_LEAKAGEUNCONV__1up_m_yy;                     myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.m_yy",                        &PH_SCALE_LEAKAGEUNCONV__1up_m_yy);
				float PH_SCALE_LEAKAGEUNCONV__1up_m_yyjj;                   myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.m_yyjj",                      &PH_SCALE_LEAKAGEUNCONV__1up_m_yyjj);
				float PH_SCALE_LEAKAGEUNCONV__1up_pT_yy;                    myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.pT_yy",                       &PH_SCALE_LEAKAGEUNCONV__1up_pT_yy);
				float PH_SCALE_LEAKAGEUNCONV__1up_HGamWeight;               myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.HGamWeight",                  &PH_SCALE_LEAKAGEUNCONV__1up_HGamWeight);
				float PH_SCALE_LEAKAGEUNCONV__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_subleadjet_pt",          &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_subleadjet_pt);
				float PH_SCALE_LEAKAGEUNCONV__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_subleadjet_phi",         &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_subleadjet_phi);
				float PH_SCALE_LEAKAGEUNCONV__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_subleadjet_m",           &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_subleadjet_m);
				float PH_SCALE_LEAKAGEUNCONV__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_subleadjet_eta",         &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_subleadjet_eta);
				float PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_leadjet_pt",             &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_pt);
				float PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_leadjet_phi",            &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_phi);
				float PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_leadjet_m",              &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_m);
				float PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("PH_SCALE_LEAKAGEUNCONV__1up.yyHF_leadjet_eta",            &PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_eta);


				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN0__1down = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN0__1down = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN0__1down = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN0__1down = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN0__1down = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN0__1down = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", "histll_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN0__1down = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", "histb_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN0__1down = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", "histc_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN0__1down = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", "histl_noMET_EG_SCALE_MATCRYO__ETABIN0__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN0__1up = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN0__1up = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN0__1up = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN0__1up = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN0__1up = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN0__1up = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", "histll_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN0__1up = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", "histb_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN0__1up = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", "histc_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN0__1up = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", "histl_noMET_EG_SCALE_MATCRYO__ETABIN0__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN1__1down = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN1__1down = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN1__1down = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN1__1down = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN1__1down = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN1__1down = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", "histll_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN1__1down = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", "histb_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN1__1down = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", "histc_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN1__1down = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", "histl_noMET_EG_SCALE_MATCRYO__ETABIN1__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN1__1up = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN1__1up = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN1__1up = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN1__1up = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN1__1up = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN1__1up = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", "histll_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN1__1up = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", "histb_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN1__1up = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", "histc_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN1__1up = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", "histl_noMET_EG_SCALE_MATCRYO__ETABIN1__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN10__1down = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN10__1down = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN10__1down = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN10__1down = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN10__1down = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN10__1down = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", "histll_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN10__1down = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", "histb_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN10__1down = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", "histc_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN10__1down = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", "histl_noMET_EG_SCALE_MATCRYO__ETABIN10__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN10__1up = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN10__1up = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN10__1up = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN10__1up = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN10__1up = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN10__1up = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", "histll_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN10__1up = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", "histb_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN10__1up = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", "histc_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN10__1up = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", "histl_noMET_EG_SCALE_MATCRYO__ETABIN10__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN11__1down = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN11__1down = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN11__1down = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN11__1down = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN11__1down = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN11__1down = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", "histll_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN11__1down = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", "histb_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN11__1down = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", "histc_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN11__1down = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", "histl_noMET_EG_SCALE_MATCRYO__ETABIN11__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN11__1up = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN11__1up = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN11__1up = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN11__1up = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN11__1up = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN11__1up = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", "histll_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN11__1up = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", "histb_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN11__1up = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", "histc_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN11__1up = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", "histl_noMET_EG_SCALE_MATCRYO__ETABIN11__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN2__1down = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN2__1down = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN2__1down = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN2__1down = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN2__1down = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN2__1down = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", "histll_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN2__1down = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", "histb_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN2__1down = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", "histc_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN2__1down = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", "histl_noMET_EG_SCALE_MATCRYO__ETABIN2__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN2__1up = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN2__1up = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN2__1up = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN2__1up = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN2__1up = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN2__1up = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", "histll_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN2__1up = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", "histb_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN2__1up = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", "histc_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN2__1up = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", "histl_noMET_EG_SCALE_MATCRYO__ETABIN2__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN3__1down = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN3__1down = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN3__1down = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN3__1down = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN3__1down = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN3__1down = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", "histll_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN3__1down = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", "histb_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN3__1down = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", "histc_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN3__1down = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", "histl_noMET_EG_SCALE_MATCRYO__ETABIN3__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN3__1up = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN3__1up = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN3__1up = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN3__1up = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN3__1up = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN3__1up = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", "histll_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN3__1up = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", "histb_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN3__1up = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", "histc_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN3__1up = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", "histl_noMET_EG_SCALE_MATCRYO__ETABIN3__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN4__1down = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN4__1down = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN4__1down = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN4__1down = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN4__1down = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN4__1down = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", "histll_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN4__1down = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", "histb_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN4__1down = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", "histc_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN4__1down = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", "histl_noMET_EG_SCALE_MATCRYO__ETABIN4__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN4__1up = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN4__1up = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN4__1up = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN4__1up = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN4__1up = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN4__1up = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", "histll_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN4__1up = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", "histb_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN4__1up = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", "histc_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN4__1up = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", "histl_noMET_EG_SCALE_MATCRYO__ETABIN4__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN5__1down = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN5__1down = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN5__1down = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN5__1down = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN5__1down = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN5__1down = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", "histll_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN5__1down = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", "histb_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN5__1down = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", "histc_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN5__1down = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", "histl_noMET_EG_SCALE_MATCRYO__ETABIN5__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN5__1up = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN5__1up = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN5__1up = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN5__1up = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN5__1up = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN5__1up = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", "histll_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN5__1up = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", "histb_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN5__1up = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", "histc_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN5__1up = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", "histl_noMET_EG_SCALE_MATCRYO__ETABIN5__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN6__1down = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN6__1down = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN6__1down = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN6__1down = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN6__1down = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN6__1down = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", "histll_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN6__1down = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", "histb_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN6__1down = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", "histc_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN6__1down = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", "histl_noMET_EG_SCALE_MATCRYO__ETABIN6__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN6__1up = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN6__1up = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN6__1up = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN6__1up = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN6__1up = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN6__1up = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", "histll_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN6__1up = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", "histb_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN6__1up = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", "histc_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN6__1up = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", "histl_noMET_EG_SCALE_MATCRYO__ETABIN6__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN7__1down = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN7__1down = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN7__1down = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN7__1down = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN7__1down = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN7__1down = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", "histll_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN7__1down = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", "histb_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN7__1down = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", "histc_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN7__1down = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", "histl_noMET_EG_SCALE_MATCRYO__ETABIN7__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN7__1up = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN7__1up = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN7__1up = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN7__1up = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN7__1up = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN7__1up = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", "histll_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN7__1up = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", "histb_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN7__1up = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", "histc_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN7__1up = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", "histl_noMET_EG_SCALE_MATCRYO__ETABIN7__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN8__1down = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN8__1down = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN8__1down = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN8__1down = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN8__1down = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN8__1down = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", "histll_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN8__1down = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", "histb_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN8__1down = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", "histc_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN8__1down = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", "histl_noMET_EG_SCALE_MATCRYO__ETABIN8__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN8__1up = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN8__1up = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN8__1up = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN8__1up = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN8__1up = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN8__1up = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", "histll_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN8__1up = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", "histb_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN8__1up = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", "histc_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN8__1up = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", "histl_noMET_EG_SCALE_MATCRYO__ETABIN8__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN9__1down = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN9__1down = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN9__1down = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN9__1down = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN9__1down = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN9__1down = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", "histll_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN9__1down = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", "histb_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN9__1down = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", "histc_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN9__1down = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", "histl_noMET_EG_SCALE_MATCRYO__ETABIN9__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_EG_SCALE_MATCRYO__ETABIN9__1up = new TH1F("histbb_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", "histbb_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_EG_SCALE_MATCRYO__ETABIN9__1up = new TH1F("histbc_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", "histbc_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_EG_SCALE_MATCRYO__ETABIN9__1up = new TH1F("histbl_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", "histbl_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_EG_SCALE_MATCRYO__ETABIN9__1up = new TH1F("histcc_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", "histcc_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_EG_SCALE_MATCRYO__ETABIN9__1up = new TH1F("histcl_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", "histcl_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_EG_SCALE_MATCRYO__ETABIN9__1up = new TH1F("histll_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", "histll_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_EG_SCALE_MATCRYO__ETABIN9__1up = new TH1F("histb_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", "histb_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_EG_SCALE_MATCRYO__ETABIN9__1up = new TH1F("histc_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", "histc_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_EG_SCALE_MATCRYO__ETABIN9__1up = new TH1F("histl_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", "histl_noMET_EG_SCALE_MATCRYO__ETABIN9__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_EFF_ID_Uncertainty__1down = new TH1F("histbb_noMET_PH_EFF_ID_Uncertainty__1down", "histbb_noMET_PH_EFF_ID_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_EFF_ID_Uncertainty__1down = new TH1F("histbc_noMET_PH_EFF_ID_Uncertainty__1down", "histbc_noMET_PH_EFF_ID_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_EFF_ID_Uncertainty__1down = new TH1F("histbl_noMET_PH_EFF_ID_Uncertainty__1down", "histbl_noMET_PH_EFF_ID_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_EFF_ID_Uncertainty__1down = new TH1F("histcc_noMET_PH_EFF_ID_Uncertainty__1down", "histcc_noMET_PH_EFF_ID_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_EFF_ID_Uncertainty__1down = new TH1F("histcl_noMET_PH_EFF_ID_Uncertainty__1down", "histcl_noMET_PH_EFF_ID_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_EFF_ID_Uncertainty__1down = new TH1F("histll_noMET_PH_EFF_ID_Uncertainty__1down", "histll_noMET_PH_EFF_ID_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_EFF_ID_Uncertainty__1down = new TH1F("histb_noMET_PH_EFF_ID_Uncertainty__1down", "histb_noMET_PH_EFF_ID_Uncertainty__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_EFF_ID_Uncertainty__1down = new TH1F("histc_noMET_PH_EFF_ID_Uncertainty__1down", "histc_noMET_PH_EFF_ID_Uncertainty__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_EFF_ID_Uncertainty__1down = new TH1F("histl_noMET_PH_EFF_ID_Uncertainty__1down", "histl_noMET_PH_EFF_ID_Uncertainty__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_EFF_ID_Uncertainty__1up = new TH1F("histbb_noMET_PH_EFF_ID_Uncertainty__1up", "histbb_noMET_PH_EFF_ID_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_EFF_ID_Uncertainty__1up = new TH1F("histbc_noMET_PH_EFF_ID_Uncertainty__1up", "histbc_noMET_PH_EFF_ID_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_EFF_ID_Uncertainty__1up = new TH1F("histbl_noMET_PH_EFF_ID_Uncertainty__1up", "histbl_noMET_PH_EFF_ID_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_EFF_ID_Uncertainty__1up = new TH1F("histcc_noMET_PH_EFF_ID_Uncertainty__1up", "histcc_noMET_PH_EFF_ID_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_EFF_ID_Uncertainty__1up = new TH1F("histcl_noMET_PH_EFF_ID_Uncertainty__1up", "histcl_noMET_PH_EFF_ID_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_EFF_ID_Uncertainty__1up = new TH1F("histll_noMET_PH_EFF_ID_Uncertainty__1up", "histll_noMET_PH_EFF_ID_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_EFF_ID_Uncertainty__1up = new TH1F("histb_noMET_PH_EFF_ID_Uncertainty__1up", "histb_noMET_PH_EFF_ID_Uncertainty__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_EFF_ID_Uncertainty__1up = new TH1F("histc_noMET_PH_EFF_ID_Uncertainty__1up", "histc_noMET_PH_EFF_ID_Uncertainty__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_EFF_ID_Uncertainty__1up = new TH1F("histl_noMET_PH_EFF_ID_Uncertainty__1up", "histl_noMET_PH_EFF_ID_Uncertainty__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_EFF_ISO_Uncertainty__1down = new TH1F("histbb_noMET_PH_EFF_ISO_Uncertainty__1down", "histbb_noMET_PH_EFF_ISO_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_EFF_ISO_Uncertainty__1down = new TH1F("histbc_noMET_PH_EFF_ISO_Uncertainty__1down", "histbc_noMET_PH_EFF_ISO_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_EFF_ISO_Uncertainty__1down = new TH1F("histbl_noMET_PH_EFF_ISO_Uncertainty__1down", "histbl_noMET_PH_EFF_ISO_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_EFF_ISO_Uncertainty__1down = new TH1F("histcc_noMET_PH_EFF_ISO_Uncertainty__1down", "histcc_noMET_PH_EFF_ISO_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_EFF_ISO_Uncertainty__1down = new TH1F("histcl_noMET_PH_EFF_ISO_Uncertainty__1down", "histcl_noMET_PH_EFF_ISO_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_EFF_ISO_Uncertainty__1down = new TH1F("histll_noMET_PH_EFF_ISO_Uncertainty__1down", "histll_noMET_PH_EFF_ISO_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_EFF_ISO_Uncertainty__1down = new TH1F("histb_noMET_PH_EFF_ISO_Uncertainty__1down", "histb_noMET_PH_EFF_ISO_Uncertainty__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_EFF_ISO_Uncertainty__1down = new TH1F("histc_noMET_PH_EFF_ISO_Uncertainty__1down", "histc_noMET_PH_EFF_ISO_Uncertainty__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_EFF_ISO_Uncertainty__1down = new TH1F("histl_noMET_PH_EFF_ISO_Uncertainty__1down", "histl_noMET_PH_EFF_ISO_Uncertainty__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_EFF_ISO_Uncertainty__1up = new TH1F("histbb_noMET_PH_EFF_ISO_Uncertainty__1up", "histbb_noMET_PH_EFF_ISO_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_EFF_ISO_Uncertainty__1up = new TH1F("histbc_noMET_PH_EFF_ISO_Uncertainty__1up", "histbc_noMET_PH_EFF_ISO_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_EFF_ISO_Uncertainty__1up = new TH1F("histbl_noMET_PH_EFF_ISO_Uncertainty__1up", "histbl_noMET_PH_EFF_ISO_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_EFF_ISO_Uncertainty__1up = new TH1F("histcc_noMET_PH_EFF_ISO_Uncertainty__1up", "histcc_noMET_PH_EFF_ISO_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_EFF_ISO_Uncertainty__1up = new TH1F("histcl_noMET_PH_EFF_ISO_Uncertainty__1up", "histcl_noMET_PH_EFF_ISO_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_EFF_ISO_Uncertainty__1up = new TH1F("histll_noMET_PH_EFF_ISO_Uncertainty__1up", "histll_noMET_PH_EFF_ISO_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_EFF_ISO_Uncertainty__1up = new TH1F("histb_noMET_PH_EFF_ISO_Uncertainty__1up", "histb_noMET_PH_EFF_ISO_Uncertainty__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_EFF_ISO_Uncertainty__1up = new TH1F("histc_noMET_PH_EFF_ISO_Uncertainty__1up", "histc_noMET_PH_EFF_ISO_Uncertainty__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_EFF_ISO_Uncertainty__1up = new TH1F("histl_noMET_PH_EFF_ISO_Uncertainty__1up", "histl_noMET_PH_EFF_ISO_Uncertainty__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_EFF_TRIGGER_Uncertainty__1down = new TH1F("histbb_noMET_PH_EFF_TRIGGER_Uncertainty__1down", "histbb_noMET_PH_EFF_TRIGGER_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_EFF_TRIGGER_Uncertainty__1down = new TH1F("histbc_noMET_PH_EFF_TRIGGER_Uncertainty__1down", "histbc_noMET_PH_EFF_TRIGGER_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_EFF_TRIGGER_Uncertainty__1down = new TH1F("histbl_noMET_PH_EFF_TRIGGER_Uncertainty__1down", "histbl_noMET_PH_EFF_TRIGGER_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_EFF_TRIGGER_Uncertainty__1down = new TH1F("histcc_noMET_PH_EFF_TRIGGER_Uncertainty__1down", "histcc_noMET_PH_EFF_TRIGGER_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_EFF_TRIGGER_Uncertainty__1down = new TH1F("histcl_noMET_PH_EFF_TRIGGER_Uncertainty__1down", "histcl_noMET_PH_EFF_TRIGGER_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_EFF_TRIGGER_Uncertainty__1down = new TH1F("histll_noMET_PH_EFF_TRIGGER_Uncertainty__1down", "histll_noMET_PH_EFF_TRIGGER_Uncertainty__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_EFF_TRIGGER_Uncertainty__1down = new TH1F("histb_noMET_PH_EFF_TRIGGER_Uncertainty__1down", "histb_noMET_PH_EFF_TRIGGER_Uncertainty__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_EFF_TRIGGER_Uncertainty__1down = new TH1F("histc_noMET_PH_EFF_TRIGGER_Uncertainty__1down", "histc_noMET_PH_EFF_TRIGGER_Uncertainty__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_EFF_TRIGGER_Uncertainty__1down = new TH1F("histl_noMET_PH_EFF_TRIGGER_Uncertainty__1down", "histl_noMET_PH_EFF_TRIGGER_Uncertainty__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_EFF_TRIGGER_Uncertainty__1up = new TH1F("histbb_noMET_PH_EFF_TRIGGER_Uncertainty__1up", "histbb_noMET_PH_EFF_TRIGGER_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_EFF_TRIGGER_Uncertainty__1up = new TH1F("histbc_noMET_PH_EFF_TRIGGER_Uncertainty__1up", "histbc_noMET_PH_EFF_TRIGGER_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_EFF_TRIGGER_Uncertainty__1up = new TH1F("histbl_noMET_PH_EFF_TRIGGER_Uncertainty__1up", "histbl_noMET_PH_EFF_TRIGGER_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_EFF_TRIGGER_Uncertainty__1up = new TH1F("histcc_noMET_PH_EFF_TRIGGER_Uncertainty__1up", "histcc_noMET_PH_EFF_TRIGGER_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_EFF_TRIGGER_Uncertainty__1up = new TH1F("histcl_noMET_PH_EFF_TRIGGER_Uncertainty__1up", "histcl_noMET_PH_EFF_TRIGGER_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_EFF_TRIGGER_Uncertainty__1up = new TH1F("histll_noMET_PH_EFF_TRIGGER_Uncertainty__1up", "histll_noMET_PH_EFF_TRIGGER_Uncertainty__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_EFF_TRIGGER_Uncertainty__1up = new TH1F("histb_noMET_PH_EFF_TRIGGER_Uncertainty__1up", "histb_noMET_PH_EFF_TRIGGER_Uncertainty__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_EFF_TRIGGER_Uncertainty__1up = new TH1F("histc_noMET_PH_EFF_TRIGGER_Uncertainty__1up", "histc_noMET_PH_EFF_TRIGGER_Uncertainty__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_EFF_TRIGGER_Uncertainty__1up = new TH1F("histl_noMET_PH_EFF_TRIGGER_Uncertainty__1up", "histl_noMET_PH_EFF_TRIGGER_Uncertainty__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_SCALE_CONVEFFICIENCY__1down = new TH1F("histbb_noMET_PH_SCALE_CONVEFFICIENCY__1down", "histbb_noMET_PH_SCALE_CONVEFFICIENCY__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_SCALE_CONVEFFICIENCY__1down = new TH1F("histbc_noMET_PH_SCALE_CONVEFFICIENCY__1down", "histbc_noMET_PH_SCALE_CONVEFFICIENCY__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_SCALE_CONVEFFICIENCY__1down = new TH1F("histbl_noMET_PH_SCALE_CONVEFFICIENCY__1down", "histbl_noMET_PH_SCALE_CONVEFFICIENCY__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_SCALE_CONVEFFICIENCY__1down = new TH1F("histcc_noMET_PH_SCALE_CONVEFFICIENCY__1down", "histcc_noMET_PH_SCALE_CONVEFFICIENCY__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_SCALE_CONVEFFICIENCY__1down = new TH1F("histcl_noMET_PH_SCALE_CONVEFFICIENCY__1down", "histcl_noMET_PH_SCALE_CONVEFFICIENCY__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_SCALE_CONVEFFICIENCY__1down = new TH1F("histll_noMET_PH_SCALE_CONVEFFICIENCY__1down", "histll_noMET_PH_SCALE_CONVEFFICIENCY__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_SCALE_CONVEFFICIENCY__1down = new TH1F("histb_noMET_PH_SCALE_CONVEFFICIENCY__1down", "histb_noMET_PH_SCALE_CONVEFFICIENCY__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_SCALE_CONVEFFICIENCY__1down = new TH1F("histc_noMET_PH_SCALE_CONVEFFICIENCY__1down", "histc_noMET_PH_SCALE_CONVEFFICIENCY__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_SCALE_CONVEFFICIENCY__1down = new TH1F("histl_noMET_PH_SCALE_CONVEFFICIENCY__1down", "histl_noMET_PH_SCALE_CONVEFFICIENCY__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_SCALE_CONVEFFICIENCY__1up = new TH1F("histbb_noMET_PH_SCALE_CONVEFFICIENCY__1up", "histbb_noMET_PH_SCALE_CONVEFFICIENCY__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_SCALE_CONVEFFICIENCY__1up = new TH1F("histbc_noMET_PH_SCALE_CONVEFFICIENCY__1up", "histbc_noMET_PH_SCALE_CONVEFFICIENCY__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_SCALE_CONVEFFICIENCY__1up = new TH1F("histbl_noMET_PH_SCALE_CONVEFFICIENCY__1up", "histbl_noMET_PH_SCALE_CONVEFFICIENCY__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_SCALE_CONVEFFICIENCY__1up = new TH1F("histcc_noMET_PH_SCALE_CONVEFFICIENCY__1up", "histcc_noMET_PH_SCALE_CONVEFFICIENCY__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_SCALE_CONVEFFICIENCY__1up = new TH1F("histcl_noMET_PH_SCALE_CONVEFFICIENCY__1up", "histcl_noMET_PH_SCALE_CONVEFFICIENCY__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_SCALE_CONVEFFICIENCY__1up = new TH1F("histll_noMET_PH_SCALE_CONVEFFICIENCY__1up", "histll_noMET_PH_SCALE_CONVEFFICIENCY__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_SCALE_CONVEFFICIENCY__1up = new TH1F("histb_noMET_PH_SCALE_CONVEFFICIENCY__1up", "histb_noMET_PH_SCALE_CONVEFFICIENCY__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_SCALE_CONVEFFICIENCY__1up = new TH1F("histc_noMET_PH_SCALE_CONVEFFICIENCY__1up", "histc_noMET_PH_SCALE_CONVEFFICIENCY__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_SCALE_CONVEFFICIENCY__1up = new TH1F("histl_noMET_PH_SCALE_CONVEFFICIENCY__1up", "histl_noMET_PH_SCALE_CONVEFFICIENCY__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_SCALE_CONVFAKERATE__1down = new TH1F("histbb_noMET_PH_SCALE_CONVFAKERATE__1down", "histbb_noMET_PH_SCALE_CONVFAKERATE__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_SCALE_CONVFAKERATE__1down = new TH1F("histbc_noMET_PH_SCALE_CONVFAKERATE__1down", "histbc_noMET_PH_SCALE_CONVFAKERATE__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_SCALE_CONVFAKERATE__1down = new TH1F("histbl_noMET_PH_SCALE_CONVFAKERATE__1down", "histbl_noMET_PH_SCALE_CONVFAKERATE__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_SCALE_CONVFAKERATE__1down = new TH1F("histcc_noMET_PH_SCALE_CONVFAKERATE__1down", "histcc_noMET_PH_SCALE_CONVFAKERATE__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_SCALE_CONVFAKERATE__1down = new TH1F("histcl_noMET_PH_SCALE_CONVFAKERATE__1down", "histcl_noMET_PH_SCALE_CONVFAKERATE__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_SCALE_CONVFAKERATE__1down = new TH1F("histll_noMET_PH_SCALE_CONVFAKERATE__1down", "histll_noMET_PH_SCALE_CONVFAKERATE__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_SCALE_CONVFAKERATE__1down = new TH1F("histb_noMET_PH_SCALE_CONVFAKERATE__1down", "histb_noMET_PH_SCALE_CONVFAKERATE__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_SCALE_CONVFAKERATE__1down = new TH1F("histc_noMET_PH_SCALE_CONVFAKERATE__1down", "histc_noMET_PH_SCALE_CONVFAKERATE__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_SCALE_CONVFAKERATE__1down = new TH1F("histl_noMET_PH_SCALE_CONVFAKERATE__1down", "histl_noMET_PH_SCALE_CONVFAKERATE__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_SCALE_CONVFAKERATE__1up = new TH1F("histbb_noMET_PH_SCALE_CONVFAKERATE__1up", "histbb_noMET_PH_SCALE_CONVFAKERATE__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_SCALE_CONVFAKERATE__1up = new TH1F("histbc_noMET_PH_SCALE_CONVFAKERATE__1up", "histbc_noMET_PH_SCALE_CONVFAKERATE__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_SCALE_CONVFAKERATE__1up = new TH1F("histbl_noMET_PH_SCALE_CONVFAKERATE__1up", "histbl_noMET_PH_SCALE_CONVFAKERATE__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_SCALE_CONVFAKERATE__1up = new TH1F("histcc_noMET_PH_SCALE_CONVFAKERATE__1up", "histcc_noMET_PH_SCALE_CONVFAKERATE__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_SCALE_CONVFAKERATE__1up = new TH1F("histcl_noMET_PH_SCALE_CONVFAKERATE__1up", "histcl_noMET_PH_SCALE_CONVFAKERATE__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_SCALE_CONVFAKERATE__1up = new TH1F("histll_noMET_PH_SCALE_CONVFAKERATE__1up", "histll_noMET_PH_SCALE_CONVFAKERATE__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_SCALE_CONVFAKERATE__1up = new TH1F("histb_noMET_PH_SCALE_CONVFAKERATE__1up", "histb_noMET_PH_SCALE_CONVFAKERATE__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_SCALE_CONVFAKERATE__1up = new TH1F("histc_noMET_PH_SCALE_CONVFAKERATE__1up", "histc_noMET_PH_SCALE_CONVFAKERATE__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_SCALE_CONVFAKERATE__1up = new TH1F("histl_noMET_PH_SCALE_CONVFAKERATE__1up", "histl_noMET_PH_SCALE_CONVFAKERATE__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_SCALE_CONVRADIUS__1down = new TH1F("histbb_noMET_PH_SCALE_CONVRADIUS__1down", "histbb_noMET_PH_SCALE_CONVRADIUS__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_SCALE_CONVRADIUS__1down = new TH1F("histbc_noMET_PH_SCALE_CONVRADIUS__1down", "histbc_noMET_PH_SCALE_CONVRADIUS__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_SCALE_CONVRADIUS__1down = new TH1F("histbl_noMET_PH_SCALE_CONVRADIUS__1down", "histbl_noMET_PH_SCALE_CONVRADIUS__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_SCALE_CONVRADIUS__1down = new TH1F("histcc_noMET_PH_SCALE_CONVRADIUS__1down", "histcc_noMET_PH_SCALE_CONVRADIUS__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_SCALE_CONVRADIUS__1down = new TH1F("histcl_noMET_PH_SCALE_CONVRADIUS__1down", "histcl_noMET_PH_SCALE_CONVRADIUS__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_SCALE_CONVRADIUS__1down = new TH1F("histll_noMET_PH_SCALE_CONVRADIUS__1down", "histll_noMET_PH_SCALE_CONVRADIUS__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_SCALE_CONVRADIUS__1down = new TH1F("histb_noMET_PH_SCALE_CONVRADIUS__1down", "histb_noMET_PH_SCALE_CONVRADIUS__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_SCALE_CONVRADIUS__1down = new TH1F("histc_noMET_PH_SCALE_CONVRADIUS__1down", "histc_noMET_PH_SCALE_CONVRADIUS__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_SCALE_CONVRADIUS__1down = new TH1F("histl_noMET_PH_SCALE_CONVRADIUS__1down", "histl_noMET_PH_SCALE_CONVRADIUS__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_SCALE_CONVRADIUS__1up = new TH1F("histbb_noMET_PH_SCALE_CONVRADIUS__1up", "histbb_noMET_PH_SCALE_CONVRADIUS__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_SCALE_CONVRADIUS__1up = new TH1F("histbc_noMET_PH_SCALE_CONVRADIUS__1up", "histbc_noMET_PH_SCALE_CONVRADIUS__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_SCALE_CONVRADIUS__1up = new TH1F("histbl_noMET_PH_SCALE_CONVRADIUS__1up", "histbl_noMET_PH_SCALE_CONVRADIUS__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_SCALE_CONVRADIUS__1up = new TH1F("histcc_noMET_PH_SCALE_CONVRADIUS__1up", "histcc_noMET_PH_SCALE_CONVRADIUS__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_SCALE_CONVRADIUS__1up = new TH1F("histcl_noMET_PH_SCALE_CONVRADIUS__1up", "histcl_noMET_PH_SCALE_CONVRADIUS__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_SCALE_CONVRADIUS__1up = new TH1F("histll_noMET_PH_SCALE_CONVRADIUS__1up", "histll_noMET_PH_SCALE_CONVRADIUS__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_SCALE_CONVRADIUS__1up = new TH1F("histb_noMET_PH_SCALE_CONVRADIUS__1up", "histb_noMET_PH_SCALE_CONVRADIUS__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_SCALE_CONVRADIUS__1up = new TH1F("histc_noMET_PH_SCALE_CONVRADIUS__1up", "histc_noMET_PH_SCALE_CONVRADIUS__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_SCALE_CONVRADIUS__1up = new TH1F("histl_noMET_PH_SCALE_CONVRADIUS__1up", "histl_noMET_PH_SCALE_CONVRADIUS__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_SCALE_LEAKAGECONV__1down = new TH1F("histbb_noMET_PH_SCALE_LEAKAGECONV__1down", "histbb_noMET_PH_SCALE_LEAKAGECONV__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_SCALE_LEAKAGECONV__1down = new TH1F("histbc_noMET_PH_SCALE_LEAKAGECONV__1down", "histbc_noMET_PH_SCALE_LEAKAGECONV__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_SCALE_LEAKAGECONV__1down = new TH1F("histbl_noMET_PH_SCALE_LEAKAGECONV__1down", "histbl_noMET_PH_SCALE_LEAKAGECONV__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_SCALE_LEAKAGECONV__1down = new TH1F("histcc_noMET_PH_SCALE_LEAKAGECONV__1down", "histcc_noMET_PH_SCALE_LEAKAGECONV__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_SCALE_LEAKAGECONV__1down = new TH1F("histcl_noMET_PH_SCALE_LEAKAGECONV__1down", "histcl_noMET_PH_SCALE_LEAKAGECONV__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_SCALE_LEAKAGECONV__1down = new TH1F("histll_noMET_PH_SCALE_LEAKAGECONV__1down", "histll_noMET_PH_SCALE_LEAKAGECONV__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_SCALE_LEAKAGECONV__1down = new TH1F("histb_noMET_PH_SCALE_LEAKAGECONV__1down", "histb_noMET_PH_SCALE_LEAKAGECONV__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_SCALE_LEAKAGECONV__1down = new TH1F("histc_noMET_PH_SCALE_LEAKAGECONV__1down", "histc_noMET_PH_SCALE_LEAKAGECONV__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_SCALE_LEAKAGECONV__1down = new TH1F("histl_noMET_PH_SCALE_LEAKAGECONV__1down", "histl_noMET_PH_SCALE_LEAKAGECONV__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_SCALE_LEAKAGECONV__1up = new TH1F("histbb_noMET_PH_SCALE_LEAKAGECONV__1up", "histbb_noMET_PH_SCALE_LEAKAGECONV__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_SCALE_LEAKAGECONV__1up = new TH1F("histbc_noMET_PH_SCALE_LEAKAGECONV__1up", "histbc_noMET_PH_SCALE_LEAKAGECONV__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_SCALE_LEAKAGECONV__1up = new TH1F("histbl_noMET_PH_SCALE_LEAKAGECONV__1up", "histbl_noMET_PH_SCALE_LEAKAGECONV__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_SCALE_LEAKAGECONV__1up = new TH1F("histcc_noMET_PH_SCALE_LEAKAGECONV__1up", "histcc_noMET_PH_SCALE_LEAKAGECONV__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_SCALE_LEAKAGECONV__1up = new TH1F("histcl_noMET_PH_SCALE_LEAKAGECONV__1up", "histcl_noMET_PH_SCALE_LEAKAGECONV__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_SCALE_LEAKAGECONV__1up = new TH1F("histll_noMET_PH_SCALE_LEAKAGECONV__1up", "histll_noMET_PH_SCALE_LEAKAGECONV__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_SCALE_LEAKAGECONV__1up = new TH1F("histb_noMET_PH_SCALE_LEAKAGECONV__1up", "histb_noMET_PH_SCALE_LEAKAGECONV__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_SCALE_LEAKAGECONV__1up = new TH1F("histc_noMET_PH_SCALE_LEAKAGECONV__1up", "histc_noMET_PH_SCALE_LEAKAGECONV__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_SCALE_LEAKAGECONV__1up = new TH1F("histl_noMET_PH_SCALE_LEAKAGECONV__1up", "histl_noMET_PH_SCALE_LEAKAGECONV__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_SCALE_LEAKAGEUNCONV__1down = new TH1F("histbb_noMET_PH_SCALE_LEAKAGEUNCONV__1down", "histbb_noMET_PH_SCALE_LEAKAGEUNCONV__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_SCALE_LEAKAGEUNCONV__1down = new TH1F("histbc_noMET_PH_SCALE_LEAKAGEUNCONV__1down", "histbc_noMET_PH_SCALE_LEAKAGEUNCONV__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_SCALE_LEAKAGEUNCONV__1down = new TH1F("histbl_noMET_PH_SCALE_LEAKAGEUNCONV__1down", "histbl_noMET_PH_SCALE_LEAKAGEUNCONV__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_SCALE_LEAKAGEUNCONV__1down = new TH1F("histcc_noMET_PH_SCALE_LEAKAGEUNCONV__1down", "histcc_noMET_PH_SCALE_LEAKAGEUNCONV__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_SCALE_LEAKAGEUNCONV__1down = new TH1F("histcl_noMET_PH_SCALE_LEAKAGEUNCONV__1down", "histcl_noMET_PH_SCALE_LEAKAGEUNCONV__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_SCALE_LEAKAGEUNCONV__1down = new TH1F("histll_noMET_PH_SCALE_LEAKAGEUNCONV__1down", "histll_noMET_PH_SCALE_LEAKAGEUNCONV__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_SCALE_LEAKAGEUNCONV__1down = new TH1F("histb_noMET_PH_SCALE_LEAKAGEUNCONV__1down", "histb_noMET_PH_SCALE_LEAKAGEUNCONV__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_SCALE_LEAKAGEUNCONV__1down = new TH1F("histc_noMET_PH_SCALE_LEAKAGEUNCONV__1down", "histc_noMET_PH_SCALE_LEAKAGEUNCONV__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_SCALE_LEAKAGEUNCONV__1down = new TH1F("histl_noMET_PH_SCALE_LEAKAGEUNCONV__1down", "histl_noMET_PH_SCALE_LEAKAGEUNCONV__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_PH_SCALE_LEAKAGEUNCONV__1up = new TH1F("histbb_noMET_PH_SCALE_LEAKAGEUNCONV__1up", "histbb_noMET_PH_SCALE_LEAKAGEUNCONV__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_PH_SCALE_LEAKAGEUNCONV__1up = new TH1F("histbc_noMET_PH_SCALE_LEAKAGEUNCONV__1up", "histbc_noMET_PH_SCALE_LEAKAGEUNCONV__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_PH_SCALE_LEAKAGEUNCONV__1up = new TH1F("histbl_noMET_PH_SCALE_LEAKAGEUNCONV__1up", "histbl_noMET_PH_SCALE_LEAKAGEUNCONV__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_PH_SCALE_LEAKAGEUNCONV__1up = new TH1F("histcc_noMET_PH_SCALE_LEAKAGEUNCONV__1up", "histcc_noMET_PH_SCALE_LEAKAGEUNCONV__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_PH_SCALE_LEAKAGEUNCONV__1up = new TH1F("histcl_noMET_PH_SCALE_LEAKAGEUNCONV__1up", "histcl_noMET_PH_SCALE_LEAKAGEUNCONV__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_PH_SCALE_LEAKAGEUNCONV__1up = new TH1F("histll_noMET_PH_SCALE_LEAKAGEUNCONV__1up", "histll_noMET_PH_SCALE_LEAKAGEUNCONV__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_PH_SCALE_LEAKAGEUNCONV__1up = new TH1F("histb_noMET_PH_SCALE_LEAKAGEUNCONV__1up", "histb_noMET_PH_SCALE_LEAKAGEUNCONV__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_PH_SCALE_LEAKAGEUNCONV__1up = new TH1F("histc_noMET_PH_SCALE_LEAKAGEUNCONV__1up", "histc_noMET_PH_SCALE_LEAKAGEUNCONV__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_PH_SCALE_LEAKAGEUNCONV__1up = new TH1F("histl_noMET_PH_SCALE_LEAKAGEUNCONV__1up", "histl_noMET_PH_SCALE_LEAKAGEUNCONV__1up", 5, -0.5, 4.5);
				

				float lumi_mc16 = 0;
				if (mc == "mc16a"){lumi_mc16 = 36205.26;}
				if (mc == "mc16d"){lumi_mc16 = 44307.4;}
				if (mc == "mc16e"){lumi_mc16 = 58450.1;}

				double sumweights = (myCutflow->GetBinContent(1) / myCutflow->GetBinContent(2) ) * myCutflow->GetBinContent(3);
				cout << sumweights << endl;

				// nEntries = 100;
				// cout << "running over " << nEntries << " events" << endl;
				for (int i = 0; i < nEntries; i++){
					if (i % 100000 == 0){cout << i << " / " << nEntries << endl;}
					myTree->GetEntry(i);

					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN0__1down, histbc_noMET_EG_SCALE_MATCRYO__ETABIN0__1down, histbl_noMET_EG_SCALE_MATCRYO__ETABIN0__1down, histcc_noMET_EG_SCALE_MATCRYO__ETABIN0__1down, histcl_noMET_EG_SCALE_MATCRYO__ETABIN0__1down, histll_noMET_EG_SCALE_MATCRYO__ETABIN0__1down,
							   EG_SCALE_MATCRYO__ETABIN0__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN0__1down_isPassed, EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN0__1down_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN0__1down_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN0__1up, histbc_noMET_EG_SCALE_MATCRYO__ETABIN0__1up, histbl_noMET_EG_SCALE_MATCRYO__ETABIN0__1up, histcc_noMET_EG_SCALE_MATCRYO__ETABIN0__1up, histcl_noMET_EG_SCALE_MATCRYO__ETABIN0__1up, histll_noMET_EG_SCALE_MATCRYO__ETABIN0__1up,
							   EG_SCALE_MATCRYO__ETABIN0__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN0__1up_isPassed, EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN0__1up_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN0__1up_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN1__1down, histbc_noMET_EG_SCALE_MATCRYO__ETABIN1__1down, histbl_noMET_EG_SCALE_MATCRYO__ETABIN1__1down, histcc_noMET_EG_SCALE_MATCRYO__ETABIN1__1down, histcl_noMET_EG_SCALE_MATCRYO__ETABIN1__1down, histll_noMET_EG_SCALE_MATCRYO__ETABIN1__1down,
							   EG_SCALE_MATCRYO__ETABIN1__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN1__1down_isPassed, EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN1__1down_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN1__1down_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN1__1up, histbc_noMET_EG_SCALE_MATCRYO__ETABIN1__1up, histbl_noMET_EG_SCALE_MATCRYO__ETABIN1__1up, histcc_noMET_EG_SCALE_MATCRYO__ETABIN1__1up, histcl_noMET_EG_SCALE_MATCRYO__ETABIN1__1up, histll_noMET_EG_SCALE_MATCRYO__ETABIN1__1up,
							   EG_SCALE_MATCRYO__ETABIN1__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN1__1up_isPassed, EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN1__1up_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN1__1up_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN10__1down, histbc_noMET_EG_SCALE_MATCRYO__ETABIN10__1down, histbl_noMET_EG_SCALE_MATCRYO__ETABIN10__1down, histcc_noMET_EG_SCALE_MATCRYO__ETABIN10__1down, histcl_noMET_EG_SCALE_MATCRYO__ETABIN10__1down, histll_noMET_EG_SCALE_MATCRYO__ETABIN10__1down,
							   EG_SCALE_MATCRYO__ETABIN10__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN10__1down_isPassed, EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN10__1down_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN10__1down_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN10__1up, histbc_noMET_EG_SCALE_MATCRYO__ETABIN10__1up, histbl_noMET_EG_SCALE_MATCRYO__ETABIN10__1up, histcc_noMET_EG_SCALE_MATCRYO__ETABIN10__1up, histcl_noMET_EG_SCALE_MATCRYO__ETABIN10__1up, histll_noMET_EG_SCALE_MATCRYO__ETABIN10__1up,
							   EG_SCALE_MATCRYO__ETABIN10__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN10__1up_isPassed, EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN10__1up_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN10__1up_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN11__1down, histbc_noMET_EG_SCALE_MATCRYO__ETABIN11__1down, histbl_noMET_EG_SCALE_MATCRYO__ETABIN11__1down, histcc_noMET_EG_SCALE_MATCRYO__ETABIN11__1down, histcl_noMET_EG_SCALE_MATCRYO__ETABIN11__1down, histll_noMET_EG_SCALE_MATCRYO__ETABIN11__1down,
							   EG_SCALE_MATCRYO__ETABIN11__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN11__1down_isPassed, EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN11__1down_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN11__1down_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN11__1up, histbc_noMET_EG_SCALE_MATCRYO__ETABIN11__1up, histbl_noMET_EG_SCALE_MATCRYO__ETABIN11__1up, histcc_noMET_EG_SCALE_MATCRYO__ETABIN11__1up, histcl_noMET_EG_SCALE_MATCRYO__ETABIN11__1up, histll_noMET_EG_SCALE_MATCRYO__ETABIN11__1up,
							   EG_SCALE_MATCRYO__ETABIN11__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN11__1up_isPassed, EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN11__1up_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN11__1up_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN2__1down, histbc_noMET_EG_SCALE_MATCRYO__ETABIN2__1down, histbl_noMET_EG_SCALE_MATCRYO__ETABIN2__1down, histcc_noMET_EG_SCALE_MATCRYO__ETABIN2__1down, histcl_noMET_EG_SCALE_MATCRYO__ETABIN2__1down, histll_noMET_EG_SCALE_MATCRYO__ETABIN2__1down,
							   EG_SCALE_MATCRYO__ETABIN2__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN2__1down_isPassed, EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN2__1down_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN2__1down_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN2__1up, histbc_noMET_EG_SCALE_MATCRYO__ETABIN2__1up, histbl_noMET_EG_SCALE_MATCRYO__ETABIN2__1up, histcc_noMET_EG_SCALE_MATCRYO__ETABIN2__1up, histcl_noMET_EG_SCALE_MATCRYO__ETABIN2__1up, histll_noMET_EG_SCALE_MATCRYO__ETABIN2__1up,
							   EG_SCALE_MATCRYO__ETABIN2__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN2__1up_isPassed, EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN2__1up_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN2__1up_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN3__1down, histbc_noMET_EG_SCALE_MATCRYO__ETABIN3__1down, histbl_noMET_EG_SCALE_MATCRYO__ETABIN3__1down, histcc_noMET_EG_SCALE_MATCRYO__ETABIN3__1down, histcl_noMET_EG_SCALE_MATCRYO__ETABIN3__1down, histll_noMET_EG_SCALE_MATCRYO__ETABIN3__1down,
							   EG_SCALE_MATCRYO__ETABIN3__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN3__1down_isPassed, EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN3__1down_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN3__1down_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN3__1up, histbc_noMET_EG_SCALE_MATCRYO__ETABIN3__1up, histbl_noMET_EG_SCALE_MATCRYO__ETABIN3__1up, histcc_noMET_EG_SCALE_MATCRYO__ETABIN3__1up, histcl_noMET_EG_SCALE_MATCRYO__ETABIN3__1up, histll_noMET_EG_SCALE_MATCRYO__ETABIN3__1up,
							   EG_SCALE_MATCRYO__ETABIN3__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN3__1up_isPassed, EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN3__1up_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN3__1up_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN4__1down, histbc_noMET_EG_SCALE_MATCRYO__ETABIN4__1down, histbl_noMET_EG_SCALE_MATCRYO__ETABIN4__1down, histcc_noMET_EG_SCALE_MATCRYO__ETABIN4__1down, histcl_noMET_EG_SCALE_MATCRYO__ETABIN4__1down, histll_noMET_EG_SCALE_MATCRYO__ETABIN4__1down,
							   EG_SCALE_MATCRYO__ETABIN4__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN4__1down_isPassed, EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN4__1down_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN4__1down_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN4__1up, histbc_noMET_EG_SCALE_MATCRYO__ETABIN4__1up, histbl_noMET_EG_SCALE_MATCRYO__ETABIN4__1up, histcc_noMET_EG_SCALE_MATCRYO__ETABIN4__1up, histcl_noMET_EG_SCALE_MATCRYO__ETABIN4__1up, histll_noMET_EG_SCALE_MATCRYO__ETABIN4__1up,
							   EG_SCALE_MATCRYO__ETABIN4__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN4__1up_isPassed, EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN4__1up_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN4__1up_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN5__1down, histbc_noMET_EG_SCALE_MATCRYO__ETABIN5__1down, histbl_noMET_EG_SCALE_MATCRYO__ETABIN5__1down, histcc_noMET_EG_SCALE_MATCRYO__ETABIN5__1down, histcl_noMET_EG_SCALE_MATCRYO__ETABIN5__1down, histll_noMET_EG_SCALE_MATCRYO__ETABIN5__1down,
							   EG_SCALE_MATCRYO__ETABIN5__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN5__1down_isPassed, EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN5__1down_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN5__1down_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN5__1up, histbc_noMET_EG_SCALE_MATCRYO__ETABIN5__1up, histbl_noMET_EG_SCALE_MATCRYO__ETABIN5__1up, histcc_noMET_EG_SCALE_MATCRYO__ETABIN5__1up, histcl_noMET_EG_SCALE_MATCRYO__ETABIN5__1up, histll_noMET_EG_SCALE_MATCRYO__ETABIN5__1up,
							   EG_SCALE_MATCRYO__ETABIN5__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN5__1up_isPassed, EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN5__1up_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN5__1up_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN6__1down, histbc_noMET_EG_SCALE_MATCRYO__ETABIN6__1down, histbl_noMET_EG_SCALE_MATCRYO__ETABIN6__1down, histcc_noMET_EG_SCALE_MATCRYO__ETABIN6__1down, histcl_noMET_EG_SCALE_MATCRYO__ETABIN6__1down, histll_noMET_EG_SCALE_MATCRYO__ETABIN6__1down,
							   EG_SCALE_MATCRYO__ETABIN6__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN6__1down_isPassed, EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN6__1down_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN6__1down_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN6__1up, histbc_noMET_EG_SCALE_MATCRYO__ETABIN6__1up, histbl_noMET_EG_SCALE_MATCRYO__ETABIN6__1up, histcc_noMET_EG_SCALE_MATCRYO__ETABIN6__1up, histcl_noMET_EG_SCALE_MATCRYO__ETABIN6__1up, histll_noMET_EG_SCALE_MATCRYO__ETABIN6__1up,
							   EG_SCALE_MATCRYO__ETABIN6__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN6__1up_isPassed, EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN6__1up_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN6__1up_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN7__1down, histbc_noMET_EG_SCALE_MATCRYO__ETABIN7__1down, histbl_noMET_EG_SCALE_MATCRYO__ETABIN7__1down, histcc_noMET_EG_SCALE_MATCRYO__ETABIN7__1down, histcl_noMET_EG_SCALE_MATCRYO__ETABIN7__1down, histll_noMET_EG_SCALE_MATCRYO__ETABIN7__1down,
							   EG_SCALE_MATCRYO__ETABIN7__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN7__1down_isPassed, EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN7__1down_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN7__1down_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN7__1up, histbc_noMET_EG_SCALE_MATCRYO__ETABIN7__1up, histbl_noMET_EG_SCALE_MATCRYO__ETABIN7__1up, histcc_noMET_EG_SCALE_MATCRYO__ETABIN7__1up, histcl_noMET_EG_SCALE_MATCRYO__ETABIN7__1up, histll_noMET_EG_SCALE_MATCRYO__ETABIN7__1up,
							   EG_SCALE_MATCRYO__ETABIN7__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN7__1up_isPassed, EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN7__1up_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN7__1up_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN8__1down, histbc_noMET_EG_SCALE_MATCRYO__ETABIN8__1down, histbl_noMET_EG_SCALE_MATCRYO__ETABIN8__1down, histcc_noMET_EG_SCALE_MATCRYO__ETABIN8__1down, histcl_noMET_EG_SCALE_MATCRYO__ETABIN8__1down, histll_noMET_EG_SCALE_MATCRYO__ETABIN8__1down,
							   EG_SCALE_MATCRYO__ETABIN8__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN8__1down_isPassed, EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN8__1down_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN8__1down_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN8__1up, histbc_noMET_EG_SCALE_MATCRYO__ETABIN8__1up, histbl_noMET_EG_SCALE_MATCRYO__ETABIN8__1up, histcc_noMET_EG_SCALE_MATCRYO__ETABIN8__1up, histcl_noMET_EG_SCALE_MATCRYO__ETABIN8__1up, histll_noMET_EG_SCALE_MATCRYO__ETABIN8__1up,
							   EG_SCALE_MATCRYO__ETABIN8__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN8__1up_isPassed, EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN8__1up_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN8__1up_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN9__1down, histbc_noMET_EG_SCALE_MATCRYO__ETABIN9__1down, histbl_noMET_EG_SCALE_MATCRYO__ETABIN9__1down, histcc_noMET_EG_SCALE_MATCRYO__ETABIN9__1down, histcl_noMET_EG_SCALE_MATCRYO__ETABIN9__1down, histll_noMET_EG_SCALE_MATCRYO__ETABIN9__1down,
							   EG_SCALE_MATCRYO__ETABIN9__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN9__1down_isPassed, EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN9__1down_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN9__1down_m_yy);
					checkDijet(histbb_noMET_EG_SCALE_MATCRYO__ETABIN9__1up, histbc_noMET_EG_SCALE_MATCRYO__ETABIN9__1up, histbl_noMET_EG_SCALE_MATCRYO__ETABIN9__1up, histcc_noMET_EG_SCALE_MATCRYO__ETABIN9__1up, histcl_noMET_EG_SCALE_MATCRYO__ETABIN9__1up, histll_noMET_EG_SCALE_MATCRYO__ETABIN9__1up,
							   EG_SCALE_MATCRYO__ETABIN9__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN9__1up_isPassed, EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_truthlabel,
							   EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_subleadjet_truthlabel, EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_subleadjet_btagbin, EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN9__1up_yyHFjj_weight, EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_met,
							   EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN9__1up_m_yy);
					checkDijet(histbb_noMET_PH_EFF_ID_Uncertainty__1down, histbc_noMET_PH_EFF_ID_Uncertainty__1down, histbl_noMET_PH_EFF_ID_Uncertainty__1down, histcc_noMET_PH_EFF_ID_Uncertainty__1down, histcl_noMET_PH_EFF_ID_Uncertainty__1down, histll_noMET_PH_EFF_ID_Uncertainty__1down,
							   PH_EFF_ID_Uncertainty__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_EFF_ID_Uncertainty__1down_isPassed, PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_truthlabel,
							   PH_EFF_ID_Uncertainty__1down_yyHF_subleadjet_truthlabel, PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_btagbin, PH_EFF_ID_Uncertainty__1down_yyHF_subleadjet_btagbin, PH_EFF_ID_Uncertainty__1down_yyHF_Njet_central, PH_EFF_ID_Uncertainty__1down_yyHFjj_weight, PH_EFF_ID_Uncertainty__1down_yyHF_met,
							   PH_EFF_ID_Uncertainty__1down_yyHF_nelectron, PH_EFF_ID_Uncertainty__1down_yyHF_nmuon, PH_EFF_ID_Uncertainty__1down_m_yy);
					checkDijet(histbb_noMET_PH_EFF_ID_Uncertainty__1up, histbc_noMET_PH_EFF_ID_Uncertainty__1up, histbl_noMET_PH_EFF_ID_Uncertainty__1up, histcc_noMET_PH_EFF_ID_Uncertainty__1up, histcl_noMET_PH_EFF_ID_Uncertainty__1up, histll_noMET_PH_EFF_ID_Uncertainty__1up,
							   PH_EFF_ID_Uncertainty__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_EFF_ID_Uncertainty__1up_isPassed, PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_truthlabel,
							   PH_EFF_ID_Uncertainty__1up_yyHF_subleadjet_truthlabel, PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_btagbin, PH_EFF_ID_Uncertainty__1up_yyHF_subleadjet_btagbin, PH_EFF_ID_Uncertainty__1up_yyHF_Njet_central, PH_EFF_ID_Uncertainty__1up_yyHFjj_weight, PH_EFF_ID_Uncertainty__1up_yyHF_met,
							   PH_EFF_ID_Uncertainty__1up_yyHF_nelectron, PH_EFF_ID_Uncertainty__1up_yyHF_nmuon, PH_EFF_ID_Uncertainty__1up_m_yy);
					checkDijet(histbb_noMET_PH_EFF_ISO_Uncertainty__1down, histbc_noMET_PH_EFF_ISO_Uncertainty__1down, histbl_noMET_PH_EFF_ISO_Uncertainty__1down, histcc_noMET_PH_EFF_ISO_Uncertainty__1down, histcl_noMET_PH_EFF_ISO_Uncertainty__1down, histll_noMET_PH_EFF_ISO_Uncertainty__1down,
							   PH_EFF_ISO_Uncertainty__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_EFF_ISO_Uncertainty__1down_isPassed, PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_truthlabel,
							   PH_EFF_ISO_Uncertainty__1down_yyHF_subleadjet_truthlabel, PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_btagbin, PH_EFF_ISO_Uncertainty__1down_yyHF_subleadjet_btagbin, PH_EFF_ISO_Uncertainty__1down_yyHF_Njet_central, PH_EFF_ISO_Uncertainty__1down_yyHFjj_weight, PH_EFF_ISO_Uncertainty__1down_yyHF_met,
							   PH_EFF_ISO_Uncertainty__1down_yyHF_nelectron, PH_EFF_ISO_Uncertainty__1down_yyHF_nmuon, PH_EFF_ISO_Uncertainty__1down_m_yy);
					checkDijet(histbb_noMET_PH_EFF_ISO_Uncertainty__1up, histbc_noMET_PH_EFF_ISO_Uncertainty__1up, histbl_noMET_PH_EFF_ISO_Uncertainty__1up, histcc_noMET_PH_EFF_ISO_Uncertainty__1up, histcl_noMET_PH_EFF_ISO_Uncertainty__1up, histll_noMET_PH_EFF_ISO_Uncertainty__1up,
							   PH_EFF_ISO_Uncertainty__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_EFF_ISO_Uncertainty__1up_isPassed, PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_truthlabel,
							   PH_EFF_ISO_Uncertainty__1up_yyHF_subleadjet_truthlabel, PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_btagbin, PH_EFF_ISO_Uncertainty__1up_yyHF_subleadjet_btagbin, PH_EFF_ISO_Uncertainty__1up_yyHF_Njet_central, PH_EFF_ISO_Uncertainty__1up_yyHFjj_weight, PH_EFF_ISO_Uncertainty__1up_yyHF_met,
							   PH_EFF_ISO_Uncertainty__1up_yyHF_nelectron, PH_EFF_ISO_Uncertainty__1up_yyHF_nmuon, PH_EFF_ISO_Uncertainty__1up_m_yy);
					checkDijet(histbb_noMET_PH_EFF_TRIGGER_Uncertainty__1down, histbc_noMET_PH_EFF_TRIGGER_Uncertainty__1down, histbl_noMET_PH_EFF_TRIGGER_Uncertainty__1down, histcc_noMET_PH_EFF_TRIGGER_Uncertainty__1down, histcl_noMET_PH_EFF_TRIGGER_Uncertainty__1down, histll_noMET_PH_EFF_TRIGGER_Uncertainty__1down,
							   PH_EFF_TRIGGER_Uncertainty__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_EFF_TRIGGER_Uncertainty__1down_isPassed, PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_truthlabel,
							   PH_EFF_TRIGGER_Uncertainty__1down_yyHF_subleadjet_truthlabel, PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_btagbin, PH_EFF_TRIGGER_Uncertainty__1down_yyHF_subleadjet_btagbin, PH_EFF_TRIGGER_Uncertainty__1down_yyHF_Njet_central, PH_EFF_TRIGGER_Uncertainty__1down_yyHFjj_weight, PH_EFF_TRIGGER_Uncertainty__1down_yyHF_met,
							   PH_EFF_TRIGGER_Uncertainty__1down_yyHF_nelectron, PH_EFF_TRIGGER_Uncertainty__1down_yyHF_nmuon, PH_EFF_TRIGGER_Uncertainty__1down_m_yy);
					checkDijet(histbb_noMET_PH_EFF_TRIGGER_Uncertainty__1up, histbc_noMET_PH_EFF_TRIGGER_Uncertainty__1up, histbl_noMET_PH_EFF_TRIGGER_Uncertainty__1up, histcc_noMET_PH_EFF_TRIGGER_Uncertainty__1up, histcl_noMET_PH_EFF_TRIGGER_Uncertainty__1up, histll_noMET_PH_EFF_TRIGGER_Uncertainty__1up,
							   PH_EFF_TRIGGER_Uncertainty__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_EFF_TRIGGER_Uncertainty__1up_isPassed, PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_truthlabel,
							   PH_EFF_TRIGGER_Uncertainty__1up_yyHF_subleadjet_truthlabel, PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_btagbin, PH_EFF_TRIGGER_Uncertainty__1up_yyHF_subleadjet_btagbin, PH_EFF_TRIGGER_Uncertainty__1up_yyHF_Njet_central, PH_EFF_TRIGGER_Uncertainty__1up_yyHFjj_weight, PH_EFF_TRIGGER_Uncertainty__1up_yyHF_met,
							   PH_EFF_TRIGGER_Uncertainty__1up_yyHF_nelectron, PH_EFF_TRIGGER_Uncertainty__1up_yyHF_nmuon, PH_EFF_TRIGGER_Uncertainty__1up_m_yy);
					checkDijet(histbb_noMET_PH_SCALE_CONVEFFICIENCY__1down, histbc_noMET_PH_SCALE_CONVEFFICIENCY__1down, histbl_noMET_PH_SCALE_CONVEFFICIENCY__1down, histcc_noMET_PH_SCALE_CONVEFFICIENCY__1down, histcl_noMET_PH_SCALE_CONVEFFICIENCY__1down, histll_noMET_PH_SCALE_CONVEFFICIENCY__1down,
							   PH_SCALE_CONVEFFICIENCY__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_CONVEFFICIENCY__1down_isPassed, PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_truthlabel,
							   PH_SCALE_CONVEFFICIENCY__1down_yyHF_subleadjet_truthlabel, PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_btagbin, PH_SCALE_CONVEFFICIENCY__1down_yyHF_subleadjet_btagbin, PH_SCALE_CONVEFFICIENCY__1down_yyHF_Njet_central, PH_SCALE_CONVEFFICIENCY__1down_yyHFjj_weight, PH_SCALE_CONVEFFICIENCY__1down_yyHF_met,
							   PH_SCALE_CONVEFFICIENCY__1down_yyHF_nelectron, PH_SCALE_CONVEFFICIENCY__1down_yyHF_nmuon, PH_SCALE_CONVEFFICIENCY__1down_m_yy);
					checkDijet(histbb_noMET_PH_SCALE_CONVEFFICIENCY__1up, histbc_noMET_PH_SCALE_CONVEFFICIENCY__1up, histbl_noMET_PH_SCALE_CONVEFFICIENCY__1up, histcc_noMET_PH_SCALE_CONVEFFICIENCY__1up, histcl_noMET_PH_SCALE_CONVEFFICIENCY__1up, histll_noMET_PH_SCALE_CONVEFFICIENCY__1up,
							   PH_SCALE_CONVEFFICIENCY__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_CONVEFFICIENCY__1up_isPassed, PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_truthlabel,
							   PH_SCALE_CONVEFFICIENCY__1up_yyHF_subleadjet_truthlabel, PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_btagbin, PH_SCALE_CONVEFFICIENCY__1up_yyHF_subleadjet_btagbin, PH_SCALE_CONVEFFICIENCY__1up_yyHF_Njet_central, PH_SCALE_CONVEFFICIENCY__1up_yyHFjj_weight, PH_SCALE_CONVEFFICIENCY__1up_yyHF_met,
							   PH_SCALE_CONVEFFICIENCY__1up_yyHF_nelectron, PH_SCALE_CONVEFFICIENCY__1up_yyHF_nmuon, PH_SCALE_CONVEFFICIENCY__1up_m_yy);
					checkDijet(histbb_noMET_PH_SCALE_CONVFAKERATE__1down, histbc_noMET_PH_SCALE_CONVFAKERATE__1down, histbl_noMET_PH_SCALE_CONVFAKERATE__1down, histcc_noMET_PH_SCALE_CONVFAKERATE__1down, histcl_noMET_PH_SCALE_CONVFAKERATE__1down, histll_noMET_PH_SCALE_CONVFAKERATE__1down,
							   PH_SCALE_CONVFAKERATE__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_CONVFAKERATE__1down_isPassed, PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_truthlabel,
							   PH_SCALE_CONVFAKERATE__1down_yyHF_subleadjet_truthlabel, PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_btagbin, PH_SCALE_CONVFAKERATE__1down_yyHF_subleadjet_btagbin, PH_SCALE_CONVFAKERATE__1down_yyHF_Njet_central, PH_SCALE_CONVFAKERATE__1down_yyHFjj_weight, PH_SCALE_CONVFAKERATE__1down_yyHF_met,
							   PH_SCALE_CONVFAKERATE__1down_yyHF_nelectron, PH_SCALE_CONVFAKERATE__1down_yyHF_nmuon, PH_SCALE_CONVFAKERATE__1down_m_yy);
					checkDijet(histbb_noMET_PH_SCALE_CONVFAKERATE__1up, histbc_noMET_PH_SCALE_CONVFAKERATE__1up, histbl_noMET_PH_SCALE_CONVFAKERATE__1up, histcc_noMET_PH_SCALE_CONVFAKERATE__1up, histcl_noMET_PH_SCALE_CONVFAKERATE__1up, histll_noMET_PH_SCALE_CONVFAKERATE__1up,
							   PH_SCALE_CONVFAKERATE__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_CONVFAKERATE__1up_isPassed, PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_truthlabel,
							   PH_SCALE_CONVFAKERATE__1up_yyHF_subleadjet_truthlabel, PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_btagbin, PH_SCALE_CONVFAKERATE__1up_yyHF_subleadjet_btagbin, PH_SCALE_CONVFAKERATE__1up_yyHF_Njet_central, PH_SCALE_CONVFAKERATE__1up_yyHFjj_weight, PH_SCALE_CONVFAKERATE__1up_yyHF_met,
							   PH_SCALE_CONVFAKERATE__1up_yyHF_nelectron, PH_SCALE_CONVFAKERATE__1up_yyHF_nmuon, PH_SCALE_CONVFAKERATE__1up_m_yy);
					checkDijet(histbb_noMET_PH_SCALE_CONVRADIUS__1down, histbc_noMET_PH_SCALE_CONVRADIUS__1down, histbl_noMET_PH_SCALE_CONVRADIUS__1down, histcc_noMET_PH_SCALE_CONVRADIUS__1down, histcl_noMET_PH_SCALE_CONVRADIUS__1down, histll_noMET_PH_SCALE_CONVRADIUS__1down,
							   PH_SCALE_CONVRADIUS__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_CONVRADIUS__1down_isPassed, PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_truthlabel,
							   PH_SCALE_CONVRADIUS__1down_yyHF_subleadjet_truthlabel, PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_btagbin, PH_SCALE_CONVRADIUS__1down_yyHF_subleadjet_btagbin, PH_SCALE_CONVRADIUS__1down_yyHF_Njet_central, PH_SCALE_CONVRADIUS__1down_yyHFjj_weight, PH_SCALE_CONVRADIUS__1down_yyHF_met,
							   PH_SCALE_CONVRADIUS__1down_yyHF_nelectron, PH_SCALE_CONVRADIUS__1down_yyHF_nmuon, PH_SCALE_CONVRADIUS__1down_m_yy);
					checkDijet(histbb_noMET_PH_SCALE_CONVRADIUS__1up, histbc_noMET_PH_SCALE_CONVRADIUS__1up, histbl_noMET_PH_SCALE_CONVRADIUS__1up, histcc_noMET_PH_SCALE_CONVRADIUS__1up, histcl_noMET_PH_SCALE_CONVRADIUS__1up, histll_noMET_PH_SCALE_CONVRADIUS__1up,
							   PH_SCALE_CONVRADIUS__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_CONVRADIUS__1up_isPassed, PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_truthlabel,
							   PH_SCALE_CONVRADIUS__1up_yyHF_subleadjet_truthlabel, PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_btagbin, PH_SCALE_CONVRADIUS__1up_yyHF_subleadjet_btagbin, PH_SCALE_CONVRADIUS__1up_yyHF_Njet_central, PH_SCALE_CONVRADIUS__1up_yyHFjj_weight, PH_SCALE_CONVRADIUS__1up_yyHF_met,
							   PH_SCALE_CONVRADIUS__1up_yyHF_nelectron, PH_SCALE_CONVRADIUS__1up_yyHF_nmuon, PH_SCALE_CONVRADIUS__1up_m_yy);
					checkDijet(histbb_noMET_PH_SCALE_LEAKAGECONV__1down, histbc_noMET_PH_SCALE_LEAKAGECONV__1down, histbl_noMET_PH_SCALE_LEAKAGECONV__1down, histcc_noMET_PH_SCALE_LEAKAGECONV__1down, histcl_noMET_PH_SCALE_LEAKAGECONV__1down, histll_noMET_PH_SCALE_LEAKAGECONV__1down,
							   PH_SCALE_LEAKAGECONV__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_LEAKAGECONV__1down_isPassed, PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_truthlabel,
							   PH_SCALE_LEAKAGECONV__1down_yyHF_subleadjet_truthlabel, PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_btagbin, PH_SCALE_LEAKAGECONV__1down_yyHF_subleadjet_btagbin, PH_SCALE_LEAKAGECONV__1down_yyHF_Njet_central, PH_SCALE_LEAKAGECONV__1down_yyHFjj_weight, PH_SCALE_LEAKAGECONV__1down_yyHF_met,
							   PH_SCALE_LEAKAGECONV__1down_yyHF_nelectron, PH_SCALE_LEAKAGECONV__1down_yyHF_nmuon, PH_SCALE_LEAKAGECONV__1down_m_yy);
					checkDijet(histbb_noMET_PH_SCALE_LEAKAGECONV__1up, histbc_noMET_PH_SCALE_LEAKAGECONV__1up, histbl_noMET_PH_SCALE_LEAKAGECONV__1up, histcc_noMET_PH_SCALE_LEAKAGECONV__1up, histcl_noMET_PH_SCALE_LEAKAGECONV__1up, histll_noMET_PH_SCALE_LEAKAGECONV__1up,
							   PH_SCALE_LEAKAGECONV__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_LEAKAGECONV__1up_isPassed, PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_truthlabel,
							   PH_SCALE_LEAKAGECONV__1up_yyHF_subleadjet_truthlabel, PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_btagbin, PH_SCALE_LEAKAGECONV__1up_yyHF_subleadjet_btagbin, PH_SCALE_LEAKAGECONV__1up_yyHF_Njet_central, PH_SCALE_LEAKAGECONV__1up_yyHFjj_weight, PH_SCALE_LEAKAGECONV__1up_yyHF_met,
							   PH_SCALE_LEAKAGECONV__1up_yyHF_nelectron, PH_SCALE_LEAKAGECONV__1up_yyHF_nmuon, PH_SCALE_LEAKAGECONV__1up_m_yy);
					checkDijet(histbb_noMET_PH_SCALE_LEAKAGEUNCONV__1down, histbc_noMET_PH_SCALE_LEAKAGEUNCONV__1down, histbl_noMET_PH_SCALE_LEAKAGEUNCONV__1down, histcc_noMET_PH_SCALE_LEAKAGEUNCONV__1down, histcl_noMET_PH_SCALE_LEAKAGEUNCONV__1down, histll_noMET_PH_SCALE_LEAKAGEUNCONV__1down,
							   PH_SCALE_LEAKAGEUNCONV__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_LEAKAGEUNCONV__1down_isPassed, PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_truthlabel,
							   PH_SCALE_LEAKAGEUNCONV__1down_yyHF_subleadjet_truthlabel, PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_btagbin, PH_SCALE_LEAKAGEUNCONV__1down_yyHF_subleadjet_btagbin, PH_SCALE_LEAKAGEUNCONV__1down_yyHF_Njet_central, PH_SCALE_LEAKAGEUNCONV__1down_yyHFjj_weight, PH_SCALE_LEAKAGEUNCONV__1down_yyHF_met,
							   PH_SCALE_LEAKAGEUNCONV__1down_yyHF_nelectron, PH_SCALE_LEAKAGEUNCONV__1down_yyHF_nmuon, PH_SCALE_LEAKAGEUNCONV__1down_m_yy);
					checkDijet(histbb_noMET_PH_SCALE_LEAKAGEUNCONV__1up, histbc_noMET_PH_SCALE_LEAKAGEUNCONV__1up, histbl_noMET_PH_SCALE_LEAKAGEUNCONV__1up, histcc_noMET_PH_SCALE_LEAKAGEUNCONV__1up, histcl_noMET_PH_SCALE_LEAKAGEUNCONV__1up, histll_noMET_PH_SCALE_LEAKAGEUNCONV__1up,
							   PH_SCALE_LEAKAGEUNCONV__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_LEAKAGEUNCONV__1up_isPassed, PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_truthlabel,
							   PH_SCALE_LEAKAGEUNCONV__1up_yyHF_subleadjet_truthlabel, PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_btagbin, PH_SCALE_LEAKAGEUNCONV__1up_yyHF_subleadjet_btagbin, PH_SCALE_LEAKAGEUNCONV__1up_yyHF_Njet_central, PH_SCALE_LEAKAGEUNCONV__1up_yyHFjj_weight, PH_SCALE_LEAKAGEUNCONV__1up_yyHF_met,
							   PH_SCALE_LEAKAGEUNCONV__1up_yyHF_nelectron, PH_SCALE_LEAKAGEUNCONV__1up_yyHF_nmuon, PH_SCALE_LEAKAGEUNCONV__1up_m_yy);




					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN0__1down, histc_noMET_EG_SCALE_MATCRYO__ETABIN0__1down, histl_noMET_EG_SCALE_MATCRYO__ETABIN0__1down,
					 		   EG_SCALE_MATCRYO__ETABIN0__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN0__1down_isPassed, EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN0__1down_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN0__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN0__1down_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN0__1up, histc_noMET_EG_SCALE_MATCRYO__ETABIN0__1up, histl_noMET_EG_SCALE_MATCRYO__ETABIN0__1up,
					 		   EG_SCALE_MATCRYO__ETABIN0__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN0__1up_isPassed, EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN0__1up_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN0__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN0__1up_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN1__1down, histc_noMET_EG_SCALE_MATCRYO__ETABIN1__1down, histl_noMET_EG_SCALE_MATCRYO__ETABIN1__1down,
					 		   EG_SCALE_MATCRYO__ETABIN1__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN1__1down_isPassed, EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN1__1down_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN1__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN1__1down_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN1__1up, histc_noMET_EG_SCALE_MATCRYO__ETABIN1__1up, histl_noMET_EG_SCALE_MATCRYO__ETABIN1__1up,
					 		   EG_SCALE_MATCRYO__ETABIN1__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN1__1up_isPassed, EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN1__1up_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN1__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN1__1up_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN10__1down, histc_noMET_EG_SCALE_MATCRYO__ETABIN10__1down, histl_noMET_EG_SCALE_MATCRYO__ETABIN10__1down,
					 		   EG_SCALE_MATCRYO__ETABIN10__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN10__1down_isPassed, EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN10__1down_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN10__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN10__1down_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN10__1up, histc_noMET_EG_SCALE_MATCRYO__ETABIN10__1up, histl_noMET_EG_SCALE_MATCRYO__ETABIN10__1up,
					 		   EG_SCALE_MATCRYO__ETABIN10__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN10__1up_isPassed, EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN10__1up_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN10__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN10__1up_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN11__1down, histc_noMET_EG_SCALE_MATCRYO__ETABIN11__1down, histl_noMET_EG_SCALE_MATCRYO__ETABIN11__1down,
					 		   EG_SCALE_MATCRYO__ETABIN11__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN11__1down_isPassed, EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN11__1down_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN11__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN11__1down_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN11__1up, histc_noMET_EG_SCALE_MATCRYO__ETABIN11__1up, histl_noMET_EG_SCALE_MATCRYO__ETABIN11__1up,
					 		   EG_SCALE_MATCRYO__ETABIN11__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN11__1up_isPassed, EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN11__1up_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN11__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN11__1up_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN2__1down, histc_noMET_EG_SCALE_MATCRYO__ETABIN2__1down, histl_noMET_EG_SCALE_MATCRYO__ETABIN2__1down,
					 		   EG_SCALE_MATCRYO__ETABIN2__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN2__1down_isPassed, EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN2__1down_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN2__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN2__1down_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN2__1up, histc_noMET_EG_SCALE_MATCRYO__ETABIN2__1up, histl_noMET_EG_SCALE_MATCRYO__ETABIN2__1up,
					 		   EG_SCALE_MATCRYO__ETABIN2__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN2__1up_isPassed, EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN2__1up_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN2__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN2__1up_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN3__1down, histc_noMET_EG_SCALE_MATCRYO__ETABIN3__1down, histl_noMET_EG_SCALE_MATCRYO__ETABIN3__1down,
					 		   EG_SCALE_MATCRYO__ETABIN3__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN3__1down_isPassed, EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN3__1down_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN3__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN3__1down_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN3__1up, histc_noMET_EG_SCALE_MATCRYO__ETABIN3__1up, histl_noMET_EG_SCALE_MATCRYO__ETABIN3__1up,
					 		   EG_SCALE_MATCRYO__ETABIN3__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN3__1up_isPassed, EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN3__1up_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN3__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN3__1up_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN4__1down, histc_noMET_EG_SCALE_MATCRYO__ETABIN4__1down, histl_noMET_EG_SCALE_MATCRYO__ETABIN4__1down,
					 		   EG_SCALE_MATCRYO__ETABIN4__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN4__1down_isPassed, EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN4__1down_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN4__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN4__1down_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN4__1up, histc_noMET_EG_SCALE_MATCRYO__ETABIN4__1up, histl_noMET_EG_SCALE_MATCRYO__ETABIN4__1up,
					 		   EG_SCALE_MATCRYO__ETABIN4__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN4__1up_isPassed, EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN4__1up_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN4__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN4__1up_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN5__1down, histc_noMET_EG_SCALE_MATCRYO__ETABIN5__1down, histl_noMET_EG_SCALE_MATCRYO__ETABIN5__1down,
					 		   EG_SCALE_MATCRYO__ETABIN5__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN5__1down_isPassed, EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN5__1down_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN5__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN5__1down_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN5__1up, histc_noMET_EG_SCALE_MATCRYO__ETABIN5__1up, histl_noMET_EG_SCALE_MATCRYO__ETABIN5__1up,
					 		   EG_SCALE_MATCRYO__ETABIN5__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN5__1up_isPassed, EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN5__1up_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN5__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN5__1up_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN6__1down, histc_noMET_EG_SCALE_MATCRYO__ETABIN6__1down, histl_noMET_EG_SCALE_MATCRYO__ETABIN6__1down,
					 		   EG_SCALE_MATCRYO__ETABIN6__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN6__1down_isPassed, EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN6__1down_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN6__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN6__1down_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN6__1up, histc_noMET_EG_SCALE_MATCRYO__ETABIN6__1up, histl_noMET_EG_SCALE_MATCRYO__ETABIN6__1up,
					 		   EG_SCALE_MATCRYO__ETABIN6__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN6__1up_isPassed, EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN6__1up_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN6__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN6__1up_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN7__1down, histc_noMET_EG_SCALE_MATCRYO__ETABIN7__1down, histl_noMET_EG_SCALE_MATCRYO__ETABIN7__1down,
					 		   EG_SCALE_MATCRYO__ETABIN7__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN7__1down_isPassed, EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN7__1down_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN7__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN7__1down_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN7__1up, histc_noMET_EG_SCALE_MATCRYO__ETABIN7__1up, histl_noMET_EG_SCALE_MATCRYO__ETABIN7__1up,
					 		   EG_SCALE_MATCRYO__ETABIN7__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN7__1up_isPassed, EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN7__1up_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN7__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN7__1up_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN8__1down, histc_noMET_EG_SCALE_MATCRYO__ETABIN8__1down, histl_noMET_EG_SCALE_MATCRYO__ETABIN8__1down,
					 		   EG_SCALE_MATCRYO__ETABIN8__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN8__1down_isPassed, EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN8__1down_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN8__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN8__1down_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN8__1up, histc_noMET_EG_SCALE_MATCRYO__ETABIN8__1up, histl_noMET_EG_SCALE_MATCRYO__ETABIN8__1up,
					 		   EG_SCALE_MATCRYO__ETABIN8__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN8__1up_isPassed, EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN8__1up_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN8__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN8__1up_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN9__1down, histc_noMET_EG_SCALE_MATCRYO__ETABIN9__1down, histl_noMET_EG_SCALE_MATCRYO__ETABIN9__1down,
					 		   EG_SCALE_MATCRYO__ETABIN9__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN9__1down_isPassed, EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN9__1down_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN9__1down_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN9__1down_m_yy);
					 checkSingleJet(histb_noMET_EG_SCALE_MATCRYO__ETABIN9__1up, histc_noMET_EG_SCALE_MATCRYO__ETABIN9__1up, histl_noMET_EG_SCALE_MATCRYO__ETABIN9__1up,
					 		   EG_SCALE_MATCRYO__ETABIN9__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, EG_SCALE_MATCRYO__ETABIN9__1up_isPassed, EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_truthlabel,
					 		   EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_leadjet_btagbin, EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_Njet_central, EG_SCALE_MATCRYO__ETABIN9__1up_yyHFj_weight, EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_met,
					 		   EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_nelectron, EG_SCALE_MATCRYO__ETABIN9__1up_yyHF_nmuon, EG_SCALE_MATCRYO__ETABIN9__1up_m_yy);
					 checkSingleJet(histb_noMET_PH_EFF_ID_Uncertainty__1down, histc_noMET_PH_EFF_ID_Uncertainty__1down, histl_noMET_PH_EFF_ID_Uncertainty__1down,
					 		   PH_EFF_ID_Uncertainty__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_EFF_ID_Uncertainty__1down_isPassed, PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_truthlabel,
					 		   PH_EFF_ID_Uncertainty__1down_yyHF_leadjet_btagbin, PH_EFF_ID_Uncertainty__1down_yyHF_Njet_central, PH_EFF_ID_Uncertainty__1down_yyHFj_weight, PH_EFF_ID_Uncertainty__1down_yyHF_met,
					 		   PH_EFF_ID_Uncertainty__1down_yyHF_nelectron, PH_EFF_ID_Uncertainty__1down_yyHF_nmuon, PH_EFF_ID_Uncertainty__1down_m_yy);
					 checkSingleJet(histb_noMET_PH_EFF_ID_Uncertainty__1up, histc_noMET_PH_EFF_ID_Uncertainty__1up, histl_noMET_PH_EFF_ID_Uncertainty__1up,
					 		   PH_EFF_ID_Uncertainty__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_EFF_ID_Uncertainty__1up_isPassed, PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_truthlabel,
					 		   PH_EFF_ID_Uncertainty__1up_yyHF_leadjet_btagbin, PH_EFF_ID_Uncertainty__1up_yyHF_Njet_central, PH_EFF_ID_Uncertainty__1up_yyHFj_weight, PH_EFF_ID_Uncertainty__1up_yyHF_met,
					 		   PH_EFF_ID_Uncertainty__1up_yyHF_nelectron, PH_EFF_ID_Uncertainty__1up_yyHF_nmuon, PH_EFF_ID_Uncertainty__1up_m_yy);
					 checkSingleJet(histb_noMET_PH_EFF_ISO_Uncertainty__1down, histc_noMET_PH_EFF_ISO_Uncertainty__1down, histl_noMET_PH_EFF_ISO_Uncertainty__1down,
					 		   PH_EFF_ISO_Uncertainty__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_EFF_ISO_Uncertainty__1down_isPassed, PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_truthlabel,
					 		   PH_EFF_ISO_Uncertainty__1down_yyHF_leadjet_btagbin, PH_EFF_ISO_Uncertainty__1down_yyHF_Njet_central, PH_EFF_ISO_Uncertainty__1down_yyHFj_weight, PH_EFF_ISO_Uncertainty__1down_yyHF_met,
					 		   PH_EFF_ISO_Uncertainty__1down_yyHF_nelectron, PH_EFF_ISO_Uncertainty__1down_yyHF_nmuon, PH_EFF_ISO_Uncertainty__1down_m_yy);
					 checkSingleJet(histb_noMET_PH_EFF_ISO_Uncertainty__1up, histc_noMET_PH_EFF_ISO_Uncertainty__1up, histl_noMET_PH_EFF_ISO_Uncertainty__1up,
					 		   PH_EFF_ISO_Uncertainty__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_EFF_ISO_Uncertainty__1up_isPassed, PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_truthlabel,
					 		   PH_EFF_ISO_Uncertainty__1up_yyHF_leadjet_btagbin, PH_EFF_ISO_Uncertainty__1up_yyHF_Njet_central, PH_EFF_ISO_Uncertainty__1up_yyHFj_weight, PH_EFF_ISO_Uncertainty__1up_yyHF_met,
					 		   PH_EFF_ISO_Uncertainty__1up_yyHF_nelectron, PH_EFF_ISO_Uncertainty__1up_yyHF_nmuon, PH_EFF_ISO_Uncertainty__1up_m_yy);
					 checkSingleJet(histb_noMET_PH_EFF_TRIGGER_Uncertainty__1down, histc_noMET_PH_EFF_TRIGGER_Uncertainty__1down, histl_noMET_PH_EFF_TRIGGER_Uncertainty__1down,
					 		   PH_EFF_TRIGGER_Uncertainty__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_EFF_TRIGGER_Uncertainty__1down_isPassed, PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_truthlabel,
					 		   PH_EFF_TRIGGER_Uncertainty__1down_yyHF_leadjet_btagbin, PH_EFF_TRIGGER_Uncertainty__1down_yyHF_Njet_central, PH_EFF_TRIGGER_Uncertainty__1down_yyHFj_weight, PH_EFF_TRIGGER_Uncertainty__1down_yyHF_met,
					 		   PH_EFF_TRIGGER_Uncertainty__1down_yyHF_nelectron, PH_EFF_TRIGGER_Uncertainty__1down_yyHF_nmuon, PH_EFF_TRIGGER_Uncertainty__1down_m_yy);
					 checkSingleJet(histb_noMET_PH_EFF_TRIGGER_Uncertainty__1up, histc_noMET_PH_EFF_TRIGGER_Uncertainty__1up, histl_noMET_PH_EFF_TRIGGER_Uncertainty__1up,
					 		   PH_EFF_TRIGGER_Uncertainty__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_EFF_TRIGGER_Uncertainty__1up_isPassed, PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_truthlabel,
					 		   PH_EFF_TRIGGER_Uncertainty__1up_yyHF_leadjet_btagbin, PH_EFF_TRIGGER_Uncertainty__1up_yyHF_Njet_central, PH_EFF_TRIGGER_Uncertainty__1up_yyHFj_weight, PH_EFF_TRIGGER_Uncertainty__1up_yyHF_met,
					 		   PH_EFF_TRIGGER_Uncertainty__1up_yyHF_nelectron, PH_EFF_TRIGGER_Uncertainty__1up_yyHF_nmuon, PH_EFF_TRIGGER_Uncertainty__1up_m_yy);
					 checkSingleJet(histb_noMET_PH_SCALE_CONVEFFICIENCY__1down, histc_noMET_PH_SCALE_CONVEFFICIENCY__1down, histl_noMET_PH_SCALE_CONVEFFICIENCY__1down,
					 		   PH_SCALE_CONVEFFICIENCY__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_CONVEFFICIENCY__1down_isPassed, PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_truthlabel,
					 		   PH_SCALE_CONVEFFICIENCY__1down_yyHF_leadjet_btagbin, PH_SCALE_CONVEFFICIENCY__1down_yyHF_Njet_central, PH_SCALE_CONVEFFICIENCY__1down_yyHFj_weight, PH_SCALE_CONVEFFICIENCY__1down_yyHF_met,
					 		   PH_SCALE_CONVEFFICIENCY__1down_yyHF_nelectron, PH_SCALE_CONVEFFICIENCY__1down_yyHF_nmuon, PH_SCALE_CONVEFFICIENCY__1down_m_yy);
					 checkSingleJet(histb_noMET_PH_SCALE_CONVEFFICIENCY__1up, histc_noMET_PH_SCALE_CONVEFFICIENCY__1up, histl_noMET_PH_SCALE_CONVEFFICIENCY__1up,
					 		   PH_SCALE_CONVEFFICIENCY__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_CONVEFFICIENCY__1up_isPassed, PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_truthlabel,
					 		   PH_SCALE_CONVEFFICIENCY__1up_yyHF_leadjet_btagbin, PH_SCALE_CONVEFFICIENCY__1up_yyHF_Njet_central, PH_SCALE_CONVEFFICIENCY__1up_yyHFj_weight, PH_SCALE_CONVEFFICIENCY__1up_yyHF_met,
					 		   PH_SCALE_CONVEFFICIENCY__1up_yyHF_nelectron, PH_SCALE_CONVEFFICIENCY__1up_yyHF_nmuon, PH_SCALE_CONVEFFICIENCY__1up_m_yy);
					 checkSingleJet(histb_noMET_PH_SCALE_CONVFAKERATE__1down, histc_noMET_PH_SCALE_CONVFAKERATE__1down, histl_noMET_PH_SCALE_CONVFAKERATE__1down,
					 		   PH_SCALE_CONVFAKERATE__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_CONVFAKERATE__1down_isPassed, PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_truthlabel,
					 		   PH_SCALE_CONVFAKERATE__1down_yyHF_leadjet_btagbin, PH_SCALE_CONVFAKERATE__1down_yyHF_Njet_central, PH_SCALE_CONVFAKERATE__1down_yyHFj_weight, PH_SCALE_CONVFAKERATE__1down_yyHF_met,
					 		   PH_SCALE_CONVFAKERATE__1down_yyHF_nelectron, PH_SCALE_CONVFAKERATE__1down_yyHF_nmuon, PH_SCALE_CONVFAKERATE__1down_m_yy);
					 checkSingleJet(histb_noMET_PH_SCALE_CONVFAKERATE__1up, histc_noMET_PH_SCALE_CONVFAKERATE__1up, histl_noMET_PH_SCALE_CONVFAKERATE__1up,
					 		   PH_SCALE_CONVFAKERATE__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_CONVFAKERATE__1up_isPassed, PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_truthlabel,
					 		   PH_SCALE_CONVFAKERATE__1up_yyHF_leadjet_btagbin, PH_SCALE_CONVFAKERATE__1up_yyHF_Njet_central, PH_SCALE_CONVFAKERATE__1up_yyHFj_weight, PH_SCALE_CONVFAKERATE__1up_yyHF_met,
					 		   PH_SCALE_CONVFAKERATE__1up_yyHF_nelectron, PH_SCALE_CONVFAKERATE__1up_yyHF_nmuon, PH_SCALE_CONVFAKERATE__1up_m_yy);
					 checkSingleJet(histb_noMET_PH_SCALE_CONVRADIUS__1down, histc_noMET_PH_SCALE_CONVRADIUS__1down, histl_noMET_PH_SCALE_CONVRADIUS__1down,
					 		   PH_SCALE_CONVRADIUS__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_CONVRADIUS__1down_isPassed, PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_truthlabel,
					 		   PH_SCALE_CONVRADIUS__1down_yyHF_leadjet_btagbin, PH_SCALE_CONVRADIUS__1down_yyHF_Njet_central, PH_SCALE_CONVRADIUS__1down_yyHFj_weight, PH_SCALE_CONVRADIUS__1down_yyHF_met,
					 		   PH_SCALE_CONVRADIUS__1down_yyHF_nelectron, PH_SCALE_CONVRADIUS__1down_yyHF_nmuon, PH_SCALE_CONVRADIUS__1down_m_yy);
					 checkSingleJet(histb_noMET_PH_SCALE_CONVRADIUS__1up, histc_noMET_PH_SCALE_CONVRADIUS__1up, histl_noMET_PH_SCALE_CONVRADIUS__1up,
					 		   PH_SCALE_CONVRADIUS__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_CONVRADIUS__1up_isPassed, PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_truthlabel,
					 		   PH_SCALE_CONVRADIUS__1up_yyHF_leadjet_btagbin, PH_SCALE_CONVRADIUS__1up_yyHF_Njet_central, PH_SCALE_CONVRADIUS__1up_yyHFj_weight, PH_SCALE_CONVRADIUS__1up_yyHF_met,
					 		   PH_SCALE_CONVRADIUS__1up_yyHF_nelectron, PH_SCALE_CONVRADIUS__1up_yyHF_nmuon, PH_SCALE_CONVRADIUS__1up_m_yy);
					 checkSingleJet(histb_noMET_PH_SCALE_LEAKAGECONV__1down, histc_noMET_PH_SCALE_LEAKAGECONV__1down, histl_noMET_PH_SCALE_LEAKAGECONV__1down,
					 		   PH_SCALE_LEAKAGECONV__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_LEAKAGECONV__1down_isPassed, PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_truthlabel,
					 		   PH_SCALE_LEAKAGECONV__1down_yyHF_leadjet_btagbin, PH_SCALE_LEAKAGECONV__1down_yyHF_Njet_central, PH_SCALE_LEAKAGECONV__1down_yyHFj_weight, PH_SCALE_LEAKAGECONV__1down_yyHF_met,
					 		   PH_SCALE_LEAKAGECONV__1down_yyHF_nelectron, PH_SCALE_LEAKAGECONV__1down_yyHF_nmuon, PH_SCALE_LEAKAGECONV__1down_m_yy);
					 checkSingleJet(histb_noMET_PH_SCALE_LEAKAGECONV__1up, histc_noMET_PH_SCALE_LEAKAGECONV__1up, histl_noMET_PH_SCALE_LEAKAGECONV__1up,
					 		   PH_SCALE_LEAKAGECONV__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_LEAKAGECONV__1up_isPassed, PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_truthlabel,
					 		   PH_SCALE_LEAKAGECONV__1up_yyHF_leadjet_btagbin, PH_SCALE_LEAKAGECONV__1up_yyHF_Njet_central, PH_SCALE_LEAKAGECONV__1up_yyHFj_weight, PH_SCALE_LEAKAGECONV__1up_yyHF_met,
					 		   PH_SCALE_LEAKAGECONV__1up_yyHF_nelectron, PH_SCALE_LEAKAGECONV__1up_yyHF_nmuon, PH_SCALE_LEAKAGECONV__1up_m_yy);
					 checkSingleJet(histb_noMET_PH_SCALE_LEAKAGEUNCONV__1down, histc_noMET_PH_SCALE_LEAKAGEUNCONV__1down, histl_noMET_PH_SCALE_LEAKAGEUNCONV__1down,
					 		   PH_SCALE_LEAKAGEUNCONV__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_LEAKAGEUNCONV__1down_isPassed, PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_truthlabel,
					 		   PH_SCALE_LEAKAGEUNCONV__1down_yyHF_leadjet_btagbin, PH_SCALE_LEAKAGEUNCONV__1down_yyHF_Njet_central, PH_SCALE_LEAKAGEUNCONV__1down_yyHFj_weight, PH_SCALE_LEAKAGEUNCONV__1down_yyHF_met,
					 		   PH_SCALE_LEAKAGEUNCONV__1down_yyHF_nelectron, PH_SCALE_LEAKAGEUNCONV__1down_yyHF_nmuon, PH_SCALE_LEAKAGEUNCONV__1down_m_yy);
					 checkSingleJet(histb_noMET_PH_SCALE_LEAKAGEUNCONV__1up, histc_noMET_PH_SCALE_LEAKAGEUNCONV__1up, histl_noMET_PH_SCALE_LEAKAGEUNCONV__1up,
					 		   PH_SCALE_LEAKAGEUNCONV__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, PH_SCALE_LEAKAGEUNCONV__1up_isPassed, PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_truthlabel,
					 		   PH_SCALE_LEAKAGEUNCONV__1up_yyHF_leadjet_btagbin, PH_SCALE_LEAKAGEUNCONV__1up_yyHF_Njet_central, PH_SCALE_LEAKAGEUNCONV__1up_yyHFj_weight, PH_SCALE_LEAKAGEUNCONV__1up_yyHF_met,
					 		   PH_SCALE_LEAKAGEUNCONV__1up_yyHF_nelectron, PH_SCALE_LEAKAGEUNCONV__1up_yyHF_nmuon, PH_SCALE_LEAKAGEUNCONV__1up_m_yy);

				}
				TFile* output_file = new TFile(output_name, "recreate");
				cout << "creating file: "<< output_name << endl;

				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN0__1down);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN0__1down);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN0__1down);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN0__1down);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN0__1down);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN0__1down);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN0__1down);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN0__1down);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN0__1down);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN0__1up);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN0__1up);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN0__1up);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN0__1up);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN0__1up);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN0__1up);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN0__1up);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN0__1up);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN0__1up);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN1__1down);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN1__1down);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN1__1down);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN1__1down);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN1__1down);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN1__1down);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN1__1down);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN1__1down);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN1__1down);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN1__1up);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN1__1up);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN1__1up);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN1__1up);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN1__1up);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN1__1up);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN1__1up);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN1__1up);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN1__1up);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN10__1down);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN10__1down);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN10__1down);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN10__1down);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN10__1down);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN10__1down);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN10__1down);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN10__1down);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN10__1down);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN10__1up);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN10__1up);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN10__1up);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN10__1up);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN10__1up);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN10__1up);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN10__1up);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN10__1up);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN10__1up);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN11__1down);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN11__1down);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN11__1down);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN11__1down);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN11__1down);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN11__1down);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN11__1down);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN11__1down);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN11__1down);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN11__1up);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN11__1up);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN11__1up);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN11__1up);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN11__1up);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN11__1up);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN11__1up);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN11__1up);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN11__1up);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN2__1down);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN2__1down);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN2__1down);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN2__1down);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN2__1down);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN2__1down);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN2__1down);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN2__1down);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN2__1down);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN2__1up);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN2__1up);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN2__1up);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN2__1up);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN2__1up);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN2__1up);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN2__1up);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN2__1up);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN2__1up);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN3__1down);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN3__1down);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN3__1down);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN3__1down);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN3__1down);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN3__1down);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN3__1down);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN3__1down);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN3__1down);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN3__1up);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN3__1up);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN3__1up);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN3__1up);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN3__1up);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN3__1up);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN3__1up);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN3__1up);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN3__1up);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN4__1down);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN4__1down);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN4__1down);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN4__1down);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN4__1down);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN4__1down);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN4__1down);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN4__1down);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN4__1down);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN4__1up);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN4__1up);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN4__1up);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN4__1up);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN4__1up);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN4__1up);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN4__1up);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN4__1up);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN4__1up);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN5__1down);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN5__1down);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN5__1down);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN5__1down);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN5__1down);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN5__1down);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN5__1down);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN5__1down);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN5__1down);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN5__1up);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN5__1up);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN5__1up);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN5__1up);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN5__1up);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN5__1up);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN5__1up);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN5__1up);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN5__1up);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN6__1down);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN6__1down);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN6__1down);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN6__1down);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN6__1down);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN6__1down);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN6__1down);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN6__1down);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN6__1down);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN6__1up);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN6__1up);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN6__1up);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN6__1up);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN6__1up);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN6__1up);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN6__1up);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN6__1up);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN6__1up);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN7__1down);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN7__1down);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN7__1down);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN7__1down);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN7__1down);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN7__1down);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN7__1down);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN7__1down);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN7__1down);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN7__1up);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN7__1up);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN7__1up);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN7__1up);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN7__1up);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN7__1up);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN7__1up);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN7__1up);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN7__1up);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN8__1down);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN8__1down);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN8__1down);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN8__1down);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN8__1down);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN8__1down);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN8__1down);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN8__1down);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN8__1down);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN8__1up);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN8__1up);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN8__1up);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN8__1up);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN8__1up);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN8__1up);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN8__1up);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN8__1up);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN8__1up);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN9__1down);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN9__1down);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN9__1down);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN9__1down);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN9__1down);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN9__1down);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN9__1down);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN9__1down);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN9__1down);
				output_file->Add(histbb_noMET_EG_SCALE_MATCRYO__ETABIN9__1up);
				output_file->Add(histbc_noMET_EG_SCALE_MATCRYO__ETABIN9__1up);
				output_file->Add(histbl_noMET_EG_SCALE_MATCRYO__ETABIN9__1up);
				output_file->Add(histcc_noMET_EG_SCALE_MATCRYO__ETABIN9__1up);
				output_file->Add(histcl_noMET_EG_SCALE_MATCRYO__ETABIN9__1up);
				output_file->Add(histll_noMET_EG_SCALE_MATCRYO__ETABIN9__1up);
				output_file->Add(histb_noMET_EG_SCALE_MATCRYO__ETABIN9__1up);
				output_file->Add(histc_noMET_EG_SCALE_MATCRYO__ETABIN9__1up);
				output_file->Add(histl_noMET_EG_SCALE_MATCRYO__ETABIN9__1up);
				output_file->Add(histbb_noMET_PH_EFF_ID_Uncertainty__1down);
				output_file->Add(histbc_noMET_PH_EFF_ID_Uncertainty__1down);
				output_file->Add(histbl_noMET_PH_EFF_ID_Uncertainty__1down);
				output_file->Add(histcc_noMET_PH_EFF_ID_Uncertainty__1down);
				output_file->Add(histcl_noMET_PH_EFF_ID_Uncertainty__1down);
				output_file->Add(histll_noMET_PH_EFF_ID_Uncertainty__1down);
				output_file->Add(histb_noMET_PH_EFF_ID_Uncertainty__1down);
				output_file->Add(histc_noMET_PH_EFF_ID_Uncertainty__1down);
				output_file->Add(histl_noMET_PH_EFF_ID_Uncertainty__1down);
				output_file->Add(histbb_noMET_PH_EFF_ID_Uncertainty__1up);
				output_file->Add(histbc_noMET_PH_EFF_ID_Uncertainty__1up);
				output_file->Add(histbl_noMET_PH_EFF_ID_Uncertainty__1up);
				output_file->Add(histcc_noMET_PH_EFF_ID_Uncertainty__1up);
				output_file->Add(histcl_noMET_PH_EFF_ID_Uncertainty__1up);
				output_file->Add(histll_noMET_PH_EFF_ID_Uncertainty__1up);
				output_file->Add(histb_noMET_PH_EFF_ID_Uncertainty__1up);
				output_file->Add(histc_noMET_PH_EFF_ID_Uncertainty__1up);
				output_file->Add(histl_noMET_PH_EFF_ID_Uncertainty__1up);
				output_file->Add(histbb_noMET_PH_EFF_ISO_Uncertainty__1down);
				output_file->Add(histbc_noMET_PH_EFF_ISO_Uncertainty__1down);
				output_file->Add(histbl_noMET_PH_EFF_ISO_Uncertainty__1down);
				output_file->Add(histcc_noMET_PH_EFF_ISO_Uncertainty__1down);
				output_file->Add(histcl_noMET_PH_EFF_ISO_Uncertainty__1down);
				output_file->Add(histll_noMET_PH_EFF_ISO_Uncertainty__1down);
				output_file->Add(histb_noMET_PH_EFF_ISO_Uncertainty__1down);
				output_file->Add(histc_noMET_PH_EFF_ISO_Uncertainty__1down);
				output_file->Add(histl_noMET_PH_EFF_ISO_Uncertainty__1down);
				output_file->Add(histbb_noMET_PH_EFF_ISO_Uncertainty__1up);
				output_file->Add(histbc_noMET_PH_EFF_ISO_Uncertainty__1up);
				output_file->Add(histbl_noMET_PH_EFF_ISO_Uncertainty__1up);
				output_file->Add(histcc_noMET_PH_EFF_ISO_Uncertainty__1up);
				output_file->Add(histcl_noMET_PH_EFF_ISO_Uncertainty__1up);
				output_file->Add(histll_noMET_PH_EFF_ISO_Uncertainty__1up);
				output_file->Add(histb_noMET_PH_EFF_ISO_Uncertainty__1up);
				output_file->Add(histc_noMET_PH_EFF_ISO_Uncertainty__1up);
				output_file->Add(histl_noMET_PH_EFF_ISO_Uncertainty__1up);
				output_file->Add(histbb_noMET_PH_EFF_TRIGGER_Uncertainty__1down);
				output_file->Add(histbc_noMET_PH_EFF_TRIGGER_Uncertainty__1down);
				output_file->Add(histbl_noMET_PH_EFF_TRIGGER_Uncertainty__1down);
				output_file->Add(histcc_noMET_PH_EFF_TRIGGER_Uncertainty__1down);
				output_file->Add(histcl_noMET_PH_EFF_TRIGGER_Uncertainty__1down);
				output_file->Add(histll_noMET_PH_EFF_TRIGGER_Uncertainty__1down);
				output_file->Add(histb_noMET_PH_EFF_TRIGGER_Uncertainty__1down);
				output_file->Add(histc_noMET_PH_EFF_TRIGGER_Uncertainty__1down);
				output_file->Add(histl_noMET_PH_EFF_TRIGGER_Uncertainty__1down);
				output_file->Add(histbb_noMET_PH_EFF_TRIGGER_Uncertainty__1up);
				output_file->Add(histbc_noMET_PH_EFF_TRIGGER_Uncertainty__1up);
				output_file->Add(histbl_noMET_PH_EFF_TRIGGER_Uncertainty__1up);
				output_file->Add(histcc_noMET_PH_EFF_TRIGGER_Uncertainty__1up);
				output_file->Add(histcl_noMET_PH_EFF_TRIGGER_Uncertainty__1up);
				output_file->Add(histll_noMET_PH_EFF_TRIGGER_Uncertainty__1up);
				output_file->Add(histb_noMET_PH_EFF_TRIGGER_Uncertainty__1up);
				output_file->Add(histc_noMET_PH_EFF_TRIGGER_Uncertainty__1up);
				output_file->Add(histl_noMET_PH_EFF_TRIGGER_Uncertainty__1up);
				output_file->Add(histbb_noMET_PH_SCALE_CONVEFFICIENCY__1down);
				output_file->Add(histbc_noMET_PH_SCALE_CONVEFFICIENCY__1down);
				output_file->Add(histbl_noMET_PH_SCALE_CONVEFFICIENCY__1down);
				output_file->Add(histcc_noMET_PH_SCALE_CONVEFFICIENCY__1down);
				output_file->Add(histcl_noMET_PH_SCALE_CONVEFFICIENCY__1down);
				output_file->Add(histll_noMET_PH_SCALE_CONVEFFICIENCY__1down);
				output_file->Add(histb_noMET_PH_SCALE_CONVEFFICIENCY__1down);
				output_file->Add(histc_noMET_PH_SCALE_CONVEFFICIENCY__1down);
				output_file->Add(histl_noMET_PH_SCALE_CONVEFFICIENCY__1down);
				output_file->Add(histbb_noMET_PH_SCALE_CONVEFFICIENCY__1up);
				output_file->Add(histbc_noMET_PH_SCALE_CONVEFFICIENCY__1up);
				output_file->Add(histbl_noMET_PH_SCALE_CONVEFFICIENCY__1up);
				output_file->Add(histcc_noMET_PH_SCALE_CONVEFFICIENCY__1up);
				output_file->Add(histcl_noMET_PH_SCALE_CONVEFFICIENCY__1up);
				output_file->Add(histll_noMET_PH_SCALE_CONVEFFICIENCY__1up);
				output_file->Add(histb_noMET_PH_SCALE_CONVEFFICIENCY__1up);
				output_file->Add(histc_noMET_PH_SCALE_CONVEFFICIENCY__1up);
				output_file->Add(histl_noMET_PH_SCALE_CONVEFFICIENCY__1up);
				output_file->Add(histbb_noMET_PH_SCALE_CONVFAKERATE__1down);
				output_file->Add(histbc_noMET_PH_SCALE_CONVFAKERATE__1down);
				output_file->Add(histbl_noMET_PH_SCALE_CONVFAKERATE__1down);
				output_file->Add(histcc_noMET_PH_SCALE_CONVFAKERATE__1down);
				output_file->Add(histcl_noMET_PH_SCALE_CONVFAKERATE__1down);
				output_file->Add(histll_noMET_PH_SCALE_CONVFAKERATE__1down);
				output_file->Add(histb_noMET_PH_SCALE_CONVFAKERATE__1down);
				output_file->Add(histc_noMET_PH_SCALE_CONVFAKERATE__1down);
				output_file->Add(histl_noMET_PH_SCALE_CONVFAKERATE__1down);
				output_file->Add(histbb_noMET_PH_SCALE_CONVFAKERATE__1up);
				output_file->Add(histbc_noMET_PH_SCALE_CONVFAKERATE__1up);
				output_file->Add(histbl_noMET_PH_SCALE_CONVFAKERATE__1up);
				output_file->Add(histcc_noMET_PH_SCALE_CONVFAKERATE__1up);
				output_file->Add(histcl_noMET_PH_SCALE_CONVFAKERATE__1up);
				output_file->Add(histll_noMET_PH_SCALE_CONVFAKERATE__1up);
				output_file->Add(histb_noMET_PH_SCALE_CONVFAKERATE__1up);
				output_file->Add(histc_noMET_PH_SCALE_CONVFAKERATE__1up);
				output_file->Add(histl_noMET_PH_SCALE_CONVFAKERATE__1up);
				output_file->Add(histbb_noMET_PH_SCALE_CONVRADIUS__1down);
				output_file->Add(histbc_noMET_PH_SCALE_CONVRADIUS__1down);
				output_file->Add(histbl_noMET_PH_SCALE_CONVRADIUS__1down);
				output_file->Add(histcc_noMET_PH_SCALE_CONVRADIUS__1down);
				output_file->Add(histcl_noMET_PH_SCALE_CONVRADIUS__1down);
				output_file->Add(histll_noMET_PH_SCALE_CONVRADIUS__1down);
				output_file->Add(histb_noMET_PH_SCALE_CONVRADIUS__1down);
				output_file->Add(histc_noMET_PH_SCALE_CONVRADIUS__1down);
				output_file->Add(histl_noMET_PH_SCALE_CONVRADIUS__1down);
				output_file->Add(histbb_noMET_PH_SCALE_CONVRADIUS__1up);
				output_file->Add(histbc_noMET_PH_SCALE_CONVRADIUS__1up);
				output_file->Add(histbl_noMET_PH_SCALE_CONVRADIUS__1up);
				output_file->Add(histcc_noMET_PH_SCALE_CONVRADIUS__1up);
				output_file->Add(histcl_noMET_PH_SCALE_CONVRADIUS__1up);
				output_file->Add(histll_noMET_PH_SCALE_CONVRADIUS__1up);
				output_file->Add(histb_noMET_PH_SCALE_CONVRADIUS__1up);
				output_file->Add(histc_noMET_PH_SCALE_CONVRADIUS__1up);
				output_file->Add(histl_noMET_PH_SCALE_CONVRADIUS__1up);
				output_file->Add(histbb_noMET_PH_SCALE_LEAKAGECONV__1down);
				output_file->Add(histbc_noMET_PH_SCALE_LEAKAGECONV__1down);
				output_file->Add(histbl_noMET_PH_SCALE_LEAKAGECONV__1down);
				output_file->Add(histcc_noMET_PH_SCALE_LEAKAGECONV__1down);
				output_file->Add(histcl_noMET_PH_SCALE_LEAKAGECONV__1down);
				output_file->Add(histll_noMET_PH_SCALE_LEAKAGECONV__1down);
				output_file->Add(histb_noMET_PH_SCALE_LEAKAGECONV__1down);
				output_file->Add(histc_noMET_PH_SCALE_LEAKAGECONV__1down);
				output_file->Add(histl_noMET_PH_SCALE_LEAKAGECONV__1down);
				output_file->Add(histbb_noMET_PH_SCALE_LEAKAGECONV__1up);
				output_file->Add(histbc_noMET_PH_SCALE_LEAKAGECONV__1up);
				output_file->Add(histbl_noMET_PH_SCALE_LEAKAGECONV__1up);
				output_file->Add(histcc_noMET_PH_SCALE_LEAKAGECONV__1up);
				output_file->Add(histcl_noMET_PH_SCALE_LEAKAGECONV__1up);
				output_file->Add(histll_noMET_PH_SCALE_LEAKAGECONV__1up);
				output_file->Add(histb_noMET_PH_SCALE_LEAKAGECONV__1up);
				output_file->Add(histc_noMET_PH_SCALE_LEAKAGECONV__1up);
				output_file->Add(histl_noMET_PH_SCALE_LEAKAGECONV__1up);
				output_file->Add(histbb_noMET_PH_SCALE_LEAKAGEUNCONV__1down);
				output_file->Add(histbc_noMET_PH_SCALE_LEAKAGEUNCONV__1down);
				output_file->Add(histbl_noMET_PH_SCALE_LEAKAGEUNCONV__1down);
				output_file->Add(histcc_noMET_PH_SCALE_LEAKAGEUNCONV__1down);
				output_file->Add(histcl_noMET_PH_SCALE_LEAKAGEUNCONV__1down);
				output_file->Add(histll_noMET_PH_SCALE_LEAKAGEUNCONV__1down);
				output_file->Add(histb_noMET_PH_SCALE_LEAKAGEUNCONV__1down);
				output_file->Add(histc_noMET_PH_SCALE_LEAKAGEUNCONV__1down);
				output_file->Add(histl_noMET_PH_SCALE_LEAKAGEUNCONV__1down);
				output_file->Add(histbb_noMET_PH_SCALE_LEAKAGEUNCONV__1up);
				output_file->Add(histbc_noMET_PH_SCALE_LEAKAGEUNCONV__1up);
				output_file->Add(histbl_noMET_PH_SCALE_LEAKAGEUNCONV__1up);
				output_file->Add(histcc_noMET_PH_SCALE_LEAKAGEUNCONV__1up);
				output_file->Add(histcl_noMET_PH_SCALE_LEAKAGEUNCONV__1up);
				output_file->Add(histll_noMET_PH_SCALE_LEAKAGEUNCONV__1up);
				output_file->Add(histb_noMET_PH_SCALE_LEAKAGEUNCONV__1up);
				output_file->Add(histc_noMET_PH_SCALE_LEAKAGEUNCONV__1up);
				output_file->Add(histl_noMET_PH_SCALE_LEAKAGEUNCONV__1up);

				output_file->Write();
				output_file->Close();
			}//end nInputs
		} //end mc
	} //end sys
}
