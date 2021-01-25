#include "AnalyzeCombineOutput.h"

//limits come from /user/kskovpen/analysis/HNL/CMSSW_10_2_13/src/Limits/limit/plotLimits.py

TGraphAsymmErrors* get_external_limit(TString identifier, Color_t lcolor, Style_t lstyle, Width_t lwidth)
{
    std::vector<std::vector<double>> limitpoints = get_limitpoints(identifier);
    std::vector<double> mass;
    std::vector<double> V2;
    std::vector<double> err;
    for(unsigned i = 0; i < limitpoints.size(); i++){
        mass.push_back(limitpoints[i][0]);
        V2.push_back(limitpoints[i][1]);
        err.push_back(0.);
    }

    TGraphAsymmErrors* graph = new TGraphAsymmErrors(mass.size(), &mass[0], &V2[0], &err[0], &err[0], &err[0], &err[0]);

    graph->SetLineColor(lcolor);
    graph->SetLineStyle(lstyle);
    graph->SetLineWidth(lwidth);

    return graph;
}

std::vector<std::vector<double>> get_limitpoints(TString identifier)
{
    if(identifier == "delphi_prompt")                    return get_delphi_prompt();
    if(identifier == "delphi_displaced")                 return get_delphi_displaced();
    if(identifier == "atlas_prompt_electron")            return get_atlas_prompt_electron();
    if(identifier == "atlas_prompt_muon")                return get_atlas_prompt_muon();
    if(identifier == "atlas_displaced_muon_LNV")         return get_atlas_displaced_muon_LNV();
    if(identifier == "atlas_displaced_muon_LNC")         return get_atlas_displaced_muon_LNC();
    if(identifier == "cms_trilepton_prompt_muon")        return get_cms_trilepton_prompt_muon();
    if(identifier == "cms_trilepton_prompt_electron")    return get_cms_trilepton_prompt_electron();
    if(identifier == "cms_trilepton_displaced_muon")     return get_cms_trilepton_displaced_muon();
    if(identifier == "cms_trilepton_displaced_electron") return get_cms_trilepton_displaced_electron();
    return {{1,1}};
}

std::vector<std::vector<double>> get_delphi_prompt()
{
    return {
        { pow(10, 0.260273972602739),  pow(10, -2.00000000000000) }, 
        { pow(10, 0.292237442922374),  pow(10, -2.19424460431654) },
        { pow(10, 0.342465753424657),  pow(10, -2.49640287769784) },
        { pow(10, 0.390410958904109),  pow(10, -2.78417266187050) },
        { pow(10, 0.447488584474885),  pow(10, -3.11510791366906) },
        { pow(10, 0.481735159817351),  pow(10, -3.33812949640287) },
        { pow(10, 0.534246575342466),  pow(10, -3.63309352517985) },
        { pow(10, 0.591324200913242),  pow(10, -3.95683453237410) },
        { pow(10, 0.625570776255707),  pow(10, -4.14388489208633) },
        { pow(10, 0.652968036529680),  pow(10, -4.30935251798561) },
        { pow(10, 0.694063926940639),  pow(10, -4.47482014388489) },
        { pow(10, 0.732876712328766),  pow(10, -4.59712230215827) },
        { pow(10, 0.776255707762557),  pow(10, -4.68345323741007) },
        { pow(10, 0.815068493150685),  pow(10, -4.72661870503597) },
        { pow(10, 0.860730593607306),  pow(10, -4.75539568345323) },
        { pow(10, 0.915525114155251),  pow(10, -4.74820143884892) },
        { pow(10, 0.972602739726027),  pow(10, -4.73381294964028) },
        { pow(10, 1.038812785388127),  pow(10, -4.72661870503597) },
        { pow(10, 1.098173515981735),  pow(10, -4.72661870503597) },
        { pow(10, 1.166666666666666),  pow(10, -4.70503597122302) },
        { pow(10, 1.230593607305935),  pow(10, -4.68345323741007) },
        { pow(10, 1.280821917808219),  pow(10, -4.67625899280575) },
        { pow(10, 1.331050228310502),  pow(10, -4.66187050359712) },
        { pow(10, 1.381278538812785),  pow(10, -4.63309352517985) },
        { pow(10, 1.456621004566209),  pow(10, -4.60431654676259) },
        { pow(10, 1.513698630136986),  pow(10, -4.60431654676259) },
        { pow(10, 1.586757990867580),  pow(10, -4.60431654676259) },
        { pow(10, 1.630136986301369),  pow(10, -4.59712230215827) },
        { pow(10, 1.666666666666666),  pow(10, -4.56115107913669) },
        { pow(10, 1.712328767123287),  pow(10, -4.48920863309352) },
        { pow(10, 1.751141552511415),  pow(10, -4.38129496402877) },
        { pow(10, 1.785388127853881),  pow(10, -4.20143884892086) },
        { pow(10, 1.815068493150684),  pow(10, -3.98561151079136) },
        { pow(10, 1.837899543378995),  pow(10, -3.73381294964028) },
        { pow(10, 1.856164383561643),  pow(10, -3.50359712230215) },
        { pow(10, 1.872146118721461),  pow(10, -3.20863309352517) },
        { pow(10, 1.888127853881278),  pow(10, -2.92805755395683) },
        { pow(10, 1.901826484018265),  pow(10, -2.64748201438848) }
    };
}

