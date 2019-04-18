#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxX 125
#define maxY 200

void AnaMenu();  //Ana menü
void KarakterDizisi(FILE *dosya);
int EofveSutun(FILE *dosya);  //Satır sonu karakterı ve sutun sayısı
int TrKarakterveUpper(int);   //Turkce karakterlerı buyuk yazdırmak ıcın
void YeniKelimeEkleme();
void Guncelleme();
void AnlamSorgulama ();
void GirilenIlkHarf();
void MetinParcasi();
void TumKelimeler();
void HarflerinYeri ();
int TrKarakterGeriAlma (int);  //okunan turkce karakteri printf ile yazdırmak ıcın

FILE *cfile;
char karakterdizi[maxX][maxY];
int eof=0,sutun=0;

int main(void)
{
  if((cfile=fopen("sozluk.dat","r+"))==NULL){
    printf ("Dosya Acılamadı");
    return;
    }
  EofveSutun(cfile);
  AnaMenu ();
  return 0;
}

void AnaMenu (){
  int Tercih;
  printf ("1- Sozluge yeni kelime ekleme\n"
          "2- Sozlukteki bir kelimenin Ingilizce anlamini guncelleme\n"
          "3- Sozlukteki bir kelimenin Ingilizce anlamini sorgulama\n"
          "4- Girilen bir Turkce harf ile baslayan kelimelerin ve Ingilizce anlamlarinin listelenmesi\n"
          "5- Girilen bir Turkce metin parcasinin gectigi kelimelerin ve Ingilizce anlamlarinin listelenmesi\n"
          "6- Sozlukteki tum kelimelerin ve Ingilizce anlamlarinin listelenmesi\n"
          "7- Harflerin kelime icinde kullanildiklari yer istatistiklerinin listelenmesi\nTercihiniz:?");
  scanf ("%d",&Tercih);
  if (Tercih==1)
    YeniKelimeEkleme ();
  if (Tercih==2)
    Guncelleme ();
  if (Tercih==3)
    AnlamSorgulama ();
  if (Tercih==4)
    GirilenIlkHarf ();
  if (Tercih==5)
    MetinParcasi ();
  if (Tercih==6)
    TumKelimeler ();
  if (Tercih==7){
    KarakterDizisi (cfile);  //Karakterleri matris dizisinde tutan fonksiyon
    HarflerinYeri();
    }
}

int EofveSutun(FILE *dosya){
  char karakter;
  fscanf (dosya,"%c",&karakter);
  while (!feof(dosya)){
      eof++;
      if (karakter=='\n')
        sutun++;
      fscanf (dosya,"%c",&karakter);
    }
  if (karakter!='\n'){
      rewind(cfile);
      fclose(cfile);
      cfile=fopen ("sozluk.dat","a+");
      fprintf (cfile,"\n");
      fclose(cfile);
      cfile=fopen("sozluk.dat","r+");
    }
      rewind(dosya);
}

int TrKarakterveUpper (int no){
  //Her türkçe harfin scanf ile alınan numara degeri ile fscanften gelen türkçe harfin büyük harf değeri değiştiriliyor//
    //ı->I
  if (no==-115)
      no=73;
    //i->İ || İ(scanf)->İ(fscanf)
  if (no==105 || no==-104)
      no=-35;
    //ğ->Ğ || Ğ(scanf)->Ğ(fscanf)
  if (no==-89 || no==-90)
      no=-48;
    //ü->Ü || Ü(scanf)->Ü(fscanf)
  if (no==-127 || no==-102)
        no=-36;
    //ş->Ş || Ş(scanf)->Ş(fscanf)
  if(no==-97 || no==-98)
      no=-34;
    //ö->Ö || Ö(scanf)->Ö(fscanf)
  if (no==-108 || no==-103)
        no=-42;
    //ç->Ç || Ç(scanf)->Ç(fscanf)
  if (no==-121 || no==-128)
        no=-57;
  return no;
}

