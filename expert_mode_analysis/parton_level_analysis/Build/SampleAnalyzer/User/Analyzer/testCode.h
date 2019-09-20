#ifndef analysis_testCode_h
#define analysis_testCode_h

#include "SampleAnalyzer/Process/Analyzer/AnalyzerBase.h"
#include "SampleAnalyzer/Interfaces/root/RootMainHeaders.h"
namespace MA5
{
class testCode : public AnalyzerBase
{
  INIT_ANALYSIS(testCode,"testCode")

 public:
  virtual bool Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters);
  virtual void Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files);
  virtual bool Execute(SampleFormat& sample, const EventFormat& event);

 private:
  TH1F* Mass;
};
}

#endif
