#ifndef MEMFREE_H
#define MEMFREE_H

void mem_free_char_array(char* c);
void mem_free_char_array_array(char** c,int count);
void mem_free_file_data(struct file_data *fd);
void mem_free_split_string(struct split_string *ss);

#endif
