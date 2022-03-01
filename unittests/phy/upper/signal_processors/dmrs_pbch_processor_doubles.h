
#ifndef SRSGNB_DMRS_PBCH_PROCESSOR_DOUBLES_H
#define SRSGNB_DMRS_PBCH_PROCESSOR_DOUBLES_H

#include "srsgnb/phy/upper/signal_processors/dmrs_pbch_processor.h"

namespace srsgnb {

class dmrs_pbch_processor_spy : public dmrs_pbch_processor
{
private:
  struct entry_t {
    config_t              config;
    resource_grid_writer* grid;
  };
  std::vector<entry_t> entries;

public:
  void map(resource_grid_writer& grid, const config_t& config) override
  {
    entry_t entry = {};
    entry.config  = config;
    entry.grid    = &grid;
    entries.emplace_back(entry);
  }
  void                        reset() { entries.clear(); }
  unsigned                    get_nof_entries() const { return entries.size(); }
  const std::vector<entry_t>& get_entries() const { return entries; }
};

} // namespace srsgnb

#endif // SRSGNB_DMRS_PBCH_PROCESSOR_DOUBLES_H
