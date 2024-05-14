#include "File.h"
#include <iostream>
#include <fstream>

Header read_from_file(const std::string &file_name) {
    //creates new instance to be returned at end of function
    Header head_instance;
    std::fstream file(file_name, std::ios::in|std::ios::binary);
    if (file) {
        head_instance.file_open = true;
    }

    //manually pushing header attributes into vector
    file.read(&head_instance.idLength, 1);
    file.read(reinterpret_cast<char*> (&head_instance.colorMapType), 1);
    file.read(reinterpret_cast<char*> (&head_instance.dataTypeCode), 1);
    file.read(reinterpret_cast<char*> (&head_instance.colorMapOrigin), 2);
    file.read(reinterpret_cast<char*> (&head_instance.colorMapLength), 2);
    file.read(reinterpret_cast<char*> (&head_instance.colorMapDepth), 1);
    file.read(reinterpret_cast<char*> (&head_instance.xOrigin), 2);
    file.read(reinterpret_cast<char*> (&head_instance.yOrigin), 2);
    file.read(reinterpret_cast<char*> (&head_instance.width), 2);
    file.read(reinterpret_cast<char*> (&head_instance.height), 2);
    file.read(reinterpret_cast<char*> (&head_instance.bitsPerPixel), 1);
    file.read(reinterpret_cast<char*> (&head_instance.imageDescriptor), 1);

    //total number of pixels in image
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    unsigned char pixel;
    for (int i = 0; i < total_pixel_count*3; i++) {
        file.read(reinterpret_cast<char*> (&pixel), 1);
        head_instance.pixel_vect.push_back(pixel);
    }

    return head_instance;
}

Header multiply(const std::string &top_layer, const std::string &bottom_layer) {
    //creates new instance to be returned at end of function
    Header head_instance;
    Header top_instance = read_from_file(top_layer);
    Header bottom_instance = read_from_file(bottom_layer);

    head_instance.idLength = bottom_instance.idLength;
    head_instance.colorMapType = bottom_instance.colorMapType;
    head_instance.dataTypeCode = bottom_instance.dataTypeCode;
    head_instance.colorMapOrigin = bottom_instance.colorMapOrigin;
    head_instance.colorMapLength = bottom_instance.colorMapLength;
    head_instance.colorMapDepth = bottom_instance.colorMapDepth;
    head_instance.xOrigin = bottom_instance.xOrigin;
    head_instance.yOrigin = bottom_instance.yOrigin;
    head_instance.width = bottom_instance.width;
    head_instance.height = bottom_instance.height;
    head_instance.bitsPerPixel = bottom_instance.bitsPerPixel;
    head_instance.imageDescriptor = bottom_instance.imageDescriptor;

    //total number of pixels
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    for (int j = 0; j < total_pixel_count*3; j++) {
        float new_pixel = ((((float)top_instance.pixel_vect[j]/255 * (float)bottom_instance.pixel_vect[j]/255)*255) + 0.5f);
        head_instance.pixel_vect.push_back((char)new_pixel);
    }

    return head_instance;
}

Header multiply(Header &passed_head, const std::string &bottom_layer) {
    //creates new instance to be returned at end of function
    Header head_instance;
    Header bottom_instance = read_from_file(bottom_layer);

    head_instance.idLength = bottom_instance.idLength;
    head_instance.colorMapType = bottom_instance.colorMapType;
    head_instance.dataTypeCode = bottom_instance.dataTypeCode;
    head_instance.colorMapOrigin = bottom_instance.colorMapOrigin;
    head_instance.colorMapLength = bottom_instance.colorMapLength;
    head_instance.colorMapDepth = bottom_instance.colorMapDepth;
    head_instance.xOrigin = bottom_instance.xOrigin;
    head_instance.yOrigin = bottom_instance.yOrigin;
    head_instance.width = bottom_instance.width;
    head_instance.height = bottom_instance.height;
    head_instance.bitsPerPixel = bottom_instance.bitsPerPixel;
    head_instance.imageDescriptor = bottom_instance.imageDescriptor;

    //total number of pixels
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    for (int j = 0; j < total_pixel_count*3; j++) {
        float new_pixel = ((((float)passed_head.pixel_vect[j]/255 * (float)bottom_instance.pixel_vect[j]/255)*255) + 0.5f);
        head_instance.pixel_vect.push_back((char)new_pixel);
    }

    return head_instance;
}

