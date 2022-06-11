// Wipe Disk
// Copyright (c) 2022 Barend Gehrels, Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the MIT License
// https://raw.githubusercontent.com/barendgehrels/wipedisk/main/LICENSE

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>

int update_status(double fraction, int previous_percentage = -1)
{
    const int percentage = int(0.5 + 100.0 * fraction);
    if (percentage != previous_percentage)
    {
        std::cout << "\b\b\b\b" << std::setw(3) << percentage << "%" << std::flush;
    }
    return percentage;
}

void wipe(const std::string& name, std::size_t kilobytes) {
    FILE *ptr = fopen(name.c_str(), "wb");
    if (ptr == NULL)
    {
        std::cout << "Cannot open " << name << std::endl;
        return;
    }
    std::cout << "Writing file with zeros " << name << "..." << std::endl;
    std::cout << "State xxx%";
    int p = update_status(0.0);

    bool unfinished = false;
    unsigned char buffer[1024] = {0};
    for (std::size_t i = 0; i < kilobytes; i++)
    {
        const std::size_t written = fwrite(buffer, sizeof(buffer), 1, ptr); 
        if (written != 1)
        {
            std::cout << std::endl << "Cannot finish writing into " << name << std::endl;
            unfinished = true;
            break;
        }
        p = update_status(1.0 * i / kilobytes, p);
    }
    fclose(ptr);

    if (! unfinished)
    {
        update_status(1.0);
    }
    std::cout << std::endl;
}

const std::string option_keep = "--keep";

int usage()
{
    std::cout << "Usage: wipedisk [filename] [size in KB] {" << option_keep << "}" << std::endl;
    return 1;
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        return usage();
    }
    const char* filename = argv[1];
    const int kilobytes = atol(argv[2]);
    if (kilobytes <= 0)
    {
        return usage();
    }
    bool error_in_arguments = false;
    bool keep = false;
    for (int i = 3; i < argc; i++)
    {
        if (option_keep == argv[i]) 
        {
            keep = true;
        }
        else
        {
            error_in_arguments = true;
        }
    }
    if (error_in_arguments)
    {
        std::cout << argv[3] << std::endl;
        return usage();
    }

    wipe(filename, kilobytes);

    // Remove the written file afterwards (by default, but optional)
    if (! keep)
    {
        std::cout << "Erasing just written file " << filename << std::endl;
        std::remove(filename);
    }
    else
    {
        std::cout << "Keeping file " << filename << " -> it is not erased!" << std::endl;
    }
    return 0;
}