std::vector<std::vector<double>> get_delphi_displaced()
{
    return {
        { pow(10, -0.365297), pow(10, -2.000000) }, 
        { pow(10, -0.228311), pow(10, -2.467626) },
        { pow(10, -0.125571), pow(10, -2.827338) },
        { pow(10, -0.020548), pow(10, -3.172662) },
        { pow(10,  0.095890), pow(10, -3.561151) },
        { pow(10,  0.232877), pow(10, -3.978417) },
        { pow(10,  0.315068), pow(10, -4.215827) },
        { pow(10,  0.326484), pow(10, -4.237410) },
        { pow(10,  0.363014), pow(10, -4.323741) },
        { pow(10,  0.413242), pow(10, -4.460432) },
        { pow(10,  0.461187), pow(10, -4.582734) },
        { pow(10,  0.506849), pow(10, -4.661871) },
        { pow(10,  0.552511), pow(10, -4.712230) },
        { pow(10,  0.586758), pow(10, -4.669065) },
        { pow(10,  0.609589), pow(10, -4.503597) },
        { pow(10,  0.618721), pow(10, -4.309353) },
        { pow(10,  0.625571), pow(10, -4.079137) },
        { pow(10,  0.632420), pow(10, -3.769784) },
        { pow(10,  0.639269), pow(10, -3.431655) },
        { pow(10,  0.646119), pow(10, -3.158273) },
        { pow(10,  0.655251), pow(10, -2.985612) },
        { pow(10,  0.655251), pow(10, -2.985612) }
    };
}

std::vector<std::vector<double>> get_atlas_prompt_electron()
{
    return {
        { 5.,  1.8e-4 },
        { 10., 4.0e-5 },
        { 20., 1.3e-5 }
    };
}

std::vector<std::vector<double>> get_atlas_prompt_muon()
{
    return {
        { 5.,  7.0e-5 },
        { 10., 3.1e-5 },
        { 20., 1.2e-5 }
    };
}

std::vector<std::vector<double>> get_atlas_displaced_muon_LNV()
{
    return {
        { 4.1, 2.0e-4 }, 
        { 4.2, 4.0e-4 },
        { 4.4, 5.0e-4 },
        { 4.6, 4.0e-4 },
        { 5.2, 2.0e-4 },
        { 5.8, 1.0e-4 },
        { 6.0, 8.0e-5 },
        { 6.6, 4.0e-5 },
        { 6.8, 3.0e-5 },
        { 7.4, 1.3e-5 },
        { 7.8, 8.0e-6 },
        { 8.0, 5.3e-6 },
        { 8.1, 3.5e-6 },
        { 8.1, 2.5e-6 },
        { 7.8, 2.0e-6 },
        { 7.5, 1.9e-6 },
        { 7.0, 2.0e-6 },
        { 6.0, 3.1e-6 },
        { 5.6, 4.0e-6 },
        { 5.2, 6.0e-6 },
        { 4.8, 1.0e-5 },
        { 4.4, 2.3e-5 },
        { 4.2, 4.3e-5 }
    };
}

