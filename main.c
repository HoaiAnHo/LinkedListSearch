#include <stdio.h>
#include<stdlib.h>

// linked list data structure
struct node {
  char *word;
  int length;
  struct node *next;
};

struct node *head = NULL;
struct node *prev = NULL;
struct node *cur = NULL;

// compare two words, case-sensitive
int compare(char* str1, char* str2)
{
  int i=0;
  while ((*(str1+i) != '\0') && (*(str2+i) != '\0'))
  {
    if (*(str1+i) > *(str2+i))
    {
      return 1;
    }
    else if (*(str1+i) < *(str2+i))
    {
      return -1;
    }
    i++;
  }
  return 0;
}

// case insensitive compare, 32 difference
int compare_insen(char* str1, char* str2)
{
  int i=0;
  while ((*(str1+i) != '\0') && (*(str2+i) != '\0'))
  {
    // STEP 1: ASCII CONVERSION
    int a = (int)*(str1+i);
    int b = (int)*(str2+i);
    // convert lowercase to uppercase for str1
    if (a >= 97 && a <= 122){
      if (b >= 97 && b <= 122){
        // both are lowercase
        a = a - 32;
        b = b - 32;
      }
      else {
        // only str1 is converted
        a = a - 32;
      }
    }
    // convert lowercase to uppercase for str2, not for str1
    else if (b >= 97 && b <= 122){
      b = b - 32;
    }
    // STEP 2: COMPARE VALS
    if (a > b){ return 1;}
    else if (a < b){ return -1;}
    i++;
  }
  return 0;
}

// search function
struct node *search(char *searched, int sensitive) {
  cur = head;
  prev = NULL;
  
  while (cur != NULL){
    int result = -1;
    if (sensitive == 1){
      result = compare_insen(searched, cur->word);
    }
    else {
      result = compare(searched, cur->word);
    }
    
    if (result > 0){
      prev = cur;
      cur = cur->next;
    }
    else if (result == 0){
      return cur;
    }
    else{
      return NULL;
    }
  }
  return NULL;
}

// insert word function (automatic alphabetization)
int insert(char *given, int word_len){
  struct node *new_node = (struct node*) malloc(sizeof(struct node));
  new_node->word = given;
  new_node->length = word_len;
  if (head != NULL) {
  }

  
  if (head == NULL) {
    head = new_node;
  }
  else {
    // compare with each node in the list
    cur = head;
    prev = NULL;
    while (1==1){
      if (compare(new_node->word, cur->word) >= 0){
        
        if (cur->next == NULL) {
          cur->next = new_node;
          return 0;
        }
        else{
          prev = cur;
          cur = cur->next;
        }
      }
      else {
        if (prev == NULL) {
          head = new_node;
          new_node->next = cur;
          return 0;
        }
        else {
          prev->next = new_node;
          new_node->next = cur;
          return 0;
        }
      }
    }
  }
  return 0;
}

// our own string token
void word_split(char *sen){
  int i = 0;
  while (sen[i] != '\0'){
    char *new_word = malloc(5 * sizeof(char));
    int char_count = 0;
    while (sen[i] != ' ' && sen[i] != '\0'){
      if (char_count < 4) {
        new_word[char_count] = *(sen+i);
        char_count++;
        i++;
      }
      else {
        char_count++;
        i++;
      }
    }
    if (sen[i] == ' ') {i++;}
    if (sen[i] == '\0') {char_count--;}
    insert(new_word, char_count);
    if (head->next != NULL) {
    }
  }
  struct node *temp = head;
  while (temp != NULL){
    temp = temp->next;
  }
}

// deleting current linked list
int delete_list(){
  prev = NULL;
  cur = head;
  while (cur->next != NULL){
    prev = cur;
    cur = cur->next;
    free(prev->word);
    free(prev);
  }
  return 0;
}

int main(void) {
  // output user prompt, grab input
  // assume that the string is limited for assignment's sake
  char sentence[100];
  printf("Input a sentence: ");
  fgets(sentence, sizeof(sentence), stdin);
  
  // linked list and alphabetical sorting
  word_split(sentence);
  
  // // create a simple menu to perform given functions on the linked list
  while(1==1){
    char command[150];
    printf("================\nMENU OPTIONS:\nE --- Exit Program\nS --- Search (case-sensitive)\nI --- Search (case-insensitive)\nA --- Add new entries\nD --- Delete Current Linked List\n================\n> ");
    fgets(command, sizeof(command), stdin);
    if (*(command) == 'E'){
      printf("End Program.\n");
      delete_list();
      head = NULL;
      exit(0);
    }
    else if (*(command) == 'I'){
      char word[100];
      printf("Look up a word: ");
      fgets(word, sizeof(word), stdin);
      struct node *result = search(word, 1);
      if (result != NULL) {
        printf("Found: %s\n", result->word);
      }
      else {
        printf("Word not found.\n");
      }
    }
    else if (*(command) == 'S'){
      char word[100];
      printf("Look up a word: ");
      fgets(word, sizeof(word), stdin);
      struct node *result = search(word, 0);
      if (result != NULL) {
        printf("Found: %s\n", result->word);
      }
      else {
        printf("Word not found.\n");
      }
    }
    else if (*(command) == 'A'){
      char new_sen[100];
      printf("Input a sentence: ");
      fgets(new_sen, sizeof(new_sen), stdin);
      word_split(new_sen);
      printf("Entry added to the list\n");
    }
    else if (*(command) == 'D'){
      printf("Deleted list.\n");
      delete_list();
      head = NULL;
    }
    
    
  }
  return 0;
}
