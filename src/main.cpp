#include "cbuffer.h"
#include <iostream>
#include <cassert>
#include <cstring>
#include <vector>
#include <iterator>
#include <functional>


void testDefault() {

	std::cout << "\n\n   ---TEST COSTRUTTORE DI DEFAULT---" << std::endl;
	std::cout << "Costruttore di default" << std::endl;
	cbuffer<int> c;
	cbuffer<double> c1;
	cbuffer<bool> c2;
	cbuffer<std::string> c3;
}

void testSecondario (){
	std::cout << "\n\n\n   ---TEST COSTRUTTORE SECONDARIO---" << std::endl;
	std::cout << "Costruttore secondario" << std::endl;
	cbuffer<int> c1(5);
	cbuffer<double> c2(10);
	cbuffer<bool> c3(2);
	cbuffer<std::string> c4(8);
}

void testInserimenti() {
	std::cout << "\n\n\n   ---TEST INSERIMENTI---" << std::endl;

	std::cout << "Istanzio un cbuffer tramite costruttore secondario" << std::endl;
	cbuffer<int> c1(5);

	std::cout << "Testo degli inserimenti in sequenza, oltre alla dimensione massima del cbuffer" << std::endl;
	c1.insert(16);
	c1.insert(12);
	c1.insert(32);
	c1.insert(24);
	c1.insert(53);
	c1.insert(86);
	c1.insert(71);
	c1.insert(1);
	c1.insert(16);
	c1.insert(12);
	c1.insert(32);
	c1.insert(24);
	c1.insert(53);
	std::cout << "Stampo il cbuffer dopo gli inserimenti" << std::endl;
	for(int i=0; i < c1.getElements(); i++){
		std::cout << c1[i] << " ";
	}
	std::cout << "\n";
}

void testSize() {
	std::cout << "\n\n\n   ---TEST SIZE E ELEMENTS---" << std::endl;
	std::cout << "Testo il copy constructor e verifico il numero di inserimenti" << std::endl;

	cbuffer<std::string> c3(8);

	c3.insert("ciao");
	c3.insert("due");
	c3.insert("prova abc");

	cbuffer<std::string> c4(c3);

	std::cout<< "Testo getSize() " << c4.getSize() << std::endl;
	std::cout << "Testo getElements() " << c4.getElements() << std::endl;
}

void testCopia() {

	std::cout << "\n\n\nTesto il copy constructor" << std::endl;
	cbuffer<bool> c(10);

	for(int i=0; i<13; i++){
		c.insert(true);
	}

	cbuffer<bool> c1(c);
	c1[0] = false;
	cbuffer<bool> c2;

	std::cout << "\n\n\n";
}

