#ifndef FCODER_ROSORIO
#define FCODER_ROSORIO





#define EXTRA_KEYWORDS "rosorio_extra_keywords.inl" // New keywords for our C/C++ code
#include "4coder_default_include.cpp"





#include "prelude.cpp"





enum class Editor_Mode {
    Normal,
    Insert,
};

struct Editor_Globals {
    Editor_Mode mode = Editor_Mode::Normal;
};

global_variable
auto editor_globals = Editor_Globals {};

internal
procedure normal_mode() { return editor_globals.mode == Editor_Mode::Normal; }
internal
procedure insert_mode() { return editor_globals.mode == Editor_Mode::Insert; }
internal
procedure switch_to_normal_mode() { editor_globals.mode = Editor_Mode::Normal; }
internal
procedure switch_to_insert_mode() { editor_globals.mode = Editor_Mode::Insert; }





// # KEYS


CUSTOM_COMMAND_SIG(modal_esc)
CUSTOM_DOC("Does whatever the modal ESC key does, probably just switch to normal mode")
{
    switch_to_normal_mode();
}



CUSTOM_COMMAND_SIG(modal_character)
CUSTOM_DOC("Inserts whatever character was used to trigger this command.")
{
    User_Input in = get_command_input(app);
    uint8_t characters[4];
    uint32_t length = to_writable_character(in, characters);
    
    if (insert_mode()) {
        write_character_parameter(app, characters, length);
    } else if (normal_mode()) {
        if (length == 1) {
            auto character = (char)tolower((int)(characters[0]));
            auto shift = in.key.modifiers[MDFR_SHIFT_INDEX];
            auto control = in.key.modifiers[MDFR_CONTROL_INDEX];
            auto alt = in.key.modifiers[MDFR_ALT_INDEX];
            auto nothing = [&,character, shift, control, alt](){
                printf("Key %c with shift %spressed, control %spressed and alt %spressed is not bound to anything\n", 
                       character,
                       shift ? "" : "not ",
                       control ? "" : "not ",
                       alt ? "" : "not ");
            };
            switch(character) {
                case 'q': {
                    nothing();
                    break;
                }
                case 'w': {
                    nothing();
                    break;
                }
                case 'e': {
                    nothing();
                    break;
                }
                case 'r': {
                    nothing();
                    break;
                }
                case 't': {
                    nothing();
                    break;
                }
                case 'y': {
                    nothing();
                    break;
                }
                case 'u': {
                    nothing();
                    break;
                }
                case 'i': {
                    switch_to_insert_mode();
                    break;
                }
                case 'o': {
                    nothing();
                    break;
                }
                case 'p': {
                    nothing();
                    break;
                }
                case 'a': {
                    nothing();
                    break;
                }
                case 's': {
                    nothing();
                    break;
                }
                case 'd': {
                    nothing();
                    break;
                }
                case 'f': {
                    nothing();
                    break;
                }
                case 'g': {
                    nothing();
                    break;
                }
                case 'h': {
                    move_left(app);
                    break;
                }
                case 'j': {
                    move_down(app);
                    break;
                }
                case 'k': {
                    move_up(app);
                    break;
                }
                case 'l': {
                    move_right(app);
                    break;
                }
                case 'z': {
                    nothing();
                    break;
                }
                case 'x': {
                    nothing();
                    break;
                }
                case 'c': {
                    nothing();
                    break;
                }
                case 'v': {
                    nothing();
                    break;
                }
                case 'b': {
                    nothing();
                    break;
                }
                case 'n': {
                    nothing();
                    break;
                }
                case 'm': {
                    nothing();
                    break;
                }
                case '_': {
                    nothing();
                    break;
                }
                case '[': {
                    nothing();
                    break;
                }
                case ']': {
                    nothing();
                    break;
                }
                case ';': {
                    nothing();
                    break;
                }
                case '\'': {
                    nothing();
                    break;
                }
                case ',': {
                    nothing();
                    break;
                }
                case '.': {
                    nothing();
                    break;
                }
                case '/': {
                    nothing();
                    break;
                }
            }
        }
    }
    
}



