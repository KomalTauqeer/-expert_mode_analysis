#ifndef analysis_Particle_level_h
#define analysis_Particle_level_h

#include "SampleAnalyzer/Process/Analyzer/AnalyzerBase.h"
#include "SampleAnalyzer/Interfaces/root/RootMainHeaders.h"

namespace MA5
{
class Particle_level : public AnalyzerBase
{
  INIT_ANALYSIS(Particle_level,"Particle_level")

 public:
  virtual bool Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters);
  virtual void Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files);
  virtual bool Execute(SampleFormat& sample, const EventFormat& event);

 private:
 TH1F* hist;
};
}

#endif
