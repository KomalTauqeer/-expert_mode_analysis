#include "SampleAnalyzer/User/Analyzer/ATLAS_1901_10917.h"
#include "SampleAnalyzer/User/Analyzer/ATLAS_1711_03301.h"
#include "SampleAnalyzer/Process/Analyzer/AnalyzerManager.h"
#include "SampleAnalyzer/Commons/Service/LogStream.h"
// -----------------------------------------------------------------------------
// BuildTable
// -----------------------------------------------------------------------------
void BuildUserTable(MA5::AnalyzerManager& manager)
{
  using namespace MA5;
  manager.Add("ATLAS_1901_10917",new ATLAS_1901_10917);
  manager.Add("ATLAS_1711_03301",new ATLAS_1711_03301);
}
