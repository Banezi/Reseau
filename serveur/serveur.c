#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>

int valeurPhrase(char* texte)
{
    int i=0, count=0;
    while(texte[i]!='\0')
    {
        count += texte[i] - 'a' +1;
        i++;
    }
    return count;
}

int nbVoyelle(char* texte)
{
    int nb=0, i=0;
    while(texte[i]!='\0')
    {
        if(texte[i]=='a' || texte[i]=='e'|| texte[i]=='i' || texte[i]=='u' || texte[i]=='o' || texte[i]=='y')
            nb++;
        i++;
    }
    return nb;
}

int main(int argc, char *argv[])   {
  int s_ecoute,scom, lg_app,i,j;
  struct sockaddr_in adr;
  struct sockaddr_storage recep;
  char buf[1500], renvoi[1500], host[1024],service[20];

   s_ecoute=socket(AF_INET,SOCK_STREAM,0);
   printf("creation socket\n");

   adr.sin_family=AF_INET;
   adr.sin_port=htons(atoi(argv[1]));
   adr.sin_addr.s_addr=INADDR_ANY;

   if (bind(s_ecoute,(struct sockaddr *)&adr,sizeof(struct sockaddr_in)) !=0) {
     printf("probleme de bind sur v4\n");
     exit(1); }

   if (listen(s_ecoute,5) != 0)      {
       printf("pb ecoute\n"); exit(1);}

   printf("en attente de connexion\n");
   while (1)  {
      scom=accept(s_ecoute,(struct sockaddr *)&recep, (unsigned long *)&lg_app);
      getnameinfo((struct sockaddr *)&recep,sizeof (recep), host, sizeof(host),service, sizeof(service),0);
       printf("recu de %s venant du port %s\n",host, service);

	   while (1)     {
	       recv(scom,buf,sizeof(buf),0);
	       printf("buf recu %s\n",buf);
	       bzero(renvoi,sizeof(renvoi));
	       //modif
	       printf("\nLe nombre de voyelle est %d \n", nbVoyelle(buf));
	       printf("\nLa valeur de la phrase est %d \n", valeurPhrase(buf));
	       for(i=strlen(buf)-1,j=0;i>=0;i--,j++)  renvoi[j]=buf[i];
	       renvoi[j+1]='\0';

	       send(scom,renvoi,strlen(renvoi),0);
	       bzero(buf,sizeof(buf));
	       if (strcmp(renvoi,"NIF") == 0)    break;   }
	   close(scom);   }
	close(s_ecoute); }

