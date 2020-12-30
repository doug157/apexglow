#pragma once

class apex
{
public:
	static char* get_level_name();
	static std::byte* get_entity(uint64_t Id);
	static std::string get_entity_type(std::byte* entity);
	static uint8_t get_signon_state();
	static bool is_in_game();
	static void set_highlight(std::byte* entity);
	static void highlight_loop();
};