Header screen(const std::string &top_layer, Header &passed_header) {
    //creates new instance to be returned at end of function
    Header head_instance;
    Header top_instance = read_from_file(top_layer);

    head_instance.idLength = passed_header.idLength;
    head_instance.colorMapType = passed_header.colorMapType;
    head_instance.dataTypeCode = passed_header.dataTypeCode;
    head_instance.colorMapOrigin = passed_header.colorMapOrigin;
    head_instance.colorMapLength = passed_header.colorMapLength;
    head_instance.colorMapDepth = passed_header.colorMapDepth;
    head_instance.xOrigin = passed_header.xOrigin;
    head_instance.yOrigin = passed_header.yOrigin;
    head_instance.width = passed_header.width;
    head_instance.height = passed_header.height;
    head_instance.bitsPerPixel = passed_header.bitsPerPixel;
    head_instance.imageDescriptor = passed_header.imageDescriptor;

    //total number of pixels
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    for (int j = 0; j < total_pixel_count*3; j++) {
        float new_pixel = ((((1 - ((1 - (float)top_instance.pixel_vect[j]/255) * (1 - (float)passed_header.pixel_vect[j]/255)))*255) + 0.5f));
        head_instance.pixel_vect.push_back((char)new_pixel);
    }

    return head_instance;
}

Header subtract(const std::string &top_layer, const std::string &bottom_layer) {
    //creates new instance to be returned at end of function
    Header head_instance;
    Header top_instance = read_from_file(top_layer);
    Header bottom_instance = read_from_file(bottom_layer);

    head_instance.idLength = bottom_instance.idLength;
    head_instance.colorMapType = bottom_instance.colorMapType;
    head_instance.dataTypeCode = bottom_instance.dataTypeCode;
    head_instance.colorMapOrigin = bottom_instance.colorMapOrigin;
    head_instance.colorMapLength = bottom_instance.colorMapLength;
    head_instance.colorMapDepth = bottom_instance.colorMapDepth;
    head_instance.xOrigin = bottom_instance.xOrigin;
    head_instance.yOrigin = bottom_instance.yOrigin;
    head_instance.width = bottom_instance.width;
    head_instance.height = bottom_instance.height;
    head_instance.bitsPerPixel = bottom_instance.bitsPerPixel;
    head_instance.imageDescriptor = bottom_instance.imageDescriptor;

    //total number of pixels
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    for (int j = 0; j < total_pixel_count*3; j++) {
        int new_pixel = top_instance.pixel_vect[j]-bottom_instance.pixel_vect[j];
        if ((int)new_pixel > 255) {
            head_instance.pixel_vect.push_back((unsigned char)255);
        }
        else if ((int)new_pixel < 0) {
            head_instance.pixel_vect.push_back((unsigned char)0);
        }
        else {
            head_instance.pixel_vect.push_back(new_pixel);
        }
    }

    return head_instance;
}

Header subtract(Header &passed_head, const std::string &bottom_layer) {
    //creates new instance to be returned at end of function
    Header head_instance;
    Header bottom_instance = read_from_file(bottom_layer);

    head_instance.idLength = bottom_instance.idLength;
    head_instance.colorMapType = bottom_instance.colorMapType;
    head_instance.dataTypeCode = bottom_instance.dataTypeCode;
    head_instance.colorMapOrigin = bottom_instance.colorMapOrigin;
    head_instance.colorMapLength = bottom_instance.colorMapLength;
    head_instance.colorMapDepth = bottom_instance.colorMapDepth;
    head_instance.xOrigin = bottom_instance.xOrigin;
    head_instance.yOrigin = bottom_instance.yOrigin;
    head_instance.width = bottom_instance.width;
    head_instance.height = bottom_instance.height;
    head_instance.bitsPerPixel = bottom_instance.bitsPerPixel;
    head_instance.imageDescriptor = bottom_instance.imageDescriptor;

    //total number of pixels
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    for (int j = 0; j < total_pixel_count*3; j++) {
        int new_pixel = passed_head.pixel_vect[j]-bottom_instance.pixel_vect[j];
        if ((int)new_pixel > 255) {
            head_instance.pixel_vect.push_back((unsigned char)255);
        }
        else if ((int)new_pixel < 0) {
            head_instance.pixel_vect.push_back((unsigned char)0);
        }
        else {
            head_instance.pixel_vect.push_back(new_pixel);
        }
    }

    return head_instance;
}

