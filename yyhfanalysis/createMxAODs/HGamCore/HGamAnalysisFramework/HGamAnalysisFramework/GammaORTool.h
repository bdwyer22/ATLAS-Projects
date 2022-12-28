#pragma once

// STL include(s):
#include <vector>

// EDM include(s):
#include "AsgTools/AsgMessaging.h"

// ROOT includes
#include "TLorentzVector.h"
#include "TMVA/Reader.h"
#include "TString.h"


class MCTruthClassifier;

// Forward declarations
namespace HG { class EventHandler; class TruthHandler; }

namespace HG {
  /*!
     @class GammaORTool
     @brief The main class for the Higgs+HF measurement.

     This tool, included in the HGamAnalysisFramework, contains all the functions designed
     specifically for the Higgs+HF measurement.
   */
  class GammaORTool : public asg::AsgMessaging {
  public:
    /**
     * @brief Constructor
     * @param eventHandler The HGam eventHandler to write information to EventInfo
     * @param truthHandler The HGam truthHandler to read truth information
     */
    GammaORTool(const char *name, HG::EventHandler *eventHandler, HG::TruthHandler *truthHandler);

    /*! Destructor, deallocates resources used by class instance. */
    virtual ~GammaORTool();

    /*!
       @fn virtual EL::StatusCode initialize(Config &config)
       @brief Set or fetch default values for members from config
       @param config
     */
    virtual EL::StatusCode initialize(Config &config);

    /**
     * @brief Function to save all the Higgs+HF information
     * @details
     *
     * @param photons Container with all photons
     * @param jets Container with all jets
     * @param jets_noJVT Container with all jets, no JVT cut
     * @param MET Container
     * @param muons Container with all muons
     * @param electron Container with all electrons
     */
    void saveGammaORInfo(const xAOD::PhotonContainer &photons,
                      const xAOD::JetContainer &jets,
                      xAOD::JetContainer &jets_noJVT,
                      const xAOD::MissingETContainer &met,
                      xAOD::MuonContainer &muons,
                      xAOD::ElectronContainer &electrons);

    /**
     * @brief Function to save all the Higgs+HF truth information
     * @details
     *
     * @param photons Container with truth photons
     * @param jets Container with truth jets
     * @param bjet Container with truth jets matched to a b-hadron
     * @param cjet Container with truth jets matched to a c-hadron
     * @param Truth MET Container
     * @param muons Container with truth muons
     * @param electron Container with truth electrons
     */
    void saveGammaORTruthInfo(const xAOD::TruthParticleContainer &photons,
                           const xAOD::JetContainer   &jets,
                           const xAOD::JetContainer   &bjets,
                           const xAOD::JetContainer   &cjets,
                           const xAOD::MissingETContainer &met,
                           xAOD::TruthParticleContainer &muons,
                           xAOD::TruthParticleContainer &electrons);


  private:
    HG::EventHandler *m_eventHandler; //!
    HG::TruthHandler *m_truthHandler; //!

    // User-configurable selection options;

    int m_max_barcode;                            //! Maximum barcode considered for final state particles (exclude particles from Geant)
    int m_n_leptons;                              //! Number of leptons expected in process 
    int m_n_photons;                              //! Number of required photons
    std::vector<int> m_lepton_pdgIds;             //! Lepton flavours considered,  signed pdgIds 
    std::vector<int> m_preferred_lepton_origins;  //! Lepton origins preferred when searching prompt leptons i.e. associated with the hard process
    std::vector<int> m_lepton_veto_origins;       //! Lepton origins of leptons never used as prompt e.g. hadron origins
    std::vector<int> m_veto_photon_origins;       //! Photon origins vetoed when searching prompt leptons
    float m_photon_pT_cuts;                       //! p_T (y) cut(s) used in inOverlap function
    float m_dR_lepton_photon_cut;                 //! delta R (l,y) cut for used in inOverlap and photonPtsOutsideDr function
    std::vector<float> m_dR_lepton_photon_cuts;   //! List of dR cuts
    float m_min_considered_photon_pT;             //! Minimum photon pT considered in algorithm
    std::string m_truthparticle_collection_name;  //! Name of truth particle collection

    MCTruthClassifier *m_truthClassifier;


    /**
     * @brief Accessor for event handler
     */
    virtual HG::EventHandler *eventHandler();

    /**
     * @brief Accessor for truth handler
     */
    virtual HG::TruthHandler *truthHandler();

    /*!
       \fn void saveMapsToEventInfo(std::map<TString, float> &eventInfoFloats, std::map<TString,int> &eventInfoInts)
       \brief Write maps to eventInfo
     */
    void saveMapsToEventInfo(std::map<TString, float> &eventInfoFloats, std::map<TString, int> &eventInfoInts);
    void saveMapsToTruthEventInfo(std::map<TString, float> &eventInfoFloats, std::map<TString, int> &eventInfoInts);

    void performVGammaOverlapSelection(std::map<TString, int> &eventInfoInts, std::map<TString, float> &eventInfoFloats);


    bool isFromTau(const xAOD::TruthParticle& lepton, int nRecursions=0) const;

  };

}
