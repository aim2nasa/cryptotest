#include <gtest/gtest.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include "util.h"

void aesEcbEncDec(unsigned int keySizeInBytes) { 
	const unsigned int keySize = keySizeInBytes;
	byte key[keySize];
	memset(key,0,sizeof(key));

	std::string plainText = "ECB Mode test";

	CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption e;
	e.SetKey(key,sizeof(key));

	//encrypt given plainText
	std::string cipherText;
	CryptoPP::StringSource(plainText,true,
		new CryptoPP::StreamTransformationFilter(e,
			new CryptoPP::StringSink(cipherText)
		)
	);
	print("plain text:"+plainText);
	show("cipher text:",cipherText);
	EXPECT_NE(plainText,cipherText);

	//decrypt cipherText
	CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption d;
	d.SetKey(key,sizeof(key));

	std::string recoveredText;
	CryptoPP::StringSource(cipherText,true,
		new CryptoPP::StreamTransformationFilter(d,
			new CryptoPP::StringSink(recoveredText)
		)
	);
	print("recovered text:"+recoveredText);

	//compare decrypt result with the given plainText
	EXPECT_EQ(plainText,recoveredText);
}

TEST(AesECBTest, encryptDescrypt) { 
	aesEcbEncDec(16); //128bit(16byte)
	aesEcbEncDec(24); //192bit(24byte)
	aesEcbEncDec(32); //256bit(32byte)
}

TEST(AesECBTest, encryptDescryptUnsupportedKeySize) { 
	unsigned int keyLen=17;
	try{
		aesEcbEncDec(keyLen);
	}catch(const CryptoPP::Exception& e){
		print(e.what());
		char msg[256];
		sprintf(msg,"AES: %d is not a valid key length",keyLen);
		EXPECT_EQ(std::string(msg),e.what());
	}
}
