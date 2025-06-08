#include "alg.h"
#include "time.h"
#include <algorithm>


int main(int argc, char** argv) {
    srand(time(NULL));

    if (argc < 2) {
        std::cerr << "Filepath is expected" << std::endl;
        return 1;
    }
    std::string input_file = argv[1];

    std::string output_file;
    enum {
        JPG = 0,
        PNG,
    } save_format = JPG;

    if (argc >= 3) {
        output_file = argv[2];
        size_t pos = output_file.size() - 1 - std::string(output_file.rbegin(), output_file.rend()).find('.');
        std::string format = output_file.substr(pos+1);
        
        if (format == "jpg") save_format = JPG;
        else if (format == "png") save_format = PNG;
        else {
            std::cerr << "Unknown file format: " << format << std::endl;
            return 1;
        }

    } else {
        size_t pos = input_file.size() - 1 - std::string(input_file.rbegin(), input_file.rend()).find('.');
        std::string format = input_file.substr(pos+1);
        output_file = input_file.substr(0, pos) + "_output" + "." + format;
        
        if (format == "jpg") save_format = JPG;
        else if (format == "png") save_format = PNG;
        else {
            std::cerr << "Unknown file format: " << format << std::endl;
            return 1;
        }
    }

    std::cout << "Input:  " << input_file << std::endl;
    std::cout << "Output: " << output_file << std::endl;
    std::cout << "Format: " << save_format << std::endl;


    Image img(input_file, 3);
    std::cout << "Image loaded: " << img.width << " x " << img.height << " x " << img.channels << " channels" << std::endl;

    Image mod = algorythm(img);
    
    switch (save_format) {
        case JPG:
            mod.save_jpg(output_file);
            break;

        case PNG:
            mod.save_png(output_file);
            break;
            
        default:
            std::cerr << "Unknown saving format: " << save_format << std::endl;
            return 1; 
            break;
    }
    std::cout << "Output saved: " << mod.width << " x " << mod.height << " x " << mod.channels << " channels" << std::endl;


    return 0;
}