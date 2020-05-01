#include "GEMCode/GEMValidation/interface/ME0DigiMatcher.h"
#include "GEMCode/GEMValidation/interface/SimHitMatcher.h"

using namespace std;
using namespace matching;

ME0DigiMatcher::ME0DigiMatcher(const SimHitMatcher& sh,
                               const edm::EDGetTokenT<ME0DigiCollection>& me0DigiInput_,
                               const edm::EDGetTokenT<ME0PadDigiCollection>& me0PadDigiInput_)
    : DigiMatcher(sh) {
  const auto& me0Digi_ = conf().getParameter<edm::ParameterSet>("me0StripDigi");
  minBXME0Digi_ = me0Digi_.getParameter<int>("minBX");
  maxBXME0Digi_ = me0Digi_.getParameter<int>("maxBX");
  matchDeltaStrip_ = me0Digi_.getParameter<int>("matchDeltaStrip");
  verboseDigi_ = me0Digi_.getParameter<int>("verbose");
  runME0Digi_ = me0Digi_.getParameter<bool>("run");

  const auto& me0Pad_ = conf().getParameter<edm::ParameterSet>("me0PadDigi");
  minBXME0Pad_ = me0Pad_.getParameter<int>("minBX");
  maxBXME0Pad_ = me0Pad_.getParameter<int>("maxBX");
  verbosePad_ = me0Pad_.getParameter<int>("verbose");
  runME0Pad_ = me0Pad_.getParameter<bool>("run");

  if (hasME0Geometry_) {
    edm::Handle<ME0DigiCollection> me0_digis;
    if (gemvalidation::getByToken(me0DigiInput_, me0_digis, event()))
      if (runME0Digi_)
        matchDigisToSimTrack(*me0_digis.product());

    edm::Handle<ME0PadDigiCollection> me0_pads;
    if (gemvalidation::getByToken(me0PadDigiInput_, me0_pads, event()))
      if (runME0Pad_)
        matchPadsToSimTrack(*me0_pads.product());
  }
}

ME0DigiMatcher::~ME0DigiMatcher() {}

void ME0DigiMatcher::matchDigisToSimTrack(const ME0DigiCollection& digis) {
  if (verboseDigi_)
    cout << "Matching simtrack to ME0 digis" << endl;
  const auto& det_ids = simhit_matcher_->detIdsME0();
  for (const auto& id : det_ids) {
    ME0DetId p_id(id);
    ME0DetId superch_id(p_id.region(), 0, p_id.chamber(), 0);
    const auto& hit_strips = simhit_matcher_->hitStripsInDetId(id, matchDeltaStrip_);
    if (verboseDigi_) {
      cout << "hit_strips_fat ";
      copy(hit_strips.begin(), hit_strips.end(), ostream_iterator<int>(cout, " "));
      cout << endl;
    }

    const auto& digis_in_det = digis.get(ME0DetId(id));

    for (auto d = digis_in_det.first; d != digis_in_det.second; ++d) {
      if (verboseDigi_)
        cout << "ME0Digi " << p_id << " " << *d << endl;
      // check that the digi is within BX range
      if (d->bx() < minBXME0Digi_ || d->bx() > maxBXME0Digi_)
        continue;
      // check that it matches a strip that was hit by SimHits from our track
      if (hit_strips.find(d->strip()) == hit_strips.end())
        continue;
      if (verboseDigi_)
        cout << "...was matched!" << endl;

      detid_to_digis_[id].push_back(*d);
      chamber_to_digis_[p_id.chamberId().rawId()].push_back(*d);
      superchamber_to_digis_[superch_id()].push_back(*d);
    }
  }
}

void ME0DigiMatcher::matchPadsToSimTrack(const ME0PadDigiCollection& pads) {
  const auto& det_ids = simhit_matcher_->detIdsME0();
  for (const auto& id : det_ids) {
    ME0DetId p_id(id);
    ME0DetId superch_id(p_id.region(), 0, p_id.chamber(), 0);

    const auto& hit_pads = simhit_matcher_->hitME0PadsInDetId(id);
    const auto& pads_in_det = pads.get(p_id);

    if (verbosePad_) {
      cout << "checkpads " << hit_pads.size() << " " << std::distance(pads_in_det.first, pads_in_det.second)
           << " hit_pads: ";
      copy(hit_pads.begin(), hit_pads.end(), ostream_iterator<int>(cout, " "));
      cout << endl;
    }

    for (auto pad = pads_in_det.first; pad != pads_in_det.second; ++pad) {
      if (verboseDigi_)
        cout << "ME0PadDigi " << p_id << " " << *pad << endl;
      // check that the pad BX is within the range
      if (pad->bx() < minBXME0Pad_ || pad->bx() > maxBXME0Pad_)
        continue;
      // check that it matches a pad that was hit by SimHits from our track
      int padn = pad->pad();
      int strip1 = padn * 2;
      int strip2 = padn * 2 + 1;

      for (const auto& p : stripNumbersInDetId(id)) {
        if (strip1 == p or strip2 == p) {
          if (verbosePad_)
            cout << "...was matched!" << endl;
          detid_to_pads_[id].push_back(*pad);
          chamber_to_pads_[p_id.chamberId().rawId()].push_back(*pad);
          superchamber_to_pads_[superch_id()].push_back(*pad);
          break;
        }
      }
    }
  }
}