Header addition(const std::string &top_layer, const std::string &bottom_layer) {
    //creates new instance to be returned at end of function
    Header head_instance;
    Header top_instance = read_from_file(top_layer);
    Header bottom_instance = read_from_file(bottom_layer);

    head_instance.idLength = bottom_instance.idLength;
    head_instance.colorMapType = bottom_instance.colorMapType;
    head_instance.dataTypeCode = bottom_instance.dataTypeCode;
    head_instance.colorMapOrigin = bottom_instance.colorMapOrigin;
    head_instance.colorMapLength = bottom_instance.colorMapLength;
    head_instance.colorMapDepth = bottom_instance.colorMapDepth;
    head_instance.xOrigin = bottom_instance.xOrigin;
    head_instance.yOrigin = bottom_instance.yOrigin;
    head_instance.width = bottom_instance.width;
    head_instance.height = bottom_instance.height;
    head_instance.bitsPerPixel = bottom_instance.bitsPerPixel;
    head_instance.imageDescriptor = bottom_instance.imageDescriptor;

    //total number of pixels
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    for (int j = 0; j < total_pixel_count*3; j++) {
        int new_pixel = top_instance.pixel_vect[j]+bottom_instance.pixel_vect[j];
        if ((int)new_pixel > 255) {
            head_instance.pixel_vect.push_back((unsigned char)255);
        }
        else if ((int)new_pixel < 0) {
            head_instance.pixel_vect.push_back((unsigned char)0);
        }
        else {
            head_instance.pixel_vect.push_back(new_pixel);
        }
    }

    return head_instance;
}

Header overlay(const std::string &top_layer, const std::string &bottom_layer) {
    //creates new instance to be returned at end of function
    Header head_instance;
    Header top_instance = read_from_file(top_layer);
    Header bottom_instance = read_from_file(bottom_layer);

    head_instance.idLength = bottom_instance.idLength;
    head_instance.colorMapType = bottom_instance.colorMapType;
    head_instance.dataTypeCode = bottom_instance.dataTypeCode;
    head_instance.colorMapOrigin = bottom_instance.colorMapOrigin;
    head_instance.colorMapLength = bottom_instance.colorMapLength;
    head_instance.colorMapDepth = bottom_instance.colorMapDepth;
    head_instance.xOrigin = bottom_instance.xOrigin;
    head_instance.yOrigin = bottom_instance.yOrigin;
    head_instance.width = bottom_instance.width;
    head_instance.height = bottom_instance.height;
    head_instance.bitsPerPixel = bottom_instance.bitsPerPixel;
    head_instance.imageDescriptor = bottom_instance.imageDescriptor;

    //total number of pixels
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    for (int i = 0; i < total_pixel_count*3; i++) {
        float combined_normal = (((float)bottom_instance.pixel_vect[i]/255));
        float final_pixel;
        if (combined_normal <= 0.5) {
            final_pixel = ((((2 * ((float)top_instance.pixel_vect[i]/255) * ((float)bottom_instance.pixel_vect[i]/255))*255) + 0.5f));
        }
        else if (combined_normal > 0.5) {
            final_pixel = (((1 - (2 * (1 - (float)top_instance.pixel_vect[i]/255) * (1 - (float)bottom_instance.pixel_vect[i]/255))) * 255) + 0.5f);
        }
        head_instance.pixel_vect.push_back((char)final_pixel);
    }

    return head_instance;
}

