#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

student *student_new(uint32_t ucid, char *cnet, uint32_t ssn, char *lname, 
                                                              char *fname)
{
  student *result = (student*)malloc(sizeof(student));
  result->ucid = ucid;
  result->cnet = strdup(cnet);
  result->ssn = ssn;
  result->lname = strdup(lname);
  result->fname = strdup(fname);
  result->next = NULL;
  return result;
}

student *student_from_string(char *csv_row){
  uint32_t ucid;
  char *cnet;
  uint32_t ssn;
  char *lname;
  char *fname;

  int start_at = 0;
  int stop_at;

  int field_counter = 0;
  int len = strlen(csv_row);
  for (int i = 0; i < len; i++){
    if (csv_row[i] == ',' || i + 1 == len){
      stop_at = i;
      if (i + 1 == len) stop_at++;
      int temp_len = stop_at - start_at;
      char temp[temp_len + 1];
      for(int j = 0; j < temp_len; j++){
        temp[j] = csv_row[start_at + j];
      }
      temp[temp_len] = '\0';
      if (field_counter == 0){
        ucid = atoi(temp);
      }
      else if (field_counter == 1){
        cnet = strdup(temp);
      }
      else if (field_counter == 2){
        ssn = atoi(temp);
      }
      else if (field_counter == 3){
        lname = strdup(temp);
      }
      else{
        fname = strdup(temp);
      }
      start_at = i + 1;
      field_counter++;
    }
  }
  student *result =  student_new(ucid, cnet, ssn, lname, fname);
  free(cnet);
  free(fname);
  free(lname);
  return result;
}

void student_free(student *stu){
  free(stu->cnet);
  free(stu->lname);
  free(stu->fname);
  free(stu);
}

ihi *ihi_new(uint32_t n_buckets, uint64_t(*h)(uint32_t n)){
  ihi *result = (ihi*)malloc(sizeof(ihi));
  result->n_buckets = n_buckets;
  result->hash = h;
  struct student_entry **buckets = (struct student_entry**)calloc(n_buckets, 
                                               sizeof(struct student_entry));
  result->buckets = buckets;
  return result;
}

void ihi_insert_by_ucid(ihi *idx, student *stu){
  int hash_code = idx->hash(stu->ucid);
  int hash_index = hash_code % idx->n_buckets;
  entry *new = (entry*)malloc(sizeof(entry));
  new->hash_code = hash_code;
  new->stu = stu;
  if (!idx->buckets[hash_index]){
    new->next = NULL;
  }
  else {
    new->next = idx->buckets[hash_index];
  }
  idx->buckets[hash_index] = new;
}

void ihi_insert_by_ssn(ihi *idx, student *stu){
  int hash_code = idx->hash(stu->ssn);
  int hash_index = hash_code % idx->n_buckets;
  entry *new = (entry*)malloc(sizeof(entry));
  new->hash_code = hash_code;
  new->stu = stu;
  if (!idx->buckets[hash_index]){
    new->next = NULL;
  }
  else {
    new->next = idx->buckets[hash_index];
  }
  idx->buckets[hash_index] = new;
}

student *ihi_find_by_ucid(ihi *idx, uint32_t n){
  int hash_code = idx->hash(n);
  int hash_index = hash_code % idx->n_buckets;
  if (!idx->buckets[hash_index]){
    return NULL;
  }
  else{
    entry *curr = idx->buckets[hash_index];
    while (curr){
      if (curr->stu->ucid == n){
        curr->stu->next = NULL;
        return curr->stu;
      }
      else{
        curr = curr->next;
      }
    }
    return NULL;
  }
}

student *ihi_find_by_ssn(ihi *idx, uint32_t n){
  int hash_code = idx->hash(n);
  int hash_index = hash_code % idx->n_buckets;
  if (!idx->buckets[hash_index]){
    return NULL;
  }
  else{
    entry *curr = idx->buckets[hash_index];
    while (curr){
      if (curr->stu->ssn == n){
        curr->stu->next = NULL;
        return curr->stu;
      }
      else{
        curr = curr->next;
      }
    }
    return NULL;
  }
}

shi *shi_new(uint32_t n_buckets, uint64_t(*h)(char *s)){
  shi *result = (shi*)malloc(sizeof(ihi));
  result->n_buckets = n_buckets;
  result->hash= h;
  struct student_entry **buckets = (struct student_entry**)calloc(n_buckets, 
                                              sizeof(struct student_entry));
  result->buckets = buckets;
  return result;
}

