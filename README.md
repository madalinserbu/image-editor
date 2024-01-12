## Homework No. 3, Serbu Ovidiu-Madalin, 324CA
# Image Editor

This is a simple command-line tool for basic image processing. It allows users to load images, select regions, crop, apply filters, save modified images, and exit the application.

I've implemented the following commands:
LOAD: Load an image from a specified file path.
SELECT: Define a region of interest in the loaded image.
CROP: Crop the image based on the selected region.
APPLY: Apply filters or effects to the selected region.
SAVE: Save the modified image to a specified file path.
EQUALIZE: Equalize the histogram of the entire image.
EXIT: Close the application.

LOAD

This module provides functionality to load images from various formats, including text and binary representations. The primary purpose is to read image files, extract relevant information, and allocate memory to store the image data.

 - The load_command function takes a file path as input and loads the corresponding image. It supports different image formats such as grayscale and color, both in text and binary representations.
 - The removeComments function is a helper function used to skip comments in the image file. It disregards lines starting with '#' and moves the file cursor to the next valid position.

 SELECT

 This module provides functionality for selecting regions within an image. Users can define a specific rectangular area of interest, and the module ensures the validity of the coordinates.

 - The select_command function interprets user input to determine the desired image selection. It supports two modes:

Selecting the entire image: SELECT ALL
Defining a rectangular region: SELECT x1 y1 x2 y2

 - The areCoordinatesValid function ensures the validity of the specified coordinates. It checks if the coordinates are in the correct order, within the image boundaries, and form a non-zero area.

 - The selectImage function sets the coordinates for the selected region within the image.

 APPLY

  - The apply_command function interprets user input to determine the desired filter type. It then calls the apply_filter function to apply the selected filter to the specified region of the image.

  - The apply_filter function applies a specific filter kernel to the selected region of the image. Supported filters include edge detection, sharpening, blur, and Gaussian blur.

  - The clamp_value function clamps a given value within a specified range to avoid overflow.

  CROP

  This module provides functionality to crop an image based on a previously selected region. Users can define a specific area of interest within the image, and the module will crop the image to retain only the selected region.

   - The crop_command function crops the image to the region defined by the current selection frame. It allocates memory for a new sub-image, transfers pixels from the old image to the new sub-image, deallocates space for the old image, and updates the image information.

   EQUALIZE

   This module provides functionality to equalize a black and white image. Image equalization enhances the contrast of an image by redistributing pixel intensity values. It is particularly effective for improving the visual appearance of grayscale images.

    - The equalize_command function equalizes a black and white image by applying a histogram equalization technique. It calculates the histogram of pixel intensity values, and then redistributes these values to enhance the overall contrast.

     - The my_clamp function clamps a double value within the range of 0 to 255 to ensure that pixel intensity values remain within valid bounds.

 - The sum function calculates the sum of elements in a vector up to a specified position.

 - The equalize_pixel function applies the equalization operation on a single pixel, taking into account the histogram and the total number of pixels.

SAVE

This module provides functionality to save an image in different formats: ASCII and binary. Users can specify the format and filename when saving the image.

The save_ascii function saves the image in ASCII format. It opens the file for writing text, writes image information (width, height, and maximum intensity), and then iterates through each pixel to write the pixel values to the file.

The save_binary function saves the image in binary format. It opens the file for writing, writes image information (format, width, height, and maximum intensity), and then iterates through each pixel to write the pixel values to the file in binary form.

The save function handles the SAVE command. It parses the user input to determine the filename and format. Then, it calls the appropriate saving function based on the format specified.

EXIT

This module provides functionality to handle the EXIT command. It frees the memory allocated for the loaded image and exits the program.

The exit_command function handles the EXIT command. It checks if there is an image loaded, frees the allocated memory for the image using the freeImageMemory function, and then exits the program.

UTILS.H

This module, named utils.h, provides utility functions and structures for handling RGB color values and managing image information.

rgb: Represents RGB color values with components r, g, and b.

ImageInfo: Stores information about an image, including width, height, selected region coordinates, magic identifier, image type, maximum intensity value, and a 2D array to store RGB pixel values.

This image processing application provides a comprehensive set of features for handling image operations. It was a very lucrative homework and it helped me sharpen my skills in pointer handling and general programme designing.