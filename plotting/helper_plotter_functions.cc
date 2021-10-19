#include "helper_plotter_functions.h"

// CMSandluminosity class functions
CMSandLuminosity::CMSandLuminosity(TPad* pad, bool is2016, bool is2017, bool is2018, bool isRun2 = false):
    CMStext( "#bf{CMS} #scale[0.8]{#it{Preliminary}}" )
    , leftmargin( pad->GetLeftMargin() )
    , topmargin( pad->GetTopMargin() )
    , rightmargin( pad->GetRightMargin() )
    , CMSlatex( get_latex(0.8*topmargin, 11, 42) )
    , lumilatex( get_latex(0.6*topmargin, 31, 42) )
    , flavorlatex( get_latex(0.6*topmargin, 21, 42) )
    , drawflavor( false )
{
    if(!is2016 and !is2017 and !is2018 and !isRun2){
        std::cout << "not clear which year to use for lumi info" << std::endl;
        lumitext = "(13 TeV)";
    }
    if(is2016 and is2017 and !is2018 and !isRun2) lumitext = "77.8 fb^{-1} (13 TeV)";
    else if(is2016 and !is2017 and is2018 and !isRun2) lumitext = "96.0 fb^{-1} (13 TeV)";
    else if(!is2016 and is2017 and is2018 and !isRun2) lumitext = "101 fb^{-1} (13 TeV)";
    else if(is2016) lumitext = "36.3 fb^{-1} (13 TeV)";
    else if(is2017) lumitext = "41.5 fb^{-1} (13 TeV)";
    else if(is2018) lumitext = "59.7 fb^{-1} (13 TeV)";
    else if(isRun2) lumitext = "138 fb^{-1} (13 TeV)";
    else lumitext = "(13 TeV)";
}

CMSandLuminosity::~CMSandLuminosity(){}

void CMSandLuminosity::change_CMStext(TString new_text){
    CMStext = new_text;
}

void CMSandLuminosity::change_lumitext(TString new_text){
    lumitext = new_text;
}

void CMSandLuminosity::add_flavor(TString histname){
    drawflavor = true;
    if(histname.Contains("_OS_ee")) flavortext = "OS ee";
    else if(histname.Contains("_SS_ee")) flavortext = "SS ee";
    else if(histname.Contains("_OS_mm")) flavortext = "OS #mu#mu";
    else if(histname.Contains("_SS_mm")) flavortext = "SS #mu#mu";
    else if(histname.Contains("_OS_me")) flavortext = "OS #mue";
    else if(histname.Contains("_SS_me")) flavortext = "SS #mue";
    else if(histname.Contains("_OS_em")) flavortext = "OS e#mu";
    else if(histname.Contains("_SS_em")) flavortext = "SS e#mu";
    else if(histname.Contains("_OS_2l")) flavortext = "OS";
    else if(histname.Contains("_SS_2l")) flavortext = "SS";
    else if(histname.Contains("_ee")) flavortext = "ee";
    else if(histname.Contains("_mm")) flavortext = "#mu#mu";
    else if(histname.Contains("_me")) flavortext = "#mu e";
    else if(histname.Contains("_em")) flavortext = "e#mu";
    else flavortext = "";
}

void CMSandLuminosity::Draw()
{
    CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);
    lumilatex.DrawLatex(1-rightmargin, 1-0.8*topmargin, lumitext);

    if(drawflavor){
        flavorlatex.DrawLatex(0.5*(1 + leftmargin - rightmargin), 1-0.8*topmargin, flavortext);
        drawflavor = false;
    }
}

// Shape_SR_plottext class functions
Shape_SR_plottext::Shape_SR_plottext(TPad* pad):
    mm( "#mu#mu" )
    , em( "e#mu" )
    , ee( "ee" )
    , me( "#mue" )
    , OS( "OS" )
    , SS( "SS" )
    , masslessthan2( "M_{SV} < 2 GeV" )
    , massmorethan2( "M_{SV} > 2 GeV" )
    , masslessthan6( "M_{SV} < 6 GeV" )
    , massmorethan6( "M_{SV} > 6 GeV" )
    , leftmargin( pad->GetLeftMargin() )
    , topmargin( pad->GetTopMargin() )
    , rightmargin( pad->GetRightMargin() )
    , bottommargin( pad->GetBottomMargin() )
    , latex( get_latex(0.56*topmargin, 21, 42) )
    , fullLine()
    , dashedLine()
{
    fullLine.SetLineStyle(1);
    dashedLine.SetLineStyle(2);
}

Shape_SR_plottext::~Shape_SR_plottext(){}