std::set<unsigned int> ME0DigiMatcher::detIdsDigi() const { return selectDetIds(detid_to_digis_); }

std::set<unsigned int> ME0DigiMatcher::detIdsPad() const { return selectDetIds(detid_to_pads_); }

std::set<unsigned int> ME0DigiMatcher::chamberIdsDigi() const { return selectDetIds(chamber_to_digis_); }

std::set<unsigned int> ME0DigiMatcher::chamberIdsPad() const { return selectDetIds(chamber_to_pads_); }

std::set<unsigned int> ME0DigiMatcher::superChamberIdsDigi() const { return selectDetIds(superchamber_to_digis_); }

std::set<unsigned int> ME0DigiMatcher::superChamberIdsPad() const { return selectDetIds(superchamber_to_pads_); }

const ME0DigiContainer& ME0DigiMatcher::digisInDetId(unsigned int detid) const {
  if (detid_to_digis_.find(detid) == detid_to_digis_.end())
    return no_digis_;
  return detid_to_digis_.at(detid);
}

const ME0DigiContainer& ME0DigiMatcher::digisInChamber(unsigned int detid) const {
  if (chamber_to_digis_.find(detid) == chamber_to_digis_.end())
    return no_digis_;
  return chamber_to_digis_.at(detid);
}

const ME0DigiContainer& ME0DigiMatcher::digisInSuperChamber(unsigned int detid) const {
  if (superchamber_to_digis_.find(detid) == superchamber_to_digis_.end())
    return no_digis_;
  return superchamber_to_digis_.at(detid);
}

const ME0PadDigiContainer& ME0DigiMatcher::padsInDetId(unsigned int detid) const {
  if (detid_to_pads_.find(detid) == detid_to_pads_.end())
    return no_pads_;
  return detid_to_pads_.at(detid);
}

const ME0PadDigiContainer& ME0DigiMatcher::padsInChamber(unsigned int detid) const {
  if (chamber_to_pads_.find(detid) == chamber_to_pads_.end())
    return no_pads_;
  return chamber_to_pads_.at(detid);
}

const ME0PadDigiContainer& ME0DigiMatcher::padsInSuperChamber(unsigned int detid) const {
  if (superchamber_to_pads_.find(detid) == superchamber_to_pads_.end())
    return no_pads_;
  return superchamber_to_pads_.at(detid);
}

int ME0DigiMatcher::nLayersWithDigisInSuperChamber(unsigned int detid) const {
  set<int> layers;
  ME0DetId sch_id(detid);
  for (int iLayer = 1; iLayer <= 6; iLayer++) {
    ME0DetId ch_id(sch_id.region(), iLayer, sch_id.chamber(), 0);
    // get the digis in this chamber
    const auto& digis = digisInChamber(ch_id.rawId());
    // at least one digi in this layer!
    if (!digis.empty()) {
      layers.insert(iLayer);
    }
  }
  return layers.size();
}

int ME0DigiMatcher::nLayersWithPadsInSuperChamber(unsigned int detid) const {
  set<int> layers;
  ME0DetId sch_id(detid);
  for (int iLayer = 1; iLayer <= 6; iLayer++) {
    ME0DetId ch_id(sch_id.region(), iLayer, sch_id.chamber(), 0);
    // get the digis in this chamber
    const auto& digis = padsInChamber(ch_id.rawId());
    // at least one digi in this layer!
    if (!digis.empty()) {
      layers.insert(iLayer);
    }
  }
  return layers.size();
}

int ME0DigiMatcher::nPads() const {
  int n = 0;
  const auto& ids = superChamberIdsPad();
  for (const auto& id : ids) {
    n += padsInSuperChamber(id).size();
  }
  return n;
}

std::set<int> ME0DigiMatcher::stripNumbersInDetId(unsigned int detid) const {
  set<int> result;
  const auto& digis = digisInDetId(detid);
  for (const auto& d : digis) {
    result.insert(d.strip());
  }
  return result;
}

std::set<int> ME0DigiMatcher::padNumbersInDetId(unsigned int detid) const {
  set<int> result;
  const auto& digis = padsInDetId(detid);
  for (const auto& d : digis) {
    result.insert(d.pad());
  }
  return result;
}

std::set<int> ME0DigiMatcher::partitionNumbers() const {
  std::set<int> result;

  const auto& detids = detIdsDigi();
  for (const auto& id : detids) {
    const ME0DetId& idd(id);
    result.insert(idd.roll());
  }
  return result;
}

ME0PadDigiContainer ME0DigiMatcher::pads() const {
  ME0PadDigiContainer out;
  for (const auto& id : chamberIdsPad()) {
    ME0PadDigiContainer temp = padsInChamber(id);
    out.insert(std::end(out), std::begin(temp), std::end(temp));
  }
  return out;
}
