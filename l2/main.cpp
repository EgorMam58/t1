#include <iostream>
#include <string>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/filters.h>


int main(int argc, char **argv)
{

    //key from password
    std::string psw="SuperPa$$w0rd";
    std::string salt = "Соль земли русской";
    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::PKCS12_PBKDF<CryptoPP::SHA1> pbkdf;
    pbkdf.DeriveKey(key.data(), key.size(), 0, (byte*)psw.data(), psw.size(), (byte*)salt.data(), salt.size(), 1024, 0.0f);
    std::cout << "Key: ";
    CryptoPP::StringSource(key.data(), key.size(), true,
                           new CryptoPP::HexEncoder(
                               new CryptoPP::FileSink(std::cout)));
    std::cout << std::endl;


    //random IV
    CryptoPP::AutoSeededRandomPool prng;
    byte iv[ CryptoPP::AES::BLOCKSIZE ];
    prng.GenerateBlock( iv, sizeof(iv) );
    std::cout << "IV:  ";
    CryptoPP::StringSource(iv, sizeof(iv), true,
                           new CryptoPP::HexEncoder(
                               new CryptoPP::FileSink(std::cout)));
    std::cout<< std::endl;


    //cipher AES in CBC mode
    std::string plain_text = "Кто прочитает - тот молодец";
    std::string cipher_text, encoded_text, recovered_text;
    std::cout << "plaint text:     "<< plain_text << std::endl;



    //encrypt
    try {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encr;
        encr.SetKeyWithIV( key, key.size(), iv );

        CryptoPP::StringSource ss(plain_text, true,
                                  new CryptoPP::StreamTransformationFilter( encr,
                                          new CryptoPP::StringSink( cipher_text)));

    } catch(const CryptoPP::Exception& e ) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    //print result
    CryptoPP::StringSource ss( cipher_text, true,
             new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded_text)));
    std::cout << "cipher text:     "<< encoded_text << std::endl;

    //decrypt
    try {
        CryptoPP::CBC_Mode< CryptoPP::AES>::Decryption decr;
        decr.SetKeyWithIV ( key, key.size(), iv);

        CryptoPP::StringSource ss(cipher_text, true,
                                  new CryptoPP::StreamTransformationFilter(decr,
                                          new CryptoPP::StringSink (recovered_text)));

    } catch(const CryptoPP::Exception& e ) {
        std::cerr <<e.what() << std::endl;
        exit(1);
    }

    //print result
    std::cout << "recovered text:  " << recovered_text <<std::endl;
    return 0;
}

