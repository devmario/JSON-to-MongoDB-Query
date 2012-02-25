//
//  main.c
//  CVS_To_MongoDBQuery
//
//  Created by wonhee jang on 12. 2. 25..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

int main (int argc, const char * argv[])
{
    if(argc != 4) {
        printf("다음과 같이 사용하세요.\nJSON_to_MongoDBQuery \"prefix\" \"endfix\" \"json파일\"\n");
        return 1;
    }
    FILE* f = fopen(argv[3], "rb");
    if(f == NULL) {
        printf("%s파일이 존재하지 않습니다.\n", argv[3]);
        return 1;
    }
    
    fseek(f, 0, SEEK_END);
    size_t s = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* inbuf = calloc(1, s + 1);
    fread(inbuf, s, 1, f);
    fclose(f);
    
    cJSON* js = cJSON_Parse(inbuf);
    
    if(1) {
        FILE *output;
        output = popen("more", "w");
        for(int i = 0; i < cJSON_GetArraySize(js); i++) {
            char* code = cJSON_PrintUnformatted(cJSON_GetArrayItem(js, i));
            fprintf(output, "%s%s%s\n", argv[1], code, argv[2]);
            free(code);
        }
        pclose(output);
    }
    
    cJSON_Delete(js);
    free(inbuf);
    
    return 0;
}

