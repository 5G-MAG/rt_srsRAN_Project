/*
 *
 * Copyright 2013-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once
#include "srsgnb/ran/rnti.h"
#include "srsgnb/scheduler/harq_id.h"

namespace srsran {

/// PUSCH transmission context.
class pusch_context
{
public:
  /// Default constructor.
  pusch_context() = default;

private:
  friend struct fmt::formatter<pusch_context>;
  rnti_t    rnti = INVALID_RNTI;
  harq_id_t h_id = INVALID_HARQ_ID;
};

} // namespace srsran