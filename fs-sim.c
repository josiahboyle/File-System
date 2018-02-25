/*
Josiah Boyle
jboyle10
113820861
307
*/

/*
This program simulates a file system with the functions mkfs, touch, mkdir, cd, ls, and pwd
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fs-sim.h"

/*This function allocates space and sets all values for file system to be made*/
void mkfs(Fs_sim *files) {
  
  /*makes a temp so that root address can be saved*/
  Fs_sim *temp = malloc(sizeof(Fs_sim));

  /*makes enough size for / string which is name of root*/
  files -> name = malloc(strlen("/")+1);

  /*makes room for files array*/
  files -> files = malloc(sizeof(files -> files));

  /*makes room for directories array*/
  files -> directories = malloc(sizeof(Fs_sim));

  /*makes room for root address*/
  files -> root = malloc(sizeof(Fs_sim));

  /*makes room for number of files*/
  files -> num_files = malloc(sizeof(int));

  /*makes room for number of directories*/
  files -> num_dirs = malloc(sizeof(int));

  /*sets parent to null because root has no parent*/
  files -> parent = NULL;
  
  *(files -> num_dirs) = 0;
  
  strcpy(files -> name, "/");
  
  *(files->num_files) = 0;

  /*saves root address in temp*/
  *temp = *files;

  /*saves temp into root*/
  *(files -> root) = temp;
  
}

/*This function makes a file and stores it in current directory*/
int touch(Fs_sim *files, const char arg[]) {

  /*i, inc, j, and l are all incrementing values and is_valid is used to return the final value*/
  int i = *(files -> num_files), inc = 0, is_valid = 1, j, l;

  char *tmp1, *tmp2;

  /*checks if any files already have the name that is being entered and exits once is_valid is 0 or it finishes incrementing*/
  while(is_valid != 0 && inc < i) {
    
    if(strcmp(arg, files -> files[inc] -> name) == 0)
      is_valid = 0;
    
    inc++;
  }

  /*resets inc so it can be used again*/
  inc = 0;

  /*checks if any directories already have the name that is being entered and exits once is_valid is 0 or it finishes incrementing*/
  while(is_valid != 0 && inc < *(files -> num_dirs)) {
    
    if(strcmp(arg, files -> directories[inc] -> name) == 0)
      is_valid = 0;
    
    inc++;
  }

  /*makes all checks for invalid file names and if its valid goes to else if it isnt the is_valid is set to zero and function exits*/
  if(is_valid == 0 || strcmp(arg, ".") == 0 || strcmp(arg, "..") == 0 || strchr(arg, '/') != NULL || strcmp(arg, "") == 0)
    is_valid = 0;
  
  else {

    /*reallocates memory for the files array so that it has enough for however amount of files in the files array*/
    files -> files = realloc(files -> files, sizeof(files -> directories[i] -> files) * (i + 1));
    
    files -> files[i] = malloc(sizeof(File));

    /*mallocs enough space for the string and null character*/
    files -> files[i] -> name = malloc(strlen(arg) + 1);
    
    strcpy(files -> files[i] -> name, arg);

    /*adds another file to the total files array*/
    *(files -> num_files) += 1;

    /*sorts the files array*/
    /*runs through all indexes*/
    for(l = 0; l < *(files -> num_files); l++) {

      /*runs through unsorted values*/
      for(j = l + 1; j < *(files -> num_files); j++) {

	/*stores both file names in temps so values can't be lost*/
        tmp1 = malloc(strlen(files -> files[l] -> name) + 1);

	tmp2 = malloc(strlen(files -> files[j] -> name) + 1);
	
	strcpy(tmp1, files -> files[l] -> name);
	
	strcpy(tmp2, files -> files[j] -> name);

	/*checks if tmp1 is greater than tmp2*/
	if(strcmp(tmp1, tmp2) > 0){

	  /*if it is it switches the indexes so the lesser value is earlier*/
	  files -> files[l] -> name = realloc(files -> files[l] -> name, strlen(tmp2) + 1);
	  
	  strcpy(files -> files[l] -> name, tmp2);
	  
	  files -> files[j] -> name = realloc(files -> files[j] -> name, strlen(tmp1) + 1);
	  
	  strcpy(files -> files[j] -> name, tmp1);
	  
	}
      }
    }
  }
  
  return is_valid;
}

