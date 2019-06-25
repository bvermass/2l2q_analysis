#include "../interface/helper_plotter_functions.h"

TCanvas* get_canvas()
{
    TCanvas *c = new TCanvas("c","",700,700);
    gStyle->SetPalette(55);
    gStyle->SetOptStat(0);
    gStyle->SetEndErrorSize(0);
    gPad->SetTicks(1,1);
    return c;
}

TLegend get_legend(double xmin, double ymin, double xmax, double ymax)
{
    TLegend lgnd(xmin, ymin, xmax, ymax);
    lgnd.SetBorderSize(0);
    lgnd.SetFillStyle(0);
    return lgnd;
}

void histstyle(TH1* h)
{
    h->SetMarkerSize(0);
    h->SetLineWidth(2.5);
}

void graphstyle(TGraph* graph)
{
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(0.9);
    graph->SetMarkerColor(kBlack);
    graph->SetLineColor(kBlack);
}
