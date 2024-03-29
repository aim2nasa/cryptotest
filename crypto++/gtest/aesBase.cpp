#include <gtest/gtest.h>
#include <cryptopp/aes.h>
 
TEST(AesParameterTest, defaultValues) { 
	ASSERT_EQ(0, 0);
	ASSERT_EQ((unsigned int)CryptoPP::AES::DEFAULT_KEYLENGTH, 16);
	ASSERT_EQ((unsigned int)CryptoPP::AES::BLOCKSIZE, 16);
}
