#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
void myPrint(char *msg){
    write(STDOUT_FILENO, msg, strlen(msg));
}
void print_error(){
        myPrint("An error has occurred\n");
}
int count_colons(char *str){
    int count = 0;
    for (int i = 0; i < strlen(str); i++){
        if (str[i] == ';'){
            count++;
        }
    }
    return count;
}
int count_entries(char * command){
    int in_word = 0;
    int num_words = 0;
    if (command[0] != '\t' && command[0] != '\n' && command[0] != ' '){
        in_word = 1;
        num_words++;
    }
    for (int i = 0; i < strlen(command); i++){
        if (command[i] == '\t' || command[i] == '\n' || command[i] == ' '){
            in_word = 0;
        }
        else if (!in_word){
            in_word = 1;
            num_words++;
        }
    }
    return num_words;
}
void run_redirect(char *command, char *arg_list[], char *dest){
    int std_original = dup(STDOUT_FILENO);
    int fd_check = open(dest, O_RDONLY);
    if (fd_check != -1){
        close(fd_check);
        print_error();
    }
    else{
        close(fd_check);
        // make sure you can create a file at dest
        int fd = open(dest, O_CREAT | O_WRONLY, 0666);
        if (fd == -1){
            close(fd);
            print_error();
            return;
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        // call execvp
        pid_t processid = fork();
        if (processid == 0){
            if(execvp(command, arg_list) == -1){
                print_error();
            }
            exit(0);
        }
        else{
            wait(NULL);
            dup2(std_original, STDOUT_FILENO);
            close(std_original);
        }
    }
}
void run_advanced(char *command, char *arg_list[], char *dest){
   
    int fd_dest = open(dest, O_RDWR);
    int std_original = dup(STDOUT_FILENO);
    int fd_temp = open("temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    // read from dest into temp
    char buff[100];
    ssize_t num_bytes = read(fd_dest, buff, sizeof(buff));
    while(num_bytes != 0 && num_bytes != -1){
        write(fd_temp, buff, num_bytes);
        num_bytes = read(fd_dest, buff, sizeof(buff));
    }
    // close and reopen dest to overwrite
    close(fd_dest);
    fd_dest = open(dest, O_RDWR | O_TRUNC | O_CREAT , 0666);
    // make sure you can create a file at dest
    if (fd_dest == -1){
        close(fd_dest);
        close(std_original);
        close(fd_temp);
        print_error();
        return;
    }
    dup2(fd_dest, STDOUT_FILENO);
    //start writing to beginning of dest and call execvp
    pid_t processid = fork();
    if (processid == 0){
        if(execvp(command, arg_list) == -1){
            print_error();
        }
        exit(0);
    }
    else{
        wait(NULL);
    }
   
    // switch standard ouput back
    dup2(std_original, STDOUT_FILENO);
    close(std_original);
    // write from temp to dest
    lseek(fd_temp, 0, SEEK_SET);
    num_bytes = read(fd_temp, buff, sizeof(buff));
    while (num_bytes != 0 && num_bytes != -1){
        write(fd_dest, buff, num_bytes);
        num_bytes = read(fd_temp, buff, sizeof(buff));
    }
    close(fd_dest);
    close(fd_temp);
    remove("temp.txt");
}
void run_default(char *command, char *arg_list[], int num_args){
    if (!strcmp(command, "exit")){
        if (num_args > 1){
            print_error();
        }
        else{
            exit(0);
        }
    }
    else if(!strcmp(command, "cd")){
        if (num_args == 1){
            (chdir(getenv("HOME")));
        }
        else if(num_args == 2){
            if (chdir(arg_list[1]) != 0){
                print_error();
            }
        }
        else{
            print_error();
        }
    }
    else if (!strcmp(command, "pwd")){
        if ((num_args) > 1){
            print_error();
        }
        else{
            char directorybuff[4096];
            char *directorypointer = getcwd(directorybuff, 4096);
            strcat(directorypointer, "\n");
            myPrint(directorypointer);
        }
    }
    else{
        pid_t processid;
        processid = fork();
        if (processid == 0){
            int code = execvp(command, arg_list);
            if (code == -1){
                print_error();
            }
            exit(0);
        }
        else{
            wait(NULL);
        }
    }
}
void handle_command(char *command){
    // create fresh string for command that is at most 512 characters
    char *fresh_command = (char *)calloc(1000, sizeof(char));
    strcpy(fresh_command, command);
    // add spaces before and after any redirect symbols in the string
    int redirect_count = 0;
    int length = strlen(fresh_command);
    char *ptr = strstr(fresh_command, ">");
    while (ptr){
        redirect_count++;
        ptr++;
        ptr = strstr(ptr, ">");
    }
    char with_spaces[length + (4 * redirect_count) + 1];
    int i = 0;
    int j = 0;
    while(fresh_command[i] != '\0'){
        if (fresh_command[i] != '>'){
            with_spaces[j] = fresh_command[i];
            i++;
            j++;
        }
        else{
            if (fresh_command[i + 1] == '+'){
                with_spaces[j] = ' ';
                with_spaces[j+1] = '>';
                with_spaces[j+2] = '+';
                with_spaces[j+3] = ' ';
                j += 4;
                i += 2;
            }
            else{
                with_spaces[j] = ' ';
                with_spaces[j+1] = '>';
                with_spaces[j+2] = ' ';
                j += 3;
                i += 1;
            }
        }
    }
    with_spaces[j] = '\0';
    strcpy(fresh_command, with_spaces);
    int num_entries = count_entries(with_spaces);
    // skip if there are no entries
    if(num_entries == 0){
        return;
    }
    char *entries[num_entries + 1];
    char *entry = strtok(fresh_command, " \t");
    int ent_count = 0;
    while(entry){
        entries[ent_count] = entry;
        ent_count++;
        entry = strtok(NULL, " \t");
    }
   
    // now we check for redirects in entry array
    int red_count = 0;
    int red_ind = -1;
    int redirect = 0;
    int advancedred = 0;
   
    for (int i = 0; i < num_entries; i++){
        if (strcmp(entries[i], ">") == 0){
            redirect = 1;
            red_ind = i;
            red_count++;
        }
        if (strcmp(entries[i], ">+") == 0){
            advancedred = 1;
            red_ind = i;
            red_count++;
        }
    }
    // check for bad redirection edge cases
    if (redirect || advancedred){ // can't redirect a built-in command
        for (int i = 0; i < num_entries; i++){
            if (strcmp(entries[i], "exit") == 0 || strcmp(entries[i], "pwd") == 0 || strcmp(entries[i], "cd") == 0){
                print_error();
                return;
            }
        }
    }
    if (red_count > 1){ // check for if there are somehow two redirects
        print_error();
        return;
    }
    if (red_ind == (num_entries - 1)){ // the redirection symbol can't be the last entry
        print_error();
        return;
    }
    // redirection can be done safely
    if (redirect){ // redirection found
        char *arg_list[red_ind + 1];
        for (int i = 0; i < red_ind; i++){
            arg_list[i] = entries[i];
            arg_list[red_ind] = NULL;
        }
        run_redirect(entries[0], arg_list, entries[red_ind + 1]);
    }
    else if (advancedred){ // advanced redirection found
        char *arg_list[red_ind + 1];
        for (int i = 0; i < red_ind; i++){
            arg_list[i] = entries[i];
            arg_list[red_ind] = NULL;
        }
        run_advanced(entries[0], arg_list, entries[red_ind + 1]);
    }
    else{ // no redirection needed
        entries[num_entries] = NULL;
        run_default(entries[0], entries, num_entries);
    }
}
int main(int argc, char *argv[]){
    // interactive mode
    if (argc == 1){
        while(1){
            char line[514];
            myPrint("myshell> ");
            char *input = fgets(line, 513, stdin);
            if (!input){
                exit(0);
            }
            else{
                if (strlen(line) >= 512){ // check for lines that are too long and handle
                    myPrint(input); 
                    int c = getc(stdin);
                    while(c != '\n'){
                        putc(c, stdout);
                        c = getc(stdin);
                    }
                        putc('\n', stdout);
                        fflush(stdout);
                        print_error();
                }
                else{ // line is not too long; check if line is empty
                    int empty = 1; // assume empty
                    for (int i = 0; i < strlen(line); i++){
                        if(line[i] != ' ' && line[i] != '\n' && line[i] != '\t'){
                            empty = 0;
                            break;
                        }
                    }
                    if (empty){
                        // do nothing
                    }
                    else{
                        if (line[strlen(line) - 1] == '\n'){ // if line ends with newline, write over it
                            line[strlen(line) - 1] = '\0';
                        }
                        int colons = count_colons(line); // count the colons to reveal how many commands there are
                        char *commands[colons + 1];
                        char *cmd = strtok(line, ";");
                        int count = 0;
                        while(cmd){
                            commands[count] = cmd;
                            count++;
                            cmd = strtok(NULL, ";");
                        }
                        for (int i = 0; i < count; i++){ // handle each command in the line
                            handle_command(commands[i]);
                        }
                    }
                }
            }
        }
    }   
    if (argc > 2){ // prevent more than one argument being passed to myshell
        print_error();
        exit(0);
    }
   
    // batch mode
    char cmd_buff[514];
    FILE *f;
    if (!(f = fopen(argv[1], "r"))){ // make sure batch file exists
        print_error();
    }
    else{ // batch file exists
        while(fgets(cmd_buff, 513, f)){ // fetch line
            if (strlen(cmd_buff) >= 512){ // check for lines that are too long and handle
                myPrint(cmd_buff);
                int c = getc(f);
                while(c != '\n' && c != '\0' && c != EOF){
                    putc(c, stdout);
                    c = getc(f);
                }
                    putc('\n', stdout);
                    fflush(stdout);
                    print_error();
            }
            else{ // line is not too long; check if line is empty
                int empty = 1; // assume empty
                for (int i = 0; i < strlen(cmd_buff); i++){
                    if(cmd_buff[i] != ' ' && cmd_buff[i] != '\n' && cmd_buff[i] != '\t'){
                        empty = 0;
                        break;
                    }
                }
                if (empty){
                    // do nothing
                }
                else{
                    myPrint(cmd_buff);
                    if (cmd_buff[strlen(cmd_buff) - 1] == '\n'){ // if line ends with newline, remove it
                        cmd_buff[strlen(cmd_buff) - 1] = '\0';
                    }
                    int colons = count_colons(cmd_buff); // count the colons to reveal how many commands there are
                    char *commands[colons + 1];
                    char *cmd = strtok(cmd_buff, ";");
                    int count = 0;
                    while(cmd){
                        commands[count] = cmd;
                        count++;
                        cmd = strtok(NULL, ";");
                    }
            
                    for (int i = 0; i < count; i++){ // handle each command in the line
                        handle_command(commands[i]);
                    }
                }
            }
        }
    }
}
