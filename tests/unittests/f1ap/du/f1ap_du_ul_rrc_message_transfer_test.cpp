/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "f1ap_du_test_helpers.h"
#include "lib/f1ap/du/ue_context/f1c_du_bearer_impl.h"
#include "srsran/support/test_utils.h"
#include <gtest/gtest.h>

using namespace srsran;
using namespace srs_du;
using namespace asn1::f1ap;

TEST_F(f1ap_du_test, when_sdu_is_received_then_sdu_is_forwarded_to_tx_pdu_notifier_as_ul_rrc_message_transfer)
{
  // Run Test Preamble.
  run_f1_setup_procedure();
  ue_test_context* ue                  = run_f1ap_ue_create(to_du_ue_index(0));
  this->msg_notifier.last_f1ap_msg.pdu = {};

  std::vector<uint8_t> bytes = test_rgen::random_vector<uint8_t>(test_rgen::uniform_int<unsigned>(1, 4000));
  byte_buffer          sdu{bytes};
  ue->f1c_bearers[1].bearer->handle_sdu(byte_buffer_slice_chain{sdu.copy()});

  ASSERT_EQ(this->msg_notifier.last_f1ap_msg.pdu.type().value, asn1::f1ap::f1ap_pdu_c::types_opts::init_msg);
  ASSERT_EQ(this->msg_notifier.last_f1ap_msg.pdu.init_msg().proc_code, ASN1_F1AP_ID_UL_RRC_MSG_TRANSFER);
  const ul_rrc_msg_transfer_s& ul_rrc_msg = this->msg_notifier.last_f1ap_msg.pdu.init_msg().value.ul_rrc_msg_transfer();
  ASSERT_EQ(ul_rrc_msg->srb_id->value, 1);
  ASSERT_EQ(ul_rrc_msg->rrc_container.value, sdu);
}
