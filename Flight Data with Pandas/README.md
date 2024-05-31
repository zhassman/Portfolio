## ASQP Data Processing Module

### Overview
This module processes and analyzes ASQP flight data, focusing on delays, cancellations, and operational metrics.

### Features
- **Data Handling**: Processes ASC and NPY files into usable formats.
- **Analytical Functions**: Includes comprehensive functions to calculate flight delays, cancellations, and performance metrics across various dimensions.
- **Time Series Analysis**: Implements methods for smoothing and detrending data to analyze trends and seasonality.

### Usage
Functions cover data processing (`read_and_process_asc`, `read_and_process_npy`), calculating metrics (`delay_and_cancel_fractions`, `average_delay`), and time series analysis (`remove_trend`, `is_seasonal`).

### Dependencies
- **NumPy & Pandas**: For data manipulation and numerical calculations.
- **Utils Module**: Provided by Borja Sotomayor at UChicago, contains essential utilities for the module.
