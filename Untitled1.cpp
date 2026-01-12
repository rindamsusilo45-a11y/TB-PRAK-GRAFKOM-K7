#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

int main(){
    char username[50],password[50];
    char user[4][50] = {"irfan","fikri","fasya","zidan"},
         pass[4][50] = {"irfan08","fikri11","fasya22","zidan33"};
    int loginBerhasil = 0;
    int i;
    do {
        system("cls");
        printf("=======================================\n");
        printf("\n         LOGIN SISTEM PARKIR          \n");
        printf("\n=======================================\n");

        printf("Username : ");scanf("%s",username);
        printf("Password : ");scanf("%s",password);

        for(i = 0; i < 4; i++) {
            if(strcmp(username,user[i]) == 0 && strcmp(password,pass[i]) == 0){
                loginBerhasil = 1;
                break;
            }
        }
        if(loginBerhasil == 1){
            printf("\n---------------------------------------\n");
            printf("LOGIN BERHASIL!!!\n");
            printf("Tekan Enter Untuk Lanjut Ke Menu...");
            getch();
        }
        else {
			loginBerhasil = 0;
			printf("\n---------------------------------------\n");
			printf("LOGIN GAGAL!!!\n");
			printf("Tekan Enter Untuk Mencoba Lagi");
			getch();
        }
    }while(loginBerhasil == 0);
    int PilihanMenu;

    do{
        system("cls");
        printf("=== MENU SISTEM PARKIR (User:%s)===\n",username);
        printf("1. Kendaraan Masuk \n");
        printf("2. Kendaraan Keluar \n");
        printf("3. Cek Slot Kosong \n");
        printf("4. Laporan Pendapatan \n");
        printf("0. Keluar Program\n");
        printf("----------------------------------\n");
        printf("Pilih Menu (0-4): ");scanf("%d", &PilihanMenu);

    switch(PilihanMenu) {
        case 1:
            printf("\nMenu 1 terpilih\n");
            getch();
            break;
            
        case 2:
            printf("\nMenu 2 terpilih\n");
            getch();
            break;
            
        case 3:
            printf("\nMenu 3 terpilih\n");
            getch();
            break;

        case 4:
            printf("\nMenu 4 terpilih\n");
            getch();
            break;

        case 0:
            printf("\nProgram Dikeluarkan. Terima kasih.\n");
            break;

        default: 
            printf("\nPilihan tidak ada!\n");
            getch();
            break;
        }
    } while(PilihanMenu != 0);

    return 0;
}
