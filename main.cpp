/**
 * The following code takes in user inputs from CLI and executes respective functions.
 *
 * @author Ajay Sommi
 * @date 03/27/24
 */
#include <iostream>
#include "File.h"

int main(int argc, char* argv[]) {
    if (argc == 1 || (std::string)argv[1] == "--help") {
        std::cout << "Project 2: Image Processing, Spring 2024\n" << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << "\t./project2.out [output] [firstImage] [method] [...]" << std::endl;
        exit(0);
    }

    Header tracking_image;
    Header output_image;
    int iteration_counter = 0;

    //check to see if output file extension (arg 1) is valid
    if (!valid_filename((std::string)argv[1])) {
        std::cout << "Invalid file name." << std::endl;
        exit(0);
    }

    //check to see if tracking file extension (arg 2) is valid
    if (valid_filename((std::string)argv[2])) {
        //assigns tracking image to second argument
        tracking_image = read_from_file(argv[2]);
        if (!tracking_image.file_open) {
            std::cout << "File does not exist." << std::endl;
            exit(0);
        }
    }
    else {
        std::cout << "Invalid file name." << std::endl;
        exit(0);
    }

    //iterate through number of arguments and perform respective functions
    for (int i = 3; i < argc;) {
        if ((std::string) argv[i] == "multiply") {
            if (i == argc - 1) {
                std::cout << "Missing argument." << std::endl;
                exit(0);
            }
            if (!valid_filename((std::string) argv[i + 1])) {
                std::cout << "Invalid argument, invalid file name." << std::endl;
                exit(0);
            }
            Header check_open = read_from_file(argv[i + 1]);
            if (!check_open.file_open) {
                std::cout << "Invalid argument, file does not exist." << std::endl;
                exit(0);
            }
            Header multiplied_result = multiply(tracking_image, (std::string) argv[i + 1]);
            tracking_image = multiplied_result;
            if (iteration_counter == 0) {
                std::cout << "Multiplying " << ((std::string)argv[2]) << " and " << ((std::string)argv[i + 1])
                          << " ..." << std::endl;
            }
            else {
                std::cout << "... and multiplying output and " << ((std::string)argv[i + 1]) << " ..." << std::endl;
            }
            i += 2;
        }
        else if ((std::string) argv[i] == "subtract") {
            if (!valid_filename((std::string) argv[i + 1])) {
                std::cout << "Invalid argument, invalid file name." << std::endl;
                exit(0);
            }
            Header check_open = read_from_file(argv[i + 1]);
            if (!check_open.file_open) {
                std::cout << "Invalid argument, file does not exist." << std::endl;
                exit(0);
            }
            Header subtracted_result = subtract(tracking_image, (std::string) argv[i + 1]);
            tracking_image = subtracted_result;
            if (iteration_counter == 0) {
                std::cout << "Subtracting " << ((std::string)argv[i + 1]) << " from " << ((std::string)argv[2])
                          << " ..." << std::endl;
            }
            else {
                std::cout << "... and subtracting " << ((std::string)argv[i + 1])
                << " from previous step ..." << std::endl;
            }
            i += 2;
        }
        else if ((std::string) argv[i] == "overlay") {
            if (!valid_filename((std::string) argv[i + 1])) {
                std::cout << "Invalid argument, invalid file name." << std::endl;
                exit(0);
            }
            Header check_open = read_from_file(argv[i + 1]);
            if (!check_open.file_open) {
                std::cout << "Invalid argument, file does not exist." << std::endl;
                exit(0);
            }
            Header overlay_result = overlay(tracking_image, (std::string) argv[i + 1]);
            tracking_image = overlay_result;
            if (iteration_counter == 0) {
                std::cout << "Overlaying " << ((std::string)argv[2]) << " and " << ((std::string)argv[i + 1])
                          << " ..." << std::endl;
            }
            else {
                std::cout << "... and overlaying output and " << ((std::string)argv[i + 1]) << " ..." << std::endl;
            }
            i += 2;
        } else if ((std::string) argv[i] == "screen") {
            if (!valid_filename((std::string) argv[i + 1])) {
                std::cout << "Invalid argument, invalid file name." << std::endl;
                exit(0);
            }
            Header check_open = read_from_file(argv[i + 1]);
            if (!check_open.file_open) {
                std::cout << "Invalid argument, file does not exist." << std::endl;
                exit(0);
            }
            Header screen_result = screen((std::string) argv[i + 1], tracking_image);
            tracking_image = screen_result;
            if (iteration_counter == 0) {
                std::cout << "Screening " << ((std::string)argv[2]) << " and " << ((std::string)argv[i + 1])
                          << " ..." << std::endl;
            }
            else {
                std::cout << "... and screening output and " << ((std::string)argv[i + 1]) << " ..." << std::endl;
            }
            i += 2;
        } else if ((std::string) argv[i] == "combine") {
            Header check_open = read_from_file(argv[i + 1]);
            if (!check_open.file_open) {
                std::cout << "Invalid argument, file does not exist." << std::endl;
                exit(0);
            }
            Header check_open2 = read_from_file(argv[i + 2]);
            if (!check_open2.file_open) {
                std::cout << "Invalid argument, file does not exist." << std::endl;
                exit(0);
            }
            if (!valid_filename((std::string) argv[i + 2])) {
                std::cout << "Invalid argument, invalid file name." << std::endl;
                exit(0);
            }
            if (!valid_filename((std::string) argv[i + 1])) {
                std::cout << "Invalid argument, invalid file name." << std::endl;
                exit(0);
            }
            Header combine = combine_files((std::string) argv[i + 2], (std::string) argv[i + 1],
                                           tracking_image);
            tracking_image = combine;
            if (iteration_counter == 0) {
                std::cout << "Combining channels of " << ((std::string)argv[2]) << ", " <<
                ((std::string)argv[i + 2]) << ", and " << ((std::string)argv[i + 1]) << " ..." << std::endl;
            }
            else {
                std::cout << "... and combining channels of output and " << ((std::string)argv[i + 2])
                << " and " << ((std::string)argv[i + 1]) << " ..." << std::endl;
            }
            i += 3;
        } else if ((std::string) argv[i] == "flip") {
            Header flip = rotate(tracking_image);
            tracking_image = flip;
            if (iteration_counter == 0) {
                std::cout << "Flipping " << ((std::string)argv[2]) << " ..." << std::endl;
            }
            else {
                std::cout << "... and flipping output of previous step ..." << std::endl;
            }
            i += 1;
        } else if ((std::string) argv[i] == "onlyred") {
            Header red_file = task_8_function(tracking_image, 2);
            tracking_image = red_file;
            i += 1;
        } else if ((std::string) argv[i] == "onlygreen") {
            Header green_file = task_8_function(tracking_image, 1);
            tracking_image = green_file;
            i += 1;
        } else if ((std::string) argv[i] == "onlyblue") {
            Header blue_file = task_8_function(tracking_image, 0);
            tracking_image = blue_file;
            i += 1;
        } else if ((std::string) argv[i] == "addred") {
            //color_val: 0 = B, 1 = G, 2 = R
            try {
                std::stoi(argv[i + 1]);
            }
            catch (std::invalid_argument& e){
                std::cout << "Invalid argument, expected number." << std::endl;
                exit(0);
            }
            Header addred_result = modifyadd(tracking_image, std::stoi(argv[i + 1]), 2);
            tracking_image = addred_result;
            std::string symbol = "-";
            if (std::stoi(argv[i + 1]) > 0) {
                symbol = "+";
            }
            if (iteration_counter == 0) {
                std::cout << "Adding " << symbol << std::stoi(argv[i + 1]) << " to red channel of "
                << (std::string)argv[2] << " ..." << std::endl;
            }
            else {
                std::cout << "... and adding " << symbol << std::stoi(argv[i + 1])
                << " to red channel of previous step ..." << std::endl;
            }
            i += 2;
        } else if ((std::string) argv[i] == "addgreen") {
            //color_val: 0 = B, 1 = G, 2 = R
            //if argv[i+1] is not integer, print "Invalid argument, expected number"
            try {
                std::stoi(argv[i + 1]);
            }
            catch (std::invalid_argument& e){
                std::cout << "Invalid argument, expected number." << std::endl;
                exit(0);
            }
            Header addgreen_result = modifyadd(tracking_image, std::stoi(argv[i + 1]), 1);
            tracking_image = addgreen_result;
            std::string symbol = "-";
            if (std::stoi(argv[i + 1]) > 0) {
                symbol = "+";
            }
            if (iteration_counter == 0) {
                std::cout << "Adding " << symbol << std::stoi(argv[i + 1]) << " to red channel of "
                          << (std::string)argv[2] << " ..." << std::endl;
            }
            else {
                std::cout << "... and adding " << symbol << std::stoi(argv[i + 1])
                          << " to red channel of previous step ..." << std::endl;
            }
            i += 2;
        } else if ((std::string) argv[i] == "addblue") {
            //color_val: 0 = B, 1 = G, 2 = R
            try {
                std::stoi(argv[i + 1]);
            }
            catch (std::invalid_argument& e){
                std::cout << "Invalid argument, expected number." << std::endl;
                exit(0);
            }
            Header addblue_result = modifyadd(tracking_image, std::stoi(argv[i + 1]), 0);
            tracking_image = addblue_result;
            std::string symbol = "-";
            if (std::stoi(argv[i + 1]) > 0) {
                symbol = "+";
            }
            if (iteration_counter == 0) {
                std::cout << "Adding " << symbol << std::stoi(argv[i + 1]) << " to red channel of "
                          << (std::string)argv[2] << " ..." << std::endl;
            }
            else {
                std::cout << "... and adding " << symbol << std::stoi(argv[i + 1])
                          << " to red channel of previous step ..." << std::endl;
            }
            i += 2;
        } else if ((std::string) argv[i] == "scalered") {
            //color_val: 0 = B, 1 = G, 2 = R
            try {
                std::stoi(argv[i + 1]);
            }
            catch (std::invalid_argument& e){
                std::cout << "Invalid argument, expected number." << std::endl;
                exit(0);
            }
            Header scalered_result = modifyscale(tracking_image, std::stoi(argv[i + 1]), 2);
            tracking_image = scalered_result;
            if (iteration_counter == 0) {
                std::cout << "Scaling the red channel of " << (std::string)argv[2] << " by "
                << std::stoi(argv[i + 1]) << " ..." << std::endl;
            }
            else {
                std::cout << "... and scaling the red channel of previous step by "
                << std::stoi(argv[i + 1]) << " ..." << std::endl;
            }
            i += 2;
        } else if ((std::string) argv[i] == "scalegreen") {
            //color_val: 0 = B, 1 = G, 2 = R
            try {
                std::stoi(argv[i + 1]);
            }
            catch (std::invalid_argument& e){
                std::cout << "Invalid argument, expected number." << std::endl;
                exit(0);
            }
            Header scalegreen_result = modifyscale(tracking_image, std::stoi(argv[i + 1]), 1);
            tracking_image = scalegreen_result;
            if (iteration_counter == 0) {
                std::cout << "Scaling the green channel of " << (std::string)argv[2] << " by "
                          << std::stoi(argv[i + 1]) << " ..." << std::endl;
            }
            else {
                std::cout << "... and scaling the green channel of previous step by "
                          << std::stoi(argv[i + 1]) << " ..." << std::endl;
            }
            i += 2;
        } else if ((std::string) argv[i] == "scaleblue") {
            //color_val: 0 = B, 1 = G, 2 = R
            try {
                try {
                    std::stoi(argv[i + 1]);
                }
                catch (std::invalid_argument& e){
                    std::cout << "Invalid argument, expected number." << std::endl;
                    exit(0);
                }
                Header scaleblue_result = modifyscale(tracking_image, std::stoi(argv[i + 1]), 0);
                tracking_image = scaleblue_result;
                if (iteration_counter == 0) {
                    std::cout << "Scaling the blue channel of " << (std::string)argv[2] << " by "
                              << std::stoi(argv[i + 1]) << " ..." << std::endl;
                }
                else {
                    std::cout << "... and scaling the blue channel of previous step by "
                              << std::stoi(argv[i + 1]) << " ..." << std::endl;
                }
                i += 2;
            }
            catch (std::logic_error& e) {
                std::cout << "Missing argument." << std::endl;
                exit(0);
            }

        }
        else {
            std::cout << "Invalid method name." << std::endl;
            exit(0);
        }
        iteration_counter++;
    }
    write_to_file(tracking_image, (std::string)argv[1]);
    std::cout << "... and saving output to " << (std::string)argv[1] << "!" << std::endl;

    return 0;
}