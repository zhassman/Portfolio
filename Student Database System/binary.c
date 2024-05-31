#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "binary.h"

student *student_new(uint32_t ucid, char *cnet, uint32_t ssn, char *lname, char *fname){
  student *result = (student*)malloc(sizeof(student));
  result->ucid = ucid;
  result->cnet = strdup(cnet);
  result->ssn = ssn;
  result->lname = strdup(lname);
  result->fname = strdup(fname);
  return result;
}

void student_free(student *stu){
  free(stu->cnet);
  free(stu->lname);
  free(stu->fname);
  free(stu);
}

uint32_idx *ui_singleton(uint32_t key, student *stu){
  uint32_idx *result = (uint32_idx*)malloc(sizeof(uint32_idx));
  result->key = key;
  result->stu = stu;
  result->left = NULL;
  result->right = NULL;
  return result;
}

void ui_insert(uint32_idx *ui, uint32_t key, student *stu){
  if (key < ui->key){
    if (!ui->left){ 
      ui->left = ui_singleton(key, stu);
    }
    else{
      ui_insert(ui->left, key, stu);
    }
  }
  else if (key > ui->key){
    if(!ui->right){
      ui->right = ui_singleton(key, stu);
    }
    else{
      ui_insert(ui->right, key, stu);
    }
  }
}

student *ui_find(uint32_idx *ui, uint32_t n){
  if (!ui){
    return NULL;
  }
  else if (ui->key == n){
    return ui->stu;
  }
  else if (n < ui->key){
    if (ui->left){
      return ui_find(ui->left, n);
    }
  }
  else if (n > ui->key){
    if (ui->right){
      return ui_find(ui->right, n);
    }
  }
  return NULL;
}

string_idx *si_singleton(char *key, student *stu){
  string_idx *result = (string_idx*)malloc(sizeof(string_idx));
  result->key = strdup(key);
  result->stu = stu;
  result->left = NULL;
  result->right = NULL;
  return result;
}

void si_insert(string_idx *si, char *key, student *stu){
  int diff = strcmp(key, si->key);
  if (diff > 0){
    if(!si->right){
      si->right = si_singleton(key, stu);
    }
    else{
      si_insert(si->right, key ,stu);
    }
  }
  else if (diff < 0){
    if(!si->left){
      si->left = si_singleton(key, stu);
    }
    else{
      si_insert(si->left, key, stu);
    }
  }
}

student *si_find(string_idx *si, char *s){
  if (!si){
    return NULL;
  }
  int diff = strcmp(s, si->key);
  if (diff == 0){
    return si->stu;
  }
  else if (diff > 0){
    if (si->right){
      return si_find(si->right, s);
    }
  }
  else if (diff < 0){
    if(si->left){
      return si_find(si->left, s);
    }
  }
  return NULL;
}

student_db *db_new(){
  student_db *result = (student_db*)malloc(sizeof(student_db));
  result->count = 0;
  result->ucid_idx = NULL;
  result->cnet_idx = NULL;
  result->ssn_idx = NULL;
  return result;
}

uint32_t db_num_entries(student_db *db){
  return db->count;
}

int check_if_unique(student_db *db, student *stu){
  int is_unique = 1;
  if (ui_find(db->ucid_idx, stu->ucid)){
    fprintf(stderr, "Non-unique ucid. Insertion failed.\n");
    is_unique = 0;
  }
  if (si_find(db->cnet_idx, stu->cnet)){
    fprintf(stderr, "Non-unique cnet. Insertion failed.\n");
    is_unique = 0;
  }
  if (ui_find(db->ssn_idx, stu->ssn)){
    fprintf(stderr, "Non-unique ssn. Insertion failed.\n");
    is_unique = 0;
  }
  return is_unique;
}

void db_insert(student_db *db, student *stu){
  if (db->count == 0){
    db->ucid_idx = ui_singleton(stu->ucid, stu);
    db->cnet_idx = si_singleton(stu->cnet, stu);
    db->ssn_idx = ui_singleton(stu->ssn, stu);
    db->count++;
  }
  else{
    if (check_if_unique(db, stu)){
      ui_insert(db->ucid_idx, stu->ucid, stu);
      si_insert(db->cnet_idx, stu->cnet, stu);
      ui_insert(db->ssn_idx, stu->ssn, stu);
      db->count++;
    }
    else{
      return;
    }
  }
}

student *find_by_ucid(student_db *db, uint32_t ucid){
  return ui_find(db->ucid_idx, ucid);
}

student *find_by_cnet(student_db *db, char *cnet){
  return si_find(db->cnet_idx, cnet);
}

student *find_by_ssn(student_db *db, uint32_t ssn){
  return ui_find(db->ssn_idx, ssn);
}

void ui_shallow_free(uint32_idx *ui){
  if (ui->left){
    ui_shallow_free(ui->left);
  }
  if (ui->right){
    ui_shallow_free(ui->right);
  }
  free(ui);
}

void si_deep_free(string_idx *si){
  student_free(si->stu);
  free(si->key);
  if (si->left){
    si_deep_free(si->left);
  }
  if (si->right){
    si_deep_free(si->right);
  }
  free(si);
}

void db_free(student_db *db){
//Note: Student structs are only freed with si_deep_free to avoid trying to free
//students multiple times.
  if (db->ucid_idx) ui_shallow_free(db->ucid_idx);
  if (db->ssn_idx) ui_shallow_free(db->ssn_idx);
  if (db->cnet_idx) si_deep_free(db->cnet_idx);
  free(db);
}
