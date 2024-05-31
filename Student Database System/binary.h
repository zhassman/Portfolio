#ifndef _binary_HEADER_
#define _binary_HEADER_
#include <stdint.h>

struct student_record {
  uint32_t ucid;
  char *cnet;
  uint32_t ssn;
  char *lname;
  char *fname;
};

typedef struct student_record student;

struct uint32_unique_index {
  uint32_t key;
  struct student_record *stu;
  struct uint32_unique_index *left;
  struct uint32_unique_index *right;
};

struct string_unique_index {
  char *key;
  struct student_record *stu;
  struct string_unique_index *left;
  struct string_unique_index *right;
};

typedef struct string_unique_index string_idx;
typedef struct uint32_unique_index uint32_idx;

struct student_database {
  uint32_t count;
  uint32_idx *ucid_idx;
  string_idx *cnet_idx;
  uint32_idx *ssn_idx;
};

typedef struct student_database student_db;

student *student_new(uint32_t ucid, char *cnet, uint32_t ssn, char *lname, char *fname);

void student_free(student *stu);

uint32_idx *ui_singleton(uint32_t key, student *stu);

void ui_insert(uint32_idx *ui, uint32_t key, student *stu);

student *ui_find(uint32_idx *ui, uint32_t n);

string_idx *si_singleton(char *key, student *stu);

void si_insert(string_idx *si, char *key, student *stu);

student *si_find(string_idx *si, char *s);

student_db *db_new();

uint32_t db_num_entries(student_db *db);

void db_insert(student_db *db, student *stu);

student *find_by_ucid(student_db *db, uint32_t ucid);

student *find_by_cnet(student_db *db, char *cnet);

student *find_by_ssn(student_db *db, uint32_t ssn);

void db_free(student_db *db);

#endif