int TrKarakterGeriAlma(int no){
  //Printf ile türkçe karakter kullanmak için//
  //İ(fscanf)->İ(printf)
  if (no==-35)
      no=-104;
  //Ğ(fscanf)->Ğ(printf)
  if (no==-48)
      no=-90;
  //Ü(fscanf)->Ü(printf)
  if (no==-36)
      no=-102;
  //Ş(fscanf)->Ş(printf)
  if(no==-34)
      no=-98;
  //Ö(fscanf)->Ö(printf)
  if (no==-42)
      no=-103;
  //Ç(fscanf)->Ç(printf)
  if (no==-57)
      no=-128;
  return no;
}

void YeniKelimeEkleme (){
  int i=0,counter,enbuyuk,sayac=1,j=0;
  char sozlukTR,ing;
  char girilenKelime[20],kontrol[20],ingilizceKelime[100],giris[20];
  printf ("\nTurkce kelimeyi giriniz: ");
  scanf("%s",giris);
  for (i=0;i<strlen (giris);i++){
      if (giris[i]!='i')
          girilenKelime[i]=toupper(giris[i]);
      else
          girilenKelime[i]='i';
      girilenKelime[i]=TrKarakterveUpper (girilenKelime[i]);
    }
  girilenKelime[i]='\0';
  fscanf (cfile,"%c",&sozlukTR);
  i=0;
  while (!feof(cfile)){
      counter=0;
      if (sozlukTR!='#'){
          kontrol[i]=sozlukTR;
          fscanf (cfile,"%c",&sozlukTR);
          sayac++;
          i++;
        }
      else{
          kontrol[i]='\0';
          enbuyuk=strlen(kontrol);
          if (strlen(girilenKelime)>strlen(kontrol))
            enbuyuk=strlen(girilenKelime);
          for (i=0;i<enbuyuk;i++){
              if (kontrol[i]==girilenKelime[i])
                  counter++;
            }
          if (counter==enbuyuk){
              printf ("\nKelime sozlukte var");
                  j++;
              break;
            }
          fscanf (cfile,"%c",&sozlukTR);
          fscanf (cfile,"%c",&sozlukTR);
          while (sozlukTR!='\n'){
              if (sayac>=eof)
                  break;
              sayac++;
              fscanf (cfile,"%c",&sozlukTR);
            }
          sayac++;
          fscanf (cfile,"%c",&sozlukTR);
          i=0;
         }
     }
  if (j!=0){
      i=0;
      rewind(cfile);
    }
  else{
     printf ("\nIngilizce anlamini giriniz: ");
     i=0;
     scanf ("%c",&ing);
     while ((ing=getchar())!='\n')
        ingilizceKelime[i++]=ing;
     ingilizceKelime[i]='\0';
     fprintf (cfile,"%s#\n%s\n",girilenKelime,ingilizceKelime);
    }
  rewind(cfile);
}