void Shape_SR_plottext::Draw(TString histname)
{
    TString mass_category = "low";
    if(histname.Contains("_M-6_") or histname.Contains("_M-8_") or histname.Contains("_M-10_") or histname.Contains("_M-12_") or histname.Contains("_M-14_") or histname.Contains("_M-15_")) mass_category = "high";
    if(histname.Contains("Shape_SR")){
        if(histname.Contains("_OS_2l") or histname.Contains("_SS_2l") and not histname.Contains("_M-10_")) Draw_OSorSS_2l(histname);
        else if(histname.Contains("_SS_2l") and histname.Contains("_M-10_")) Draw_SSHighMass_2l(histname);
        else if(histname.Contains("_2l") and histname.Contains("_M-10_")) Draw_2l_LowMass(mass_category);
        else if(histname.Contains("_2l") and histname.Contains("_M-5_")) Draw_2l_HighMass(mass_category);
        if(histname.Contains("_ee")) Draw_ee(mass_category);
        if(histname.Contains("_em")) Draw_em(mass_category);
        if(histname.Contains("_me")) Draw_me(mass_category);
        if(histname.Contains("_mm")) Draw_mm(mass_category);
    }else if(histname.Contains("Shape_alpha")){
        Draw_Shape_alpha_lines_and_generaltext(histname, mass_category);
    }
}

