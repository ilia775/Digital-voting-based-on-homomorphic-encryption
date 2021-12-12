
#include <iostream>
#include <seal/seal.h>
#include <fstream>
using namespace std;
using namespace seal;

long int shextod(string s) {

    long len = s.length();
    long int res = 0, x, ind;

    for (int i = 0; i < len; i++) {
        ind = (int)s[len - i - 1];
        if (ind > 58) x = ind - 55;
        else x = ind - 48;
        res += x * pow(16, i);
    }
    return res;
}
 




int main() {
	EncryptionParameters parms;
	ifstream finn;
	finn.open("param.txt", ios::binary);
	parms.load(finn);
	SEALContext context(parms);
	Plaintext vote,sum;
	sum = 0;
	ifstream fp("publick.txt", ios::binary);
	PublicKey pKey;
	pKey.load(context, fp);
	Ciphertext encrypted(context),Esum(context);
	Encryptor encryptor(context, pKey);
	encryptor.encrypt(sum, Esum);
	Evaluator evaluate(context);
	ifstream ofchtr("cipher.txt", ios::binary);
	encrypted.load(context,ofchtr);
	evaluate.add_inplace(Esum, encrypted);
	SecretKey secret_key;
	ifstream ofsk("sk.txt", ios::binary);
	secret_key.load(context,ofsk);
	ofchtr.close();
	int i;
	for (i = 1;; i++) {
		ofchtr.open("cipher(" + to_string(i) + ").txt", ios::binary);
		if (!ofchtr.is_open()) break;
		encrypted.load(context, ofchtr);
		evaluate.add_inplace(Esum, encrypted);
		ofchtr.close();

	}
	Decryptor decryptor(context, secret_key);
	decryptor.decrypt(Esum, vote);
	cout << "Quntity of votes:  " << i << endl;
	cout <<"Quntity of votes for 1st candidate: " << i - shextod(vote.to_string()) << endl;
	cout << "Quntity of votes for 2nd candidate: " << shextod(vote.to_string()) << endl;
	cin.get();
	return 0;
}