#include <iostream>
#include <string>
#include <conio.h>
#include <ctime>
#include <Windows.h>

using namespace std;

// su dung cac phim mui ten thay vi chu cai

#define LEN 72
#define TRAI 75
#define PHAI 77
#define XUONG 80

int bangGiai[10][10];

void inBang(int banCo[][10], int);  // in bang tro choi
void khoiTaoBanCo(int banCo[][10], int); // khoi tao tro choi
void diChuyenO(int banCo[][10], int huong, int); // cac lenh di chuyen
bool laBanCoDaGiai(int banCo[][10], int); //tro choi khi hoan thanh
void tronBanCo(int banCo[][10], int); // xao tron ban co
void choDenKhiNhanPhim(); // nhan biet phim vua bam

// In ban co va thay the mau cho cac so da sap xep dung vi tri
void inBang(int banCo[][10], int kichThuoc)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int hang = 0; hang <= kichThuoc; hang++)
    {
    	cout<<endl;
        for(int cot = 0; cot <= kichThuoc; cot++)
        {
        	cout<<"\t";
            if(banCo[hang][cot] == 0)
            {
                SetConsoleTextAttribute(hConsole, 7); // su dung mau mac dinh
                cout << "\xB1\xB1 ";
            }
            else
            {
                if(banCo[hang][cot] == bangGiai[hang][cot]) // Neu vi tri hien tai sap xep dung thi chuyen sang mau xanh
                    SetConsoleTextAttribute(hConsole, 10);
                else
                    SetConsoleTextAttribute(hConsole, 12); // nguoc lai dat mau do
                if (banCo[hang][cot] < 10) // In so 0 truoc cac so
                    cout << "0";
                cout << banCo[hang][cot] << " ";
            }
        }
        cout << endl;
    }
    SetConsoleTextAttribute(hConsole, 7); // mau mac dinh
}

// khoi tao ban co
void khoiTaoBanCo(int banCo[][10], int kichThuoc)
{
    int i = 1;
    for(int hang = 0; hang <= kichThuoc; hang++)
    {
        for(int cot = 0; cot <= kichThuoc; cot++)
        {
            banCo[hang][cot] = i; 
            bangGiai[hang][cot] = i;
            i++;
        }
        banCo[kichThuoc][kichThuoc] = 0;
        bangGiai[kichThuoc][kichThuoc] = 0;
    }
}

// Thuc hien cac lenh di chuyen
void diChuyenO(int banCo[][10], int huong, int kichThuoc)
{
    int hangTrong;
    int cotTrong;
    bool nhungBuocHopLe[4] = {1,1,1,1}; // kiem tra cac buoc di chuyen hop le, [0] = trai, [1] = phai, [2] = len, [3] = xuong. true (1) chi danh cho 1 buoc di chuyen hop le
    for(int hang = 0; hang <= kichThuoc; hang++)
    {
        for(int cot = 0; cot <= kichThuoc; cot++)
        {
            if(banCo[hang][cot] == 0) // Tim vi tri cua o trong trong bang
            {
                hangTrong = hang;
                cotTrong = cot;
            }
        }
    }
    if(hangTrong + 1 > kichThuoc) // kiem tra co the di chuyen len khong
        nhungBuocHopLe[2] = false; // Neu khong thi buoc di chuyen khong hop le
    else if(hangTrong - 1 < 0) // kiem tra di chuyen xuong
        nhungBuocHopLe[3] = false; 

    if(cotTrong - 1 < 0) // kiem tra di chuyen qua phai
        nhungBuocHopLe[1] = false;
    else if(cotTrong + 1 > kichThuoc) // kiem tra di chuyen qua trai
        nhungBuocHopLe[0] = false;

    switch(huong) // Thay the o trong bang o ben trai, ben phai , tren hoac duoi 
    { 
    case 0: // trai
        if(nhungBuocHopLe[huong])
        {
            banCo[hangTrong][cotTrong] = banCo[hangTrong][cotTrong + 1];
            banCo[hangTrong][cotTrong + 1] = 0;
            cotTrong = cotTrong + 1;
        }
        break;
    case 1: // phai
        if(nhungBuocHopLe[huong])
        {
            banCo[hangTrong][cotTrong] = banCo[hangTrong][cotTrong - 1];
            banCo[hangTrong][cotTrong - 1] = 0;
            cotTrong = cotTrong - 1;
        }
        break;
    case 2: // len
        if(nhungBuocHopLe[huong])
        {
            banCo[hangTrong][cotTrong] = banCo[hangTrong + 1][cotTrong];
            banCo[hangTrong + 1][cotTrong] = 0;
            hangTrong = hangTrong + 1;
        }
        break;
    case 3: // xuong
        if(nhungBuocHopLe[huong])
        {
            banCo[hangTrong][cotTrong] = banCo[hangTrong - 1][cotTrong];
            banCo[hangTrong - 1][cotTrong] = 0;
            hangTrong = hangTrong - 1;
        }
        break;
    }
}
// dieu kien de chien thang
bool laBanCoDaGiai(int banCo[][10], int kichThuoc)
{
    for (int hang = 0; hang <= kichThuoc; hang++)
    {
        for (int cot = 0; cot <= kichThuoc; cot++)
        {
            if (bangGiai[hang][cot] != banCo[hang][cot])
            {
                return false; // Neu co bat ky mot o nao khac nhau thi chua hoan thanh
            }
        }
    }
    return true; // Neu khong co o nao khac nhau, tro choi da hoan thanh
}

