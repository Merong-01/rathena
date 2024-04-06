// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Atcommands
 * Place the body of custom atcommands in this file.
 * Format:
 *	ACMD_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//ACMD_FUNC(newcommand)
//{
//	clif_displaymessage(fd, "It works!");
//	clif_specialeffect(&sd->bl, EF_HEARTCASTING, AREA);
//	return 0;
//}

ACMD_FUNC(whosell)
{
	uint16 search_store_type = 0; //SEARCHTYPE_VENDING

	if (!message || !*message) {
		clif_displaymessage(fd, "Please enter item name/ID (usage: @whosell/buy <item name/ID>).");
		return -1;
	}

	if(strstr(command, "buy") != NULL){
		search_store_type = 1; //SEARCHTYPE_BUYING_STORE
	}

	std::map<t_itemid, std::shared_ptr<item_data>> item_array = {};
	uint16 count = 1;
	t_itemid itemid = strtoul(message, nullptr, 10);

	if (itemid == 0) // Entered a string
		count = itemdb_searchname_array(item_array, MAX_SEARCH, message);
	else {
		if ((item_array[0] = item_db.find(itemid)) == nullptr)
			count = 0;
	}

	if (!count) {
		clif_displaymessage(fd, msg_txt(sd,19));	// Invalid item ID or name.
		return -1;
	}

	if (count == MAX_SEARCH) {
		sprintf(atcmd_output, msg_txt(sd,269), MAX_SEARCH); // Displaying first %d matches
		clif_displaymessage(fd, atcmd_output);
	}

	for (const auto &result : item_array) {
		std::shared_ptr<item_data> id = result.second;

		sprintf(atcmd_output, msg_txt(sd,1285), item_db.create_item_link( id ).c_str(), id->nameid); // Item: '%s' (ID:%u)
		clif_displaymessage(fd, atcmd_output);

		struct s_mapiterator* iter = mapit_getallusers();
		map_session_data* pl_sd;
		for( pl_sd = (TBL_PC*)mapit_first(iter); mapit_exists(iter); pl_sd = (TBL_PC*)mapit_next(iter) )
		{
			if(pl_sd->mapindex != sd->mapindex){
				continue;
			}

			if(search_store_type == 0){
				if(!vending_search(pl_sd, id->nameid)){
					continue;
				}
			}
			else if(search_store_type == 1){
				if(!buyingstore_search(pl_sd, id->nameid)){
					continue;
				}
			}
			else {
				clif_displaymessage(fd, "Invalid search store type");
				return -1;
			}

			sprintf(atcmd_output, msg_txt(sd,481), // Player '%s' (session #%d) | Location: %d,%d
				        pl_sd->status.name, pl_sd->fd, pl_sd->bl.x, pl_sd->bl.y);
			clif_displaymessage(fd, atcmd_output);
		}
		mapit_free(iter);
	}

	return 0;
}