Header overlay(Header &passed_head, const std::string &bottom_layer) {
    //creates new instance to be returned at end of function
    Header head_instance;
    Header bottom_instance = read_from_file(bottom_layer);

    head_instance.idLength = bottom_instance.idLength;
    head_instance.colorMapType = bottom_instance.colorMapType;
    head_instance.dataTypeCode = bottom_instance.dataTypeCode;
    head_instance.colorMapOrigin = bottom_instance.colorMapOrigin;
    head_instance.colorMapLength = bottom_instance.colorMapLength;
    head_instance.colorMapDepth = bottom_instance.colorMapDepth;
    head_instance.xOrigin = bottom_instance.xOrigin;
    head_instance.yOrigin = bottom_instance.yOrigin;
    head_instance.width = bottom_instance.width;
    head_instance.height = bottom_instance.height;
    head_instance.bitsPerPixel = bottom_instance.bitsPerPixel;
    head_instance.imageDescriptor = bottom_instance.imageDescriptor;

    //total number of pixels
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    for (int i = 0; i < total_pixel_count*3; i++) {
        float combined_normal = (((float)bottom_instance.pixel_vect[i]/255));
        float final_pixel;
        if (combined_normal <= 0.5) {
            final_pixel = ((((2 * ((float)passed_head.pixel_vect[i]/255) * ((float)bottom_instance.pixel_vect[i]/255))*255) + 0.5f));
        }
        else if (combined_normal > 0.5) {
            final_pixel = (((1 - (2 * (1 - (float)passed_head.pixel_vect[i]/255) * (1 - (float)bottom_instance.pixel_vect[i]/255))) * 255) + 0.5f);
        }
        head_instance.pixel_vect.push_back((char)final_pixel);
    }

    return head_instance;
}

Header modifyadd(Header &passed_header, int val, int color_val) {
    //creates new instance to be returned at end of function
    Header head_instance;

    head_instance.idLength = passed_header.idLength;
    head_instance.colorMapType = passed_header.colorMapType;
    head_instance.dataTypeCode = passed_header.dataTypeCode;
    head_instance.colorMapOrigin = passed_header.colorMapOrigin;
    head_instance.colorMapLength = passed_header.colorMapLength;
    head_instance.colorMapDepth = passed_header.colorMapDepth;
    head_instance.xOrigin = passed_header.xOrigin;
    head_instance.yOrigin = passed_header.yOrigin;
    head_instance.width = passed_header.width;
    head_instance.height = passed_header.height;
    head_instance.bitsPerPixel = passed_header.bitsPerPixel;
    head_instance.imageDescriptor = passed_header.imageDescriptor;


    //total number of pixels
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    for (int i = 0; i < total_pixel_count*3; i++) {
        head_instance.pixel_vect.push_back(passed_header.pixel_vect[i]);
    }

    for (int j = color_val; j < total_pixel_count*3; j+=3) {
        int end_val = head_instance.pixel_vect[j] + val;
        if (end_val > 255) {
            end_val = 255;
            head_instance.pixel_vect[j] = (unsigned char)end_val;
        }
        if (end_val < 0) {
            end_val = 0;
            head_instance.pixel_vect[j] = (unsigned char)end_val;
        }
        else {
            head_instance.pixel_vect[j] = (unsigned char)end_val;
        }
    }

    return head_instance;
}

Header modifyscale(Header &passed_header, int val, int color_val) {
    //creates new instance to be returned at end of function
    Header head_instance;

    head_instance.idLength = passed_header.idLength;
    head_instance.colorMapType = passed_header.colorMapType;
    head_instance.dataTypeCode = passed_header.dataTypeCode;
    head_instance.colorMapOrigin = passed_header.colorMapOrigin;
    head_instance.colorMapLength = passed_header.colorMapLength;
    head_instance.colorMapDepth = passed_header.colorMapDepth;
    head_instance.xOrigin = passed_header.xOrigin;
    head_instance.yOrigin = passed_header.yOrigin;
    head_instance.width = passed_header.width;
    head_instance.height = passed_header.height;
    head_instance.bitsPerPixel = passed_header.bitsPerPixel;
    head_instance.imageDescriptor = passed_header.imageDescriptor;


    //total number of pixels
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    for (int i = 0; i < total_pixel_count*3; i++) {
        head_instance.pixel_vect.push_back(passed_header.pixel_vect[i]);
    }

    for (int j = color_val; j < total_pixel_count*3; j+=3) {
        int end_val = head_instance.pixel_vect[j] * val;
        if (end_val > 255) {
            end_val = 255;
            head_instance.pixel_vect[j] = (unsigned char)end_val;
        }
        if (end_val < 0) {
            end_val = 0;
            head_instance.pixel_vect[j] = (unsigned char)end_val;
        }
        else {
            head_instance.pixel_vect[j] = (unsigned char)end_val;
        }
    }

    return head_instance;
}

