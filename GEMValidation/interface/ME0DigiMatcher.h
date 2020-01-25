#ifndef GEMCode_GEMValidation_ME0DigiMatcher_h
#define GEMCode_GEMValidation_ME0DigiMatcher_h

#include "GEMCode/GEMValidation/interface/DigiMatcher.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/GEMDigi/interface/ME0DigiCollection.h"
#include "DataFormats/GEMDigi/interface/ME0PadDigiCollection.h"

#include <vector>
#include <map>
#include <set>
#include <unordered_set>

typedef std::vector<ME0Digi> ME0DigiContainer;
typedef std::vector<ME0PadDigi> ME0PadDigiContainer;

class SimHitMatcher;

class ME0DigiMatcher : public DigiMatcher
{
public:

  ME0DigiMatcher(const SimHitMatcher& sh,
                 const edm::EDGetTokenT<ME0DigiCollection>& me0DigiInput_,
                 const edm::EDGetTokenT<ME0PadDigiCollection>& me0PadDigiInput_);

  ~ME0DigiMatcher();

  // partition ME0 detIds with digis
  std::set<unsigned int> detIdsDigi() const;
  std::set<unsigned int> detIdsPad() const;

  // chamber detIds with digis
  std::set<unsigned int> chamberIdsDigi() const;
  std::set<unsigned int> chamberIdsPad() const;

  // superchamber detIds with digis
  std::set<unsigned int> superChamberIdsDigi() const;
  std::set<unsigned int> superChamberIdsPad() const;

  // ME0 digis from a particular partition, chamber or superchamber
  const ME0DigiContainer& digisInDetId(unsigned int) const;
  const ME0DigiContainer& digisInChamber(unsigned int) const;
  const ME0DigiContainer& digisInSuperChamber(unsigned int) const;

  // ME0 pads from a particular partition, chamber or superchamber
  const ME0PadDigiContainer& padsInDetId(unsigned int) const;
  const ME0PadDigiContainer& padsInChamber(unsigned int) const;
  const ME0PadDigiContainer& padsInSuperChamber(unsigned int) const;

  // #layers with digis from this simtrack
  int nLayersWithDigisInSuperChamber(unsigned int) const;
  int nLayersWithPadsInSuperChamber(unsigned int) const;

  /// How many pads in ME0 did this simtrack get in total?
  int nPads() const;

  std::set<int> stripNumbersInDetId(unsigned int) const;
  std::set<int> padNumbersInDetId(unsigned int) const;

  // what unique partitions numbers with digis from this simtrack?
  std::set<int> partitionNumbers() const;

  GlobalPoint getGlobalPointDigi(unsigned int rawId, const ME0Digi& d) const;
  GlobalPoint getGlobalPointPad(unsigned int rawId, const ME0PadDigi& tp) const;

private:

  void matchDigisToSimTrack(const ME0DigiCollection&);
  void matchPadsToSimTrack(const ME0PadDigiCollection&);

  template <class T>
  std::set<unsigned int> selectDetIds(const T &) const;

  int minBXME0Digi_, maxBXME0Digi_;
  int minBXME0Pad_, maxBXME0Pad_;

  int matchDeltaStrip_;

  std::map<unsigned int, ME0DigiContainer> detid_to_digis_;
  std::map<unsigned int, ME0DigiContainer> chamber_to_digis_;
  std::map<unsigned int, ME0DigiContainer> superchamber_to_digis_;

  std::map<unsigned int, ME0PadDigiContainer> detid_to_pads_;
  std::map<unsigned int, ME0PadDigiContainer> chamber_to_pads_;
  std::map<unsigned int, ME0PadDigiContainer> superchamber_to_pads_;

  bool verboseDigi_;
  bool verbosePad_;

  bool runME0Digi_;
  bool runME0Pad_;

  ME0DigiContainer no_digis_;
  ME0PadDigiContainer no_pads_;
};

template <class T>
std::set<unsigned int> ME0DigiMatcher::selectDetIds(const T &digis) const
{
  std::set<unsigned int> result;
  for (auto& p: digis)
  {
    const auto& id = p.first;
    result.insert(p.first);
  }
  return result;
}

#endif
