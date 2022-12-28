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
	std::vector<TString> systematicType = {"FlavorAllSys3"};//, "JetSys2", "JetSys3",   "JetSys4"};
	std::vector<TString> mcType = {"mc16a", "mc16d", "mc16e"};

	for(TString sys : systematicType){
		for(TString mc : mcType){
			int nInputs;
			if (mc == "mc16a"){nInputs = 4;}
			if (mc == "mc16d"){nInputs = 5;}
			if (mc == "mc16e"){nInputs = 7;}
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

				int FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_leadjet_truthlabel",     &FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_truthlabel);
				int FT_EFF_Eigen_Light_4__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_subleadjet_truthlabel",  &FT_EFF_Eigen_Light_4__1down_yyHF_subleadjet_truthlabel);
				int FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_leadjet_btagbin",        &FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_btagbin);
				int FT_EFF_Eigen_Light_4__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_subleadjet_btagbin",     &FT_EFF_Eigen_Light_4__1down_yyHF_subleadjet_btagbin);
				int FT_EFF_Eigen_Light_4__1down_yyHF_Njet_central;          myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_Njet_central",           &FT_EFF_Eigen_Light_4__1down_yyHF_Njet_central);
				int FT_EFF_Eigen_Light_4__1down_yyHF_cutFlow;               myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_cutFlow",                &FT_EFF_Eigen_Light_4__1down_yyHF_cutFlow);
				int FT_EFF_Eigen_Light_4__1down_yyHF_nelectron;             myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_nelectron",              &FT_EFF_Eigen_Light_4__1down_yyHF_nelectron);
				int FT_EFF_Eigen_Light_4__1down_yyHF_nmuon;                 myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_nmuon",                  &FT_EFF_Eigen_Light_4__1down_yyHF_nmuon);
				bool FT_EFF_Eigen_Light_4__1down_isPassed;                  myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.isPassed",                    &FT_EFF_Eigen_Light_4__1down_isPassed);
				float FT_EFF_Eigen_Light_4__1down_yyHFjj_weight;            myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHFjj_weight",               &FT_EFF_Eigen_Light_4__1down_yyHFjj_weight);
				float FT_EFF_Eigen_Light_4__1down_yyHFj_weight;             myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHFj_weight",                &FT_EFF_Eigen_Light_4__1down_yyHFj_weight);
				float FT_EFF_Eigen_Light_4__1down_yyHF_met;                 myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_met",                    &FT_EFF_Eigen_Light_4__1down_yyHF_met);
				float FT_EFF_Eigen_Light_4__1down_m_yy;                     myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.m_yy",                        &FT_EFF_Eigen_Light_4__1down_m_yy);
				float FT_EFF_Eigen_Light_4__1down_m_yyjj;                   myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.m_yyjj",                      &FT_EFF_Eigen_Light_4__1down_m_yyjj);
				float FT_EFF_Eigen_Light_4__1down_pT_yy;                    myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.pT_yy",                       &FT_EFF_Eigen_Light_4__1down_pT_yy);
				float FT_EFF_Eigen_Light_4__1down_HGamWeight;               myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.HGamWeight",                  &FT_EFF_Eigen_Light_4__1down_HGamWeight);
				float FT_EFF_Eigen_Light_4__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_subleadjet_pt",          &FT_EFF_Eigen_Light_4__1down_yyHF_subleadjet_pt);
				float FT_EFF_Eigen_Light_4__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_subleadjet_phi",         &FT_EFF_Eigen_Light_4__1down_yyHF_subleadjet_phi);
				float FT_EFF_Eigen_Light_4__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_subleadjet_m",           &FT_EFF_Eigen_Light_4__1down_yyHF_subleadjet_m);
				float FT_EFF_Eigen_Light_4__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_subleadjet_eta",         &FT_EFF_Eigen_Light_4__1down_yyHF_subleadjet_eta);
				float FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_leadjet_pt",             &FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_pt);
				float FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_leadjet_phi",            &FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_phi);
				float FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_leadjet_m",              &FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_m);
				float FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("FT_EFF_Eigen_Light_4__1down.yyHF_leadjet_eta",            &FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_eta);
				int FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_leadjet_truthlabel",     &FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_truthlabel);
				int FT_EFF_Eigen_Light_3__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_subleadjet_truthlabel",  &FT_EFF_Eigen_Light_3__1down_yyHF_subleadjet_truthlabel);
				int FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_leadjet_btagbin",        &FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_btagbin);
				int FT_EFF_Eigen_Light_3__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_subleadjet_btagbin",     &FT_EFF_Eigen_Light_3__1down_yyHF_subleadjet_btagbin);
				int FT_EFF_Eigen_Light_3__1down_yyHF_Njet_central;          myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_Njet_central",           &FT_EFF_Eigen_Light_3__1down_yyHF_Njet_central);
				int FT_EFF_Eigen_Light_3__1down_yyHF_cutFlow;               myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_cutFlow",                &FT_EFF_Eigen_Light_3__1down_yyHF_cutFlow);
				int FT_EFF_Eigen_Light_3__1down_yyHF_nelectron;             myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_nelectron",              &FT_EFF_Eigen_Light_3__1down_yyHF_nelectron);
				int FT_EFF_Eigen_Light_3__1down_yyHF_nmuon;                 myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_nmuon",                  &FT_EFF_Eigen_Light_3__1down_yyHF_nmuon);
				bool FT_EFF_Eigen_Light_3__1down_isPassed;                  myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.isPassed",                    &FT_EFF_Eigen_Light_3__1down_isPassed);
				float FT_EFF_Eigen_Light_3__1down_yyHFjj_weight;            myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHFjj_weight",               &FT_EFF_Eigen_Light_3__1down_yyHFjj_weight);
				float FT_EFF_Eigen_Light_3__1down_yyHFj_weight;             myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHFj_weight",                &FT_EFF_Eigen_Light_3__1down_yyHFj_weight);
				float FT_EFF_Eigen_Light_3__1down_yyHF_met;                 myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_met",                    &FT_EFF_Eigen_Light_3__1down_yyHF_met);
				float FT_EFF_Eigen_Light_3__1down_m_yy;                     myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.m_yy",                        &FT_EFF_Eigen_Light_3__1down_m_yy);
				float FT_EFF_Eigen_Light_3__1down_m_yyjj;                   myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.m_yyjj",                      &FT_EFF_Eigen_Light_3__1down_m_yyjj);
				float FT_EFF_Eigen_Light_3__1down_pT_yy;                    myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.pT_yy",                       &FT_EFF_Eigen_Light_3__1down_pT_yy);
				float FT_EFF_Eigen_Light_3__1down_HGamWeight;               myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.HGamWeight",                  &FT_EFF_Eigen_Light_3__1down_HGamWeight);
				float FT_EFF_Eigen_Light_3__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_subleadjet_pt",          &FT_EFF_Eigen_Light_3__1down_yyHF_subleadjet_pt);
				float FT_EFF_Eigen_Light_3__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_subleadjet_phi",         &FT_EFF_Eigen_Light_3__1down_yyHF_subleadjet_phi);
				float FT_EFF_Eigen_Light_3__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_subleadjet_m",           &FT_EFF_Eigen_Light_3__1down_yyHF_subleadjet_m);
				float FT_EFF_Eigen_Light_3__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_subleadjet_eta",         &FT_EFF_Eigen_Light_3__1down_yyHF_subleadjet_eta);
				float FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_leadjet_pt",             &FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_pt);
				float FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_leadjet_phi",            &FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_phi);
				float FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_leadjet_m",              &FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_m);
				float FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("FT_EFF_Eigen_Light_3__1down.yyHF_leadjet_eta",            &FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_eta);
				int FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_leadjet_truthlabel",     &FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_truthlabel);
				int FT_EFF_Eigen_Light_2__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_subleadjet_truthlabel",  &FT_EFF_Eigen_Light_2__1down_yyHF_subleadjet_truthlabel);
				int FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_leadjet_btagbin",        &FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_btagbin);
				int FT_EFF_Eigen_Light_2__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_subleadjet_btagbin",     &FT_EFF_Eigen_Light_2__1down_yyHF_subleadjet_btagbin);
				int FT_EFF_Eigen_Light_2__1down_yyHF_Njet_central;          myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_Njet_central",           &FT_EFF_Eigen_Light_2__1down_yyHF_Njet_central);
				int FT_EFF_Eigen_Light_2__1down_yyHF_cutFlow;               myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_cutFlow",                &FT_EFF_Eigen_Light_2__1down_yyHF_cutFlow);
				int FT_EFF_Eigen_Light_2__1down_yyHF_nelectron;             myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_nelectron",              &FT_EFF_Eigen_Light_2__1down_yyHF_nelectron);
				int FT_EFF_Eigen_Light_2__1down_yyHF_nmuon;                 myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_nmuon",                  &FT_EFF_Eigen_Light_2__1down_yyHF_nmuon);
				bool FT_EFF_Eigen_Light_2__1down_isPassed;                  myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.isPassed",                    &FT_EFF_Eigen_Light_2__1down_isPassed);
				float FT_EFF_Eigen_Light_2__1down_yyHFjj_weight;            myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHFjj_weight",               &FT_EFF_Eigen_Light_2__1down_yyHFjj_weight);
				float FT_EFF_Eigen_Light_2__1down_yyHFj_weight;             myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHFj_weight",                &FT_EFF_Eigen_Light_2__1down_yyHFj_weight);
				float FT_EFF_Eigen_Light_2__1down_yyHF_met;                 myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_met",                    &FT_EFF_Eigen_Light_2__1down_yyHF_met);
				float FT_EFF_Eigen_Light_2__1down_m_yy;                     myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.m_yy",                        &FT_EFF_Eigen_Light_2__1down_m_yy);
				float FT_EFF_Eigen_Light_2__1down_m_yyjj;                   myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.m_yyjj",                      &FT_EFF_Eigen_Light_2__1down_m_yyjj);
				float FT_EFF_Eigen_Light_2__1down_pT_yy;                    myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.pT_yy",                       &FT_EFF_Eigen_Light_2__1down_pT_yy);
				float FT_EFF_Eigen_Light_2__1down_HGamWeight;               myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.HGamWeight",                  &FT_EFF_Eigen_Light_2__1down_HGamWeight);
				float FT_EFF_Eigen_Light_2__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_subleadjet_pt",          &FT_EFF_Eigen_Light_2__1down_yyHF_subleadjet_pt);
				float FT_EFF_Eigen_Light_2__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_subleadjet_phi",         &FT_EFF_Eigen_Light_2__1down_yyHF_subleadjet_phi);
				float FT_EFF_Eigen_Light_2__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_subleadjet_m",           &FT_EFF_Eigen_Light_2__1down_yyHF_subleadjet_m);
				float FT_EFF_Eigen_Light_2__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_subleadjet_eta",         &FT_EFF_Eigen_Light_2__1down_yyHF_subleadjet_eta);
				float FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_leadjet_pt",             &FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_pt);
				float FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_leadjet_phi",            &FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_phi);
				float FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_leadjet_m",              &FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_m);
				float FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("FT_EFF_Eigen_Light_2__1down.yyHF_leadjet_eta",            &FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_eta);
				int FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_leadjet_truthlabel",     &FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_truthlabel);
				int FT_EFF_Eigen_Light_1__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_subleadjet_truthlabel",  &FT_EFF_Eigen_Light_1__1down_yyHF_subleadjet_truthlabel);
				int FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_leadjet_btagbin",        &FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_btagbin);
				int FT_EFF_Eigen_Light_1__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_subleadjet_btagbin",     &FT_EFF_Eigen_Light_1__1down_yyHF_subleadjet_btagbin);
				int FT_EFF_Eigen_Light_1__1down_yyHF_Njet_central;          myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_Njet_central",           &FT_EFF_Eigen_Light_1__1down_yyHF_Njet_central);
				int FT_EFF_Eigen_Light_1__1down_yyHF_cutFlow;               myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_cutFlow",                &FT_EFF_Eigen_Light_1__1down_yyHF_cutFlow);
				int FT_EFF_Eigen_Light_1__1down_yyHF_nelectron;             myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_nelectron",              &FT_EFF_Eigen_Light_1__1down_yyHF_nelectron);
				int FT_EFF_Eigen_Light_1__1down_yyHF_nmuon;                 myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_nmuon",                  &FT_EFF_Eigen_Light_1__1down_yyHF_nmuon);
				bool FT_EFF_Eigen_Light_1__1down_isPassed;                  myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.isPassed",                    &FT_EFF_Eigen_Light_1__1down_isPassed);
				float FT_EFF_Eigen_Light_1__1down_yyHFjj_weight;            myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHFjj_weight",               &FT_EFF_Eigen_Light_1__1down_yyHFjj_weight);
				float FT_EFF_Eigen_Light_1__1down_yyHFj_weight;             myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHFj_weight",                &FT_EFF_Eigen_Light_1__1down_yyHFj_weight);
				float FT_EFF_Eigen_Light_1__1down_yyHF_met;                 myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_met",                    &FT_EFF_Eigen_Light_1__1down_yyHF_met);
				float FT_EFF_Eigen_Light_1__1down_m_yy;                     myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.m_yy",                        &FT_EFF_Eigen_Light_1__1down_m_yy);
				float FT_EFF_Eigen_Light_1__1down_m_yyjj;                   myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.m_yyjj",                      &FT_EFF_Eigen_Light_1__1down_m_yyjj);
				float FT_EFF_Eigen_Light_1__1down_pT_yy;                    myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.pT_yy",                       &FT_EFF_Eigen_Light_1__1down_pT_yy);
				float FT_EFF_Eigen_Light_1__1down_HGamWeight;               myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.HGamWeight",                  &FT_EFF_Eigen_Light_1__1down_HGamWeight);
				float FT_EFF_Eigen_Light_1__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_subleadjet_pt",          &FT_EFF_Eigen_Light_1__1down_yyHF_subleadjet_pt);
				float FT_EFF_Eigen_Light_1__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_subleadjet_phi",         &FT_EFF_Eigen_Light_1__1down_yyHF_subleadjet_phi);
				float FT_EFF_Eigen_Light_1__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_subleadjet_m",           &FT_EFF_Eigen_Light_1__1down_yyHF_subleadjet_m);
				float FT_EFF_Eigen_Light_1__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_subleadjet_eta",         &FT_EFF_Eigen_Light_1__1down_yyHF_subleadjet_eta);
				float FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_leadjet_pt",             &FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_pt);
				float FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_leadjet_phi",            &FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_phi);
				float FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_leadjet_m",              &FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_m);
				float FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("FT_EFF_Eigen_Light_1__1down.yyHF_leadjet_eta",            &FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_eta);
				int FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_leadjet_truthlabel",     &FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_truthlabel);
				int FT_EFF_Eigen_Light_0__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_subleadjet_truthlabel",  &FT_EFF_Eigen_Light_0__1down_yyHF_subleadjet_truthlabel);
				int FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_leadjet_btagbin",        &FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_btagbin);
				int FT_EFF_Eigen_Light_0__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_subleadjet_btagbin",     &FT_EFF_Eigen_Light_0__1down_yyHF_subleadjet_btagbin);
				int FT_EFF_Eigen_Light_0__1down_yyHF_Njet_central;          myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_Njet_central",           &FT_EFF_Eigen_Light_0__1down_yyHF_Njet_central);
				int FT_EFF_Eigen_Light_0__1down_yyHF_cutFlow;               myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_cutFlow",                &FT_EFF_Eigen_Light_0__1down_yyHF_cutFlow);
				int FT_EFF_Eigen_Light_0__1down_yyHF_nelectron;             myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_nelectron",              &FT_EFF_Eigen_Light_0__1down_yyHF_nelectron);
				int FT_EFF_Eigen_Light_0__1down_yyHF_nmuon;                 myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_nmuon",                  &FT_EFF_Eigen_Light_0__1down_yyHF_nmuon);
				bool FT_EFF_Eigen_Light_0__1down_isPassed;                  myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.isPassed",                    &FT_EFF_Eigen_Light_0__1down_isPassed);
				float FT_EFF_Eigen_Light_0__1down_yyHFjj_weight;            myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHFjj_weight",               &FT_EFF_Eigen_Light_0__1down_yyHFjj_weight);
				float FT_EFF_Eigen_Light_0__1down_yyHFj_weight;             myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHFj_weight",                &FT_EFF_Eigen_Light_0__1down_yyHFj_weight);
				float FT_EFF_Eigen_Light_0__1down_yyHF_met;                 myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_met",                    &FT_EFF_Eigen_Light_0__1down_yyHF_met);
				float FT_EFF_Eigen_Light_0__1down_m_yy;                     myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.m_yy",                        &FT_EFF_Eigen_Light_0__1down_m_yy);
				float FT_EFF_Eigen_Light_0__1down_m_yyjj;                   myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.m_yyjj",                      &FT_EFF_Eigen_Light_0__1down_m_yyjj);
				float FT_EFF_Eigen_Light_0__1down_pT_yy;                    myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.pT_yy",                       &FT_EFF_Eigen_Light_0__1down_pT_yy);
				float FT_EFF_Eigen_Light_0__1down_HGamWeight;               myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.HGamWeight",                  &FT_EFF_Eigen_Light_0__1down_HGamWeight);
				float FT_EFF_Eigen_Light_0__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_subleadjet_pt",          &FT_EFF_Eigen_Light_0__1down_yyHF_subleadjet_pt);
				float FT_EFF_Eigen_Light_0__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_subleadjet_phi",         &FT_EFF_Eigen_Light_0__1down_yyHF_subleadjet_phi);
				float FT_EFF_Eigen_Light_0__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_subleadjet_m",           &FT_EFF_Eigen_Light_0__1down_yyHF_subleadjet_m);
				float FT_EFF_Eigen_Light_0__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_subleadjet_eta",         &FT_EFF_Eigen_Light_0__1down_yyHF_subleadjet_eta);
				float FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_leadjet_pt",             &FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_pt);
				float FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_leadjet_phi",            &FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_phi);
				float FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_leadjet_m",              &FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_m);
				float FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("FT_EFF_Eigen_Light_0__1down.yyHF_leadjet_eta",            &FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_eta);


				TH1F *histbb_noMET_FT_EFF_Eigen_Light_4__1down = new TH1F("histbb_noMET_FT_EFF_Eigen_Light_4__1down", "histbb_noMET_FT_EFF_Eigen_Light_4__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_FT_EFF_Eigen_Light_4__1down = new TH1F("histbc_noMET_FT_EFF_Eigen_Light_4__1down", "histbc_noMET_FT_EFF_Eigen_Light_4__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_FT_EFF_Eigen_Light_4__1down = new TH1F("histbl_noMET_FT_EFF_Eigen_Light_4__1down", "histbl_noMET_FT_EFF_Eigen_Light_4__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_FT_EFF_Eigen_Light_4__1down = new TH1F("histcc_noMET_FT_EFF_Eigen_Light_4__1down", "histcc_noMET_FT_EFF_Eigen_Light_4__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_FT_EFF_Eigen_Light_4__1down = new TH1F("histcl_noMET_FT_EFF_Eigen_Light_4__1down", "histcl_noMET_FT_EFF_Eigen_Light_4__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_FT_EFF_Eigen_Light_4__1down = new TH1F("histll_noMET_FT_EFF_Eigen_Light_4__1down", "histll_noMET_FT_EFF_Eigen_Light_4__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_FT_EFF_Eigen_Light_4__1down = new TH1F("histb_noMET_FT_EFF_Eigen_Light_4__1down", "histb_noMET_FT_EFF_Eigen_Light_4__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_FT_EFF_Eigen_Light_4__1down = new TH1F("histc_noMET_FT_EFF_Eigen_Light_4__1down", "histc_noMET_FT_EFF_Eigen_Light_4__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_FT_EFF_Eigen_Light_4__1down = new TH1F("histl_noMET_FT_EFF_Eigen_Light_4__1down", "histl_noMET_FT_EFF_Eigen_Light_4__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_FT_EFF_Eigen_Light_3__1down = new TH1F("histbb_noMET_FT_EFF_Eigen_Light_3__1down", "histbb_noMET_FT_EFF_Eigen_Light_3__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_FT_EFF_Eigen_Light_3__1down = new TH1F("histbc_noMET_FT_EFF_Eigen_Light_3__1down", "histbc_noMET_FT_EFF_Eigen_Light_3__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_FT_EFF_Eigen_Light_3__1down = new TH1F("histbl_noMET_FT_EFF_Eigen_Light_3__1down", "histbl_noMET_FT_EFF_Eigen_Light_3__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_FT_EFF_Eigen_Light_3__1down = new TH1F("histcc_noMET_FT_EFF_Eigen_Light_3__1down", "histcc_noMET_FT_EFF_Eigen_Light_3__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_FT_EFF_Eigen_Light_3__1down = new TH1F("histcl_noMET_FT_EFF_Eigen_Light_3__1down", "histcl_noMET_FT_EFF_Eigen_Light_3__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_FT_EFF_Eigen_Light_3__1down = new TH1F("histll_noMET_FT_EFF_Eigen_Light_3__1down", "histll_noMET_FT_EFF_Eigen_Light_3__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_FT_EFF_Eigen_Light_3__1down = new TH1F("histb_noMET_FT_EFF_Eigen_Light_3__1down", "histb_noMET_FT_EFF_Eigen_Light_3__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_FT_EFF_Eigen_Light_3__1down = new TH1F("histc_noMET_FT_EFF_Eigen_Light_3__1down", "histc_noMET_FT_EFF_Eigen_Light_3__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_FT_EFF_Eigen_Light_3__1down = new TH1F("histl_noMET_FT_EFF_Eigen_Light_3__1down", "histl_noMET_FT_EFF_Eigen_Light_3__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_FT_EFF_Eigen_Light_2__1down = new TH1F("histbb_noMET_FT_EFF_Eigen_Light_2__1down", "histbb_noMET_FT_EFF_Eigen_Light_2__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_FT_EFF_Eigen_Light_2__1down = new TH1F("histbc_noMET_FT_EFF_Eigen_Light_2__1down", "histbc_noMET_FT_EFF_Eigen_Light_2__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_FT_EFF_Eigen_Light_2__1down = new TH1F("histbl_noMET_FT_EFF_Eigen_Light_2__1down", "histbl_noMET_FT_EFF_Eigen_Light_2__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_FT_EFF_Eigen_Light_2__1down = new TH1F("histcc_noMET_FT_EFF_Eigen_Light_2__1down", "histcc_noMET_FT_EFF_Eigen_Light_2__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_FT_EFF_Eigen_Light_2__1down = new TH1F("histcl_noMET_FT_EFF_Eigen_Light_2__1down", "histcl_noMET_FT_EFF_Eigen_Light_2__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_FT_EFF_Eigen_Light_2__1down = new TH1F("histll_noMET_FT_EFF_Eigen_Light_2__1down", "histll_noMET_FT_EFF_Eigen_Light_2__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_FT_EFF_Eigen_Light_2__1down = new TH1F("histb_noMET_FT_EFF_Eigen_Light_2__1down", "histb_noMET_FT_EFF_Eigen_Light_2__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_FT_EFF_Eigen_Light_2__1down = new TH1F("histc_noMET_FT_EFF_Eigen_Light_2__1down", "histc_noMET_FT_EFF_Eigen_Light_2__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_FT_EFF_Eigen_Light_2__1down = new TH1F("histl_noMET_FT_EFF_Eigen_Light_2__1down", "histl_noMET_FT_EFF_Eigen_Light_2__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_FT_EFF_Eigen_Light_1__1down = new TH1F("histbb_noMET_FT_EFF_Eigen_Light_1__1down", "histbb_noMET_FT_EFF_Eigen_Light_1__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_FT_EFF_Eigen_Light_1__1down = new TH1F("histbc_noMET_FT_EFF_Eigen_Light_1__1down", "histbc_noMET_FT_EFF_Eigen_Light_1__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_FT_EFF_Eigen_Light_1__1down = new TH1F("histbl_noMET_FT_EFF_Eigen_Light_1__1down", "histbl_noMET_FT_EFF_Eigen_Light_1__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_FT_EFF_Eigen_Light_1__1down = new TH1F("histcc_noMET_FT_EFF_Eigen_Light_1__1down", "histcc_noMET_FT_EFF_Eigen_Light_1__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_FT_EFF_Eigen_Light_1__1down = new TH1F("histcl_noMET_FT_EFF_Eigen_Light_1__1down", "histcl_noMET_FT_EFF_Eigen_Light_1__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_FT_EFF_Eigen_Light_1__1down = new TH1F("histll_noMET_FT_EFF_Eigen_Light_1__1down", "histll_noMET_FT_EFF_Eigen_Light_1__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_FT_EFF_Eigen_Light_1__1down = new TH1F("histb_noMET_FT_EFF_Eigen_Light_1__1down", "histb_noMET_FT_EFF_Eigen_Light_1__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_FT_EFF_Eigen_Light_1__1down = new TH1F("histc_noMET_FT_EFF_Eigen_Light_1__1down", "histc_noMET_FT_EFF_Eigen_Light_1__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_FT_EFF_Eigen_Light_1__1down = new TH1F("histl_noMET_FT_EFF_Eigen_Light_1__1down", "histl_noMET_FT_EFF_Eigen_Light_1__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_FT_EFF_Eigen_Light_0__1down = new TH1F("histbb_noMET_FT_EFF_Eigen_Light_0__1down", "histbb_noMET_FT_EFF_Eigen_Light_0__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_FT_EFF_Eigen_Light_0__1down = new TH1F("histbc_noMET_FT_EFF_Eigen_Light_0__1down", "histbc_noMET_FT_EFF_Eigen_Light_0__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_FT_EFF_Eigen_Light_0__1down = new TH1F("histbl_noMET_FT_EFF_Eigen_Light_0__1down", "histbl_noMET_FT_EFF_Eigen_Light_0__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_FT_EFF_Eigen_Light_0__1down = new TH1F("histcc_noMET_FT_EFF_Eigen_Light_0__1down", "histcc_noMET_FT_EFF_Eigen_Light_0__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_FT_EFF_Eigen_Light_0__1down = new TH1F("histcl_noMET_FT_EFF_Eigen_Light_0__1down", "histcl_noMET_FT_EFF_Eigen_Light_0__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_FT_EFF_Eigen_Light_0__1down = new TH1F("histll_noMET_FT_EFF_Eigen_Light_0__1down", "histll_noMET_FT_EFF_Eigen_Light_0__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_FT_EFF_Eigen_Light_0__1down = new TH1F("histb_noMET_FT_EFF_Eigen_Light_0__1down", "histb_noMET_FT_EFF_Eigen_Light_0__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_FT_EFF_Eigen_Light_0__1down = new TH1F("histc_noMET_FT_EFF_Eigen_Light_0__1down", "histc_noMET_FT_EFF_Eigen_Light_0__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_FT_EFF_Eigen_Light_0__1down = new TH1F("histl_noMET_FT_EFF_Eigen_Light_0__1down", "histl_noMET_FT_EFF_Eigen_Light_0__1down", 5, -0.5, 4.5);
				

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

					checkDijet(histbb_noMET_FT_EFF_Eigen_Light_4__1down, histbc_noMET_FT_EFF_Eigen_Light_4__1down, histbl_noMET_FT_EFF_Eigen_Light_4__1down, histcc_noMET_FT_EFF_Eigen_Light_4__1down, histcl_noMET_FT_EFF_Eigen_Light_4__1down, histll_noMET_FT_EFF_Eigen_Light_4__1down,
							   FT_EFF_Eigen_Light_4__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, FT_EFF_Eigen_Light_4__1down_isPassed, FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_truthlabel,
							   FT_EFF_Eigen_Light_4__1down_yyHF_subleadjet_truthlabel, FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_btagbin, FT_EFF_Eigen_Light_4__1down_yyHF_subleadjet_btagbin, FT_EFF_Eigen_Light_4__1down_yyHF_Njet_central, FT_EFF_Eigen_Light_4__1down_yyHFjj_weight, FT_EFF_Eigen_Light_4__1down_yyHF_met,
							   FT_EFF_Eigen_Light_4__1down_yyHF_nelectron, FT_EFF_Eigen_Light_4__1down_yyHF_nmuon, FT_EFF_Eigen_Light_4__1down_m_yy);
					checkDijet(histbb_noMET_FT_EFF_Eigen_Light_3__1down, histbc_noMET_FT_EFF_Eigen_Light_3__1down, histbl_noMET_FT_EFF_Eigen_Light_3__1down, histcc_noMET_FT_EFF_Eigen_Light_3__1down, histcl_noMET_FT_EFF_Eigen_Light_3__1down, histll_noMET_FT_EFF_Eigen_Light_3__1down,
							   FT_EFF_Eigen_Light_3__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, FT_EFF_Eigen_Light_3__1down_isPassed, FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_truthlabel,
							   FT_EFF_Eigen_Light_3__1down_yyHF_subleadjet_truthlabel, FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_btagbin, FT_EFF_Eigen_Light_3__1down_yyHF_subleadjet_btagbin, FT_EFF_Eigen_Light_3__1down_yyHF_Njet_central, FT_EFF_Eigen_Light_3__1down_yyHFjj_weight, FT_EFF_Eigen_Light_3__1down_yyHF_met,
							   FT_EFF_Eigen_Light_3__1down_yyHF_nelectron, FT_EFF_Eigen_Light_3__1down_yyHF_nmuon, FT_EFF_Eigen_Light_3__1down_m_yy);
					checkDijet(histbb_noMET_FT_EFF_Eigen_Light_2__1down, histbc_noMET_FT_EFF_Eigen_Light_2__1down, histbl_noMET_FT_EFF_Eigen_Light_2__1down, histcc_noMET_FT_EFF_Eigen_Light_2__1down, histcl_noMET_FT_EFF_Eigen_Light_2__1down, histll_noMET_FT_EFF_Eigen_Light_2__1down,
							   FT_EFF_Eigen_Light_2__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, FT_EFF_Eigen_Light_2__1down_isPassed, FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_truthlabel,
							   FT_EFF_Eigen_Light_2__1down_yyHF_subleadjet_truthlabel, FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_btagbin, FT_EFF_Eigen_Light_2__1down_yyHF_subleadjet_btagbin, FT_EFF_Eigen_Light_2__1down_yyHF_Njet_central, FT_EFF_Eigen_Light_2__1down_yyHFjj_weight, FT_EFF_Eigen_Light_2__1down_yyHF_met,
							   FT_EFF_Eigen_Light_2__1down_yyHF_nelectron, FT_EFF_Eigen_Light_2__1down_yyHF_nmuon, FT_EFF_Eigen_Light_2__1down_m_yy);
					checkDijet(histbb_noMET_FT_EFF_Eigen_Light_1__1down, histbc_noMET_FT_EFF_Eigen_Light_1__1down, histbl_noMET_FT_EFF_Eigen_Light_1__1down, histcc_noMET_FT_EFF_Eigen_Light_1__1down, histcl_noMET_FT_EFF_Eigen_Light_1__1down, histll_noMET_FT_EFF_Eigen_Light_1__1down,
							   FT_EFF_Eigen_Light_1__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, FT_EFF_Eigen_Light_1__1down_isPassed, FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_truthlabel,
							   FT_EFF_Eigen_Light_1__1down_yyHF_subleadjet_truthlabel, FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_btagbin, FT_EFF_Eigen_Light_1__1down_yyHF_subleadjet_btagbin, FT_EFF_Eigen_Light_1__1down_yyHF_Njet_central, FT_EFF_Eigen_Light_1__1down_yyHFjj_weight, FT_EFF_Eigen_Light_1__1down_yyHF_met,
							   FT_EFF_Eigen_Light_1__1down_yyHF_nelectron, FT_EFF_Eigen_Light_1__1down_yyHF_nmuon, FT_EFF_Eigen_Light_1__1down_m_yy);
					checkDijet(histbb_noMET_FT_EFF_Eigen_Light_0__1down, histbc_noMET_FT_EFF_Eigen_Light_0__1down, histbl_noMET_FT_EFF_Eigen_Light_0__1down, histcc_noMET_FT_EFF_Eigen_Light_0__1down, histcl_noMET_FT_EFF_Eigen_Light_0__1down, histll_noMET_FT_EFF_Eigen_Light_0__1down,
							   FT_EFF_Eigen_Light_0__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, FT_EFF_Eigen_Light_0__1down_isPassed, FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_truthlabel,
							   FT_EFF_Eigen_Light_0__1down_yyHF_subleadjet_truthlabel, FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_btagbin, FT_EFF_Eigen_Light_0__1down_yyHF_subleadjet_btagbin, FT_EFF_Eigen_Light_0__1down_yyHF_Njet_central, FT_EFF_Eigen_Light_0__1down_yyHFjj_weight, FT_EFF_Eigen_Light_0__1down_yyHF_met,
							   FT_EFF_Eigen_Light_0__1down_yyHF_nelectron, FT_EFF_Eigen_Light_0__1down_yyHF_nmuon, FT_EFF_Eigen_Light_0__1down_m_yy);




					 checkSingleJet(histb_noMET_FT_EFF_Eigen_Light_4__1down, histc_noMET_FT_EFF_Eigen_Light_4__1down, histl_noMET_FT_EFF_Eigen_Light_4__1down,
					 		   FT_EFF_Eigen_Light_4__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, FT_EFF_Eigen_Light_4__1down_isPassed, FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_truthlabel,
					 		   FT_EFF_Eigen_Light_4__1down_yyHF_leadjet_btagbin, FT_EFF_Eigen_Light_4__1down_yyHF_Njet_central, FT_EFF_Eigen_Light_4__1down_yyHFj_weight, FT_EFF_Eigen_Light_4__1down_yyHF_met,
					 		   FT_EFF_Eigen_Light_4__1down_yyHF_nelectron, FT_EFF_Eigen_Light_4__1down_yyHF_nmuon, FT_EFF_Eigen_Light_4__1down_m_yy);
					 checkSingleJet(histb_noMET_FT_EFF_Eigen_Light_3__1down, histc_noMET_FT_EFF_Eigen_Light_3__1down, histl_noMET_FT_EFF_Eigen_Light_3__1down,
					 		   FT_EFF_Eigen_Light_3__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, FT_EFF_Eigen_Light_3__1down_isPassed, FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_truthlabel,
					 		   FT_EFF_Eigen_Light_3__1down_yyHF_leadjet_btagbin, FT_EFF_Eigen_Light_3__1down_yyHF_Njet_central, FT_EFF_Eigen_Light_3__1down_yyHFj_weight, FT_EFF_Eigen_Light_3__1down_yyHF_met,
					 		   FT_EFF_Eigen_Light_3__1down_yyHF_nelectron, FT_EFF_Eigen_Light_3__1down_yyHF_nmuon, FT_EFF_Eigen_Light_3__1down_m_yy);
					 checkSingleJet(histb_noMET_FT_EFF_Eigen_Light_2__1down, histc_noMET_FT_EFF_Eigen_Light_2__1down, histl_noMET_FT_EFF_Eigen_Light_2__1down,
					 		   FT_EFF_Eigen_Light_2__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, FT_EFF_Eigen_Light_2__1down_isPassed, FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_truthlabel,
					 		   FT_EFF_Eigen_Light_2__1down_yyHF_leadjet_btagbin, FT_EFF_Eigen_Light_2__1down_yyHF_Njet_central, FT_EFF_Eigen_Light_2__1down_yyHFj_weight, FT_EFF_Eigen_Light_2__1down_yyHF_met,
					 		   FT_EFF_Eigen_Light_2__1down_yyHF_nelectron, FT_EFF_Eigen_Light_2__1down_yyHF_nmuon, FT_EFF_Eigen_Light_2__1down_m_yy);
					 checkSingleJet(histb_noMET_FT_EFF_Eigen_Light_1__1down, histc_noMET_FT_EFF_Eigen_Light_1__1down, histl_noMET_FT_EFF_Eigen_Light_1__1down,
					 		   FT_EFF_Eigen_Light_1__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, FT_EFF_Eigen_Light_1__1down_isPassed, FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_truthlabel,
					 		   FT_EFF_Eigen_Light_1__1down_yyHF_leadjet_btagbin, FT_EFF_Eigen_Light_1__1down_yyHF_Njet_central, FT_EFF_Eigen_Light_1__1down_yyHFj_weight, FT_EFF_Eigen_Light_1__1down_yyHF_met,
					 		   FT_EFF_Eigen_Light_1__1down_yyHF_nelectron, FT_EFF_Eigen_Light_1__1down_yyHF_nmuon, FT_EFF_Eigen_Light_1__1down_m_yy);
					 checkSingleJet(histb_noMET_FT_EFF_Eigen_Light_0__1down, histc_noMET_FT_EFF_Eigen_Light_0__1down, histl_noMET_FT_EFF_Eigen_Light_0__1down,
					 		   FT_EFF_Eigen_Light_0__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, FT_EFF_Eigen_Light_0__1down_isPassed, FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_truthlabel,
					 		   FT_EFF_Eigen_Light_0__1down_yyHF_leadjet_btagbin, FT_EFF_Eigen_Light_0__1down_yyHF_Njet_central, FT_EFF_Eigen_Light_0__1down_yyHFj_weight, FT_EFF_Eigen_Light_0__1down_yyHF_met,
					 		   FT_EFF_Eigen_Light_0__1down_yyHF_nelectron, FT_EFF_Eigen_Light_0__1down_yyHF_nmuon, FT_EFF_Eigen_Light_0__1down_m_yy);

				}
				TFile* output_file = new TFile(output_name, "recreate");
				cout << "creating file: "<< output_name << endl;

				output_file->Add(histbb_noMET_FT_EFF_Eigen_Light_4__1down);
				output_file->Add(histbc_noMET_FT_EFF_Eigen_Light_4__1down);
				output_file->Add(histbl_noMET_FT_EFF_Eigen_Light_4__1down);
				output_file->Add(histcc_noMET_FT_EFF_Eigen_Light_4__1down);
				output_file->Add(histcl_noMET_FT_EFF_Eigen_Light_4__1down);
				output_file->Add(histll_noMET_FT_EFF_Eigen_Light_4__1down);
				output_file->Add(histb_noMET_FT_EFF_Eigen_Light_4__1down);
				output_file->Add(histc_noMET_FT_EFF_Eigen_Light_4__1down);
				output_file->Add(histl_noMET_FT_EFF_Eigen_Light_4__1down);
				output_file->Add(histbb_noMET_FT_EFF_Eigen_Light_3__1down);
				output_file->Add(histbc_noMET_FT_EFF_Eigen_Light_3__1down);
				output_file->Add(histbl_noMET_FT_EFF_Eigen_Light_3__1down);
				output_file->Add(histcc_noMET_FT_EFF_Eigen_Light_3__1down);
				output_file->Add(histcl_noMET_FT_EFF_Eigen_Light_3__1down);
				output_file->Add(histll_noMET_FT_EFF_Eigen_Light_3__1down);
				output_file->Add(histb_noMET_FT_EFF_Eigen_Light_3__1down);
				output_file->Add(histc_noMET_FT_EFF_Eigen_Light_3__1down);
				output_file->Add(histl_noMET_FT_EFF_Eigen_Light_3__1down);
				output_file->Add(histbb_noMET_FT_EFF_Eigen_Light_2__1down);
				output_file->Add(histbc_noMET_FT_EFF_Eigen_Light_2__1down);
				output_file->Add(histbl_noMET_FT_EFF_Eigen_Light_2__1down);
				output_file->Add(histcc_noMET_FT_EFF_Eigen_Light_2__1down);
				output_file->Add(histcl_noMET_FT_EFF_Eigen_Light_2__1down);
				output_file->Add(histll_noMET_FT_EFF_Eigen_Light_2__1down);
				output_file->Add(histb_noMET_FT_EFF_Eigen_Light_2__1down);
				output_file->Add(histc_noMET_FT_EFF_Eigen_Light_2__1down);
				output_file->Add(histl_noMET_FT_EFF_Eigen_Light_2__1down);
				output_file->Add(histbb_noMET_FT_EFF_Eigen_Light_1__1down);
				output_file->Add(histbc_noMET_FT_EFF_Eigen_Light_1__1down);
				output_file->Add(histbl_noMET_FT_EFF_Eigen_Light_1__1down);
				output_file->Add(histcc_noMET_FT_EFF_Eigen_Light_1__1down);
				output_file->Add(histcl_noMET_FT_EFF_Eigen_Light_1__1down);
				output_file->Add(histll_noMET_FT_EFF_Eigen_Light_1__1down);
				output_file->Add(histb_noMET_FT_EFF_Eigen_Light_1__1down);
				output_file->Add(histc_noMET_FT_EFF_Eigen_Light_1__1down);
				output_file->Add(histl_noMET_FT_EFF_Eigen_Light_1__1down);
				output_file->Add(histbb_noMET_FT_EFF_Eigen_Light_0__1down);
				output_file->Add(histbc_noMET_FT_EFF_Eigen_Light_0__1down);
				output_file->Add(histbl_noMET_FT_EFF_Eigen_Light_0__1down);
				output_file->Add(histcc_noMET_FT_EFF_Eigen_Light_0__1down);
				output_file->Add(histcl_noMET_FT_EFF_Eigen_Light_0__1down);
				output_file->Add(histll_noMET_FT_EFF_Eigen_Light_0__1down);
				output_file->Add(histb_noMET_FT_EFF_Eigen_Light_0__1down);
				output_file->Add(histc_noMET_FT_EFF_Eigen_Light_0__1down);
				output_file->Add(histl_noMET_FT_EFF_Eigen_Light_0__1down);

				output_file->Write();
				output_file->Close();
			} //end nInputs
		} //end mc
	} //end sys
}
