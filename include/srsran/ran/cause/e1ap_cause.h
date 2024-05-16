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

#include "common.h"
#include "fmt/format.h"
#include <variant>

namespace srsran {

enum class e1ap_cause_radio_network_t : uint8_t {
  unspecified = 0,
  unknown_or_already_allocated_gnb_cu_cp_ue_e1ap_id,
  unknown_or_already_allocated_gnb_cu_up_ue_e1ap_id,
  unknown_or_inconsistent_pair_of_ue_e1ap_id,
  interaction_with_other_proc,
  ppdcp_count_wrap_around,
  not_supported_qci_value,
  not_supported_5qi_value,
  encryption_algorithms_not_supported,
  integrity_protection_algorithms_not_supported,
  up_integrity_protection_not_possible,
  up_confidentiality_protection_not_possible,
  multiple_pdu_session_id_instances,
  unknown_pdu_session_id,
  multiple_qos_flow_id_instances,
  unknown_qos_flow_id,
  multiple_drb_id_instances,
  unknown_drb_id,
  invalid_qos_combination,
  proc_cancelled,
  normal_release,
  no_radio_res_available,
  action_desirable_for_radio_reasons,
  res_not_available_for_the_slice,
  pdcp_cfg_not_supported,
  ue_dl_max_ip_data_rate_reason,
  up_integrity_protection_fail,
  release_due_to_pre_emption,
  rsn_not_available_for_the_up,
  npn_not_supported,
  report_characteristic_empty,
  existing_meas_id,
  meas_temporarily_not_available,
  meas_not_supported_for_the_obj
};

enum class e1ap_cause_transport_t : uint8_t { unspecified = 0, transport_res_unavailable, unknown_tnl_address_for_iab };

using e1ap_cause_t = std::variant<e1ap_cause_radio_network_t, e1ap_cause_transport_t, cause_protocol_t, cause_misc_t>;

} // namespace srsran

namespace fmt {

// e1ap_cause_t formatter
template <>
struct formatter<srsran::e1ap_cause_t> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx) -> decltype(ctx.begin())
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(srsran::e1ap_cause_t o, FormatContext& ctx) -> decltype(std::declval<FormatContext>().out())
  {
    if (const auto* result = std::get_if<srsran::e1ap_cause_radio_network_t>(&o)) {
      return format_to(ctx.out(), "radio_network-id{}", *result);
    }
    if (const auto* result = std::get_if<srsran::e1ap_cause_transport_t>(&o)) {
      return format_to(ctx.out(), "transport-id{}", *result);
    }
    if (const auto* result = std::get_if<srsran::cause_protocol_t>(&o)) {
      return format_to(ctx.out(), "protocol-id{}", *result);
    }
    return format_to(ctx.out(), "misc-id{}", std::get<srsran::cause_misc_t>(o));
  }
};

} // namespace fmt
