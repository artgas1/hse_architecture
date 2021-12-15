#include <iostream>
#include <thread>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

int o=1;      //Флаг очередности
bool end=false;//Конец игры
int asn=15;   //количество  снарядов игрока А
int asl=400;   //количество  солдат игрока А
int bsn=30;   //цена снаряда игрока А
int bsl=200;   //цена  солдата игрока А
int apn=1;    //количество  снарядов игрока В
int apl=10;   //количество  солдат игрока В
int bpn=100;    //цена снаряда игрока В
int bpl=10;   //цена  солдата игрока В
int ain,ail,bin,bil;
int nmax=1000; // максимальное кол-во значений аргументов

void usage(){
    std::cout<<"Usage:\n";
    std::cout<<"-asn количество  снарядов игрока А (15)\n";
    std::cout<<"-asl количество  солдат игрока А(400)\n";
    std::cout<<"-bsn количество снаряда игрока А(30)\n";
    std::cout<<"-bsl количество  солдата игрока А(200)\n";
    std::cout<<"-apn цена  снарядов игрока В (1)\n";
    std::cout<<"-apl цена  солдат игрока В (10)\n";
    std::cout<<"-bpn цена снаряда игрока В (100)\n";
    std::cout<<"-bpl цена  солдата игрока В (10)\n";
    std::cout<<nmax<<"-- максимальное кол-во значений аргументов\n";
}


int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
        void *(*start_routine) (void *), void *arg);

void awar() {
    for (;asn>0 & !end & asl>0;asn--){
        for (;o==0;){}
        /* если есть солдаты и снаряды --воюем */
        if (asl>0 & bsl>0 & !end){             
            std::cout << "\nFire A: lost "<<asn-1<<"\n";
            int tbsl=std::rand()%12;
            tbsl=(bsl>tbsl?tbsl:bsl);
            bsl-=tbsl;
            bil+=tbsl;
            ain++;
            std::cout << "kill "<<tbsl<<" solder B: lost "<<(bsl>0?bsl:0)<<"\n";
            std::cout <<"$"<<ain*apn<<" <=> $"<<bil*bpl<<"\n";
            /* если стоимость снарядов больше 
             * стоимости ущерба -- игра закончена */
            if (ain*apn>bil*bpl){end=true;}
        }
        o=0;
    }
    /* Если нет больше снарядов и, вообще, 
     * -- игра закончена*/
    if (asn==0){std::cout<<"\tNot Fire!\n";}
    end=true;
}
void bwar() {
    for (;bsn>0 & !end & bsl>0;bsn--){
        for (;o==1;){}
        if (bsl>0 & asl>0 & !end){
            std::cout << "\nFire B: lost "<<bsn-1<<"\n";
            int tasl=std::rand()%12;
            tasl=(asl>tasl?tasl:asl);
            asl-=tasl;
            ail+=tasl;
            bin++;
            std::cout << "kill "<<tasl<<" solder A: lost "<<(asl>0?asl:0)<<"\n";
            std::cout <<"$"<<bin*bpn<<" <=> $"<<ail*apl<<"\n";
            if (bin*bpn>ail*apl){end=true;}
        }
        o=1;
    }
    if (bsn==0){std::cout<<"\tNot Fire!\n";}
    end=true;
}

int main(int argc, char *argv[]) {
    usage();
    if (argc>1){
        if (argc%2 ==1){
            /* если все правильно, берем аргументы */
            for (int i=(argc-1)/2;i>0;i-=1){
                 if (strcmp(argv[i*2-1],"-asn")==0){
                     int tasn=(atoi(argv[i*2])); 
                     asn=(tasn>0 & tasn<nmax?tasn:asn);
                     continue;
                 }
                 if (strcmp(argv[i*2-1],"-bsn")==0){
                     int tbsn=(atoi(argv[i*2])); 
                     bsn=(tbsn>0 & tbsn<nmax?tbsn:bsn);
                     continue;
                 }
                 if (strcmp(argv[i*2-1],"-asl")==0){
                     int tasl=(atoi(argv[i*2])); 
                     asl=(tasl>0 & tasl<nmax?tasl:asl);
                     continue;
                 }
                 if (strcmp(argv[i*2-1],"-bsl")==0){
                     int tbsl=(atoi(argv[i*2])); 
                     bsl=(tbsl>0 & tbsl<nmax?tbsl:bsl);
                     continue;
                 }
                 if (strcmp(argv[i*2-1],"-apn")==0){
                     int tapn=(atoi(argv[i*2])); 
                     apn=(tapn>0 & tapn<nmax?tapn:apn);
                     continue;
                 }
                 if (strcmp(argv[i*2-1],"-bpn")==0){
                     int tbpn=(atoi(argv[i*2])); 
                     bpn=(tbpn>0 & tbpn<nmax?tbpn:bpn);
                     continue;
                 }
                 if (strcmp(argv[i*2-1],"-apl")==0){
                     int tapl=(atoi(argv[i*2])); 
                     apl=(tapl>0 & tapl<nmax?tapl:apl);
                     continue;
                 }
                 if (strcmp(argv[i*2-1],"-bpl")==0){
                     int tbpl=(atoi(argv[i*2])); 
                     bpl=(tbpl>0 & tbpl<nmax?tbpl:bpl);
                     continue;
                 }

            }
        }else{
            std::cout<<"Неверное количество аргументов\n";
            return 0;
        }
    }
    /* высвечиваем начальные значения */
    std::cout<<"\nA: solder "<<asl<<" = $"<<asl*apl<<", fire "<<asn<<
        " = $"<<apn*asn<<"\n";
    std::cout<<"B: solder "<<bsl<<" = $"<<bsl*bpl<<", fire "<<bsn<<
        " = $"<<bpn*bsn<<"\n";
    /* начинаем */
    std::cout<<"\nGame start\n";
    std::thread t(awar);
    std::thread tb(bwar);
    tb.join();
    t.join();
    std::cout<<"Game over\n";
    /* хорошо то, что хорошо заканчивается */
    return 0;
}