void testRimozioni() {

	std::cout << "\n\n\n   ---TEST RIMOZIONI---" << std::endl;

	std::cout << "Testo una serie di inserimenti/rimozioni/copie." << std::endl;
	std::cout << "Istanzio c1 tramite costruttore secondario." << std::endl;
	cbuffer<int> c1(5);

	c1.insert(16);
	c1.insert(12);
	c1.insert(32);
	c1.insert(24);
	c1.insert(53);
	c1.insert(86);
	c1.insert(71);

	std::cout << "Stampo c1" << std::endl;
	for(int i=0; i < c1.getElements(); i++){
		std::cout << c1[i] << " ";
	}

	std::cout << "\n";

	std::cout << "Testo delle rimozioni in testa" << std::endl;
	c1.deleteFromHead();
	c1.deleteFromHead();
	c1.deleteFromHead();
	c1.deleteFromHead();

	std::cout << "Inserisco altri elementi" << std::endl;

	c1.insert(1);
	c1.insert(16);
	c1.insert(12);
	c1.insert(32);
	c1.insert(24);
	c1.insert(53);

	std::cout << "Stampo c1" << std::endl;
	for(int i=0; i < c1.getElements(); i++){
		std::cout << c1[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Genero una copia  c2 del cbuffer tramite copy constructor" << std::endl;

	cbuffer<int> c2(c1);

	std::cout << "Stampo c2" << std::endl;
	for(int i=0; i < c2.getElements(); i++){
		std::cout << c2[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Modifico il secondo elemento del primo cbuffer con l'operatore di accesso []" << std::endl;
	c1[1] = 120;

	std::cout << "Stampo stampo il cbuffer modificato" << std::endl;
	for(int i=0; i < c1.getElements(); i++){
		std::cout << c1[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Stampo il buffer istanziato con  copy constructor per verificare che i due cbuffer non abbiano condivisione di memoria" << std::endl;
	for(int i=0; i < c2.getElements(); i++){
		std::cout << c2[i] << " ";
	}
	std::cout << "\n";

	std::cout << "Eseguo due rimozioni in testa da c2" << std::endl;
	c2.deleteFromHead();
	c2.deleteFromHead();

	std::cout << "Stampo c2 dopo la cancellazione" << std::endl;
	for(int i=0; i < c2.getElements(); i++){
		std::cout << c2[i] << " ";
	}
}

void testAccesso() {

	std::cout << "\n\n\n   ---TEST ACCESSO---" << std::endl;
	cbuffer<int> c(5);

	c.insert(1);
	c.insert(2);
	c.insert(3);
	c.insert(4);
	c.insert(5);

	std::cout << "primo: " << c[0] << std::endl;
	std::cout << "secondo: " << c[1] << std::endl;
	std::cout << "terzo: " << c[2] << std::endl;
	std::cout << "quarto: " << c[3] << std::endl;
	std::cout << "quinto: " << c[4] << std::endl;
}

void testrandom() {

	std::cout << "\n\n\nTest di funzioni varie (accesso, inserimento)" << "\n";
	cbuffer<int> c(5);
	c.insert(1);
	std::cout << c[0] << std::endl;
	c.insert(2);
	std::cout << c[1] << std::endl;
	c.insert(3);
	std::cout << c[2] << std::endl;
	c.insert(4);
	std::cout << c[3] << std::endl;
	c.insert(5);
	std::cout << c[4] << std::endl;
	for(int i=0; i < c.getSize(); i++){
		std::cout << c[i] << " ";
	}
	std::cout << std::endl;
	c.insert(6);
	for(int i=0; i < c.getSize(); i++){
		std::cout << c[i] << " ";
	}
	std::cout << std::endl;
	c.insert(7);
	for(int i=0; i < c.getSize(); i++){
		std::cout << c[i] << " ";
	}
}

void testAssegnamento() {

	std::cout << "\n\n\n   ---TEST ASSEGNAMENTO---" << std::endl;

	std::cout << "Istanzio un cbuffer tramite costruttore secondario (size = 10)" << "\n";
	cbuffer<int> c1(10);

	std::cout << "Lo riempio con 100 elementi" << "\n";
	for(int i = 0; i < 100; i++) {
		c1.insert(i);
	}

	std::cout << "Verifico la struttura" << std::endl;
	for(int i=0; i < c1.getElements(); i++){
		std::cout << c1[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Istanzio un cbuffer vuoto (costruttore default)" << "\n";
	cbuffer<int> c2;

	std::cout << "eseguo l'assegnamento del buffer popolato al buffer vuoto" << "\n";
	c2 = c1;
	std::cout << "Modifico il primo buffer e stampo il secondo per verificare eventale condivisione di memoria" << "\n";
	c1[0] = 100;

	for(int i=0; i < c2.getElements(); i++){
		std::cout << c2[i] << " ";
	}
	std::cout << std::endl;
}

void testStampaIteratori() {

	std::cout << "\n\n\n   ---TEST STAMPA ITERATORI---" << "\n";

	cbuffer<int> c(10);

	for(int i = 0; i < 100; i++) {
		c.insert(i);
	}

	std::cout << "Stampo con ciclo for" << "\n";
	for(int i=0; i < c.getElements(); i++){
		std::cout << c[i] << " ";
	}
	std::cout << "\n\nRimuovo 5 elementi in testa\n";
	c.deleteFromHead();
	c.deleteFromHead();
	c.deleteFromHead();
	c.deleteFromHead();
	c.deleteFromHead();
	std::cout << "\nStampo con iteratori\n";

	std::cout << c << "\n";

	std::cout << "Inserisco altri elementi (buffer sicuramente pieno)\n";

	for(int i=0; i<5; i++){
		c.insert(i+100);
	}

	std::cout << "\nStampo il cbuffer modificato con iteratori\n";
	std::cout << c << "\n";

	std::cout << "\n\nRimuovo 5 elementi in testa\n";
	c.deleteFromHead();
	c.deleteFromHead();
	c.deleteFromHead();
	c.deleteFromHead();
	c.deleteFromHead();


	std::cout << "\n\nStampo con ciclo for" << "\n";
	for(int i=0; i < c.getElements(); i++){
		std::cout << c[i] << " ";
	}

	std::cout << "\n\n\nStampo con iteratori\n";

	std::cout << c << "\n\n";
}

void testCostruttoreIteratori(){

	std::cout << "\n   ---TEST COSTRUTTORE DA SEQUENZA---\n";

	int arr[5] = {1,2,3,4,5};

	cbuffer<int> c1(10, arr, arr+5)	;

	std::cout << "\nStampo il cbuffer di int\n" << c1 << std::endl;

	std::string stringhe[10] = {"uno", "due", "tre", "quattro", "cinque", "sei", "sette", "otto", "nove", "dieci"};

	cbuffer<std::string> c2(8, stringhe, stringhe+10);
	std::cout << "\nStampo il cbuffer di stringhe\n" << c2 << std::endl;

	bool verofalso[9] = {true, false, false, true, true, false, false, true, false};
	cbuffer<bool> c3(8, verofalso, verofalso+9);
	std::cout << "\nStampo il cbuffer di bool\n" << c3 << std::endl;
}

void testScritturaIteratori(){

	std::cout << "\n\n\n---TEST SCRITTURA ITERATORI---\n\n";

	std::cout << "\nIstanzio un cbuffer con elementi da 0 a 30\n";
	int v[31] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
	cbuffer<int> c(31, v, v+31);

	std::cout << "\nStampo il cbuffer\n";
	std::cout << c;

	std::cout << "\n\nScrivo tramite iteratori valori decrescenti a partire da 42\n";
	cbuffer<int>::iterator ib = c.begin();
	cbuffer<int>::iterator ie = c.end();

	for(int i = 42; ib != ie ; ib++){
		ib.insert(i);
		i--;
	}
	std::cout << "\nStampo il cbuffer dopo la scrittura\n" << c << "\n";
}

bool isEven(int x){
	if(x%2 == 0)
		return true;
	return false;
};

bool isOdd(int x){
	if(x%2 != 0)
		return true;
	return false;
};

char isVowel(char c){
	if( c == 'a' ||
	   	c == 'e' ||
   		c == 'i' ||
		c == 'o' ||
		c == 'u')
		return true;
	return false;
};

void testEvaluateif () {
	std::cout << "\n\n   ---TEST EVALUATE_IF---\n\n";

	int v[] = {11,23,34,42,15,61,37,84,95,102,116,152,3,14,95};
	cbuffer<int> c(15, v, v+15);
	std::cout << "Buffer di interi c\n";
	std::cout<< c << "\n\n\n";
	std::cout << "evaluate_if(c, isEven)\n\n";
	evaluate_if(c, isEven);
	std::cout << "\n\n\nevaluate_if(c, isOdd)\n\n";
	evaluate_if(c, isOdd);

	char v1[] = {'a','b','c','e','f','g','h','i','j','k','l','m','n'};
	cbuffer<char> c1(13, v1, v1+13);
	std::cout << "\n\n\nBuffer di char c1\n";
	std::cout<< c1 << "\n\n\n";
	std::cout << "evaluate_if(c1, isVowel)\n\n";
	evaluate_if(c1, isVowel);
	std::cout << "\n\n\n\n";

}

int main () {

	testDefault();

	testSecondario();

	testCopia();

	testSize();

	testInserimenti();

	testAccesso();

	testrandom();

	testAssegnamento();

	testRimozioni();

	testStampaIteratori();

	testCostruttoreIteratori();

	testScritturaIteratori();

	testEvaluateif();

	return 0;
}
