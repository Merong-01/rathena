// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom battle config initializations
 * Place the definition of custom battle configuration initializations in this file.
 *
 * Do not forget to add a comma at the end of the line, if you want to add another config
 *
 * Format:
 *	 { "name", &battle_config.<variable name>, <default value>, <minimum value>, <maximum value> },
 **/
 { "right_hand_mastery_buff", &battle_config.as_rightHandMasteryBuff, 0, 0, 1},
 { "left_hand_mastery_buff", &battle_config.as_leftHandMasteryBuff, 0, 0, 1},
 { "enable_double_attack_critical", &battle_config.tf_doubleAttackEnableCritical, 0, 0, 1},
 { "katar_mastery_crit_bonus", &battle_config.as_katarMasteryCritBonus, 0, 0, 1},
 { "venom_splasher_renewal_setting", &battle_config.as_splasherRenewalSetting, 0, 0, 1},
 { "spear_mastery_aspd_buff", &battle_config.kn_spearMasteryAspdBuff, 0, 0, 1},
 { "mace_mastery_aspd_buff", &battle_config.pr_maceMasteryAspdBuff, 0, 0, 1},
 { "spear_quicken_buff", &battle_config.cr_spearQuickenBuff, 0, 0, 1},
 { "auto_spell_buff", &battle_config.sa_autoSpellBuff, 0, 0, 1},
