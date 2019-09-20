#ifndef analysis_ATLAS_1711_03301_h
#define analysis_ATLAS_1711_03301_h

#include "SampleAnalyzer/Process/Analyzer/AnalyzerBase.h"
#include "SampleAnalyzer/Interfaces/root/RootMainHeaders.h"

namespace MA5
{
class ATLAS_1711_03301 : public AnalyzerBase
{
  INIT_ANALYSIS(ATLAS_1711_03301,"ATLAS_1711_03301")

 public:
  virtual bool Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters);
  virtual void Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files);
  virtual bool Execute(SampleFormat& sample, const EventFormat& event);

 private:
 TH1F* hist_M;
 TF1* fit;
};
}

#endif