std::vector<std::vector<double>> get_atlas_displaced_muon_LNC()
{
    return {
        { 4.0, 3.0e-4 }, 
        { 4.1, 1.0e-3 },
        { 4.2, 1.2e-3 },
        { 4.3, 1.3e-3 },
        { 4.6, 1.1e-3 },
        { 5.0, 7.0e-4 },
        { 5.2, 6.0e-4 },
        { 5.8, 3.0e-4 },
        { 6.2, 2.0e-4 },
        { 7.0, 9.0e-5 },
        { 7.4, 6.0e-5 },
        { 8.0, 3.0e-5 },
        { 9.0, 8.5e-6 },
        { 9.4, 5.0e-6 },
        { 9.6, 3.0e-6 },
        { 9.6, 2.3e-6 },
        { 9.2, 1.6e-6 },
        { 8.8, 1.4e-6 },
        { 8.0, 1.5e-6 },
        { 7.0, 2.0e-6 },
        { 6.0, 3.3e-6 },
        { 5.0, 8.0e-6 },
        { 4.2, 5.0e-5 },
        { 4.1, 1.0e-4 }
    };
}

std::vector<std::vector<double>> get_cms_trilepton_prompt_muon()
{
    return {
        { 1.,  0.016319900}, 
        { 2.,  0.001829360}, 
        { 3.,  0.000594150}, 
        { 4.,  0.000280499}, 
        { 5.,  0.000149561}, 
        { 6.,  0.000103852}, 
        { 7.,  6.81653e-05}, 
        { 8.,  4.97358e-05}, 
        { 9.,  3.52154e-05}, 
        { 10., 3.12335e-05},  
        { 11., 2.46796e-05},  
        { 12., 2.13769e-05},  
        { 20., 1.48506e-05}
    };
}

std::vector<std::vector<double>> get_cms_trilepton_prompt_electron()
{
    return {
        { 1.,  0.013578400 },
        { 2.,  0.001518790 },
        { 3.,  0.000447416 },
        { 4.,  0.000223742 },
        { 5.,  0.000113030 },
        { 6.,  7.23346e-05 },
        { 7.,  5.10346e-05 },
        { 8.,  3.77547e-05 },
        { 9.,  2.72229e-05 },
        { 10., 2.33201e-05 },
        { 11., 1.86880e-05 },
        { 12., 1.75216e-05 },
        { 20., 1.20661e-05 }
    };
}

std::vector<std::vector<double>> get_cms_trilepton_displaced_electron()//these are preliminary expected limits as given on 13/01/21
{
    return {
        { 1.0,  0.000507247343194 }, 
        { 2.0,  4.44824327133e-05 },
        { 3.0,  1.26321037897e-05 },
        { 4.0,  5.84631607126e-06 },
        { 5.0,  3.04948275698e-06 },
        { 6.0,  1.86352940545e-06 },
        { 8.0,  9.26660504774e-07 },
        { 9.0,  1.19193691717e-06 },
        { 10.0, 7.86185410107e-07 },
        { 11.0, 1.14545503038e-06 },
        { 12.0, 1.15660122901e-06 },
        { 12.0, 1.71914525708e-05 },
        { 11.0, 3.87666659663e-05 },
        { 10.0, 8.04311057436e-05 },
        { 9.0,  0.000159761009854 },
        { 8.0,  0.000495258893352 },
        { 5.0,  0.005563333164900 },
        { 4.0,  0.028079211711900 },
        { 3.0,  0.161476194859000 }
    };
}

std::vector<std::vector<double>> get_cms_trilepton_displaced_muon()//these are preliminary expected limits as given on 13/01/21
{
    return {
        { 1.0,  0.000156651076395 }, 
        { 2.0,  1.75803561433e-05 },
        { 3.0,  5.17953594681e-06 },
        { 4.0,  2.30045043281e-06 },
        { 5.0,  1.25302301512e-06 },
        { 6.0,  7.78043499849e-07 },
        { 8.0,  4.05253416602e-07 },
        { 9.0,  5.16569400588e-07 },
        { 10.0, 2.52402315937e-07 },
        { 11.0, 5.47522006400e-07 },
        { 12.0, 6.11055043009e-07 },
        { 12.0, 2.97024598694e-05 },
        { 11.0, 5.40627115697e-05 },
        { 10.0, 0.000112582682050 },
        { 9.0,  0.000221144146053 },
        { 8.0,  0.000507995544467 },
        { 6.0,  0.002842344110830 },
        { 5.0,  0.007285948377100 },
        { 4.0,  0.030216753482800 }
    };
}
