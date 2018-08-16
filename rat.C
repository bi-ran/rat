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

#include "include/defines.h"
#include "include/lists.h"

std::vector<int> palette = {
   TColor::GetColor("#f2777a"),
   TColor::GetColor("#f9a257"),
   TColor::GetColor("#99cc99"),
   TColor::GetColor("#66cccc"),
   TColor::GetColor("#6699cc"),
   TColor::GetColor("#9966cc")
};

int rate(const char* input) {
   TFile* fin = new TFile(input, "read");
   TTree* tin = (TTree*)fin->Get("hltbitanalysis/HltTree");

   auto branches = tin->GetListOfBranches();

   uint64_t nentries = tin->GetEntries();
   EGTRIGGERS(RATE, nentries)
   EGXMUTRIGGERS(RATE, nentries)
   LXJETTRIGGERS(RATE, nentries)

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

constexpr float hfc5ev8[21] = {
   0.0000, 13.708, 17.489, 22.965, 33.699,
   53.345, 78.712, 117.59, 171.80, 245.83,
   339.12, 453.95, 610.02, 795.81, 1024.8,
   1306.1, 1621.9, 2026.1, 2499.6, 3095.0, 50000
};

int turnon(const char* hlt, const char* skim, const char* output) {
   TFile* fhlt = new TFile(hlt, "read");
   TTree* thlt = (TTree*)fhlt->Get("hltbitanalysis/HltTree");
   thlt->SetBranchStatus("*", 0);

   TFile* fs = new TFile(skim, "read");
   TTree* teg = (TTree*)fs->Get("electrons");
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

   EGTRIGGERS(SETBRANCH, thlt, int)
   VARSPERELE(SETPERELE, teg)
   VARSPEREVT(SETPEREVT, teg)

   std::map<std::string, std::pair<std::string, std::string>> desc;
   std::map<uint64_t, std::map<std::string, float>> dbginfo;

   constexpr int nptb = 15;
   constexpr float ptb[nptb + 1] = {
      0, 10, 15, 20, 25, 30, 35, 40,
      45, 50, 55, 60, 70, 80, 100, 120};
   SELECTIONS(SELSETUP, EGTRIGGERS)

   ALLVARS(BIN)
   ALLVARS(VARSETUP, SEGTRIGGERS)

   printf("event loop\n");
   uint64_t negentries = teg->GetEntries();
   for (uint64_t i=0; i<negentries; ++i) {
      teg->GetEntry(i);

      auto hltentry = entrymap.find(std::make_tuple(
         run, lumis, event));
      if (hltentry == std::end(entrymap)) continue;
      thlt->GetEntry(hltentry->second);

      if (elePt->empty()) continue;
      auto maxele = std::max_element(
         std::begin(*elePt), std::end(*elePt));
      auto index = maxele - std::begin(*elePt);
      float maxPt = (*elePt)[index];

      if ((*eleHoverE)[index] > 0.2) continue;

      SEGTRIGGERS(FILL, loose, maxPt)
      FULLOFFLINEID(index)
      SEGTRIGGERS(FILL, tight, maxPt)

      if (fabs((*eleSCEta)[index]) < 1.4442)
      { SEGTRIGGERS(FILL, barrel, maxPt) }
      if (fabs((*eleSCEta)[index]) > 1.566)
      { SEGTRIGGERS(FILL, endcap, maxPt) }

      if (hiHF > hfc5ev8[14])
      { SEGTRIGGERS(FILL, central, maxPt) }
      if (hiHF <= hfc5ev8[14])
      { SEGTRIGGERS(FILL, peripheral, maxPt) }

      VARSPERELE(FILLPERELE, FWD, SEGTRIGGERS)
      VARSPEREVT(FILLPEREVT, FWD, SEGTRIGGERS)

      DEBUG(HLT_Ele15GsfUM_v1,
         maxPt > 80, pt, (*elePt)[index])

      int index2 = -1; float maxPt2 = 0.;
      for (std::size_t j=0; j<elePt->size()
            && j!=(uint32_t)index; ++j) {
         if ((*elePt)[j] > maxPt2) {
            index2 = j; maxPt2 = (*elePt)[j]; }}

      if (index2 == -1) continue;
      if (maxPt2 < 10) continue;
      if ((*eleHoverE)[index2] > 0.2) continue;

      DEGTRIGGERSPT(FILL, loose, maxPt)
      FULLOFFLINEID(index2)
      DEGTRIGGERSPT(FILL, tight, maxPt)

      if (hiHF > hfc5ev8[14])
      { DEGTRIGGERSPT(FILL, central, maxPt) }
      if (hiHF <= hfc5ev8[14])
      { DEGTRIGGERSPT(FILL, peripheral, maxPt) }
   }

   std::map<std::string, int> colours;
   EGTRIGGERS(PALETTE)

   SELECTIONS(DIVIDE)
   SELECTIONS(TOC, SEGTRIGGERS)
   SELECTIONS(TOC, DEGTRIGGERS)

   ALLVARS(VAREFF, SEGTRIGGERS)
   ALLVARS(DISTRN, SEGTRIGGERS)

   DEBUGSUMMARY

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 3 && atoi(argv[1]) == 0) {
      return rate(argv[2]);
   } else if (argc == 5 && atoi(argv[1]) == 1) {
      return turnon(argv[2], argv[3], argv[4]);
   } else {
      printf("usage: %s\n"
             "       - 0 [input]\n"
             "       - 1 [hlt] [skim] [output]\n", argv[0]);
      return 1;
   }
}