/*This function makes a directory and stores it in current directory*/
int mkdir(Fs_sim *files, const char arg[]) {

  /*i, inc, j, and l are all incrementing values and is_valid is used to return the final value*/
  int i = *(files -> num_dirs), inc = 0, is_valid = 1, j, l;

  /*makes a temp so that parent address can be saved*/
  Fs_sim *temp = malloc(sizeof(Fs_sim));

  char *tmp1, *tmp2;

  /*checks if any files already have the name that is being entered and exits once is_valid is 0 or it finishes incrementing*/
  while(is_valid != 0 && inc < *(files -> num_files)) {
    
    if(strcmp(arg, files -> files[inc] -> name) == 0)
      is_valid = 0;
    
    inc++;
  }

  /*resets inc so it can be used again*/
  inc = 0;

  /*checks if any directories already have the name that is being entered and exits once is_valid is 0 or it finishes incrementing*/
  while(is_valid != 0 && inc < i) {
    
    if(strcmp(arg, files -> directories[inc] -> name) == 0)
      is_valid = 0;
    
    inc++;
  }

  /*makes all checks for invalid directory names and if its valid goes to else if it isnt the is_valid is set to zero and function exits*/
  if(is_valid == 0 || strcmp(arg, ".") == 0 || strcmp(arg, "..") == 0 || strchr(arg, '/') != NULL || strcmp(arg, "") == 0)
    is_valid = 0;
  
  else {

    /*reallocates memory for the directories array so that it has enough for however amount of directories are in the directories array*/
    files -> directories[i] = realloc(files -> directories[i], sizeof(Fs_sim) * (i + 1));

    /*mallocs enough space for the string and null character*/
    files -> directories[i] -> name = malloc(strlen(arg) + 1);

    /*makes room for the files array in the subdirectory*/
    files -> directories[i] -> files = malloc(sizeof(files -> directories[i] -> files));

    /*makes room for the directories array in the subdirectory*/
    files -> directories[i] -> directories = malloc(sizeof(Fs_sim));

    /*makes room for the parent address to be stored in the subdirectory*/
    files -> directories[i] -> parent = malloc(sizeof(Fs_sim));

    /*makes room for the root address to be stored in the subdirectory*/
    files -> directories[i] -> root = malloc(sizeof(Fs_sim));

    /*makes room for the files array in the subdirectory*/
    files -> directories[i] -> num_files = malloc(sizeof(int));

    /*makes room for the files array in the subdirectory*/
    files -> directories[i] -> num_dirs = malloc(sizeof(int));
    
    *(files -> directories[i] -> num_dirs) = 0;
    
    strcpy(files -> directories[i] -> name, arg);
    
    *(files -> directories[i] -> num_files) = 0;

    /*saves directory address in temp*/
    *temp = *files;

    /*stores temp in the parent so that address of parent directory will be remembered in subdirectory*/
    files -> directories[i] -> parent[0] = temp;

    /*stores root address in subdirectory root address will never change*/
    *(files -> directories[i] -> root) = *(files -> root);

    /*increments number of directories up*/
    *(files -> num_dirs) += 1;

    /*sorts the directories array*/
    /*runs through all indexes*/
    for(l = 0; l < *(files -> num_dirs); l++) {

      /*runs through unsorted values*/
      for(j = l + 1; j < *(files -> num_dirs); j++) {

	/*stores both file names in temps so values can't be lost*/
        tmp1 = malloc(strlen(files -> directories[l] -> name) + 1);

	tmp2 = malloc(strlen(files -> directories[j] -> name) + 1);
	
	strcpy(tmp1, files -> directories[l] -> name);
	
	strcpy(tmp2, files -> directories[j] -> name);

	/*checks if tmp1 is greater than tmp2*/
	if(strcmp(tmp1, tmp2) > 0){

	  /*if it is it switches the indexes so the lesser value is earlier*/
	  files -> directories[l] -> name = realloc(files -> directories[l] -> name, strlen(tmp2) + 1);
	  
	  strcpy(files -> directories[l] -> name, tmp2);
	  
	  files -> directories[j] -> name = realloc(files -> directories[j] -> name, strlen(tmp1) + 1);
	  
	  strcpy(files -> directories[j] -> name, tmp1);
	}
      }
    }
  }
  return is_valid;
}

