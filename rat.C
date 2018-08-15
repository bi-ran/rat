#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TGraphAsymmErrors.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLine.h"
#include "TLatex.h"

#include <algorithm>
#include <array>
#include <map>
#include <string>
#include <vector>

#include "defines.h"

std::vector<int> palette = {
   TColor::GetColor("#f2777a"),
   TColor::GetColor("#99cc99"),
   TColor::GetColor("#6699cc")
};

int rate(const char* input) {
   TFile* fin = new TFile(input, "read");
   TTree* tin = (TTree*)fin->Get("hltbitanalysis/HltTree");

   uint64_t nentries = tin->GetEntries();
   TRIGGERS(RATE, nentries)

   return 0;
}

template<int... I>
struct pack {};

template<int N, int... I>
struct expand : expand<N-1, N, I...> {};

template<int... I>
struct expand<0, I...> : pack<0, I...> {};

template<int N>
constexpr float edge(float min, float max, int i) {
   return min + i * (max - min) / N; }

template<int N, int... I>
static constexpr auto edges(float min, float max, pack<I...>)
      -> std::array<float, N+1> {
   return {{ edge<N>(min, max, I)... }}; }

int turnon(const char* hlt, const char* forest, const char* output) {
   TFile* fhlt = new TFile(hlt, "read");
   TTree* thlt = (TTree*)fhlt->Get("hltbitanalysis/HltTree");

   TFile* ffor = new TFile(forest, "read");
   TTree* teg = (TTree*)ffor->Get("ggHiNtuplizerGED/EventTree");

   thlt->SetBranchStatus("*", 0);
   teg->SetBranchStatus("*", 0);

   SETVAR(int32_t, Run, thlt)
   SETVAR(int32_t, LumiBlock, thlt)
   SETVAR(ULong64_t, Event, thlt)
   SETVAR(uint32_t, run, teg)
   SETVAR(uint32_t, lumis, teg)
   SETVAR(ULong64_t, event, teg)

   std::map<std::tuple<uint32_t, uint32_t, uint64_t>,
      uint64_t> entrymap;

   printf("building entry map...\n");
   uint64_t nhltentries = thlt->GetEntries();
   for (uint64_t i=0; i<nhltentries; ++i) {
      thlt->GetEntry(i);
      entrymap[std::make_tuple(Run, LumiBlock, Event)] = i;
   }

   TRIGGERS(SETBRANCH, thlt, int)

   SETVEC(float, elePt, teg)
   SETVEC(float, eleEta, teg)
   SETVEC(float, elePhi, teg)
   SETVEC(float, eleSCEta, teg)
   SETVEC(float, eleHoverE, teg)
   SETVEC(float, eleSigmaIEtaIEta_2012, teg)
   SETVEC(float, eleEoverPInv, teg)
   SETVEC(float, eleD0, teg)
   SETVEC(float, eleDz, teg)
   SETVEC(float, eledEtaAtVtx, teg)
   SETVEC(float, eledPhiAtVtx, teg)
   SETVEC(int, eleMissHits, teg)

   TH1::SetDefaultSumw2();

   std::map<std::string, std::pair<std::string, std::string>> desc;

   constexpr int nptb = 15;
   constexpr float ptb[nptb + 1] = {
      0, 10, 20, 30, 35, 40, 45, 50, 55,
      60, 70, 80, 100, 120, 150, 200};
   constexpr int nscetab = 14;
   constexpr float scetab[nscetab + 1] = {
      -3.0, -2.5, -2.0, -1.566, -1.4442, -1.0, -0.5,
      0.0, 0.5, 1.0, 1.4442, 1.566, 2.0, 2.5, 3.0};

   BIN(eta, 20, -3.0, 3.0)
   BIN(phi, 32, -3.2, 3.2)
   BIN(hovere, 20, 0, 0.2)
   BIN(sieie, 20, 0, 0.4)
   BIN(eopinv, 15, 0, 0.3)
   BIN(d0, 20, -1.0, 1.0)
   BIN(dz, 20, -1.0, 1.0)
   BIN(detavtx, 16, -1.6, 1.6)
   BIN(dphivtx, 16, -1.6, 1.6)
   BIN(misshits, 8, 0, 8)

   SETUP(loose, nptb, ptb, "H/E < 0.2", ";p_{T};efficiency")
   SETUP(tight, nptb, ptb, "2015 veto ID", ";p_{T};efficiency")

   SETUP(pt, nptb, ptb, "p_{T}", ";p_{T};")
   SETUP(eta, netab, etab, "#eta", ";#eta;")
   SETUP(phi, nphib, phib, "#phi", ";#phi;")
   SETUP(sceta, nscetab, scetab, "#eta_{SC}", ";#eta_{SC};")
   SETUP(hovere, nhovereb, hovereb, "H/E", ";H/E;")
   SETUP(sieie, nsieieb, sieieb, "#sigma_{#eta#eta}", ";#sigma_{#eta#eta};")
   SETUP(eopinv, neopinvb, eopinvb, "1/E-1/p", ";1/E-1/p;")
   SETUP(d0, nd0b, d0b, "track d_{0}", ";d_{0};")
   SETUP(dz, ndzb, dzb, "track d_{z}", ";d_{z};")
   SETUP(detavtx, ndetavtxb, detavtxb, "track #Delta#eta at vertex", ";#Delta#eta;")
   SETUP(dphivtx, ndphivtxb, dphivtxb, "track #Delta#phi at vertex", ";#Delta#phi;")
   SETUP(misshits, nmisshitsb, misshitsb, "missing hits", ";d_{z};")

   printf("event loop\n");
   uint64_t negentries = teg->GetEntries();
   for (uint64_t i=0; i<negentries; ++i) {
      teg->GetEntry(i);

      auto hltentry = entrymap.find(std::make_tuple(
         run, lumis, event));
      if (hltentry == std::end(entrymap)) continue;
      thlt->GetEntry(hltentry->second);

      auto maxele = std::max_element(
         std::begin(*elePt), std::end(*elePt));
      auto index = maxele - std::begin(*elePt);
      float maxPt = (*elePt)[index];

      if ((*eleHoverE)[index] > 0.15) continue;

      FILL(HLT_Ele20Gsf_v1, loose, maxPt)

      FULLOFFLINEID(index)
      FILL(HLT_Ele20Gsf_v1, tight, maxPt)
      INVFILL(HLT_Ele20Gsf_v1, pt, (*elePt)[index])
      INVFILL(HLT_Ele20Gsf_v1, eta, (*eleEta)[index])
      INVFILL(HLT_Ele20Gsf_v1, phi, (*elePhi)[index])
      INVFILL(HLT_Ele20Gsf_v1, sceta, (*eleSCEta)[index])
      INVFILL(HLT_Ele20Gsf_v1, hovere, (*eleHoverE)[index])
      INVFILL(HLT_Ele20Gsf_v1, sieie, (*eleSigmaIEtaIEta_2012)[index])
      INVFILL(HLT_Ele20Gsf_v1, eopinv, (*eleEoverPInv)[index])
      INVFILL(HLT_Ele20Gsf_v1, d0, (*eleD0)[index])
      INVFILL(HLT_Ele20Gsf_v1, dz, (*eleDz)[index])
      INVFILL(HLT_Ele20Gsf_v1, detavtx, (*eledEtaAtVtx)[index])
      INVFILL(HLT_Ele20Gsf_v1, dphivtx, (*eledPhiAtVtx)[index])
      INVFILL(HLT_Ele20Gsf_v1, misshits, (*eleMissHits)[index])

      int index2 = -1; float maxPt2 = 0.;
      for (std::size_t j=0; j<elePt->size() && j!=index; ++j) {
         if ((*elePt)[j] > maxPt2) {
            index2 = j; maxPt2 = (*elePt)[j];
         }
      }

      if (index2 == -1) continue; if (maxPt2 < 20) continue;
      if ((*eleHoverE)[index2] > 0.15) continue;

      FILL(HLT_DoubleEle20Gsf_v1, loose, maxPt)
      FILL(HLT_DoubleEle20Gsf_Mass50_v1, loose, maxPt)

      FULLOFFLINEID(index2)
      FILL(HLT_DoubleEle20Gsf_v1, tight, maxPt)
      FILL(HLT_DoubleEle20Gsf_Mass50_v1, tight, maxPt)
   }

   std::map<std::string, int> colours;
   TRIGGERS(PALETTE)

   SELECTIONS(PRODUCE)
   SELECTIONS(TOCURVE)

   VARIABLES(DISTRIBUTION, HLT_Ele20Gsf_v1)

   return 0;
}

int main(int argc, char* argv[]) {
   if (!(NTRIGGERS)) {
      printf("error: no triggers listed!\n");
      return 2;
   }

   if (argc == 3 && atoi(argv[1]) == 0) {
      return rate(argv[2]);
   } else if (argc == 5 && atoi(argv[1]) == 1) {
      return turnon(argv[2], argv[3], argv[4]);
   } else {
      printf("usage: %s\n"
             "       - 0 [input]\n"
             "       - 1 [hlt] [forest] [output]\n", argv[0]);
      return 1;
   }
}
