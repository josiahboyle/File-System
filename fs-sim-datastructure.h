/*file struct has just a name and nothing else*/
typedef struct {
  char *name;
} File;

typedef struct Directory {
  /*files has to be a double pointer so it can have multiple values and remember address*/
  File **files;
  /*num_files has to be a pointer so it can hold the address and the number*/
  int *num_files;
  char *name;
  /*num_dirs has to be a pointer so it can hold the address and the number*/
  int *num_dirs;
  /*directories has to be a double pointer so it can have multiple values and remember address*/
  struct Directory **directories;
  /*parent has to be a double pointer so it can have multiple values and remember address*/
  struct Directory **parent;
  /*root has to be a double pointer so it can have multiple values and remember address*/
  struct Directory **root;
} Fs_sim;
