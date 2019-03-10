
#include "windows.h"

#include "stdio.h"


/// We make things go boom when condition is true
bool crash_if(bool condition) {
    if(condition) {
        *(int*)0 = 0xDEADBEEF;
    }
    return condition;
}


void report_error(int error_code) {
    (void) error_code; // @@TODO(ruben): Deal with this somehow
}

/// Checks if the file provided is setup as readonly
/// in the file system.
bool is_file_readonly(const char* filename) {
    DWORD attributes = GetFileAttributes(filename);
    if (attributes != INVALID_FILE_ATTRIBUTES) {
        return attributes & FILE_ATTRIBUTE_READONLY;
    }
    return false;
}


/// Opens a particular file in Microsoft's Visual Studio with the option to 
/// speficy a specific row and column to open on
bool plattform_open_in_msvs(const char* filename, int row = 0, int column = 0) {
    
    if (!filename) return false;
    
    int filename_length = (int)strlen(filename);
    
    // @@NOTE(ruben): Replace cscript with cmd /K to see the result in the terminal
    // if this command isnt' working and you want to see the result of why
    const char* path = "cscript .\\4coder_ruben\\ruben_scripts\\open-in-msvs.vbs";
    int path_length = (int)strlen(path);
    
    char command[512];
    char* command_ptr = command;
    
    
    // Copy the path to the script
    memcpy(command_ptr, path, path_length);
    command_ptr += path_length;
    
    // Append space
    const char* space = " ";
    memcpy(command_ptr, space, 1);
    command_ptr += 1;
    
    // Append name of the file to open
    memcpy(command_ptr, filename, filename_length);
    command_ptr += filename_length;
    
    // Append space
    memcpy(command_ptr, space, 1);
    command_ptr += 1;
    
	// Append row
	char row_str[32];
    itoa(row, row_str, 10);
    int row_length = (int)strlen(row_str);
	memcpy(command_ptr, row_str, row_length);
	command_ptr += row_length;
    
    // Append space
    memcpy(command_ptr, space, 1);
    command_ptr += 1;
    
	// Append col
	char col_str[32];
    itoa(column, col_str, 10);
    int col_length = (int)strlen(col_str);
	memcpy(command_ptr, col_str, col_length);
	command_ptr += col_length;
    
    // Null-terminate
    const char* null_terminator = "\0";
    memcpy(command_ptr, null_terminator, 1);
    command_ptr += 1;
    
    
    
    // Launch our process to open the file :)
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

