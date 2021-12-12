#include<SEAl/seal.h>
#include <fstream>
#include<iostream>
#include <sstream>

using namespace seal;
using namespace std;



int main() {
    EncryptionParameters parms(scheme_type::bfv);
    size_t poly_modulus_degree = 8192;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));
    parms.set_plain_modulus(PlainModulus::Batching(poly_modulus_degree, 20));
    SEALContext context(parms);
    KeyGenerator keygen(context);
    auto secret_key = keygen.secret_key();
    ofstream fout;
    fout.open("param.txt", ios::binary);
    for (int i = 0; i < 51; i++) parms.save(fout);
    ofstream ofsk("sk.txt", ios::binary);
    for (int i = 0; i < 51; i++) secret_key.save(ofsk);
    auto publick = keygen.create_public_key();
    ofstream pout("publick.txt", ios::binary);
    for (int i = 0; i < 51; i++) publick.save(pout);
    return 0;
}