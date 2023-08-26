#ifndef RAKIA_HAKIM_H
#define RAKIA_HAKIM_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

/**
 * struct list - linked list for environmental variables
 * @var: holds environmental variable string
 * @next: points to next node
 */
typedef struct list
{
	char *var;
	struct list *next;

} list_t;

int custom_setenv(list_t **env_list, char *var_name, char *dir_path);
void change_directory_only(list_t *env_list, char *current_dir);
int execute_cd(list_t *env_list, char *current_dir, char *target_dir, char *arg_str, int line_num);
int custom_cd(char **user_input, list_t *env_list, int command_num);
void custom_exit(char **user_command, list_t *env_list);
int execute_command(char **command, list_t *env_list, int command_num);
int custom_string_to_int(char *input_str);
int custom_exit_command(char **args, list_t *environment, int command_num, char **command_tokens);
size_t custom_get_line(char **buffer);
char *determine_full_path(char *command, list_t *env_list);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int custom_token_length(char *input, int position, char delimiter);
int token_count(char *input, char delimiter);
char *ignore_leading_delimiters(char *input, char delimiter);
char **_strtok(char *input, char *delimiter);
int custom_token_count(char *input_str, char delimiter);
char **custom_str_tok(char *input_str, char *delimiter);
size_t display_list(list_t *list);
list_t *add_to_end(list_t **head, char *data);
int delete_node_at_index(list_t **head, int index);
void free_linked_list(list_t *list);
void command_not_found(char *command, int command_num, list_t *env_list);
void report_cd_error(char *arg, int command_num, list_t *env_list);
void illegal_number_error(char *num_str, int command_num, list_t *env_list);
list_t *create_env_linked_list(char **env_vars);
int print_env(char **user_command, list_t *env_list);
void free_double_pointer(char **str);
char *custom_strdup(char *source, int exclude_bytes);
char *get_env(char *var_name, list_t *env_list);
int count_digits(int num);
char *int_to_string(int number);
void handle_ctrl_c(int signal_number);
int custom_build_in(char **command_tokens, list_t *env_list, int command_line_num, char **original_command);
char *remove_leading_space(char *str);
void handle_ctrl_D(int char_count, char *command, list_t *env_list);
int shell_prompt(char **environment);
char *_strcat(char *destination, char *source);
int _strcmp(char *str1, char *str2);
char *_strcpy(char *destination, char *source);
char *_strdup(char *source);
char *custom_ignore_spaces_newlines(char *str);
void handle_non_interactive(list_t *env_list);
int find_environment_variable(list_t *env_list, char *var_name);
int custom_unsetenv(list_t **env_list, char **command);
int _setenv(list_t **env_list, char **command);

#endif
