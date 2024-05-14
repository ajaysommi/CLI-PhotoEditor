#include <iostream>
#include <vector>
#ifndef PROJECT_2_PART_2_FILE_H
#define PROJECT_2_PART_2_FILE_H

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin = 0;
    short colorMapLength = 0;
    char colorMapDepth = 0;
    short xOrigin = 0;
    short yOrigin = 0;
    short width;
    short height;
    char bitsPerPixel = 24;
    char imageDescriptor;
    bool file_open = false;

    std::vector<unsigned char> pixel_vect;
};

Header read_from_file(const std::string &file_name);

Header multiply(const std::string &top_layer, const std::string &bottom_layer);
Header multiply(Header &passed_head, const std::string &bottom_layer);

Header screen(std::string top_layer, std::string bottom_layer);
Header screen(const std::string &top_layer, Header &passed_header);

Header subtract(const std::string &top_layer, const std::string &bottom_layer);
Header subtract(Header &passed_head, const std::string &bottom_layer);

Header addition(std::string top_layer, std::string bottom_layer);

Header overlay(const std::string &top_layer, const std::string &bottom_layer);
Header overlay(Header &passed_head, const std::string &bottom_layer);

Header modifyadd(Header &passed_header, int val, int color_val);

Header modifyscale(Header &passed_header, int val, int color_val);

Header modifymultiply(const std::string &image);

Header task_8_function(const std::string &image, int starting_index);
Header task_8_function(Header &passed_header, int starting_index);

Header combine_files(const std::string &blue_channel, const std::string &green_channel, const std::string &red_channel);
Header combine_files(const std::string &blue_channel, const std::string &green_channel, Header &red_channel);

Header rotate(const std::string &image);
Header rotate(Header &passed_header);

void write_to_file(Header &passed_header, const std::string &file_name);

bool valid_filename(const std::string &filename);


#endif //PROJECT_2_PART_2_FILE_H
