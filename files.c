#include "files.h"

Warehouse * open_config_file(){
    Warehouse *warehouses;
    FILE * fp;
    int size, i, j, k;
    char str[200], *pch;
    char prod[30];
  
    fp = fopen("config.txt", "r");
    if (fp != NULL) {
        fseek(fp, 0, SEEK_END); /*vai ate ao fim do ficheiro*/
        size = ftell(fp); /*retorna a posição corrente de leitura ou escrita no arquivo (em bytes)*/
        if (size == 0) {
            printf("\nO ficheiro esta vazio.\n"); 
            exit(1);
        }
        else {
            fseek(fp, 0, SEEK_SET);/*volta ao inicio do ficheiro*/
            fgets(str, 200, fp);
             
            pch = strtok(str, ",");
            sscanf(pch, "%lf", &(coord_max.x));
            pch = strtok(NULL, ",");
            sscanf(pch, "%lf", &(coord_max.y));
            fgets(str, 200, fp);
            for (i =0; i< strlen(str); i++){ //conta nr produtos
                if(str[i] == ','){
                    num_prod++;
                }
            }
            product_types = (Product *)malloc(num_prod*sizeof(Product));
            pch = strtok(str, ",");
            for(i=0;i<num_prod;i++){
                strcpy(product_types[i].type, pch);
                pch = strtok(NULL, ",");

            }
            product_types[num_prod-1].type[strlen(product_types[num_prod-1].type)-1] = '\0';

            fgets(str, 200, fp);
            sscanf(str, "%d", &num_drones);

            fgets(str, 200, fp);
            pch = strtok(str, ",");
            sscanf(pch, "%d", &freq_abast);
            pch = strtok(NULL, ",");
            sscanf(pch, "%d", &quant_abast);
            pch = strtok(NULL, ",");
            sscanf(pch, "%d", &time_unit);
            fgets(str, 200, fp);
            fgets(str, 200, fp);
            sscanf(str, "%d", &num_warehouses);
            warehouses = (Warehouse *)malloc(num_warehouses*sizeof(Warehouse));
            
            for(i=0;i<num_warehouses;i++){
                for(j=0;j<num_prod;j++) {
                    warehouses[i].products[j].quant = -1;
                }
                fgets(str, 200, fp); 
                pch = strtok(str, " ");
                strcpy(warehouses[i].name, pch); //nome armazem
                pch = strtok(NULL, " "); 
                pch = strtok(NULL, " "); //passar a frente ate 2 espaços
                
                sscanf(pch, "%lf", &warehouses[i].local.x);
                pch = strtok(NULL, " ");
                sscanf(pch, "%lf", &warehouses[i].local.y);
                pch = strtok(NULL, ":");

                for (k = 0; k<3; k++){ //quant de produtos por armazem = 3
                    pch = strtok(NULL, ",");
                    strcpy(prod, pch);
                    strcpy(warehouses[i].products[k].type, prod);
                    pch = strtok(NULL, ",");
                    sscanf(pch, "%d", &(warehouses[i].products[k].quant));
                }      
            } 
       }                         
    }
    else {
        printf("\nO ficheiro nao esta disponivel.");
        exit(1); /*codigo de erro ficheiro nao disponivel*/
    }  
    fclose(fp);
    return warehouses;
}