void deal_with_custom_command_error(const char * message) {
    //@@TODO(ruben): Deal with this errors somehow
}

CUSTOM_COMMAND_SIG(open_in_msvs)
CUSTOM_DOC("Opens the file in the current active fuffer in Microsoft's Visual Studio")
{
    View_Summary view = get_active_view(app, AccessAll);
    Buffer_Summary buffer = get_buffer(app, view.buffer_id, AccessAll);
    Assert(buffer.exists);
    
    if (!plattform_open_in_msvs(buffer.file_name, view.cursor.line, view.cursor.character - 1)) {
        deal_with_custom_command_error("We couldn't open the file provided in Visual Studio");
    }
}

CUSTOM_COMMAND_SIG(p4_edit)
CUSTOM_DOC("Checks out the file in the current active buffer in Perforce")
{
    View_Summary view = get_active_view(app, AccessAll);
    Buffer_Summary buffer = get_buffer(app, view.buffer_id, AccessAll);
    Assert(buffer.exists);
    
    bool success = plattform_p4_edit(buffer.file_name);
    
    if(!success) {
        deal_with_custom_command_error("We couldn't execute a \"p4 edit\" on the file provided");
        return;
    }
    
    // Check if file is no longer readonly after launching the command
    // and allowing edit if it's not
    int32_t buffer_was_readonly;
    buffer_get_setting(app, &buffer, BufferSetting_ReadOnly, &buffer_was_readonly);
    if(buffer_was_readonly && !is_file_readonly(buffer.file_name)){
        buffer_set_setting(app, &buffer, BufferSetting_ReadOnly, false);
    }
}