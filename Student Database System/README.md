## Student Database System

### hash.c: Hash Table Student Database
- **Description**: Implements a student database using hash tables to store and manage student records efficiently.
- **Key Functions**:
  - `student_new`, `student_free`: Manages student records dynamically.
  - `db_new`, `db_insert`, `db_from_file`: Initializes the database, adds new entries, and fills the database from a file.
  - `find_by_ucid`, `find_by_cnet`, `find_by_ssn`: Searches for students using various identifiers.
  - `db_free`, `shi_deep_free`, `ihi_shallow_free`: Ensures proper memory management and cleanup.
- **Highlights**:
  - Uses hash tables to optimize data retrieval and management.
  - Supports complex data structures for improved performance.
  - Robust error handling and uniqueness checks for data integrity.

### binary.c: Binary Search Tree Student Database
- **Description**: Utilizes binary search trees to manage a student database, enabling efficient data operations using identifiers and names.
- **Key Functions**:
  - `student_new`, `student_free`: Handles creation and deletion of student records.
  - `ui_insert`, `si_insert`: Inserts students into integer-keyed and string-keyed binary search trees.
  - `ui_find`, `si_find`: Retrieves student records from trees.
  - `db_new`, `db_insert`, `db_free`: Manages overall database functions, including initialization and memory cleanup.
- **Highlights**:
  - Implements binary search trees for efficient sorting and retrieval.
  - Manages dual indexing systems (integer and string keys) for versatile operations.
  - Focuses on deep and shallow memory management to prevent memory leaks.
