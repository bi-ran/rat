#ifndef _LISTS_H
#define _LISTS_H

#define EGTRIGGERS(ACTION, ...)                                \
   SEGTRIGGERS(ACTION, ## __VA_ARGS__)                         \
   DEGTRIGGERS(ACTION, ## __VA_ARGS__)

#define SEGTRIGGERS(ACTION, ...)                               \
   ACTION(HLT_Ele10GsfUM_v1, ## __VA_ARGS__)                   \
   ACTION(HLT_Ele15GsfUM_v1, ## __VA_ARGS__)                   \
   ACTION(HLT_Ele20GsfUM_v1, ## __VA_ARGS__)                   \
   ACTION(HLT_Ele30GsfUM_v1, ## __VA_ARGS__)                   \
   ACTION(HLT_Ele40GsfUM_v1, ## __VA_ARGS__)                   \
   ACTION(HLT_Ele50GsfUM_v1, ## __VA_ARGS__)

#define DEGTRIGGERS(ACTION, ...)                               \
   DEGMIN15TRIGGERS(ACTION, ## __VA_ARGS__)                    \
   DEGMIN10TRIGGERS(ACTION, ## __VA_ARGS__)

#define DEGMIN15TRIGGERS(ACTION, ...)                          \
   ACTION(HLT_DoubleEle15GsfUM_v1, ## __VA_ARGS__)             \
   ACTION(HLT_DoubleEle15GsfMass50UM_v1, ## __VA_ARGS__)

#define DEGMIN10TRIGGERS(ACTION, ...)                          \
   ACTION(HLT_Ele15Ele10GsfUM_v1, ## __VA_ARGS__)              \
   ACTION(HLT_Ele15Ele10GsfMass50UM_v1, ## __VA_ARGS__)        \
   ACTION(HLT_DoubleEle10GsfUM_v1, ## __VA_ARGS__)             \
   ACTION(HLT_DoubleEle10GsfMass50UM_v1, ## __VA_ARGS__)

#include "egxmu.h"

#include "lxjet.h"

#define SELECTIONS(ACTION, ...)                                \
   ACTION(tight, ## __VA_ARGS__, "2015 veto ID")               \
   ACTION(barrel, ## __VA_ARGS__,                              \
      "barrel (|#eta_{SC}|<1.4442)")                           \
   ACTION(endcap, ## __VA_ARGS__,                              \
      "endcap (|#eta_{SC}|>1.566)")                            \
   ACTION(central, ## __VA_ARGS__, "0 - 30% centrality")       \
   ACTION(peripheral, ## __VA_ARGS__, "30 - 100% centrality")

#define VARSPERELE(ACTION, ...)                                \
   ACTION(elePt, ## __VA_ARGS__, float, 40, 0, 200,            \
      "p_{T}", ";p_{T};")                                      \
   ACTION(eleEta, ## __VA_ARGS__, float, 20, -3.0, 3.0,        \
      "#eta", ";#eta;")                                        \
   ACTION(elePhi, ## __VA_ARGS__, float, 32, -3.2, 3.2,        \
      "#phi", ";#phi;")                                        \
   ACTION(eleSCEta, ## __VA_ARGS__, float, 20, -3.0, 3.0,      \
      "#eta_{SC}", ";#eta_{SC};")                              \
   ACTION(eleHoverE, ## __VA_ARGS__, float, 20, 0, 0.2,        \
      "H/E", ";H/E;")                                          \
   ACTION(eleSigmaIEtaIEta_2012, ## __VA_ARGS__, float,        \
      20, 0, 0.04, "#sigma_{#eta#eta}", ";#sigma_{#eta#eta};") \
   ACTION(eleEoverPInv, ## __VA_ARGS__, float, 20, 0, 0.2,     \
      "1/E-1/p", ";1/E-1/p;")                                  \
   ACTION(eleD0, ## __VA_ARGS__, float, 20, -0.2, 0.2,         \
      "track d_{0}", ";d_{0};")                                \
   ACTION(eleDz, ## __VA_ARGS__, float, 20, -0.2, 0.2,         \
      "track d_{z}", ";d_{z};")                                \
   ACTION(eledEtaAtVtx, ## __VA_ARGS__, float,                 \
      20, -0.02, 0.02, "#Delta#eta at vertex", ";#Delta#eta;") \
   ACTION(eledPhiAtVtx, ## __VA_ARGS__, float,                 \
      20, -0.2, 0.2, "#Delta#phi at vertex", ";#Delta#phi;")   \
   ACTION(eleMissHits, ## __VA_ARGS__, int, 8, 0, 8,           \
      "missing hits", ";d_{z};")                               \
   ACTION(eleBrem, ## __VA_ARGS__, float, 20, 0, 1.0,          \
      "bremsstrahlung", ";f_{brem};")                          \
   ACTION(eleTrkPt, ## __VA_ARGS__, float, 40, 0, 200,         \
      "track p_{t}", ";p_{T}^{trk};")                          \
   ACTION(eleGenMatchIndex, ## __VA_ARGS__, int, 11, -1, 10,   \
      "gen particle index", ";gen particle index;")

#define VARSPEREVT(ACTION, ...)                                \
   ACTION(elePairZMass, ## __VA_ARGS__, float, 30, 60, 120,    \
      "invariant mass", ";M_{Z};")                             \
   ACTION(hiHF, ## __VA_ARGS__, float, 20, 0, 10000,           \
      "#Sigma E_{T}^{HF}", ";#Sigma E_{T}^{HF};")

#define ALLVARS(ACTION, ...)                                   \
   VARSPERELE(ACTION, ## __VA_ARGS__)                          \
   VARSPEREVT(ACTION, ## __VA_ARGS__)

#endif /* _LISTS_H */
