#include <iostream>
using namespace std;

int main() {
    char startValue;
    float onlineshopping(void);
    cout << "please press S to start Shopping" << endl;
    cin>>  startValue;
if (startValue="s" || startValue= "S"){
 float  totalamount=onlineshopping();
}
else{
    cout<< "you have enterned wrong option pleae press s to start shopping "<< endl;
    goto start;
}
}
float onlineshopping ()
char choice;
char item ;
int quantity;
float billamount=0;

cout << " ******************* WELCOME TO THE SHOPPING *****************"<< endl;
cout<< "******************please follow the instruction  *****************" << endl;
cout << "(1) please press enter m to order mobile phones " << endl;
cout << "(2) please press enter l to order laptops " << endl;
cout << "(3) please press enter b to order burgers " << endl;
cout << "(4) please press enter s to order  speakers" << endl;
cout << "(5) please press enter f to order fans  " << endl;
cout << "(6) please press enter n to order head phones  " << endl;
cout << "(7) please press enter q to order cloths " << endl;
cout << "(8) please press enter w to order water " << endl;
cout << "(9) please press enter t to order toys" << endl;
cout << "(10) please press enter u to order fruits  " << endl;
cout << "(11) please press enter o to order vegetables " << endl;
cout << "(12) please press enter k to order kites " << endl;
cout << "(13) please press enter v to order camera " << endl;
cout << "(14) please press enter c to order cats " << endl;


// MOBILE PHONE 

if (choice='m' || choice='M'){
    cout<< "Mobile phone details" << endl;
    cout<< "  (1) I PHONE 15 PRO MAX  => PRICE : 450000 RS  " << endl;
    cout<< "  (2) I PHONE 15 PRO      => PRICE : 400000 RS  " << endl;
    cout<< " I PHONE 14 PRO MAX  => PRICE : 350000 RS  " << endl;
    cout<< " I PHONE 13 PRO MAX  => PRICE : 280000 RS  " << endl;
    cout<< " I PHONE 12 PRO MAX  => PRICE : 250000 RS  " << endl;
    cout<< " I PHONE 10 PRO      => PRICE : 200000 RS  " << endl;
    cout<< " I PHONE  X          => PRICE : 145000 RS  " << endl;
    cout<< " I PHONE 8           => PRICE : 110000 RS  " << endl;
    cout<< " Symsung S23 ULTRA   => PRICE : 480000 RS "  << endl;
    cout<< " Symsung S22 ULTRA   => PRICE : 340000 RS "  << endl;
    cout<< " Symsung S21 ULTRA   => PRICE : 230000 RS "  << endl;
    cout<< " Symsung A 64 ULTRA  => PRICE : 120000 RS "  << endl;
    cout<< " Symsung NOTE 7      => PRICE : 89000 RS "   << endl;
    cout<< " Symsung  NOTE 10    => PRICE : 110000 RS "  << endl;


    cout<< " please enter your choice " << endl;
     cin >> item;
    if ( item = '1'){
        cout<< " enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 450000 ;
    }
    

}
