#define L1SEEDS(ACTION, ...)                                         \
   ACTION(L1_ZeroBias, ## __VA_ARGS__)                               \
   ACTION(L1_MinimumBiasHF1_AND_BptxAND, ## __VA_ARGS__)             \
   ACTION(L1_MinimumBiasHF1_OR_BptxAND, ## __VA_ARGS__)              \
   ACTION(L1_MinimumBiasHF2_AND_BptxAND, ## __VA_ARGS__)             \
   ACTION(L1_MinimumBiasHF2_OR_BptxAND, ## __VA_ARGS__)              \
   ACTION(L1_DoubleEG2_BptxAND, ## __VA_ARGS__)                      \
   ACTION(L1_DoubleEG5_BptxAND, ## __VA_ARGS__)                      \
   ACTION(L1_DoubleEG8_BptxAND, ## __VA_ARGS__)                      \
   ACTION(L1_DoubleEG10_BptxAND, ## __VA_ARGS__)                     \
   ACTION(L1_SingleMuOpen_BptxAND, ## __VA_ARGS__)                   \
   EGL1SEEDS(ACTION, ...)
   ACTION(L1_SingleMuOpen_SingleJet28_MidEta2p7_BptxAND, ## __VA_ARGS__)   \
   ACTION(L1_SingleMuOpen_SingleJet44_MidEta2p7_BptxAND, ## __VA_ARGS__)   \
   ACTION(L1_SingleMuOpen_SingleJet56_MidEta2p7_BptxAND, ## __VA_ARGS__)   \
   ACTION(L1_SingleMuOpen_SingleJet64_MidEta2p7_BptxAND, ## __VA_ARGS__)   \
   ACTION(L1_SingleEG7_SingleJet28_MidEta2p7_BptxAND, ## __VA_ARGS__)      \
   ACTION(L1_SingleEG7_SingleJet44_MidEta2p7_BptxAND, ## __VA_ARGS__)      \
   ACTION(L1_SingleEG7_SingleJet56_MidEta2p7_BptxAND, ## __VA_ARGS__)      \
   ACTION(L1_SingleEG7_SingleJet60_MidEta2p7_BptxAND, ## __VA_ARGS__)      \
   ACTION(L1_SingleEG12_SingleJet28_MidEta2p7_BptxAND, ## __VA_ARGS__)     \
   ACTION(L1_SingleEG12_SingleJet44_MidEta2p7_BptxAND, ## __VA_ARGS__)     \
   ACTION(L1_SingleEG12_SingleJet56_MidEta2p7_BptxAND, ## __VA_ARGS__)     \
   ACTION(L1_SingleEG12_SingleJet60_MidEta2p7_BptxAND, ## __VA_ARGS__)     \
   ACTION(L1_SingleEG15_SingleJet28_MidEta2p7_BptxAND, ## __VA_ARGS__)     \
   ACTION(L1_SingleEG15_SingleJet44_MidEta2p7_BptxAND, ## __VA_ARGS__)     \
   ACTION(L1_SingleEG15_SingleJet56_MidEta2p7_BptxAND, ## __VA_ARGS__)     \
   ACTION(L1_SingleEG15_SingleJet60_MidEta2p7_BptxAND, ## __VA_ARGS__)

#define EGL1SEEDS(ACTION, ...)                                       \
   ACTION(L1_SingleEG3_BptxAND, ## __VA_ARGS__)                      \
   ACTION(L1_SingleEG5_BptxAND, ## __VA_ARGS__)                      \
   ACTION(L1_SingleEG7_BptxAND, ## __VA_ARGS__)                      \
   ACTION(L1_SingleEG12_BptxAND, ## __VA_ARGS__)                     \
   ACTION(L1_SingleEG15_BptxAND, ## __VA_ARGS__)                     \
   ACTION(L1_SingleEG21_BptxAND, ## __VA_ARGS__)                     \
   ACTION(L1_SingleEG30_BptxAND, ## __VA_ARGS__)
