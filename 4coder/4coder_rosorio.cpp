#ifndef FCODER_ROSORIO
#define FCODER_ROSORIO

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



// # MAIN ENTRY

extern "C" 
int32_t get_bindings(void *data, int32_t size) {
    Bind_Helper context_ = begin_bind_helper(data, size);
    Bind_Helper *context = &context_;
    {
        set_all_default_hooks(context);
        bind_keys(context);
    }
    int32_t result = end_bind_helper(context);
    return(result);
}



#endif //FCODER_ROSORIO
