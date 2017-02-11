    #include<stdio.h>  
    #include<stdlib.h>  
    #include<string.h>  
    #include <iostream>
    using namespace std; 
    int main()  
    {  
        char ip_str[] = "192.168.1.250";  
        int ip_arr[4] ;  
        char * s = strtok(ip_str, ".");  
        int i=0;  
        while(s)  
        {  
            printf("%s\n",s);  
            ip_arr[i] = int(*s);  
            s = strtok(NULL, ".");  
            i++;  
        }  
      
       // for(i=0; i<2; i++)  
       //     printf("%s\n",ip_arr[i]);  
       cout<<sizeof(ip_arr)/sizeof(ip_arr[0])<<endl;
    }  