//
// The modal keys bound right now only work if we would have written 
// a character instead.
//
// This means that all the previous keybindings that worked before with 4coder
// work as they did both in Insert and Normal mode. This still means that 
// we have all the shift+key combinations (and a lot of the others to be honest).
//
procedure bind_keys (Bind_Helper* context) -> void {
    
    // NOTE(rosorio): Look in 4coder_generater/remapping.h to
    // see other options of keys that are bound by default that
    // I might want bound too?
    
    auto bind_global_keys = [&](){
        bind(context, ',', MDFR_CTRL, change_active_panel);
        bind(context, '<', MDFR_CTRL, change_active_panel_backwards);
        bind(context, 'n', MDFR_CTRL, interactive_new);
        bind(context, 'o', MDFR_CTRL, interactive_open_or_new);
        bind(context, 'o', MDFR_ALT, open_in_other);
        bind(context, 'k', MDFR_CTRL, interactive_kill_buffer);
        bind(context, 'i', MDFR_CTRL, interactive_switch_buffer);
        bind(context, 'h', MDFR_CTRL, project_go_to_root_directory);
        bind(context, 'S', MDFR_CTRL, save_all_dirty_buffers);
        bind(context, '.', MDFR_ALT, change_to_build_panel);
        bind(context, ',', MDFR_ALT, close_build_panel);
        bind(context, 'n', MDFR_ALT, goto_next_jump_sticky);
        bind(context, 'N', MDFR_ALT, goto_prev_jump_sticky);
        bind(context, 'M', MDFR_ALT, goto_first_jump_sticky);
        bind(context, 'm', MDFR_ALT, build_in_build_panel);
        bind(context, 'b', MDFR_ALT, toggle_filebar);
        bind(context, 'z', MDFR_ALT, execute_any_cli);
        bind(context, 'Z', MDFR_ALT, execute_previous_cli);
        bind(context, 'x', MDFR_ALT, command_lister);
        bind(context, 'X', MDFR_ALT, project_command_lister);
        bind(context, 'I', MDFR_CTRL, list_all_functions_all_buffers_lister);
        bind(context, 'E', MDFR_ALT, exit_4coder);
        bind(context, key_f1, MDFR_NONE, project_fkey_command);
        bind(context, key_f2, MDFR_NONE, project_fkey_command);
        bind(context, key_f3, MDFR_NONE, project_fkey_command);
        bind(context, key_f4, MDFR_NONE, project_fkey_command);
        bind(context, key_f5, MDFR_NONE, project_fkey_command);
        bind(context, key_f6, MDFR_NONE, project_fkey_command);
        bind(context, key_f7, MDFR_NONE, project_fkey_command);
        bind(context, key_f8, MDFR_NONE, project_fkey_command);
        bind(context, key_f9, MDFR_NONE, project_fkey_command);
        bind(context, key_f10, MDFR_NONE, project_fkey_command);
        bind(context, key_f11, MDFR_NONE, project_fkey_command);
        bind(context, key_f12, MDFR_NONE, project_fkey_command);
        bind(context, key_f13, MDFR_NONE, project_fkey_command);
        bind(context, key_f14, MDFR_NONE, project_fkey_command);
        bind(context, key_f15, MDFR_NONE, project_fkey_command);
        bind(context, key_f16, MDFR_NONE, project_fkey_command);
        bind(context, key_mouse_wheel, MDFR_NONE, mouse_wheel_scroll);
        bind(context, key_mouse_wheel, MDFR_CTRL, mouse_wheel_change_face_size);
    };
    
    {
        begin_map(context, mapid_global);
        defer { end_map(context); };
        bind_global_keys();
    }
    
    
    {
        begin_map(context, mapid_file);
        defer { end_map(context); };
        
        
        for (auto i = 0; i < 32; ++i) {
            // We're binding all the combinations of MDFR_*
            // that we can have, we'll overwrite them later.
            bind(context, 0, i, modal_character);
        }
        bind(context, key_esc, MDFR_NONE, modal_esc);
        
        bind_global_keys();
        
        bind(context, key_mouse_left, MDFR_NONE, click_set_cursor_and_mark);
        bind(context, key_click_activate_view, MDFR_NONE, click_set_cursor_and_mark);
        bind(context, key_mouse_left_release, MDFR_NONE, click_set_cursor);
        bind(context, key_mouse_move, MDFR_NONE, click_set_cursor_if_lbutton);
        
        bind(context, key_del, MDFR_NONE, delete_char);
        bind(context, key_del, MDFR_SHIFT, delete_char);
        bind(context, key_back, MDFR_NONE, backspace_char);
        bind(context, key_back, MDFR_SHIFT, backspace_char);
        bind(context, key_up, MDFR_NONE, move_up);
        bind(context, key_down, MDFR_NONE, move_down);
        bind(context, key_left, MDFR_NONE, move_left);
        bind(context, key_right, MDFR_NONE, move_right);
        bind(context, key_up, MDFR_SHIFT, move_up);
        bind(context, key_down, MDFR_SHIFT, move_down);
        bind(context, key_left, MDFR_SHIFT, move_left);
        bind(context, key_right, MDFR_SHIFT, move_right);
        bind(context, key_end, MDFR_NONE, seek_end_of_line);
        bind(context, key_home, MDFR_NONE, seek_beginning_of_line);
        bind(context, key_page_up, MDFR_CTRL, goto_beginning_of_file);
        bind(context, key_page_down, MDFR_CTRL, goto_end_of_file);
        bind(context, key_page_up, MDFR_NONE, page_up);
        bind(context, key_page_down, MDFR_NONE, page_down);
        bind(context, key_end, MDFR_SHIFT, seek_end_of_line);
        bind(context, key_home, MDFR_SHIFT, seek_beginning_of_line);
        bind(context, key_page_up, MDFR_CTRL|MDFR_SHIFT, goto_beginning_of_file);
        bind(context, key_page_down, MDFR_CTRL|MDFR_SHIFT, goto_end_of_file);
        bind(context, key_page_up, MDFR_SHIFT, page_up);
        bind(context, key_page_down, MDFR_SHIFT, page_down);
        bind(context, key_up, MDFR_CTRL, seek_whitespace_up_end_line);
        bind(context, key_down, MDFR_CTRL, seek_whitespace_down_end_line);
        bind(context, key_left, MDFR_CTRL, seek_whitespace_left);
        bind(context, key_right, MDFR_CTRL, seek_whitespace_right);
        bind(context, key_up, MDFR_CTRL|MDFR_SHIFT, seek_whitespace_up_end_line);
        bind(context, key_down, MDFR_CTRL|MDFR_SHIFT, seek_whitespace_down_end_line);
        bind(context, key_left, MDFR_CTRL|MDFR_SHIFT, seek_whitespace_left);
        bind(context, key_right, MDFR_CTRL|MDFR_SHIFT, seek_whitespace_right);
        bind(context, key_up, MDFR_ALT, move_line_up);
        bind(context, key_down, MDFR_ALT, move_line_down);
        bind(context, key_back, MDFR_CTRL, backspace_word);
        bind(context, key_del, MDFR_CTRL, delete_word);
        bind(context, key_back, MDFR_ALT, snipe_token_or_word);
        bind(context, key_del, MDFR_ALT, snipe_token_or_word_right);
        bind(context, 'a', MDFR_CTRL, replace_in_range);
        bind(context, 'c', MDFR_CTRL, copy);
        bind(context, 'd', MDFR_CTRL, delete_range);
        bind(context, 'D', MDFR_CTRL, delete_line);
        bind(context, 'e', MDFR_CTRL, center_view);
        bind(context, 'E', MDFR_CTRL, left_adjust_view);
        bind(context, 'f', MDFR_CTRL, search);
        bind(context, 'F', MDFR_CTRL, list_all_locations);
        bind(context, 'F', MDFR_ALT, list_all_substring_locations_case_insensitive);
        bind(context, 'g', MDFR_CTRL, goto_line);
        bind(context, 'G', MDFR_CTRL, list_all_locations_of_selection);
        bind(context, 'j', MDFR_CTRL, snippet_lister);
        bind(context, 'K', MDFR_CTRL, kill_buffer);
        bind(context, 'L', MDFR_CTRL, duplicate_line);
        bind(context, 'm', MDFR_CTRL, cursor_mark_swap);
        bind(context, 'O', MDFR_CTRL, reopen);
        bind(context, 'q', MDFR_CTRL, query_replace);
        bind(context, 'Q', MDFR_CTRL, query_replace_identifier);
        bind(context, 'q', MDFR_ALT, query_replace_selection);
        bind(context, 'r', MDFR_CTRL, reverse_search);
        bind(context, 's', MDFR_CTRL, save);
        bind(context, 't', MDFR_CTRL, search_identifier);
        bind(context, 'T', MDFR_CTRL, list_all_locations_of_identifier);
        bind(context, 'v', MDFR_CTRL, paste_and_indent);
        bind(context, 'V', MDFR_CTRL, paste_next_and_indent);
        bind(context, 'x', MDFR_CTRL, cut);
        bind(context, 'y', MDFR_CTRL, redo);
        bind(context, 'z', MDFR_CTRL, undo);
        bind(context, '1', MDFR_CTRL, view_buffer_other_panel);
        bind(context, '2', MDFR_CTRL, swap_buffers_between_panels);
        bind(context, '\n', MDFR_NONE, newline_or_goto_position_sticky);
        bind(context, '\n', MDFR_SHIFT, newline_or_goto_position_same_panel_sticky);
        bind(context, '>', MDFR_CTRL, view_jump_list_with_lister);
        bind(context, ' ', MDFR_SHIFT, write_character);
    }
    
    {
        begin_map(context, default_code_map);
        defer { end_map(context); };
        inherit_map(context, mapid_file);
        bind(context, key_left, MDFR_CTRL, seek_alphanumeric_or_camel_left);
        bind(context, key_right, MDFR_CTRL, seek_alphanumeric_or_camel_right);
        bind(context, '\n', MDFR_NONE, write_and_auto_tab);
        bind(context, '\n', MDFR_SHIFT, write_and_auto_tab);
        bind(context, '}', MDFR_NONE, write_and_auto_tab);
        bind(context, ')', MDFR_NONE, write_and_auto_tab);
        bind(context, ']', MDFR_NONE, write_and_auto_tab);
        bind(context, ';', MDFR_NONE, write_and_auto_tab);
        bind(context, '#', MDFR_NONE, write_and_auto_tab);
        bind(context, ';', MDFR_CTRL, comment_line_toggle);
        bind(context, '\t', MDFR_NONE, word_complete);
        bind(context, '\t', MDFR_CTRL, auto_tab_range);
        bind(context, '\t', MDFR_SHIFT, auto_tab_line_at_cursor);
        bind(context, 'r', MDFR_ALT, write_block);
        bind(context, 't', MDFR_ALT, write_todo);
        bind(context, 'y', MDFR_ALT, write_note);
        bind(context, 'D', MDFR_ALT, list_all_locations_of_type_definition);
        bind(context, 'T', MDFR_ALT, list_all_locations_of_type_definition_of_identifier);
        bind(context, '[', MDFR_CTRL, open_long_braces);
        bind(context, '{', MDFR_CTRL, open_long_braces_semicolon);
        bind(context, '}', MDFR_CTRL, open_long_braces_break);
        bind(context, '[', MDFR_ALT, select_surrounding_scope);
        bind(context, ']', MDFR_ALT, select_prev_scope_absolute);
        bind(context, '\'', MDFR_ALT, select_next_scope_absolute);
        bind(context, '/', MDFR_ALT, place_in_scope);
        bind(context, '-', MDFR_ALT, delete_current_scope);
        bind(context, 'j', MDFR_ALT, scope_absorb_down);
        bind(context, 'i', MDFR_ALT, if0_off);
        bind(context, '1', MDFR_ALT, open_file_in_quotes);
        bind(context, '2', MDFR_ALT, open_matching_file_cpp);
        bind(context, '0', MDFR_CTRL, write_zero_struct);
    }
    
    {
        begin_map(context, default_lister_ui_map);
        defer { end_map(context); };
        bind_vanilla_keys(context, lister__write_character);
        bind(context, key_esc, MDFR_NONE, lister__quit);
        bind(context, '\n', MDFR_NONE, lister__activate);
        bind(context, '\t', MDFR_NONE, lister__activate);
        bind(context, key_back, MDFR_NONE, lister__backspace_text_field);
        bind(context, key_up, MDFR_NONE, lister__move_up);
        bind(context, 'k', MDFR_ALT, lister__move_up);
        bind(context, key_page_up, MDFR_NONE, lister__move_up);
        bind(context, key_down, MDFR_NONE, lister__move_down);
        bind(context, 'j', MDFR_ALT, lister__move_down);
        bind(context, key_page_down, MDFR_NONE, lister__move_down);
        bind(context, key_mouse_wheel, MDFR_NONE, lister__wheel_scroll);
        bind(context, key_mouse_left, MDFR_NONE, lister__mouse_press);
        bind(context, key_mouse_left_release, MDFR_NONE, lister__mouse_release);
        bind(context, key_mouse_move, MDFR_NONE, lister__repaint);
        bind(context, key_animate, MDFR_NONE, lister__repaint);
    }
    
}





