#include <processenv.h>
#include <windows.h>

#include <iostream>
#include <string>

int main() {
  while (true) {
    std::string command;
    std::cout << "> ";
    std::getline(std::cin, command);

    if (command == "exit") {
      break;
    }

    // Creating process structures
    STARTUPINFOA startup_info;
    PROCESS_INFORMATION process_info;
    ZeroMemory(&startup_info, sizeof(startup_info));
    startup_info.cb = sizeof(startup_info);
    ZeroMemory(&process_info, sizeof(process_info));

    BOOL success =
        CreateProcessA(NULL, const_cast<char*>(command.c_str()), NULL, NULL,
                       FALSE, 0, NULL, NULL, &startup_info, &process_info);
    if (!success) {
      std::cout << "Command "
                << "'" << command << "'"
                << " not found" << std::endl;
      continue;
    }

    // Wait for process to finish
    WaitForSingleObject(process_info.hProcess, INFINITE);

    // CLose handles
    CloseHandle(process_info.hProcess);
    CloseHandle(process_info.hThread);
  }
  return 0;
}