void Guncelleme (){
  FILE *yedek;
  yedek=fopen ("yedek.dat","w");
  int i=0,counter,enbuyuk,sayac=0,j=0;
  char girilenKelime[20],kontrol[20],giris[20],yeniKelime[100];
  char ingilizceKelime[100],c,yeni;
  printf ("\nGuncellencek Turkce kelimeyi giriniz: ");
  scanf("%s",giris);
  for (i=0;i<strlen (giris);i++){
      if (giris[i]!='i')
          girilenKelime[i]=toupper(giris[i]);
      else
          girilenKelime[i]='i';
      girilenKelime[i]=TrKarakterveUpper (girilenKelime[i]);
    }
  girilenKelime[i]='#';
  girilenKelime[i+1]='\0';
  fscanf (cfile,"%s",kontrol);
  sayac+=strlen (kontrol);
  i=0;
  fscanf (cfile,"%c",&c);
  fscanf (cfile,"%c",&c);
  while (c!='\n'){
      ingilizceKelime[i++]=c;
      fscanf (cfile,"%c",&c);
      sayac++;
    }
  ingilizceKelime[i]='\0';
  while (!feof(cfile)){
      counter=0;
      if (sayac>=eof)
          break;
      enbuyuk=strlen(kontrol);
      if (strlen(girilenKelime)>strlen(kontrol))
          enbuyuk=strlen(girilenKelime);
      for (i=0;i<enbuyuk;i++){
          if (kontrol[i]==girilenKelime[i])
              counter++;
            }
      if (counter==enbuyuk){
          j=1,i=0;
          printf ("Ingilizce kelimeyi giriniz: ");
          scanf ("%c",&yeni);
          while ((yeni=getchar ())!='\n')
              yeniKelime[i++]=yeni;
          yeniKelime[i]='\0';
          fprintf (yedek,"%s\n%s\n",kontrol,yeniKelime);
             }
      else{
          fprintf (yedek,"%s\n%s\n",kontrol,ingilizceKelime);
           }
      fscanf (cfile,"%s",kontrol);
      sayac+=strlen (kontrol);
      i=0;
      fscanf (cfile,"%c",&c);
      fscanf (cfile,"%c",&c);
      while (c!='\n'){
          ingilizceKelime[i++]=c;
          fscanf (cfile,"%c",&c);
          sayac++;
        }
      ingilizceKelime[i]='\0';
     }
  if (j==0)
      printf ("\nKelime  sozlukte bulunamadi");
  rewind(cfile);
  rewind(yedek);
  fclose(cfile);
  fclose(yedek);
  remove ("sozluk.dat");
  rename ("yedek.dat","sozluk.dat");
  cfile=fopen("sozluk.dat","r+");
}

void AnlamSorgulama(){
  int i=0,counter,enbuyuk,sayac=1,j=0;
  char sozlukTR;
  char girilenKelime[20],kontrol[20],giris[20];
  char ingilizceKelime[100];
  printf ("\nIngilizce anlamini bulmak istediginiz kelime: ");
  scanf("%s",giris);
  for (i=0;i<strlen (giris);i++){
      if (giris[i]!='i')
          girilenKelime[i]=toupper(giris[i]);
      else
          girilenKelime[i]='i';
      girilenKelime[i]=TrKarakterveUpper (girilenKelime[i]);
    }
  girilenKelime[i]='\0';
  fscanf (cfile,"%c",&sozlukTR);
  i=0;
  while (!feof(cfile)){
      counter=0;
      if (sozlukTR!='#'){
          kontrol[i]=sozlukTR;
          fscanf (cfile,"%c",&sozlukTR);
          sayac++;
          i++;
        }
      else{
          kontrol[i]='\0';
          enbuyuk=strlen(kontrol);
          if (strlen(girilenKelime)>strlen(kontrol))
            enbuyuk=strlen(girilenKelime);
          for (i=0;i<enbuyuk;i++){
              if (kontrol[i]==girilenKelime[i])
                  counter++;
            }
          fscanf (cfile,"%c",&sozlukTR);
          if (enbuyuk==counter){
              fgets(ingilizceKelime,100,cfile);
              printf ("Kelimenin ingilizce anlami: %s",ingilizceKelime);
              j=1;
            }
          fscanf (cfile,"%c",&sozlukTR);
          while (sozlukTR!='\n'){
              if (sayac>=eof)
                  break;
              sayac++;
              fscanf (cfile,"%c",&sozlukTR);
            }
          sayac++;
          fscanf (cfile,"%c",&sozlukTR);
          i=0;
         }
     }
  if (j==0){
      printf ("\nKelime  sozlukte bulunamadi\n");
      rewind(cfile);
    }
  rewind(cfile);
}