void shi_insert_by_cnet(shi *idx, student *stu){
  int hash_code = idx->hash(stu->cnet);
  int hash_index = hash_code % idx->n_buckets;
  entry *new = (entry*)malloc(sizeof(entry));
  new->hash_code = hash_code;
  new->stu = stu;
  if (!idx->buckets[hash_index]){
    new->next = NULL;
  }
  else{
    new->next = idx->buckets[hash_index];
  }
  idx->buckets[hash_index] = new;
}

void shi_insert_by_lname(shi *idx, student *stu){
  int hash_code = idx->hash(stu->lname);
  int hash_index = hash_code % idx->n_buckets;
  entry *new = (entry*)malloc(sizeof(entry));
  new->hash_code = hash_code;
  new->stu = stu;
  if (!idx->buckets[hash_index]){
    new->next = NULL;
  }
  else{
    new->next = idx->buckets[hash_index];
  }
  idx->buckets[hash_index] = new;
}

void shi_insert_by_fname(shi *idx, student *stu){
  int hash_code = idx->hash(stu->fname);
  int hash_index = hash_code % idx->n_buckets;
  entry *new = (entry*)malloc(sizeof(entry));
  new->hash_code = hash_code;
  new->stu = stu;
  if (!idx->buckets[hash_index]){
    new->next = NULL;
  }
  else{
    new->next = idx->buckets[hash_index];
  }
  idx->buckets[hash_index] = new;
}

student *shi_find_by_cnet(shi *idx, char *s){
  int hash_code = idx->hash(s);
  int hash_index = hash_code % idx->n_buckets;
  if (!idx->buckets[hash_index]){
    return NULL;
  }
  else{
    entry *curr = idx->buckets[hash_index];
    while (curr){
      if (strcmp(curr->stu->cnet, s) == 0){
        curr->stu->next = NULL;
        return curr->stu;
      }
      else{
        curr = curr->next;
      }
    }
    return NULL;
  }
}

student *shi_find_by_lname(shi *idx, char *s){
  int hash_code = idx->hash(s);
  int hash_index = hash_code % idx->n_buckets;
  if (!idx->buckets[hash_index]){
    return NULL;
  }
  else{
    entry *curr = idx->buckets[hash_index];
    student *result = NULL;
    while (curr){
      if (strcmp(curr->stu->lname, s) == 0){
        curr->stu->next = result;
        result = curr->stu;
        curr = curr->next;
      }
      else{
        curr = curr->next;
      }
    }
    return result;
  }
}

student *shi_find_by_fname(shi *idx, char *s){
  int hash_code = idx->hash(s);
  int hash_index = hash_code % idx->n_buckets;
  if (!idx->buckets[hash_index]){
    return NULL;
  }
  else{
    entry *curr = idx->buckets[hash_index];
    student *result = NULL;
    while (curr){
      if (strcmp(curr->stu->fname, s) == 0){
        curr->stu->next = result;
        result = curr->stu;
        curr = curr->next;
      }
      else{
        curr = curr->next;
      }
    }
    return result;
  }
}

student_db *db_new(uint32_t n_buckets, uint64_t(*int_hash)(uint32_t n), 
                                       uint64_t(*string_hash)(char *))
{
  student_db *result = (student_db*)malloc(sizeof(student_db));
  result->count = 0;
  result->ucid_idx = ihi_new(n_buckets, int_hash);
  result->cnet_idx = shi_new(n_buckets, string_hash);
  result->ssn_idx = ihi_new(n_buckets, int_hash);
  result->lname_idx = shi_new(n_buckets, string_hash);
  result->fname_idx = shi_new(n_buckets, string_hash);
  return result;
}

int check_if_unique(student_db *db, student *stu){
  int is_unique = 1;
  if (ihi_find_by_ucid(db->ucid_idx, stu->ucid)){
    fprintf(stderr, "Non-unique ucid. Insertion failed.\n");
    is_unique = 0;
  }
  if (shi_find_by_cnet(db->cnet_idx, stu->cnet)){
    fprintf(stderr, "Non-unique cnet. Insertion failed.\n");
    is_unique = 0;
  }
  if(ihi_find_by_ssn(db->ssn_idx, stu->ssn)){
    fprintf(stderr, "Non-unique ssn. Insertion failed.\n");
    is_unique = 0;
  }
  return is_unique;
}

void db_insert(student_db *db, student *stu){
  if (!db || !stu){
    return;
  }
  else if (check_if_unique(db, stu)){
    ihi_insert_by_ucid(db->ucid_idx, stu);
    shi_insert_by_cnet(db->cnet_idx, stu);
    ihi_insert_by_ssn(db->ssn_idx, stu);
    shi_insert_by_lname(db->lname_idx, stu);
    shi_insert_by_fname(db->fname_idx, stu);
    db->count++;
  }
  else{
    return;
  }
}