Header modifymultiply(const std::string &image) {
    //creates new instance to be returned at end of function
    Header head_instance;
    Header passed_header = read_from_file(image);

    head_instance.idLength = passed_header.idLength;
    head_instance.colorMapType = passed_header.colorMapType;
    head_instance.dataTypeCode = passed_header.dataTypeCode;
    head_instance.colorMapOrigin = passed_header.colorMapOrigin;
    head_instance.colorMapLength = passed_header.colorMapLength;
    head_instance.colorMapDepth = passed_header.colorMapDepth;
    head_instance.xOrigin = passed_header.xOrigin;
    head_instance.yOrigin = passed_header.yOrigin;
    head_instance.width = passed_header.width;
    head_instance.height = passed_header.height;
    head_instance.bitsPerPixel = passed_header.bitsPerPixel;
    head_instance.imageDescriptor = passed_header.imageDescriptor;


    //total number of pixels
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    for (int i = 0; i < total_pixel_count*3; i++) {
        head_instance.pixel_vect.push_back(passed_header.pixel_vect[i]);
    }

    for (int j = 2; j < total_pixel_count*3; j+=3) {
        int end_val = head_instance.pixel_vect[j] * 4;
        if (end_val > 255) {
            end_val = 255;
            head_instance.pixel_vect[j] = (unsigned char)end_val;
        }
        if (end_val < 0) {
            end_val = 0;
            head_instance.pixel_vect[j] = (unsigned char)end_val;
        }
        else {
            head_instance.pixel_vect[j] = (unsigned char)end_val;
        }
    }

    for (int k = 0; k < total_pixel_count*3; k+=3) {
        int end_val = head_instance.pixel_vect[k] * 0;
        head_instance.pixel_vect[k] = (unsigned char)end_val;
    }

    return head_instance;
}

Header task_8_function(const std::string &image, int starting_index) {
    //creates new instance to be returned at end of function
    Header head_instance;
    Header passed_header = read_from_file(image);

    head_instance.idLength = passed_header.idLength;
    head_instance.colorMapType = passed_header.colorMapType;
    head_instance.dataTypeCode = passed_header.dataTypeCode;
    head_instance.colorMapOrigin = passed_header.colorMapOrigin;
    head_instance.colorMapLength = passed_header.colorMapLength;
    head_instance.colorMapDepth = passed_header.colorMapDepth;
    head_instance.xOrigin = passed_header.xOrigin;
    head_instance.yOrigin = passed_header.yOrigin;
    head_instance.width = passed_header.width;
    head_instance.height = passed_header.height;
    head_instance.bitsPerPixel = passed_header.bitsPerPixel;
    head_instance.imageDescriptor = passed_header.imageDescriptor;

    //total number of pixels
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    //starting_index: 0 = B, 1 = G, 2 = R
    for (int i = starting_index; i < total_pixel_count*3; i+=3) {
        head_instance.pixel_vect.push_back(passed_header.pixel_vect[i]);
        head_instance.pixel_vect.push_back(passed_header.pixel_vect[i]);
        head_instance.pixel_vect.push_back(passed_header.pixel_vect[i]);
    }

    return head_instance;
}

