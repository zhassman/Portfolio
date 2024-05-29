## Password Cracking

### Project Overview

This toolkit comprises several scripts designed to analyze password datasets, extract password hashes, crack them using Hashcat, and generate passwords using a Markov model. The scripts provide a comprehensive approach to understanding and enhancing password security.

### File Descriptions

#### `passwordAnalysis.py`
- **Purpose**: Analyzes a dataset of passwords (specifically, the RockYou breach) to determine common characteristics such as length and complexity.
- **Outputs**: Generates a list of the 1,000 most common passwords from the dataset.

#### `hashExtractor.py`
- **Purpose**: Extracts password hashes from a UNIX shadow file. Focuses on specific user accounts to prepare data for hash cracking.
- **Output**: List of extracted password hashes.

#### `potfileComparer.py`
- **Purpose**: Compares Hashcat pot files to determine unique and common entries between different cracking sessions. Useful for analyzing the effectiveness of various hash cracking approaches.

#### `findBestMask.py`
- **Purpose**: Analyzes password datasets to determine the most effective mask patterns for use with Hashcat, enhancing the efficiency of mask attacks.

#### `markovTrain.py`
- **Purpose**: Trains an order-1 Markov model on a password dataset to understand password structure and predictability.
- **Output**: Trained Markov model serialized into a file for further analysis or generation tasks.

#### `markovProbability.py`
- **Purpose**: Calculates the probability of passwords based on a trained Markov model, providing insights into password strength and common patterns.
- **Output**: Outputs password probabilities, aiding in the assessment of password security.

#### `markovGenerator.py`
- **Purpose**: Generates passwords based on a trained Markov model, using probabilistic methods to simulate realistic password creation behaviors.
- **Output**: List of 1,000 generated passwords, showcasing the application of the Markov model in generating plausible passwords.

### Tools and Technologies
- **Hashcat**: Utilized for cracking password hashes, leveraging both CPU and GPU capabilities to test various cracking strategies.
- **Python**: Scripts are written in Python, chosen for its robust libraries and ease of handling data manipulations and file operations.

### Project Goals
- **Analyze Password Security**: Offers tools to analyze real-world password security by studying actual data breaches.
- **Enhance Cracking Techniques**: Improves understanding of effective password cracking strategies using Hashcat.
- **Innovate Password Generation**: Explores probabilistic models to generate and evaluate password strengths, contributing to better security practices.

This toolkit serves as a practical application of password security concepts, suitable for security professionals and researchers interested in the fields of data security and cryptographic applications.