student_db *db_from_file(char *filename, uint64_t(*int_hash)(uint32_t n), 
                                         uint64_t(*string_hash)(char *))
{
  if (!filename || !int_hash || !string_hash){
    return NULL;
  }
  FILE *f = fopen(filename, "r");
  char row[256] = {0};
  int new_line_count = 0;
  char c = '\0';

  while(c != EOF){
    c = getc(f);
    if (c == '\n') new_line_count++;
  }
  fseek(f, 0, SEEK_SET);
  student_db *result = db_new(new_line_count, int_hash, string_hash);

  while(fgets(row, 256, f)){
    int len = strlen(row);
    int i = 1;
    while (!isprint(row[len-i])){
      row[len-i] = 0;
      i++;
    }
    student *stu = student_from_string(row);
    db_insert(result, stu);
  }
  fclose(f);
  return result;
}

student *find_by_ucid(student_db *db, uint32_t ucid){
  if (!db){
    return NULL;
  }
  return ihi_find_by_ucid(db->ucid_idx, ucid);
}

student *find_by_cnet(student_db *db, char *cnet){
  if (!db || !cnet){
    return NULL;
  }
  return shi_find_by_cnet(db->cnet_idx, cnet);
}

student *find_by_ssn(student_db *db, uint32_t ssn){
  if (!db){
    return NULL;
  }
  return ihi_find_by_ssn(db->ssn_idx, ssn);
}

student *find_by_lname(student_db *db, char *lname){
  if (!db || !lname){
    return NULL;
  }
  return shi_find_by_lname(db->lname_idx, lname);
}

student *find_by_fname(student_db *db, char *fname){
  if (!db || !fname){
    return NULL;
  }
  return shi_find_by_fname(db->fname_idx, fname);
}

void fill_with_cnets(char **arr, student_db *db){
  int found = 0;
  for (int i = 0; found < db->count; i++){
    entry *curr = db->cnet_idx->buckets[i];
    while (curr){
      arr[found] = curr->stu->cnet;
      found++;
      curr = curr->next;
    }
  }
}

void swap(char **arr, int i, int j){
  char *temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

void bubblesort(char **arr, int len){
  int sorted;
  do{
    sorted = 1;
    for(int i =1; i < len; i++){
      if (strcmp(arr[i-1], arr[i]) > 0){
        swap(arr, i-1, i);
        sorted = 0;
      }
    }
    len--;
  } while(!sorted);
}

char **cnets_asc(student_db *db){
  if (!db){
    return NULL;
  }
  int len = db->count;
  char **arr = (char**)malloc(len * sizeof(char**));
  fill_with_cnets(arr, db);
  bubblesort(arr, len);
  return arr;
}

student_db *db_resize(student_db *db, uint32_t n_buckets){
  if(!db){
    return NULL;
  }
  student_db *result = db_new(n_buckets, db->ucid_idx->hash, 
                                         db->cnet_idx->hash);
  int found = 0;
  for(int i = 0; found < db->count; i++){
    entry *curr = db->ucid_idx->buckets[i];
    while(curr){
      db_insert(result, curr->stu);
      found++;
      curr = curr->next;
    }
  }
  return result;
}


void ihi_shallow_free(ihi *idx, int count){
  int found = 0;
  for (int i = 0; found < count; i++){
    entry *curr = idx->buckets[i];
    while (curr){
      entry *next = curr->next;
      free(curr);
      found++;
      curr = next;
    }
  }
  free(idx->buckets);
  free(idx);
}

void shi_shallow_free(shi *idx, int count){
  int found = 0;
  for (int i = 0; found < count; i++){
    entry *curr = idx->buckets[i];
    while (curr){
      entry *next = curr->next;
      free(curr);
      found++;
      curr = next;
    }
  }
  free(idx->buckets);
  free(idx);
}

void shi_deep_free(shi *idx, int count){
  int found = 0;
  for (int i = 0; found < count; i++){
    entry *curr = idx->buckets[i];
    while(curr){
      entry *next = curr->next;
      student_free(curr->stu);
      free(curr);
      found++;
      curr = next;
    }
  }
  free(idx->buckets);
  free(idx);
}

void db_free(student_db *db){
//Note: student structs are only freed with shi_deep_free to avoid trying to
//free students multiple times.
  if (!db){
    return;
  }
  ihi_shallow_free(db->ucid_idx, db->count);
  shi_shallow_free(db->cnet_idx, db->count);
  ihi_shallow_free(db->ssn_idx, db->count);
  shi_shallow_free(db->lname_idx, db->count);
  shi_deep_free(db->fname_idx, db->count);
  free(db);
}
