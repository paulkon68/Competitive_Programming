#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LINES 100


unsigned int shortest_line(int array[], unsigned int length, unsigned int m){

    unsigned int i, index=0;
    int min=INT_MAX;

    for(i=0; i<length; i++){
        if(min>array[i]) {
            min = array[i];
            index = i;
        }
    }

    array[index]++;

    return min;
}

void solve(int array[], unsigned int length, unsigned int m){

    unsigned int sl, i; 
    
    for(i = 0; i < m; i++){
        sl = shortest_line(array, length, m);
        printf("%d\n", sl);
    }
    

}

int main(void){
    
    int n, m;
    unsigned int i;
    int lines[MAX_LINES];

    scanf("%d%d", &n, &m);
    
    for(i=0; i<n; i++){
        scanf("%d", &lines[i]);
    }

    solve(lines, n, m);
    return 0;
}
