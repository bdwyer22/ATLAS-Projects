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
	std::vector<TString> systematicType = {"JetSys2"};//, "JetSys2", "JetSys3",   "JetSys4"};
	std::vector<TString> mcType = {"mc16a", "mc16d", "mc16e"};

	for(TString sys : systematicType){
		for(TString mc : mcType){
			int nInputs;
			if (mc == "mc16a"){nInputs = 15;}
			if (mc == "mc16d"){nInputs = 15;}
			if (mc == "mc16e"){nInputs = 23;}
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

				int JET_BJES_Response__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_leadjet_truthlabel",     &JET_BJES_Response__1down_yyHF_leadjet_truthlabel);
				int JET_BJES_Response__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_subleadjet_truthlabel",  &JET_BJES_Response__1down_yyHF_subleadjet_truthlabel);
				int JET_BJES_Response__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_leadjet_btagbin",        &JET_BJES_Response__1down_yyHF_leadjet_btagbin);
				int JET_BJES_Response__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_subleadjet_btagbin",     &JET_BJES_Response__1down_yyHF_subleadjet_btagbin);
				int JET_BJES_Response__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_Njet_central",           &JET_BJES_Response__1down_yyHF_Njet_central);
				int JET_BJES_Response__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_cutFlow",                &JET_BJES_Response__1down_yyHF_cutFlow);
				int JET_BJES_Response__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_nelectron",              &JET_BJES_Response__1down_yyHF_nelectron);
				int JET_BJES_Response__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_nmuon",                  &JET_BJES_Response__1down_yyHF_nmuon);
				bool JET_BJES_Response__1down_isPassed;                  myTree->SetBranchAddress("JET_BJES_Response__1down.isPassed",                    &JET_BJES_Response__1down_isPassed);
				float JET_BJES_Response__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_BJES_Response__1down.yyHFjj_weight",               &JET_BJES_Response__1down_yyHFjj_weight);
				float JET_BJES_Response__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_BJES_Response__1down.yyHFj_weight",                &JET_BJES_Response__1down_yyHFj_weight);
				float JET_BJES_Response__1down_yyHF_met;                 myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_met",                    &JET_BJES_Response__1down_yyHF_met);
				float JET_BJES_Response__1down_m_yy;                     myTree->SetBranchAddress("JET_BJES_Response__1down.m_yy",                        &JET_BJES_Response__1down_m_yy);
				float JET_BJES_Response__1down_m_yyjj;                   myTree->SetBranchAddress("JET_BJES_Response__1down.m_yyjj",                      &JET_BJES_Response__1down_m_yyjj);
				float JET_BJES_Response__1down_pT_yy;                    myTree->SetBranchAddress("JET_BJES_Response__1down.pT_yy",                       &JET_BJES_Response__1down_pT_yy);
				float JET_BJES_Response__1down_HGamWeight;               myTree->SetBranchAddress("JET_BJES_Response__1down.HGamWeight",                  &JET_BJES_Response__1down_HGamWeight);
				float JET_BJES_Response__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_subleadjet_pt",          &JET_BJES_Response__1down_yyHF_subleadjet_pt);
				float JET_BJES_Response__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_subleadjet_phi",         &JET_BJES_Response__1down_yyHF_subleadjet_phi);
				float JET_BJES_Response__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_subleadjet_m",           &JET_BJES_Response__1down_yyHF_subleadjet_m);
				float JET_BJES_Response__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_subleadjet_eta",         &JET_BJES_Response__1down_yyHF_subleadjet_eta);
				float JET_BJES_Response__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_leadjet_pt",             &JET_BJES_Response__1down_yyHF_leadjet_pt);
				float JET_BJES_Response__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_leadjet_phi",            &JET_BJES_Response__1down_yyHF_leadjet_phi);
				float JET_BJES_Response__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_leadjet_m",              &JET_BJES_Response__1down_yyHF_leadjet_m);
				float JET_BJES_Response__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_BJES_Response__1down.yyHF_leadjet_eta",            &JET_BJES_Response__1down_yyHF_leadjet_eta);
				int JET_BJES_Response__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_leadjet_truthlabel",     &JET_BJES_Response__1up_yyHF_leadjet_truthlabel);
				int JET_BJES_Response__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_subleadjet_truthlabel",  &JET_BJES_Response__1up_yyHF_subleadjet_truthlabel);
				int JET_BJES_Response__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_leadjet_btagbin",        &JET_BJES_Response__1up_yyHF_leadjet_btagbin);
				int JET_BJES_Response__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_subleadjet_btagbin",     &JET_BJES_Response__1up_yyHF_subleadjet_btagbin);
				int JET_BJES_Response__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_Njet_central",           &JET_BJES_Response__1up_yyHF_Njet_central);
				int JET_BJES_Response__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_cutFlow",                &JET_BJES_Response__1up_yyHF_cutFlow);
				int JET_BJES_Response__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_nelectron",              &JET_BJES_Response__1up_yyHF_nelectron);
				int JET_BJES_Response__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_nmuon",                  &JET_BJES_Response__1up_yyHF_nmuon);
				bool JET_BJES_Response__1up_isPassed;                  myTree->SetBranchAddress("JET_BJES_Response__1up.isPassed",                    &JET_BJES_Response__1up_isPassed);
				float JET_BJES_Response__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_BJES_Response__1up.yyHFjj_weight",               &JET_BJES_Response__1up_yyHFjj_weight);
				float JET_BJES_Response__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_BJES_Response__1up.yyHFj_weight",                &JET_BJES_Response__1up_yyHFj_weight);
				float JET_BJES_Response__1up_yyHF_met;                 myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_met",                    &JET_BJES_Response__1up_yyHF_met);
				float JET_BJES_Response__1up_m_yy;                     myTree->SetBranchAddress("JET_BJES_Response__1up.m_yy",                        &JET_BJES_Response__1up_m_yy);
				float JET_BJES_Response__1up_m_yyjj;                   myTree->SetBranchAddress("JET_BJES_Response__1up.m_yyjj",                      &JET_BJES_Response__1up_m_yyjj);
				float JET_BJES_Response__1up_pT_yy;                    myTree->SetBranchAddress("JET_BJES_Response__1up.pT_yy",                       &JET_BJES_Response__1up_pT_yy);
				float JET_BJES_Response__1up_HGamWeight;               myTree->SetBranchAddress("JET_BJES_Response__1up.HGamWeight",                  &JET_BJES_Response__1up_HGamWeight);
				float JET_BJES_Response__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_subleadjet_pt",          &JET_BJES_Response__1up_yyHF_subleadjet_pt);
				float JET_BJES_Response__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_subleadjet_phi",         &JET_BJES_Response__1up_yyHF_subleadjet_phi);
				float JET_BJES_Response__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_subleadjet_m",           &JET_BJES_Response__1up_yyHF_subleadjet_m);
				float JET_BJES_Response__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_subleadjet_eta",         &JET_BJES_Response__1up_yyHF_subleadjet_eta);
				float JET_BJES_Response__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_leadjet_pt",             &JET_BJES_Response__1up_yyHF_leadjet_pt);
				float JET_BJES_Response__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_leadjet_phi",            &JET_BJES_Response__1up_yyHF_leadjet_phi);
				float JET_BJES_Response__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_leadjet_m",              &JET_BJES_Response__1up_yyHF_leadjet_m);
				float JET_BJES_Response__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_BJES_Response__1up.yyHF_leadjet_eta",            &JET_BJES_Response__1up_yyHF_leadjet_eta);
				int JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_leadjet_truthlabel",     &JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_truthlabel);
				int JET_EtaIntercalibration_Modelling__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_subleadjet_truthlabel",  &JET_EtaIntercalibration_Modelling__1down_yyHF_subleadjet_truthlabel);
				int JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_leadjet_btagbin",        &JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_btagbin);
				int JET_EtaIntercalibration_Modelling__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_subleadjet_btagbin",     &JET_EtaIntercalibration_Modelling__1down_yyHF_subleadjet_btagbin);
				int JET_EtaIntercalibration_Modelling__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_Njet_central",           &JET_EtaIntercalibration_Modelling__1down_yyHF_Njet_central);
				int JET_EtaIntercalibration_Modelling__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_cutFlow",                &JET_EtaIntercalibration_Modelling__1down_yyHF_cutFlow);
				int JET_EtaIntercalibration_Modelling__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_nelectron",              &JET_EtaIntercalibration_Modelling__1down_yyHF_nelectron);
				int JET_EtaIntercalibration_Modelling__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_nmuon",                  &JET_EtaIntercalibration_Modelling__1down_yyHF_nmuon);
				bool JET_EtaIntercalibration_Modelling__1down_isPassed;                  myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.isPassed",                    &JET_EtaIntercalibration_Modelling__1down_isPassed);
				float JET_EtaIntercalibration_Modelling__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHFjj_weight",               &JET_EtaIntercalibration_Modelling__1down_yyHFjj_weight);
				float JET_EtaIntercalibration_Modelling__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHFj_weight",                &JET_EtaIntercalibration_Modelling__1down_yyHFj_weight);
				float JET_EtaIntercalibration_Modelling__1down_yyHF_met;                 myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_met",                    &JET_EtaIntercalibration_Modelling__1down_yyHF_met);
				float JET_EtaIntercalibration_Modelling__1down_m_yy;                     myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.m_yy",                        &JET_EtaIntercalibration_Modelling__1down_m_yy);
				float JET_EtaIntercalibration_Modelling__1down_m_yyjj;                   myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.m_yyjj",                      &JET_EtaIntercalibration_Modelling__1down_m_yyjj);
				float JET_EtaIntercalibration_Modelling__1down_pT_yy;                    myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.pT_yy",                       &JET_EtaIntercalibration_Modelling__1down_pT_yy);
				float JET_EtaIntercalibration_Modelling__1down_HGamWeight;               myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.HGamWeight",                  &JET_EtaIntercalibration_Modelling__1down_HGamWeight);
				float JET_EtaIntercalibration_Modelling__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_subleadjet_pt",          &JET_EtaIntercalibration_Modelling__1down_yyHF_subleadjet_pt);
				float JET_EtaIntercalibration_Modelling__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_subleadjet_phi",         &JET_EtaIntercalibration_Modelling__1down_yyHF_subleadjet_phi);
				float JET_EtaIntercalibration_Modelling__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_subleadjet_m",           &JET_EtaIntercalibration_Modelling__1down_yyHF_subleadjet_m);
				float JET_EtaIntercalibration_Modelling__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_subleadjet_eta",         &JET_EtaIntercalibration_Modelling__1down_yyHF_subleadjet_eta);
				float JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_leadjet_pt",             &JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_pt);
				float JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_leadjet_phi",            &JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_phi);
				float JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_leadjet_m",              &JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_m);
				float JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1down.yyHF_leadjet_eta",            &JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_eta);
				int JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_leadjet_truthlabel",     &JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_truthlabel);
				int JET_EtaIntercalibration_Modelling__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_subleadjet_truthlabel",  &JET_EtaIntercalibration_Modelling__1up_yyHF_subleadjet_truthlabel);
				int JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_leadjet_btagbin",        &JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_btagbin);
				int JET_EtaIntercalibration_Modelling__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_subleadjet_btagbin",     &JET_EtaIntercalibration_Modelling__1up_yyHF_subleadjet_btagbin);
				int JET_EtaIntercalibration_Modelling__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_Njet_central",           &JET_EtaIntercalibration_Modelling__1up_yyHF_Njet_central);
				int JET_EtaIntercalibration_Modelling__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_cutFlow",                &JET_EtaIntercalibration_Modelling__1up_yyHF_cutFlow);
				int JET_EtaIntercalibration_Modelling__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_nelectron",              &JET_EtaIntercalibration_Modelling__1up_yyHF_nelectron);
				int JET_EtaIntercalibration_Modelling__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_nmuon",                  &JET_EtaIntercalibration_Modelling__1up_yyHF_nmuon);
				bool JET_EtaIntercalibration_Modelling__1up_isPassed;                  myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.isPassed",                    &JET_EtaIntercalibration_Modelling__1up_isPassed);
				float JET_EtaIntercalibration_Modelling__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHFjj_weight",               &JET_EtaIntercalibration_Modelling__1up_yyHFjj_weight);
				float JET_EtaIntercalibration_Modelling__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHFj_weight",                &JET_EtaIntercalibration_Modelling__1up_yyHFj_weight);
				float JET_EtaIntercalibration_Modelling__1up_yyHF_met;                 myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_met",                    &JET_EtaIntercalibration_Modelling__1up_yyHF_met);
				float JET_EtaIntercalibration_Modelling__1up_m_yy;                     myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.m_yy",                        &JET_EtaIntercalibration_Modelling__1up_m_yy);
				float JET_EtaIntercalibration_Modelling__1up_m_yyjj;                   myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.m_yyjj",                      &JET_EtaIntercalibration_Modelling__1up_m_yyjj);
				float JET_EtaIntercalibration_Modelling__1up_pT_yy;                    myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.pT_yy",                       &JET_EtaIntercalibration_Modelling__1up_pT_yy);
				float JET_EtaIntercalibration_Modelling__1up_HGamWeight;               myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.HGamWeight",                  &JET_EtaIntercalibration_Modelling__1up_HGamWeight);
				float JET_EtaIntercalibration_Modelling__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_subleadjet_pt",          &JET_EtaIntercalibration_Modelling__1up_yyHF_subleadjet_pt);
				float JET_EtaIntercalibration_Modelling__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_subleadjet_phi",         &JET_EtaIntercalibration_Modelling__1up_yyHF_subleadjet_phi);
				float JET_EtaIntercalibration_Modelling__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_subleadjet_m",           &JET_EtaIntercalibration_Modelling__1up_yyHF_subleadjet_m);
				float JET_EtaIntercalibration_Modelling__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_subleadjet_eta",         &JET_EtaIntercalibration_Modelling__1up_yyHF_subleadjet_eta);
				float JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_leadjet_pt",             &JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_pt);
				float JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_leadjet_phi",            &JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_phi);
				float JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_leadjet_m",              &JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_m);
				float JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_EtaIntercalibration_Modelling__1up.yyHF_leadjet_eta",            &JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_eta);
				int JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_leadjet_truthlabel",     &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_subleadjet_truthlabel",  &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_subleadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_leadjet_btagbin",        &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_subleadjet_btagbin",     &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_subleadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_Njet_central",           &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_Njet_central);
				int JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_cutFlow",                &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_cutFlow);
				int JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_nelectron",              &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_nelectron);
				int JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_nmuon",                  &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_nmuon);
				bool JET_EtaIntercalibration_NonClosure_2018data__1down_isPassed;                  myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.isPassed",                    &JET_EtaIntercalibration_NonClosure_2018data__1down_isPassed);
				float JET_EtaIntercalibration_NonClosure_2018data__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHFjj_weight",               &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHFjj_weight);
				float JET_EtaIntercalibration_NonClosure_2018data__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHFj_weight",                &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHFj_weight);
				float JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_met;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_met",                    &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_met);
				float JET_EtaIntercalibration_NonClosure_2018data__1down_m_yy;                     myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.m_yy",                        &JET_EtaIntercalibration_NonClosure_2018data__1down_m_yy);
				float JET_EtaIntercalibration_NonClosure_2018data__1down_m_yyjj;                   myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.m_yyjj",                      &JET_EtaIntercalibration_NonClosure_2018data__1down_m_yyjj);
				float JET_EtaIntercalibration_NonClosure_2018data__1down_pT_yy;                    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.pT_yy",                       &JET_EtaIntercalibration_NonClosure_2018data__1down_pT_yy);
				float JET_EtaIntercalibration_NonClosure_2018data__1down_HGamWeight;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.HGamWeight",                  &JET_EtaIntercalibration_NonClosure_2018data__1down_HGamWeight);
				float JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_subleadjet_pt",          &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_subleadjet_pt);
				float JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_subleadjet_phi",         &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_subleadjet_phi);
				float JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_subleadjet_m",           &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_subleadjet_m);
				float JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_subleadjet_eta",         &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_subleadjet_eta);
				float JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_leadjet_pt",             &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_pt);
				float JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_leadjet_phi",            &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_phi);
				float JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_leadjet_m",              &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_m);
				float JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1down.yyHF_leadjet_eta",            &JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_eta);
				int JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_leadjet_truthlabel",     &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_subleadjet_truthlabel",  &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_subleadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_leadjet_btagbin",        &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_subleadjet_btagbin",     &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_subleadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_Njet_central",           &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_Njet_central);
				int JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_cutFlow",                &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_cutFlow);
				int JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_nelectron",              &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_nelectron);
				int JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_nmuon",                  &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_nmuon);
				bool JET_EtaIntercalibration_NonClosure_2018data__1up_isPassed;                  myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.isPassed",                    &JET_EtaIntercalibration_NonClosure_2018data__1up_isPassed);
				float JET_EtaIntercalibration_NonClosure_2018data__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHFjj_weight",               &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHFjj_weight);
				float JET_EtaIntercalibration_NonClosure_2018data__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHFj_weight",                &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHFj_weight);
				float JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_met;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_met",                    &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_met);
				float JET_EtaIntercalibration_NonClosure_2018data__1up_m_yy;                     myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.m_yy",                        &JET_EtaIntercalibration_NonClosure_2018data__1up_m_yy);
				float JET_EtaIntercalibration_NonClosure_2018data__1up_m_yyjj;                   myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.m_yyjj",                      &JET_EtaIntercalibration_NonClosure_2018data__1up_m_yyjj);
				float JET_EtaIntercalibration_NonClosure_2018data__1up_pT_yy;                    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.pT_yy",                       &JET_EtaIntercalibration_NonClosure_2018data__1up_pT_yy);
				float JET_EtaIntercalibration_NonClosure_2018data__1up_HGamWeight;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.HGamWeight",                  &JET_EtaIntercalibration_NonClosure_2018data__1up_HGamWeight);
				float JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_subleadjet_pt",          &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_subleadjet_pt);
				float JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_subleadjet_phi",         &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_subleadjet_phi);
				float JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_subleadjet_m",           &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_subleadjet_m);
				float JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_subleadjet_eta",         &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_subleadjet_eta);
				float JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_leadjet_pt",             &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_pt);
				float JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_leadjet_phi",            &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_phi);
				float JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_leadjet_m",              &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_m);
				float JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_2018data__1up.yyHF_leadjet_eta",            &JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_eta);
				int JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_leadjet_truthlabel",     &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_subleadjet_truthlabel",  &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_subleadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_leadjet_btagbin",        &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_subleadjet_btagbin",     &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_subleadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_Njet_central",           &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_Njet_central);
				int JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_cutFlow",                &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_cutFlow);
				int JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_nelectron",              &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_nelectron);
				int JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_nmuon",                  &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_nmuon);
				bool JET_EtaIntercalibration_NonClosure_highE__1down_isPassed;                  myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.isPassed",                    &JET_EtaIntercalibration_NonClosure_highE__1down_isPassed);
				float JET_EtaIntercalibration_NonClosure_highE__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHFjj_weight",               &JET_EtaIntercalibration_NonClosure_highE__1down_yyHFjj_weight);
				float JET_EtaIntercalibration_NonClosure_highE__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHFj_weight",                &JET_EtaIntercalibration_NonClosure_highE__1down_yyHFj_weight);
				float JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_met;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_met",                    &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_met);
				float JET_EtaIntercalibration_NonClosure_highE__1down_m_yy;                     myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.m_yy",                        &JET_EtaIntercalibration_NonClosure_highE__1down_m_yy);
				float JET_EtaIntercalibration_NonClosure_highE__1down_m_yyjj;                   myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.m_yyjj",                      &JET_EtaIntercalibration_NonClosure_highE__1down_m_yyjj);
				float JET_EtaIntercalibration_NonClosure_highE__1down_pT_yy;                    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.pT_yy",                       &JET_EtaIntercalibration_NonClosure_highE__1down_pT_yy);
				float JET_EtaIntercalibration_NonClosure_highE__1down_HGamWeight;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.HGamWeight",                  &JET_EtaIntercalibration_NonClosure_highE__1down_HGamWeight);
				float JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_subleadjet_pt",          &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_subleadjet_pt);
				float JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_subleadjet_phi",         &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_subleadjet_phi);
				float JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_subleadjet_m",           &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_subleadjet_m);
				float JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_subleadjet_eta",         &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_subleadjet_eta);
				float JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_leadjet_pt",             &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_pt);
				float JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_leadjet_phi",            &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_phi);
				float JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_leadjet_m",              &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_m);
				float JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1down.yyHF_leadjet_eta",            &JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_eta);
				int JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_leadjet_truthlabel",     &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_subleadjet_truthlabel",  &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_subleadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_leadjet_btagbin",        &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_subleadjet_btagbin",     &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_subleadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_Njet_central",           &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_Njet_central);
				int JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_cutFlow",                &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_cutFlow);
				int JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_nelectron",              &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_nelectron);
				int JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_nmuon",                  &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_nmuon);
				bool JET_EtaIntercalibration_NonClosure_highE__1up_isPassed;                  myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.isPassed",                    &JET_EtaIntercalibration_NonClosure_highE__1up_isPassed);
				float JET_EtaIntercalibration_NonClosure_highE__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHFjj_weight",               &JET_EtaIntercalibration_NonClosure_highE__1up_yyHFjj_weight);
				float JET_EtaIntercalibration_NonClosure_highE__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHFj_weight",                &JET_EtaIntercalibration_NonClosure_highE__1up_yyHFj_weight);
				float JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_met;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_met",                    &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_met);
				float JET_EtaIntercalibration_NonClosure_highE__1up_m_yy;                     myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.m_yy",                        &JET_EtaIntercalibration_NonClosure_highE__1up_m_yy);
				float JET_EtaIntercalibration_NonClosure_highE__1up_m_yyjj;                   myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.m_yyjj",                      &JET_EtaIntercalibration_NonClosure_highE__1up_m_yyjj);
				float JET_EtaIntercalibration_NonClosure_highE__1up_pT_yy;                    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.pT_yy",                       &JET_EtaIntercalibration_NonClosure_highE__1up_pT_yy);
				float JET_EtaIntercalibration_NonClosure_highE__1up_HGamWeight;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.HGamWeight",                  &JET_EtaIntercalibration_NonClosure_highE__1up_HGamWeight);
				float JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_subleadjet_pt",          &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_subleadjet_pt);
				float JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_subleadjet_phi",         &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_subleadjet_phi);
				float JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_subleadjet_m",           &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_subleadjet_m);
				float JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_subleadjet_eta",         &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_subleadjet_eta);
				float JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_leadjet_pt",             &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_pt);
				float JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_leadjet_phi",            &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_phi);
				float JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_leadjet_m",              &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_m);
				float JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_highE__1up.yyHF_leadjet_eta",            &JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_eta);
				int JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_leadjet_truthlabel",     &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_subleadjet_truthlabel",  &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_subleadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_leadjet_btagbin",        &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_subleadjet_btagbin",     &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_subleadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_Njet_central",           &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_Njet_central);
				int JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_cutFlow",                &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_cutFlow);
				int JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_nelectron",              &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_nelectron);
				int JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_nmuon",                  &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_nmuon);
				bool JET_EtaIntercalibration_NonClosure_negEta__1down_isPassed;                  myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.isPassed",                    &JET_EtaIntercalibration_NonClosure_negEta__1down_isPassed);
				float JET_EtaIntercalibration_NonClosure_negEta__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHFjj_weight",               &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHFjj_weight);
				float JET_EtaIntercalibration_NonClosure_negEta__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHFj_weight",                &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHFj_weight);
				float JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_met;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_met",                    &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_met);
				float JET_EtaIntercalibration_NonClosure_negEta__1down_m_yy;                     myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.m_yy",                        &JET_EtaIntercalibration_NonClosure_negEta__1down_m_yy);
				float JET_EtaIntercalibration_NonClosure_negEta__1down_m_yyjj;                   myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.m_yyjj",                      &JET_EtaIntercalibration_NonClosure_negEta__1down_m_yyjj);
				float JET_EtaIntercalibration_NonClosure_negEta__1down_pT_yy;                    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.pT_yy",                       &JET_EtaIntercalibration_NonClosure_negEta__1down_pT_yy);
				float JET_EtaIntercalibration_NonClosure_negEta__1down_HGamWeight;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.HGamWeight",                  &JET_EtaIntercalibration_NonClosure_negEta__1down_HGamWeight);
				float JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_subleadjet_pt",          &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_subleadjet_pt);
				float JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_subleadjet_phi",         &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_subleadjet_phi);
				float JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_subleadjet_m",           &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_subleadjet_m);
				float JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_subleadjet_eta",         &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_subleadjet_eta);
				float JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_leadjet_pt",             &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_pt);
				float JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_leadjet_phi",            &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_phi);
				float JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_leadjet_m",              &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_m);
				float JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1down.yyHF_leadjet_eta",            &JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_eta);
				int JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_leadjet_truthlabel",     &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_subleadjet_truthlabel",  &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_subleadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_leadjet_btagbin",        &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_subleadjet_btagbin",     &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_subleadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_Njet_central",           &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_Njet_central);
				int JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_cutFlow",                &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_cutFlow);
				int JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_nelectron",              &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_nelectron);
				int JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_nmuon",                  &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_nmuon);
				bool JET_EtaIntercalibration_NonClosure_negEta__1up_isPassed;                  myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.isPassed",                    &JET_EtaIntercalibration_NonClosure_negEta__1up_isPassed);
				float JET_EtaIntercalibration_NonClosure_negEta__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHFjj_weight",               &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHFjj_weight);
				float JET_EtaIntercalibration_NonClosure_negEta__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHFj_weight",                &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHFj_weight);
				float JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_met;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_met",                    &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_met);
				float JET_EtaIntercalibration_NonClosure_negEta__1up_m_yy;                     myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.m_yy",                        &JET_EtaIntercalibration_NonClosure_negEta__1up_m_yy);
				float JET_EtaIntercalibration_NonClosure_negEta__1up_m_yyjj;                   myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.m_yyjj",                      &JET_EtaIntercalibration_NonClosure_negEta__1up_m_yyjj);
				float JET_EtaIntercalibration_NonClosure_negEta__1up_pT_yy;                    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.pT_yy",                       &JET_EtaIntercalibration_NonClosure_negEta__1up_pT_yy);
				float JET_EtaIntercalibration_NonClosure_negEta__1up_HGamWeight;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.HGamWeight",                  &JET_EtaIntercalibration_NonClosure_negEta__1up_HGamWeight);
				float JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_subleadjet_pt",          &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_subleadjet_pt);
				float JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_subleadjet_phi",         &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_subleadjet_phi);
				float JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_subleadjet_m",           &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_subleadjet_m);
				float JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_subleadjet_eta",         &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_subleadjet_eta);
				float JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_leadjet_pt",             &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_pt);
				float JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_leadjet_phi",            &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_phi);
				float JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_leadjet_m",              &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_m);
				float JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_negEta__1up.yyHF_leadjet_eta",            &JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_eta);
				int JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_leadjet_truthlabel",     &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_subleadjet_truthlabel",  &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_subleadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_leadjet_btagbin",        &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_subleadjet_btagbin",     &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_subleadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_Njet_central",           &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_Njet_central);
				int JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_cutFlow",                &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_cutFlow);
				int JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_nelectron",              &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_nelectron);
				int JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_nmuon",                  &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_nmuon);
				bool JET_EtaIntercalibration_NonClosure_posEta__1down_isPassed;                  myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.isPassed",                    &JET_EtaIntercalibration_NonClosure_posEta__1down_isPassed);
				float JET_EtaIntercalibration_NonClosure_posEta__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHFjj_weight",               &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHFjj_weight);
				float JET_EtaIntercalibration_NonClosure_posEta__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHFj_weight",                &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHFj_weight);
				float JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_met;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_met",                    &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_met);
				float JET_EtaIntercalibration_NonClosure_posEta__1down_m_yy;                     myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.m_yy",                        &JET_EtaIntercalibration_NonClosure_posEta__1down_m_yy);
				float JET_EtaIntercalibration_NonClosure_posEta__1down_m_yyjj;                   myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.m_yyjj",                      &JET_EtaIntercalibration_NonClosure_posEta__1down_m_yyjj);
				float JET_EtaIntercalibration_NonClosure_posEta__1down_pT_yy;                    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.pT_yy",                       &JET_EtaIntercalibration_NonClosure_posEta__1down_pT_yy);
				float JET_EtaIntercalibration_NonClosure_posEta__1down_HGamWeight;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.HGamWeight",                  &JET_EtaIntercalibration_NonClosure_posEta__1down_HGamWeight);
				float JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_subleadjet_pt",          &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_subleadjet_pt);
				float JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_subleadjet_phi",         &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_subleadjet_phi);
				float JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_subleadjet_m",           &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_subleadjet_m);
				float JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_subleadjet_eta",         &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_subleadjet_eta);
				float JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_leadjet_pt",             &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_pt);
				float JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_leadjet_phi",            &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_phi);
				float JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_leadjet_m",              &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_m);
				float JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1down.yyHF_leadjet_eta",            &JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_eta);
				int JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_leadjet_truthlabel",     &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_subleadjet_truthlabel",  &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_subleadjet_truthlabel);
				int JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_leadjet_btagbin",        &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_subleadjet_btagbin",     &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_subleadjet_btagbin);
				int JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_Njet_central",           &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_Njet_central);
				int JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_cutFlow",                &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_cutFlow);
				int JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_nelectron",              &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_nelectron);
				int JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_nmuon",                  &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_nmuon);
				bool JET_EtaIntercalibration_NonClosure_posEta__1up_isPassed;                  myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.isPassed",                    &JET_EtaIntercalibration_NonClosure_posEta__1up_isPassed);
				float JET_EtaIntercalibration_NonClosure_posEta__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHFjj_weight",               &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHFjj_weight);
				float JET_EtaIntercalibration_NonClosure_posEta__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHFj_weight",                &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHFj_weight);
				float JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_met;                 myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_met",                    &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_met);
				float JET_EtaIntercalibration_NonClosure_posEta__1up_m_yy;                     myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.m_yy",                        &JET_EtaIntercalibration_NonClosure_posEta__1up_m_yy);
				float JET_EtaIntercalibration_NonClosure_posEta__1up_m_yyjj;                   myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.m_yyjj",                      &JET_EtaIntercalibration_NonClosure_posEta__1up_m_yyjj);
				float JET_EtaIntercalibration_NonClosure_posEta__1up_pT_yy;                    myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.pT_yy",                       &JET_EtaIntercalibration_NonClosure_posEta__1up_pT_yy);
				float JET_EtaIntercalibration_NonClosure_posEta__1up_HGamWeight;               myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.HGamWeight",                  &JET_EtaIntercalibration_NonClosure_posEta__1up_HGamWeight);
				float JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_subleadjet_pt",          &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_subleadjet_pt);
				float JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_subleadjet_phi",         &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_subleadjet_phi);
				float JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_subleadjet_m",           &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_subleadjet_m);
				float JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_subleadjet_eta",         &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_subleadjet_eta);
				float JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_leadjet_pt",             &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_pt);
				float JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_leadjet_phi",            &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_phi);
				float JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_leadjet_m",              &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_m);
				float JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_EtaIntercalibration_NonClosure_posEta__1up.yyHF_leadjet_eta",            &JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_eta);
				int JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_leadjet_truthlabel",     &JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_truthlabel);
				int JET_EtaIntercalibration_TotalStat__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_subleadjet_truthlabel",  &JET_EtaIntercalibration_TotalStat__1down_yyHF_subleadjet_truthlabel);
				int JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_leadjet_btagbin",        &JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_btagbin);
				int JET_EtaIntercalibration_TotalStat__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_subleadjet_btagbin",     &JET_EtaIntercalibration_TotalStat__1down_yyHF_subleadjet_btagbin);
				int JET_EtaIntercalibration_TotalStat__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_Njet_central",           &JET_EtaIntercalibration_TotalStat__1down_yyHF_Njet_central);
				int JET_EtaIntercalibration_TotalStat__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_cutFlow",                &JET_EtaIntercalibration_TotalStat__1down_yyHF_cutFlow);
				int JET_EtaIntercalibration_TotalStat__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_nelectron",              &JET_EtaIntercalibration_TotalStat__1down_yyHF_nelectron);
				int JET_EtaIntercalibration_TotalStat__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_nmuon",                  &JET_EtaIntercalibration_TotalStat__1down_yyHF_nmuon);
				bool JET_EtaIntercalibration_TotalStat__1down_isPassed;                  myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.isPassed",                    &JET_EtaIntercalibration_TotalStat__1down_isPassed);
				float JET_EtaIntercalibration_TotalStat__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHFjj_weight",               &JET_EtaIntercalibration_TotalStat__1down_yyHFjj_weight);
				float JET_EtaIntercalibration_TotalStat__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHFj_weight",                &JET_EtaIntercalibration_TotalStat__1down_yyHFj_weight);
				float JET_EtaIntercalibration_TotalStat__1down_yyHF_met;                 myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_met",                    &JET_EtaIntercalibration_TotalStat__1down_yyHF_met);
				float JET_EtaIntercalibration_TotalStat__1down_m_yy;                     myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.m_yy",                        &JET_EtaIntercalibration_TotalStat__1down_m_yy);
				float JET_EtaIntercalibration_TotalStat__1down_m_yyjj;                   myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.m_yyjj",                      &JET_EtaIntercalibration_TotalStat__1down_m_yyjj);
				float JET_EtaIntercalibration_TotalStat__1down_pT_yy;                    myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.pT_yy",                       &JET_EtaIntercalibration_TotalStat__1down_pT_yy);
				float JET_EtaIntercalibration_TotalStat__1down_HGamWeight;               myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.HGamWeight",                  &JET_EtaIntercalibration_TotalStat__1down_HGamWeight);
				float JET_EtaIntercalibration_TotalStat__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_subleadjet_pt",          &JET_EtaIntercalibration_TotalStat__1down_yyHF_subleadjet_pt);
				float JET_EtaIntercalibration_TotalStat__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_subleadjet_phi",         &JET_EtaIntercalibration_TotalStat__1down_yyHF_subleadjet_phi);
				float JET_EtaIntercalibration_TotalStat__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_subleadjet_m",           &JET_EtaIntercalibration_TotalStat__1down_yyHF_subleadjet_m);
				float JET_EtaIntercalibration_TotalStat__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_subleadjet_eta",         &JET_EtaIntercalibration_TotalStat__1down_yyHF_subleadjet_eta);
				float JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_leadjet_pt",             &JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_pt);
				float JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_leadjet_phi",            &JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_phi);
				float JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_leadjet_m",              &JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_m);
				float JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1down.yyHF_leadjet_eta",            &JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_eta);
				int JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_leadjet_truthlabel",     &JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_truthlabel);
				int JET_EtaIntercalibration_TotalStat__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_subleadjet_truthlabel",  &JET_EtaIntercalibration_TotalStat__1up_yyHF_subleadjet_truthlabel);
				int JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_leadjet_btagbin",        &JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_btagbin);
				int JET_EtaIntercalibration_TotalStat__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_subleadjet_btagbin",     &JET_EtaIntercalibration_TotalStat__1up_yyHF_subleadjet_btagbin);
				int JET_EtaIntercalibration_TotalStat__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_Njet_central",           &JET_EtaIntercalibration_TotalStat__1up_yyHF_Njet_central);
				int JET_EtaIntercalibration_TotalStat__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_cutFlow",                &JET_EtaIntercalibration_TotalStat__1up_yyHF_cutFlow);
				int JET_EtaIntercalibration_TotalStat__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_nelectron",              &JET_EtaIntercalibration_TotalStat__1up_yyHF_nelectron);
				int JET_EtaIntercalibration_TotalStat__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_nmuon",                  &JET_EtaIntercalibration_TotalStat__1up_yyHF_nmuon);
				bool JET_EtaIntercalibration_TotalStat__1up_isPassed;                  myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.isPassed",                    &JET_EtaIntercalibration_TotalStat__1up_isPassed);
				float JET_EtaIntercalibration_TotalStat__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHFjj_weight",               &JET_EtaIntercalibration_TotalStat__1up_yyHFjj_weight);
				float JET_EtaIntercalibration_TotalStat__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHFj_weight",                &JET_EtaIntercalibration_TotalStat__1up_yyHFj_weight);
				float JET_EtaIntercalibration_TotalStat__1up_yyHF_met;                 myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_met",                    &JET_EtaIntercalibration_TotalStat__1up_yyHF_met);
				float JET_EtaIntercalibration_TotalStat__1up_m_yy;                     myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.m_yy",                        &JET_EtaIntercalibration_TotalStat__1up_m_yy);
				float JET_EtaIntercalibration_TotalStat__1up_m_yyjj;                   myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.m_yyjj",                      &JET_EtaIntercalibration_TotalStat__1up_m_yyjj);
				float JET_EtaIntercalibration_TotalStat__1up_pT_yy;                    myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.pT_yy",                       &JET_EtaIntercalibration_TotalStat__1up_pT_yy);
				float JET_EtaIntercalibration_TotalStat__1up_HGamWeight;               myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.HGamWeight",                  &JET_EtaIntercalibration_TotalStat__1up_HGamWeight);
				float JET_EtaIntercalibration_TotalStat__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_subleadjet_pt",          &JET_EtaIntercalibration_TotalStat__1up_yyHF_subleadjet_pt);
				float JET_EtaIntercalibration_TotalStat__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_subleadjet_phi",         &JET_EtaIntercalibration_TotalStat__1up_yyHF_subleadjet_phi);
				float JET_EtaIntercalibration_TotalStat__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_subleadjet_m",           &JET_EtaIntercalibration_TotalStat__1up_yyHF_subleadjet_m);
				float JET_EtaIntercalibration_TotalStat__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_subleadjet_eta",         &JET_EtaIntercalibration_TotalStat__1up_yyHF_subleadjet_eta);
				float JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_leadjet_pt",             &JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_pt);
				float JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_leadjet_phi",            &JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_phi);
				float JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_leadjet_m",              &JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_m);
				float JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_EtaIntercalibration_TotalStat__1up.yyHF_leadjet_eta",            &JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_eta);
				int JET_fJvtEfficiency__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_leadjet_truthlabel",     &JET_fJvtEfficiency__1down_yyHF_leadjet_truthlabel);
				int JET_fJvtEfficiency__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_subleadjet_truthlabel",  &JET_fJvtEfficiency__1down_yyHF_subleadjet_truthlabel);
				int JET_fJvtEfficiency__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_leadjet_btagbin",        &JET_fJvtEfficiency__1down_yyHF_leadjet_btagbin);
				int JET_fJvtEfficiency__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_subleadjet_btagbin",     &JET_fJvtEfficiency__1down_yyHF_subleadjet_btagbin);
				int JET_fJvtEfficiency__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_Njet_central",           &JET_fJvtEfficiency__1down_yyHF_Njet_central);
				int JET_fJvtEfficiency__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_cutFlow",                &JET_fJvtEfficiency__1down_yyHF_cutFlow);
				int JET_fJvtEfficiency__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_nelectron",              &JET_fJvtEfficiency__1down_yyHF_nelectron);
				int JET_fJvtEfficiency__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_nmuon",                  &JET_fJvtEfficiency__1down_yyHF_nmuon);
				bool JET_fJvtEfficiency__1down_isPassed;                  myTree->SetBranchAddress("JET_fJvtEfficiency__1down.isPassed",                    &JET_fJvtEfficiency__1down_isPassed);
				float JET_fJvtEfficiency__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHFjj_weight",               &JET_fJvtEfficiency__1down_yyHFjj_weight);
				float JET_fJvtEfficiency__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHFj_weight",                &JET_fJvtEfficiency__1down_yyHFj_weight);
				float JET_fJvtEfficiency__1down_yyHF_met;                 myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_met",                    &JET_fJvtEfficiency__1down_yyHF_met);
				float JET_fJvtEfficiency__1down_m_yy;                     myTree->SetBranchAddress("JET_fJvtEfficiency__1down.m_yy",                        &JET_fJvtEfficiency__1down_m_yy);
				float JET_fJvtEfficiency__1down_m_yyjj;                   myTree->SetBranchAddress("JET_fJvtEfficiency__1down.m_yyjj",                      &JET_fJvtEfficiency__1down_m_yyjj);
				float JET_fJvtEfficiency__1down_pT_yy;                    myTree->SetBranchAddress("JET_fJvtEfficiency__1down.pT_yy",                       &JET_fJvtEfficiency__1down_pT_yy);
				float JET_fJvtEfficiency__1down_HGamWeight;               myTree->SetBranchAddress("JET_fJvtEfficiency__1down.HGamWeight",                  &JET_fJvtEfficiency__1down_HGamWeight);
				float JET_fJvtEfficiency__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_subleadjet_pt",          &JET_fJvtEfficiency__1down_yyHF_subleadjet_pt);
				float JET_fJvtEfficiency__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_subleadjet_phi",         &JET_fJvtEfficiency__1down_yyHF_subleadjet_phi);
				float JET_fJvtEfficiency__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_subleadjet_m",           &JET_fJvtEfficiency__1down_yyHF_subleadjet_m);
				float JET_fJvtEfficiency__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_subleadjet_eta",         &JET_fJvtEfficiency__1down_yyHF_subleadjet_eta);
				float JET_fJvtEfficiency__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_leadjet_pt",             &JET_fJvtEfficiency__1down_yyHF_leadjet_pt);
				float JET_fJvtEfficiency__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_leadjet_phi",            &JET_fJvtEfficiency__1down_yyHF_leadjet_phi);
				float JET_fJvtEfficiency__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_leadjet_m",              &JET_fJvtEfficiency__1down_yyHF_leadjet_m);
				float JET_fJvtEfficiency__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_fJvtEfficiency__1down.yyHF_leadjet_eta",            &JET_fJvtEfficiency__1down_yyHF_leadjet_eta);
				int JET_fJvtEfficiency__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_leadjet_truthlabel",     &JET_fJvtEfficiency__1up_yyHF_leadjet_truthlabel);
				int JET_fJvtEfficiency__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_subleadjet_truthlabel",  &JET_fJvtEfficiency__1up_yyHF_subleadjet_truthlabel);
				int JET_fJvtEfficiency__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_leadjet_btagbin",        &JET_fJvtEfficiency__1up_yyHF_leadjet_btagbin);
				int JET_fJvtEfficiency__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_subleadjet_btagbin",     &JET_fJvtEfficiency__1up_yyHF_subleadjet_btagbin);
				int JET_fJvtEfficiency__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_Njet_central",           &JET_fJvtEfficiency__1up_yyHF_Njet_central);
				int JET_fJvtEfficiency__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_cutFlow",                &JET_fJvtEfficiency__1up_yyHF_cutFlow);
				int JET_fJvtEfficiency__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_nelectron",              &JET_fJvtEfficiency__1up_yyHF_nelectron);
				int JET_fJvtEfficiency__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_nmuon",                  &JET_fJvtEfficiency__1up_yyHF_nmuon);
				bool JET_fJvtEfficiency__1up_isPassed;                  myTree->SetBranchAddress("JET_fJvtEfficiency__1up.isPassed",                    &JET_fJvtEfficiency__1up_isPassed);
				float JET_fJvtEfficiency__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHFjj_weight",               &JET_fJvtEfficiency__1up_yyHFjj_weight);
				float JET_fJvtEfficiency__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHFj_weight",                &JET_fJvtEfficiency__1up_yyHFj_weight);
				float JET_fJvtEfficiency__1up_yyHF_met;                 myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_met",                    &JET_fJvtEfficiency__1up_yyHF_met);
				float JET_fJvtEfficiency__1up_m_yy;                     myTree->SetBranchAddress("JET_fJvtEfficiency__1up.m_yy",                        &JET_fJvtEfficiency__1up_m_yy);
				float JET_fJvtEfficiency__1up_m_yyjj;                   myTree->SetBranchAddress("JET_fJvtEfficiency__1up.m_yyjj",                      &JET_fJvtEfficiency__1up_m_yyjj);
				float JET_fJvtEfficiency__1up_pT_yy;                    myTree->SetBranchAddress("JET_fJvtEfficiency__1up.pT_yy",                       &JET_fJvtEfficiency__1up_pT_yy);
				float JET_fJvtEfficiency__1up_HGamWeight;               myTree->SetBranchAddress("JET_fJvtEfficiency__1up.HGamWeight",                  &JET_fJvtEfficiency__1up_HGamWeight);
				float JET_fJvtEfficiency__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_subleadjet_pt",          &JET_fJvtEfficiency__1up_yyHF_subleadjet_pt);
				float JET_fJvtEfficiency__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_subleadjet_phi",         &JET_fJvtEfficiency__1up_yyHF_subleadjet_phi);
				float JET_fJvtEfficiency__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_subleadjet_m",           &JET_fJvtEfficiency__1up_yyHF_subleadjet_m);
				float JET_fJvtEfficiency__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_subleadjet_eta",         &JET_fJvtEfficiency__1up_yyHF_subleadjet_eta);
				float JET_fJvtEfficiency__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_leadjet_pt",             &JET_fJvtEfficiency__1up_yyHF_leadjet_pt);
				float JET_fJvtEfficiency__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_leadjet_phi",            &JET_fJvtEfficiency__1up_yyHF_leadjet_phi);
				float JET_fJvtEfficiency__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_leadjet_m",              &JET_fJvtEfficiency__1up_yyHF_leadjet_m);
				float JET_fJvtEfficiency__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_fJvtEfficiency__1up.yyHF_leadjet_eta",            &JET_fJvtEfficiency__1up_yyHF_leadjet_eta);
				int JET_Flavor_Composition__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_leadjet_truthlabel",     &JET_Flavor_Composition__1down_yyHF_leadjet_truthlabel);
				int JET_Flavor_Composition__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_subleadjet_truthlabel",  &JET_Flavor_Composition__1down_yyHF_subleadjet_truthlabel);
				int JET_Flavor_Composition__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_leadjet_btagbin",        &JET_Flavor_Composition__1down_yyHF_leadjet_btagbin);
				int JET_Flavor_Composition__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_subleadjet_btagbin",     &JET_Flavor_Composition__1down_yyHF_subleadjet_btagbin);
				int JET_Flavor_Composition__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_Njet_central",           &JET_Flavor_Composition__1down_yyHF_Njet_central);
				int JET_Flavor_Composition__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_cutFlow",                &JET_Flavor_Composition__1down_yyHF_cutFlow);
				int JET_Flavor_Composition__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_nelectron",              &JET_Flavor_Composition__1down_yyHF_nelectron);
				int JET_Flavor_Composition__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_nmuon",                  &JET_Flavor_Composition__1down_yyHF_nmuon);
				bool JET_Flavor_Composition__1down_isPassed;                  myTree->SetBranchAddress("JET_Flavor_Composition__1down.isPassed",                    &JET_Flavor_Composition__1down_isPassed);
				float JET_Flavor_Composition__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHFjj_weight",               &JET_Flavor_Composition__1down_yyHFjj_weight);
				float JET_Flavor_Composition__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHFj_weight",                &JET_Flavor_Composition__1down_yyHFj_weight);
				float JET_Flavor_Composition__1down_yyHF_met;                 myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_met",                    &JET_Flavor_Composition__1down_yyHF_met);
				float JET_Flavor_Composition__1down_m_yy;                     myTree->SetBranchAddress("JET_Flavor_Composition__1down.m_yy",                        &JET_Flavor_Composition__1down_m_yy);
				float JET_Flavor_Composition__1down_m_yyjj;                   myTree->SetBranchAddress("JET_Flavor_Composition__1down.m_yyjj",                      &JET_Flavor_Composition__1down_m_yyjj);
				float JET_Flavor_Composition__1down_pT_yy;                    myTree->SetBranchAddress("JET_Flavor_Composition__1down.pT_yy",                       &JET_Flavor_Composition__1down_pT_yy);
				float JET_Flavor_Composition__1down_HGamWeight;               myTree->SetBranchAddress("JET_Flavor_Composition__1down.HGamWeight",                  &JET_Flavor_Composition__1down_HGamWeight);
				float JET_Flavor_Composition__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_subleadjet_pt",          &JET_Flavor_Composition__1down_yyHF_subleadjet_pt);
				float JET_Flavor_Composition__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_subleadjet_phi",         &JET_Flavor_Composition__1down_yyHF_subleadjet_phi);
				float JET_Flavor_Composition__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_subleadjet_m",           &JET_Flavor_Composition__1down_yyHF_subleadjet_m);
				float JET_Flavor_Composition__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_subleadjet_eta",         &JET_Flavor_Composition__1down_yyHF_subleadjet_eta);
				float JET_Flavor_Composition__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_leadjet_pt",             &JET_Flavor_Composition__1down_yyHF_leadjet_pt);
				float JET_Flavor_Composition__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_leadjet_phi",            &JET_Flavor_Composition__1down_yyHF_leadjet_phi);
				float JET_Flavor_Composition__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_leadjet_m",              &JET_Flavor_Composition__1down_yyHF_leadjet_m);
				float JET_Flavor_Composition__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_Flavor_Composition__1down.yyHF_leadjet_eta",            &JET_Flavor_Composition__1down_yyHF_leadjet_eta);
				int JET_Flavor_Composition__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_leadjet_truthlabel",     &JET_Flavor_Composition__1up_yyHF_leadjet_truthlabel);
				int JET_Flavor_Composition__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_subleadjet_truthlabel",  &JET_Flavor_Composition__1up_yyHF_subleadjet_truthlabel);
				int JET_Flavor_Composition__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_leadjet_btagbin",        &JET_Flavor_Composition__1up_yyHF_leadjet_btagbin);
				int JET_Flavor_Composition__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_subleadjet_btagbin",     &JET_Flavor_Composition__1up_yyHF_subleadjet_btagbin);
				int JET_Flavor_Composition__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_Njet_central",           &JET_Flavor_Composition__1up_yyHF_Njet_central);
				int JET_Flavor_Composition__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_cutFlow",                &JET_Flavor_Composition__1up_yyHF_cutFlow);
				int JET_Flavor_Composition__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_nelectron",              &JET_Flavor_Composition__1up_yyHF_nelectron);
				int JET_Flavor_Composition__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_nmuon",                  &JET_Flavor_Composition__1up_yyHF_nmuon);
				bool JET_Flavor_Composition__1up_isPassed;                  myTree->SetBranchAddress("JET_Flavor_Composition__1up.isPassed",                    &JET_Flavor_Composition__1up_isPassed);
				float JET_Flavor_Composition__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHFjj_weight",               &JET_Flavor_Composition__1up_yyHFjj_weight);
				float JET_Flavor_Composition__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHFj_weight",                &JET_Flavor_Composition__1up_yyHFj_weight);
				float JET_Flavor_Composition__1up_yyHF_met;                 myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_met",                    &JET_Flavor_Composition__1up_yyHF_met);
				float JET_Flavor_Composition__1up_m_yy;                     myTree->SetBranchAddress("JET_Flavor_Composition__1up.m_yy",                        &JET_Flavor_Composition__1up_m_yy);
				float JET_Flavor_Composition__1up_m_yyjj;                   myTree->SetBranchAddress("JET_Flavor_Composition__1up.m_yyjj",                      &JET_Flavor_Composition__1up_m_yyjj);
				float JET_Flavor_Composition__1up_pT_yy;                    myTree->SetBranchAddress("JET_Flavor_Composition__1up.pT_yy",                       &JET_Flavor_Composition__1up_pT_yy);
				float JET_Flavor_Composition__1up_HGamWeight;               myTree->SetBranchAddress("JET_Flavor_Composition__1up.HGamWeight",                  &JET_Flavor_Composition__1up_HGamWeight);
				float JET_Flavor_Composition__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_subleadjet_pt",          &JET_Flavor_Composition__1up_yyHF_subleadjet_pt);
				float JET_Flavor_Composition__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_subleadjet_phi",         &JET_Flavor_Composition__1up_yyHF_subleadjet_phi);
				float JET_Flavor_Composition__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_subleadjet_m",           &JET_Flavor_Composition__1up_yyHF_subleadjet_m);
				float JET_Flavor_Composition__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_subleadjet_eta",         &JET_Flavor_Composition__1up_yyHF_subleadjet_eta);
				float JET_Flavor_Composition__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_leadjet_pt",             &JET_Flavor_Composition__1up_yyHF_leadjet_pt);
				float JET_Flavor_Composition__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_leadjet_phi",            &JET_Flavor_Composition__1up_yyHF_leadjet_phi);
				float JET_Flavor_Composition__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_leadjet_m",              &JET_Flavor_Composition__1up_yyHF_leadjet_m);
				float JET_Flavor_Composition__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_Flavor_Composition__1up.yyHF_leadjet_eta",            &JET_Flavor_Composition__1up_yyHF_leadjet_eta);
				int JET_Flavor_Response__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_leadjet_truthlabel",     &JET_Flavor_Response__1down_yyHF_leadjet_truthlabel);
				int JET_Flavor_Response__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_subleadjet_truthlabel",  &JET_Flavor_Response__1down_yyHF_subleadjet_truthlabel);
				int JET_Flavor_Response__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_leadjet_btagbin",        &JET_Flavor_Response__1down_yyHF_leadjet_btagbin);
				int JET_Flavor_Response__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_subleadjet_btagbin",     &JET_Flavor_Response__1down_yyHF_subleadjet_btagbin);
				int JET_Flavor_Response__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_Njet_central",           &JET_Flavor_Response__1down_yyHF_Njet_central);
				int JET_Flavor_Response__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_cutFlow",                &JET_Flavor_Response__1down_yyHF_cutFlow);
				int JET_Flavor_Response__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_nelectron",              &JET_Flavor_Response__1down_yyHF_nelectron);
				int JET_Flavor_Response__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_nmuon",                  &JET_Flavor_Response__1down_yyHF_nmuon);
				bool JET_Flavor_Response__1down_isPassed;                  myTree->SetBranchAddress("JET_Flavor_Response__1down.isPassed",                    &JET_Flavor_Response__1down_isPassed);
				float JET_Flavor_Response__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHFjj_weight",               &JET_Flavor_Response__1down_yyHFjj_weight);
				float JET_Flavor_Response__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHFj_weight",                &JET_Flavor_Response__1down_yyHFj_weight);
				float JET_Flavor_Response__1down_yyHF_met;                 myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_met",                    &JET_Flavor_Response__1down_yyHF_met);
				float JET_Flavor_Response__1down_m_yy;                     myTree->SetBranchAddress("JET_Flavor_Response__1down.m_yy",                        &JET_Flavor_Response__1down_m_yy);
				float JET_Flavor_Response__1down_m_yyjj;                   myTree->SetBranchAddress("JET_Flavor_Response__1down.m_yyjj",                      &JET_Flavor_Response__1down_m_yyjj);
				float JET_Flavor_Response__1down_pT_yy;                    myTree->SetBranchAddress("JET_Flavor_Response__1down.pT_yy",                       &JET_Flavor_Response__1down_pT_yy);
				float JET_Flavor_Response__1down_HGamWeight;               myTree->SetBranchAddress("JET_Flavor_Response__1down.HGamWeight",                  &JET_Flavor_Response__1down_HGamWeight);
				float JET_Flavor_Response__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_subleadjet_pt",          &JET_Flavor_Response__1down_yyHF_subleadjet_pt);
				float JET_Flavor_Response__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_subleadjet_phi",         &JET_Flavor_Response__1down_yyHF_subleadjet_phi);
				float JET_Flavor_Response__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_subleadjet_m",           &JET_Flavor_Response__1down_yyHF_subleadjet_m);
				float JET_Flavor_Response__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_subleadjet_eta",         &JET_Flavor_Response__1down_yyHF_subleadjet_eta);
				float JET_Flavor_Response__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_leadjet_pt",             &JET_Flavor_Response__1down_yyHF_leadjet_pt);
				float JET_Flavor_Response__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_leadjet_phi",            &JET_Flavor_Response__1down_yyHF_leadjet_phi);
				float JET_Flavor_Response__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_leadjet_m",              &JET_Flavor_Response__1down_yyHF_leadjet_m);
				float JET_Flavor_Response__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_Flavor_Response__1down.yyHF_leadjet_eta",            &JET_Flavor_Response__1down_yyHF_leadjet_eta);
				int JET_Flavor_Response__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_leadjet_truthlabel",     &JET_Flavor_Response__1up_yyHF_leadjet_truthlabel);
				int JET_Flavor_Response__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_subleadjet_truthlabel",  &JET_Flavor_Response__1up_yyHF_subleadjet_truthlabel);
				int JET_Flavor_Response__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_leadjet_btagbin",        &JET_Flavor_Response__1up_yyHF_leadjet_btagbin);
				int JET_Flavor_Response__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_subleadjet_btagbin",     &JET_Flavor_Response__1up_yyHF_subleadjet_btagbin);
				int JET_Flavor_Response__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_Njet_central",           &JET_Flavor_Response__1up_yyHF_Njet_central);
				int JET_Flavor_Response__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_cutFlow",                &JET_Flavor_Response__1up_yyHF_cutFlow);
				int JET_Flavor_Response__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_nelectron",              &JET_Flavor_Response__1up_yyHF_nelectron);
				int JET_Flavor_Response__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_nmuon",                  &JET_Flavor_Response__1up_yyHF_nmuon);
				bool JET_Flavor_Response__1up_isPassed;                  myTree->SetBranchAddress("JET_Flavor_Response__1up.isPassed",                    &JET_Flavor_Response__1up_isPassed);
				float JET_Flavor_Response__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHFjj_weight",               &JET_Flavor_Response__1up_yyHFjj_weight);
				float JET_Flavor_Response__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHFj_weight",                &JET_Flavor_Response__1up_yyHFj_weight);
				float JET_Flavor_Response__1up_yyHF_met;                 myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_met",                    &JET_Flavor_Response__1up_yyHF_met);
				float JET_Flavor_Response__1up_m_yy;                     myTree->SetBranchAddress("JET_Flavor_Response__1up.m_yy",                        &JET_Flavor_Response__1up_m_yy);
				float JET_Flavor_Response__1up_m_yyjj;                   myTree->SetBranchAddress("JET_Flavor_Response__1up.m_yyjj",                      &JET_Flavor_Response__1up_m_yyjj);
				float JET_Flavor_Response__1up_pT_yy;                    myTree->SetBranchAddress("JET_Flavor_Response__1up.pT_yy",                       &JET_Flavor_Response__1up_pT_yy);
				float JET_Flavor_Response__1up_HGamWeight;               myTree->SetBranchAddress("JET_Flavor_Response__1up.HGamWeight",                  &JET_Flavor_Response__1up_HGamWeight);
				float JET_Flavor_Response__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_subleadjet_pt",          &JET_Flavor_Response__1up_yyHF_subleadjet_pt);
				float JET_Flavor_Response__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_subleadjet_phi",         &JET_Flavor_Response__1up_yyHF_subleadjet_phi);
				float JET_Flavor_Response__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_subleadjet_m",           &JET_Flavor_Response__1up_yyHF_subleadjet_m);
				float JET_Flavor_Response__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_subleadjet_eta",         &JET_Flavor_Response__1up_yyHF_subleadjet_eta);
				float JET_Flavor_Response__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_leadjet_pt",             &JET_Flavor_Response__1up_yyHF_leadjet_pt);
				float JET_Flavor_Response__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_leadjet_phi",            &JET_Flavor_Response__1up_yyHF_leadjet_phi);
				float JET_Flavor_Response__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_leadjet_m",              &JET_Flavor_Response__1up_yyHF_leadjet_m);
				float JET_Flavor_Response__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_Flavor_Response__1up.yyHF_leadjet_eta",            &JET_Flavor_Response__1up_yyHF_leadjet_eta);
				int JET_JvtEfficiency__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_leadjet_truthlabel",     &JET_JvtEfficiency__1down_yyHF_leadjet_truthlabel);
				int JET_JvtEfficiency__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_subleadjet_truthlabel",  &JET_JvtEfficiency__1down_yyHF_subleadjet_truthlabel);
				int JET_JvtEfficiency__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_leadjet_btagbin",        &JET_JvtEfficiency__1down_yyHF_leadjet_btagbin);
				int JET_JvtEfficiency__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_subleadjet_btagbin",     &JET_JvtEfficiency__1down_yyHF_subleadjet_btagbin);
				int JET_JvtEfficiency__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_Njet_central",           &JET_JvtEfficiency__1down_yyHF_Njet_central);
				int JET_JvtEfficiency__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_cutFlow",                &JET_JvtEfficiency__1down_yyHF_cutFlow);
				int JET_JvtEfficiency__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_nelectron",              &JET_JvtEfficiency__1down_yyHF_nelectron);
				int JET_JvtEfficiency__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_nmuon",                  &JET_JvtEfficiency__1down_yyHF_nmuon);
				bool JET_JvtEfficiency__1down_isPassed;                  myTree->SetBranchAddress("JET_JvtEfficiency__1down.isPassed",                    &JET_JvtEfficiency__1down_isPassed);
				float JET_JvtEfficiency__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHFjj_weight",               &JET_JvtEfficiency__1down_yyHFjj_weight);
				float JET_JvtEfficiency__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHFj_weight",                &JET_JvtEfficiency__1down_yyHFj_weight);
				float JET_JvtEfficiency__1down_yyHF_met;                 myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_met",                    &JET_JvtEfficiency__1down_yyHF_met);
				float JET_JvtEfficiency__1down_m_yy;                     myTree->SetBranchAddress("JET_JvtEfficiency__1down.m_yy",                        &JET_JvtEfficiency__1down_m_yy);
				float JET_JvtEfficiency__1down_m_yyjj;                   myTree->SetBranchAddress("JET_JvtEfficiency__1down.m_yyjj",                      &JET_JvtEfficiency__1down_m_yyjj);
				float JET_JvtEfficiency__1down_pT_yy;                    myTree->SetBranchAddress("JET_JvtEfficiency__1down.pT_yy",                       &JET_JvtEfficiency__1down_pT_yy);
				float JET_JvtEfficiency__1down_HGamWeight;               myTree->SetBranchAddress("JET_JvtEfficiency__1down.HGamWeight",                  &JET_JvtEfficiency__1down_HGamWeight);
				float JET_JvtEfficiency__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_subleadjet_pt",          &JET_JvtEfficiency__1down_yyHF_subleadjet_pt);
				float JET_JvtEfficiency__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_subleadjet_phi",         &JET_JvtEfficiency__1down_yyHF_subleadjet_phi);
				float JET_JvtEfficiency__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_subleadjet_m",           &JET_JvtEfficiency__1down_yyHF_subleadjet_m);
				float JET_JvtEfficiency__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_subleadjet_eta",         &JET_JvtEfficiency__1down_yyHF_subleadjet_eta);
				float JET_JvtEfficiency__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_leadjet_pt",             &JET_JvtEfficiency__1down_yyHF_leadjet_pt);
				float JET_JvtEfficiency__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_leadjet_phi",            &JET_JvtEfficiency__1down_yyHF_leadjet_phi);
				float JET_JvtEfficiency__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_leadjet_m",              &JET_JvtEfficiency__1down_yyHF_leadjet_m);
				float JET_JvtEfficiency__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_JvtEfficiency__1down.yyHF_leadjet_eta",            &JET_JvtEfficiency__1down_yyHF_leadjet_eta);
				int JET_JvtEfficiency__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_leadjet_truthlabel",     &JET_JvtEfficiency__1up_yyHF_leadjet_truthlabel);
				int JET_JvtEfficiency__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_subleadjet_truthlabel",  &JET_JvtEfficiency__1up_yyHF_subleadjet_truthlabel);
				int JET_JvtEfficiency__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_leadjet_btagbin",        &JET_JvtEfficiency__1up_yyHF_leadjet_btagbin);
				int JET_JvtEfficiency__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_subleadjet_btagbin",     &JET_JvtEfficiency__1up_yyHF_subleadjet_btagbin);
				int JET_JvtEfficiency__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_Njet_central",           &JET_JvtEfficiency__1up_yyHF_Njet_central);
				int JET_JvtEfficiency__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_cutFlow",                &JET_JvtEfficiency__1up_yyHF_cutFlow);
				int JET_JvtEfficiency__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_nelectron",              &JET_JvtEfficiency__1up_yyHF_nelectron);
				int JET_JvtEfficiency__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_nmuon",                  &JET_JvtEfficiency__1up_yyHF_nmuon);
				bool JET_JvtEfficiency__1up_isPassed;                  myTree->SetBranchAddress("JET_JvtEfficiency__1up.isPassed",                    &JET_JvtEfficiency__1up_isPassed);
				float JET_JvtEfficiency__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHFjj_weight",               &JET_JvtEfficiency__1up_yyHFjj_weight);
				float JET_JvtEfficiency__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHFj_weight",                &JET_JvtEfficiency__1up_yyHFj_weight);
				float JET_JvtEfficiency__1up_yyHF_met;                 myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_met",                    &JET_JvtEfficiency__1up_yyHF_met);
				float JET_JvtEfficiency__1up_m_yy;                     myTree->SetBranchAddress("JET_JvtEfficiency__1up.m_yy",                        &JET_JvtEfficiency__1up_m_yy);
				float JET_JvtEfficiency__1up_m_yyjj;                   myTree->SetBranchAddress("JET_JvtEfficiency__1up.m_yyjj",                      &JET_JvtEfficiency__1up_m_yyjj);
				float JET_JvtEfficiency__1up_pT_yy;                    myTree->SetBranchAddress("JET_JvtEfficiency__1up.pT_yy",                       &JET_JvtEfficiency__1up_pT_yy);
				float JET_JvtEfficiency__1up_HGamWeight;               myTree->SetBranchAddress("JET_JvtEfficiency__1up.HGamWeight",                  &JET_JvtEfficiency__1up_HGamWeight);
				float JET_JvtEfficiency__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_subleadjet_pt",          &JET_JvtEfficiency__1up_yyHF_subleadjet_pt);
				float JET_JvtEfficiency__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_subleadjet_phi",         &JET_JvtEfficiency__1up_yyHF_subleadjet_phi);
				float JET_JvtEfficiency__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_subleadjet_m",           &JET_JvtEfficiency__1up_yyHF_subleadjet_m);
				float JET_JvtEfficiency__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_subleadjet_eta",         &JET_JvtEfficiency__1up_yyHF_subleadjet_eta);
				float JET_JvtEfficiency__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_leadjet_pt",             &JET_JvtEfficiency__1up_yyHF_leadjet_pt);
				float JET_JvtEfficiency__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_leadjet_phi",            &JET_JvtEfficiency__1up_yyHF_leadjet_phi);
				float JET_JvtEfficiency__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_leadjet_m",              &JET_JvtEfficiency__1up_yyHF_leadjet_m);
				float JET_JvtEfficiency__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_JvtEfficiency__1up.yyHF_leadjet_eta",            &JET_JvtEfficiency__1up_yyHF_leadjet_eta);
				int JET_Pileup_OffsetMu__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_leadjet_truthlabel",     &JET_Pileup_OffsetMu__1down_yyHF_leadjet_truthlabel);
				int JET_Pileup_OffsetMu__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_subleadjet_truthlabel",  &JET_Pileup_OffsetMu__1down_yyHF_subleadjet_truthlabel);
				int JET_Pileup_OffsetMu__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_leadjet_btagbin",        &JET_Pileup_OffsetMu__1down_yyHF_leadjet_btagbin);
				int JET_Pileup_OffsetMu__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_subleadjet_btagbin",     &JET_Pileup_OffsetMu__1down_yyHF_subleadjet_btagbin);
				int JET_Pileup_OffsetMu__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_Njet_central",           &JET_Pileup_OffsetMu__1down_yyHF_Njet_central);
				int JET_Pileup_OffsetMu__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_cutFlow",                &JET_Pileup_OffsetMu__1down_yyHF_cutFlow);
				int JET_Pileup_OffsetMu__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_nelectron",              &JET_Pileup_OffsetMu__1down_yyHF_nelectron);
				int JET_Pileup_OffsetMu__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_nmuon",                  &JET_Pileup_OffsetMu__1down_yyHF_nmuon);
				bool JET_Pileup_OffsetMu__1down_isPassed;                  myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.isPassed",                    &JET_Pileup_OffsetMu__1down_isPassed);
				float JET_Pileup_OffsetMu__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHFjj_weight",               &JET_Pileup_OffsetMu__1down_yyHFjj_weight);
				float JET_Pileup_OffsetMu__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHFj_weight",                &JET_Pileup_OffsetMu__1down_yyHFj_weight);
				float JET_Pileup_OffsetMu__1down_yyHF_met;                 myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_met",                    &JET_Pileup_OffsetMu__1down_yyHF_met);
				float JET_Pileup_OffsetMu__1down_m_yy;                     myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.m_yy",                        &JET_Pileup_OffsetMu__1down_m_yy);
				float JET_Pileup_OffsetMu__1down_m_yyjj;                   myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.m_yyjj",                      &JET_Pileup_OffsetMu__1down_m_yyjj);
				float JET_Pileup_OffsetMu__1down_pT_yy;                    myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.pT_yy",                       &JET_Pileup_OffsetMu__1down_pT_yy);
				float JET_Pileup_OffsetMu__1down_HGamWeight;               myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.HGamWeight",                  &JET_Pileup_OffsetMu__1down_HGamWeight);
				float JET_Pileup_OffsetMu__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_subleadjet_pt",          &JET_Pileup_OffsetMu__1down_yyHF_subleadjet_pt);
				float JET_Pileup_OffsetMu__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_subleadjet_phi",         &JET_Pileup_OffsetMu__1down_yyHF_subleadjet_phi);
				float JET_Pileup_OffsetMu__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_subleadjet_m",           &JET_Pileup_OffsetMu__1down_yyHF_subleadjet_m);
				float JET_Pileup_OffsetMu__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_subleadjet_eta",         &JET_Pileup_OffsetMu__1down_yyHF_subleadjet_eta);
				float JET_Pileup_OffsetMu__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_leadjet_pt",             &JET_Pileup_OffsetMu__1down_yyHF_leadjet_pt);
				float JET_Pileup_OffsetMu__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_leadjet_phi",            &JET_Pileup_OffsetMu__1down_yyHF_leadjet_phi);
				float JET_Pileup_OffsetMu__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_leadjet_m",              &JET_Pileup_OffsetMu__1down_yyHF_leadjet_m);
				float JET_Pileup_OffsetMu__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_Pileup_OffsetMu__1down.yyHF_leadjet_eta",            &JET_Pileup_OffsetMu__1down_yyHF_leadjet_eta);
				int JET_Pileup_OffsetMu__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_leadjet_truthlabel",     &JET_Pileup_OffsetMu__1up_yyHF_leadjet_truthlabel);
				int JET_Pileup_OffsetMu__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_subleadjet_truthlabel",  &JET_Pileup_OffsetMu__1up_yyHF_subleadjet_truthlabel);
				int JET_Pileup_OffsetMu__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_leadjet_btagbin",        &JET_Pileup_OffsetMu__1up_yyHF_leadjet_btagbin);
				int JET_Pileup_OffsetMu__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_subleadjet_btagbin",     &JET_Pileup_OffsetMu__1up_yyHF_subleadjet_btagbin);
				int JET_Pileup_OffsetMu__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_Njet_central",           &JET_Pileup_OffsetMu__1up_yyHF_Njet_central);
				int JET_Pileup_OffsetMu__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_cutFlow",                &JET_Pileup_OffsetMu__1up_yyHF_cutFlow);
				int JET_Pileup_OffsetMu__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_nelectron",              &JET_Pileup_OffsetMu__1up_yyHF_nelectron);
				int JET_Pileup_OffsetMu__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_nmuon",                  &JET_Pileup_OffsetMu__1up_yyHF_nmuon);
				bool JET_Pileup_OffsetMu__1up_isPassed;                  myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.isPassed",                    &JET_Pileup_OffsetMu__1up_isPassed);
				float JET_Pileup_OffsetMu__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHFjj_weight",               &JET_Pileup_OffsetMu__1up_yyHFjj_weight);
				float JET_Pileup_OffsetMu__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHFj_weight",                &JET_Pileup_OffsetMu__1up_yyHFj_weight);
				float JET_Pileup_OffsetMu__1up_yyHF_met;                 myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_met",                    &JET_Pileup_OffsetMu__1up_yyHF_met);
				float JET_Pileup_OffsetMu__1up_m_yy;                     myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.m_yy",                        &JET_Pileup_OffsetMu__1up_m_yy);
				float JET_Pileup_OffsetMu__1up_m_yyjj;                   myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.m_yyjj",                      &JET_Pileup_OffsetMu__1up_m_yyjj);
				float JET_Pileup_OffsetMu__1up_pT_yy;                    myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.pT_yy",                       &JET_Pileup_OffsetMu__1up_pT_yy);
				float JET_Pileup_OffsetMu__1up_HGamWeight;               myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.HGamWeight",                  &JET_Pileup_OffsetMu__1up_HGamWeight);
				float JET_Pileup_OffsetMu__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_subleadjet_pt",          &JET_Pileup_OffsetMu__1up_yyHF_subleadjet_pt);
				float JET_Pileup_OffsetMu__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_subleadjet_phi",         &JET_Pileup_OffsetMu__1up_yyHF_subleadjet_phi);
				float JET_Pileup_OffsetMu__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_subleadjet_m",           &JET_Pileup_OffsetMu__1up_yyHF_subleadjet_m);
				float JET_Pileup_OffsetMu__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_subleadjet_eta",         &JET_Pileup_OffsetMu__1up_yyHF_subleadjet_eta);
				float JET_Pileup_OffsetMu__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_leadjet_pt",             &JET_Pileup_OffsetMu__1up_yyHF_leadjet_pt);
				float JET_Pileup_OffsetMu__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_leadjet_phi",            &JET_Pileup_OffsetMu__1up_yyHF_leadjet_phi);
				float JET_Pileup_OffsetMu__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_leadjet_m",              &JET_Pileup_OffsetMu__1up_yyHF_leadjet_m);
				float JET_Pileup_OffsetMu__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_Pileup_OffsetMu__1up.yyHF_leadjet_eta",            &JET_Pileup_OffsetMu__1up_yyHF_leadjet_eta);
				int JET_Pileup_OffsetNPV__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_leadjet_truthlabel",     &JET_Pileup_OffsetNPV__1down_yyHF_leadjet_truthlabel);
				int JET_Pileup_OffsetNPV__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_subleadjet_truthlabel",  &JET_Pileup_OffsetNPV__1down_yyHF_subleadjet_truthlabel);
				int JET_Pileup_OffsetNPV__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_leadjet_btagbin",        &JET_Pileup_OffsetNPV__1down_yyHF_leadjet_btagbin);
				int JET_Pileup_OffsetNPV__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_subleadjet_btagbin",     &JET_Pileup_OffsetNPV__1down_yyHF_subleadjet_btagbin);
				int JET_Pileup_OffsetNPV__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_Njet_central",           &JET_Pileup_OffsetNPV__1down_yyHF_Njet_central);
				int JET_Pileup_OffsetNPV__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_cutFlow",                &JET_Pileup_OffsetNPV__1down_yyHF_cutFlow);
				int JET_Pileup_OffsetNPV__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_nelectron",              &JET_Pileup_OffsetNPV__1down_yyHF_nelectron);
				int JET_Pileup_OffsetNPV__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_nmuon",                  &JET_Pileup_OffsetNPV__1down_yyHF_nmuon);
				bool JET_Pileup_OffsetNPV__1down_isPassed;                  myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.isPassed",                    &JET_Pileup_OffsetNPV__1down_isPassed);
				float JET_Pileup_OffsetNPV__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHFjj_weight",               &JET_Pileup_OffsetNPV__1down_yyHFjj_weight);
				float JET_Pileup_OffsetNPV__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHFj_weight",                &JET_Pileup_OffsetNPV__1down_yyHFj_weight);
				float JET_Pileup_OffsetNPV__1down_yyHF_met;                 myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_met",                    &JET_Pileup_OffsetNPV__1down_yyHF_met);
				float JET_Pileup_OffsetNPV__1down_m_yy;                     myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.m_yy",                        &JET_Pileup_OffsetNPV__1down_m_yy);
				float JET_Pileup_OffsetNPV__1down_m_yyjj;                   myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.m_yyjj",                      &JET_Pileup_OffsetNPV__1down_m_yyjj);
				float JET_Pileup_OffsetNPV__1down_pT_yy;                    myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.pT_yy",                       &JET_Pileup_OffsetNPV__1down_pT_yy);
				float JET_Pileup_OffsetNPV__1down_HGamWeight;               myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.HGamWeight",                  &JET_Pileup_OffsetNPV__1down_HGamWeight);
				float JET_Pileup_OffsetNPV__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_subleadjet_pt",          &JET_Pileup_OffsetNPV__1down_yyHF_subleadjet_pt);
				float JET_Pileup_OffsetNPV__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_subleadjet_phi",         &JET_Pileup_OffsetNPV__1down_yyHF_subleadjet_phi);
				float JET_Pileup_OffsetNPV__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_subleadjet_m",           &JET_Pileup_OffsetNPV__1down_yyHF_subleadjet_m);
				float JET_Pileup_OffsetNPV__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_subleadjet_eta",         &JET_Pileup_OffsetNPV__1down_yyHF_subleadjet_eta);
				float JET_Pileup_OffsetNPV__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_leadjet_pt",             &JET_Pileup_OffsetNPV__1down_yyHF_leadjet_pt);
				float JET_Pileup_OffsetNPV__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_leadjet_phi",            &JET_Pileup_OffsetNPV__1down_yyHF_leadjet_phi);
				float JET_Pileup_OffsetNPV__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_leadjet_m",              &JET_Pileup_OffsetNPV__1down_yyHF_leadjet_m);
				float JET_Pileup_OffsetNPV__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1down.yyHF_leadjet_eta",            &JET_Pileup_OffsetNPV__1down_yyHF_leadjet_eta);
				int JET_Pileup_OffsetNPV__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_leadjet_truthlabel",     &JET_Pileup_OffsetNPV__1up_yyHF_leadjet_truthlabel);
				int JET_Pileup_OffsetNPV__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_subleadjet_truthlabel",  &JET_Pileup_OffsetNPV__1up_yyHF_subleadjet_truthlabel);
				int JET_Pileup_OffsetNPV__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_leadjet_btagbin",        &JET_Pileup_OffsetNPV__1up_yyHF_leadjet_btagbin);
				int JET_Pileup_OffsetNPV__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_subleadjet_btagbin",     &JET_Pileup_OffsetNPV__1up_yyHF_subleadjet_btagbin);
				int JET_Pileup_OffsetNPV__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_Njet_central",           &JET_Pileup_OffsetNPV__1up_yyHF_Njet_central);
				int JET_Pileup_OffsetNPV__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_cutFlow",                &JET_Pileup_OffsetNPV__1up_yyHF_cutFlow);
				int JET_Pileup_OffsetNPV__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_nelectron",              &JET_Pileup_OffsetNPV__1up_yyHF_nelectron);
				int JET_Pileup_OffsetNPV__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_nmuon",                  &JET_Pileup_OffsetNPV__1up_yyHF_nmuon);
				bool JET_Pileup_OffsetNPV__1up_isPassed;                  myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.isPassed",                    &JET_Pileup_OffsetNPV__1up_isPassed);
				float JET_Pileup_OffsetNPV__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHFjj_weight",               &JET_Pileup_OffsetNPV__1up_yyHFjj_weight);
				float JET_Pileup_OffsetNPV__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHFj_weight",                &JET_Pileup_OffsetNPV__1up_yyHFj_weight);
				float JET_Pileup_OffsetNPV__1up_yyHF_met;                 myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_met",                    &JET_Pileup_OffsetNPV__1up_yyHF_met);
				float JET_Pileup_OffsetNPV__1up_m_yy;                     myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.m_yy",                        &JET_Pileup_OffsetNPV__1up_m_yy);
				float JET_Pileup_OffsetNPV__1up_m_yyjj;                   myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.m_yyjj",                      &JET_Pileup_OffsetNPV__1up_m_yyjj);
				float JET_Pileup_OffsetNPV__1up_pT_yy;                    myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.pT_yy",                       &JET_Pileup_OffsetNPV__1up_pT_yy);
				float JET_Pileup_OffsetNPV__1up_HGamWeight;               myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.HGamWeight",                  &JET_Pileup_OffsetNPV__1up_HGamWeight);
				float JET_Pileup_OffsetNPV__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_subleadjet_pt",          &JET_Pileup_OffsetNPV__1up_yyHF_subleadjet_pt);
				float JET_Pileup_OffsetNPV__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_subleadjet_phi",         &JET_Pileup_OffsetNPV__1up_yyHF_subleadjet_phi);
				float JET_Pileup_OffsetNPV__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_subleadjet_m",           &JET_Pileup_OffsetNPV__1up_yyHF_subleadjet_m);
				float JET_Pileup_OffsetNPV__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_subleadjet_eta",         &JET_Pileup_OffsetNPV__1up_yyHF_subleadjet_eta);
				float JET_Pileup_OffsetNPV__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_leadjet_pt",             &JET_Pileup_OffsetNPV__1up_yyHF_leadjet_pt);
				float JET_Pileup_OffsetNPV__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_leadjet_phi",            &JET_Pileup_OffsetNPV__1up_yyHF_leadjet_phi);
				float JET_Pileup_OffsetNPV__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_leadjet_m",              &JET_Pileup_OffsetNPV__1up_yyHF_leadjet_m);
				float JET_Pileup_OffsetNPV__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_Pileup_OffsetNPV__1up.yyHF_leadjet_eta",            &JET_Pileup_OffsetNPV__1up_yyHF_leadjet_eta);
				int JET_Pileup_PtTerm__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_leadjet_truthlabel",     &JET_Pileup_PtTerm__1down_yyHF_leadjet_truthlabel);
				int JET_Pileup_PtTerm__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_subleadjet_truthlabel",  &JET_Pileup_PtTerm__1down_yyHF_subleadjet_truthlabel);
				int JET_Pileup_PtTerm__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_leadjet_btagbin",        &JET_Pileup_PtTerm__1down_yyHF_leadjet_btagbin);
				int JET_Pileup_PtTerm__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_subleadjet_btagbin",     &JET_Pileup_PtTerm__1down_yyHF_subleadjet_btagbin);
				int JET_Pileup_PtTerm__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_Njet_central",           &JET_Pileup_PtTerm__1down_yyHF_Njet_central);
				int JET_Pileup_PtTerm__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_cutFlow",                &JET_Pileup_PtTerm__1down_yyHF_cutFlow);
				int JET_Pileup_PtTerm__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_nelectron",              &JET_Pileup_PtTerm__1down_yyHF_nelectron);
				int JET_Pileup_PtTerm__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_nmuon",                  &JET_Pileup_PtTerm__1down_yyHF_nmuon);
				bool JET_Pileup_PtTerm__1down_isPassed;                  myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.isPassed",                    &JET_Pileup_PtTerm__1down_isPassed);
				float JET_Pileup_PtTerm__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHFjj_weight",               &JET_Pileup_PtTerm__1down_yyHFjj_weight);
				float JET_Pileup_PtTerm__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHFj_weight",                &JET_Pileup_PtTerm__1down_yyHFj_weight);
				float JET_Pileup_PtTerm__1down_yyHF_met;                 myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_met",                    &JET_Pileup_PtTerm__1down_yyHF_met);
				float JET_Pileup_PtTerm__1down_m_yy;                     myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.m_yy",                        &JET_Pileup_PtTerm__1down_m_yy);
				float JET_Pileup_PtTerm__1down_m_yyjj;                   myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.m_yyjj",                      &JET_Pileup_PtTerm__1down_m_yyjj);
				float JET_Pileup_PtTerm__1down_pT_yy;                    myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.pT_yy",                       &JET_Pileup_PtTerm__1down_pT_yy);
				float JET_Pileup_PtTerm__1down_HGamWeight;               myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.HGamWeight",                  &JET_Pileup_PtTerm__1down_HGamWeight);
				float JET_Pileup_PtTerm__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_subleadjet_pt",          &JET_Pileup_PtTerm__1down_yyHF_subleadjet_pt);
				float JET_Pileup_PtTerm__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_subleadjet_phi",         &JET_Pileup_PtTerm__1down_yyHF_subleadjet_phi);
				float JET_Pileup_PtTerm__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_subleadjet_m",           &JET_Pileup_PtTerm__1down_yyHF_subleadjet_m);
				float JET_Pileup_PtTerm__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_subleadjet_eta",         &JET_Pileup_PtTerm__1down_yyHF_subleadjet_eta);
				float JET_Pileup_PtTerm__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_leadjet_pt",             &JET_Pileup_PtTerm__1down_yyHF_leadjet_pt);
				float JET_Pileup_PtTerm__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_leadjet_phi",            &JET_Pileup_PtTerm__1down_yyHF_leadjet_phi);
				float JET_Pileup_PtTerm__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_leadjet_m",              &JET_Pileup_PtTerm__1down_yyHF_leadjet_m);
				float JET_Pileup_PtTerm__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_Pileup_PtTerm__1down.yyHF_leadjet_eta",            &JET_Pileup_PtTerm__1down_yyHF_leadjet_eta);
				int JET_Pileup_PtTerm__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_leadjet_truthlabel",     &JET_Pileup_PtTerm__1up_yyHF_leadjet_truthlabel);
				int JET_Pileup_PtTerm__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_subleadjet_truthlabel",  &JET_Pileup_PtTerm__1up_yyHF_subleadjet_truthlabel);
				int JET_Pileup_PtTerm__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_leadjet_btagbin",        &JET_Pileup_PtTerm__1up_yyHF_leadjet_btagbin);
				int JET_Pileup_PtTerm__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_subleadjet_btagbin",     &JET_Pileup_PtTerm__1up_yyHF_subleadjet_btagbin);
				int JET_Pileup_PtTerm__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_Njet_central",           &JET_Pileup_PtTerm__1up_yyHF_Njet_central);
				int JET_Pileup_PtTerm__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_cutFlow",                &JET_Pileup_PtTerm__1up_yyHF_cutFlow);
				int JET_Pileup_PtTerm__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_nelectron",              &JET_Pileup_PtTerm__1up_yyHF_nelectron);
				int JET_Pileup_PtTerm__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_nmuon",                  &JET_Pileup_PtTerm__1up_yyHF_nmuon);
				bool JET_Pileup_PtTerm__1up_isPassed;                  myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.isPassed",                    &JET_Pileup_PtTerm__1up_isPassed);
				float JET_Pileup_PtTerm__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHFjj_weight",               &JET_Pileup_PtTerm__1up_yyHFjj_weight);
				float JET_Pileup_PtTerm__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHFj_weight",                &JET_Pileup_PtTerm__1up_yyHFj_weight);
				float JET_Pileup_PtTerm__1up_yyHF_met;                 myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_met",                    &JET_Pileup_PtTerm__1up_yyHF_met);
				float JET_Pileup_PtTerm__1up_m_yy;                     myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.m_yy",                        &JET_Pileup_PtTerm__1up_m_yy);
				float JET_Pileup_PtTerm__1up_m_yyjj;                   myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.m_yyjj",                      &JET_Pileup_PtTerm__1up_m_yyjj);
				float JET_Pileup_PtTerm__1up_pT_yy;                    myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.pT_yy",                       &JET_Pileup_PtTerm__1up_pT_yy);
				float JET_Pileup_PtTerm__1up_HGamWeight;               myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.HGamWeight",                  &JET_Pileup_PtTerm__1up_HGamWeight);
				float JET_Pileup_PtTerm__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_subleadjet_pt",          &JET_Pileup_PtTerm__1up_yyHF_subleadjet_pt);
				float JET_Pileup_PtTerm__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_subleadjet_phi",         &JET_Pileup_PtTerm__1up_yyHF_subleadjet_phi);
				float JET_Pileup_PtTerm__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_subleadjet_m",           &JET_Pileup_PtTerm__1up_yyHF_subleadjet_m);
				float JET_Pileup_PtTerm__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_subleadjet_eta",         &JET_Pileup_PtTerm__1up_yyHF_subleadjet_eta);
				float JET_Pileup_PtTerm__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_leadjet_pt",             &JET_Pileup_PtTerm__1up_yyHF_leadjet_pt);
				float JET_Pileup_PtTerm__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_leadjet_phi",            &JET_Pileup_PtTerm__1up_yyHF_leadjet_phi);
				float JET_Pileup_PtTerm__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_leadjet_m",              &JET_Pileup_PtTerm__1up_yyHF_leadjet_m);
				float JET_Pileup_PtTerm__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_Pileup_PtTerm__1up.yyHF_leadjet_eta",            &JET_Pileup_PtTerm__1up_yyHF_leadjet_eta);
				int JET_Pileup_RhoTopology__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_leadjet_truthlabel",     &JET_Pileup_RhoTopology__1down_yyHF_leadjet_truthlabel);
				int JET_Pileup_RhoTopology__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_subleadjet_truthlabel",  &JET_Pileup_RhoTopology__1down_yyHF_subleadjet_truthlabel);
				int JET_Pileup_RhoTopology__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_leadjet_btagbin",        &JET_Pileup_RhoTopology__1down_yyHF_leadjet_btagbin);
				int JET_Pileup_RhoTopology__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_subleadjet_btagbin",     &JET_Pileup_RhoTopology__1down_yyHF_subleadjet_btagbin);
				int JET_Pileup_RhoTopology__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_Njet_central",           &JET_Pileup_RhoTopology__1down_yyHF_Njet_central);
				int JET_Pileup_RhoTopology__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_cutFlow",                &JET_Pileup_RhoTopology__1down_yyHF_cutFlow);
				int JET_Pileup_RhoTopology__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_nelectron",              &JET_Pileup_RhoTopology__1down_yyHF_nelectron);
				int JET_Pileup_RhoTopology__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_nmuon",                  &JET_Pileup_RhoTopology__1down_yyHF_nmuon);
				bool JET_Pileup_RhoTopology__1down_isPassed;                  myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.isPassed",                    &JET_Pileup_RhoTopology__1down_isPassed);
				float JET_Pileup_RhoTopology__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHFjj_weight",               &JET_Pileup_RhoTopology__1down_yyHFjj_weight);
				float JET_Pileup_RhoTopology__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHFj_weight",                &JET_Pileup_RhoTopology__1down_yyHFj_weight);
				float JET_Pileup_RhoTopology__1down_yyHF_met;                 myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_met",                    &JET_Pileup_RhoTopology__1down_yyHF_met);
				float JET_Pileup_RhoTopology__1down_m_yy;                     myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.m_yy",                        &JET_Pileup_RhoTopology__1down_m_yy);
				float JET_Pileup_RhoTopology__1down_m_yyjj;                   myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.m_yyjj",                      &JET_Pileup_RhoTopology__1down_m_yyjj);
				float JET_Pileup_RhoTopology__1down_pT_yy;                    myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.pT_yy",                       &JET_Pileup_RhoTopology__1down_pT_yy);
				float JET_Pileup_RhoTopology__1down_HGamWeight;               myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.HGamWeight",                  &JET_Pileup_RhoTopology__1down_HGamWeight);
				float JET_Pileup_RhoTopology__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_subleadjet_pt",          &JET_Pileup_RhoTopology__1down_yyHF_subleadjet_pt);
				float JET_Pileup_RhoTopology__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_subleadjet_phi",         &JET_Pileup_RhoTopology__1down_yyHF_subleadjet_phi);
				float JET_Pileup_RhoTopology__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_subleadjet_m",           &JET_Pileup_RhoTopology__1down_yyHF_subleadjet_m);
				float JET_Pileup_RhoTopology__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_subleadjet_eta",         &JET_Pileup_RhoTopology__1down_yyHF_subleadjet_eta);
				float JET_Pileup_RhoTopology__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_leadjet_pt",             &JET_Pileup_RhoTopology__1down_yyHF_leadjet_pt);
				float JET_Pileup_RhoTopology__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_leadjet_phi",            &JET_Pileup_RhoTopology__1down_yyHF_leadjet_phi);
				float JET_Pileup_RhoTopology__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_leadjet_m",              &JET_Pileup_RhoTopology__1down_yyHF_leadjet_m);
				float JET_Pileup_RhoTopology__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_Pileup_RhoTopology__1down.yyHF_leadjet_eta",            &JET_Pileup_RhoTopology__1down_yyHF_leadjet_eta);
				int JET_Pileup_RhoTopology__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_leadjet_truthlabel",     &JET_Pileup_RhoTopology__1up_yyHF_leadjet_truthlabel);
				int JET_Pileup_RhoTopology__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_subleadjet_truthlabel",  &JET_Pileup_RhoTopology__1up_yyHF_subleadjet_truthlabel);
				int JET_Pileup_RhoTopology__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_leadjet_btagbin",        &JET_Pileup_RhoTopology__1up_yyHF_leadjet_btagbin);
				int JET_Pileup_RhoTopology__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_subleadjet_btagbin",     &JET_Pileup_RhoTopology__1up_yyHF_subleadjet_btagbin);
				int JET_Pileup_RhoTopology__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_Njet_central",           &JET_Pileup_RhoTopology__1up_yyHF_Njet_central);
				int JET_Pileup_RhoTopology__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_cutFlow",                &JET_Pileup_RhoTopology__1up_yyHF_cutFlow);
				int JET_Pileup_RhoTopology__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_nelectron",              &JET_Pileup_RhoTopology__1up_yyHF_nelectron);
				int JET_Pileup_RhoTopology__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_nmuon",                  &JET_Pileup_RhoTopology__1up_yyHF_nmuon);
				bool JET_Pileup_RhoTopology__1up_isPassed;                  myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.isPassed",                    &JET_Pileup_RhoTopology__1up_isPassed);
				float JET_Pileup_RhoTopology__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHFjj_weight",               &JET_Pileup_RhoTopology__1up_yyHFjj_weight);
				float JET_Pileup_RhoTopology__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHFj_weight",                &JET_Pileup_RhoTopology__1up_yyHFj_weight);
				float JET_Pileup_RhoTopology__1up_yyHF_met;                 myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_met",                    &JET_Pileup_RhoTopology__1up_yyHF_met);
				float JET_Pileup_RhoTopology__1up_m_yy;                     myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.m_yy",                        &JET_Pileup_RhoTopology__1up_m_yy);
				float JET_Pileup_RhoTopology__1up_m_yyjj;                   myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.m_yyjj",                      &JET_Pileup_RhoTopology__1up_m_yyjj);
				float JET_Pileup_RhoTopology__1up_pT_yy;                    myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.pT_yy",                       &JET_Pileup_RhoTopology__1up_pT_yy);
				float JET_Pileup_RhoTopology__1up_HGamWeight;               myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.HGamWeight",                  &JET_Pileup_RhoTopology__1up_HGamWeight);
				float JET_Pileup_RhoTopology__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_subleadjet_pt",          &JET_Pileup_RhoTopology__1up_yyHF_subleadjet_pt);
				float JET_Pileup_RhoTopology__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_subleadjet_phi",         &JET_Pileup_RhoTopology__1up_yyHF_subleadjet_phi);
				float JET_Pileup_RhoTopology__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_subleadjet_m",           &JET_Pileup_RhoTopology__1up_yyHF_subleadjet_m);
				float JET_Pileup_RhoTopology__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_subleadjet_eta",         &JET_Pileup_RhoTopology__1up_yyHF_subleadjet_eta);
				float JET_Pileup_RhoTopology__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_leadjet_pt",             &JET_Pileup_RhoTopology__1up_yyHF_leadjet_pt);
				float JET_Pileup_RhoTopology__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_leadjet_phi",            &JET_Pileup_RhoTopology__1up_yyHF_leadjet_phi);
				float JET_Pileup_RhoTopology__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_leadjet_m",              &JET_Pileup_RhoTopology__1up_yyHF_leadjet_m);
				float JET_Pileup_RhoTopology__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_Pileup_RhoTopology__1up.yyHF_leadjet_eta",            &JET_Pileup_RhoTopology__1up_yyHF_leadjet_eta);
				int JET_SingleParticle_HighPt__1down_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_leadjet_truthlabel",     &JET_SingleParticle_HighPt__1down_yyHF_leadjet_truthlabel);
				int JET_SingleParticle_HighPt__1down_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_subleadjet_truthlabel",  &JET_SingleParticle_HighPt__1down_yyHF_subleadjet_truthlabel);
				int JET_SingleParticle_HighPt__1down_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_leadjet_btagbin",        &JET_SingleParticle_HighPt__1down_yyHF_leadjet_btagbin);
				int JET_SingleParticle_HighPt__1down_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_subleadjet_btagbin",     &JET_SingleParticle_HighPt__1down_yyHF_subleadjet_btagbin);
				int JET_SingleParticle_HighPt__1down_yyHF_Njet_central;          myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_Njet_central",           &JET_SingleParticle_HighPt__1down_yyHF_Njet_central);
				int JET_SingleParticle_HighPt__1down_yyHF_cutFlow;               myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_cutFlow",                &JET_SingleParticle_HighPt__1down_yyHF_cutFlow);
				int JET_SingleParticle_HighPt__1down_yyHF_nelectron;             myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_nelectron",              &JET_SingleParticle_HighPt__1down_yyHF_nelectron);
				int JET_SingleParticle_HighPt__1down_yyHF_nmuon;                 myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_nmuon",                  &JET_SingleParticle_HighPt__1down_yyHF_nmuon);
				bool JET_SingleParticle_HighPt__1down_isPassed;                  myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.isPassed",                    &JET_SingleParticle_HighPt__1down_isPassed);
				float JET_SingleParticle_HighPt__1down_yyHFjj_weight;            myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHFjj_weight",               &JET_SingleParticle_HighPt__1down_yyHFjj_weight);
				float JET_SingleParticle_HighPt__1down_yyHFj_weight;             myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHFj_weight",                &JET_SingleParticle_HighPt__1down_yyHFj_weight);
				float JET_SingleParticle_HighPt__1down_yyHF_met;                 myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_met",                    &JET_SingleParticle_HighPt__1down_yyHF_met);
				float JET_SingleParticle_HighPt__1down_m_yy;                     myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.m_yy",                        &JET_SingleParticle_HighPt__1down_m_yy);
				float JET_SingleParticle_HighPt__1down_m_yyjj;                   myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.m_yyjj",                      &JET_SingleParticle_HighPt__1down_m_yyjj);
				float JET_SingleParticle_HighPt__1down_pT_yy;                    myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.pT_yy",                       &JET_SingleParticle_HighPt__1down_pT_yy);
				float JET_SingleParticle_HighPt__1down_HGamWeight;               myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.HGamWeight",                  &JET_SingleParticle_HighPt__1down_HGamWeight);
				float JET_SingleParticle_HighPt__1down_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_subleadjet_pt",          &JET_SingleParticle_HighPt__1down_yyHF_subleadjet_pt);
				float JET_SingleParticle_HighPt__1down_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_subleadjet_phi",         &JET_SingleParticle_HighPt__1down_yyHF_subleadjet_phi);
				float JET_SingleParticle_HighPt__1down_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_subleadjet_m",           &JET_SingleParticle_HighPt__1down_yyHF_subleadjet_m);
				float JET_SingleParticle_HighPt__1down_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_subleadjet_eta",         &JET_SingleParticle_HighPt__1down_yyHF_subleadjet_eta);
				float JET_SingleParticle_HighPt__1down_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_leadjet_pt",             &JET_SingleParticle_HighPt__1down_yyHF_leadjet_pt);
				float JET_SingleParticle_HighPt__1down_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_leadjet_phi",            &JET_SingleParticle_HighPt__1down_yyHF_leadjet_phi);
				float JET_SingleParticle_HighPt__1down_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_leadjet_m",              &JET_SingleParticle_HighPt__1down_yyHF_leadjet_m);
				float JET_SingleParticle_HighPt__1down_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_SingleParticle_HighPt__1down.yyHF_leadjet_eta",            &JET_SingleParticle_HighPt__1down_yyHF_leadjet_eta);
				int JET_SingleParticle_HighPt__1up_yyHF_leadjet_truthlabel;    myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_leadjet_truthlabel",     &JET_SingleParticle_HighPt__1up_yyHF_leadjet_truthlabel);
				int JET_SingleParticle_HighPt__1up_yyHF_subleadjet_truthlabel; myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_subleadjet_truthlabel",  &JET_SingleParticle_HighPt__1up_yyHF_subleadjet_truthlabel);
				int JET_SingleParticle_HighPt__1up_yyHF_leadjet_btagbin;       myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_leadjet_btagbin",        &JET_SingleParticle_HighPt__1up_yyHF_leadjet_btagbin);
				int JET_SingleParticle_HighPt__1up_yyHF_subleadjet_btagbin;    myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_subleadjet_btagbin",     &JET_SingleParticle_HighPt__1up_yyHF_subleadjet_btagbin);
				int JET_SingleParticle_HighPt__1up_yyHF_Njet_central;          myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_Njet_central",           &JET_SingleParticle_HighPt__1up_yyHF_Njet_central);
				int JET_SingleParticle_HighPt__1up_yyHF_cutFlow;               myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_cutFlow",                &JET_SingleParticle_HighPt__1up_yyHF_cutFlow);
				int JET_SingleParticle_HighPt__1up_yyHF_nelectron;             myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_nelectron",              &JET_SingleParticle_HighPt__1up_yyHF_nelectron);
				int JET_SingleParticle_HighPt__1up_yyHF_nmuon;                 myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_nmuon",                  &JET_SingleParticle_HighPt__1up_yyHF_nmuon);
				bool JET_SingleParticle_HighPt__1up_isPassed;                  myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.isPassed",                    &JET_SingleParticle_HighPt__1up_isPassed);
				float JET_SingleParticle_HighPt__1up_yyHFjj_weight;            myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHFjj_weight",               &JET_SingleParticle_HighPt__1up_yyHFjj_weight);
				float JET_SingleParticle_HighPt__1up_yyHFj_weight;             myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHFj_weight",                &JET_SingleParticle_HighPt__1up_yyHFj_weight);
				float JET_SingleParticle_HighPt__1up_yyHF_met;                 myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_met",                    &JET_SingleParticle_HighPt__1up_yyHF_met);
				float JET_SingleParticle_HighPt__1up_m_yy;                     myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.m_yy",                        &JET_SingleParticle_HighPt__1up_m_yy);
				float JET_SingleParticle_HighPt__1up_m_yyjj;                   myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.m_yyjj",                      &JET_SingleParticle_HighPt__1up_m_yyjj);
				float JET_SingleParticle_HighPt__1up_pT_yy;                    myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.pT_yy",                       &JET_SingleParticle_HighPt__1up_pT_yy);
				float JET_SingleParticle_HighPt__1up_HGamWeight;               myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.HGamWeight",                  &JET_SingleParticle_HighPt__1up_HGamWeight);
				float JET_SingleParticle_HighPt__1up_yyHF_subleadjet_pt;       myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_subleadjet_pt",          &JET_SingleParticle_HighPt__1up_yyHF_subleadjet_pt);
				float JET_SingleParticle_HighPt__1up_yyHF_subleadjet_phi;      myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_subleadjet_phi",         &JET_SingleParticle_HighPt__1up_yyHF_subleadjet_phi);
				float JET_SingleParticle_HighPt__1up_yyHF_subleadjet_m;        myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_subleadjet_m",           &JET_SingleParticle_HighPt__1up_yyHF_subleadjet_m);
				float JET_SingleParticle_HighPt__1up_yyHF_subleadjet_eta;      myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_subleadjet_eta",         &JET_SingleParticle_HighPt__1up_yyHF_subleadjet_eta);
				float JET_SingleParticle_HighPt__1up_yyHF_leadjet_pt;          myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_leadjet_pt",             &JET_SingleParticle_HighPt__1up_yyHF_leadjet_pt);
				float JET_SingleParticle_HighPt__1up_yyHF_leadjet_phi;         myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_leadjet_phi",            &JET_SingleParticle_HighPt__1up_yyHF_leadjet_phi);
				float JET_SingleParticle_HighPt__1up_yyHF_leadjet_m;           myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_leadjet_m",              &JET_SingleParticle_HighPt__1up_yyHF_leadjet_m);
				float JET_SingleParticle_HighPt__1up_yyHF_leadjet_eta;         myTree->SetBranchAddress("JET_SingleParticle_HighPt__1up.yyHF_leadjet_eta",            &JET_SingleParticle_HighPt__1up_yyHF_leadjet_eta);


				TH1F *histbb_noMET_JET_BJES_Response__1down = new TH1F("histbb_noMET_JET_BJES_Response__1down", "histbb_noMET_JET_BJES_Response__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_BJES_Response__1down = new TH1F("histbc_noMET_JET_BJES_Response__1down", "histbc_noMET_JET_BJES_Response__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_BJES_Response__1down = new TH1F("histbl_noMET_JET_BJES_Response__1down", "histbl_noMET_JET_BJES_Response__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_BJES_Response__1down = new TH1F("histcc_noMET_JET_BJES_Response__1down", "histcc_noMET_JET_BJES_Response__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_BJES_Response__1down = new TH1F("histcl_noMET_JET_BJES_Response__1down", "histcl_noMET_JET_BJES_Response__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_BJES_Response__1down = new TH1F("histll_noMET_JET_BJES_Response__1down", "histll_noMET_JET_BJES_Response__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_BJES_Response__1down = new TH1F("histb_noMET_JET_BJES_Response__1down", "histb_noMET_JET_BJES_Response__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_BJES_Response__1down = new TH1F("histc_noMET_JET_BJES_Response__1down", "histc_noMET_JET_BJES_Response__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_BJES_Response__1down = new TH1F("histl_noMET_JET_BJES_Response__1down", "histl_noMET_JET_BJES_Response__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_BJES_Response__1up = new TH1F("histbb_noMET_JET_BJES_Response__1up", "histbb_noMET_JET_BJES_Response__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_BJES_Response__1up = new TH1F("histbc_noMET_JET_BJES_Response__1up", "histbc_noMET_JET_BJES_Response__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_BJES_Response__1up = new TH1F("histbl_noMET_JET_BJES_Response__1up", "histbl_noMET_JET_BJES_Response__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_BJES_Response__1up = new TH1F("histcc_noMET_JET_BJES_Response__1up", "histcc_noMET_JET_BJES_Response__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_BJES_Response__1up = new TH1F("histcl_noMET_JET_BJES_Response__1up", "histcl_noMET_JET_BJES_Response__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_BJES_Response__1up = new TH1F("histll_noMET_JET_BJES_Response__1up", "histll_noMET_JET_BJES_Response__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_BJES_Response__1up = new TH1F("histb_noMET_JET_BJES_Response__1up", "histb_noMET_JET_BJES_Response__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_BJES_Response__1up = new TH1F("histc_noMET_JET_BJES_Response__1up", "histc_noMET_JET_BJES_Response__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_BJES_Response__1up = new TH1F("histl_noMET_JET_BJES_Response__1up", "histl_noMET_JET_BJES_Response__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_EtaIntercalibration_Modelling__1down = new TH1F("histbb_noMET_JET_EtaIntercalibration_Modelling__1down", "histbb_noMET_JET_EtaIntercalibration_Modelling__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_EtaIntercalibration_Modelling__1down = new TH1F("histbc_noMET_JET_EtaIntercalibration_Modelling__1down", "histbc_noMET_JET_EtaIntercalibration_Modelling__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_EtaIntercalibration_Modelling__1down = new TH1F("histbl_noMET_JET_EtaIntercalibration_Modelling__1down", "histbl_noMET_JET_EtaIntercalibration_Modelling__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_EtaIntercalibration_Modelling__1down = new TH1F("histcc_noMET_JET_EtaIntercalibration_Modelling__1down", "histcc_noMET_JET_EtaIntercalibration_Modelling__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_EtaIntercalibration_Modelling__1down = new TH1F("histcl_noMET_JET_EtaIntercalibration_Modelling__1down", "histcl_noMET_JET_EtaIntercalibration_Modelling__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_EtaIntercalibration_Modelling__1down = new TH1F("histll_noMET_JET_EtaIntercalibration_Modelling__1down", "histll_noMET_JET_EtaIntercalibration_Modelling__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_EtaIntercalibration_Modelling__1down = new TH1F("histb_noMET_JET_EtaIntercalibration_Modelling__1down", "histb_noMET_JET_EtaIntercalibration_Modelling__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_EtaIntercalibration_Modelling__1down = new TH1F("histc_noMET_JET_EtaIntercalibration_Modelling__1down", "histc_noMET_JET_EtaIntercalibration_Modelling__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_EtaIntercalibration_Modelling__1down = new TH1F("histl_noMET_JET_EtaIntercalibration_Modelling__1down", "histl_noMET_JET_EtaIntercalibration_Modelling__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_EtaIntercalibration_Modelling__1up = new TH1F("histbb_noMET_JET_EtaIntercalibration_Modelling__1up", "histbb_noMET_JET_EtaIntercalibration_Modelling__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_EtaIntercalibration_Modelling__1up = new TH1F("histbc_noMET_JET_EtaIntercalibration_Modelling__1up", "histbc_noMET_JET_EtaIntercalibration_Modelling__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_EtaIntercalibration_Modelling__1up = new TH1F("histbl_noMET_JET_EtaIntercalibration_Modelling__1up", "histbl_noMET_JET_EtaIntercalibration_Modelling__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_EtaIntercalibration_Modelling__1up = new TH1F("histcc_noMET_JET_EtaIntercalibration_Modelling__1up", "histcc_noMET_JET_EtaIntercalibration_Modelling__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_EtaIntercalibration_Modelling__1up = new TH1F("histcl_noMET_JET_EtaIntercalibration_Modelling__1up", "histcl_noMET_JET_EtaIntercalibration_Modelling__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_EtaIntercalibration_Modelling__1up = new TH1F("histll_noMET_JET_EtaIntercalibration_Modelling__1up", "histll_noMET_JET_EtaIntercalibration_Modelling__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_EtaIntercalibration_Modelling__1up = new TH1F("histb_noMET_JET_EtaIntercalibration_Modelling__1up", "histb_noMET_JET_EtaIntercalibration_Modelling__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_EtaIntercalibration_Modelling__1up = new TH1F("histc_noMET_JET_EtaIntercalibration_Modelling__1up", "histc_noMET_JET_EtaIntercalibration_Modelling__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_EtaIntercalibration_Modelling__1up = new TH1F("histl_noMET_JET_EtaIntercalibration_Modelling__1up", "histl_noMET_JET_EtaIntercalibration_Modelling__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down = new TH1F("histbb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", "histbb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down = new TH1F("histbc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", "histbc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down = new TH1F("histbl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", "histbl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down = new TH1F("histcc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", "histcc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down = new TH1F("histcl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", "histcl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down = new TH1F("histll_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", "histll_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down = new TH1F("histb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", "histb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down = new TH1F("histc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", "histc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down = new TH1F("histl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", "histl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up = new TH1F("histbb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", "histbb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up = new TH1F("histbc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", "histbc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up = new TH1F("histbl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", "histbl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up = new TH1F("histcc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", "histcc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up = new TH1F("histcl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", "histcl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up = new TH1F("histll_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", "histll_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up = new TH1F("histb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", "histb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up = new TH1F("histc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", "histc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up = new TH1F("histl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", "histl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_EtaIntercalibration_NonClosure_highE__1down = new TH1F("histbb_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", "histbb_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_EtaIntercalibration_NonClosure_highE__1down = new TH1F("histbc_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", "histbc_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_EtaIntercalibration_NonClosure_highE__1down = new TH1F("histbl_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", "histbl_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_EtaIntercalibration_NonClosure_highE__1down = new TH1F("histcc_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", "histcc_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_EtaIntercalibration_NonClosure_highE__1down = new TH1F("histcl_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", "histcl_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_EtaIntercalibration_NonClosure_highE__1down = new TH1F("histll_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", "histll_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_EtaIntercalibration_NonClosure_highE__1down = new TH1F("histb_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", "histb_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_EtaIntercalibration_NonClosure_highE__1down = new TH1F("histc_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", "histc_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_EtaIntercalibration_NonClosure_highE__1down = new TH1F("histl_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", "histl_noMET_JET_EtaIntercalibration_NonClosure_highE__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_EtaIntercalibration_NonClosure_highE__1up = new TH1F("histbb_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", "histbb_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_EtaIntercalibration_NonClosure_highE__1up = new TH1F("histbc_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", "histbc_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_EtaIntercalibration_NonClosure_highE__1up = new TH1F("histbl_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", "histbl_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_EtaIntercalibration_NonClosure_highE__1up = new TH1F("histcc_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", "histcc_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_EtaIntercalibration_NonClosure_highE__1up = new TH1F("histcl_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", "histcl_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_EtaIntercalibration_NonClosure_highE__1up = new TH1F("histll_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", "histll_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_EtaIntercalibration_NonClosure_highE__1up = new TH1F("histb_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", "histb_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_EtaIntercalibration_NonClosure_highE__1up = new TH1F("histc_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", "histc_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_EtaIntercalibration_NonClosure_highE__1up = new TH1F("histl_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", "histl_noMET_JET_EtaIntercalibration_NonClosure_highE__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down = new TH1F("histbb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", "histbb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down = new TH1F("histbc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", "histbc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down = new TH1F("histbl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", "histbl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down = new TH1F("histcc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", "histcc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down = new TH1F("histcl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", "histcl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down = new TH1F("histll_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", "histll_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down = new TH1F("histb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", "histb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down = new TH1F("histc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", "histc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down = new TH1F("histl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", "histl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up = new TH1F("histbb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", "histbb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up = new TH1F("histbc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", "histbc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up = new TH1F("histbl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", "histbl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up = new TH1F("histcc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", "histcc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up = new TH1F("histcl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", "histcl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up = new TH1F("histll_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", "histll_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up = new TH1F("histb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", "histb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up = new TH1F("histc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", "histc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up = new TH1F("histl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", "histl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down = new TH1F("histbb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", "histbb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down = new TH1F("histbc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", "histbc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down = new TH1F("histbl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", "histbl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down = new TH1F("histcc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", "histcc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down = new TH1F("histcl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", "histcl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down = new TH1F("histll_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", "histll_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down = new TH1F("histb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", "histb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down = new TH1F("histc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", "histc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down = new TH1F("histl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", "histl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up = new TH1F("histbb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", "histbb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up = new TH1F("histbc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", "histbc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up = new TH1F("histbl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", "histbl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up = new TH1F("histcc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", "histcc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up = new TH1F("histcl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", "histcl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up = new TH1F("histll_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", "histll_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up = new TH1F("histb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", "histb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up = new TH1F("histc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", "histc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up = new TH1F("histl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", "histl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_EtaIntercalibration_TotalStat__1down = new TH1F("histbb_noMET_JET_EtaIntercalibration_TotalStat__1down", "histbb_noMET_JET_EtaIntercalibration_TotalStat__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_EtaIntercalibration_TotalStat__1down = new TH1F("histbc_noMET_JET_EtaIntercalibration_TotalStat__1down", "histbc_noMET_JET_EtaIntercalibration_TotalStat__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_EtaIntercalibration_TotalStat__1down = new TH1F("histbl_noMET_JET_EtaIntercalibration_TotalStat__1down", "histbl_noMET_JET_EtaIntercalibration_TotalStat__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_EtaIntercalibration_TotalStat__1down = new TH1F("histcc_noMET_JET_EtaIntercalibration_TotalStat__1down", "histcc_noMET_JET_EtaIntercalibration_TotalStat__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_EtaIntercalibration_TotalStat__1down = new TH1F("histcl_noMET_JET_EtaIntercalibration_TotalStat__1down", "histcl_noMET_JET_EtaIntercalibration_TotalStat__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_EtaIntercalibration_TotalStat__1down = new TH1F("histll_noMET_JET_EtaIntercalibration_TotalStat__1down", "histll_noMET_JET_EtaIntercalibration_TotalStat__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_EtaIntercalibration_TotalStat__1down = new TH1F("histb_noMET_JET_EtaIntercalibration_TotalStat__1down", "histb_noMET_JET_EtaIntercalibration_TotalStat__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_EtaIntercalibration_TotalStat__1down = new TH1F("histc_noMET_JET_EtaIntercalibration_TotalStat__1down", "histc_noMET_JET_EtaIntercalibration_TotalStat__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_EtaIntercalibration_TotalStat__1down = new TH1F("histl_noMET_JET_EtaIntercalibration_TotalStat__1down", "histl_noMET_JET_EtaIntercalibration_TotalStat__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_EtaIntercalibration_TotalStat__1up = new TH1F("histbb_noMET_JET_EtaIntercalibration_TotalStat__1up", "histbb_noMET_JET_EtaIntercalibration_TotalStat__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_EtaIntercalibration_TotalStat__1up = new TH1F("histbc_noMET_JET_EtaIntercalibration_TotalStat__1up", "histbc_noMET_JET_EtaIntercalibration_TotalStat__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_EtaIntercalibration_TotalStat__1up = new TH1F("histbl_noMET_JET_EtaIntercalibration_TotalStat__1up", "histbl_noMET_JET_EtaIntercalibration_TotalStat__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_EtaIntercalibration_TotalStat__1up = new TH1F("histcc_noMET_JET_EtaIntercalibration_TotalStat__1up", "histcc_noMET_JET_EtaIntercalibration_TotalStat__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_EtaIntercalibration_TotalStat__1up = new TH1F("histcl_noMET_JET_EtaIntercalibration_TotalStat__1up", "histcl_noMET_JET_EtaIntercalibration_TotalStat__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_EtaIntercalibration_TotalStat__1up = new TH1F("histll_noMET_JET_EtaIntercalibration_TotalStat__1up", "histll_noMET_JET_EtaIntercalibration_TotalStat__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_EtaIntercalibration_TotalStat__1up = new TH1F("histb_noMET_JET_EtaIntercalibration_TotalStat__1up", "histb_noMET_JET_EtaIntercalibration_TotalStat__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_EtaIntercalibration_TotalStat__1up = new TH1F("histc_noMET_JET_EtaIntercalibration_TotalStat__1up", "histc_noMET_JET_EtaIntercalibration_TotalStat__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_EtaIntercalibration_TotalStat__1up = new TH1F("histl_noMET_JET_EtaIntercalibration_TotalStat__1up", "histl_noMET_JET_EtaIntercalibration_TotalStat__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_fJvtEfficiency__1down = new TH1F("histbb_noMET_JET_fJvtEfficiency__1down", "histbb_noMET_JET_fJvtEfficiency__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_fJvtEfficiency__1down = new TH1F("histbc_noMET_JET_fJvtEfficiency__1down", "histbc_noMET_JET_fJvtEfficiency__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_fJvtEfficiency__1down = new TH1F("histbl_noMET_JET_fJvtEfficiency__1down", "histbl_noMET_JET_fJvtEfficiency__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_fJvtEfficiency__1down = new TH1F("histcc_noMET_JET_fJvtEfficiency__1down", "histcc_noMET_JET_fJvtEfficiency__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_fJvtEfficiency__1down = new TH1F("histcl_noMET_JET_fJvtEfficiency__1down", "histcl_noMET_JET_fJvtEfficiency__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_fJvtEfficiency__1down = new TH1F("histll_noMET_JET_fJvtEfficiency__1down", "histll_noMET_JET_fJvtEfficiency__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_fJvtEfficiency__1down = new TH1F("histb_noMET_JET_fJvtEfficiency__1down", "histb_noMET_JET_fJvtEfficiency__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_fJvtEfficiency__1down = new TH1F("histc_noMET_JET_fJvtEfficiency__1down", "histc_noMET_JET_fJvtEfficiency__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_fJvtEfficiency__1down = new TH1F("histl_noMET_JET_fJvtEfficiency__1down", "histl_noMET_JET_fJvtEfficiency__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_fJvtEfficiency__1up = new TH1F("histbb_noMET_JET_fJvtEfficiency__1up", "histbb_noMET_JET_fJvtEfficiency__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_fJvtEfficiency__1up = new TH1F("histbc_noMET_JET_fJvtEfficiency__1up", "histbc_noMET_JET_fJvtEfficiency__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_fJvtEfficiency__1up = new TH1F("histbl_noMET_JET_fJvtEfficiency__1up", "histbl_noMET_JET_fJvtEfficiency__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_fJvtEfficiency__1up = new TH1F("histcc_noMET_JET_fJvtEfficiency__1up", "histcc_noMET_JET_fJvtEfficiency__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_fJvtEfficiency__1up = new TH1F("histcl_noMET_JET_fJvtEfficiency__1up", "histcl_noMET_JET_fJvtEfficiency__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_fJvtEfficiency__1up = new TH1F("histll_noMET_JET_fJvtEfficiency__1up", "histll_noMET_JET_fJvtEfficiency__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_fJvtEfficiency__1up = new TH1F("histb_noMET_JET_fJvtEfficiency__1up", "histb_noMET_JET_fJvtEfficiency__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_fJvtEfficiency__1up = new TH1F("histc_noMET_JET_fJvtEfficiency__1up", "histc_noMET_JET_fJvtEfficiency__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_fJvtEfficiency__1up = new TH1F("histl_noMET_JET_fJvtEfficiency__1up", "histl_noMET_JET_fJvtEfficiency__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_Flavor_Composition__1down = new TH1F("histbb_noMET_JET_Flavor_Composition__1down", "histbb_noMET_JET_Flavor_Composition__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_Flavor_Composition__1down = new TH1F("histbc_noMET_JET_Flavor_Composition__1down", "histbc_noMET_JET_Flavor_Composition__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_Flavor_Composition__1down = new TH1F("histbl_noMET_JET_Flavor_Composition__1down", "histbl_noMET_JET_Flavor_Composition__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_Flavor_Composition__1down = new TH1F("histcc_noMET_JET_Flavor_Composition__1down", "histcc_noMET_JET_Flavor_Composition__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_Flavor_Composition__1down = new TH1F("histcl_noMET_JET_Flavor_Composition__1down", "histcl_noMET_JET_Flavor_Composition__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_Flavor_Composition__1down = new TH1F("histll_noMET_JET_Flavor_Composition__1down", "histll_noMET_JET_Flavor_Composition__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_Flavor_Composition__1down = new TH1F("histb_noMET_JET_Flavor_Composition__1down", "histb_noMET_JET_Flavor_Composition__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_Flavor_Composition__1down = new TH1F("histc_noMET_JET_Flavor_Composition__1down", "histc_noMET_JET_Flavor_Composition__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_Flavor_Composition__1down = new TH1F("histl_noMET_JET_Flavor_Composition__1down", "histl_noMET_JET_Flavor_Composition__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_Flavor_Composition__1up = new TH1F("histbb_noMET_JET_Flavor_Composition__1up", "histbb_noMET_JET_Flavor_Composition__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_Flavor_Composition__1up = new TH1F("histbc_noMET_JET_Flavor_Composition__1up", "histbc_noMET_JET_Flavor_Composition__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_Flavor_Composition__1up = new TH1F("histbl_noMET_JET_Flavor_Composition__1up", "histbl_noMET_JET_Flavor_Composition__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_Flavor_Composition__1up = new TH1F("histcc_noMET_JET_Flavor_Composition__1up", "histcc_noMET_JET_Flavor_Composition__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_Flavor_Composition__1up = new TH1F("histcl_noMET_JET_Flavor_Composition__1up", "histcl_noMET_JET_Flavor_Composition__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_Flavor_Composition__1up = new TH1F("histll_noMET_JET_Flavor_Composition__1up", "histll_noMET_JET_Flavor_Composition__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_Flavor_Composition__1up = new TH1F("histb_noMET_JET_Flavor_Composition__1up", "histb_noMET_JET_Flavor_Composition__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_Flavor_Composition__1up = new TH1F("histc_noMET_JET_Flavor_Composition__1up", "histc_noMET_JET_Flavor_Composition__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_Flavor_Composition__1up = new TH1F("histl_noMET_JET_Flavor_Composition__1up", "histl_noMET_JET_Flavor_Composition__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_Flavor_Response__1down = new TH1F("histbb_noMET_JET_Flavor_Response__1down", "histbb_noMET_JET_Flavor_Response__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_Flavor_Response__1down = new TH1F("histbc_noMET_JET_Flavor_Response__1down", "histbc_noMET_JET_Flavor_Response__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_Flavor_Response__1down = new TH1F("histbl_noMET_JET_Flavor_Response__1down", "histbl_noMET_JET_Flavor_Response__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_Flavor_Response__1down = new TH1F("histcc_noMET_JET_Flavor_Response__1down", "histcc_noMET_JET_Flavor_Response__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_Flavor_Response__1down = new TH1F("histcl_noMET_JET_Flavor_Response__1down", "histcl_noMET_JET_Flavor_Response__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_Flavor_Response__1down = new TH1F("histll_noMET_JET_Flavor_Response__1down", "histll_noMET_JET_Flavor_Response__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_Flavor_Response__1down = new TH1F("histb_noMET_JET_Flavor_Response__1down", "histb_noMET_JET_Flavor_Response__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_Flavor_Response__1down = new TH1F("histc_noMET_JET_Flavor_Response__1down", "histc_noMET_JET_Flavor_Response__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_Flavor_Response__1down = new TH1F("histl_noMET_JET_Flavor_Response__1down", "histl_noMET_JET_Flavor_Response__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_Flavor_Response__1up = new TH1F("histbb_noMET_JET_Flavor_Response__1up", "histbb_noMET_JET_Flavor_Response__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_Flavor_Response__1up = new TH1F("histbc_noMET_JET_Flavor_Response__1up", "histbc_noMET_JET_Flavor_Response__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_Flavor_Response__1up = new TH1F("histbl_noMET_JET_Flavor_Response__1up", "histbl_noMET_JET_Flavor_Response__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_Flavor_Response__1up = new TH1F("histcc_noMET_JET_Flavor_Response__1up", "histcc_noMET_JET_Flavor_Response__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_Flavor_Response__1up = new TH1F("histcl_noMET_JET_Flavor_Response__1up", "histcl_noMET_JET_Flavor_Response__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_Flavor_Response__1up = new TH1F("histll_noMET_JET_Flavor_Response__1up", "histll_noMET_JET_Flavor_Response__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_Flavor_Response__1up = new TH1F("histb_noMET_JET_Flavor_Response__1up", "histb_noMET_JET_Flavor_Response__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_Flavor_Response__1up = new TH1F("histc_noMET_JET_Flavor_Response__1up", "histc_noMET_JET_Flavor_Response__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_Flavor_Response__1up = new TH1F("histl_noMET_JET_Flavor_Response__1up", "histl_noMET_JET_Flavor_Response__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_JvtEfficiency__1down = new TH1F("histbb_noMET_JET_JvtEfficiency__1down", "histbb_noMET_JET_JvtEfficiency__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_JvtEfficiency__1down = new TH1F("histbc_noMET_JET_JvtEfficiency__1down", "histbc_noMET_JET_JvtEfficiency__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_JvtEfficiency__1down = new TH1F("histbl_noMET_JET_JvtEfficiency__1down", "histbl_noMET_JET_JvtEfficiency__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_JvtEfficiency__1down = new TH1F("histcc_noMET_JET_JvtEfficiency__1down", "histcc_noMET_JET_JvtEfficiency__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_JvtEfficiency__1down = new TH1F("histcl_noMET_JET_JvtEfficiency__1down", "histcl_noMET_JET_JvtEfficiency__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_JvtEfficiency__1down = new TH1F("histll_noMET_JET_JvtEfficiency__1down", "histll_noMET_JET_JvtEfficiency__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_JvtEfficiency__1down = new TH1F("histb_noMET_JET_JvtEfficiency__1down", "histb_noMET_JET_JvtEfficiency__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_JvtEfficiency__1down = new TH1F("histc_noMET_JET_JvtEfficiency__1down", "histc_noMET_JET_JvtEfficiency__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_JvtEfficiency__1down = new TH1F("histl_noMET_JET_JvtEfficiency__1down", "histl_noMET_JET_JvtEfficiency__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_JvtEfficiency__1up = new TH1F("histbb_noMET_JET_JvtEfficiency__1up", "histbb_noMET_JET_JvtEfficiency__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_JvtEfficiency__1up = new TH1F("histbc_noMET_JET_JvtEfficiency__1up", "histbc_noMET_JET_JvtEfficiency__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_JvtEfficiency__1up = new TH1F("histbl_noMET_JET_JvtEfficiency__1up", "histbl_noMET_JET_JvtEfficiency__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_JvtEfficiency__1up = new TH1F("histcc_noMET_JET_JvtEfficiency__1up", "histcc_noMET_JET_JvtEfficiency__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_JvtEfficiency__1up = new TH1F("histcl_noMET_JET_JvtEfficiency__1up", "histcl_noMET_JET_JvtEfficiency__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_JvtEfficiency__1up = new TH1F("histll_noMET_JET_JvtEfficiency__1up", "histll_noMET_JET_JvtEfficiency__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_JvtEfficiency__1up = new TH1F("histb_noMET_JET_JvtEfficiency__1up", "histb_noMET_JET_JvtEfficiency__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_JvtEfficiency__1up = new TH1F("histc_noMET_JET_JvtEfficiency__1up", "histc_noMET_JET_JvtEfficiency__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_JvtEfficiency__1up = new TH1F("histl_noMET_JET_JvtEfficiency__1up", "histl_noMET_JET_JvtEfficiency__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_Pileup_OffsetMu__1down = new TH1F("histbb_noMET_JET_Pileup_OffsetMu__1down", "histbb_noMET_JET_Pileup_OffsetMu__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_Pileup_OffsetMu__1down = new TH1F("histbc_noMET_JET_Pileup_OffsetMu__1down", "histbc_noMET_JET_Pileup_OffsetMu__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_Pileup_OffsetMu__1down = new TH1F("histbl_noMET_JET_Pileup_OffsetMu__1down", "histbl_noMET_JET_Pileup_OffsetMu__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_Pileup_OffsetMu__1down = new TH1F("histcc_noMET_JET_Pileup_OffsetMu__1down", "histcc_noMET_JET_Pileup_OffsetMu__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_Pileup_OffsetMu__1down = new TH1F("histcl_noMET_JET_Pileup_OffsetMu__1down", "histcl_noMET_JET_Pileup_OffsetMu__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_Pileup_OffsetMu__1down = new TH1F("histll_noMET_JET_Pileup_OffsetMu__1down", "histll_noMET_JET_Pileup_OffsetMu__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_Pileup_OffsetMu__1down = new TH1F("histb_noMET_JET_Pileup_OffsetMu__1down", "histb_noMET_JET_Pileup_OffsetMu__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_Pileup_OffsetMu__1down = new TH1F("histc_noMET_JET_Pileup_OffsetMu__1down", "histc_noMET_JET_Pileup_OffsetMu__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_Pileup_OffsetMu__1down = new TH1F("histl_noMET_JET_Pileup_OffsetMu__1down", "histl_noMET_JET_Pileup_OffsetMu__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_Pileup_OffsetMu__1up = new TH1F("histbb_noMET_JET_Pileup_OffsetMu__1up", "histbb_noMET_JET_Pileup_OffsetMu__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_Pileup_OffsetMu__1up = new TH1F("histbc_noMET_JET_Pileup_OffsetMu__1up", "histbc_noMET_JET_Pileup_OffsetMu__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_Pileup_OffsetMu__1up = new TH1F("histbl_noMET_JET_Pileup_OffsetMu__1up", "histbl_noMET_JET_Pileup_OffsetMu__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_Pileup_OffsetMu__1up = new TH1F("histcc_noMET_JET_Pileup_OffsetMu__1up", "histcc_noMET_JET_Pileup_OffsetMu__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_Pileup_OffsetMu__1up = new TH1F("histcl_noMET_JET_Pileup_OffsetMu__1up", "histcl_noMET_JET_Pileup_OffsetMu__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_Pileup_OffsetMu__1up = new TH1F("histll_noMET_JET_Pileup_OffsetMu__1up", "histll_noMET_JET_Pileup_OffsetMu__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_Pileup_OffsetMu__1up = new TH1F("histb_noMET_JET_Pileup_OffsetMu__1up", "histb_noMET_JET_Pileup_OffsetMu__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_Pileup_OffsetMu__1up = new TH1F("histc_noMET_JET_Pileup_OffsetMu__1up", "histc_noMET_JET_Pileup_OffsetMu__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_Pileup_OffsetMu__1up = new TH1F("histl_noMET_JET_Pileup_OffsetMu__1up", "histl_noMET_JET_Pileup_OffsetMu__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_Pileup_OffsetNPV__1down = new TH1F("histbb_noMET_JET_Pileup_OffsetNPV__1down", "histbb_noMET_JET_Pileup_OffsetNPV__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_Pileup_OffsetNPV__1down = new TH1F("histbc_noMET_JET_Pileup_OffsetNPV__1down", "histbc_noMET_JET_Pileup_OffsetNPV__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_Pileup_OffsetNPV__1down = new TH1F("histbl_noMET_JET_Pileup_OffsetNPV__1down", "histbl_noMET_JET_Pileup_OffsetNPV__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_Pileup_OffsetNPV__1down = new TH1F("histcc_noMET_JET_Pileup_OffsetNPV__1down", "histcc_noMET_JET_Pileup_OffsetNPV__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_Pileup_OffsetNPV__1down = new TH1F("histcl_noMET_JET_Pileup_OffsetNPV__1down", "histcl_noMET_JET_Pileup_OffsetNPV__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_Pileup_OffsetNPV__1down = new TH1F("histll_noMET_JET_Pileup_OffsetNPV__1down", "histll_noMET_JET_Pileup_OffsetNPV__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_Pileup_OffsetNPV__1down = new TH1F("histb_noMET_JET_Pileup_OffsetNPV__1down", "histb_noMET_JET_Pileup_OffsetNPV__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_Pileup_OffsetNPV__1down = new TH1F("histc_noMET_JET_Pileup_OffsetNPV__1down", "histc_noMET_JET_Pileup_OffsetNPV__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_Pileup_OffsetNPV__1down = new TH1F("histl_noMET_JET_Pileup_OffsetNPV__1down", "histl_noMET_JET_Pileup_OffsetNPV__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_Pileup_OffsetNPV__1up = new TH1F("histbb_noMET_JET_Pileup_OffsetNPV__1up", "histbb_noMET_JET_Pileup_OffsetNPV__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_Pileup_OffsetNPV__1up = new TH1F("histbc_noMET_JET_Pileup_OffsetNPV__1up", "histbc_noMET_JET_Pileup_OffsetNPV__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_Pileup_OffsetNPV__1up = new TH1F("histbl_noMET_JET_Pileup_OffsetNPV__1up", "histbl_noMET_JET_Pileup_OffsetNPV__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_Pileup_OffsetNPV__1up = new TH1F("histcc_noMET_JET_Pileup_OffsetNPV__1up", "histcc_noMET_JET_Pileup_OffsetNPV__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_Pileup_OffsetNPV__1up = new TH1F("histcl_noMET_JET_Pileup_OffsetNPV__1up", "histcl_noMET_JET_Pileup_OffsetNPV__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_Pileup_OffsetNPV__1up = new TH1F("histll_noMET_JET_Pileup_OffsetNPV__1up", "histll_noMET_JET_Pileup_OffsetNPV__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_Pileup_OffsetNPV__1up = new TH1F("histb_noMET_JET_Pileup_OffsetNPV__1up", "histb_noMET_JET_Pileup_OffsetNPV__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_Pileup_OffsetNPV__1up = new TH1F("histc_noMET_JET_Pileup_OffsetNPV__1up", "histc_noMET_JET_Pileup_OffsetNPV__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_Pileup_OffsetNPV__1up = new TH1F("histl_noMET_JET_Pileup_OffsetNPV__1up", "histl_noMET_JET_Pileup_OffsetNPV__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_Pileup_PtTerm__1down = new TH1F("histbb_noMET_JET_Pileup_PtTerm__1down", "histbb_noMET_JET_Pileup_PtTerm__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_Pileup_PtTerm__1down = new TH1F("histbc_noMET_JET_Pileup_PtTerm__1down", "histbc_noMET_JET_Pileup_PtTerm__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_Pileup_PtTerm__1down = new TH1F("histbl_noMET_JET_Pileup_PtTerm__1down", "histbl_noMET_JET_Pileup_PtTerm__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_Pileup_PtTerm__1down = new TH1F("histcc_noMET_JET_Pileup_PtTerm__1down", "histcc_noMET_JET_Pileup_PtTerm__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_Pileup_PtTerm__1down = new TH1F("histcl_noMET_JET_Pileup_PtTerm__1down", "histcl_noMET_JET_Pileup_PtTerm__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_Pileup_PtTerm__1down = new TH1F("histll_noMET_JET_Pileup_PtTerm__1down", "histll_noMET_JET_Pileup_PtTerm__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_Pileup_PtTerm__1down = new TH1F("histb_noMET_JET_Pileup_PtTerm__1down", "histb_noMET_JET_Pileup_PtTerm__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_Pileup_PtTerm__1down = new TH1F("histc_noMET_JET_Pileup_PtTerm__1down", "histc_noMET_JET_Pileup_PtTerm__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_Pileup_PtTerm__1down = new TH1F("histl_noMET_JET_Pileup_PtTerm__1down", "histl_noMET_JET_Pileup_PtTerm__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_Pileup_PtTerm__1up = new TH1F("histbb_noMET_JET_Pileup_PtTerm__1up", "histbb_noMET_JET_Pileup_PtTerm__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_Pileup_PtTerm__1up = new TH1F("histbc_noMET_JET_Pileup_PtTerm__1up", "histbc_noMET_JET_Pileup_PtTerm__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_Pileup_PtTerm__1up = new TH1F("histbl_noMET_JET_Pileup_PtTerm__1up", "histbl_noMET_JET_Pileup_PtTerm__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_Pileup_PtTerm__1up = new TH1F("histcc_noMET_JET_Pileup_PtTerm__1up", "histcc_noMET_JET_Pileup_PtTerm__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_Pileup_PtTerm__1up = new TH1F("histcl_noMET_JET_Pileup_PtTerm__1up", "histcl_noMET_JET_Pileup_PtTerm__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_Pileup_PtTerm__1up = new TH1F("histll_noMET_JET_Pileup_PtTerm__1up", "histll_noMET_JET_Pileup_PtTerm__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_Pileup_PtTerm__1up = new TH1F("histb_noMET_JET_Pileup_PtTerm__1up", "histb_noMET_JET_Pileup_PtTerm__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_Pileup_PtTerm__1up = new TH1F("histc_noMET_JET_Pileup_PtTerm__1up", "histc_noMET_JET_Pileup_PtTerm__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_Pileup_PtTerm__1up = new TH1F("histl_noMET_JET_Pileup_PtTerm__1up", "histl_noMET_JET_Pileup_PtTerm__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_Pileup_RhoTopology__1down = new TH1F("histbb_noMET_JET_Pileup_RhoTopology__1down", "histbb_noMET_JET_Pileup_RhoTopology__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_Pileup_RhoTopology__1down = new TH1F("histbc_noMET_JET_Pileup_RhoTopology__1down", "histbc_noMET_JET_Pileup_RhoTopology__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_Pileup_RhoTopology__1down = new TH1F("histbl_noMET_JET_Pileup_RhoTopology__1down", "histbl_noMET_JET_Pileup_RhoTopology__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_Pileup_RhoTopology__1down = new TH1F("histcc_noMET_JET_Pileup_RhoTopology__1down", "histcc_noMET_JET_Pileup_RhoTopology__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_Pileup_RhoTopology__1down = new TH1F("histcl_noMET_JET_Pileup_RhoTopology__1down", "histcl_noMET_JET_Pileup_RhoTopology__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_Pileup_RhoTopology__1down = new TH1F("histll_noMET_JET_Pileup_RhoTopology__1down", "histll_noMET_JET_Pileup_RhoTopology__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_Pileup_RhoTopology__1down = new TH1F("histb_noMET_JET_Pileup_RhoTopology__1down", "histb_noMET_JET_Pileup_RhoTopology__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_Pileup_RhoTopology__1down = new TH1F("histc_noMET_JET_Pileup_RhoTopology__1down", "histc_noMET_JET_Pileup_RhoTopology__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_Pileup_RhoTopology__1down = new TH1F("histl_noMET_JET_Pileup_RhoTopology__1down", "histl_noMET_JET_Pileup_RhoTopology__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_Pileup_RhoTopology__1up = new TH1F("histbb_noMET_JET_Pileup_RhoTopology__1up", "histbb_noMET_JET_Pileup_RhoTopology__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_Pileup_RhoTopology__1up = new TH1F("histbc_noMET_JET_Pileup_RhoTopology__1up", "histbc_noMET_JET_Pileup_RhoTopology__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_Pileup_RhoTopology__1up = new TH1F("histbl_noMET_JET_Pileup_RhoTopology__1up", "histbl_noMET_JET_Pileup_RhoTopology__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_Pileup_RhoTopology__1up = new TH1F("histcc_noMET_JET_Pileup_RhoTopology__1up", "histcc_noMET_JET_Pileup_RhoTopology__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_Pileup_RhoTopology__1up = new TH1F("histcl_noMET_JET_Pileup_RhoTopology__1up", "histcl_noMET_JET_Pileup_RhoTopology__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_Pileup_RhoTopology__1up = new TH1F("histll_noMET_JET_Pileup_RhoTopology__1up", "histll_noMET_JET_Pileup_RhoTopology__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_Pileup_RhoTopology__1up = new TH1F("histb_noMET_JET_Pileup_RhoTopology__1up", "histb_noMET_JET_Pileup_RhoTopology__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_Pileup_RhoTopology__1up = new TH1F("histc_noMET_JET_Pileup_RhoTopology__1up", "histc_noMET_JET_Pileup_RhoTopology__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_Pileup_RhoTopology__1up = new TH1F("histl_noMET_JET_Pileup_RhoTopology__1up", "histl_noMET_JET_Pileup_RhoTopology__1up", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_SingleParticle_HighPt__1down = new TH1F("histbb_noMET_JET_SingleParticle_HighPt__1down", "histbb_noMET_JET_SingleParticle_HighPt__1down", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_SingleParticle_HighPt__1down = new TH1F("histbc_noMET_JET_SingleParticle_HighPt__1down", "histbc_noMET_JET_SingleParticle_HighPt__1down", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_SingleParticle_HighPt__1down = new TH1F("histbl_noMET_JET_SingleParticle_HighPt__1down", "histbl_noMET_JET_SingleParticle_HighPt__1down", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_SingleParticle_HighPt__1down = new TH1F("histcc_noMET_JET_SingleParticle_HighPt__1down", "histcc_noMET_JET_SingleParticle_HighPt__1down", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_SingleParticle_HighPt__1down = new TH1F("histcl_noMET_JET_SingleParticle_HighPt__1down", "histcl_noMET_JET_SingleParticle_HighPt__1down", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_SingleParticle_HighPt__1down = new TH1F("histll_noMET_JET_SingleParticle_HighPt__1down", "histll_noMET_JET_SingleParticle_HighPt__1down", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_SingleParticle_HighPt__1down = new TH1F("histb_noMET_JET_SingleParticle_HighPt__1down", "histb_noMET_JET_SingleParticle_HighPt__1down", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_SingleParticle_HighPt__1down = new TH1F("histc_noMET_JET_SingleParticle_HighPt__1down", "histc_noMET_JET_SingleParticle_HighPt__1down", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_SingleParticle_HighPt__1down = new TH1F("histl_noMET_JET_SingleParticle_HighPt__1down", "histl_noMET_JET_SingleParticle_HighPt__1down", 5, -0.5, 4.5);
				TH1F *histbb_noMET_JET_SingleParticle_HighPt__1up = new TH1F("histbb_noMET_JET_SingleParticle_HighPt__1up", "histbb_noMET_JET_SingleParticle_HighPt__1up", 26, -0.5, 25.5);
				TH1F *histbc_noMET_JET_SingleParticle_HighPt__1up = new TH1F("histbc_noMET_JET_SingleParticle_HighPt__1up", "histbc_noMET_JET_SingleParticle_HighPt__1up", 26, -0.5, 25.5);
				TH1F *histbl_noMET_JET_SingleParticle_HighPt__1up = new TH1F("histbl_noMET_JET_SingleParticle_HighPt__1up", "histbl_noMET_JET_SingleParticle_HighPt__1up", 26, -0.5, 25.5);
				TH1F *histcc_noMET_JET_SingleParticle_HighPt__1up = new TH1F("histcc_noMET_JET_SingleParticle_HighPt__1up", "histcc_noMET_JET_SingleParticle_HighPt__1up", 26, -0.5, 25.5);
				TH1F *histcl_noMET_JET_SingleParticle_HighPt__1up = new TH1F("histcl_noMET_JET_SingleParticle_HighPt__1up", "histcl_noMET_JET_SingleParticle_HighPt__1up", 26, -0.5, 25.5);
				TH1F *histll_noMET_JET_SingleParticle_HighPt__1up = new TH1F("histll_noMET_JET_SingleParticle_HighPt__1up", "histll_noMET_JET_SingleParticle_HighPt__1up", 26, -0.5, 25.5);
				TH1F *histb_noMET_JET_SingleParticle_HighPt__1up = new TH1F("histb_noMET_JET_SingleParticle_HighPt__1up", "histb_noMET_JET_SingleParticle_HighPt__1up", 5, -0.5, 4.5);
				TH1F *histc_noMET_JET_SingleParticle_HighPt__1up = new TH1F("histc_noMET_JET_SingleParticle_HighPt__1up", "histc_noMET_JET_SingleParticle_HighPt__1up", 5, -0.5, 4.5);
				TH1F *histl_noMET_JET_SingleParticle_HighPt__1up = new TH1F("histl_noMET_JET_SingleParticle_HighPt__1up", "histl_noMET_JET_SingleParticle_HighPt__1up", 5, -0.5, 4.5);
				

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

				checkDijet(histbb_noMET_JET_BJES_Response__1down, histbc_noMET_JET_BJES_Response__1down, histbl_noMET_JET_BJES_Response__1down, histcc_noMET_JET_BJES_Response__1down, histcl_noMET_JET_BJES_Response__1down, histll_noMET_JET_BJES_Response__1down,
						   JET_BJES_Response__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_BJES_Response__1down_isPassed, JET_BJES_Response__1down_yyHF_leadjet_truthlabel,
						   JET_BJES_Response__1down_yyHF_subleadjet_truthlabel, JET_BJES_Response__1down_yyHF_leadjet_btagbin, JET_BJES_Response__1down_yyHF_subleadjet_btagbin, JET_BJES_Response__1down_yyHF_Njet_central, JET_BJES_Response__1down_yyHFjj_weight, JET_BJES_Response__1down_yyHF_met,
						   JET_BJES_Response__1down_yyHF_nelectron, JET_BJES_Response__1down_yyHF_nmuon, JET_BJES_Response__1down_m_yy);
				checkDijet(histbb_noMET_JET_BJES_Response__1up, histbc_noMET_JET_BJES_Response__1up, histbl_noMET_JET_BJES_Response__1up, histcc_noMET_JET_BJES_Response__1up, histcl_noMET_JET_BJES_Response__1up, histll_noMET_JET_BJES_Response__1up,
						   JET_BJES_Response__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_BJES_Response__1up_isPassed, JET_BJES_Response__1up_yyHF_leadjet_truthlabel,
						   JET_BJES_Response__1up_yyHF_subleadjet_truthlabel, JET_BJES_Response__1up_yyHF_leadjet_btagbin, JET_BJES_Response__1up_yyHF_subleadjet_btagbin, JET_BJES_Response__1up_yyHF_Njet_central, JET_BJES_Response__1up_yyHFjj_weight, JET_BJES_Response__1up_yyHF_met,
						   JET_BJES_Response__1up_yyHF_nelectron, JET_BJES_Response__1up_yyHF_nmuon, JET_BJES_Response__1up_m_yy);
				checkDijet(histbb_noMET_JET_EtaIntercalibration_Modelling__1down, histbc_noMET_JET_EtaIntercalibration_Modelling__1down, histbl_noMET_JET_EtaIntercalibration_Modelling__1down, histcc_noMET_JET_EtaIntercalibration_Modelling__1down, histcl_noMET_JET_EtaIntercalibration_Modelling__1down, histll_noMET_JET_EtaIntercalibration_Modelling__1down,
						   JET_EtaIntercalibration_Modelling__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_Modelling__1down_isPassed, JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_truthlabel,
						   JET_EtaIntercalibration_Modelling__1down_yyHF_subleadjet_truthlabel, JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_btagbin, JET_EtaIntercalibration_Modelling__1down_yyHF_subleadjet_btagbin, JET_EtaIntercalibration_Modelling__1down_yyHF_Njet_central, JET_EtaIntercalibration_Modelling__1down_yyHFjj_weight, JET_EtaIntercalibration_Modelling__1down_yyHF_met,
						   JET_EtaIntercalibration_Modelling__1down_yyHF_nelectron, JET_EtaIntercalibration_Modelling__1down_yyHF_nmuon, JET_EtaIntercalibration_Modelling__1down_m_yy);
				checkDijet(histbb_noMET_JET_EtaIntercalibration_Modelling__1up, histbc_noMET_JET_EtaIntercalibration_Modelling__1up, histbl_noMET_JET_EtaIntercalibration_Modelling__1up, histcc_noMET_JET_EtaIntercalibration_Modelling__1up, histcl_noMET_JET_EtaIntercalibration_Modelling__1up, histll_noMET_JET_EtaIntercalibration_Modelling__1up,
						   JET_EtaIntercalibration_Modelling__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_Modelling__1up_isPassed, JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_truthlabel,
						   JET_EtaIntercalibration_Modelling__1up_yyHF_subleadjet_truthlabel, JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_btagbin, JET_EtaIntercalibration_Modelling__1up_yyHF_subleadjet_btagbin, JET_EtaIntercalibration_Modelling__1up_yyHF_Njet_central, JET_EtaIntercalibration_Modelling__1up_yyHFjj_weight, JET_EtaIntercalibration_Modelling__1up_yyHF_met,
						   JET_EtaIntercalibration_Modelling__1up_yyHF_nelectron, JET_EtaIntercalibration_Modelling__1up_yyHF_nmuon, JET_EtaIntercalibration_Modelling__1up_m_yy);
				checkDijet(histbb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down, histbc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down, histbl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down, histcc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down, histcl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down, histll_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down,
						   JET_EtaIntercalibration_NonClosure_2018data__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_2018data__1down_isPassed, JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_truthlabel,
						   JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_subleadjet_truthlabel, JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_subleadjet_btagbin, JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_2018data__1down_yyHFjj_weight, JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_met,
						   JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_2018data__1down_m_yy);
				checkDijet(histbb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up, histbc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up, histbl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up, histcc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up, histcl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up, histll_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up,
						   JET_EtaIntercalibration_NonClosure_2018data__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_2018data__1up_isPassed, JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_truthlabel,
						   JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_subleadjet_truthlabel, JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_subleadjet_btagbin, JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_2018data__1up_yyHFjj_weight, JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_met,
						   JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_2018data__1up_m_yy);
				checkDijet(histbb_noMET_JET_EtaIntercalibration_NonClosure_highE__1down, histbc_noMET_JET_EtaIntercalibration_NonClosure_highE__1down, histbl_noMET_JET_EtaIntercalibration_NonClosure_highE__1down, histcc_noMET_JET_EtaIntercalibration_NonClosure_highE__1down, histcl_noMET_JET_EtaIntercalibration_NonClosure_highE__1down, histll_noMET_JET_EtaIntercalibration_NonClosure_highE__1down,
						   JET_EtaIntercalibration_NonClosure_highE__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_highE__1down_isPassed, JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_truthlabel,
						   JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_subleadjet_truthlabel, JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_subleadjet_btagbin, JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_highE__1down_yyHFjj_weight, JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_met,
						   JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_highE__1down_m_yy);
				checkDijet(histbb_noMET_JET_EtaIntercalibration_NonClosure_highE__1up, histbc_noMET_JET_EtaIntercalibration_NonClosure_highE__1up, histbl_noMET_JET_EtaIntercalibration_NonClosure_highE__1up, histcc_noMET_JET_EtaIntercalibration_NonClosure_highE__1up, histcl_noMET_JET_EtaIntercalibration_NonClosure_highE__1up, histll_noMET_JET_EtaIntercalibration_NonClosure_highE__1up,
						   JET_EtaIntercalibration_NonClosure_highE__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_highE__1up_isPassed, JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_truthlabel,
						   JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_subleadjet_truthlabel, JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_subleadjet_btagbin, JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_highE__1up_yyHFjj_weight, JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_met,
						   JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_highE__1up_m_yy);
				checkDijet(histbb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down, histbc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down, histbl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down, histcc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down, histcl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down, histll_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down,
						   JET_EtaIntercalibration_NonClosure_negEta__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_negEta__1down_isPassed, JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_truthlabel,
						   JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_subleadjet_truthlabel, JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_subleadjet_btagbin, JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_negEta__1down_yyHFjj_weight, JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_met,
						   JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_negEta__1down_m_yy);
				checkDijet(histbb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up, histbc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up, histbl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up, histcc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up, histcl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up, histll_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up,
						   JET_EtaIntercalibration_NonClosure_negEta__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_negEta__1up_isPassed, JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_truthlabel,
						   JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_subleadjet_truthlabel, JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_subleadjet_btagbin, JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_negEta__1up_yyHFjj_weight, JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_met,
						   JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_negEta__1up_m_yy);
				checkDijet(histbb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down, histbc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down, histbl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down, histcc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down, histcl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down, histll_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down,
						   JET_EtaIntercalibration_NonClosure_posEta__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_posEta__1down_isPassed, JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_truthlabel,
						   JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_subleadjet_truthlabel, JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_subleadjet_btagbin, JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_posEta__1down_yyHFjj_weight, JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_met,
						   JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_posEta__1down_m_yy);
				checkDijet(histbb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up, histbc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up, histbl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up, histcc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up, histcl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up, histll_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up,
						   JET_EtaIntercalibration_NonClosure_posEta__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_posEta__1up_isPassed, JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_truthlabel,
						   JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_subleadjet_truthlabel, JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_subleadjet_btagbin, JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_posEta__1up_yyHFjj_weight, JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_met,
						   JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_posEta__1up_m_yy);
				checkDijet(histbb_noMET_JET_EtaIntercalibration_TotalStat__1down, histbc_noMET_JET_EtaIntercalibration_TotalStat__1down, histbl_noMET_JET_EtaIntercalibration_TotalStat__1down, histcc_noMET_JET_EtaIntercalibration_TotalStat__1down, histcl_noMET_JET_EtaIntercalibration_TotalStat__1down, histll_noMET_JET_EtaIntercalibration_TotalStat__1down,
						   JET_EtaIntercalibration_TotalStat__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_TotalStat__1down_isPassed, JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_truthlabel,
						   JET_EtaIntercalibration_TotalStat__1down_yyHF_subleadjet_truthlabel, JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_btagbin, JET_EtaIntercalibration_TotalStat__1down_yyHF_subleadjet_btagbin, JET_EtaIntercalibration_TotalStat__1down_yyHF_Njet_central, JET_EtaIntercalibration_TotalStat__1down_yyHFjj_weight, JET_EtaIntercalibration_TotalStat__1down_yyHF_met,
						   JET_EtaIntercalibration_TotalStat__1down_yyHF_nelectron, JET_EtaIntercalibration_TotalStat__1down_yyHF_nmuon, JET_EtaIntercalibration_TotalStat__1down_m_yy);
				checkDijet(histbb_noMET_JET_EtaIntercalibration_TotalStat__1up, histbc_noMET_JET_EtaIntercalibration_TotalStat__1up, histbl_noMET_JET_EtaIntercalibration_TotalStat__1up, histcc_noMET_JET_EtaIntercalibration_TotalStat__1up, histcl_noMET_JET_EtaIntercalibration_TotalStat__1up, histll_noMET_JET_EtaIntercalibration_TotalStat__1up,
						   JET_EtaIntercalibration_TotalStat__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_TotalStat__1up_isPassed, JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_truthlabel,
						   JET_EtaIntercalibration_TotalStat__1up_yyHF_subleadjet_truthlabel, JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_btagbin, JET_EtaIntercalibration_TotalStat__1up_yyHF_subleadjet_btagbin, JET_EtaIntercalibration_TotalStat__1up_yyHF_Njet_central, JET_EtaIntercalibration_TotalStat__1up_yyHFjj_weight, JET_EtaIntercalibration_TotalStat__1up_yyHF_met,
						   JET_EtaIntercalibration_TotalStat__1up_yyHF_nelectron, JET_EtaIntercalibration_TotalStat__1up_yyHF_nmuon, JET_EtaIntercalibration_TotalStat__1up_m_yy);
				checkDijet(histbb_noMET_JET_fJvtEfficiency__1down, histbc_noMET_JET_fJvtEfficiency__1down, histbl_noMET_JET_fJvtEfficiency__1down, histcc_noMET_JET_fJvtEfficiency__1down, histcl_noMET_JET_fJvtEfficiency__1down, histll_noMET_JET_fJvtEfficiency__1down,
						   JET_fJvtEfficiency__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_fJvtEfficiency__1down_isPassed, JET_fJvtEfficiency__1down_yyHF_leadjet_truthlabel,
						   JET_fJvtEfficiency__1down_yyHF_subleadjet_truthlabel, JET_fJvtEfficiency__1down_yyHF_leadjet_btagbin, JET_fJvtEfficiency__1down_yyHF_subleadjet_btagbin, JET_fJvtEfficiency__1down_yyHF_Njet_central, JET_fJvtEfficiency__1down_yyHFjj_weight, JET_fJvtEfficiency__1down_yyHF_met,
						   JET_fJvtEfficiency__1down_yyHF_nelectron, JET_fJvtEfficiency__1down_yyHF_nmuon, JET_fJvtEfficiency__1down_m_yy);
				checkDijet(histbb_noMET_JET_fJvtEfficiency__1up, histbc_noMET_JET_fJvtEfficiency__1up, histbl_noMET_JET_fJvtEfficiency__1up, histcc_noMET_JET_fJvtEfficiency__1up, histcl_noMET_JET_fJvtEfficiency__1up, histll_noMET_JET_fJvtEfficiency__1up,
						   JET_fJvtEfficiency__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_fJvtEfficiency__1up_isPassed, JET_fJvtEfficiency__1up_yyHF_leadjet_truthlabel,
						   JET_fJvtEfficiency__1up_yyHF_subleadjet_truthlabel, JET_fJvtEfficiency__1up_yyHF_leadjet_btagbin, JET_fJvtEfficiency__1up_yyHF_subleadjet_btagbin, JET_fJvtEfficiency__1up_yyHF_Njet_central, JET_fJvtEfficiency__1up_yyHFjj_weight, JET_fJvtEfficiency__1up_yyHF_met,
						   JET_fJvtEfficiency__1up_yyHF_nelectron, JET_fJvtEfficiency__1up_yyHF_nmuon, JET_fJvtEfficiency__1up_m_yy);
				checkDijet(histbb_noMET_JET_Flavor_Composition__1down, histbc_noMET_JET_Flavor_Composition__1down, histbl_noMET_JET_Flavor_Composition__1down, histcc_noMET_JET_Flavor_Composition__1down, histcl_noMET_JET_Flavor_Composition__1down, histll_noMET_JET_Flavor_Composition__1down,
						   JET_Flavor_Composition__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Flavor_Composition__1down_isPassed, JET_Flavor_Composition__1down_yyHF_leadjet_truthlabel,
						   JET_Flavor_Composition__1down_yyHF_subleadjet_truthlabel, JET_Flavor_Composition__1down_yyHF_leadjet_btagbin, JET_Flavor_Composition__1down_yyHF_subleadjet_btagbin, JET_Flavor_Composition__1down_yyHF_Njet_central, JET_Flavor_Composition__1down_yyHFjj_weight, JET_Flavor_Composition__1down_yyHF_met,
						   JET_Flavor_Composition__1down_yyHF_nelectron, JET_Flavor_Composition__1down_yyHF_nmuon, JET_Flavor_Composition__1down_m_yy);
				checkDijet(histbb_noMET_JET_Flavor_Composition__1up, histbc_noMET_JET_Flavor_Composition__1up, histbl_noMET_JET_Flavor_Composition__1up, histcc_noMET_JET_Flavor_Composition__1up, histcl_noMET_JET_Flavor_Composition__1up, histll_noMET_JET_Flavor_Composition__1up,
						   JET_Flavor_Composition__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Flavor_Composition__1up_isPassed, JET_Flavor_Composition__1up_yyHF_leadjet_truthlabel,
						   JET_Flavor_Composition__1up_yyHF_subleadjet_truthlabel, JET_Flavor_Composition__1up_yyHF_leadjet_btagbin, JET_Flavor_Composition__1up_yyHF_subleadjet_btagbin, JET_Flavor_Composition__1up_yyHF_Njet_central, JET_Flavor_Composition__1up_yyHFjj_weight, JET_Flavor_Composition__1up_yyHF_met,
						   JET_Flavor_Composition__1up_yyHF_nelectron, JET_Flavor_Composition__1up_yyHF_nmuon, JET_Flavor_Composition__1up_m_yy);
				checkDijet(histbb_noMET_JET_Flavor_Response__1down, histbc_noMET_JET_Flavor_Response__1down, histbl_noMET_JET_Flavor_Response__1down, histcc_noMET_JET_Flavor_Response__1down, histcl_noMET_JET_Flavor_Response__1down, histll_noMET_JET_Flavor_Response__1down,
						   JET_Flavor_Response__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Flavor_Response__1down_isPassed, JET_Flavor_Response__1down_yyHF_leadjet_truthlabel,
						   JET_Flavor_Response__1down_yyHF_subleadjet_truthlabel, JET_Flavor_Response__1down_yyHF_leadjet_btagbin, JET_Flavor_Response__1down_yyHF_subleadjet_btagbin, JET_Flavor_Response__1down_yyHF_Njet_central, JET_Flavor_Response__1down_yyHFjj_weight, JET_Flavor_Response__1down_yyHF_met,
						   JET_Flavor_Response__1down_yyHF_nelectron, JET_Flavor_Response__1down_yyHF_nmuon, JET_Flavor_Response__1down_m_yy);
				checkDijet(histbb_noMET_JET_Flavor_Response__1up, histbc_noMET_JET_Flavor_Response__1up, histbl_noMET_JET_Flavor_Response__1up, histcc_noMET_JET_Flavor_Response__1up, histcl_noMET_JET_Flavor_Response__1up, histll_noMET_JET_Flavor_Response__1up,
						   JET_Flavor_Response__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Flavor_Response__1up_isPassed, JET_Flavor_Response__1up_yyHF_leadjet_truthlabel,
						   JET_Flavor_Response__1up_yyHF_subleadjet_truthlabel, JET_Flavor_Response__1up_yyHF_leadjet_btagbin, JET_Flavor_Response__1up_yyHF_subleadjet_btagbin, JET_Flavor_Response__1up_yyHF_Njet_central, JET_Flavor_Response__1up_yyHFjj_weight, JET_Flavor_Response__1up_yyHF_met,
						   JET_Flavor_Response__1up_yyHF_nelectron, JET_Flavor_Response__1up_yyHF_nmuon, JET_Flavor_Response__1up_m_yy);
				checkDijet(histbb_noMET_JET_JvtEfficiency__1down, histbc_noMET_JET_JvtEfficiency__1down, histbl_noMET_JET_JvtEfficiency__1down, histcc_noMET_JET_JvtEfficiency__1down, histcl_noMET_JET_JvtEfficiency__1down, histll_noMET_JET_JvtEfficiency__1down,
						   JET_JvtEfficiency__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_JvtEfficiency__1down_isPassed, JET_JvtEfficiency__1down_yyHF_leadjet_truthlabel,
						   JET_JvtEfficiency__1down_yyHF_subleadjet_truthlabel, JET_JvtEfficiency__1down_yyHF_leadjet_btagbin, JET_JvtEfficiency__1down_yyHF_subleadjet_btagbin, JET_JvtEfficiency__1down_yyHF_Njet_central, JET_JvtEfficiency__1down_yyHFjj_weight, JET_JvtEfficiency__1down_yyHF_met,
						   JET_JvtEfficiency__1down_yyHF_nelectron, JET_JvtEfficiency__1down_yyHF_nmuon, JET_JvtEfficiency__1down_m_yy);
				checkDijet(histbb_noMET_JET_JvtEfficiency__1up, histbc_noMET_JET_JvtEfficiency__1up, histbl_noMET_JET_JvtEfficiency__1up, histcc_noMET_JET_JvtEfficiency__1up, histcl_noMET_JET_JvtEfficiency__1up, histll_noMET_JET_JvtEfficiency__1up,
						   JET_JvtEfficiency__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_JvtEfficiency__1up_isPassed, JET_JvtEfficiency__1up_yyHF_leadjet_truthlabel,
						   JET_JvtEfficiency__1up_yyHF_subleadjet_truthlabel, JET_JvtEfficiency__1up_yyHF_leadjet_btagbin, JET_JvtEfficiency__1up_yyHF_subleadjet_btagbin, JET_JvtEfficiency__1up_yyHF_Njet_central, JET_JvtEfficiency__1up_yyHFjj_weight, JET_JvtEfficiency__1up_yyHF_met,
						   JET_JvtEfficiency__1up_yyHF_nelectron, JET_JvtEfficiency__1up_yyHF_nmuon, JET_JvtEfficiency__1up_m_yy);
				checkDijet(histbb_noMET_JET_Pileup_OffsetMu__1down, histbc_noMET_JET_Pileup_OffsetMu__1down, histbl_noMET_JET_Pileup_OffsetMu__1down, histcc_noMET_JET_Pileup_OffsetMu__1down, histcl_noMET_JET_Pileup_OffsetMu__1down, histll_noMET_JET_Pileup_OffsetMu__1down,
						   JET_Pileup_OffsetMu__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_OffsetMu__1down_isPassed, JET_Pileup_OffsetMu__1down_yyHF_leadjet_truthlabel,
						   JET_Pileup_OffsetMu__1down_yyHF_subleadjet_truthlabel, JET_Pileup_OffsetMu__1down_yyHF_leadjet_btagbin, JET_Pileup_OffsetMu__1down_yyHF_subleadjet_btagbin, JET_Pileup_OffsetMu__1down_yyHF_Njet_central, JET_Pileup_OffsetMu__1down_yyHFjj_weight, JET_Pileup_OffsetMu__1down_yyHF_met,
						   JET_Pileup_OffsetMu__1down_yyHF_nelectron, JET_Pileup_OffsetMu__1down_yyHF_nmuon, JET_Pileup_OffsetMu__1down_m_yy);
				checkDijet(histbb_noMET_JET_Pileup_OffsetMu__1up, histbc_noMET_JET_Pileup_OffsetMu__1up, histbl_noMET_JET_Pileup_OffsetMu__1up, histcc_noMET_JET_Pileup_OffsetMu__1up, histcl_noMET_JET_Pileup_OffsetMu__1up, histll_noMET_JET_Pileup_OffsetMu__1up,
						   JET_Pileup_OffsetMu__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_OffsetMu__1up_isPassed, JET_Pileup_OffsetMu__1up_yyHF_leadjet_truthlabel,
						   JET_Pileup_OffsetMu__1up_yyHF_subleadjet_truthlabel, JET_Pileup_OffsetMu__1up_yyHF_leadjet_btagbin, JET_Pileup_OffsetMu__1up_yyHF_subleadjet_btagbin, JET_Pileup_OffsetMu__1up_yyHF_Njet_central, JET_Pileup_OffsetMu__1up_yyHFjj_weight, JET_Pileup_OffsetMu__1up_yyHF_met,
						   JET_Pileup_OffsetMu__1up_yyHF_nelectron, JET_Pileup_OffsetMu__1up_yyHF_nmuon, JET_Pileup_OffsetMu__1up_m_yy);
				checkDijet(histbb_noMET_JET_Pileup_OffsetNPV__1down, histbc_noMET_JET_Pileup_OffsetNPV__1down, histbl_noMET_JET_Pileup_OffsetNPV__1down, histcc_noMET_JET_Pileup_OffsetNPV__1down, histcl_noMET_JET_Pileup_OffsetNPV__1down, histll_noMET_JET_Pileup_OffsetNPV__1down,
						   JET_Pileup_OffsetNPV__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_OffsetNPV__1down_isPassed, JET_Pileup_OffsetNPV__1down_yyHF_leadjet_truthlabel,
						   JET_Pileup_OffsetNPV__1down_yyHF_subleadjet_truthlabel, JET_Pileup_OffsetNPV__1down_yyHF_leadjet_btagbin, JET_Pileup_OffsetNPV__1down_yyHF_subleadjet_btagbin, JET_Pileup_OffsetNPV__1down_yyHF_Njet_central, JET_Pileup_OffsetNPV__1down_yyHFjj_weight, JET_Pileup_OffsetNPV__1down_yyHF_met,
						   JET_Pileup_OffsetNPV__1down_yyHF_nelectron, JET_Pileup_OffsetNPV__1down_yyHF_nmuon, JET_Pileup_OffsetNPV__1down_m_yy);
				checkDijet(histbb_noMET_JET_Pileup_OffsetNPV__1up, histbc_noMET_JET_Pileup_OffsetNPV__1up, histbl_noMET_JET_Pileup_OffsetNPV__1up, histcc_noMET_JET_Pileup_OffsetNPV__1up, histcl_noMET_JET_Pileup_OffsetNPV__1up, histll_noMET_JET_Pileup_OffsetNPV__1up,
						   JET_Pileup_OffsetNPV__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_OffsetNPV__1up_isPassed, JET_Pileup_OffsetNPV__1up_yyHF_leadjet_truthlabel,
						   JET_Pileup_OffsetNPV__1up_yyHF_subleadjet_truthlabel, JET_Pileup_OffsetNPV__1up_yyHF_leadjet_btagbin, JET_Pileup_OffsetNPV__1up_yyHF_subleadjet_btagbin, JET_Pileup_OffsetNPV__1up_yyHF_Njet_central, JET_Pileup_OffsetNPV__1up_yyHFjj_weight, JET_Pileup_OffsetNPV__1up_yyHF_met,
						   JET_Pileup_OffsetNPV__1up_yyHF_nelectron, JET_Pileup_OffsetNPV__1up_yyHF_nmuon, JET_Pileup_OffsetNPV__1up_m_yy);
				checkDijet(histbb_noMET_JET_Pileup_PtTerm__1down, histbc_noMET_JET_Pileup_PtTerm__1down, histbl_noMET_JET_Pileup_PtTerm__1down, histcc_noMET_JET_Pileup_PtTerm__1down, histcl_noMET_JET_Pileup_PtTerm__1down, histll_noMET_JET_Pileup_PtTerm__1down,
						   JET_Pileup_PtTerm__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_PtTerm__1down_isPassed, JET_Pileup_PtTerm__1down_yyHF_leadjet_truthlabel,
						   JET_Pileup_PtTerm__1down_yyHF_subleadjet_truthlabel, JET_Pileup_PtTerm__1down_yyHF_leadjet_btagbin, JET_Pileup_PtTerm__1down_yyHF_subleadjet_btagbin, JET_Pileup_PtTerm__1down_yyHF_Njet_central, JET_Pileup_PtTerm__1down_yyHFjj_weight, JET_Pileup_PtTerm__1down_yyHF_met,
						   JET_Pileup_PtTerm__1down_yyHF_nelectron, JET_Pileup_PtTerm__1down_yyHF_nmuon, JET_Pileup_PtTerm__1down_m_yy);
				checkDijet(histbb_noMET_JET_Pileup_PtTerm__1up, histbc_noMET_JET_Pileup_PtTerm__1up, histbl_noMET_JET_Pileup_PtTerm__1up, histcc_noMET_JET_Pileup_PtTerm__1up, histcl_noMET_JET_Pileup_PtTerm__1up, histll_noMET_JET_Pileup_PtTerm__1up,
						   JET_Pileup_PtTerm__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_PtTerm__1up_isPassed, JET_Pileup_PtTerm__1up_yyHF_leadjet_truthlabel,
						   JET_Pileup_PtTerm__1up_yyHF_subleadjet_truthlabel, JET_Pileup_PtTerm__1up_yyHF_leadjet_btagbin, JET_Pileup_PtTerm__1up_yyHF_subleadjet_btagbin, JET_Pileup_PtTerm__1up_yyHF_Njet_central, JET_Pileup_PtTerm__1up_yyHFjj_weight, JET_Pileup_PtTerm__1up_yyHF_met,
						   JET_Pileup_PtTerm__1up_yyHF_nelectron, JET_Pileup_PtTerm__1up_yyHF_nmuon, JET_Pileup_PtTerm__1up_m_yy);
				checkDijet(histbb_noMET_JET_Pileup_RhoTopology__1down, histbc_noMET_JET_Pileup_RhoTopology__1down, histbl_noMET_JET_Pileup_RhoTopology__1down, histcc_noMET_JET_Pileup_RhoTopology__1down, histcl_noMET_JET_Pileup_RhoTopology__1down, histll_noMET_JET_Pileup_RhoTopology__1down,
						   JET_Pileup_RhoTopology__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_RhoTopology__1down_isPassed, JET_Pileup_RhoTopology__1down_yyHF_leadjet_truthlabel,
						   JET_Pileup_RhoTopology__1down_yyHF_subleadjet_truthlabel, JET_Pileup_RhoTopology__1down_yyHF_leadjet_btagbin, JET_Pileup_RhoTopology__1down_yyHF_subleadjet_btagbin, JET_Pileup_RhoTopology__1down_yyHF_Njet_central, JET_Pileup_RhoTopology__1down_yyHFjj_weight, JET_Pileup_RhoTopology__1down_yyHF_met,
						   JET_Pileup_RhoTopology__1down_yyHF_nelectron, JET_Pileup_RhoTopology__1down_yyHF_nmuon, JET_Pileup_RhoTopology__1down_m_yy);
				checkDijet(histbb_noMET_JET_Pileup_RhoTopology__1up, histbc_noMET_JET_Pileup_RhoTopology__1up, histbl_noMET_JET_Pileup_RhoTopology__1up, histcc_noMET_JET_Pileup_RhoTopology__1up, histcl_noMET_JET_Pileup_RhoTopology__1up, histll_noMET_JET_Pileup_RhoTopology__1up,
						   JET_Pileup_RhoTopology__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_RhoTopology__1up_isPassed, JET_Pileup_RhoTopology__1up_yyHF_leadjet_truthlabel,
						   JET_Pileup_RhoTopology__1up_yyHF_subleadjet_truthlabel, JET_Pileup_RhoTopology__1up_yyHF_leadjet_btagbin, JET_Pileup_RhoTopology__1up_yyHF_subleadjet_btagbin, JET_Pileup_RhoTopology__1up_yyHF_Njet_central, JET_Pileup_RhoTopology__1up_yyHFjj_weight, JET_Pileup_RhoTopology__1up_yyHF_met,
						   JET_Pileup_RhoTopology__1up_yyHF_nelectron, JET_Pileup_RhoTopology__1up_yyHF_nmuon, JET_Pileup_RhoTopology__1up_m_yy);
				checkDijet(histbb_noMET_JET_SingleParticle_HighPt__1down, histbc_noMET_JET_SingleParticle_HighPt__1down, histbl_noMET_JET_SingleParticle_HighPt__1down, histcc_noMET_JET_SingleParticle_HighPt__1down, histcl_noMET_JET_SingleParticle_HighPt__1down, histll_noMET_JET_SingleParticle_HighPt__1down,
						   JET_SingleParticle_HighPt__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_SingleParticle_HighPt__1down_isPassed, JET_SingleParticle_HighPt__1down_yyHF_leadjet_truthlabel,
						   JET_SingleParticle_HighPt__1down_yyHF_subleadjet_truthlabel, JET_SingleParticle_HighPt__1down_yyHF_leadjet_btagbin, JET_SingleParticle_HighPt__1down_yyHF_subleadjet_btagbin, JET_SingleParticle_HighPt__1down_yyHF_Njet_central, JET_SingleParticle_HighPt__1down_yyHFjj_weight, JET_SingleParticle_HighPt__1down_yyHF_met,
						   JET_SingleParticle_HighPt__1down_yyHF_nelectron, JET_SingleParticle_HighPt__1down_yyHF_nmuon, JET_SingleParticle_HighPt__1down_m_yy);
				checkDijet(histbb_noMET_JET_SingleParticle_HighPt__1up, histbc_noMET_JET_SingleParticle_HighPt__1up, histbl_noMET_JET_SingleParticle_HighPt__1up, histcc_noMET_JET_SingleParticle_HighPt__1up, histcl_noMET_JET_SingleParticle_HighPt__1up, histll_noMET_JET_SingleParticle_HighPt__1up,
						   JET_SingleParticle_HighPt__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_SingleParticle_HighPt__1up_isPassed, JET_SingleParticle_HighPt__1up_yyHF_leadjet_truthlabel,
						   JET_SingleParticle_HighPt__1up_yyHF_subleadjet_truthlabel, JET_SingleParticle_HighPt__1up_yyHF_leadjet_btagbin, JET_SingleParticle_HighPt__1up_yyHF_subleadjet_btagbin, JET_SingleParticle_HighPt__1up_yyHF_Njet_central, JET_SingleParticle_HighPt__1up_yyHFjj_weight, JET_SingleParticle_HighPt__1up_yyHF_met,
						   JET_SingleParticle_HighPt__1up_yyHF_nelectron, JET_SingleParticle_HighPt__1up_yyHF_nmuon, JET_SingleParticle_HighPt__1up_m_yy);


				 checkSingleJet(histb_noMET_JET_BJES_Response__1down, histc_noMET_JET_BJES_Response__1down, histl_noMET_JET_BJES_Response__1down,
				 		   JET_BJES_Response__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_BJES_Response__1down_isPassed, JET_BJES_Response__1down_yyHF_leadjet_truthlabel,
				 		   JET_BJES_Response__1down_yyHF_leadjet_btagbin, JET_BJES_Response__1down_yyHF_Njet_central, JET_BJES_Response__1down_yyHFj_weight, JET_BJES_Response__1down_yyHF_met,
				 		   JET_BJES_Response__1down_yyHF_nelectron, JET_BJES_Response__1down_yyHF_nmuon, JET_BJES_Response__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_BJES_Response__1up, histc_noMET_JET_BJES_Response__1up, histl_noMET_JET_BJES_Response__1up,
				 		   JET_BJES_Response__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_BJES_Response__1up_isPassed, JET_BJES_Response__1up_yyHF_leadjet_truthlabel,
				 		   JET_BJES_Response__1up_yyHF_leadjet_btagbin, JET_BJES_Response__1up_yyHF_Njet_central, JET_BJES_Response__1up_yyHFj_weight, JET_BJES_Response__1up_yyHF_met,
				 		   JET_BJES_Response__1up_yyHF_nelectron, JET_BJES_Response__1up_yyHF_nmuon, JET_BJES_Response__1up_m_yy);
				 checkSingleJet(histb_noMET_JET_EtaIntercalibration_Modelling__1down, histc_noMET_JET_EtaIntercalibration_Modelling__1down, histl_noMET_JET_EtaIntercalibration_Modelling__1down,
				 		   JET_EtaIntercalibration_Modelling__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_Modelling__1down_isPassed, JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_truthlabel,
				 		   JET_EtaIntercalibration_Modelling__1down_yyHF_leadjet_btagbin, JET_EtaIntercalibration_Modelling__1down_yyHF_Njet_central, JET_EtaIntercalibration_Modelling__1down_yyHFj_weight, JET_EtaIntercalibration_Modelling__1down_yyHF_met,
				 		   JET_EtaIntercalibration_Modelling__1down_yyHF_nelectron, JET_EtaIntercalibration_Modelling__1down_yyHF_nmuon, JET_EtaIntercalibration_Modelling__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_EtaIntercalibration_Modelling__1up, histc_noMET_JET_EtaIntercalibration_Modelling__1up, histl_noMET_JET_EtaIntercalibration_Modelling__1up,
				 		   JET_EtaIntercalibration_Modelling__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_Modelling__1up_isPassed, JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_truthlabel,
				 		   JET_EtaIntercalibration_Modelling__1up_yyHF_leadjet_btagbin, JET_EtaIntercalibration_Modelling__1up_yyHF_Njet_central, JET_EtaIntercalibration_Modelling__1up_yyHFj_weight, JET_EtaIntercalibration_Modelling__1up_yyHF_met,
				 		   JET_EtaIntercalibration_Modelling__1up_yyHF_nelectron, JET_EtaIntercalibration_Modelling__1up_yyHF_nmuon, JET_EtaIntercalibration_Modelling__1up_m_yy);
				 checkSingleJet(histb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down, histc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down, histl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down,
				 		   JET_EtaIntercalibration_NonClosure_2018data__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_2018data__1down_isPassed, JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_truthlabel,
				 		   JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_2018data__1down_yyHFj_weight, JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_met,
				 		   JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_2018data__1down_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_2018data__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up, histc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up, histl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up,
				 		   JET_EtaIntercalibration_NonClosure_2018data__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_2018data__1up_isPassed, JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_truthlabel,
				 		   JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_2018data__1up_yyHFj_weight, JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_met,
				 		   JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_2018data__1up_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_2018data__1up_m_yy);
				 checkSingleJet(histb_noMET_JET_EtaIntercalibration_NonClosure_highE__1down, histc_noMET_JET_EtaIntercalibration_NonClosure_highE__1down, histl_noMET_JET_EtaIntercalibration_NonClosure_highE__1down,
				 		   JET_EtaIntercalibration_NonClosure_highE__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_highE__1down_isPassed, JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_truthlabel,
				 		   JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_highE__1down_yyHFj_weight, JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_met,
				 		   JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_highE__1down_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_highE__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_EtaIntercalibration_NonClosure_highE__1up, histc_noMET_JET_EtaIntercalibration_NonClosure_highE__1up, histl_noMET_JET_EtaIntercalibration_NonClosure_highE__1up,
				 		   JET_EtaIntercalibration_NonClosure_highE__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_highE__1up_isPassed, JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_truthlabel,
				 		   JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_highE__1up_yyHFj_weight, JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_met,
				 		   JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_highE__1up_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_highE__1up_m_yy);
				 checkSingleJet(histb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down, histc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down, histl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down,
				 		   JET_EtaIntercalibration_NonClosure_negEta__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_negEta__1down_isPassed, JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_truthlabel,
				 		   JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_negEta__1down_yyHFj_weight, JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_met,
				 		   JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_negEta__1down_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_negEta__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up, histc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up, histl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up,
				 		   JET_EtaIntercalibration_NonClosure_negEta__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_negEta__1up_isPassed, JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_truthlabel,
				 		   JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_negEta__1up_yyHFj_weight, JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_met,
				 		   JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_negEta__1up_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_negEta__1up_m_yy);
				 checkSingleJet(histb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down, histc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down, histl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down,
				 		   JET_EtaIntercalibration_NonClosure_posEta__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_posEta__1down_isPassed, JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_truthlabel,
				 		   JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_posEta__1down_yyHFj_weight, JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_met,
				 		   JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_posEta__1down_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_posEta__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up, histc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up, histl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up,
				 		   JET_EtaIntercalibration_NonClosure_posEta__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_NonClosure_posEta__1up_isPassed, JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_truthlabel,
				 		   JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_leadjet_btagbin, JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_Njet_central, JET_EtaIntercalibration_NonClosure_posEta__1up_yyHFj_weight, JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_met,
				 		   JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_nelectron, JET_EtaIntercalibration_NonClosure_posEta__1up_yyHF_nmuon, JET_EtaIntercalibration_NonClosure_posEta__1up_m_yy);
				 checkSingleJet(histb_noMET_JET_EtaIntercalibration_TotalStat__1down, histc_noMET_JET_EtaIntercalibration_TotalStat__1down, histl_noMET_JET_EtaIntercalibration_TotalStat__1down,
				 		   JET_EtaIntercalibration_TotalStat__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_TotalStat__1down_isPassed, JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_truthlabel,
				 		   JET_EtaIntercalibration_TotalStat__1down_yyHF_leadjet_btagbin, JET_EtaIntercalibration_TotalStat__1down_yyHF_Njet_central, JET_EtaIntercalibration_TotalStat__1down_yyHFj_weight, JET_EtaIntercalibration_TotalStat__1down_yyHF_met,
				 		   JET_EtaIntercalibration_TotalStat__1down_yyHF_nelectron, JET_EtaIntercalibration_TotalStat__1down_yyHF_nmuon, JET_EtaIntercalibration_TotalStat__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_EtaIntercalibration_TotalStat__1up, histc_noMET_JET_EtaIntercalibration_TotalStat__1up, histl_noMET_JET_EtaIntercalibration_TotalStat__1up,
				 		   JET_EtaIntercalibration_TotalStat__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_EtaIntercalibration_TotalStat__1up_isPassed, JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_truthlabel,
				 		   JET_EtaIntercalibration_TotalStat__1up_yyHF_leadjet_btagbin, JET_EtaIntercalibration_TotalStat__1up_yyHF_Njet_central, JET_EtaIntercalibration_TotalStat__1up_yyHFj_weight, JET_EtaIntercalibration_TotalStat__1up_yyHF_met,
				 		   JET_EtaIntercalibration_TotalStat__1up_yyHF_nelectron, JET_EtaIntercalibration_TotalStat__1up_yyHF_nmuon, JET_EtaIntercalibration_TotalStat__1up_m_yy);
				 checkSingleJet(histb_noMET_JET_fJvtEfficiency__1down, histc_noMET_JET_fJvtEfficiency__1down, histl_noMET_JET_fJvtEfficiency__1down,
				 		   JET_fJvtEfficiency__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_fJvtEfficiency__1down_isPassed, JET_fJvtEfficiency__1down_yyHF_leadjet_truthlabel,
				 		   JET_fJvtEfficiency__1down_yyHF_leadjet_btagbin, JET_fJvtEfficiency__1down_yyHF_Njet_central, JET_fJvtEfficiency__1down_yyHFj_weight, JET_fJvtEfficiency__1down_yyHF_met,
				 		   JET_fJvtEfficiency__1down_yyHF_nelectron, JET_fJvtEfficiency__1down_yyHF_nmuon, JET_fJvtEfficiency__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_fJvtEfficiency__1up, histc_noMET_JET_fJvtEfficiency__1up, histl_noMET_JET_fJvtEfficiency__1up,
				 		   JET_fJvtEfficiency__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_fJvtEfficiency__1up_isPassed, JET_fJvtEfficiency__1up_yyHF_leadjet_truthlabel,
				 		   JET_fJvtEfficiency__1up_yyHF_leadjet_btagbin, JET_fJvtEfficiency__1up_yyHF_Njet_central, JET_fJvtEfficiency__1up_yyHFj_weight, JET_fJvtEfficiency__1up_yyHF_met,
				 		   JET_fJvtEfficiency__1up_yyHF_nelectron, JET_fJvtEfficiency__1up_yyHF_nmuon, JET_fJvtEfficiency__1up_m_yy);
				 checkSingleJet(histb_noMET_JET_Flavor_Composition__1down, histc_noMET_JET_Flavor_Composition__1down, histl_noMET_JET_Flavor_Composition__1down,
				 		   JET_Flavor_Composition__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Flavor_Composition__1down_isPassed, JET_Flavor_Composition__1down_yyHF_leadjet_truthlabel,
				 		   JET_Flavor_Composition__1down_yyHF_leadjet_btagbin, JET_Flavor_Composition__1down_yyHF_Njet_central, JET_Flavor_Composition__1down_yyHFj_weight, JET_Flavor_Composition__1down_yyHF_met,
				 		   JET_Flavor_Composition__1down_yyHF_nelectron, JET_Flavor_Composition__1down_yyHF_nmuon, JET_Flavor_Composition__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_Flavor_Composition__1up, histc_noMET_JET_Flavor_Composition__1up, histl_noMET_JET_Flavor_Composition__1up,
				 		   JET_Flavor_Composition__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Flavor_Composition__1up_isPassed, JET_Flavor_Composition__1up_yyHF_leadjet_truthlabel,
				 		   JET_Flavor_Composition__1up_yyHF_leadjet_btagbin, JET_Flavor_Composition__1up_yyHF_Njet_central, JET_Flavor_Composition__1up_yyHFj_weight, JET_Flavor_Composition__1up_yyHF_met,
				 		   JET_Flavor_Composition__1up_yyHF_nelectron, JET_Flavor_Composition__1up_yyHF_nmuon, JET_Flavor_Composition__1up_m_yy);
				 checkSingleJet(histb_noMET_JET_Flavor_Response__1down, histc_noMET_JET_Flavor_Response__1down, histl_noMET_JET_Flavor_Response__1down,
				 		   JET_Flavor_Response__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Flavor_Response__1down_isPassed, JET_Flavor_Response__1down_yyHF_leadjet_truthlabel,
				 		   JET_Flavor_Response__1down_yyHF_leadjet_btagbin, JET_Flavor_Response__1down_yyHF_Njet_central, JET_Flavor_Response__1down_yyHFj_weight, JET_Flavor_Response__1down_yyHF_met,
				 		   JET_Flavor_Response__1down_yyHF_nelectron, JET_Flavor_Response__1down_yyHF_nmuon, JET_Flavor_Response__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_Flavor_Response__1up, histc_noMET_JET_Flavor_Response__1up, histl_noMET_JET_Flavor_Response__1up,
				 		   JET_Flavor_Response__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Flavor_Response__1up_isPassed, JET_Flavor_Response__1up_yyHF_leadjet_truthlabel,
				 		   JET_Flavor_Response__1up_yyHF_leadjet_btagbin, JET_Flavor_Response__1up_yyHF_Njet_central, JET_Flavor_Response__1up_yyHFj_weight, JET_Flavor_Response__1up_yyHF_met,
				 		   JET_Flavor_Response__1up_yyHF_nelectron, JET_Flavor_Response__1up_yyHF_nmuon, JET_Flavor_Response__1up_m_yy);
				 checkSingleJet(histb_noMET_JET_JvtEfficiency__1down, histc_noMET_JET_JvtEfficiency__1down, histl_noMET_JET_JvtEfficiency__1down,
				 		   JET_JvtEfficiency__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_JvtEfficiency__1down_isPassed, JET_JvtEfficiency__1down_yyHF_leadjet_truthlabel,
				 		   JET_JvtEfficiency__1down_yyHF_leadjet_btagbin, JET_JvtEfficiency__1down_yyHF_Njet_central, JET_JvtEfficiency__1down_yyHFj_weight, JET_JvtEfficiency__1down_yyHF_met,
				 		   JET_JvtEfficiency__1down_yyHF_nelectron, JET_JvtEfficiency__1down_yyHF_nmuon, JET_JvtEfficiency__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_JvtEfficiency__1up, histc_noMET_JET_JvtEfficiency__1up, histl_noMET_JET_JvtEfficiency__1up,
				 		   JET_JvtEfficiency__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_JvtEfficiency__1up_isPassed, JET_JvtEfficiency__1up_yyHF_leadjet_truthlabel,
				 		   JET_JvtEfficiency__1up_yyHF_leadjet_btagbin, JET_JvtEfficiency__1up_yyHF_Njet_central, JET_JvtEfficiency__1up_yyHFj_weight, JET_JvtEfficiency__1up_yyHF_met,
				 		   JET_JvtEfficiency__1up_yyHF_nelectron, JET_JvtEfficiency__1up_yyHF_nmuon, JET_JvtEfficiency__1up_m_yy);
				 checkSingleJet(histb_noMET_JET_Pileup_OffsetMu__1down, histc_noMET_JET_Pileup_OffsetMu__1down, histl_noMET_JET_Pileup_OffsetMu__1down,
				 		   JET_Pileup_OffsetMu__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_OffsetMu__1down_isPassed, JET_Pileup_OffsetMu__1down_yyHF_leadjet_truthlabel,
				 		   JET_Pileup_OffsetMu__1down_yyHF_leadjet_btagbin, JET_Pileup_OffsetMu__1down_yyHF_Njet_central, JET_Pileup_OffsetMu__1down_yyHFj_weight, JET_Pileup_OffsetMu__1down_yyHF_met,
				 		   JET_Pileup_OffsetMu__1down_yyHF_nelectron, JET_Pileup_OffsetMu__1down_yyHF_nmuon, JET_Pileup_OffsetMu__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_Pileup_OffsetMu__1up, histc_noMET_JET_Pileup_OffsetMu__1up, histl_noMET_JET_Pileup_OffsetMu__1up,
				 		   JET_Pileup_OffsetMu__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_OffsetMu__1up_isPassed, JET_Pileup_OffsetMu__1up_yyHF_leadjet_truthlabel,
				 		   JET_Pileup_OffsetMu__1up_yyHF_leadjet_btagbin, JET_Pileup_OffsetMu__1up_yyHF_Njet_central, JET_Pileup_OffsetMu__1up_yyHFj_weight, JET_Pileup_OffsetMu__1up_yyHF_met,
				 		   JET_Pileup_OffsetMu__1up_yyHF_nelectron, JET_Pileup_OffsetMu__1up_yyHF_nmuon, JET_Pileup_OffsetMu__1up_m_yy);
				 checkSingleJet(histb_noMET_JET_Pileup_OffsetNPV__1down, histc_noMET_JET_Pileup_OffsetNPV__1down, histl_noMET_JET_Pileup_OffsetNPV__1down,
				 		   JET_Pileup_OffsetNPV__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_OffsetNPV__1down_isPassed, JET_Pileup_OffsetNPV__1down_yyHF_leadjet_truthlabel,
				 		   JET_Pileup_OffsetNPV__1down_yyHF_leadjet_btagbin, JET_Pileup_OffsetNPV__1down_yyHF_Njet_central, JET_Pileup_OffsetNPV__1down_yyHFj_weight, JET_Pileup_OffsetNPV__1down_yyHF_met,
				 		   JET_Pileup_OffsetNPV__1down_yyHF_nelectron, JET_Pileup_OffsetNPV__1down_yyHF_nmuon, JET_Pileup_OffsetNPV__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_Pileup_OffsetNPV__1up, histc_noMET_JET_Pileup_OffsetNPV__1up, histl_noMET_JET_Pileup_OffsetNPV__1up,
				 		   JET_Pileup_OffsetNPV__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_OffsetNPV__1up_isPassed, JET_Pileup_OffsetNPV__1up_yyHF_leadjet_truthlabel,
				 		   JET_Pileup_OffsetNPV__1up_yyHF_leadjet_btagbin, JET_Pileup_OffsetNPV__1up_yyHF_Njet_central, JET_Pileup_OffsetNPV__1up_yyHFj_weight, JET_Pileup_OffsetNPV__1up_yyHF_met,
				 		   JET_Pileup_OffsetNPV__1up_yyHF_nelectron, JET_Pileup_OffsetNPV__1up_yyHF_nmuon, JET_Pileup_OffsetNPV__1up_m_yy);
				 checkSingleJet(histb_noMET_JET_Pileup_PtTerm__1down, histc_noMET_JET_Pileup_PtTerm__1down, histl_noMET_JET_Pileup_PtTerm__1down,
				 		   JET_Pileup_PtTerm__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_PtTerm__1down_isPassed, JET_Pileup_PtTerm__1down_yyHF_leadjet_truthlabel,
				 		   JET_Pileup_PtTerm__1down_yyHF_leadjet_btagbin, JET_Pileup_PtTerm__1down_yyHF_Njet_central, JET_Pileup_PtTerm__1down_yyHFj_weight, JET_Pileup_PtTerm__1down_yyHF_met,
				 		   JET_Pileup_PtTerm__1down_yyHF_nelectron, JET_Pileup_PtTerm__1down_yyHF_nmuon, JET_Pileup_PtTerm__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_Pileup_PtTerm__1up, histc_noMET_JET_Pileup_PtTerm__1up, histl_noMET_JET_Pileup_PtTerm__1up,
				 		   JET_Pileup_PtTerm__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_PtTerm__1up_isPassed, JET_Pileup_PtTerm__1up_yyHF_leadjet_truthlabel,
				 		   JET_Pileup_PtTerm__1up_yyHF_leadjet_btagbin, JET_Pileup_PtTerm__1up_yyHF_Njet_central, JET_Pileup_PtTerm__1up_yyHFj_weight, JET_Pileup_PtTerm__1up_yyHF_met,
				 		   JET_Pileup_PtTerm__1up_yyHF_nelectron, JET_Pileup_PtTerm__1up_yyHF_nmuon, JET_Pileup_PtTerm__1up_m_yy);
				 checkSingleJet(histb_noMET_JET_Pileup_RhoTopology__1down, histc_noMET_JET_Pileup_RhoTopology__1down, histl_noMET_JET_Pileup_RhoTopology__1down,
				 		   JET_Pileup_RhoTopology__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_RhoTopology__1down_isPassed, JET_Pileup_RhoTopology__1down_yyHF_leadjet_truthlabel,
				 		   JET_Pileup_RhoTopology__1down_yyHF_leadjet_btagbin, JET_Pileup_RhoTopology__1down_yyHF_Njet_central, JET_Pileup_RhoTopology__1down_yyHFj_weight, JET_Pileup_RhoTopology__1down_yyHF_met,
				 		   JET_Pileup_RhoTopology__1down_yyHF_nelectron, JET_Pileup_RhoTopology__1down_yyHF_nmuon, JET_Pileup_RhoTopology__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_Pileup_RhoTopology__1up, histc_noMET_JET_Pileup_RhoTopology__1up, histl_noMET_JET_Pileup_RhoTopology__1up,
				 		   JET_Pileup_RhoTopology__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_Pileup_RhoTopology__1up_isPassed, JET_Pileup_RhoTopology__1up_yyHF_leadjet_truthlabel,
				 		   JET_Pileup_RhoTopology__1up_yyHF_leadjet_btagbin, JET_Pileup_RhoTopology__1up_yyHF_Njet_central, JET_Pileup_RhoTopology__1up_yyHFj_weight, JET_Pileup_RhoTopology__1up_yyHF_met,
				 		   JET_Pileup_RhoTopology__1up_yyHF_nelectron, JET_Pileup_RhoTopology__1up_yyHF_nmuon, JET_Pileup_RhoTopology__1up_m_yy);
				 checkSingleJet(histb_noMET_JET_SingleParticle_HighPt__1down, histc_noMET_JET_SingleParticle_HighPt__1down, histl_noMET_JET_SingleParticle_HighPt__1down,
				 		   JET_SingleParticle_HighPt__1down_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_SingleParticle_HighPt__1down_isPassed, JET_SingleParticle_HighPt__1down_yyHF_leadjet_truthlabel,
				 		   JET_SingleParticle_HighPt__1down_yyHF_leadjet_btagbin, JET_SingleParticle_HighPt__1down_yyHF_Njet_central, JET_SingleParticle_HighPt__1down_yyHFj_weight, JET_SingleParticle_HighPt__1down_yyHF_met,
				 		   JET_SingleParticle_HighPt__1down_yyHF_nelectron, JET_SingleParticle_HighPt__1down_yyHF_nmuon, JET_SingleParticle_HighPt__1down_m_yy);
				 checkSingleJet(histb_noMET_JET_SingleParticle_HighPt__1up, histc_noMET_JET_SingleParticle_HighPt__1up, histl_noMET_JET_SingleParticle_HighPt__1up,
				 		   JET_SingleParticle_HighPt__1up_HGamWeight, XSWeight, lumi_mc16, sumweights, JET_SingleParticle_HighPt__1up_isPassed, JET_SingleParticle_HighPt__1up_yyHF_leadjet_truthlabel,
				 		   JET_SingleParticle_HighPt__1up_yyHF_leadjet_btagbin, JET_SingleParticle_HighPt__1up_yyHF_Njet_central, JET_SingleParticle_HighPt__1up_yyHFj_weight, JET_SingleParticle_HighPt__1up_yyHF_met,
				 		   JET_SingleParticle_HighPt__1up_yyHF_nelectron, JET_SingleParticle_HighPt__1up_yyHF_nmuon, JET_SingleParticle_HighPt__1up_m_yy);

				}
				TFile* output_file = new TFile(output_name, "recreate");
				cout << "creating file: "<< output_name << endl;

				output_file->Add(histbb_noMET_JET_BJES_Response__1down);
				output_file->Add(histbc_noMET_JET_BJES_Response__1down);
				output_file->Add(histbl_noMET_JET_BJES_Response__1down);
				output_file->Add(histcc_noMET_JET_BJES_Response__1down);
				output_file->Add(histcl_noMET_JET_BJES_Response__1down);
				output_file->Add(histll_noMET_JET_BJES_Response__1down);
				output_file->Add(histb_noMET_JET_BJES_Response__1down);
				output_file->Add(histc_noMET_JET_BJES_Response__1down);
				output_file->Add(histl_noMET_JET_BJES_Response__1down);
				output_file->Add(histbb_noMET_JET_BJES_Response__1up);
				output_file->Add(histbc_noMET_JET_BJES_Response__1up);
				output_file->Add(histbl_noMET_JET_BJES_Response__1up);
				output_file->Add(histcc_noMET_JET_BJES_Response__1up);
				output_file->Add(histcl_noMET_JET_BJES_Response__1up);
				output_file->Add(histll_noMET_JET_BJES_Response__1up);
				output_file->Add(histb_noMET_JET_BJES_Response__1up);
				output_file->Add(histc_noMET_JET_BJES_Response__1up);
				output_file->Add(histl_noMET_JET_BJES_Response__1up);
				output_file->Add(histbb_noMET_JET_EtaIntercalibration_Modelling__1down);
				output_file->Add(histbc_noMET_JET_EtaIntercalibration_Modelling__1down);
				output_file->Add(histbl_noMET_JET_EtaIntercalibration_Modelling__1down);
				output_file->Add(histcc_noMET_JET_EtaIntercalibration_Modelling__1down);
				output_file->Add(histcl_noMET_JET_EtaIntercalibration_Modelling__1down);
				output_file->Add(histll_noMET_JET_EtaIntercalibration_Modelling__1down);
				output_file->Add(histb_noMET_JET_EtaIntercalibration_Modelling__1down);
				output_file->Add(histc_noMET_JET_EtaIntercalibration_Modelling__1down);
				output_file->Add(histl_noMET_JET_EtaIntercalibration_Modelling__1down);
				output_file->Add(histbb_noMET_JET_EtaIntercalibration_Modelling__1up);
				output_file->Add(histbc_noMET_JET_EtaIntercalibration_Modelling__1up);
				output_file->Add(histbl_noMET_JET_EtaIntercalibration_Modelling__1up);
				output_file->Add(histcc_noMET_JET_EtaIntercalibration_Modelling__1up);
				output_file->Add(histcl_noMET_JET_EtaIntercalibration_Modelling__1up);
				output_file->Add(histll_noMET_JET_EtaIntercalibration_Modelling__1up);
				output_file->Add(histb_noMET_JET_EtaIntercalibration_Modelling__1up);
				output_file->Add(histc_noMET_JET_EtaIntercalibration_Modelling__1up);
				output_file->Add(histl_noMET_JET_EtaIntercalibration_Modelling__1up);
				output_file->Add(histbb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down);
				output_file->Add(histbc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down);
				output_file->Add(histbl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down);
				output_file->Add(histcc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down);
				output_file->Add(histcl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down);
				output_file->Add(histll_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down);
				output_file->Add(histb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down);
				output_file->Add(histc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down);
				output_file->Add(histl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1down);
				output_file->Add(histbb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up);
				output_file->Add(histbc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up);
				output_file->Add(histbl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up);
				output_file->Add(histcc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up);
				output_file->Add(histcl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up);
				output_file->Add(histll_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up);
				output_file->Add(histb_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up);
				output_file->Add(histc_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up);
				output_file->Add(histl_noMET_JET_EtaIntercalibration_NonClosure_2018data__1up);
				output_file->Add(histbb_noMET_JET_EtaIntercalibration_NonClosure_highE__1down);
				output_file->Add(histbc_noMET_JET_EtaIntercalibration_NonClosure_highE__1down);
				output_file->Add(histbl_noMET_JET_EtaIntercalibration_NonClosure_highE__1down);
				output_file->Add(histcc_noMET_JET_EtaIntercalibration_NonClosure_highE__1down);
				output_file->Add(histcl_noMET_JET_EtaIntercalibration_NonClosure_highE__1down);
				output_file->Add(histll_noMET_JET_EtaIntercalibration_NonClosure_highE__1down);
				output_file->Add(histb_noMET_JET_EtaIntercalibration_NonClosure_highE__1down);
				output_file->Add(histc_noMET_JET_EtaIntercalibration_NonClosure_highE__1down);
				output_file->Add(histl_noMET_JET_EtaIntercalibration_NonClosure_highE__1down);
				output_file->Add(histbb_noMET_JET_EtaIntercalibration_NonClosure_highE__1up);
				output_file->Add(histbc_noMET_JET_EtaIntercalibration_NonClosure_highE__1up);
				output_file->Add(histbl_noMET_JET_EtaIntercalibration_NonClosure_highE__1up);
				output_file->Add(histcc_noMET_JET_EtaIntercalibration_NonClosure_highE__1up);
				output_file->Add(histcl_noMET_JET_EtaIntercalibration_NonClosure_highE__1up);
				output_file->Add(histll_noMET_JET_EtaIntercalibration_NonClosure_highE__1up);
				output_file->Add(histb_noMET_JET_EtaIntercalibration_NonClosure_highE__1up);
				output_file->Add(histc_noMET_JET_EtaIntercalibration_NonClosure_highE__1up);
				output_file->Add(histl_noMET_JET_EtaIntercalibration_NonClosure_highE__1up);
				output_file->Add(histbb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down);
				output_file->Add(histbc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down);
				output_file->Add(histbl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down);
				output_file->Add(histcc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down);
				output_file->Add(histcl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down);
				output_file->Add(histll_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down);
				output_file->Add(histb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down);
				output_file->Add(histc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down);
				output_file->Add(histl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1down);
				output_file->Add(histbb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up);
				output_file->Add(histbc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up);
				output_file->Add(histbl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up);
				output_file->Add(histcc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up);
				output_file->Add(histcl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up);
				output_file->Add(histll_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up);
				output_file->Add(histb_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up);
				output_file->Add(histc_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up);
				output_file->Add(histl_noMET_JET_EtaIntercalibration_NonClosure_negEta__1up);
				output_file->Add(histbb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down);
				output_file->Add(histbc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down);
				output_file->Add(histbl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down);
				output_file->Add(histcc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down);
				output_file->Add(histcl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down);
				output_file->Add(histll_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down);
				output_file->Add(histb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down);
				output_file->Add(histc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down);
				output_file->Add(histl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1down);
				output_file->Add(histbb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up);
				output_file->Add(histbc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up);
				output_file->Add(histbl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up);
				output_file->Add(histcc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up);
				output_file->Add(histcl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up);
				output_file->Add(histll_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up);
				output_file->Add(histb_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up);
				output_file->Add(histc_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up);
				output_file->Add(histl_noMET_JET_EtaIntercalibration_NonClosure_posEta__1up);
				output_file->Add(histbb_noMET_JET_EtaIntercalibration_TotalStat__1down);
				output_file->Add(histbc_noMET_JET_EtaIntercalibration_TotalStat__1down);
				output_file->Add(histbl_noMET_JET_EtaIntercalibration_TotalStat__1down);
				output_file->Add(histcc_noMET_JET_EtaIntercalibration_TotalStat__1down);
				output_file->Add(histcl_noMET_JET_EtaIntercalibration_TotalStat__1down);
				output_file->Add(histll_noMET_JET_EtaIntercalibration_TotalStat__1down);
				output_file->Add(histb_noMET_JET_EtaIntercalibration_TotalStat__1down);
				output_file->Add(histc_noMET_JET_EtaIntercalibration_TotalStat__1down);
				output_file->Add(histl_noMET_JET_EtaIntercalibration_TotalStat__1down);
				output_file->Add(histbb_noMET_JET_EtaIntercalibration_TotalStat__1up);
				output_file->Add(histbc_noMET_JET_EtaIntercalibration_TotalStat__1up);
				output_file->Add(histbl_noMET_JET_EtaIntercalibration_TotalStat__1up);
				output_file->Add(histcc_noMET_JET_EtaIntercalibration_TotalStat__1up);
				output_file->Add(histcl_noMET_JET_EtaIntercalibration_TotalStat__1up);
				output_file->Add(histll_noMET_JET_EtaIntercalibration_TotalStat__1up);
				output_file->Add(histb_noMET_JET_EtaIntercalibration_TotalStat__1up);
				output_file->Add(histc_noMET_JET_EtaIntercalibration_TotalStat__1up);
				output_file->Add(histl_noMET_JET_EtaIntercalibration_TotalStat__1up);
				output_file->Add(histbb_noMET_JET_fJvtEfficiency__1down);
				output_file->Add(histbc_noMET_JET_fJvtEfficiency__1down);
				output_file->Add(histbl_noMET_JET_fJvtEfficiency__1down);
				output_file->Add(histcc_noMET_JET_fJvtEfficiency__1down);
				output_file->Add(histcl_noMET_JET_fJvtEfficiency__1down);
				output_file->Add(histll_noMET_JET_fJvtEfficiency__1down);
				output_file->Add(histb_noMET_JET_fJvtEfficiency__1down);
				output_file->Add(histc_noMET_JET_fJvtEfficiency__1down);
				output_file->Add(histl_noMET_JET_fJvtEfficiency__1down);
				output_file->Add(histbb_noMET_JET_fJvtEfficiency__1up);
				output_file->Add(histbc_noMET_JET_fJvtEfficiency__1up);
				output_file->Add(histbl_noMET_JET_fJvtEfficiency__1up);
				output_file->Add(histcc_noMET_JET_fJvtEfficiency__1up);
				output_file->Add(histcl_noMET_JET_fJvtEfficiency__1up);
				output_file->Add(histll_noMET_JET_fJvtEfficiency__1up);
				output_file->Add(histb_noMET_JET_fJvtEfficiency__1up);
				output_file->Add(histc_noMET_JET_fJvtEfficiency__1up);
				output_file->Add(histl_noMET_JET_fJvtEfficiency__1up);
				output_file->Add(histbb_noMET_JET_Flavor_Composition__1down);
				output_file->Add(histbc_noMET_JET_Flavor_Composition__1down);
				output_file->Add(histbl_noMET_JET_Flavor_Composition__1down);
				output_file->Add(histcc_noMET_JET_Flavor_Composition__1down);
				output_file->Add(histcl_noMET_JET_Flavor_Composition__1down);
				output_file->Add(histll_noMET_JET_Flavor_Composition__1down);
				output_file->Add(histb_noMET_JET_Flavor_Composition__1down);
				output_file->Add(histc_noMET_JET_Flavor_Composition__1down);
				output_file->Add(histl_noMET_JET_Flavor_Composition__1down);
				output_file->Add(histbb_noMET_JET_Flavor_Composition__1up);
				output_file->Add(histbc_noMET_JET_Flavor_Composition__1up);
				output_file->Add(histbl_noMET_JET_Flavor_Composition__1up);
				output_file->Add(histcc_noMET_JET_Flavor_Composition__1up);
				output_file->Add(histcl_noMET_JET_Flavor_Composition__1up);
				output_file->Add(histll_noMET_JET_Flavor_Composition__1up);
				output_file->Add(histb_noMET_JET_Flavor_Composition__1up);
				output_file->Add(histc_noMET_JET_Flavor_Composition__1up);
				output_file->Add(histl_noMET_JET_Flavor_Composition__1up);
				output_file->Add(histbb_noMET_JET_Flavor_Response__1down);
				output_file->Add(histbc_noMET_JET_Flavor_Response__1down);
				output_file->Add(histbl_noMET_JET_Flavor_Response__1down);
				output_file->Add(histcc_noMET_JET_Flavor_Response__1down);
				output_file->Add(histcl_noMET_JET_Flavor_Response__1down);
				output_file->Add(histll_noMET_JET_Flavor_Response__1down);
				output_file->Add(histb_noMET_JET_Flavor_Response__1down);
				output_file->Add(histc_noMET_JET_Flavor_Response__1down);
				output_file->Add(histl_noMET_JET_Flavor_Response__1down);
				output_file->Add(histbb_noMET_JET_Flavor_Response__1up);
				output_file->Add(histbc_noMET_JET_Flavor_Response__1up);
				output_file->Add(histbl_noMET_JET_Flavor_Response__1up);
				output_file->Add(histcc_noMET_JET_Flavor_Response__1up);
				output_file->Add(histcl_noMET_JET_Flavor_Response__1up);
				output_file->Add(histll_noMET_JET_Flavor_Response__1up);
				output_file->Add(histb_noMET_JET_Flavor_Response__1up);
				output_file->Add(histc_noMET_JET_Flavor_Response__1up);
				output_file->Add(histl_noMET_JET_Flavor_Response__1up);
				output_file->Add(histbb_noMET_JET_JvtEfficiency__1down);
				output_file->Add(histbc_noMET_JET_JvtEfficiency__1down);
				output_file->Add(histbl_noMET_JET_JvtEfficiency__1down);
				output_file->Add(histcc_noMET_JET_JvtEfficiency__1down);
				output_file->Add(histcl_noMET_JET_JvtEfficiency__1down);
				output_file->Add(histll_noMET_JET_JvtEfficiency__1down);
				output_file->Add(histb_noMET_JET_JvtEfficiency__1down);
				output_file->Add(histc_noMET_JET_JvtEfficiency__1down);
				output_file->Add(histl_noMET_JET_JvtEfficiency__1down);
				output_file->Add(histbb_noMET_JET_JvtEfficiency__1up);
				output_file->Add(histbc_noMET_JET_JvtEfficiency__1up);
				output_file->Add(histbl_noMET_JET_JvtEfficiency__1up);
				output_file->Add(histcc_noMET_JET_JvtEfficiency__1up);
				output_file->Add(histcl_noMET_JET_JvtEfficiency__1up);
				output_file->Add(histll_noMET_JET_JvtEfficiency__1up);
				output_file->Add(histb_noMET_JET_JvtEfficiency__1up);
				output_file->Add(histc_noMET_JET_JvtEfficiency__1up);
				output_file->Add(histl_noMET_JET_JvtEfficiency__1up);
				output_file->Add(histbb_noMET_JET_Pileup_OffsetMu__1down);
				output_file->Add(histbc_noMET_JET_Pileup_OffsetMu__1down);
				output_file->Add(histbl_noMET_JET_Pileup_OffsetMu__1down);
				output_file->Add(histcc_noMET_JET_Pileup_OffsetMu__1down);
				output_file->Add(histcl_noMET_JET_Pileup_OffsetMu__1down);
				output_file->Add(histll_noMET_JET_Pileup_OffsetMu__1down);
				output_file->Add(histb_noMET_JET_Pileup_OffsetMu__1down);
				output_file->Add(histc_noMET_JET_Pileup_OffsetMu__1down);
				output_file->Add(histl_noMET_JET_Pileup_OffsetMu__1down);
				output_file->Add(histbb_noMET_JET_Pileup_OffsetMu__1up);
				output_file->Add(histbc_noMET_JET_Pileup_OffsetMu__1up);
				output_file->Add(histbl_noMET_JET_Pileup_OffsetMu__1up);
				output_file->Add(histcc_noMET_JET_Pileup_OffsetMu__1up);
				output_file->Add(histcl_noMET_JET_Pileup_OffsetMu__1up);
				output_file->Add(histll_noMET_JET_Pileup_OffsetMu__1up);
				output_file->Add(histb_noMET_JET_Pileup_OffsetMu__1up);
				output_file->Add(histc_noMET_JET_Pileup_OffsetMu__1up);
				output_file->Add(histl_noMET_JET_Pileup_OffsetMu__1up);
				output_file->Add(histbb_noMET_JET_Pileup_OffsetNPV__1down);
				output_file->Add(histbc_noMET_JET_Pileup_OffsetNPV__1down);
				output_file->Add(histbl_noMET_JET_Pileup_OffsetNPV__1down);
				output_file->Add(histcc_noMET_JET_Pileup_OffsetNPV__1down);
				output_file->Add(histcl_noMET_JET_Pileup_OffsetNPV__1down);
				output_file->Add(histll_noMET_JET_Pileup_OffsetNPV__1down);
				output_file->Add(histb_noMET_JET_Pileup_OffsetNPV__1down);
				output_file->Add(histc_noMET_JET_Pileup_OffsetNPV__1down);
				output_file->Add(histl_noMET_JET_Pileup_OffsetNPV__1down);
				output_file->Add(histbb_noMET_JET_Pileup_OffsetNPV__1up);
				output_file->Add(histbc_noMET_JET_Pileup_OffsetNPV__1up);
				output_file->Add(histbl_noMET_JET_Pileup_OffsetNPV__1up);
				output_file->Add(histcc_noMET_JET_Pileup_OffsetNPV__1up);
				output_file->Add(histcl_noMET_JET_Pileup_OffsetNPV__1up);
				output_file->Add(histll_noMET_JET_Pileup_OffsetNPV__1up);
				output_file->Add(histb_noMET_JET_Pileup_OffsetNPV__1up);
				output_file->Add(histc_noMET_JET_Pileup_OffsetNPV__1up);
				output_file->Add(histl_noMET_JET_Pileup_OffsetNPV__1up);
				output_file->Add(histbb_noMET_JET_Pileup_PtTerm__1down);
				output_file->Add(histbc_noMET_JET_Pileup_PtTerm__1down);
				output_file->Add(histbl_noMET_JET_Pileup_PtTerm__1down);
				output_file->Add(histcc_noMET_JET_Pileup_PtTerm__1down);
				output_file->Add(histcl_noMET_JET_Pileup_PtTerm__1down);
				output_file->Add(histll_noMET_JET_Pileup_PtTerm__1down);
				output_file->Add(histb_noMET_JET_Pileup_PtTerm__1down);
				output_file->Add(histc_noMET_JET_Pileup_PtTerm__1down);
				output_file->Add(histl_noMET_JET_Pileup_PtTerm__1down);
				output_file->Add(histbb_noMET_JET_Pileup_PtTerm__1up);
				output_file->Add(histbc_noMET_JET_Pileup_PtTerm__1up);
				output_file->Add(histbl_noMET_JET_Pileup_PtTerm__1up);
				output_file->Add(histcc_noMET_JET_Pileup_PtTerm__1up);
				output_file->Add(histcl_noMET_JET_Pileup_PtTerm__1up);
				output_file->Add(histll_noMET_JET_Pileup_PtTerm__1up);
				output_file->Add(histb_noMET_JET_Pileup_PtTerm__1up);
				output_file->Add(histc_noMET_JET_Pileup_PtTerm__1up);
				output_file->Add(histl_noMET_JET_Pileup_PtTerm__1up);
				output_file->Add(histbb_noMET_JET_Pileup_RhoTopology__1down);
				output_file->Add(histbc_noMET_JET_Pileup_RhoTopology__1down);
				output_file->Add(histbl_noMET_JET_Pileup_RhoTopology__1down);
				output_file->Add(histcc_noMET_JET_Pileup_RhoTopology__1down);
				output_file->Add(histcl_noMET_JET_Pileup_RhoTopology__1down);
				output_file->Add(histll_noMET_JET_Pileup_RhoTopology__1down);
				output_file->Add(histb_noMET_JET_Pileup_RhoTopology__1down);
				output_file->Add(histc_noMET_JET_Pileup_RhoTopology__1down);
				output_file->Add(histl_noMET_JET_Pileup_RhoTopology__1down);
				output_file->Add(histbb_noMET_JET_Pileup_RhoTopology__1up);
				output_file->Add(histbc_noMET_JET_Pileup_RhoTopology__1up);
				output_file->Add(histbl_noMET_JET_Pileup_RhoTopology__1up);
				output_file->Add(histcc_noMET_JET_Pileup_RhoTopology__1up);
				output_file->Add(histcl_noMET_JET_Pileup_RhoTopology__1up);
				output_file->Add(histll_noMET_JET_Pileup_RhoTopology__1up);
				output_file->Add(histb_noMET_JET_Pileup_RhoTopology__1up);
				output_file->Add(histc_noMET_JET_Pileup_RhoTopology__1up);
				output_file->Add(histl_noMET_JET_Pileup_RhoTopology__1up);
				output_file->Add(histbb_noMET_JET_SingleParticle_HighPt__1down);
				output_file->Add(histbc_noMET_JET_SingleParticle_HighPt__1down);
				output_file->Add(histbl_noMET_JET_SingleParticle_HighPt__1down);
				output_file->Add(histcc_noMET_JET_SingleParticle_HighPt__1down);
				output_file->Add(histcl_noMET_JET_SingleParticle_HighPt__1down);
				output_file->Add(histll_noMET_JET_SingleParticle_HighPt__1down);
				output_file->Add(histb_noMET_JET_SingleParticle_HighPt__1down);
				output_file->Add(histc_noMET_JET_SingleParticle_HighPt__1down);
				output_file->Add(histl_noMET_JET_SingleParticle_HighPt__1down);
				output_file->Add(histbb_noMET_JET_SingleParticle_HighPt__1up);
				output_file->Add(histbc_noMET_JET_SingleParticle_HighPt__1up);
				output_file->Add(histbl_noMET_JET_SingleParticle_HighPt__1up);
				output_file->Add(histcc_noMET_JET_SingleParticle_HighPt__1up);
				output_file->Add(histcl_noMET_JET_SingleParticle_HighPt__1up);
				output_file->Add(histll_noMET_JET_SingleParticle_HighPt__1up);
				output_file->Add(histb_noMET_JET_SingleParticle_HighPt__1up);
				output_file->Add(histc_noMET_JET_SingleParticle_HighPt__1up);
				output_file->Add(histl_noMET_JET_SingleParticle_HighPt__1up);

				output_file->Write();
				output_file->Close();
			}//end nInputs
		} //end mc
	} //end sys
}
