
#include "windows.h"

#include "stdio.h"

#define COMMAND_SIZE (512)

#ifndef internal
#define internal static
#endif

#ifndef procedure
#define procedure auto
#endif


/// We make things go boom when condition is true
internal procedure
crash_if(bool condition) -> bool
{
    if(condition) {
        *(int*)0 = 0xDEADBEEF;
    }
    return condition;
}


/// Reports a windows error to the user
internal procedure
report_error(int error_code) -> void
{
    (void) error_code; // @@TODO(ruben): Deal with this somehow
}


/// Executes a windows command
internal procedure
execute_command(const char* command) -> bool
{
    STARTUPINFO startup_info = {0};
    startup_info.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION process_information = {0};
    int result = CreateProcess(
        nullptr, 
        (LPSTR)command,
        nullptr,
        nullptr,
        false,
        CREATE_NO_WINDOW,
        nullptr,
        nullptr,
        &startup_info,
        &process_information
        );
    
    if (!result) {
		int error = GetLastError();
        report_error(error);
		return false;
	}
	
    WaitForSingleObject(process_information.hProcess, INFINITE);
    CloseHandle(process_information.hProcess);
    CloseHandle(process_information.hThread);
    
    return true;
}


/// Checks if the file provided is setup as readonly
/// in the file system.
internal procedure
is_file_readonly(const char* filename) -> bool
{
    DWORD attributes = GetFileAttributes(filename);
    if (attributes != INVALID_FILE_ATTRIBUTES) {
        return attributes & FILE_ATTRIBUTE_READONLY;
    }
    return false;
}


/// Appends the string provided to the string
internal procedure
append_string(char** ptr, const char* to_append) -> char*
{
    int to_append_length = (int)strlen(to_append);
    memcpy(*ptr, to_append, to_append_length);
    *ptr += to_append_length;
    return *ptr;
}


/// Appends the integer provided to the string
internal procedure
append_int(char** ptr, int to_append) -> char*
{
    char to_append_str[32] = {0};
    itoa(to_append, to_append_str, 10);
    return append_string(ptr, to_append_str);
}


/// Appends a space to the given char* and moves it forward
internal procedure
append_space(char** ptr) -> char*
{
    const char* space = " ";
    memcpy(*ptr, space, 1);
    *ptr += 1;
    return *ptr;
}


/// Appends a null character to the given char* and moves it forward
internal procedure 
null_terminate(char ** ptr) -> char* 
{
    const char* null_char = "\0";
    memcpy(*ptr, null_char, 1);
    *ptr += 1;
    return *ptr;
}


/// Opens a particular file in Microsoft's Visual Studio with the option to 
/// speficy a specific row and column to open on
procedure
plattform_open_in_msvs(const char* filename, int row = 0, int column = 0) -> bool
{
    if (!filename) return false;
    
    // @@NOTE(ruben): Replace cscript with cmd /K to see the result in the terminal
    // if this command isnt' working and you want to see the result of why
    const char* incomplete_command = "cscript .\\4coder_ruben\\ruben_scripts\\open-in-msvs.vbs";
    
    char command[COMMAND_SIZE];
    char* command_ptr = command;
    
    append_string(&command_ptr, incomplete_command); // Command without parameters
    append_space(&command_ptr);
    append_string(&command_ptr, filename); // Filename
    append_space(&command_ptr);
	append_int(&command_ptr, row); // Row
    append_space(&command_ptr);
	append_int(&command_ptr, column); // Column
    null_terminate(&command_ptr);
    
    // Launch our process to open the file :)
	return execute_command(command);
}


/// Executes a "p4 edit" on the file provided
procedure
plattform_p4_edit(const char* filename) -> bool
{
    if (!filename) return false;
    
    // @@NOTE(ruben): Replace cscript with cmd /K to see the result in the terminal
    // if this command isnt' working and you want to see the result of why
    const char* incomplete_command = "p4 edit";
    
    char command[COMMAND_SIZE];
    char* command_ptr = command;
    
    append_string(&command_ptr, incomplete_command); // Command without parameters
    append_space(&command_ptr);
    append_string(&command_ptr, filename); // Filename
    null_terminate(&command_ptr);
    
    // Launch our process to open the file :)
	return execute_command(command);
}
