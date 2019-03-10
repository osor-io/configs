CUSTOM_COMMAND_SIG(open_in_msvs)
CUSTOM_DOC("Opens the file in the current fuffer in Microsoft's Visual Studio")
{
    View_Summary view = get_active_view(app, AccessAll);
    Buffer_Summary buffer = get_buffer(app, view.buffer_id, AccessAll);
    Assert(buffer.exists);
    
    plattform_open_in_msvs(buffer.file_name, view.cursor.line, view.cursor.character - 1);
}