#include "rib.h"

void Rib::add_pending_agent(int agent_id) {
  pending_agents_.insert(agent_id);
}

void Rib::remove_pending_agent(int agent_id) {
  pending_agents_.erase(agent_id);
}

bool Rib::agent_is_pending(int agent_id) {
  auto search = pending_agents_.find(agent_id);
  return search != pending_agents_.end();
}

void Rib::new_eNB_config_entry(int agent_id) {
  eNB_configs_.insert(std::pair<int,
		      std::shared_ptr<enb_rib_info>>(agent_id,
						     std::shared_ptr<enb_rib_info>(new enb_rib_info(agent_id))));
}

bool Rib::has_eNB_config_entry(int agent_id) {
  auto it = eNB_configs_.find(agent_id);
  return it != eNB_configs_.end();
}

void Rib::eNB_config_update(int agent_id,
			    const protocol::prp_enb_config_reply& enb_config_update) {
  auto it = eNB_configs_.find(agent_id);

  if (it == eNB_configs_.end()) {
    return;
  } else {
    it->second->update_eNB_config(enb_config_update);
  }
}

void Rib::ue_config_update(int agent_id,
			   const protocol::prp_ue_config_reply& ue_config_update) {
  auto it = eNB_configs_.find(agent_id);

  if (it == eNB_configs_.end()) {
    return;
  } else {
    it->second->update_UE_config(ue_config_update);
  }
}

void Rib::lc_config_update(int agent_id,
			   const protocol::prp_lc_config_reply& lc_config_update) {
  auto it = eNB_configs_.find(agent_id);

  if (it == eNB_configs_.end()) {
    return;
  } else {
    it->second->update_LC_config(lc_config_update);
  }
}