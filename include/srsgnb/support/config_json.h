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

#include "CLI/CLI11.hpp"

namespace srsgnb {

/// Creates an instance of a JSON configuration parser.
std::unique_ptr<CLI::Config> create_json_config_parser();

} // namespace srsgnb
