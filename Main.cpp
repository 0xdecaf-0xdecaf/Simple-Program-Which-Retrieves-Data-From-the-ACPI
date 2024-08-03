#include <windows.h>
#include <iostream>
#include <vector>

void GetAcpiTable(const char* signature) {
    UINT table_size = GetSystemFirmwareTable('ACPI', *(reinterpret_cast<const UINT*>(signature)), NULL, 0);
    if (table_size == 0) { // this should never happen
        return;
    }

    std::vector<BYTE> table_buffer(table_size);

    UINT result = GetSystemFirmwareTable('ACPI', *(reinterpret_cast<const UINT*>(signature)), table_buffer.data(), table_size);
    if (result != table_size) { // this shold never happen either
        std::cerr << "can't retrieve acpi table" << std::endl;
        return;
    }

    std::cout << "retrieved acpi table: " << signature << std::endl;
    for (size_t i = 0; i < table_buffer.size(); ++i) {
        printf("%02X ", table_buffer[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
}

int main(int argc, char** argv) {
    GetAcpiTable("DSDT");
}
