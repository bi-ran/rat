#ifndef _DEFINES_H
#define _DEFINES_H

/* scale factor for MB to kHz */
#define SCALE 100000

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

#define TRIGGERS(ACTION, ...)                                  \
   ACTION(HLT_Ele20Gsf_v1, ## __VA_ARGS__)                     \
   ACTION(HLT_DoubleEle20Gsf_v1, ## __VA_ARGS__)               \
   ACTION(HLT_DoubleEle20Gsf_Mass50_v1, ## __VA_ARGS__)

#define COUNT(OBJ) + 1
#define NTRIGGERS (0 TRIGGERS(COUNT))

#define RATE(TRIGGER, total)                                   \
   uint64_t pass_##TRIGGER = tin->GetEntries(#TRIGGER);        \
   float percent_pass_##TRIGGER =                              \
      (float)pass_##TRIGGER / total;                           \
   printf(#TRIGGER "\n ^ pass: %f%%, rate: %f Hz\n",           \
      percent_pass_##TRIGGER * 100,                            \
      percent_pass_##TRIGGER * SCALE);

#define SETBRANCH(TRIGGER, tree, type)                         \
   SETVAR(type, TRIGGER, tree);

#define BOOK(TRIGGER, label, nbins, bins)                      \
   label.emplace(#TRIGGER, std::make_pair(                     \
      new TH1F(#label "_pass_" #TRIGGER, "", nbins, bins),     \
      new TH1F(#label "_denom_" #TRIGGER, "", nbins, bins)));

#define FILL(TRIGGER, label, val)                              \
   if (TRIGGER) label[#TRIGGER].first->Fill(val);              \
   label[#TRIGGER].second->Fill(val);

#define PALETTE(TRIGGER)                                       \
   colours.emplace(#TRIGGER, -1);                              \
   colours[#TRIGGER] = palette[(colours.size() - 1)            \
      % palette.size()];

#define DIVIDE(TRIGGER, label)                                 \
   g##label.emplace(#TRIGGER, new TGraphAsymmErrors(nbins+2)); \
   g##label[#TRIGGER]->Divide(                                 \
      label[#TRIGGER].first, label[#TRIGGER].second,           \
      "c1=0.683 b(1,1) mode");

#define STYLE(TRIGGER, label)                                  \
   g##label[#TRIGGER]->SetLineColor(colours[#TRIGGER]);        \
   g##label[#TRIGGER]->SetMarkerColor(colours[#TRIGGER]);      \
   g##label[#TRIGGER]->SetMarkerStyle(20);

#define DRAW(TRIGGER, label)                                   \
   g##label[#TRIGGER]->SetMarkerSize(0.4);                     \
   g##label[#TRIGGER]->Draw("same");                           \
   l##label->AddEntry(g##label[#TRIGGER], #TRIGGER, "pl");

#define GRAPHS(ACTION)        \
   ACTION(loose)              \
   ACTION(tight)

#define PRODUCE(label)                                         \
   std::map<std::string, TGraphAsymmErrors*> g##label;         \
   TRIGGERS(DIVIDE, label) TRIGGERS(STYLE, label)

#define PAPER(label)                                           \
   TCanvas* c##label = new TCanvas("c" #label, "", 400, 400);  \
   TH1F* href##label = (*label.begin()).second.first;          \
   TH1F* hframe##label = new TH1F(                             \
      "hframe" #label, "", 1,                                  \
      href##label->GetBinLowEdge(1),                           \
      href##label->GetBinLowEdge(                              \
         href##label->GetNbinsX()));                           \
   hframe##label->SetAxisRange(0, 1.2, "Y");                   \
   hframe##label->SetTitle(desc[#label].second.data());        \
   hframe##label->SetStats(0); hframe##label->Draw();          \
   TLatex* tex##label = new TLatex();                          \
   tex##label->SetTextFont(43); tex##label->SetTextSize(12);   \
   tex##label->DrawLatexNDC(0.72, 0.84,                        \
      desc[#label].first.data());                              \
   if (desc[#label].second.find("efficiency")                  \
         != std::string::npos) {                               \
      TLine* unity = new TLine(href##label->GetBinLowEdge(1),  \
         1, href##label->GetBinLowEdge(                        \
            href##label->GetNbinsX()), 1);                     \
      unity->SetLineStyle(7); unity->Draw(); }                 \
   TLegend* l##label = new TLegend(0.32, 0.4, 0.9, 0.52);      \
   l##label->SetFillStyle(0); l##label->SetBorderSize(0);      \
   l##label->SetTextFont(43); l##label->SetTextSize(12);

#define SAVE(label)                                            \
   c##label->SaveAs(Form(#label "-turnon-%s.pdf", output));    \
   c##label->SaveAs(Form(#label "-turnon-%s.png", output));

#define PLOT(label)                                            \
   PAPER(label) TRIGGERS(DRAW, label) l##label->Draw();        \
   SAVE(label)

#define VARIABLES(ACTION)     \
   ACTION(pt)                 \
   ACTION(eta)                \
   ACTION(phi)                \
   ACTION(sceta)              \
   ACTION(hovere)             \
   ACTION(sieie)              \
   ACTION(eopinv)             \
   ACTION(d0)                 \
   ACTION(dz)                 \
   ACTION(detavtx)            \
   ACTION(dphivtx)            \
   ACTION(misshits)

#endif /* _DEFINES_H */
