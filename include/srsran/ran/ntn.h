/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsran/adt/optional.h"
#include <cstdint>
#include <string>
#include <variant>

namespace srsran {

struct ecef_coordinates_t {
  int position_x;
  int position_y;
  int position_z;
  int velocity_vx;
  int velocity_vy;
  int velocity_vz;
};

struct orbital_coordinates_t {
  uint64_t semi_major_axis;
  double   eccentricity;
  double   periapsis;
  double   longitude;
  double   mean_anomaly;
  double   inclination;
};

struct ta_common_t {
  unsigned ta_common;
  int      ta_common_drift;
  unsigned ta_common_drift_variant;
};

struct epoch_time_t {
  unsigned sfn;
  unsigned subframe_number;
};

struct ntn_config {
  /// SIB 19 values
  /// Reference location of the serving cell provided via NTN quasi-Earth fixed system. (TS 38.304)
  std::optional<std::string> reference_location;
  /// Distance from the serving cell reference location, as defined in TS 38.304. Each step represents 50m.
  std::optional<unsigned> distance_threshold;
  // NTN-config values
  /// Indicate the epoch time for the NTN assistance information.
  std::optional<epoch_time_t> epoch_time;
  /// Scheduling offset used for the timing relationships that are modified for NTN (see TS 38.213). The unit of the
  /// field K_offset is number of slots for a given subcarrier spacing of 15 kHz.
  unsigned cell_specific_koffset;
  /// Scheduling offset provided by network if downlink and uplink frame timing are not aligned at gNB.
  std::optional<unsigned> k_mac;
  /// This field provides satellite ephemeris either in format of position and velocity state vector or in format of
  /// orbital parameters.
  std::variant<ecef_coordinates_t, orbital_coordinates_t> ephemeris_info;
  /// Network-controlled common timing advanced value and it may include any timing offset considered necessary by the
  /// network.
  std::optional<ta_common_t> ta_info;
};
} // namespace srsran
