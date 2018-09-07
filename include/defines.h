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
#define NEGTRIGGERS (0 EGTRIGGERS(COUNT))

/* scale factor (MB rate, in kHz) */
#define SCALE 50000

#define RATE(TRIGGER, total)                                   \
   uint64_t pass_##TRIGGER = tin->GetEntries(#TRIGGER);        \
   float percent_pass_##TRIGGER =                              \
      (float)pass_##TRIGGER / total;                           \
   printf(#TRIGGER "\n ^ pass: %f%%, rate: %f Hz\n",           \
      percent_pass_##TRIGGER * 100,                            \
      percent_pass_##TRIGGER * SCALE);

#define SETBRANCH(TRIGGER, tree, type)                         \
   SETVAR(type, TRIGGER, tree);

#define SETPERELE(var, tree, type, arg4, arg5)                 \
   SETPERELEIMPL(var, tree, type)
#define SETPERELEIMPL(var, tree, type)                         \
   SETVEC(type, var, tree)

#define SETPEREVT(var, tree, type, arg4, arg5)                 \
   SETPEREVTIMPL(var, tree, type)
#define SETPEREVTIMPL(var, tree, type)                         \
   SETVAR(type, var, tree)

#define BOOK(TRIGGER, label, nbins, bins)                      \
   label.emplace(#TRIGGER, std::make_pair(                     \
      new TH1F(#label "_pass_" #TRIGGER, "", nbins, bins),     \
      new TH1F(#label "_denom_" #TRIGGER, "", nbins, bins)));

#define FILL(TRIGGER, label, val)                              \
   if (TRIGGER) label[#TRIGGER].first->Fill(val);              \
   label[#TRIGGER].second->Fill(val);

#define INVFILLPERELE(var, TRIGGER, arg3, arg4, arg5)          \
   INVFILLPERELEIMPL(var, TRIGGER)
#define INVFILLPERELEIMPL(var, TRIGGER)                        \
   INVFILL(TRIGGER, v##var, (*var)[index])

#define INVFILLPEREVT(var, TRIGGER, arg3, arg4, arg5)          \
   INVFILLPEREVTIMPL(var, TRIGGER)
#define INVFILLPEREVTIMPL(var, TRIGGER)                        \
   INVFILL(TRIGGER, v##var, var)

#define INVFILL(TRIGGER, label, val)                           \
   if (!TRIGGER) label[#TRIGGER].first->Fill(val);             \
   else label[#TRIGGER].second->Fill(val);

#define PALETTE(TRIGGER)                                       \
   colours.emplace(#TRIGGER, -1);                              \
   colours[#TRIGGER] = palette[(colours.size() - 1)            \
      % palette.size()];

#define STYLE(TRIGGER, label)                                  \
   g##label[#TRIGGER]->SetLineColor(colours[#TRIGGER]);        \
   g##label[#TRIGGER]->SetMarkerColor(colours[#TRIGGER]);      \
   g##label[#TRIGGER]->SetMarkerSize(0.4);                     \
   g##label[#TRIGGER]->SetMarkerStyle(21);

#define DRAW(TRIGGER, label, tag)                              \
   g##label[#TRIGGER]->Draw("same");                           \
   l##label##tag->AddEntry(g##label[#TRIGGER], #TRIGGER, "pl");

#define DECORATE(obj)                                          \
   obj->SetMarkerSize(0.8); obj->SetMarkerStyle(21);

#define PAINT(TRIGGER, label, obj, opt)                        \
   obj->Draw("same " #opt);                                    \
   l##label##TRIGGER->AddEntry(obj, #TRIGGER, "pl");

#define SETUP(label, nbins, bins, info, title)                 \
   std::map<std::string, std::pair<TH1F*, TH1F*>> label;       \
   desc.emplace(#label, std::make_pair(info, title));          \
   EGTRIGGERS(BOOK, label, nbins, bins)

#define SELSETUP(sel, info)                                    \
   SETUP(sel, nptb, ptb, info, ";p_{T};efficiency")

#define VARSETUP(var, arg2, info, title)                       \
   VARSETUPIMPL(var, info, title)
#define VARSETUPIMPL(var, info, title)                         \
   SETUP(v##var, n##var##b, var##b, info, title)

#define VAREFF(var, TRIGGER, arg2, arg3, arg4)                 \
   VAREFFIMPL(var, TRIGGER)
#define VAREFFIMPL(var, TRIGGER)                               \
   std::map<std::string, TH1F*> var##e;                        \
   var##e[#TRIGGER] = (TH1F*)v##var[#TRIGGER].first->Clone(    \
      #var "_eff_" #TRIGGER);                                  \
   var##e[#TRIGGER]->Divide(v##var[#TRIGGER].second);

#define PAPER(label, tag, n)                                   \
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
   float l##label##tag##y0 = std::max(0.12, 0.48 - 0.04 * n);  \
   float l##label##tag##y1 = std::min(0.60,                    \
      l##label##tag##y0 + 0.04 * n);                           \
   TLegend* l##label##tag = new TLegend(                       \
      0.32, l##label##tag##y0, 0.9, l##label##tag##y1);        \
   l##label##tag->SetFillStyle(0);                             \
   l##label##tag->SetBorderSize(0);                            \
   l##label##tag->SetTextFont(43);                             \
   l##label##tag->SetTextSize(12);

#define SAVE(label, tag)                                       \
   c##label##tag->SaveAs(Form(                                 \
      "figs/pdf/" #label "-" #tag "-%s.pdf", output));         \
   c##label##tag->SaveAs(Form(                                 \
      "figs/png/" #label "-" #tag "-%s.png", output));

#define DIVIDE(label, arg2)                                    \
   std::map<std::string, TGraphAsymmErrors*> g##label;         \
   EGTRIGGERS(DIVIDEIMPL, label)
#define DIVIDEIMPL(TRIGGER, label)                             \
   g##label.emplace(#TRIGGER, new TGraphAsymmErrors(           \
      label[#TRIGGER].first->GetNbinsX() + 2));                \
   g##label[#TRIGGER]->Divide(                                 \
      label[#TRIGGER].first, label[#TRIGGER].second,           \
      "c1=0.683 b(1,1) mode");

#define GRAPH(label, tag, TSET)                                \
   PAPER(label, tag, ( 0 TSET(COUNT)))                         \
   TSET(STYLE, label) TSET(DRAW, label, tag)                   \
   l##label##tag->Draw(); SAVE(label, tag)

#define TOC(label, set, arg3) GRAPH(label, turnon_##set, set)

#define AUTOYRANGE(label, TRIGGER)                             \
   hfr##label##TRIGGER->SetAxisRange(                          \
      0, label[#TRIGGER].first->GetBinContent(                 \
         label[#TRIGGER].first->GetMaximumBin()) * 1.2, "Y");  \

#define DISTRIBUTIONS(label, TRIGGER, arg3, arg4, arg5)        \
   DISTRNIMPL(label, TRIGGER)
#define DISTRNIMPL(label, TRIGGER)                             \
   PAPER(v##label, TRIGGER, 1) AUTOYRANGE(v##label, TRIGGER)   \
   DECORATE(v##label[#TRIGGER].first)                          \
   PAINT(TRIGGER, v##label, v##label[#TRIGGER].first, pe)      \
   l##v##label##TRIGGER->Draw(); SAVE(v##label, TRIGGER)       \
   PAPER(v##label, e##TRIGGER, 1) DECORATE(label##e[#TRIGGER]) \
   label##e[#TRIGGER]->SetAxisRange(0, 0.2, "Y");              \
   PAINT(TRIGGER, v##label##e, label##e[#TRIGGER], pe)         \
   l##v##label##e##TRIGGER->Draw(); SAVE(v##label, e##TRIGGER)

#endif /* _DEFINES_H */