Header task_8_function(Header &passed_header, int starting_index) {
    //creates new instance to be returned at end of function
    Header head_instance;

    head_instance.idLength = passed_header.idLength;
    head_instance.colorMapType = passed_header.colorMapType;
    head_instance.dataTypeCode = passed_header.dataTypeCode;
    head_instance.colorMapOrigin = passed_header.colorMapOrigin;
    head_instance.colorMapLength = passed_header.colorMapLength;
    head_instance.colorMapDepth = passed_header.colorMapDepth;
    head_instance.xOrigin = passed_header.xOrigin;
    head_instance.yOrigin = passed_header.yOrigin;
    head_instance.width = passed_header.width;
    head_instance.height = passed_header.height;
    head_instance.bitsPerPixel = passed_header.bitsPerPixel;
    head_instance.imageDescriptor = passed_header.imageDescriptor;

    //total number of pixels
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    //starting_index: 0 = B, 1 = G, 2 = R
    for (int i = starting_index; i < total_pixel_count*3; i+=3) {
        head_instance.pixel_vect.push_back(passed_header.pixel_vect[i]);
        head_instance.pixel_vect.push_back(passed_header.pixel_vect[i]);
        head_instance.pixel_vect.push_back(passed_header.pixel_vect[i]);
    }

    return head_instance;
}

Header combine_files(const std::string &blue_channel, const std::string &green_channel, const std::string &red_channel) {
    //creates new instance to be returned at end of function
    Header combined_head;
    Header blue_instance = read_from_file(blue_channel);
    Header green_instance = read_from_file(green_channel);
    Header red_instance = read_from_file(red_channel);

    combined_head.idLength = blue_instance.idLength;
    combined_head.colorMapType = blue_instance.colorMapType;
    combined_head.dataTypeCode = blue_instance.dataTypeCode;
    combined_head.colorMapOrigin = blue_instance.colorMapOrigin;
    combined_head.colorMapLength = blue_instance.colorMapLength;
    combined_head.colorMapDepth = blue_instance.colorMapDepth;
    combined_head.xOrigin = blue_instance.xOrigin;
    combined_head.yOrigin = blue_instance.yOrigin;
    combined_head.width = blue_instance.width;
    combined_head.height = blue_instance.height;
    combined_head.bitsPerPixel = blue_instance.bitsPerPixel;
    combined_head.imageDescriptor = blue_instance.imageDescriptor;

    //total number of pixels
    int total_pixel_count = (int)combined_head.width*(int)combined_head.height;

    //pushes every third index of each color instance to final vector
    for (int i = 0; i < total_pixel_count*3; i+=3) {
        combined_head.pixel_vect.push_back(blue_instance.pixel_vect[i]);
        combined_head.pixel_vect.push_back(green_instance.pixel_vect[i]);
        combined_head.pixel_vect.push_back(red_instance.pixel_vect[i]);
    }

    return combined_head;
}

Header combine_files(const std::string &blue_channel, const std::string &green_channel, Header &red_channel) {
    //creates new instance to be returned at end of function
    Header combined_head;
    Header blue_instance = read_from_file(blue_channel);
    Header green_instance = read_from_file(green_channel);

    combined_head.idLength = blue_instance.idLength;
    combined_head.colorMapType = blue_instance.colorMapType;
    combined_head.dataTypeCode = blue_instance.dataTypeCode;
    combined_head.colorMapOrigin = blue_instance.colorMapOrigin;
    combined_head.colorMapLength = blue_instance.colorMapLength;
    combined_head.colorMapDepth = blue_instance.colorMapDepth;
    combined_head.xOrigin = blue_instance.xOrigin;
    combined_head.yOrigin = blue_instance.yOrigin;
    combined_head.width = blue_instance.width;
    combined_head.height = blue_instance.height;
    combined_head.bitsPerPixel = blue_instance.bitsPerPixel;
    combined_head.imageDescriptor = blue_instance.imageDescriptor;

    //total number of pixels
    int total_pixel_count = (int)combined_head.width*(int)combined_head.height;

    //pushes every third index of each color instance to final vector
    for (int i = 0; i < total_pixel_count*3; i+=3) {
        combined_head.pixel_vect.push_back(blue_instance.pixel_vect[i]);
        combined_head.pixel_vect.push_back(green_instance.pixel_vect[i]);
        combined_head.pixel_vect.push_back(red_channel.pixel_vect[i]);
    }

    return combined_head;
}

