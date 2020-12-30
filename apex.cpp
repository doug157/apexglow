#include "includes.h"

char* apex::get_level_name()
{
	auto level_name = (std::byte*)GetModuleHandleW(nullptr) + LEVEL_NAME;
	if (level_name) { return (char*)level_name; }
	return nullptr;
}

std::byte* apex::get_entity(uint64_t Id)
{
	auto entity_list = (std::byte*)GetModuleHandleW(nullptr) + ENTITY_LIST;
	auto base_entity = *(std::byte**)entity_list;
	if (!base_entity) { return nullptr; }
	return *(std::byte**)(entity_list + (Id << 5));
}

std::string apex::get_entity_type(std::byte* entity)
{
	if (!entity) return {};
	std::string result;
	result.assign(*(char**)(entity + ENTITY_TYPE));
	return result;
}

uint8_t apex::get_signon_state()
{
	return *(uint8_t*)((std::byte*)GetModuleHandleW(nullptr) + SIGNON_STATE);
}

bool apex::is_in_game()
{
	if (get_signon_state() == 8 && get_level_name()[0] != '\0' && !!strcmp(get_level_name(), "mp_lobby")) { return true; }
	return false;
}

void apex::set_highlight(std::byte* entity)
{
	memcpy((bool*)(entity + GLOW), new bool(true), sizeof(bool));
	memcpy((int*)(entity + HIGHLIGHT_CONTEXT), new int(1), sizeof(int));
	memcpy((float*)(entity + GLOW_RANGE), new float(INFINITY), sizeof(float));

	for (auto i = GLOW_DURATION; i < GLOW_DURATION + 0x18; i += 0x4)
		memcpy((float*)(entity + i), new float(INFINITY), sizeof(float));

	static const float color[3] = {
		((SRGB >> 16) & 0xff) * BRIGHTNESS,
		((SRGB >> 8) & 0xff) * BRIGHTNESS,
		((SRGB >> 0) & 0xff) * BRIGHTNESS,
	};

	memcpy(entity + COLOR, color, sizeof(color));
}

void apex::highlight_loop()
{
	if (apex::is_in_game())
	{
		for (auto i = 0; i < 100; i++)
		{
			auto entity = apex::get_entity(i);
			if (!entity) { continue; }
			auto entity_type = apex::get_entity_type(entity);
			if (strcmp(entity_type.c_str(), "player") == 0)
			{
				if (!apex::is_in_game()) { break; }
				apex::set_highlight(entity);
			}
		}
	}
}