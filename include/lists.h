#ifndef _LISTS_H
#define _LISTS_H

#define EGTRIGGERS(ACTION, ...)                                \
   SEGTRIGGERS(ACTION, ## __VA_ARGS__)                         \
   DEGTRIGGERS(ACTION, ## __VA_ARGS__)

#define SEGTRIGGERS(ACTION, ...)                               \
   HIGHPTSEGTRIGGERS(ACTION, ## __VA_ARGS__)                   \
   LOWPTSEGTRIGGERS(ACTION, ## __VA_ARGS__)

#define HIGHPTSEGTRIGGERS(ACTION, ...)                         \
   ACTION(HLT_Ele20Gsf_v1, ## __VA_ARGS__)                     \
   ACTION(HLT_Ele30Gsf_v1, ## __VA_ARGS__)                     \
   ACTION(HLT_Ele40Gsf_v1, ## __VA_ARGS__)                     \
   ACTION(HLT_Ele50Gsf_v1, ## __VA_ARGS__)

#define LOWPTSEGTRIGGERS(ACTION, ...)                          \
   ACTION(HLT_Ele15Gsf_v1, ## __VA_ARGS__)                     \
   ACTION(HLT_Ele10Gsf_v1, ## __VA_ARGS__)                     \
   ACTION(HLT_Ele5Gsf_v1, ## __VA_ARGS__)

#define DEGTRIGGERS(ACTION, ...)                               \
   DEGMIN20TRIGGERS(ACTION, ## __VA_ARGS__)                    \
   DEGMIN10TRIGGERS(ACTION, ## __VA_ARGS__)

#define DEGMIN20TRIGGERS(ACTION, ...)                          \
   ACTION(HLT_DoubleEle20Gsf_v1, ## __VA_ARGS__)               \
   ACTION(HLT_DoubleEle20Gsf_Mass50_v1, ## __VA_ARGS__)

#define DEGMIN10TRIGGERS(ACTION, ...)                          \
   ACTION(HLT_DoubleEle20Ele10Gsf_v1, ## __VA_ARGS__)          \
   ACTION(HLT_DoubleEle10Gsf_v1, ## __VA_ARGS__)               \
   ACTION(HLT_DoubleEle20Ele10Gsf_Mass50_v1, ## __VA_ARGS__)   \
   ACTION(HLT_DoubleEle10Gsf_Mass50_v1, ## __VA_ARGS__)

#include "egxmu.h"

#include "egxjet.h"

#define SELECTIONS(ACTION, ...)                                \
   ACTION(loose, ## __VA_ARGS__, "H/E < 0.2")                  \
   ACTION(tight, ## __VA_ARGS__, "2015 veto ID")               \
   ACTION(barrel, ## __VA_ARGS__,                              \
      "barrel (|#eta_{SC}|<1.4442)")                           \
   ACTION(endcap, ## __VA_ARGS__,                              \
      "endcap (|#eta_{SC}|>1.566)")                            \
   ACTION(central, ## __VA_ARGS__, "0 - 30% centrality")       \
   ACTION(peripheral, ## __VA_ARGS__, "30 - 100% centrality")

#define VARSPERELE(ACTION, ...)                                \
   ACTION(elePt, ## __VA_ARGS__, float, "p_{T}", ";p_{T};")    \
   ACTION(eleEta, ## __VA_ARGS__, float, "#eta", ";#eta;")     \
   ACTION(elePhi, ## __VA_ARGS__, float, "#phi", ";#phi;")     \
   ACTION(eleSCEta, ## __VA_ARGS__, float,                     \
      "#eta_{SC}", ";#eta_{SC};")                              \
   ACTION(eleHoverE, ## __VA_ARGS__, float,                    \
      "H/E", ";H/E;")                                          \
   ACTION(eleSigmaIEtaIEta_2012, ## __VA_ARGS__, float,        \
      "#sigma_{#eta#eta}", ";#sigma_{#eta#eta};")              \
   ACTION(eleEoverPInv, ## __VA_ARGS__, float,                 \
      "1/E-1/p", ";1/E-1/p;")                                  \
   ACTION(eleD0, ## __VA_ARGS__, float,                        \
      "track d_{0}", ";d_{0};")                                \
   ACTION(eleDz, ## __VA_ARGS__, float,                        \
      "track d_{z}", ";d_{z};")                                \
   ACTION(eledEtaAtVtx, ## __VA_ARGS__, float,                 \
      "track #Delta#eta at vertex", ";#Delta#eta;")            \
   ACTION(eledPhiAtVtx, ## __VA_ARGS__, float,                 \
      "track #Delta#phi at vertex", ";#Delta#phi;")            \
   ACTION(eleMissHits, ## __VA_ARGS__, int,                    \
      "missing hits", ";d_{z};")                               \
   ACTION(eleBrem, ## __VA_ARGS__, float,                      \
      "bremsstrahlung", ";f_{brem};")                          \
   ACTION(eleTrkPt, ## __VA_ARGS__, float,                     \
      "track p_{t}", ";p_{T}^{trk};")                          \
   ACTION(eleGenMatchIndex, ## __VA_ARGS__, int,               \
      "gen particle index", ";gen particle index;")

#define VARSPEREVT(ACTION, ...)                                \
   ACTION(elePairZMass, ## __VA_ARGS__, float,                 \
      "invariant mass", ";M_{Z};")                             \
   ACTION(hiHF, ## __VA_ARGS__, float,                         \
      "#Sigma E_{T}^{HF}", ";#Sigma E_{T}^{HF};")

#define ALLVARS(ACTION, ...)                                   \
   VARSPERELE(ACTION, ## __VA_ARGS__)                          \
   VARSPEREVT(ACTION, ## __VA_ARGS__)

#define SETUPVARBINS                                           \
   BIN(elePt, 40, 0, 200)                                      \
   BIN(eleEta, 20, -3.0, 3.0)                                  \
   BIN(elePhi, 32, -3.2, 3.2)                                  \
   BIN(eleSCEta, 20, -3.0, 3.0)                                \
   BIN(eleHoverE, 20, 0, 0.2)                                  \
   BIN(eleSigmaIEtaIEta_2012, 20, 0, 0.04)                     \
   BIN(eleEoverPInv, 20, 0, 0.2)                               \
   BIN(eleD0, 20, -0.2, 0.2)                                   \
   BIN(eleDz, 20, -0.2, 0.2)                                   \
   BIN(eledEtaAtVtx, 20, -0.02, 0.02)                          \
   BIN(eledPhiAtVtx, 20, -0.2, 0.2)                            \
   BIN(eleMissHits, 8, 0, 8)                                   \
   BIN(eleBrem, 20, 0, 1.0)                                    \
   BIN(eleTrkPt, 40, 0, 200)                                   \
   BIN(eleGenMatchIndex, 11, -1, 10)                           \
   BIN(elePairZMass, 30, 60, 120)                              \
   BIN(hiHF, 20, 0, 10000)

#endif /* _LISTS_H */
