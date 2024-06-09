#include <cctype>
#include <iostream>
#include <pthread.h>
#include <bits/stdc++.h>
#include <string>

std::string phrase;
std::stringstream head;
std::string word;
bool bit[2] = {false, false};


void *alpha(void *);
void *numeric(void *);

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
      std::cerr << "USAGE: " << argv[0] << " <message string>" << std::endl;
      exit(-1);
    }
  
    phrase = argv[1];
    head << phrase;
    head >> word;
  
    //threads for processing of alpha and numeric
    pthread_t t1, t2;
    pthread_create(&t1, NULL, alpha, NULL);
    pthread_create(&t2, NULL, numeric, NULL);
  
    //wait
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}

void *alpha(void *arg) {
    do{
        //see what the first word is 
      if (isalpha(word[0]) || ispunct(word[0])) 
      {
        std::cout << "alpha: " << word << std::endl;
        bit[1] = true;
      }
      else{
        //set your flags
        bit[0] = true;
        bit[1] = false;

        if(!head){
            break;
        }
        while(bit[0]){
            continue;
        }
    }
    if (bit[1]){
        head >> word;
    }
}
    while (head); //when there is a word
    bit[0] = true;  
    pthread_exit(NULL);
}

void *numeric(void *arg) 
{
    do{
      if (isdigit(word[0])) 
      {
        std::cout << "numeric: " << word << std::endl;
        bit[1] = true;
      }
      else{
        bit[0] = false;
        bit[1] = false;
        if(!head){ //checking for more words
            break;
        }
        while(!bit[0]){
            continue;
        }
      }
      if(bit[1]){
        head >> word; //reading next word
      }
    }
    while(head)
    bit[0] = false;
    pthread_exit(NULL);
}