Header rotate(const std::string &image) {
    //creates new instance to be returned at end of function
    Header head_instance;
    Header passed_header = read_from_file(image);

    head_instance.idLength = passed_header.idLength;
    head_instance.colorMapType = passed_header.colorMapType;
    head_instance.dataTypeCode = passed_header.dataTypeCode;
    head_instance.colorMapOrigin = passed_header.colorMapOrigin;
    head_instance.colorMapLength = passed_header.colorMapLength;
    head_instance.colorMapDepth = passed_header.colorMapDepth;
    head_instance.xOrigin = passed_header.xOrigin;
    head_instance.yOrigin = passed_header.yOrigin;
    head_instance.width = passed_header.width;
    head_instance.height = passed_header.height;
    head_instance.bitsPerPixel = passed_header.bitsPerPixel;
    head_instance.imageDescriptor = passed_header.imageDescriptor;

    //total number of pixels
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    //iterates through passed-in header in reverse and adds to return instance
    for (int i = total_pixel_count*3; i > 0; i-=3) {
        head_instance.pixel_vect.push_back(passed_header.pixel_vect[i-3]);
        head_instance.pixel_vect.push_back(passed_header.pixel_vect[i-2]);
        head_instance.pixel_vect.push_back(passed_header.pixel_vect[i-1]);
    }

    return head_instance;
}

Header rotate(Header &passed_header) {
    //creates new instance to be returned at end of function
    Header head_instance;

    head_instance.idLength = passed_header.idLength;
    head_instance.colorMapType = passed_header.colorMapType;
    head_instance.dataTypeCode = passed_header.dataTypeCode;
    head_instance.colorMapOrigin = passed_header.colorMapOrigin;
    head_instance.colorMapLength = passed_header.colorMapLength;
    head_instance.colorMapDepth = passed_header.colorMapDepth;
    head_instance.xOrigin = passed_header.xOrigin;
    head_instance.yOrigin = passed_header.yOrigin;
    head_instance.width = passed_header.width;
    head_instance.height = passed_header.height;
    head_instance.bitsPerPixel = passed_header.bitsPerPixel;
    head_instance.imageDescriptor = passed_header.imageDescriptor;

    //total number of pixels
    int total_pixel_count = (int)head_instance.width*(int)head_instance.height;

    //iterates through passed-in header in reverse and adds to return instance
    for (int i = total_pixel_count*3; i > 0; i-=3) {
        head_instance.pixel_vect.push_back(passed_header.pixel_vect[i-3]);
        head_instance.pixel_vect.push_back(passed_header.pixel_vect[i-2]);
        head_instance.pixel_vect.push_back(passed_header.pixel_vect[i-1]);
    }

    return head_instance;
}

void write_to_file(Header &passed_header, const std::string& file_name) {
    //creates output file with desired "file_name"
    std::fstream output_file(file_name,std::ios::binary|std::ios::out);

    output_file.write((const char*) &passed_header.idLength, 1);
    output_file.write((const char*) &passed_header.colorMapType, 1);
    output_file.write((const char*) &passed_header.dataTypeCode, 1);
    output_file.write((const char*) &passed_header.colorMapOrigin, 2);
    output_file.write((const char*) &passed_header.colorMapLength, 2);
    output_file.write((const char*) &passed_header.colorMapDepth, 1);
    output_file.write((const char*) &passed_header.xOrigin, 2);
    output_file.write((const char*) &passed_header.yOrigin, 2);
    output_file.write((const char*) &passed_header.width, 2);
    output_file.write((const char*) &passed_header.height, 2);
    output_file.write((const char*) &passed_header.bitsPerPixel, 1);
    output_file.write((const char*) &passed_header.imageDescriptor, 1);

    //total number of pixels
    int total_pixel_count = (int)passed_header.width*(int)passed_header.height;

    for (int i = 0; i < total_pixel_count*3; i++) {
        output_file.write((const char*) &passed_header.pixel_vect[i], 1);
    }
}

bool valid_filename(const std::string &filename) {
    if (filename.length() >= 5) {
        if (filename.substr((filename.length()-4),filename.length()) == ".tga") {
            return true;
        }
    }
    return false;
}


