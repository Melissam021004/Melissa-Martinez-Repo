// D4E3E5

#include <stdio.h>

int main(){

  
  //Prompting denominations
  printf("How many denominations? ");
  int total_denoms = 0;;
  
  
  //Scanning denoms and accounting for potential input error
  if(scanf("%d", &total_denoms) < 1){
    fprintf(stderr, "Invalid input\n");
    return 1;
  }
  
  
  //Creating null arrays to store denomination values
  int MAX_DENOMINATIONS = 20;
  char identifiers[MAX_DENOMINATIONS];
  int values[MAX_DENOMINATIONS];
  int total[MAX_DENOMINATIONS];
  int total_count[MAX_DENOMINATIONS];
  
  
  //Prompting for identifiers and values and storing them
  for(int i = 0; i < total_denoms; i++){
    
    printf("Enter coin identifier and value in cents: ");
    
    //Accounting for potential input errors
    if(scanf(" %c%d", &identifiers[i], &values[i]) < 2){
      fprintf(stderr, "Invalid input\n");
      return 1;
      break;
    }
  }
  
  
  //Setting appropriate lists to 0
  for(int i = 0; i < total_denoms; i++){
    total_count[i] = 0;
    total[i] = 0;
  }
  
  
  //Prompting for the first command
  printf("Enter a command: ");
  char command;
  char denom;
  int count;
  float coll_total = 0.0;
  
  //Prompting and executing commands
  while((scanf(" %c", &command)) == 1){
    
    switch(command){
      
    case 'a':
      if(scanf(" %c %d", &denom, &count) == 2){
	for(int i = 0; i < total_denoms; i++){
	  if(denom == identifiers[i]){
	    total[i] += values[i] * count;
	    coll_total += (values[i] * count)/100.0;
	    total_count[i] += count;
	    break;
	  }
	  else if (i == total_denoms-1){
	    fprintf(stderr, "Unknown coin identifier\n");
	    return 2;
	  }
	}
      }
      else{
	fprintf(stderr, "Invalid input\n");
        return 1;
      }
      
      break;
      
    case 'r':
      if(scanf(" %c %d", &denom, &count) == 2){
	for(int i = 0; i < total_denoms; i++){
	  if(denom == identifiers[i]){
	    total[i] -= values[i] * count;
	    coll_total -= (values[i] * count)/100.0;
	    total_count[i] -= count;
	    break;
	  }
	  else if (i == total_denoms-1){
	    fprintf(stderr, "Unknown coin identifier\n");
	    return 2;
	  }
	}
      }
      else{
	fprintf(stderr, "Invalid input\n");
	return 1;
      }
      break;
      
    case 's':
      printf("Identifier,Face Value,Count,Total Value\n");
      for(int i = 0; i < total_denoms; i++){
	
	printf("%c,%d,%d,%d\n", identifiers[i], values[i], total_count[i], total[i]);
	
      }
      printf("Overall value of collection: $%.2f\n", coll_total);
      break;
        
    case 'q':
      printf("Bye!\n");
      return 0;
      break;

    //Invalid command  
    default:
      fprintf(stderr, "Invalid command\n");
      return 3;
      break;
      
    }
    printf("Enter a command: ");
  }

  //
  printf("Bye!\n");
  return 0;
  
}
