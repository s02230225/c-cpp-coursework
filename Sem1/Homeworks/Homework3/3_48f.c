Support Compiler Explorer on Patreon!
×

C

C
1234567891011121314151617
        else if (c == 'r') a+=1;
        else a=0;
        if (a==4) anz=1;
    } while(c != EOF);
    (anz==1) ? printf("yes"): printf("no");
    return 0;
} 

x86-64 gcc 14.2
x86-64 gcc 14.2
-Wall -pedantic -lm 
fhpimcharpokdm

Program returned: 0
Program stdout
yes
x86-64 gcc 14.2 - 1037ms
