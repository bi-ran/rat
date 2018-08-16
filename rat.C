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
#include "lists.h"

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
   thlt->SetBranchStatus("*", 0);

   TFile* ffor = new TFile(forest, "read");
   TTree* teg = (TTree*)ffor->Get("ggHiNtuplizerGED/EventTree");
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

   TH1::SetDefaultSumw2();

   TRIGGERS(SETBRANCH, thlt, int)
   VARIABLES(VARSETBRANCH, teg)

   std::map<std::string, std::pair<std::string, std::string>> desc;
   SETUPTOBINS
   SETUP(loose, nptb, ptb, "H/E < 0.2", ";p_{T};efficiency")
   SETUP(tight, nptb, ptb, "2015 veto ID", ";p_{T};efficiency")

   SETUPVARBINS
   VARIABLES(VARSETUP)

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

      SEGTRIGGERS(FILL, loose, maxPt)
      FULLOFFLINEID(index)
      SEGTRIGGERS(FILL, tight, maxPt)

      VARIABLES(VARINVFILL, HLT_Ele20Gsf_v1)

      int index2 = -1; float maxPt2 = 0.;
      for (std::size_t j=0; j<elePt->size() && j!=index; ++j) {
         if ((*elePt)[j] > maxPt2) {
            index2 = j; maxPt2 = (*elePt)[j];
         }
      }

      if (index2 == -1) continue; if (maxPt2 < 20) continue;
      if ((*eleHoverE)[index2] > 0.15) continue;

      DEGTRIGGERS(FILL, loose, maxPt)
      FULLOFFLINEID(index2)
      DEGTRIGGERS(FILL, tight, maxPt)
   }

   std::map<std::string, int> colours;
   TRIGGERS(PALETTE)

   SELECTIONS(PRODUCE)
   SELECTIONS(TOCURVE)

   VARIABLES(VAREFF, HLT_Ele20Gsf_v1)
   VARIABLES(DISTRIBUTIONS, HLT_Ele20Gsf_v1)

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