void GirilenIlkHarf (){
  int i,sayac;
  char sozlukTR,ilk;
  char ingilizceKelime[100],turkceKelime[20];
  printf ("Ilk harfi giriniz: ",getchar ());
  scanf ("%c",&ilk);
  if (ilk!='i')
      ilk=toupper(ilk);
  ilk=TrKarakterveUpper (ilk);
  printf ("\nTURKCE KELIME\t\tINGILIZCE ANLAMI");
  printf ("\n_____________________\t_____________________________________");
  fscanf (cfile,"%c",&sozlukTR);
  sayac=1;
  while (!feof(cfile)){
      i=0;
      if (sozlukTR==ilk){
          while (sozlukTR!='#'){
             turkceKelime[i++]=sozlukTR;
             fscanf (cfile,"%c",&sozlukTR);
             sayac++;
            }
          turkceKelime[i]='\0';
          fscanf (cfile,"%c",&sozlukTR);
          fscanf (cfile,"%c",&sozlukTR);
          sayac+=2;
          i=0;
          while (sozlukTR!='\n'){
             ingilizceKelime[i++]=sozlukTR;
             fscanf (cfile,"%c",&sozlukTR);
             sayac++;
            }
          ingilizceKelime[i]='\0';
          for (i=0;i<strlen (turkceKelime);i++){
              turkceKelime[i]=TrKarakterGeriAlma (turkceKelime[i]);
            }
          turkceKelime[i]='\0';
          printf ("\n%s\t\t\t %s",turkceKelime,ingilizceKelime);
          fscanf (cfile,"%c",&sozlukTR);
          if (sozlukTR=='\n')
              break;
          sayac++;
          }
      if (sozlukTR!=ilk){
          while (sozlukTR!='#'){
             fscanf (cfile,"%c",&sozlukTR);
             sayac++;
            }
          fscanf (cfile,"%c",&sozlukTR);
          fscanf (cfile,"%c",&sozlukTR);
          sayac+=2;
          while (sozlukTR!='\n'){
              fscanf (cfile,"%c",&sozlukTR);
              sayac++;
            }
          fscanf (cfile,"%c",&sozlukTR);
          sayac++;
        }
      if (sayac>=eof)
        break;
    }
  rewind(cfile);
}

void MetinParcasi (){
  int i=0,j=0,sayac=0,swap,eofsayaci;
  char sozlukTR,parca;
  char ingilizceKelime[100],turkceKelime[20],metinParca[20],giris[20];
  printf ("Metin parcasini giriniz: ",getchar ());
  while ((parca=getchar ())!='\n')
      giris[i++]=parca;
  giris[i]='\0';
  for (i=0;i<strlen (giris);i++){
      if (giris[i]!='i')
          metinParca[i]=toupper(giris[i]);
      else
          metinParca[i]='i';
      metinParca[i]=TrKarakterveUpper (metinParca[i]);
    }
  metinParca[i]='\0';
  printf ("\nTURKCE KELIME\t\tINGILIZCE ANLAMI");
  printf ("\n_____________________\t_____________________________________");
  fscanf (cfile,"%c",&sozlukTR);
  eofsayaci=1;
  while (!feof(cfile)){
      i=0,j=0,sayac=0;
      while (sozlukTR!='#'){
          turkceKelime[i]=sozlukTR;
          fscanf (cfile,"%c",&sozlukTR);
          eofsayaci++;
          i++;
        }
      turkceKelime[i]='\0';
      i=0;
      while (metinParca[j]!='\0'){
          if (turkceKelime[i]=='\0'){
              fscanf (cfile,"%c",&sozlukTR);
              fscanf (cfile,"%c",&sozlukTR);
              eofsayaci+=2;
              while (sozlukTR!='\n'){
                  fscanf (cfile,"%c",&sozlukTR);
                  eofsayaci++;
                }
              fscanf (cfile,"%c",&sozlukTR);
              eofsayaci++;
              break;
            }
          if (metinParca[j]==turkceKelime[i]){
              swap=i;
              for (j=0;j<strlen (metinParca);j++){
                  if (metinParca[j]==turkceKelime[i++])
                      sayac++;
                }
              if (sayac==strlen (metinParca)){
                  fscanf (cfile,"%c",&sozlukTR);
                  fscanf (cfile,"%c",&sozlukTR);
                  eofsayaci+=2,i=0;
                  while (sozlukTR!='\n'){
                      ingilizceKelime[i++]=sozlukTR;
                      fscanf (cfile,"%c",&sozlukTR);
                      eofsayaci++;
                    }
                  ingilizceKelime[i]='\0';
                  fscanf (cfile,"%c",&sozlukTR);
                  for (i=0;i<strlen (turkceKelime);i++){
                      turkceKelime[i]=TrKarakterGeriAlma (turkceKelime[i]);
                    }
                  turkceKelime[i]='\0';
                  eofsayaci++;
                  printf ("\n%s\t\t\t %s",turkceKelime,ingilizceKelime);
                  break;
                }
              else{
                  j=0,i=swap+1,sayac=0;
                }
            }
          else
             i++;
         }
      if (eofsayaci>=eof)
        break;
    }
  rewind(cfile);
  printf ("\n");
}

