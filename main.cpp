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
cout << "(3) please press enter b to order speakers " << endl;
cout << "(4) please press enter w to order  watches" << endl;
cout << "(5) please press enter h to order head phones  " << endl;
cout << "(6) please press enter c to order computers " << endl;
cout << "(7) please press enter a to order Accesoories " << endl;
cout << "(8) please press enter g to order Gamingconsoles" << endl;
cout << "(9) please press enter t to order Tablets  " << endl;



// MOBILE PHONE 

if (choice='m' || choice='M'){
    cout<< "Mobile phone details" << endl;
    cout<< "  (1)  I-PHONE 15 PRO MAX  => PRICE : 450000 RS  " << endl;
    cout<< "  (2)  I-PHONE 15 PRO      => PRICE : 400000 RS  " << endl;
    cout<< "  (3)  I-PHONE 14 PRO MAX  => PRICE : 350000 RS  " << endl;
    cout<< "  (4)  I-PHONE 13 PRO MAX  => PRICE : 280000 RS  " << endl;
    cout<< "  (5)  I-PHONE 12 PRO MAX  => PRICE : 250000 RS  " << endl;
    cout<< "  (6)  I-PHONE 10 PRO      => PRICE : 200000 RS  " << endl;
    cout<< "  (7)  I-PHONE  X          => PRICE : 145000 RS  " << endl;
    cout<< "  (8)  I-PHONE 8           => PRICE : 110000 RS  " << endl;
    cout<< "  (9)  Samsung S23 ULTRA   => PRICE : 480000 RS "  << endl;
    cout<< "  (10) Samsung S22 ULTRA   => PRICE : 340000 RS "  << endl;
    cout<< "  (11) Samsung S21 ULTRA   => PRICE : 230000 RS "  << endl;
    cout<< "  (12) Samsung A 64 ULTRA  => PRICE : 120000 RS "  << endl;
    cout<< "  (13) Samsung NOTE 7      => PRICE : 89000 RS "   << endl;
    cout<< "  (14) Samsung  NOTE 10    => PRICE : 110000 RS "  << endl;
    cout<< "  (15) Samsung S24 ULTRA   => PRICE : 500000 RS "  << endl;
    cout<< "  (16) Google pixel 8 xl   => PRICE : 380000 RS "  << endl;
    cout<< "  (17) Google pixel 7xl    => PRICE : 300000 RS "  << endl;
    cout<< "  (18) Google pixel 6 pro  => PRICE : 230000 RS "  << endl;
    cout<< "  (19) Google pixel 6a     => PRICE : 180000 RS "  << endl; 
    cout<< "  (19) Google pixel 5      => PRICE : 150000 RS "  << endl; 


    cout<< " Please enter your choice " << endl;
     cin >> item;
    if ( item = '1'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 450000 ;
    }
    else ( item = '2'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 400000 ;
    }
     else  ( item = '3'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
        else  ( item = '4'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 280000 ; 
     }
        else  ( item = '5'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
        else  ( item = '6'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
        else  ( item = '7'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
        else  ( item = '8'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
        else  ( item = '9'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
        else  ( item = '10'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
        else  ( item = '11'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
        else  ( item = '12'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
        else  ( item = '13'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
        else  ( item = '14'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
        else  ( item = '15'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
        else  ( item = '16'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
        else  ( item = '17'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
        else  ( item = '18'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
        else  ( item = '19'){
        cout<< " Enter quantity " endl;
        cin >> quantity;
        billamount=billamount+ quantity* 350000 ; 
     }
      


}