void Shape_SR_plottext::Draw_OSorSS_2l(TString histname)
{
    latex.DrawLatex(0.125*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, mm);
    latex.DrawLatex(0.375*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, em);
    latex.DrawLatex(0.625*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, ee);
    latex.DrawLatex(0.875*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, me);
    
    fullLine.DrawLineNDC(0.25*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.25*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3*topmargin);
    fullLine.DrawLineNDC(0.5*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.5*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3*topmargin);
    fullLine.DrawLineNDC(0.75*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.75*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3*topmargin);
    
    dashedLine.DrawLineNDC(0.125*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.125*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(0.375*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.375*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(0.625*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.625*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(0.875*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.875*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    
    if(histname.Contains("_M-5_")){
        latex.DrawLatex(0.0625*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan2);
        latex.DrawLatex(0.1875*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan2);
        latex.DrawLatex(0.3125*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan2);
        latex.DrawLatex(0.4375*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan2);
        latex.DrawLatex(0.5625*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan2);
        latex.DrawLatex(0.6875*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan2);
        latex.DrawLatex(0.8125*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan2);
        latex.DrawLatex(0.9375*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan2);
    }
    if(histname.Contains("_M-10_")){
        latex.DrawLatex(0.0625*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan6);
        latex.DrawLatex(0.1875*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan6);
        latex.DrawLatex(0.3125*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan6);
        latex.DrawLatex(0.4375*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan6);
        latex.DrawLatex(0.5625*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan6);
        latex.DrawLatex(0.6875*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan6);
        latex.DrawLatex(0.8125*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan6);
        latex.DrawLatex(0.9375*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan6);
    }
}

void Shape_SR_plottext::Draw_SSHighMass_2l(TString histname)
{
    double ntotal = 22.;
    latex.DrawLatex(3./ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, mm);
    latex.DrawLatex(8./ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, em);
    latex.DrawLatex(13./ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, ee);
    latex.DrawLatex(19./ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, me);

    fullLine.DrawLineNDC(5./ntotal*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 5./ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3*topmargin);
    fullLine.DrawLineNDC(10./ntotal*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 10./ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3*topmargin);
    fullLine.DrawLineNDC(16./ntotal*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 16./ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3*topmargin);

    dashedLine.DrawLineNDC(3./ntotal*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 3./ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(8./ntotal*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 8./ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(13./ntotal*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 13./ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(19./ntotal*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 19./ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);

    if(histname.Contains("_M-10_")){
        latex.DrawLatex(1.5/ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan6);
        latex.DrawLatex(4/ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan6);
        latex.DrawLatex(6.5/ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan6);
        latex.DrawLatex(9/ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan6);
        latex.DrawLatex(11.5/ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan6);
        latex.DrawLatex(14.5/ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan6);
        latex.DrawLatex(17.5/ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan6);
        latex.DrawLatex(20.5/ntotal*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan6);
    }
}

void Shape_SR_plottext::Draw_2l_LowMass(TString mass_category)
{
    latex.DrawLatex(0.125*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, mm);
    latex.DrawLatex(0.375*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, em);
    latex.DrawLatex(0.625*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, ee);
    latex.DrawLatex(0.875*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, me);

    latex.DrawLatex(0.0625*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, OS);
    latex.DrawLatex(0.3125*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, OS);
    latex.DrawLatex(0.5625*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, OS);
    latex.DrawLatex(0.8125*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, OS);

    latex.DrawLatex(0.1875*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, SS);
    latex.DrawLatex(0.4375*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, SS);
    latex.DrawLatex(0.6875*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, SS);
    latex.DrawLatex(0.9375*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, SS);

    fullLine.DrawLineNDC(0.25*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.25*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3*topmargin);
    fullLine.DrawLineNDC(0.5*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.5*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3*topmargin);
    fullLine.DrawLineNDC(0.75*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.75*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3*topmargin);

    dashedLine.DrawLineNDC(0.125*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.125*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(0.375*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.375*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(0.625*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.625*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(0.875*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.875*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
}


void Shape_SR_plottext::Draw_2l_HighMass(TString mass_category)
{
    double nt = 46.;
    latex.DrawLatex(6./nt*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, mm);
    latex.DrawLatex(17./nt*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, em);
    latex.DrawLatex(28./nt*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, ee);
    latex.DrawLatex(40./nt*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, me);

    latex.DrawLatex(3./nt*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, OS);
    latex.DrawLatex(14./nt*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, OS);
    latex.DrawLatex(25./nt*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, OS);
    latex.DrawLatex(37./nt*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, OS);

    latex.DrawLatex(7.5/nt*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, SS);
    latex.DrawLatex(18.5/nt*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, SS);
    latex.DrawLatex(31./nt*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, SS);
    latex.DrawLatex(43./nt*(1 - leftmargin - rightmargin) + leftmargin, 1-4.3*topmargin, SS);

    fullLine.DrawLineNDC(11.*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 11.*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3*topmargin);
    fullLine.DrawLineNDC(22.*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 22.*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3*topmargin);
    fullLine.DrawLineNDC(34.*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 34.*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3*topmargin);

    dashedLine.DrawLineNDC(6.*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 6.*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(17.*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 17.*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(28.*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 28.*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(40.*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 40.*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
}

void Shape_SR_plottext::Draw_ee(TString mass_category)
{
    //latex.DrawLatex(0.5*(1 - leftmargin - rightmargin) + leftmargin, 1-0.8*topmargin, ee);
    Draw_lines_and_generaltext(mass_category);
}

void Shape_SR_plottext::Draw_em(TString mass_category)
{
    //latex.DrawLatex(0.5*(1 - leftmargin - rightmargin) + leftmargin, 1-0.8*topmargin, em);
    if(mass_category == "low") Draw_lines_and_generaltext(mass_category);
    if(mass_category == "high") Draw_lines_and_generaltext_HighMass();
}

void Shape_SR_plottext::Draw_me(TString mass_category)
{
    //latex.DrawLatex(0.5*(1 - leftmargin - rightmargin) + leftmargin, 1-0.8*topmargin, me);
    Draw_lines_and_generaltext(mass_category);
}

void Shape_SR_plottext::Draw_mm(TString mass_category)
{
    //latex.DrawLatex(0.5*(1 - leftmargin - rightmargin) + leftmargin, 1-0.8*topmargin, mm);
    if(mass_category == "low") Draw_lines_and_generaltext(mass_category);
    if(mass_category == "high") Draw_lines_and_generaltext_HighMass();
}

void Shape_SR_plottext::Draw_lines_and_generaltext_HighMass()
{
    double nt = 11.;
    latex.DrawLatex(3./nt*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, OS);
    latex.DrawLatex(9./nt*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, SS);
    fullLine.DrawLineNDC(6./nt*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 6./nt*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(3./nt*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 3./nt*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(9./nt*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 9./nt*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);

    latex.DrawLatex(1.5/nt*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan6);
    latex.DrawLatex(4.5/nt*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan6);
    latex.DrawLatex(7.5/nt*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan6);
    latex.DrawLatex(10./nt*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan6);
}

void Shape_SR_plottext::Draw_lines_and_generaltext(TString mass_category)
{
    latex.DrawLatex(0.25*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, OS);
    latex.DrawLatex(0.75*(1 - leftmargin - rightmargin) + leftmargin, 1-3.5*topmargin, SS);
    fullLine.DrawLineNDC(0.5*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.5*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(0.25*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.25*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    dashedLine.DrawLineNDC(0.75*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.75*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);

    if(mass_category == "low"){
        latex.DrawLatex(0.125*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan2);
        latex.DrawLatex(0.375*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan2);
        latex.DrawLatex(0.625*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan2);
        latex.DrawLatex(0.875*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan2);
    }
    if(mass_category == "high"){
        latex.DrawLatex(0.125*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan6);
        latex.DrawLatex(0.375*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan6);
        latex.DrawLatex(0.625*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan6);
        latex.DrawLatex(0.875*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan6);
    }
}

void Shape_SR_plottext::Draw_Shape_alpha_lines_and_generaltext(TString histname, TString mass_category){
    fullLine.DrawLineNDC(0.5*(1 - leftmargin - rightmargin) + leftmargin, bottommargin, 0.5*(1 - leftmargin - rightmargin) + leftmargin, 1 - 3.8*topmargin);
    if(mass_category == "low"){
        latex.DrawLatex(0.25*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan2);
        latex.DrawLatex(0.75*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan2);
    }
    if(mass_category == "high"){
        latex.DrawLatex(0.25*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, masslessthan6);
        latex.DrawLatex(0.75*(1 - leftmargin - rightmargin) + leftmargin, 1-4.2*topmargin, massmorethan6);
    }
    if(histname.Contains("_ee")) latex.DrawLatex(0.5*(1 - leftmargin - rightmargin) + leftmargin, 1-0.8*topmargin, ee);
    if(histname.Contains("_em")) latex.DrawLatex(0.5*(1 - leftmargin - rightmargin) + leftmargin, 1-0.8*topmargin, em);
    if(histname.Contains("_me")) latex.DrawLatex(0.5*(1 - leftmargin - rightmargin) + leftmargin, 1-0.8*topmargin, me);
    if(histname.Contains("_mm")) latex.DrawLatex(0.5*(1 - leftmargin - rightmargin) + leftmargin, 1-0.8*topmargin, mm);
}


std::vector<std::vector<TString>> get_identifiers(TString identifier_filename, const char* delim)
{
    std::string line;
    std::ifstream identifier_file (identifier_filename);
    std::vector<std::vector<TString>> identifiers; // 2D vector, vector of vectors where inner vectors are to be used in AND mode (outer in OR mode)
    if(identifier_file.is_open()){
        while(std::getline(identifier_file, line)){
            std::vector<TString> AND_identifiers;
            size_t start, end = 0;
            while((start = line.find_first_not_of(delim, end)) != std::string::npos){
                end = line.find(delim, start);
                AND_identifiers.push_back(line.substr(start, end - start));
            }
            identifiers.push_back(AND_identifiers);
        }
        identifier_file.close();
    }
    return identifiers;
}


bool check_identifiers(TString histname, std::vector<std::vector<TString>> identifiers)
{
    // Inner vector of strings are parts of the histname that have to match altogether, e.g. _OS_e AND _mll have to be in the name (put as _OS_e,_mll in identifier.txt)
    // Outer vector is in OR mode for the tags (different lines in identifier.txt)
    bool check = true;
    for(auto& stringvector : identifiers){
        check = true;
        for(TString id : stringvector){
            if(histname.Index(id) != -1) continue;
            check = false;
            break;
        }
        if(check) break;
    }
    return check;
}


TString make_general_pathname(const TString& plottype, TString specific_dir)
{
    //// pathname structure example: plots/multihists/HNL_358e/ and after this plot specific directories can follow
    //// or plots/singlehists/final/WJets/ and then plotspecific stuff
    //if(plottype == "plots/singlehists/"){
    //    TString filename = specific_dir; // specific_dir is actually the full filename in 'singlehists' case
    //    specific_dir = "";
    //    if(filename.Index("HeavyNeutrino") != -1) specific_dir += filename(filename.Index("HeavyNeutrino") + 14, filename.Index(".root") - filename.Index("HeavyNeutrino") - 14) + "/";
    //    else if(filename.Index("Run") != -1){
    //        specific_dir += filename(filename.Index("Run"), filename.Index(".root") - filename.Index("Run"));
    //        if(filename.Contains("Muon")) specific_dir += "_mm/";
    //        else if(filename.Contains("Electron") or filename.Contains("EGamma")) specific_dir += "_ee/";
    //        else specific_dir += "/";
    //    }
    //    else if(filename.Index("hists_full_analyzer") != -1) specific_dir += filename(filename.Index("hists_full_analyzer") + 20, filename.Index(".root") - filename.Index("hists_full_analyzer") - 20) + "/";
    //    else if(filename.Index("hists_mini_analyzer") != -1) specific_dir += filename(filename.Index("hists_mini_analyzer") + 20, filename.Index(".root") - filename.Index("hists_mini_analyzer") - 20) + "/";
    //}

    return "/user/bvermass/public_html/2l2q_analysis/" + plottype + specific_dir;
}


TString make_plotspecific_pathname(const TString& histname, const TString& pathname, const TString& linorlog)
{
    TString fullname = pathname + linorlog;

    if(histname.Contains("gen_"))               fullname += "gen/";
    if(histname.Contains("l1reco_") or histname.Contains("l1id_"))            fullname += "l1reco/";
    if(histname.Contains("l2reco_") or histname.Contains("l2id_"))            fullname += "l2reco/";
    if(histname.Contains("HLT_"))               fullname += "HLT/";
    fullname += get_lflavor(histname);
    if(histname.Contains("_OS_"))               fullname += "OS/";
    else if(histname.Contains("_SS_"))          fullname += "SS/";
    if(histname.Contains("_Bool_"))             fullname += "Bool/";
    if(histname.Contains("_CR"))                fullname += "CR/";
    if(histname.Contains("_SR"))                fullname += "SR/";
    if(histname.Contains("_2prompt"))           fullname += "2prompt/";
    if(histname.Contains("_2Jets"))             fullname += "2Jets/";
    if(histname.Contains("_2BJets"))            fullname += "2BJets/";
    if(histname.Contains("_2BJetsExtraCuts"))   fullname += "2BJetsExtraCuts/";
    if(histname.Contains("_2prompt2BJets"))     fullname += "2prompt2BJets/";
    if(histname.Contains("_TooFar"))            fullname += "TooFar/";
    if(histname.Contains("before") or histname.Contains("after") or histname.Contains("_Training")) fullname += "partialcuts/";

    //related to ABCD method
    if(histname.Contains("cutphill_"))          fullname += "ABCDwithDeltaPhi/";
    if(histname.Contains("cutmll_"))            fullname += "ABCDwithmll/";
    if(histname.Contains("cutphiORmll_"))       fullname += "ABCDwithDeltaPhiORmll/";
    if(histname.Contains("cutmlSV_"))           fullname += "ABCDwithmlSV/";
    if(histname.Contains("cutCR1mlSV_"))        fullname += "ABCDwithCR1mlSV/";
    if(histname.Contains("cutCR2mlSV_"))        fullname += "ABCDwithCR2mlSV/";
    if(histname.Contains("cutCR3mlSV_"))        fullname += "ABCDwithCR3mlSV/";
    if(histname.Contains("cutCR1phill_"))       fullname += "ABCDwithCR1phill/";
    if(histname.Contains("cutCR2phill_"))       fullname += "ABCDwithCR2phill/";
    if(histname.Contains("cutCR3phill_"))       fullname += "ABCDwithCR3phill/";
    if(histname.Contains("cutTightphill_"))     fullname += "ABCDwithTightDeltaPhi/";
    if(histname.Contains("cutTightmll_"))       fullname += "ABCDwithTightmll/";
    if(histname.Contains("cutTightphiORmll_"))  fullname += "ABCDwithTightDeltaPhiORmll/";
    if(histname.Contains("cutTightmlSV_"))      fullname += "ABCDwithTightmlSV/";
    if(histname.Contains("cutMediummlSV_"))     fullname += "ABCDwithMediummlSV/";
    if(histname.Contains("cutTightCR1mlSV_"))   fullname += "ABCDwithTightCR1mlSV/";
    if(histname.Contains("cutOldTightCR1mlSV_")) fullname += "ABCDwithOldTightCR1mlSV/";
    if(histname.Contains("cutTightCR2mlSV_"))   fullname += "ABCDwithTightCR2mlSV/";
    if(histname.Contains("cutTightCR3mlSV_"))   fullname += "ABCDwithTightCR3mlSV/";
    if(histname.Contains("cutMediumCR2mlSV_"))   fullname += "ABCDwithMediumCR2mlSV/";
    if(histname.Contains("cutMediumCR3mlSV_"))   fullname += "ABCDwithMediumCR3mlSV/";
    if(histname.Contains("cutTightCR2phill_"))  fullname += "ABCDwithTightCR2phill/";
    if(histname.Contains("cutTightCR3phill_"))  fullname += "ABCDwithTightCR3phill/";
    if(histname.Contains("cutAll_"))            fullname += "ABCDwithAllmethods/";
    if(histname.Contains("cutTightAll_"))       fullname += "ABCDwithAllTightmethods/";
    if(histname.Contains("quadA_"))             fullname += "quadA/";
    if(histname.Contains("quadB_"))             fullname += "quadB/";
    if(histname.Contains("quadC_"))             fullname += "quadC/";
    if(histname.Contains("quadD_"))             fullname += "quadD/";
    if(histname.Contains("quadAB_"))            fullname += "quadAB/";
    if(histname.Contains("quadAC_"))            fullname += "quadAC/";
    if(histname.Contains("quadCD_"))            fullname += "quadCD/";
    if(histname.Contains("quadBD_"))            fullname += "quadBD/";
    if(histname.Contains("quadABCD_"))          fullname += "quadABCD/";
    if(histname.Contains("quadBCD_"))           fullname += "quadBCD/";
    if(histname.Contains("quadAB-CD_"))         fullname += "quadAB-CD/";
    if(histname.Contains("quadAC-BD_"))         fullname += "quadAC-BD/";
    if(histname.Contains("quadA-B_"))           fullname += "quadA-B/";
    if(histname.Contains("quadA-C_"))           fullname += "quadA-C/";
    if(histname.Contains("quadC-D_"))           fullname += "quadC-D/";
    if(histname.Contains("AoverB_"))            fullname += "AoverB/";
    if(histname.Contains("CoverD_"))            fullname += "CoverD/";
    if(histname.Contains("BoverD_"))            fullname += "BoverD/";
    if(histname.Contains("DtoCwithCD_"))        fullname += "DtoCwithCD/";
    if(histname.Contains("BtoAwithCD_"))        fullname += "BtoAwithCD/";
    if(histname.Contains("CtoAwithBD_"))        fullname += "CtoAwithBD/";
    if(histname.Contains("quadAwithBtoA_"))     fullname += "quadAwithBtoA/";
    if(histname.Contains("quadCwithDtoC_"))     fullname += "quadCwithDtoC/";

    if(histname.Contains("_M-") and histname.Contains("_V2-")) fullname += (TString)histname(histname.Index("_M-") + 1, histname.Index("e-0") - histname.Index("_M-") + 3) + "/";
    if(histname.Contains("KVF_"))              fullname += "KVF/";
    if(histname.Contains("_IVF_"))              fullname += "IVF/";
    if(histname.Contains("_jetl2_"))            fullname += "jetl2/";
    if(histname.Contains("_oldID_"))            fullname += "oldID/";
    if(histname.Contains("_invVtx_"))           fullname += "invVtx/";
    if(histname.Contains("_eff"))               fullname += "eff/";
    if(histname.Contains("_invIVFSVgenreco"))   fullname += "invIVFSVgenreco/";
    if(histname.Contains("_projection"))        fullname += "projection/";
    if(histname.Contains("_outsideMSV"))        fullname += "outsideMSV/";

    while(gSystem->Exec("mkdir -p " + fullname) != 0){
        std::cout << "command \"mkdir -p " << fullname << "\" failed, checking" << std::endl;
        gSystem->Exec("rm " + (TString)fullname(0, fullname.Length() - 1));
        std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );
    }
    //gSystem->Exec("cp /user/bvermass/public_html/index.php " + fullname);
    return fullname;
}


TString get_lflavor(const TString& histname){
    if(histname.Index("_ee_") != -1) return "ee/";
    else if(histname.Index("_mm_") != -1) return "mm/";
    else if(histname.Index("_em_") != -1) return "em/";
    else if(histname.Index("_me_") != -1) return "me/";
    else if(histname.Index("_2l_") != -1) return "2l/";
    else if(histname.Index("_l2e_") != -1) return "l2e/";
    else if(histname.Index("_l2m_") != -1) return "l2m/";
    else return "";
}


TLegend get_legend(double xmin, double ymin, double xmax, double ymax, int Ncolumns)
{
    TLegend legend = TLegend(xmin, ymin, xmax, ymax);
    legend.SetNColumns(Ncolumns);
    legend.SetFillStyle(0);
    
    return legend;
}


TString adjust_legend(TString legend)
{
    TString adjusted_legend = legend.ReplaceAll("x", " ");
    return adjusted_legend;
}


TLatex get_latex(double textsize, int textalign, int textfont)
{
    TLatex textltx;//0.9,0.905,text);//"35.9 fb^{-1} (13 TeV)"); 
    textltx.SetNDC();
    textltx.SetTextAlign(textalign);
    textltx.SetTextFont(textfont);
    textltx.SetTextSize(textsize);
    textltx.SetTextColor(kBlack);
    return textltx;
}


int get_color(TString legend)
{
    if(legend.Index("Bkg")           != -1) return kOrange+4;
    else if(legend.Index("W+Jets")   != -1) return kRed+3;
    else if(legend.Index("DY")       != -1) return kOrange-1;
    else if(legend.Index("t#bar{t}") != -1) return kCyan-3;
    else if(legend.Index("Diboson")  != -1) return kGreen+3;
    else if(legend.Index("Triboson") != -1) return kRed+3;
    else if(legend.Index("WG")       != -1) return 7;
    else if(legend.Index("V#gamma")  != -1) return 7;
    else if(legend.Index("ZG")       != -1) return 8;
    else if(legend.Index("JPsi")     != -1) return 2;
    else if(legend.Index("QCD")      != -1) return 2;
    else if(legend.Index("Top")      != -1) return kBlue+2;
    else if(legend.Index("M-15")   != -1) return kBlack;
    else if(legend.Index("M-3")    != -1) return kRed-9;
    else if(legend.Index("M-5")    != -1) return kGreen-9;
    else if(legend.Index("M-8")    != -1) return kMagenta-7;
    else if(legend.Index("M-10")   != -1) return kCyan-2;
    else return kBlack;
}


TH1F get_histoRatio(TH1F* data, TH1F* MC, TString xaxistitle)
{
    TH1F histo_ratio("data/MC", ";" + xaxistitle + ";data/MC", data->GetNbinsX(), data->GetXaxis()->GetXmin(), data->GetXaxis()->GetXmax());
    histo_ratio.Divide(data, MC);

    histo_ratio.GetXaxis()->SetLabelSize(0.09);
    histo_ratio.GetYaxis()->SetLabelSize(0.09);
    histo_ratio.GetXaxis()->SetTitleSize(0.09);
    histo_ratio.GetYaxis()->SetTitleSize(0.09);
    histo_ratio.GetYaxis()->SetTitleOffset(0.7);
    histo_ratio.SetMinimum(0);
    histo_ratio.SetMaximum(2);

    return histo_ratio;
}


void draw_line_at_1(double xmin, double xmax)
{
    TLine line;
    line.SetLineStyle(2);
    line.DrawLine(xmin, 1., xmax, 1.);
}


void divide_by_binwidth(TH1F* h)
{
    for(int i = 1; i <= h->GetNbinsX(); i++){
        double bincontent = h->GetBinContent(i);
        double binwidth   = h->GetBinWidth(i);
        h->SetBinContent(i, bincontent/binwidth);
    }
    if(h->GetYaxis()->GetTitle() == (TString)"Events") h->GetYaxis()->SetTitle("Events / GeV");
}


std::vector< double > computeEfficiencyForROC(TH1F* hist)
{
    int nbins = hist->GetXaxis()->GetNbins();
    // first check that underflow and overflow are empty
    if(hist->GetBinContent(0) != 0) std::cout << "underflow not empty! " << hist->GetBinContent(0) << std::endl;
    if(hist->GetBinContent(nbins+1) != 0) std::cout << "overflow not empty! " << hist->GetBinContent(nbins+1) << std::endl;
    std::vector< double > effs;
    double passed = 0;
    double total = hist->Integral();
    for(int i = 0; i <= nbins; i++){
        passed += hist->GetBinContent(i);
        effs.push_back(1-passed/total);
    }
    return effs;
}


double computeAUC(TGraph* roc)
{
    double area = 0.;
    double x1, x2, y1, y2;
    for(int i = 0; i < roc->GetN() - 1; i++){
        roc->GetPoint(i, x1, y1);
        roc->GetPoint(i+1, x2, y2);
        area += (x2 - x1)*(y1 + y2)/2;
    }
    return  fabs(round(area*10000)/100);
}

TGraph* get_roc(std::vector< double > eff_signal, std::vector< double > eff_bkg)
{
    TGraph* roc = new TGraph(eff_signal.size(), &(eff_bkg[0]), &(eff_signal[0]));
    roc->SetLineWidth(2);
    return roc;
}


std::tuple<double, double, double> computeCuttingPointEfficiency(std::vector<double> eff_signal, std::vector<double> eff_bkg, TH1F* hist_signal, TH1F* hist_bkg, double cutting_point, TString general_pathname, TString histname)
{
    unsigned bin_number  = hist_signal->FindBin(cutting_point);
    double cp_eff_signal = eff_signal[bin_number-1];
    double cp_eff_bkg    = eff_bkg[bin_number-1];
    return std::make_tuple(cp_eff_signal, cp_eff_bkg, cutting_point);
}

std::tuple<double,double, double> computeCuttingPoint(std::vector<double> eff_signal, std::vector<double> eff_bkg, TH1F* hist_signal, TH1F* hist_bkg, double required_signal_eff, TString general_pathname, TString histname)
{
    double cp = 0, cp_eff_signal = 0, cp_eff_bkg = 0, cp_eff_signal_unc = 0, cp_eff_bkg_unc = 0;
    for(int j = eff_signal.size() -1;  j >= 0; j--){
        if(eff_signal[j] > required_signal_eff){
            cp = hist_signal->GetXaxis()->GetBinLowEdge(j+1);
            cp_eff_signal = eff_signal[j];
            cp_eff_bkg = eff_bkg[j];
            for(int junc = j + 1; junc <= hist_signal->GetNbinsX(); junc++){
                cp_eff_signal_unc += hist_signal->GetBinContent(junc);
                cp_eff_bkg_unc    += hist_bkg->GetBinContent(junc);
            }
            break;
        }
    }
    std::ostringstream eff_signal_stream;
    eff_signal_stream << round(cp_eff_signal*10000)/100;
    std::ostringstream eff_bkg_stream;
    eff_bkg_stream << round(cp_eff_bkg*10000)/100;
    std::ostringstream eff_signal_unc_stream;
    eff_signal_unc_stream << round(cp_eff_signal_unc*10000)/100;
    std::ostringstream eff_bkg_unc_stream;
    eff_bkg_unc_stream << round(cp_eff_bkg_unc*10000)/100;
    std::ostringstream eff_cp_stream;
    eff_cp_stream << round(cp*100)/100;

    std::string content = (std::string)histname + "\n";
    content += "\\item Sig " + eff_signal_stream.str() + "\\% (" + eff_signal_unc_stream.str() + " events)\\\\\n";
    content += "Bkg " + eff_bkg_stream.str() + "\\% (" + eff_bkg_unc_stream.str() + " events)\\\\\n";
    content += "PFN output > " + eff_cp_stream.str() + "\n\n";
    filePutContents((std::string)general_pathname + "Signal_Bkg_Yields.txt", content, true);

    return std::make_tuple(cp_eff_signal, cp_eff_bkg, cp);
}


// 2D histograms
TString get_2D_draw_options(TH2F* h)
{
    int nbinsx = h->GetNbinsX();
    int nbinsy = h->GetNbinsY();
    if(nbinsx > 10 or nbinsy > 10) return "colz";
    else return "colz text";
}

void alphanumeric_labels_2D(TH2F* hist, TString histname)
{
    if(histname.Index("lsources") != -1){
        const char* labels[14] = {"und.", "mis.", "Z", "W", "t", "b", "c", "uds", "g", "phot", "tau", "mu", "e", "HNL"};
        for(int i = 1; i <= 14; i++){
            hist->GetXaxis()->SetBinLabel(i, labels[i-1]);
            hist->GetYaxis()->SetBinLabel(i, labels[i-1]);
        }
    }
    if(histname.Index("lprovenance") != -1 and histname.Index("Compressed") == -1){
        const char* labels[19] = {"W_L", "W_T_L", "W_B_L", "W_B_C_L", "W_B_C_T_L", "W_B_T_L", "W_C_L", "W_C_T_L", "B_L", "B_C_L", "B_C_T_L", "B_T_L", "C_L", "C_T_L", "B_Baryon", "C_Baryon", "pi_0", "photon", "F_L"};
        for(int i = 1; i <= 19; i++){
            hist->GetXaxis()->SetBinLabel(i, labels[i-1]);
            hist->GetYaxis()->SetBinLabel(i, labels[i-1]);
        }
    }
    if(histname.Index("lprovenanceCompressed") != -1){
        const char* labels[5] = {"prompt", "b", "c", "fake", "unknown"};
        for(int i = 1; i <= 5; i++){
            hist->GetXaxis()->SetBinLabel(i, labels[i-1]);
            hist->GetYaxis()->SetBinLabel(i, labels[i-1]);
        }
    }
    if(histname.Contains("l2provCompressedvsConversion")){
        const char* labely[4] = {"prompt", "fragmentation", "non-prompt", "not photon"};
        for(int i = 1; i <= 4; i++){
            hist->GetYaxis()->SetBinLabel(i, labely[i-1]);
        }
        const char* labelx[5] = {"prompt", "b", "c", "fake", "unknown"};
        for(int i = 1; i <= 5; i++){
            hist->GetXaxis()->SetBinLabel(i, labelx[i-1]);
        }
    }
    if(histname.Contains("_QuadFractions_2D")){
        const char* labely[4] = {"A", "B", "C", "D"};
        for(int i = 1; i <= 4; i++){
            hist->GetYaxis()->SetBinLabel(i, labely[i-1]);
        }
        const char* labelx[4] = {"#splitline{M_{SV}<4}{L_{xy}<10}", "#splitline{M_{SV}<4}{L_{xy}>10}", "#splitline{M_{SV}>4}{L_{xy}<10}", "#splitline{M_{SV}>4}{L_{xy}>10}"};
        for(int i = 1; i <= 4; i++){
            hist->GetXaxis()->SetBinLabel(i, labelx[i-1]);
        }
    }
    if(histname.Contains("_QuadFractions2_2D")){
        const char* labely[4] = {"A", "B", "C", "D"};
        for(int i = 1; i <= 4; i++){
            hist->GetYaxis()->SetBinLabel(i, labely[i-1]);
        }
        const char* labelx[4] = {"L_{xy}<10", "L_{xy}>10"};
        for(int i = 1; i <= 4; i++){
            hist->GetXaxis()->SetBinLabel(i, labelx[i-1]);
        }
    }
}