/*This function changes the current directory to the root, parent, or subdirectory*/
int cd(Fs_sim *files, const char arg[]) {

  /*i, inc are incrementing values, is_valid is used to return the final value, and found is used to tell whether name is found in subdirectories*/
  int i = *(files -> num_dirs), inc = 0, is_valid = 1, found = 0;

  /*checks if arg is equal to "." and if it is the function doesn't do anything because its already in current directory*/
  if(strcmp(arg, ".") == 0)
    is_valid = 1;

  /*checks if arg has the character '/' and sets is_valid to zero if the arg is not only "/" because if it is then its just the root*/
  else if(strchr(arg, '/') != NULL && strcmp(arg, "/") != 0)
    is_valid = 0;

  /*checks if arg is equal to ".." because if it is it sets the parent address equal to the current address*/
  else if(strcmp(arg, "..") == 0)
    *files = **(files -> parent);

  /*checks if arg is equal to "/" because if it is it sets the root address equal to the current address*/
  else if(strcmp(arg, "/") == 0)
    *files = **(files) -> root;

  /*if it gets here that means arg has to be a name so this checks if the name is a subdirectory*/
  else {

    /*runs through directories array looking for a name matching the arg if it does match it exits the while
      by setting found to 1 and then stores the address of the subdirectory to the current directory*/
    while(found != 1 && inc < i) {
      
      if(strcmp(arg, files -> directories[inc] -> name) == 0) {
	
	found = 1;
	
	*files = *(files -> directories[inc]);
      }
      else {
	
	inc++;
      }
    }

    /*if the while loop never found a matching directory then found will be zero and the function will need to return zero*/
    if(found == 0)
      is_valid = 0;
  }
  
  return is_valid;
}

