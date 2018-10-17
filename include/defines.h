#ifndef _DEFINES_H
#define _DEFINES_H

#define CONCATENATE(a, b) a##b
#define CAT(a, b) CONCATENATE(a, b)

#define SETVAR(type, var, tree)                                \
   type var;                                                   \
   tree->SetBranchStatus(#var, 1);                             \
   tree->SetBranchAddress(#var, &var);

#define MAXSIZE 2000

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

#define BIN(var, a0, nbins, min, max, ...)                     \
   constexpr int n##var##b = nbins;                            \
   auto a##var##b = edges<n##var##b>(                          \
      min, max, expand<n##var##b>{});                          \
   float* var##b = a##var##b.data();

#define COUNT(OBJ) + 1

/* scale factor (MB rate, in kHz) */
#define SCALE 40000

#define RATE(TRIGGER, total)                                   \
   if (branches->FindObject(#TRIGGER)) {                       \
      uint64_t npass_##TRIGGER = tin->GetEntries(#TRIGGER);    \
      float ppass_##TRIGGER = (float)npass_##TRIGGER / total;  \
      printf("%50s > %9.5f > %9.3f\n", #TRIGGER,               \
         ppass_##TRIGGER * 100, ppass_##TRIGGER * SCALE); }

#define DEBUG(TRIGGER, condition, label, value)                \
   if (!TRIGGER && condition) dbginfo[event][#label] = value;

#define DEBUGSUMMARY                                           \
   for (auto& event : dbginfo)                                 \
      for (auto& var : event.second)                           \
         printf("event: %zu, %s: %f\n",                        \
            event.first, var.first.data(), var.second);        \
   printf("counts: %zu\n", dbginfo.size());

#define SETBRANCH(TRIGGER, tree, type)                         \
   SETVAR(type, TRIGGER, tree);

#define SETPERELE(var, tree, type, ...)                        \
   SETVEC(type, var, tree)

#define SETPEREVT(var, tree, type, ...)                        \
   SETVAR(type, var, tree)

#define SELDECL(sel, a0, info)                                 \
   DECLARE(sel, info, ";p_{T};efficiency;")

#define DECLARE(label, info, title)                            \
   std::map<std::string, std::pair<TH1F*, TH1F*>> label;       \
   std::map<std::string, TGraphAsymmErrors*> g##label;         \
   desc.emplace(#label, std::make_pair(info, title));

#define BOOK(TRIGGER, label, nbins, bins)                      \
   label.emplace(#TRIGGER, std::make_pair(                     \
      new TH1F(#label "_pass_" #TRIGGER, "", nbins, bins),     \
      new TH1F(#label "_denom_" #TRIGGER, "", nbins, bins)));

#define ACT(ACTION, ...) ACTION(__VA_ARGS__)

#define SELECT(sel, TRIGGERS, val, condition, ...)             \
   if (condition) { TRIGGERS(FILL, sel, val) }

#define DEGTRIGGERSPT(ACTION, ...)                             \
   if (maxPt2 > 10) {                                          \
      DEGMIN10TRIGGERS(ACTION, ## __VA_ARGS__)                 \
      if (maxPt2 > 15) {                                       \
         DEGMIN15TRIGGERS(ACTION, ## __VA_ARGS__) }}

#define FILL(TRIGGER, label, val)                              \
   if (TRIGGER) label[#TRIGGER].first->Fill(val);              \
   label[#TRIGGER].second->Fill(val);

#define FWDFILL(...) FILL(__VA_ARGS__)

#define INVFILL(TRIGGER, label, val)                           \
   if (!TRIGGER) label[#TRIGGER].first->Fill(val);             \
   label[#TRIGGER].second->Fill(val);

#define FILLPERELE(var, DIR, TRIGGERS, ...)                    \
   TRIGGERS(CAT(DIR, FILL), v##var, (*var)[index])

#define FILLPEREVT(var, DIR, TRIGGERS, ...)                    \
   TRIGGERS(CAT(DIR, FILL), v##var, var)

#define PALETTE(T)                                             \
   colours[#T] = palette[(colours.size()) % palette.size()];

#define STYLE(TRIGGER, label)                                  \
   g##label[#TRIGGER]->SetLineColor(colours[#TRIGGER]);        \
   g##label[#TRIGGER]->SetMarkerColor(colours[#TRIGGER]);      \
   g##label[#TRIGGER]->SetMarkerSize(0.4);                     \
   g##label[#TRIGGER]->SetMarkerStyle(21);

#define DRAW(TRIGGER, l, t)                                    \
   g##l[#TRIGGER]->Draw("same");                               \
   lg##l##t->AddEntry(g##l[#TRIGGER], #TRIGGER, "pl");

#define DECORATE(obj)                                          \
   obj->SetMarkerSize(0.8); obj->SetMarkerStyle(21);

#define PAINT(TRIGGER, label, obj, opt)                        \
   obj->Draw("same " #opt);                                    \
   lg##label##TRIGGER->AddEntry(obj, #TRIGGER, "pl");

#define SETUP(label, TRIGGERS, nbins, bins)                    \
   TRIGGERS(BOOK, label, nbins, bins)

#define SELSETUP(sel, TRIGGERS, ...)                           \
   SELSETUPIMPL(sel, TRIGGERS)
#define SELSETUPIMPL(sel, TRIGGERS)                            \
   SETUP(sel, TRIGGERS, nptb, ptb)

#define VARSETUP(var, TRIGGERS, a0, a1, a2, a3, info, title)   \
   VARSETUPIMPL(var, TRIGGERS, info, title)
#define VARSETUPIMPL(var, TRIGGERS, info, title)               \
   DECLARE(v##var, info, title);                               \
   SETUP(v##var, TRIGGERS, n##var##b, var##b)

#define VAREFF(var, TRIGGERS, ...)                             \
   std::map<std::string, TGraphAsymmErrors*> e##var;           \
   ACT(TRIGGERS, VAREFFIMPL, var)
#define VAREFFIMPL(TRIGGER, var)                               \
   e##var[#TRIGGER] = new TGraphAsymmErrors(                   \
      v##var[#TRIGGER].first->GetNbinsX() + 2);                \
   e##var[#TRIGGER]->Divide(                                   \
      v##var[#TRIGGER].first, v##var[#TRIGGER].second,         \
      "c1=0.683 b(1,1) mode");

#define PAPER(l, t, n)                                         \
   TCanvas* c##l##t = new TCanvas("c" #l #t, "", 400, 400);    \
   auto hp##l##t = (*l.begin()).second.first;                  \
   float min##l##t = hp##l##t->GetBinLowEdge(1);               \
   float max##l##t = hp##l##t->GetBinLowEdge(                  \
         hp##l##t->GetNbinsX() + 1);                           \
   TH1F* hfr##l##t = new TH1F("hfr" #l #t, "",                 \
      1, min##l##t, max##l##t);                                \
   hfr##l##t->SetAxisRange(0, 1.2, "Y");                       \
   hfr##l##t->SetTitle(desc[#l].second.data());                \
   hfr##l##t->SetStats(0); hfr##l##t->Draw();                  \
   TLatex* tex##l##t = new TLatex();                           \
   tex##l##t->SetTextFont(43); tex##l##t->SetTextSize(12);     \
   tex##l##t->DrawLatexNDC(0.6, 0.84, desc[#l].first.data());  \
   if (desc[#l].second.find("eff") != std::string::npos) {     \
      TLine* unity = new TLine(min##l##t, 1, max##l##t, 1);    \
      unity->SetLineStyle(7); unity->Draw(); }                 \
   float l##t##y0 = std::max(0.12, 0.48 - n * 0.04);           \
   float l##t##y1 = std::min(0.60, l##t##y0 + n * 0.04);       \
   TLegend* lg##l##t = new TLegend(                            \
      0.32, l##t##y0, 0.9, l##t##y1);                          \
   lg##l##t->SetFillStyle(0); lg##l##t->SetBorderSize(0);      \
   lg##l##t->SetTextFont(43); lg##l##t->SetTextSize(12);

#define SAVE(label, tag)                                       \
   c##label##tag->SaveAs(Form(                                 \
      "figs/pdf/" #label "-" #tag "-%s.pdf", output));         \
   c##label##tag->SaveAs(Form(                                 \
      "figs/png/" #label "-" #tag "-%s.png", output));

#define DIVIDE(label, TRIGGERS, ...)                           \
   ACT(TRIGGERS, DIVIDEIMPL, label)
#define DIVIDEIMPL(TRIGGER, label)                             \
   g##label.emplace(#TRIGGER, new TGraphAsymmErrors(           \
      label[#TRIGGER].first->GetNbinsX() + 2));                \
   g##label[#TRIGGER]->Divide(                                 \
      label[#TRIGGER].first, label[#TRIGGER].second,           \
      "c1=0.683 b(1,1) mode");

#define GRAPH(label, TRIGGERS, ...)                            \
   PAPER(label, to##TRIGGERS, ( 0 TRIGGERS(COUNT)))            \
   TRIGGERS(STYLE, label) TRIGGERS(DRAW, label, to##TRIGGERS)  \
   lg##label##to##TRIGGERS->Draw(); SAVE(label, to##TRIGGERS)

#define AUTOYRANGE(label, TRIGGER)                             \
   hfr##label##TRIGGER->SetAxisRange(                          \
      0, label[#TRIGGER].first->GetBinContent(                 \
         label[#TRIGGER].first->GetMaximumBin()) * 1.2, "Y");  \

#define DISTRN(label, TRIGGERS, ...)                           \
   ACT(TRIGGERS, DISTRNIMPL, label)
#define DISTRNIMPL(TRIGGER, label)                             \
   PAPER(v##label, TRIGGER, 1) AUTOYRANGE(v##label, TRIGGER)   \
   DECORATE(v##label[#TRIGGER].first)                          \
   PAINT(TRIGGER, v##label, v##label[#TRIGGER].first, pe)      \
   lg##v##label##TRIGGER->Draw(); SAVE(v##label, TRIGGER)      \
   PAPER(v##label, e##TRIGGER, 1) DECORATE(e##label[#TRIGGER]) \
   PAINT(TRIGGER, v##label##e, e##label[#TRIGGER], pe)         \
   lg##v##label##e##TRIGGER->Draw(); SAVE(v##label, e##TRIGGER)

#endif /* _DEFINES_H */
