#ifndef _LISTS_H
#define _LISTS_H

#define TRIGGERS(ACTION, ...)                                  \
   SEGTRIGGERS(ACTION, ## __VA_ARGS__)                         \
   DEGTRIGGERS(ACTION, ## __VA_ARGS__)

#define SEGTRIGGERS(ACTION, ...)                               \
   ACTION(HLT_Ele20Gsf_v1, ## __VA_ARGS__)

#define DEGTRIGGERS(ACTION, ...)                               \
   ACTION(HLT_DoubleEle20Gsf_v1, ## __VA_ARGS__)               \
   ACTION(HLT_DoubleEle20Gsf_Mass50_v1, ## __VA_ARGS__)

#define SELECTIONS(ACTION, ...)                                \
   ACTION(loose, ## __VA_ARGS__)                               \
   ACTION(tight, ## __VA_ARGS__)

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
      "missing hits", ";d_{z};")

#endif /* _LISTS_H */
