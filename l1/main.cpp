#include <iostream>
#include <vector>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>
#include <cryptopp/base64.h>
int main (int argc, char* argv[])
{
    using namespace CryptoPP;

    SHA1 hash;

    std::cout << "Name: " << hash.AlgorithmName() << std::endl;
    std::cout << "Digest size: " << hash.DigestSize() << std::endl;
    std::cout << "Block size: " << hash.BlockSize() << std::endl;

    std::string msg = "Yoda said, Do or do not. There is no try.";

    std::vector<byte> digest(hash.DigestSize());

    hash.Update((const byte*)msg.data(), msg.size());
    hash.Final(digest.data());

    std::cout << "Message: " << msg << std::endl;

    std::cout << "Digest: ";
    StringSource(digest.data(), digest.size(), true, 
        new Base64Encoder(new FileSink(std::cout)));
    std::cout << std::endl;
    return 0;
}
