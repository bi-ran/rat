#ifndef _DEFINES_H
#define _DEFINES_H

#define SETVAR(type, var, tree)                                \
   type var;                                                   \
   tree->SetBranchStatus(#var, 1);                             \
   tree->SetBranchAddress(#var, &var);

#define MAXSIZE 2000

#define SETARR(type, var, tree)                                \
   type var[MAXSIZE];                                          \
   tree->SetBranchStatus(#var, 1);                             \
   tree->SetBranchAddress(#var, var);

#define SETVEC(type, var, tree)                                \
   std::vector<type>* var = 0;                                 \
   tree->SetBranchStatus(#var, 1);                             \
   tree->SetBranchAddress(#var, &var);

#define VETOIDBARREL(index)                                    \
   if ((*eleSigmaIEtaIEta_2012)[index] > 0.01107) continue;    \
   if (fabs((*eledEtaAtVtx)[index]) > 0.01576) continue;       \
   if (fabs((*eledPhiAtVtx)[index]) > 0.15724) continue;       \
   if ((*eleHoverE)[index] > 0.08849) continue;                \
   if ((*eleEoverPInv)[index] > 0.28051) continue;             \
   if (fabs((*eleD0)[index]) > 0.05216) continue;              \
   if (fabs((*eleDz)[index]) > 0.12997) continue;              \
   if ((*eleMissHits)[index] > 1) continue;

#define VETOIDENDCAP(index)                                    \
   if ((*eleSigmaIEtaIEta_2012)[index] > 0.03488) continue;    \
   if (fabs((*eledEtaAtVtx)[index]) > 0.01707) continue;       \
   if (fabs((*eledPhiAtVtx)[index]) > 0.35537) continue;       \
   if ((*eleHoverE)[index] > 0.12275) continue;                \
   if ((*eleEoverPInv)[index] > 0.18672) continue;             \
   if (fabs((*eleD0)[index]) > 0.19092) continue;              \
   if (fabs((*eleDz)[index]) > 0.26407) continue;              \
   if ((*eleMissHits)[index] > 1) continue;

#define FULLOFFLINEID(index)                                   \
   if (fabs((*eleSCEta)[index]) < 1.4442) {                    \
      VETOIDBARREL(index)                                      \
   } else if (fabs((*eleSCEta)[index]) > 1.566) {              \
      if (fabs((*eleSCEta)[index]) > 2.5) continue;            \
      VETOIDENDCAP(index)                                      \
   } else { continue; }

#define BIN(var, num, min, max)                                \
   constexpr int n##var##b = num;                              \
   auto a##var##b = edges<n##var##b>(                          \
      min, max, expand<n##var##b>{});                          \
   float* var##b = a##var##b.data();

#define COUNT(OBJ) + 1
#define NTRIGGERS (0 TRIGGERS(COUNT))

/* scale factor for MB to kHz */
#define SCALE 100000

#define RATE(TRIGGER, total)                                   \
   uint64_t pass_##TRIGGER = tin->GetEntries(#TRIGGER);        \
   float percent_pass_##TRIGGER =                              \
      (float)pass_##TRIGGER / total;                           \
   printf(#TRIGGER "\n ^ pass: %f%%, rate: %f Hz\n",           \
      percent_pass_##TRIGGER * 100,                            \
      percent_pass_##TRIGGER * SCALE);

#define SETBRANCH(TRIGGER, tree, type)                         \
   SETVAR(type, TRIGGER, tree);

#define VARSETBRANCH(var, tree, type, arg4, arg5)              \
   VARSETBRIMPL(var, tree, type)

#define VARSETBRIMPL(var, tree, type)                          \
   SETVEC(type, ele##var, tree)

#define BOOK(TRIGGER, label, nbins, bins)                      \
   label.emplace(#TRIGGER, std::make_pair(                     \
      new TH1F(#label "_pass_" #TRIGGER, "", nbins, bins),     \
      new TH1F(#label "_denom_" #TRIGGER, "", nbins, bins)));

#define FILL(TRIGGER, label, val)                              \
   if (TRIGGER) label[#TRIGGER].first->Fill(val);              \
   label[#TRIGGER].second->Fill(val);

#define VARINVFILL(var, TRIGGER, arg3, arg4, arg5)             \
   VARINVFILLIMPL(var, TRIGGER)

#define VARINVFILLIMPL(var, TRIGGER)                           \
   INVFILL(TRIGGER, var, (*ele##var)[index])

#define INVFILL(TRIGGER, label, val)                           \
   if (!TRIGGER) label[#TRIGGER].first->Fill(val);             \
   else label[#TRIGGER].second->Fill(val);

#define PALETTE(TRIGGER)                                       \
   colours.emplace(#TRIGGER, -1);                              \
   colours[#TRIGGER] = palette[(colours.size() - 1)            \
      % palette.size()];

#define DIVIDE(TRIGGER, label)                                 \
   g##label.emplace(#TRIGGER, new TGraphAsymmErrors(           \
      label[#TRIGGER].first->GetNbinsX() + 2));                \
   g##label[#TRIGGER]->Divide(                                 \
      label[#TRIGGER].first, label[#TRIGGER].second,           \
      "c1=0.683 b(1,1) mode");

#define STYLE(TRIGGER, label)                                  \
   g##label[#TRIGGER]->SetLineColor(colours[#TRIGGER]);        \
   g##label[#TRIGGER]->SetMarkerColor(colours[#TRIGGER]);      \
   g##label[#TRIGGER]->SetMarkerSize(0.4);                     \
   g##label[#TRIGGER]->SetMarkerStyle(21);

#define DRAW(TRIGGER, label, tag)                              \
   g##label[#TRIGGER]->Draw("same");                           \
   l##label##tag->AddEntry(g##label[#TRIGGER], #TRIGGER, "pl");

#define DECORATE(TRIGGER, label)                               \
   label[#TRIGGER].first->SetMarkerSize(0.8);                  \
   label[#TRIGGER].first->SetMarkerStyle(21);

#define PAINT(TRIGGER, label)                                  \
   label[#TRIGGER].first->Draw("same pe");                     \
   l##label##TRIGGER->AddEntry(                                \
      label[#TRIGGER].first, #TRIGGER, "pl");

#define SETUP(label, nbins, bins, info, title)                 \
   std::map<std::string, std::pair<TH1F*, TH1F*>> label;       \
   desc.emplace(#label, std::make_pair(info, title));          \
   TRIGGERS(BOOK, label, nbins, bins)

#define VARSETUP(var, arg2, info, title)                       \
   VARSETUPIMPL(var, info, title)

#define VARSETUPIMPL(var, info, title)                         \
   SETUP(var, n##var##b, var##b, info, title)

#define PRODUCE(label)                                         \
   std::map<std::string, TGraphAsymmErrors*> g##label;         \
   TRIGGERS(DIVIDE, label)

#define PAPER(label, tag)                                      \
   TCanvas* c##label##tag = new TCanvas(                       \
      "c" #label #tag, "", 400, 400);                          \
   TH1F* hfr##label##tag = new TH1F("hfr" #label #tag, "", 1,  \
      (*label.begin()).second.first->GetBinLowEdge(1),         \
      (*label.begin()).second.first->GetBinLowEdge(            \
         (*label.begin()).second.first->GetNbinsX() + 1));     \
   hfr##label##tag->SetAxisRange(0, 1.2, "Y");                 \
   hfr##label##tag->SetTitle(desc[#label].second.data());      \
   hfr##label##tag->SetStats(0); hfr##label##tag->Draw();      \
   TLatex* tex##label##tag = new TLatex();                     \
   tex##label##tag->SetTextFont(43);                           \
   tex##label##tag->SetTextSize(12);                           \
   tex##label##tag->DrawLatexNDC(0.60, 0.84,                   \
      desc[#label].first.data());                              \
   if (desc[#label].second.find("efficiency")                  \
         != std::string::npos) {                               \
      TLine* unity = new TLine(                                \
         (*label.begin()).second.first->GetBinLowEdge(1), 1,   \
         (*label.begin()).second.first->GetBinLowEdge(         \
            (*label.begin()).second.first->GetNbinsX()+1), 1); \
      unity->SetLineStyle(7); unity->Draw(); }                 \
   TLegend* l##label##tag = new TLegend(0.32, 0.3, 0.9, 0.42); \
   l##label##tag->SetFillStyle(0);                             \
   l##label##tag->SetBorderSize(0);                            \
   l##label##tag->SetTextFont(43);                             \
   l##label##tag->SetTextSize(12);

#define SAVE(label, tag)                                       \
   c##label##tag->SaveAs(Form(                                 \
      #label "-" #tag "-%s.pdf", output));                     \
   c##label##tag->SaveAs(Form(                                 \
      #label "-" #tag "-%s.png", output));

#define GRAPH(label, tag)                                      \
   PAPER(label, tag) TRIGGERS(STYLE, label)                    \
   TRIGGERS(DRAW, label, tag)                                  \
   l##label##tag->Draw(); SAVE(label, tag)

#define TOCURVE(label) GRAPH(label, turnon)

#define SETYRANGE(label, TRIGGER)                              \
   hfr##label##TRIGGER->SetAxisRange(                          \
      0, label[#TRIGGER].first->GetBinContent(                 \
         label[#TRIGGER].first->GetMaximumBin()) * 1.2, "Y");  \

#define DISTRIBUTION(label, TRIGGER, arg3, arg4, arg5)         \
   DISTRNIMPL(label, TRIGGER)

#define DISTRNIMPL(label, TRIGGER)                             \
   PAPER(label, TRIGGER) SETYRANGE(label, TRIGGER)             \
   DECORATE(TRIGGER, label) PAINT(TRIGGER, label)              \
   l##label##TRIGGER->Draw(); SAVE(label, TRIGGER)

#endif /* _DEFINES_H */
