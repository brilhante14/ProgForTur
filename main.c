#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct city{
        char *name;
        char *about;
        struct city *prev, *next;
}City;

City *AddCity(char* name, char* about){
    City *c = (City*) malloc(sizeof(City));
    c->name = name;   
    c->about = about;
    c->prev = NULL;
    c->next = NULL;
    return c;
}
typedef struct route{
    int horario[3];
    City *inicio;
    char *name;
    
}Route;

void NextCity(Route *R, City *c){
  City *aux = R->inicio;
  while(aux->next != NULL) aux = aux->next;
  aux = aux->prev;
  aux->next->prev = c;
  c->next = aux->next;
  aux->next = c;
  c->prev = aux;
}

Route *AddRoute(char *name, char *about){
  Route *r = (Route*) malloc(sizeof(Route));
  r->horario[0] = 04;
  r->horario[1] = 12;
  r->horario[2] = 20;
  r->name = name;
  r->inicio = AddCity("Fortaleza", "Terra do sol");
  City *end = AddCity(name, about);
  r->inicio->next = end;
  end->prev = r->inicio;
  return r;
}


void PrintRoute(Route *R){
  City *aux = R->inicio;
  while(aux != NULL){
    printf("%s -> ", aux->name);
    aux = aux->next;
  }
  printf("/ \n");
}

void createVecRoutes(Route **Routes){
  Route *one = AddRoute("Aracati", "Terra dos Bons Ventos");
  Routes[0] = one;
  Route *two = AddRoute("Quixeramobim", "Terra de Antônio Conselheiro");
  City *Aquiraz = AddCity("Aquiraz", "Feira Metropolitana do Artesanato");
  NextCity(two, Aquiraz);
  Routes[1] = two;
  Route *three = AddRoute("Quixadá", "Terra dos Monólitos e Voo Livre");
  City *Horizonte = AddCity("Horizonte", " Olho d'água");
  NextCity(three, Horizonte);
  Routes[2] = three;  
  Route *four = AddRoute("Sobral", "Terra de Dom José");
  Routes[3] = four;  
  Route *five = AddRoute("Viçosa", "Festejos de Nossa Senhora da Assunção");
  City *Cascavel = AddCity("Cascavel", "Feira de São Bento");
  NextCity(five, Cascavel);
  Routes[4] = five;
  Route *six = AddRoute("Madalena", "Possui uma das maiores Igrejas católicas do Brasil");
  City *Caninde = AddCity("Canindé", "Festa de São Francisco das Chagas");
  NextCity(six, Caninde);
  Routes[5] = six;
  Route *seven = AddRoute("Jericoacoara", "Paraíso cearense");
  City *Itarema = AddCity("Itarema", "Festa da Padroeira Nossa Senhora de Fátima");
  NextCity(seven, Itarema);
  Routes[6] = seven;
  Route *eight = AddRoute("Arneiroz", "Terra natal do Padre Antônio Teodósio Nunes");
  City *Maracanau = AddCity("Maracanaú", "Maior centro industrial do estado");
  NextCity(eight, Maracanau);
  Routes[7] = eight;
  Route *nine = AddRoute("Aiuaba", "Lugar da bebida");
  City *BoaViagem = AddCity("Boa Viagem", "Festa da padroeira Nossa Senhora da Boa Viagem");
  NextCity(nine, BoaViagem);
  City *Taua = AddCity("Tauá", "Igreja de Nossa Senhora do Rosário");
  NextCity(nine, Taua);
  Routes[8] = nine;
  Route *ten = AddRoute("Amontada", "Festa da padroeira Nossa Senhora da Conceição");
  City *Uruburetama = AddCity("Uruburetama", "Terra da Banana e Arraial");
  NextCity(ten, Uruburetama);
  City *Itapipoca = AddCity("Itapipoca", "Cidade dos três climas");
  NextCity(ten, Itapipoca);
  Routes[9] = ten;
}

int getRoute(char* name, Route** Routes){
  for(int i=0; i<10; i++) {
   if(strcmp(name, Routes[i]->name) == 0) return i;
  }
  return -1; 
}

int main(){
  Route **Routes = (Route**) malloc(sizeof(Route)*10);
  createVecRoutes(Routes);
  printf("Rotas disponíveis: \n");
  for(int i=0; i<10; ++i){
    PrintRoute(Routes[i]);
  }
  printf("\nDigite o destino para ver mais informações sobre a rota:\n");
  char destino[30];
  scanf("%s", destino);
  int iter = getRoute(destino, Routes);
  if(iter==-1){
    printf("Destino indisponível!");
    return 1;
  }
  City *city = Routes[iter]->inicio;
  printf("Digite o horario desejado: [0 -> 23] ");
  int hora_chegada;
  scanf("%d", &hora_chegada);
  if(hora_chegada >= 0 && hora_chegada < 8) hora_chegada = Routes[iter]->horario[0];
  if(hora_chegada >= 8 && hora_chegada < 16) hora_chegada = Routes[iter]->horario[1];
  if(hora_chegada >= 16 && hora_chegada < 24) hora_chegada = Routes[iter]->horario[2];
  int trigger = 1;
  while(trigger){
    printf("\nDestino: %s\n", Routes[iter]->name);
    printf("Horário de chegada: %d:00\n", hora_chegada);
    printf("Você está em %s, %s!\n", city->name, city->about);
    if(city->prev != NULL) printf("Parada anterior: %s.\n", city->prev->name);
    if(city->next != NULL) printf("Próxima parada: %s.\n", city->next->name);
    else printf("\nEstamos no seu destino!\n\n");
    printf("Digite:\n");
    printf("1, para agendar outra viagem!\n");
    printf("2, para ver a parada anterior!\n");
    printf("3, para ver a próxima parada!\n");
    printf("4, para finalizar!\n");
    int escolha;
    scanf("%d", &escolha);
    switch(escolha){
      case 1:
        main();
        return 0;
      break;
      case 2:
        if(city->prev == NULL){
          printf("Esta já é a primeira parada!\n\n");
          break;
        }
        city = city->prev;
      break;
      case 3:
        if(city->next == NULL){
          printf("Esta já é a última parada!\n\n");
          break;
        }
        city = city->next;
      break;
      case 4:
        trigger = 0;
      break;
    } 
  }
  printf("Obrigado por utilizar nossos serviços!\n");
  return 0;
}