void TumKelimeler (){
  int i=0,eofsayaci;
  char sozlukTR;
  char ingilizceKelime[100],turkceKelime[20];
  printf ("\nTURKCE KELIME\t\tINGILIZCE ANLAMI");
  printf ("\n_____________________\t_____________________________________");
  fscanf (cfile,"%c",&sozlukTR);
  eofsayaci=1;
  while (!feof(cfile)){
      i=0;
      while (sozlukTR!='#'){
          turkceKelime[i]=sozlukTR;
          fscanf (cfile,"%c",&sozlukTR);
          eofsayaci++;
          i++;
        }
      turkceKelime[i]='\0',i=0;
      fscanf (cfile,"%c",&sozlukTR);
      fscanf (cfile,"%c",&sozlukTR);
      eofsayaci+=2;
      while (sozlukTR!='\n'){
          ingilizceKelime[i++]=sozlukTR;
          fscanf (cfile,"%c",&sozlukTR);
          eofsayaci++;
        }
      ingilizceKelime[i]='\0';
      for (i=0;i<strlen (turkceKelime);i++){
          turkceKelime[i]=TrKarakterGeriAlma (turkceKelime[i]);
        }
      turkceKelime[i]='\0';
      printf ("\n%s\t\t\t%s",turkceKelime,ingilizceKelime);
      if (eofsayaci>=eof)
        break;
    }
  printf("\n");
  rewind(cfile);
}

void KarakterDizisi (FILE *dosya){
  int i,j,krktrSayi=0;
  char okunanKarakter;
  fscanf(dosya,"%c",&okunanKarakter);
  for (i=0;i<sutun/2+1;i++){
      for (j=0;j<maxX;j++){
          if (okunanKarakter!='#')
              karakterdizi[i][j]=okunanKarakter;
          else{
              karakterdizi[i][j]='\0';
              fscanf(dosya,"%c",&okunanKarakter);
              fscanf(dosya,"%c",&okunanKarakter);
              krktrSayi+=2;
              while (okunanKarakter!='\n'){
                  fscanf(dosya,"%c",&okunanKarakter);
                  krktrSayi++;
                }
              i++;
              j=-1;
            }
          fscanf(dosya,"%c",&okunanKarakter);
          krktrSayi++;
        }
    }
  rewind(dosya);
}

void HarflerinYeri (){
  int i,j,k,z;
  char harfler[29]="ABCÇDEFGĞHIİJKLMNOÖPRSŞTUÜVYZ";
  int harfSayi[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  printf ("Harf 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20\n"
          "____ _  _  _  _  _  _  _  _  _  __ __ __ __ __ __ __ __ __ __ __\n");
  for (k=0;k<29;k++){
      for (i=0;i<sutun/2+1;i++){
          for (j=0;j<20;j++){
              if (karakterdizi[i][j]==harfler[k])
                   harfSayi[j]++;
            }
        }
      harfler[k]=TrKarakterGeriAlma (harfler[k]);
      printf (" %c   ",harfler[k]);
      for (z=0;z<20;z++){
          printf ("%d  ",harfSayi[z]);
        }
      for (z=0;z<20;z++){
          harfSayi[z]=0;
        }
      printf ("\n");
    }
  printf ("\n");
}
