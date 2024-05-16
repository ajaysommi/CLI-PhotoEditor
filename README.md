# CLI-PhotoEditor
This program is a powerful and flexible image manipulator that allows users to apply various transformations to their TGA format image files. Inspired by the capabilities of professional photo editing software, this program offers a range of features through a simple command-line interface. Whether you need to flip, rotate, or tweak your images, this program provides the functionality you need with ease and efficiency.

## Features
* **Multiply**: Multiply the pixel values of two TGA images.
* **Subtract**: Subtract the pixel values of two TGA images.
* **Overlay**: Places or "overlays" second TGA image onto first.
* **Screen**: Similar to overlay except the second TGA image is the first layer.
* **Combine**: Takes the individual pixel values from three different TGA images and combines them into one image.
* **Flip**: Rotates the given image 180 degrees.
* **Add**: Adds a certain amount to a specific color channel. For example, the "addgreen" command would add an amount specified by the user to the green channel.
* **Scale**: Similar to the add feature, scale multiplies a certain amount to a specific color channel. For example, the "scalegreen" command would multiply an amount specified by the user to the green channel.

## Usage
Run the tool from the command line by providing the desired commands and options. Here are some examples:

#### Multiply

    ./project2.out output firstimage multiply secondimage

#### Subtract

    ./project2.out output firstimage subtract secondimage

#### Overlay

    ./project2.out output firstimage overlay secondimage

#### Screen

    ./project2.out output firstimage screen secondimage

#### Combine

    ./project2.out output firstimage combine secondimage thirdimage

#### Flip

    ./project2.out output firstimage flip

#### Add

    ./project2.out output firstimage add 200

#### Scale

    ./project2.out output firstimage scale 3

