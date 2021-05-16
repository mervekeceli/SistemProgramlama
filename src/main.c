#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "jval.h"
#include "jrb.h"
#include "dllist.h"

int main(int argc, char *argv[])
{
   IS kilit;
   IS giris;
  JRB kriptoTree;
  JRB tmp;
  Jval jvkod;
  Jval jvkelime;  
  JRB cikisKelimesi;
  
  char *geciciKelime;
  char kelime[500];
  char kod[500];
  
  // Yeni bir dosya okuyucusu tanımla
  kilit = new_inputstruct(".kilit"); 
  giris = new_inputstruct(argv[2]);//               ./kripto -e giris_metin cikis_metin
  FILE *dosya =fopen(argv[3],"w");
  kriptoTree = make_jrb();
                             
       
  while(get_line(kilit) >= 0) {
	  
    if(kilit->NF != 1) {
      for(int i = 0; i < kilit->NF; i++) {
        geciciKelime = strtok(kilit->fields[i], ":");
        geciciKelime = strtok(geciciKelime, "\"");
	  
        if(i%2 == 0){
			if(strcmp(argv[1],"-e") == 0) {
			strcpy(kelime,strdup(geciciKelime));
			}
			else {
			jvkelime = new_jval_s(strdup(geciciKelime));
			}      
        }
        else{
			if(strcmp(argv[1], "-e") == 0) {
			jvkod = new_jval_s(strdup(geciciKelime));
			}
			else {
				strcpy(kod,strdup(geciciKelime));
			}
		}
	  }
     }
    	
      //(void)jrb_insert_str(kriptoTree, kelimeler->val.s, new_jval_s(strdup(kodlar->val.s)));

    if(strcmp(argv[1],"-e") == 0) {
		jrb_insert_str(kriptoTree, strdup(kelime), jvkod); 
    }
	else if(strcmp(argv[1],"-d") == 0) {
		jrb_insert_str(kriptoTree, strdup(kod), jvkelime);
    }   
  }
  fseek(kilit->f, 0, SEEK_END);
	long uzunluk = ftell(kilit->f);
  while(get_line(giris) >= 0) {
	  
	if(uzunluk == 0){
		fprintf(stderr, ".kilit dosyası boş");
		
	}
	else{
		  for(int i = 0; i < giris->NF; i++){
			if( jrb_find_str(kriptoTree, giris->fields[i])){
				cikisKelimesi = jrb_find_str(kriptoTree, giris->fields[i]);
				fprintf(dosya,"%s ",cikisKelimesi->val.s);
				printf("%s ", cikisKelimesi->val.s);
			}
			else{
				fprintf(dosya,"%s ",giris->fields[i]);
			}
		  }
         	fclose(dosya);
	}
	  }

  
  
  jettison_inputstruct(kilit);
  jettison_inputstruct(giris);
  
  return 0;
}