// # HOOKS


procedure on_open_file (Application_Links *app, Buffer_ID buffer_id) -> int32_t {
    auto ret = default_file_settings(app, buffer_id);
    // TODO(rosorio): Set the buffer as a readonly buffer if the file is read only
    return ret;
}



struct Textual_Highlight {
    int32_t first;
    int32_t one_past_last;
    int_color background_color;
    int_color text_color;
};



internal
procedure sort_textual_highlights (Textual_Highlight *records, int32_t first, int32_t one_past_last) -> void {
    if (first + 1 < one_past_last){
        int32_t pivot_index = one_past_last - 1;
        int_color pivot_color = records[pivot_index].text_color;
        int32_t j = first;
        for (int32_t i = first; i < pivot_index; i += 1){
            int_color color = records[i].text_color;
            if (color < pivot_color){
                Swap(Textual_Highlight, records[i], records[j]);
                j += 1;
            }
        }
        Swap(Textual_Highlight, records[pivot_index], records[j]);
        pivot_index = j;
        
        sort_textual_highlights(records, first, pivot_index);
        sort_textual_highlights(records, pivot_index + 1, one_past_last);
    }
}



procedure on_render (struct Application_Links *app, View_ID view_id, Range on_screen_range, Render_Callback *do_core_render) -> void {
    View_Summary view = get_view(app, view_id, AccessAll);
    Buffer_Summary buffer = get_buffer(app, view.buffer_id, AccessAll);
    View_Summary active_view = get_active_view(app, AccessAll);
    bool32 is_active_view = (active_view.view_id == view_id);
    
    static Managed_Scope render_scope = 0;
    if (render_scope == 0){
        render_scope = create_user_managed_scope(app);
    }
    
    Partition *scratch = &global_part;
    
    // Textual Highlighting
    {
        Theme_Color colors[2];
        colors[0].tag = Stag_Text_Cycle_2;
        colors[1].tag = Stag_Text_Cycle_1;
        get_theme_colors(app, colors, 2);
        
        Temp_Memory temp = begin_temp_memory(scratch);
        int32_t text_size = on_screen_range.one_past_last - on_screen_range.first;
        char *text = push_array(scratch, char, text_size);
        buffer_read_range(app, &buffer, on_screen_range.first, on_screen_range.one_past_last, text);
        
        Textual_Highlight *records = push_array(scratch, Textual_Highlight, 0);
        String tail = make_string(text, text_size);
        
        // Iterate through all the visible text
        for (int32_t i = 0; i < text_size; tail.str += 1, tail.size -= 1, i += 1) {
            if (tail.str[0] == '#') { // We might be in a hex color
                auto* color_string = tail.str + 1;
                auto color_string_count = tail.size - 1; 
                
                auto hex_to_int = [](char c) -> int {
                    if (c >= '0' && c <= '9')
                        return (c - '0');
                    else if (c >= 'a' && c <= 'f')
                        return (c - 'a' + 10);
                    else if (c >= 'A' && c <= 'F')
                        return (c - 'A' + 10);
                    return -1;
                };
                
                auto count = 0;
                while ((count < color_string_count) &&
                       (hex_to_int(color_string[count]) >= 0) &&
                       (count < 8))
                {
                    count += 1;
                }
                
                auto highlight_color = int_color {0xFF000000};
                auto do_alpha = false;
                
                auto red   = int{0};
                auto green = int{0};
                auto blue  = int{0};
                auto alpha = int{255};
                
                if (count == 3) { // #RGB
                    red   = hex_to_int(color_string[0]) << 4;
                    green = hex_to_int(color_string[1]) << 4;
                    blue  = hex_to_int(color_string[2]) << 4;
                } else if (count == 4) { // #RGBA
                    red   = hex_to_int(color_string[0]) << 4;
                    green = hex_to_int(color_string[1]) << 4;
                    blue  = hex_to_int(color_string[2]) << 4;
                    alpha = hex_to_int(color_string[3]) << 4;
                } else if (count == 6) { // #RRGGBB
                    red   = (hex_to_int(color_string[0]) << 4) | hex_to_int(color_string[1]);
                    green = (hex_to_int(color_string[2]) << 4) | hex_to_int(color_string[3]);
                    blue  = (hex_to_int(color_string[4]) << 4) | hex_to_int(color_string[5]);
                } else if (count == 8) { // #RRGGBBAA
                    red   = (hex_to_int(color_string[0]) << 4) | hex_to_int(color_string[1]);
                    green = (hex_to_int(color_string[2]) << 4) | hex_to_int(color_string[3]);
                    blue  = (hex_to_int(color_string[4]) << 4) | hex_to_int(color_string[5]);
                    alpha = (hex_to_int(color_string[6]) << 4) | hex_to_int(color_string[7]);
                } else {
                    continue;
                }
                
                if (do_alpha) highlight_color |= alpha << (8 * 3);
                highlight_color |= red   << (8 * 2); 
                highlight_color |= green << (8 * 1); 
                highlight_color |= blue;
                auto opposite_color = ((highlight_color) & (0xFF000000)) | ((~highlight_color) & (0x00FFFFFF)); 
                
                if (std::max(std::max(abs(red - 127), abs(green - 127)), abs(blue - 127)) < 35) {
                    opposite_color = 0xFF000000;
                }
                
                // Highlight the text
                {
                    Textual_Highlight *record = push_array(scratch, Textual_Highlight, 1);
                    record->first = i + on_screen_range.first;
                    record->one_past_last = record->first + count + 1;
                    record->text_color = opposite_color;
                    record->background_color = highlight_color;
                }
                
                tail.str += count + 1;
                tail.size -= count + 1;
                i += count + 1;
            } else if (match_part(tail, make_lit_string("NOTE"))) {
                // In here and in the next one we try to match if the beggining of where we are in
                // the buffer matches with the NOTE/TODO string.
                Textual_Highlight *record = push_array(scratch, Textual_Highlight, 1);
                record->first = i + on_screen_range.first;
                record->one_past_last = record->first + 4;
                record->text_color = colors[0].color;
                record->background_color = SymbolicColor_Transparent;
                // We increment by 3 because the for is gonna do anoter +1 for us
                tail.str += 3;
                tail.size -= 3;
                i += 3;
            } else if (match_part(tail, make_lit_string("TODO"))) {
                Textual_Highlight *record = push_array(scratch, Textual_Highlight, 1);
                record->first = i + on_screen_range.first;
                record->one_past_last = record->first + 4;
                record->text_color = colors[1].color;
                record->background_color = SymbolicColor_Transparent;
                tail.str += 3;
                tail.size -= 3;
                i += 3;
            }
        }
        int32_t record_count = (int32_t)(push_array(scratch, Textual_Highlight, 0) - records);
        push_array(scratch, Textual_Highlight, 1);
        
        if (record_count > 0){
            sort_textual_highlights(records, 0, record_count);
            Temp_Memory marker_temp = begin_temp_memory(scratch);
            Marker *markers = push_array(scratch, Marker, 0);
            int_color current_text_color = records[0].text_color;
            int_color current_background_color = records[0].background_color;
            {
                Marker *marker = push_array(scratch, Marker, 2);
                marker[0].pos = records[0].first;
                marker[1].pos = records[0].one_past_last;
            }
            for (int32_t i = 1; i <= record_count; i += 1){
                bool32 do_emit = ((i == record_count) ||
                                  (records[i].text_color != current_text_color) ||
                                  (records[i].background_color != current_background_color));
                if (do_emit){
                    int32_t marker_count = (int32_t)(push_array(scratch, Marker, 0) - markers);
                    Managed_Object o = alloc_buffer_markers_on_buffer(app, buffer.buffer_id, marker_count, &render_scope);
                    managed_object_store_data(app, o, 0, marker_count, markers);
                    Marker_Visual v = create_marker_visual(app, o);
                    marker_visual_set_effect(app, v,
                                             VisualType_CharacterHighlightRanges,
                                             current_background_color, current_text_color, 0);
                    marker_visual_set_priority(app, v, VisualPriority_Lowest);
                    end_temp_memory(marker_temp);
                    current_text_color = records[i].text_color;
                    current_background_color = records[i].background_color;
                }
                
                Marker *marker = push_array(scratch, Marker, 2);
                marker[0].pos = records[i].first;
                marker[1].pos = records[i].one_past_last;
            }
        }
        
        end_temp_memory(temp);
    }
    
    // Rendering Cursors, Marks and Highlights
    Managed_Object cursor_and_mark = alloc_buffer_markers_on_buffer(app, buffer.buffer_id, 2, &render_scope);
    {
        Marker cm_markers[2] = {};
        cm_markers[0].pos = view.cursor.pos;
        cm_markers[1].pos = view.mark.pos;
        managed_object_store_data(app, cursor_and_mark, 0, 2, cm_markers);
        
        bool32 cursor_is_hidden_in_this_view = (cursor_is_hidden && is_active_view);
        
        if (!cursor_is_hidden_in_this_view) {
            int_color cursor_color    = SymbolicColorFromPalette(Stag_Cursor);
            int_color highlight_color = SymbolicColorFromPalette(Stag_Highlight);
            int_color mark_color      = SymbolicColorFromPalette(Stag_Mark);
            int_color text_color    = is_active_view?
                SymbolicColorFromPalette(Stag_At_Cursor):SymbolicColorFromPalette(Stag_Default);
            
            Marker_Visual_Take_Rule take_rule = {};
            take_rule.first_index = 0;
            take_rule.take_count_per_step = 1;
            take_rule.step_stride_in_marker_count = 1;
            take_rule.maximum_number_of_markers = 1;
            
            // Cursor
            Marker_Visual visual = create_marker_visual(app, cursor_and_mark);
            Marker_Visual_Type type = is_active_view ? VisualType_CharacterBlocks : VisualType_CharacterWireFrames;
            marker_visual_set_effect(app, visual, type, cursor_color, text_color, 0);
            marker_visual_set_take_rule(app, visual, take_rule);
            marker_visual_set_priority(app, visual, VisualPriority_Highest);
            
            
            // Selection
            if (view.cursor.pos != view.mark.pos){
                visual = create_marker_visual(app, cursor_and_mark);
                marker_visual_set_effect(app, visual,
                                         VisualType_CharacterHighlightRanges,
                                         highlight_color,
                                         SymbolicColorFromPalette(Stag_At_Highlight),
                                         0);
                take_rule.maximum_number_of_markers = 2;
                marker_visual_set_take_rule(app, visual, take_rule);
                marker_visual_set_priority(app, visual, VisualPriority_Highest);
            }
            
            // Marker
            visual = create_marker_visual(app, cursor_and_mark);
            marker_visual_set_effect(app, visual,VisualType_CharacterWireFrames, mark_color, 0, 0);
            take_rule.first_index = 1;
            marker_visual_set_take_rule(app, visual, take_rule);
            marker_visual_set_priority(app, visual, VisualPriority_Highest);
            
        }
    }
    
    // Line highlight setup
    {
        if (highlight_line_at_cursor && is_active_view){
            Theme_Color color = {};
            color.tag = Stag_Highlight_Cursor_Line;
            get_theme_colors(app, &color, 1);
            uint32_t line_color = color.color;
            Marker_Visual visual = create_marker_visual(app, cursor_and_mark);
            marker_visual_set_effect(app, visual, VisualType_LineHighlights,
                                     line_color, 0, 0);
            Marker_Visual_Take_Rule take_rule = {};
            take_rule.first_index = 0;
            take_rule.take_count_per_step = 1;
            take_rule.step_stride_in_marker_count = 1;
            take_rule.maximum_number_of_markers = 1;
            marker_visual_set_take_rule(app, visual, take_rule);
            marker_visual_set_priority(app, visual, VisualPriority_Highest);
        }
    }
    
    // Token highlight setup
    {
        bool32 do_token_highlight = false;
        if (do_token_highlight){
            Theme_Color color = {};
            color.tag = Stag_Cursor;
            get_theme_colors(app, &color, 1);
            uint32_t token_color = (0x50 << 24) | (color.color&0xFFFFFF);
            
            uint32_t token_flags = BoundaryToken|BoundaryWhitespace;
            int32_t pos0 = view.cursor.pos;
            int32_t pos1 = buffer_boundary_seek(app, &buffer, pos0, DirLeft , token_flags);
            int32_t pos2 = buffer_boundary_seek(app, &buffer, pos1, DirRight, token_flags);
            
            Managed_Object token_highlight = alloc_buffer_markers_on_buffer(app, buffer.buffer_id, 2, &render_scope);
            Marker range_markers[2] = {};
            range_markers[0].pos = pos1;
            range_markers[1].pos = pos2;
            managed_object_store_data(app, token_highlight, 0, 2, range_markers);
            Marker_Visual visual = create_marker_visual(app, token_highlight);
            marker_visual_set_effect(app, visual,
                                     VisualType_CharacterHighlightRanges,
                                     token_color, SymbolicColorFromPalette(Stag_At_Highlight), 0);
        }
    }
    
    // Matching enclosure highlight setup
    {
        static const int32_t color_count = 4;
        if (do_matching_enclosure_highlight){
            Theme_Color theme_colors[color_count];
            int_color colors[color_count];
            for (int32_t i = 0; i < 4; i += 1){
                theme_colors[i].tag = Stag_Back_Cycle_1 + i;
            }
            get_theme_colors(app, theme_colors, color_count);
            for (int32_t i = 0; i < 4; i += 1){
                colors[i] = theme_colors[i].color;
            }
            mark_enclosures(app, scratch, render_scope,
                            &buffer, view.cursor.pos, FindScope_Brace,
                            VisualType_LineHighlightRanges,
                            colors, 0, color_count);
        }
        if (do_matching_paren_highlight){
            Theme_Color theme_colors[color_count];
            int_color colors[color_count];
            for (int32_t i = 0; i < 4; i += 1){
                theme_colors[i].tag = Stag_Text_Cycle_1 + i;
            }
            get_theme_colors(app, theme_colors, color_count);
            for (int32_t i = 0; i < 4; i += 1){
                colors[i] = theme_colors[i].color;
            }
            int32_t pos = view.cursor.pos;
            if (buffer_get_char(app, &buffer, pos) == '('){
                pos += 1;
            }
            else if (pos > 0){
                if (buffer_get_char(app, &buffer, pos - 1) == ')'){
                    pos -= 1;
                }
            }
            mark_enclosures(app, scratch, render_scope,
                            &buffer, pos, FindScope_Paren,
                            VisualType_CharacterBlocks,
                            0, colors, color_count);
        }
    }
    
    do_core_render(app);
    
    managed_scope_clear_self_all_dependent_scopes(app, render_scope);
}



internal
procedure set_hooks (Bind_Helper *context) -> void {
    set_hook(context, hook_exit, default_exit);
    set_hook(context, hook_view_size_change, default_view_adjust);
    
    set_start_hook(context, default_start);
    set_open_file_hook(context, on_open_file);
    set_new_file_hook(context, default_new_file);
    set_save_file_hook(context, default_file_save);
    
    set_end_file_hook(context, end_file_close_jump_list);
    
    set_command_caller(context, default_command_caller);
    set_render_caller(context, on_render);
    set_input_filter(context, default_suppress_mouse_filter);
    set_scroll_rule(context, smooth_scroll_rule);
    set_buffer_name_resolver(context, default_buffer_name_resolution);
}





// # MAIN ENTRY

extern "C" 
int32_t get_bindings(void *data, int32_t size) {
    Bind_Helper context_ = begin_bind_helper(data, size);
    Bind_Helper *context = &context_;
    {
        set_hooks(context);
        bind_keys(context);
    }
    int32_t result = end_bind_helper(context);
    return(result);
}





#endif //FCODER_ROSORIO
