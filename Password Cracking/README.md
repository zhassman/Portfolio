## Password Cracking Toolkit

### Overview
This toolkit comprises scripts for analyzing password datasets, extracting hashes, cracking them using Hashcat, and generating passwords with a Markov model. It aims to enhance understanding and security of password systems.

### Scripts

- **`passwordAnalysis.py`**
  - **Purpose**: Analyzes password data to identify common traits.
  - **Output**: Lists the 1,000 most common passwords.

- **`hashExtractor.py`**
  - **Purpose**: Extracts password hashes from UNIX shadow files.
  - **Output**: Produces a list of password hashes.

- **`potfileComparer.py`**
  - **Purpose**: Compares Hashcat pot files to find unique and common cracks.
  
- **`findBestMask.py`**
  - **Purpose**: Identifies effective mask patterns for Hashcat.
  
- **`markovTrain.py`**
  - **Purpose**: Trains a Markov model on password datasets.
  - **Output**: Serialized Markov model file.
  
- **`markovProbability.py`**
  - **Purpose**: Calculates probabilities of passwords based on the Markov model.
  - **Output**: Password strength assessments.
  
- **`markovGenerator.py`**
  - **Purpose**: Generates passwords using the Markov model.
  - **Output**: 1,000 plausible passwords.

### Tools and Technologies
- **Hashcat**: For password cracking, leveraging CPU and GPU capabilities.
- **Python**: For scripting, given its robust libraries and ease of use.

### Goals
- **Analyze Password Security**: Uses real-world data to study password security.
- **Enhance Cracking Techniques**: Improves password cracking strategies.
- **Innovate Password Generation**: Uses probabilistic models to create and assess passwords.
