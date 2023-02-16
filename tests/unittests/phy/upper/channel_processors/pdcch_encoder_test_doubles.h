/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "../../phy_test_utils.h"
#include "srsgnb/phy/upper/channel_processors/channel_processor_factories.h"
#include <vector>

namespace srsran {

class pdcch_encoder_spy : public pdcch_encoder
{
private:
  struct entry_t {
    config_t             config;
    std::vector<uint8_t> data;
    std::vector<uint8_t> encoded;
  };
  std::vector<entry_t> entries;

public:
  void encode(span<uint8_t> encoded, span<const uint8_t> data, const config_t& config) override
  {
    // Generate new entry.
    entry_t entry = {};
    entry.config  = config;
    entry.encoded.resize(encoded.size());

    // Fill data.
    entry.data.resize(data.size());
    std::copy(data.begin(), data.end(), entry.data.begin());

    // Generate encoded message.
    for (unsigned i = 0, len = encoded.size(); i != len; ++i) {
      encoded[i]       = static_cast<uint8_t>(i & 0xff);
      entry.encoded[i] = encoded[i];
    }

    // Append entry.
    entries.emplace_back(entry);
  }

  void                        reset() { entries.clear(); }
  unsigned                    get_nof_entries() const { return entries.size(); }
  const std::vector<entry_t>& get_entries() const { return entries; }
};

PHY_SPY_FACTORY_TEMPLATE(pdcch_encoder);

} // namespace srsran