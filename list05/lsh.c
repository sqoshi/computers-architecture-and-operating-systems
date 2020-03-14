#include <sys/wait.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>

#define Delimiter " \t\r\n\a"

char *builtin_names[] = {
  "exit",
  "cd"
};

int sh_exit(char **args){
    return 0;
}

int sh_cd(char **args){
    if (args[1] == NULL) {
        fprintf(stderr, "NULL");
    } 
    else {
        if (chdir(args[1]) != 0) {
            perror("error");
        }
    }
    return 1;
}

int (*builtin_func[]) (char **) = {
  &sh_exit,
  &sh_cd
};


char *read_line()
{
  char *line = NULL;
  ssize_t bufsize = 0; 
  
  if(getline(&line, &bufsize, stdin)>0)
      return line; 
  else 
      exit(1);
}

char **split_line(char *line)
{
  int tableSize = 64, position = 0;
  char **args = malloc(tableSize * sizeof(char*));
  char *word, **backup;
  char c;
  if (!args) {
    fprintf(stderr, "error\n");
    exit(EXIT_FAILURE);
  }

  word = strtok(line, Delimiter);
  while (word != NULL) {
    args[position] = word;
    position++;

    if (position >= tableSize) {
      tableSize = tableSize*2;
      backup = args;
      args = realloc(args, tableSize * sizeof(char*));
      if (!args) {
		    free(backup);
        fprintf(stderr, "error\n");
        exit(EXIT_FAILURE);
      }
    }
    word = strtok(NULL, Delimiter);
  }
  args[position] = NULL;
  return args;
}

int ampersand(char **args) {
    int i;
    for(i = 1; args[i] != NULL; i++);
    if(args[i-1][0] == '&') {
        args[i-1] = NULL;
        return 1;
    } else
        return 0;
}
void func (int signum){
wait(NULL);
}
int sh_launch(char **args)
{
  pid_t pid, wpid;
  int status;
  int bg=0;
  bg = ampersand(args);
  pid = fork();
  
  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("lsh");
  } else {
   signal(SIGCHLD, func);
   if(!bg){
    do {
      wpid = waitpid(pid, &status, WUNTRACED);

    }
    while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
  }

  return 1;
}

int sh_builtin(char **args){
    
    if (args[0] == NULL) {
        return 1;
    }
    
    int length = sizeof(builtin_names) / sizeof(builtin_names[0]), i, counter = 0;
    for(i = 0; i < length; i++){
        if(strcmp(args[0], builtin_names[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }
    return 2;
}

void sh_loop(){
    char *line;
    char **args;
    int status;
    char cwd[1024]; 

  do {
    getcwd(cwd, sizeof(cwd)); 
    printf("\n \x1b[38;5;43m Dir: %s \x1b[0m\n", cwd); 
    line = read_line();
    args = split_line(line);
    status = sh_builtin(args);
        if(status == 2){
            status = sh_launch(args);
        }
        free(args);
        free(line);
  } while (status);
}


void intHandler(int state) {
fprintf(stderr, "\x1b[38;5;12m Ctrl-D to exit \x1b[0m");
    sh_loop();

}

int main(int argc, char **arg)
{

    signal(SIGINT, intHandler);
    sh_loop();
 
  return EXIT_SUCCESS;
}
