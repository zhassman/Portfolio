## Grayscale: Image Processing System

### Overview
Grayscale is a project focused on converting images to grayscale using various methods, both sequential and parallel, to illustrate differences in performance related to image processing tasks.

### gray.c: Core Functionality
- **Description**: Contains functions for converting RGB images to grayscale by calculating luminance and applying it to all color channels. It includes methods for both sequential and parallel processing.
- **Key Functions**:
  - `luminance`: Calculates the brightness of a color using a specific formula.
  - `grayscale`: Converts an RGB value to its grayscale equivalent.
  - `same_image`: Checks if two images are identical.
  - `is_grayscale`: Determines if an image is already in grayscale.
  - `read_image`: Reads images in formats P3 or P6 and populates an image structure.
  - `grayscale_seq`: Converts an entire image to grayscale using sequential processing.
  - `grayscale_par`: Utilizes multiple threads to convert an image to grayscale in parallel.
- **Highlights**:
  - Implements efficient image processing algorithms.
  - Utilizes pthreads for parallel processing, demonstrating the effectiveness of multi-threading in reducing processing time.

### graypar.c: Parallel Execution
- **Description**: This component handles the parallel conversion of images to grayscale, intended to demonstrate performance optimization through multi-threading.
- **Execution**:
  - Reads an image and converts it to grayscale using a specified number of threads.
  - Measures and reports the time taken for the conversion, emphasizing the speed-up achieved with parallel processing.

### grayseq.c: Sequential Execution
- **Description**: Manages the sequential conversion of images to grayscale, serving as a benchmark for comparing against parallel execution.
- **Execution**:
  - Processes images in grayscale sequentially.
  - Measures and outputs the time taken to process the image, providing a baseline for performance comparison.

### Performance
- Each component logs the processing time, showcasing the potential time savings when using parallel processing techniques over sequential methods.
