#include "bloom_filter.h"

BloomFilter::BloomFilter(size_t hashes, size_t bits) : _hashes(hashes), _bits(bits), _filter(bits, false) {
}

void BloomFilter::add(const std::string &value) {
  _raw_set.insert(value);
  for (size_t i = 0; i < _hashes; ++i) {
    size_t idx = _get_hash(i, value) % _bits;
    _filter[idx] = true;
  }
}

bool BloomFilter::verify(const std::string &value) {
  cnt++;
  for (size_t i = 0; i < _hashes; ++i) {
    size_t idx = _get_hash(i, value) % _bits;
    if (!_filter[idx]) return false;
  }

  if (_raw_set.find(value) == _raw_set.end()) {
    false_positive_cnt++;
  }

  return true;
}

double BloomFilter::getFPRate() const {
  return cnt == 0 ? 0.0 : static_cast<double>(false_positive_cnt) / cnt;
}

size_t BloomFilter::numberOfHashFunctions() const {
  return _hashes;
}

size_t BloomFilter::numberOfBits() const {
  return _bits;
}

inline size_t BloomFilter::_get_hash(int idx, const std::string& value) const {
  std::string salt = value + std::to_string(idx);
  return hasher(salt);
}
