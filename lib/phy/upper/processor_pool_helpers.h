/*
 *
 * Copyright 2013-2022 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsgnb/ran/slot_point.h"
#include "srsgnb/ran/subcarrier_spacing.h"
#include <array>

namespace srsgnb {

/// \brief Represents a sector in the pool of processors.
template <typename T>
class pool_procesor_sector
{
  /// Container of processors<T>. Each entry belongs to a different slot.
  using processor_pool = std::vector<std::unique_ptr<T>>;

  /// Container of processor pools. Each entry belongs to a different numerology.
  std::array<processor_pool, NOF_NUMEROLOGIES> numerologies;

public:
  /// \brief Returns a reference to a processor using the given slot.
  T& get_processor(slot_point slot)
  {
    unsigned numerology = slot.numerology();
    srsgnb_assert(numerology < NOF_NUMEROLOGIES, "Invalid numerology ({}).", numerology);

    processor_pool& pool = numerologies[numerology];
    srsgnb_assert(!pool.empty(), "Numerology ({}) has no processors.", numerology);

    unsigned index = slot.system_slot() % pool.size();
    return *pool[index];
  }

  /// \brief Associates the given processor pool with this sector.
  ///
  /// \param[in] scs Subcarrier spacing.
  /// \param[in] obj New processor pool for the current sector.
  void insert(subcarrier_spacing scs, processor_pool&& obj)
  {
    unsigned numerology = to_numerology_value(scs);
    srsgnb_assert(numerology < NOF_NUMEROLOGIES, "Invalid numerology ({}).", numerology);

    processor_pool& pool = numerologies[numerology];
    srsgnb_assert(pool.empty(), "Numerology ({}) already has processors.", numerology);

    numerologies[numerology] = std::move(obj);
  }
};

} // namespace srsgnb