/*This function prints out the files and directory names in increasing order in the current directory*/
int ls(Fs_sim *files, const char arg[]) {

  /*i, inc, and j are incrementing values, is_valid is used to return the final value, and found is used to 
    tell whether name is found in subdirectories or files*/
  int i = 0, j = 0, inc = 0, is_valid = 0, found = 0;

  /*used to temporarily hold the address of the directory ls tries to print*/
  Fs_sim *print_directory = malloc(sizeof(Fs_sim));

  /*checks if arg is equal to "/" and if it is root address will be stored into print directory to be printed later and sets is_valid to 1*/
  if(strcmp(arg, "/") == 0) {
    
    is_valid = 1;
    
    print_directory = *(files -> root);
  }

  /*checks if arg contains '/' and if it does function sets is_valid to 0 and exits*/
  else if(strchr(arg, '/') != NULL)
    is_valid = 0;

  /*checks if arg is equal to "." and if it is files address will be stored into print directory to be printed later and sets is_valid to 1*/
  else if(strcmp(arg, ".") == 0 || strcmp(arg, "") == 0) {
    
    is_valid = 1;
    
    print_directory = files;
  }

  /*checks if arg is equal to ".." and if it is parent address will be stored into print directory to be printed later and sets is_valid to 1*/
  else if(strcmp(arg, "..") == 0) {
    
    is_valid = 1;
    
    print_directory = *(files -> parent);
  }

  /*if function gets here that means the arg must be a name or a none existing directory so it will run though the files and subdirectories arrays*/
  else {

    /*while loop is used to find if the arg is a file name and if it is it sets is_valid to one and sets found to 
      2 so that the function knows its a file and not a directory*/
    while(found != 2 && inc < *(files -> num_files)) {
      
      if(strcmp(arg, files -> files[inc] -> name) == 0) {
      
	found = 2;
	
	is_valid = 1;
      }
      else {
	
	inc++;
      }
    }

    /*only goes here if arg is not a file name*/
    if(is_valid != 1) {

      /*resets inc*/
      inc = 0;

      /*checks if arg equals directory name and if it is found sets found to 1 and is_valid to 1 then stores the 
	subdirectory address in print directory to be printed later*/
      while(found != 1 && inc < *(files -> num_dirs)) {
	
	if(strcmp(arg, files -> directories[inc] -> name) == 0) {
      
	  found = 1;
	  
	  print_directory = files -> directories[inc];
	  
	  is_valid = 1;
	}
	else {
	  
	  inc++;
	}
      }
    }
  }

  /*only enters here if the function is now valid and the reason it is valid is not a file*/
  if(is_valid == 1 && found != 2) {

    /*keeps looping until both the subdirectories array and files array have no more values*/
    while(j < *(print_directory -> num_dirs) || i < *(print_directory -> num_files)) {

      /*prints the next subdirectoy name in array if the files array has no more values and increments the subdirectories array*/
      if(i >= *(print_directory -> num_files)) {
	
        printf("%s/\n", print_directory -> directories[j] -> name);
	
        j++;
      }

      /*prints the next file name in array if the subdirectories array has no more values and increments the files array*/
      else if(j >= *(print_directory -> num_dirs)) {
	
	printf("%s\n", print_directory -> files[i] -> name);
	
	i++;
      }

      /*prints the next subdirectoy name in array the subdirectory name is less than the file name and increments subdirectories array*/
      else if(strcmp(print_directory -> directories[j] -> name, print_directory -> files[i] -> name) < 0) {
	
	printf("%s/\n", print_directory->directories[j]->name);
	
	j++;
      }

      /*prints the next file name and increments it because the file name was less than the directory name*/
      else {
	
	printf("%s\n", print_directory -> files[i] -> name);
	
	i++;
      }
    }
  }
  
  return is_valid;
}

/*This function prints out the path of the current directory*/
void pwd(Fs_sim *files) {

  /*path is used to store all the names of the parent directories until finished*/
  File *path = malloc(sizeof(files -> files));

  /*temp is used to go through directories without accidently changing directories completely*/
  Fs_sim *temp = malloc(sizeof(Fs_sim));

  /*i and j are incrementing values, done is used to know when root directory was found*/
  int i = 0, done = 0, j;

  /*checks if current directory is already the root and just prints "/"*/
  if(strcmp(files -> name, "/") == 0)
    printf("%s", files -> name);

  /*if it is not the root then it goes here*/
  else {

    /*stores files in temp so files can't be accidently changed*/
    temp = files;

    /*keeps going upstream until root is found*/
    while(done != 1){

      /*keeps making room for the path to hold names of each directory read*/
      path = realloc(path, sizeof(File)*(i+1));

      /*puts the path variable in correct index*/
      path += i;

      /*makes enough room for directory name in path*/
      path -> name = malloc(strlen(temp -> name) + 1);
      
      strcpy(path -> name, temp -> name);

      /*checks if in root so the function can exit*/
      if(strcmp(temp -> name, "/") == 0)
	done = 1;

      /*if we aren't in root then it sets current directory to the parent*/
      else 
	temp = *(temp -> parent);

      /*sets path variable back to the root index*/
      path -= i;
      
      i++;
    }

    /*sets path to be in the index right before the root directory name so it doesn't print just "/"*/
    path += (i - 2);

    /*iterates through the rest of the path and prints the names in correct order*/
    for(j = 0; j < (i - 1); j++) {

      /*puts "/" before string to match general format*/
      printf("/%s", path -> name);

      /*increments backwards because the path was set in reverse order*/
      path--;
    }
  }

  /*makes a next line in the end so that the path matches general format*/
  printf("\n");
}
