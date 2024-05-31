#ifndef _hash_HEADER_
#define _hash_HEADER_
#include <stdint.h>

struct student_record {
  uint32_t ucid;
  char    *cnet;
  uint32_t ssn;
  char    *lname;
  char    *fname;
  struct   student_record *next;
};

typedef struct student_record student;

struct student_entry {
  uint64_t hash_code;
  student *stu;
  struct student_entry *next;
};

typedef struct student_entry entry;

struct uint32_hash_index {
  uint64_t(*hash)(uint32_t n);
  uint32_t n_buckets;
  struct student_entry **buckets;
};

struct string_hash_index {
  uint64_t(*hash)(char *s);
  uint32_t n_buckets;
  struct student_entry **buckets;
};

typedef struct string_hash_index shi;
typedef struct uint32_hash_index ihi;

struct student_database {
  uint32_t count;
  ihi *ucid_idx;
  shi *cnet_idx;
  ihi *ssn_idx;
  shi *lname_idx;
  shi *fname_idx;
};

typedef struct student_database student_db;

student *student_new(uint32_t ucid, char *cnet, uint32_t ssn, char *lname, char *fname);

student *student_from_string(char *csv_row);

void student_free(student *stu);

ihi *ihi_new(uint32_t n_buckets, uint64_t(*h)(uint32_t n));

void ihi_insert_by_ucid(ihi *idx, student *stu);

void ihi_insert_by_ssn(ihi *idx, student *stu);

student *ihi_find_by_ucid(ihi *idx, uint32_t n);

student *ihi_find_by_ssn(ihi *idx, uint32_t n);

shi *shi_new(uint32_t n_buckets, uint64_t(*h)(char *s));

void shi_insert_by_cnet(shi *idx, student *stu);

void shi_insert_by_lname(shi *idx, student *stu);

void shi_insert_by_fname(shi *idx, student *stu);

student *shi_find_by_cnet(shi *idx, char *s);

student *shi_find_by_lname(shi *idx, char *s);

student *shi_find_by_fname(shi *idx, char *s);

student_db *db_new(uint32_t n_buckets, uint64_t(*int_hash)(uint32_t n), uint64_t(*string_hash)(char *));

void db_insert(student_db *db, student *stu);

student_db *db_from_file(char *filename, uint64_t(*int_hash)(uint32_t n), uint64_t(*string_hash)(char *));

student *find_by_ucid(student_db *db, uint32_t ucid);

student *find_by_cnet(student_db *db, char *cnet);

student *find_by_ssn(student_db *db, uint32_t ssn);

student *find_by_lname(student_db *db, char *lname);

student *find_by_fname(student_db *db, char *fname);

void fill_with_cnets(char **arr, student_db *db);

void swap(char **arr, int i, int j);

void bubblesort(char **arr, int len);

char **cnets_asc(student_db *db);

student_db *db_resize(student_db *db, uint32_t n_buckets);

void ihi_shallow_free(ihi *idx, int count);

void shi_shallow_free(shi *idx, int count);

void shi_deep_free(shi *idx, int count);

void db_free(student_db *db);

#endif
