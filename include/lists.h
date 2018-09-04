#ifndef _LISTS_H
#define _LISTS_H

#define TRIGGERS(ACTION, ...)                                  \
   SEGTRIGGERS(ACTION, ## __VA_ARGS__)                         \
   DEGTRIGGERS(ACTION, ## __VA_ARGS__)

#define SEGTRIGGERS(ACTION, ...)                               \
   ACTION(HLT_Ele20Gsf_v1, ## __VA_ARGS__)                     \
   ACTION(HLT_Ele30Gsf_v1, ## __VA_ARGS__)                     \
   ACTION(HLT_Ele40Gsf_v1, ## __VA_ARGS__)                     \
   ACTION(HLT_Ele50Gsf_v1, ## __VA_ARGS__)                     \
   ACTION(HLT_Ele15Gsf_v1, ## __VA_ARGS__)                     \
   ACTION(HLT_Ele10Gsf_v1, ## __VA_ARGS__)                     \
   ACTION(HLT_Ele5Gsf_v1, ## __VA_ARGS__)

#define DEGTRIGGERS(ACTION, ...)                               \
   ACTION(HLT_DoubleEle20Gsf_v1, ## __VA_ARGS__)               \
   ACTION(HLT_DoubleEle20Ele10Gsf_v1, ## __VA_ARGS__)          \
   ACTION(HLT_DoubleEle10Gsf_v1, ## __VA_ARGS__)               \
   ACTION(HLT_DoubleEle20Gsf_Mass50_v1, ## __VA_ARGS__)        \
   ACTION(HLT_DoubleEle20Ele10Gsf_Mass50_v1, ## __VA_ARGS__)   \
   ACTION(HLT_DoubleEle10Gsf_Mass50_v1, ## __VA_ARGS__)        \

#define SELECTIONS(ACTION, ...)                                \
   ACTION(loose, ## __VA_ARGS__)                               \
   ACTION(tight, ## __VA_ARGS__)                               \
   ACTION(barrel, ## __VA_ARGS__)                              \
   ACTION(endcap, ## __VA_ARGS__)                              \
   ACTION(central, ## __VA_ARGS__)                             \
   ACTION(peripheral, ## __VA_ARGS__)

#define VARIABLES(ACTION, ...)                                 \
   ACTION(Pt, ## __VA_ARGS__, float, "p_{T}", ";p_{T};")       \
   ACTION(Eta, ## __VA_ARGS__, float, "#eta", ";#eta;")        \
   ACTION(Phi, ## __VA_ARGS__, float, "#phi", ";#phi;")        \
   ACTION(SCEta, ## __VA_ARGS__, float,                        \
      "#eta_{SC}", ";#eta_{SC};")                              \
   ACTION(HoverE, ## __VA_ARGS__, float,                       \
      "H/E", ";H/E;")                                          \
   ACTION(SigmaIEtaIEta_2012, ## __VA_ARGS__, float,           \
      "#sigma_{#eta#eta}", ";#sigma_{#eta#eta};")              \
   ACTION(EoverPInv, ## __VA_ARGS__, float,                    \
      "1/E-1/p", ";1/E-1/p;")                                  \
   ACTION(D0, ## __VA_ARGS__, float,                           \
      "track d_{0}", ";d_{0};")                                \
   ACTION(Dz, ## __VA_ARGS__, float,                           \
      "track d_{z}", ";d_{z};")                                \
   ACTION(dEtaAtVtx, ## __VA_ARGS__, float,                    \
      "track #Delta#eta at vertex", ";#Delta#eta;")            \
   ACTION(dPhiAtVtx, ## __VA_ARGS__, float,                    \
      "track #Delta#phi at vertex", ";#Delta#phi;")            \
   ACTION(MissHits, ## __VA_ARGS__, int,                       \
      "missing hits", ";d_{z};")                               \
   ACTION(Brem, ## __VA_ARGS__, float,                         \
      "bremsstrahlung", ";f_{brem};")                          \
   ACTION(TrkPt, ## __VA_ARGS__, float,                        \
      "track p_{t}", ";p_{T}^{trk};")                          \
   ACTION(GenMatchIndex, ## __VA_ARGS__, int,                  \
      "gen particle index", ";gen particle index;")

#define SETUPVARBINS                                           \
   BIN(Pt, 40, 0, 200)                                         \
   BIN(Eta, 20, -3.0, 3.0)                                     \
   BIN(Phi, 32, -3.2, 3.2)                                     \
   BIN(SCEta, 20, -3.0, 3.0)                                   \
   BIN(HoverE, 20, 0, 0.2)                                     \
   BIN(SigmaIEtaIEta_2012, 20, 0, 0.04)                        \
   BIN(EoverPInv, 20, 0, 0.2)                                  \
   BIN(D0, 20, -0.2, 0.2)                                      \
   BIN(Dz, 20, -0.2, 0.2)                                      \
   BIN(dEtaAtVtx, 20, -0.02, 0.02)                             \
   BIN(dPhiAtVtx, 20, -0.2, 0.2)                               \
   BIN(MissHits, 8, 0, 8)                                      \
   BIN(Brem, 20, 0, 1.0)                                       \
   BIN(TrkPt, 40, 0, 200)                                      \
   BIN(GenMatchIndex, 11, -1, 10)

#endif /* _LISTS_H */
