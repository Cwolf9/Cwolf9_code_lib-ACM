#include <bits/stdc++.h>
using namespace std;

#define AC 0
#define WA 1
#define ERROR -1

int spj(FILE *input, FILE *user_output);

void close_file(FILE *f){
    if(f != NULL){
        fclose(f);
    }
}

int main(int argc, char *args[]){
    FILE *input = NULL, *user_output = NULL;
    int result;
    if(argc != 3){
        return ERROR;
    }
    input = fopen(args[1], "r");
    user_output = fopen(args[2], "r");
    if(input == NULL || user_output == NULL){
        close_file(input);
        close_file(user_output);
        return ERROR;
    }

    result = spj(input, user_output);

    close_file(input);
    close_file(user_output);
    return result;
}

int spj(FILE *input, FILE *user_output){
    
      double x, y, z;
      while(fscanf(input, "%lf %lf", &x, &y) != EOF){
          fscanf(user_output, "%lf", &z);
          if(fabs(x+y - z) > 1e-6) return WA;
      }
      return AC;

}