void tronBanCo(int banCo[][10], int kichThuoc)
{
    time_t t;
    srand((unsigned) time(&t));
    int buocDi;
    while(laBanCoDaGiai(banCo, kichThuoc)) // Neu ban co da duoc giai, tron ngau nhien lai cac so de tao ban co moi
    {
        for(int i = 0; i < 100000;i++) // di chuyen ngau nhien cac so
        {
            buocDi = rand() % 4;
            diChuyenO(banCo, buocDi, kichThuoc);
        }
    }
}

void choDenKhiNhanPhim()
{
    while (_kbhit()) _getch(); // Làm trong de bam phim moi
    _getch(); // Cho de bam 1 phim  
    while (_kbhit()) _getch(); // Làm trong de bam phim moi(1 phim tao 2 lenh)
}
bool choiTiep() // dieu kien de choi lai lan nua
{
    cout << "ban co muon choi lai khong ? (y/n): ";
    char choice;
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}
void trochoi()
{
    
    int kichThuoc = 3; // kich thuoc ban co
    
        system("CLS");
        cout << "Huong dan choi tro choi puzzle 3x3:\n";
    	cout << "Muc tieu cua tro choi la sap xep cac o so tu 1 den 8 theo thu tu tang dan, bang cach di chuyen o trong tren mot bang 3x3\n";
    
		cout << "Ban co the di chuyen o trong theo 4 huong: len, xuong, trai, phai, bang cach nhan cac phim len xuong trai phai.\n";
    
		cout << "Vi du, ban co the di chuyen o trong tu vi tri (1, 2) sang vi tri (1, 1) bang cach nhan phim mui ten trai.\n";
    
		cout << "Ban se thang khi cac o so duoc sap xep nhu sau:\n";
    
		cout << "+---+---+---+\n";
    	cout << "| 1 | 2 | 3 |\n";
    	cout << "+---+---+---+\n";
    	cout << "| 4 | 5 | 6 |\n";
    	cout << "+---+---+---+\n";
    	cout << "| 7 | 8 |   |\n";
    	cout << "+---+---+---+\n";
    		
		cout << "De bat dau choi, hay nhan mot phim bat ky.......\n";
		cout << "De thoat khoi tro choi, hay nhan phim t.......\n";

    int banCo[10][10]; 
	char nhap;
    while(1)
	{ // nhan t de thoat tro choi
    	int t;
    	t = getch();
        if (t =='t' ||t =='T')
		{
			break; 
		} 
		else
		{
			cout << "Dang tao tro choi, nhan phim bat ky de tiep tuc......." << endl;
	    	string huong;
	    	bool khongHoptLe = false;
	     
	    	kichThuoc--; 
	    	do 
	    	{
			
	    	khoiTaoBanCo(banCo, kichThuoc); // khoi tao ban co
	    	cout << boolalpha; // tra ve gia tri true or false
	    	choDenKhiNhanPhim(); // kiem tra buoc di chuyen hop le hay khong
	    	tronBanCo(banCo, kichThuoc); // xao tron ban co 
	    	system("CLS"); // xoa man hinh
	    	inBang(banCo, kichThuoc); // in ban co tro choi
	    	cout << endl << endl;
	    	cout << "Su dung cac phim mui ten de hoan thanh tro choi......." << endl;
	    	cout << "Nhap: ";
		    	while(!laBanCoDaGiai(banCo, kichThuoc)) { // dieu kien kiem tra ket thuc tro choi
		        	nhap = _getch();
		        	system("CLS"); // xoa man hinh
		
		        	switch(nhap) 
					{
		        		case LEN:  
		            		diChuyenO(banCo, 2, kichThuoc); // di chuyen o phia duoi len o trong
		            		huong = "Len";
		            		break;
		        		case TRAI:
		            		diChuyenO(banCo, 0, kichThuoc);  // di chuyen o ben phai qua o trong
		            		huong = "Trai";
		            		break;
		        		case XUONG:
		           			 diChuyenO(banCo, 3, kichThuoc); // di chuyen o phia tren xuong o trong
		            		huong = "Xuong";
		            		break;
		        		case PHAI:
		            		diChuyenO(banCo, 1, kichThuoc); // di chuyen o ben trai qua o trong
		            		huong = "Phai";
		            		break;
		        	default:
		            	khongHoptLe = true;  // phim di chuyen khong hop le
		
		        	}
		        	inBang(banCo, kichThuoc); // in bang sau khi da di chuyen  
		        	cout << endl << endl;
		        	cout << "Su dung cac phim di chuyen de hoan thanh tro choi......." << endl;
		        	if(khongHoptLe) // kiem tra phim bam co hop le khong
		            	khongHoptLe = false; // neu khong hop le tra ve false
		        	else
		            	cout << "Phim cuoi cung: " << huong; // ghi lai phim di chuyen cuoi cung da su dung
	    		}
	    		cout << endl;
	    		cout << "!!!!!!!BAN DA CHIEN THANG TRO CHOI!!!!!!!" << endl; 	
	    	}while (choiTiep());
	    	break;
		}
	}
	
}

int main()
{
	trochoi();
	cout<<"\n\t\tCAM ON BAN DA CHOI TRO CHOI";
	system("exit");
	return 0;
}




