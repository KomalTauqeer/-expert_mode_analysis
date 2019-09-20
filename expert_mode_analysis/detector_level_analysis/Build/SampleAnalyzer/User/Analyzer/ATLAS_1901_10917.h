#ifndef analysis_ATLAS_1901_10917_h
#define analysis_ATLAS_1901_10917_h

#include "SampleAnalyzer/Process/Analyzer/AnalyzerBase.h"

namespace MA5
{
class ATLAS_1901_10917 : public AnalyzerBase
{
  INIT_ANALYSIS(ATLAS_1901_10917,"ATLAS_1901_10917")

 public:
  virtual bool Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters);
  virtual void Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files);
  virtual bool Execute(SampleFormat& sample, const EventFormat& event);

 private:
};
}

#endif