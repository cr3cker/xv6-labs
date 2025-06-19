#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

char **split_words(char *line, int *cnt_out) {
  char **words = malloc(sizeof(char *) * MAXARG);
  int cnt = 0;

  char word[128];
  int word_len = 0;
  
  for (int i = 0; ; i++) {
    char c = line[i];

    if (c != ' ' && c != '\0') {
      if (word_len < sizeof(word) - 1) {
        word[word_len++] = c;
      }
    } else {
      if (word_len > 0) {
        word[word_len] = '\0';
        char *copy = malloc(word_len + 1);
        for (int j = 0; j <= word_len; j++) {
          copy[j] = word[j];
        }
        words[cnt++] = copy;
        word_len = 0;
      }
      if (c == '\0') break;
    }
  }

  *cnt_out = cnt;
  
  return words;
}

int main(int argc, char *argv[]) {
  char line[512];
  int len = 0;
  char byte;
  char **words;
  int cnt = 0;

  char **args = argv + 1;

  while (read(0, &byte, 1) == 1) {
    if (byte == '\n') {
      line[len] = '\0';
      words = split_words(line, &cnt);
      char *final_args[MAXARG];
      int i = 0;

      while (args[i] != 0 && i < MAXARG - 1) {
        final_args[i] = args[i];
        i++;
      }

      int j = 0;
      while (words[j] != 0 && i < MAXARG - 1) {
        final_args[i++] = words[j++];
      }

      final_args[i] = 0;
      
      if (fork() == 0) {
        exec(final_args[0], final_args); 
      } else {
        wait(0);
      }
      len = 0;
    } else if (len < sizeof(line) - 1) {
      line[len++] = byte;
    }
  }

  exit(0);
}
