#include <iostream>
#include <seal/seal.h>
#include <fstream>


using namespace std;
using namespace seal;



int main() {
	EncryptionParameters parms;
	ifstream finn;
	finn.open("param.txt", ios::binary);
	parms.load(finn);
	SEALContext context(parms);
	Plaintext vote;
	ifstream fp("publick.txt", ios::binary);
	PublicKey pKey;
	pKey.load(context,fp);
	Ciphertext encrypted(context);
	Encryptor encryptor(context, pKey);
	string v;
	while (1) {
		cout << "Please enter number of your candidate: " << endl;
		cin >> v;
		if (v == "1") {
			vote = 0;
			break;
		}
		else if (v == "2") {
			vote = 1;
			break;
		}
		else cout << "Incorrect input" << endl;
	}
	encryptor.encrypt(vote, encrypted);
	finn.close();
	finn.open("cipher.txt", ios::binary);
	int i = 0;
	if (finn.is_open()) {
		finn.close();
		for (i = 1;; i++) {
			finn.open("cipher("+to_string(i)+").txt", ios::binary);
			if (!finn.is_open()) break;
			finn.close();
		}
	}
	ofstream ofchtr;
	if (i == 0) ofchtr.open("cipher.txt", ios::binary);
	else {
		ofchtr.open("cipher("+to_string(i)+").txt", ios::binary);
	}
	for (int i = 0; i < 51; i++) encrypted.save(ofchtr);
	return 0;
}


